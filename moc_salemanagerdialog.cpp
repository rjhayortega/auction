/****************************************************************************
** Meta object code from reading C++ file 'salemanagerdialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "salemanagerdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'salemanagerdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SaleManagerDialog[] = {

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
      19,   18,   18,   18, 0x0a,
      38,   18,   18,   18, 0x0a,
      50,   18,   18,   18, 0x0a,
      64,   60,   18,   18, 0x0a,
      92,   87,   18,   18, 0x0a,
     119,   18,  115,   18, 0x0a,
     137,   18,   18,   18, 0x0a,
     156,   18,   18,   18, 0x0a,
     175,   18,  115,   18, 0x0a,
     192,   18,   18,   18, 0x0a,
     212,   18,  204,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SaleManagerDialog[] = {
    "SaleManagerDialog\0\0populateSaleList()\0"
    "createNew()\0saveNew()\0row\0"
    "changeCurrentSale(int)\0date\0"
    "keepDateCurrent(QDate)\0int\0getCurrentIndex()\0"
    "closeCurrentSale()\0openSelectedSale()\0"
    "checkSelection()\0setActive()\0QString\0"
    "getPassword()\0"
};

void SaleManagerDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SaleManagerDialog *_t = static_cast<SaleManagerDialog *>(_o);
        switch (_id) {
        case 0: _t->populateSaleList(); break;
        case 1: _t->createNew(); break;
        case 2: _t->saveNew(); break;
        case 3: _t->changeCurrentSale((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->keepDateCurrent((*reinterpret_cast< QDate(*)>(_a[1]))); break;
        case 5: { int _r = _t->getCurrentIndex();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 6: _t->closeCurrentSale(); break;
        case 7: _t->openSelectedSale(); break;
        case 8: { int _r = _t->checkSelection();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 9: _t->setActive(); break;
        case 10: { QString _r = _t->getPassword();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SaleManagerDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SaleManagerDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SaleManagerDialog,
      qt_meta_data_SaleManagerDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SaleManagerDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SaleManagerDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SaleManagerDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SaleManagerDialog))
        return static_cast<void*>(const_cast< SaleManagerDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int SaleManagerDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
