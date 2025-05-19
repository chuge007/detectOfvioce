#include "ascan.h"
#include "ui_ascan.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include "mainwindow.h"


ascan::ascan(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ascan),
    tcpServer(new QTcpServer(this)),  // 创建 TCP 服务器对象
    tcpSocket(nullptr)                 // 初始化为 nullptr
{
    ui->setupUi(this);


    // 启动 TCP 监听，监听端口 56789
    startServer();

    // 连接发送按钮的点击事件
    connect(ui->saveScanStan_but, &QPushButton::clicked, this, &ascan::onSendstanPoint);
}

ascan::~ascan()
{
    delete ui;
    if (tcpSocket) {
        tcpSocket->disconnectFromHost();  // 断开连接
    }
}

void ascan::startServer()
{
    // 启动监听端口 56789
    if (!tcpServer->listen(QHostAddress::Any, 56789)) {
        QMessageBox::critical(this, tr("Error"), tr("Unable to start the server: %1").arg(tcpServer->errorString()));
        return;
    }

    // 监听新连接
    connect(tcpServer, &QTcpServer::newConnection, this, &ascan::onNewConnection);

}

void ascan::onNewConnection()
{
    // 当有新连接时接受连接
    tcpSocket = tcpServer->nextPendingConnection();

    // 连接接收数据的槽函数
    connect(tcpSocket, &QTcpSocket::readyRead, this, &ascan::onReadyRead);

    // 连接成功后，可以通过 tcpSocket 发送和接收数据
    QMessageBox::information(this, tr("Connection"), tr("New connection established."));
}

void ascan::onReadyRead()
{
    // 当接收到数据时调用
    QByteArray data = tcpSocket->readAll();  // 读取所有数据
    QString message = QString::fromUtf8(data);  // 转换为字符串
    ui->disPlayIformationLb->setText(message);  // 显示接收到的数据（假设你有一个 QTextEdit 来显示）

    if(isStanPointSing){
        stanPointSing=message.toDouble();
        Rsettings->setValue("AscanStanPoint",message);
        isStanPointSing=false;
    }
}

void ascan::onSendstanPoint()
{
    if (tcpSocket) {
        sendData("1");  // 发送一个“1”到服务器
    }
    isStanPointSing=true;
}

void ascan::sendData(const QString &data)
{
    if (tcpSocket) {
        tcpSocket->write(data.toUtf8());  // 将数据转换为字节流并发送
        tcpSocket->flush();  // 确保数据立刻发送
    }
}




void ascan::autoCorretionPath(){
    int row_count = mw->model->rowCount();
    float x0, y0, z0, r0, x1, y1, z1, r1, x2, y2, z2, r2;
    QString name;

    for(int i = 0; i < row_count; ++i)
    {
        name = mw->model->data(mw->model->index(i, 1), Qt::DisplayRole).toString();
        x0 = mw->model->data(mw->model->index(i, 2), Qt::DisplayRole).toFloat();
        y0 = mw->model->data(mw->model->index(i, 3), Qt::DisplayRole).toFloat();
        z0 = mw->model->data(mw->model->index(i, 4), Qt::DisplayRole).toFloat();
        r0 = mw->model->data(mw->model->index(i, 5), Qt::DisplayRole).toFloat();

        x1 = mw->model->data(mw->model->index(i, 6), Qt::DisplayRole).toFloat();
        y1 = mw->model->data(mw->model->index(i, 7), Qt::DisplayRole).toFloat();
        z1 = mw->model->data(mw->model->index(i, 8), Qt::DisplayRole).toFloat();
        r1 = mw->model->data(mw->model->index(i, 9), Qt::DisplayRole).toFloat();

        x2 = mw->model->data(mw->model->index(i, 10), Qt::DisplayRole).toFloat();
        y2 = mw->model->data(mw->model->index(i, 11), Qt::DisplayRole).toFloat();
        z2 = mw->model->data(mw->model->index(i, 12), Qt::DisplayRole).toFloat();
        r2 = mw->model->data(mw->model->index(i, 13), Qt::DisplayRole).toFloat();

        if(i == 0){
            autoCorretionPathAlgrith();
            auto currentPoint = mw->pbGetCurrentlyPoint();
            float xg = std::get<0>(currentPoint);
            float yg = std::get<1>(currentPoint);
            float zg = std::get<2>(currentPoint);
            float rg = std::get<3>(currentPoint);

            mw->model->setData(mw->model->index(i, 6), xg);
            mw->model->setData(mw->model->index(i, 7), yg);
            mw->model->setData(mw->model->index(i, 8), zg);
            mw->model->setData(mw->model->index(i, 9), rg);
        }

        if(name == "arc"){
            auto currentPoint = mw->pbGetCurrentlyPoint();
            float xg = std::get<0>(currentPoint);
            float yg = std::get<1>(currentPoint);
            float zg = std::get<2>(currentPoint);
            float rg = std::get<3>(currentPoint);

            mw->model->setData(mw->model->index(i, 6), xg);
            mw->model->setData(mw->model->index(i, 7), yg);
            mw->model->setData(mw->model->index(i, 8), zg);
            mw->model->setData(mw->model->index(i, 9), rg);

            auto currentPoint2 = mw->pbGetCurrentlyPoint();
            float x2g = std::get<0>(currentPoint2);
            float y2g = std::get<1>(currentPoint2);
            float z2g = std::get<2>(currentPoint2);
            float r2g = std::get<3>(currentPoint2);

            mw->model->setData(mw->model->index(i, 10), x2g);
            mw->model->setData(mw->model->index(i, 11), y2g);
            mw->model->setData(mw->model->index(i, 12), z2g);
            mw->model->setData(mw->model->index(i, 13), r2g);
        } else {
            auto currentPoint = mw->pbGetCurrentlyPoint();
            float xg = std::get<0>(currentPoint);
            float yg = std::get<1>(currentPoint);
            float zg = std::get<2>(currentPoint);
            float rg = std::get<3>(currentPoint);

            mw->model->setData(mw->model->index(i, 6), xg);
            mw->model->setData(mw->model->index(i, 7), yg);
            mw->model->setData(mw->model->index(i, 8), zg);
            mw->model->setData(mw->model->index(i, 9), rg);
        }
    }
}


void ascan::autoCorretionPathAlgrith(){




}
