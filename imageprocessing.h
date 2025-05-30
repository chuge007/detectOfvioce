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
    int idx;
    double area;
    double ratio;
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
protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void init();
    void pbSetImagePath();
    void pbSetRoi();
    void pbCleanRoi();

    void pbImageProcess();
    void pbTestReport();

private:

    QVector<QRect> roiRects;
    QString outputImagePath;
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
    QPoint originView;     // 在 viewport 坐标系下的起点
    QPointF originScene;   // 在 scene 坐标系下的起点

    QString ascanImagePath;

    // scene→image 1:1 映射时直接用 sceneRoi.toRect()
    QRect convertToImageCoordinates(const QRectF &sceneRoi) { return sceneRoi.toRect(); }
    void ShowImg(const HObject& region) ;
};

#endif // IMAGEPROCESSING_H
