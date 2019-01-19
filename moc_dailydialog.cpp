/****************************************************************************
** Meta object code from reading C++ file 'dailydialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dailydialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dailydialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DailyDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      31,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   13,   12,   12, 0x0a,
      40,   12,   12,   12, 0x0a,
      49,   12,   12,   12, 0x0a,
      82,   69,   12,   12, 0x0a,
     115,  109,   12,   12, 0x0a,
     157,  137,   12,   12, 0x0a,
     182,   12,   12,   12, 0x0a,
     194,   12,   12,   12, 0x0a,
     215,   12,   12,   12, 0x0a,
     241,  236,   12,   12, 0x0a,
     280,  267,   12,   12, 0x0a,
     301,   12,   12,   12, 0x0a,
     314,   12,   12,   12, 0x0a,
     336,  327,   12,   12, 0x0a,
     358,   12,   12,   12, 0x0a,
     381,  377,   12,   12, 0x0a,
     404,   12,   12,   12, 0x0a,
     428,   12,   12,   12, 0x0a,
     444,   12,   12,   12, 0x0a,
     459,   12,   12,   12, 0x0a,
     477,  236,   12,   12, 0x0a,
     498,   12,   12,   12, 0x0a,
     513,   12,   12,   12, 0x0a,
     540,   12,   12,   12, 0x0a,
     578,  566,   12,   12, 0x0a,
     616,   12,   12,   12, 0x0a,
     638,  629,   12,   12, 0x0a,
     664,   12,   12,   12, 0x0a,
     675,   12,   12,   12, 0x0a,
     709,  700,   12,   12, 0x0a,
     734,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_DailyDialog[] = {
    "DailyDialog\0\0e\0timerEvent(QTimerEvent*)\0"
    "polish()\0populateDailyList()\0selectNumber\0"
    "populateDailyList(QString)\0index\0"
    "loadItemFromList(int)\0customer,loadNumber\0"
    "showDaily(Customer,bool)\0saveDaily()\0"
    "removeCurrentDaily()\0searchListByNumber()\0"
    "text\0searchListByName(QString)\0"
    "customerType\0init(Customer::Type)\0"
    "clearDaily()\0resetDaily()\0buttonId\0"
    "changeDialogMode(int)\0populatePermList()\0"
    "row\0loadDailyFromPerm(int)\0"
    "startChargeAdjustment()\0startTrucking()\0"
    "startTagEdit()\0showDailyReport()\0"
    "findNearest(QString)\0autoLoadPerm()\0"
    "loadCityStateZipFromCity()\0"
    "loadCityStateZipFromZip()\0zipCodeList\0"
    "autoLoadCityStateZip(vector<Address>)\0"
    "mergeDaily()\0keyPress\0keyPressEvent(QKeyEvent*)\0"
    "startVet()\0displayAnimalCodeDescr()\0"
    "funcName\0showCustomerType(string)\0"
    "showMissingBuyers()\0"
};

void DailyDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DailyDialog *_t = static_cast<DailyDialog *>(_o);
        switch (_id) {
        case 0: _t->timerEvent((*reinterpret_cast< QTimerEvent*(*)>(_a[1]))); break;
        case 1: _t->polish(); break;
        case 2: _t->populateDailyList(); break;
        case 3: _t->populateDailyList((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->loadItemFromList((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->showDaily((*reinterpret_cast< Customer(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 6: _t->saveDaily(); break;
        case 7: _t->removeCurrentDaily(); break;
        case 8: _t->searchListByNumber(); break;
        case 9: _t->searchListByName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->init((*reinterpret_cast< Customer::Type(*)>(_a[1]))); break;
        case 11: _t->clearDaily(); break;
        case 12: _t->resetDaily(); break;
        case 13: _t->changeDialogMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->populatePermList(); break;
        case 15: _t->loadDailyFromPerm((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->startChargeAdjustment(); break;
        case 17: _t->startTrucking(); break;
        case 18: _t->startTagEdit(); break;
        case 19: _t->showDailyReport(); break;
        case 20: _t->findNearest((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 21: _t->autoLoadPerm(); break;
        case 22: _t->loadCityStateZipFromCity(); break;
        case 23: _t->loadCityStateZipFromZip(); break;
        case 24: _t->autoLoadCityStateZip((*reinterpret_cast< vector<Address>(*)>(_a[1]))); break;
        case 25: _t->mergeDaily(); break;
        case 26: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 27: _t->startVet(); break;
        case 28: _t->displayAnimalCodeDescr(); break;
        case 29: _t->showCustomerType((*reinterpret_cast< const string(*)>(_a[1]))); break;
        case 30: _t->showMissingBuyers(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DailyDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DailyDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DailyDialog,
      qt_meta_data_DailyDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DailyDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DailyDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DailyDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DailyDialog))
        return static_cast<void*>(const_cast< DailyDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int DailyDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 31)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 31;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
