/****************************************************************************
** Meta object code from reading C++ file 'history.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "history.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'history.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_History[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x0a,
      24,   16,    8,    8, 0x0a,
      39,    8,    8,    8, 0x0a,
      57,    8,    8,    8, 0x0a,
      82,   72,    8,    8, 0x0a,
     108,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_History[] = {
    "History\0\0init()\0indexNo\0initIndex(int)\0"
    "populateHistory()\0printHistory()\0"
    "parameter\0predictParamater(QString)\0"
    "clear()\0"
};

void History::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        History *_t = static_cast<History *>(_o);
        switch (_id) {
        case 0: _t->init(); break;
        case 1: _t->initIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->populateHistory(); break;
        case 3: _t->printHistory(); break;
        case 4: _t->predictParamater((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->clear(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData History::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject History::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_History,
      qt_meta_data_History, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &History::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *History::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *History::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_History))
        return static_cast<void*>(const_cast< History*>(this));
    return QDialog::qt_metacast(_clname);
}

int History::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
