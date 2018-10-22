/****************************************************************************
** Meta object code from reading C++ file 'frmstartup.h'
**
** Created: Mon Oct 22 16:29:08 2018
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../frmstartup.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frmstartup.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Startup[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x0a,
      30,    8,    8,    8, 0x0a,
      58,    8,    8,    8, 0x0a,
      91,    8,    8,    8, 0x0a,
     118,    8,    8,    8, 0x0a,
     142,    8,    8,    8, 0x0a,
     164,    8,    8,    8, 0x0a,
     188,    8,    8,    8, 0x0a,
     218,    8,    8,    8, 0x0a,
     261,  244,    8,    8, 0x0a,
     297,  244,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Startup[] = {
    "Startup\0\0on_btnQuit_clicked()\0"
    "on_btnViewResults_clicked()\0"
    "on_btnUpdatePartitions_clicked()\0"
    "on_btnUpdateRuns_clicked()\0"
    "on_btnMarkBad_clicked()\0on_btnState_clicked()\0"
    "on_btnAnalyze_clicked()\0"
    "on_btnPrepareGlobal_clicked()\0"
    "on_btnTimingO2O_clicked()\0current,previous\0"
    "runChanged(QModelIndex,QModelIndex)\0"
    "partitionChanged(QModelIndex,QModelIndex)\0"
};

void Startup::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Startup *_t = static_cast<Startup *>(_o);
        switch (_id) {
        case 0: _t->on_btnQuit_clicked(); break;
        case 1: _t->on_btnViewResults_clicked(); break;
        case 2: _t->on_btnUpdatePartitions_clicked(); break;
        case 3: _t->on_btnUpdateRuns_clicked(); break;
        case 4: _t->on_btnMarkBad_clicked(); break;
        case 5: _t->on_btnState_clicked(); break;
        case 6: _t->on_btnAnalyze_clicked(); break;
        case 7: _t->on_btnPrepareGlobal_clicked(); break;
        case 8: _t->on_btnTimingO2O_clicked(); break;
        case 9: _t->runChanged((*reinterpret_cast< QModelIndex(*)>(_a[1])),(*reinterpret_cast< QModelIndex(*)>(_a[2]))); break;
        case 10: _t->partitionChanged((*reinterpret_cast< QModelIndex(*)>(_a[1])),(*reinterpret_cast< QModelIndex(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Startup::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Startup::staticMetaObject = {
    { &QConnectedTabWidget::staticMetaObject, qt_meta_stringdata_Startup,
      qt_meta_data_Startup, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Startup::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Startup::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Startup::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Startup))
        return static_cast<void*>(const_cast< Startup*>(this));
    return QConnectedTabWidget::qt_metacast(_clname);
}

int Startup::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QConnectedTabWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
