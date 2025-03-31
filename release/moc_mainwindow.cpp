/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[50];
    char stringdata0[793];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 26), // "x_velocity_editingFinished"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 3), // "arg"
QT_MOC_LITERAL(4, 43, 26), // "y_velocity_editingFinished"
QT_MOC_LITERAL(5, 70, 28), // "jog_velocity_editingFinished"
QT_MOC_LITERAL(6, 99, 24), // "x_lenght_editingFinished"
QT_MOC_LITERAL(7, 124, 24), // "y_lenght_editingFinished"
QT_MOC_LITERAL(8, 149, 22), // "y_step_editingFinished"
QT_MOC_LITERAL(9, 172, 35), // "backOrigin_velocity_editingFi..."
QT_MOC_LITERAL(10, 208, 29), // "scan_velocity_editingFinished"
QT_MOC_LITERAL(11, 238, 36), // "jog_add_sub_velocity_editingF..."
QT_MOC_LITERAL(12, 275, 12), // "movePosition"
QT_MOC_LITERAL(13, 288, 1), // "x"
QT_MOC_LITERAL(14, 290, 1), // "y"
QT_MOC_LITERAL(15, 292, 13), // "targetReached"
QT_MOC_LITERAL(16, 306, 17), // "modbusStateChange"
QT_MOC_LITERAL(17, 324, 20), // "QModbusDevice::State"
QT_MOC_LITERAL(18, 345, 5), // "state"
QT_MOC_LITERAL(19, 351, 15), // "pbAddElliptical"
QT_MOC_LITERAL(20, 367, 14), // "updatePosition"
QT_MOC_LITERAL(21, 382, 3), // "pos"
QT_MOC_LITERAL(22, 386, 5), // "cur_r"
QT_MOC_LITERAL(23, 392, 5), // "cur_z"
QT_MOC_LITERAL(24, 398, 11), // "pbAddSpline"
QT_MOC_LITERAL(25, 410, 21), // "on_delete_but_clicked"
QT_MOC_LITERAL(26, 432, 22), // "on_editPos_but_clicked"
QT_MOC_LITERAL(27, 455, 12), // "pbWriteInPLC"
QT_MOC_LITERAL(28, 468, 11), // "pbAddArcPos"
QT_MOC_LITERAL(29, 480, 12), // "pbAddLinePos"
QT_MOC_LITERAL(30, 493, 14), // "pbDXFimportBut"
QT_MOC_LITERAL(31, 508, 26), // "on_setTrajec_start_clicked"
QT_MOC_LITERAL(32, 535, 12), // "PbCreatGcode"
QT_MOC_LITERAL(33, 548, 14), // "PbImageProcess"
QT_MOC_LITERAL(34, 563, 11), // "PbSetOrigin"
QT_MOC_LITERAL(35, 575, 16), // "PbMoveToPosition"
QT_MOC_LITERAL(36, 592, 18), // "PbAxleVelocity_lin"
QT_MOC_LITERAL(37, 611, 17), // "PblinVelocity_lin"
QT_MOC_LITERAL(38, 629, 17), // "PbarcVelocity_lin"
QT_MOC_LITERAL(39, 647, 7), // "pbAscan"
QT_MOC_LITERAL(40, 655, 11), // "updateSence"
QT_MOC_LITERAL(41, 667, 10), // "cleanTable"
QT_MOC_LITERAL(42, 678, 18), // "PbModbusConnectBtn"
QT_MOC_LITERAL(43, 697, 15), // "cbSelectPlcType"
QT_MOC_LITERAL(44, 713, 5), // "index"
QT_MOC_LITERAL(45, 719, 15), // "pbmoveUpForSort"
QT_MOC_LITERAL(46, 735, 17), // "pbmoveDownForSort"
QT_MOC_LITERAL(47, 753, 15), // "pbGetCurryPoint"
QT_MOC_LITERAL(48, 769, 11), // "saveSetting"
QT_MOC_LITERAL(49, 781, 11) // "initSetting"

    },
    "MainWindow\0x_velocity_editingFinished\0"
    "\0arg\0y_velocity_editingFinished\0"
    "jog_velocity_editingFinished\0"
    "x_lenght_editingFinished\0"
    "y_lenght_editingFinished\0"
    "y_step_editingFinished\0"
    "backOrigin_velocity_editingFinished\0"
    "scan_velocity_editingFinished\0"
    "jog_add_sub_velocity_editingFinished\0"
    "movePosition\0x\0y\0targetReached\0"
    "modbusStateChange\0QModbusDevice::State\0"
    "state\0pbAddElliptical\0updatePosition\0"
    "pos\0cur_r\0cur_z\0pbAddSpline\0"
    "on_delete_but_clicked\0on_editPos_but_clicked\0"
    "pbWriteInPLC\0pbAddArcPos\0pbAddLinePos\0"
    "pbDXFimportBut\0on_setTrajec_start_clicked\0"
    "PbCreatGcode\0PbImageProcess\0PbSetOrigin\0"
    "PbMoveToPosition\0PbAxleVelocity_lin\0"
    "PblinVelocity_lin\0PbarcVelocity_lin\0"
    "pbAscan\0updateSence\0cleanTable\0"
    "PbModbusConnectBtn\0cbSelectPlcType\0"
    "index\0pbmoveUpForSort\0pbmoveDownForSort\0"
    "pbGetCurryPoint\0saveSetting\0initSetting"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      39,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  209,    2, 0x06 /* Public */,
       4,    1,  212,    2, 0x06 /* Public */,
       5,    1,  215,    2, 0x06 /* Public */,
       6,    1,  218,    2, 0x06 /* Public */,
       7,    1,  221,    2, 0x06 /* Public */,
       8,    1,  224,    2, 0x06 /* Public */,
       9,    1,  227,    2, 0x06 /* Public */,
      10,    1,  230,    2, 0x06 /* Public */,
      11,    1,  233,    2, 0x06 /* Public */,
      12,    2,  236,    2, 0x06 /* Public */,
      15,    0,  241,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      16,    1,  242,    2, 0x08 /* Private */,
      19,    0,  245,    2, 0x08 /* Private */,
      20,    3,  246,    2, 0x08 /* Private */,
      24,    0,  253,    2, 0x08 /* Private */,
      25,    0,  254,    2, 0x08 /* Private */,
      26,    0,  255,    2, 0x08 /* Private */,
      27,    0,  256,    2, 0x08 /* Private */,
      28,    0,  257,    2, 0x08 /* Private */,
      29,    0,  258,    2, 0x08 /* Private */,
      30,    0,  259,    2, 0x08 /* Private */,
      31,    0,  260,    2, 0x08 /* Private */,
      32,    0,  261,    2, 0x08 /* Private */,
      33,    0,  262,    2, 0x08 /* Private */,
      34,    0,  263,    2, 0x08 /* Private */,
      35,    0,  264,    2, 0x08 /* Private */,
      36,    0,  265,    2, 0x08 /* Private */,
      37,    0,  266,    2, 0x08 /* Private */,
      38,    0,  267,    2, 0x08 /* Private */,
      39,    0,  268,    2, 0x08 /* Private */,
      40,    0,  269,    2, 0x08 /* Private */,
      41,    0,  270,    2, 0x08 /* Private */,
      42,    0,  271,    2, 0x08 /* Private */,
      43,    1,  272,    2, 0x08 /* Private */,
      45,    0,  275,    2, 0x08 /* Private */,
      46,    0,  276,    2, 0x08 /* Private */,
      47,    0,  277,    2, 0x08 /* Private */,
      48,    0,  278,    2, 0x08 /* Private */,
      49,    0,  279,    2, 0x08 /* Private */,

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
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPointF, QMetaType::Float, QMetaType::Float,   21,   22,   23,
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
    QMetaType::Void, QMetaType::Int,   44,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
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
        case 11: _t->modbusStateChange((*reinterpret_cast< QModbusDevice::State(*)>(_a[1]))); break;
        case 12: _t->pbAddElliptical(); break;
        case 13: _t->updatePosition((*reinterpret_cast< QPointF(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 14: _t->pbAddSpline(); break;
        case 15: _t->on_delete_but_clicked(); break;
        case 16: _t->on_editPos_but_clicked(); break;
        case 17: _t->pbWriteInPLC(); break;
        case 18: _t->pbAddArcPos(); break;
        case 19: _t->pbAddLinePos(); break;
        case 20: _t->pbDXFimportBut(); break;
        case 21: _t->on_setTrajec_start_clicked(); break;
        case 22: _t->PbCreatGcode(); break;
        case 23: _t->PbImageProcess(); break;
        case 24: _t->PbSetOrigin(); break;
        case 25: _t->PbMoveToPosition(); break;
        case 26: _t->PbAxleVelocity_lin(); break;
        case 27: _t->PblinVelocity_lin(); break;
        case 28: _t->PbarcVelocity_lin(); break;
        case 29: _t->pbAscan(); break;
        case 30: _t->updateSence(); break;
        case 31: _t->cleanTable(); break;
        case 32: _t->PbModbusConnectBtn(); break;
        case 33: _t->cbSelectPlcType((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 34: _t->pbmoveUpForSort(); break;
        case 35: _t->pbmoveDownForSort(); break;
        case 36: _t->pbGetCurryPoint(); break;
        case 37: _t->saveSetting(); break;
        case 38: _t->initSetting(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::x_velocity_editingFinished)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::y_velocity_editingFinished)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::jog_velocity_editingFinished)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::x_lenght_editingFinished)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::y_lenght_editingFinished)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::y_step_editingFinished)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::backOrigin_velocity_editingFinished)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::scan_velocity_editingFinished)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::jog_add_sub_velocity_editingFinished)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(double , double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::movePosition)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::targetReached)) {
                *result = 10;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 39)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 39;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 39)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 39;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::x_velocity_editingFinished(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::y_velocity_editingFinished(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MainWindow::jog_velocity_editingFinished(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MainWindow::x_lenght_editingFinished(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MainWindow::y_lenght_editingFinished(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MainWindow::y_step_editingFinished(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void MainWindow::backOrigin_velocity_editingFinished(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void MainWindow::scan_velocity_editingFinished(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void MainWindow::jog_add_sub_velocity_editingFinished(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void MainWindow::movePosition(double _t1, double _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void MainWindow::targetReached()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
