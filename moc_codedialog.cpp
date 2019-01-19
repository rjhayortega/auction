/****************************************************************************
** Meta object code from reading C++ file 'codedialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "codedialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'codedialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CodeDialog[] = {

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
      12,   11,   11,   11, 0x0a,
      35,   31,   11,   11, 0x0a,
      56,   11,   11,   11, 0x0a,
      74,   11,   11,   11, 0x0a,
      94,   11,   11,   11, 0x0a,
     108,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CodeDialog[] = {
    "CodeDialog\0\0populateCodeList()\0row\0"
    "loadCurrentCode(int)\0saveCurrentCode()\0"
    "deleteCurrentCode()\0resetFields()\0"
    "printCodeList()\0"
};

void CodeDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CodeDialog *_t = static_cast<CodeDialog *>(_o);
        switch (_id) {
        case 0: _t->populateCodeList(); break;
        case 1: _t->loadCurrentCode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->saveCurrentCode(); break;
        case 3: _t->deleteCurrentCode(); break;
        case 4: _t->resetFields(); break;
        case 5: _t->printCodeList(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CodeDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CodeDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CodeDialog,
      qt_meta_data_CodeDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CodeDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CodeDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CodeDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CodeDialog))
        return static_cast<void*>(const_cast< CodeDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int CodeDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
