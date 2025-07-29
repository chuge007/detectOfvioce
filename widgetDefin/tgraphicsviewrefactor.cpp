#include "tgraphicsviewrefactor.h"
#include <QWheelEvent>
#include <QGraphicsSvgItem>

#include <QGraphicsRectItem>
#include <QSvgRenderer>
#include <QPainter>
#include <QDebug>
#include <QLayout>
#include <QColor>
#include <QScrollBar>
#include <QGraphicsOpacityEffect>

TGraphicsViewRefactor::TGraphicsViewRefactor(QWidget *parent)
:QGraphicsView(parent)
{
    setRenderHint(QPainter::Antialiasing);
    //setCacheMode(QGraphicsView::CacheBackground);
    setCacheMode(QGraphicsView::CacheNone);
    setScene(new QGraphicsScene());
    SetDefaultItem();

    this->setMouseTracking(true);
    setStyleSheet("margin:10");
    viewport()->setMouseTracking(true);
    setDragMode(QGraphicsView::ScrollHandDrag);  // 已设置
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse); // 缩放围绕鼠标
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    fitInView(sceneRect(), Qt::KeepAspectRatio); // 自动适配场景
}

void TGraphicsViewRefactor::SetDefaultItem()
{


}

///////////////////////////////////////////// 缩放相关  /////////////////////////////////////////////



void TGraphicsViewRefactor::wheelEvent(QWheelEvent *event)
{
     factor=qPow(1.2, event->delta() / 240.0) ;
     const qreal currentZoom = transform().m11();
     if ((factor< 1 && currentZoom < 0.1) || (factor > 1 && currentZoom > 10))
         return;
     scale(factor, factor);
     const int percent = qRound(transform().m11() * qreal(100));
     setWindowTitle("VIEW: "+QString::number(percent) + QLatin1Char('%'));

    emit zoomChanged(transform().m11());
}



///////////////////////////////////////////// 绘制背景 /////////////////////////////////////////////
#include <QStyleOptionGraphicsItem>
void TGraphicsViewRefactor::paintEvent(QPaintEvent *event)
{
//    qDebug()<<"paintEvent ------>";
//    QPainter painter(this->viewport()); // this指向QWidget，也可以是QPixmap等

//    painter.begin(this); // 调用begin()方法
//    DrawHorizonRuler(painter);
//    painter.end();



    //! 先绘制 scene() 再绘制边框 防止覆盖
    //! 绘制QGraphicsItem
    QGraphicsView::paintEvent(event);

    //! 绘制标尺
    QPainter paint(this->viewport());//这行很重要，没有这行的话，绘制出来的东西都会被view里面的其他东西遮住
    //! 每次都重复计算了步长和缩放比例D
    //! 上边 -X轴
    DrawHorizonRuler(paint);
    //! 左侧 -Y轴
    DrawVerticalRuler(paint);
    //! 左上 十符号
    DrawRuleCross(paint);
    //! 竖线
    DrawHorGridLine(paint);
    //! 横线
    DrawVerGridLine(paint);
    //!绘制 面板
    //DrawCanvasRect(paint);


    // 1. 将场景原点(0,0)转换为视图坐标
    QPoint viewOrigin = mapFromScene(QPointF(0, 0));

    // 2. 设置红色画笔
    paint.setPen(Qt::red);

    // 3. 绘制竖线（x 坐标为 viewOrigin.x()）
    paint.drawLine(QPoint(viewOrigin.x(), 0), QPoint(viewOrigin.x(), this->height()));

    // 4. 绘制横线（y 坐标为 viewOrigin.y()）
    paint.drawLine(QPoint(0, viewOrigin.y()), QPoint(this->width(), viewOrigin.y()));
}


void TGraphicsViewRefactor::DrawHorizonRuler(QPainter &painter)
{
    QPoint lefttop= QPoint(0,0);
    QPoint rigthtop=QPoint(this->width(),0);

    //! 转换成 QGraphicsScene 坐标
    QPointF scene_lefttop=mapToScene(lefttop);
    QPointF scene_rigthtop=mapToScene(rigthtop);


    float fscale = (scene_rigthtop.x() - scene_lefttop.x())*1.0 / this->width();
    int  nDistance = 100;
    nDistance = ((1.0 / fscale * 100) / 10) * 10;
    if (nDistance > 50 && nDistance < 150)
    {
        nDistance = 100;
    }
    if (nDistance >= 150 && nDistance < 200)
    {
        nDistance = 200;
    }
//    float fDistance = nDistance * 1.0*fscale;

    //! 抹除 上边框 20*width 内容
    painter.setPen(Qt::white);
    painter.setBrush(Qt::white);
    QRect rc(0, 0, this->width(), 20);
    painter.drawRect(rc);
    //! 画下边框线  --为了不出现上 左 右 三条边
    painter.setPen(Qt::black);
    painter.setBrush(Qt::white);
    painter.drawLine(QPoint(20,20),QPoint(this->width(),20));


    QPolygon Rightpoints;
    int nIndex = 0;
    for (int i =0; i < scene_rigthtop.x(); i += nDistance)
    {
        for (int j = 0; j < 10; ++j)
        {
            int nxPt = i + j * (nDistance / 10);
            QPoint viewpointX=mapFromScene(nxPt,0);
            if (viewpointX.x() < 20) //! 为了左上角的符号
                continue;
            int nyPt = 0;
            if (j == 0)
            {
                nyPt = 0;
            }
            else if (j % 5 == 0)
            {
                nyPt = 10;
            }
            else
            {
                nyPt = 15;
            }
            Rightpoints.push_back(QPoint(viewpointX.x(), 20));
            Rightpoints.push_back(QPoint(viewpointX.x(), nyPt));
            Rightpoints.push_back(QPoint(viewpointX.x(), 20));
        }
        if (i >= 0)
        {
            //! 向右偏两像素 避免被遮挡
            QPoint viewpointX=mapFromScene(i,0);
            painter.setBrush(Qt::black);
            painter.drawText(QPoint(viewpointX.x()+2, 14), QString::number(nIndex*nDistance));
        }
        nIndex++;
    }

    //////////////////////////////////////////////////////////////////////////
    QPolygon Leftpoints;
    nIndex = 0;
    for (int i =0; i > scene_lefttop.x(); i -= nDistance)
    {
        for (int j = 0; j < 10; ++j)
        {
            int nxPt = i - j * (nDistance / 10);
            QPoint viewpointX=mapFromScene(nxPt,0);
            if (viewpointX.x() < 20) //! 为了左上角的符号
                continue;
            int nyPt = 0;
            if (j == 0)
            {
                nyPt = 0;
            }
            else if (j % 5 == 0)
            {
                nyPt = 10;
            }
            else
            {
                nyPt = 15;
            }
            Leftpoints.push_front(QPoint(viewpointX.x(), 20));
            Leftpoints.push_front(QPoint(viewpointX.x(), nyPt));
            Leftpoints.push_front(QPoint(viewpointX.x(), 20));
        }
        if (i <= 0)
        {
            QPoint viewpointX=mapFromScene(i,0);
            painter.setBrush(Qt::black);
            //! 向右偏两像素 避免负号被遮挡
            painter.drawText(QPoint(viewpointX.x()+2, 14), QString::number(-nIndex * nDistance));
        }
        nIndex++;
    }

    painter.setPen(Qt::black);
    painter.setBrush(Qt::white);
    painter.drawPolyline(Rightpoints);
    painter.drawPolyline(Leftpoints);

}


void TGraphicsViewRefactor::DrawVerticalRuler(QPainter &painter)
{
    QPoint lefttop= QPoint(0,0);
    QPoint leftbtn =QPoint(this->width(),this->height());

    //! 转换成 QGraphicsScene 坐标
    QPointF scene_lefttop=mapToScene(lefttop);
    QPointF scene_leftbtn=mapToScene(leftbtn);


    //! 还是以宽 为标准
    float fscale = (scene_leftbtn.x() - scene_lefttop.x())*1.0 / this->width();

    //! 步长
    int  nDistance = 100;
    nDistance = ((1.0 / fscale * 100) / 10) * 10;
    if (nDistance > 50 && nDistance < 150)
    {
        nDistance = 100;
    }
    if (nDistance >= 150 && nDistance < 200)
    {
        nDistance = 200;
    }

    //! 抹除 左边框 20*height 内容
    painter.setPen(Qt::white);
    painter.setBrush(Qt::white);
    QRect rc(0, 0, 20, this->height());
    painter.drawRect(rc);
    //! 画右边框线  --为了不出现上 左 下 三条边
    painter.setPen(Qt::black);
    painter.setBrush(Qt::white);
    painter.drawLine(QPoint(20,0),QPoint(20,this->height()));

    //! 从 0 往下
    QPolygon Bottompoints;
    int nIndex = 0;
    for (int i = 0; i < scene_leftbtn.y(); i += nDistance)
    {
        for (int j = 0; j < 10; ++j)
        {
            int nyPt = i + j * (nDistance / 10);
            QPoint viewpointY=mapFromScene(QPointF(0,nyPt));
            if (viewpointY.y() < 20)
                continue;
            int nxPt = 0;
            if (j == 0)
            {
                nxPt = 0;
            }
            else if (j % 5 == 0)
            {
                nxPt = 10;
            }
            else
            {
                nxPt = 15;
            }
            Bottompoints.push_back(QPoint(20, viewpointY.y()));
            Bottompoints.push_back(QPoint(nxPt, viewpointY.y()));
            Bottompoints.push_back(QPoint(20, viewpointY.y()));
        }
        if (i >= 0)
        {
            QPoint viewpointY=mapFromScene(QPointF(0,i));
            painter.setBrush(Qt::black);
            QMatrix mat;
            mat.translate(2, (viewpointY.y() + 2));
            mat.rotate(90);
            mat.translate(2, -(viewpointY.y() + 2));
            painter.setMatrix(mat);
            painter.drawText(QPoint(2, viewpointY.y() + 2), QString::number(nIndex*nDistance));
            painter.resetMatrix();
        }
        nIndex++;
    }


    //////////////////////////////////////////////////////////////////////////
    //! 从 0 向上
    QPolygon Toppoints;
    nIndex = 0;
    for (int i = 0; i >= scene_lefttop.y(); i -= nDistance)
    {
        for (int j = 0; j < 10; ++j)
        {
            int nyPt = i - j * (nDistance / 10);
            QPoint viewpointY=mapFromScene(QPointF(0,nyPt));
            if (viewpointY.y() < 20)
                continue;
            int nxPt = 0;
            if (j == 0)
            {
                nxPt = 0;
            }
            else if (j % 5 == 0)
            {
                nxPt = 10;
            }
            else
            {
                nxPt = 15;
            }

            Toppoints.push_front(QPoint(20, viewpointY.y()));
            Toppoints.push_front(QPoint(nxPt, viewpointY.y()));
            Toppoints.push_front(QPoint(20, viewpointY.y()));
        }
        if (i <= 0)
        {
            QPoint viewpointY=mapFromScene(QPointF(0,i));
            painter.setBrush(Qt::black);
            QMatrix mat;
            mat.translate(2, (viewpointY.y() + 2));
            mat.rotate(90);
            mat.translate(2, -(viewpointY.y() + 2));
            painter.setMatrix(mat);
            painter.drawText(QPoint(2, viewpointY.y() + 2), QString::number(-nIndex * nDistance));
            painter.resetMatrix();
        }
        nIndex++;
    }


    //////////////////////////////////////////////////////////////////////////
    //! 绘制线段
    QPen pen(Qt::black, 1, Qt::SolidLine);
    painter.setPen(pen);
    painter.setBrush(Qt::white);
    painter.drawPolyline(Toppoints);
    painter.drawPolyline(Bottompoints);
}


void TGraphicsViewRefactor::DrawRuleCross(QPainter &painter)
{
    painter.setBrush(QColor(255, 255, 255, 255));
    painter.setPen(Qt::white);
    painter.drawRect(QRect(0, 0, 20, 20));
    painter.setPen(Qt::DashLine);
    painter.drawLine(QPoint(0, 10), QPoint(20, 10));
    painter.drawLine(QPoint(10, 0), QPoint(10, 20));
    painter.setPen(Qt::SolidLine);
    painter.drawLine(QPoint(0, 20), QPoint(20, 20));
    painter.drawLine(QPoint(20, 0), QPoint(20, 20));
}


void TGraphicsViewRefactor::DrawHorGridLine(QPainter &painter)
{
    QPoint lefttop= QPoint(0,0);
    QPoint righttop =QPoint(this->width(),0);

    //! 转换成 QGraphicsScene 坐标
    QPointF scene_lefttop=mapToScene(lefttop);
    QPointF scene_righttop=mapToScene(righttop);


    //! 还是以宽 为标准
    float fscale = (scene_righttop.x() - scene_lefttop.x())*1.0 / this->width();

    //! 步长
    int  nDistance = 100;
    nDistance = ((1.0 / fscale * 100) / 10) * 10;
    if (nDistance > 50 && nDistance < 150)
    {
        nDistance = 100;
    }
    if (nDistance >= 150 && nDistance < 200)
    {
        nDistance = 200;
    }

    QPolygon BoldPoints;
    QPolygon ThinPoints;

    //! 从 0 -> ∞
    for (int i = 0; i < scene_righttop.x(); i += nDistance)
    {
        for (int j = 0; j < 10; ++j)
        {
            int nxPt = i + j * (nDistance / 10);
            QPoint viewpointX=mapFromScene(nxPt,0);
            if (viewpointX.x() < 20)
                continue;
            if (j == 0)
            {
                BoldPoints.push_back(QPoint(viewpointX.x(), 20));
                BoldPoints.push_back(QPoint(viewpointX.x(), this->height()));
                BoldPoints.push_back(QPoint(viewpointX.x(), 20));
            }
            else
            {
                ThinPoints.push_back(QPoint(viewpointX.x(), 20));
                ThinPoints.push_back(QPoint(viewpointX.x(), this->height()));
                ThinPoints.push_back(QPoint(viewpointX.x(), 20));
            }
        }
    }

    //! 从 0 到 负无穷
    for (int i = 0; i >= scene_lefttop.x(); i -= nDistance)
    {
        for (int j = 0; j < 10; ++j)
        {
            int nxPt = i - j * (nDistance / 10);
            QPoint viewpointX=mapFromScene(nxPt,0);
            if (viewpointX.x() < 20)
                continue;
            if (j == 0)
            {
                BoldPoints.push_back(QPoint(viewpointX.x(), 20));
                BoldPoints.push_back(QPoint(viewpointX.x(), this->height()));
                BoldPoints.push_back(QPoint(viewpointX.x(), 20));
            }
            else
            {
                ThinPoints.push_back(QPoint(viewpointX.x(), 20));
                ThinPoints.push_back(QPoint(viewpointX.x(), this->height()));
                ThinPoints.push_back(QPoint(viewpointX.x(), 20));
            }
        }
    }

    QPen boldpen(QBrush(QColor(0, 0, 0, 50)), 1);
    painter.setPen(boldpen);
    painter.drawPolyline(BoldPoints);
    QPen thinpen(QBrush(QColor(0, 0, 0, 25)), 1);
    painter.setPen(thinpen);
    painter.drawPolyline(ThinPoints);
}


void TGraphicsViewRefactor::DrawVerGridLine(QPainter &painter)
{
    QPoint lefttop= QPoint(0,0);
    QPoint leftbtn =QPoint(this->width(),this->height());

    //! 转换成 QGraphicsScene 坐标
    QPointF scene_lefttop=mapToScene(lefttop);
    QPointF scene_leftbtn=mapToScene(leftbtn);
    //! 还是以宽 为标准
    float fscale = (scene_leftbtn.x() - scene_lefttop.x())*1.0 / this->width();

    //! 步长
    int  nDistance = 100;
    nDistance = ((1.0 / fscale * 100) / 10) * 10;
    if (nDistance > 50 && nDistance < 150)
    {
        nDistance = 100;
    }
    if (nDistance >= 150 && nDistance < 200)
    {
        nDistance = 200;
    }

    QPolygon BoldPoints;
    QPolygon ThinPoints;

    //! 从 0 向下 前进
    for (int i = 0; i < scene_leftbtn.y(); i += nDistance)
    {
        for (int j = 0; j < 10; ++j)
        {
            int nyPt = i + j * (nDistance / 10);
            QPoint viewpointY=mapFromScene(0,nyPt);
            if (viewpointY.y() < 20)
                continue;
            if (j == 0)
            {
                BoldPoints.push_back(QPoint(20, viewpointY.y()));
                BoldPoints.push_back(QPoint(this->width(), viewpointY.y()));
                BoldPoints.push_back(QPoint(20, viewpointY.y()));
            }
            else
            {
                ThinPoints.push_back(QPoint(20, viewpointY.y()));
                ThinPoints.push_back(QPoint(this->width(), viewpointY.y()));
                ThinPoints.push_back(QPoint(20, viewpointY.y()));
            }
        }
    }

    //! 从0 向上 移动
    for (int i = 0; i >= scene_lefttop.y(); i -= nDistance)
    {
        for (int j = 0; j < 10; ++j)
        {
            int nyPt = i - j * (nDistance / 10);
            QPoint viewpointY=mapFromScene(0,nyPt);
            if (viewpointY.y() < 20)
                continue;
            if (j == 0)
            {
                BoldPoints.push_back(QPoint(20, viewpointY.y()));
                BoldPoints.push_back(QPoint(this->width(), viewpointY.y()));
                BoldPoints.push_back(QPoint(20, viewpointY.y()));
            }
            else
            {
                ThinPoints.push_back(QPoint(20, viewpointY.y()));
                ThinPoints.push_back(QPoint(this->width(), viewpointY.y()));
                ThinPoints.push_back(QPoint(20, viewpointY.y()));
            }
        }
    }

    QPen boldpen(QBrush(QColor(0, 0, 0, 50)), 1);
    painter.setPen(boldpen);
    painter.drawPolyline(BoldPoints);
    QPen thinpen(QBrush(QColor(0, 0, 0, 25)), 1);
    painter.setPen(thinpen);
    painter.drawPolyline(ThinPoints);
}


void TGraphicsViewRefactor::DrawCanvasRect(QPainter &painter)
{
    QPoint leftTop= mapFromScene(QPointF(0, 0));
    QPoint rightbtn= mapFromScene(QPointF(500, 500));
    QPen boldpen(QBrush(QColor(100, 100, 100,255)), 1);
    painter.setPen(boldpen);
    painter.setBrush(QColor(255,255,255,255));
    QRect rc(QPoint(qMax(leftTop.x(),20),qMax(leftTop.y(),20)), rightbtn);
    painter.drawRect(rc);
    scene()->update(QRectF(0,0,500,500));

}

///////////////////////////////////////////// 拖拽视窗 /////////////////////////////////////////////


void TGraphicsViewRefactor::mousePressEvent(QMouseEvent *event)
{
    // 只有当中键按下时才开始拖动
    if(event->button() == Qt::MiddleButton)
    {
        IsMoveView=!IsMoveView;
        // 记录按下时的视图坐标
        C_Movepos = mapToScene(event->pos()) - event->pos() + QPointF(width() / 2, height() / 2);
        C_Downpos  = event->pos();

        return;
    }
    QGraphicsView::mousePressEvent(event);
}

void TGraphicsViewRefactor::mouseMoveEvent(QMouseEvent *event)
{
    if (IsMoveView)
    {
        QPointF offsetPos = event->pos() - C_Downpos;

        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        centerOn(C_Movepos - offsetPos);

        //qDebug()<<"IsMoveView"<<IsMoveView;
    }
    QGraphicsView::mouseMoveEvent(event);
}

void TGraphicsViewRefactor::mouseReleaseEvent(QMouseEvent *event)
{   qDebug() << "mouseReleaseEvent :"<<IsMoveView;
    if (event->button() == Qt::MiddleButton)
    {
        //IsMoveView = false;
        viewport()->setCursor(Qt::ArrowCursor);
        event->accept();
        return;
    }
    QGraphicsView::mouseReleaseEvent(event);
}

//中键双击居中
void TGraphicsViewRefactor::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        // 将视图中心设置为场景的中心
        QRectF sceneRect = scene()->sceneRect(); // 场景矩形
        QPointF centerPoint = sceneRect.center(); // 场景中心点

        centerOn(centerPoint); // 让视图以 scene 中心为中心

        return;
    }

    QGraphicsView::mouseDoubleClickEvent(event);
}
