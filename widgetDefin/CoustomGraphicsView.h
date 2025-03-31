#ifndef COUSTOMGRAPHICSVIEW_H
#define COUSTOMGRAPHICSVIEW_H

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QPainter>

class CustomGraphicsView : public QGraphicsView {
public:
    CustomGraphicsView() {
        setScene(new QGraphicsScene(this));
        scene()->setSceneRect(0, 0, 400, 400);
        setRenderHint(QPainter::Antialiasing);

        drawGrid();    // 绘制背景栅格
        drawAxes();    // 绘制坐标轴
        drawTicks();   // 绘制刻度和数字

        // 反转Y轴，使原点在左上角
        scale(1, -1);
        translate(0, -400);
    }

private:
    void drawGrid() {
        int gridSize = 20; // 栅格大小

        // 绘制水平和垂直栅格线
        for (int x = 0; x <= 400; x += gridSize) {
            scene()->addLine(x, 0, x, 400, QPen(QColor(220, 220, 220))); // 垂直线
        }
        for (int y = 0; y <= 400; y += gridSize) {
            scene()->addLine(0, y, 400, y, QPen(QColor(220, 220, 220))); // 水平线
        }
    }

    void drawAxes() {
        // X 轴
        scene()->addLine(0, 200, 400, 200, QPen(Qt::black, 2));
        // Y 轴
        scene()->addLine(200, 0, 200, 400, QPen(Qt::black, 2));
    }

    void drawTicks() {
        int tickLength = 10; // 刻度长度
        int gridSize = 20;   // 刻度间隔

        // X 轴刻度和标签
        for (int x = 0; x <= 400; x += gridSize) {
            scene()->addLine(x, 200, x, 200 - tickLength, QPen(Qt::black));
            scene()->addText(QString::number(x - 200), QFont("Arial", 10))->setPos(x - 10, 210); // 标签
        }

        // Y 轴刻度和标签
        for (int y = 0; y <= 400; y += gridSize) {
            scene()->addLine(200, y, 200 + tickLength, y, QPen(Qt::black));
            scene()->addText(QString::number(200 - y), QFont("Arial", 10))->setPos(210, y - 10); // 标签
        }
    }
};
#endif // COUSTOMGRAPHICSVIEW_H
