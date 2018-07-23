/****************************************************************************
** Meta object code from reading C++ file 'CustomTQtWidget.h'
**
** Created: Tue May 8 15:29:04 2018
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../CustomTQtWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CustomTQtWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CustomTQtWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   17,   16,   16, 0x05,
      47,   16,   16,   16, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_CustomTQtWidget[] = {
    "CustomTQtWidget\0\0,\0selectSignal(QPoint,QPoint)\0"
    "zoomoutSignal()\0"
};

void CustomTQtWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CustomTQtWidget *_t = static_cast<CustomTQtWidget *>(_o);
        switch (_id) {
        case 0: _t->selectSignal((*reinterpret_cast< QPoint(*)>(_a[1])),(*reinterpret_cast< QPoint(*)>(_a[2]))); break;
        case 1: _t->zoomoutSignal(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CustomTQtWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CustomTQtWidget::staticMetaObject = {
    { &TQtWidget::staticMetaObject, qt_meta_stringdata_CustomTQtWidget,
      qt_meta_data_CustomTQtWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CustomTQtWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CustomTQtWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CustomTQtWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CustomTQtWidget))
        return static_cast<void*>(const_cast< CustomTQtWidget*>(this));
    return TQtWidget::qt_metacast(_clname);
}

int CustomTQtWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TQtWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void CustomTQtWidget::selectSignal(QPoint _t1, QPoint _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CustomTQtWidget::zoomoutSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
