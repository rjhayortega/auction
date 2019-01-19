/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef READYSELLERDIALOG_H
#define READYSELLERDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include <qprogressdialog.h>
#include "dao/invoicedao.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class Q3ListBox;
class Q3ListBoxItem;

namespace Ui {
  class ReadySellerDialog;
}

class ReadySellerDialog : public QDialog
{
    Q_OBJECT

public:
    ReadySellerDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~ReadySellerDialog();

    QString getNumber();
    static void progressCallback( int completed, int total );

public slots:
    void setDAO( InvoiceDAO * invoiceDao );
    void populateReadyList();
    void accept( int row );

protected:

protected slots:

private:
    vector<string> readyList;
    QString number;
    InvoiceDAO* invoiceDao;
    static QProgressDialog* progressDialog;

    void init();

    Ui::ReadySellerDialog *ui;
};

#endif // READYSELLERDIALOG_H
