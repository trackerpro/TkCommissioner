/****************************************************************************
** Meta object code from reading C++ file 'frmfedmap.h'
**
** Created: Mon Oct 22 16:29:17 2018
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../frmfedmap.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frmfedmap.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FedMap[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x0a,
      31,    7,    7,    7, 0x0a,
      55,    7,    7,    7, 0x0a,
      78,    7,    7,    7, 0x08,
      92,    7,    7,    7, 0x08,
     123,    7,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_FedMap[] = {
    "FedMap\0\0on_btnZoomIn_clicked()\0"
    "on_btnZoomOut_clicked()\0on_btnUpload_clicked()\0"
    "setupMatrix()\0catchWheelSignal(QWheelEvent*)\0"
    "catchZoomSignal(QPointF)\0"
};

void FedMap::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FedMap *_t = static_cast<FedMap *>(_o);
        switch (_id) {
        case 0: _t->on_btnZoomIn_clicked(); break;
        case 1: _t->on_btnZoomOut_clicked(); break;
        case 2: _t->on_btnUpload_clicked(); break;
        case 3: _t->setupMatrix(); break;
        case 4: _t->catchWheelSignal((*reinterpret_cast< QWheelEvent*(*)>(_a[1]))); break;
        case 5: _t->catchZoomSignal((*reinterpret_cast< const QPointF(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData FedMap::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FedMap::staticMetaObject = {
    { &QConnectedTabWidget::staticMetaObject, qt_meta_stringdata_FedMap,
      qt_meta_data_FedMap, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FedMap::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FedMap::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FedMap::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FedMap))
        return static_cast<void*>(const_cast< FedMap*>(this));
    return QConnectedTabWidget::qt_metacast(_clname);
}

int FedMap::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QConnectedTabWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
