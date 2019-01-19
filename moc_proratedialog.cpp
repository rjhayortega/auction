/****************************************************************************
** Meta object code from reading C++ file 'proratedialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "proratedialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'proratedialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ProrateDialog[] = {

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
      23,   15,   14,   14, 0x0a,
      46,   37,   14,   14, 0x0a,
      69,   14,   14,   14, 0x0a,
      86,   14,   14,   14, 0x0a,
     104,   14,   14,   14, 0x0a,
     124,  116,   14,   14, 0x0a,
     157,  153,   14,   14, 0x0a,
     186,  153,   14,   14, 0x0a,
     207,   14,   14,   14, 0x0a,
     221,   14,   14,   14, 0x0a,
     240,   14,   14,   14, 0x0a,
     247,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ProrateDialog[] = {
    "ProrateDialog\0\0invoice\0init(Invoice)\0"
    "selected\0changeProrateMode(int)\0"
    "updateProrates()\0updateShareList()\0"
    "initTable()\0row,col\0startSpecialProrate(int,int)\0"
    "row\0startTransactionProrate(int)\0"
    "startSexProrate(int)\0createPayee()\0"
    "initCheckFactory()\0save()\0"
    "removeCurrentPayee()\0"
};

void ProrateDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ProrateDialog *_t = static_cast<ProrateDialog *>(_o);
        switch (_id) {
        case 0: _t->init((*reinterpret_cast< Invoice(*)>(_a[1]))); break;
        case 1: _t->changeProrateMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->updateProrates(); break;
        case 3: _t->updateShareList(); break;
        case 4: _t->initTable(); break;
        case 5: _t->startSpecialProrate((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->startTransactionProrate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->startSexProrate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->createPayee(); break;
        case 9: _t->initCheckFactory(); break;
        case 10: _t->save(); break;
        case 11: _t->removeCurrentPayee(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ProrateDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ProrateDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ProrateDialog,
      qt_meta_data_ProrateDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ProrateDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ProrateDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ProrateDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ProrateDialog))
        return static_cast<void*>(const_cast< ProrateDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int ProrateDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
