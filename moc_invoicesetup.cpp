/****************************************************************************
** Meta object code from reading C++ file 'invoicesetup.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "invoicesetup.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'invoicesetup.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_InvoiceSetup[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      23,   14,   13,   13, 0x0a,
      44,   13,   13,   13, 0x0a,
      51,   13,   13,   13, 0x0a,
      65,   58,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_InvoiceSetup[] = {
    "InvoiceSetup\0\0custType\0init(Customer::Type)\0"
    "load()\0save()\0enable\0"
    "enableCheckOnInvoiceOptions(bool)\0"
};

void InvoiceSetup::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        InvoiceSetup *_t = static_cast<InvoiceSetup *>(_o);
        switch (_id) {
        case 0: _t->init((*reinterpret_cast< Customer::Type(*)>(_a[1]))); break;
        case 1: _t->load(); break;
        case 2: _t->save(); break;
        case 3: _t->enableCheckOnInvoiceOptions((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData InvoiceSetup::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject InvoiceSetup::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_InvoiceSetup,
      qt_meta_data_InvoiceSetup, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &InvoiceSetup::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *InvoiceSetup::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *InvoiceSetup::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_InvoiceSetup))
        return static_cast<void*>(const_cast< InvoiceSetup*>(this));
    return QDialog::qt_metacast(_clname);
}

int InvoiceSetup::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
