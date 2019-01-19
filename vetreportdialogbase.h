/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef VETREPORTDIALOGBASE_H
#define VETREPORTDIALOGBASE_H

#include <qvariant.h>
#include <qdialog.h>
#include <string>
#include <vector>
#include "lineprinter.h"
#include "types/tag.h"
#include "dao/tagdao.h"
#include "dao/setupdao.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QLabel;
class QGroupBox;
class QComboBox;
class QTextEdit;
class QSpinBox;

namespace Ui{
  class VetReportDialogBase;
}

class VetReportDialogBase : public QDialog
{
    Q_OBJECT

public:
    VetReportDialogBase( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~VetReportDialogBase();

    string headerColKey();
    string headerRowKey();
    QString makePage( QStringList headerText, QStringList bodyText, QStringList footerText, int bodySpace );
    TagDAO::Index getIndex();
    QStringList nextBodyLine( bool * last );
    QStringList tagLine( Tag t );

public slots:
    void delayedInit();
    void setPrinter( PrinterBase* p );
    void initHeight();
    void initHeader();
    void initHeaderCursorPos();
    void initFooter();
    void heightChanged( int value );
    void headerChanged();
    void footerChanged();
    void headerChanged( const QString & text );
    void footerChanged( const QString & text );
    void print();
    void initTagVector();
    void headerCursorMoved( int para, int pos );
    void footCursorMoved( int para, int pos );
    void setIndexRange();
    void importText( int index );
    void importDailyBuyerText();
    void importPermBuyerText();
    void insertText( QStringList insert );

protected:
    string heightKey();
    string headerKey();
    string footerKey();

    QGridLayout* VetReportDialogBaseLayout;
    QSpacerItem* spacer4;
    QGridLayout* rangeGroupLayout;

protected slots:

private:
    PrinterBase* m_printer;
    vector<Tag> tagVector;
    int currentTag;
    TagDAO tagDao;
    SetupDAO setup;

    void init();
    
    Ui::VetReportDialogBase *ui;

};

#endif // VETREPORTDIALOGBASE_H
