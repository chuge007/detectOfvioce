#include <QtGui>
#include <QGraphicsRectItem>
#include <QApplication>
#include "route_worksence.h"
#include <QDebug>

route_worksence::route_worksence(QObject *parent) :
    QGraphicsScene(parent)
{
    imgbg_scale_f =1.0;
    // 镜像 Y 轴
    setSceneRect(-5000, -5000, 10000, 10000); // 左上角(-2000, -2000)，右下角(+2000, +2000)


}

void  route_worksence::drawBackground (QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect)
    painter->fillRect(oneimg_theRect, this->backgroundBrush());

}

void route_worksence::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);
}

void route_worksence::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);
}

void route_worksence::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseReleaseEvent(event);
}

void route_worksence::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
}

int route_worksence::bytesToInt(QByteArray bytes) //int 转 bytearray
{
    int addr = bytes[0] & 0x000000FF;
    addr |= ((bytes[1] << 8) & 0x0000FF00);
    addr |= ((bytes[2] << 16) & 0x00FF0000);
    addr |= ((bytes[3] << 24) & 0xFF000000);
    return addr;
}
