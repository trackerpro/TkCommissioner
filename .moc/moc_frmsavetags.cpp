/****************************************************************************
** Meta object code from reading C++ file 'frmsavetags.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../frmsavetags.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frmsavetags.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TagUpload[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   11,   10,   10, 0x0a,
      56,   10,   10,   10, 0x0a,
      86,   10,   10,   10, 0x0a,
     112,   10,   10,   10, 0x0a,
     139,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TagUpload[] = {
    "TagUpload\0\0current,\0"
    "devChanged(QModelIndex,QModelIndex)\0"
    "on_confirmCheck_toggled(bool)\0"
    "on_buttonCancel_clicked()\0"
    "on_btnAddComment_clicked()\0"
    "on_buttonOk_clicked()\0"
};

void TagUpload::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TagUpload *_t = static_cast<TagUpload *>(_o);
        switch (_id) {
        case 0: _t->devChanged((*reinterpret_cast< QModelIndex(*)>(_a[1])),(*reinterpret_cast< QModelIndex(*)>(_a[2]))); break;
        case 1: _t->on_confirmCheck_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->on_buttonCancel_clicked(); break;
        case 3: _t->on_btnAddComment_clicked(); break;
        case 4: _t->on_buttonOk_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData TagUpload::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TagUpload::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_TagUpload,
      qt_meta_data_TagUpload, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TagUpload::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TagUpload::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TagUpload::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TagUpload))
        return static_cast<void*>(const_cast< TagUpload*>(this));
    return QDialog::qt_metacast(_clname);
}

int TagUpload::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
