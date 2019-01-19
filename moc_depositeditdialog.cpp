/****************************************************************************
** Meta object code from reading C++ file 'depositeditdialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "depositeditdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'depositeditdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DepositEditDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      27,   19,   18,   18, 0x0a,
      41,   18,   18,   18, 0x0a,
      55,   18,   18,   18, 0x0a,
      73,   18,   18,   18, 0x0a,
      86,   18,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_DepositEditDialog[] = {
    "DepositEditDialog\0\0deposit\0init(Deposit)\0"
    "saveCleared()\0saveOutstanding()\0"
    "saveVoided()\0saveDeposit()\0"
};

void DepositEditDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DepositEditDialog *_t = static_cast<DepositEditDialog *>(_o);
        switch (_id) {
        case 0: _t->init((*reinterpret_cast< Deposit(*)>(_a[1]))); break;
        case 1: _t->saveCleared(); break;
        case 2: _t->saveOutstanding(); break;
        case 3: _t->saveVoided(); break;
        case 4: _t->saveDeposit(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DepositEditDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DepositEditDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DepositEditDialog,
      qt_meta_data_DepositEditDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DepositEditDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DepositEditDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DepositEditDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DepositEditDialog))
        return static_cast<void*>(const_cast< DepositEditDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int DepositEditDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
