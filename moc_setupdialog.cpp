/****************************************************************************
** Meta object code from reading C++ file 'setupdialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "setupdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'setupdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SetupDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      29,   12,   12,   12, 0x0a,
      47,   12,   12,   12, 0x0a,
      63,   12,   12,   12, 0x0a,
      89,   12,   12,   12, 0x0a,
     114,   12,   12,   12, 0x0a,
     132,   12,   12,   12, 0x0a,
     157,   12,   12,   12, 0x0a,
     172,   12,   12,   12, 0x0a,
     192,   12,   12,   12, 0x0a,
     210,   12,   12,   12, 0x0a,
     227,   12,   12,   12, 0x0a,
     244,   12,   12,   12, 0x0a,
     263,   12,   12,   12, 0x0a,
     284,   12,   12,   12, 0x0a,
     302,   12,   12,   12, 0x0a,
     320,   12,   12,   12, 0x0a,
     344,   12,   12,   12, 0x0a,
     365,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SetupDialog[] = {
    "SetupDialog\0\0startCommEdit()\0"
    "startChargeEdit()\0startCodeEdit()\0"
    "startSellerInvoiceSetup()\0"
    "startBuyerInvoiceSetup()\0startCheckSetup()\0"
    "startMarketReportSetup()\0setupPrinter()\0"
    "extrasSetupDialog()\0startScaleSetup()\0"
    "loadMarketInfo()\0saveMarketInfo()\0"
    "startReportSetup()\0startDisplaysSetup()\0"
    "loadWebAuctions()\0saveWebAuctions()\0"
    "startVideoCameraSetup()\0startFaxModemSetup()\0"
    "startSaleManagerSetup()\0"
};

void SetupDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SetupDialog *_t = static_cast<SetupDialog *>(_o);
        switch (_id) {
        case 0: _t->startCommEdit(); break;
        case 1: _t->startChargeEdit(); break;
        case 2: _t->startCodeEdit(); break;
        case 3: _t->startSellerInvoiceSetup(); break;
        case 4: _t->startBuyerInvoiceSetup(); break;
        case 5: _t->startCheckSetup(); break;
        case 6: _t->startMarketReportSetup(); break;
        case 7: _t->setupPrinter(); break;
        case 8: _t->extrasSetupDialog(); break;
        case 9: _t->startScaleSetup(); break;
        case 10: _t->loadMarketInfo(); break;
        case 11: _t->saveMarketInfo(); break;
        case 12: _t->startReportSetup(); break;
        case 13: _t->startDisplaysSetup(); break;
        case 14: _t->loadWebAuctions(); break;
        case 15: _t->saveWebAuctions(); break;
        case 16: _t->startVideoCameraSetup(); break;
        case 17: _t->startFaxModemSetup(); break;
        case 18: _t->startSaleManagerSetup(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData SetupDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SetupDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SetupDialog,
      qt_meta_data_SetupDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SetupDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SetupDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SetupDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SetupDialog))
        return static_cast<void*>(const_cast< SetupDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int SetupDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
