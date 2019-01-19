/****************************************************************************
** Meta object code from reading C++ file 'invoicedialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "invoicedialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'invoicedialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_InvoiceDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      28,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   15,   14,   14, 0x0a,
      45,   14,   14,   14, 0x0a,
      65,   14,   14,   14, 0x0a,
      83,   14,   14,   14, 0x0a,
      97,   14,   14,   14, 0x0a,
     119,   14,   14,   14, 0x0a,
     141,  133,   14,   14, 0x0a,
     173,   14,   14,   14, 0x0a,
     188,   14,   14,   14, 0x0a,
     215,   14,  210,   14, 0x0a,
     239,   14,   14,   14, 0x0a,
     258,   14,   14,   14, 0x0a,
     282,  273,   14,   14, 0x0a,
     306,   14,   14,   14, 0x0a,
     324,   14,   14,   14, 0x0a,
     339,   14,   14,   14, 0x0a,
     357,   14,   14,   14, 0x0a,
     374,   14,   14,   14, 0x0a,
     401,   14,   14,   14, 0x0a,
     439,  427,   14,   14, 0x0a,
     477,   14,   14,   14, 0x0a,
     497,   14,   14,   14, 0x0a,
     515,   14,   14,   14, 0x0a,
     528,   14,   14,   14, 0x0a,
     547,   14,   14,   14, 0x0a,
     565,   14,   14,   14, 0x0a,
     580,   14,  210,   14, 0x0a,
     600,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_InvoiceDialog[] = {
    "InvoiceDialog\0\0custType\0init(Customer::Type)\0"
    "loadInvoiceFromId()\0initInvoiceById()\0"
    "showInvoice()\0saveCustomerAsDaily()\0"
    "showPreview()\0row,col\0"
    "editClickedTransaction(int,int)\0"
    "printInvoice()\0startTruckingDialog()\0"
    "bool\0startChargeAdjustment()\0"
    "showReadySellers()\0startProrate()\0"
    "buttonId\0changeCustomerType(int)\0"
    "startBuyerRecap()\0resetInvoice()\0"
    "startPermSearch()\0loadNumberList()\0"
    "loadCityStateZipFromCity()\0"
    "loadCityStateZipFromZip()\0zipCodeList\0"
    "autoLoadCityStateZip(vector<Address>)\0"
    "globalBuyerChange()\0globalPenChange()\0"
    "faxInvoice()\0setInvoiceStatus()\0"
    "overrideAddress()\0emailInvoice()\0"
    "fileExists(QString)\0showMissingBuyers()\0"
};

void InvoiceDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        InvoiceDialog *_t = static_cast<InvoiceDialog *>(_o);
        switch (_id) {
        case 0: _t->init((*reinterpret_cast< Customer::Type(*)>(_a[1]))); break;
        case 1: _t->loadInvoiceFromId(); break;
        case 2: _t->initInvoiceById(); break;
        case 3: _t->showInvoice(); break;
        case 4: _t->saveCustomerAsDaily(); break;
        case 5: _t->showPreview(); break;
        case 6: _t->editClickedTransaction((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->printInvoice(); break;
        case 8: _t->startTruckingDialog(); break;
        case 9: { bool _r = _t->startChargeAdjustment();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 10: _t->showReadySellers(); break;
        case 11: _t->startProrate(); break;
        case 12: _t->changeCustomerType((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->startBuyerRecap(); break;
        case 14: _t->resetInvoice(); break;
        case 15: _t->startPermSearch(); break;
        case 16: _t->loadNumberList(); break;
        case 17: _t->loadCityStateZipFromCity(); break;
        case 18: _t->loadCityStateZipFromZip(); break;
        case 19: _t->autoLoadCityStateZip((*reinterpret_cast< vector<Address>(*)>(_a[1]))); break;
        case 20: _t->globalBuyerChange(); break;
        case 21: _t->globalPenChange(); break;
        case 22: _t->faxInvoice(); break;
        case 23: _t->setInvoiceStatus(); break;
        case 24: _t->overrideAddress(); break;
        case 25: _t->emailInvoice(); break;
        case 26: { bool _r = _t->fileExists((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 27: _t->showMissingBuyers(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData InvoiceDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject InvoiceDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_InvoiceDialog,
      qt_meta_data_InvoiceDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &InvoiceDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *InvoiceDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *InvoiceDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_InvoiceDialog))
        return static_cast<void*>(const_cast< InvoiceDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int InvoiceDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 28)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 28;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
