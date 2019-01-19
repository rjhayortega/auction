/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef CHECKREGISTER_H
#define CHECKREGISTER_H

#include <qvariant.h>
#include <qdialog.h>
#include <vector>
#include "dao/checkdao.h"
#include "dao/setupdao.h"
#include "dao/salemanager.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QGroupBox;
class QTable;
class QButtonGroup;
class QRadioButton;
class QDateEdit;
class QCheckBox;
class QLabel;
class QLineEdit;
class QTabWidget;
class QWidget;
class QComboBox;
class Q3ListView;
class Q3ListViewItem;

namespace Ui {
  class CheckRegister;
}

class CheckRegister : public QDialog
{
    Q_OBJECT

public:
    CheckRegister( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~CheckRegister();


    static bool avoidCheckConflict( QWidget * parent );
    vector<Check> getSelectedChecks();
    vector<Deposit> getSelectedDeposits();

public slots:
    void newCheck();
    void populateCheckList();
    void showCheckList();
    void editCheck( Q3ListViewItem * item );
    void editCheck( int row );
    void setSelectedCleared();
    void setSelectedOutstanding();
    void setSelectedVoided();
    void setSelectedStatus( Check::STATUS status );
    void populateDepositList();
    void newDeposit();
    void editDeposit( Q3ListViewItem * item );
    void calculateSummary();
    void setNextCheckNo();
    void deleteChecks();
    void printRegister();
    void startCheckPost();
    void handleCheckNumberRequest();
    void setNumberOption();
    void sortCheckListByIndex();
    void searchChecksByIndex();

protected:

protected slots:
    
private:
    vector<Deposit> depositList;
    vector<Check> checkList;
    CheckDAO dao;
    SetupDAO setup;
    SaleManager sale;

    void init();

    Ui::CheckRegister *ui;
};

#endif // CHECKREGISTER_H
