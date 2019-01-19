//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add ui->setupUi(this);
//   Add delete ui;
//   delete moc include at end

#include "commissiondialog.h"
#include "ui_commissiondialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <Q3Table>
#include <Q3ListBox>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

CommissionDialog::CommissionDialog( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl ), ui (new Ui::CommissionDialog)
{
  ui->setupUi(this);
    // signals and slots connections
    connect( ui->codeRelLineEdit, SIGNAL( textChanged(const QString&) ), this, SLOT( checkTable(const QString&) ) );
    connect( ui->commResetButt, SIGNAL( clicked() ), this, SLOT( clearForm() ) );
    connect( ui->commissionListBox, SIGNAL( clicked(Q3ListBoxItem*) ), this, SLOT( loadCommission(Q3ListBoxItem*) ) );
    connect( ui->commissionListBox, SIGNAL( doubleClicked(Q3ListBoxItem*) ), this, SLOT( editBreakList(Q3ListBoxItem*) ) );
    connect( ui->commSaveButt, SIGNAL( clicked() ), this, SLOT( saveCommission() ) );
    connect( ui->commDelButt, SIGNAL( clicked() ), this, SLOT( deleteItem() ) );
    connect( ui->colorComboBox, SIGNAL( activated(int) ), this, SLOT( showForm() ) );
    connect( ui->codeTable, SIGNAL( currentChanged(int,int) ), this, SLOT( showDescripAtCoord(int,int) ) );

    // tab order
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CommissionDialog::~CommissionDialog()
{
    delete ui;
}

 
typedef enum {C_SEX, C_FLAW, C_COMM, C_TYPE, C_BREAK, C_BREAK_TYPE} COMMISSION_COLUMNS;

class CommissionGroupItem
{
public:
  string sex;
  vector<string> flawList;
 
  CommissionGroupItem(string sex="", string flaw="")
    {
      this->sex = sex;
      this->flawList.push_back(flaw);
    }
  
  bool operator==(string sex)
    {
      return this->sex == sex;
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
// Notes: sets the table items to be checkboxes
//        
// Todo:  
//
///////////////////////////////////////////////////////////////////////////////

void CommissionDialog::init()
{
  //populateCommissionView();
  populateCommissionListBox();
  
  for(int i = 0; i < 10; i++)
  {
    ui->codeTable->setColumnWidth(i, ui->codeTable->rowHeight(0));
      
    for(int j = 0; j < 10; j++)
    {
      ui->codeTable->setItem(i, j, new Q3CheckTableItem(ui->codeTable, ""));
    }
  }
  blockSignal = false;
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    checkTable(const QString &text)
// 
// purpose: A quick way to fill the columns of the code table
// 
// calling params: const QString &text - a string of digits that represent the 
//                                       columns of the table to completely
//                                       check
// 
// return params:
//
// Notes: 
//        
// Todo:  
//
///////////////////////////////////////////////////////////////////////////////

void CommissionDialog::checkTable(const QString &text)
{
  int col;

  if(!blockSignal)
  {
    for(int i = 0; i < 10; i++)
    {
      checkTableCol(i, false);
    }

    for(unsigned int i = 0; i < text.length(); i++)
    { 
      if(text.at(i).isDigit())
      {
	col = text.at(i).digitValue();
	checkTableCol(col, true);
      }
    }
  }
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    checkTableCol(int, bool)
// 
// purpose: sets all of the check boxes in column 'col' of the table to be
//          checked or unchecked based on the value of 'check'
// 
// calling params: 
// 
// return params:
//
// Notes: check == true => check, check == false => uncheck
//        
// Todo:  
//
///////////////////////////////////////////////////////////////////////////////

void CommissionDialog::checkTableCol(int col, bool check)
{ 
  for(int i = 0; i < 10; i++)
  {
    if(((Q3CheckTableItem*)ui->codeTable->item(i, col))->isEnabled())
    {
      ((Q3CheckTableItem*)ui->codeTable->item(i, col))->setChecked(check);
    }
  }
}


void CommissionDialog::populateCommissionListBox()
{
  CommissionDAO commDao;
  commList = commDao.getCommissionList(CommissionDAO::COLOR_GROUP(ui->colorComboBox->currentItem()));
  vector<Commission>::iterator current;
  
  list<AnimalCode> codeList;
  list<AnimalCode>::iterator currentCode;

  
  short baseColor = 0;
  
  switch(ui->colorComboBox->currentItem())
  {
  case AnimalCode::First:
    baseColor = 0;
    break;
 
  case AnimalCode::Second:
    baseColor  = 70;
    break;
  
  case AnimalCode::Third:
    baseColor = 80;
    break;
 
  case AnimalCode::Fourth:
    baseColor = 90;
    break;
 
  case AnimalCode::Invalid:
    baseColor = 0;
    break;
  }
  
  QStringList codeStringList;
  QString commLabel;
  QStringList commissionStringList;
  
  vector<CommissionGroupItem> groupItemList;
  vector<CommissionGroupItem>::iterator groupItem;
  string descripString;

  for(current = commList.begin(); current != commList.end(); current++)
  {
    descripString = "";
    if(current->getName() == "")
    {
      codeList = commDao.getCodeRelList(current->getId());
      codeStringList.clear();

      groupItemList = vector<CommissionGroupItem>();


      for(currentCode = codeList.begin(); currentCode != codeList.end(); currentCode++)
      {
        currentCode->setColor(baseColor);
        codeDao.fillAnimalCode(*currentCode);

        if(currentCode->getTypeDescrip() == "")
        {
          currentCode->setTypeDescrip(QString::number(currentCode->getType()).toStdString());
        }
  
        if(currentCode->getFlawDescrip() == "")
        {
          currentCode->setFlawDescrip(QString::number(currentCode->getFlaw()).toStdString());
        }
  
        if((groupItem = std::find(groupItemList.begin(), groupItemList.end(), currentCode->getTypeDescrip())) == groupItemList.end())
        {
  	  groupItemList.push_back(CommissionGroupItem(currentCode->getTypeDescrip(), currentCode->getFlawDescrip()));
        }
        else
        {
          groupItem->flawList.push_back(currentCode->getFlawDescrip());
        }
      }
  
      for(unsigned int i = 0; i < groupItemList.size(); i++)
      {
        descripString += groupItemList[i].sex;
        descripString += (i < groupItemList.size() - 1 ? ", " : "");
      }
    }
    else
    {
      descripString = current->getName();
    }
      commissionStringList += QString::fromStdString(descripString);
    
  }
  

  
  ui->commissionListBox->clear();
  ui->commissionListBox->insertStringList(commissionStringList);
}


void CommissionDialog::loadCommission(Q3ListBoxItem* item)
{
  int i = ui->commissionListBox->index(item);

  if(0 <= i || i < commList.size())
  { 
    resetFields();
    ui->calculationMode->setCurrentItem(commList[i].getType());
    ui->breakMode->setCurrentItem(commList[i].getBreakType());
    ui->minEdit->setText(QString::number(commList[i].getMin(), 'f', 2));
    ui->maxEdit->setText(QString::number(commList[i].getMax(), 'f', 2));
    ui->noSaleEdit->setText(QString::number(commList[i].getNoSaleCharge(), 'f', 2));
    loadCodeList(commList[i].getId());
   
    ui->commissionDescriptionEdit->setText(QString::fromStdString(commList[i].getName()));
    

/*     if(commissionDescriptionEdit->text() == "") */
/*     { */
/*       QApplication::flush(); */
/*       string tempDescrip =  */
/* 	QInputDialog::getText("Enter a description", */
/* 			      "There is no description set for this commission. \n" */
/* 			      "A description, such as: 'Fat Cattle' or 'Dairy Cows'\n" */
/* 			      "While not necessary, can make the commission setup\n" */
/* 			      "much easier.", QLineEdit::Normal, "Commission Description"); */
	
/*       commissionDescriptionEdit->setText(tempDescrip); */
				      
/*     } */

  }
}

void CommissionDialog::editBreakList(Q3ListBoxItem* item)
{
  int i = ui->commissionListBox->index(item);
  if(0 <= i || i < commList.size())
  {
    BreakEditDialog breakDialog(this);
    breakDialog.init(commList[i]);
    breakDialog.exec();
    populateCommissionListBox();
    ui->commissionListBox->setSelected(i, true);
  }
}

///////////////////////////////////////////////////////////////////////////////
//
// name:    loadCodeList(long)
// 
// purpose: sets codes associated with the commission commId in the database to 
//          checked
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

void CommissionDialog::loadCodeList(long commId)
{
  CommissionDAO commDao;
  clearCommCodeTable();
  list<AnimalCode> codeList = commDao.getCodeRelList();
  list<AnimalCode>::iterator current;  

  codeList = CommissionDAO().getCodeRelList(commId);

  QString sexList = "";   
  int row, col;
  for(current = codeList.begin(); current != codeList.end(); current++)
  {
    if(current == codeList.begin())
    {
      ui->colorComboBox->setCurrentItem(current->getColor());
    }
  
    if(sexList.indexOf(QString::number(current->getType())) < 1)
    {
      sexList += QString::number(current->getType());
    }

    row = current->getFlaw();
    col = current->getType();
  
    // codeTable->setItem(row, col, (QCheckTableItem*)codeTable->item(row, col));
    ((Q3CheckTableItem*)ui->codeTable->item(row, col))->setChecked(true);
  }
 
  blockSignal = true;  // this is ugly
  ui->codeRelLineEdit->setText(sexList);
  blockSignal = false;
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    createCommission()
// 
// purpose: creates a commission in the database with the initial values set
//          those in the commission fields and combo boxes.
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
//
//void CommissionDialog::createCommission()
//{
//  saveCommission(0);
//}
//

///////////////////////////////////////////////////////////////////////////////
//
// name:    saveCommission()
// 
// purpose: saves the currently selected commission to the database
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

//void CommissionDialog::saveCommission()
//{
//  if(commissionListView->currentItem() == NULL)
//  {  return; }
// 
//  vector<Commission>::iterator current;
//   
//  if(commissionListView->currentItem()->depth() == 0)
//  {
//    current = commList.begin() + commissionListView->currentItem()->text(2).toInt();
//  }
//  else
//  {
//    current = commList.begin() + commissionListView->currentItem()->parent()->text(2).toInt();
//  }
// 
//  saveCommission(current->getId());
//}


///////////////////////////////////////////////////////////////////////////////
//
// name:    save()
// 
// purpose: saves a commission or a break depending on which is selected
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

//void CommissionDialog::save()
//{
//  if(commissionListView->currentItem() == NULL)
//  {
//    cerr << "Tried to save non-existent item" << endl;
//    return;
//  }
// 
//  if(commissionListView->currentItem()->depth() == 0)
//  {
//    saveCommission();
//  }
//  else if(commissionListView->currentItem()->depth() == 1)
//  {
//    saveBreak   ();
//  }
//}



///////////////////////////////////////////////////////////////////////////////
//
// name:    saveCommission()
// 
// purpose: saves the data in the fields in the form as a commission that has 
//          the id 'id'
// 
// calling params: long id - the id of the commission to save
// 
// return params:
//
// Notes: if id == 0 a new commission will be saved
//        
// Todo:  
//
///////////////////////////////////////////////////////////////////////////////

void CommissionDialog::saveCommission()
{
  list<AnimalCode> codeList;
  vector<CommissionBreak> emptyBreakList;
  
  for(int i =0; i < 10; i++)
  {
    for(int j = 0; j < 10; j++)
    {
      if(((Q3CheckTableItem*)ui->codeTable->item(i, j))->isChecked())
      {
	codeList.push_back(AnimalCode(j, 0, i));
      }
    }
  }

    
  if(codeList.size() == 0)
  {
    QMessageBox::information(this, "Warning!", 
			     "Can't save\n"
			     "A commission must be associated with at least one animal code", 
			     QMessageBox::Ok);
    return;
  }
    
  double max = ui->maxEdit->text().toDouble();
    
  if(ui->maxEdit->text().trimmed().isEmpty()) {
        max = 99999.99;
  }
  int index = selectedCommissionIndex();
  
  if(index == -1)
  {
    long commId = CommissionDAO().saveCommission(
      Commission(0, 
		 Commission::TYPE(ui->calculationMode->currentItem()),
		 Commission::BREAK_TYPE(ui->breakMode->currentItem()),
		 emptyBreakList,  ui->minEdit->text().toDouble(), max, ui->noSaleEdit->text().toDouble(), ui->commissionDescriptionEdit->text().toStdString()),
      codeList, CommissionDAO::COLOR_GROUP(ui->colorComboBox->currentItem()));
  }
  else
  {
    commList[index].setType(Commission::TYPE(ui->calculationMode->currentItem()));
    commList[index].setBreakType(Commission::BREAK_TYPE(ui->breakMode->currentItem()));
    commList[index].setMin(ui->minEdit->text().toDouble());
    commList[index].setMax(max);
    commList[index].setNoSaleCharge(ui->noSaleEdit->text().toDouble());
    commList[index].setName(ui->commissionDescriptionEdit->text().toStdString());
    CommissionDAO().saveCommission(commList[index], codeList,
				   CommissionDAO::COLOR_GROUP(ui->colorComboBox->currentItem()));
  }
  
  populateCommissionListBox();
  clearForm();
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    clearCommCodeTable()
// 
// purpose: resets the code table to all unchecked
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

void CommissionDialog::clearCommCodeTable()
{
  CommissionDAO commDao;
  
  list<AnimalCode> codeList = commDao.getCodeRelList();
  list<AnimalCode>::iterator current;
  
  for(int i = 0; i < 10; i++)
  {
    for(int j = 0; j < 10; j++)
    {
      ui->codeTable->item(i, j)->setEnabled(true);  
    }
  }
  
  ui->codeRelLineEdit->setText("");
  int row, col;
  
  for(current = codeList.begin(); current != codeList.end(); current++)
  {
    row = current->getFlaw();
    col = current->getFlaw();
//   codeTable->setItem(row, col, (QTableItem*)codeTable->item(row, col));
  }
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    deleteItem()
// 
// purpose: removes the selected break or commisison from the database
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

void CommissionDialog::deleteItem()
{  
  int index = selectedCommissionIndex();

  if(0 <= index && index < commList.size())
  {
   

    int confirm = QMessageBox::Ok;

    confirm = QMessageBox::warning(this, "Warning",
				   "You are about to remove this commission from the system.\n"
				   "Are you sure that you want to continue?",
				   QMessageBox::Cancel, QMessageBox::Ok);
    if(confirm == QMessageBox::Ok)
    {
      CommissionDAO().deleteCommission(commList[index]);
      clearForm();
      populateCommissionListBox();
    }
    
  }

}

int CommissionDialog::selectedCommissionIndex()
{
  for(unsigned int i = 0; i < ui->commissionListBox->numRows(); i++)
  {
    if(ui->commissionListBox->isSelected(i))
    {
      return i;
    }
  }
  return -1;
}

void CommissionDialog::clearForm()
{
  ui->commissionListBox->clearSelection();
  resetFields();
}

void CommissionDialog::showForm()
{
  clearForm();
  populateCommissionListBox();
}

///////////////////////////////////////////////////////////////////////////////
//
// name:    resetFields()
// 
// purpose: resets the fields of the form to the initial values.
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

void CommissionDialog::resetFields()
{
  ui->calculationMode->setCurrentItem(0);
  ui->breakMode->setCurrentItem(0);
  
  ui->minEdit->setText("");
  ui->maxEdit->setText("99999.99");
  ui->noSaleEdit->setText("");
  ui->commissionDescriptionEdit->setText("");
  clearCommCodeTable();
}

void CommissionDialog::mouseMoveEvent(QMouseEvent* e)
{
  //showDescripAtCoord(e->x() - (codeTable->x() + codeTable->verticalHeader()->width()), e->y() - (codeTable->y() + codeTable->horizontalHeader()->height()));
}

void CommissionDialog::showDescripAtCoord(int x, int y)
{
  short flaw = x;//codeTable->rowAt(y);
  short sex = y;//codeTable->columnAt(x);
  short color;
   
  if(flaw > -1 && sex > -1)
  {
    switch(ui->colorComboBox->currentItem())
    {
    case 0:
      color = 0;
      break;
   
    case 1:
      color = 70;
      break;
     
    case 2:
      color = 80;
      break;
    case 3:
      color = 90;
      break;
    }
  
    AnimalCode tempCode(sex, color, flaw);
    codeDao.fillAnimalCode(tempCode);
   
    ui->messageArea->setText(QString::fromStdString(tempCode.getTypeDescrip() + "-" + tempCode.getFlawDescrip()));
  }
  else
  {
    ui->messageArea->setText("");
  }
}

