#include "imageprocessing.h"
#include "ui_imageprocessing.h"

#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QWheelEvent>
#include <QDebug>
#include <QPdfWriter>
#include <QPagedPaintDevice>
#include <QTextDocument>
#include <QPainter>
#include <QDate>
#include <thread>
#include <chrono>

#include "C:/Users/a/AppData/Local/Programs/MVTec/HALCON-24.11-Progress-Steady/include/halconcpp/HalconCpp.h"

using namespace HalconCpp;

imageprocessing::imageprocessing(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::imageprocessing)
{
    ui->setupUi(this);

    // 信号槽
    connect(ui->pBsetImagePath, &QPushButton::clicked, this, &imageprocessing::pbSetImagePath);
    connect(ui->pbSetRoi,       &QPushButton::clicked, this, &imageprocessing::pbSetRoi);
    connect(ui->pBimagesProcess,&QPushButton::clicked, this, &imageprocessing::pbImageProcess);
    connect(ui->pBtestReport,   &QPushButton::clicked, this, &imageprocessing::pbTestReport);
    connect(ui->pbCleanRoi,   &QPushButton::clicked, this, &imageprocessing::pbCleanRoi);

    ui->lbprocessImage->setWordWrap(true);
    QTimer::singleShot(0, this, &imageprocessing::init);

    // 初始化 rubberBand（但不显示）
    rubberBand = new QRubberBand(QRubberBand::Rectangle, ui->gVimageprocess->viewport());

    // 初始化 scene & view
    scene = new QGraphicsScene(this);
    ui->gVimageprocess->setScene(scene);

    // 缩放锚点 & 拖动 & 滚动条
    ui->gVimageprocess->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    ui->gVimageprocess->setDragMode(QGraphicsView::ScrollHandDrag);
    ui->gVimageprocess->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->gVimageprocess->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    // 全局安装 filter，拦截滚轮及鼠标点击/移动
    ui->gVimageprocess->viewport()->installEventFilter(this);


}

imageprocessing::~imageprocessing()
{
    delete ui;
}

void imageprocessing::init()
{
    // 加载上次路径
    settings = new QSettings("MyCompany", "MyApp", this);
    ascanImagePath = settings->value("ascanImagePath", "").toString();
    ui->lbprocessImage->setText(ascanImagePath);

    // 如果已有路径，则载入
    if (!ascanImagePath.isEmpty()) {
        QPixmap pix(ascanImagePath);
        scene->clear();
        scene->addPixmap(pix);
        scene->setSceneRect(pix.rect());
        ui->gVimageprocess->fitInView(pix.rect(), Qt::KeepAspectRatio);
    }
}

void imageprocessing::pbSetImagePath()
{
    QString path = QFileDialog::getOpenFileName(
                this,
                tr("Open Image File"),
                ascanImagePath.isEmpty() ? QDir::homePath() : ascanImagePath,
                tr("Image Files (*.png *.jpg *.jpeg *.bmp *.tif *.tiff *.gif);;All Files (*.*)")
                );
    if (path.isEmpty()) return;

    ascanImagePath = path;

    settings->setValue("ascanImagePath", ascanImagePath);
    ui->lbprocessImage->setText(ascanImagePath);

    QPixmap pix(path);
    scene->clear();
    scene->addPixmap(pix);
    scene->setSceneRect(pix.rect());
    ui->gVimageprocess->fitInView(pix.rect(), Qt::KeepAspectRatio);
}

void imageprocessing::pbSetRoi()
{
    // 切换到 ROI 模式
    isSettingRoi = true;
    isFirstClick = true;
}


void imageprocessing::pbCleanRoi(){

    // 清空ROI列表
    roiRects.clear();
    QList<QGraphicsItem *> allItems = ui->gVimageprocess->items();
    for (QGraphicsItem *item : allItems) {
        // 可根据类型过滤（例如只删除矩形）
        if (dynamic_cast<QGraphicsRectItem *>(item))
            scene->removeItem(item);
    }
    update();

}



bool imageprocessing::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->gVimageprocess->viewport()) {
        // 1) 滚轮缩放 —— 不论是否在 ROI 模式，都可用
        if (event->type() == QEvent::Wheel) {
            auto we = static_cast<QWheelEvent*>(event);
            constexpr qreal inF = 1.15, outF = 1.0 / inF;
            ui->gVimageprocess->scale( we->angleDelta().y() > 0 ? inF : outF,
                                       we->angleDelta().y() > 0 ? inF : outF );
            return true;
        }

        // 以下为 ROI 模式时才处理
        if (!isSettingRoi)
            return QWidget::eventFilter(obj, event);

        // 2) 第一次点击：记录左上角
        if (event->type() == QEvent::MouseButtonPress) {
            auto me = static_cast<QMouseEvent*>(event);

            // 第一次点击
            if (isFirstClick) {
                originView  = me->pos();
                originScene = ui->gVimageprocess->mapToScene(originView);
                rubberBand->setGeometry(QRect(originView, QSize()));
                rubberBand->show();
                isFirstClick = false;
            }
            // 第二次点击
            else {
                QPointF endScene = ui->gVimageprocess->mapToScene(me->pos());
                QRectF sceneRoi(originScene, endScene);
                sceneRoi = sceneRoi.normalized();
                scene->addRect(sceneRoi, QPen(Qt::red));

                QRect imageRoi = convertToImageCoordinates(sceneRoi);
                qDebug() << "ROI in image coords:" << imageRoi;
                roiRects.append(imageRoi);

                rubberBand->hide();
                isSettingRoi = false;
            }
            return true;
        }

        // 3) 鼠标移动 —— 更新 rubberBand 大小
        if (event->type() == QEvent::MouseMove && !isFirstClick) {
            auto me = static_cast<QMouseEvent*>(event);
            QRect r(originView, me->pos());
            rubberBand->setGeometry(r.normalized());
            return true;
        }
    }

    return QWidget::eventFilter(obj, event);
}


bool IsImage(const HObject& obj) {
    try {
        HTuple width, height;
        GetImageSize(obj, &width, &height);
        return true;  // 能取大小，说明是图像
    } catch (...) {
        return false; // 异常说明不是图像，可能是区域等
    }
}
void TestShow(const HObject& image) {
    try {
        HTuple width, height, windowHandle;

        if (IsImage(image)) {
            // 是图像，直接获取大小
            GetImageSize(image, &width, &height);
        }
        else {
            // 不是图像，尝试当区域处理，获取外接矩形大小
            HTuple row1, col1, row2, col2;
            SmallestRectangle1(image, &row1, &col1, &row2, &col2);
            width = col2 - col1 + 1;
            height = row2 - row1 + 1;
        }

        int w = width.I();
        int h = height.I();

        // 打开窗口
        OpenWindow(0, 0, w, h, 0, "visible", "", &windowHandle);
        // 设置显示区域
        SetPart(windowHandle, 0, 0, h - 1, w - 1);

        if (IsImage(image)) {
            DispObj(image, windowHandle);
        }
        else {
            // 区域显示需要转成图像，先生成背景，再涂色
            HObject background, painted;
            GenImageConst(&background, "byte", w, h);
            PaintRegion(image, background, &painted, 255, "fill");
            DispObj(painted, windowHandle);
        }

        WaitSeconds(5.0);

        CloseWindow(windowHandle);
    }
    catch (HException& e) {
        std::cerr << "Halcon异常: " << e.ErrorMessage() << std::endl;
    }
}

void SaveRegionAsImage(const HObject &region, const std::string &filename)
{
    try
    {
        std::cout << "[INFO] 开始保存区域图片: " << filename << std::endl;

        // 先合并区域，避免多个子区域引起参数错误
        HObject unionRegion;
        Union1(region, &unionRegion);

        // 计算合并后区域面积及中心
        HTuple areas, rows, cols;
        AreaCenter(unionRegion, &areas, &rows, &cols);
        if (areas.Length() == 0 || areas[0].D() == 0.0)
        {
            std::cerr << "[ERROR] 区域为空，不能保存图片" << std::endl;
            return;
        }
        std::cout << "[INFO] 区域面积数量: " << areas.Length() << ", 第一个面积: " << areas[0].D() << std::endl;

        // 获取最小外接矩形框
        HTuple row1, col1, row2, col2;
        SmallestRectangle1(unionRegion, &row1, &col1, &row2, &col2);
        std::cout << "[INFO] 最小外接矩形坐标: (" << row1.D() << ", " << col1.D() << ") - (" << row2.D() << ", " << col2.D() << ")" << std::endl;

        int width = col2.I() - col1.I() + 1;
        int height = row2.I() - row1.I() + 1;
        if (width <= 0 || height <= 0)
        {
            std::cerr << "[ERROR] 计算出的宽高不合理: width=" << width << ", height=" << height << std::endl;
            return;
        }
        std::cout << "[INFO] 目标图像尺寸: " << width << " x " << height << std::endl;

        // 创建黑色背景图像
        HObject background;
        GenImageConst(&background, "byte", width, height);

        // 移动区域，使其左上角对齐到图像(0,0)
        HObject shiftedRegion;
        HTuple negRow1 = -row1;
        HTuple negCol1 = -col1;
        std::cout << "[INFO] 移动区域偏移量: (" << negRow1.D() << ", " << negCol1.D() << ")" << std::endl;
        MoveRegion(unionRegion, &shiftedRegion, negRow1, negCol1);

        // 用白色填充区域
        HObject painted;
        PaintRegion(shiftedRegion, background, &painted, 255, "fill");

        // 保存图片，-1表示默认压缩
        WriteImage(painted, "png", -1, filename.c_str());

        std::cout << "[INFO] 区域保存成功: " << filename << std::endl;
    }
    catch (HException &e)
    {
        std::cerr << "[EXCEPTION] 保存区域图片异常: " << e.ErrorMessage() << std::endl;
    }
}

void imageprocessing::pbImageProcess()
{
    QDir dir(QCoreApplication::applicationDirPath() + "/date/workpice/");
    if (!dir.exists())
        dir.mkpath(".");

    outputImagePath = dir.absoluteFilePath(workPice + ".png");
    qDebug() << "outputImagePath" << outputImagePath;

    qDebug() << "pbImageProcess started";
    defects.clear();

    HObject ho_Image;
    try {
        qDebug() << "Reading image from path:" << ascanImagePath;
        ReadImage(&ho_Image, ascanImagePath.toStdString().c_str());
    } catch (HException &e) {
        qDebug() << "[Error] Image read failed:" << e.ErrorMessage().Text();
        return;
    }

    HTuple imgWidth, imgHeight;
    GetImageSize(ho_Image, &imgWidth, &imgHeight);
    double totalArea = imgWidth.D() * imgHeight.D();

    qDebug() << "Image size:" << imgWidth.D() << "x" << imgHeight.D();
    qDebug() << "Total image area:" << totalArea;

    // 拷贝显示图像用于后期标注
    HObject ho_R, ho_G, ho_B;
    try {
        Decompose3(ho_Image, &ho_R, &ho_G, &ho_B);
    } catch (HException &e) {
        qDebug() << "[Error] Decompose3 failed:" << e.ErrorMessage().Text();
        return;
    }


    for (int i = 0; i < roiRects.size(); ++i) {
        const QRect &r = roiRects[i];
        qDebug() << "Processing ROI #" << i+1 << ":" << r;

        HObject ho_ROI;
        GenRectangle1(&ho_ROI, HTuple(r.top()), HTuple(r.left()), HTuple(r.bottom()), HTuple(r.right()));
        qDebug() << "Generated rectangle ROI";

        HObject ho_Dom;
        ReduceDomain(ho_Image, ho_ROI, &ho_Dom);
        qDebug() << "Reduced domain to ROI";

        HObject ho_Gray;
        HTuple channels;
        CountChannels(ho_Dom, &channels);
        if (channels == 3) {
            Rgb1ToGray(ho_Dom, &ho_Gray);
            qDebug() << "Converted RGB to grayscale";
        } else {
            CopyImage(ho_Dom, &ho_Gray);
            qDebug() << "Image is already grayscale";
        }


        HObject ho_Thresh;
        double sigma_val = 0.5;

        AutoThreshold(ho_Gray, &ho_Thresh, HTuple(sigma_val));
        qDebug() << "AutoThreshold succeeded with sigma =" << sigma_val;

SaveRegionAsImage(ho_Thresh,"ho_Thresh.png");

        HObject ho_Conn, ho_Sel;
        Connection(ho_Thresh, &ho_Conn);
        SelectShape(ho_Conn, &ho_Sel, "area", "and", 20.0, totalArea);
        qDebug() << "Connected & selected regions";


        HTuple areas, rows, cols;
        AreaCenter(ho_Sel, &areas, &rows, &cols);
        for (int j = 0; j < areas.Length(); ++j) {
            double a = areas[j].D();
            double ratio = a / totalArea;
            qDebug() << QString("Defect %1: area=%2 ratio=%3%")
                        .arg(defects.size() + 1).arg(a).arg(ratio * 100.0, 0, 'f', 3);
            defects.push_back({ (int)defects.size() + 1, a, ratio });
        }

        HTuple regionCount;
        CountObj(ho_Sel, &regionCount);
        qDebug() << "Region count:" << regionCount.I();

        for (int j = 0; j < regionCount; ++j) {
            try {
                HObject hoSingleRegion;
                SelectObj(ho_Sel, &hoSingleRegion, j + 1);

                HTuple row1, col1, row2, col2;
                SmallestRectangle1(hoSingleRegion, &row1, &col1, &row2, &col2);
                qDebug() << "Rectangle coords:" << row1.D() << col1.D() << row2.D() << col2.D();

                HObject hoSingleRect;
                GenRectangle1(&hoSingleRect, row1, col1, row2, col2);

                // Paint 到 R 通道（仅 margin 不填充）
                PaintRegion(hoSingleRect, ho_R, &ho_R, 255, "margin");

            } catch (HException &e) {
                qDebug() << "[Error] PaintRegion error:" << e.ErrorMessage().Text();
            }
        }
    }

    // 合并图像
    HObject ho_Vis;
    try {
        Compose3(ho_R, ho_G, ho_B, &ho_Vis);
        qDebug() << "Channels composed successfully";

        WriteImage(ho_Vis, "png", 0, outputImagePath.toStdString().c_str());
        qDebug() << "Image saved to:" << outputImagePath;

    } catch (HException &e) {
        qDebug() << "[Error] Compose or Write failed:" << e.ErrorMessage().Text();
    }

    qDebug() << "pbImageProcess finished";
}

void imageprocessing::pbTestReport()
{
    QPdfWriter pdfWriter(pdfOutputPath);
    pdfWriter.setPageSize(QPagedPaintDevice::A4);
    pdfWriter.setResolution(300);

    QTextDocument doc;
    QString html;
    html += R"(
            <h2 align="center">相控阵超声检测报告</h2>
            <table border="1" cellpadding="4" cellspacing="0" width="100%">
            <tr><td>报告编号：</td><td></td>
            <td>检测日期：</td><td>)" + QDate::currentDate().toString("yyyy-MM-dd") + R"(</td></tr>
                                                                                 <tr><td>委托单位：</td><td></td>
                                                                                 <td>工件编号：</td><td></td></tr>
                                                                                 </table>
                                                                                 <h3>缺陷列表</h3>
                                                                                 <table border="1" cellpadding="4" cellspacing="0" width="100%">
                                                                                 <tr><th>序号</th><th>面积 (px²)</th><th>占比</th></tr>
                                                                                 )";

    for (const auto &d : defects) {
        html += QString("<tr><td>%1</td><td>%2</td><td>%3%</td></tr>")
                .arg(d.idx)
                .arg(d.area, 0, 'f', 1)
                .arg(d.ratio * 100.0, 0, 'f', 2);
    }

    html += R"(</table>
            <h3>检测结果图</h3>
            <p><img src=")" + outputImagePath + R"(" width="600"/></p>
                                                )";

    doc.setHtml(html);
    QPainter painter(&pdfWriter);
    doc.drawContents(&painter);
}

void imageprocessing::ShowImg(const HObject& ho_Gray) {
    try {
        // 获取图像尺寸
        HTuple imgWidth, imgHeight;
        GetImageSize(ho_Gray, &imgWidth, &imgHeight);

        HTuple minVal, maxVal, meanVal, deviation;
        HTuple range;

        // 创建全图区域
        HObject region;
        GenRectangle1(&region, 0, 0, imgHeight - 1, imgWidth - 1);

        // 传入具体的百分比参数，比如 0
        MinMaxGray(region, ho_Gray, 0, &minVal, &maxVal, &range);
        Intensity(region, ho_Gray, &meanVal, &deviation);

        qDebug() << "灰度图 最小值：" << minVal.D();
        qDebug() << "灰度图 最大值：" << maxVal.D();
        qDebug() << "灰度图 平均值：" << meanVal.D();
        qDebug() << "灰度图 标准差：" << deviation.D();

        // 打开窗口
        HTuple hv_WindowID;
        SetWindowAttr("background_color", "black");
        OpenWindow(0, 0, imgWidth, imgHeight, 0, "", "", &hv_WindowID);

        SetPart(hv_WindowID, 0, 0, imgHeight - 1, imgWidth - 1);


        // 显示原图
        ClearWindow(hv_WindowID);
        DispObj(ho_Gray, hv_WindowID);
        WriteImage(ho_Gray, "png", 0, "test_gray.png");

        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    } catch (HException &e) {
        qDebug() << "显示阈值图出错：" << e.ErrorMessage().Text();
    }
}


