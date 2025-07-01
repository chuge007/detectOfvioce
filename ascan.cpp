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


    // 启动 TCP 监听，监听端口
    startServer();

    // 连接发送按钮的点击事件
    connect(ui->saveScanStan_but, &QPushButton::clicked, this, &ascan::onSendstanPoint);
    connect(ui->autoCorrection_but, &QPushButton::clicked, this, &ascan::autoCorretionPath);
    connect(ui->pbstepCorrect, &QPushButton::clicked, this, &ascan::stepCorretionPath);
    connect(ui->pbstopCorrcet, &QPushButton::clicked, this, &ascan::stopCorretionPath);


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
    if (!tcpServer->listen(QHostAddress::Any, 34567)) {
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
    ui->disPlayIformationLb->setText(QString::fromLocal8Bit("客户端连接成功"));  // 显示接收到的数据（假设你有一个 QTextEdit 来显示）

}

void ascan::onReadyRead()
{
    // 当接收到数据时调用
    QByteArray data = tcpSocket->readAll();  // 读取所有数据
    QString message = QString::fromUtf8(data);  // 转换为字符串
    ui->disPlayIformationLb->setText(QString::fromLocal8Bit("此点信号值为：%1").arg(message));  // 显示接收到的数据（假设你有一个 QTextEdit 来显示）

    PointSing=message.toDouble();
    isSingUPdate=true;
    emit signalUpdated();

    if(isStanPointSing){
        stanPointSing=message.toDouble();
        Rsettings->setValue("AscanStanPoint",message);
        isStanPointSing=false;
        ui->disPlayIformationLb->setText(QString::fromLocal8Bit("设定的标准点信号值为：%1").arg(message));  // 显示接收到的数据（假设你有一个 QTextEdit 来显示）

    }
}

void ascan::onSendstanPoint()
{
    if (tcpSocket) {
        isStanPointSing=true;
        sendData("1");  // 发送一个“1”到服务器
    }
}

void ascan::sendData(const QString &data)
{
    if (tcpSocket) {
        tcpSocket->write(data.toUtf8());  // 将数据转换为字节流并发送
        tcpSocket->flush();  // 确保数据立刻发送
    }
}

void ascan::waitForSignal(int timeoutMs) {
    QEventLoop loop;
    QTimer timeoutTimer;
    timeoutTimer.setSingleShot(true);

    // 信号触发时退出循环
    connect(this, &ascan::signalUpdated, &loop, &QEventLoop::quit);
    // 超时也退出循环
    connect(&timeoutTimer, &QTimer::timeout, &loop, &QEventLoop::quit);

    timeoutTimer.start(timeoutMs);
    loop.exec();  // 进入事件循环，阻塞直到 quit()
}


void ascan::autoCorretionPath(){

    mw->dbManager->db.transaction();


    stopCorretion=false;
    qDebug()<<"autoCorretionPath";

    int row_count = mw->model->rowCount();
    float x0, y0, z0, r0, x1, y1, z1, r1, x2, y2, z2, r2;
    QString name;



    for(int i = 0; i < row_count; ++i)
    {

        if(stopCorretion){return;}


        qDebug()<<"autoCorretionPath-stepCorretion";


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
            autoCorretionPathAlgrith(i,x0,y0,z0,r0);
            auto currentPoint = mw->pbGetCurrentlyPoint();
            float xg = std::get<0>(currentPoint);
            float yg = std::get<1>(currentPoint);
            float zg = std::get<2>(currentPoint);
            float rg = std::get<3>(currentPoint);

            mw->model->setData(mw->model->index(i, 2), xg);
            mw->model->setData(mw->model->index(i, 3), yg);
            mw->model->setData(mw->model->index(i, 4), zg);
            mw->model->setData(mw->model->index(i, 5), rg);
        }

        if(name == "arc"){

            autoCorretionPathAlgrith(i,x1,y1,z1,r1);

            auto currentPoint = mw->pbGetCurrentlyPoint();
            float xg = std::get<0>(currentPoint);
            float yg = std::get<1>(currentPoint);
            float zg = std::get<2>(currentPoint);
            float rg = std::get<3>(currentPoint);

            mw->model->setData(mw->model->index(i, 6), xg);
            mw->model->setData(mw->model->index(i, 7), yg);
            mw->model->setData(mw->model->index(i, 8), zg);
            mw->model->setData(mw->model->index(i, 9), rg);

            autoCorretionPathAlgrith(i,x2,y2,z2,r2);

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


            autoCorretionPathAlgrith(i,x2,y2,z2,r2);

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

    if (!mw->model->submitAll()) {
        qDebug() << "提交数据失败:" << mw->model->lastError().text();
        mw->dbManager->db.rollback();
        QMessageBox::critical(this, "Error", "提交数据失败: " + mw->model->lastError().text());
        return;
    }


    if (!mw->dbManager->db.commit()) {
        qDebug() << "Failed to commit transaction:" << mw->dbManager->db.lastError().text();
        QMessageBox::critical(this, "Error", "事务提交失败:" + mw->dbManager->db.lastError().text());
        mw->dbManager->db.rollback();
    }

    stepCorretion=false;
}




void ascan::autoCorretionPathAlgrith(int index, float& x, float& y, float& z, float& r) {

    qDebug()<<"autoCorretionPathAlgrith";

    // 设置目标信号值
    float targetSignal = stanPointSing;  // 从接收到的信号中获取目标信号
    isSingUPdate=false;


    // 设置爬山算法的初始点
    float currentX = x;
    float currentY = y;
    float currentZ = z;
    float currentR = r;

    // 设置搜索范围和步长
    float searchRange = ui->searchRange_dSb->value();  // 搜索范围（单位）
    float stepSize = ui->searchStep_dsb->value();     // 步长（单位）
    float bestSignalDiff;

    qDebug()<<"searchRange:"<<searchRange;

    qDebug()<<"stepSize:"<<stepSize;


    // 获取当前点的邻域，基于步长和搜索范围
    std::vector<std::pair<float, float>> neighbors = getNeighbors(currentX, currentY, currentZ, currentR, searchRange, stepSize);

    qDebug()<<"getNeighbors:"<<neighbors;

    bool isFirst = true;  // 标记是否为第一个元素

    for (auto& neighbor : neighbors) {
        float nx = neighbor.first;
        float ny = neighbor.second;

        qDebug()<<"nx:"<<nx<<"  "<<"ny"<<ny;

        // 移动到邻居位置
        mw->scanDetectCtrl->runTargetPosition(nx, ny, currentZ, currentR);  // 执行目标位置移动
        qDebug()<<"autoCorretionPathAlgrith-runTargetPosition";


        // 发送信号请求
        sendData("1");  // 发送请求信号，等待信号更新

        waitForSignal();  // 阻塞直到接收到信号或超时

        // 计算当前邻域点的信号差值
        float diff = std::abs(PointSing - targetSignal);  // 使用接收到的信号与目标信号进行比较


        if (isFirst) {
            bestSignalDiff=diff;
            isFirst = false;
        }

        // 如果找到更接近目标信号的点，更新当前点
        if (diff < bestSignalDiff) {
            currentX = nx;
            currentY = ny;
            bestSignalDiff = diff;
        }

        isSingUPdate=false;


        qDebug() <<"neighbor"<<neighbor.first<<"  "<<neighbor.second;
    }

    mw->scanDetectCtrl->runTargetPosition(currentX, currentY, currentZ, currentR);  // 执行目标位置移动


    qDebug() << "runTargetPosition  "
             << "X:" << currentX
             << "Y:" << currentY
             << "Z:" << currentZ
             << "R:" << currentR;
}


// 获取邻居点：假设这里的邻居点是周围的一个小范围（±步长单位）
std::vector<std::pair<float, float>> ascan::getNeighbors(float x, float y, float z, float r, float searchRange, float stepSize) {
    std::vector<std::pair<float, float>> neighbors;

    // 在 x, y 方向进行小范围的探索（根据搜索范围和步长）
    for (float dx = -searchRange; dx <= searchRange; dx += stepSize) {
        for (float dy = -searchRange; dy <= searchRange; dy += stepSize) {
            neighbors.push_back({x + dx, y + dy});
        }
    }

    return neighbors;
}



void ascan::stepCorretionPath(){


    stepCorretion=true;
    qDebug()<<"stepCorretionPath";


}


void ascan::stopCorretionPath(){


    stopCorretion=true;
    qDebug()<<"stopCorretionPath";

}
