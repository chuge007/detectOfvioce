/****************************************************************************
** Meta object code from reading C++ file 'MotionControl.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../MotionControl.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MotionControl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MotionControl_t {
    QByteArrayData data[62];
    char stringdata0[978];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MotionControl_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MotionControl_t qt_meta_stringdata_MotionControl = {
    {
QT_MOC_LITERAL(0, 0, 13), // "MotionControl"
QT_MOC_LITERAL(1, 14, 26), // "x_velocity_editingFinished"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 3), // "arg"
QT_MOC_LITERAL(4, 46, 26), // "y_velocity_editingFinished"
QT_MOC_LITERAL(5, 73, 28), // "jog_velocity_editingFinished"
QT_MOC_LITERAL(6, 102, 24), // "x_lenght_editingFinished"
QT_MOC_LITERAL(7, 127, 24), // "y_lenght_editingFinished"
QT_MOC_LITERAL(8, 152, 22), // "y_step_editingFinished"
QT_MOC_LITERAL(9, 175, 35), // "backOrigin_velocity_editingFi..."
QT_MOC_LITERAL(10, 211, 29), // "scan_velocity_editingFinished"
QT_MOC_LITERAL(11, 241, 36), // "jog_add_sub_velocity_editingF..."
QT_MOC_LITERAL(12, 278, 12), // "movePosition"
QT_MOC_LITERAL(13, 291, 1), // "x"
QT_MOC_LITERAL(14, 293, 1), // "y"
QT_MOC_LITERAL(15, 295, 13), // "targetReached"
QT_MOC_LITERAL(16, 309, 14), // "pbStartScanBtn"
QT_MOC_LITERAL(17, 324, 17), // "modbusStateChange"
QT_MOC_LITERAL(18, 342, 20), // "QModbusDevice::State"
QT_MOC_LITERAL(19, 363, 5), // "state"
QT_MOC_LITERAL(20, 369, 15), // "pbAddElliptical"
QT_MOC_LITERAL(21, 385, 14), // "updatePosition"
QT_MOC_LITERAL(22, 400, 3), // "pos"
QT_MOC_LITERAL(23, 404, 5), // "cur_r"
QT_MOC_LITERAL(24, 410, 5), // "cur_z"
QT_MOC_LITERAL(25, 416, 11), // "pbAddSpline"
QT_MOC_LITERAL(26, 428, 21), // "on_delete_but_clicked"
QT_MOC_LITERAL(27, 450, 22), // "on_editPos_but_clicked"
QT_MOC_LITERAL(28, 473, 12), // "pbWriteInPLC"
QT_MOC_LITERAL(29, 486, 11), // "pbAddArcPos"
QT_MOC_LITERAL(30, 498, 12), // "pbAddLinePos"
QT_MOC_LITERAL(31, 511, 14), // "pbDXFimportBut"
QT_MOC_LITERAL(32, 526, 25), // "pbsetTrajec_start_clicked"
QT_MOC_LITERAL(33, 552, 12), // "PbCreatGcode"
QT_MOC_LITERAL(34, 565, 17), // "CalculatingAngles"
QT_MOC_LITERAL(35, 583, 14), // "PbImageProcess"
QT_MOC_LITERAL(36, 598, 11), // "PbSetOrigin"
QT_MOC_LITERAL(37, 610, 16), // "PbMoveToPosition"
QT_MOC_LITERAL(38, 627, 18), // "PbtrajectoryOffset"
QT_MOC_LITERAL(39, 646, 13), // "PbsmoothCurve"
QT_MOC_LITERAL(40, 660, 18), // "PbAxleVelocity_lin"
QT_MOC_LITERAL(41, 679, 17), // "PblinVelocity_lin"
QT_MOC_LITERAL(42, 697, 17), // "PbarcVelocity_lin"
QT_MOC_LITERAL(43, 715, 19), // "PbPointVelocity_lin"
QT_MOC_LITERAL(44, 735, 7), // "pbAscan"
QT_MOC_LITERAL(45, 743, 11), // "updateSence"
QT_MOC_LITERAL(46, 755, 10), // "cleanTable"
QT_MOC_LITERAL(47, 766, 18), // "PbModbusConnectBtn"
QT_MOC_LITERAL(48, 785, 15), // "cbSelectPlcType"
QT_MOC_LITERAL(49, 801, 5), // "index"
QT_MOC_LITERAL(50, 807, 15), // "pbmoveUpForSort"
QT_MOC_LITERAL(51, 823, 17), // "pbmoveDownForSort"
QT_MOC_LITERAL(52, 841, 13), // "sortModelLine"
QT_MOC_LITERAL(53, 855, 15), // "pbGetModelPoint"
QT_MOC_LITERAL(54, 871, 18), // "pbMoveDirectionNot"
QT_MOC_LITERAL(55, 890, 9), // "pBbrazing"
QT_MOC_LITERAL(56, 900, 15), // "selectWorkpiece"
QT_MOC_LITERAL(57, 916, 12), // "selectChange"
QT_MOC_LITERAL(58, 929, 13), // "pbdeletePiece"
QT_MOC_LITERAL(59, 943, 10), // "pbnewPiece"
QT_MOC_LITERAL(60, 954, 11), // "saveSetting"
QT_MOC_LITERAL(61, 966, 11) // "initSetting"

    },
    "MotionControl\0x_velocity_editingFinished\0"
    "\0arg\0y_velocity_editingFinished\0"
    "jog_velocity_editingFinished\0"
    "x_lenght_editingFinished\0"
    "y_lenght_editingFinished\0"
    "y_step_editingFinished\0"
    "backOrigin_velocity_editingFinished\0"
    "scan_velocity_editingFinished\0"
    "jog_add_sub_velocity_editingFinished\0"
    "movePosition\0x\0y\0targetReached\0"
    "pbStartScanBtn\0modbusStateChange\0"
    "QModbusDevice::State\0state\0pbAddElliptical\0"
    "updatePosition\0pos\0cur_r\0cur_z\0"
    "pbAddSpline\0on_delete_but_clicked\0"
    "on_editPos_but_clicked\0pbWriteInPLC\0"
    "pbAddArcPos\0pbAddLinePos\0pbDXFimportBut\0"
    "pbsetTrajec_start_clicked\0PbCreatGcode\0"
    "CalculatingAngles\0PbImageProcess\0"
    "PbSetOrigin\0PbMoveToPosition\0"
    "PbtrajectoryOffset\0PbsmoothCurve\0"
    "PbAxleVelocity_lin\0PblinVelocity_lin\0"
    "PbarcVelocity_lin\0PbPointVelocity_lin\0"
    "pbAscan\0updateSence\0cleanTable\0"
    "PbModbusConnectBtn\0cbSelectPlcType\0"
    "index\0pbmoveUpForSort\0pbmoveDownForSort\0"
    "sortModelLine\0pbGetModelPoint\0"
    "pbMoveDirectionNot\0pBbrazing\0"
    "selectWorkpiece\0selectChange\0pbdeletePiece\0"
    "pbnewPiece\0saveSetting\0initSetting"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MotionControl[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      51,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  269,    2, 0x06 /* Public */,
       4,    1,  272,    2, 0x06 /* Public */,
       5,    1,  275,    2, 0x06 /* Public */,
       6,    1,  278,    2, 0x06 /* Public */,
       7,    1,  281,    2, 0x06 /* Public */,
       8,    1,  284,    2, 0x06 /* Public */,
       9,    1,  287,    2, 0x06 /* Public */,
      10,    1,  290,    2, 0x06 /* Public */,
      11,    1,  293,    2, 0x06 /* Public */,
      12,    2,  296,    2, 0x06 /* Public */,
      15,    0,  301,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      16,    0,  302,    2, 0x08 /* Private */,
      17,    1,  303,    2, 0x08 /* Private */,
      20,    0,  306,    2, 0x08 /* Private */,
      21,    3,  307,    2, 0x08 /* Private */,
      25,    0,  314,    2, 0x08 /* Private */,
      26,    0,  315,    2, 0x08 /* Private */,
      27,    0,  316,    2, 0x08 /* Private */,
      28,    0,  317,    2, 0x08 /* Private */,
      29,    0,  318,    2, 0x08 /* Private */,
      30,    0,  319,    2, 0x08 /* Private */,
      31,    0,  320,    2, 0x08 /* Private */,
      32,    0,  321,    2, 0x08 /* Private */,
      33,    0,  322,    2, 0x08 /* Private */,
      34,    0,  323,    2, 0x08 /* Private */,
      35,    0,  324,    2, 0x08 /* Private */,
      36,    0,  325,    2, 0x08 /* Private */,
      37,    0,  326,    2, 0x08 /* Private */,
      38,    0,  327,    2, 0x08 /* Private */,
      39,    0,  328,    2, 0x08 /* Private */,
      40,    0,  329,    2, 0x08 /* Private */,
      41,    0,  330,    2, 0x08 /* Private */,
      42,    0,  331,    2, 0x08 /* Private */,
      43,    0,  332,    2, 0x08 /* Private */,
      44,    0,  333,    2, 0x08 /* Private */,
      45,    0,  334,    2, 0x08 /* Private */,
      46,    0,  335,    2, 0x08 /* Private */,
      47,    0,  336,    2, 0x08 /* Private */,
      48,    1,  337,    2, 0x08 /* Private */,
      50,    0,  340,    2, 0x08 /* Private */,
      51,    0,  341,    2, 0x08 /* Private */,
      52,    0,  342,    2, 0x08 /* Private */,
      53,    0,  343,    2, 0x08 /* Private */,
      54,    0,  344,    2, 0x08 /* Private */,
      55,    0,  345,    2, 0x08 /* Private */,
      56,    0,  346,    2, 0x08 /* Private */,
      57,    0,  347,    2, 0x08 /* Private */,
      58,    0,  348,    2, 0x08 /* Private */,
      59,    0,  349,    2, 0x08 /* Private */,
      60,    0,  350,    2, 0x08 /* Private */,
      61,    0,  351,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,   13,   14,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPointF, QMetaType::Float, QMetaType::Float,   22,   23,   24,
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
    QMetaType::Void, QMetaType::Int,   49,
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

       0        // eod
};

void MotionControl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MotionControl *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->x_velocity_editingFinished((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 1: _t->y_velocity_editingFinished((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->jog_velocity_editingFinished((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->x_lenght_editingFinished((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 4: _t->y_lenght_editingFinished((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 5: _t->y_step_editingFinished((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 6: _t->backOrigin_velocity_editingFinished((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 7: _t->scan_velocity_editingFinished((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 8: _t->jog_add_sub_velocity_editingFinished((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 9: _t->movePosition((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 10: _t->targetReached(); break;
        case 11: _t->pbStartScanBtn(); break;
        case 12: _t->modbusStateChange((*reinterpret_cast< QModbusDevice::State(*)>(_a[1]))); break;
        case 13: _t->pbAddElliptical(); break;
        case 14: _t->updatePosition((*reinterpret_cast< QPointF(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 15: _t->pbAddSpline(); break;
        case 16: _t->on_delete_but_clicked(); break;
        case 17: _t->on_editPos_but_clicked(); break;
        case 18: _t->pbWriteInPLC(); break;
        case 19: _t->pbAddArcPos(); break;
        case 20: _t->pbAddLinePos(); break;
        case 21: _t->pbDXFimportBut(); break;
        case 22: _t->pbsetTrajec_start_clicked(); break;
        case 23: _t->PbCreatGcode(); break;
        case 24: _t->CalculatingAngles(); break;
        case 25: _t->PbImageProcess(); break;
        case 26: _t->PbSetOrigin(); break;
        case 27: _t->PbMoveToPosition(); break;
        case 28: _t->PbtrajectoryOffset(); break;
        case 29: _t->PbsmoothCurve(); break;
        case 30: _t->PbAxleVelocity_lin(); break;
        case 31: _t->PblinVelocity_lin(); break;
        case 32: _t->PbarcVelocity_lin(); break;
        case 33: _t->PbPointVelocity_lin(); break;
        case 34: _t->pbAscan(); break;
        case 35: _t->updateSence(); break;
        case 36: _t->cleanTable(); break;
        case 37: _t->PbModbusConnectBtn(); break;
        case 38: _t->cbSelectPlcType((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 39: _t->pbmoveUpForSort(); break;
        case 40: _t->pbmoveDownForSort(); break;
        case 41: _t->sortModelLine(); break;
        case 42: _t->pbGetModelPoint(); break;
        case 43: _t->pbMoveDirectionNot(); break;
        case 44: _t->pBbrazing(); break;
        case 45: _t->selectWorkpiece(); break;
        case 46: _t->selectChange(); break;
        case 47: _t->pbdeletePiece(); break;
        case 48: _t->pbnewPiece(); break;
        case 49: _t->saveSetting(); break;
        case 50: _t->initSetting(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MotionControl::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MotionControl::x_velocity_editingFinished)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MotionControl::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MotionControl::y_velocity_editingFinished)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MotionControl::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MotionControl::jog_velocity_editingFinished)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MotionControl::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MotionControl::x_lenght_editingFinished)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MotionControl::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MotionControl::y_lenght_editingFinished)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (MotionControl::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MotionControl::y_step_editingFinished)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (MotionControl::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MotionControl::backOrigin_velocity_editingFinished)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (MotionControl::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MotionControl::scan_velocity_editingFinished)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (MotionControl::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MotionControl::jog_add_sub_velocity_editingFinished)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (MotionControl::*)(double , double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MotionControl::movePosition)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (MotionControl::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MotionControl::targetReached)) {
                *result = 10;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MotionControl::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MotionControl.data,
    qt_meta_data_MotionControl,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MotionControl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MotionControl::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MotionControl.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MotionControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 51)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 51;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 51)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 51;
    }
    return _id;
}

// SIGNAL 0
void MotionControl::x_velocity_editingFinished(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MotionControl::y_velocity_editingFinished(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MotionControl::jog_velocity_editingFinished(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MotionControl::x_lenght_editingFinished(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MotionControl::y_lenght_editingFinished(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MotionControl::y_step_editingFinished(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void MotionControl::backOrigin_velocity_editingFinished(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void MotionControl::scan_velocity_editingFinished(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void MotionControl::jog_add_sub_velocity_editingFinished(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void MotionControl::movePosition(double _t1, double _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void MotionControl::targetReached()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
