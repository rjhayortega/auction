/****************************************************************************
** Meta object code from reading C++ file 'dragwidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "types/dragwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dragwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DragWidget[] = {

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
      12,   11,   11,   11, 0x0a,
      30,   11,   11,   11, 0x0a,
      48,   11,   11,   11, 0x0a,
      64,   11,   11,   11, 0x0a,
      78,   11,   11,   11, 0x0a,
      92,   11,   11,   11, 0x0a,
     106,   11,   11,   11, 0x0a,
     120,   11,   11,   11, 0x0a,
     136,   11,   11,   11, 0x0a,
     151,   11,   11,   11, 0x0a,
     170,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_DragWidget[] = {
    "DragWidget\0\0checkedAddress1()\0"
    "checkedAddress2()\0checkedAmount()\0"
    "checkedCity()\0checkedDate()\0checkedHead()\0"
    "checkedMemo()\0checkedNumber()\0"
    "checkedPayee()\0checkedSignature()\0"
    "checkedTextAmount()\0"
};

void DragWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DragWidget *_t = static_cast<DragWidget *>(_o);
        switch (_id) {
        case 0: _t->checkedAddress1(); break;
        case 1: _t->checkedAddress2(); break;
        case 2: _t->checkedAmount(); break;
        case 3: _t->checkedCity(); break;
        case 4: _t->checkedDate(); break;
        case 5: _t->checkedHead(); break;
        case 6: _t->checkedMemo(); break;
        case 7: _t->checkedNumber(); break;
        case 8: _t->checkedPayee(); break;
        case 9: _t->checkedSignature(); break;
        case 10: _t->checkedTextAmount(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData DragWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DragWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_DragWidget,
      qt_meta_data_DragWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DragWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DragWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DragWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DragWidget))
        return static_cast<void*>(const_cast< DragWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int DragWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
