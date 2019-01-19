/****************************************************************************
** Meta object code from reading C++ file 'transactiondialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "transactiondialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'transactiondialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TransactionDialog[] = {

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
      27,   19,   18,   18, 0x0a,
      49,   18,   18,   18, 0x0a,
      69,   18,   18,   18, 0x0a,
      90,   18,   18,   18, 0x0a,
     108,   18,   18,   18, 0x0a,
     117,   18,   18,   18, 0x0a,
     131,   18,   18,   18, 0x0a,
     144,   18,   18,   18, 0x0a,
     164,   18,   18,   18, 0x0a,
     187,  182,   18,   18, 0x0a,
     225,  210,   18,   18, 0x0a,
     259,  254,   18,   18, 0x0a,
     278,  254,   18,   18, 0x0a,
     294,  182,   18,   18, 0x0a,
     324,   18,   18,   18, 0x0a,
     338,   18,   18,   18, 0x0a,
     350,   18,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TransactionDialog[] = {
    "TransactionDialog\0\0transId\0"
    "loadTransaction(long)\0saveButtonHandler()\0"
    "printButtonHandler()\0populateTagList()\0"
    "addTag()\0saveTagList()\0deleteTags()\0"
    "deleteSelectedTag()\0saveTransaction()\0"
    "text\0updateDescrip(QString)\0totalWeightStr\0"
    "recalcAverageWeight(QString)\0item\0"
    "updateModeBox(int)\0updateMode(int)\0"
    "formatToDollarString(QString)\0"
    "printTicket()\0playVideo()\0quitPlayer()\0"
};

void TransactionDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TransactionDialog *_t = static_cast<TransactionDialog *>(_o);
        switch (_id) {
        case 0: _t->loadTransaction((*reinterpret_cast< long(*)>(_a[1]))); break;
        case 1: _t->saveButtonHandler(); break;
        case 2: _t->printButtonHandler(); break;
        case 3: _t->populateTagList(); break;
        case 4: _t->addTag(); break;
        case 5: _t->saveTagList(); break;
        case 6: _t->deleteTags(); break;
        case 7: _t->deleteSelectedTag(); break;
        case 8: _t->saveTransaction(); break;
        case 9: _t->updateDescrip((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->recalcAverageWeight((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: _t->updateModeBox((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->updateMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->formatToDollarString((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 14: _t->printTicket(); break;
        case 15: _t->playVideo(); break;
        case 16: _t->quitPlayer(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData TransactionDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TransactionDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_TransactionDialog,
      qt_meta_data_TransactionDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TransactionDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TransactionDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TransactionDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TransactionDialog))
        return static_cast<void*>(const_cast< TransactionDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int TransactionDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
