#include "printerbase.h"
#include <QTextDocument>

PrinterBase::PrinterBase(QString name):
    m_printerName(name)
{
}

PrinterBase::~PrinterBase()
{
}

void PrinterBase::setPrinterName(QString &name)
{
    m_printerName = name;
}

QString PrinterBase::printerName()
{
    return m_printerName;
}

//Virtual function, overloaded in derived classes
void PrinterBase::print(string text,  const QTextDocument &textReportDoc , CharacterPitch, bool)
{
}

bool PrinterBase::isLaser()
{
    return false;
}

//Virtual function, overloaded in derived classes
string PrinterBase::adjustCheck(string checkText, int lines, bool useFF) {
}
