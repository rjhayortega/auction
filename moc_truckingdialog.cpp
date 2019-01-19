/****************************************************************************
** Meta object code from reading C++ file 'truckingdialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "truckingdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'truckingdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TruckingDialog[] = {

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
      16,   15,   15,   15, 0x0a,
      44,   23,   15,   15, 0x0a,
      79,   15,   15,   15, 0x0a,
      97,   15,   15,   15, 0x0a,
     112,   15,   15,   15, 0x0a,
     126,   15,   15,   15, 0x0a,
     152,  148,   15,   15, 0x0a,
     169,   15,   15,   15, 0x0a,
     178,   15,   15,   15, 0x0a,
     194,   15,   15,   15, 0x0a,
     202,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_TruckingDialog[] = {
    "TruckingDialog\0\0init()\0invoice,customerType\0"
    "init(Invoice,ChargeDAO::CUST_TYPE)\0"
    "autoSaveTrucker()\0reformatForm()\0"
    "saveTrucker()\0populateTruckerList()\0"
    "row\0loadTrucker(int)\0recalc()\0"
    "deleteTrucker()\0reset()\0destroy()\0"
};

void TruckingDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TruckingDialog *_t = static_cast<TruckingDialog *>(_o);
        switch (_id) {
        case 0: _t->init(); break;
        case 1: _t->init((*reinterpret_cast< Invoice(*)>(_a[1])),(*reinterpret_cast< ChargeDAO::CUST_TYPE(*)>(_a[2]))); break;
        case 2: _t->autoSaveTrucker(); break;
        case 3: _t->reformatForm(); break;
        case 4: _t->saveTrucker(); break;
        case 5: _t->populateTruckerList(); break;
        case 6: _t->loadTrucker((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->recalc(); break;
        case 8: _t->deleteTrucker(); break;
        case 9: _t->reset(); break;
        case 10: _t->destroy(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData TruckingDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TruckingDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_TruckingDialog,
      qt_meta_data_TruckingDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TruckingDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TruckingDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TruckingDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TruckingDialog))
        return static_cast<void*>(const_cast< TruckingDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int TruckingDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
