/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef DAILYDIALOG_H
#define DAILYDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include <vector>
#include "./types/customer.h"
#include "./dao/customerdao.h"
#include "dao/setupdao.h"
#include "serialport.h"
#include "dao/radiotagdao.h"
#include "dao/salemanager.h"

#include <Q3ListBox>

namespace Ui {
  class DailyDialog;
}

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QLineEdit;
class QButtonGroup;
class QRadioButton;
class QCheckBox;
class Q3ListBox;
class Q3ListBoxItem;
class QPushButton;
class QComboBox;

class DailyDialog : public QDialog
{
    Q_OBJECT

public:
    DailyDialog( QWidget* parent = 0);
    virtual ~DailyDialog();

    void init();

    typedef enum {SELLER, BUYER} CUSTOMER_TYPE;

    Customer::Type getCustomerType();
    bool mergeSeller();
    static Customer checkPayeeLength( Customer baseCustomer, QWidget * parent );

public slots:
    void timerEvent( QTimerEvent * e );
    void polish();
    void populateDailyList();
    void populateDailyList( QString selectNumber );
    void loadItemFromList( int index );
    void showDaily( Customer customer, bool loadNumber );
    void saveDaily();
    void removeCurrentDaily();
    void searchListByNumber();
    void searchListByName( const QString & text );
    void init( Customer::Type customerType );
    void clearDaily();
    void resetDaily();
    void changeDialogMode( int buttonId );
    void populatePermList();
    void loadDailyFromPerm( int row );
    void startChargeAdjustment();
    void startTrucking();
    void startTagEdit();
    void showDailyReport();
    void findNearest( const QString & text );
    void autoLoadPerm();
    void loadCityStateZipFromCity();
    void loadCityStateZipFromZip();
    void autoLoadCityStateZip( vector<Address> zipCodeList );
    void mergeDaily();
    void keyPressEvent( QKeyEvent * keyPress );
    void startVet();
    void displayAnimalCodeDescr();
    // [KLN] add (for debugging)
    void showCustomerType( const string & funcName );
    // [KLN] add end
    void showMissingBuyers();

protected:

protected slots:

private:
    bool blockAutoMerge;
    SaleManager sale;
    vector<RadioTag> radioTagList;
    int timerId;
    bool rfIdTagsOn;
    SerialPort rfTagPort;
    bool blockInit;
    bool blockLoad;
    long customerId;
    vector<Customer> permList;
    vector<Buyer>::iterator currentBuyer;
    vector <Seller>::iterator currentSeller;
    int lastSelected;
    vector <Buyer> buyerList;
    vector <Seller>sellerList;
    Customer::Type customerType;
    CustomerDAO *dao;
    SetupDAO setup;

    void destroy();
    
    Ui::DailyDialog *ui;

};

#endif // DAILYDIALOG_H
