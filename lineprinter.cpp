
#include "lineprinter.h"
#include <qstringlist.h>
#include "auctionmain.h"

#include <qeventloop.h>

///////////////////////////////////////////////////////////////////////////////
//
// name:    LinePrinter(string)
//
// purpose: Constructor
//
// calling params: string printer - the printer the LinePrinter object will print to
//
// return params:
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

LinePrinter::LinePrinter(QString name) :
    PrinterBase(name)
{
    printerProcess = NULL;
}


LinePrinter::~LinePrinter()
{
    if(printerProcess != NULL)
    {
        delete printerProcess;
        printerProcess = NULL;
    }
}

///////////////////////////////////////////////////////////////////////////////
//
// name:    setPrinter(string)
//
// purpose: sets the printer the LinePrinter class will print to
//
// calling params: string printer - the name of the printer the line printer
//                                  will print to
//
// return params:
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void LinePrinter::setPrinter(QString& name)
{
    setPrinterName(name);
    if(printerProcess != NULL)
    {
        delete printerProcess;
        printerProcess = NULL;
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    print(string)
//
// purpose: sends raw text to the printer
//
// calling params: string text - the text to print
//
// return params:
//
// Notes:
//
// Todo:  be sure that this isn't going to cause a memory leak
// [KLN] This is *only* for Okidata printers!
//
///////////////////////////////////////////////////////////////////////////////

void LinePrinter::print(string text, const QTextDocument &textReportDoc, CharacterPitch pitch, bool wait)
{
    if (text.empty()){
        return;   // Prevent printing blank page or form feed
    }

    if (textReportDoc.blockCount() > 0 || wait) {
        // do nothing, just clearing compile-time warning
    }
    qDebug("LinePrinter::print(string text, CharacterPitch pitch, bool wait)");

    QByteArray buf(text.size() + (pitch == Small ? 2 : 0));

//    char smallPitch  = char(103);
//    char normalPitch = char(80);

    if(pitch == Small) // turn on condensed print
    {
        buf[0] = 15;
    }

    for(unsigned int i = 0; i< text.size(); i++)
    {
        buf[i + (pitch == Small ? 1 : 0)] = text[i];
    }

    if(pitch == Small)
    {
        buf[(uint)text.size()] = 18; // turn off condensed print
    }

    QString home = getenv("HOME");
    const QString filename = home + "/print-temp.txt";

    QFile file(filename);
    if (file.exists()) {
      file.remove();
      QFile file(filename);
    }

    file.open(QIODevice::WriteOnly);
    file.write(buf);
    file.close();

//    cout << "LinePrinter::print printerName: " << printerName().toStdString() << endl;

    convertToLaser(text);


    QString cmdPlusArgs = printerName().prepend("lp -o raw -d ").append(" ").append(file.fileName());

    if(printerProcess != NULL)
    {
        delete printerProcess;
        printerProcess = NULL;
    }

    qDebug("Starting Processs");
    printerProcess = new QProcess();
    printerProcess->setProcessChannelMode(QProcess::MergedChannels);
    //printerProcess->setCommunication(QProcess::Stdin);

    printerProcess->start(cmdPlusArgs);
    //printerProcess->closeWriteChannel();

    qDebug("cmdPlusArgs == %s", cmdPlusArgs.toLatin1().data());

    //if(printerProcess != NULL && !printerProcess->waitForStarted())
    if(!printerProcess->waitForStarted())
    {
	qDebug("!printerProcess->waitForStarted()");
        cerr << "could not start lp" << endl;
        if(printerProcess != NULL) {

            delete printerProcess;
            printerProcess = NULL;
        }
    }

//     qDebug("while(isPrinting())");
//     while(isPrinting() && wait)
//     {
// //     AuctionMain::applicationReference->processEvents();
//         //QApplication::eventLoop()->processEvents(QEventLoop::ExcludeUserInput);
//         QApplication::processEvents();
//     }

    if (!printerProcess->waitForFinished())
    {
	qDebug("!printerProcess->waitForFinished()");
         cerr << "could not finish lp" << endl;
        if(printerProcess != NULL) {

            delete printerProcess;
            printerProcess = NULL;
        }
    }

     QByteArray result = printerProcess->readAll();
     qDebug("result == " + result);
     qDebug("exit status == %d", printerProcess->exitCode());

    qDebug("LinePrinter::print(string text, CharacterPitch pitch, bool wait) exiting");
}



bool LinePrinter::isPrinting()
{
    if(printerProcess != NULL && !printerProcess->atEnd())
    {
        return true;
    }

    return false;
}

bool LinePrinter::operator==(LinePrinter that)
{
    return printerName() == that.printerName();
}

bool LinePrinter::operator==(QString that)
{
    return printerName() == that;
}

///////////////////////////////////////////////////////////////////////////////
//
// name:    convertToLaser(string)
//
// purpose: converts dot matrix text file to be compatible with laser (PCL5 commands)
//
// calling params: string text - the text to print
//
// return params:
//
// Notes:
//
//
///////////////////////////////////////////////////////////////////////////////

void LinePrinter::convertToLaser(string text)
{
    if (text.empty()){
        return;   // Prevent printing blank page or form feed
    }

    qDebug("LinePrinter::convert(string text)");

    string escChr = "\x1b";
    string endOfLine = "\r\n";

    string uelCmd = escChr + "%–12345X";
    string resetCmd = escChr + "E";
    string separationCmd = escChr + "&l1T";

    string symbolSetP = escChr + "(10U";
    string symbolSetS = escChr + ")10U";

    string spacingP = escChr + "(s0P";
    string spacingS = escChr + ")s0P";

    string pitchP = escChr + "(s10H";
    string pitchS = escChr + ")s18H";

    string heightP = escChr + "(s12V";
    string heightS = escChr + ")s12V";

    string pclStart = resetCmd + symbolSetP + spacingP + pitchP + heightP + symbolSetS + spacingS + pitchS + heightS;
    string pclStop = resetCmd;

    string priFont = "\x0f";
    string secFont = "\x0e";

    string jobName = "TestingPCL";

//    <ESC>%–12345X@PJL JOB NAME = "My Print Job Name" <CR><LF>
//    @PJL ENTER LANGUAGE = PCL <CR><LF>
//    string jobStart = escChr + "%–12345X@PJL JOB NAME = " + jobName + endOfLine + "@PJL ENTER LANGUAGE = PCL" + endOfLine;

//    <ESC>%–12345X @PJL EOF <CR><LF>
//    <ESC>%–12345X
//    string jobStop = escChr + "%–12345X @PJL EOF" + endOfLine + escChr + "%–12345X";

    string testDoc;

    testDoc = text;

    ReplaceString(testDoc, "\x1bP", "" ); // remove Oki codes
    ReplaceString(testDoc, "\x1bM", "" ); // remove Oki codes
    ReplaceString(testDoc, "\x0f", secFont); // replace Oki condensed ON with PCL 18cpi
    ReplaceString(testDoc, "\x12", priFont); // replace Oki condensed OFF with PCL 10cpi
    ReplaceString(testDoc, "\x0a", endOfLine); // replace LF with CR/LF

//    testDoc = pclStart + testDoc + pclStop;
//    testDoc = resetCmd + pitchP + testDoc;

    testDoc = pclStart + testDoc;

////    testDoc = jobStart;
////    testDoc += "Top of page, already sent UEL command and RESET command (Job Start)." + endOfLine;

//    testDoc += pitchP + "Top of page, set primary font (10cpi)." + endOfLine;
//    testDoc += "This is still a 10cpi line." + endOfLine;
//    testDoc += pitchS + "This is a sample of 18cpi line." + pitchP + endOfLine;
//    testDoc += "A line of 10cpi with " + pitchS + "this part in 18cpi " + pitchP + "and back to 10cpi!" + endOfLine;
//    testDoc += pclStop;
//    testDoc += "\f";

////    testDoc += jobStop + endOfLine;

////    testDoc += "";
////    testDoc += "";
////    testDoc += "";
////    testDoc += "";

    QByteArray buf2((uint)testDoc.size());
    QString home = getenv("HOME");
const QString filename = home + "/print-matrix-to-laser.txt";

    QFile file2(filename);
    if (file2.exists()) {
      file2.remove();
      QFile file2(filename);
    }

    for(unsigned int i = 0; i< testDoc.size(); i++)
    {
        buf2[i] = testDoc[i];
    }

    file2.open(QIODevice::WriteOnly);
    file2.write(buf2);
    file2.close();

    qDebug("LinePrinter::print(string text) exiting");
}

void LinePrinter::ReplaceString(string& subject, const string& search,
                          const string& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != string::npos) {
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }

}
