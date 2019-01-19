/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef DISPLAYSETUPDIALOG_H
#define DISPLAYSETUPDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include "dao/setupdao.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QPushButton;
class QLineEdit;
class QComboBox;
class QSpinBox;
class QTable;

namespace Ui {
  class DisplaySetupDialog;
}

class DisplaySetupDialog : public QDialog
{
    Q_OBJECT

public:
    DisplaySetupDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~DisplaySetupDialog();

public slots:
    void init( SetupDAO::DisplayRecord display );
    void initRowsTable();
    void browse();
    void save();

protected:

protected slots:

private:
    SetupDAO setup;
    SetupDAO::DisplayRecord display;
    QStringList itemList;

    void init();
    Ui::DisplaySetupDialog *ui;
};

#endif // DISPLAYSETUPDIALOG_H
