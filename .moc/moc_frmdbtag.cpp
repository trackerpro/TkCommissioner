/****************************************************************************
** Meta object code from reading C++ file 'frmdbtag.h'
**
** Created: Tue May 8 15:29:14 2018
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../frmdbtag.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frmdbtag.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TagCreator[] = {

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
      44,   11,   11,   11, 0x0a,
      53,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TagCreator[] = {
    "TagCreator\0\0on_tagLine_textChanged(QString)\0"
    "accept()\0reject()\0"
};

void TagCreator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TagCreator *_t = static_cast<TagCreator *>(_o);
        switch (_id) {
        case 0: _t->on_tagLine_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->accept(); break;
        case 2: _t->reject(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData TagCreator::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TagCreator::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_TagCreator,
      qt_meta_data_TagCreator, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TagCreator::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TagCreator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TagCreator::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TagCreator))
        return static_cast<void*>(const_cast< TagCreator*>(this));
    return QDialog::qt_metacast(_clname);
}

int TagCreator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
