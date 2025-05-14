#ifndef TGRAPHICSVIEWREFACTOR_H
#define TGRAPHICSVIEWREFACTOR_H

#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <qmath.h>
class QGraphicsView;


//! 重构视图
class TGraphicsViewRefactor:public QGraphicsView
{
    Q_OBJECT
public:
    TGraphicsViewRefactor(QWidget *parent = nullptr);

    //! 设置一个默认item作为参照
    void SetDefaultItem();


protected:
    //! 缩放
    void wheelEvent(QWheelEvent *event) override;

    //! 重绘
    void paintEvent(QPaintEvent *event) override;

    //! 拖拽视窗
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event);
private:
    //! 布景
    //! 上标尺
    void DrawHorizonRuler(QPainter &painter);
    //! 左标尺
    void DrawVerticalRuler(QPainter &painter);
    //! 左上角 图标
    void DrawRuleCross(QPainter &painter);
    //! 竖线栅栏
    void DrawHorGridLine(QPainter &painter);
    //! 横线栅栏
    void DrawVerGridLine(QPainter &painter);


    void DrawCanvasRect(QPainter &painter);


    double factor;
//signals:

//    void sendFactor();

    ///鼠标移动坐标
    QPointF C_Movepos;
    ///鼠标点击坐标
    QPointF C_Downpos;
    ///视窗正在拖拽移动
    bool IsMoveView=false;

signals:
    void zoomChanged(qreal newZoom);
};

#endif // TGRAPHICSVIEWREFACTOR_H
