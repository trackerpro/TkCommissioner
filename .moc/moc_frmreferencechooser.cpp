/****************************************************************************
** Meta object code from reading C++ file 'frmreferencechooser.h'
**
** Created: Tue May 8 15:29:11 2018
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../frmreferencechooser.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frmreferencechooser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ReferenceChooser[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   18,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      62,   53,   17,   17, 0x0a,
     105,   98,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ReferenceChooser[] = {
    "ReferenceChooser\0\0,,\0"
    "refSignal(QString,QString,bool)\0"
    "current,\0runChanged(QModelIndex,QModelIndex)\0"
    "button\0on_buttonBox_clicked(QAbstractButton*)\0"
};

void ReferenceChooser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ReferenceChooser *_t = static_cast<ReferenceChooser *>(_o);
        switch (_id) {
        case 0: _t->refSignal((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 1: _t->runChanged((*reinterpret_cast< QModelIndex(*)>(_a[1])),(*reinterpret_cast< QModelIndex(*)>(_a[2]))); break;
        case 2: _t->on_buttonBox_clicked((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ReferenceChooser::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ReferenceChooser::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ReferenceChooser,
      qt_meta_data_ReferenceChooser, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ReferenceChooser::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ReferenceChooser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ReferenceChooser::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ReferenceChooser))
        return static_cast<void*>(const_cast< ReferenceChooser*>(this));
    return QDialog::qt_metacast(_clname);
}

int ReferenceChooser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void ReferenceChooser::refSignal(QString _t1, QString _t2, bool _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
