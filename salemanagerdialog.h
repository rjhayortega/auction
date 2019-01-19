/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef SALEMANAGERDIALOG_H
#define SALEMANAGERDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include <QInputDialog>
#include "dao/salemanager.h"
#include "dao/setupdao.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QListBox;
class QListBoxItem;
class KDatePicker;
class QLabel;

namespace Ui {
  class SaleManagerDialog;
}

class SaleManagerDialog : public QDialog
{
    Q_OBJECT

public:
    SaleManagerDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~SaleManagerDialog();

 
public slots:
    void populateSaleList();
    void createNew();
    void saveNew();
    void changeCurrentSale( int row );
    void keepDateCurrent( QDate date );
    int getCurrentIndex();
    void closeCurrentSale();
    void openSelectedSale();
    int checkSelection();
    void setActive();
    QString getPassword();

protected:

protected slots:

private:
    vector<Sale> saleList;
    SaleManager sale;
    bool block;
    SetupDAO m_setup;

    void init();

    Ui::SaleManagerDialog *ui;
};

#endif // SALEMANAGERDIALOG_H
