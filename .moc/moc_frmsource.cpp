/****************************************************************************
** Meta object code from reading C++ file 'frmsource.h'
**
** Created: Tue May 8 15:29:17 2018
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../frmsource.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frmsource.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SourceDisplay[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   15,   14,   14, 0x0a,
      56,   14,   14,   14, 0x0a,
      83,   14,   14,   14, 0x0a,
     118,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SourceDisplay[] = {
    "SourceDisplay\0\0,\0"
    "deviceChanged(QModelIndex,QModelIndex)\0"
    "updatePlot(QStandardItem*)\0"
    "on_source_currentIndexChanged(int)\0"
    "on_btnPrint_clicked()\0"
};

void SourceDisplay::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SourceDisplay *_t = static_cast<SourceDisplay *>(_o);
        switch (_id) {
        case 0: _t->deviceChanged((*reinterpret_cast< QModelIndex(*)>(_a[1])),(*reinterpret_cast< QModelIndex(*)>(_a[2]))); break;
        case 1: _t->updatePlot((*reinterpret_cast< QStandardItem*(*)>(_a[1]))); break;
        case 2: _t->on_source_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_btnPrint_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SourceDisplay::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SourceDisplay::staticMetaObject = {
    { &QConnectedTabWidget::staticMetaObject, qt_meta_stringdata_SourceDisplay,
      qt_meta_data_SourceDisplay, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SourceDisplay::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SourceDisplay::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SourceDisplay::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SourceDisplay))
        return static_cast<void*>(const_cast< SourceDisplay*>(this));
    return QConnectedTabWidget::qt_metacast(_clname);
}

int SourceDisplay::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QConnectedTabWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
