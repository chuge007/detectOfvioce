#ifndef scanDetect_frictionWelding_H
#define scanDetect_frictionWelding_H

#include "scancontrolabstract.h"
#include <QProgressDialog>
#include <QDebug>
#include <QModbusDataUnit>
#include <QMutex>


class scanDetect_frictionWelding : public ScanControlAbstract  // 修改继承关系
{
    Q_OBJECT



public:
    explicit scanDetect_frictionWelding(QObject *parent = nullptr);

    ~scanDetect_frictionWelding();


    void setModbusTcpIP(QString ip) { PlcIP = ip;}   //设置IP
    void setModbusPort(int port) { PlcPort = port;}   //设置端口

    void selectProcessType(int type);



public slots:
    void init();
    void destroy();

    void on_connectBtn_clicked();

    void on_startScanBtn_clicked();     //开始扫查
    void on_stopScanBtn_clicked();      //暂停扫查
    void on_endScanBtn_clicked();       //结束扫描
    void on_aganStartScanBtn_clicked();       //结束扫描

    void on_setOriginBtn_clicked(QString axitType);     //设置零点


    void on_line_velocity_editingFinished(float val); // 设置直线速度
    void on_arc_velocity_editingFinished(float val); // 设置圆弧速度
    void on_jog_velocity_editingFinished(float val); // 设置点动速度
    void on_point_velocity_editingFinished(float val);

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
    void onBackOriginBtn_clicked();
    bool runTargetPosition(double x, double y,double z, double r);



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

    float readModbusFloatData(uint16_t  v1, uint16_t  v2);
    QPair<quint16, quint16> writeModbusFloatData(float value);



    void writeAxisJog(int address, bool data);


    void updataCurrentPos();        //更新当前点位置

    void perfromJogTasks();         //点动

    bool sendPulseCommand(QModbusClient *modbusClient,
                          QModbusDataUnit::RegisterType rGtype, quint16 address);

    bool sendCommandValue(QModbusClient *modbusClient,
                          QModbusDataUnit::RegisterType rGtype, quint16 address,float value);


    bool sendStringCommand(QModbusClient *modbusClient, QModbusDataUnit::RegisterType type, quint16 address,QString Value);

private:

    //QModbusTcpClient *modbusClient = nullptr;
    QString PlcIP;
    int PlcPort = 502;

    QSettings *Rsettings = nullptr;
    QTimer *timer = nullptr;

    float xVelocity = 20;
    float yVelocity = 20;
    float jogVelocity = 20;



    bool isRunTarget = false;   //执行目标点
    bool isStartScan = false;   //开始扫查标志位
    bool isStopScan = false;    //暂停扫查标志位
    bool isAxisStop = false;    //轴停止状态
    bool updateCurPos = false;  //更新轴位置
    bool isEndScan = false;     //结束扫查标志位
    bool isJogDone = false;     //点动完成标志位


    ScanModel scanModel = ScanModel::NormalScan;    //扫查模式
    AxisJog axisInch = AxisJog::NotAxisJog;      //寸动
    AxisJog  axisJog = AxisJog::NotAxisJog;      //点动

    AxisJog lastAxisJog = AxisJog::NotAxisJog;
    float curZ,curR;

    QMutex mutex;
 //-----------------------------------------------


private:

    int jopStep = 1;
    bool isHaveMachine = true;  //判断是否有机械原点
    bool isHaveLimit = true;    //判断是否有机械极限

    bool manState[2] = {false, false};  //手动状态位

    QPointF zeroPoint  = QPointF(0,0);       //虚拟0点
    QPointF limitPoint = QPointF(500, 400);  //极限位置
    QPointF currentPos = QPointF(0,0);

    bool isXCrossed();   //判断扫查区域的X轴是否越界
    bool isYCrossed();   //判断扫查区域的Y轴是否越界
    bool isJogCrossed(int &address, float &data);

    void writeAxisVelocity(int address, quint16 size, float data);
    void readAxisVelocity(int address, quint16 size);
    void readAxisJogStatus(int address);
    void readAxisErrorID();
    void writeAxisReset();
    void writeAxisLimitPosition();
    void writeAxisMachineOrigin();
    void writeHoldingRegistersData(int address, quint16 size, float data);


public slots:
    void on_setLimitBtn_clicked();      //设置机械极限位
    void on_setMachineBtn_clicked();    //设置机械极原点

    void setXAxisVelocity(float vel);       //设置X轴速度
    void setYAxisVelocity(float vel);       //设置Y轴速度
    void setJogVelocity(float vel);         //设置点动速度


    void writeRegisterGroup( int startAddress,
                            const QVector<modelDate> &modelDates, int serverAddress);
    void writeAc700PointRegisterGroup( int startAddress,
                                       const QVector<modelDate> &modelDates, int serverAddress);

    void ZdetectHight(float hight);
};

#endif // scanDetect_frictionWelding_H

