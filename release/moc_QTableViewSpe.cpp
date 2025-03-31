/****************************************************************************
** Meta object code from reading C++ file 'QTableViewSpe.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../widgetDefin/QTableViewSpe.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QTableViewSpe.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QTableViewSpe_t {
    QByteArrayData data[7];
    char stringdata0[68];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QTableViewSpe_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QTableViewSpe_t qt_meta_stringdata_QTableViewSpe = {
    {
QT_MOC_LITERAL(0, 0, 13), // "QTableViewSpe"
QT_MOC_LITERAL(1, 14, 18), // "allwelds_lostfocus"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 7), // "loadCol"
QT_MOC_LITERAL(4, 42, 11), // "QModelIndex"
QT_MOC_LITERAL(5, 54, 4), // "indy"
QT_MOC_LITERAL(6, 59, 8) // "eraseCol"

    },
    "QTableViewSpe\0allwelds_lostfocus\0\0"
    "loadCol\0QModelIndex\0indy\0eraseCol"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QTableViewSpe[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   30,    2, 0x0a /* Public */,
       6,    1,   33,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 4,    5,

       0        // eod
};

void QTableViewSpe::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QTableViewSpe *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->allwelds_lostfocus(); break;
        case 1: _t->loadCol((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 2: _t->eraseCol((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QTableViewSpe::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QTableViewSpe::allwelds_lostfocus)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QTableViewSpe::staticMetaObject = { {
    &QTableView::staticMetaObject,
    qt_meta_stringdata_QTableViewSpe.data,
    qt_meta_data_QTableViewSpe,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QTableViewSpe::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QTableViewSpe::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QTableViewSpe.stringdata0))
        return static_cast<void*>(this);
    return QTableView::qt_metacast(_clname);
}

int QTableViewSpe::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void QTableViewSpe::allwelds_lostfocus()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
