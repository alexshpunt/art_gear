/****************************************************************************
** Meta object code from reading C++ file 'AGETransformPanel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Editor/UI/AGETransformPanel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AGETransformPanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_AGETransformPanel_t {
    QByteArrayData data[16];
    char stringdata[241];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AGETransformPanel_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AGETransformPanel_t qt_meta_stringdata_AGETransformPanel = {
    {
QT_MOC_LITERAL(0, 0, 17),
QT_MOC_LITERAL(1, 18, 11),
QT_MOC_LITERAL(2, 30, 0),
QT_MOC_LITERAL(3, 31, 4),
QT_MOC_LITERAL(4, 36, 15),
QT_MOC_LITERAL(5, 52, 5),
QT_MOC_LITERAL(6, 58, 18),
QT_MOC_LITERAL(7, 77, 5),
QT_MOC_LITERAL(8, 83, 18),
QT_MOC_LITERAL(9, 102, 18),
QT_MOC_LITERAL(10, 121, 18),
QT_MOC_LITERAL(11, 140, 18),
QT_MOC_LITERAL(12, 159, 18),
QT_MOC_LITERAL(13, 178, 20),
QT_MOC_LITERAL(14, 199, 20),
QT_MOC_LITERAL(15, 220, 20)
    },
    "AGETransformPanel\0nameChanged\0\0text\0"
    "visiableChanged\0state\0spinBoxPosXChanged\0"
    "value\0spinBoxPosYChanged\0spinBoxPosZChanged\0"
    "spinBoxRotXChanged\0spinBoxRotYChanged\0"
    "spinBoxRotZChanged\0spinBoxScaleXChanged\0"
    "spinBoxScaleYChanged\0spinBoxScaleZChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AGETransformPanel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x08 /* Private */,
       4,    1,   72,    2, 0x08 /* Private */,
       6,    1,   75,    2, 0x08 /* Private */,
       8,    1,   78,    2, 0x08 /* Private */,
       9,    1,   81,    2, 0x08 /* Private */,
      10,    1,   84,    2, 0x08 /* Private */,
      11,    1,   87,    2, 0x08 /* Private */,
      12,    1,   90,    2, 0x08 /* Private */,
      13,    1,   93,    2, 0x08 /* Private */,
      14,    1,   96,    2, 0x08 /* Private */,
      15,    1,   99,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Double,    7,
    QMetaType::Void, QMetaType::Double,    7,
    QMetaType::Void, QMetaType::Double,    7,
    QMetaType::Void, QMetaType::Double,    7,
    QMetaType::Void, QMetaType::Double,    7,
    QMetaType::Void, QMetaType::Double,    7,
    QMetaType::Void, QMetaType::Double,    7,
    QMetaType::Void, QMetaType::Double,    7,
    QMetaType::Void, QMetaType::Double,    7,

       0        // eod
};

void AGETransformPanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AGETransformPanel *_t = static_cast<AGETransformPanel *>(_o);
        switch (_id) {
        case 0: _t->nameChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->visiableChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->spinBoxPosXChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->spinBoxPosYChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->spinBoxPosZChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->spinBoxRotXChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->spinBoxRotYChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->spinBoxRotZChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: _t->spinBoxScaleXChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 9: _t->spinBoxScaleYChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 10: _t->spinBoxScaleZChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject AGETransformPanel::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_AGETransformPanel.data,
      qt_meta_data_AGETransformPanel,  qt_static_metacall, 0, 0}
};


const QMetaObject *AGETransformPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AGETransformPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AGETransformPanel.stringdata))
        return static_cast<void*>(const_cast< AGETransformPanel*>(this));
    if (!strcmp(_clname, "AGObject"))
        return static_cast< AGObject*>(const_cast< AGETransformPanel*>(this));
    return QFrame::qt_metacast(_clname);
}

int AGETransformPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
