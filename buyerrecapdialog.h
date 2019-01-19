#ifndef BUYERRECAPDIALOG_H
#define BUYERRECAPDIALOG_H
  
#include <QDialog>
#include "ui_buyerrecapdialog.h"
#include <vector>
#include "types/chargerecord.h"
#include "ui_faxsenddialog.h"

using namespace::std;
class PrinterBase;
class QListWidgetItem;

namespace Ui {
  class BuyerRecapDialog;
}
  
class BuyerRecapDialog : public QDialog {
  Q_OBJECT
  public:
  BuyerRecapDialog(QWidget *parent = 0);
  virtual ~BuyerRecapDialog();
  
private slots:
  vector<ChargeRecord> getBuyerRecapCharges();
  void generateReport();
  void printBuyers();
  void allBuyers();
  void removeBuyer(const QModelIndex &index);
  void addBuyer();
  void faxBuyers();

private:
  Ui::BuyerRecapDialog ui;
  Ui::sendFaxDialog sendFaxDialog;
  PrinterBase * m_reportPrinter;
  
  };
  
#endif // BUYERRECAPDIALOG_H
