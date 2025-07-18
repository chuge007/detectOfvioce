﻿#ifndef ASCAN_H
#define ASCAN_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QSettings>
#include "mainwindow.h"

namespace Ui {
class ascan;
}

class ascan : public QWidget
{
    Q_OBJECT

public:
    explicit ascan(QWidget *parent = nullptr);
    ~ascan();

    QSettings *Rsettings = nullptr;
    double  stanPointSing;
    double  PointSing;
    bool    isStanPointSing;
    bool    isSingUPdate;
    bool    stepCorretion=false;

    bool    stopCorretion=false;

    int     numStepCorretionRow;
    int     numStepCorretionCol;
    MainWindow *mw;

    std::vector<std::pair<float, float>> getNeighbors(float x, float y, float z, float r, float searchRange, float stepSize);
    bool autoCorretionPathAlgrith(int index, float& x, float& y, float& z, float& r);
    bool moveAndWaitUntilReached(double targetX, double targetY, double targetZ, double targetR);
    void waitForSignal(int timeoutMs=3000);

    QStringList dynamicMessages;
    const int maxDynamicLines = 5;  // 最大显示10行（不含第一行）
    QString fixedLine;


private slots:
    void onNewConnection();  // 处理新连接
    void onReadyRead();      // 处理接收到的数据
    void onSendstanPoint();  // 发送按钮点击槽
    void autoCorretionPath();

    void stepCorretionPath();

    void stopCorretionPath();

    void appendLabelMessage(const QString &msg);


signals:
    void signalUpdated();
    void statusMessage(QString text);
private:
    Ui::ascan *ui;
    QTcpServer *tcpServer;  // TCP 服务器对象
    QTcpSocket *tcpSocket;  // TCP 套接字对象
    void startServer();     // 启动监听
    void sendData(const QString &data);  // 发送数据

    void disConnection();

   QTimer* checkTimer = nullptr;
};

#endif // ASCAN_H
