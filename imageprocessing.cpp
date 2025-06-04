#include "imageprocessing.h"
#include "ui_imageprocessing.h"

#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QWheelEvent>
#include <QDebug>
#include <QPdfWriter>
#include <QPagedPaintDevice>
#include <QPrinter>
#include <QPainter>
#include <QTextDocument>
#include <QString>
#include <QDate>
#include <QFont>
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


    saveImagePath = QCoreApplication::applicationDirPath() + "/date/image/";

    QDir dir(saveImagePath);
    if (!dir.exists()) {
        if (!dir.mkpath(saveImagePath)) {
            qDebug() << "Failed to create directory:" << saveImagePath;
            return;
        }
    }
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

void imageprocessing::SaveRegionAsImage(const HObject &region, const std::string &filename){
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
            std::cerr << " [ERROR] 区域为空，不能保存图片 " << std::endl;
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

        std::string imageFilename= saveImagePath.toStdString()+filename;
        // 保存图片，-1表示默认压缩
        WriteImage(painted, "png", -1, imageFilename.c_str());

        std::cout << "[INFO] 区域保存成功: " << filename << std::endl;
    }
    catch (HException &e)
    {
        std::cerr << "[EXCEPTION] 保存区域图片异常: " << e.ErrorMessage() << std::endl;
    }
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

        WaitSeconds(5.0);

        saveImagePath=saveImagePath+"ho_Gray";
        WriteImage(ho_Gray, "png", 0, saveImagePath.toStdString().c_str());

        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    } catch (HException &e) {
        qDebug() << " 显示阈值图出错： " << e.ErrorMessage().Text();
    }
}

void imageprocessing::pbImageProcess()
{

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
        double sigma_val = 1;

        //AutoThreshold(ho_Gray, &ho_Thresh, HTuple(sigma_val));
        BinThreshold(ho_Gray, &ho_Thresh);
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
            double x = cols[j].D();  // 列，对应横坐标
            double y = rows[j].D();  // 行，对应纵坐标

            // 提取第 j 个子区域
            HObject singleRegion;
            SelectObj(ho_Sel, &singleRegion, j + 1);

            // 计算该区域的最小外接矩形
            HTuple row1, col1, row2, col2;
            SmallestRectangle1(singleRegion, &row1, &col1, &row2, &col2);

            double width = col2.D() - col1.D();
            double height = row2.D() - row1.D();

            defects.push_back({ (int)defects.size() + 1, a, ratio,x, y ,width,height});

            qDebug() << QString("Defect %1: area=%2 ratio=%3% center=(%4, %5) size=(%6 x %7)")
                        .arg(defects.size() + 1)
                        .arg(a)
                        .arg(ratio * 100.0, 0, 'f', 3)
                        .arg(x, 0, 'f', 2)
                        .arg(y, 0, 'f', 2)
                        .arg(width, 0, 'f', 1)
                        .arg(height, 0, 'f', 1);
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

        ShowImg(ho_Vis);
        qDebug() << "Image saved to:" << saveImagePath;

    } catch (HException &e) {
        qDebug() << "[Error] Compose or Write failed:" << e.ErrorMessage().Text();
    }

    qDebug() << "pbImageProcess finished";
}



void imageprocessing::pbTestReport()
{
    QString path = QFileDialog::getSaveFileName(
        this,
        QString::fromLocal8Bit("保存检测报告"),
        QDir::homePath() + QString::fromLocal8Bit("/检测报告.pdf"),
        QString::fromLocal8Bit("PDF 文件 (*.pdf);;所有文件 (*.*)")
    );
    if (path.isEmpty()) return;

    QPrinter printer(QPrinter::ScreenResolution);
    printer.setPageSize(QPageSize(QPageSize::A4));
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageMargins(QMarginsF(20, 20, 20, 20), QPageLayout::Millimeter);
    printer.setOutputFileName(path);

    QPainter painter;
    if (!painter.begin(&printer)) return;

    QFont font(QString::fromLocal8Bit("仿宋"), 12);
    painter.setFont(font);
    painter.setPen(Qt::black);

    int lineHeight = 26;
    int y = 0;
    int pageWidth = printer.pageRect().width();

    auto drawTitle = [&](const char *title, bool bold = false) {
        QFont f = font;
        if (bold) { f.setBold(true); f.setPointSize(14); }
        painter.setFont(f);
        painter.drawText(QRect(0, y, pageWidth, lineHeight), Qt::AlignCenter, QString::fromLocal8Bit(title));
        y += lineHeight * 3;
        painter.setFont(font);
    };

    auto drawLine = [&](const char *left, int leftOffset = 0, int lineLen = 200) {
        int x = 0 + leftOffset;
        painter.drawText(x, y, QString::fromLocal8Bit(left));
        painter.drawLine(x + 100, y + 5, x + 100 + lineLen, y + 5);
        y += lineHeight * 3;
    };

    auto drawTwoCol = [&](const char *l1, const char *l2) {
        int x1 = 0;
        int x2 = pageWidth / 2;
        painter.drawText(x1, y, QString::fromLocal8Bit(l1));
        painter.drawLine(x1 + 150, y + 5, x1 + 320, y + 5);
        painter.drawText(x2, y, QString::fromLocal8Bit(l2));
        painter.drawLine(x2 + 150, y + 5, x2 + 320, y + 5);
        y += lineHeight * 3;
    };

    // === 页 1 ===
    drawTitle("相 控 阵 超 声 检 测 报 告", true);

    drawTitle("");


    drawTwoCol("报告编号：", "工程名称：");
    drawTitle("");
    drawTwoCol("检测日期：", "原始记录编号：");
    drawTitle("");
    drawTwoCol("委托单位：", "工件编号：");
    drawTitle("");

    drawTitle("工 件 参 数");
   drawTitle("");

    drawTwoCol("工件名称：", "坡口型式：");
    drawTitle("");
    drawTwoCol("焊接方法：", "检测部位：");
    drawTitle("");
    drawTwoCol("热处理状态：", "材质：");
    drawTitle("");
    drawTwoCol("规格：", "检测时机：");
    drawTitle("");

    drawTitle("技 术 要 求");
   drawTitle("");

    drawTwoCol("检测标准：", "技术等级：");
    drawTitle("");
    drawTwoCol("合格级别：", "检测比例：");
    drawTitle("");
    drawTwoCol("表面状态：", "现场温度：");
    drawTitle("");
    drawTwoCol("扫查灵敏度：", "灵敏度补偿：");

    drawTitle("检 测 器 材");
   drawTitle("");

    drawTwoCol("设备型号：", "校准试块：");
    drawTitle("");
    drawTwoCol("探头编号：", "设备编号：");
    drawTitle("");
    drawTwoCol("对比试块：", "楔块型号：");
    drawTitle("");
    drawTwoCol("耦合剂：", "模拟试块：");
    drawTitle("");
    drawLine("扫查装置：");
    drawTitle("");


    drawTitle("检 测 参 数");
    const char* params[] = {
        "材料声速：", "工件厚度：", "工件长度：", "探头频率：",
        "晶片数量：", "晶片间距：", "晶片长度：", "楔块声速：",
        "楔块角度：", "1晶片X值：", "1晶片Z值：", "正反装：",
        "激发电压：", "脉冲宽度：", "刷新频率：", "PRF：",
        "收发模式：", "滤波：", "激发孔径：", "起始角：",
        "终止角：", "聚焦模式：", "聚焦方式：", "焦距：",
        "闸门A模式：", "闸门A测量：", "闸门A起点：", "闸门A宽度：",
        "闸门A阈值：", "C扫查1数据源：", "C扫查2数据源：",
        "扫查分辨力：", "时间分辨力：", "范围起点：", "范围终点：",
        "基准增益：", "增益：", "扫查长度：", "TCG点数：",
        "工件长度：", "工件宽度：", "工件厚度："
    };
    int paramCount = sizeof(params) / sizeof(params[0]);
    for (int i = 0; i < paramCount; i += 2) {
        const char* left = params[i];
        const char* right = (i + 1 < paramCount) ? params[i + 1] : "";
        drawTwoCol(left, right);
        drawTitle("");

    }

    // === 换页 ===
    printer.newPage();
    y = 0;

    drawTitle("缺 陷 列 表");
    QStringList tableHeaders = {
        QString::fromLocal8Bit("序号"),
        QString::fromLocal8Bit("位置 mm"),
        QString::fromLocal8Bit("长度 mm"),
        QString::fromLocal8Bit("高度 mm"),
        QString::fromLocal8Bit("水平 mm"),
        QString::fromLocal8Bit("幅值 %"),
        QString::fromLocal8Bit("当量值 dB"),
        QString::fromLocal8Bit("幅值区域"),
        QString::fromLocal8Bit("缺陷性质"),
        QString::fromLocal8Bit("缺陷评定")
    };
     int colX = 0;
    int colW = pageWidth / tableHeaders.size();
    for (const QString &header : tableHeaders) {
        painter.drawText(colX, y, colW, lineHeight, Qt::AlignCenter, header);
        colX += colW;
        painter.drawRect(colX, y, colW, lineHeight);
    }


    for (const Defect &d : defects) {

        y += lineHeight;

        colX = 0;
        QStringList row = {
            QString::number(d.idx),                         // 序号
            QString::number(d.area, 'f', 2),                // 位置 mm
            QString::number(d.length, 'f', 2),              // 长度 mm
            QString::number(d.width, 'f', 2),               // 高度 mm
            QString::number(d.x, 'f', 2),                   // 水平 mm
            QString::number(d.ratio * 100.0, 'f', 2),       // 幅值 %
            "", "", "", ""                                  // 留空：当量值dB、幅值区域、缺陷性质、缺陷评定
        };

        for (int j = 0; j < row.size(); ++j) {
            painter.drawRect(colX, y, colW, lineHeight);
            painter.drawText(colX, y, colW, lineHeight, Qt::AlignCenter, row[j]);
            colX += colW;
        }


        // 自动分页
        if (y + lineHeight > printer.pageRect().height()) {
            printer.newPage();
            y = 0;

            // 重新绘制表头
            colX = 0;
            for (const QString &header : tableHeaders) {
                painter.drawText(colX, y, colW, lineHeight, Qt::AlignCenter, header);
                colX += colW;
            }
            y += lineHeight;
        }
    }




    drawTitle("结 论");
    y += lineHeight * 3;
    drawTitle("备 注");
    y += lineHeight * 3;

    drawTwoCol("检测人/资格：", "日期：");
    drawTwoCol("审核人/资格：", "日期：");
    y += lineHeight * 2;
    painter.drawText(QRect(0, y, pageWidth, lineHeight), Qt::AlignCenter, QString::fromLocal8Bit("检测机构盖章"));

    painter.end();
}







//void imageprocessing::pbTestReport()
//{
//    QString path = QFileDialog::getSaveFileName(
//        this,
//        QString::fromLocal8Bit(" 检测报告 "),  // 窗口标题
//        QDir::homePath() + QString::fromLocal8Bit("/检测报告.pdf"),   // 默认路径+文件名（无需fromLocal8Bit）
//        QString::fromLocal8Bit("PDF 文件 (*.pdf);;所有文件 (*.*)")  // 文件类型过滤器
//    );

//    qDebug() << "path:" << path;

//    if (path.isEmpty()) {
//        qDebug() << "用户取消保存";
//        return;
//    }

//    // 如果用户没有加 .pdf 后缀，则自动补全
//    if (!path.endsWith(".pdf", Qt::CaseInsensitive)) {
//        path += ".pdf";
//    }

//    pdfOutputPath = path;
//    qDebug() << "最终PDF保存路径:" << pdfOutputPath;


//    QPdfWriter pdfWriter(pdfOutputPath);
//    pdfWriter.setPageSize(QPagedPaintDevice::A4);
//    pdfWriter.setResolution(300);

//    QTextDocument doc;
//    QString html;

//    html += QString::fromLocal8Bit(
//        "<h2 align=\"center\">相控阵超声检测报告</h2>"
//        "<table border=\"1\" cellpadding=\"4\" cellspacing=\"0\" width=\"100%\">"
//        "<tr><td>报告编号：</td><td></td>"
//        "<td>检测日期：</td><td>");
//    html += QDate::currentDate().toString("yyyy-MM-dd");
//    html += QString::fromLocal8Bit(
//        "</td></tr>"
//        "<tr><td>委托单位：</td><td></td>"
//        "<td>工件编号：</td><td></td></tr>"
//        "</table>"
//        "<h3>缺陷列表</h3>"
//        "<table border=\"1\" cellpadding=\"4\" cellspacing=\"0\" width=\"100%\">"
//        "<tr><th>序号</th><th>d面积 (px²)</th><th>占比</th></tr>"
//    );

//    for (const auto &d : defects) {
//        html += QString("<tr>"
//                        "<td>%1</td>"
//                        "<td>%2</td>"
//                        "<td>%3%</td>"
//                        "<td>%4</td>"
//                        "<td>%5</td>"
//                        "<td>%6</td>"
//                        "<td>%7</td>"
//                        "</tr>")
//                .arg(d.idx)
//                .arg(d.area, 0, 'f', 1)
//                .arg(d.ratio * 100.0, 0, 'f', 2)
//                .arg(d.x, 0, 'f', 2)
//                .arg(d.y, 0, 'f', 2)
//                .arg(d.length, 0, 'f', 2)
//                .arg(d.width, 0, 'f', 2);
//    }

//    QString imageHtml = "<p><img src=\"" + saveImagePath + "\" width=\"600\"/></p>";
//    html += QString::fromLocal8Bit("</table><h3>检测结果图</h3>") + imageHtml;


//    doc.setHtml(html);
//    QPainter painter(&pdfWriter);
//    doc.drawContents(&painter);
//}
