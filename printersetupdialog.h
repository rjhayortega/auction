/****************************************************************************
** Updated to Qt4
**
** Added namespace Ui
** Added private:  Ui::ClassName *ui;
**
****************************************************************************/

#ifndef PRINTERSETUPDIALOG_H
#define PRINTERSETUPDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include <qprocess.h>
#include "dao/printerdao.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QCheckBox;
class Q3Table;

namespace Ui {
  class PrinterSetupDialog;
}

class PrinterSetupDialog : public QDialog
{
    Q_OBJECT

public:
    PrinterSetupDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~PrinterSetupDialog();

public slots:
    void loadPrinterData();
    void processLpstatData();
    void getPrinterMenu();
    void savePrinterMapTable();
    void saveDefaultPrinterTable();
    void loadPrinterMapTable();
    void loadDefaultPrinterTable();
    void save();

protected:

protected slots:

private:
    QStringList printerMenu;
    PrinterDAO dao;
    QProcess lpstatProc;
    QString lpstatBuffer;
    Ui::PrinterSetupDialog *ui;

private slots:
    void init();
};

#endif // PRINTERSETUPDIALOG_H
