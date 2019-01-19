/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef DISPLAYBROWSERDIALOG_H
#define DISPLAYBROWSERDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include "dao/setupdao.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class Q3ListBox;
class Q3ListBoxItem;
class QPushButton;

namespace Ui {
  class DisplayBrowserDialog;
}

class DisplayBrowserDialog : public QDialog
{
    Q_OBJECT

public:
    DisplayBrowserDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~DisplayBrowserDialog();

public slots:
    void populateDisplayList();
    void editDisplay();
    void newDisplay();
    void deleteDisplay();

protected:

protected slots:

private:
    vector<SetupDAO::DisplayRecord> displayList;
    SetupDAO setup;
    int nextNum;
  
    void init();
  Ui::DisplayBrowserDialog *ui;
};

#endif // DISPLAYBROWSERDIALOG_H
