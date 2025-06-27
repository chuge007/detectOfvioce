/****************************************************************************
** Meta object code from reading C++ file 'gcodemodulation.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../gcodemodulation.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gcodemodulation.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_gCodeModulation_t {
    QByteArrayData data[11];
    char stringdata0[153];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_gCodeModulation_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_gCodeModulation_t qt_meta_stringdata_gCodeModulation = {
    {
QT_MOC_LITERAL(0, 0, 15), // "gCodeModulation"
QT_MOC_LITERAL(1, 16, 13), // "allInsertPaus"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 13), // "allDeletePaus"
QT_MOC_LITERAL(4, 45, 10), // "insertPaus"
QT_MOC_LITERAL(5, 56, 10), // "deleteLine"
QT_MOC_LITERAL(6, 67, 8), // "autoSave"
QT_MOC_LITERAL(7, 76, 11), // "addRangeRow"
QT_MOC_LITERAL(8, 88, 18), // "on_saveBtn_clicked"
QT_MOC_LITERAL(9, 107, 28), // "on_trajectory_smooth_clicked"
QT_MOC_LITERAL(10, 136, 16) // "TransmissionFile"

    },
    "gCodeModulation\0allInsertPaus\0\0"
    "allDeletePaus\0insertPaus\0deleteLine\0"
    "autoSave\0addRangeRow\0on_saveBtn_clicked\0"
    "on_trajectory_smooth_clicked\0"
    "TransmissionFile"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_gCodeModulation[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x08 /* Private */,
       3,    0,   60,    2, 0x08 /* Private */,
       4,    0,   61,    2, 0x08 /* Private */,
       5,    0,   62,    2, 0x08 /* Private */,
       6,    0,   63,    2, 0x08 /* Private */,
       7,    0,   64,    2, 0x08 /* Private */,
       8,    0,   65,    2, 0x08 /* Private */,
       9,    0,   66,    2, 0x08 /* Private */,
      10,    0,   67,    2, 0x08 /* Private */,

 // slots: parameters
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

void gCodeModulation::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<gCodeModulation *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->allInsertPaus(); break;
        case 1: _t->allDeletePaus(); break;
        case 2: _t->insertPaus(); break;
        case 3: _t->deleteLine(); break;
        case 4: _t->autoSave(); break;
        case 5: _t->addRangeRow(); break;
        case 6: _t->on_saveBtn_clicked(); break;
        case 7: _t->on_trajectory_smooth_clicked(); break;
        case 8: _t->TransmissionFile(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject gCodeModulation::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_gCodeModulation.data,
    qt_meta_data_gCodeModulation,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *gCodeModulation::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *gCodeModulation::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_gCodeModulation.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int gCodeModulation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
