/****************************************************************************
** Meta object code from reading C++ file 'frmpartitions.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../frmpartitions.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frmpartitions.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Partitions[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      31,   11,   11,   11, 0x0a,
      54,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Partitions[] = {
    "Partitions\0\0on_btnOk_clicked()\0"
    "on_btnCancel_clicked()\0"
    "partitionClicked(QModelIndex)\0"
};

void Partitions::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Partitions *_t = static_cast<Partitions *>(_o);
        switch (_id) {
        case 0: _t->on_btnOk_clicked(); break;
        case 1: _t->on_btnCancel_clicked(); break;
        case 2: _t->partitionClicked((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Partitions::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Partitions::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Partitions,
      qt_meta_data_Partitions, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Partitions::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Partitions::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Partitions::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Partitions))
        return static_cast<void*>(const_cast< Partitions*>(this));
    return QDialog::qt_metacast(_clname);
}

int Partitions::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
