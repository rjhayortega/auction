/****************************************************************************
** Meta object code from reading C++ file 'truckerchecksdialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "truckerchecksdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'truckerchecksdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TruckerChecksDialog[] = {

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
      21,   20,   20,   20, 0x0a,
      81,   43,   20,   20, 0x0a,
     152,   20,   20,   20, 0x0a,
     191,  166,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TruckerChecksDialog[] = {
    "TruckerChecksDialog\0\0populateTruckerList()\0"
    "turckerList,truckingList,customerType\0"
    "populateTruckerList(Q3ListBox*,vector<TruckingRecord>&,Customer::Type)\0"
    "printChecks()\0truckerList,truckingList\0"
    "printChecks(Q3ListBox*,vector<TruckingRecord>)\0"
};

void TruckerChecksDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TruckerChecksDialog *_t = static_cast<TruckerChecksDialog *>(_o);
        switch (_id) {
        case 0: _t->populateTruckerList(); break;
        case 1: _t->populateTruckerList((*reinterpret_cast< Q3ListBox*(*)>(_a[1])),(*reinterpret_cast< vector<TruckingRecord>(*)>(_a[2])),(*reinterpret_cast< Customer::Type(*)>(_a[3]))); break;
        case 2: _t->printChecks(); break;
        case 3: _t->printChecks((*reinterpret_cast< Q3ListBox*(*)>(_a[1])),(*reinterpret_cast< vector<TruckingRecord>(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData TruckerChecksDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TruckerChecksDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_TruckerChecksDialog,
      qt_meta_data_TruckerChecksDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TruckerChecksDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TruckerChecksDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TruckerChecksDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TruckerChecksDialog))
        return static_cast<void*>(const_cast< TruckerChecksDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int TruckerChecksDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
