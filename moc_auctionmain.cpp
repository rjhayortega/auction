/****************************************************************************
** Meta object code from reading C++ file 'auctionmain.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "auctionmain.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'auctionmain.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AuctionMain[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      38,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      53,   32,   12,   12, 0x0a,
      92,   12,   12,   12, 0x0a,
     105,   12,   12,   12, 0x0a,
     126,   12,   12,   12, 0x0a,
     145,   12,   12,   12, 0x0a,
     171,   12,   12,   12, 0x0a,
     188,   12,   12,   12, 0x0a,
     210,   12,   12,   12, 0x0a,
     224,   12,   12,   12, 0x0a,
     242,   12,   12,   12, 0x0a,
     254,   12,   12,   12, 0x0a,
     273,   12,   12,   12, 0x0a,
     290,   12,   12,   12, 0x0a,
     310,   12,   12,   12, 0x0a,
     326,   12,   12,   12, 0x0a,
     342,   12,   12,   12, 0x0a,
     360,   12,   12,   12, 0x0a,
     392,   12,   12,   12, 0x0a,
     419,   12,   12,   12, 0x0a,
     446,  444,   12,   12, 0x0a,
     471,   12,   12,   12, 0x0a,
     480,   12,   12,   12, 0x0a,
     520,  500,   12,   12, 0x0a,
     558,   12,   12,   12, 0x0a,
     568,  500,   12,   12, 0x0a,
     612,   12,   12,   12, 0x0a,
     641,   12,   12,   12, 0x0a,
     663,   12,   12,   12, 0x0a,
     683,   12,   12,   12, 0x0a,
     704,   12,   12,   12, 0x0a,
     719,   12,   12,   12, 0x0a,
     736,   12,   12,   12, 0x0a,
     758,   12,   12,   12, 0x0a,
     776,   12,   12,   12, 0x0a,
     800,  794,   12,   12, 0x0a,
     826,   12,   12,   12, 0x0a,
     860,  854,   12,   12, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_AuctionMain[] = {
    "AuctionMain\0\0updateStatistics()\0"
    "applicationReference\0"
    "setApplicationReference(QApplication*)\0"
    "startDaily()\0startSellerInvoice()\0"
    "startSetupDialog()\0startTransactionBrowser()\0"
    "startCheckEdit()\0toggleSQLDebugLevel()\0"
    "showSummary()\0showDiscrepancy()\0"
    "startPerm()\0startSaleManager()\0"
    "showBuyerRecap()\0startMarketReport()\0"
    "showTagReport()\0showPenReport()\0"
    "startLienImport()\0startBuyerAccountsReceiveable()\0"
    "startTruckerChecksDialog()\0"
    "startBuyerChecksDialog()\0e\0"
    "timerEvent(QTimerEvent*)\0backup()\0"
    "readBackupProcess()\0exitCode,exitStatus\0"
    "writeBackup(int,QProcess::ExitStatus)\0"
    "restore()\0autoRestoreCursor(int,QProcess::ExitStatus)\0"
    "startBuyerCommissionReport()\0"
    "startTruckingReport()\0showDetailSummary()\0"
    "startCheckTransfer()\0startHistory()\0"
    "startBrandEdit()\0startDatabaseRepair()\0"
    "startTagBrowser()\0startBuyerCount()\0"
    "event\0keyPressEvent(QKeyEvent*)\0"
    "startVetInspectionManager()\0state\0"
    "onCameraRecording(bool)\0"
};

void AuctionMain::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AuctionMain *_t = static_cast<AuctionMain *>(_o);
        switch (_id) {
        case 0: _t->updateStatistics(); break;
        case 1: _t->setApplicationReference((*reinterpret_cast< QApplication*(*)>(_a[1]))); break;
        case 2: _t->startDaily(); break;
        case 3: _t->startSellerInvoice(); break;
        case 4: _t->startSetupDialog(); break;
        case 5: _t->startTransactionBrowser(); break;
        case 6: _t->startCheckEdit(); break;
        case 7: _t->toggleSQLDebugLevel(); break;
        case 8: _t->showSummary(); break;
        case 9: _t->showDiscrepancy(); break;
        case 10: _t->startPerm(); break;
        case 11: _t->startSaleManager(); break;
        case 12: _t->showBuyerRecap(); break;
        case 13: _t->startMarketReport(); break;
        case 14: _t->showTagReport(); break;
        case 15: _t->showPenReport(); break;
        case 16: _t->startLienImport(); break;
        case 17: _t->startBuyerAccountsReceiveable(); break;
        case 18: _t->startTruckerChecksDialog(); break;
        case 19: _t->startBuyerChecksDialog(); break;
        case 20: _t->timerEvent((*reinterpret_cast< QTimerEvent*(*)>(_a[1]))); break;
        case 21: _t->backup(); break;
        case 22: _t->readBackupProcess(); break;
        case 23: _t->writeBackup((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        case 24: _t->restore(); break;
        case 25: _t->autoRestoreCursor((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        case 26: _t->startBuyerCommissionReport(); break;
        case 27: _t->startTruckingReport(); break;
        case 28: _t->showDetailSummary(); break;
        case 29: _t->startCheckTransfer(); break;
        case 30: _t->startHistory(); break;
        case 31: _t->startBrandEdit(); break;
        case 32: _t->startDatabaseRepair(); break;
        case 33: _t->startTagBrowser(); break;
        case 34: _t->startBuyerCount(); break;
        case 35: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 36: _t->startVetInspectionManager(); break;
        case 37: _t->onCameraRecording((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData AuctionMain::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AuctionMain::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_AuctionMain,
      qt_meta_data_AuctionMain, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AuctionMain::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AuctionMain::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AuctionMain::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AuctionMain))
        return static_cast<void*>(const_cast< AuctionMain*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int AuctionMain::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 38)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 38;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
