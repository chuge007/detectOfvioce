#include "imageprocessing.h"
#include "ui_imageprocessing.h"

#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QWheelEvent>
#include <QDebug>

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
void imageprocessing::pbImageProcess()
{
    // TODO
}

void imageprocessing::pbTestReport()
{
    // TODO
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
