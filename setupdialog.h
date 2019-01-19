/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef SETUPDIALOG_H
#define SETUPDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include <vector>
#include "./dao/animalcodedao.h"
#include "./types/animalcode.h"
#include "dao/commissiondao.h"
#include "dao/setupdao.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QTabWidget;
class QWidget;
class QPushButton;
class QLabel;
class QLineEdit;
class QSpinBox;
class QCheckBox;

namespace Ui {
  class SetupDialog;
}

class SetupDialog : public QDialog
{
    Q_OBJECT

public:
    SetupDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~SetupDialog();


public slots:
    void startCommEdit();
    void startChargeEdit();
    void startCodeEdit();
    void startSellerInvoiceSetup();
    void startBuyerInvoiceSetup();
    void startCheckSetup();
    void startMarketReportSetup();
    void setupPrinter();
    void extrasSetupDialog();
    void startScaleSetup();
    void loadMarketInfo();
    void saveMarketInfo();
    void startReportSetup();
    void startDisplaysSetup();
    void loadWebAuctions();
    void saveWebAuctions();
//    void loadCattleUSASetup();
//    void saveCattleUSASetup();
//    void loadDVAuctionSetup();
//    void saveDVAuctionSetup();
    void startVideoCameraSetup();
    void startFaxModemSetup();
    void startSaleManagerSetup();

protected:

protected slots:

private slots:
//    void on_enableCattleUSACheckBox_clicked();

private:
    vector<AnimalCode> codeList;
    SetupDAO setup;

    void init();
  
    Ui::SetupDialog *ui;
};

#endif // SETUPDIALOG_H
