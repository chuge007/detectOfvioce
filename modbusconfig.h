﻿#ifndef MODBUSCONFIG_H
#define MODBUSCONFIG_H

//汇川寄存器地址
#define R_REGISTER_BASE 0x3000  //寄存器R的基地址
#define X_TARTPOS 2002  //设置X轴位置
#define Y_TARTPOS 2004  //设置Y轴位置
#define X_VELOCITY 2006 //设置X轴速度
#define Y_VELOCITY 2008 //设置Y轴速度
#define JOG_VELOCITY 2014   //设置点动速度
#define X_CUR_POS 300   //当前绝对位置X
#define Y_CUR_POS 302   //当前绝对位置Y
#define Z_CUR_POS 298
#define R_CUR_POS 296

#define X_AXIS_DONE 100     //X轴动作完成位
#define Y_AXIS_DONE 101     //Y轴动作完成位

#define X_VIRTUAL_ORIGIN 304    //虚拟0点X
#define Y_VIRTUAL_ORIGIN 306    //虚拟0点Y

#define X_START 2   //X轴开始
#define Y_START 3   //Y轴开始
#define X_STOP 4    //X轴暂停
#define Y_STOP 5    //Y轴暂停
#define END_SCAN 6  //结束扫查
#define MACHINE_ORIGIN  7   //设置机械原点
#define AXIS_RESET 8        //轴复位
#define LIMIT_POINT 9       //设置机械极限

#define X_ADD 13    //X+
#define X_SUB 14    //X-
#define Y_ADD 15    //Y+
#define Y_SUB 16    //Y-
#define Z_ADD 17    //Z+
#define Z_SUB 18    //Z-
#define R_ADD 19    //R+
#define R_SUB 20    //R-

#define AXIS_ERROR_ID 308   //轴错误ID
#define MACHINE_START 310   //机械按键开始
#define MACHINE_STOP 311    //机械按键开始

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




//汇川摩擦焊定义

//D区
#define frictionWeldingMovePointDate   3000
#define frictionWeldingStart           4216
#define frictionWeldingStop            4220
#define frictionWeldingEnd             4222
#define frictionWeldingAlarmReset      4218
#define frictionWeldinSetOrigin        4224

#define frictionWeldinZdetctHight       4208
#define frictionWeldinLineV             4210
#define frictionWeldinArcV              4212
#define frictionWeldinEndNumber         4214
#define frictionWeldinXOrigin           4200
#define frictionWeldinYOrigin           4202
#define frictionWeldinZOrigin           4204
#define frictionWeldinROrigin           4206
//M区
#define frictionWeldinMoveType         1000




#endif // MODBUSCONFIG_H
