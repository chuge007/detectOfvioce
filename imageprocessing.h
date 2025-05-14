#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <QWidget>
#include <QMouseEvent>
#include <QRubberBand>
#include <QGraphicsScene>
#include <QSettings>

namespace Ui {
class imageprocessing;
}

class imageprocessing : public QWidget
{
    Q_OBJECT

public:
    explicit imageprocessing(QWidget *parent = nullptr);
    ~imageprocessing();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void init();
    void pbSetImagePath();
    void pbSetRoi();
    void pbImageProcess();
    void pbTestReport();
    void pbCleanRoi();
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
    QVector<QRect> roiRects;

    // scene→image 1:1 映射时直接用 sceneRoi.toRect()
    QRect convertToImageCoordinates(const QRectF &sceneRoi) { return sceneRoi.toRect(); }
};

#endif // IMAGEPROCESSING_H
