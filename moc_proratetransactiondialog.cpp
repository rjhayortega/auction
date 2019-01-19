/****************************************************************************
** Meta object code from reading C++ file 'proratetransactiondialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "proratetransactiondialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'proratetransactiondialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ProrateTransactionDialog[] = {

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
      59,   26,   25,   25, 0x0a,
     127,  106,   25,   25, 0x0a,
     177,  159,   25,   25, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ProrateTransactionDialog[] = {
    "ProrateTransactionDialog\0\0"
    "transactionList,proratedList,row\0"
    "init(vector<Transaction>,vector<Prorate>,uint)\0"
    "prorate,currentPayee\0"
    "addProrateToTable(Prorate,bool)\0"
    "data,currentPayee\0addDataToTable(Prorate::Data,bool)\0"
};

void ProrateTransactionDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ProrateTransactionDialog *_t = static_cast<ProrateTransactionDialog *>(_o);
        switch (_id) {
        case 0: _t->init((*reinterpret_cast< vector<Transaction>(*)>(_a[1])),(*reinterpret_cast< vector<Prorate>(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3]))); break;
        case 1: _t->addProrateToTable((*reinterpret_cast< Prorate(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->addDataToTable((*reinterpret_cast< Prorate::Data(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ProrateTransactionDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ProrateTransactionDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ProrateTransactionDialog,
      qt_meta_data_ProrateTransactionDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ProrateTransactionDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ProrateTransactionDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ProrateTransactionDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ProrateTransactionDialog))
        return static_cast<void*>(const_cast< ProrateTransactionDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int ProrateTransactionDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
