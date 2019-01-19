#ifndef LASERPRINTER_H
#define LASERPRINTER_H
#include "printerbase.h"
#include "reports/textreport.h"

class LaserPrinter : public PrinterBase
{
public:
    LaserPrinter(QString name = QString());
    virtual ~LaserPrinter();
    virtual void print(string text,const QTextDocument &textReportDoc,CharacterPitch=Normal,bool=true);
    virtual bool isLaser() { return true;}
    virtual string adjustCheck(string, int, bool=false);
private:
    void printDocument(QPrinter& printer, QTextDocument* doc, QWidget* parentWidget = NULL , int pointSize = 10);
private:
    TextReport m_report;
};

#endif // LASERPRINTER_H
