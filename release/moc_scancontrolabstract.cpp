/****************************************************************************
** Meta object code from reading C++ file 'scancontrolabstract.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../scanMovecontrl/scancontrolabstract.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scancontrolabstract.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ScanControlAbstract_t {
    QByteArrayData data[66];
    char stringdata0[1059];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ScanControlAbstract_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ScanControlAbstract_t qt_meta_stringdata_ScanControlAbstract = {
    {
QT_MOC_LITERAL(0, 0, 19), // "ScanControlAbstract"
QT_MOC_LITERAL(1, 20, 17), // "modbusStateChange"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 20), // "QModbusDevice::State"
QT_MOC_LITERAL(4, 60, 14), // "positionChange"
QT_MOC_LITERAL(5, 75, 5), // "cur_r"
QT_MOC_LITERAL(6, 81, 5), // "cur_z"
QT_MOC_LITERAL(7, 87, 14), // "velocityChange"
QT_MOC_LITERAL(8, 102, 1), // "x"
QT_MOC_LITERAL(9, 104, 1), // "y"
QT_MOC_LITERAL(10, 106, 3), // "jog"
QT_MOC_LITERAL(11, 110, 9), // "axisError"
QT_MOC_LITERAL(12, 120, 8), // "xErrorId"
QT_MOC_LITERAL(13, 129, 8), // "yErrorId"
QT_MOC_LITERAL(14, 138, 12), // "machineStart"
QT_MOC_LITERAL(15, 151, 11), // "machineStop"
QT_MOC_LITERAL(16, 163, 16), // "scanRowNumChange"
QT_MOC_LITERAL(17, 180, 3), // "num"
QT_MOC_LITERAL(18, 184, 10), // "scanRowEnd"
QT_MOC_LITERAL(19, 195, 9), // "AxisState"
QT_MOC_LITERAL(20, 205, 8), // "scanTime"
QT_MOC_LITERAL(21, 214, 2), // "ms"
QT_MOC_LITERAL(22, 217, 4), // "init"
QT_MOC_LITERAL(23, 222, 7), // "destroy"
QT_MOC_LITERAL(24, 230, 21), // "on_connectBtn_clicked"
QT_MOC_LITERAL(25, 252, 23), // "on_startScanBtn_clicked"
QT_MOC_LITERAL(26, 276, 22), // "on_stopScanBtn_clicked"
QT_MOC_LITERAL(27, 299, 21), // "on_endScanBtn_clicked"
QT_MOC_LITERAL(28, 321, 27), // "on_aganStartScanBtn_clicked"
QT_MOC_LITERAL(29, 349, 23), // "on_setOriginBtn_clicked"
QT_MOC_LITERAL(30, 373, 8), // "axitType"
QT_MOC_LITERAL(31, 382, 23), // "onBackOriginBtn_clicked"
QT_MOC_LITERAL(32, 406, 32), // "on_line_velocity_editingFinished"
QT_MOC_LITERAL(33, 439, 3), // "val"
QT_MOC_LITERAL(34, 443, 31), // "on_arc_velocity_editingFinished"
QT_MOC_LITERAL(35, 475, 31), // "on_jog_velocity_editingFinished"
QT_MOC_LITERAL(36, 507, 33), // "on_point_velocity_editingFini..."
QT_MOC_LITERAL(37, 541, 18), // "on_xAddBtn_clicked"
QT_MOC_LITERAL(38, 560, 18), // "on_xSubBtn_clicked"
QT_MOC_LITERAL(39, 579, 18), // "on_yAddBtn_clicked"
QT_MOC_LITERAL(40, 598, 18), // "on_ySubBtn_clicked"
QT_MOC_LITERAL(41, 617, 18), // "on_xAddBtn_pressed"
QT_MOC_LITERAL(42, 636, 19), // "on_xAddBtn_released"
QT_MOC_LITERAL(43, 656, 18), // "on_xSubBtn_pressed"
QT_MOC_LITERAL(44, 675, 19), // "on_xSubBtn_released"
QT_MOC_LITERAL(45, 695, 18), // "on_yAddBtn_pressed"
QT_MOC_LITERAL(46, 714, 19), // "on_yAddBtn_released"
QT_MOC_LITERAL(47, 734, 18), // "on_ySubBtn_pressed"
QT_MOC_LITERAL(48, 753, 19), // "on_ySubBtn_released"
QT_MOC_LITERAL(49, 773, 18), // "on_zAddBtn_pressed"
QT_MOC_LITERAL(50, 792, 19), // "on_zAddBtn_released"
QT_MOC_LITERAL(51, 812, 18), // "on_zSubBtn_pressed"
QT_MOC_LITERAL(52, 831, 19), // "on_zSubBtn_released"
QT_MOC_LITERAL(53, 851, 18), // "on_rAddBtn_pressed"
QT_MOC_LITERAL(54, 870, 19), // "on_rAddBtn_released"
QT_MOC_LITERAL(55, 890, 18), // "on_rSubBtn_pressed"
QT_MOC_LITERAL(56, 909, 19), // "on_rSubBtn_released"
QT_MOC_LITERAL(57, 929, 24), // "on_alarmResetBtn_clicked"
QT_MOC_LITERAL(58, 954, 22), // "on_setLimitBtn_clicked"
QT_MOC_LITERAL(59, 977, 24), // "on_setMachineBtn_clicked"
QT_MOC_LITERAL(60, 1002, 17), // "runTargetPosition"
QT_MOC_LITERAL(61, 1020, 1), // "z"
QT_MOC_LITERAL(62, 1022, 1), // "r"
QT_MOC_LITERAL(63, 1024, 11), // "modbusState"
QT_MOC_LITERAL(64, 1036, 17), // "selectProcessType"
QT_MOC_LITERAL(65, 1054, 4) // "type"

    },
    "ScanControlAbstract\0modbusStateChange\0"
    "\0QModbusDevice::State\0positionChange\0"
    "cur_r\0cur_z\0velocityChange\0x\0y\0jog\0"
    "axisError\0xErrorId\0yErrorId\0machineStart\0"
    "machineStop\0scanRowNumChange\0num\0"
    "scanRowEnd\0AxisState\0scanTime\0ms\0init\0"
    "destroy\0on_connectBtn_clicked\0"
    "on_startScanBtn_clicked\0on_stopScanBtn_clicked\0"
    "on_endScanBtn_clicked\0on_aganStartScanBtn_clicked\0"
    "on_setOriginBtn_clicked\0axitType\0"
    "onBackOriginBtn_clicked\0"
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
    "on_setLimitBtn_clicked\0on_setMachineBtn_clicked\0"
    "runTargetPosition\0z\0r\0modbusState\0"
    "selectProcessType\0type"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ScanControlAbstract[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      48,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  254,    2, 0x06 /* Public */,
       4,    3,  257,    2, 0x06 /* Public */,
       7,    3,  264,    2, 0x06 /* Public */,
      11,    2,  271,    2, 0x06 /* Public */,
      14,    0,  276,    2, 0x06 /* Public */,
      15,    0,  277,    2, 0x06 /* Public */,
      16,    1,  278,    2, 0x06 /* Public */,
      18,    1,  281,    2, 0x06 /* Public */,
      20,    1,  284,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      22,    0,  287,    2, 0x0a /* Public */,
      23,    0,  288,    2, 0x0a /* Public */,
      24,    0,  289,    2, 0x0a /* Public */,
      25,    0,  290,    2, 0x0a /* Public */,
      26,    0,  291,    2, 0x0a /* Public */,
      27,    0,  292,    2, 0x0a /* Public */,
      28,    0,  293,    2, 0x0a /* Public */,
      29,    1,  294,    2, 0x0a /* Public */,
      31,    0,  297,    2, 0x0a /* Public */,
      32,    1,  298,    2, 0x0a /* Public */,
      34,    1,  301,    2, 0x0a /* Public */,
      35,    1,  304,    2, 0x0a /* Public */,
      36,    1,  307,    2, 0x0a /* Public */,
      37,    0,  310,    2, 0x0a /* Public */,
      38,    0,  311,    2, 0x0a /* Public */,
      39,    0,  312,    2, 0x0a /* Public */,
      40,    0,  313,    2, 0x0a /* Public */,
      41,    0,  314,    2, 0x0a /* Public */,
      42,    0,  315,    2, 0x0a /* Public */,
      43,    0,  316,    2, 0x0a /* Public */,
      44,    0,  317,    2, 0x0a /* Public */,
      45,    0,  318,    2, 0x0a /* Public */,
      46,    0,  319,    2, 0x0a /* Public */,
      47,    0,  320,    2, 0x0a /* Public */,
      48,    0,  321,    2, 0x0a /* Public */,
      49,    0,  322,    2, 0x0a /* Public */,
      50,    0,  323,    2, 0x0a /* Public */,
      51,    0,  324,    2, 0x0a /* Public */,
      52,    0,  325,    2, 0x0a /* Public */,
      53,    0,  326,    2, 0x0a /* Public */,
      54,    0,  327,    2, 0x0a /* Public */,
      55,    0,  328,    2, 0x0a /* Public */,
      56,    0,  329,    2, 0x0a /* Public */,
      57,    0,  330,    2, 0x0a /* Public */,
      58,    0,  331,    2, 0x0a /* Public */,
      59,    0,  332,    2, 0x0a /* Public */,
      60,    4,  333,    2, 0x0a /* Public */,
      63,    0,  342,    2, 0x0a /* Public */,
      64,    1,  343,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::QPointF, QMetaType::Float, QMetaType::Float,    2,    5,    6,
    QMetaType::Void, QMetaType::Float, QMetaType::Float, QMetaType::Float,    8,    9,   10,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   12,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void, 0x80000000 | 19,    2,
    QMetaType::Void, QMetaType::QString,   21,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   30,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Float,   33,
    QMetaType::Void, QMetaType::Float,   33,
    QMetaType::Void, QMetaType::Float,   33,
    QMetaType::Void, QMetaType::Float,   33,
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
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double,    8,    9,   61,   62,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int,   65,

       0        // eod
};

void ScanControlAbstract::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ScanControlAbstract *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->modbusStateChange((*reinterpret_cast< QModbusDevice::State(*)>(_a[1]))); break;
        case 1: _t->positionChange((*reinterpret_cast< QPointF(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 2: _t->velocityChange((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 3: _t->axisError((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->machineStart(); break;
        case 5: _t->machineStop(); break;
        case 6: _t->scanRowNumChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->scanRowEnd((*reinterpret_cast< AxisState(*)>(_a[1]))); break;
        case 8: _t->scanTime((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->init(); break;
        case 10: _t->destroy(); break;
        case 11: _t->on_connectBtn_clicked(); break;
        case 12: _t->on_startScanBtn_clicked(); break;
        case 13: _t->on_stopScanBtn_clicked(); break;
        case 14: _t->on_endScanBtn_clicked(); break;
        case 15: _t->on_aganStartScanBtn_clicked(); break;
        case 16: _t->on_setOriginBtn_clicked((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 17: _t->onBackOriginBtn_clicked(); break;
        case 18: _t->on_line_velocity_editingFinished((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 19: _t->on_arc_velocity_editingFinished((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 20: _t->on_jog_velocity_editingFinished((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 21: _t->on_point_velocity_editingFinished((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 22: _t->on_xAddBtn_clicked(); break;
        case 23: _t->on_xSubBtn_clicked(); break;
        case 24: _t->on_yAddBtn_clicked(); break;
        case 25: _t->on_ySubBtn_clicked(); break;
        case 26: _t->on_xAddBtn_pressed(); break;
        case 27: _t->on_xAddBtn_released(); break;
        case 28: _t->on_xSubBtn_pressed(); break;
        case 29: _t->on_xSubBtn_released(); break;
        case 30: _t->on_yAddBtn_pressed(); break;
        case 31: _t->on_yAddBtn_released(); break;
        case 32: _t->on_ySubBtn_pressed(); break;
        case 33: _t->on_ySubBtn_released(); break;
        case 34: _t->on_zAddBtn_pressed(); break;
        case 35: _t->on_zAddBtn_released(); break;
        case 36: _t->on_zSubBtn_pressed(); break;
        case 37: _t->on_zSubBtn_released(); break;
        case 38: _t->on_rAddBtn_pressed(); break;
        case 39: _t->on_rAddBtn_released(); break;
        case 40: _t->on_rSubBtn_pressed(); break;
        case 41: _t->on_rSubBtn_released(); break;
        case 42: _t->on_alarmResetBtn_clicked(); break;
        case 43: _t->on_setLimitBtn_clicked(); break;
        case 44: _t->on_setMachineBtn_clicked(); break;
        case 45: _t->runTargetPosition((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        case 46: { bool _r = _t->modbusState();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 47: _t->selectProcessType((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ScanControlAbstract::*)(QModbusDevice::State );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ScanControlAbstract::modbusStateChange)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ScanControlAbstract::*)(QPointF , float , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ScanControlAbstract::positionChange)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ScanControlAbstract::*)(float , float , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ScanControlAbstract::velocityChange)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ScanControlAbstract::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ScanControlAbstract::axisError)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ScanControlAbstract::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ScanControlAbstract::machineStart)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ScanControlAbstract::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ScanControlAbstract::machineStop)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (ScanControlAbstract::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ScanControlAbstract::scanRowNumChange)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (ScanControlAbstract::*)(AxisState );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ScanControlAbstract::scanRowEnd)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (ScanControlAbstract::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ScanControlAbstract::scanTime)) {
                *result = 8;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ScanControlAbstract::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_ScanControlAbstract.data,
    qt_meta_data_ScanControlAbstract,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ScanControlAbstract::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ScanControlAbstract::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ScanControlAbstract.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ScanControlAbstract::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 48)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 48;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 48)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 48;
    }
    return _id;
}

// SIGNAL 0
void ScanControlAbstract::modbusStateChange(QModbusDevice::State _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ScanControlAbstract::positionChange(QPointF _t1, float _t2, float _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ScanControlAbstract::velocityChange(float _t1, float _t2, float _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ScanControlAbstract::axisError(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ScanControlAbstract::machineStart()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void ScanControlAbstract::machineStop()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void ScanControlAbstract::scanRowNumChange(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void ScanControlAbstract::scanRowEnd(AxisState _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void ScanControlAbstract::scanTime(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
