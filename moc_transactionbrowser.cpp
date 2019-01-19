/****************************************************************************
** Meta object code from reading C++ file 'transactionbrowser.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "transactionbrowser.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'transactionbrowser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TransactionBrowser[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x0a,
      27,   19,   19,   19, 0x0a,
      44,   19,   19,   19, 0x0a,
      94,   71,   19,   19, 0x0a,
     130,   19,   19,   19, 0x0a,
     150,   19,   19,   19, 0x0a,
     177,   19,   19,   19, 0x0a,
     200,   19,   19,   19, 0x0a,
     242,  226,   19,   19, 0x0a,
     274,   19,   19,   19, 0x0a,
     297,   19,   19,   19, 0x0a,
     323,  317,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TransactionBrowser[] = {
    "TransactionBrowser\0\0init()\0newTransaction()\0"
    "deleteCurrentTransaction()\0"
    "row,col,butt,mouse_pos\0"
    "editTransaction(int,int,int,QPoint)\0"
    "printTransactions()\0populateTransactionTable()\0"
    "showTransactionTable()\0sortTransactionsByIndex()\0"
    "row,transaction\0updateTableRow(int,Transaction)\0"
    "printTransactionList()\0searchListByIndex()\0"
    "event\0keyPressEvent(QKeyEvent*)\0"
};

void TransactionBrowser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TransactionBrowser *_t = static_cast<TransactionBrowser *>(_o);
        switch (_id) {
        case 0: _t->init(); break;
        case 1: _t->newTransaction(); break;
        case 2: _t->deleteCurrentTransaction(); break;
        case 3: _t->editTransaction((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< const QPoint(*)>(_a[4]))); break;
        case 4: _t->printTransactions(); break;
        case 5: _t->populateTransactionTable(); break;
        case 6: _t->showTransactionTable(); break;
        case 7: _t->sortTransactionsByIndex(); break;
        case 8: _t->updateTableRow((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< Transaction(*)>(_a[2]))); break;
        case 9: _t->printTransactionList(); break;
        case 10: _t->searchListByIndex(); break;
        case 11: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData TransactionBrowser::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TransactionBrowser::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_TransactionBrowser,
      qt_meta_data_TransactionBrowser, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TransactionBrowser::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TransactionBrowser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TransactionBrowser::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TransactionBrowser))
        return static_cast<void*>(const_cast< TransactionBrowser*>(this));
    return QDialog::qt_metacast(_clname);
}

int TransactionBrowser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
