
#include "graphicTool.h"
#include <QPainter>
#include <math.h>
#include <QDebug>

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>

#define PI 3.14159265
#define MID_ANGLE PI/6


line_item::line_item(const QPointF& startPosition, const QPointF& endPosition,int sort_vaule ,route_worksence *parent)
{
    _end = endPosition;
    _start = startPosition;
    _sortNum=sort_vaule;
    is_hover =false;
    imgbg_scale_f = parent->imgbg_scale_f;


    //this->setFlag(QGraphicsItem::ItemIsSelectable,true); // 设置为可选中项
    //this->setFlags (ItemSendsGeometryChanges);
    this->setFlags ( ItemIsSelectable  | ItemIgnoresTransformations | ItemSendsGeometryChanges);
    setFlag(QGraphicsItem::ItemIsFocusable); // 使项可以接收焦点
    this->setSelected ( false );
    this->setAcceptHoverEvents ( true );
    this->setZValue ( 1 );

}

void line_item::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
{
    //QPainterPath path( QPointF(0,0) );
    //qDebug()<<"***line_item paint";

    painter->setRenderHint(QPainter::Antialiasing, true);
    //painter->scale(1,-1);
    QPen pen;
    if (this->isSelected()==true) {
        pen.setColor(Qt::red);
    }else if(is_hover) {
        pen.setColor(Qt::green);
    }else{
        pen.setColor(Qt::black);
    }

    pen.setWidth(2);
    painter->setPen(pen);
    QPointF end_pos = QPointF( _end.x() - _start.x() ,_end.y() - _start.y() );

    //painter->setPen( QPen(QColor(20,181,253,255), 0) );
    //painter->drawPath( path );
    painter->drawLine( _start, _end );
    //painter->drawLine( 0 ,0 , end_pos.x(), end_pos.y() );

#if 0
    QPointF start= QPointF(0,0);
    QPointF end= QPointF(_end.x()-_start.x(),_end.y()-_start.y());
    // 计算方向向量
    QPointF direction = end - start;
    float length = std::sqrt(direction.x() * direction.x() + direction.y() * direction.y());

    // 单位化方向向量
    QPointF unitDirection = direction / length;

    // 计算垂直于方向的单位向量（顺时针旋转90度）
    QPointF offset(-unitDirection.y(), unitDirection.x());

    // 偏移量
    float offsetDistance = 3.0f;

    // 计算平行线段的端点
    QPointF parallelStart1 = start + offset * offsetDistance;
    QPointF parallelEnd1 = end + offset * offsetDistance;
    QPointF parallelStart2 = start - offset * offsetDistance;
    QPointF parallelEnd2 = end - offset * offsetDistance;

    painter->setPen( QPen(QColor(Qt::green), 0) );
    QPolygonF polygon;
    polygon << parallelStart1 << parallelStart2 << parallelEnd2 << parallelEnd1;
#endif
    //QPolygonF polygon = get_Polygon();
    //painter->drawPolygon(polygon);

    //painter->setPen( QPen(QColor(20,181,253,255), 0) );
    //painter->drawRect(QRectF( -4,-4 ,_end.x()-_start.x()+8,_end.y()-_start.y()+8 ));

}

QRectF line_item::boundingRect() const
{
    //return QRectF( -4,-4 ,_end.x()-_start.x()+8,_end.y()-_start.y()+8 );
    QPolygonF polygon = get_Polygon();
    return polygon.boundingRect();
}

QPainterPath line_item::shape() const{
    QPainterPath ret;
#if 0
    QPointF start= QPointF(0,0);
    QPointF end= QPointF(_end.x()-_start.x(),_end.y()-_start.y());
    // 计算方向向量
    QPointF direction = end - start;
    float length = std::sqrt(direction.x() * direction.x() + direction.y() * direction.y());

    // 单位化方向向量
    QPointF unitDirection = direction / length;

    // 计算垂直于方向的单位向量（顺时针旋转90度）
    QPointF offset(-unitDirection.y(), unitDirection.x());

    // 偏移量
    float offsetDistance = 4.0f;

    // 计算平行线段的端点
    QPointF parallelStart1 = start + offset * offsetDistance;
    QPointF parallelEnd1 = end + offset * offsetDistance;
    QPointF parallelStart2 = start - offset * offsetDistance;
    QPointF parallelEnd2 = end - offset * offsetDistance;

    // 创建一个QPolygonF用于绘制
     QPolygonF polygon;
     polygon << parallelStart1 << parallelStart2 << parallelEnd2 << parallelEnd1;
    //ret.addRect(QRectF(parallelStart2, parallelEnd1));
#endif
    QPolygonF polygon = get_Polygon();
    ret.addPolygon(polygon);
    return ret;
}

void line_item::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event); // 调用基类事件处理
    qDebug()<<"**mousePressEvent**"<<this->isSelected();
}

void line_item::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverEnterEvent(event); // 调用基类事件处理
    is_hover=true;
    //qDebug()<<"**hoverEnterEvent**";
}

void line_item::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverLeaveEvent(event); // 调用基类事件处理
    is_hover=false;
}

QPolygonF  line_item::get_Polygon() const
{
    QPointF start= QPointF(0,0);
    QPointF end= QPointF(_end.x()-_start.x(),_end.y()-_start.y());
    // 计算方向向量
    QPointF direction = end - start;
    float length = std::sqrt(direction.x() * direction.x() + direction.y() * direction.y());

    // 单位化方向向量
    QPointF unitDirection = direction / length;

    // 计算垂直于方向的单位向量（顺时针旋转90度）
    QPointF offset(-unitDirection.y(), unitDirection.x());

    // 偏移量
    float offsetDistance = 4.0f;

    // 计算平行线段的端点
    QPointF parallelStart1 = start + offset * offsetDistance;
    QPointF parallelEnd1 = end + offset * offsetDistance;
    QPointF parallelStart2 = start - offset * offsetDistance;
    QPointF parallelEnd2 = end - offset * offsetDistance;

    // 创建一个QPolygonF用于绘制
     QPolygonF polygon;
     polygon << parallelStart1 << parallelStart2 << parallelEnd2 << parallelEnd1;
    return polygon;
}






arc_item::arc_item(const QPointF& startPosition, const QPointF& transPosition, const QPointF& endPosition ,int sortValue,route_worksence *parent)
{
    _end = endPosition;
    _start = startPosition;
    _trans =transPosition;
    _sortNum=sortValue;
    imgbg_scale_f = parent->imgbg_scale_f;

    this->setFlags ( ItemIsSelectable  | ItemIgnoresTransformations | ItemSendsGeometryChanges);
    this->setSelected ( false );
    this->setAcceptHoverEvents ( true );
    this->setZValue ( 1 );

    is_hover=false;

}

void arc_item::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
{
    //QPainterPath path( QPointF(0,0) );
    //painter->setPen( QPen(QColor(20,181,253,255), 0) );
    #if 0
   //qDebug()<<"end="<<_end<<"start="<<_start<<"trans="<<_trans;
    double x1,x2,x3,y1,y2,y3;
    x1=_start.x();
    y1=_start.y();
    x2=_trans.x();
    y2=_trans.y();
    x3=_end.x();
    y3=_end.y();
    //qDebug()<<"x1"<<x1<<"y1="<<y1<<"x2="<<x2<<y2<<x3<<y3;
    /*x1=100;
    y1=0;
    x2=120.53;
    y2=7;
    x3=125;
    y3=25;*/

    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::blue);
    painter->setPen(pen);
    painter->drawPoint(x1,y1);
    painter->drawPoint(x2,y2);
    painter->drawPoint(x3,y3);
    double ma = (y2 - y1) / (x2 - x1);  // 点1到点2的斜率
    double mb = (y3 - y2) / (x3 - x2);  // 点2到点3的斜率
    // 求圆心坐标
    double cx = (ma*mb*(y1 - y3) + mb*(x1 + x2) - ma*(x2 + x3)) / (2*(mb - ma));
    double cy = (-1/ma)*(cx - (x1 + x2) / 2) + (y1 + y2) / 2;

    // 求圆半径
    double r = sqrt((cx - x1)*(cx - x1) + (cy - y1)*(cy - y1));
    //qDebug()<<"cx="<<cx<<"cy="<<cy<<"r="<<r;

    double startAngle = atan2(y1 - cy, x1 - cx)* 180 / PI;  // 从点1开始
    double endAngle = atan2(y3 - cy, x3 - cx)* 180 / PI;    // 结束于点3
    double spanAngle = endAngle - startAngle;
    double crossProduct = (_trans.x() - _start.x()) * (_end.y() - _start.y()) - (_trans.y() - _start.y()) * (_end.x() - _start.x());
    qDebug()<<"*****crossProduct="<<crossProduct;
    //外接矩形
    //QRectF rect = QRectF(cx - r, cy - r, 2 * r, 2 * r);
    QRectF rect = QRectF(- r, - r, 2 * r, 2 * r);
    qDebug()<<"rect="<<rect<<"startAngle="<<startAngle<<"endAngle="<<endAngle<<"spanAngle="<<spanAngle;

    // 移动原点到圆心
    painter->translate(cx, cy);
    // 反转 Y 轴
    painter->scale(1, -1);
    //绘制三点圆弧
    painter->setPen( QPen(QColor(Qt::red), 0) );
    painter->drawRect(rect);
    if(crossProduct<0){
        painter->drawArc(rect, startAngle*16, -qAbs(spanAngle)*16);
    }else if(crossProduct>0){
        painter->drawArc(rect, startAngle*16, qAbs(spanAngle)*16);
    }
    else{
        qDebug()<<"3 point in a line can not make a cycle!";
        return;
    }
#endif

     //qDebug()<<"***arc if selected"<<this->isSelected();
    painter->setRenderHint(QPainter::Antialiasing, true);
      //painter->scale(1,-1);
    QPen pen;
    if (this->isSelected()==true) {
        pen.setColor(Qt::red);
    }else if(is_hover) {
        pen.setColor(Qt::green);
    }else{
        pen.setColor(Qt::black);
    }
    pen.setWidth(2);
    painter->setPen(pen);
    pen.setWidth(2);
    painter->setPen(pen);
    QPointF A, B, C;
    A=_start;
    B=_trans;
    C=_end;
    // A = {450, 100}, B = {200, 200}, C = {359, 349};
    auto s_ab = A + B;
    auto s_bc = B + C;
    auto m_ab = A - B;
    auto m_bc = B - C;
    double mat[2][2]{{m_bc.rx() * -2, m_bc.ry() * -2},
                     {m_ab.rx() * -2, m_ab.ry() * -2}};
    auto det = mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
    if (std::abs(det) < std::numeric_limits<double>::epsilon()) {
        // 3 points on the same line,
        painter->drawLine(A, B);
        painter->drawLine(B, C);
        return;
    }
    double b[2]{-(s_bc.rx() * m_bc.rx() + s_bc.ry() * m_bc.ry()),
                -(s_ab.rx() * m_ab.rx() + s_ab.ry() * m_ab.ry())};
    auto O = QPointF{
        (b[0] * mat[1][1] - b[1] * mat[0][1]) / det,
        (b[1] * mat[0][0] - b[0] * mat[1][0]) / det
    };

    auto vr = A - O;
    auto r = std::sqrt(vr.rx() * vr.rx() + vr.ry() * vr.ry());

    auto &&on_rect = [&]() {
        return QRectF{O - QPointF{r, r}, O + QPointF{r, r}};
    };

    auto &&on_ang = [&](const QPointF &p) {
        auto s = p - O;
        auto a = std::acos(s.rx() / r) * (s.ry() > 0 ? -1 : 1);
        return a / PI * 180 * 16;
    };

    auto &&on_span = [&](double a1, double a2, double a3) {
        if ((a3 - a1) * (a3 - a2) > 0) {
            return a2 - a1;
        } else {
            return (360 * 16 - std::abs(a2 - a1)) * (a2 - a1 > 0 ? -1 : 1);
        }
    };

    auto ang_A = on_ang(A), ang_B = on_ang(B), ang_C = on_ang(C);
    get_rect= QRectF(on_rect());
    painter->drawArc(on_rect(), ang_A, on_span(ang_A, ang_B, ang_C));
    painter->drawArc(on_rect(), ang_B, on_span(ang_B, ang_C, ang_A));

    painter->drawEllipse(A, 3, 3);
    painter->drawText(A + QPointF(10, 10), "A");
    painter->drawEllipse(B, 3, 3);
    painter->drawText(B + QPointF(10, 10), "B");
    painter->drawEllipse(C, 3, 3);
    painter->drawText(C + QPointF(10, 10), "C");

    //painter->drawRect(on_rect());
    //painter->drawEllipse(O, 3, 3);

}

QRectF arc_item::boundingRect() const
{
    return get_rect;
    //return QRectF( QPointF(0,0) ,_end - _start );
}

QPainterPath arc_item::shape() const{
    QPainterPath ret;
    //QRectF rect( QPointF(0,0) ,_end - _start );
    ret.addRect(get_rect);
    return ret;
}

void arc_item::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event); // 调用基类事件处理
    //qDebug()<<"**mousePressEvent**"<<this->isSelected();
}

void arc_item::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverEnterEvent(event); // 调用基类事件处理
    is_hover=true;
    //qDebug()<<"**hoverEnterEvent**";
}

void arc_item::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverLeaveEvent(event); // 调用基类事件处理
    is_hover=false;
}
