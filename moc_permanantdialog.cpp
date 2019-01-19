/****************************************************************************
** Meta object code from reading C++ file 'permanantdialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "permanantdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'permanantdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PermanantDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      22,   17,   16,   16, 0x0a,
      43,   16,   16,   16, 0x0a,
      71,   66,   16,   16, 0x0a,
      95,   16,   16,   16, 0x0a,
     114,  110,   16,   16, 0x0a,
     128,   16,   16,   16, 0x0a,
     139,   16,   16,   16, 0x0a,
     147,   16,   16,   16, 0x0a,
     165,   16,   16,   16, 0x0a,
     178,   16,   16,   16, 0x0a,
     205,   16,   16,   16, 0x0a,
     243,  231,   16,   16, 0x0a,
     281,   16,   16,   16, 0x0a,
     308,  302,   16,   16, 0x0a,
     334,   16,   16,   16, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_PermanantDialog[] = {
    "PermanantDialog\0\0type\0init(Customer::Type)\0"
    "populateCustomerList()\0text\0"
    "permListSearch(QString)\0autoLoadPerm()\0"
    "row\0loadItem(int)\0saveItem()\0reset()\0"
    "deletePermanent()\0showReport()\0"
    "loadCityStateZipFromCity()\0"
    "loadCityStateZipFromZip()\0zipCodeList\0"
    "autoLoadCityStateZip(vector<Address>)\0"
    "printMailingLabels()\0event\0"
    "keyPressEvent(QKeyEvent*)\0"
    "onPermNumLostFocus()\0"
};

void PermanantDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PermanantDialog *_t = static_cast<PermanantDialog *>(_o);
        switch (_id) {
        case 0: _t->init((*reinterpret_cast< Customer::Type(*)>(_a[1]))); break;
        case 1: _t->populateCustomerList(); break;
        case 2: _t->permListSearch((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->autoLoadPerm(); break;
        case 4: _t->loadItem((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->saveItem(); break;
        case 6: _t->reset(); break;
        case 7: _t->deletePermanent(); break;
        case 8: _t->showReport(); break;
        case 9: _t->loadCityStateZipFromCity(); break;
        case 10: _t->loadCityStateZipFromZip(); break;
        case 11: _t->autoLoadCityStateZip((*reinterpret_cast< vector<Address>(*)>(_a[1]))); break;
        case 12: _t->printMailingLabels(); break;
        case 13: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 14: _t->onPermNumLostFocus(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PermanantDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PermanantDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_PermanantDialog,
      qt_meta_data_PermanantDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PermanantDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PermanantDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PermanantDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PermanantDialog))
        return static_cast<void*>(const_cast< PermanantDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int PermanantDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
