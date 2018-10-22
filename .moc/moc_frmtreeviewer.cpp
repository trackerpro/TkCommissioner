/****************************************************************************
** Meta object code from reading C++ file 'frmtreeviewer.h'
**
** Created: Mon Oct 22 16:29:08 2018
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../frmtreeviewer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frmtreeviewer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TreeViewer[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   12,   11,   11, 0x0a,
      48,   46,   11,   11, 0x0a,
      75,   11,   11,   11, 0x0a,
      90,   11,   11,   11, 0x0a,
     111,   11,   11,   11, 0x0a,
     139,   11,   11,   11, 0x0a,
     167,   11,   11,   11, 0x0a,
     187,   11,   11,   11, 0x0a,
     212,   11,   11,   11, 0x0a,
     240,   11,   11,   11, 0x0a,
     262,   11,   11,   11, 0x0a,
     290,  285,   11,   11, 0x0a,
     327,  285,   11,   11, 0x0a,
     364,  285,   11,   11, 0x0a,
     406,  401,   11,   11, 0x0a,
     437,  401,   11,   11, 0x0a,
     468,  401,   11,   11, 0x0a,
     505,  499,   11,   11, 0x0a,
     534,  499,   11,   11, 0x0a,
     563,  499,   11,   11, 0x0a,
     592,   11,   11,   11, 0x0a,
     621,   11,   11,   11, 0x0a,
     650,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TreeViewer[] = {
    "TreeViewer\0\0,,\0catchRef(QString,QString,bool)\0"
    ",\0catchSelect(QPoint,QPoint)\0"
    "catchZoomout()\0on_btnDraw_clicked()\0"
    "on_btnShowSummary_clicked()\0"
    "on_btnPrintToFile_clicked()\0"
    "on_btnRef_clicked()\0on_btnDBUpload_clicked()\0"
    "on_btnGetSelected_clicked()\0"
    "on_btnTkMap_clicked()\0on_btnFedMap_clicked()\0"
    "text\0on_cmbX_currentIndexChanged(QString)\0"
    "on_cmbY_currentIndexChanged(QString)\0"
    "on_cmbZ_currentIndexChanged(QString)\0"
    "bins\0on_xSpinBins_valueChanged(int)\0"
    "on_ySpinBins_valueChanged(int)\0"
    "on_zSpinBins_valueChanged(int)\0state\0"
    "on_chkLogX_stateChanged(int)\0"
    "on_chkLogY_stateChanged(int)\0"
    "on_chkLogZ_stateChanged(int)\0"
    "on_chkRefX_stateChanged(int)\0"
    "on_chkRefY_stateChanged(int)\0"
    "on_chkRefZ_stateChanged(int)\0"
};

void TreeViewer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TreeViewer *_t = static_cast<TreeViewer *>(_o);
        switch (_id) {
        case 0: _t->catchRef((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 1: _t->catchSelect((*reinterpret_cast< QPoint(*)>(_a[1])),(*reinterpret_cast< QPoint(*)>(_a[2]))); break;
        case 2: _t->catchZoomout(); break;
        case 3: _t->on_btnDraw_clicked(); break;
        case 4: _t->on_btnShowSummary_clicked(); break;
        case 5: _t->on_btnPrintToFile_clicked(); break;
        case 6: _t->on_btnRef_clicked(); break;
        case 7: _t->on_btnDBUpload_clicked(); break;
        case 8: _t->on_btnGetSelected_clicked(); break;
        case 9: _t->on_btnTkMap_clicked(); break;
        case 10: _t->on_btnFedMap_clicked(); break;
        case 11: _t->on_cmbX_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 12: _t->on_cmbY_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 13: _t->on_cmbZ_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 14: _t->on_xSpinBins_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->on_ySpinBins_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->on_zSpinBins_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->on_chkLogX_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->on_chkLogY_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: _t->on_chkLogZ_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: _t->on_chkRefX_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: _t->on_chkRefY_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 22: _t->on_chkRefZ_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData TreeViewer::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TreeViewer::staticMetaObject = {
    { &QConnectedTabWidget::staticMetaObject, qt_meta_stringdata_TreeViewer,
      qt_meta_data_TreeViewer, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TreeViewer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TreeViewer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TreeViewer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TreeViewer))
        return static_cast<void*>(const_cast< TreeViewer*>(this));
    return QConnectedTabWidget::qt_metacast(_clname);
}

int TreeViewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QConnectedTabWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
