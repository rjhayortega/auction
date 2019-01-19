/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef PERMSEARCHDIALOG_H
#define PERMSEARCHDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include "dao/customerdao.h"
#include "dao/checkdao.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QListBox;
class QListBoxItem;
class QPushButton;

namespace Ui {
  class PermSearchDialog;
}

class PermSearchDialog : public QDialog
{
    Q_OBJECT

public:
    PermSearchDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~PermSearchDialog();

    Customer getSelectedCustomer();

public slots:
    void init( QString namePart, Customer::Type type );
    void clearSelection();
    void showValidNames();

protected:

protected slots:

private:
    vector<Customer> customerList;
    QString namePart;
    Customer::Type type;
    CheckDAO checkDao;
    bool looseMatch;

    void init();
    void setLooseMatch(bool);
    
    Ui::PermSearchDialog *ui;

};

#endif // PERMSEARCHDIALOG_H
