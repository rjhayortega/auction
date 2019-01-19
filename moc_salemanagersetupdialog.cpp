/****************************************************************************
** Meta object code from reading C++ file 'salemanagersetupdialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "salemanagersetupdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'salemanagersetupdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SaleManagerSetupDialog[] = {

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
      24,   23,   23,   23, 0x08,
      39,   23,   23,   23, 0x08,
      53,   23,   23,   23, 0x08,
      69,   23,   23,   23, 0x08,
      86,   23,   23,   23, 0x08,
     103,   23,   23,   23, 0x08,
     131,   23,  123,   23, 0x08,
     145,   23,   23,   23, 0x08,
     166,   23,   23,   23, 0x08,
     187,   23,   23,   23, 0x08,
     208,   23,   23,   23, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SaleManagerSetupDialog[] = {
    "SaleManagerSetupDialog\0\0saveSettings()\0"
    "savePressed()\0cancelPressed()\0"
    "setOldPassword()\0setNewPassword()\0"
    "setVerifyPassword()\0QString\0GetPassword()\0"
    "SetPassword(QString)\0processOldPassword()\0"
    "processNewPassword()\0processVerifyPassword()\0"
};

void SaleManagerSetupDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SaleManagerSetupDialog *_t = static_cast<SaleManagerSetupDialog *>(_o);
        switch (_id) {
        case 0: _t->saveSettings(); break;
        case 1: _t->savePressed(); break;
        case 2: _t->cancelPressed(); break;
        case 3: _t->setOldPassword(); break;
        case 4: _t->setNewPassword(); break;
        case 5: _t->setVerifyPassword(); break;
        case 6: { QString _r = _t->GetPassword();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 7: _t->SetPassword((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->processOldPassword(); break;
        case 9: _t->processNewPassword(); break;
        case 10: _t->processVerifyPassword(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SaleManagerSetupDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SaleManagerSetupDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SaleManagerSetupDialog,
      qt_meta_data_SaleManagerSetupDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SaleManagerSetupDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SaleManagerSetupDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SaleManagerSetupDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SaleManagerSetupDialog))
        return static_cast<void*>(const_cast< SaleManagerSetupDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int SaleManagerSetupDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
