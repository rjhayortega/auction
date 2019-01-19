/****************************************************************************
** Meta object code from reading C++ file 'printersetupdialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "printersetupdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'printersetupdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PrinterSetupDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x0a,
      38,   19,   19,   19, 0x0a,
      58,   19,   19,   19, 0x0a,
      75,   19,   19,   19, 0x0a,
      97,   19,   19,   19, 0x0a,
     123,   19,   19,   19, 0x0a,
     145,   19,   19,   19, 0x0a,
     171,   19,   19,   19, 0x0a,
     178,   19,   19,   19, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_PrinterSetupDialog[] = {
    "PrinterSetupDialog\0\0loadPrinterData()\0"
    "processLpstatData()\0getPrinterMenu()\0"
    "savePrinterMapTable()\0saveDefaultPrinterTable()\0"
    "loadPrinterMapTable()\0loadDefaultPrinterTable()\0"
    "save()\0init()\0"
};

void PrinterSetupDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PrinterSetupDialog *_t = static_cast<PrinterSetupDialog *>(_o);
        switch (_id) {
        case 0: _t->loadPrinterData(); break;
        case 1: _t->processLpstatData(); break;
        case 2: _t->getPrinterMenu(); break;
        case 3: _t->savePrinterMapTable(); break;
        case 4: _t->saveDefaultPrinterTable(); break;
        case 5: _t->loadPrinterMapTable(); break;
        case 6: _t->loadDefaultPrinterTable(); break;
        case 7: _t->save(); break;
        case 8: _t->init(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData PrinterSetupDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PrinterSetupDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_PrinterSetupDialog,
      qt_meta_data_PrinterSetupDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PrinterSetupDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PrinterSetupDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PrinterSetupDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PrinterSetupDialog))
        return static_cast<void*>(const_cast< PrinterSetupDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int PrinterSetupDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
