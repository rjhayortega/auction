//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add ui->setupUi(this);
//   Add delete ui;
//   delete moc include at end

#include "textdialog.h"
#include "checkregister.h"
#include "ui_checkregister.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qgroupbox.h>
#include <Q3Table>
#include <qbuttongroup.h>
#include <qradiobutton.h>
#include <qdatetimeedit.h>
#include <qcheckbox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qtabwidget.h>
#include <qwidget.h>
#include <qcombobox.h>
#include <Q3ListView>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

CheckRegister::CheckRegister( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
  : QDialog( parent, name, modal, fl ), ui(new Ui::CheckRegister)
{

  ui->setupUi(this);

  // signals and slots connections
  connect( ui->buttChkNo, SIGNAL( clicked() ), this, SLOT( setNextCheckNo() ) );
  connect( ui->filterGroup, SIGNAL( clicked(int) ), this, SLOT( populateDepositList() ) );
  connect( ui->listViewDeposits, SIGNAL( doubleClicked(Q3ListViewItem*) ), this, SLOT( editDeposit(Q3ListViewItem*) ) );
  connect( ui->buttonNewDep, SIGNAL( clicked() ), this, SLOT( newDeposit() ) );
  connect( ui->buttonVoidSel, SIGNAL( clicked() ), this, SLOT( setSelectedVoided() ) );
  connect( ui->buttonOutSel, SIGNAL( clicked() ), this, SLOT( setSelectedOutstanding() ) );
  connect( ui->buttonClearSel, SIGNAL( clicked() ), this, SLOT( setSelectedCleared() ) );
  connect( ui->filterGroup, SIGNAL( clicked(int) ), this, SLOT( populateCheckList() ) );
  connect( ui->buttonNewChk, SIGNAL( clicked() ), this, SLOT( newCheck() ) );
  connect( ui->buttonDone, SIGNAL( clicked() ), this, SLOT( accept() ) );
  connect( ui->deleteChecksButtons, SIGNAL( clicked() ), this, SLOT( deleteChecks() ) );
  connect( ui->buttonReport, SIGNAL( clicked() ), this, SLOT( printRegister() ) );
  connect( ui->registerFromDate, SIGNAL( valueChanged(const QDate&) ), this, SLOT( populateCheckList() ) );
  connect( ui->registerToDate, SIGNAL( valueChanged(const QDate&) ), this, SLOT( populateCheckList() ) );
  connect( ui->postChecksButton, SIGNAL( clicked() ), this, SLOT( startCheckPost() ) );
  connect( ui->fromNumberEdit, SIGNAL( textChanged(const QString&) ), this, SLOT( handleCheckNumberRequest() ) );
  connect( ui->toNumberEdit, SIGNAL( textChanged(const QString&) ), this, SLOT( handleCheckNumberRequest() ) );
  connect( ui->fromNumberEdit, SIGNAL( returnPressed() ), this, SLOT( handleCheckNumberRequest() ) );
  connect( ui->toNumberEdit, SIGNAL( returnPressed() ), this, SLOT( handleCheckNumberRequest() ) );
  connect( ui->checkTable, SIGNAL( doubleClicked(int,int,int,const QPoint&) ), this, SLOT( editCheck(int) ) );
  connect( ui->indexCombo, SIGNAL( activated(int) ), this, SLOT( showCheckList() ) );
  connect( ui->searchEdit, SIGNAL( returnPressed() ), this, SLOT( searchChecksByIndex() ) );
  connect( ui->searchButton, SIGNAL( clicked() ), this, SLOT( searchChecksByIndex() ) );
  connect( ui->payeeFilterEdit, SIGNAL( textChanged(const QString&) ), this, SLOT( populateCheckList() ) );

  init();


}

/*
 *  Destroys the object and frees any allocated resources
 */
CheckRegister::~CheckRegister()
{
  delete ui;
}

#include "checkeditdialog.h"
#include "depositeditdialog.h"
#include <qinputdialog.h>
#include <qmessagebox.h>
#include "previewdialog.h"
#include "reports/checkreport.h"
#include "postcheckdialog.h"
#include <algorithm>

/******************************************************************************
class LeftTableItem

description: a Table Item that is always aligned on the left
*****************************************************************************/
class LeftTableItem : public Q3TableItem
{
public:
  LeftTableItem(Q3Table* parent=NULL, QString text = "") : Q3TableItem(parent, Q3TableItem::Never, text)
  {}
  virtual int aligment()
  {
    return Qt::AlignLeft;
  }
};

/******************************************************************************
class RightTableItem

description: a Table Item that is always aligned on the right
*****************************************************************************/
class RightTableItem : public Q3TableItem
{
public:
  RightTableItem(Q3Table* parent=NULL, QString text = "") : Q3TableItem(parent, Q3TableItem::Never, text)
  {}

  virtual int alignment()
  {
    return Qt::AlignRight;
  }
};

///////////////////////////////////////////////////////////////////////////////
//
// name:    init()
//
// purpose: constructor like function
//
// calling params:
//
// return params:
//
// Notes:
//
// Todo:  Find a better way to keep the check an deposit list currents, this
//        feels like it will be slow
//
///////////////////////////////////////////////////////////////////////////////

void CheckRegister::init()
{
  Date saleDate = sale.currentSaleDate();
  Date toDate = sale.maxNextNonSaleDay();

  QDate temp = QDate(saleDate.getYear(), saleDate.getMonth(),saleDate.getDay());
  ui->registerFromDate->setDate(temp);
  temp = QDate(toDate.getYear(), toDate.getMonth(), toDate.getDay());
  ui->registerToDate->setDate(temp);
  ui->indexCombo->setCurrentItem(1);
  populateCheckList();
  populateDepositList();

  ui->checkTable->verticalHeader()->hide();
  ui->checkTable->setLeftMargin(0);
  ui->checkTable->setColumnWidth(0, 120);
  ui->checkTable->setColumnWidth(1, 90);
  ui->checkTable->setColumnWidth(2, 470);
  ui->checkTable->setColumnWidth(3, 120);
  ui->checkTable->setColumnWidth(4, 20);
}

///////////////////////////////////////////////////////////////////////////////
//
// name:    newCheck()
//
// purpose: Starts a check edit dialog with the newCheck flag set to true
//
// calling params:
//
// return params:
//
// Notes: Checks created with this function will be able to be saved and
//        printed
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void CheckRegister::newCheck()
{
  CheckEditDialog checkEdit(this);
  long nextCheckNo = 0;

  nextCheckNo = dao.peekAtNextCheckNo();

  Check nextCheck(0, nextCheckNo);
  nextCheck.setType(Check::Misc);
  checkEdit.init(dao.saveCheck(nextCheck), true);
  checkEdit.exec();

  populateCheckList();
}

bool CheckRegister::avoidCheckConflict(QWidget* parent)
{
  int option = QMessageBox::question(parent, "Check Conflict",
                                     "This check number already exists,\n"
                                     "What do you want to do?\n",
                                     "Change number?", "Allow Duplicate");

  switch(option)
    {
    case 0:
      CheckRegister().setNextCheckNo();
      return false;
      break;
    case 1:
      return true;
      break;
    }
  return false;
}

///////////////////////////////////////////////////////////////////////////////
//
// name:    populateCheckList()
//
// purpose: populates the check list view by retrieving a list of checks from
//          the database into the objects class list and copying data from that
//          list into the list view
//
// calling params:
//
// return params:
//
// Notes:
//
// Todo:
//
//////////////////////////////////////////////////////////////////////////////

void CheckRegister::populateCheckList()
{
  setCursor(Qt::WaitCursor);
  QDate fromQDate = ui->registerFromDate->date();
  QDate toQDate = ui->registerToDate->date();

  Date fromDate = Date(fromQDate.day(), fromQDate.month(), fromQDate.year());
  Date toDate = Date(toQDate.day(), toQDate.month(), toQDate.year());
  string payeeFilter = ui->payeeFilterEdit->text().toStdString();

  if(ui->dateOption->isChecked())
    {
      checkList = dao.getCheckList(fromDate, toDate, ui->showVoidBox->isChecked(), ui->showOutBox->isChecked(), ui->showClearBox->isChecked(), payeeFilter);
    }
  else
    {
      long fromNumber = ui->fromNumberEdit->text().toLong();
      long toNumber = ui->toNumberEdit->text().toLong();

      if(ui->toNumberEdit->text().length( ) == 0)
        {
          toNumber = fromNumber;
        }
      checkList = dao.getCheckList(fromNumber, toNumber, ui->showVoidBox->isChecked(), ui->showOutBox->isChecked(), ui->showClearBox->isChecked(), payeeFilter);
    }

  showCheckList();

  calculateSummary();
  setCursor(Qt::ArrowCursor);
}

void CheckRegister::showCheckList()
{
  sortCheckListByIndex();

  vector<Check>::iterator current;
  string status[3] = {"O", "V", "C"};
  int row = 0;
  ui->checkTable->setNumRows(checkList.size());

  for(current = checkList.begin(); current != checkList.end(); current++)
    {
      if(current->getStatus() == Check::Void && ui->showVoidBox->isChecked() ||
         current->getStatus() == Check::Out && ui->showOutBox->isChecked() ||
         current->getStatus() == Check::Cleared && ui->showClearBox->isChecked())
        {
          ui->checkTable->setText(row, 0, QString::fromStdString(current->getDate().toString("mm-dd-YYYY")));
          ui->checkTable->setText(row, 1, QString::number(current->getNumber()));
          ui->checkTable->setText(row, 2, QString::fromStdString(current->getPayee()));
          ui->checkTable->setText(row, 3, QString::number(current->getAmount(), 'f', 2));
          ui->checkTable->setText(row, 4, QString::fromStdString(status[current->getStatus()]));
          row++;
        }
    }
}
///////////////////////////////////////////////////////////////////////////////
//
// name:    editCheck(QListViewItem *)
//
// purpose: starts the check edit dialog with a check from the checkList
//
// calling params: QListViewItem *item - an item in the QListView
//
// return params:
//
// Notes: Checks in the CheckEditDialog created by this function will only
//        be able to have the status changed in the database
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void CheckRegister::editCheck(Q3ListViewItem *item)
{
  if(item == NULL)
    {
      return;
    }

  CheckEditDialog checkEdit(this);
  checkEdit.init(dao.getCheckById(item->text(5).toLong()), false);
  checkEdit.exec();
  populateCheckList();
}

void CheckRegister::editCheck(int row)
{
  if(0 <= row && row < checkList.size())
    {
      CheckEditDialog checkEdit(this);
      checkEdit.init(checkList[row], false);
      checkEdit.exec();
      populateCheckList();
    }
}

///////////////////////////////////////////////////////////////////////////////
//
// name:    setSelectedCleared()
//
// purpose: sets the status of all of the selected items in the deposit and
//          check list views to cleared
//
// calling params:
//
// return params:
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void CheckRegister::setSelectedCleared()
{
  setSelectedStatus(Check::Cleared);
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    setSelectedOutstanding()
//
// purpose: sets the status of all of the selected items in the deposit and
//          check list views to outstanding
//
// calling params:
//
// return params:
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void CheckRegister::setSelectedOutstanding()
{
  setSelectedStatus(Check::Out);
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    setSelectedVoided()
//
// purpose: sets the status of all of the selected items in the deposit and
//          check list views to void
//
// calling params:
//
// return params:
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void CheckRegister::setSelectedVoided()
{
  setSelectedStatus(Check::Void);
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    setSelectedStatus(Check::STATUS)
//
// purpose: sets the status of all of the selected items in the deposit and
//          check list views to 'status'
//
// calling params: Check::STATUS status - the status to change the selected
//                                        items to
//
// return params:
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void CheckRegister::setSelectedStatus(Check::STATUS status)
{
  vector<Check> toClear;
  vector<Deposit> depClear;

  if(ui->tabChecks->currentPageIndex() == 0)
    {
      toClear = getSelectedChecks();
    }
  else if(ui->tabChecks->currentPageIndex() == 1)
    {
      depClear = getSelectedDeposits();
    }

  vector<Check>::iterator current;

  for(current = toClear.begin(); current != toClear.end(); current++)
    {
      dao.setCheckStatus(*current, status);
    }

  vector<Deposit>::iterator curDep;

  for(curDep = depClear.begin(); curDep != depClear.end(); curDep++)
    {
      dao.setDepositStatus(*curDep, Deposit::STATUS(status));
    }

  populateCheckList();
  populateDepositList();
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    getSelectedChecks()
//
// purpose: returns the list of selected checks
//
// calling params:
//
// return params: a STL vector of checks
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

vector<Check> CheckRegister::getSelectedChecks()
{
  vector<Check> selected;

  for(unsigned int i = 0; i < ui->checkTable->numRows(); i++)
    {
      if(ui->checkTable->isRowSelected(i))
        {
          selected.push_back(checkList[i]);
        }
    }

  return selected;
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    getSelectedDeposits()
//
// purpose: gets the list of selected deposits
//
// calling params:
//
// return params: a STL vector of Deposits
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

vector<Deposit> CheckRegister::getSelectedDeposits()
{
  Q3ListViewItemIterator it(ui->listViewDeposits);
  vector<Deposit> selected;
  while(it.current())
    {
      if(it.current()->isSelected())
        {
          selected.push_back(dao.getDepositByNumber(it.current()->text(1).toLong()));
        }
      ++it;
    }

  return selected;
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    populateDepositList()
//
// purpose: loads data in the deposit list from a STL vector of Deposits loaded
//          from the database
//
// calling params:
//
// return params:
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void CheckRegister::populateDepositList()
{
  ui->listViewDeposits->clear();
  depositList = dao.getDepositList();
  string status[3] = {"O", "V", "C"};
  vector<Deposit>::iterator current;

  for(current = depositList.begin(); current != depositList.end(); current++)
    {
      if(current->getStatus() == Deposit::Void && ui->showVoidBox->isChecked() ||
         current->getStatus() == Deposit::Out && ui->showOutBox->isChecked() ||
         current->getStatus() == Deposit::Cleared && ui->showClearBox->isChecked())
        {
          Q3ListViewItem *list = new Q3ListViewItem(ui->listViewDeposits,
                                                    QString::fromStdString(status[current->getStatus()]),
              QString::number(current->getNumber()),
              QString::fromStdString(current->getDate().toString("mm-dd-YYYY")),
              QString::number(current->getAmount(), 'f', 2),
              QString::fromStdString(current->getComment()));

          if(list == NULL)
            {
              cerr << "Error inserting list item" << endl;
            }
        }
    }
  calculateSummary();
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    newDeposit()
//
// purpose: creates a new deposit in the database and starts the deposit edit
//          dialog with this new deposit
//
// calling params:
//
// return params:
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void CheckRegister::newDeposit()
{
  DepositEditDialog depEdit(this);
  depEdit.init(dao.saveDeposit(Deposit()));
  depEdit.exec();
  populateDepositList();
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    editDeposit(QListViewItem *)
//
// purpose: starts the deposit edit dialog with the Deposit represented by
//          *item in the deposit list view
//
// calling params: QListViewItem *item - the list view item representing the
//                                       deposit to be edited
//
// return params:
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void CheckRegister::editDeposit(Q3ListViewItem *item)
{
  DepositEditDialog depEdit(this);
  depEdit.init(dao.getDepositByNumber(item->text(1).toLong()));
  depEdit.exec();
  populateDepositList();
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    calculateSummary()
//
// purpose: displays the summary data in the summary table
//
// calling params:
//
// return params:
//
// Notes: The database engine calculates the totals, so that if only a partial
//        list is loaded, the summary will still be correct
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void CheckRegister::calculateSummary()
{
  double dep, chk;
  double depTotal, chkTotal;

  depTotal = dep = dao.getDepositTotal(Deposit::Cleared);
  chkTotal = chk = dao.getCheckTotal(Check::Cleared);

  ui->tabSummary->setText(0, 0, QString::number(dep, 'f', 2));
  ui->tabSummary->setText(0, 1, QString::number(chk, 'f', 2));
  ui->tabSummary->setText(0, 2, QString::number(dep - chk, 'f', 2));

  depTotal += dep = dao.getDepositTotal(Deposit::Out);
  chkTotal += chk = dao.getCheckTotal(Deposit::Out);

  ui->tabSummary->setText(1, 0, QString::number(dep, 'f', 2));
  ui->tabSummary->setText(1, 1, QString::number(chk, 'f', 2));
  ui->tabSummary->setText(1, 2, QString::number(dep - chk, 'f', 2));

  ui->tabSummary->setText(2, 0, QString::number(depTotal, 'f', 2));
  ui->tabSummary->setText(2, 1, QString::number(chkTotal, 'f', 2));
  ui->tabSummary->setText(2, 2, QString::number(depTotal - chkTotal, 'f', 2));
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    setNextCheckNo()
//
// purpose: sets the next check number in the database from a user defined
//          value
//
// calling params:
//
// return params:
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void CheckRegister::setNextCheckNo()
{
  bool ok = false;
  long checkNum = dao.getNextCheckNo(false);
  long nextNumber = QInputDialog::getInt(this,"Enter next check number",
                                         "Enter the next check number in the sequence",
                                         checkNum ,0,999999999,1,&ok);
  if(ok)
    {
      dao.setNextCheck(nextNumber);
    }
}

void CheckRegister::deleteChecks()
{
  vector<Check> deleteQueue;
  deleteQueue = getSelectedChecks();
  int option = 0;
  for(unsigned int i = 0; i < deleteQueue.size(); i++)
    {

      if(option != 1)
        {
          option = QMessageBox::warning(this, "Warning",
                                        "About to delete check #" + QString::number(deleteQueue[i].getNumber()) + "",
                                        "Ok", "Ok to all", "Cancel");
        }

      switch(option)
        {
        case 0:
        case 1:
          dao.deleteCheck(deleteQueue[i]);
          break;

        case 2:
          return;
        };

    }
  populateCheckList();
}


void CheckRegister::printRegister()
{
  QDate fromQDate = ui->registerFromDate->date();
  QDate toQDate = ui->registerToDate->date();

  Date fromDate = Date(fromQDate.day(), fromQDate.month(), fromQDate.year());
  Date toDate = Date(toQDate.day(), toQDate.month(), toQDate.year());

  QStringList modeMenu;
  modeMenu << "Check And Deposit Register" << "Check Register Only" << "Deposit Register Only" << "Reconciliation Report" << "Text Export Checks" << "Text Export Deposits";
  bool ok;

  QString modeString = QInputDialog::getItem("Report Mode",
                                             "What do you want there to be on the report?",
                                             modeMenu,
                                             0, false, &ok, this);

  bool showReconcile = false;
  bool exportChecks = false;
  bool exportDeposits = false;
  double statementBalance = 0.00001;

  if(ok)
    {
      CheckReport::DisplayMode displayMode;

      if(modeString == modeMenu[0])
        {
          displayMode = CheckReport::CheckAndDeposit;
        }
      else if(modeString == modeMenu[1])
        {
          displayMode = CheckReport::OnlyCheck;
        }
      else if(modeString == modeMenu[2])
        {
          displayMode = CheckReport::OnlyDeposit;
        }
      else if(modeString == modeMenu[3])
        {
          displayMode = CheckReport::CheckAndDeposit;
          showReconcile = true;
          ui->showVoidBox->setChecked(false);
          ui->showOutBox->setChecked(true);
          ui->showClearBox->setChecked(false);

          populateCheckList();
          statementBalance = QInputDialog::getDouble("Statement Balance", "Enter the Statement Balance", 0.00, -2147483647, 2147483647,  2, &ok, this);

          if(!ok)
            {
              return;
            }
        }
      else if(modeString == modeMenu[4]) // Text Export (checks)
        {
          displayMode = CheckReport::OnlyCheck;
          exportChecks = true;
        }
      else if(modeString == modeMenu[5]) // Text Export (deposits)
        {
          displayMode = CheckReport::OnlyDeposit;
          exportDeposits = true;
        }

      CheckReport report(checkList,
                         dao.getDepositList(fromDate, toDate, ui->showVoidBox->isChecked(),
                                            ui->showOutBox->isChecked(),
                                            ui->showClearBox->isChecked()),
                         ui->showClearBox->isChecked(),
                         ui->showVoidBox->isChecked(),
                         ui->showOutBox->isChecked(),
                         displayMode);

      if(showReconcile)
        {
          report.setStatementBalance(statementBalance);
        }

      // [KLN] add/mod
      if ( exportChecks || exportDeposits ) {
          // This is just simple text for Emporia's accountant (she copy/pastes the onscreen preview)
          // Need to set this up to export CSV, just in a hurry to get this to Emporia before end of month!
          //            cout << "chk: " << report.text();
          char* pathname;
          if ( exportChecks ) {
              pathname = "/home/auction/Desktop/Register-Checks.txt";
            } else {
              pathname = "/home/auction/Desktop/Register-Deposits.txt";
            }
          ofstream myfile;
          myfile.open (pathname);
          myfile << report.text();
          myfile.close();
        } else {
          report.setHeader(setup.reportHeader("Check Register", true, "", true));
          PreviewDialog prev;
          prev.setText(QString::fromStdString(report.text()));
          prev.setReport(&report);
          prev.setShowPrint(true);

          prev.exec();
        }
      // [KLN] end
    }
}


void CheckRegister::startCheckPost()
{
  PostCheckDialog(this).exec();
  populateCheckList();
}

void CheckRegister::handleCheckNumberRequest()
{
  setNumberOption();
  populateCheckList();
}
void CheckRegister::setNumberOption()
{
  ui->numberOption->setChecked(true);
}

void CheckRegister::sortCheckListByIndex()
{
  QString keyString = ui->indexCombo->currentText();

  if(keyString == "Date")
    {
      std::sort(checkList.begin(), checkList.end(), Check::compareDatesLT);
    }
  else if(keyString == "Number")
    {
      std::sort(checkList.begin(), checkList.end(), Check::compareNumbersLT);
    }
  else if(keyString == "Payee")
    {
      std::sort(checkList.begin(), checkList.end(), Check::comparePayeesLT);
    }
  else if(keyString == "Amount")
    {
      std::sort(checkList.begin(), checkList.end(), Check::compareAmountsLT);
    }
  else if(keyString == "Status")
    {
      std::sort(checkList.begin(), checkList.end(), Check::compareStatusLT);
    }
}

void CheckRegister::searchChecksByIndex()
{
  ui->checkTable->clearSelection();
  QString keyString = ui->indexCombo->currentText();
  int keyColumn = -1;
  QString pattern = ui->searchEdit->text();

  bool numericSearch;

  double numberPattern = pattern.toDouble(&numericSearch);

  if(keyString == "Date")
    {
      keyColumn = 0;
    }
  else if(keyString == "Number")
    {
      keyColumn = 1;
    }
  else if(keyString == "Payee")
    {
      keyColumn = 2;
    }
  else if(keyString == "Amount")
    {
      keyColumn = 3;
    }
  else if(keyString == "Status")
    {
      keyColumn = 4;
    }

  ui->checkTable->setSelectionMode(Q3Table::SingleRow);
  for(unsigned int i = 0; i < ui->checkTable->numRows() && 0 <= keyColumn; i++)
    {
      if(numericSearch)
        {
          if(ui->checkTable->text(i, keyColumn).toDouble() >= numberPattern)
            {
              ui->checkTable->selectRow(i);
              break;
            }
        }
      else
        {
          if(ui->checkTable->text(i, keyColumn).lower() >= pattern.lower())
            {
              ui->checkTable->selectRow(i);
              break;
            }
        }
    }
  ui->checkTable->setSelectionMode(Q3Table::MultiRow);

}
