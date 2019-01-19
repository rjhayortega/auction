/****************************************************************************
** Meta object code from reading C++ file 'commissiondialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "commissiondialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'commissiondialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CommissionDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      23,   18,   17,   17, 0x0a,
      53,   43,   17,   17, 0x0a,
      77,   17,   17,   17, 0x0a,
     110,  105,   17,   17, 0x0a,
     141,  105,   17,   17, 0x0a,
     178,  171,   17,   17, 0x0a,
     197,   17,   17,   17, 0x0a,
     214,   17,   17,   17, 0x0a,
     235,   17,   17,   17, 0x0a,
     248,   17,   17,   17, 0x0a,
     260,   17,   17,   17, 0x0a,
     271,   17,   17,   17, 0x0a,
     287,  285,   17,   17, 0x0a,
     320,  316,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CommissionDialog[] = {
    "CommissionDialog\0\0text\0checkTable(QString)\0"
    "col,check\0checkTableCol(int,bool)\0"
    "populateCommissionListBox()\0item\0"
    "loadCommission(Q3ListBoxItem*)\0"
    "editBreakList(Q3ListBoxItem*)\0commId\0"
    "loadCodeList(long)\0saveCommission()\0"
    "clearCommCodeTable()\0deleteItem()\0"
    "clearForm()\0showForm()\0resetFields()\0"
    "e\0mouseMoveEvent(QMouseEvent*)\0x,y\0"
    "showDescripAtCoord(int,int)\0"
};

void CommissionDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CommissionDialog *_t = static_cast<CommissionDialog *>(_o);
        switch (_id) {
        case 0: _t->checkTable((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->checkTableCol((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->populateCommissionListBox(); break;
        case 3: _t->loadCommission((*reinterpret_cast< Q3ListBoxItem*(*)>(_a[1]))); break;
        case 4: _t->editBreakList((*reinterpret_cast< Q3ListBoxItem*(*)>(_a[1]))); break;
        case 5: _t->loadCodeList((*reinterpret_cast< long(*)>(_a[1]))); break;
        case 6: _t->saveCommission(); break;
        case 7: _t->clearCommCodeTable(); break;
        case 8: _t->deleteItem(); break;
        case 9: _t->clearForm(); break;
        case 10: _t->showForm(); break;
        case 11: _t->resetFields(); break;
        case 12: _t->mouseMoveEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 13: _t->showDescripAtCoord((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CommissionDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CommissionDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CommissionDialog,
      qt_meta_data_CommissionDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CommissionDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CommissionDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CommissionDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CommissionDialog))
        return static_cast<void*>(const_cast< CommissionDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int CommissionDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
