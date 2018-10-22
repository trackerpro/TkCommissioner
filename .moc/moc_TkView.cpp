/****************************************************************************
** Meta object code from reading C++ file 'TkView.h'
**
** Created: Mon Oct 22 16:29:06 2018
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../TkView.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TkView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GraphicsView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_GraphicsView[] = {
    "GraphicsView\0"
};

void GraphicsView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData GraphicsView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GraphicsView::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_GraphicsView,
      qt_meta_data_GraphicsView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GraphicsView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GraphicsView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GraphicsView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GraphicsView))
        return static_cast<void*>(const_cast< GraphicsView*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int GraphicsView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_View[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   11,    6,    5, 0x05,
      38,    5,    5,    5, 0x05,
      54,    5,    5,    5, 0x05,
      69,    5,    5,    5, 0x05,

 // slots: signature, parameters, type, tag, flags
      94,   88,    5,    5, 0x0a,
     106,    5,    5,    5, 0x2a,
     115,   88,    5,    5, 0x0a,
     128,    5,    5,    5, 0x2a,
     138,    5,    5,    5, 0x0a,
     150,    5,    5,    5, 0x0a,
     163,    5,    5,    5, 0x08,
     179,    5,    5,    5, 0x08,
     194,    5,    5,    5, 0x08,
     213,   11,    5,    5, 0x08,
     227,    5,    5,    5, 0x08,
     251,    5,    5,    5, 0x08,
     265,    5,    5,    5, 0x08,
     285,    5,    5,    5, 0x08,
     306,    5,    5,    5, 0x08,
     314,    5,    5,    5, 0x08,
     327,    5,    5,    5, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_View[] = {
    "View\0\0bool\0state\0invertedChanged(int)\0"
    "showSelection()\0fixSelection()\0"
    "releaseSelection()\0level\0zoomIn(int)\0"
    "zoomIn()\0zoomOut(int)\0zoomOut()\0"
    "resetView()\0viewUpdate()\0showTriggered()\0"
    "fixTriggered()\0releaseTriggered()\0"
    "inverted(int)\0setResetButtonEnabled()\0"
    "setupMatrix()\0togglePointerMode()\0"
    "toggleAntialiasing()\0print()\0minChanged()\0"
    "maxChanged()\0"
};

void View::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        View *_t = static_cast<View *>(_o);
        switch (_id) {
        case 0: { bool _r = _t->invertedChanged((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 1: _t->showSelection(); break;
        case 2: _t->fixSelection(); break;
        case 3: _t->releaseSelection(); break;
        case 4: _t->zoomIn((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->zoomIn(); break;
        case 6: _t->zoomOut((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->zoomOut(); break;
        case 8: _t->resetView(); break;
        case 9: _t->viewUpdate(); break;
        case 10: _t->showTriggered(); break;
        case 11: _t->fixTriggered(); break;
        case 12: _t->releaseTriggered(); break;
        case 13: _t->inverted((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->setResetButtonEnabled(); break;
        case 15: _t->setupMatrix(); break;
        case 16: _t->togglePointerMode(); break;
        case 17: _t->toggleAntialiasing(); break;
        case 18: _t->print(); break;
        case 19: _t->minChanged(); break;
        case 20: _t->maxChanged(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData View::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject View::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_View,
      qt_meta_data_View, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &View::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *View::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *View::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_View))
        return static_cast<void*>(const_cast< View*>(this));
    return QFrame::qt_metacast(_clname);
}

int View::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    }
    return _id;
}

// SIGNAL 0
bool View::invertedChanged(int _t1)
{
    bool _t0;
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
    return _t0;
}

// SIGNAL 1
void View::showSelection()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void View::fixSelection()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void View::releaseSelection()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
QT_END_MOC_NAMESPACE
