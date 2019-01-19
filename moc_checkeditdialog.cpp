/****************************************************************************
** Meta object code from reading C++ file 'checkeditdialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "checkeditdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'checkeditdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CheckEditDialog[] = {

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
      32,   17,   16,   16, 0x0a,
      56,   49,   16,   16, 0x0a,
      79,   16,   16,   16, 0x0a,
     104,   94,   16,   16, 0x0a,
     127,   16,   16,   16, 0x0a,
     146,   16,   16,   16, 0x0a,
     162,   16,   16,   16, 0x0a,
     185,   16,   16,   16, 0x0a,
     197,   16,   16,   16, 0x0a,
     209,   16,   16,   16, 0x0a,
     222,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CheckEditDialog[] = {
    "CheckEditDialog\0\0check,newCheck\0"
    "init(Check,bool)\0number\0updateCheckNumber(int)\0"
    "setCheckType()\0numAmount\0"
    "setAmountText(QString)\0setStatusCleared()\0"
    "setStatusVoid()\0setStatusOutstanding()\0"
    "okPressed()\0saveCheck()\0printCheck()\0"
    "reject()\0"
};

void CheckEditDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CheckEditDialog *_t = static_cast<CheckEditDialog *>(_o);
        switch (_id) {
        case 0: _t->init((*reinterpret_cast< Check(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->updateCheckNumber((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->setCheckType(); break;
        case 3: _t->setAmountText((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->setStatusCleared(); break;
        case 5: _t->setStatusVoid(); break;
        case 6: _t->setStatusOutstanding(); break;
        case 7: _t->okPressed(); break;
        case 8: _t->saveCheck(); break;
        case 9: _t->printCheck(); break;
        case 10: _t->reject(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CheckEditDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CheckEditDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CheckEditDialog,
      qt_meta_data_CheckEditDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CheckEditDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CheckEditDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CheckEditDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CheckEditDialog))
        return static_cast<void*>(const_cast< CheckEditDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int CheckEditDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
