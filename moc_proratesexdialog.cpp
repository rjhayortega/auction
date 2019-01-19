/****************************************************************************
** Meta object code from reading C++ file 'proratesexdialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "proratesexdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'proratesexdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ProrateSexDialog[] = {

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
      50,   18,   17,   17, 0x0a,
     137,  113,   17,   17, 0x0a,
     194,  173,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ProrateSexDialog[] = {
    "ProrateSexDialog\0\0codeList,prorateList,prorateRow\0"
    "init(vector<SexCheckFactory::CodeRecord>,vector<Prorate>,uint)\0"
    "prorate,currentCustomer\0"
    "removeProrateFromList(Prorate,bool)\0"
    "data,currentCustomer\0"
    "removeDataFromList(Prorate::Data,bool)\0"
};

void ProrateSexDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ProrateSexDialog *_t = static_cast<ProrateSexDialog *>(_o);
        switch (_id) {
        case 0: _t->init((*reinterpret_cast< vector<SexCheckFactory::CodeRecord>(*)>(_a[1])),(*reinterpret_cast< vector<Prorate>(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3]))); break;
        case 1: _t->removeProrateFromList((*reinterpret_cast< Prorate(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->removeDataFromList((*reinterpret_cast< Prorate::Data(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ProrateSexDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ProrateSexDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ProrateSexDialog,
      qt_meta_data_ProrateSexDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ProrateSexDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ProrateSexDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ProrateSexDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ProrateSexDialog))
        return static_cast<void*>(const_cast< ProrateSexDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int ProrateSexDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
