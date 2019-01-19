/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef PRORATEDIALOG_H
#define PRORATEDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include "types/invoice.h"
#include "types/prorate.h"
#include "types/checkfactory.h"
#include "dao/proratedao.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QPushButton;
class Q3Table;
class QCheckBox;
class QComboBox;

namespace Ui { 
  class ProrateDialog;
}

class ProrateDialog : public QDialog
{
    Q_OBJECT

public:
    ProrateDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~ProrateDialog();


    enum LIMIT_TYPE{BY_PER = 0, BY_SEX = 1, BY_TRANS = 2, BY_HEAD = 3, BY_FLAT = 4};
    enum CODE_FIELD{CODE = 0, HEAD = 1, AMOUNT = 2};

    virtual vector<Prorate::Data> primaryDataList();
    virtual QString getProrateDataString( vector<Prorate::Data> dataList );

public slots:
     void init( Invoice invoice );
     void changeProrateMode( int selected );
     void updateProrates();
     void updateShareList();
     void initTable();
     void startSpecialProrate( int row, int col );
     void startTransactionProrate( int row );
     void startSexProrate( int row );
     void createPayee();
     void initCheckFactory();
     void save();
    void removeCurrentPayee();

protected:

protected slots:

private:
    Invoice invoice;
    vector<Prorate> prorateList;
    CheckFactory *checkFactory;
    vector<Prorate> prorates;
    ProrateDAO prorateDao;
    bool block;

    void init();
    void destroy();
    void initTableRow( unsigned int row );

    Ui::ProrateDialog *ui;
};

#endif // PRORATEDIALOG_H
