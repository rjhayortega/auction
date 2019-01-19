#include "laserprinter.h"
#include <QDebug>
#include <QTextDocument>
#include <QPrinter>
#include <QPainter>
#include <QProgressDialog>
#include "previewdialog.h"

LaserPrinter::LaserPrinter(QString name) :
    PrinterBase(name)
{
    qDebug() << "LaserPrinter::LaserPrinter();" ;
}


LaserPrinter::~LaserPrinter()
{
    qDebug() << "LaserPrinter::~LaserPrinter();" ;
}

void LaserPrinter::print(string text, const QTextDocument &textReportDoc, CharacterPitch pitch, bool)
{
    qDebug() << "LaserPrinter::print();" ;

    QPrinter printer;
    int pointSize = (pitch == PrinterBase::Small) ? 8 : 10;
    printer.setFullPage(false);
    printer.setPaperSize(QPrinter::Letter);
    printer.setPrinterName(printerName());
    if (!textReportDoc.isEmpty()) {

        printDocument(printer,(QTextDocument*) &textReportDoc, 0,pointSize);
    }
    else {
        if (! text.empty()) {
            qDebug() << "LaserPrinter::print() called for printer: " << printerName();
            QString textToPrint = QString::fromStdString(text);
            PreviewDialog printPreview;
            printPreview.setText(textToPrint);
            printPreview.printDocument(printer);
        }
    }
}


void LaserPrinter::printDocument(QPrinter& printer, QTextDocument* doc, QWidget* parentWidget, int pointSize)
{
    PreviewDialog printPreview;
    printPreview.printDocument(printer,doc,parentWidget);

}

/*
 * This can only print one check at a time, up to three posistions on page (top, middle, bottom).
 * If there are multiple checks, this needs to be called for each check in the loop, adding
 * a formfeed to each check except the last.
 *
 * The "useFF" defaults to false in virtual function so there is no effect on Seller Invoice printing,
 * or anywhere else where only one check is printed. When printed from an external loop, the loop must
 * specifically set "useFF" true until the last check, otherwise they all run together.
 *
 */
string LaserPrinter::adjustCheck(string checkText, int lines, /*bool top, bool middle, bool bottom,*/ bool useFF) {
//    cout << "Laser Printer, not on invoice" << endl;
    // get line count of printed check:
    int count = 0, lineTotal = lines;
    int chkLen, blankLen;
//    cout << "checkText.length(): [" << checkText.length() << "]" << endl; // [KLN] debug
    for (int i=0; i<checkText.length(); i++) {
        if (checkText[i] == '\n') {
            count++;
        }
    }
    chkLen = count;
//    cout << "checkText: [" << checkText << "]" << endl;
    // Make sure it's 1/3 of a page (20 lines assumed at 12 points and ten inches)
    for (int i = count; i < lineTotal; i++) {
        checkText += "\n";
        chkLen++; // [KLN] debug
    }

    string checkPage = "";
    string blankCheck = "";
    blankLen = 0; // [KLN] debug
    for(int i = 0; i < lineTotal; i++) {
        blankCheck += "\n";
        blankLen++; // [KLN] debug
    }
//    cout << "       lineTotal: [" << lineTotal << "]" << endl;
//    cout << " checkText lines: [" << chkLen << "]" << endl;
//    cout << "blankCheck lines: [" << blankLen << "]" << endl;
    bool top,middle,bottom;
    top = SetupDAO().getBoolean("sinvLaserCheckTop");
    middle = SetupDAO().getBoolean("sinvLaserCheckMiddle");
    bottom = SetupDAO().getBoolean("sinvLaserCheckBottom");
//    cout << "top, middle, bottom: " << top << ", " << middle << ", " << bottom << endl;
    if (top || middle || bottom) {
        if (top) {
//            cout << "top is set" << endl;
            checkPage = checkText;
        } else {
//            cout << "top is not set" << endl;
            checkPage = blankCheck;
        }
        if (middle) {
//            cout << "middle is set" << endl;
            checkPage += checkText;
        } else {
//            cout << "middle is not set" << endl;
            checkPage += blankCheck;
        }
        if (bottom) {
//            cout << "bottom is set" << endl;
            checkPage += checkText;
        } else {
//            cout << "bottom is not set" << endl;
            checkPage += blankCheck;
        }
//        cout << "checkPage: [" << checkPage << "]" << endl;
//        checkText = checkPage;
//        cout << "checkText: [" << checkText << "]" << endl;
    } else { // single check,
        checkPage = blankCheck;
        checkPage += blankCheck;
        checkPage += checkText;
    }
    if (chkLen <= lineTotal) { // lineTotal is lines per check as set in Seller Invoice (usually 20)
        checkText = checkPage;
      } else { // most likely using chkPreSpaceLines which is set in the Setup -> Documents -> Check screen

      }
    checkText += useFF ? "\f" : ""; // [KLN] add
    PreviewDialog printPreview;
    printPreview.setCheckText(QString::fromStdString(checkText));

    QPrinter printer;
    printer.setFullPage(false);
    printer.setPaperSize(QPrinter::Letter);
    printer.setPrinterName(printerName());

    printPreview.printCheckDocument(printer);

    return checkText;
}


