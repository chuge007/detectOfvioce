#include "scanDetect_frictionWelding.h"
#include "scancontrolabstract.h"

#include <iostream>

#include <QDebug>
#include <qwidget.h>
#include <QMessageBox>
#include <QTimer>
#include <QProgressDialog>
#include <QCoreApplication>


scanDetect_frictionWelding::scanDetect_frictionWelding(QObject *parent):
    ScanControlAbstract(parent)  // 调用基类构造函数
{
    qRegisterMetaType<QModbusDevice::State>("QModbusDevice::State");
    QMetaObject::invokeMethod(this, "init", Qt::QueuedConnection);
}

scanDetect_frictionWelding::~scanDetect_frictionWelding()
{

    QMetaObject::invokeMethod(this, "destroy", Qt::QueuedConnection);

}

void scanDetect_frictionWelding::init()
{
    initWidget();
    connectFun();
    readSetting();

}


void scanDetect_frictionWelding::initWidget()
{

    modbusClient = new QModbusTcpClient(this);

    timer = new QTimer(this);
    timer->setInterval(200);

}


void scanDetect_frictionWelding::connectFun()
{
    connect(modbusClient, &QModbusClient::stateChanged, this, &scanDetect_frictionWelding::modbusState);
    connect(timer, &QTimer::timeout, this, &scanDetect_frictionWelding::performTasks);
}


void scanDetect_frictionWelding::readSetting()
{
    if(Rsettings == nullptr) return;

    float xPos   = Rsettings->value("Virtual_origin_X", 0).toFloat();
    float yPos   = Rsettings->value("Virtual_origin_Y", 0).toFloat();
    float xLimit = Rsettings->value("Limit_position_X", 0).toFloat();
    float yLimit = Rsettings->value("Limit_position_Y", 0).toFloat();

    isHaveMachine = Rsettings->value("Have_basePlcData.MACHINE_ORIGIN", false).toBool();
    isHaveLimit = Rsettings->value("Have_Limit_origin", false).toBool();
    bool temp = Rsettings->value("Single_Scan", false).toBool();
    if(xPos < 0 || xPos > xLimit) xPos = 0;
    if(yPos < 0 || yPos > yLimit) yPos = 0;

    if(!temp) {
        scanModel = ScanModel::NormalScan;
    }else {
        scanModel = ScanModel::SingleScan;
    }


    zeroPoint.setX(static_cast<qreal>(xPos));
    zeroPoint.setY(static_cast<qreal>(yPos));
    limitPoint.setX(static_cast<qreal>(xLimit));
    limitPoint.setY(static_cast<qreal>(yLimit));


}


void scanDetect_frictionWelding::writeSetting()
{
    if(Rsettings == nullptr) return;

    Rsettings->setValue("Virtual_origin_X", zeroPoint.x());
    Rsettings->setValue("Virtual_origin_Y", zeroPoint.y());
    Rsettings->setValue("Limit_position_X", limitPoint.x());
    Rsettings->setValue("Limit_position_Y", limitPoint.y());

    Rsettings->setValue("Single_Scan", scanModel == ScanModel::NormalScan ? false : true);

    Rsettings->sync();

}


void scanDetect_frictionWelding::initStates()
{
    isStartScan = false;
    isStopScan = false;
    isAxisStop = false;
    updateCurPos = false;
    isEndScan = false;
    isJogDone = false;
}



//低位在前，高位在后
float scanDetect_frictionWelding::readModbusFloatData(uint16_t regHigh, uint16_t regLow)
{
    // 先把低位放到高 16 位，再把高位放到低 16 位
    uint32_t raw = (static_cast<uint32_t>(regLow) << 16)
            | static_cast<uint32_t>(regHigh);

    float value;
    std::memcpy(&value, &raw, sizeof(value));
    return value;
}

//高位在前，低位在后
QPair<quint16, quint16> scanDetect_frictionWelding::writeModbusFloatData(float value) {
    quint32 intValue = *reinterpret_cast<uint32_t*>(&value);
    quint16 high = (intValue >> 16) & 0xFFFF;
    quint16 low = intValue & 0xFFFF;

    // 返回顺序与 read 一致：低在前，高在后
    return QPair<quint16, quint16>(low, high);
}



void scanDetect_frictionWelding::writeAxisJog(int address, bool data)
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;

    QModbusDataUnit modbusData(QModbusDataUnit::Coils,  address, 1);
    modbusData.setValue(0, data);
    auto reply = modbusClient->sendWriteRequest(modbusData, 1);
    qDebug()<<"writeAxisJog******address:"<<address<<"data:"<<data;

    if (!reply) {
        return ;
    }
    QEventLoop loop;
    QObject::connect(reply, &QModbusReply::finished, &loop, &QEventLoop::quit);
    loop.exec();  // 等待finished信号
    bool success = (reply->error() == QModbusDevice::NoError);
    reply->deleteLater();

}

void scanDetect_frictionWelding::on_connectBtn_clicked()
{


    if(modbusClient->state() != QModbusDevice::ConnectedState ){
        modbusClient->setConnectionParameter(QModbusDevice::NetworkAddressParameter, PlcIP);
        modbusClient->setConnectionParameter(QModbusDevice::NetworkPortParameter, PlcPort);
        modbusClient->setNumberOfRetries(3);
        modbusClient->setTimeout(3000);

        if(modbusClient->connectDevice()){

        }
    }else {
        modbusClient->disconnectDevice();
    }


}


bool scanDetect_frictionWelding::sendStringCommand(QModbusClient *modbusClient, QModbusDataUnit::RegisterType type,
                                                   quint16 address, QString Value) {
    updateCurPos=true;
    if (modbusClient->state() != QModbusDevice::ConnectedState) {
        qWarning() << "Modbus client not connected.";
        return false;
    }
    modbusClient->setTimeout(3000);
    modbusClient->setNumberOfRetries(2);

    QVector<quint16> dataToSend;
    for (int i = 0; i < Value.length(); i += 2) {
        quint16 word = 0;
        if (i < Value.length())
            word |= static_cast<quint16>(Value[i].unicode()) << 8;
        if (i + 1 < Value.length())
            word |= static_cast<quint16>(Value[i + 1].unicode());
        dataToSend.append(word);
    }

    if (dataToSend.size() > 20) {
        qWarning() << "String length exceeds 20 registers. Truncating to 20.";
        return false;
    }

    // 高低字节互换
    for (int i = 0; i < dataToSend.size(); ++i) {
        dataToSend[i] = (dataToSend[i] << 8) | (dataToSend[i] >> 8);
    }

    QModbusDataUnit command(type, address, dataToSend.size());
    for (int i = 0; i < dataToSend.size(); ++i) {
        command.setValue(i, dataToSend[i]);
    }

    QModbusReply* reply = modbusClient->sendWriteRequest(command, 1);
    if (!reply) {
        qWarning() << "Failed to send Modbus write request (nullptr)";
        return false;
    }



    if (reply->error() != QModbusDevice::NoError) {
        qWarning() << "[sendStringCommand] Modbus write error:" << reply->errorString()
                   << "(value:" << Value << "address:" << address << ")";
        reply->deleteLater();
        return false;
    }

    QEventLoop loop;
    QObject::connect(reply, &QModbusReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    std::cout << "sendStringCommand success: " << Value.toStdString()
              << " to address: " << address << std::endl;
    reply->deleteLater();
    updateCurPos=false;
    return true;
}



bool scanDetect_frictionWelding::sendPulseCommand(QModbusClient *modbusClient, QModbusDataUnit::RegisterType rGtype,
                                                  quint16 address)
{
    updateCurPos=true;

    if (modbusClient->state() != QModbusDevice::ConnectedState) {
        qWarning() << "Modbus client not connected.";
        return false;
    }

    modbusClient->setTimeout(5000);
    modbusClient->setNumberOfRetries(3);

    auto sendValue = [&](int value) -> bool {
        QModbusDataUnit command(rGtype, static_cast<quint16>(address), 1);
        command.setValue(0, value);

        QModbusReply* reply = modbusClient->sendWriteRequest(command, 1);
        if (!reply) {
            qWarning() << "Failed to send Modbus write request (nullptr)";
            return false;  // ❌ 不要递归调用
        }

        QEventLoop loop;
        QObject::connect(reply, &QModbusReply::finished, &loop, &QEventLoop::quit);
        loop.exec();  // 等待 finished 信号

        if (reply->error() != QModbusDevice::NoError) {
            qWarning() << "[sendPulseCommand] Modbus write error:" << reply->errorString()
                       << "(value:" << value << " address:" << address << ")";
            reply->deleteLater();
            return false;
        }

        qDebug() << "sendPulseCommand success, value:" << value << " to address:" << address;
        reply->deleteLater();
        return true;
    };

    // Step 1: 先写入 1
    if (!sendValue(1))
        return false;

    // Step 2: 延时 100ms 后写入 0（使用 QTimer 延迟，不阻塞主线程事件循环）
    QEventLoop delayLoop;
    QTimer::singleShot(350, &delayLoop, &QEventLoop::quit);
    delayLoop.exec();

    updateCurPos=false;
    return sendValue(0);
}





//bool scanDetect_frictionWelding::sendPulseCommand(QModbusClient *modbusClient, QModbusDataUnit::RegisterType rGtype,
//                                                  float address){
//    if (modbusClient->state() != QModbusDevice::ConnectedState) {
//        qWarning() << "Modbus client not connected.";
//        return false;
//    }

//    modbusClient->setTimeout(5000); // 3秒
//    modbusClient->setNumberOfRetries(3); // 不重试

//    auto sendValue = [&](int value) -> bool {
//        QModbusDataUnit command(rGtype, address, 1);
//        command.setValue(0, value);

//        QModbusReply* reply = modbusClient->sendWriteRequest(command, 1);
//        if (!reply) {
//            qWarning() << "Failed to send Modbus write request (nullptr)";
//            sendPulseCommand(modbusClient,rGtype,address);
//            //return false;
//        }

//        QEventLoop loop;
//        QObject::connect(reply, &QModbusReply::finished, &loop, &QEventLoop::quit);
//        loop.exec();  // 等待 finished 信号

//        if (reply->error() != QModbusDevice::NoError) {
//            qWarning() << "[sendPulseCommand] Modbus write error:" << reply->errorString()
//                       << "(value:" << value << "address:" << address << ")";
//            reply->deleteLater();
//            return false;
//        }

//        qDebug() << "sendPulseCommand success, value:" << value << "to address:" << address;
//        reply->deleteLater();
//        return true;
//    };

//    // 按顺序发送 1 和 0
//    return sendValue(1) && sendValue(0);
//}

//bool  scanDetect_frictionWelding::sendStringCommand(QModbusClient *modbusClient, QModbusDataUnit::RegisterType type,
//                                                    float address,QString Value){

//    if (modbusClient->state() != QModbusDevice::ConnectedState) {
//        qWarning() << "Modbus client not connected.";
//        return false;
//    }



//    modbusClient->setTimeout(5000); // 3秒
//    modbusClient->setNumberOfRetries(3); // 不重试

//    QVector<quint16> dataToSend;
//    for (int i = 0; i < Value.length(); i += 2) {
//        quint16 word = 0;
//        if (i < Value.length())
//            word |= static_cast<quint16>(Value[i].unicode()) << 8;
//        if (i + 1 < Value.length())
//            word |= static_cast<quint16>(Value[i + 1].unicode());
//        dataToSend.append(word);
//    }

//    if (dataToSend.size() > 20) {
//        return false;
//        qWarning() << "String length exceeds 20 registers. Truncating to 20.";
//    }

//    // 高低字节互换
//    for (int i = 0; i < dataToSend.size(); ++i) {
//        dataToSend[i] = (dataToSend[i] << 8) | (dataToSend[i] >> 8);
//    }

//    QModbusDataUnit command(type, address, dataToSend.size());
//    for (int i = 0; i < dataToSend.size(); ++i) {
//        command.setValue(i, dataToSend[i]);
//    }

//    QModbusReply* reply = modbusClient->sendWriteRequest(command, 1);
//    if (!reply) {
//        qWarning() << "Failed to send Modbus write request (nullptr)";
//        sendStringCommand(modbusClient,  type,  address, Value);
//        //return false;
//    }

//    QEventLoop loop;
//    QObject::connect(reply, &QModbusReply::finished, &loop, &QEventLoop::quit);
//    loop.exec();  // 等待 finished 信号
//    if (reply->error() != QModbusDevice::NoError) {
//               qWarning() << "[sendStringCommand] Modbus write error:" << reply->errorString()
//                          << "(value:" << Value << "address:" << address << ")";
//               reply->deleteLater();
//               return false;
//           }

//    std::cout << "sendStringCommand success: " << Value.toStdString()
//              << " to address: " << address << std::endl;
//    reply->deleteLater();
//    return true;
//}

//bool scanDetect_frictionWelding::sendPulseCommand(QModbusClient *modbusClient, QModbusDataUnit::RegisterType rGtype,
//                                                  float address) {

//    if(modbusClient->state() != QModbusDevice::ConnectedState)
//        return false;

//    auto sendValue = [=](int value) -> bool {
//        QModbusDataUnit command(rGtype, address, 1);
//        command.setValue(0, value);
//        QModbusReply* reply = modbusClient->sendWriteRequest(command, 1);  // 假定设备ID为1
//        if (!reply) {
//            return false;
//        }
//        QEventLoop loop;
//        QObject::connect(reply, &QModbusReply::finished, &loop, &QEventLoop::quit);
//        loop.exec();  // 等待finished信号

//        // 检查请求是否成功
//        if(!(reply->error() == QModbusDevice::NoError)){

//            reply->deleteLater();
//            sendPulseCommand(modbusClient,rGtype,address);
//        }

//        reply->deleteLater();

//        qDebug()<<"sendPulseCommand:"<<address;

//        return true;
//    };

//    // 先发送1，再发送0
//    return sendValue(1) && sendValue(0);
//}

bool scanDetect_frictionWelding::sendCommandValue(QModbusClient *modbusClient, QModbusDataUnit::RegisterType rGtype,
                                                  quint16 address,float value){
     updateCurPos=true;
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return false;
    qDebug()<<"sendCommandValue:"<<address;
    modbusClient->setTimeout(5000); // 3秒
    modbusClient->setNumberOfRetries(3); // 不重试

     auto v=writeModbusFloatData(value);

    QModbusDataUnit command(rGtype, address, 2);
    command.setValue(0,v.first);
    command.setValue(1,v.second);

    auto *reply = modbusClient->sendWriteRequest(command, 1);

    QEventLoop loop;
    QObject::connect(reply, &QModbusReply::finished, &loop, &QEventLoop::quit);
    loop.exec();  // 等待 finished 信号
    bool success = (reply->error() == QModbusDevice::NoError);
    reply->deleteLater();
    updateCurPos=false;
    return success;
}


//bool  scanDetect_frictionWelding::sendStringCommand(QModbusClient *modbusClient, QModbusDataUnit::RegisterType type, float address,QString Value){


//    if (modbusClient->state() != QModbusDevice::ConnectedState)
//        return false;

//    // 假设要发送的字符串
//    QString strToSend = Value;

//    // 将字符串转换为 16 位整数数组
//    QVector<quint16> dataToSend;
//    for (int i = 0; i < strToSend.length();  i += 2) {
//        quint16 value = 0;
//        if (i < strToSend.length())  {
//            value |= static_cast<quint16>(strToSend[i].unicode()) << 8;
//        }
//        if (i + 1 < strToSend.length())  {
//            value |= static_cast<quint16>(strToSend[i + 1].unicode());
//        }
//        dataToSend.append(value);
//    }

//    // 确保数据长度不超过 20 个寄存器
//    if (dataToSend.size()  > 20) {
//        dataToSend.resize(20);
//    }


//    QModbusDataUnit command(
//                type,
//                address,
//                dataToSend.size()
//                );

//    for (int i = 0; i < dataToSend.size();  ++i) {
//        dataToSend[i] = ((dataToSend[i] & 0xFF) << 8) | ((dataToSend[i] >> 8) & 0xFF);
//    }

//    for (int i = 0; i < dataToSend.size();  ++i) {
//        command.setValue(i,  dataToSend[i]);
//    }

//    // 发送写请求
//    auto *reply = modbusClient->sendWriteRequest(command, 1);

//    // 等待请求完成
//    QEventLoop loop;
//    QObject::connect(reply, &QModbusReply::finished, &loop, &QEventLoop::quit);
//    loop.exec();   // 等待 finished 信号

//    // 检查请求是否成功
//    if(!(reply->error() == QModbusDevice::NoError)){

//        reply->deleteLater();
//        sendStringCommand(modbusClient,type,address,Value);


//    }

//    reply->deleteLater();

//    return true;


//}





void scanDetect_frictionWelding::on_startScanBtn_clicked()
{



    //sendStringCommand(modbusClient,QModbusDataUnit::HoldingRegisters,workPieceModbusAdress,workPiece);

    sendPulseCommand(modbusClient,QModbusDataUnit::Coils,basePlcData.Start);

}



void scanDetect_frictionWelding::on_stopScanBtn_clicked()
{

    sendPulseCommand(modbusClient,QModbusDataUnit::Coils,basePlcData.Stop);

}



void scanDetect_frictionWelding::on_endScanBtn_clicked()
{

    sendPulseCommand(modbusClient,QModbusDataUnit::Coils,basePlcData.End);

}


void scanDetect_frictionWelding::on_aganStartScanBtn_clicked()
{

    sendPulseCommand(modbusClient,QModbusDataUnit::Coils,basePlcData.AganStart);

}


void scanDetect_frictionWelding::on_setOriginBtn_clicked(QString axitType)
{
    float axitatypeAdress;

    if (axitType=="x"){
        axitatypeAdress=basePlcData.XOrigin;
    }
    else if (axitType=="y") {
        axitatypeAdress=basePlcData.YOrigin;
    }
    else if (axitType=="z") {
        axitatypeAdress=basePlcData.ZOrigin;
    }
    else if (axitType=="r") {
        axitatypeAdress=basePlcData.ROrigin;
    }
    sendPulseCommand(modbusClient,QModbusDataUnit::Coils,axitatypeAdress);

    qDebug()<<"on_setOriginBtn_clicked: "<<axitatypeAdress;

}



void scanDetect_frictionWelding::on_line_velocity_editingFinished(float val)
{


    sendCommandValue(modbusClient,QModbusDataUnit::HoldingRegisters,basePlcData.LineV,
                     val);
}



void scanDetect_frictionWelding::on_arc_velocity_editingFinished(float val)
{


    sendCommandValue(modbusClient,QModbusDataUnit::HoldingRegisters,basePlcData.ArcV,
                     val);
}



void scanDetect_frictionWelding::on_jog_velocity_editingFinished(float val)
{
    sendCommandValue(modbusClient,QModbusDataUnit::HoldingRegisters,basePlcData.pointV,
                     val);

}

void scanDetect_frictionWelding::on_point_velocity_editingFinished(float val){

    sendCommandValue(modbusClient,QModbusDataUnit::HoldingRegisters,basePlcData.jv,
                     val);

}


void scanDetect_frictionWelding::on_xAddBtn_clicked()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;

    if( isEndScan || isAxisStop || isJogDone || isRunTarget) return;

    updateCurPos = true;
    axisInch = AxisJog::XJogAdd;

}


void scanDetect_frictionWelding::on_xSubBtn_clicked()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;

    if( isEndScan || isAxisStop || isJogDone || isRunTarget) return;

    updateCurPos = true;
    axisInch = AxisJog::XJogSub;

}


void scanDetect_frictionWelding::on_yAddBtn_clicked()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;

    if( isEndScan || isAxisStop || isJogDone || isRunTarget) return;

    updateCurPos = true;
    axisInch = AxisJog::YJogAdd;

}


void scanDetect_frictionWelding::on_ySubBtn_clicked()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;

    if( isEndScan || isAxisStop || isJogDone || isRunTarget) return;

    updateCurPos = true;
    axisInch = AxisJog::YJogSub;

}


void scanDetect_frictionWelding::on_xAddBtn_pressed()
{

    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;
    if( isEndScan || isAxisStop || isJogDone || isRunTarget) return;

    updateCurPos = true;
    axisJog = AxisJog::XJogAddPressed;
    qDebug()<<"on_xAddBtn_pressed";
}


void scanDetect_frictionWelding::on_xAddBtn_released()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;
    if( isEndScan || isAxisStop || isJogDone || isRunTarget) return;
    qDebug()<<"on_xAddBtn_released";

    updateCurPos = true;
    axisJog = AxisJog::XJogAddReleased;

}


void scanDetect_frictionWelding::on_xSubBtn_pressed()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;
    if( isEndScan || isAxisStop || isJogDone || isRunTarget) return;
    qDebug()<<"on_xSubBtn_pressed";

    updateCurPos = true;
    axisJog = AxisJog::XJogSubPressed;
}


void scanDetect_frictionWelding::on_xSubBtn_released()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;
    if( isEndScan || isAxisStop || isJogDone || isRunTarget) return;
    qDebug()<<"on_xSubBtn_released";

    updateCurPos = true;
    axisJog = AxisJog::XJogSubReleased;
}


void scanDetect_frictionWelding::on_yAddBtn_pressed()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;
    if( isEndScan || isAxisStop || isJogDone || isRunTarget) return;
    qDebug()<<"on_yAddBtn_pressed";

    updateCurPos = true;
    axisJog = AxisJog::YJogAddPressed;
}


void scanDetect_frictionWelding::on_yAddBtn_released()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;
    if( isEndScan || isAxisStop || isJogDone || isRunTarget) return;
    qDebug()<<"on_yAddBtn_released";

    updateCurPos = true;
    axisJog = AxisJog::YJogAddReleased;
}


void scanDetect_frictionWelding::on_ySubBtn_pressed()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;
    if( isEndScan || isAxisStop || isJogDone || isRunTarget) return;
    qDebug()<<"on_ySubBtn_pressed";

    updateCurPos = true;
    axisJog = AxisJog::YJogSubPressed;
}


void scanDetect_frictionWelding::on_ySubBtn_released()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;
    if( isEndScan || isAxisStop || isJogDone || isRunTarget) return;
    qDebug()<<"on_ySubBtn_released";

    updateCurPos = true;
    axisJog = AxisJog::YJogSubReleased;
}


void scanDetect_frictionWelding::on_zAddBtn_pressed()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;
    if( isEndScan || isAxisStop || isJogDone || isRunTarget) return;
    qDebug()<<"on_zAddBtn_pressed";

    updateCurPos = true;
    axisJog = AxisJog::ZJogAddPressed;
}


void scanDetect_frictionWelding::on_zAddBtn_released()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;
    if( isEndScan || isAxisStop || isJogDone || isRunTarget) return;
    qDebug()<<"on_zAddBtn_released";

    updateCurPos = true;
    axisJog = AxisJog::ZJogAddReleased;
}


void scanDetect_frictionWelding::on_zSubBtn_pressed()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;
    if( isEndScan || isAxisStop || isJogDone || isRunTarget) return;
    qDebug()<<"on_zSubBtn_pressed";

    updateCurPos = true;
    axisJog = AxisJog::ZJogSubPressed;
}


void scanDetect_frictionWelding::on_zSubBtn_released()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;
    if( isEndScan || isAxisStop || isJogDone || isRunTarget) return;
    qDebug()<<"on_zSubBtn_released";

    updateCurPos = true;
    axisJog = AxisJog::ZJogSubReleased;
}


void scanDetect_frictionWelding::on_rAddBtn_pressed()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;
    if( isEndScan || isAxisStop || isJogDone || isRunTarget) return;
    qDebug()<<"on_rAddBtn_pressed";

    updateCurPos = true;
    axisJog = AxisJog::RJogAddPressed;
}


void scanDetect_frictionWelding::on_rAddBtn_released()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;
    if( isEndScan || isAxisStop || isJogDone || isRunTarget) return;
    qDebug()<<"on_rAddBtn_released";

    updateCurPos = true;
    axisJog = AxisJog::RJogAddReleased;
}


void scanDetect_frictionWelding::on_rSubBtn_pressed()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;
    if( isEndScan || isAxisStop || isJogDone || isRunTarget) return;
    qDebug()<<"on_rSubBtn_pressed";

    updateCurPos = true;
    axisJog = AxisJog::RJogSubPressed;
}


void scanDetect_frictionWelding::on_rSubBtn_released()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;
    if( isEndScan || isAxisStop || isJogDone || isRunTarget) return;
    qDebug()<<"on_rSubBtn_released";
    updateCurPos = true;
    axisJog = AxisJog::RJogSubReleased;
}


void scanDetect_frictionWelding::on_alarmResetBtn_clicked()
{


    sendPulseCommand(modbusClient,QModbusDataUnit::Coils,basePlcData.AlarmReset);

}

void scanDetect_frictionWelding::onBackOriginBtn_clicked(){

    sendPulseCommand(modbusClient,QModbusDataUnit::Coils,basePlcData.SetOrigin);


}

void scanDetect_frictionWelding::ZdetectHight(float hight){


    sendCommandValue(modbusClient,QModbusDataUnit::HoldingRegisters,basePlcData.ZdetctHight,
                     hight);
}

void scanDetect_frictionWelding::selectProcessType(int type){

    const QVector<int> processTypes = {
        processTypeGcode,
        processTypeFrictionWelding,
        processTypeBrazing
    };

    sendPulseCommand(modbusClient,QModbusDataUnit::Coils,processTypes[type]);

    qDebug()<<"select process"<<type;
}

void scanDetect_frictionWelding::runTargetPosition(double x, double y ,double z, double r)
{

    updateCurPos=true;
    if(modbusClient->state() != QModbusDevice::ConnectedState){
        QMessageBox::information(nullptr," warning ",QString::fromLocal8Bit(" 通讯未连接 "));
        return;
    }
    if( isEndScan || isAxisStop || isJogDone) return;

    if(!isRunTarget){
        updateCurPos = false;

    }

    //ZdetectHight(z);


    QModbusDataUnit modbusData(QModbusDataUnit::HoldingRegisters, basePlcData.MoveTargetX, 8);

    auto xpos = writeModbusFloatData(x);
    auto ypos = writeModbusFloatData(y);
    auto zpos = writeModbusFloatData(z);
    auto rpos = writeModbusFloatData(r);

    modbusData.setValue(0, xpos.first);
    modbusData.setValue(1, xpos.second);

    modbusData.setValue(2, ypos.first);
    modbusData.setValue(3, ypos.second);

    modbusData.setValue(4, zpos.first);
    modbusData.setValue(5, zpos.second);

    modbusData.setValue(6, rpos.first);
    modbusData.setValue(7, rpos.second);

    auto reply = modbusClient->sendWriteRequest(modbusData, 1);

    QEventLoop loop;
    QObject::connect(reply, &QModbusReply::finished, &loop, &QEventLoop::quit);
    loop.exec();  // 等待finished信号
    bool success = (reply->error() == QModbusDevice::NoError);
    reply->deleteLater();

    updateCurPos=false;
    sendPulseCommand(modbusClient,QModbusDataUnit::Coils,4822);

    qDebug()<<basePlcData.curX<<"sg";

}




void scanDetect_frictionWelding::destroy()
{
    if (modbusClient) {
        if (modbusClient->state() != QModbusDevice::UnconnectedState) {
            // 断开后 deleteLater，保证安全析构
            connect(modbusClient, &QModbusClient::stateChanged, this, [this](int state) {
                if (state == QModbusDevice::UnconnectedState) {
                    if (modbusClient) {
                        modbusClient->deleteLater();
                        modbusClient = nullptr;
                    }
                }
            });
            modbusClient->disconnectDevice();
        } else {
            modbusClient->deleteLater();
            modbusClient = nullptr;
        }
    }

    if (Rsettings) {
        writeSetting();
        Rsettings->deleteLater();
        Rsettings = nullptr;
    }

    if (timer) {
        timer->stop();
        timer->deleteLater();
        timer = nullptr;
    }
}



bool scanDetect_frictionWelding::modbusState()
{
    if(modbusClient->state() == QModbusDevice::ConnectedState){
        timer->start();
        qDebug() << "PLC Connection Successful!";

        emit modbusStateChange(modbusClient->state());
        return true;
    }else if (modbusClient->state() == QModbusDevice::UnconnectedState) {
        timer->stop();
        initStates();
        qDebug() << "PLC Connection Failure!";


        emit modbusStateChange(modbusClient->state());
        return false;
    }

}


void scanDetect_frictionWelding::performTasks()
{


    if(isAddRoute_dialogOpen||updateCurPos){

        //qDebug()<<"isAddRoute_dialogOpen"<<isAddRoute_dialogOpen;
        perfromJogTasks();
        updateCurPos=false;

    }
    //_sleep(500);
    updataCurrentPos();


}

void scanDetect_frictionWelding::updataCurrentPos()
{
    if (updateCurPos) return;
    if (modbusClient->state() != QModbusDevice::ConnectedState)
        return;


      updateCurPos = true;  // 标记为繁忙
    // 从地址 50 开始，读取 8 个寄存器（X/Y/Z/R 各 2 个）
    QModbusDataUnit data(QModbusDataUnit::HoldingRegisters, basePlcData.curX, 8);

    QModbusReply *reply = modbusClient->sendReadRequest(data, 1); // 1 是 Modbus 设备 ID
    if (reply) {
        if (!reply->isFinished()) {
            connect(reply, &QModbusReply::finished, [=]() {

                  updateCurPos = false;
                if (reply->error() == QModbusDevice::NoError) {
                    const QModbusDataUnit result = reply->result();

                    auto round2 = [](float v) {
                        return static_cast<float>(static_cast<int>(v * 100.0f)) / 100.0f;
                    };

                    float xPos = round2(readModbusFloatData(result.value(0), result.value(1))); // 50, 51
                    float yPos = round2(readModbusFloatData(result.value(2), result.value(3))); // 52, 53
                    float zPos = round2(readModbusFloatData(result.value(4), result.value(5))); // 54, 55
                    float rPos = round2(readModbusFloatData(result.value(6), result.value(7))); // 56, 57

                    currentPos.setX(static_cast<qreal>(xPos));
                    currentPos.setY(static_cast<qreal>(yPos));
                    curZ = zPos;
                    curR = rPos;
                    //                    qDebug() << QString("X=%1 Y=%2 Z=%3 R=%4")
                    //                                    .arg(xPos)
                    //                                    .arg(yPos)
                    //                                    .arg(zPos)
                    //                                    .arg(rPos);


                    emit positionChange(currentPos, curR, curZ);

                    readAxisErrorID();
                }
                reply->deleteLater();
            });
        } else {
            reply->deleteLater();
              updateCurPos = false;
        }
    }else{

          updateCurPos = false;
    }
}



void scanDetect_frictionWelding::perfromJogTasks()
{
    //qDebug()<<"****perfromJogTasks******";
//    if(axisInch != AxisJog::NotAxisJog && axisJog == AxisJog::NotAxisJog){
//        if(!isJogDone){
//            int address = 0;
//            float data = 0;
//            bool state = isJogCrossed(address, data);

//            if(state){
//                writeHoldingRegistersData(address, 2, data);
//            }else {
//                axisInch = AxisJog::NotAxisJog;
//            }
//        }else {
//            if(axisInch == XJogAdd || axisInch == XJogSub){
//                readAxisJogStatus(basePlcData.xDone);
//            }else if (axisInch == YJogAdd || axisInch == YJogSub) {
//                readAxisJogStatus(basePlcData.YDone);
//            }
//        }
//    }

    if(axisJog != AxisJog::NotAxisJog && axisInch == AxisJog::NotAxisJog){

        if (axisJog == lastAxisJog) {
            return;  // 不往下执行
        }


        switch (axisJog) {
        case XJogAddPressed:{
            writeAxisJog(basePlcData.X_ADD, true);
            //qDebug()<<"XJogAddPressed******";
        }break;
        case XJogAddReleased:{
            writeAxisJog(basePlcData.X_ADD, false);
        }break;
        case XJogSubPressed:{
            writeAxisJog(basePlcData.X_SUB, true);
        }break;
        case XJogSubReleased:{
            writeAxisJog(basePlcData.X_SUB, false);
        }break;
        case YJogAddPressed:{
            writeAxisJog(basePlcData.Y_ADD, true);
        }break;
        case YJogAddReleased:{
            writeAxisJog(basePlcData.Y_ADD, false);
        }break;
        case YJogSubPressed:{
            writeAxisJog(basePlcData.Y_SUB, true);
        }break;
        case YJogSubReleased:{
            writeAxisJog(basePlcData.Y_SUB, false);
        }break;
        case ZJogAddPressed:{
            writeAxisJog(basePlcData.Z_ADD, true);
        }break;
        case ZJogAddReleased:{
            writeAxisJog(basePlcData.Z_ADD, false);
        }break;
        case ZJogSubPressed:{
            writeAxisJog(basePlcData.Z_SUB, true);
        }break;
        case ZJogSubReleased:{
            writeAxisJog(basePlcData.Z_SUB, false);
        }break;
        case RJogAddPressed:{
            writeAxisJog(basePlcData.R_ADD, true);
        }break;
        case RJogAddReleased:{
            writeAxisJog(basePlcData.R_ADD, false);
        }break;
        case RJogSubPressed:{
            writeAxisJog(basePlcData.R_SUB, true);
        }break;
        case RJogSubReleased:{
            writeAxisJog(basePlcData.R_SUB, false);
        }break;
        }

        lastAxisJog=axisJog;
    }
}



//_________________________________________________________________________***************_________________________________________________________________________________________


void scanDetect_frictionWelding::writeRegisterGroup(int startAddress, const QVector<modelDate> &modelDates, int serverAddress)
{

    int  moveDatelen=12;                            //每条指令的总长度
    int  MaxregistersPerGroup = 100*moveDatelen;    // 最多能写的寄存器总长度
    int  maxSendRegisters= 120;                     // 一次写入的寄存器最大数量
    int  currentWriteCount = qMin(MaxregistersPerGroup, modelDates.count()*moveDatelen);  // 本次写入的寄存器总数量
    int  BatchPonits=maxSendRegisters/moveDatelen;                                          //每批次发送的点位数
    double  toltalBatch=std::ceil(static_cast<double>(currentWriteCount)/maxSendRegisters); //总批次
    int  totalPoints=modelDates.count();

    qDebug()<<"modelDates.count()"<<totalPoints;

    for (int batch=0; batch<toltalBatch; batch++) {


        totalPoints = qAbs(totalPoints - (BatchPonits*batch));
        int PointsRemaining = (totalPoints > BatchPonits) ? BatchPonits : totalPoints;

        qDebug()<<"totalPoints"<<totalPoints;
        qDebug()<<"PointsRemaining*moveDatelen"<<PointsRemaining*moveDatelen;
        QModbusDataUnit moveDate(QModbusDataUnit::HoldingRegisters, startAddress+(maxSendRegisters*batch), PointsRemaining*moveDatelen);

        // 设置要写入的寄存器值
        for (int i = 0; i <BatchPonits; i++) {


            int index=i+batch*BatchPonits;
            qDebug()<<"index"<<index;

            if (modelDates.count()<(index+1)){break;}

            if(modelDates[index].type=="arc"){
                auto xpos0 = writeModbusFloatData(modelDates[index].points[0][0]);
                auto ypos0 = writeModbusFloatData(modelDates[index].points[0][1]);
                auto rpos0 = writeModbusFloatData(modelDates[index].points[0][2]);
                auto xpos1 = writeModbusFloatData(modelDates[index].points[1][0]);
                auto ypos1 = writeModbusFloatData(modelDates[index].points[1][1]);
                auto rpos1 = writeModbusFloatData(modelDates[index].points[1][2]);

                moveDate.setValue(0+(i*moveDatelen), xpos0.first);
                moveDate.setValue(1+(i*moveDatelen), xpos0.second);
                moveDate.setValue(2+(i*moveDatelen), ypos0.first);
                moveDate.setValue(3+(i*moveDatelen), ypos0.second);
                moveDate.setValue(4+(i*moveDatelen), rpos0.first);
                moveDate.setValue(5+(i*moveDatelen), rpos0.second);

                moveDate.setValue(6+(i*moveDatelen), xpos1.first);
                moveDate.setValue(7+(i*moveDatelen), xpos1.second);
                moveDate.setValue(8+(i*moveDatelen), ypos1.first);
                moveDate.setValue(9+(i*moveDatelen), ypos1.second);
                moveDate.setValue(10+(i*moveDatelen), rpos1.first);
                moveDate.setValue(11+(i*moveDatelen), rpos1.second);


                QModbusDataUnit moveType(QModbusDataUnit::Coils, basePlcData.moveType+index, 1);
                moveType.setValue(0,false);
                auto *reply = modbusClient->sendWriteRequest(moveType, serverAddress);

                QEventLoop loop;
                QObject::connect(reply, &QModbusReply::finished, &loop, &QEventLoop::quit);
                loop.exec();  // 等待 finished 信号

                qDebug()<<"acr"<<index<<"  " <<index*moveDatelen<<"  "<<modelDates[index].points[0][0] <<" "<<modelDates[index].points[0][1]<<" "
                                                                                                                                           <<modelDates[index].points[0][2]
                        <<modelDates[index].points[1][0]<<" "<<modelDates[index].points[1][1]<<" "<<modelDates[index].points[1][2];


            }else {

                auto xpos0 = writeModbusFloatData(modelDates[index].points[0][0]);
                auto ypos0 = writeModbusFloatData(modelDates[index].points[0][1]);
                auto rpos0 = writeModbusFloatData(modelDates[index].points[0][2]);

                moveDate.setValue(0+(i*12), xpos0.first);
                moveDate.setValue(1+(i*12), xpos0.second);
                moveDate.setValue(2+(i*12), ypos0.first);
                moveDate.setValue(3+(i*12), ypos0.second);
                moveDate.setValue(4+(i*12), rpos0.first);
                moveDate.setValue(5+(i*12), rpos0.second);

                moveDate.setValue(6+(i*12), 0);
                moveDate.setValue(7+(i*12), 0);
                moveDate.setValue(8+(i*12), 0);
                moveDate.setValue(9+(i*12), 0);
                moveDate.setValue(10+(i*12), 0);
                moveDate.setValue(11+(i*12), 0);

                QModbusDataUnit moveType(QModbusDataUnit::Coils, basePlcData.moveType+index, 1);
                moveType.setValue(0,true);
                auto *reply = modbusClient->sendWriteRequest(moveType, serverAddress);

                QEventLoop loop;
                QObject::connect(reply, &QModbusReply::finished, &loop, &QEventLoop::quit);
                loop.exec();  // 等待 finished 信号

                qDebug()<<"l"<<index<<"  "<<index*moveDatelen<<"  "<<modelDates[index].points[0][0] <<" "<<
                                                                                                      modelDates[index].points[0][1]<<" "<<modelDates[index].points[0][2];

            }



        }

        qDebug() << "Write group from address " << startAddress+(maxSendRegisters*batch) << " start!";


        auto *reply = modbusClient->sendWriteRequest(moveDate, serverAddress);



        QEventLoop loop;
        QObject::connect(reply, &QModbusReply::finished, &loop, &QEventLoop::quit);
        loop.exec();  // 等待 finished 信号




        QMessageBox::information(nullptr, "Information", QString::fromLocal8Bit("点位发送完毕"));


    }

}


void scanDetect_frictionWelding::writeAc700PointRegisterGroup(int startAddress, const QVector<modelDate> &modelDates, int serverAddress)
{

    int  moveDatelen=12;                                //每条指令的总长度
    int  MaxregistersPerGroup = 100*moveDatelen;       // 最多能写的寄存器总长度
    int  maxSendRegisters= 120;                         // 一次写入的寄存器最大数量
    int  currentWriteCount = qMin(MaxregistersPerGroup, modelDates.count()*moveDatelen);  // 本次写入的寄存器总数量
    int  BatchPonits=maxSendRegisters/moveDatelen;                                        //每批次发送的点位数
    double  toltalBatch=std::ceil(static_cast<double>(currentWriteCount)/maxSendRegisters);//总批次
    int  totalPoints=modelDates.count();

    qDebug()<<"modelDates.count()"<<totalPoints;

    for (int batch=0; batch<toltalBatch; batch++) {


        totalPoints = qAbs(totalPoints - (BatchPonits*batch));
        int PointsRemaining = (totalPoints > BatchPonits) ? BatchPonits : totalPoints;

        qDebug()<<"totalPoints"<<totalPoints;
        qDebug()<<"PointsRemaining*moveDatelen"<<PointsRemaining*moveDatelen;
        QModbusDataUnit moveDate_xtran(QModbusDataUnit::HoldingRegisters, 5100+(maxSendRegisters*batch), PointsRemaining*moveDatelen);
        QModbusDataUnit moveDate_ytran(QModbusDataUnit::HoldingRegisters, 5300+(maxSendRegisters*batch), PointsRemaining*moveDatelen);
        QModbusDataUnit moveDate_rtran(QModbusDataUnit::HoldingRegisters, 5500+(maxSendRegisters*batch), PointsRemaining*moveDatelen);
        QModbusDataUnit moveDate_xend(QModbusDataUnit::HoldingRegisters, 5700+(maxSendRegisters*batch), PointsRemaining*moveDatelen);
        QModbusDataUnit moveDate_yend(QModbusDataUnit::HoldingRegisters, 5900+(maxSendRegisters*batch), PointsRemaining*moveDatelen);
        QModbusDataUnit moveDate_rend(QModbusDataUnit::HoldingRegisters, 6100+(maxSendRegisters*batch), PointsRemaining*moveDatelen);

        // 设置要写入的寄存器值
        for (int i = 0; i <BatchPonits; i++) {


            int index=i+batch*BatchPonits;
            qDebug()<<"index"<<index;

            if (modelDates.count()<(index+1)){break;}

            if(modelDates[index].type=="arc"){
                auto xpos0 = writeModbusFloatData(modelDates[index].points[0][0]);
                auto ypos0 = writeModbusFloatData(modelDates[index].points[0][1]);
                auto rpos0 = writeModbusFloatData(modelDates[index].points[0][2]);
                auto xpos1 = writeModbusFloatData(modelDates[index].points[1][0]);
                auto ypos1 = writeModbusFloatData(modelDates[index].points[1][1]);
                auto rpos1 = writeModbusFloatData(modelDates[index].points[1][2]);

                moveDate_xend.setValue(0+(i*moveDatelen), xpos0.first);
                moveDate_xend.setValue(1+(i*moveDatelen), xpos0.second);

                moveDate_yend.setValue(2+(i*moveDatelen), ypos0.first);
                moveDate_yend.setValue(3+(i*moveDatelen), ypos0.second);

                moveDate_rend.setValue(4+(i*moveDatelen), rpos0.first);
                moveDate_rend.setValue(5+(i*moveDatelen), rpos0.second);

                moveDate_xtran.setValue(6+(i*moveDatelen), xpos1.first);
                moveDate_xtran.setValue(7+(i*moveDatelen), xpos1.second);

                moveDate_ytran.setValue(8+(i*moveDatelen), ypos1.first);
                moveDate_ytran.setValue(9+(i*moveDatelen), ypos1.second);

                moveDate_rtran.setValue(10+(i*moveDatelen), rpos1.first);
                moveDate_rtran.setValue(11+(i*moveDatelen), rpos1.second);


                QModbusDataUnit moveType(QModbusDataUnit::Coils, basePlcData.moveType+index, 1);
                moveType.setValue(0,false);
                auto *reply = modbusClient->sendWriteRequest(moveType, serverAddress);

                QEventLoop loop;
                QObject::connect(reply, &QModbusReply::finished, &loop, &QEventLoop::quit);
                loop.exec();  // 等待 finished 信号

                qDebug()<<"acr"<<index<<"  " <<index*moveDatelen<<"  "<<modelDates[index].points[0][0] <<" "<<modelDates[index].points[0][1]<<" "
                                                                                                                                           <<modelDates[index].points[0][2]
                        <<modelDates[index].points[1][0]<<" "<<modelDates[index].points[1][1]<<" "<<modelDates[index].points[1][2];


            }else {

                auto xpos0 = writeModbusFloatData(modelDates[index].points[0][0]);
                auto ypos0 = writeModbusFloatData(modelDates[index].points[0][1]);
                auto rpos0 = writeModbusFloatData(modelDates[index].points[0][2]);

                moveDate_xend.setValue(0+(i*12), xpos0.first);
                moveDate_xend.setValue(1+(i*12), xpos0.second);
                moveDate_yend.setValue(2+(i*12), ypos0.first);
                moveDate_yend.setValue(3+(i*12), ypos0.second);
                moveDate_rend.setValue(4+(i*12), rpos0.first);
                moveDate_rend.setValue(5+(i*12), rpos0.second);

                moveDate_xtran.setValue(6+(i*12), 0);
                moveDate_xtran.setValue(7+(i*12), 0);
                moveDate_ytran.setValue(8+(i*12), 0);
                moveDate_ytran.setValue(9+(i*12), 0);
                moveDate_rtran.setValue(10+(i*12), 0);
                moveDate_rtran.setValue(11+(i*12), 0);

                QModbusDataUnit moveType(QModbusDataUnit::Coils, basePlcData.moveType+index, 1);
                moveType.setValue(0,true);
                auto *reply = modbusClient->sendWriteRequest(moveType, serverAddress);

                QEventLoop loop;
                QObject::connect(reply, &QModbusReply::finished, &loop, &QEventLoop::quit);
                loop.exec();  // 等待 finished 信号

                qDebug()<<"l"<<index<<"  "<<index*moveDatelen<<"  "<<modelDates[index].points[0][0] <<" "<<
                                                                                                      modelDates[index].points[0][1]<<" "<<modelDates[index].points[0][2];

            }



        }

        qDebug() << "Write group from address " << startAddress+(maxSendRegisters*batch) << " start!";



        // 将它们按顺序放入容器中
        QVector<QModbusDataUnit*> modbusUnits = {
            &moveDate_xtran,
            &moveDate_ytran,
            &moveDate_rtran,
            &moveDate_xend,
            &moveDate_yend,
            &moveDate_rend
        };

        // 逐个发送
        for (QModbusDataUnit* unit : modbusUnits) {
            if (auto* reply = modbusClient->sendWriteRequest(*unit, serverAddress)) {
                QEventLoop loop;
                QObject::connect(reply, &QModbusReply::finished, &loop, &QEventLoop::quit);
                loop.exec();  // 等待响应
                reply->deleteLater();

                if (reply->error() != QModbusDevice::NoError) {
                    qWarning() << "Modbus write failed:" << reply->errorString();
                    break;
                }
            } else {
                qWarning() << "Failed to create Modbus write request";
                break;
            }
        }



        QMessageBox::information(nullptr, "Information", QString::fromLocal8Bit("点位发送完毕"));


    }

}





void scanDetect_frictionWelding::setXAxisVelocity(float vel)
{
    xVelocity = vel;
    writeAxisVelocity(basePlcData.xV, 2, xVelocity);


}


void scanDetect_frictionWelding::setYAxisVelocity(float vel)
{
    yVelocity = vel;
    writeAxisVelocity(basePlcData.yV, 2, yVelocity);
}


void scanDetect_frictionWelding::setJogVelocity(float vel)
{
    jogVelocity = vel;
    writeAxisVelocity(basePlcData.jv, 2, jogVelocity);
}

void scanDetect_frictionWelding::writeAxisLimitPosition()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;

    QModbusDataUnit modbusData(QModbusDataUnit::Coils,  basePlcData.LIMIT_POINT, 1);
    modbusData.setValue(0, 1);
    auto reply = modbusClient->sendWriteRequest(modbusData, 1);
    if(reply){
        if (!reply->isFinished())
        {
            connect(reply, &QModbusReply::finished, [=](){
                if(reply->error() == QModbusDevice::NoError){
                    limitPoint.setX(currentPos.x());
                    limitPoint.setY(currentPos.y());

                    Rsettings->setValue("Limit_position_X", limitPoint.x());
                    Rsettings->setValue("Limit_position_Y", limitPoint.y());
                    isHaveLimit = true;
                }else {
                    writeAxisLimitPosition();
                }
                reply->deleteLater();
            });
        }else {
            reply->deleteLater();
        }
    }
}


void scanDetect_frictionWelding::writeAxisMachineOrigin()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;

    QModbusDataUnit modbusData(QModbusDataUnit::Coils,  basePlcData.MACHINE_ORIGIN, 1);
    modbusData.setValue(0, 1);
    auto reply = modbusClient->sendWriteRequest(modbusData, 1);
    if(reply){
        if (!reply->isFinished())
        {
            connect(reply, &QModbusReply::finished, [=](){
                if(reply->error() == QModbusDevice::NoError){
                    zeroPoint.setX(0);
                    zeroPoint.setY(0);

                    Rsettings->setValue("MACHINE_ORIGIN_X", limitPoint.x());
                    Rsettings->setValue("MACHINE_ORIGIN_Y", limitPoint.y());
                    isHaveMachine = true;
                }else {
                    writeAxisLimitPosition();
                }
                reply->deleteLater();
            });
        }else {
            reply->deleteLater();
        }
    }
}



bool scanDetect_frictionWelding::isXCrossed()
{
    bool state = false;
    float xTemp = static_cast<float>(zeroPoint.x());
    if(static_cast<qreal>(xTemp) > limitPoint.x()) {
        state = true;
        qDebug() << "scan X-axis crossed";
    }

    return state;
}


bool scanDetect_frictionWelding::isYCrossed()
{
    bool state = false;
    float yTemp = static_cast<float>(zeroPoint.y()) ;
    if(static_cast<qreal>(yTemp) > limitPoint.y()) {
        state = true;
        qDebug() << "scan Y-axis crossed";
    }

    return state;
}


bool scanDetect_frictionWelding::isJogCrossed(int &address, float &data){
    bool state = true;

    switch (axisInch) {
    case AxisJog::NotAxisJog: state = false; break;
    case AxisJog::XJogAdd: {
        address = basePlcData.curX;
        data = static_cast<float>(currentPos.x()) + jopStep;
        if(static_cast<qreal>(data) >= limitPoint.x()) state = false;
    }break;
    case AxisJog::XJogSub: {
        address = basePlcData.curX;
        data = static_cast<float>(currentPos.x()) - jopStep;
        if(static_cast<qreal>(data) < 0) state = false;
    }break;
    case AxisJog::YJogAdd: {
        address = basePlcData.curY;
        data = static_cast<float>(currentPos.y()) + jopStep;
        if(static_cast<qreal>(data) >= limitPoint.y()) state = false;
    }break;
    case AxisJog::YJogSub: {
        address = basePlcData.curY;
        data = static_cast<float>(currentPos.y()) - jopStep;
        if(static_cast<qreal>(data) < 0) state = false;
    }break;
    }

    //没有极限点不做先为限位
    if(!isHaveMachine || !isHaveLimit) state = true;

    return state;
}

void scanDetect_frictionWelding::on_setLimitBtn_clicked()
{
    writeAxisLimitPosition();
}


void scanDetect_frictionWelding::on_setMachineBtn_clicked()
{
    writeAxisMachineOrigin();
}



void scanDetect_frictionWelding::writeHoldingRegistersData(int address, quint16 size, float data)
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;

    QModbusDataUnit modbusData(QModbusDataUnit::HoldingRegisters, address, size);

    auto d = writeModbusFloatData(data);
    modbusData.setValue(0, d.first);
    modbusData.setValue(1, d.second);

    auto reply = modbusClient->sendWriteRequest(modbusData, 1);
    if(reply){
        if (!reply->isFinished())
        {
            connect(reply, &QModbusReply::finished, [=](){
                if(reply->error() == QModbusDevice::NoError){
                    //判断如果是开始扫查触发，并开始执行任务
                    if(isStartScan){
                        if(manState[0]) manState[1] = false;
                    }
                    if(axisInch != AxisJog::NotAxisJog){
                        isJogDone = true;
                    }
                }else{
                    //                    isPerform = false;
                    //                    if(!isEndScan)  //如果是结束扫查，写失败就不处理
                    //                    writeHoldingRegistersData(address, size, data);

                }
                reply->deleteLater();
            });
        }else {
            reply->deleteLater();
        }
    }
}


void scanDetect_frictionWelding::writeAxisVelocity(int address, quint16 size, float data)
{
    updateCurPos=true;
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;
    QModbusDataUnit modbusData(QModbusDataUnit::HoldingRegisters,  address, size);

    auto xpos = writeModbusFloatData(data);
    modbusData.setValue(0, xpos.first);
    modbusData.setValue(1, xpos.second);

    auto reply = modbusClient->sendWriteRequest(modbusData, 1);
    if(reply){
        if (!reply->isFinished())
        {
            connect(reply, &QModbusReply::finished, [=](){
                if(reply->error() == QModbusDevice::NoError){
                }else {
                    writeAxisVelocity(address, size, data);
                }
                reply->deleteLater();
            });
        }else {
            reply->deleteLater();
        }
    }

    updateCurPos=false;
}


void scanDetect_frictionWelding::readAxisVelocity(int address, quint16 size)
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;

    QModbusDataUnit modbusData(QModbusDataUnit::HoldingRegisters,  address, size);

    auto reply = modbusClient->sendReadRequest(modbusData, 1);
    if(reply){
        if (!reply->isFinished())
        {
            connect(reply, &QModbusReply::finished, [=](){
                if(reply->error() == QModbusDevice::NoError){
                    float xVel = readModbusFloatData(reply->result().value(1), reply->result().value(0));
                    float yVel = readModbusFloatData(reply->result().value(3), reply->result().value(2));
                    float jogVel = readModbusFloatData(reply->result().value(9), reply->result().value(8));
                    emit velocityChange(xVel, yVel, jogVel);

                }else {
                    readAxisVelocity(address, size);
                }
                reply->deleteLater();
            });
        }else {
            reply->deleteLater();
        }
    }
}


void scanDetect_frictionWelding::readAxisJogStatus(int address)
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;

    QModbusDataUnit modbusData(QModbusDataUnit::Coils,  address, 1);

    auto reply = modbusClient->sendReadRequest(modbusData, 1);
    if(reply){
        if (!reply->isFinished())
        {
            connect(reply, &QModbusReply::finished, [=](){
                if(reply->error() == QModbusDevice::NoError){
                    int temp = reply->result().value(0);
                    if(temp == 1){
                        axisInch = AxisJog::NotAxisJog;
                        isJogDone = false;
                        updateCurPos = true;
                    }
                    updataCurrentPos();
                }else {
                    //            readAxisVelocity(address, size);
                }
                reply->deleteLater();
            });
        }else {
            reply->deleteLater();
        }
    }
}


void scanDetect_frictionWelding::readAxisErrorID()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;

    QModbusDataUnit modbusData(QModbusDataUnit::HoldingRegisters,  basePlcData.AxiSid, 4);

    auto reply = modbusClient->sendReadRequest(modbusData, 1);
    if(reply){
        if (!reply->isFinished())
        {
            connect(reply, &QModbusReply::finished, [=](){
                if(reply->error() == QModbusDevice::NoError){
                    int xErrorId = reply->result().value(0);
                    int yErrorId = reply->result().value(1);
                    //顺便读取机械按键的是否按下
                    int m_start = reply->result().value(2);
                    int m_stop = reply->result().value(3);

                    if(xErrorId || yErrorId)
                        emit axisError(xErrorId, yErrorId);

                    if(m_start == 1 && m_stop == 0 ){
                        emit machineStart();
                    }else if (m_start == 0 && m_stop == 1 ) {
                        emit machineStop();
                    }
                }
                reply->deleteLater();
            });
        }else {
            reply->deleteLater();
        }
    }
}


void scanDetect_frictionWelding::writeAxisReset()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;

    updateCurPos=true;
    QModbusDataUnit modbusData(QModbusDataUnit::Coils,  basePlcData.AlarmReset, 1);
    modbusData.setValue(0, 1);
    auto reply = modbusClient->sendWriteRequest(modbusData, 1);
    if(reply){
        if (!reply->isFinished())
        {
            connect(reply, &QModbusReply::finished, [=](){
                if(reply->error() != QModbusDevice::NoError){
                    writeAxisReset();
                }
                reply->deleteLater();
            });
        }else {
            reply->deleteLater();
        }
    }

    updateCurPos=false;
}



//void scanDetect_frictionWelding::readAxisEndState()
//{
//    if(modbusClient->state() != QModbusDevice::ConnectedState)
//        return;

//    QModbusDataUnit data(QModbusDataUnit::Coils, basePlcData.xDone, 2);

//    QModbusReply *reply = modbusClient->sendReadRequest(data, 1);
//    if(reply){
//        if (!reply->isFinished())
//        {
//            connect(reply, &QModbusReply::finished, [=](){

//                if(reply->error() == QModbusDevice::NoError){
//                    if(isEndScan){

//                        if(reply->result().value(0) == 1 &&
//                                reply->result().value(1) == 1){
//                            isEndScan = false;
//                        }
//                    }

//                    //正在执行目标点位
//                    if(isRunTarget){
//                        int temp1 = reply->result().value(0);
//                        int temp2 = reply->result().value(1);
//                        if(temp1 && temp2){
//                            isRunTarget = false;
//                        }
//                    }
//                }else {
//                }
//                reply->deleteLater();
//            });
//        }else {
//            reply->deleteLater();
//        }
//    }
//}
//                    if(isEndScan || isRunTarget){//如果在执行结束扫查任务, 判断轴是否回到虚拟原点
//                        readAxisEndState();
//                        return ;
//                             }
//void scanDetect_frictionWelding::writeBackZero()
//{
//    if(modbusClient->state() != QModbusDevice::ConnectedState)
//        return;

//    QModbusDataUnit modbusData(QModbusDataUnit::HoldingRegisters,  basePlcData.X_VIRTUAL_ORIGIN, 4);

//    auto xpos = writeModbusFloatData(static_cast<float>(zeroPoint.x()));
//    auto ypos = writeModbusFloatData(static_cast<float>(zeroPoint.y()));
//    modbusData.setValue(0, xpos.first);
//    modbusData.setValue(1, xpos.second);
//    modbusData.setValue(2, ypos.first);
//    modbusData.setValue(3, ypos.second);

//    auto reply = modbusClient->sendWriteRequest(modbusData, 1);
//    if(reply){
//        if (!reply->isFinished())
//        {
//            connect(reply, &QModbusReply::finished, [=](){
//                if(reply->error() == QModbusDevice::NoError){
//                    //            writeAxisStopStatus(X_START);
//                    writeEndScanStatus();

//                }else {
//                    writeBackZero();
//                }
//                reply->deleteLater();
//            });
//        }else {
//            reply->deleteLater();
//        }
//    }
//}


//void scanDetect_frictionWelding::writeEndScanStatus()
//{
//    if(modbusClient->state() != QModbusDevice::ConnectedState)
//        return;

//    QModbusDataUnit modbusData(QModbusDataUnit::Coils,  END_SCAN, 1);

//    modbusData.setValue(0, 1);

//    auto reply = modbusClient->sendWriteRequest(modbusData, 1);
//    if(reply){
//        if (!reply->isFinished())
//        {
//            connect(reply, &QModbusReply::finished, [=](){
//                if(reply->error() == QModbusDevice::NoError){
//                    updateCurPos = true;
//                    timer->start();
//                }else {
//                    writeEndScanStatus();
//                }
//                reply->deleteLater();
//            });
//        }else {
//            reply->deleteLater();
//        }
//    }
//}


//void scanDetect_frictionWelding::writeAxisStopStatus(int address)
//{
//    if(modbusClient->state() != QModbusDevice::ConnectedState)
//        return;

//    QModbusDataUnit data(QModbusDataUnit::Coils, address, 2);
//    data.setValue(0, 1);
//    data.setValue(1, 1);
//    QModbusReply *reply = modbusClient->sendWriteRequest(data, 1);
//    if(reply){
//        if (!reply->isFinished())
//        {
//            connect(reply, &QModbusReply::finished, [=](){
//                if(reply->error() == QModbusDevice::NoError){
//                    if(isEndScan){
//                        return ;    //结束扫查，不需要置位
//                    }

//                    if(isRunTarget){
//                        isRunTarget = false;
//                        return;
//                    }

//                    if(address == X_STOP){
//                        isStopScan = false;
//                        isAxisStop = true;
//                        updateCurPos = true;
//                    }else if (address == X_START) {
//                        isKeepScan = false;
//                        isStartScan = true;
//                        isAxisStop = false;
//                    }
//                }else {
//                    writeAxisStopStatus(address);
//                }
//                reply->deleteLater();
//            });
//        }else {
//            reply->deleteLater();
//        }
//    }
//}

//void scanDetect_frictionWelding::readAxisRunStatus(int address, quint16 size)
//{
//    if(modbusClient->state() != QModbusDevice::ConnectedState)
//        return;

//    QModbusDataUnit data(QModbusDataUnit::Coils, address, size);

//    QModbusReply *reply = modbusClient->sendReadRequest(data, 1);
//    if(reply){
//        if (!reply->isFinished())
//        {
//            connect(reply, &QModbusReply::finished, [=](){
//                if(reply->error() == QModbusDevice::NoError){
//                    if(tasks.isEmpty()){
//                        isPerform = false;
//                        reply->deleteLater();
//                        return ;
//                    }

//                    //正在执行自动扫查
//                    if(isStartScan){
//                        int temp = false;
//                        if(tasks.head().first == "x"){
//                            temp = reply->result().value(0);
//                            if(temp) emit scanRowEnd(AxisState::XMoveDone);
//                        }else if (tasks.head().first == "y") {
//                            temp = reply->result().value(1);
//                            if(temp) emit scanRowEnd(AxisState::YMoveDone);
//                        }

//                        if(temp){
//                            isPerform = false;
//                            if(!tasks.isEmpty()) tasks.pop_front();
//                        }
//                        if(tasks.count() != 0){
//                            updataCurrentPos();
//                        }else {
//                            keepTime = 0;
//                            emit scanTime("");
//                            updateCurPos = true;
//                        }
//                    }
//                }else {
//                    //                    if(!isEndScan)  //如果是结束扫查，写失败就不处理
//                    //                    readAxisRunStatus(address, size);
//                }
//                reply->deleteLater();
//            });
//        }else {
//            delete reply;
//        }
//    }
//}


//bool scanDetect_frictionWelding::nextScan()
//{
//    if(!tasks.isEmpty()){
//        manState[1] = true;
//    }else {
//        manState[1] = false;
//    }
//    return manState[1];
//}

//void scanDetect_frictionWelding::setManualModel(bool states)
//{
//    manState[0] = states;
//}

//void scanDetect_frictionWelding::on_singleScan_toggled(bool checked)
//{
//    if(checked){
//        scanModel = ScanModel::SingleScan;
//    }else {
//        scanModel = ScanModel::NormalScan;
//    }
//}

//void scanDetect_frictionWelding::setAxisJogStep(int step)
//{
//    jopStep = step;
//    qDebug() << jopStep;
//}


//void scanDetect_frictionWelding::on_jogStep_1_clicked()
//{
//    setAxisJogStep(1);
//}

//void scanDetect_frictionWelding::on_jogStep_5_clicked()
//{
//    setAxisJogStep(5);
//}

//void scanDetect_frictionWelding::on_jogStep_10_clicked()
//{
//    setAxisJogStep(10);
//}


//void scanDetect_frictionWelding::perfromStopScanTasks()
//{
//    if(isStopScan){
//        writeAxisStopStatus(X_STOP);
//    }
//}

//void scanDetect_frictionWelding::perfromEndScanTasks()
//{
//    if(isEndScan){
//        writeBackZero();
//    }
//}


//void scanDetect_frictionWelding::creataTasksTable()
//{
//    int stepNum = 0;
//    if(yScanLenght <= yScanStep || qFuzzyIsNull(yScanStep)){
//        stepNum = 1;
//    }else {
//        float divisor = yScanLenght / yScanStep;
//        stepNum = static_cast<int>(divisor);
//        float  remainder = divisor - stepNum;

//        if(remainder > 0){
//            stepNum++;
//        }
//    }
//    qDebug() << "Y-axis Scan Number " << stepNum;

//    float xPos = static_cast<float>(zeroPoint.x());
//    float yPos = static_cast<float>(zeroPoint.y());
//    float xTemp = xPos + xScanLenght;
//    tasks.clear();
//    if(scanModel == ScanModel::NormalScan){
//        emit scanRowNumChange(stepNum);
//        //        tasks.push_back(QPair<QString, float>("x", static_cast<float>(zeroPoint.x())));
//        //        tasks.push_back(QPair<QString, float>("y", static_cast<float>(zeroPoint.y())));
//        if(stepNum > 1){
//            bool b = true;
//            for (int i=0; i<=stepNum-1; i++) {
//                tasks.push_back(QPair<QString, float>("x", xTemp));
//                tasks.push_back(QPair<QString, float>("y", yPos+(yScanStep*(i+1))));
//                xTemp = b ? xPos : xPos + xScanLenght;
//                b = !b;
//            }
//            tasks.pop_back();
//        }else {
//            tasks.push_back(QPair<QString, float>("x", xTemp));
//        }
//    }else if (scanModel == ScanModel::SingleScan) {
//        emit scanRowNumChange(stepNum*2);
//        //        tasks.push_back(QPair<QString, float>("x", static_cast<float>(zeroPoint.x())));
//        //        tasks.push_back(QPair<QString, float>("y", static_cast<float>(zeroPoint.y())));

//        if(stepNum > 1){
//            for (int i=0; i<=stepNum-1; i++) {
//                tasks.push_back(QPair<QString, float>("x", xTemp));
//                tasks.push_back(QPair<QString, float>("x", static_cast<float>(zeroPoint.x())));
//                tasks.push_back(QPair<QString, float>("y", yPos+(yScanStep*(i+1))));
//            }
//            tasks.pop_back();
//        }else {
//            tasks.push_back(QPair<QString, float>("x", xTemp));
//            tasks.push_back(QPair<QString, float>("x", static_cast<float>(zeroPoint.x())));
//        }
//    }

//    if(!tasks.isEmpty()){
//        keepTime = 0;
//        for (int i=0; i< tasks.count(); i++) {
//            if(tasks[i].first == "x"){
//                keepTime += xScanLenght / xVelocity;
//            }else if(tasks[i].first == "y"){
//                keepTime += yScanStep / yVelocity;
//            }
//        }
//        keepTime *= 1000;
//    }
//    //    qDebug() << "tasks count" << tasks.count();
//    //    for (int i=0; i< tasks.count(); i++) {
//    //        qDebug() << tasks[i];
//    //    }
//    isStartScan = true;
//}


//perfromStopScanTasks();
//perfromStartScanTasks();

//void scanDetect_frictionWelding::perfromStartScanTasks()
//{
//    if(tasks.count() == 0) {
//        //        if(!isInit || (axisInch != AxisJog::NotAxisJog)) updateCurPos = true;
//        isStartScan = false;
//        return;
//    }

//    if(isKeepScan){
//        writeAxisStopStatus(X_START);
//    }

//    //执行任务列表
//    if(isStartScan){
//        if(!tasks.isEmpty()){
//            if(tasks.head().first == "x" && !isPerform && (manState[0] ? manState[1] : true)){
//                int address = R_REGISTER_BASE + X_TARTPOS;
//                writeHoldingRegistersData(address, 2, tasks.head().second);
//                return;
//            }
//            else if(tasks.head().first == "y" && !isPerform /*&& (manState[0] ? manState[1] : true)*/){
//                int address = R_REGISTER_BASE + Y_TARTPOS;
//                writeHoldingRegistersData(address, 2, tasks.head().second);
//                return;
//            }

//            //读轴的动作状态
//            if(isPerform){
//                readAxisRunStatus(basePlcData.xDone, 2);
//                keepTime -= 50;
//                scanTime(QTime().addMSecs(keepTime).toString("HH:mm:ss"));

//                return;
//            }
//            updataCurrentPos();
//        }
//    }
//}

//// 假设你要写入的寄存器数量和每次写入的组大小
//int registersPerGroup = 100*12;  // 每组写入 100 个寄存器

////int currentWriteCount = qMin(registersPerGroup, modelDates.count());  // 本次写入的寄存器数量
//int currentWriteCount = qMin(registersPerGroup, 120);  // 本次写入的寄存器数量
//QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, startAddress, currentWriteCount);

//// 设置要写入的寄存器值
//for (int i = 0; i < modelDates.count(); i++) {

//    if(modelDates[i].type=="arc"){
//        auto xpos0 = writeModbusFloatData(modelDates[i].points[0][0]);
//        auto ypos0 = writeModbusFloatData(modelDates[i].points[0][1]);
//        auto rpos0 = writeModbusFloatData(modelDates[i].points[0][2]);
//        auto xpos1 = writeModbusFloatData(modelDates[i].points[1][0]);
//        auto ypos1 = writeModbusFloatData(modelDates[i].points[1][1]);
//        auto rpos1 = writeModbusFloatData(modelDates[i].points[1][2]);

//        writeUnit.setValue(0+(i*12), xpos0.first);
//        writeUnit.setValue(1+(i*12), xpos0.second);
//        writeUnit.setValue(2+(i*12), ypos0.first);
//        writeUnit.setValue(3+(i*12), ypos0.second);
//        writeUnit.setValue(4+(i*12), rpos0.first);
//        writeUnit.setValue(5+(i*12), rpos0.second);

//        writeUnit.setValue(6+(i*12), xpos1.first);
//        writeUnit.setValue(7+(i*12), xpos1.second);
//        writeUnit.setValue(8+(i*12), ypos1.first);
//        writeUnit.setValue(9+(i*12), ypos1.second);
//        writeUnit.setValue(10+(i*12), rpos1.first);
//        writeUnit.setValue(11+(i*12), rpos1.second);

//        qDebug()<<"acr"<<i<<"  " <<i*12<<"  "<<modelDates[i].points[0][0] <<" "<<modelDates[i].points[0][1]<<" "<<modelDates[i].points[0][2]
//                <<modelDates[i].points[1][0]<<" "<<modelDates[i].points[1][1]<<" "<<modelDates[i].points[1][2];
//    }else {

//        auto xpos0 = writeModbusFloatData(modelDates[i].points[0][0]);
//        auto ypos0 = writeModbusFloatData(modelDates[i].points[0][1]);
//        auto rpos0 = writeModbusFloatData(modelDates[i].points[0][2]);

//        writeUnit.setValue(0+(i*12), xpos0.first);
//        writeUnit.setValue(1+(i*12), xpos0.second);
//        writeUnit.setValue(2+(i*12), ypos0.first);
//        writeUnit.setValue(3+(i*12), ypos0.second);
//        writeUnit.setValue(4+(i*12), rpos0.first);
//        writeUnit.setValue(5+(i*12), rpos0.second);

//        writeUnit.setValue(6+(i*12), 0);
//        writeUnit.setValue(7+(i*12), 0);
//        writeUnit.setValue(8+(i*12), 0);
//        writeUnit.setValue(9+(i*12), 0);
//        writeUnit.setValue(10+(i*12), 0);
//        writeUnit.setValue(11+(i*12), 0);

//        qDebug()<<"l"<<i<<"  "<<i*12<<"  "<<modelDates[i].points[0][0] <<" "<<modelDates[i].points[0][1]<<" "<<modelDates[i].points[0][2];

//    }



//}

//// 发送写入请求
//if (auto *reply = modbusClient->sendWriteRequest(writeUnit, serverAddress)) {
//    if (!reply->isFinished()) {
//        // 连接写入完成的信号
//        connect(reply, &QModbusReply::finished, [=]() {
//            if (reply->error() == QModbusDevice::ProtocolError) {
//                qWarning() << "Write error: " << reply->errorString();
//            } else if (reply->error() == QModbusDevice::TimeoutError) {
//                qWarning() << "Request timeout occurred. Retrying...";
//                // 如果请求超时，进行重试
//                if (retryCount < 3) {  // 设置重试次数为3次
//                    progressDialog->setValue(progressDialog->value() + 20);  // 更新进度
//                    QTimer::singleShot(500, this, [=]() {
//                        writeRegisterGroup( startAddress,modelDates, serverAddress);  // 重试
//                        retryCount=retryCount + 1;
//                    });
//                } else {
//                    progressDialog->close();
//                    QMessageBox::warning(nullptr,  // 父窗口，这里传递 nullptr 表示没有父窗口
//                                         "Warning",  // 对话框的标题
//                                         "Max retry attempts reached. "
//                                         "Aborting write."
//                                         "Please rewrite!",  // 显示的文本
//                                         QMessageBox::Ok);  // 确认按钮
//                    qWarning() << "Max retry attempts reached. Aborting write.";
//                }

//            } else if (reply->error() != QModbusDevice::NoError) {

//                qWarning() << "Write finished with error: " << reply->errorString();

//            } else {

//                qDebug() << "Write group from address " << startAddress << " successful!";

//            }

//            reply->deleteLater();
//        });

//    } else {
//        delete reply;
//    }
//} else {
//    qWarning() << "Failed to send write request: " << modbusClient->errorString();
//}




//void scanDetect_frictionWelding::writeNameRegisterGroup(QModbusClient *modbusDevice, int serverAddress,QList<QString> nameList)
//{
//    int address_name=1000;
//    int size_name =nameList.count();
//    qDebug()<<"*****size_name="<<size_name;
//    QModbusDataUnit modbusData(QModbusDataUnit::Coils,  address_name, size_name);
//    for (int i = 0; i < size_name; ++i) {
//        if(nameList.at(i)=="arc"){
//            modbusData.setValue(i, true);
//            qDebug()<<QString::fromLocal8Bit("arc")<<"true";
//        }else{
//            modbusData.setValue(i, false);
//            qDebug()<<QString::fromUtf8("line")<<"false";
//        }
//    }
//    qDebug()<<"modbusData"<<modbusData.values();
//    auto reply_coils = modbusDevice->sendWriteRequest(modbusData, serverAddress);
//    if(reply_coils){
//        if (!reply_coils->isFinished())
//        {
//            connect(reply_coils, &QModbusReply::finished, [=](){
//                if(reply_coils->error() == QModbusDevice::NoError){qDebug()<<"****write oK****";
//                }else {
//                    QMessageBox::warning(nullptr,tr("Write Failed!"),tr("error message：").arg(reply_coils->errorString()).arg(reply_coils->error(), -1, 16), 5000,QMessageBox::Yes,QMessageBox::No);
//                }
//                reply_coils->deleteLater();
//            });
//        }else {
//            reply_coils->deleteLater();
//        }
//    }
//}

//void scanDetect_frictionWelding::writeRegisterGroup(QModbusClient *modbusDevice, int startAddress, int remainingRegisters, QVector<uint16_t> data, int serverAddress)
//{

//    // 假设你要写入的寄存器数量和每次写入的组大小
//    int registersPerGroup = 120;  // 每组写入 100 个寄存器

//    int currentWriteCount = qMin(registersPerGroup, remainingRegisters);  // 本次写入的寄存器数量
//    QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, startAddress, currentWriteCount);

//    // 设置要写入的寄存器值
//    for (int i = 0; i < currentWriteCount; ++i) {
//        writeUnit.setValue(i, data[startAddress + i-3000]);
//        //qDebug()<<"data="<<data<<"count="<<startAddress + i-3000;
//    }
//    //qDebug()<<"writeUnit="<<writeUnit.values();

//    // 发送写入请求
//    if (auto *reply = modbusDevice->sendWriteRequest(writeUnit, serverAddress)) {
//        if (!reply->isFinished()) {
//            // 连接写入完成的信号
//            connect(reply, &QModbusReply::finished, [=]() {
//                if (reply->error() == QModbusDevice::ProtocolError) {
//                    qWarning() << "Write error: " << reply->errorString();
//                } else if (reply->error() == QModbusDevice::TimeoutError) {
//                    qWarning() << "Request timeout occurred. Retrying...";
//                    // 如果请求超时，进行重试
//                    if (retryCount < 3) {  // 设置重试次数为3次
//                        progressDialog->setValue(progressDialog->value() + 20);  // 更新进度
//                        qDebug() << "Retrying write group from address " << startAddress << " retry count: " << (retryCount + 1);
//                        QTimer::singleShot(500, this, [=]() {
//                            writeRegisterGroup(modbusDevice, startAddress, remainingRegisters, data, serverAddress);  // 重试
//                            retryCount=retryCount + 1;
//                        });
//                    } else {
//                        progressDialog->close();
//                        QMessageBox::warning(nullptr,  // 父窗口，这里传递 nullptr 表示没有父窗口
//                                             "Warning",  // 对话框的标题
//                                             "Max retry attempts reached. "
//                                             "Aborting write."
//                                             "Please rewrite!",  // 显示的文本
//                                             QMessageBox::Ok);  // 确认按钮
//                        qWarning() << "Max retry attempts reached. Aborting write.";
//                    }
//                } else if (reply->error() != QModbusDevice::NoError) {
//                    qWarning() << "Write finished with error: " << reply->errorString();
//                } else {
//                    qDebug() << "Write group from address " << startAddress << " successful!";
//                    // 如果还有剩余的寄存器，需要继续写入
//                    if (remainingRegisters - currentWriteCount > 0) {
//                        // 递归调用，写入下一组
//                        progressDialog->setValue(progressDialog->value() + 5);  // 更新进度
//                        writeRegisterGroup(modbusDevice, startAddress + currentWriteCount, remainingRegisters - currentWriteCount, data, serverAddress);
//                    } else {
//                        qDebug() << "All register groups written successfully!";
//                        progressDialog->close();
//                        QMessageBox::information(nullptr,  // 父窗口，这里传递 nullptr 表示没有父窗口
//                                                 "Information",  // 对话框的标题
//                                                 "All register groups written successfully!",  // 显示的文本
//                                                 QMessageBox::Ok);  // 确认按钮
//                    }
//                }
//                reply->deleteLater();
//            });
//        } else {
//            delete reply;
//        }
//    } else {
//        qWarning() << "Failed to send write request: " << modbusDevice->errorString();
//    }

//}
















//void scanDetect_frictionWelding::writeRoutePos(int startAddress, quint16 size, QList<float> dataList_x0,QList<float> dataList_y0, QList<float> dataList_r0,QList<float> dataList_x1, QList<float> dataList_y1,QList<float> dataList_r1,QList<QString> nameList)
//{

//    if (modbusClient->state() != QModbusDevice::ConnectedState)
//        return;

//    int totalRegisters = 6 * size * 2;
//    int serverAddress = 1;

//    // 准备要写入的数据
//    QVector<uint16_t> data(totalRegisters, 0);  // 假设这里初始化了总共1000个寄存器数据

//    // 初始化进度条
//    progressDialog= new QProgressDialog;
//    progressDialog->setLabelText(tr("Writing registers..."));
//    progressDialog->setCancelButton(nullptr);  // 禁用取消按钮
//    progressDialog->setWindowModality(Qt::WindowModal);  // 设置为模态
//    progressDialog->setRange(0, 100); // size 是数据块的数量
//    progressDialog->setValue(10);
//    progressDialog->show();

//    int retryCount = 0;

//    // 填充数据
//    for (int i = 0; i < size * 2 * 6; i += 2 * 6) {
//        // 数据处理逻辑与之前相同
//        float data_x0 = dataList_x0.at(i / (2 * 6));
//        quint32 intValue_x0 = *reinterpret_cast<uint32_t*>(&data_x0);
//        data[i] = intValue_x0 & 0xFFFF;           // 低16位
//        data[i + 1] = (intValue_x0 >> 16) & 0xFFFF; // 高16位

//        float data_y0 = dataList_y0.at(i / (2 * 6));
//        quint32 intValue_y0 = *reinterpret_cast<uint32_t*>(&data_y0);
//        data[i + 2] = intValue_y0 & 0xFFFF;           // 低16位
//        data[i + 3] = (intValue_y0 >> 16) & 0xFFFF; // 高16位

//        float data_r0 = dataList_r0.at(i / (2 * 6));
//        quint32 intValue_r0 = *reinterpret_cast<uint32_t*>(&data_r0);
//        data[i + 4] = intValue_r0 & 0xFFFF;           // 低16位
//        data[i + 5] = (intValue_r0 >> 16) & 0xFFFF; // 高16位

//        float data_x1 = dataList_x1.at(i / (2 * 6));
//        quint32 intValue_x1 = *reinterpret_cast<uint32_t*>(&data_x1);
//        data[i + 6] = intValue_x1 & 0xFFFF;           // 低16位
//        data[i + 7] = (intValue_x1 >> 16) & 0xFFFF; // 高16位

//        float data_y1 = dataList_y1.at(i / (2 * 6));
//        quint32 intValue_y1 = *reinterpret_cast<uint32_t*>(&data_y1);
//        data[i + 8] = intValue_y1 & 0xFFFF;           // 低16位
//        data[i + 9] = (intValue_y1 >> 16) & 0xFFFF; // 高16位

//        float data_r1 = dataList_r1.at(i / (2 * 6));
//        quint32 intValue_r1 = *reinterpret_cast<uint32_t*>(&data_r1);
//        data[i + 10] = intValue_r1 & 0xFFFF;           // 低16位
//        data[i + 11] = (intValue_r1 >> 16) & 0xFFFF; // 高16位
//    }

//    if (size < 120) {
//        int address_name = 1000;
//        int size_name = nameList.count();
//        QModbusDataUnit modbusData(QModbusDataUnit::Coils, address_name, size_name);

//        for (int i = 0; i < size_name; ++i) {
//            modbusData.setValue(i, nameList.at(i) == "arc");
//        }

//        int maxRetryCount = 3;
//        // 递归函数用于重试逻辑
//        std::function<void(int)> sendWriteRequestWithRetry = [=, &sendWriteRequestWithRetry](int currentRetryCount) mutable {
//            auto reply_coils = modbusClient->sendWriteRequest(modbusData, serverAddress);
//            if (reply_coils) {
//                if (!reply_coils->isFinished()) {
//                    connect(reply_coils, &QModbusReply::finished, [=]() mutable {
//                        if (reply_coils->error() == QModbusDevice::NoError) {
//                            qDebug() << "****Write OK****";
//                            // 更新进度条
//                            progressDialog->setValue(progressDialog->value() + 20);  // 更新进度

//                            // 写入成功后，继续写入剩余的寄存器
//                            writeRegisterGroup(modbusClient, startAddress, totalRegisters, data, serverAddress);
//                        } else if (reply_coils->error() == QModbusDevice::TimeoutError && currentRetryCount < maxRetryCount) {
//                            qWarning() << "Request timeout occurred. Retrying... (" << currentRetryCount + 1 << "/" << maxRetryCount << ")";
//                            // 进行重试
//                            QTimer::singleShot(500, this, [=]() mutable {
//                                sendWriteRequestWithRetry(currentRetryCount + 1);  // 递归重试
//                            });
//                        } else {
//                            QMessageBox::warning(nullptr, tr("Write Failed!"), tr("Error message: %1 (Error code: %2)")
//                                                 .arg(reply_coils->errorString())
//                                                 .arg(reply_coils->error(), -1, 16), QMessageBox::Yes);
//                        }
//                        reply_coils->deleteLater();
//                    });
//                } else {
//                    reply_coils->deleteLater();
//                }
//            } else {
//                qWarning() << "Failed to send write request: " << modbusClient->errorString();
//            }
//        };

//        // 发送初次请求
//        sendWriteRequestWithRetry(retryCount);
//    }

//    // 关闭进度条
//    //progressDialog->close();
//}

//void scanDetect_frictionWelding::writeRoutPosName(int address,QList<QString> nameList)
//{
//    //qDebug()<<"*****writeRoutPosName"<<address<<nameList;
//    if(modbusClient->state() != QModbusDevice::ConnectedState)
//        return;

//    int size =nameList.count();
//    //qDebug()<<"*****size"<<size;
//    QModbusDataUnit modbusData(QModbusDataUnit::Coils,  address, size);
//    for (int i = 0; i < size; ++i) {
//        if(nameList.at(i)=="arc"){
//            modbusData.setValue(i, true);
//            qDebug()<<QString::fromLocal8Bit("arc")<<"true";
//        }else{
//            modbusData.setValue(i, false);
//            qDebug()<<QString::fromUtf8("line")<<"false";
//        }
//        //qDebug()<<"modbusData"<<modbusData.values()<<"i="<<i<<"name="<<nameList.at(i);
//    }
//    auto reply = modbusClient->sendWriteRequest(modbusData, 1);
//    if(reply){
//        if (!reply->isFinished())
//        {
//            connect(reply, &QModbusReply::finished, [=](){
//                if(reply->error() == QModbusDevice::NoError){qDebug()<<"****write oK****";
//                }else {
//                    QMessageBox::warning(nullptr,tr("Write Failed!"),tr("error message：").arg(reply->errorString()).arg(reply->error(), -1, 16), 5000,QMessageBox::Yes,QMessageBox::No);
//                }
//                reply->deleteLater();
//            });
//        }else {
//            reply->deleteLater();
//        }
//    }
//}











#if 0
// 发送写入请求
if (auto *reply = modbusDevice->sendWriteRequest(writeUnit, serverAddress)) {
    if (!reply->isFinished()) {
        // 连接写入完成的信号
        connect(reply, &QModbusReply::finished, [=]() {
            if (reply->error() == QModbusDevice::ProtocolError) {
                qWarning() << "Write error: " << reply->errorString();
            } else if (reply->error() != QModbusDevice::NoError) {
                qWarning() << "Write finished with error: " << reply->errorString();
                //connect(reply, &QModbusReply::finished, this, &scanDetect_frictionWelding::handleReply);
            } else {
                qDebug() << "Write group from address " << startAddress << " successful!";
                // 如果还有剩余的寄存器，需要继续写入
                if (remainingRegisters - currentWriteCount > 0) {
                    // 递归调用，写入下一组
                    writeRegisterGroup(modbusDevice, startAddress + currentWriteCount, remainingRegisters - currentWriteCount, data, serverAddress);
                } else {
                    qDebug() << "All register groups written successfully!";
                    QMessageBox::information(nullptr, // 父窗口，这里传递 nullptr 表示没有父窗口
                                             "Information", // 对话框的标题
                                             "All register groups written successfully!", // 显示的文本
                                             QMessageBox::Ok); // 确认按钮

                }
            }
            reply->deleteLater();
        });
    } else {
        delete reply;
    }
} else {
qWarning() << "Failed to send write request: " << modbusDevice->errorString();
}
#endif
//qDebug()<<"=dataList_x0="<<dataList_x0<<dataList_y0<<dataList_r0<<"dataList_x1="<<dataList_x1<<dataList_y1<<dataList_r1;
#if 0
if(modbusClient->state() != QModbusDevice::ConnectedState)
return;

int totalRegisters=6*size*2;
int serverAddress=1;
// 准备要写入的数据
QVector<uint16_t> data(totalRegisters, 0);  // 假设这里初始化了总共1000个寄存器数据

// 初始化进度条
QProgressDialog progressDialog;
progressDialog.setLabelText(tr("Writing registers..."));
progressDialog.setRange(0, size); // size 是数据块的数量
progressDialog.setCancelButton(nullptr);  // 禁用取消按钮，确保写入过程不会被中断
progressDialog.setWindowModality(Qt::WindowModal);  // 设置为模态对话框，阻塞其他操作

// 进度条显示
progressDialog.show();

retryCount=0;
//QModbusDataUnit modbusData(QModbusDataUnit::HoldingRegisters,  address, 6*size*2);
for (int i = 0; i< size*2*6; i+=2*6) {
    qDebug()<<"****i/2*6=****"<<i/(2*6)<<startAddress<<size;
    float data_x0, data_y0, data_r0, data_x1, data_y1,data_r1;
    data_x0 = dataList_x0.at(i/(2*6));
    quint32 intValue_x0 = *reinterpret_cast<uint32_t*>(&data_x0);
    quint16 v2_x0 = (intValue_x0 >> 16) & 0xFFFF;
    quint16 v1_x0 = intValue_x0 & 0xFFFF;
    //modbusData.setValue(i,v1_x0);
    //modbusData.setValue(i+1,v2_x0);
    data.replace(i,v1_x0);
    data.replace(i+1,v2_x0);

    data_y0 = dataList_y0.at(i/(2*6));
    quint32 intValue_y0 = *reinterpret_cast<uint32_t*>(&data_y0);
    quint16 v2_y0 = (intValue_y0 >> 16) & 0xFFFF;
    quint16 v1_y0 = intValue_y0 & 0xFFFF;
    //modbusData.setValue(i+2,v1_y0);
    //modbusData.setValue(i+3,v2_y0);
    data.replace(i+2,v1_y0);
    data.replace(i+3,v2_y0);

    data_r0 = dataList_r0.at(i/(2*6));
    quint32 intValue_r0 = *reinterpret_cast<uint32_t*>(&data_r0);
    quint16 v2_r0 = (intValue_r0 >> 16) & 0xFFFF;
    quint16 v1_r0 = intValue_r0 & 0xFFFF;
    //modbusData.setValue(i+4,v1_r0);
    //modbusData.setValue(i+5,v2_r0);
    data.replace(i+4,v1_r0);
    data.replace(i+5,v2_r0);

    data_x1 = dataList_x1.at(i/(2*6));
    quint32 intValue_x1 = *reinterpret_cast<uint32_t*>(&data_x1);
    quint16 v2_x1 = (intValue_x1 >> 16) & 0xFFFF;
    quint16 v1_x1 = intValue_x1 & 0xFFFF;
    //modbusData.setValue(i+6,v1_x1);
    //modbusData.setValue(i+7,v2_x1);
    data.replace(i+6,v1_x1);
    data.replace(i+7,v2_x1);

    data_y1 = dataList_y1.at(i/(2*6));
    quint32 intValue_y1 = *reinterpret_cast<uint32_t*>(&data_y1);
    quint16 v2_y1 = (intValue_y1 >> 16) & 0xFFFF;
    quint16 v1_y1 = intValue_y1 & 0xFFFF;
    //modbusData.setValue(i+8,v1_y1);
    //modbusData.setValue(i+9,v2_y1);
    data.replace(i+8,v1_y1);
    data.replace(i+9,v2_y1);

    data_r1 = dataList_r1.at(i/(2*6));
    quint32 intValue_r1 = *reinterpret_cast<uint32_t*>(&data_r1);
    quint16 v2_r1 = (intValue_r1 >> 16) & 0xFFFF;
    quint16 v1_r1 = intValue_r1 & 0xFFFF;
    //modbusData.setValue(i+10,v1_r1);
    //modbusData.setValue(i+11,v2_r1);
    data.replace(i+10,v1_r1);
    data.replace(i+11,v2_r1);
}

if(size<120){
    int address_name=1000;
    int size_name =nameList.count();
    qDebug()<<"*****size_name="<<size_name;
    QModbusDataUnit modbusData(QModbusDataUnit::Coils,  address_name, size_name);
    for (int i = 0; i < size_name; ++i) {
        if(nameList.at(i)=="arc"){
            modbusData.setValue(i, true);
            qDebug()<<QString::fromLocal8Bit("arc")<<"true";
        }else{
            modbusData.setValue(i, false);
            qDebug()<<QString::fromUtf8("line")<<"false";
        }
    }
    qDebug()<<"modbusData"<<modbusData.values();

    int maxRetryCount=3;
    // 递归函数用于重试逻辑
    std::function<void(int)> sendWriteRequestWithRetry = [=, &sendWriteRequestWithRetry](int currentRetryCount) mutable {
        auto reply_coils = modbusClient->sendWriteRequest(modbusData, serverAddress);
        if (reply_coils) {
            if (!reply_coils->isFinished()) {
                connect(reply_coils, &QModbusReply::finished, [=]() mutable {
                    if (reply_coils->error() == QModbusDevice::NoError) {
                        qDebug() << "****Write OK****";
                        // 写入成功后，继续写入剩余的寄存器
                        writeRegisterGroup(modbusClient, startAddress, totalRegisters, data, serverAddress);
                    } else if (reply_coils->error() == QModbusDevice::TimeoutError && currentRetryCount < maxRetryCount) {
                        qWarning() << "Request timeout occurred. Retrying... (" << currentRetryCount + 1 << "/" << maxRetryCount << ")";
                        // 进行重试
                        QTimer::singleShot(500, this, [=]() mutable {
                            sendWriteRequestWithRetry(currentRetryCount + 1);  // 递归重试
                        });
                    } else {
                        QMessageBox::warning(nullptr, tr("Write Failed!"), tr("Error message: %1 (Error code: %2)")
                                             .arg(reply_coils->errorString())
                                             .arg(reply_coils->error(), -1, 16), QMessageBox::Yes);
                    }
                    reply_coils->deleteLater();
                });
            } else {
                reply_coils->deleteLater();
            }
        } else {
            qWarning() << "Failed to send write request: " << modbusClient->errorString();
        }
    };

    // 发送初次请求
    sendWriteRequestWithRetry(retryCount);
}
#endif
