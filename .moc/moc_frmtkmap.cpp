/****************************************************************************
** Meta object code from reading C++ file 'frmtkmap.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../frmtkmap.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frmtkmap.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TkMap[] = {

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
       7,    6,    6,    6, 0x0a,
      24,    6,    6,    6, 0x0a,
      39,    6,    6,    6, 0x0a,
      71,   58,    6,    6, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TkMap[] = {
    "TkMap\0\0printSelection()\0fixSelection()\0"
    "releaseSelection()\0items,status\0"
    "setSelection(QList<QGraphicsItem*>&,bool)\0"
};

void TkMap::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TkMap *_t = static_cast<TkMap *>(_o);
        switch (_id) {
        case 0: _t->printSelection(); break;
        case 1: _t->fixSelection(); break;
        case 2: _t->releaseSelection(); break;
        case 3: _t->setSelection((*reinterpret_cast< QList<QGraphicsItem*>(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData TkMap::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TkMap::staticMetaObject = {
    { &QConnectedTabWidget::staticMetaObject, qt_meta_stringdata_TkMap,
      qt_meta_data_TkMap, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TkMap::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TkMap::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TkMap::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TkMap))
        return static_cast<void*>(const_cast< TkMap*>(this));
    return QConnectedTabWidget::qt_metacast(_clname);
}

int TkMap::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
