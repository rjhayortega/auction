/****************************************************************************
** Meta object code from reading C++ file 'readysellerdialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "readysellerdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'readysellerdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ReadySellerDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      30,   19,   18,   18, 0x0a,
      50,   18,   18,   18, 0x0a,
      74,   70,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ReadySellerDialog[] = {
    "ReadySellerDialog\0\0invoiceDao\0"
    "setDAO(InvoiceDAO*)\0populateReadyList()\0"
    "row\0accept(int)\0"
};

void ReadySellerDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ReadySellerDialog *_t = static_cast<ReadySellerDialog *>(_o);
        switch (_id) {
        case 0: _t->setDAO((*reinterpret_cast< InvoiceDAO*(*)>(_a[1]))); break;
        case 1: _t->populateReadyList(); break;
        case 2: _t->accept((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ReadySellerDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ReadySellerDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ReadySellerDialog,
      qt_meta_data_ReadySellerDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ReadySellerDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ReadySellerDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ReadySellerDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ReadySellerDialog))
        return static_cast<void*>(const_cast< ReadySellerDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int ReadySellerDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
