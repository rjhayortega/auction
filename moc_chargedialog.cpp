/****************************************************************************
** Meta object code from reading C++ file 'chargedialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "chargedialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chargedialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ChargeDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x0a,
      35,   13,   13,   13, 0x0a,
      50,   13,   13,   13, 0x0a,
      67,   13,   13,   13, 0x0a,
      98,   87,   13,   13, 0x0a,
     121,   13,   13,   13, 0x0a,
     135,   13,   13,   13, 0x0a,
     162,  152,   13,   13, 0x0a,
     193,   13,   13,   13, 0x0a,
     222,  215,   13,   13, 0x0a,
     249,  244,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ChargeDialog[] = {
    "ChargeDialog\0\0populateChargeList()\0"
    "moveChargeUp()\0moveChargeDown()\0"
    "saveCurrentCharge()\0currentRow\0"
    "loadCurrentCharge(int)\0resetCharge()\0"
    "clearCodeTable()\0col,check\0"
    "checkCodeTableColumn(int,bool)\0"
    "deleteCurrentCharge()\0charge\0"
    "loadCodeTable(Charge)\0text\0"
    "checkColumns(QString)\0"
};

void ChargeDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ChargeDialog *_t = static_cast<ChargeDialog *>(_o);
        switch (_id) {
        case 0: _t->populateChargeList(); break;
        case 1: _t->moveChargeUp(); break;
        case 2: _t->moveChargeDown(); break;
        case 3: _t->saveCurrentCharge(); break;
        case 4: _t->loadCurrentCharge((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->resetCharge(); break;
        case 6: _t->clearCodeTable(); break;
        case 7: _t->checkCodeTableColumn((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 8: _t->deleteCurrentCharge(); break;
        case 9: _t->loadCodeTable((*reinterpret_cast< Charge(*)>(_a[1]))); break;
        case 10: _t->checkColumns((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ChargeDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ChargeDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ChargeDialog,
      qt_meta_data_ChargeDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ChargeDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ChargeDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ChargeDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ChargeDialog))
        return static_cast<void*>(const_cast< ChargeDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int ChargeDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
