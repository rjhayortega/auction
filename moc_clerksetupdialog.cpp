/****************************************************************************
** Meta object code from reading C++ file 'clerksetupdialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "clerksetupdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'clerksetupdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ClerkSetupDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x0a,
      42,   35,   17,   17, 0x0a,
      76,   35,   17,   17, 0x0a,
     108,   17,   17,   17, 0x0a,
     126,   17,   17,   17, 0x0a,
     135,   17,   17,   17, 0x0a,
     152,   17,   17,   17, 0x0a,
     178,  170,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ClerkSetupDialog[] = {
    "ClerkSetupDialog\0\0loadClerkSetup()\0"
    "enable\0enableAlternateTicketOption(bool)\0"
    "enableZeroBalNotifyOption(bool)\0"
    "loadPennerSetup()\0accept()\0saveClerkSetup()\0"
    "savePennerSetup()\0checked\0"
    "on_zeroBalNotifycheckBox_toggled(bool)\0"
};

void ClerkSetupDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ClerkSetupDialog *_t = static_cast<ClerkSetupDialog *>(_o);
        switch (_id) {
        case 0: _t->loadClerkSetup(); break;
        case 1: _t->enableAlternateTicketOption((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->enableZeroBalNotifyOption((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->loadPennerSetup(); break;
        case 4: _t->accept(); break;
        case 5: _t->saveClerkSetup(); break;
        case 6: _t->savePennerSetup(); break;
        case 7: _t->on_zeroBalNotifycheckBox_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ClerkSetupDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ClerkSetupDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ClerkSetupDialog,
      qt_meta_data_ClerkSetupDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ClerkSetupDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ClerkSetupDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ClerkSetupDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ClerkSetupDialog))
        return static_cast<void*>(const_cast< ClerkSetupDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int ClerkSetupDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
