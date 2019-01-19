/****************************************************************************
** Meta object code from reading C++ file 'chargeadjustmentdialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "chargeadjustmentdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chargeadjustmentdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ChargeAdjustmentDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      32,   24,   23,   23, 0x0a,
      58,   47,   23,   23, 0x0a,
      97,   88,   23,   23, 0x0a,
     114,   23,   23,   23, 0x0a,
     135,   23,   23,   23, 0x0a,
     144,   23,   23,   23, 0x0a,
     160,   23,   23,   23, 0x0a,
     198,  190,   23,   23, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ChargeAdjustmentDialog[] = {
    "ChargeAdjustmentDialog\0\0invoice\0"
    "init(Invoice*)\0invoiceDao\0"
    "setInvoiceDAORef(InvoiceDAO*)\0selected\0"
    "changeGroup(int)\0populateChargeList()\0"
    "accept()\0creditCharges()\0"
    "doCalclulateBuyerCommission()\0isBuyer\0"
    "setIsBuyer(bool)\0"
};

void ChargeAdjustmentDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ChargeAdjustmentDialog *_t = static_cast<ChargeAdjustmentDialog *>(_o);
        switch (_id) {
        case 0: _t->init((*reinterpret_cast< Invoice*(*)>(_a[1]))); break;
        case 1: _t->setInvoiceDAORef((*reinterpret_cast< InvoiceDAO*(*)>(_a[1]))); break;
        case 2: _t->changeGroup((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->populateChargeList(); break;
        case 4: _t->accept(); break;
        case 5: _t->creditCharges(); break;
        case 6: _t->doCalclulateBuyerCommission(); break;
        case 7: _t->setIsBuyer((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ChargeAdjustmentDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ChargeAdjustmentDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ChargeAdjustmentDialog,
      qt_meta_data_ChargeAdjustmentDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ChargeAdjustmentDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ChargeAdjustmentDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ChargeAdjustmentDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ChargeAdjustmentDialog))
        return static_cast<void*>(const_cast< ChargeAdjustmentDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int ChargeAdjustmentDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
