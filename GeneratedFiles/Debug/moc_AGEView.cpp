/****************************************************************************
** Meta object code from reading C++ file 'AGEView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Editor/UI/AGEView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AGEView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_AGEView_t {
    QByteArrayData data[1];
    char stringdata[8];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AGEView_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AGEView_t qt_meta_stringdata_AGEView = {
    {
QT_MOC_LITERAL(0, 0, 7)
    },
    "AGEView"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AGEView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void AGEView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject AGEView::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_AGEView.data,
      qt_meta_data_AGEView,  qt_static_metacall, 0, 0}
};


const QMetaObject *AGEView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AGEView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AGEView.stringdata))
        return static_cast<void*>(const_cast< AGEView*>(this));
    return QFrame::qt_metacast(_clname);
}

int AGEView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_AGEViewTop_t {
    QByteArrayData data[8];
    char stringdata[118];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AGEViewTop_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AGEViewTop_t qt_meta_stringdata_AGEViewTop = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 22),
QT_MOC_LITERAL(2, 34, 0),
QT_MOC_LITERAL(3, 35, 5),
QT_MOC_LITERAL(4, 41, 25),
QT_MOC_LITERAL(5, 67, 1),
QT_MOC_LITERAL(6, 69, 25),
QT_MOC_LITERAL(7, 95, 22)
    },
    "AGEViewTop\0fovSpinBoxValueChanged\0\0"
    "value\0renderModeComboBoxChanged\0i\0"
    "cameraModeComboBoxChanged\0"
    "maximizedButtonClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AGEViewTop[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x09 /* Protected */,
       4,    1,   37,    2, 0x09 /* Protected */,
       6,    1,   40,    2, 0x09 /* Protected */,
       7,    1,   43,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Bool,    3,

       0        // eod
};

void AGEViewTop::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AGEViewTop *_t = static_cast<AGEViewTop *>(_o);
        switch (_id) {
        case 0: _t->fovSpinBoxValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->renderModeComboBoxChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->cameraModeComboBoxChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->maximizedButtonClicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject AGEViewTop::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_AGEViewTop.data,
      qt_meta_data_AGEViewTop,  qt_static_metacall, 0, 0}
};


const QMetaObject *AGEViewTop::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AGEViewTop::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AGEViewTop.stringdata))
        return static_cast<void*>(const_cast< AGEViewTop*>(this));
    return QWidget::qt_metacast(_clname);
}

int AGEViewTop::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
