/****************************************************************************
** Meta object code from reading C++ file 'frmaddskip.h'
**
** Created: Tue May 8 15:29:12 2018
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../frmaddskip.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frmaddskip.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AddSkipChannel[] = {

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
      16,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      38,   15,   15,   15, 0x0a,
      47,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_AddSkipChannel[] = {
    "AddSkipChannel\0\0key(QPair<uint,uint>)\0"
    "accept()\0reject()\0"
};

void AddSkipChannel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AddSkipChannel *_t = static_cast<AddSkipChannel *>(_o);
        switch (_id) {
        case 0: _t->key((*reinterpret_cast< QPair<uint,uint>(*)>(_a[1]))); break;
        case 1: _t->accept(); break;
        case 2: _t->reject(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData AddSkipChannel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AddSkipChannel::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_AddSkipChannel,
      qt_meta_data_AddSkipChannel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AddSkipChannel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AddSkipChannel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AddSkipChannel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AddSkipChannel))
        return static_cast<void*>(const_cast< AddSkipChannel*>(this));
    return QDialog::qt_metacast(_clname);
}

int AddSkipChannel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void AddSkipChannel::key(QPair<unsigned,unsigned> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
