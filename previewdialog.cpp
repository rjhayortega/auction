#include "previewdialog.h"
//#include "ui_previewdialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <Q3TextEdit>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>
#include <qprinter.h>
#include <qpainter.h>
#include "oki2pixmap.h"
#include "qapplication.h"
#include <qeventloop.h>
#include <QMessageBox>
#include <QPrintPreviewDialog>
#include <QPrintPreviewWidget>
#include <QToolBar>
#include <QProgressDialog>
#include <QTextFrame>
#include <QTextBlock>
#include <QAbstractTextDocumentLayout>

#include <QTextTable>
#include <QTextTableCell>
#include <QTextCursor>
#include <QPrinter>

// To show rectangles, line numbers, and output to file
//#define _DEBUG_PRINT_BOXES_
//#define _DEBUG_PRINT_LINES_
//#define _DEBUG_PRINT_FILE_
//#define _DEBUG_PRINT_PREVIEW_FILE_

#include <iostream>
#include <fstream>

static const int textMargins = 5; // in millimeters
static const int borderMargins = 2; // in millimeters
static const int LINES_PER_PAGE = 67; // WHY??

double PreviewDialog::mmToPixels(QPrinter& printer, int mm)
{
//  cout << "                  mm -- " << mm << endl;
//  cout << "printer.resolution() -- " << printer.resolution() << endl;
//  cout << "mmToPixels returns: " << mm * 0.039370147 * printer.resolution() << endl;
    return mm * 0.039370147 * printer.resolution();
}

void PreviewDialog::paintPage(QPrinter& printer, int pageNumber, int pageCount,
                              QPainter* painter, QTextDocument* doc,
                              const QRectF& textRect, qreal footerHeight, bool isLastCopyPage)


{
    if (m_checkPrintMode) {
        //qDebug() << "Printing page" << pageNumber;
        const QSizeF pageSize = printer.pageRect().size();

        const double bm = mmToPixels(printer, borderMargins);
        const QRectF borderRect(bm, bm, pageSize.width() - 2 * bm, pageSize.height() - 2 * bm);
#ifdef _DEBUG_PRINT_BOXES_
        painter->drawRect(borderRect);
#endif
        painter->save();
        // textPageRect is the rectangle in the coordinate system of the QTextDocument, in pixels,
        // and starting at (0,0) for the first page. Second page is at y=doc->pageSize().height().
        const QRectF textPageRect(0, pageNumber * doc->pageSize().height(), doc->pageSize().width(), doc->pageSize().height());
        // Clip the drawing so that the text of the other pages doesn't appear in the margins
        painter->setClipRect(textRect);
        // Translate so that 0,0 is now the page corner
        painter->translate(0, -textPageRect.top());
        // Translate so that 0,0 is the text rect corner
        painter->translate(textRect.left(), textRect.top());
        painter->scale(1.12, 1.0); // [KLN] original line from Armen
        doc->drawContents(painter);

        painter->restore();

        // Footer: page number
        QRectF footerRect = borderRect;
        footerRect.setTop(borderRect.bottom()-footerHeight);
        footerRect.setHeight(footerHeight);
        painter->drawText(footerRect, Qt::AlignVCenter | Qt::AlignRight, QObject::tr("Page %1/%2").arg(pageNumber+1).arg(pageCount));


    }
    else {
        bool printInvoice = true;
        if ((m_textCheckList.size()>0) && (pageNumber <  m_textCheckList.size())) {
             printInvoice = !m_textCheckList[pageNumber].isPrintOnlyCheck();
        }

        const QSizeF pageSize = printer.pageRect().size();
        const double bm = mmToPixels(printer, borderMargins);
        QRectF borderRect(bm, bm, pageSize.width() - 2 * bm, pageSize.height() - 2 * bm);

        if (printInvoice ) {
#ifdef _DEBUG_PRINT_BOXES_
            painter->drawRect(borderRect);
#endif
            painter->save();
            // textPageRect is the rectangle in the coordinate system of the QTextDocument, in pixels,
            // and starting at (0,0) for the first page. Second page is at y=doc->pageSize().height().
            const QRectF textPageRect(0, m_invoicePageNum * doc->pageSize().height(), doc->pageSize().width(), doc->pageSize().height());
            // Clip the drawing so that the text of the other pages doesn't appear in the margins
            painter->setClipRect(textRect);
            // Translate so that 0,0 is now the page corner
            painter->translate(0, -textPageRect.top());
            // Translate so that 0,0 is the text rect corner
            painter->translate(textRect.left(), textRect.top());
            doc->drawContents(painter);
            painter->restore();
            if (isLastCopyPage) {
                m_invoicePageNum++;
            }
        }
        if ( m_isNeedPrintCheck  && (m_checkTextList.size() > 0) ) {
            // Check rectangle
            QRectF checkRect = borderRect;
            checkRect.setX(2*bm);
            checkRect.setY(2*bm);

            checkRect.setTop(m_checkStartLine*painter->fontMetrics().lineSpacing());
            checkRect.setWidth(borderRect.width()-2*bm);

            if (m_checkStartLine < m_topSkipLines) { //Check will be printed in skipped lines area
                checkRect.setHeight((m_topSkipLines - m_checkStartLine)*painter->fontMetrics().lineSpacing());
            }
            else {
                checkRect.setHeight(borderRect.bottom()-checkRect.top()-footerHeight-2*bm);
            }
            int checkNum = pageNumber;
            //QString checkText =  ((pageNumber < pageCount-1) ? m_checkTextLparentWidgetist[0] : m_checkTextList[1] );
            //QString checkText =  ( (checkNum > m_checkTextList.size() - 1) ? m_checkTextList[0] : m_checkTextList[checkNum] );

            QString checkText;
            if (checkNum < m_checkTextList.size()) {
                checkText =  m_checkTextList[checkNum];
            }

            painter->save();

            painter->setClipRect(checkRect);
#ifdef _DEBUG_PRINT_BOXES_
            painter->drawRect(checkRect);
#endif
            painter->translate(checkRect.left(), checkRect.top());
            painter->scale(1.12, 1.0);
            setCheckText(checkText);
            m_checkDocument->drawContents(painter);
            painter->restore();
        }
        // Footer: page number
        QRectF footerRect = borderRect;
        footerRect.setTop(borderRect.bottom()-footerHeight);
        footerRect.setHeight(footerHeight);
        painter->drawText(footerRect, Qt::AlignVCenter | Qt::AlignRight, QObject::tr("Page %1/%2").arg(pageNumber+1).arg(pageCount));

#ifdef _DEBUG_PRINT_LINES_
        for (int k = 1; k <= LINES_PER_PAGE; k++) {
            QRectF numRect = borderRect;
            numRect.setX(2*bm);
            numRect.setY(2*bm);

            numRect.setTop(k*painter->fontMetrics().lineSpacing());
            numRect.setWidth(2*bm);
            numRect.setHeight(footerHeight);
            painter->drawText(numRect, Qt::AlignLeft, QObject::tr("%1").arg(k));

        }
        painter->drawRect(footerRect);
#endif
    }
}

void PreviewDialog::printDocument(QPrinter& printer, int copyCount)
{
    printDocument(printer, m_textDocument,0,copyCount);
}

// Calculate and return number of pages. Do it on clone, to aviod damage of
// main document.
int  PreviewDialog::pageCount(QPrinter& printer, QTextDocument* docClone)
{
    QFont cellFont;
    cellFont.setFamily("Bitstream Vera Sans Mono");
    int pointSize = (pitch == PrinterBase::Small ? 8 : 10);
    cellFont.setPointSize(pointSize);
    cellFont.setBold(true);
    cellFont.setKerning(true);

    QFontMetrics fontMetric(cellFont);
    int lineSpacing = fontMetric.lineSpacing();
    QSizeF pageSize = printer.pageRect().size(); // page size in pixels
    // Calculate the rectangle where to lay out the text
    const double tm = mmToPixels(printer, textMargins);
    const qreal footerHeight = fontMetric.height();

    double scaleCoeff = pageSize.height()/(lineSpacing*LINES_PER_PAGE);
    cout << "PreviewDialog::pageCount scaleCoeff: " << scaleCoeff << endl;
    cout << "PreviewDialog::pageCount         tm: " << tm << endl;

    const QRectF textRect(tm, tm + m_topSkipLines*lineSpacing*scaleCoeff,
                          pageSize.width() - 2 * tm, lineSpacing*m_pageHeight*scaleCoeff - 2 * tm - footerHeight);

    int pageCount = 0;
    if (docClone) {
        docClone->setPageSize(textRect.size());
        pageCount = docClone->pageCount();
        // Free cloned document.
        delete docClone;
    }
    return pageCount;
}

void PreviewDialog::printDocument(QPrinter& printer, QTextDocument* doc, QWidget* parentWidget, int copyCount)
{

#ifdef _DEBUG_PRINT_FILE_
    // DEBUG  redirect output to file.
    QString fileName = QString("TestPrint_%1.pdf").arg(QDateTime::QDateTime::currentMSecsSinceEpoch());
    printer.setOutputFileName(fileName);
#endif
    qDebug() << "  PreviewDialog::printDocument() entered.";

    QPainter painter;
    if (! painter.begin( &printer )) {
        qDebug() << "  **************** !!!!!! Failed to initialize printer. !!!!!!";
        return;
    }
    QFont cellFont;
    cellFont.setFamily("Bitstream Vera Sans Mono");
    int pointSize = (pitch == PrinterBase::Small ? 8 : 10);
    cellFont.setPointSize(pointSize);
    cellFont.setBold(true);
    cellFont.setKerning(true);
    painter.setFont(cellFont);

    int lineSpacing = painter.fontMetrics().lineSpacing();
    QSizeF pageSize = printer.pageRect().size(); // page size in pixels
    // Calculate the rectangle where to lay out the text
    const double tm = mmToPixels(printer, textMargins);
    const qreal footerHeight = painter.fontMetrics().height();
    //    const QRectF textRect(tm, tm, pageSize.width() - 2 * tm, pageSize.height() - 2 * tm - footerHeight);
    double scaleCoeff = pageSize.height()/(lineSpacing*LINES_PER_PAGE);
    if (scaleCoeff > 1.0) {  //Don't shrink, only zoom in.
        scaleCoeff = 1.0;
    }
    const QRectF textRect(tm, tm + m_topSkipLines*lineSpacing*scaleCoeff,
                          pageSize.width() - 2 * tm, lineSpacing*m_pageHeight*scaleCoeff );
                          //pageSize.width() - 2 * tm, lineSpacing*m_pageHeight*scaleCoeff - 2 * tm - footerHeight);


    //qDebug() << "textRect=" << textRect;
    int pageCount = 0;
    if (doc) {
        int debugLineCount = doc->lineCount();
        doc->setDocumentMargin(0.0);
        doc->setPageSize(textRect.size());
        pageCount = doc->pageCount();
    }

    QProgressDialog dialog( QObject::tr( "Printing" ), QObject::tr( "Cancel" ), 0, pageCount, parentWidget );
    dialog.setWindowModality( Qt::ApplicationModal );

    bool firstPage = true;
    if (m_checkTextList.size() > pageCount ) {
        pageCount += m_checkTextList.size() - pageCount;
    }
    m_invoicePageNum = 0;
    for (int pageIndex = 0; pageIndex < pageCount; ++pageIndex) {
        dialog.setValue( pageIndex );
        if (dialog.wasCanceled())
            break;

        for (int i = 0; i< copyCount; i++) {
            if (!firstPage) {
                printer.newPage();
            }
            bool isLastCopy = (i==(copyCount-1));
            paintPage( printer, pageIndex, pageCount, &painter, doc, textRect, footerHeight, isLastCopy );
            firstPage = false;
        }
    }
    painter.end();

}




/**

 name:    PreviewDialog( QWidget* parent )
 purpose: Class constructor. Sets ZoomMode and factor, add new print button
          to dialog toolbar.
 calling params: QWidget* parent - parent widget
 return params: None
 Notes:

 Todo:

*/
PreviewDialog::PreviewDialog( QWidget* parent )
    : QPrintPreviewDialog( parent )
{
    m_checkPrintMode = false;
    m_topSkipLines = 0;
    m_pageHeight = LINES_PER_PAGE; //Default height
    m_isNeedPrintCheck = false;

    m_textDocument = new QTextDocument();
    m_checkDocument = new QTextDocument();
    m_loadOutDocument = new QTextDocument();
    m_printButton.setText("Print");
    m_loadOutButton.setText("Invoice");

    setWindowIcon( qApp->windowIcon() );
    connect( this, SIGNAL(paintRequested(QPrinter*)), SLOT(draw(QPrinter*)) );

    QList<QPrintPreviewWidget *> list = findChildren<QPrintPreviewWidget *>();
    if(!list.isEmpty()) { // safety check
        QPrintPreviewWidget * printWidget = list.first();
        printWidget->setZoomMode(QPrintPreviewWidget::FitToWidth);
        printWidget->setZoomFactor(1.0);
        // Add new button to toolbar for direct print.
        QList<QToolBar *> list1 = findChildren<QToolBar *>();
        if(!list1.isEmpty()) { // safety check
            list1.first()->addWidget(&m_printButton);
            connect( &m_printButton, SIGNAL(clicked()),this,SLOT(print()));
            m_loadOutAction = list1.first()->addWidget(&m_loadOutButton);
            connect( &m_loadOutButton, SIGNAL(clicked()),this,SLOT(printLoadout()));
            m_loadOutAction->setVisible(false);

        }
    }
    init();
}

PreviewDialog::~PreviewDialog()
{
    qDebug("PreviewDialog::~PreviewDialog() entered.");
    if (m_textDocument != 0) {
        delete m_textDocument;
        m_textDocument = 0;
    }
    if (m_loadOutDocument !=0) {
        delete m_loadOutDocument;
        m_loadOutDocument = 0;
    }
    if ( m_checkDocument !=0 ) {
        delete m_checkDocument;
        m_checkDocument = 0;
    }
    qDebug() << "PreviewDialog::~PreviewDialog() exited." ;
}

void PreviewDialog::init()
{
    qDebug("PreviewDialog::init()");
    setShowPrint(false);
    m_printerType = PrinterDAO::Report;
    m_report = NULL;
    pitch = PrinterBase::Normal;
}

void PreviewDialog::setShowPrint(bool showPrint)
{
    qDebug("PreviewDialog::setShowPrint(bool showPrint)");
    //    switch(showPrint)
    //    {
    //    case true:
    //        ui->printButton->show();
    //        break;

    //    case false:
    //    default:
    //        ui->printButton->hide();
    //        break;
    //    }
}

void PreviewDialog::setPrintButtonText(QString text)
{
    qDebug("PreviewDialog::setPrintButtonText(QString text)");
    m_loadOutButton.setText(text);
    m_loadOutButton.show();
}

void PreviewDialog::setReport(TextReport *report)
{
    qDebug("PreviewDialog::setReport(TextReport *report)");
    this->m_report = report;

    deque<string> pageList = report->paginatedText(0);
    int commandPos = 0;
    char commandChar = 'X';
    QString text;

    for(unsigned int i = 0; i < pageList.size(); i++)
    {
        QString temp = QString::fromStdString(pageList[i]);
        temp = temp.replace("<", "&lt;");
        temp = temp.replace(">", "&gt;");
        pageList[i] = temp.ascii(); // updated line
        do
        {
            commandPos = pageList[i].find_first_of(string(1, 27), 0);
            commandChar = 'X';
            if(commandPos != string::npos)
            {
                commandChar = pageList[i][commandPos + 1];
                pageList[i].erase(commandPos, 2);

                switch(commandChar)
                {
                case 'M':
                    pageList[i].insert(commandPos, "<small>");
                    break;
                case 'P':
                    pageList[i].insert(commandPos, "</small>");
                    break;

                default:
                    break;

                }
            }

        }
        while(commandPos != string::npos);
        text += (pitch == PrinterBase::Small ? "<small>"+QString::fromStdString(pageList[i]) + "</small>" : QString::fromStdString(pageList[i]))  ;
    }


    setText(text);
}

void PreviewDialog::setShowPrint(bool showPrint, PrinterDAO::PrinterType printerType)
{
    qDebug("PreviewDialog::setShowPrint(bool showPrint, PrinterDAO::PrinterType printerType)");
    this->m_printerType = printerType;
    m_loadOutAction->setVisible(true);
}

void PreviewDialog::print()
{
    qDebug("PreviewDialog::print()");
    print(0);
}

void PreviewDialog::print(PrinterBase* printer)
{
    qDebug("PreviewDialog::print(PrinterBase *printer)");
    bool isNeedDeletePrinter = false;
    if(printer == 0)
    {
        qDebug() << "PreviewDialog::print - Printer is 0, get default printer." ;
        printer = PrinterDAO().getPrinter(m_printerType);
        isNeedDeletePrinter = true;
    }

    QString text = "";
    if(m_report == NULL)
    {
        //  text = ui->previewText->text() + "\f"; // [KLN] Not sure why this is commented-out, yet we process it?
        text = text.replace("&nbsp;", " ");
        text.replace("<BR>", "\n");
    }
    else
    {
        int pageLength = atoi(setup.get("reportPageLength").c_str());
        m_report->setPageLength((pageLength > 1 ? pageLength : 55));
        deque<string> pageList = m_report->paginatedText(atoi(setup.get("reportFirstLine").c_str()));
        for(unsigned int i = 0; i < pageList.size(); i++)
        {
            text += QString::fromStdString(pageList[i]) + QString::fromStdString((pitch == PrinterBase::Small ? string(1, char(PrinterBase::OKI_NORMAL)) : ""))
                    + "\f"
                    +  QString::fromStdString((pitch == PrinterBase::Small ? string(1, char(PrinterBase::OKI_SMALL)) : ""));
        }
    }

    if ( printer->isLaser()) {
        qDebug() << "PreviewDialog::print - Printer is Laser." ;
        QPrinter printerObj;
        printerObj.setPaperSize(QPrinter::Letter);
        printerObj.setPrinterName(printer->printerName());
        printDocument(printerObj,m_textDocument,0);

    }
    else {
        qDebug() << "PreviewDialog::print - Printer is not laser." ;
        printer->print(text.toStdString(),*m_textDocument, pitch);
    }

    qDebug() << "PreviewDialog::print - Before delete printer." ;
    if (isNeedDeletePrinter) {
        delete printer;
    }
    qDebug() << "PreviewDialog::print - After delete printer." ;

    QDialog::accept();

}

///////////////////////////////////////////////////////////////////////////////
//
// name:    setText(const QString &text)
//
// purpose: sets the text of the preview dialog to 'text'
//
// calling params: const QString &text - the text to set in the preview dialog
//
// return params:
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void PreviewDialog::setText(QString text)
{
    qDebug("PreviewDialog::setText(QString text)");
    m_textDocument->clear();

#ifdef _DEBUG_PRINT_PREVIEW_FILE_
    // [KLN] add
    QString home = getenv("HOME");
    const QString previewFilename = home + "/print-preview-report-debug.txt";
    ofstream myfile;
    myfile.open (previewFilename, std::ofstream::out | std::ofstream::app);
    myfile << text.toStdString();
    myfile.close();
    // [KLN] add end
#endif

    QFont printerFont;
    printerFont.setFamily("Bitstream Vera Sans Mono");
    int pointSize = (pitch == PrinterBase::Small ? 8 : 10);
    //int pointSize = 9;
    printerFont.setPointSize(pointSize);
    printerFont.setBold(true);
    printerFont.setKerning(true);
    m_textDocument->setDefaultFont(printerFont);

    text.replace("\n", "<BR>");
    text.replace("\r", "<BR>");
    text.replace(" ", "&nbsp;");
    text.replace("\t", "&nbsp;&nbsp;&nbsp;");
    text.replace("\f","<DIV style=\"page-break-after: always; text-align: center;\">&nbsp;&nbsp;&nbsp;</DIV>");

    text.replace(QChar(15),"");
    text.replace(QChar(18),"");

    QString escape1 = QString("%1%2").arg(QChar(27)).arg(QChar(77));
    QString escape2 = QString("%1%2").arg(QChar(27)).arg(QChar(80));
    text.replace(escape1,"");
    text.replace(escape2,"");
    m_textDocument->setHtml(text);

}

void PreviewDialog::setPrintType(PrinterBase::CharacterPitch printType)
{
    qDebug("PreviewDialog::setPrintType(PrinterBase::CharacterPitch printType)");
    this->pitch = printType;
}

void PreviewDialog::setCheckText(QString text )
{
#ifdef _DEBUG_PRINT_PREVIEW_FILE_
    // [KLN] add
    QString home = getenv("HOME");
    const QString previewFilename = home + "/print-preview-check-debug.txt";
    ofstream myfile;
    myfile.open (previewFilename, std::ofstream::out | std::ofstream::app);
    myfile << text.toStdString();
    myfile.close();
    // [KLN] add end
#endif

    m_checkDocument->clear();
    QFont printerFont;
    printerFont.setFamily("Bitstream Vera Sans Mono");
    int pointSize = (pitch == PrinterBase::Small ? 8 : 10);
    printerFont.setPointSize(pointSize);
    printerFont.setBold(true);
    printerFont.setKerning(true);
    m_checkDocument->setDefaultFont(printerFont);
    text.replace("\n", "<BR>");
    text.replace("\r", "<BR>");
    text.replace(" ", "&nbsp;");
    text.replace("\t", "&nbsp;&nbsp;&nbsp;");
    text.replace(QChar(15),"");
    text.replace(QChar(18),"");

    QString escape1 = QString("%1%2").arg(QChar(27)).arg(QChar(77));
    QString escape2 = QString("%1%2").arg(QChar(27)).arg(QChar(80));
    text.replace(escape1,"");
    text.replace(escape2,"");
    m_checkDocument->setHtml(text);
}

void PreviewDialog::draw(QPrinter* printer)
{
    printer->setPaperSize(QPrinter::Letter);
    printDocument(*printer,m_textDocument,this);
}


void PreviewDialog::setTextDocument(QTextDocument * textDoc)
{
    if (m_textDocument != 0) {
        delete m_textDocument;
    }
    m_textDocument = textDoc;
}
void PreviewDialog::setLoadoutDocument(QTextDocument * textDoc)
{
    if (m_loadOutDocument != 0) {
        delete m_loadOutDocument;
    }
    m_loadOutDocument = textDoc;
}


void PreviewDialog::setPageHeight(int pageHeight)
{
    m_pageHeight = pageHeight;
}

void PreviewDialog::setCheckStartLine(int checkLine)
{
    m_checkStartLine = checkLine;
}

void PreviewDialog::setCheckPrint(bool enable)
{
    m_isNeedPrintCheck = enable;
}
void PreviewDialog::setCheckTextList(QStringList& list )
{
    m_checkTextList = list;
}
void PreviewDialog::setCheckTextList(vector<TextCheck> &list)
{
    m_textCheckList = list;
}

void PreviewDialog::printLoadout()
{
    qDebug("PreviewDialog::printLoadout()");
    PrinterBase *printer = PrinterDAO().getPrinter(PrinterDAO::Loadout);
    if(printer == 0)
    {
        return;
    }

    QString text = "";
    if(m_report == NULL)
    {
        text = text.replace("&nbsp;", " ");
        text.replace("<BR>", "\n");
    }
    else
    {
        int pageLength = atoi(setup.get("reportPageLength").c_str());
        m_report->setPageLength((pageLength > 1 ? pageLength : 55));
        deque<string> pageList = m_report->paginatedText(atoi(setup.get("reportFirstLine").c_str()),true);
        for(unsigned int i = 0; i < pageList.size(); i++)
        {
            text += QString::fromStdString(pageList[i]) + QString::fromStdString((pitch == PrinterBase::Small ? string(1, char(PrinterBase::OKI_NORMAL)) : ""))
                    + "\f"
                    +  QString::fromStdString((pitch == PrinterBase::Small ? string(1, char(PrinterBase::OKI_SMALL)) : ""));
        }
    }

    if ( printer->isLaser()) {
        QPrinter printerObj;
        printerObj.setPaperSize(QPrinter::Letter);
        printerObj.setPrinterName(printer->printerName());
        printDocument(printerObj,m_loadOutDocument,0);

    }
    else {
        printer->print(text.toStdString(),*m_loadOutDocument, pitch);
    }
    delete printer;
    QDialog::accept();

}

void PreviewDialog::setTopSkipLines(int topSkipLines)
{
    m_topSkipLines = topSkipLines;
}


void PreviewDialog::printCheckDocument(QPrinter& printer)
{
    m_checkPrintMode = true;
    printDocument(printer, m_checkDocument, 0);
    m_checkPrintMode = false;

}
