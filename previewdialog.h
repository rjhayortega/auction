/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef PREVIEWDIALOG_H
#define PREVIEWDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include "dao/printerdao.h"
#include "reports/textreport.h"
#include "dao/setupdao.h"
#include <QPrintPreviewDialog>
#include <QPushButton>
#include <QAction>
#include "reports/textcheck.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QTextEdit;

namespace Ui {
  class PreviewDialog;
}

class PreviewDialog : public QPrintPreviewDialog
{
    Q_OBJECT

public:
    PreviewDialog( QWidget* parent = 0 );
    virtual ~PreviewDialog();
    void setTextDocument(QTextDocument * textDoc);
    void setLoadoutDocument(QTextDocument * textDoc);
    void setPageHeight(int pageHeight);
    void setCheckStartLine(int checkLine);
    void setCheckTextList(QStringList& list );
    void setCheckTextList(vector<TextCheck> &list );

    void printDocument(QPrinter& printer, QTextDocument* doc, QWidget* parentWidget,int copyCount = 1);

    void printDocument(QPrinter& printer,int copyCount=1);
    void setTopSkipLines(int topSkipLines);
    int  pageCount(QPrinter& printer, QTextDocument* docClone);

    void printCheckDocument(QPrinter& printer);

public slots:
    void setShowPrint( bool showPrint );
    void setPrintButtonText( QString text );
    void setReport( TextReport * m_report );
    void setShowPrint( bool showPrint, PrinterDAO::PrinterType printerType );
    void setText( QString text );
    void setPrintType( PrinterBase::CharacterPitch printType );
    void setCheckText(QString text );
    void setCheckPrint(bool enable);
    void printLoadout();

protected:

private slots:
    void draw( QPrinter* printer);
    void print();
    void print(PrinterBase *printer );  // If printer is 0, the printer type selected from setup.


private:
    double mmToPixels(QPrinter& printer, int mm);
    void   paintPage(QPrinter& printer, int pageNumber, int pageCount,
                          QPainter* painter, QTextDocument* doc,
                          const QRectF& textRect, qreal footerHeight, bool isLastCopyPage);  //isLastCopyPage - indicate this page is last copy.
                                                                                            // Need to know to increase invoice page number.s




private:
    bool allowPrint;
    PrinterDAO::PrinterType m_printerType;
    TextReport *m_report;

    SetupDAO setup;
    PrinterBase::CharacterPitch pitch;
    QPushButton  m_printButton;
    QPushButton  m_loadOutButton;
    QAction * m_loadOutAction;

    void init();
    
    QTextDocument * m_textDocument;
    QTextDocument * m_checkDocument;
    QTextDocument * m_loadOutDocument;

    int m_pageHeight;
    int m_topSkipLines;
    int m_checkStartLine;
    bool m_isNeedPrintCheck;
    QStringList m_checkTextList;
    vector<TextCheck> m_textCheckList;

    bool m_checkPrintMode; //Hack to make checks working
    int m_invoicePageNum;

};

#endif // PREVIEWDIALOG_H
