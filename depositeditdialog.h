/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef DEPOSITEDITDIALOG_H
#define DEPOSITEDITDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include "dao/checkdao.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QLineEdit;
class QPushButton;
class QDateEdit;

namespace Ui {
  class DepositEditDialog;
}

class DepositEditDialog : public QDialog
{
    Q_OBJECT

public:
    DepositEditDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~DepositEditDialog();

    void init();

public slots:
    void init( Deposit deposit );
    void saveCleared();
    void saveOutstanding();
    void saveVoided();
    void saveDeposit();

protected:

protected slots:

private:
    Deposit deposit;
    CheckDAO dao;

    Ui::DepositEditDialog *ui;
};

#endif // DEPOSITEDITDIALOG_H
