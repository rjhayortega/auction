/****************************************************************************
** Meta object code from reading C++ file 'vetdialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "vetdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vetdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_VetDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      33,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   11,   10,   10, 0x0a,
      37,   10,   10,   10, 0x0a,
      54,   10,   10,   10, 0x0a,
      68,   10,   10,   10, 0x0a,
      86,   10,   10,   10, 0x0a,
      97,   10,   10,   10, 0x0a,
     117,  110,   10,   10, 0x0a,
     132,   10,   10,   10, 0x0a,
     168,   10,   10,   10, 0x0a,
     206,   10,   10,   10, 0x0a,
     236,   10,   10,   10, 0x0a,
     288,  275,   10,   10, 0x0a,
     331,  324,   10,   10, 0x0a,
     369,   10,   10,   10, 0x0a,
     378,   10,   10,   10, 0x0a,
     392,  387,   10,   10, 0x0a,
     421,   10,   10,   10, 0x0a,
     435,   10,   10,   10, 0x0a,
     451,   10,   10,   10, 0x0a,
     460,   10,   10,   10, 0x0a,
     474,   10,   10,   10, 0x0a,
     484,   10,   10,   10, 0x0a,
     505,   10,   10,   10, 0x0a,
     534,  324,   10,   10, 0x0a,
     575,  324,   10,   10, 0x0a,
     623,   10,   10,   10, 0x0a,
     654,  641,   10,   10, 0x0a,
     681,   10,   10,   10, 0x0a,
     701,   10,   10,   10, 0x0a,
     720,   10,   10,   10, 0x0a,
     738,   10,   10,   10, 0x0a,
     759,   10,   10,   10, 0x0a,
     786,  775,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_VetDialog[] = {
    "VetDialog\0\0seller\0initSeller(Seller)\0"
    "showCurrentTag()\0loadNextTag()\0"
    "loadPreviousTag()\0autoSave()\0browseTags()\0"
    "formId\0printForm(int)\0"
    "printSouthDakotaHealthCertificate()\0"
    "printMinnesotaVeterinaryCertificate()\0"
    "printTuberculosisTestRecord()\0"
    "printAlternateMinnesotaVetInspection()\0"
    "healthRecord\0printMinnesotaVetCert(HealthRecord)\0"
    "record\0printTuberculosisRecord(HealthRecord)\0"
    "reject()\0accept()\0data\0"
    "validateBrucellosis(QString)\0validateSex()\0"
    "setupTagToAdd()\0search()\0loadVetData()\0"
    "editVet()\0printAllflexReport()\0"
    "printBrucellosisTestRecord()\0"
    "printBrucellosisTestRecord(HealthRecord)\0"
    "printSouthDakotaHealthCertificate(HealthRecord)\0"
    "autoChangeIndex()\0cert,topSkip\0"
    "printForm(TextReport*,int)\0"
    "processLpstatData()\0setupPrinterList()\0"
    "editFormMetrics()\0loadVetFormMetrics()\0"
    "sellerSummary()\0vetPrinter\0"
    "updateVetPrinter(QString)\0"
};

void VetDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        VetDialog *_t = static_cast<VetDialog *>(_o);
        switch (_id) {
        case 0: _t->initSeller((*reinterpret_cast< Seller(*)>(_a[1]))); break;
        case 1: _t->showCurrentTag(); break;
        case 2: _t->loadNextTag(); break;
        case 3: _t->loadPreviousTag(); break;
        case 4: _t->autoSave(); break;
        case 5: _t->browseTags(); break;
        case 6: _t->printForm((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->printSouthDakotaHealthCertificate(); break;
        case 8: _t->printMinnesotaVeterinaryCertificate(); break;
        case 9: _t->printTuberculosisTestRecord(); break;
        case 10: _t->printAlternateMinnesotaVetInspection(); break;
        case 11: _t->printMinnesotaVetCert((*reinterpret_cast< HealthRecord(*)>(_a[1]))); break;
        case 12: _t->printTuberculosisRecord((*reinterpret_cast< HealthRecord(*)>(_a[1]))); break;
        case 13: _t->reject(); break;
        case 14: _t->accept(); break;
        case 15: _t->validateBrucellosis((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 16: _t->validateSex(); break;
        case 17: _t->setupTagToAdd(); break;
        case 18: _t->search(); break;
        case 19: _t->loadVetData(); break;
        case 20: _t->editVet(); break;
        case 21: _t->printAllflexReport(); break;
        case 22: _t->printBrucellosisTestRecord(); break;
        case 23: _t->printBrucellosisTestRecord((*reinterpret_cast< HealthRecord(*)>(_a[1]))); break;
        case 24: _t->printSouthDakotaHealthCertificate((*reinterpret_cast< HealthRecord(*)>(_a[1]))); break;
        case 25: _t->autoChangeIndex(); break;
        case 26: _t->printForm((*reinterpret_cast< TextReport*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 27: _t->processLpstatData(); break;
        case 28: _t->setupPrinterList(); break;
        case 29: _t->editFormMetrics(); break;
        case 30: _t->loadVetFormMetrics(); break;
        case 31: _t->sellerSummary(); break;
        case 32: _t->updateVetPrinter((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData VetDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject VetDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_VetDialog,
      qt_meta_data_VetDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &VetDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *VetDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *VetDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VetDialog))
        return static_cast<void*>(const_cast< VetDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int VetDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 33)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 33;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
