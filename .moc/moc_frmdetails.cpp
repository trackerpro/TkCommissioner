/****************************************************************************
** Meta object code from reading C++ file 'frmdetails.h'
**
** Created: Mon Oct 22 16:29:12 2018
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../frmdetails.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frmdetails.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SelectionDetails[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x0a,
      44,   17,   17,   17, 0x0a,
      72,   17,   17,   17, 0x0a,
     101,   17,   17,   17, 0x0a,
     132,   17,   17,   17, 0x0a,
     167,   17,   17,   17, 0x0a,
     199,   17,   17,   17, 0x0a,
     229,   17,   17,   17, 0x0a,
     252,   17,   17,   17, 0x0a,
     280,   17,   17,   17, 0x0a,
     307,   17,   17,   17, 0x0a,
     333,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SelectionDetails[] = {
    "SelectionDetails\0\0on_btnSelectAll_clicked()\0"
    "on_btnUnselectAll_clicked()\0"
    "on_btnSelectTagged_clicked()\0"
    "on_btnUnselectTagged_clicked()\0"
    "on_btnShowTaggedSelected_clicked()\0"
    "on_btnShowAllSelected_clicked()\0"
    "on_btnShowTaggedAll_clicked()\0"
    "on_btnAddTag_clicked()\0"
    "on_btnTagSelected_clicked()\0"
    "on_btnShowSource_clicked()\0"
    "on_btnShowTrend_clicked()\0"
    "on_btnSave_clicked()\0"
};

void SelectionDetails::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SelectionDetails *_t = static_cast<SelectionDetails *>(_o);
        switch (_id) {
        case 0: _t->on_btnSelectAll_clicked(); break;
        case 1: _t->on_btnUnselectAll_clicked(); break;
        case 2: _t->on_btnSelectTagged_clicked(); break;
        case 3: _t->on_btnUnselectTagged_clicked(); break;
        case 4: _t->on_btnShowTaggedSelected_clicked(); break;
        case 5: _t->on_btnShowAllSelected_clicked(); break;
        case 6: _t->on_btnShowTaggedAll_clicked(); break;
        case 7: _t->on_btnAddTag_clicked(); break;
        case 8: _t->on_btnTagSelected_clicked(); break;
        case 9: _t->on_btnShowSource_clicked(); break;
        case 10: _t->on_btnShowTrend_clicked(); break;
        case 11: _t->on_btnSave_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData SelectionDetails::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SelectionDetails::staticMetaObject = {
    { &QConnectedTabWidget::staticMetaObject, qt_meta_stringdata_SelectionDetails,
      qt_meta_data_SelectionDetails, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SelectionDetails::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SelectionDetails::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SelectionDetails::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SelectionDetails))
        return static_cast<void*>(const_cast< SelectionDetails*>(this));
    return QConnectedTabWidget::qt_metacast(_clname);
}

int SelectionDetails::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QConnectedTabWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
