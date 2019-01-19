/****************************************************************************
** Meta object code from reading C++ file 'breakeditdialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "breakeditdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'breakeditdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BreakEditDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      28,   17,   16,   16, 0x0a,
      54,   45,   16,   16, 0x0a,
      92,   16,   16,   16, 0x0a,
     113,   16,   16,   16, 0x0a,
     122,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_BreakEditDialog[] = {
    "BreakEditDialog\0\0commission\0"
    "init(Commission)\0codeList\0"
    "showCodeAssociation(list<AnimalCode>)\0"
    "populateBreakTable()\0accept()\0"
    "saveBreakList()\0"
};

void BreakEditDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        BreakEditDialog *_t = static_cast<BreakEditDialog *>(_o);
        switch (_id) {
        case 0: _t->init((*reinterpret_cast< Commission(*)>(_a[1]))); break;
        case 1: _t->showCodeAssociation((*reinterpret_cast< list<AnimalCode>(*)>(_a[1]))); break;
        case 2: _t->populateBreakTable(); break;
        case 3: _t->accept(); break;
        case 4: _t->saveBreakList(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData BreakEditDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject BreakEditDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_BreakEditDialog,
      qt_meta_data_BreakEditDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BreakEditDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BreakEditDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BreakEditDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BreakEditDialog))
        return static_cast<void*>(const_cast< BreakEditDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int BreakEditDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
