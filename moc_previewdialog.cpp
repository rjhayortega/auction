/****************************************************************************
** Meta object code from reading C++ file 'previewdialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "previewdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'previewdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PreviewDialog[] = {

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
      25,   15,   14,   14, 0x0a,
      49,   44,   14,   14, 0x0a,
      86,   77,   14,   14, 0x0a,
     131,  109,   14,   14, 0x0a,
     174,   44,   14,   14, 0x0a,
     201,  191,   14,   14, 0x0a,
     243,   44,   14,   14, 0x0a,
     272,  265,   14,   14, 0x0a,
     292,   14,   14,   14, 0x0a,
     315,  307,   14,   14, 0x08,
     331,   14,   14,   14, 0x08,
     339,  307,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_PreviewDialog[] = {
    "PreviewDialog\0\0showPrint\0setShowPrint(bool)\0"
    "text\0setPrintButtonText(QString)\0"
    "m_report\0setReport(TextReport*)\0"
    "showPrint,printerType\0"
    "setShowPrint(bool,PrinterDAO::PrinterType)\0"
    "setText(QString)\0printType\0"
    "setPrintType(PrinterBase::CharacterPitch)\0"
    "setCheckText(QString)\0enable\0"
    "setCheckPrint(bool)\0printLoadout()\0"
    "printer\0draw(QPrinter*)\0print()\0"
    "print(PrinterBase*)\0"
};

void PreviewDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PreviewDialog *_t = static_cast<PreviewDialog *>(_o);
        switch (_id) {
        case 0: _t->setShowPrint((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->setPrintButtonText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->setReport((*reinterpret_cast< TextReport*(*)>(_a[1]))); break;
        case 3: _t->setShowPrint((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< PrinterDAO::PrinterType(*)>(_a[2]))); break;
        case 4: _t->setText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->setPrintType((*reinterpret_cast< PrinterBase::CharacterPitch(*)>(_a[1]))); break;
        case 6: _t->setCheckText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->setCheckPrint((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->printLoadout(); break;
        case 9: _t->draw((*reinterpret_cast< QPrinter*(*)>(_a[1]))); break;
        case 10: _t->print(); break;
        case 11: _t->print((*reinterpret_cast< PrinterBase*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PreviewDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PreviewDialog::staticMetaObject = {
    { &QPrintPreviewDialog::staticMetaObject, qt_meta_stringdata_PreviewDialog,
      qt_meta_data_PreviewDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PreviewDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PreviewDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PreviewDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PreviewDialog))
        return static_cast<void*>(const_cast< PreviewDialog*>(this));
    return QPrintPreviewDialog::qt_metacast(_clname);
}

int PreviewDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPrintPreviewDialog::qt_metacall(_c, _id, _a);
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
