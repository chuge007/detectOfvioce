#ifndef SCANCONTROLABSTRACT_H
#define SCANCONTROLABSTRACT_H

#include <QObject>
#include <QModbusTcpClient>
#include <QModbusReply>
#include <QDoubleValidator>
#include <QPointF>
#include <QTimer>
#include <QQueue>
#include <QPair>
#include <QSettings>
#include <QTimer>
#include <QTime>

#include "modbusconfig.h"

class Ui_MainWindow;

enum ScanModel{
    NormalScan = 0, //正常模式
    SingleScan      //单边模式
};

enum AxisJog{       //寸动
    NotAxisJog = 0,
    XJogAdd,
    XJogSub,
    YJogAdd,
    YJogSub,

    XJogAddPressed ,
    XJogAddReleased,
    XJogSubPressed ,
    XJogSubReleased,
    YJogAddPressed ,
    YJogAddReleased,
    YJogSubPressed ,
    YJogSubReleased,
    ZJogAddPressed ,
    ZJogAddReleased,
    ZJogSubPressed ,
    ZJogSubReleased,
    RJogAddPressed ,
    RJogAddReleased,
    RJogSubPressed ,
    RJogSubReleased,
};

enum AxisState{
    XMoveDone = 0,
    YMoveDone
};

struct modelDate {
    QString type;                        // 保存 "arc" 或 "line" 字符串
    QVector<QVector<float>> points;        // 保存相关点，每个点包含 4 个 float
};



class ScanControlAbstract : public QObject
{
    Q_OBJECT



public:



    explicit ScanControlAbstract(QObject *parent = nullptr):QObject(parent){}

    virtual ~ScanControlAbstract() {}

    virtual void setModbusTcpIP(QString ip)  = 0;   //设置IP
    virtual void setModbusPort(int port)  = 0;      //设置端口
    virtual void disConncet() = 0;

    virtual void setXAxisVelocity(float vel) = 0;   //设置X轴速度
    virtual void setYAxisVelocity(float vel) = 0;   //设置Y轴速度
    virtual void setJogVelocity(float vel) = 0;     //设置点动速度

    virtual bool isXCrossed() = 0;                  //判断扫查区域的X轴是否越界
    virtual bool isYCrossed() = 0;                  //判断扫查区域的Y轴是否越界
    virtual bool isJogCrossed(int &address, float &data) = 0; //点动判断是都越界

    virtual bool sendPulseCommand(QModbusClient *modbusClient, QModbusDataUnit::RegisterType type, int address)=0;

    virtual void writeRegisterGroup( int startAddress,
                         const   QVector<modelDate> &modelDates, int serverAddress)=0;

    virtual void ZdetectHight(float hight)=0;

    QSettings *Rsettings;
    bool isRunTarget;
    bool isUseScanDetect;


public slots:
    virtual void init() = 0;   //初始化设置
    virtual void destroy() = 0;  //销毁设置

    virtual void on_connectBtn_clicked() = 0;       //连接服务

    virtual void on_startScanBtn_clicked() = 0;     //开始扫查
    virtual void on_stopScanBtn_clicked() = 0;      //暂停扫查
    virtual void on_endScanBtn_clicked() = 0;       //结束扫描

    virtual void on_setOriginBtn_clicked(float x,float y,bool isCurrPosi) = 0;     //设置零点

    virtual void on_x_or_line_velocity_editingFinished(float val) = 0;   // 设置X轴速度
    virtual void on_y_or_arc_velocity_editingFinished(float val) = 0;   // 设置Y轴速度
    virtual void on_jog_velocity_editingFinished(float val) = 0; // 设置点动速度


    //寸动
    virtual void on_xAddBtn_clicked() = 0;  //X+
    virtual void on_xSubBtn_clicked() = 0;  //X-
    virtual void on_yAddBtn_clicked() = 0;  //Y+
    virtual void on_ySubBtn_clicked() = 0;  //Y-
    //点动
    virtual void on_xAddBtn_pressed() = 0;  //X+
    virtual void on_xAddBtn_released() = 0;
    virtual void on_xSubBtn_pressed() = 0;  //X-
    virtual void on_xSubBtn_released() = 0;
    virtual void on_yAddBtn_pressed() = 0;  //Y+
    virtual void on_yAddBtn_released() = 0;
    virtual void on_ySubBtn_pressed() = 0;  //Y-
    virtual void on_ySubBtn_released() = 0;
    virtual void on_zAddBtn_pressed() = 0;  //Z+
    virtual void on_zAddBtn_released() = 0;
    virtual void on_zSubBtn_pressed() = 0;  //Z-
    virtual void on_zSubBtn_released() = 0;
    virtual void on_rAddBtn_pressed() = 0;  //r+
    virtual void on_rAddBtn_released() = 0;
    virtual void on_rSubBtn_pressed() = 0;  //r-
    virtual void on_rSubBtn_released() = 0;

    virtual void on_alarmResetBtn_clicked() = 0;    //报警复位
    virtual void on_setLimitBtn_clicked() = 0;      //设置机械极限位
    virtual void on_setMachineBtn_clicked() = 0;    //设置机械极原点

    virtual void runTargetPosition(double x, double y,double z, double r) = 0; //运动到目标位置
    virtual  bool modbusState()=0;






signals:
    void modbusStateChange(QModbusDevice::State);   //modbus连接状态
    void positionChange(QPointF,float cur_r,float cur_z);                   //轴位置变化
    void velocityChange(float x, float y, float jog);          //轴速度变化
    void axisError(int xErrorId, int yErrorId);     //轴报错
    void machineStart();    //机械开始按键
    void machineStop();     //机械暂停按键
    void scanRowNumChange(int num);     //扫查行数
    void scanRowEnd(AxisState);  //行扫查结束信号
    void scanTime(QString ms);  //扫查时间-单位毫秒

};

#endif // SCANCONTROLABSTRACT_H
