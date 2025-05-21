#ifndef ASCAN_H
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
<<<<<<< HEAD
    bool    isStanPointSing;
=======
    double  PointSing;
    bool    isStanPointSing;
    bool    isSingUPdate;

    MainWindow *mw;

    std::vector<std::pair<float, float>> getNeighbors(float x, float y, float z, float r, float searchRange, float stepSize);
    void autoCorretionPathAlgrith(int index, float& x, float& y, float& z, float& r);

>>>>>>> c82df02 (界面)
private slots:
    void onNewConnection();  // 处理新连接
    void onReadyRead();      // 处理接收到的数据
    void onSendstanPoint();  // 发送按钮点击槽
    void autoCorretionPath();


private:
    Ui::ascan *ui;
    QTcpServer *tcpServer;  // TCP 服务器对象
    QTcpSocket *tcpSocket;  // TCP 套接字对象
    void startServer();     // 启动监听
    void sendData(const QString &data);  // 发送数据
<<<<<<< HEAD
    void autoCorretionPathAlgrith();


public:

    MainWindow *mw;
=======



>>>>>>> c82df02 (界面)

};

#endif // ASCAN_H
