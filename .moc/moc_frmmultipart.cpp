/****************************************************************************
** Meta object code from reading C++ file 'frmmultipart.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../frmmultipart.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frmmultipart.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MultiPart[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,
      34,   10,   10,   10, 0x0a,
      55,   10,   10,   10, 0x0a,
      98,   10,   10,   10, 0x0a,
     140,   10,   10,   10, 0x0a,
     182,   10,   10,   10, 0x0a,
     225,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MultiPart[] = {
    "MultiPart\0\0on_btnUpdate_clicked()\0"
    "on_btnShow_clicked()\0"
    "on_cmbRunType_currentIndexChanged(QString)\0"
    "on_cmbRunTib_currentIndexChanged(QString)\0"
    "on_cmbRunTob_currentIndexChanged(QString)\0"
    "on_cmbRunTecp_currentIndexChanged(QString)\0"
    "on_cmbRunTecm_currentIndexChanged(QString)\0"
};

void MultiPart::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MultiPart *_t = static_cast<MultiPart *>(_o);
        switch (_id) {
        case 0: _t->on_btnUpdate_clicked(); break;
        case 1: _t->on_btnShow_clicked(); break;
        case 2: _t->on_cmbRunType_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->on_cmbRunTib_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->on_cmbRunTob_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->on_cmbRunTecp_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->on_cmbRunTecm_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MultiPart::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MultiPart::staticMetaObject = {
    { &QConnectedTabWidget::staticMetaObject, qt_meta_stringdata_MultiPart,
      qt_meta_data_MultiPart, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MultiPart::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MultiPart::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MultiPart::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MultiPart))
        return static_cast<void*>(const_cast< MultiPart*>(this));
    return QConnectedTabWidget::qt_metacast(_clname);
}

int MultiPart::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QConnectedTabWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
