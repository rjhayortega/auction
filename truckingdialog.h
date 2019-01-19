/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef TRUCKINGDIALOG_H
#define TRUCKINGDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include <vector>
#include "dao/truckingrecorddao.h"
#include "types/invoice.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QListBox;
class QListBoxItem;
class QPushButton;
class QLineEdit;
class QComboBox;

namespace Ui {
  class TruckingDialog;
}


class TruckingDialog : public QDialog
{
    Q_OBJECT

public:
    TruckingDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~TruckingDialog();


public slots:
    void init();
    void init( Invoice invoice, ChargeDAO::CUST_TYPE customerType );
    void autoSaveTrucker();
    void reformatForm();
    void saveTrucker();
    void populateTruckerList();
    void loadTrucker( int row );
    void recalc();
    void deleteTrucker();
    void reset();

protected:

protected slots:

private:
    bool newTrucker;
    vector<TruckingRecord> truckingList;
    TruckingRecordDAO dao;
    Invoice invoice;
    ChargeDAO::CUST_TYPE customerType;
    Ui::TruckingDialog *ui;

private slots:
    void destroy();
};

#endif // TRUCKINGDIALOG_H
