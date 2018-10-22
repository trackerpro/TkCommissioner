/****************************************************************************
** Meta object code from reading C++ file 'frmterminaldialog.h'
**
** Created: Mon Oct 22 16:29:22 2018
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../frmterminaldialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frmterminaldialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TkTerminalDialog[] = {

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
      18,   17,   17,   17, 0x0a,
      47,   35,   17,   17, 0x0a,
      89,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TkTerminalDialog[] = {
    "TkTerminalDialog\0\0readFromStdout()\0"
    ",exitStatus\0processFinished(int,QProcess::ExitStatus)\0"
    "executeWaitForReadyRead()\0"
};

void TkTerminalDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TkTerminalDialog *_t = static_cast<TkTerminalDialog *>(_o);
        switch (_id) {
        case 0: _t->readFromStdout(); break;
        case 1: _t->processFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        case 2: _t->executeWaitForReadyRead(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData TkTerminalDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TkTerminalDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_TkTerminalDialog,
      qt_meta_data_TkTerminalDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TkTerminalDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TkTerminalDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TkTerminalDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TkTerminalDialog))
        return static_cast<void*>(const_cast< TkTerminalDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int TkTerminalDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
