#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <QWidget>
#include <QMouseEvent>
#include <QRubberBand>
#include <QGraphicsScene>
#include <QSettings>

#include "C:/Users/a/AppData/Local/Programs/MVTec/HALCON-24.11-Progress-Steady/include/halconcpp/HalconCpp.h"

using namespace HalconCpp;

struct Defect {
    int idx;          // 缺陷编号
    double area;      // 面积
    double ratio;     // 面积占比
    double x;       // 缺陷中心 X 坐标
    double y;       // 缺陷中心 Y 坐标
    double length;    // 外接矩形高度（行差）
    double  width;     // 外接矩形宽度（列差）
};


namespace Ui {
class imageprocessing;
}

class imageprocessing : public QWidget
{
    Q_OBJECT

public:
    explicit imageprocessing(QWidget *parent = nullptr);
    ~imageprocessing();

    QString workPice;
    QString saveImagePath;
    QString xldPath;

    double  regionArea;

    HObject ho_OriginImage;
    HTuple windowHandle;
    double contourArea;
protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void init();
    void pbSetImagePath();
    void pbSetRoi();
    void pbCleanRoi();

    void pbImageProcess();
    void pbTestReport();
    double action( );

private:

    QVector<QRect> roiRects;
    QString pdfOutputPath;
    QVector<Defect> defects;

public:
    Ui::imageprocessing *ui;
    QGraphicsScene     *scene         = nullptr;
    QRubberBand        *rubberBand    = nullptr;
    QSettings          *settings      = nullptr;

    // ROI 状态
    bool  isSettingRoi = false;
    bool  isFirstClick = true;
    bool  isDraw;
    bool  windowOpened=false;
    QPoint originView;     // 在 viewport 坐标系下的起点
    QPointF originScene;   // 在 scene 坐标系下的起点


    QPoint originView_draw_contours;
    QPointF originScene_draw_contours;

    QString ascanImagePath;

    // scene→image 1:1 映射时直接用 sceneRoi.toRect()
    QRect convertToImageCoordinates(const QRectF &sceneRoi) { return sceneRoi.toRect(); }
    void ShowImg(const HObject& region) ;
    void SaveRegionAsImage(const HObject &region, QString filename);
};

#endif // IMAGEPROCESSING_H
