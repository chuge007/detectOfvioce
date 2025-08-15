/****************************************************************************
** Meta object code from reading C++ file 'ascan.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ascan.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ascan.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ascan_t {
    QByteArrayData data[13];
    char stringdata0[161];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ascan_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ascan_t qt_meta_stringdata_ascan = {
    {
QT_MOC_LITERAL(0, 0, 5), // "ascan"
QT_MOC_LITERAL(1, 6, 13), // "signalUpdated"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 13), // "statusMessage"
QT_MOC_LITERAL(4, 35, 4), // "text"
QT_MOC_LITERAL(5, 40, 15), // "onNewConnection"
QT_MOC_LITERAL(6, 56, 11), // "onReadyRead"
QT_MOC_LITERAL(7, 68, 15), // "onSendstanPoint"
QT_MOC_LITERAL(8, 84, 17), // "autoCorretionPath"
QT_MOC_LITERAL(9, 102, 17), // "stepCorretionPath"
QT_MOC_LITERAL(10, 120, 17), // "stopCorretionPath"
QT_MOC_LITERAL(11, 138, 18), // "appendLabelMessage"
QT_MOC_LITERAL(12, 157, 3) // "msg"

    },
    "ascan\0signalUpdated\0\0statusMessage\0"
    "text\0onNewConnection\0onReadyRead\0"
    "onSendstanPoint\0autoCorretionPath\0"
    "stepCorretionPath\0stopCorretionPath\0"
    "appendLabelMessage\0msg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ascan[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,
       3,    1,   60,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   63,    2, 0x08 /* Private */,
       6,    0,   64,    2, 0x08 /* Private */,
       7,    0,   65,    2, 0x08 /* Private */,
       8,    0,   66,    2, 0x08 /* Private */,
       9,    0,   67,    2, 0x08 /* Private */,
      10,    0,   68,    2, 0x08 /* Private */,
      11,    1,   69,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   12,

       0        // eod
};

void ascan::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ascan *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalUpdated(); break;
        case 1: _t->statusMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->onNewConnection(); break;
        case 3: _t->onReadyRead(); break;
        case 4: _t->onSendstanPoint(); break;
        case 5: _t->autoCorretionPath(); break;
        case 6: _t->stepCorretionPath(); break;
        case 7: _t->stopCorretionPath(); break;
        case 8: _t->appendLabelMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ascan::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ascan::signalUpdated)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ascan::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ascan::statusMessage)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ascan::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_ascan.data,
    qt_meta_data_ascan,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ascan::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ascan::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ascan.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ascan::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void ascan::signalUpdated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ascan::statusMessage(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
