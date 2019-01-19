/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef ZIPCODEDIALOG_H
#define ZIPCODEDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include <vector>
#include "types/address.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class Q3ListBox;
class Q3ListBoxItem;

namespace Ui {
  class ZipCodeDialog;
}

class ZipCodeDialog : public QDialog
{
    Q_OBJECT

public:
    ZipCodeDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~ZipCodeDialog();

    Address getCurrentAddress();

public slots:
    void init( vector<Address> zipCodeList );

protected:

protected slots:
    

private:
    vector<Address> zipCodeList;

    void init();

    Ui::ZipCodeDialog *ui;
};

#endif // ZIPCODEDIALOG_H
