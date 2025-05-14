#ifndef MODBUSCONFIG_H
#define MODBUSCONFIG_H


#define HuiChuan_IP "192.168.1.88"
#define TaiDa_IP    "192.168.1.5"

#define HuiChuan_Port 502
#define TaiDa_Port    502

#define processTypeGcode            4824
#define processTypeFrictionWelding  4825
#define processTypeBrazing          4826
#define workPieceModbusAdress       150


//汇川寄存器地址h5u
//D区 汇川摩擦焊定义
#define h5uMovePointDate   3000
#define h5uStart           4216
#define h5uStop            4220
#define h5uEnd             4222
#define h5uAlarmReset      4817
#define h5uSetOrigin        4224

#define h5uZdetctHight       4208
#define h5uLineV             4210
#define h5uArcV              4212
#define h5uEndNumber         4214

#define h5uXOrigin           4200
#define h5uYOrigin           4202
#define h5uZOrigin           4204
#define h5uROrigin           4206
//汇川摩擦焊定义

#define h5uX_CUR_POS 300   //当前绝对位置X
#define h5uY_CUR_POS 302   //当前绝对位置Y
#define h5uZ_CUR_POS 298    //当前绝对位置Z
#define h5uR_CUR_POS 296    //当前绝对位置R

#define h5uJOG_VELOCITY 2014   //设置点动速度
//R区
#define h5uR_REGISTER_BASE 0x3000  //寄存器R的基地址
#define h5uX_TARTPOS 2002  //设置X轴位置
#define h5uY_TARTPOS 2004  //设置Y轴位置


#define h5uX_VELOCITY 2006 //设置X轴速度
#define h5uY_VELOCITY 2008 //设置Y轴速度
#define h5uX_VIRTUAL_ORIGIN 304    //虚拟0点X
#define h5uY_VIRTUAL_ORIGIN 306    //虚拟0点Y

//M区
#define h5uMoveType         1000

#define h5uX_ADD 13    //X+
#define h5uX_SUB 14    //X-
#define h5uY_ADD 15    //Y+
#define h5uY_SUB 16    //Y-
#define h5uZ_ADD 17    //Z+
#define h5uZ_SUB 18    //Z-
#define h5uR_ADD 19    //R+
#define h5uR_SUB 20    //R-
#define h5uAXIS_ERROR_ID 308   //轴错误ID

#define h5uLIMIT_POINT 9       //设置机械极限
#define h5uMACHINE_ORIGIN  7   //设置机械原点

#define h5uX_AXIS_DONE 100     //X轴动作完成位
#define h5uY_AXIS_DONE 101     //Y轴动作完成位

#define h5uX_START 2   //X轴开始
#define h5uY_START 3   //Y轴开始
#define h5uX_STOP 4    //X轴暂停
#define h5uY_STOP 5    //Y轴暂停
#define h5uZ_STOP 44    //Z轴暂停
#define h5uR_STOP 45    //R轴暂停

#define h5uEND_SCAN 6  //结束扫查
#define h5uAXIS_RESET 8        //轴复位

#define h5uMACHINE_START 310   //机械按键开始
#define h5uMACHINE_STOP 311    //机械按键开始









//----------------------------------------------------/台大寄存器地址--------
//台大寄存器地址
#define WORKPIECEHIGH 650
#define WORKPIECEWIDE 652
#define SCANSCOPE     654

#define STARTSCANE 0
#define STOPSCAN   8
#define ENDSCAN    120

#define GOORIGIN  77
#define SETORIGIN 66

#define XCURPOS 300
#define YCURPOS 302
#define ZCURPOS 298
#define RCURPOS 296

#define XENABLE 80
#define YENABLE 81
#define T_Y_ADD   40
#define T_Y_SUB   41
#define T_X_ADD   42
#define T_X_SUB   43

#define POINT_VELOCITY          680
#define POINT_ADD_SUB_VELOCITY  690
#define GO_ORIGIN_VELOCITY      692
#define SCANSPEED               512

#define DEVICEORIGIN   151
#define ILLUMINATING   154
#define UNILATERALSCAN 155

#define X_IOSTATE quint16(0x6000)
#define Y_IOSTATE quint16(0xa000)




//-------------------------------------------------------ac700----------------

//D区 汇川摩擦焊定义
#define ac700MovePointDate   3000
#define ac700Start           4818
#define ac700Stop            4820
#define ac700End             4819
#define ac700AlarmReset      4817
#define ac700SetOrigin       4823
#define ac700AganStart       4821

#define ac700ZdetctHight       3216
#define ac700LineV             6312
#define ac700ArcV              6314
#define ac700JOG_VELOCITY      95
#define ac700pointV            97
#define ac700EndNumber         6316

#define ac700XOrigin           4808
#define ac700YOrigin           4809
#define ac700ZOrigin           4810
#define ac700ROrigin           4811
//汇川摩擦焊定义

#define ac700X_CUR_POS 50   //手动绝对位置X
#define ac700Y_CUR_POS 52   //手动绝对位置Y
#define ac700Z_CUR_POS 54    //手动绝对位置Z
#define ac700R_CUR_POS 56    //手动绝对位置R

#define ac700X_Tar_POS 100   //手动绝对位置X
#define ac700Y_Tar_POS 102   //手动绝对位置Y
#define ac700Z_Tar_POS 104    //手动绝对位置Z
#define ac700R_Tar_POS 106    //手动绝对位置R
//R区
#define ac700R_REGISTER_BASE 0x3000  //寄存器R的基地址
#define ac700X_TARTPOS 2002  //设置X轴位置
#define ac700Y_TARTPOS 2004  //设置Y轴位置


#define ac700X_VELOCITY 2006 //设置X轴速度
#define ac700Y_VELOCITY 2008 //设置Y轴速度
#define ac700X_VIRTUAL_ORIGIN 304    //虚拟0点X
#define ac700Y_VIRTUAL_ORIGIN 306    //虚拟0点Y

//M区
#define ac700MoveType         10000

#define ac700X_ADD 4800    //X+
#define ac700X_SUB 4801    //X-
#define ac700Y_ADD 4802    //Y+
#define ac700Y_SUB 4803    //Y-
#define ac700Z_ADD 4804    //Z+
#define ac700Z_SUB 4805    //Z-
#define ac700R_ADD 4806    //R+
#define ac700R_SUB 4807    //R-
#define ac700AXIS_ERROR_ID 308   //轴错误ID

#define ac700LIMIT_POINT 9       //设置机械极限
#define ac700MACHINE_ORIGIN  7   //设置机械原点

#define ac700X_AXIS_DONE 100     //X轴动作完成位
#define ac700Y_AXIS_DONE 101     //Y轴动作完成位

#define ac700X_START 2   //X轴开始
#define ac700Y_START 3   //Y轴开始
#define ac700X_STOP 4    //X轴暂停
#define ac700Y_STOP 5    //Y轴暂停
#define ac700Z_STOP 44    //Z轴暂停
#define ac700R_STOP 45    //R轴暂停

#define ac700END_SCAN 6  //结束扫查
#define ac700AXIS_RESET 8        //轴复位

#define ac700MACHINE_START 310   //机械按键开始
#define ac700MACHINE_STOP 311    //机械按键开始



#endif // MODBUSCONFIG_H
