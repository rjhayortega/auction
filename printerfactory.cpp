#include "printerfactory.h"
#include "laserprinter.h"
#include "lineprinter.h"

PrinterFactory::PrinterFactory()
{
}

PrinterBase *PrinterFactory::createPrinter(const QString& printerName)
{
    // Check  if printer matrix or laser or matrix2laser.
    //  Laser printer name should be configured with 'lp' prefix.
    if (printerName.left(2) == "lp") {
        return new LaserPrinter(printerName);
    }  else {
        return new LinePrinter(printerName);
    }
}
