/****************************************************************************
** Meta object code from reading C++ file 'AGEPainter.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Editor/UI/AGEPainter.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AGEPainter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_AGEMaterialsView_t {
    QByteArrayData data[6];
    char stringdata[70];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AGEMaterialsView_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AGEMaterialsView_t qt_meta_stringdata_AGEMaterialsView = {
    {
QT_MOC_LITERAL(0, 0, 16),
QT_MOC_LITERAL(1, 17, 11),
QT_MOC_LITERAL(2, 29, 0),
QT_MOC_LITERAL(3, 30, 16),
QT_MOC_LITERAL(4, 47, 4),
QT_MOC_LITERAL(5, 52, 17)
    },
    "AGEMaterialsView\0itemClicked\0\0"
    "QListWidgetItem*\0item\0itemDoubleClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AGEMaterialsView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x0a /* Public */,
       5,    1,   27,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void AGEMaterialsView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AGEMaterialsView *_t = static_cast<AGEMaterialsView *>(_o);
        switch (_id) {
        case 0: _t->itemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 1: _t->itemDoubleClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject AGEMaterialsView::staticMetaObject = {
    { &QListWidget::staticMetaObject, qt_meta_stringdata_AGEMaterialsView.data,
      qt_meta_data_AGEMaterialsView,  qt_static_metacall, 0, 0}
};


const QMetaObject *AGEMaterialsView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AGEMaterialsView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AGEMaterialsView.stringdata))
        return static_cast<void*>(const_cast< AGEMaterialsView*>(this));
    return QListWidget::qt_metacast(_clname);
}

int AGEMaterialsView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
struct qt_meta_stringdata_AGEPainter_t {
    QByteArrayData data[13];
    char stringdata[221];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AGEPainter_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AGEPainter_t qt_meta_stringdata_AGEPainter = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 19),
QT_MOC_LITERAL(2, 31, 0),
QT_MOC_LITERAL(3, 32, 5),
QT_MOC_LITERAL(4, 38, 20),
QT_MOC_LITERAL(5, 59, 21),
QT_MOC_LITERAL(6, 81, 22),
QT_MOC_LITERAL(7, 104, 23),
QT_MOC_LITERAL(8, 128, 18),
QT_MOC_LITERAL(9, 147, 18),
QT_MOC_LITERAL(10, 166, 17),
QT_MOC_LITERAL(11, 184, 16),
QT_MOC_LITERAL(12, 201, 19)
    },
    "AGEPainter\0radiusSliderChanged\0\0value\0"
    "radiusSpinBoxChanged\0hardnessSliderChanged\0"
    "hardnessSpinBoxChanged\0saturationSliderChanged\0"
    "colorButtonPressed\0resetButtonPressed\0"
    "saveButtonPressed\0addButtonPressed\0"
    "removeButtonPressed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AGEPainter[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x0a /* Public */,
       4,    1,   67,    2, 0x0a /* Public */,
       5,    1,   70,    2, 0x0a /* Public */,
       6,    1,   73,    2, 0x0a /* Public */,
       7,    1,   76,    2, 0x0a /* Public */,
       8,    0,   79,    2, 0x0a /* Public */,
       9,    0,   80,    2, 0x0a /* Public */,
      10,    0,   81,    2, 0x0a /* Public */,
      11,    0,   82,    2, 0x0a /* Public */,
      12,    0,   83,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void AGEPainter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AGEPainter *_t = static_cast<AGEPainter *>(_o);
        switch (_id) {
        case 0: _t->radiusSliderChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->radiusSpinBoxChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->hardnessSliderChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->hardnessSpinBoxChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->saturationSliderChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->colorButtonPressed(); break;
        case 6: _t->resetButtonPressed(); break;
        case 7: _t->saveButtonPressed(); break;
        case 8: _t->addButtonPressed(); break;
        case 9: _t->removeButtonPressed(); break;
        default: ;
        }
    }
}

const QMetaObject AGEPainter::staticMetaObject = {
    { &AGESidePanelWidget::staticMetaObject, qt_meta_stringdata_AGEPainter.data,
      qt_meta_data_AGEPainter,  qt_static_metacall, 0, 0}
};


const QMetaObject *AGEPainter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AGEPainter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AGEPainter.stringdata))
        return static_cast<void*>(const_cast< AGEPainter*>(this));
    return AGESidePanelWidget::qt_metacast(_clname);
}

int AGEPainter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AGESidePanelWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
