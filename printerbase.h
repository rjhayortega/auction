/***************************************************************
- class LinePrinter
-
- Author: Armen Zakaryan
-
- Purpose: Base printer class to store printer name
-
- Notes:
-
- Todo:
-
-**************************************************************/

#ifndef PRINTERBASE_H
#define PRINTERBASE_H
#include <QString>
#include <string>
#include <QTextDocument>
#include <vector>
#include <QStringList>

using namespace std;
class PrinterBase
{
public:
    typedef enum {OKI_SMALL=15, OKI_NORMAL=18}Commands;
    typedef enum {Normal, Small}CharacterPitch;
    PrinterBase(QString name = QString());
    virtual ~PrinterBase();
    virtual void print(string text, const QTextDocument &textReportDoc = QTextDocument(), CharacterPitch=Normal, bool=true );
    void setPrinterName(QString &name);
    QString printerName();
    virtual bool isLaser();
    virtual string adjustCheck(string, int, bool=false);

private:
    QString m_printerName;
};

#endif // PRINTERBASE_H
