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
}

void  route_worksence::drawBackground (QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect)
    painter->fillRect(oneimg_theRect, this->backgroundBrush());

#if 0
    int gridSize = 20; // 栅格大小
    // 绘制水平和垂直栅格线
    for (int x = -200; x <= 200; x += gridSize) {
        addLine(x, -200, x, 200, QPen(QColor(200, 200, 200))); // 垂直线
    }
    for (int y = -200; y <= 200; y += gridSize) {
        addLine(-200, y, 200, y, QPen(QColor(200, 200, 200))); // 水平线
    }

    // X 轴
    addLine(-200, 0, 200, 0, QPen(Qt::black, 2));
    addText("X", QFont("Arial", 10))->setPos(210, 0); // X 轴标签

    // Y 轴
    addLine(0, -200, 0, 200, QPen(Qt::black, 2));
    addText("Y", QFont("Arial", 10))->setPos(0, 210); // Y 轴标签
    int tickLength = 10; // 刻度长度
    int gridSize_mid = 20;   // 刻度间隔

    // X 轴刻度和标签
    for (int x = 0; x <= 400; x += gridSize_mid) {
        addLine(x, 200, x, 200 - tickLength, QPen(Qt::black));
        addText(QString::number(x - 200), QFont("Arial", 10))->setPos(x - 10, 205); // 标签
    }

    // Y 轴刻度和标签
    for (int y = 0; y <= 400; y += gridSize_mid) {
        addLine(200, y, 200 + tickLength, y, QPen(Qt::black));
        addText(QString::number(200 - y), QFont("Arial", 10))->setPos(205, y - 10); // 标签
    }
#endif
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
