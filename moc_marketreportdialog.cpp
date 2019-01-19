/****************************************************************************
** Meta object code from reading C++ file 'marketreportdialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "marketreportdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'marketreportdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MarketReportDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x0a,
      52,   46,   19,   19, 0x0a,
      77,   19,   19,   19, 0x0a,
      99,   19,   19,   19, 0x0a,
     123,   19,   19,   19, 0x0a,
     143,   19,   19,   19, 0x0a,
     179,  171,   19,   19, 0x0a,
     222,  204,   19,   19, 0x0a,
     252,   19,   19,   19, 0x0a,
     284,   19,   19,   19, 0x0a,
     325,  305,   19,   19, 0x0a,
     365,   19,   19,   19, 0x0a,
     384,   19,   19,   19, 0x0a,
     403,   19,   19,   19, 0x0a,
     431,   19,   19,   19, 0x0a,
     440,   19,   19,   19, 0x0a,
     467,  454,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MarketReportDialog[] = {
    "MarketReportDialog\0\0populateTransactionList()\0"
    "index\0sortTransactionList(int)\0"
    "showTransactionList()\0copySelectedToInclude()\0"
    "restoreMarketList()\0moveTransactionToIncluded()\0"
    "transNo\0includeTransaction(long)\0"
    "transNo,redisplay\0includeTransaction(long,bool)\0"
    "removeTransactionFromIncluded()\0"
    "displayIncludeList()\0table,i,transaction\0"
    "fillTableRow(Q3Table*,uint,Transaction)\0"
    "clearIncludeList()\0copyAllToInclude()\0"
    "removeSelectedFromInclude()\0reject()\0"
    "printReport()\0marketReport\0"
    "setComments(MarketReport&)\0"
};

void MarketReportDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MarketReportDialog *_t = static_cast<MarketReportDialog *>(_o);
        switch (_id) {
        case 0: _t->populateTransactionList(); break;
        case 1: _t->sortTransactionList((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->showTransactionList(); break;
        case 3: _t->copySelectedToInclude(); break;
        case 4: _t->restoreMarketList(); break;
        case 5: _t->moveTransactionToIncluded(); break;
        case 6: _t->includeTransaction((*reinterpret_cast< long(*)>(_a[1]))); break;
        case 7: _t->includeTransaction((*reinterpret_cast< long(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 8: _t->removeTransactionFromIncluded(); break;
        case 9: _t->displayIncludeList(); break;
        case 10: _t->fillTableRow((*reinterpret_cast< Q3Table*(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< Transaction(*)>(_a[3]))); break;
        case 11: _t->clearIncludeList(); break;
        case 12: _t->copyAllToInclude(); break;
        case 13: _t->removeSelectedFromInclude(); break;
        case 14: _t->reject(); break;
        case 15: _t->printReport(); break;
        case 16: _t->setComments((*reinterpret_cast< MarketReport(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MarketReportDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MarketReportDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_MarketReportDialog,
      qt_meta_data_MarketReportDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MarketReportDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MarketReportDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MarketReportDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MarketReportDialog))
        return static_cast<void*>(const_cast< MarketReportDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int MarketReportDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
