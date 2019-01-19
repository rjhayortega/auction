/****************************************************************************
** Meta object code from reading C++ file 'tablerepairdialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "tablerepairdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tablerepairdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TableRepairDialog[] = {

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
      19,   18,   18,   18, 0x0a,
      36,   18,   18,   18, 0x0a,
      55,   18,   18,   18, 0x0a,
      80,   18,   18,   18, 0x0a,
     106,   18,   18,   18, 0x0a,
     127,   18,   18,   18, 0x0a,
     147,   18,   18,   18, 0x0a,
     165,   18,   18,   18, 0x0a,
     190,   18,   18,   18, 0x0a,
     213,   18,   18,   18, 0x0a,
     235,   18,   18,   18, 0x0a,
     257,   18,   18,   18, 0x0a,
     285,   18,   18,   18, 0x0a,
     312,   18,   18,   18, 0x0a,
     331,   18,   18,   18, 0x0a,
     357,   18,   18,   18, 0x0a,
     378,   18,   18,   18, 0x0a,
     399,   18,   18,   18, 0x0a,
     443,  417,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TableRepairDialog[] = {
    "TableRepairDialog\0\0repairTagTable()\0"
    "repairBrandTable()\0repairDailyBuyerTables()\0"
    "repairDailySellerTables()\0"
    "repairChargeTables()\0repairCheckTables()\0"
    "repairCodeTable()\0repairCommissionTables()\0"
    "repairPermanantTable()\0repairPrinterTables()\0"
    "repairDisplayTables()\0repairSellerInvoiceTables()\0"
    "repairBuyerInvoiceTables()\0"
    "repairSetupTable()\0repairTransactionTables()\0"
    "repairTruckinTable()\0repairZipCodeTable()\0"
    "repairAllTables()\0tableList,listDescription\0"
    "repairTableList(QStringList,QString)\0"
};

void TableRepairDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TableRepairDialog *_t = static_cast<TableRepairDialog *>(_o);
        switch (_id) {
        case 0: _t->repairTagTable(); break;
        case 1: _t->repairBrandTable(); break;
        case 2: _t->repairDailyBuyerTables(); break;
        case 3: _t->repairDailySellerTables(); break;
        case 4: _t->repairChargeTables(); break;
        case 5: _t->repairCheckTables(); break;
        case 6: _t->repairCodeTable(); break;
        case 7: _t->repairCommissionTables(); break;
        case 8: _t->repairPermanantTable(); break;
        case 9: _t->repairPrinterTables(); break;
        case 10: _t->repairDisplayTables(); break;
        case 11: _t->repairSellerInvoiceTables(); break;
        case 12: _t->repairBuyerInvoiceTables(); break;
        case 13: _t->repairSetupTable(); break;
        case 14: _t->repairTransactionTables(); break;
        case 15: _t->repairTruckinTable(); break;
        case 16: _t->repairZipCodeTable(); break;
        case 17: _t->repairAllTables(); break;
        case 18: _t->repairTableList((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData TableRepairDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TableRepairDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_TableRepairDialog,
      qt_meta_data_TableRepairDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TableRepairDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TableRepairDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TableRepairDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TableRepairDialog))
        return static_cast<void*>(const_cast< TableRepairDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int TableRepairDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
