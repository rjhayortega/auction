/****************************************************************************
** Meta object code from reading C++ file 'checkregister.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "checkregister.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'checkregister.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CheckRegister[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x0a,
      26,   14,   14,   14, 0x0a,
      46,   14,   14,   14, 0x0a,
      67,   62,   14,   14, 0x0a,
      98,   94,   14,   14, 0x0a,
     113,   14,   14,   14, 0x0a,
     134,   14,   14,   14, 0x0a,
     159,   14,   14,   14, 0x0a,
     186,  179,   14,   14, 0x0a,
     219,   14,   14,   14, 0x0a,
     241,   14,   14,   14, 0x0a,
     254,   62,   14,   14, 0x0a,
     283,   14,   14,   14, 0x0a,
     302,   14,   14,   14, 0x0a,
     319,   14,   14,   14, 0x0a,
     334,   14,   14,   14, 0x0a,
     350,   14,   14,   14, 0x0a,
     367,   14,   14,   14, 0x0a,
     394,   14,   14,   14, 0x0a,
     412,   14,   14,   14, 0x0a,
     435,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CheckRegister[] = {
    "CheckRegister\0\0newCheck()\0populateCheckList()\0"
    "showCheckList()\0item\0editCheck(Q3ListViewItem*)\0"
    "row\0editCheck(int)\0setSelectedCleared()\0"
    "setSelectedOutstanding()\0setSelectedVoided()\0"
    "status\0setSelectedStatus(Check::STATUS)\0"
    "populateDepositList()\0newDeposit()\0"
    "editDeposit(Q3ListViewItem*)\0"
    "calculateSummary()\0setNextCheckNo()\0"
    "deleteChecks()\0printRegister()\0"
    "startCheckPost()\0handleCheckNumberRequest()\0"
    "setNumberOption()\0sortCheckListByIndex()\0"
    "searchChecksByIndex()\0"
};

void CheckRegister::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CheckRegister *_t = static_cast<CheckRegister *>(_o);
        switch (_id) {
        case 0: _t->newCheck(); break;
        case 1: _t->populateCheckList(); break;
        case 2: _t->showCheckList(); break;
        case 3: _t->editCheck((*reinterpret_cast< Q3ListViewItem*(*)>(_a[1]))); break;
        case 4: _t->editCheck((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->setSelectedCleared(); break;
        case 6: _t->setSelectedOutstanding(); break;
        case 7: _t->setSelectedVoided(); break;
        case 8: _t->setSelectedStatus((*reinterpret_cast< Check::STATUS(*)>(_a[1]))); break;
        case 9: _t->populateDepositList(); break;
        case 10: _t->newDeposit(); break;
        case 11: _t->editDeposit((*reinterpret_cast< Q3ListViewItem*(*)>(_a[1]))); break;
        case 12: _t->calculateSummary(); break;
        case 13: _t->setNextCheckNo(); break;
        case 14: _t->deleteChecks(); break;
        case 15: _t->printRegister(); break;
        case 16: _t->startCheckPost(); break;
        case 17: _t->handleCheckNumberRequest(); break;
        case 18: _t->setNumberOption(); break;
        case 19: _t->sortCheckListByIndex(); break;
        case 20: _t->searchChecksByIndex(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CheckRegister::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CheckRegister::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CheckRegister,
      qt_meta_data_CheckRegister, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CheckRegister::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CheckRegister::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CheckRegister::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CheckRegister))
        return static_cast<void*>(const_cast< CheckRegister*>(this));
    return QDialog::qt_metacast(_clname);
}

int CheckRegister::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
