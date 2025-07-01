/****************************************************************************
** Meta object code from reading C++ file 'scandetect_frictionwelding.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../scanMovecontrl/scandetect_frictionwelding.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scandetect_frictionwelding.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_scanDetect_frictionWelding_t {
    QByteArrayData data[59];
    char stringdata0[1041];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_scanDetect_frictionWelding_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_scanDetect_frictionWelding_t qt_meta_stringdata_scanDetect_frictionWelding = {
    {
QT_MOC_LITERAL(0, 0, 26), // "scanDetect_frictionWelding"
QT_MOC_LITERAL(1, 27, 4), // "init"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 7), // "destroy"
QT_MOC_LITERAL(4, 41, 21), // "on_connectBtn_clicked"
QT_MOC_LITERAL(5, 63, 23), // "on_startScanBtn_clicked"
QT_MOC_LITERAL(6, 87, 22), // "on_stopScanBtn_clicked"
QT_MOC_LITERAL(7, 110, 21), // "on_endScanBtn_clicked"
QT_MOC_LITERAL(8, 132, 27), // "on_aganStartScanBtn_clicked"
QT_MOC_LITERAL(9, 160, 23), // "on_setOriginBtn_clicked"
QT_MOC_LITERAL(10, 184, 8), // "axitType"
QT_MOC_LITERAL(11, 193, 32), // "on_line_velocity_editingFinished"
QT_MOC_LITERAL(12, 226, 3), // "val"
QT_MOC_LITERAL(13, 230, 31), // "on_arc_velocity_editingFinished"
QT_MOC_LITERAL(14, 262, 31), // "on_jog_velocity_editingFinished"
QT_MOC_LITERAL(15, 294, 33), // "on_point_velocity_editingFini..."
QT_MOC_LITERAL(16, 328, 18), // "on_xAddBtn_clicked"
QT_MOC_LITERAL(17, 347, 18), // "on_xSubBtn_clicked"
QT_MOC_LITERAL(18, 366, 18), // "on_yAddBtn_clicked"
QT_MOC_LITERAL(19, 385, 18), // "on_ySubBtn_clicked"
QT_MOC_LITERAL(20, 404, 18), // "on_xAddBtn_pressed"
QT_MOC_LITERAL(21, 423, 19), // "on_xAddBtn_released"
QT_MOC_LITERAL(22, 443, 18), // "on_xSubBtn_pressed"
QT_MOC_LITERAL(23, 462, 19), // "on_xSubBtn_released"
QT_MOC_LITERAL(24, 482, 18), // "on_yAddBtn_pressed"
QT_MOC_LITERAL(25, 501, 19), // "on_yAddBtn_released"
QT_MOC_LITERAL(26, 521, 18), // "on_ySubBtn_pressed"
QT_MOC_LITERAL(27, 540, 19), // "on_ySubBtn_released"
QT_MOC_LITERAL(28, 560, 18), // "on_zAddBtn_pressed"
QT_MOC_LITERAL(29, 579, 19), // "on_zAddBtn_released"
QT_MOC_LITERAL(30, 599, 18), // "on_zSubBtn_pressed"
QT_MOC_LITERAL(31, 618, 19), // "on_zSubBtn_released"
QT_MOC_LITERAL(32, 638, 18), // "on_rAddBtn_pressed"
QT_MOC_LITERAL(33, 657, 19), // "on_rAddBtn_released"
QT_MOC_LITERAL(34, 677, 18), // "on_rSubBtn_pressed"
QT_MOC_LITERAL(35, 696, 19), // "on_rSubBtn_released"
QT_MOC_LITERAL(36, 716, 24), // "on_alarmResetBtn_clicked"
QT_MOC_LITERAL(37, 741, 23), // "onBackOriginBtn_clicked"
QT_MOC_LITERAL(38, 765, 17), // "runTargetPosition"
QT_MOC_LITERAL(39, 783, 1), // "x"
QT_MOC_LITERAL(40, 785, 1), // "y"
QT_MOC_LITERAL(41, 787, 1), // "z"
QT_MOC_LITERAL(42, 789, 1), // "r"
QT_MOC_LITERAL(43, 791, 11), // "modbusState"
QT_MOC_LITERAL(44, 803, 12), // "performTasks"
QT_MOC_LITERAL(45, 816, 22), // "on_setLimitBtn_clicked"
QT_MOC_LITERAL(46, 839, 24), // "on_setMachineBtn_clicked"
QT_MOC_LITERAL(47, 864, 16), // "setXAxisVelocity"
QT_MOC_LITERAL(48, 881, 3), // "vel"
QT_MOC_LITERAL(49, 885, 16), // "setYAxisVelocity"
QT_MOC_LITERAL(50, 902, 14), // "setJogVelocity"
QT_MOC_LITERAL(51, 917, 18), // "writeRegisterGroup"
QT_MOC_LITERAL(52, 936, 12), // "startAddress"
QT_MOC_LITERAL(53, 949, 18), // "QVector<modelDate>"
QT_MOC_LITERAL(54, 968, 10), // "modelDates"
QT_MOC_LITERAL(55, 979, 13), // "serverAddress"
QT_MOC_LITERAL(56, 993, 28), // "writeAc700PointRegisterGroup"
QT_MOC_LITERAL(57, 1022, 12), // "ZdetectHight"
QT_MOC_LITERAL(58, 1035, 5) // "hight"

    },
    "scanDetect_frictionWelding\0init\0\0"
    "destroy\0on_connectBtn_clicked\0"
    "on_startScanBtn_clicked\0on_stopScanBtn_clicked\0"
    "on_endScanBtn_clicked\0on_aganStartScanBtn_clicked\0"
    "on_setOriginBtn_clicked\0axitType\0"
    "on_line_velocity_editingFinished\0val\0"
    "on_arc_velocity_editingFinished\0"
    "on_jog_velocity_editingFinished\0"
    "on_point_velocity_editingFinished\0"
    "on_xAddBtn_clicked\0on_xSubBtn_clicked\0"
    "on_yAddBtn_clicked\0on_ySubBtn_clicked\0"
    "on_xAddBtn_pressed\0on_xAddBtn_released\0"
    "on_xSubBtn_pressed\0on_xSubBtn_released\0"
    "on_yAddBtn_pressed\0on_yAddBtn_released\0"
    "on_ySubBtn_pressed\0on_ySubBtn_released\0"
    "on_zAddBtn_pressed\0on_zAddBtn_released\0"
    "on_zSubBtn_pressed\0on_zSubBtn_released\0"
    "on_rAddBtn_pressed\0on_rAddBtn_released\0"
    "on_rSubBtn_pressed\0on_rSubBtn_released\0"
    "on_alarmResetBtn_clicked\0"
    "onBackOriginBtn_clicked\0runTargetPosition\0"
    "x\0y\0z\0r\0modbusState\0performTasks\0"
    "on_setLimitBtn_clicked\0on_setMachineBtn_clicked\0"
    "setXAxisVelocity\0vel\0setYAxisVelocity\0"
    "setJogVelocity\0writeRegisterGroup\0"
    "startAddress\0QVector<modelDate>\0"
    "modelDates\0serverAddress\0"
    "writeAc700PointRegisterGroup\0ZdetectHight\0"
    "hight"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_scanDetect_frictionWelding[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      45,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  239,    2, 0x0a /* Public */,
       3,    0,  240,    2, 0x0a /* Public */,
       4,    0,  241,    2, 0x0a /* Public */,
       5,    0,  242,    2, 0x0a /* Public */,
       6,    0,  243,    2, 0x0a /* Public */,
       7,    0,  244,    2, 0x0a /* Public */,
       8,    0,  245,    2, 0x0a /* Public */,
       9,    1,  246,    2, 0x0a /* Public */,
      11,    1,  249,    2, 0x0a /* Public */,
      13,    1,  252,    2, 0x0a /* Public */,
      14,    1,  255,    2, 0x0a /* Public */,
      15,    1,  258,    2, 0x0a /* Public */,
      16,    0,  261,    2, 0x0a /* Public */,
      17,    0,  262,    2, 0x0a /* Public */,
      18,    0,  263,    2, 0x0a /* Public */,
      19,    0,  264,    2, 0x0a /* Public */,
      20,    0,  265,    2, 0x0a /* Public */,
      21,    0,  266,    2, 0x0a /* Public */,
      22,    0,  267,    2, 0x0a /* Public */,
      23,    0,  268,    2, 0x0a /* Public */,
      24,    0,  269,    2, 0x0a /* Public */,
      25,    0,  270,    2, 0x0a /* Public */,
      26,    0,  271,    2, 0x0a /* Public */,
      27,    0,  272,    2, 0x0a /* Public */,
      28,    0,  273,    2, 0x0a /* Public */,
      29,    0,  274,    2, 0x0a /* Public */,
      30,    0,  275,    2, 0x0a /* Public */,
      31,    0,  276,    2, 0x0a /* Public */,
      32,    0,  277,    2, 0x0a /* Public */,
      33,    0,  278,    2, 0x0a /* Public */,
      34,    0,  279,    2, 0x0a /* Public */,
      35,    0,  280,    2, 0x0a /* Public */,
      36,    0,  281,    2, 0x0a /* Public */,
      37,    0,  282,    2, 0x0a /* Public */,
      38,    4,  283,    2, 0x0a /* Public */,
      43,    0,  292,    2, 0x08 /* Private */,
      44,    0,  293,    2, 0x08 /* Private */,
      45,    0,  294,    2, 0x0a /* Public */,
      46,    0,  295,    2, 0x0a /* Public */,
      47,    1,  296,    2, 0x0a /* Public */,
      49,    1,  299,    2, 0x0a /* Public */,
      50,    1,  302,    2, 0x0a /* Public */,
      51,    3,  305,    2, 0x0a /* Public */,
      56,    3,  312,    2, 0x0a /* Public */,
      57,    1,  319,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::Float,   12,
    QMetaType::Void, QMetaType::Float,   12,
    QMetaType::Void, QMetaType::Float,   12,
    QMetaType::Void, QMetaType::Float,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double,   39,   40,   41,   42,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Float,   48,
    QMetaType::Void, QMetaType::Float,   48,
    QMetaType::Void, QMetaType::Float,   48,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 53, QMetaType::Int,   52,   54,   55,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 53, QMetaType::Int,   52,   54,   55,
    QMetaType::Void, QMetaType::Float,   58,

       0        // eod
};

void scanDetect_frictionWelding::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<scanDetect_frictionWelding *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->init(); break;
        case 1: _t->destroy(); break;
        case 2: _t->on_connectBtn_clicked(); break;
        case 3: _t->on_startScanBtn_clicked(); break;
        case 4: _t->on_stopScanBtn_clicked(); break;
        case 5: _t->on_endScanBtn_clicked(); break;
        case 6: _t->on_aganStartScanBtn_clicked(); break;
        case 7: _t->on_setOriginBtn_clicked((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->on_line_velocity_editingFinished((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 9: _t->on_arc_velocity_editingFinished((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 10: _t->on_jog_velocity_editingFinished((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 11: _t->on_point_velocity_editingFinished((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 12: _t->on_xAddBtn_clicked(); break;
        case 13: _t->on_xSubBtn_clicked(); break;
        case 14: _t->on_yAddBtn_clicked(); break;
        case 15: _t->on_ySubBtn_clicked(); break;
        case 16: _t->on_xAddBtn_pressed(); break;
        case 17: _t->on_xAddBtn_released(); break;
        case 18: _t->on_xSubBtn_pressed(); break;
        case 19: _t->on_xSubBtn_released(); break;
        case 20: _t->on_yAddBtn_pressed(); break;
        case 21: _t->on_yAddBtn_released(); break;
        case 22: _t->on_ySubBtn_pressed(); break;
        case 23: _t->on_ySubBtn_released(); break;
        case 24: _t->on_zAddBtn_pressed(); break;
        case 25: _t->on_zAddBtn_released(); break;
        case 26: _t->on_zSubBtn_pressed(); break;
        case 27: _t->on_zSubBtn_released(); break;
        case 28: _t->on_rAddBtn_pressed(); break;
        case 29: _t->on_rAddBtn_released(); break;
        case 30: _t->on_rSubBtn_pressed(); break;
        case 31: _t->on_rSubBtn_released(); break;
        case 32: _t->on_alarmResetBtn_clicked(); break;
        case 33: _t->onBackOriginBtn_clicked(); break;
        case 34: _t->runTargetPosition((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        case 35: { bool _r = _t->modbusState();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 36: _t->performTasks(); break;
        case 37: _t->on_setLimitBtn_clicked(); break;
        case 38: _t->on_setMachineBtn_clicked(); break;
        case 39: _t->setXAxisVelocity((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 40: _t->setYAxisVelocity((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 41: _t->setJogVelocity((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 42: _t->writeRegisterGroup((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QVector<modelDate>(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 43: _t->writeAc700PointRegisterGroup((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QVector<modelDate>(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 44: _t->ZdetectHight((*reinterpret_cast< float(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject scanDetect_frictionWelding::staticMetaObject = { {
    QMetaObject::SuperData::link<ScanControlAbstract::staticMetaObject>(),
    qt_meta_stringdata_scanDetect_frictionWelding.data,
    qt_meta_data_scanDetect_frictionWelding,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *scanDetect_frictionWelding::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *scanDetect_frictionWelding::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_scanDetect_frictionWelding.stringdata0))
        return static_cast<void*>(this);
    return ScanControlAbstract::qt_metacast(_clname);
}

int scanDetect_frictionWelding::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ScanControlAbstract::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 45)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 45;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 45)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 45;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
