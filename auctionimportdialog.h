/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef AUCTIONIMPORTDIALOG_H
#define AUCTIONIMPORTDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include "dao/customerdao.h"
#include "types/customer.h"
#include "types/check.h"
#include "dao/checkdao.h"
#include "types/historyitem.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLineEdit;
class QPushButton;
class QComboBox;


namespace Ui {
  class AuctionImportDialog;
}

class AuctionImportDialog : public QDialog
{
    Q_OBJECT

public:
    AuctionImportDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~AuctionImportDialog();


    Customer getCustomerFromFile( ifstream & inputFile, bool & alteredRecord, int & lineLength );
    Customer getBuyerFromFile( ifstream & inputFile, int & lineLength );
    Check getCheckFromFile( ifstream & inputFile, int & lineLength );
    HistoryItem getHistoryFromFile( ifstream & inputFile, int & lineLength );

public slots:
    void importPermanant();
    void createScript();
    void importFile();
    void createCustomerImportScript();
    void extractCityStateZip( string cityStZipStr, string & city, string & state, string & zip );
    void getFileNameToImport();
    void createCheckImportScript();
    void importChecks();
    void createHistoryImportScript();

protected:

protected slots:

private:
    QString lastPath;

    void init();

    Ui::AuctionImportDialog *ui;
};

#endif // AUCTIONIMPORTDIALOG_H
