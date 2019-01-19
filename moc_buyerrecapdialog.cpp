/****************************************************************************
** Meta object code from reading C++ file 'buyerrecapdialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "buyerrecapdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'buyerrecapdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BuyerRecapDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      39,   17,   18,   17, 0x08,
      62,   17,   17,   17, 0x08,
      79,   17,   17,   17, 0x08,
      93,   17,   17,   17, 0x08,
     111,  105,   17,   17, 0x08,
     136,   17,   17,   17, 0x08,
     147,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_BuyerRecapDialog[] = {
    "BuyerRecapDialog\0\0vector<ChargeRecord>\0"
    "getBuyerRecapCharges()\0generateReport()\0"
    "printBuyers()\0allBuyers()\0index\0"
    "removeBuyer(QModelIndex)\0addBuyer()\0"
    "faxBuyers()\0"
};

void BuyerRecapDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        BuyerRecapDialog *_t = static_cast<BuyerRecapDialog *>(_o);
        switch (_id) {
        case 0: { vector<ChargeRecord> _r = _t->getBuyerRecapCharges();
            if (_a[0]) *reinterpret_cast< vector<ChargeRecord>*>(_a[0]) = _r; }  break;
        case 1: _t->generateReport(); break;
        case 2: _t->printBuyers(); break;
        case 3: _t->allBuyers(); break;
        case 4: _t->removeBuyer((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 5: _t->addBuyer(); break;
        case 6: _t->faxBuyers(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData BuyerRecapDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject BuyerRecapDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_BuyerRecapDialog,
      qt_meta_data_BuyerRecapDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BuyerRecapDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BuyerRecapDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BuyerRecapDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BuyerRecapDialog))
        return static_cast<void*>(const_cast< BuyerRecapDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int BuyerRecapDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
