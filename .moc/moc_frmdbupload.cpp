/****************************************************************************
** Meta object code from reading C++ file 'frmdbupload.h'
**
** Created: Tue May 8 15:29:12 2018
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../frmdbupload.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frmdbupload.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DBUpload[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x0a,
      34,    9,    9,    9, 0x0a,
      58,    9,    9,    9, 0x0a,
      82,    9,    9,    9, 0x0a,
     107,    9,    9,    9, 0x0a,
     131,    9,    9,    9, 0x0a,
     159,    9,    9,    9, 0x0a,
     182,    9,    9,    9, 0x0a,
     206,    9,    9,    9, 0x0a,
     242,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_DBUpload[] = {
    "DBUpload\0\0on_radAll_toggled(bool)\0"
    "on_radFed_toggled(bool)\0on_radFec_toggled(bool)\0"
    "on_radRing_toggled(bool)\0"
    "on_radCcu_toggled(bool)\0"
    "on_radCcuChan_toggled(bool)\0"
    "on_btnUpload_clicked()\0on_btnAddSkip_clicked()\0"
    "channelCheckChanged(QStandardItem*)\0"
    "addSkipChannel(QPair<uint,uint>)\0"
};

void DBUpload::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DBUpload *_t = static_cast<DBUpload *>(_o);
        switch (_id) {
        case 0: _t->on_radAll_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->on_radFed_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->on_radFec_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->on_radRing_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->on_radCcu_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->on_radCcuChan_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->on_btnUpload_clicked(); break;
        case 7: _t->on_btnAddSkip_clicked(); break;
        case 8: _t->channelCheckChanged((*reinterpret_cast< QStandardItem*(*)>(_a[1]))); break;
        case 9: _t->addSkipChannel((*reinterpret_cast< QPair<uint,uint>(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DBUpload::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DBUpload::staticMetaObject = {
    { &QConnectedTabWidget::staticMetaObject, qt_meta_stringdata_DBUpload,
      qt_meta_data_DBUpload, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DBUpload::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DBUpload::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DBUpload::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DBUpload))
        return static_cast<void*>(const_cast< DBUpload*>(this));
    return QConnectedTabWidget::qt_metacast(_clname);
}

int DBUpload::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QConnectedTabWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
