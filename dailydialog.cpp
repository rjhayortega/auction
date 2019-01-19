//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add ui->setupUi(this);
//   Add delete ui;
//   delete moc include at end

#include <QKeyEvent>


#include "dailydialog.h"
#include "ui_dailydialog.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qbuttongroup.h>
#include <qradiobutton.h>
#include <qcheckbox.h>
#include <qpushbutton.h>
#include <qcombobox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>


// from the old ui.h file
#include "vetdialog.h"
#include "dao/customerdao.h"
#include "types/customer.h"
#include "chargeadjustmentdialog.h"
#include "dao/invoicedao.h"
#include "truckingdialog.h"
#include "tageditdialog.h"
#include "reports/customerreport.h"
#include "reports/checkinreport.h"
#include "previewdialog.h"
#include "dao/chargedao.h"
#include <qinputdialog.h>
#include <qmessagebox.h>
#include "zipcodedialog.h"
#include "dao/zipcodedao.h"
#include "lineprinter.h"
#include <QDebug>






DailyDialog::DailyDialog( QWidget* parent )
    : QDialog( parent), ui(new Ui::DailyDialog)
{
    qDebug() << "DailyDialog::DailyDialog()";
    ui->setupUi(this);
    //Associate id's with radiobuttons.
    ui->customerTypeButtonGroup->setId(ui->sellerButton, Customer::Seller);
    ui->customerTypeButtonGroup->setId(ui->buyerButton,  Customer::Buyer);

    // signals and slots connections
    connect( ui->customerTypeButtonGroup, SIGNAL( buttonClicked(int) ), this, SLOT( changeDialogMode(int) ) );
    connect( ui->dailyAddress1, SIGNAL( returnPressed() ), ui->dailyHead, SLOT( setFocus() ) );
    connect( ui->dailyAddress2, SIGNAL( returnPressed() ), ui->dailyHead, SLOT( setFocus() ) );
    connect( ui->dailyCharges, SIGNAL( clicked() ), this, SLOT( startChargeAdjustment() ) );
    connect( ui->dailyCity, SIGNAL( lostFocus() ), this, SLOT( loadCityStateZipFromCity() ) );
    connect( ui->dailyComment, SIGNAL( returnPressed() ), ui->dailyHead, SLOT( setFocus() ) );
    connect( ui->dailyHead, SIGNAL( returnPressed() ), ui->dailySave, SLOT( setFocus() ) );
    connect( ui->dailyID, SIGNAL( returnPressed() ), ui->dailyName, SLOT( setFocus() ) );
    connect( ui->dailyID, SIGNAL( textChanged(const QString&) ), this, SLOT( resetDaily() ) );
    connect( ui->dailyID, SIGNAL( lostFocus() ), this, SLOT( searchListByNumber() ) );
    connect( ui->dailyListBox, SIGNAL( highlighted(int) ), this, SLOT( loadItemFromList(int) ) );
    connect( ui->dailyListBox, SIGNAL( selected(int) ), this, SLOT( loadItemFromList(int) ) );
    connect( ui->dailyMortgage, SIGNAL( returnPressed() ), ui->dailyHead, SLOT( setFocus() ) );
    connect( ui->dailyName, SIGNAL( textChanged(const QString&) ), this, SLOT( findNearest(const QString&) ) );
    connect( ui->dailyName, SIGNAL( returnPressed() ), this, SLOT( autoLoadPerm() ) );
    connect( ui->dailyName, SIGNAL( lostFocus() ), this, SLOT( mergeDaily() ) );
    connect( ui->dailyPermListBox, SIGNAL( highlighted(int) ), this, SLOT( loadDailyFromPerm(int) ) );
    connect( ui->dailyPermListBox, SIGNAL( selected(int) ), this, SLOT( loadDailyFromPerm(int) ) );
    connect( ui->dailySave, SIGNAL( clicked() ), this, SLOT( saveDaily() ) );
    connect( ui->dailyState, SIGNAL( returnPressed() ), ui->dailyHead, SLOT( setFocus() ) );
    connect( ui->dailyTrucking, SIGNAL( clicked() ), this, SLOT( startTrucking() ) );
    connect( ui->dailyZip, SIGNAL( returnPressed() ), this, SLOT( loadCityStateZipFromZip() ) );
    connect( ui->deleteDaily, SIGNAL( clicked() ), this, SLOT( removeCurrentDaily() ) );
    connect( ui->letterComboBox, SIGNAL( activated(const QString&) ), this, SLOT( populatePermList() ) );
    connect( ui->printDailyButton, SIGNAL( clicked() ), this, SLOT( showDailyReport() ) );
    connect( ui->resetRecordButton, SIGNAL( clicked() ), this, SLOT( resetDaily() ) );
    connect( ui->sortGroup, SIGNAL( clicked(int) ), this, SLOT( populateDailyList() ) );
    connect( ui->tagButtonDaily, SIGNAL( clicked() ), this, SLOT( startTagEdit() ) );
    connect( ui->vetButton, SIGNAL( clicked() ), this, SLOT( startVet() ) );
    connect( ui->descrCode, SIGNAL( returnPressed() ), this, SLOT( displayAnimalCodeDescr() ) );
    connect( ui->showMissingBuyersButton, SIGNAL( clicked() ), this, SLOT( showMissingBuyers() ) );

    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
DailyDialog::~DailyDialog()
{
    qDebug() << "DailyDialog::~DailyDialog()";
    delete ui;
}

///////////////////////////////////////////////////////////////////////////////
//
// name:    init()
//
// purpose: constructor like class
//
// calling params:
//
// return params:
//
// Notes: Defaults to being a SELLER dialog
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void DailyDialog::init()
{
    qDebug() << "DailyDialog::init()";
    if(sale.currentSaleOpen())
    {
        ui->dailySave->setEnabled(true);
        ui->deleteDaily->setEnabled(true);
        ui->dailyCharges->setEnabled(true);
        ui->dailyTrucking->setEnabled(true);
        ui->tagButtonDaily->setEnabled(true);
    }
    else
    {
        ui->dailySave->setEnabled(false);
        ui->deleteDaily->setEnabled(false);
        ui->dailyCharges->setEnabled(false);
        ui->dailyTrucking->setEnabled(false);
        ui->tagButtonDaily->setEnabled(false);
    }

    QStringList filterList;
    filterList << "A"<<"B"<<"C"<<"D"<<"E"<<"F"<<"G"<<"H"<<"I"<<"J"<<"K"<<"L"<<"M"<<"N"
               << "O"<<"P"<<"Q"<<"R"<<"S"<<"T"<<"U"<<"V"<<"W"<<"X"<<"Y"<<"Z"<<"Other"<<"All";
    ui->letterComboBox->insertStringList(filterList);

    customerType = Customer::Seller;
    customerId = 0;
    blockLoad = false;
    blockInit = false;

    rfIdTagsOn = bool(atoi(setup.get("rfIdTagsOn").c_str()));
    timerId = 0;


    if(rfIdTagsOn)
    {
        rfTagPort = SerialPort(setup.get("rfIdTagsPort"), 9600, 8, SerialPort::None, 1);
        rfTagPort.setReadWait(0, 100);
        rfTagPort.openPort();
        timerId = startTimer(1000);
    }
    else
    {
        ui->rfTagListBox->hide();
    }

    ui->sellerButton->setChecked(true);
//    changeDialogMode(Customer::Seller);
}

void DailyDialog::destroy()
{
    qDebug() << "DailyDialog::destroy()";
    if(timerId != 0)
    {
        killTimer(timerId);
    }

    if(customerType == Customer::Seller)
    {
        ui->madCowCheckBox->hide();
    }
    else
    {
        ui->madCowCheckBox->show();
    }
}

void DailyDialog::timerEvent(QTimerEvent* e)
{
    if(e->timerId() == timerId)
    {
        string data = rfTagPort.receive('\n');
        rfTagPort.clear();

        if(data.length() > 0)
        {
            radioTagList.push_back(RadioTag(0, data));
            ui->rfTagListBox->insertItem(QString::fromStdString(data));
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
//
// name:    polish()
//
// purpose: auto called after object creation but before display
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

void DailyDialog::polish()
{
    qDebug() << "DailyDialog::polish()";
    populateDailyList();
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    populateDailyList()
//
// purpose: fills the daily list box from the database
//
// calling params:
//
// return params:
//
// Notes: method maintains a STL vector of Sellers or Buyers based on the type
//        of customer the dialog is meant tor represent
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void DailyDialog::populateDailyList()
{
    qDebug() << "DailyDialog::populateDailyList()";
    populateDailyList("");
}

void DailyDialog::populateDailyList(QString selectNumber)
{
    qDebug() << "DailyDialog::populateDailyList() .Number is: " <<  selectNumber;
    ui->dailyListBox->clear();
    QStringList stringList;
    int selectIndex = -1;
    switch(customerType)
    {
    case Customer::Seller:
    default:
        sellerList = SellerDAO::getCustomerList();
        if(ui->numberSortRadio->isChecked())
        {
            std::sort(sellerList.begin(), sellerList.end(), Customer::compareCustomerNumbers);
        }
        else
        {
            std::sort(sellerList.begin(), sellerList.end(), Customer::compareCustomerNames);
        }
        for(currentSeller = sellerList.begin(); currentSeller != sellerList.end(); currentSeller++)
        {
            if(selectNumber != "" && !Customer::compareCustomerNumbersLT(selectNumber.toStdString(), currentSeller->getNumber()))
            {
                selectIndex = stringList.size();
            }

            stringList += QString(QString::fromStdString(currentSeller->toString())).leftJustify(25, ' ', true) + " #" + QString::fromStdString(currentSeller->getNumber());
        }
        break;

    case Customer::Buyer:
        buyerList = BuyerDAO::getCustomerList();

        if(ui->numberSortRadio->isChecked())
        {
            std::sort(buyerList.begin(), buyerList.end(), Customer::compareCustomerNumbers);
        }
        else
        {
            std::sort(buyerList.begin(), buyerList.end(), Customer::compareCustomerNames);
        }

        for(currentBuyer = buyerList.begin(); currentBuyer != buyerList.end(); currentBuyer++)
        {
            if(selectNumber != "" && !Customer::compareCustomerNumbersLT(selectNumber.toStdString(), currentBuyer->getNumber()))
            {
                selectIndex = stringList.size();
            }

            stringList += QString(QString::fromStdString(currentBuyer->toString())).leftJustify(25, ' ', true) + " #" + QString::fromStdString(currentBuyer->getNumber());
        }
        break;
    }


    ui->dailyListBox->insertStringList(stringList);

    if(selectNumber != "" && selectIndex < 0)
    {
        selectIndex = stringList.size() - 1;
    }

    if(0 <= selectIndex && selectIndex < stringList.size())
    {
        blockLoad = true;
        ui->dailyListBox->setCurrentItem(selectIndex);
        blockLoad = false;
    }

    currentBuyer = buyerList.end();
    currentSeller = sellerList.end();
    customerId = 0;
    lastSelected = -1;
    populatePermList();
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    loadItemFromList(int)
//
// purpose: loads an item from the object's STL vector of Sellers or Buyers
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

void DailyDialog::loadItemFromList(int index)
{
    qDebug() << "DailyDialog::loadItemFromList() .Index is: " <<  index;
    if(blockLoad)
    {
         qDebug() << "DailyDialog::loadItemFromList() .BlockLoad true, exiting. ";
        return;
    }

    lastSelected = index;

    bool isSeller = (customerType == Customer::Seller ? true : false);
    if(!(0 <= index && index < (isSeller ? sellerList.size() : buyerList.size())))
    {
        return;
    }

    ui->dailyID->setText((isSeller ? QString::fromStdString(sellerList[index].getNumber()) : QString::fromStdString(buyerList[index].getNumber())));

    ui->dailyHead->setText(QString::number((isSeller ? sellerList[index].getHead() : buyerList[index].getHead())));
    ui->dailyMortgage->setText((isSeller ? QString::fromStdString(sellerList[index].getCompany()) : QString::fromStdString(buyerList[index].getCompany())));

    ui->dailyName->setText((isSeller ? QString::fromStdString(sellerList[index].getName().getLast()) : QString::fromStdString(buyerList[index].getName().getLast())));
    Address address =(isSeller ? sellerList[index].getAddress() : buyerList[index].getAddress());
    ui->dailyAddress1->setText(QString::fromStdString(address.getAddress1()));
    ui->dailyAddress2->setText(QString::fromStdString(address.getAddress2()));
    ui->dailyCity->setText(QString::fromStdString(address.getCity()));
    ui->dailyState->setText(QString::fromStdString(address.getState()));
    ui->dailyZip->setText(QString::fromStdString(address.getZip()));
    ui->dailyComment->setText((isSeller ? QString::fromStdString(sellerList[index].getComment()) : QString::fromStdString(buyerList[index].getComment())));
    customerId = (isSeller ? sellerList[index].getId() : buyerList[index].getId());
    if(isSeller)
    {
        ui->dailyBeefCouncil->setChecked(sellerList[index].isBeefCouncil());
        ui->madCowCheckBox->setChecked(sellerList[index].isMadCowCertified());
    }

    if(rfIdTagsOn && isSeller)
    {
        RadioTagDAO radioTagDao;
        radioTagList = radioTagDao.getSellerRadioTagList(sellerList[index]);
        QStringList rtStringList;

        for(unsigned int i = 0; i < radioTagList.size(); i++)
        {
            rtStringList += QString::fromStdString(radioTagList[i].getNumber());
        }

        ui->rfTagListBox->clear();
        ui->rfTagListBox->insertStringList(rtStringList);
    }
}

///////////////////////////////////////////////////////////////////////////////
//
// name:    loadItemFromList(int)
//
// purpose: loads an item from the object's STL vector of Sellers or Buyers
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

void DailyDialog::showDaily(Customer customer, bool loadNumber)
{
    qDebug() << "DailyDialog::showDaily() .loadNumber is: " <<  loadNumber;
    if(loadNumber)
    {
        ui->dailyID->setText(QString::fromStdString(customer.getNumber()));
    }

    ui->dailyHead->setText(QString::number(customer.getHead()));
    ui->dailyMortgage->setText(QString::fromStdString(customer.getCompany()));

    ui->dailyName->setText(QString::fromStdString(customer.getName().getLast()));
    Address address =customer.getAddress();
    ui->dailyAddress1->setText(QString::fromStdString(address.getAddress1()));
    ui->dailyAddress2->setText(QString::fromStdString(address.getAddress2()));
    ui->dailyCity->setText(QString::fromStdString(address.getCity()));
    ui->dailyState->setText(QString::fromStdString(address.getState()));
    ui->dailyZip->setText(QString::fromStdString(address.getZip()));
    ui->dailyComment->setText(QString::fromStdString(customer.getComment()));
    customerId = customer.getId();

    if(customerType == Customer::Seller)
    {
        ui->dailyBeefCouncil->setChecked(customer.isBeefCouncil());
    }

    //cout << "testing mad cow" << endl;
    ui->madCowCheckBox->setChecked(customer.isMadCowCertified());

    if(rfIdTagsOn && customerType == Customer::Seller)
    {
        RadioTagDAO radioTagDao;
        radioTagList = radioTagDao.getSellerRadioTagList((Seller)customer);
        QStringList rtStringList;

        for(unsigned int i = 0; i < radioTagList.size(); i++)
        {
            rtStringList += QString::fromStdString(radioTagList[i].getNumber());
        }

        ui->rfTagListBox->clear();
        ui->rfTagListBox->insertStringList(rtStringList);
    }
}
///////////////////////////////////////////////////////////////////////////////
//
// name:   saveDaily()
//
// purpose: saves the current daily record to the database
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

void DailyDialog::saveDaily()
{
    qDebug() << "DailyDialog::saveDaily()";
    Seller seller;
    Buyer buyer;

    long head;
    long id;
    string mortgage = ui->dailyMortgage->text().toStdString();
    string company = ui->dailyMortgage->text().toStdString();
    string number = ui->dailyID->text().toStdString();
    string name = ui->dailyName->text().toStdString();
    string address1 = ui->dailyAddress1->text().toStdString();
    string address2 = ui->dailyAddress2->text().toStdString();
    string city = ui->dailyCity->text().toStdString();
    string state = ui->dailyState->text().toStdString();
    string zip = ui->dailyZip->text().toStdString();
    string comment = ui->dailyComment->text().toStdString();
    bool madCow = ui->madCowCheckBox->isChecked();
    unsigned int listSize = (customerType == Customer::Seller ? sellerList.size() : buyerList.size());

    if(customerId == 0 && lastSelected >= 0 && lastSelected < listSize)
    {
        customerId = (customerType == Customer::Seller ? sellerList[lastSelected].getId() : buyerList[lastSelected].getId());
    }

    if(customerType == Customer::Buyer)
    {
        Customer existingPerm = CustomerDAO::loadFromPermNumber(number);

        if(existingPerm.getId() != 0 && existingPerm.getId() != customerId)
        {
            /*
              int opt = QMessageBox::question(this, "Warning",
              "This number is not transient and has already been used for another customer.\n"
              "What do you wish to do?", "Cancel", "Save Anyway");

              if(opt == 0)
              {
              return;
              }
            */
        }
    }

    bool savedOk = true;
    switch(customerType)
    {
    case Customer::Seller:
        head = ui->dailyHead->text().toLong();
        seller = Seller(customerId, Name(name),
                        Address(address1, address2, city, state, zip),
                        ContactList(), number, mortgage, Date(), head);
        seller.setComment(comment);
        seller.setBeefCouncil(ui->dailyBeefCouncil->isChecked());
        seller = Seller(DailyDialog::checkPayeeLength(seller, this), head);
        seller.setMadCowCertified(madCow);
        savedOk = SellerDAO::saveCustomer(seller);
//    SellerDAO::updateParentCountryOfOrigin(seller);
        if(rfIdTagsOn)
        {
            RadioTagDAO radioTagDao;
            for(unsigned int i = 0; i < radioTagList.size(); i++)
            {
                radioTagList[i].setSellerNumber(seller.getNumber());
                radioTagDao.saveRadioTag(radioTagList[i]);
            }
        }

        // print the checkin ticket if that is enabled and savedOk is true
        //   and the initials field is not empty
        if ( savedOk && setup.getBoolean("dailyFMCheckinTickets") &&
                ui->opInitials->text().stripWhiteSpace().length() != 0 )
        {
            PrinterDAO pdao;
            PrinterBase* printer = pdao.getPrinter(PrinterDAO::CheckIn);
            PrinterBase* officePrinter = pdao.getPrinter(PrinterDAO::CheckInOffice);
            CheckinReport ckinreport(
                ui->dailyHead->text().toInt(),
                ui->dailyID->text().toStdString(),
                ui->dailyName->text().toStdString(),
                ui->dailyAddress1->text().toStdString(),
                ui->dailyAddress2->text().toStdString(),
                ui->dailyCity->text().toStdString() + " " + ui->dailyState->text().toStdString() + " " + ui->dailyZip->text().toStdString(),
                std::string(setup.get("genMktName") + "  " + setup.get("genMktCity") + ", " + setup.get("genMktState")),
                sale.currentSaleDateSQLString(),
                "", //string trucker"
                ui->opInitials->text().toStdString(),
                ui->descriptionLabel->text().toStdString(),
                ui->dailyComment->text().toStdString()
            );

            // Print checkin ticket twice, and then once more in office.
            // yes, do it twice.
            printer->print( ckinreport.reportText(),QTextDocument(), LinePrinter::Normal, true);
            printer->print( ckinreport.reportText(),QTextDocument(), LinePrinter::Normal, true);
            officePrinter->print( ckinreport.reportText(),QTextDocument(), LinePrinter::Normal, true);
            // ********************************************

            delete printer;
            delete officePrinter;
        }


        break;

    case Customer::Buyer:
        buyer = Buyer(customerId, Name(name),
                      Address(address1, address2, city, state, zip),
                      ContactList(), number, company);
        buyer.setComment(comment);
        savedOk = BuyerDAO::saveCustomer(buyer);

        break;
    }

    populateDailyList(QString::fromStdString(number));
    clearDaily();
}

///////////////////////////////////////////////////////////////////////////////
//
// name:    removeCurrentDaily()
//
// purpose: deletes the current daily record from the database
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

void DailyDialog::removeCurrentDaily()
{
    qDebug() << "DailyDialog::removeCurrentDaily()";
    vector <Seller>::iterator  currentSeller;
    vector <Buyer>::iterator  currentBuyer;

    if(lastSelected < 0)
        return;

    int confirm = QMessageBox::warning(this, "Warning",
                                       "This will remove the daily record from the system permanantly.\n"
                                       "Are you sure that you want to do this?",
                                       QMessageBox::Cancel, QMessageBox::Ok);

    if(confirm == QMessageBox::Cancel)
    {
        return;
    }

    ChargeDAO chargeDao;
    TruckingRecordDAO truckingDao;
    string currentNumber = "";

    switch(customerType)
    {
    case Customer::Seller:
    default:
        currentSeller = sellerList.begin();
        currentSeller += lastSelected;
        currentNumber = currentSeller->getNumber();

        chargeDao.deleteAdjustment(*currentSeller, Customer::Seller);
        chargeDao.deleteChargeSummary(*currentSeller, Customer::Seller);
        truckingDao.deleteTruckingRecordList(*currentSeller, Customer::Seller);
        SellerInvoiceDAO().deleteSummary(*currentSeller);
        SellerDAO::deleteSeller(*currentSeller);
        break;

    case Customer::Buyer:
        currentBuyer = buyerList.begin();
        currentBuyer += lastSelected;
        currentNumber = currentBuyer->getNumber();
        chargeDao.deleteAdjustment(*currentBuyer, Customer::Buyer);
        chargeDao.deleteChargeSummary(*currentBuyer, Customer::Buyer);
        truckingDao.deleteTruckingRecordList(*currentBuyer, Customer::Buyer);
        BuyerDAO::deleteBuyer(*currentBuyer);
        BuyerInvoiceDAO().deleteSummary(*currentBuyer);
        break;
    }
    clearDaily();
    populateDailyList(QString::fromStdString(currentNumber));
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    searchListByNumber()
//
// purpose: sets the current daily to the daily in the daily vector that has
//          the customer number in the dailyId edit box
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

void DailyDialog::searchListByNumber()
{
     qDebug() << "DailyDialog::searchListByNumber()";
    QString text = ui->dailyID->text().stripWhiteSpace();
    vector<Seller>::iterator currentSeller = sellerList.begin();
    vector<Buyer>::iterator currentBuyer = buyerList.begin();
    int index = -1;
    int listSize = (customerType == Customer::Seller ? sellerList.size() : buyerList.size());

    for(int i = 0; i < listSize; i++)
    {
        switch(customerType)
        {
        case Customer::Seller:
            if(*currentSeller == text.toStdString())
                index = i;
            else
                currentSeller++;
            break;

        case Customer::Buyer:
            if(*currentBuyer == text.toStdString())
                index = i;
            else
                currentBuyer++;
            break;
        }
        if(index != -1)
        {
            break;
        }
    }

    if ( index == -1 && customerType == Customer::Seller)
    {
        //cout << "Didn't find the seller/buyer in Seller/Buyer vector." << endl;
        if ( setup.getBoolean("dailyFMPhoneMatch") )
        {
            //cout << "    dailyFMPhoneMatch true" << endl;
            QString q = QString(text);
            q = q.remove("-");
            Customer stemp = CustomerDAO::loadFromPhone(q.toStdString());
            if ( stemp.getId() == 0 )
            {
                //cout << "    phone didn't match" << endl;
            } else {
                showDaily(stemp, false);
                ui->dailySave->setFocus();
                //cout << "    having shown the record, exit routine." << endl;
                return;
            }
        } else {
            //cout << "    dailyFMPhoneMatch false" << endl;
        }
    }

    if(index == -1 && customerType == Customer::Buyer)
    {
        Buyer temp = BuyerDAO::loadFromNumber(text.toStdString());
        if(temp.getId() != 0)
        {
            showDaily(temp, true);
            ui->dailySave->setFocus();
        }
        return;
    }

    resetDaily();
    if(ui->dailyListBox->currentItem() == index)
    {
        loadItemFromList(index);
    }
    else
    {
        ui->dailyListBox->setCurrentItem(ui->dailyListBox->item(index));
    }
    ui->dailyName->setFocus();
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    searchListByNumber()
//
// purpose: sets the current daily to the daily in the daily vector that has
//          the customer name in the dailyName edit box
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

void DailyDialog::searchListByName(const QString &text)
{
    qDebug() << "DailyDialog::searchListByName() " << text;
    vector<Buyer>::iterator currentBuyer = buyerList.begin();
    vector<Seller>::iterator currentSeller = sellerList.begin();
    Name key(text.toStdString());

    int listSize = (customerType == Customer::Seller ? sellerList.size() : buyerList.size());

    for(int i = 0; i < listSize; i++)
    {
        if((customerType == Customer::Seller && *currentSeller  == key) || (customerType == Customer::Buyer && *currentBuyer == key))
        {
            ui->dailyListBox->setCurrentItem(ui->dailyListBox->item(i));
            return;
        }
        if(customerType == Customer::Seller) {
            currentSeller++;
        }
        else currentBuyer++;
    }
}

///////////////////////////////////////////////////////////////////////////////
//
// name:    init(CUSTOMER_TYPE)
//
// purpose: sets up the class as a BUYER or SELLER
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

void DailyDialog::init(Customer::Type customerType)
{
    qDebug() << "DailyDialog::init([customerType]) ";
    this->customerType = customerType;
    blockAutoMerge = false;
    if(blockInit)
    {
        return;
    }

    blockInit = true;
    this->customerType = customerType;

    switch(customerType)
    {
    case SELLER:

        ui->formHeader->setText("<i><b><font size=\"+4\">Daily Seller File</font></b></i>");
        ui->companyLabel->setText("Mortgage:");
        ui->headLabel->show();
        ui->dailyHead->show();
        ui->tagButtonDaily->show();
        ui->sellerButton->setChecked(true);
        ui->dailyBeefCouncil->show();
        if(rfIdTagsOn)
        {
            ui->rfTagListBox->show();
        }
        else
        {
            ui->rfTagListBox->hide();
        }
        if ( setup.getBoolean("dailyFMCheckinTickets") )
        {
            ui->opInitialsLabel->show();
            ui->opInitials->show();
            ui->descrCodeLabel->show();
            ui->descrCode->show();
            ui->descriptionLabel->show();
        }
        else  {
            ui->opInitialsLabel->hide();
            ui->opInitials->hide();
            ui->descrCodeLabel->hide();
            ui->descrCode->hide();
            ui->descriptionLabel->hide();
        }

        ui->showMissingBuyersButton->hide();

        break;

    case BUYER:
        ui->formHeader->setText("<i><b><font size=\"+4\">Daily Buyer File</font></b></i>");
        ui->companyLabel->setText("Company");
        ui->headLabel->hide();
        ui->dailyHead->hide();
        ui->tagButtonDaily->hide();
        ui->buyerButton->setChecked(true);
        ui->rfTagListBox->hide();
        ui->dailyBeefCouncil->hide();
        ui->opInitialsLabel->hide();
        ui->opInitials->hide();
        ui->descrCodeLabel->hide();
        ui->descrCode->hide();
        ui->descriptionLabel->hide();
        ui->showMissingBuyersButton->show();
        break;
    }
    blockInit = false;

    clearDaily();
    populatePermList();
    populateDailyList();
}

Customer::Type DailyDialog::getCustomerType()
{
    return customerType;
}

///////////////////////////////////////////////////////////////////////////////
//
// name:    clearDaily()
//
// purpose: resets the form
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

void DailyDialog::clearDaily()
{
    qDebug() << "DailyDialog::clearDaily() ";
    ui->dailyID->setText("");
    resetDaily();
    ui->dailyID->setFocus();
}

void DailyDialog::resetDaily()
{
    qDebug() << "DailyDialog::resetDaily() ";
    ui->dailyName->setText("");
    ui->dailyAddress1->setText("");
    ui->dailyAddress2->setText("");
    ui->dailyCity->setText("");
    ui->dailyState->setText("");
    ui->dailyZip->setText("");
    ui->dailyMortgage->setText("");
    ui->dailyHead->setText("");
    ui->dailyComment->setText("");
    ui->descrCode->setText("");
    ui->descriptionLabel->setText("");

    ui->dailyBeefCouncil->setChecked(true);
    customerId = 0;

    if(rfIdTagsOn)
    {
        ui->rfTagListBox->clear();
    }
}

void DailyDialog::changeDialogMode(int buttonId)
{
    qDebug() << "DailyDialog::changeDialogMode() ";
    init(Customer::Type(buttonId));
//    populatePermList();
//    populateDailyList();
}

void DailyDialog::populatePermList()
{
     qDebug() << "DailyDialog::populatePermList() ";
    setCursor(Qt::WaitCursor);
    string filter = ui->letterComboBox->currentText().toStdString();

    if(filter == "Other")
    {
        filter = "([[:blank:]]|[[:digit:]]|[[:punct:]]|[[:space:]])";
    }
    else if(filter == "All")
    {
        filter="";
    }

    permList = CustomerDAO::getCustomerListThatBeginsWith(filter, customerType);

//    std::sort(permList.begin(), permList.end(), Customer::comparePermanantCustomers);
    QStringList itemList;
    string address1String;
    string address2String;
    string cityString;
    string companyString;

    for(unsigned int i = 0; i < permList.size(); i++)
    {
        address1String = permList[i].getAddress().getAddress1();
        address2String = permList[i].getAddress().getAddress2();
        cityString = permList[i].getAddress().cityStateZipStr();
        companyString = permList[i].getCompany();

        itemList += QString(customerType == Customer::Seller && permList[i].isAltered() ? "*" : " ") + QString::fromStdString(permList[i].getName().getLast()).leftJustify(20, ' ', true) +
                    (address1String.length() > 0 ? " >>" : "") + QString::fromStdString(address1String) +
                    (address2String.length() > 0 ? " >>" : "") + QString::fromStdString(address2String) +
                    (cityString.length() > 0 ? " >>" : "") + QString::fromStdString(cityString) +
                    (companyString.length()  >0 ? ">>" : "") + QString::fromStdString(companyString);
    }

    ui->dailyPermListBox->clear();
    ui->dailyPermListBox->insertStringList(itemList);
    setCursor(Qt::ArrowCursor);
}

void DailyDialog::loadDailyFromPerm(int row)
{
    qDebug() << "DailyDialog::loadDailyFromPerm() ";
    if(blockLoad)
    {
        return;
    }

    if(row < 0 || row >= ui->dailyPermListBox->numRows())
    {
        return;
    }

    blockAutoMerge = true;
    if(!mergeSeller())
    {
        Customer baseCustomer = permList[row];

        if(customerType == Customer::Seller)
        {
            ui->dailyBeefCouncil->setChecked(baseCustomer.isBeefCouncil());
            string mortgageString = baseCustomer.getCompany();
            ui->madCowCheckBox->setChecked(baseCustomer.isMadCowCertified());
            for(unsigned int i = 0; i < permList.size(); i++)
            {
                if(Customer::sameCustomer(baseCustomer, permList[i]) && permList[i].getCompany() != baseCustomer.getCompany())
                {
                    if(permList[i].getCompany().length() > 0)
                    {
                        mortgageString += " & " + permList[i].getCompany();
                    }
                }
            }
            baseCustomer.setCompany(mortgageString);

            baseCustomer = DailyDialog::checkPayeeLength(baseCustomer, this);

            if(baseCustomer.getId() == 0)
            {
                baseCustomer = permList[row];
            }
        }


        if ( setup.getBoolean("dailyFMPhoneMatch") )
        {
            //cout << "just setting id on id #:" << customerId << ":" << endl;
            ContactList cl = baseCustomer.getContactList();
            string phone = cl.firstPhoneToString();
            //cout << "just setting id to:" << phone << ":" << endl;
            ui->dailyID->setText(QString::fromStdString(phone));
        }
        customerId = baseCustomer.getId();
        ui->dailyName->setText(QString::fromStdString(baseCustomer.getName().getLast()));
        ui->dailyCity->setText(QString::fromStdString(baseCustomer.getAddress().getCity()));
        ui->dailyState->setText(QString::fromStdString(baseCustomer.getAddress().getState()));
        ui->dailyZip->setText(QString::fromStdString(baseCustomer.getAddress().getZip()));
        ui->dailyAddress1->setText(QString::fromStdString(baseCustomer.getAddress().getAddress1()));
        ui->dailyAddress2->setText(QString::fromStdString(baseCustomer.getAddress().getAddress2()));
        ui->dailyMortgage->setText(QString::fromStdString(baseCustomer.getCompany()));


        if(ui->sellerButton->isChecked())
        {
            ui->dailyHead->setFocus();
        }
        else
        {
            ui->dailySave->setFocus();
        }
    }
    blockAutoMerge = false;
}

void DailyDialog::startChargeAdjustment()
{
     qDebug() << "DailyDialog::startChargeAdjustment() ";
    ChargeAdjustmentDialog chargeAdjust(this);
    InvoiceDAO *invoiceDao;
    Invoice *invoice;

    switch(customerType)
    {
    case Customer::Seller:
    default:
        invoiceDao = new SellerInvoiceDAO();
        break;

    case Customer::Buyer:
        invoiceDao = new BuyerInvoiceDAO();
        break;
    }

    CommissionDAO::COLOR_GROUP group = CommissionDAO::INVALID;


    invoice = invoiceDao->getInvoiceByCustomer(ui->dailyID->text().toStdString(), group, true);

    if(invoice != NULL)
    {
        chargeAdjust.init(invoice);
        chargeAdjust.setInvoiceDAORef(invoiceDao);

        if(customerType == Customer::Buyer)
        {
            chargeAdjust.setIsBuyer(true);
        }
        chargeAdjust.exec();

    }
    invoiceDao->freeInvoice();
    delete invoiceDao;
}

void DailyDialog::startTrucking()
{
    qDebug() << "DailyDialog::startTrucking() ";
    InvoiceDAO *invoiceDao;
    ChargeDAO::CUST_TYPE chargeType;
    switch(customerType)
    {
    case Customer::Seller:
        chargeType = ChargeDAO::Seller;
        invoiceDao = new SellerInvoiceDAO();
        break;

    case Customer::Buyer:
        chargeType = ChargeDAO::Buyer;
        invoiceDao = new BuyerInvoiceDAO();
        break;
    }
    TruckingDialog trucking(this);
    trucking.init(*invoiceDao->getInvoiceByCustomer(ui->dailyID->text().toStdString()), chargeType);
    trucking.exec();
    delete invoiceDao;
}


void DailyDialog::startTagEdit()
{
        qDebug() << "DailyDialog::startTagEdit() ";
    if(customerType == Customer::Seller && ui->dailyID->text() != "")// && 0 <= lastSelected && lastSelected < sellerList.size())
    {
        TagEditDialog tagEditor(this);
        Seller temp;
        temp.setNumber(ui->dailyID->text().stripWhiteSpace().toStdString());
        tagEditor.init(temp);//sellerList[lastSelected]);
        tagEditor.exec();
    }
}

void DailyDialog::showDailyReport()
{
     qDebug() << "DailyDialog::showDailyReport() ";
    QStringList options;
    bool ok;
    options << "Sort By Name" << "Sort By Number";
    string option = QInputDialog::getItem("Sort Option?", "How do you wish to sort the list?", options, 0, false, &ok).toStdString();
    vector<Seller> sellerReportList;
    vector<Buyer> buyerReportList;

    if(!ok)
    {
        return;
    }

    CustomerReport *report;
    vector<string> checkNumberList;
    setCursor(Qt::WaitCursor);
    switch(customerType)
    {
    case Customer::Seller:
    default:
        sellerReportList = SellerDAO::getCustomerList();
        std::sort(sellerReportList.begin(), sellerReportList.end(),
                  (option == options[0].toStdString() ? Customer::compareCustomerNames : Customer::compareCustomerNumbers));
        checkNumberList = SellerInvoiceDAO().getCustomersCheckList(sellerReportList);
        report = new SellerReport(sellerReportList, checkNumberList);
        break;

    case Customer::Buyer:
        buyerReportList = BuyerDAO::getCustomerList();
        std::sort(buyerReportList.begin(), buyerReportList.end(),
                  (option == options[0].toStdString() ? Customer::compareCustomerNames : Customer::compareCustomerNumbers));
        report = new BuyerReport(buyerReportList);
        break;
    }

    report->setHeader(setup.reportHeader(report->headerString()));
    report->text(); // Generate report
    setCursor(Qt::ArrowCursor);
    PreviewDialog prev;
    prev.setReport(report);
    prev.setShowPrint(true);
    prev.exec();

    delete report;
    qDebug() << "DailyDialog::showDailyReport() exited ";
}

void DailyDialog::findNearest(const QString& text)
{
    char firstChar = 'A';

    if(ui->dailyName->text().length() > 0)
    {
        firstChar = ui->dailyName->text().upper().ascii()[0];


        if((firstChar != ui->letterComboBox->currentText().upper().ascii()[0] && (isalpha(firstChar) != 0) ||
                ((isalpha(firstChar) == 0) && ui->letterComboBox->currentText() != "Other")) && ui->letterComboBox->currentText() != "All")
        {
            if(isalpha(firstChar) != 0)
            {
                ui->letterComboBox->setCurrentText(QString(1, firstChar));
            }
            else
            {
                ui->letterComboBox->setCurrentText("Other");
            }

            populatePermList();
        }
    }
    blockLoad = true;

    Q3ListBoxItem* permItem = ui->dailyPermListBox->findItem(QString("*") + text);

    if(permItem == NULL)
    {
        permItem = ui->dailyPermListBox->findItem(QString(" ") + text);
    }

    if (permItem != NULL) {
        ui->dailyPermListBox->setCurrentItem(permItem);
        ui->dailyListBox->setCurrentItem(ui->dailyListBox->findItem(text));
        blockLoad = false;
    }
    else {
        ui->dailyPermListBox->clearSelection();
        ui->dailyListBox->clearSelection();
        blockLoad = false;
    }
}

void DailyDialog::autoLoadPerm()
{
    loadDailyFromPerm(ui->dailyPermListBox->currentItem());
}

void DailyDialog::loadCityStateZipFromCity()
{
    vector<Address> zipCodeList = ZipCodeDAO().getZipCodeListByCity(ui->dailyCity->text().toStdString());
    autoLoadCityStateZip(zipCodeList);
}

void DailyDialog::loadCityStateZipFromZip()
{
    vector<Address> zipCodeList = ZipCodeDAO().getZipCodeListByZip(ui->dailyZip->text().toStdString());
    autoLoadCityStateZip(zipCodeList);
}

void DailyDialog::autoLoadCityStateZip(vector<Address> zipCodeList)
{
    string city, state, zip;

    if(zipCodeList.size() == 0)
    {
        return;
    }
    if(zipCodeList.size() == 1)
    {
        city = zipCodeList[0].getCity();
        state = zipCodeList[0].getState();
        zip = zipCodeList[0].getZip();
    }
    else if(zipCodeList.size() > 1)
    {

        ZipCodeDialog zipDialog(this);
        zipDialog.init(zipCodeList);

        if(zipDialog.exec() == QDialog::Accepted)
        {
            Address temp = zipDialog.getCurrentAddress();
            city = temp.getCity();
            state = temp.getState();
            zip = temp.getZip();
        }
        else
        {
            return;
        }
    }
    ui->dailyCity->setText(QString::fromStdString(city));
    ui->dailyState->setText(QString::fromStdString(state));
    ui->dailyZip->setText(QString::fromStdString(zip));
    ui->dailyMortgage->setFocus();
}

void DailyDialog::mergeDaily()
{
    if(!blockAutoMerge)
        mergeSeller();
}

bool DailyDialog::mergeSeller()
{
    if(customerType == Customer::Seller && customerId == 0 && ui->dailyName->text().length() > 0)
    {
        Name tempName(ui->dailyName->text().toStdString());
        vector<Seller>::iterator sellerIt;

        if((sellerIt = std::find(sellerList.begin(), sellerList.end(), tempName)) != sellerList.end())
        {
            int option = QMessageBox::question(this, "Found Customer With Same Name",
                                               "A Customer with this name already exists.\n"
                                               "Do you want to add head to the customer that "
                                               "already exists, or create a new record?",
                                               "Add Head", "Create New");

            if(option == 0)
            {
                bool ok;
                long headToAdd = QInputDialog::getInteger("Enter head to add",
                                 "How many head do you wish to add?",
                                 ui->dailyHead->text().toLong(), 0,  2147483647, 1, &ok, this);

                if(ok)
                {
                    sellerIt->setHead(sellerIt->getHead() + headToAdd);
                    SellerDAO::saveCustomer(*sellerIt);
                    populateDailyList();
                    clearDaily();
                    return true;
                }
            }
        }
    }

    return false;
}

Customer DailyDialog::checkPayeeLength(Customer baseCustomer, QWidget* parent)
{
    CheckFormatData checkFormat = CheckDAO().getCheckFormat();

    while(!checkFormat.payeeFitsOnLine(Check::createSellerPayeeLine(baseCustomer)))
    {
        QStringList menu;
        menu << "Edit the mortgage line"
             << "Edit the name line"
             << "Truncate the payee line on the check(NOT RECOMMENDED)";

        bool ok;

        QString option = QInputDialog::getItem("Payee line too long",
                                               "When the check is written, the customer name and mortgages\n"
                                               "will be to long to fit on the payee line, what do you wish to do?",
                                               menu, 0, false, &ok, parent);

        if(!ok)
        {
            return Customer();
        }
        else if(option == menu[0])
        {
            string newMortgage = QInputDialog::getText("Re-enter mortgage",
                                 "How do you wish the mortgage to appear?",
                                 QLineEdit::Normal, QString::fromStdString(baseCustomer.getCompany()), &ok, parent ).toStdString();

            if(!ok)
            {
                return Customer();
            }

            baseCustomer.setCompany(newMortgage);
        }
        else if(option == menu[1])
        {
            string newName = QInputDialog::getText("Re-enter name",
                                                   "How do you wish the name to appear?",
                                                   QLineEdit::Normal, QString::fromStdString(baseCustomer.getName().getLast()), &ok, parent ).toStdString();

            if(!ok)
            {
                return Customer();
            }

            baseCustomer.setCompany(newName);
        }
        else
        {
            int option = QMessageBox::warning(parent, "!!CAUTION!!",
                                              "Are you sure that you want to do this?\n"
                                              "If a mortgage is truncated there may be a liability!",
                                              QMessageBox::Cancel, QMessageBox::Ok);
            if(option == QMessageBox::Ok)
            {
                return baseCustomer;
            }
        }
    }

    return baseCustomer;
}

void DailyDialog::keyPressEvent(QKeyEvent* keyPress)
{
    if(ui->dailyName->hasFocus())
    {
        int permIndex = ui->dailyPermListBox->currentItem();
        bool changePerm = false;
        switch(keyPress->key())
        {
        case Qt::Key_Up:
            permIndex--;
            changePerm = true;
            break;

        case Qt::Key_Down:
            permIndex++;
            changePerm = true;
            break;
        }

        if(changePerm && ui->dailyPermListBox->numRows() > 0)
        {
            if(permIndex < 0)
            {
                permIndex = 0;
            }

            if(permIndex > ui->dailyPermListBox->numRows() - 1)
            {
                permIndex = ui->dailyPermListBox->numRows() - 1;
            }

            //blockLoad = true;
            ui->dailyPermListBox->setCurrentItem(permIndex);
            ui->dailyName->setFocus();
            //blockLoad = false;
        }
    }

    QDialog::keyPressEvent(keyPress);
}

void DailyDialog::startVet()
{
    if(ui->dailyID->text().stripWhiteSpace() != "")
    {
        VetDialog vetDialog(this);
        Seller tempSeller = SellerDAO::loadFromNumber(ui->dailyID->text().stripWhiteSpace().toStdString());
        vetDialog.initSeller(tempSeller);
        vetDialog.exec();
    }
}



void DailyDialog::displayAnimalCodeDescr()
{
    AnimalCodeDAO dao;
    AnimalCode tempCode = AnimalCode::fromString(ui->descrCode->text().toStdString());
    ui->descriptionLabel->setText(QString::fromStdString(dao.fillAnimalCode(tempCode).getDescrip()));
    //cout << "Display animal code." << endl;
}

// [KLN] add (for debugging)
void DailyDialog::showCustomerType(const string &funcName) {
    switch(customerType)
    {
    case Customer::Seller:
        cout << "(" << funcName << ") customerType: Seller" << endl;
        break;
    case Customer::Buyer:
        cout << "(" << funcName << ") customerType: Buyer" << endl;
        break;
     default:
        cout << "(" << funcName << ") customerType: Other" << endl;
        break;
   }
}
// [KLN] add end

///////////////////////////////////////////////////////////////////////////////
//
// name:    void showMissingBuyers()
//
// purpose: call a Java program to display buyers that are in transactions but
//          not in the daily buyer file.
//
// calling params:
//
// return params:
//
// Notes:
//
// Todo:
//
//////////////////////////////////////////////////

void DailyDialog::showMissingBuyers() {
    QString home = qgetenv("HOME");
    system("java -jar " + home + "/dist/MissingBuyers.jar");
}

