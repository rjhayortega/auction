/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef PERMANANTDIALOG_H
#define PERMANANTDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include <vector>
#include "dao/customerdao.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QLineEdit;
class QComboBox;
class QPushButton;
class QButtonGroup;
class QRadioButton;
class Q3ListBox;
class Q3ListBoxItem;
class QCheckBox;

namespace Ui {
  class PermanantDialog;
}
class PermanantDialog : public QDialog
{
    Q_OBJECT

public:
    PermanantDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~PermanantDialog();


    Customer::Type currentType();

public slots:
    void init( Customer::Type type );
    void populateCustomerList();
    void permListSearch( const QString & text );
    void autoLoadPerm();
    void loadItem( int row );
    void saveItem();
    void reset();
    void deletePermanent();
    void showReport();
    void loadCityStateZipFromCity();
    void loadCityStateZipFromZip();
    void autoLoadCityStateZip( vector<Address> zipCodeList );
    void printMailingLabels();
    void keyPressEvent( QKeyEvent * event );


protected:

protected slots:
    void onPermNumLostFocus();
private:
    vector<Customer> customerList;
    CustomerDAO customerDao;
    long custId;
    bool blockLoad;

    void init();
    static bool comparePermanantCustomers( Customer a, Customer b );
    
    Ui::PermanantDialog *ui;

};

#endif // PERMANANTDIALOG_H
