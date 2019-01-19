/****************************************************************************
** Meta object code from reading C++ file 'brandbrowserdialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "brandbrowserdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'brandbrowserdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BrandBrowserDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x0a,
      36,   19,   19,   19, 0x0a,
      48,   19,   19,   19, 0x0a,
      64,   19,   19,   19, 0x0a,
      76,   19,   19,   19, 0x0a,
      89,   19,   19,   19, 0x0a,
     107,   19,   19,   19, 0x0a,
     124,   19,   19,   19, 0x0a,
     141,   19,   19,   19, 0x0a,
     158,   19,   19,   19, 0x0a,
     175,   19,   19,   19, 0x0a,
     196,  192,   19,   19, 0x0a,
     213,   19,   19,   19, 0x0a,
     229,   19,   19,   19, 0x0a,
     245,   19,   19,   19, 0x0a,
     261,   19,   19,   19, 0x0a,
     284,  277,   19,   19, 0x0a,
     301,   19,   19,   19, 0x0a,
     315,   19,   19,   19, 0x0a,
     329,   19,   19,   19, 0x0a,
     343,   19,   19,   19, 0x0a,
     357,  277,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_BrandBrowserDialog[] = {
    "BrandBrowserDialog\0\0loadBrandList()\0"
    "nextGroup()\0previousGroup()\0lastGroup()\0"
    "firstGroup()\0clearBrandTable()\0"
    "initBrandTable()\0processColumn1()\0"
    "processColumn2()\0processColumn3()\0"
    "processColumn4()\0col\0processItem(int)\0"
    "deleteColumn1()\0deleteColumn2()\0"
    "deleteColumn3()\0deleteColumn4()\0column\0"
    "deleteBrand(int)\0copyColumn1()\0"
    "copyColumn2()\0copyColumn3()\0copyColumn4()\0"
    "copyColumn(int)\0"
};

void BrandBrowserDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        BrandBrowserDialog *_t = static_cast<BrandBrowserDialog *>(_o);
        switch (_id) {
        case 0: _t->loadBrandList(); break;
        case 1: _t->nextGroup(); break;
        case 2: _t->previousGroup(); break;
        case 3: _t->lastGroup(); break;
        case 4: _t->firstGroup(); break;
        case 5: _t->clearBrandTable(); break;
        case 6: _t->initBrandTable(); break;
        case 7: _t->processColumn1(); break;
        case 8: _t->processColumn2(); break;
        case 9: _t->processColumn3(); break;
        case 10: _t->processColumn4(); break;
        case 11: _t->processItem((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->deleteColumn1(); break;
        case 13: _t->deleteColumn2(); break;
        case 14: _t->deleteColumn3(); break;
        case 15: _t->deleteColumn4(); break;
        case 16: _t->deleteBrand((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->copyColumn1(); break;
        case 18: _t->copyColumn2(); break;
        case 19: _t->copyColumn3(); break;
        case 20: _t->copyColumn4(); break;
        case 21: _t->copyColumn((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData BrandBrowserDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject BrandBrowserDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_BrandBrowserDialog,
      qt_meta_data_BrandBrowserDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BrandBrowserDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BrandBrowserDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BrandBrowserDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BrandBrowserDialog))
        return static_cast<void*>(const_cast< BrandBrowserDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int BrandBrowserDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
