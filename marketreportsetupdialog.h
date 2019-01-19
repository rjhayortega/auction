/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef MARKETREPORTSETUPDIALOG_H
#define MARKETREPORTSETUPDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include "dao/setupdao.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QGroupBox;
class Q3Table;
class QPushButton;

namespace Ui {
  class MarketReportSetupDialog;
}

class MarketReportSetupDialog : public QDialog
{
    Q_OBJECT

public:
    MarketReportSetupDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~MarketReportSetupDialog();

public slots:
    void swapItem( int row, int col );
    void save();
    void checkValues();

protected:

protected slots:

private:
    QStringList sortMenu;
    QStringList keyList;
    SetupDAO setup;
    bool blockSignal;

    void init();
    Ui::MarketReportSetupDialog *ui;
};

#endif // MARKETREPORTSETUPDIALOG_H
