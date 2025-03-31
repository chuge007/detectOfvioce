
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


    this->setFlags ( ItemIsSelectable  | ItemIgnoresTransformations | ItemSendsGeometryChanges);
    this->setSelected ( false );
    this->setAcceptHoverEvents ( true );
    this->setZValue ( 1 );
    this->setAcceptedMouseButtons(Qt::LeftButton);

}

void line_item::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
{


    painter->setRenderHint(QPainter::Antialiasing, true);
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

    painter->drawLine( _start, _end );

}

QRectF line_item::boundingRect() const
{
    // 计算直线的起点和终点所在的矩形区域
    QRectF rect(_start, _end);
    rect = rect.normalized();

    // 增加额外的边距（例如 4 像素），以确保包括笔宽和悬停区域
    qreal extra = 4;
    return rect.adjusted(-extra, -extra, extra, extra);
}

QPainterPath line_item::shape() const{
    // 创建一个路径，并将直线添加进去
    QPainterPath path;
    path.moveTo(_start);
    path.lineTo(_end);

    // 使用 QPainterPathStroker 将路径扩宽
    QPainterPathStroker stroker;
    stroker.setWidth(8);  // 设置宽度，值可以根据需要调整
    return stroker.createStroke(path);
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
    qDebug()<<"**hoverEnterEvent**";
}

void line_item::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverLeaveEvent(event); // 调用基类事件处理
    is_hover=false;
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



    painter->setRenderHint(QPainter::Antialiasing, true);
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
    qDebug()<<"**hoverEnterEvent**";
}

void arc_item::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverLeaveEvent(event); // 调用基类事件处理
    is_hover=false;
}
