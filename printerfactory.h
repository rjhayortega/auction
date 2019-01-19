#ifndef PRINTERFACTORY_H
#define PRINTERFACTORY_H

#include <QString>
#include "printerbase.h"
class PrinterFactory
{
public:
    PrinterFactory();
    static PrinterBase *createPrinter(const QString &printerName);
};

#endif // PRINTERFACTORY_H
