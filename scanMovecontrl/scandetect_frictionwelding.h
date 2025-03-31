#ifndef scanDetect_frictionWelding_H
#define scanDetect_frictionWelding_H

#include "scancontrolabstract.h"
#include <QProgressDialog>
#include <QDebug>


class scanDetect_frictionWelding : public ScanControlAbstract  // 修改继承关系
{
    Q_OBJECT



public:
    explicit scanDetect_frictionWelding(QObject *parent = nullptr);

    ~scanDetect_frictionWelding();

    void setModbusTcpIP(QString ip) { PlcIP = ip;}   //设置IP
    void setModbusPort(int port) { PlcPort = port;}   //设置端口

    QPointF virtualOrigin() const { return zeroPoint; }     //虚拟0点
    QPointF currentPosition() const { return currentPos;}   //当前位置

    void setXAxisVelocity(float vel);       //设置X轴速度
    void setYAxisVelocity(float vel);       //设置Y轴速度
    void setJogVelocity(float vel);         //设置点动速度


    bool isXCrossed();   //判断扫查区域的X轴是否越界
    bool isYCrossed();   //判断扫查区域的Y轴是否越界
    bool isJogCrossed(int &address, float &data);


    void writeRegisterGroup( int startAddress,
                            const QVector<modelDate> &modelDates, int serverAddress);
    bool isRunTarget = false;   //执行目标点
    void ZdetectHight(float hight);



public slots:
    void init();
    void destroy();

    void on_connectBtn_clicked();

    void on_startScanBtn_clicked();     //开始扫查
    void on_stopScanBtn_clicked();      //暂停扫查
    void on_endScanBtn_clicked();       //结束扫描

    void on_setOriginBtn_clicked(float x,float y,bool isCurrPosi);     //设置零点


    void on_line_velocity_editingFinished(float val); // 设置直线速度
    void on_arc_velocity_editingFinished(float val); // 设置圆弧速度
    void on_jog_velocity_editingFinished(float val); // 设置点动速度


    //寸动
    void on_xAddBtn_clicked();  //X+
    void on_xSubBtn_clicked();  //X-
    void on_yAddBtn_clicked();  //Y+
    void on_ySubBtn_clicked();  //Y-
    //点动
    void on_xAddBtn_pressed();  //X+
    void on_xAddBtn_released();
    void on_xSubBtn_pressed();  //X-
    void on_xSubBtn_released();
    void on_yAddBtn_pressed();  //Y+
    void on_yAddBtn_released();
    void on_ySubBtn_pressed();  //Y-
    void on_ySubBtn_released();
    void on_zAddBtn_pressed();  //z+
    void on_zAddBtn_released();
    void on_zSubBtn_pressed();  //z-
    void on_zSubBtn_released();
    void on_rAddBtn_pressed();  //r+
    void on_rAddBtn_released();
    void on_rSubBtn_pressed();  //r-
    void on_rSubBtn_released();

    void on_alarmResetBtn_clicked();    //报警复位
    void on_setLimitBtn_clicked();      //设置机械极限位
    void on_setMachineBtn_clicked();    //设置机械极原点


    void runTargetPosition(double x, double y,double z, double r);

private slots:
    bool modbusState();
    void performTasks();


private:
    int retryCount ;
    QProgressDialog *progressDialog;

    void initWidget();
    void connectFun();
    void readSetting();
    void writeSetting();
    void initStates();

    float readModbusFloatData(int v1, int v2);
    QPair<quint16, quint16> writeModbusFloatData(float value);
    void writeHoldingRegistersData(int address, quint16 size, float data);





    void writeAxisVelocity(int address, quint16 size, float data);
    void readAxisVelocity(int address, quint16 size);
    void readAxisJogStatus(int address);
    void readAxisErrorID();
    void writeAxisReset();
    void writeAxisLimitPosition();
    void writeAxisMachineOrigin();
    void writeAxisJog(int address, bool data);


    void updataCurrentPos();        //更新当前点位置

    void perfromJogTasks();         //点动

    bool sendPulseCommand(QModbusClient *modbusClient,
                          QModbusDataUnit::RegisterType rGtype, int address);

    bool sendCommandValue(QModbusClient *modbusClient,
                          QModbusDataUnit::RegisterType rGtype, int address,float value);


private:
    QModbusTcpClient *modbusClient = nullptr;
    QString PlcIP;
    int PlcPort = 502;

    QSettings *Rsettings = nullptr;
    QTimer *timer = nullptr;


    float xVelocity = 20;
    float yVelocity = 20;
    float jogVelocity = 20;
    int jopStep = 1;



    bool isStartScan = false;   //开始扫查标志位
    bool isStopScan = false;    //暂停扫查标志位
    bool isAxisStop = false;    //轴停止状态
    bool updateCurPos = false;  //更新轴位置
    bool isEndScan = false;     //结束扫查标志位
    bool isJogDone = false;     //点动完成标志位



    bool isHaveMachine = true;  //判断是否有机械原点
    bool isHaveLimit = true;    //判断是否有机械极限

    bool manState[2] = {false, false};  //手动状态位

    ScanModel scanModel = ScanModel::NormalScan;    //扫查模式
    AxisJog axisInch = AxisJog::NotAxisJog;      //寸动
    AxisJog  axisJog = AxisJog::NotAxisJog;      //点动

    QPointF zeroPoint  = QPointF(0,0);       //虚拟0点
    QPointF limitPoint = QPointF(500, 400);  //极限位置
    QPointF currentPos = QPointF(0,0);
    float curZ,curR;

};

#endif // scanDetect_frictionWelding_H



//    void readAxisEndState();
//    void writeBackZero();
//    void writeEndScanStatus();

//    void writeAxisStopStatus(int address);
//    void readAxisRunStatus(int address, quint16 size);
    //bool nextScan();
    //void setManualModel(bool states);
//void on_singleScan_toggled(bool checked);   //单边模式
//    void setAxisJogStep(int step);          //设置轴寸动步进
//void on_jogStep_1_clicked();    //点动步进1
//void on_jogStep_5_clicked();    //点动步进5
//void on_jogStep_10_clicked();   //点动不经10
//    void creataTasksTable();        //创建自动扫查任务
//    void perfromStartScanTasks();   //执行自动扫查任务
//    void perfromStopScanTasks();    //执行暂停
//    void perfromEndScanTasks();     //结束扫查
//    void writeNameRegisterGroup(QModbusClient *modbusDevice, int serverAddress,QList<QString> nameList);
//    void writeRegisterGroup(QModbusClient *modbusDevice, int startAddress, int remainingRegisters, QVector<uint16_t> data, int serverAddress);

//    void writeRoutePos(int address, quint16 size, QList<float> dataList_x0,QList<float> dataList_y0, QList<float> dataList_r0,QList<float> dataList_x1, QList<float> dataList_y1,QList<float> dataList_r1,QList<QString> nameList);
//    void writeRoutPosName(int address,QList<QString> nameList);
