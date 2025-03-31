/****************************************************************************
** Meta object code from reading C++ file 'scandetect_frictionwelding.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../scanMovecontrl/scandetect_frictionwelding.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scandetect_frictionwelding.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_scanDetect_frictionWelding_t {
    QByteArrayData data[44];
    char stringdata0[780];
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
QT_MOC_LITERAL(8, 132, 23), // "on_setOriginBtn_clicked"
QT_MOC_LITERAL(9, 156, 1), // "x"
QT_MOC_LITERAL(10, 158, 1), // "y"
QT_MOC_LITERAL(11, 160, 10), // "isCurrPosi"
QT_MOC_LITERAL(12, 171, 32), // "on_line_velocity_editingFinished"
QT_MOC_LITERAL(13, 204, 3), // "val"
QT_MOC_LITERAL(14, 208, 31), // "on_arc_velocity_editingFinished"
QT_MOC_LITERAL(15, 240, 31), // "on_jog_velocity_editingFinished"
QT_MOC_LITERAL(16, 272, 18), // "on_xAddBtn_clicked"
QT_MOC_LITERAL(17, 291, 18), // "on_xSubBtn_clicked"
QT_MOC_LITERAL(18, 310, 18), // "on_yAddBtn_clicked"
QT_MOC_LITERAL(19, 329, 18), // "on_ySubBtn_clicked"
QT_MOC_LITERAL(20, 348, 18), // "on_xAddBtn_pressed"
QT_MOC_LITERAL(21, 367, 19), // "on_xAddBtn_released"
QT_MOC_LITERAL(22, 387, 18), // "on_xSubBtn_pressed"
QT_MOC_LITERAL(23, 406, 19), // "on_xSubBtn_released"
QT_MOC_LITERAL(24, 426, 18), // "on_yAddBtn_pressed"
QT_MOC_LITERAL(25, 445, 19), // "on_yAddBtn_released"
QT_MOC_LITERAL(26, 465, 18), // "on_ySubBtn_pressed"
QT_MOC_LITERAL(27, 484, 19), // "on_ySubBtn_released"
QT_MOC_LITERAL(28, 504, 18), // "on_zAddBtn_pressed"
QT_MOC_LITERAL(29, 523, 19), // "on_zAddBtn_released"
QT_MOC_LITERAL(30, 543, 18), // "on_zSubBtn_pressed"
QT_MOC_LITERAL(31, 562, 19), // "on_zSubBtn_released"
QT_MOC_LITERAL(32, 582, 18), // "on_rAddBtn_pressed"
QT_MOC_LITERAL(33, 601, 19), // "on_rAddBtn_released"
QT_MOC_LITERAL(34, 621, 18), // "on_rSubBtn_pressed"
QT_MOC_LITERAL(35, 640, 19), // "on_rSubBtn_released"
QT_MOC_LITERAL(36, 660, 24), // "on_alarmResetBtn_clicked"
QT_MOC_LITERAL(37, 685, 22), // "on_setLimitBtn_clicked"
QT_MOC_LITERAL(38, 708, 24), // "on_setMachineBtn_clicked"
QT_MOC_LITERAL(39, 733, 17), // "runTargetPosition"
QT_MOC_LITERAL(40, 751, 1), // "z"
QT_MOC_LITERAL(41, 753, 1), // "r"
QT_MOC_LITERAL(42, 755, 11), // "modbusState"
QT_MOC_LITERAL(43, 767, 12) // "performTasks"

    },
    "scanDetect_frictionWelding\0init\0\0"
    "destroy\0on_connectBtn_clicked\0"
    "on_startScanBtn_clicked\0on_stopScanBtn_clicked\0"
    "on_endScanBtn_clicked\0on_setOriginBtn_clicked\0"
    "x\0y\0isCurrPosi\0on_line_velocity_editingFinished\0"
    "val\0on_arc_velocity_editingFinished\0"
    "on_jog_velocity_editingFinished\0"
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
    "performTasks"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_scanDetect_frictionWelding[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      36,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  194,    2, 0x0a /* Public */,
       3,    0,  195,    2, 0x0a /* Public */,
       4,    0,  196,    2, 0x0a /* Public */,
       5,    0,  197,    2, 0x0a /* Public */,
       6,    0,  198,    2, 0x0a /* Public */,
       7,    0,  199,    2, 0x0a /* Public */,
       8,    3,  200,    2, 0x0a /* Public */,
      12,    1,  207,    2, 0x0a /* Public */,
      14,    1,  210,    2, 0x0a /* Public */,
      15,    1,  213,    2, 0x0a /* Public */,
      16,    0,  216,    2, 0x0a /* Public */,
      17,    0,  217,    2, 0x0a /* Public */,
      18,    0,  218,    2, 0x0a /* Public */,
      19,    0,  219,    2, 0x0a /* Public */,
      20,    0,  220,    2, 0x0a /* Public */,
      21,    0,  221,    2, 0x0a /* Public */,
      22,    0,  222,    2, 0x0a /* Public */,
      23,    0,  223,    2, 0x0a /* Public */,
      24,    0,  224,    2, 0x0a /* Public */,
      25,    0,  225,    2, 0x0a /* Public */,
      26,    0,  226,    2, 0x0a /* Public */,
      27,    0,  227,    2, 0x0a /* Public */,
      28,    0,  228,    2, 0x0a /* Public */,
      29,    0,  229,    2, 0x0a /* Public */,
      30,    0,  230,    2, 0x0a /* Public */,
      31,    0,  231,    2, 0x0a /* Public */,
      32,    0,  232,    2, 0x0a /* Public */,
      33,    0,  233,    2, 0x0a /* Public */,
      34,    0,  234,    2, 0x0a /* Public */,
      35,    0,  235,    2, 0x0a /* Public */,
      36,    0,  236,    2, 0x0a /* Public */,
      37,    0,  237,    2, 0x0a /* Public */,
      38,    0,  238,    2, 0x0a /* Public */,
      39,    4,  239,    2, 0x0a /* Public */,
      42,    0,  248,    2, 0x08 /* Private */,
      43,    0,  249,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Float, QMetaType::Float, QMetaType::Bool,    9,   10,   11,
    QMetaType::Void, QMetaType::Float,   13,
    QMetaType::Void, QMetaType::Float,   13,
    QMetaType::Void, QMetaType::Float,   13,
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
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double,    9,   10,   40,   41,
    QMetaType::Bool,
    QMetaType::Void,

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
        case 6: _t->on_setOriginBtn_clicked((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 7: _t->on_line_velocity_editingFinished((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 8: _t->on_arc_velocity_editingFinished((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 9: _t->on_jog_velocity_editingFinished((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 10: _t->on_xAddBtn_clicked(); break;
        case 11: _t->on_xSubBtn_clicked(); break;
        case 12: _t->on_yAddBtn_clicked(); break;
        case 13: _t->on_ySubBtn_clicked(); break;
        case 14: _t->on_xAddBtn_pressed(); break;
        case 15: _t->on_xAddBtn_released(); break;
        case 16: _t->on_xSubBtn_pressed(); break;
        case 17: _t->on_xSubBtn_released(); break;
        case 18: _t->on_yAddBtn_pressed(); break;
        case 19: _t->on_yAddBtn_released(); break;
        case 20: _t->on_ySubBtn_pressed(); break;
        case 21: _t->on_ySubBtn_released(); break;
        case 22: _t->on_zAddBtn_pressed(); break;
        case 23: _t->on_zAddBtn_released(); break;
        case 24: _t->on_zSubBtn_pressed(); break;
        case 25: _t->on_zSubBtn_released(); break;
        case 26: _t->on_rAddBtn_pressed(); break;
        case 27: _t->on_rAddBtn_released(); break;
        case 28: _t->on_rSubBtn_pressed(); break;
        case 29: _t->on_rSubBtn_released(); break;
        case 30: _t->on_alarmResetBtn_clicked(); break;
        case 31: _t->on_setLimitBtn_clicked(); break;
        case 32: _t->on_setMachineBtn_clicked(); break;
        case 33: _t->runTargetPosition((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        case 34: { bool _r = _t->modbusState();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 35: _t->performTasks(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject scanDetect_frictionWelding::staticMetaObject = { {
    &ScanControlAbstract::staticMetaObject,
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
        if (_id < 36)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 36;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 36)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 36;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
