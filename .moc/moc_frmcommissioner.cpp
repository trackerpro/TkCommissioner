/****************************************************************************
** Meta object code from reading C++ file 'frmcommissioner.h'
**
** Created: Mon Oct 22 16:29:07 2018
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../frmcommissioner.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frmcommissioner.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Commissioner[] = {

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
      14,   13,   13,   13, 0x0a,
      36,   34,   13,   13, 0x0a,
      58,   50,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Commissioner[] = {
    "Commissioner\0\0closeCommissioner()\0i\0"
    "closeTab(int)\0w,label\0"
    "showTab(QConnectedTabWidget*,QString)\0"
};

void Commissioner::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Commissioner *_t = static_cast<Commissioner *>(_o);
        switch (_id) {
        case 0: _t->closeCommissioner(); break;
        case 1: _t->closeTab((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->showTab((*reinterpret_cast< QConnectedTabWidget*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Commissioner::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Commissioner::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Commissioner,
      qt_meta_data_Commissioner, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Commissioner::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Commissioner::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Commissioner::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Commissioner))
        return static_cast<void*>(const_cast< Commissioner*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Commissioner::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
