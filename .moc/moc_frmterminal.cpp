/****************************************************************************
** Meta object code from reading C++ file 'frmterminal.h'
**
** Created: Mon Oct 22 16:29:19 2018
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../frmterminal.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frmterminal.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TkTerminal[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      33,   11,   11,   11, 0x0a,
      62,   50,   11,   11, 0x0a,
     110,  104,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TkTerminal[] = {
    "TkTerminal\0\0on_btnKill_clicked()\0"
    "readFromStdout()\0,exitStatus\0"
    "processFinished(int,QProcess::ExitStatus)\0"
    "error\0processError(QProcess::ProcessError)\0"
};

void TkTerminal::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TkTerminal *_t = static_cast<TkTerminal *>(_o);
        switch (_id) {
        case 0: _t->on_btnKill_clicked(); break;
        case 1: _t->readFromStdout(); break;
        case 2: _t->processFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        case 3: _t->processError((*reinterpret_cast< QProcess::ProcessError(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData TkTerminal::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TkTerminal::staticMetaObject = {
    { &QConnectedTabWidget::staticMetaObject, qt_meta_stringdata_TkTerminal,
      qt_meta_data_TkTerminal, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TkTerminal::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TkTerminal::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TkTerminal::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TkTerminal))
        return static_cast<void*>(const_cast< TkTerminal*>(this));
    return QConnectedTabWidget::qt_metacast(_clname);
}

int TkTerminal::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QConnectedTabWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
