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
#include <QModbusDataUnit>

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


struct basePlc {
    int MovePointDate ;
    int Start ;
    int Stop ;
    int End ;
    int AganStart;
    int AlarmReset ;
    int SetOrigin ;
    int ZdetctHight ;
    int LineV ;
    int ArcV ;
    int xV;
    int yV;
    int jv;
    int pointV;
    int EndNumber ;
    int XOrigin ;
    int YOrigin ;
    int ZOrigin ;
    int ROrigin ;
    int moveType;
    int singeMove;
    int curX;
    int curY;
    int curZ;
    int curR;
    int MoveTargetX;
    int MoveTargetY;
    int MoveTargetZ;
    int MoveTargetR;
    int AxiSid;
    int  X_ADD;
    int  X_SUB;
    int  Y_ADD;
    int  Y_SUB;
    int  Z_ADD;
    int  Z_SUB;
    int  R_ADD;
    int  R_SUB;
    int  X_VIRTUAL_ORIGIN;
    int  Y_VIRTUAL_ORIGIN;
    int  MACHINE_ORIGIN;
    int  LIMIT_POINT;
    int  xDone;
    int  YDone;
    int  zDone;
    int  rDone;
};



struct h5u {
    int MovePointDate = h5uMovePointDate;
    int Start = h5uStart;
    int Stop = h5uStop;
    int End = h5uEnd;
    int AganStart;
    int AlarmReset = h5uAlarmReset;
    int SetOrigin = h5uSetOrigin;
    int ZdetctHight = h5uZdetctHight;
    int LineV = h5uLineV;
    int ArcV = h5uArcV;
    int xV=h5uR_REGISTER_BASE+h5uX_VELOCITY;
    int yV=h5uR_REGISTER_BASE+h5uY_VELOCITY;
    int jV=h5uR_REGISTER_BASE+h5uJOG_VELOCITY;
    int pointV;
    int EndNumber = h5uEndNumber;
    int XOrigin = h5uXOrigin;
    int YOrigin = h5uYOrigin;
    int ZOrigin = h5uZOrigin;
    int ROrigin = h5uROrigin;
    int moveType=h5uMoveType;
    int singeMove=h5uR_REGISTER_BASE+h5uX_TARTPOS;
    int curX=h5uR_REGISTER_BASE+h5uX_TARTPOS;
    int curY=h5uR_REGISTER_BASE+h5uY_TARTPOS;
    int curZ=h5uZ_CUR_POS;
    int curR=h5uR_CUR_POS;
    int MoveTargetX;
    int MoveTargetY;
    int MoveTargetZ;
    int MoveTargetR;
    int AxiSid=h5uAXIS_ERROR_ID;
    int  X_ADD=h5uX_ADD;
    int  X_SUB=h5uX_SUB;
    int  Y_ADD=h5uY_ADD;
    int  Y_SUB=h5uY_SUB;
    int  Z_ADD=h5uZ_ADD;
    int  Z_SUB=h5uZ_SUB;
    int  R_ADD=h5uR_ADD;
    int  R_SUB=h5uR_SUB;
    int  X_VIRTUAL_ORIGIN=h5uX_VIRTUAL_ORIGIN;
    int  Y_VIRTUAL_ORIGIN=h5uY_VIRTUAL_ORIGIN;
    int  MACHINE_ORIGIN=h5uMACHINE_ORIGIN;
    int  LIMIT_POINT=h5uLIMIT_POINT;
    int  xDone=h5uX_AXIS_DONE;
    int  YDone=h5uY_AXIS_DONE;
    int  zDone=h5uZ_STOP;
    int  rDone=h5uR_STOP;
};


struct ac700 {
    int MovePointDate = ac700MovePointDate;
    int Start = ac700Start;
    int Stop = ac700Stop;
    int End = ac700End;
    int AganStart=ac700AganStart;
    int AlarmReset = ac700AlarmReset;
    int SetOrigin = ac700SetOrigin;
    int ZdetctHight = ac700ZdetctHight;
    int LineV = ac700LineV;
    int ArcV = ac700ArcV;
    int xV=ac700R_REGISTER_BASE+ac700X_VELOCITY;
    int yV=ac700R_REGISTER_BASE+ac700Y_VELOCITY;
    int jV=ac700JOG_VELOCITY;
    int pointV=ac700pointV;
    int EndNumber = ac700EndNumber;
    int XOrigin = ac700XOrigin;
    int YOrigin = ac700YOrigin;
    int ZOrigin = ac700ZOrigin;
    int ROrigin = ac700ROrigin;
    int moveType=ac700MoveType;
    int singeMove=ac700R_REGISTER_BASE+ac700X_TARTPOS;
    int curX=ac700X_CUR_POS;
    int curY=ac700Y_CUR_POS;
    int curZ=ac700Z_CUR_POS;
    int curR=ac700R_CUR_POS;
    int MoveTargetX=ac700X_Tar_POS;
    int MoveTargetY=ac700Y_Tar_POS;
    int MoveTargetZ=ac700Y_Tar_POS;
    int MoveTargetR=ac700Y_Tar_POS;
    int AxiSid=ac700AXIS_ERROR_ID;
    int  X_ADD=ac700X_ADD;
    int  X_SUB=ac700X_SUB;
    int  Y_ADD=ac700Y_ADD;
    int  Y_SUB=ac700Y_SUB;
    int  Z_ADD=ac700Z_ADD;
    int  Z_SUB=ac700Z_SUB;
    int  R_ADD=ac700R_ADD;
    int  R_SUB=ac700R_SUB;
    int  X_VIRTUAL_ORIGIN=ac700X_VIRTUAL_ORIGIN;
    int  Y_VIRTUAL_ORIGIN=ac700Y_VIRTUAL_ORIGIN;
    int  MACHINE_ORIGIN=ac700MACHINE_ORIGIN;
    int  LIMIT_POINT=ac700LIMIT_POINT;
    int  xDone=ac700X_AXIS_DONE;
    int  YDone=ac700Y_AXIS_DONE;
    int  zDone=ac700Z_STOP;
    int  rDone=ac700R_STOP;
};



class ScanControlAbstract : public QObject
{
    Q_OBJECT



public:



    explicit ScanControlAbstract(QObject *parent = nullptr):QObject(parent){}

    virtual ~ScanControlAbstract() {}

    virtual void setModbusTcpIP(QString ip)  = 0;   //设置IP
    virtual void setModbusPort(int port)  = 0;      //设置端口

    virtual void setXAxisVelocity(float vel) = 0;   //设置X轴速度
    virtual void setYAxisVelocity(float vel) = 0;   //设置Y轴速度
    virtual void setJogVelocity(float vel) = 0;     //设置点动速度

    virtual bool isXCrossed() = 0;                  //判断扫查区域的X轴是否越界
    virtual bool isYCrossed() = 0;                  //判断扫查区域的Y轴是否越界
    virtual bool isJogCrossed(int &address, float &data) = 0; //点动判断是都越界

    virtual bool sendPulseCommand(QModbusClient *modbusClient, QModbusDataUnit::RegisterType type, quint16 address)=0;

    virtual bool sendStringCommand(QModbusClient *modbusClient, QModbusDataUnit::RegisterType type, quint16 address,QString Value)=0;

    virtual void writeRegisterGroup( int startAddress,
                         const   QVector<modelDate> &modelDates, int serverAddress)=0;

    virtual void writeAc700PointRegisterGroup( int startAddress,
                                       const QVector<modelDate> &modelDates, int serverAddress)=0;


    virtual void ZdetectHight(float hight)=0;

    virtual void updataCurrentPos()=0;



public:
    h5u h5uData;
    ac700 ac700Data;
    basePlc basePlcData;

    QString workPiece;

    QModbusTcpClient *modbusClient;
    QSettings *Rsettings;
    bool isRunTarget;
    bool isAddRoute_dialogOpen;

public slots:
    virtual void init() = 0;   //初始化设置
    virtual void destroy() = 0;  //销毁设置

    virtual void on_connectBtn_clicked() = 0;       //连接服务

    virtual void on_startScanBtn_clicked() = 0;     //开始扫查
    virtual void on_stopScanBtn_clicked() = 0;      //暂停扫查
    virtual void on_endScanBtn_clicked() = 0;       //结束扫描
    virtual void on_aganStartScanBtn_clicked()=0;

    virtual void on_setOriginBtn_clicked(QString axitType) = 0;     //设置零点

    virtual void onBackOriginBtn_clicked() = 0;     //设置零点

    virtual void on_line_velocity_editingFinished(float val) = 0;   // 设置X轴速度
    virtual void on_arc_velocity_editingFinished(float val) = 0;   // 设置Y轴速度
    virtual void on_jog_velocity_editingFinished(float val) = 0; // 设置点动速度
    virtual void on_point_velocity_editingFinished(float val) = 0; // 设置点动速度


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

    virtual bool runTargetPosition(double x, double y,double z, double r) = 0; //运动到目标位置
    virtual  bool modbusState()=0;
    virtual  void selectProcessType(int type)=0;





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
