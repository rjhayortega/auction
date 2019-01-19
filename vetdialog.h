/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef VETDIALOG_H
#define VETDIALOG_H

#include <QDialog>


#include <vector>
#include "dao/tagdao.h"
#include "dao/transactiondao.h"
#include "dao/salemanager.h"
#include "types/healthrecord.h"
#include "reports/tuberculosisrecord.h"
#include "dao/setupdao.h"
#include "lineprinter.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QPushButton;
class QGroupBox;
class QComboBox;
class QLineEdit;
class QDateEdit;
class QSpinBox;
class QCheckBox;


namespace Ui {
  class VetDialog;
}

class VetDialog : public QDialog
{
    Q_OBJECT

public:
    VetDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~VetDialog();

    bool saveCurrentTag();
    QStringList validateEntry();

public slots:
    void initSeller( Seller seller );
    void showCurrentTag();
    void loadNextTag();
    void loadPreviousTag();
    void autoSave();
    void browseTags();
    void printForm( int formId );
    void printSouthDakotaHealthCertificate();
    void printMinnesotaVeterinaryCertificate();
    void printTuberculosisTestRecord();
    void printAlternateMinnesotaVetInspection();
    void printMinnesotaVetCert( HealthRecord healthRecord );
    void printTuberculosisRecord( HealthRecord record );
    void reject();
    void accept();
    void validateBrucellosis( const QString & data );
    void validateSex();
    void setupTagToAdd();
    void search();
    void loadVetData();
    void editVet();
    void printAllflexReport();
    void printBrucellosisTestRecord();
    void printBrucellosisTestRecord( HealthRecord record );
    void printSouthDakotaHealthCertificate( HealthRecord record );
    void autoChangeIndex();
    void printForm( TextReport * cert, int topSkip );
    void processLpstatData();
    void setupPrinterList();
    void editFormMetrics();
    void loadVetFormMetrics();
    void sellerSummary();
    void updateVetPrinter( const QString & vetPrinter );

protected:

private:
    Seller seller;
    QValidator* btagValidator;
    SaleManager sale;
    Tag currentTag;
    TransactionDAO transactionDao;
    TagDAO tagDao;
    QString oldBrucellosisText;
    Person vet;
    SetupDAO setup;
    PrinterBase * m_printer;
    QProcess lpstatProc;
    QString lpstatBuffer;
    QStringList printerMenu;
    QStringList vetFormMetrics;

    void init();
    Ui::VetDialog *ui;
    
};

#endif // VETDIALOG_H
