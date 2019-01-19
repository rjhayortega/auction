
/***************************************************************
- class LinePrinter
-
- Author: Jason Langford
-
- Purpose: Sends raw data to the lpd daemon
-
- Notes: There are so many things wrong about this, I'm not going
-        to even try to apologize. This is what works for this 
-        purpose. So Mr. Maintainer, good luck
-
- Todo: Find a better way to send raw data to the printer
-       one that doesn't involve calling lpr tools as a seperate
-       process
-
-**************************************************************/
#ifndef _LINE_PRINTER_H_
#define _LINE_PRINTER_H_
#include <qprocess.h>

#include <string>
#include <iostream>
#include "printerbase.h"

using namespace std;

class LinePrinter  : public PrinterBase
{


public:
    LinePrinter(QString name=QString());
    virtual ~LinePrinter();
    void setPrinter(QString &name);
    virtual void print(string text, const QTextDocument &textReportDoc = QTextDocument(),CharacterPitch=Normal,  bool=true);
    bool isPrinting();
    bool operator==(LinePrinter);
    bool operator==(QString);
    void convertToLaser(string text);
    void ReplaceString(string&, const string&, const string&);

private:
    unsigned char*image;
    QProcess *printerProcess;
};

#endif
