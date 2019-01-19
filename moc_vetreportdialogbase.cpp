/****************************************************************************
** Meta object code from reading C++ file 'vetreportdialogbase.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "vetreportdialogbase.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vetreportdialogbase.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_VetReportDialogBase[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x0a,
      37,   35,   20,   20, 0x0a,
      62,   20,   20,   20, 0x0a,
      75,   20,   20,   20, 0x0a,
      88,   20,   20,   20, 0x0a,
     110,   20,   20,   20, 0x0a,
     129,  123,   20,   20, 0x0a,
     148,   20,   20,   20, 0x0a,
     164,   20,   20,   20, 0x0a,
     185,  180,   20,   20, 0x0a,
     208,  180,   20,   20, 0x0a,
     231,   20,   20,   20, 0x0a,
     239,   20,   20,   20, 0x0a,
     264,  255,   20,   20, 0x0a,
     291,  255,   20,   20, 0x0a,
     316,   20,   20,   20, 0x0a,
     338,  332,   20,   20, 0x0a,
     354,   20,   20,   20, 0x0a,
     377,   20,   20,   20, 0x0a,
     406,  399,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_VetReportDialogBase[] = {
    "VetReportDialogBase\0\0delayedInit()\0p\0"
    "setPrinter(PrinterBase*)\0initHeight()\0"
    "initHeader()\0initHeaderCursorPos()\0"
    "initFooter()\0value\0heightChanged(int)\0"
    "headerChanged()\0footerChanged()\0text\0"
    "headerChanged(QString)\0footerChanged(QString)\0"
    "print()\0initTagVector()\0para,pos\0"
    "headerCursorMoved(int,int)\0"
    "footCursorMoved(int,int)\0setIndexRange()\0"
    "index\0importText(int)\0importDailyBuyerText()\0"
    "importPermBuyerText()\0insert\0"
    "insertText(QStringList)\0"
};

void VetReportDialogBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        VetReportDialogBase *_t = static_cast<VetReportDialogBase *>(_o);
        switch (_id) {
        case 0: _t->delayedInit(); break;
        case 1: _t->setPrinter((*reinterpret_cast< PrinterBase*(*)>(_a[1]))); break;
        case 2: _t->initHeight(); break;
        case 3: _t->initHeader(); break;
        case 4: _t->initHeaderCursorPos(); break;
        case 5: _t->initFooter(); break;
        case 6: _t->heightChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->headerChanged(); break;
        case 8: _t->footerChanged(); break;
        case 9: _t->headerChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->footerChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: _t->print(); break;
        case 12: _t->initTagVector(); break;
        case 13: _t->headerCursorMoved((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 14: _t->footCursorMoved((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 15: _t->setIndexRange(); break;
        case 16: _t->importText((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->importDailyBuyerText(); break;
        case 18: _t->importPermBuyerText(); break;
        case 19: _t->insertText((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData VetReportDialogBase::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject VetReportDialogBase::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_VetReportDialogBase,
      qt_meta_data_VetReportDialogBase, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &VetReportDialogBase::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *VetReportDialogBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *VetReportDialogBase::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VetReportDialogBase))
        return static_cast<void*>(const_cast< VetReportDialogBase*>(this));
    return QDialog::qt_metacast(_clname);
}

int VetReportDialogBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
