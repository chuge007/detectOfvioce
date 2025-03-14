#include "ScanControlHuiChuan.h"
#include "mainwindow.h"

#include <QDebug>
#include <qwidget.h>
#include <QMessageBox>
#include <QTimer>
#include <QProgressDialog>

ScanControlHuiChuan::ScanControlHuiChuan(QObject *parent) :
    ScanControlAbstract(parent)
{
    qRegisterMetaType<QModbusDevice::State>("QModbusDevice::State");
    QMetaObject::invokeMethod(this, "init", Qt::QueuedConnection);


}

ScanControlHuiChuan::~ScanControlHuiChuan()
{
    QMetaObject::invokeMethod(this, "destroy", Qt::QueuedConnection);
}

bool ScanControlHuiChuan::isXCrossed()
{
    bool state = false;
    float xTemp = static_cast<float>(zeroPoint.x())  + xScanLenght;
    if(static_cast<qreal>(xTemp) > limitPoint.x()) {
        state = true;
        qDebug() << "scan X-axis crossed";
    }

    return state;
}

bool ScanControlHuiChuan::isYCrossed()
{
    bool state = false;
    float yTemp = static_cast<float>(zeroPoint.y())  + yScanLenght;
    if(static_cast<qreal>(yTemp) > limitPoint.y()) {
        state = true;
        qDebug() << "scan Y-axis crossed";
    }

    return state;
}

bool ScanControlHuiChuan::isJogCrossed(int &address, float &data)
{
    bool state = true;

    switch (axisInch) {
        case AxisJog::NotAxisJog: state = false; break;
        case AxisJog::XJogAdd: {
            address = R_REGISTER_BASE+X_TARTPOS;
            data = static_cast<float>(currentPos.x()) + jopStep;
            if(static_cast<qreal>(data) >= limitPoint.x()) state = false;
        }break;
        case AxisJog::XJogSub: {
            address = R_REGISTER_BASE+X_TARTPOS;
            data = static_cast<float>(currentPos.x()) - jopStep;
            if(static_cast<qreal>(data) < 0) state = false;
        }break;
        case AxisJog::YJogAdd: {
            address = R_REGISTER_BASE+Y_TARTPOS;
            data = static_cast<float>(currentPos.y()) + jopStep;
            if(static_cast<qreal>(data) >= limitPoint.y()) state = false;
        }break;
        case AxisJog::YJogSub: {
            address = R_REGISTER_BASE+Y_TARTPOS;
            data = static_cast<float>(currentPos.y()) - jopStep;
            if(static_cast<qreal>(data) < 0) state = false;
        }break;
    }

    //没有极限点不做先为限位
    if(!isHaveMachine || !isHaveLimit) state = true;

    return state;
}

void ScanControlHuiChuan::setManualModel(bool states)
{
    manState[0] = states;
}

bool ScanControlHuiChuan::nextScan()
{
    if(!tasks.isEmpty()){
        manState[1] = true;
    }else {
        manState[1] = false;
    }
    return manState[1];
}

void ScanControlHuiChuan::initWidget()
{
//    QDoubleValidator *doubleValidator = new QDoubleValidator(this);
//    doubleValidator->setRange(0.0, 500.000);
//    doubleValidator->setDecimals(3);

    modbusClient = new QModbusTcpClient(this);

    settings = new QSettings("./scan_setting.ini", QSettings::IniFormat);

    timer = new QTimer(this);
    timer->setInterval(50);

}

void ScanControlHuiChuan::connectFun()
{
    connect(modbusClient, &QModbusClient::stateChanged, this, &ScanControlHuiChuan::modbusState);
    connect(timer, &QTimer::timeout, this, &ScanControlHuiChuan::performTasks);

//    connect(this, &ScanControlHuiChuan::machineStart, this, &ScanControlHuiChuan::on_startScanBtn_clicked);
//    connect(this, &ScanControlHuiChuan::machineStop, this, &ScanControlHuiChuan::on_stopScanBtn_clicked);
}

void ScanControlHuiChuan::readSetting()
{
    if(settings == nullptr) return;

    float xPos   = settings->value("Virtual_origin_X", 0).toFloat();
    float yPos   = settings->value("Virtual_origin_Y", 0).toFloat();
    float xLimit = settings->value("Limit_position_X", 0).toFloat();
    float yLimit = settings->value("Limit_position_Y", 0).toFloat();
    xScanLenght = settings->value("X_Lenght", 0).toFloat();
    yScanLenght = settings->value("Y_Lenght", 0).toFloat();
    yScanStep = settings->value  ("Y_Step", 0).toFloat();
    isHaveMachine = settings->value("Have_Machine_origin", false).toBool();
    isHaveLimit = settings->value("Have_Limit_origin", false).toBool();
    bool temp = settings->value("Single_Scan", false).toBool();
    if(xPos < 0 || xPos > xLimit) xPos = 0;
    if(yPos < 0 || yPos > yLimit) yPos = 0;

    if(!temp) {
        scanModel = ScanModel::NormalScan;
    }else {
        scanModel = ScanModel::SingleScan;
    }
    qDebug() << xLimit << yLimit << xScanLenght <<
                yScanLenght <<
                yScanStep;

    zeroPoint.setX(static_cast<qreal>(xPos));
    zeroPoint.setY(static_cast<qreal>(yPos));
    limitPoint.setX(static_cast<qreal>(xLimit));
    limitPoint.setY(static_cast<qreal>(yLimit));


}

void ScanControlHuiChuan::writeSetting()
{
    if(settings == nullptr) return;

    settings->setValue("Virtual_origin_X", zeroPoint.x());
    settings->setValue("Virtual_origin_Y", zeroPoint.y());
    settings->setValue("Limit_position_X", limitPoint.x());
    settings->setValue("Limit_position_Y", limitPoint.y());

    settings->setValue("X_Lenght", static_cast<qreal>(xScanLenght));
    settings->setValue("Y_Lenght", static_cast<qreal>(yScanLenght));
    settings->setValue("Y_Step", static_cast<qreal>(yScanStep));
    settings->setValue("Single_Scan", scanModel == ScanModel::NormalScan ? false : true);

    settings->sync();

}

void ScanControlHuiChuan::initStates()
{
    isInit = true;
    isStartScan = false;
    isPerform = false;
    isStopScan = false;
    isKeepScan = false;
    isAxisStop = false;
    updateCurPos = false;
    isEndScan = false;
    isJogDone = false;
    if(!tasks.isEmpty())tasks.clear();
}

float ScanControlHuiChuan::readModbusFloatData(int v1, int v2)
{
    uint32_t intValue = (static_cast<uint32_t>(v1) << 16) | static_cast<uint32_t>(v2);
    return *reinterpret_cast<float*>(&intValue);
}

QPair<quint16, quint16> ScanControlHuiChuan::writeModbusFloatData(float value) {
    quint32 intValue = *reinterpret_cast<uint32_t*>(&value);
    quint16 v2 = (intValue >> 16) & 0xFFFF;
    quint16 v1 = intValue & 0xFFFF;

    return QPair<quint16, quint16>(v1, v2);
}

void ScanControlHuiChuan::writeHoldingRegistersData(int address, quint16 size, float data)
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
                        isPerform = true;
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

void ScanControlHuiChuan::readAxisRunStatus(int address, quint16 size)
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;

    QModbusDataUnit data(QModbusDataUnit::Coils, address, size);

    QModbusReply *reply = modbusClient->sendReadRequest(data, 1);
    if(reply){
        if (!reply->isFinished())
        {
            connect(reply, &QModbusReply::finished, [=](){
                if(reply->error() == QModbusDevice::NoError){
                    if(tasks.isEmpty()){
                        isPerform = false;
                        reply->deleteLater();
                        return ;
                    }

                    //正在执行自动扫查
                    if(isStartScan){
                        int temp = false;
                        if(tasks.head().first == "x"){
                            temp = reply->result().value(0);
                            if(temp) emit scanRowEnd(AxisState::XMoveDone);
                        }else if (tasks.head().first == "y") {
                            temp = reply->result().value(1);
                            if(temp) emit scanRowEnd(AxisState::YMoveDone);
                        }

                        if(temp){
                            isPerform = false;
                            if(!tasks.isEmpty()) tasks.pop_front();
                        }
                        if(tasks.count() != 0){
                            updataCurrentPos();
                        }else {
                            keepTime = 0;
                            emit scanTime("");
                            updateCurPos = true;
                        }
                    }
                }else {
//                    if(!isEndScan)  //如果是结束扫查，写失败就不处理
//                    readAxisRunStatus(address, size);
                }
                reply->deleteLater();
            });
        }else {
            delete reply;
        }
    }
}

void ScanControlHuiChuan::writeAxisStopStatus(int address)
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;

    QModbusDataUnit data(QModbusDataUnit::Coils, address, 2);
    data.setValue(0, 1);
    data.setValue(1, 1);
    QModbusReply *reply = modbusClient->sendWriteRequest(data, 1);
    if(reply){
        if (!reply->isFinished())
        {
            connect(reply, &QModbusReply::finished, [=](){
                if(reply->error() == QModbusDevice::NoError){
                    if(isEndScan){
                        return ;    //结束扫查，不需要置位
                    }

                    if(isRunTarget){
                        isRunTarget = false;
                        return;
                    }

                    if(address == X_STOP){
                        isStopScan = false;
                        isAxisStop = true;
                        updateCurPos = true;
                    }else if (address == X_START) {
                        isKeepScan = false;
                        isStartScan = true;
                        isAxisStop = false;
                    }
                }else {
                    writeAxisStopStatus(address);
                }
                reply->deleteLater();
            });
        }else {
            reply->deleteLater();
        }
    }
}

void ScanControlHuiChuan::writeEndScanStatus()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;

    QModbusDataUnit modbusData(QModbusDataUnit::Coils,  END_SCAN, 1);

    modbusData.setValue(0, 1);

    auto reply = modbusClient->sendWriteRequest(modbusData, 1);
    if(reply){
        if (!reply->isFinished())
        {
            connect(reply, &QModbusReply::finished, [=](){
                if(reply->error() == QModbusDevice::NoError){
                    updateCurPos = true;
                    timer->start();
                }else {
                    writeEndScanStatus();
                }
                reply->deleteLater();
            });
        }else {
            reply->deleteLater();
        }
    }
}

void ScanControlHuiChuan::writeBackZero()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;

    QModbusDataUnit modbusData(QModbusDataUnit::HoldingRegisters,  X_VIRTUAL_ORIGIN, 4);

    auto xpos = writeModbusFloatData(static_cast<float>(zeroPoint.x()));
    auto ypos = writeModbusFloatData(static_cast<float>(zeroPoint.y()));
    modbusData.setValue(0, xpos.first);
    modbusData.setValue(1, xpos.second);
    modbusData.setValue(2, ypos.first);
    modbusData.setValue(3, ypos.second);

    auto reply = modbusClient->sendWriteRequest(modbusData, 1);
    if(reply){
        if (!reply->isFinished())
        {
            connect(reply, &QModbusReply::finished, [=](){
                if(reply->error() == QModbusDevice::NoError){
        //            writeAxisStopStatus(X_START);
                    writeEndScanStatus();

                }else {
                    writeBackZero();
                }
                reply->deleteLater();
            });
        }else {
            reply->deleteLater();
        }
    }
}

void ScanControlHuiChuan::readAxisEndState()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;

    QModbusDataUnit data(QModbusDataUnit::Coils, X_AXIS_DONE, 2);

    QModbusReply *reply = modbusClient->sendReadRequest(data, 1);
    if(reply){
        if (!reply->isFinished())
        {
            connect(reply, &QModbusReply::finished, [=](){

                if(reply->error() == QModbusDevice::NoError){
                    if(isEndScan){

                        if(reply->result().value(0) == 1 &&
                           reply->result().value(1) == 1){
                            isEndScan = false;
                        }
                    }

                    //正在执行目标点位
                    if(isRunTarget){
                        int temp1 = reply->result().value(0);
                        int temp2 = reply->result().value(1);
                        if(temp1 && temp2){
                            isRunTarget = false;
                        }
                    }
                }else {
                }
                reply->deleteLater();
            });
        }else {
            reply->deleteLater();
        }
    }
}

void ScanControlHuiChuan::writeAxisVelocity(int address, quint16 size, float data)
{
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
}

void ScanControlHuiChuan::readAxisVelocity(int address, quint16 size)
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
                    isInit = false;
                    updateCurPos = true;
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

void ScanControlHuiChuan::readAxisJogStatus(int address)
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

void ScanControlHuiChuan::readAxisErrorID()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;

    QModbusDataUnit modbusData(QModbusDataUnit::HoldingRegisters,  AXIS_ERROR_ID, 4);

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

void ScanControlHuiChuan::writeAxisReset()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;

    QModbusDataUnit modbusData(QModbusDataUnit::Coils,  AXIS_RESET, 1);
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
}

void ScanControlHuiChuan::writeAxisLimitPosition()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;

    QModbusDataUnit modbusData(QModbusDataUnit::Coils,  LIMIT_POINT, 1);
    modbusData.setValue(0, 1);
    auto reply = modbusClient->sendWriteRequest(modbusData, 1);
    if(reply){
        if (!reply->isFinished())
        {
            connect(reply, &QModbusReply::finished, [=](){
                if(reply->error() == QModbusDevice::NoError){
                    limitPoint.setX(currentPos.x());
                    limitPoint.setY(currentPos.y());

                    settings->setValue("Limit_position_X", limitPoint.x());
                    settings->setValue("Limit_position_Y", limitPoint.y());
                    settings->setValue("Have_Limit_origin", true);
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

void ScanControlHuiChuan::writeAxisMachineOrigin()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;

    QModbusDataUnit modbusData(QModbusDataUnit::Coils,  MACHINE_ORIGIN, 1);
    modbusData.setValue(0, 1);
    auto reply = modbusClient->sendWriteRequest(modbusData, 1);
    if(reply){
        if (!reply->isFinished())
        {
            connect(reply, &QModbusReply::finished, [=](){
                if(reply->error() == QModbusDevice::NoError){
                    zeroPoint.setX(0);
                    zeroPoint.setY(0);

                    settings->setValue("Virtual_origin_X", limitPoint.x());
                    settings->setValue("Virtual_origin_Y", limitPoint.y());
                    settings->setValue("Have_Machine_origin", true);
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

void ScanControlHuiChuan::writeAxisJog(int address, bool data)
{
    //qDebug()<<"writeAxisJog******address:"<<address<<"data:"<<data;
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;

    QModbusDataUnit modbusData(QModbusDataUnit::Coils,  address, 1);
    modbusData.setValue(0, data);
    auto reply = modbusClient->sendWriteRequest(modbusData, 1);
    if(reply)
    {
        if (!reply->isFinished())
        {
            connect(reply, &QModbusReply::finished, [=](){
                if(reply->error() == QModbusDevice::NoError){
                    axisJog =  AxisJog::NotAxisJog;
                    updateCurPos = true;
                }else {
//                  qDebug() << __FUNCTION__ << "SHI BAI";
                    if(!data){
//                  如果写OFF, 必然要写成功
//                  qDebug() << __FUNCTION__ << data;
                    writeAxisJog(address, data);
                    }else {
                        updateCurPos = true;
                    }
                }
                reply->deleteLater();
            });
        }else {
            reply->deleteLater();
        }
    }
}


void ScanControlHuiChuan::initTasks()
{
    if(isInit){
        readAxisVelocity(R_REGISTER_BASE+X_VELOCITY, 10);
    }
}

void ScanControlHuiChuan::on_connectBtn_clicked()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState ){
        modbusClient->setConnectionParameter(QModbusDevice::NetworkAddressParameter, PlcIP);
        modbusClient->setConnectionParameter(QModbusDevice::NetworkPortParameter, PlcPort);
        modbusClient->setNumberOfRetries(3);
        modbusClient->setTimeout(1000);
        qDebug()<<"PlcIP="<<PlcIP<<"PlcPort="<<PlcPort;
        if(modbusClient->connectDevice()){
        }else {
        }
    }else {
        modbusClient->disconnectDevice();
    }
}

void ScanControlHuiChuan::on_startScanBtn_clicked()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;

//    qDebug() << zeroPoint << currentPos;
//    if() return;
    if(isEndScan || isRunTarget) return;

    if(isXCrossed() || isYCrossed()) return;

    if(tasks.count() == 0){
        updateCurPos = false;
        creataTasksTable();
    }else {
        if(!isStartScan){
            updateCurPos = false;
            isKeepScan = true;
        }
    }
    isAxisStop = false;
    isRunTarget = false;
}

void ScanControlHuiChuan::on_stopScanBtn_clicked()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;

    if(isEndScan) return;

    if(tasks.count() == 0) {
        if(!isRunTarget){
//            updateCurPos = true;
//            isStopScan = false;
            return;
        }
    }

    if(!isAxisStop){
        isStopScan = true;
        isStartScan = false;
        updateCurPos = false;
    }
}

void ScanControlHuiChuan::on_endScanBtn_clicked()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;

    if(isEndScan) return;

    isStopScan = false;
    isPerform = false;
    isStartScan = false;
    isKeepScan = false;
    isAxisStop = false;
    updateCurPos = false;
    isRunTarget = false;
    if(!tasks.isEmpty())tasks.clear();
    isEndScan = true;
    if(timer->isActive())
        timer->stop();
    perfromEndScanTasks();
}

void ScanControlHuiChuan::on_setOriginBtn_clicked()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;

    if(isEndScan || isAxisStop) return;

    if(!isPerform){
        zeroPoint.setX(currentPos.x());
        zeroPoint.setY(currentPos.y());
        settings->setValue("Virtual_origin_X", zeroPoint.x());
        settings->setValue("Virtual_origin_Y", zeroPoint.y());
    }
}

void ScanControlHuiChuan::on_x_velocity_editingFinished(float val)
{
    setXAxisVelocity(val);
}

void ScanControlHuiChuan::on_y_velocity_editingFinished(float val)
{
    setYAxisVelocity(val);
}

void ScanControlHuiChuan::on_jog_velocity_editingFinished(float val)
{
    setJogVelocity(val);
}

void ScanControlHuiChuan::on_jogStep_1_clicked()
{
    setAxisJogStep(1);
}

void ScanControlHuiChuan::on_jogStep_5_clicked()
{
    setAxisJogStep(5);
}

void ScanControlHuiChuan::on_jogStep_10_clicked()
{
    setAxisJogStep(10);
}

void ScanControlHuiChuan::on_xAddBtn_clicked()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;

    if((tasks.count() != 0)  || isEndScan || isAxisStop || isJogDone || isRunTarget) return;
    updateCurPos = false;
    axisInch = AxisJog::XJogAdd;

}

void ScanControlHuiChuan::on_xSubBtn_clicked()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;

    if((tasks.count() != 0)  || isEndScan || isAxisStop || isJogDone || isRunTarget) return;
    updateCurPos = false;
    axisInch = AxisJog::XJogSub;

}

void ScanControlHuiChuan::on_yAddBtn_clicked()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;

    if((tasks.count() != 0) || isEndScan || isAxisStop || isJogDone || isRunTarget) return;
    updateCurPos = false;
    axisInch = AxisJog::YJogAdd;

}

void ScanControlHuiChuan::on_ySubBtn_clicked()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;

    if((tasks.count() != 0)  || isEndScan || isAxisStop || isJogDone || isRunTarget) return;
    updateCurPos = false;
    axisInch = AxisJog::YJogSub;

}

void ScanControlHuiChuan::on_xAddBtn_pressed()
{

    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;
    if((tasks.count() != 0)  || isEndScan || isAxisStop || isJogDone || isRunTarget) return;
    updateCurPos = false;
    axisJog = AxisJog::XJogAddPressed;
    qDebug()<<"****on_xAddBtn_pressed****";
}

void ScanControlHuiChuan::on_xAddBtn_released()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;
    if((tasks.count() != 0)  || isEndScan || isAxisStop || isJogDone || isRunTarget) return;
    updateCurPos = false;
    axisJog = AxisJog::XJogAddReleased;

}

void ScanControlHuiChuan::on_xSubBtn_pressed()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;
    if((tasks.count() != 0)  || isEndScan || isAxisStop || isJogDone || isRunTarget) return;
    updateCurPos = false;
    axisJog = AxisJog::XJogSubPressed;
}

void ScanControlHuiChuan::on_xSubBtn_released()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;
    if((tasks.count() != 0)  || isEndScan || isAxisStop || isJogDone || isRunTarget) return;
    updateCurPos = false;
    axisJog = AxisJog::XJogSubReleased;
}

void ScanControlHuiChuan::on_yAddBtn_pressed()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;
    if((tasks.count() != 0)  || isEndScan || isAxisStop || isJogDone || isRunTarget) return;
    updateCurPos = false;
    axisJog = AxisJog::YJogAddPressed;
}

void ScanControlHuiChuan::on_yAddBtn_released()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;
    if((tasks.count() != 0)  || isEndScan || isAxisStop || isJogDone || isRunTarget) return;
    updateCurPos = false;
    axisJog = AxisJog::YJogAddReleased;
}

void ScanControlHuiChuan::on_ySubBtn_pressed()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;
    if((tasks.count() != 0)  || isEndScan || isAxisStop || isJogDone || isRunTarget) return;
    updateCurPos = false;
    axisJog = AxisJog::YJogSubPressed;
}

void ScanControlHuiChuan::on_ySubBtn_released()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;
    if((tasks.count() != 0)  || isEndScan || isAxisStop || isJogDone || isRunTarget) return;
    updateCurPos = false;
    axisJog = AxisJog::YJogSubReleased;
}

void ScanControlHuiChuan::on_zAddBtn_pressed()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;
    if((tasks.count() != 0)  || isEndScan || isAxisStop || isJogDone || isRunTarget) return;
    updateCurPos = false;
    axisJog = AxisJog::ZJogAddPressed;
}

void ScanControlHuiChuan::on_zAddBtn_released()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;
    if((tasks.count() != 0)  || isEndScan || isAxisStop || isJogDone || isRunTarget) return;
    updateCurPos = false;
    axisJog = AxisJog::ZJogAddReleased;
}

void ScanControlHuiChuan::on_zSubBtn_pressed()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;
    if((tasks.count() != 0)  || isEndScan || isAxisStop || isJogDone || isRunTarget) return;
    updateCurPos = false;
    axisJog = AxisJog::ZJogSubPressed;
}

void ScanControlHuiChuan::on_zSubBtn_released()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;
    if((tasks.count() != 0)  || isEndScan || isAxisStop || isJogDone || isRunTarget) return;
    updateCurPos = false;
    axisJog = AxisJog::ZJogSubReleased;
}

void ScanControlHuiChuan::on_rAddBtn_pressed()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;
    if((tasks.count() != 0)  || isEndScan || isAxisStop || isJogDone || isRunTarget) return;
    updateCurPos = false;
    axisJog = AxisJog::RJogAddPressed;
}

void ScanControlHuiChuan::on_rAddBtn_released()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;
    if((tasks.count() != 0)  || isEndScan || isAxisStop || isJogDone || isRunTarget) return;
    updateCurPos = false;
    axisJog = AxisJog::RJogAddReleased;
}

void ScanControlHuiChuan::on_rSubBtn_pressed()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;
    if((tasks.count() != 0)  || isEndScan || isAxisStop || isJogDone || isRunTarget) return;
    updateCurPos = false;
    axisJog = AxisJog::RJogSubPressed;
}

void ScanControlHuiChuan::on_rSubBtn_released()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;
    if((tasks.count() != 0)  || isEndScan || isAxisStop || isJogDone || isRunTarget) return;
    updateCurPos = false;
    axisJog = AxisJog::RJogSubReleased;
}

void ScanControlHuiChuan::on_alarmResetBtn_clicked()
{
    writeAxisReset();
}

void ScanControlHuiChuan::on_setLimitBtn_clicked()
{
    writeAxisLimitPosition();
}

void ScanControlHuiChuan::on_setMachineBtn_clicked()
{
    writeAxisMachineOrigin();
}

void ScanControlHuiChuan::on_singleScan_toggled(bool checked)
{
    if(checked){
        scanModel = ScanModel::SingleScan;
    }else {
        scanModel = ScanModel::NormalScan;
    }
}

void ScanControlHuiChuan::runTargetPosition(double x, double y ,double z, double r)
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;

    if((tasks.count() != 0)  || isEndScan || isAxisStop || isJogDone) return;

    if(!isRunTarget){
        updateCurPos = false;

    }

    QModbusDataUnit modbusData(QModbusDataUnit::HoldingRegisters, R_REGISTER_BASE + X_TARTPOS, 8);

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
    if(reply){
        if (!reply->isFinished())
        {
            connect(reply, &QModbusReply::finished, [=](){
                if(reply->error() == QModbusDevice::NoError){
                    updateCurPos = true;
                    isRunTarget = true;
                }else{
                    runTargetPosition(x, y,z,r);
                }
                reply->deleteLater();
            });
        }else {
            reply->deleteLater();
        }
    }
}

void ScanControlHuiChuan::init()
{
    initWidget();
    connectFun();
    readSetting();
}

void ScanControlHuiChuan::destroy()
{
    if (settings) {
        writeSetting();
        delete settings;
        settings = nullptr;
    }
    if (modbusClient) {
         modbusClient->disconnectDevice();
         delete modbusClient;
         modbusClient= nullptr;
    }
    if (timer) {
        timer->stop();
        delete timer;
        timer = nullptr;
    }
}

void ScanControlHuiChuan::setXAxisVelocity(float vel)
{
    xVelocity = vel;
    writeAxisVelocity(R_REGISTER_BASE+X_VELOCITY, 2, xVelocity);
}

void ScanControlHuiChuan::setYAxisVelocity(float vel)
{
    yVelocity = vel;
    writeAxisVelocity(R_REGISTER_BASE+Y_VELOCITY, 2, yVelocity);
}

void ScanControlHuiChuan::setJogVelocity(float vel)
{
    jogVelocity = vel;
    writeAxisVelocity(R_REGISTER_BASE+JOG_VELOCITY, 2, jogVelocity);
}

void ScanControlHuiChuan::setAxisJogStep(int step)
{
    jopStep = step;
    qDebug() << jopStep;
}

bool ScanControlHuiChuan::modbusState()
{
    if(modbusClient->state() == QModbusDevice::ConnectedState){
        timer->start();
        qDebug() << "PLC Connection Successful!";
        return true;
    }else if (modbusClient->state() == QModbusDevice::UnconnectedState) {
        timer->stop();
        initStates();
        qDebug() << "PLC Connection Failure!";
        return false;
    }
    emit modbusStateChange(modbusClient->state());
    //    emit scanRackTcpStateChangedSignal(modbusClient->state());
}



void ScanControlHuiChuan::performTasks()
{
    //qDebug()<<"****performTasks*****";
//    perfromEndScanTasks();
    initTasks();
    perfromJogTasks();
    perfromStopScanTasks();
    perfromStartScanTasks();
    if(updateCurPos/*tasks.count() == 0 || isAxisStop (!isStartScan && !isPerform)*/){
        updataCurrentPos();
    }
//    if(isRunTarget){
//        readAxisRunStatus(X_AXIS_DONE, 2);
//    }
}

void ScanControlHuiChuan::creataTasksTable()
{
    int stepNum = 0;
    if(yScanLenght <= yScanStep || qFuzzyIsNull(yScanStep)){
        stepNum = 1;
    }else {
        float divisor = yScanLenght / yScanStep;
        stepNum = static_cast<int>(divisor);
        float  remainder = divisor - stepNum;

        if(remainder > 0){
            stepNum++;
        }
    }
    qDebug() << "Y-axis Scan Number " << stepNum;

    float xPos = static_cast<float>(zeroPoint.x());
    float yPos = static_cast<float>(zeroPoint.y());
    float xTemp = xPos + xScanLenght;
    tasks.clear();
    if(scanModel == ScanModel::NormalScan){
         emit scanRowNumChange(stepNum);
//        tasks.push_back(QPair<QString, float>("x", static_cast<float>(zeroPoint.x())));
//        tasks.push_back(QPair<QString, float>("y", static_cast<float>(zeroPoint.y())));
        if(stepNum > 1){
            bool b = true;
            for (int i=0; i<=stepNum-1; i++) {
                tasks.push_back(QPair<QString, float>("x", xTemp));
                tasks.push_back(QPair<QString, float>("y", yPos+(yScanStep*(i+1))));
                xTemp = b ? xPos : xPos + xScanLenght;
                b = !b;
            }
            tasks.pop_back();
        }else {
            tasks.push_back(QPair<QString, float>("x", xTemp));
        }
    }else if (scanModel == ScanModel::SingleScan) {
        emit scanRowNumChange(stepNum*2);
//        tasks.push_back(QPair<QString, float>("x", static_cast<float>(zeroPoint.x())));
//        tasks.push_back(QPair<QString, float>("y", static_cast<float>(zeroPoint.y())));

        if(stepNum > 1){
            for (int i=0; i<=stepNum-1; i++) {
                tasks.push_back(QPair<QString, float>("x", xTemp));
                tasks.push_back(QPair<QString, float>("x", static_cast<float>(zeroPoint.x())));
                tasks.push_back(QPair<QString, float>("y", yPos+(yScanStep*(i+1))));
            }
            tasks.pop_back();
        }else {
            tasks.push_back(QPair<QString, float>("x", xTemp));
            tasks.push_back(QPair<QString, float>("x", static_cast<float>(zeroPoint.x())));
        }
    }

    if(!tasks.isEmpty()){
        keepTime = 0;
        for (int i=0; i< tasks.count(); i++) {
            if(tasks[i].first == "x"){
                keepTime += xScanLenght / xVelocity;
            }else if(tasks[i].first == "y"){
                keepTime += yScanStep / yVelocity;
            }
        }
        keepTime *= 1000;
    }
//    qDebug() << "tasks count" << tasks.count();
//    for (int i=0; i< tasks.count(); i++) {
//        qDebug() << tasks[i];
//    }
    isStartScan = true;
}

void ScanControlHuiChuan::perfromStartScanTasks()
{
    if(tasks.count() == 0) {
//        if(!isInit || (axisInch != AxisJog::NotAxisJog)) updateCurPos = true;
        isStartScan = false;
        return;
    }

    if(isKeepScan){
        writeAxisStopStatus(X_START);
    }

    //执行任务列表
    if(isStartScan){
        if(!tasks.isEmpty()){
            if(tasks.head().first == "x" && !isPerform && (manState[0] ? manState[1] : true)){
                int address = R_REGISTER_BASE + X_TARTPOS;
                writeHoldingRegistersData(address, 2, tasks.head().second);
                return;
            }
            else if(tasks.head().first == "y" && !isPerform /*&& (manState[0] ? manState[1] : true)*/){
                int address = R_REGISTER_BASE + Y_TARTPOS;
                writeHoldingRegistersData(address, 2, tasks.head().second);
                return;
            }

            //读轴的动作状态
            if(isPerform){
                readAxisRunStatus(X_AXIS_DONE, 2);
                keepTime -= 50;
                scanTime(QTime().addMSecs(keepTime).toString("HH:mm:ss"));

                return;
            }
            updataCurrentPos();
        }
    }
}

void ScanControlHuiChuan::updataCurrentPos()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;

    //QModbusDataUnit data(QModbusDataUnit::HoldingRegisters, X_CUR_POS, 4);
    QModbusDataUnit data(QModbusDataUnit::HoldingRegisters, R_CUR_POS, 8);

    QModbusReply *reply = modbusClient->sendReadRequest(data, 1);
    if(reply){
        if (!reply->isFinished())
        {
            connect(reply, &QModbusReply::finished, [=](){
                if(reply->error() == QModbusDevice::NoError){
                    curR=readModbusFloatData(reply->result().value(1), reply->result().value(0));
                    curZ=readModbusFloatData(reply->result().value(3), reply->result().value(2));
                    float xPos = readModbusFloatData(reply->result().value(5), reply->result().value(4));
                    float yPos = readModbusFloatData(reply->result().value(7), reply->result().value(6));

                    currentPos.setX(static_cast<qreal>(xPos));
                    currentPos.setY(static_cast<qreal>(yPos));

                    emit positionChange(currentPos,curR,curZ);

                    if(isEndScan || isRunTarget){//如果在执行结束扫查任务, 判断轴是否回到虚拟原点
                        readAxisEndState();
                        return ;
                    }
                    readAxisErrorID();
                }
                reply->deleteLater();
            });
        }else {
                reply->deleteLater();
        }
    }
}

void ScanControlHuiChuan::perfromStopScanTasks()
{
    if(isStopScan){
        writeAxisStopStatus(X_STOP);
    }
}

void ScanControlHuiChuan::perfromEndScanTasks()
{
    if(isEndScan){
        writeBackZero();
    }
}

void ScanControlHuiChuan::perfromJogTasks()
{
    //qDebug()<<"****perfromJogTasks******";
    if(axisInch != AxisJog::NotAxisJog && axisJog == AxisJog::NotAxisJog){
        if(!isJogDone){
            int address = 0;
            float data = 0;
            bool state = isJogCrossed(address, data);

            if(state){
                writeHoldingRegistersData(address, 2, data);
            }else {
                axisInch = AxisJog::NotAxisJog;
            }
        }else {
            if(axisInch == XJogAdd || axisInch == XJogSub){
                readAxisJogStatus(X_AXIS_DONE);
            }else if (axisInch == YJogAdd || axisInch == YJogSub) {
                readAxisJogStatus(Y_AXIS_DONE);
            }
        }
    }

    if(axisJog != AxisJog::NotAxisJog && axisInch == AxisJog::NotAxisJog){
        switch (axisJog) {
            case XJogAddPressed:{
                writeAxisJog(X_ADD, true);
                        //qDebug()<<"XJogAddPressed******";
            }break;
            case XJogAddReleased:{
                writeAxisJog(X_ADD, false);
            }break;
            case XJogSubPressed:{
                writeAxisJog(X_SUB, true);
            }break;
            case XJogSubReleased:{
                writeAxisJog(X_SUB, false);
            }break;
            case YJogAddPressed:{
                writeAxisJog(Y_ADD, true);
            }break;
            case YJogAddReleased:{
                writeAxisJog(Y_ADD, false);
            }break;
            case YJogSubPressed:{
                writeAxisJog(Y_SUB, true);
            }break;
            case YJogSubReleased:{
                writeAxisJog(Y_SUB, false);
            }break;
            case ZJogAddPressed:{
                writeAxisJog(Z_ADD, true);
            }break;
            case ZJogAddReleased:{
                writeAxisJog(Z_ADD, false);
            }break;
            case ZJogSubPressed:{
                writeAxisJog(Z_SUB, true);
            }break;
            case ZJogSubReleased:{
                writeAxisJog(Z_SUB, false);
            }break;
            case RJogAddPressed:{
            writeAxisJog(R_ADD, true);
            }break;
            case RJogAddReleased:{
                writeAxisJog(R_ADD, false);
            }break;
            case RJogSubPressed:{
                writeAxisJog(R_SUB, true);
            }break;
            case RJogSubReleased:{
                writeAxisJog(R_SUB, false);
            }break;
        }
    }
}

void ScanControlHuiChuan::writeRoutePos(int startAddress, quint16 size, QList<float> dataList_x0,QList<float> dataList_y0, QList<float> dataList_r0,QList<float> dataList_x1, QList<float> dataList_y1,QList<float> dataList_r1,QList<QString> nameList)
{
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
    if (modbusClient->state() != QModbusDevice::ConnectedState)
            return;

        int totalRegisters = 6 * size * 2;
        int serverAddress = 1;

        // 准备要写入的数据
        QVector<uint16_t> data(totalRegisters, 0);  // 假设这里初始化了总共1000个寄存器数据

        // 初始化进度条
        progressDialog= new QProgressDialog;
        progressDialog->setLabelText(tr("Writing registers..."));
        progressDialog->setCancelButton(nullptr);  // 禁用取消按钮
        progressDialog->setWindowModality(Qt::WindowModal);  // 设置为模态
        progressDialog->setRange(0, 100); // size 是数据块的数量
        progressDialog->setValue(10);
        progressDialog->show();

        int retryCount = 0;

        // 填充数据
        for (int i = 0; i < size * 2 * 6; i += 2 * 6) {
            // 数据处理逻辑与之前相同
            float data_x0 = dataList_x0.at(i / (2 * 6));
            quint32 intValue_x0 = *reinterpret_cast<uint32_t*>(&data_x0);
            data[i] = intValue_x0 & 0xFFFF;           // 低16位
            data[i + 1] = (intValue_x0 >> 16) & 0xFFFF; // 高16位

            float data_y0 = dataList_y0.at(i / (2 * 6));
            quint32 intValue_y0 = *reinterpret_cast<uint32_t*>(&data_y0);
            data[i + 2] = intValue_y0 & 0xFFFF;           // 低16位
            data[i + 3] = (intValue_y0 >> 16) & 0xFFFF; // 高16位

            float data_r0 = dataList_r0.at(i / (2 * 6));
            quint32 intValue_r0 = *reinterpret_cast<uint32_t*>(&data_r0);
            data[i + 4] = intValue_r0 & 0xFFFF;           // 低16位
            data[i + 5] = (intValue_r0 >> 16) & 0xFFFF; // 高16位

            float data_x1 = dataList_x1.at(i / (2 * 6));
            quint32 intValue_x1 = *reinterpret_cast<uint32_t*>(&data_x1);
            data[i + 6] = intValue_x1 & 0xFFFF;           // 低16位
            data[i + 7] = (intValue_x1 >> 16) & 0xFFFF; // 高16位

            float data_y1 = dataList_y1.at(i / (2 * 6));
            quint32 intValue_y1 = *reinterpret_cast<uint32_t*>(&data_y1);
            data[i + 8] = intValue_y1 & 0xFFFF;           // 低16位
            data[i + 9] = (intValue_y1 >> 16) & 0xFFFF; // 高16位

            float data_r1 = dataList_r1.at(i / (2 * 6));
            quint32 intValue_r1 = *reinterpret_cast<uint32_t*>(&data_r1);
            data[i + 10] = intValue_r1 & 0xFFFF;           // 低16位
            data[i + 11] = (intValue_r1 >> 16) & 0xFFFF; // 高16位
        }

        if (size < 120) {
            int address_name = 1000;
            int size_name = nameList.count();
            QModbusDataUnit modbusData(QModbusDataUnit::Coils, address_name, size_name);

            for (int i = 0; i < size_name; ++i) {
                modbusData.setValue(i, nameList.at(i) == "arc");
            }

            int maxRetryCount = 3;
            // 递归函数用于重试逻辑
            std::function<void(int)> sendWriteRequestWithRetry = [=, &sendWriteRequestWithRetry](int currentRetryCount) mutable {
                auto reply_coils = modbusClient->sendWriteRequest(modbusData, serverAddress);
                if (reply_coils) {
                    if (!reply_coils->isFinished()) {
                        connect(reply_coils, &QModbusReply::finished, [=]() mutable {
                            if (reply_coils->error() == QModbusDevice::NoError) {
                                qDebug() << "****Write OK****";
                                // 更新进度条
                                progressDialog->setValue(progressDialog->value() + 20);  // 更新进度

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

        // 关闭进度条
        //progressDialog->close();
}

void ScanControlHuiChuan::writeRoutPosName(int address,QList<QString> nameList)
{
    //qDebug()<<"*****writeRoutPosName"<<address<<nameList;
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;

    int size =nameList.count();
        //qDebug()<<"*****size"<<size;
    QModbusDataUnit modbusData(QModbusDataUnit::Coils,  address, size);
    for (int i = 0; i < size; ++i) {
        if(nameList.at(i)=="arc"){
             modbusData.setValue(i, true);
             qDebug()<<QString::fromLocal8Bit("arc")<<"true";
        }else{
             modbusData.setValue(i, false);
             qDebug()<<QString::fromUtf8("line")<<"false";
        }
    //qDebug()<<"modbusData"<<modbusData.values()<<"i="<<i<<"name="<<nameList.at(i);
    }
    auto reply = modbusClient->sendWriteRequest(modbusData, 1);
    if(reply){
        if (!reply->isFinished())
        {
            connect(reply, &QModbusReply::finished, [=](){
                if(reply->error() == QModbusDevice::NoError){qDebug()<<"****write oK****";
                }else {
                    QMessageBox::warning(nullptr,tr("Write Failed!"),tr("error message：").arg(reply->errorString()).arg(reply->error(), -1, 16), 5000,QMessageBox::Yes,QMessageBox::No);
                }
                reply->deleteLater();
            });
        }else {
            reply->deleteLater();
        }
    }
}

void ScanControlHuiChuan::writeNameRegisterGroup(QModbusClient *modbusDevice, int serverAddress,QList<QString> nameList)
{
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
    auto reply_coils = modbusDevice->sendWriteRequest(modbusData, serverAddress);
    if(reply_coils){
        if (!reply_coils->isFinished())
        {
            connect(reply_coils, &QModbusReply::finished, [=](){
                if(reply_coils->error() == QModbusDevice::NoError){qDebug()<<"****write oK****";
                }else {
                    QMessageBox::warning(nullptr,tr("Write Failed!"),tr("error message：").arg(reply_coils->errorString()).arg(reply_coils->error(), -1, 16), 5000,QMessageBox::Yes,QMessageBox::No);
                }
                reply_coils->deleteLater();
            });
        }else {
            reply_coils->deleteLater();
        }
    }
}

void ScanControlHuiChuan::writeRegisterGroup(QModbusClient *modbusDevice, int startAddress, int remainingRegisters, QVector<uint16_t> data, int serverAddress)
{

    // 假设你要写入的寄存器数量和每次写入的组大小
    int registersPerGroup = 120;  // 每组写入 100 个寄存器

    int currentWriteCount = qMin(registersPerGroup, remainingRegisters);  // 本次写入的寄存器数量
    QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, startAddress, currentWriteCount);

    // 设置要写入的寄存器值
    for (int i = 0; i < currentWriteCount; ++i) {
        writeUnit.setValue(i, data[startAddress + i-3000]);
        //qDebug()<<"data="<<data<<"count="<<startAddress + i-3000;
    }
     //qDebug()<<"writeUnit="<<writeUnit.values();

     // 发送写入请求
         if (auto *reply = modbusDevice->sendWriteRequest(writeUnit, serverAddress)) {
             if (!reply->isFinished()) {
                 // 连接写入完成的信号
                 connect(reply, &QModbusReply::finished, [=]() {
                     if (reply->error() == QModbusDevice::ProtocolError) {
                         qWarning() << "Write error: " << reply->errorString();
                     } else if (reply->error() == QModbusDevice::TimeoutError) {
                         qWarning() << "Request timeout occurred. Retrying...";
                         // 如果请求超时，进行重试
                         if (retryCount < 3) {  // 设置重试次数为3次
                             progressDialog->setValue(progressDialog->value() + 20);  // 更新进度
                             qDebug() << "Retrying write group from address " << startAddress << " retry count: " << (retryCount + 1);
                             QTimer::singleShot(500, this, [=]() {
                                 writeRegisterGroup(modbusDevice, startAddress, remainingRegisters, data, serverAddress);  // 重试
                                 retryCount=retryCount + 1;
                             });
                         } else {
                             progressDialog->close();
                             QMessageBox::warning(nullptr,  // 父窗口，这里传递 nullptr 表示没有父窗口
                                                      "Warning",  // 对话框的标题
                                                      "Max retry attempts reached. "
                                                      "Aborting write."
                                                      "Please rewrite!",  // 显示的文本
                                                      QMessageBox::Ok);  // 确认按钮
                             qWarning() << "Max retry attempts reached. Aborting write.";
                         }
                     } else if (reply->error() != QModbusDevice::NoError) {
                         qWarning() << "Write finished with error: " << reply->errorString();
                     } else {
                         qDebug() << "Write group from address " << startAddress << " successful!";
                         // 如果还有剩余的寄存器，需要继续写入
                         if (remainingRegisters - currentWriteCount > 0) {
                             // 递归调用，写入下一组
                             progressDialog->setValue(progressDialog->value() + 5);  // 更新进度
                             writeRegisterGroup(modbusDevice, startAddress + currentWriteCount, remainingRegisters - currentWriteCount, data, serverAddress);
                         } else {
                             qDebug() << "All register groups written successfully!";
                             progressDialog->close();
                             QMessageBox::information(nullptr,  // 父窗口，这里传递 nullptr 表示没有父窗口
                                                      "Information",  // 对话框的标题
                                                      "All register groups written successfully!",  // 显示的文本
                                                      QMessageBox::Ok);  // 确认按钮
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
                    //connect(reply, &QModbusReply::finished, this, &ScanControlHuiChuan::handleReply);
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
}


