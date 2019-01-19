/****************************************************************************
** Meta object code from reading C++ file 'brandinputdialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "brandinputdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'brandinputdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BrandInputDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x0a,
      33,   17,   17,   17, 0x0a,
      46,   17,   17,   17, 0x0a,
      64,   17,   17,   17, 0x0a,
      85,   17,   17,   17, 0x0a,
      99,   17,   17,   17, 0x0a,
     112,   17,   17,   17, 0x0a,
     142,  130,   17,   17, 0x0a,
     167,   17,   17,   17, 0x0a,
     186,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_BrandInputDialog[] = {
    "BrandInputDialog\0\0browseBrands()\0"
    "clearBrand()\0setPositionEdit()\0"
    "setTransactionEdit()\0setHeadEdit()\0"
    "setTagEdit()\0processEditItem()\0"
    "cur_painter\0clearPainting(QPainter*)\0"
    "drawNoBrandImage()\0saveImage()\0"
};

void BrandInputDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        BrandInputDialog *_t = static_cast<BrandInputDialog *>(_o);
        switch (_id) {
        case 0: _t->browseBrands(); break;
        case 1: _t->clearBrand(); break;
        case 2: _t->setPositionEdit(); break;
        case 3: _t->setTransactionEdit(); break;
        case 4: _t->setHeadEdit(); break;
        case 5: _t->setTagEdit(); break;
        case 6: _t->processEditItem(); break;
        case 7: _t->clearPainting((*reinterpret_cast< QPainter*(*)>(_a[1]))); break;
        case 8: _t->drawNoBrandImage(); break;
        case 9: _t->saveImage(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData BrandInputDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject BrandInputDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_BrandInputDialog,
      qt_meta_data_BrandInputDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BrandInputDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BrandInputDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BrandInputDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BrandInputDialog))
        return static_cast<void*>(const_cast< BrandInputDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int BrandInputDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
