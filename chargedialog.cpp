//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add ui->setupUi(this);
//   Add delete ui;
//   delete moc include at end

#include "chargedialog.h"
#include "ui_chargedialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qbuttongroup.h>
#include <qradiobutton.h>
#include <qgroupbox.h>
#include <qcheckbox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <Q3Table>
#include <Q3ListBox>
#include <qcombobox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

ChargeDialog::ChargeDialog( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl ), ui(new Ui::ChargeDialog)
{
    
    ui->setupUi(this);
    // signals and slots connections
    connect( ui->chgSaveButt, SIGNAL( clicked() ), this, SLOT( saveCurrentCharge() ) );
    connect( ui->chgCustType, SIGNAL( clicked(int) ), this, SLOT( populateChargeList() ) );
    connect( ui->chgListBox, SIGNAL( highlighted(int) ), this, SLOT( loadCurrentCharge(int) ) );
    connect( ui->chgNewButt, SIGNAL( clicked() ), this, SLOT( resetCharge() ) );
    connect( ui->chgDelButt, SIGNAL( clicked() ), this, SLOT( deleteCurrentCharge() ) );
    connect( ui->codeRelLineEdit, SIGNAL( textChanged(const QString&) ), this, SLOT( checkColumns(const QString&) ) );
    connect( ui->colorComboBox, SIGNAL( activated(const QString&) ), this, SLOT( populateChargeList() ) );
    connect( ui->moveChargeDownButton, SIGNAL( clicked() ), this, SLOT( moveChargeDown() ) );
    connect( ui->moveChargeUpButton, SIGNAL( clicked() ), this, SLOT( moveChargeUp() ) );

    // tab order
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
ChargeDialog::~ChargeDialog()
{
    delete ui;
}

///////////////////////////////////////////////////////////////////////////////
//
// name:    init()
// 
// purpose: Constructor like function, initializes the dialog
//
// calling params: 
// 
// return params:
//
// Notes: sets up the code table as a grid of checkboxes and populates the 
//        charge list
//        
// Todo:  
//
///////////////////////////////////////////////////////////////////////////////

void ChargeDialog::init()
{
    for(int i =0; i < 10; i++)
    {
        ui->codeTable->setColumnWidth(i, ui->codeTable->rowHeight(0));

        for(int j = 0; j < 10; j++)
        {
            ui->codeTable->setItem(i, j, new Q3CheckTableItem(ui->codeTable, ""));
        }
    }

    populateChargeList();
    saveNew = true;
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    populateChargeList()
// 
// purpose: displays the list of charges by retrieving the charge list for the
//          object from the database, iterating through that list and displaying charge 
//          information for each item
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

void ChargeDialog::populateChargeList()
{
    resetCharge();
    ui->chgListBox->clear();
    chargeList = chargeDao.getChargeList(ChargeDAO::CUST_TYPE(ui->chgCustType->selectedId()),
                                         CommissionDAO::COLOR_GROUP(ui->colorComboBox->currentItem()));

    vector<Charge> manualList = chargeDao.getManualChargeList(CommissionDAO::COLOR_GROUP(ui->colorComboBox->currentItem()),
                                                              ChargeDAO::CUST_TYPE(ui->chgCustType->selectedId()));
    chargeList.insert(chargeList.end(), manualList.begin(), manualList.end());
    QStringList chargeStringList;

    vector<Charge>::iterator current;
    std::sort(chargeList.begin(), chargeList.end(), Charge::compareIdsLT);
    for(current = chargeList.begin(); current != chargeList.end(); current++)
    {
        chargeStringList += QString::fromStdString(current->getDescrip()) + ", " + QString::fromStdString(current->getExpression());
    }

    ui->chgListBox->insertStringList(chargeStringList);
}


///////////////////////////////////////////////////////////////////////////////
//
// name: moveChargeUp()
// 
// purpose: swaps the charge ids of 2 adjacent charge ids in the charge table.
//          in such a way that the current charge id will be less than 
//          the item swapped. This in effect will sort the charges on the 
//          invoice and in the summary
//
// calling params: void
// 
// return params: void
//
// Notes: 
//        
// Todo: 
//
///////////////////////////////////////////////////////////////////////////////
void ChargeDialog::moveChargeUp()
{
    int index = getSelectedChargeIndex();

    if(index < chargeList.size() && index > 0)
    {
        list<AnimalCode> list1 = chargeDao.getCodeList(chargeList[index]);
        list<AnimalCode> list2 = chargeDao.getCodeList(chargeList[index - 1]);
        long tempId = chargeList[index].getId();
        chargeList[index].setId(chargeList[index - 1].getId());
        chargeList[index - 1].setId(tempId);
        
        chargeDao.saveCharge(chargeList[index], ChargeDAO::CUST_TYPE(ui->chgCustType->selectedId()),list1);
        chargeDao.saveCharge(chargeList[index - 1], ChargeDAO::CUST_TYPE(ui->chgCustType->selectedId()),list2);
        chargeDao.swapChargeAdjustmentIds(chargeList[index], chargeList[index - 1]);
        chargeDao.swapChargeBreakIds(chargeList[index], chargeList[index - 1]);
        populateChargeList();
        ui->chgListBox->setSelected(index - 1, true);
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// name: moveChargeDown()
// 
// purpose: swaps the charge ids of 2 adjacent charge ids in the charge table.
//          in such a way that the current charge id will be greater than 
//          the item swapped. This in effect will sort the charges on the 
//          invoice and in the summary
//
// calling params: void
// 
// return params: void
//
// Notes: 
//        
// Todo: 
//
///////////////////////////////////////////////////////////////////////////////
void ChargeDialog::moveChargeDown()
{
    int index = getSelectedChargeIndex();

    if(index < chargeList.size() - 1 && index >= 0)
    {
        list<AnimalCode> list1 = chargeDao.getCodeList(chargeList[index]);
        list<AnimalCode> list2 = chargeDao.getCodeList(chargeList[index + 1]);
        long tempId = chargeList[index].getId();
        chargeList[index].setId(chargeList[index + 1].getId());
        chargeList[index +1].setId(tempId);
        
        chargeDao.saveCharge(chargeList[index], ChargeDAO::CUST_TYPE(ui->chgCustType->selectedId()),list1);
        chargeDao.saveCharge(chargeList[index + 1], ChargeDAO::CUST_TYPE(ui->chgCustType->selectedId()),list2);
        chargeDao.swapChargeAdjustmentIds(chargeList[index], chargeList[index + 1]);
        chargeDao.swapChargeBreakIds(chargeList[index], chargeList[index + 1]);
        populateChargeList();
        ui->chgListBox->setSelected(index + 1, true);
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// name: getSelectedChargeIndex()
//
// purpose: returns the index of the charge that is selected in the charge list
//
// calling params: void
// 
// return params: void
//
// Notes: 
//        
// Todo: 
//
///////////////////////////////////////////////////////////////////////////////

int ChargeDialog::getSelectedChargeIndex()
{
    for(unsigned int i = 0; i < ui->chgListBox->numRows(); i++)
    {
        if(ui->chgListBox->isSelected(i))
        {
            return i;
        }
    }
    return -1;
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    saveCurrentCharge()
// 
// purpose: Commits changes made to the current charge to the database
//
// calling params: 
// 
// return params:
//
// Notes: uses the saveNew flag to determine if the charge should be saved as 
//        a new charge
//        
// Todo:  
//
///////////////////////////////////////////////////////////////////////////////
void ChargeDialog::saveCurrentCharge()
{
    long id;
    QString descrip, expression;
    bool chargeOnNoSale, chargeOnReSale, doubleOnPairs, needsMultiplier;

    descrip = ui->chgEditName->text();
    expression = ui->chgEditAmt->text();
    chargeOnNoSale = ui->chgNoSale->isChecked();
    chargeOnReSale = ui->chgReSale->isChecked();
    doubleOnPairs = ui->chgPairs->isChecked();
    needsMultiplier = ui->chgMult->isChecked();
    bool beefCouncil  = ui->isBeefCouncil->isChecked();
    ChargeDAO::CUST_TYPE chargeCustomer = ChargeDAO::CUST_TYPE(ui->chgCustType->selectedId());
    int currentRow = ui->chgListBox->currentItem();

    vector<ChargeBreak> breakList;

    for(int i = 0; i < ui->breakTable->numRows(); i++)
    {
        if(ui->breakTable->text(i, 0) != "")
        {
            breakList.push_back(ChargeBreak(0, ui->breakTable->text(i, 1).toDouble(),ui->breakTable->text(i, 0).toStdString()));
        }
    }

    if(saveNew)
    {
        id = 0;
    }
    else
    {
        vector<Charge>::iterator current = chargeList.begin() + currentRow;
        id = current->getId();
    }
    list<AnimalCode> codeList = getAnimalCodeList();
    if(codeList.size() < 1)
    {
        QMessageBox::information(this, "Warning!",
                                 "Can't save.\n"
                                 "A Charge must be associated with at least one animal code",
                                 QMessageBox::Ok);
        return;
    }

    Charge charge(id, descrip.toStdString(), expression.toStdString(), chargeOnNoSale, chargeOnReSale,
                  doubleOnPairs, needsMultiplier, ui->chgComm->isChecked(), beefCouncil);
    charge.setBreakList(breakList);
    charge.setBreakType(ChargeBreak::Type(ui->breakTypeCombo->currentItem()));
    charge.setScope(Charge::Scope(ui->scopeCombo->currentItem()));
    ChargeDAO().saveCharge(charge, chargeCustomer, codeList);

    populateChargeList();
}



///////////////////////////////////////////////////////////////////////////////
//
// name:    getAnimalCodeList()
// 
// purpose: gets the list of AnimalCodes from the code table
//
// calling params: 
// 
// return params: A STL list of animal codes
//
// Notes:
//        
// Todo:  
//
///////////////////////////////////////////////////////////////////////////////
list<AnimalCode> ChargeDialog::getAnimalCodeList()
{
    list<AnimalCode> codeList;

    for(int i = 0; i < 10; i++)
    {
        for(int j = 0;j < 10; j++)
        {
            if(((Q3CheckTableItem*)ui->codeTable->item(i, j))->isChecked())
            {
                codeList.push_back(AnimalCode(j,ui->colorComboBox->currentItem(),i));
            }
        }
    }
    return codeList;
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    loadCurrentCharge(int)
// 
// purpose: loads the charge at row 'currentRow' into the fields of the dialog
//
// calling params: int currentRow  - the row to load the charge from in the 
//                                   charge list
// 
// return params:
//
// Notes:
//        
// Todo:  
//
///////////////////////////////////////////////////////////////////////////////

void ChargeDialog::loadCurrentCharge(int currentRow)
{
    if(0 <= currentRow && currentRow < int(chargeList.size()))
    {
        saveNew = false;
        vector<Charge>::iterator current = chargeList.begin() + currentRow;
        ui->chgEditName->setText(QString::fromStdString(current->getDescrip()));
        ui->chgEditAmt->setText(QString::fromStdString(current->getExpression()));
        ui->chgNoSale->setChecked(current->chargesOnNoSale());
        ui->chgReSale->setChecked(current->chargesOnReSale());
        ui->chgPairs->setChecked(current->doublesOnPairs());
        ui->chgMult->setChecked(current->needsMultiplier());
        ui->chgComm->setChecked(current->isCommissionCharge());
        ui->isBeefCouncil->setChecked(current->isBeefCouncil());
        loadCodeTable(*current);
        ui->breakTypeCombo->setCurrentItem(current->getBreakType());
        ui->scopeCombo->setCurrentItem(current->getScope());
        vector<ChargeBreak> breakList = current->getBreakList();

        for(unsigned int i = 0; i < ui->breakTable->numRows(); i++)
        {
            ui->breakTable->setText(i, 0, "");
            ui->breakTable->setText(i, 1, "");
        }

        for(unsigned int i = 0; i < breakList.size(); i++)
        {
            if(i < ui->breakTable->numRows())
            {
                ui->breakTable->setText(i, 0, QString::fromStdString(breakList[i].getExpression()));
                ui->breakTable->setText(i, 1, QString::number(breakList[i].getAmount(), 'f', 2));
            }
        }
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    resetCharge()
// 
// purpose: clears all of the fields of dialog
//
// calling params: 
// 
// return params:
//
// Notes: sets the saveNew flag as true so that unless another slot changes
//        the status, the save button will cause a new charge to be entered
//        in the database
//        
// Todo:  
//
///////////////////////////////////////////////////////////////////////////////

void ChargeDialog::resetCharge()
{
    saveNew = true;
    ui->chgEditName->setText("");
    ui->chgEditAmt->setText("");
    ui->chgNoSale->setChecked(false);
    ui->chgReSale->setChecked(false);
    ui->chgPairs->setChecked(false);
    ui->chgComm->setChecked(false);
    ui->chgMult->setChecked(false);
    ui->isBeefCouncil->setChecked(false);
    ui->chgListBox->clearSelection();

    ui->breakTypeCombo->setCurrentItem(ChargeBreak::None);
    ui->scopeCombo->setCurrentItem(Charge::Transaction);
    for(unsigned int i = 0; i < ui->breakTable->numRows(); i++)
    {
        ui->breakTable->setText(i, 0, "");
        ui->breakTable->setText(i, 1, "");
    }

    clearCodeTable();
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    clearCodeTable()
// 
// purpose: unchecks all of the checkboxes in the code table
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

void ChargeDialog::clearCodeTable()
{
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            ((Q3CheckTableItem*)ui->codeTable->item(i,j))->setChecked(false);
        }
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    checkCodeTableColumn(int, bool)
// 
// purpose: checks or unchecks all of the checkboxes in column 'col' of the 
//          code table based on the value of 'check'
//
// calling params: 
// 
// return params:
//
// Notes: if 'check' is true the checkBoxes will be checked, if 'check' is 
//        false then the checkBoxes will be unchecked
//        
// Todo:  
//
///////////////////////////////////////////////////////////////////////////////

void ChargeDialog::checkCodeTableColumn(int col, bool check)
{
    for(int i = 0; i < 10; i++)
    {
        ((Q3CheckTableItem*)ui->codeTable->item(i,col))->setChecked(check);
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    deleteCurrentCharg()
// 
// purpose: removes the charge represented by the current item in the list from
//          the database
//
// calling params: 
// 
// return params:
//
// Notes: reloads the charge list upon completion
//        
// Todo:  
//
///////////////////////////////////////////////////////////////////////////////

void ChargeDialog::deleteCurrentCharge()
{
    int currentItem = ui->chgListBox->currentItem();

    if(currentItem < 0 || currentItem > int(chargeList.size()) - 1)
    { return;}

    int confirm = QMessageBox::warning(this, "Warning",
                                       "This will remove the charge from the system permanantly.\n"
                                       "Are you sure that you want to continue?",
                                       QMessageBox::Cancel,  QMessageBox::Ok);

    if(confirm == QMessageBox::Ok)
    {
        vector<Charge>::iterator current = chargeList.begin() + currentItem;
        ChargeDAO().deleteCharge(*current);
        populateChargeList();
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    loadCodeTable(Charge)
// 
// purpose: Sets the check boxes in the code table to checked or unchecked
//          based on whether they are associatied with the Charge 'charge' 
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

void ChargeDialog::loadCodeTable(Charge charge)
{
    list<AnimalCode> codeList = ChargeDAO().getCodeList(charge);
    list<AnimalCode>::iterator current;
    clearCodeTable();
    for(current = codeList.begin(); current != codeList.end(); current++)
    {
        if(current == codeList.begin())
        {
            ui->colorComboBox->setCurrentItem(current->getColor());
        }

        ((Q3CheckTableItem*)ui->codeTable->item(current->getFlaw(), current->getType()))->setChecked(true);
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    checkColumns(const QString &text)
// 
// purpose: gets the integer values of each charachter in the string text and
//          sets all of the checkboxes in those columns to being checked
//
// calling params: const QString &text  - a string of digit characters to set
//                                        the columns of the code table to 
//                                        checked
// 
// return params:
//
// Notes:
//        
// Todo:  
//
///////////////////////////////////////////////////////////////////////////////

void ChargeDialog::checkColumns(const QString &text)
{
    int col;

    for(int i = 0; i < 10; i++)
    {
        checkCodeTableColumn(i, false);
    }

    for(unsigned int i = 0; i < text.length(); i++)
    {
        if(text.at(i).isDigit())
        {
            col = text.at(i).digitValue();
            checkCodeTableColumn(col, true);
        }
    }
}
