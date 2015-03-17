/****************************************************************************
** Meta object code from reading C++ file 'AGEToolBar.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Editor/UI/AGEToolBar.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AGEToolBar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_AGEToolBar_t {
    QByteArrayData data[13];
    char stringdata[166];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AGEToolBar_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AGEToolBar_t qt_meta_stringdata_AGEToolBar = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 16),
QT_MOC_LITERAL(2, 28, 0),
QT_MOC_LITERAL(3, 29, 7),
QT_MOC_LITERAL(4, 37, 14),
QT_MOC_LITERAL(5, 52, 16),
QT_MOC_LITERAL(6, 69, 15),
QT_MOC_LITERAL(7, 85, 11),
QT_MOC_LITERAL(8, 97, 11),
QT_MOC_LITERAL(9, 109, 11),
QT_MOC_LITERAL(10, 121, 12),
QT_MOC_LITERAL(11, 134, 25),
QT_MOC_LITERAL(12, 160, 5)
    },
    "AGEToolBar\0btnMirrorToggled\0\0checked\0"
    "btnMoveToggled\0btnRotateToggled\0"
    "btnScaleToggled\0btnXToggled\0btnYToggled\0"
    "btnZToggled\0btnXZToggled\0"
    "coordSystemStateActivated\0state"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AGEToolBar[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x08 /* Private */,
       4,    1,   62,    2, 0x08 /* Private */,
       5,    1,   65,    2, 0x08 /* Private */,
       6,    1,   68,    2, 0x08 /* Private */,
       7,    1,   71,    2, 0x08 /* Private */,
       8,    1,   74,    2, 0x08 /* Private */,
       9,    1,   77,    2, 0x08 /* Private */,
      10,    1,   80,    2, 0x08 /* Private */,
      11,    1,   83,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::QString,   12,

       0        // eod
};

void AGEToolBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AGEToolBar *_t = static_cast<AGEToolBar *>(_o);
        switch (_id) {
        case 0: _t->btnMirrorToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->btnMoveToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->btnRotateToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->btnScaleToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->btnXToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->btnYToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->btnZToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->btnXZToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->coordSystemStateActivated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject AGEToolBar::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_AGEToolBar.data,
      qt_meta_data_AGEToolBar,  qt_static_metacall, 0, 0}
};


const QMetaObject *AGEToolBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AGEToolBar::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AGEToolBar.stringdata))
        return static_cast<void*>(const_cast< AGEToolBar*>(this));
    return QFrame::qt_metacast(_clname);
}

int AGEToolBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
