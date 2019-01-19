//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add delete ui;
//   delete moc include at end

#include "permanantdialog.h"
#include "ui_permanantdialog.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qcombobox.h>
#include <qpushbutton.h>
#include <qbuttongroup.h>
#include <qradiobutton.h>
#include <Q3ListBox>
#include <qcheckbox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

#include <QKeyEvent>

PermanantDialog::PermanantDialog( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl ), ui(new Ui::PermanantDialog)
{
    ui->setupUi(this);

    // signals and slots connections
    connect( ui->customers, SIGNAL( highlighted(int) ), this, SLOT( loadItem(int) ) );
    connect( ui->permSave, SIGNAL( clicked() ), this, SLOT( saveItem() ) );
    connect( ui->deletePerm, SIGNAL( clicked() ), this, SLOT( deletePermanent() ) );
    connect( ui->printPermButton, SIGNAL( clicked() ), this, SLOT( showReport() ) );
    connect( ui->letterComboBox, SIGNAL( activated(const QString&) ), this, SLOT( populateCustomerList() ) );
    connect( ui->customerTypeButtonGroup, SIGNAL( clicked(int) ), this, SLOT( populateCustomerList() ) );
    connect( ui->permName, SIGNAL( textChanged(const QString&) ), this, SLOT( permListSearch(const QString&) ) );
    connect( ui->permName, SIGNAL( returnPressed() ), this, SLOT( autoLoadPerm() ) );
    connect( ui->customerTypeButtonGroup, SIGNAL( clicked(int) ), this, SLOT( reset() ) );
    connect( ui->printLabelsButton, SIGNAL( clicked() ), this, SLOT( printMailingLabels() ) );
    connect( ui->letterComboBox, SIGNAL( activated(int) ), this, SLOT( reset() ) );
    connect( ui->permCity, SIGNAL( lostFocus() ), this, SLOT( loadCityStateZipFromCity() ) );
    connect( ui->permNumberEdit, SIGNAL( lostFocus() ), this, SLOT( onPermNumLostFocus() ) );
    connect( ui->permZip, SIGNAL( returnPressed() ), this, SLOT( loadCityStateZipFromZip() ) );
    connect( ui->customers, SIGNAL( selected(int) ), this, SLOT( loadItem(int) ) );

    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
PermanantDialog::~PermanantDialog()
{
    qDebug("~PermanantDialog() deleting");
    delete ui;
}

#include "dao/salemanager.h"
#include "previewdialog.h"
#include "reports/customerreport.h"
#include "reports/mailinglabels.h"
#include "dao/zipcodedao.h"
#include "zipcodedialog.h"
#include <qmessagebox.h>
#include <qinputdialog.h>

void PermanantDialog::init()
{
    qDebug("PermanantDialog::init()");
    QStringList letterOptions;
    letterOptions <<"A"<<"B"<<"C"<<"D"<<"E"<<"F"<<"G"<<"H"<<"I"<<"J"
                  <<"K"<<"L"<<"M"<<"N"<<"O"<<"P"<<"Q"<<"R"<<"S"<<"T"
                  <<"U"<<"V"<<"W"<<"X"<<"Y"<<"Z"<<"Other"<<"All";
    ui->letterComboBox->insertStringList(letterOptions);
    ui->letterComboBox->setCurrentItem(0);

    ui->currentDate->setText(QString::fromStdString(SaleManager().currentSaleDate().toString("mm-dd-YYYY")));
    custId = 0;
    blockLoad = false;

    /*
     * not implementing this functionality unless someone asks
     * for it
     */

//  permMadCow->hide();

    ui->permBCouncil->setChecked(TRUE);
}

void PermanantDialog::init(Customer::Type type)
{
    qDebug("PermanantDialog::init(Customer::Type type)");
    if(type == Customer::Buyer)
    {
        ui->buyerButton->setChecked(true);
    }
    else
    {
        ui->sellerButton->setChecked(true);
    }
    populateCustomerList();
}
bool PermanantDialog::comparePermanantCustomers(Customer a, Customer b)
{
    if(a.getName().getLast() == b.getName().getLast())
    {
        return (a.getCompany() < b.getCompany());
    }

    return a.getName().getLast() < b.getName().getLast();
}

void PermanantDialog::populateCustomerList()
{
    setCursor(Qt::WaitCursor);
    string filter = ui->letterComboBox->currentText().toStdString();
    if(filter == "All")
    {
        filter = "";
    }

    if(filter == "Other")
    {
        filter = "([[:blank:]]|[[:digit:]]|[[:punct:]]|[[:space:]])";
    }
    Customer::Type type = Customer::Seller;

    if(ui->buyerButton->isChecked())
    {
        type = Customer::Buyer;

        ui->permNumberLabel->show();
        ui->permNumberEdit->show();
        ui->permBCouncil->hide();
    }
    else
    {

        ui->permBCouncil->show();
        ui->permNumberLabel->hide();
        ui->permNumberEdit->hide();
    }

    ui->relationsComboBox->hide();

    ui->companyLabel->setText(type == Customer::Buyer ? "Company" : "Mortgage");
    customerList = customerDao.getCustomerListThatBeginsWith(filter, type);
    std::sort(customerList.begin(), customerList.end(), comparePermanantCustomers);

    QStringList customerStringList;


    string address1String, address2String, cityString, companyString;

    for(unsigned int i = 0; i < customerList.size(); i++)
    {
        address1String = customerList[i].getAddress().getAddress1();
        address2String = customerList[i].getAddress().getAddress2();
        cityString = customerList[i].getAddress().cityStateZipStr();
        companyString = customerList[i].getCompany();

        customerStringList += QString(type == Customer::Seller && customerList[i].isAltered() ? "*" : " ") + QString(QString::fromStdString(customerList[i].getName().getLast())).leftJustify(20, ' ', true) +
                              (address1String.length() > 0 ? " >>" : "") + QString::fromStdString(address1String) +
                              (address2String.length() > 0 ? " >>" : "") + QString::fromStdString(address2String) +
                              (cityString.length() > 0 ? " >>" : "") + QString::fromStdString(cityString) +
                              (companyString.length() > 0 ? " >>" : "") + QString::fromStdString(companyString);
    }
    ui->customers->clear();
    ui->customers->insertStringList(customerStringList);
    setCursor(Qt::ArrowCursor);
//   reset();
}

void PermanantDialog::permListSearch(const QString& text)
{
    blockLoad = true;
    char firstChar = 'A';

    if(ui->permName->text().length() > 0)
    {
        firstChar = ui->permName->text().upper().ascii()[0];


        if(firstChar != ui->letterComboBox->currentText().upper().ascii()[0]
                && ((isalpha(firstChar) != 0) || ((isalpha(firstChar) == 0)  && ui->letterComboBox->currentText() != "Other"))
                && ui->letterComboBox->currentText().stripWhiteSpace() != "All")
        {
            if(isalpha(firstChar) != 0 && ui->letterComboBox->currentText().stripWhiteSpace() != "All")
            {
                ui->letterComboBox->setCurrentText(QString::fromStdString(string(1, firstChar)));
            }
            else if(ui->letterComboBox->currentText().stripWhiteSpace() != "All")
            {
                ui->letterComboBox->setCurrentText("Other");
            }
            populateCustomerList();
        }
    }

    Q3ListBoxItem* item = ui->customers->findItem("*" + text);

    if(item == NULL)
    {
        item = ui->customers->findItem(" " + text);
    }

    if (item != NULL ) {
        ui->customers->setCurrentItem(item);
        blockLoad = false;
    }
    else {
        ui->customers->clearSelection();
        blockLoad = false;
    }
}

void PermanantDialog::autoLoadPerm()
{
    loadItem(ui->customers->currentItem());
}

void PermanantDialog::loadItem(int row)
{
    if(row < 0 || row >= ui->customers->numRows() || blockLoad)
    {
        return;
    }

    ui->permName->setText(QString::fromStdString(customerList[row].getName().getLast()));
    ui->permAddress1->setText(QString::fromStdString(customerList[row].getAddress().getAddress1()));
    ui->permAddress2->setText(QString::fromStdString(customerList[row].getAddress().getAddress2()));
    ui->permCity->setText(QString::fromStdString(customerList[row].getAddress().getCity()));
    ui->permState->setText(QString::fromStdString(customerList[row].getAddress().getState()));
    ui->permZip->setText(QString::fromStdString(customerList[row].getAddress().getZip()));
    ui->permCounty->setText(QString::fromStdString(customerList[row].getAddress().getCounty()));

    ui->permPhone->setText(QString::fromStdString(customerList[row].getContactList().getFirstPhone()));
    ui->permSSN->setText(QString::fromStdString(customerList[row].getSocialSecurityNumber()));
    ui->permComment->setText(QString::fromStdString(customerList[row].getComment()));
    ui->permCCNo->setText(QString::fromStdString(customerList[row].getCreditCardNumber()));
    custId = customerList[row].getId();

    ui->permMadCow->setChecked(customerList[row].isMadCowCertified());
    ui->permBCouncil->setChecked(customerList[row].isBeefCouncil());
    ui->permMailList->setChecked(customerList[row].isOnMailingList());
    ui->permMortgage->setText(QString::fromStdString(customerList[row].getCompany()));

    if(ui->buyerButton->isChecked())
    {
        ui->permNumberEdit->setText(QString::fromStdString(customerList[row].getNumber()));
        if ( ui->permNumberEdit->text().isEmpty()) {
            ui->relationsComboBox->hide();
        }
        else {
            ui->relationsComboBox->show();
            ui->relationsComboBox->setCurrentIndex(customerList[row].getRelation());
        }

    }
}

void PermanantDialog::saveItem()
{
    bool altered = true;

    if(Customer::customerPartOfNumber(ui->permNumberEdit->text().toStdString()) != "")
    {
        Customer existingCustomer = CustomerDAO::loadFromPermNumber(ui->permNumberEdit->text().toStdString(), false);

        if(existingCustomer.getId() != 0 && existingCustomer.getId() != custId
                && ui->permNumberEdit->text() == QString::fromStdString(existingCustomer.getNumber())
                && !ui->permNumberEdit->text().isEmpty()  // Ticket #94 - do not compare empty string.
          )
        {
            int opt = QMessageBox::warning(this, "Warning",
                                           "This permanant number is already in use by another customer.",
                                           "Cancel", "Save Anyway");

            if(opt == 0)
            {
                return;
            }
        }
    }

    if(custId != 0)
    {
        int i = ui->customers->currentItem();
        altered = customerDao.previouslyAltered(custId);

        if(0 <= i && i < customerList.size() && !altered)
        {
            if(ui->permName->text() != QString(QString::fromStdString(customerList[i].getName().getLast())))
            {
                altered = true;
            }
            else if(ui->permAddress1->text() != QString::fromStdString(customerList[i].getAddress().getAddress1()))
            {
                altered = true;
            }
            else if(ui->permAddress2->text() != QString::fromStdString(customerList[i].getAddress().getAddress2()))
            {
                altered = true;
            }
            else if(ui->permCity->text() != QString::fromStdString(customerList[i].getAddress().getCity()))
            {
                altered = true;
            }
            else if(ui->permState->text() != QString::fromStdString(customerList[i].getAddress().getState()))
            {
                altered = true;
            }
            else if(ui->permZip->text() != QString::fromStdString(customerList[i].getAddress().getZip()))
            {
                altered = true;
            }
            else if(ui->permCounty->text() != QString::fromStdString(customerList[i].getAddress().getCounty()))
            {
                altered = true;
            }
            else if(ui->permSSN->text() != QString::fromStdString(customerList[i].getSocialSecurityNumber()))
            {
                altered = true;
            }
            else if(ui->permMortgage->text() != QString::fromStdString(customerList[i].getCompany()))
            {
                altered = true;
            }
            else if(ui->permCCNo->text() != QString::fromStdString(customerList[i].getCreditCardNumber()))
            {
                altered = true;
            }
            else if(ui->permComment->text() != QString::fromStdString(customerList[i].getComment()))
            {
                altered = true;
            }
            else if(ui->permMadCow->isChecked() != customerList[i].isMadCowCertified())
            {
                altered = true;
            }
            else if(ui->permBCouncil->isChecked() != customerList[i].isBeefCouncil())
            {
                altered = true;
            }
            else if(ui->permMailList->isChecked() != customerList[i].isOnMailingList())
            {
                altered = true;
            }
            else if(ui->permPhone->text() != QString::fromStdString(customerList[i].getContactList().getFirstPhone()))
            {
                altered = true;
            }
        }
    }

    Customer temp = Customer(custId, Name(ui->permName->text().toStdString()),
                             Address(ui->permAddress1->text().toStdString(), ui->permAddress2->text().toStdString(), ui->permCity->text().toStdString(),
                                     ui->permState->text().toStdString(), ui->permZip->text().toStdString(), "", ui->permCounty->text().toStdString()),
                             ContactList(ui->permPhone->text().toStdString()), "", ui->permSSN->text().toStdString(), ui->permCCNo->text().toStdString(),
                             ui->permComment->text().toStdString(), ui->permMadCow->isChecked(), ui->permBCouncil->isChecked(), ui->permMailList->isChecked(),
                             ui->permMortgage->text().toStdString(),ui->relationsComboBox->currentIndex());

    temp.setNumber(ui->permNumberEdit->text().toStdString());

    Customer::Type type = Customer::Seller;

    if(ui->buyerButton->isChecked())
    {
        type = Customer::Buyer;
    }

    customerDao.saveCustomer(temp, type, altered, type == Customer::Buyer);

    if(temp.getId() != 0)
    {
//    CustomerDAO::updateChildCountryOfOrigin(temp);
    }

    int currentItem = ui->customers->currentItem();
    populateCustomerList();

    if(0 <= currentItem && currentItem < customerList.size())
    {
        blockLoad = true;
        ui->customers->setCurrentItem(currentItem);
        blockLoad = false;
    }

    reset();
}

void PermanantDialog::reset()
{
    ui->permName->setText("");
    ui->permAddress1->setText("");
    ui->permAddress2->setText("");
    ui->permCity->setText("");
    ui->permState->setText("");
    ui->permZip->setText("");
    ui->permCounty->setText("");
    //   permAC->setText("");
    ui->permPhone->setText("");
    ui->permSSN->setText("");
    ui->permComment->setText("");
    ui->permCCNo->setText("");
    custId = 0;

    ui->permMadCow->setChecked(false);
    ui->permBCouncil->setChecked(true);
    ui->permMailList->setChecked(false);
    ui->permMortgage->setText("");

    ui->permName->setFocus();
    ui->permNumberEdit->setText("");
}

void PermanantDialog::deletePermanent()
{
    int confirm = QMessageBox::warning(this, "Warning",
                                       "This will remove the record from the system permanantly.\n"
                                       "Are you sure that you want to continue?",
                                       QMessageBox::Cancel, QMessageBox::Ok);

    if(confirm == QMessageBox::Ok)
    {
        int customerIndex = ui->customers->currentItem();
        customerDao.deleteCustomer(Customer(custId));
        populateCustomerList();
        reset();
        blockLoad = true;
        if(0 <= customerIndex && customerIndex < ui->customers->numRows())
        {
            ui->customers->setCurrentItem(customerIndex);
        }
        else if(0 < customerIndex && customerIndex - 1 < ui->customers->numRows())
        {
            ui->customers->setCurrentItem(customerIndex - 1);
        }
        else if(0 < ui->customers->numRows())
        {
            ui->customers->setCurrentItem(ui->customers->numRows() - 1);
        }
        blockLoad = false;
    }
}

void PermanantDialog::showReport()
{
    CustomerReport report(customerList);
    PreviewDialog prev;
    QString reportStr = QString::fromStdString(report.unformattedText());
    prev.setReport(&report);
    prev.setText(reportStr);
    prev.setShowPrint(true);
    prev.exec();
}

void PermanantDialog::loadCityStateZipFromCity()
{
    vector<Address> zipCodeList = ZipCodeDAO().getZipCodeListByCity(ui->permCity->text().toStdString());
    autoLoadCityStateZip(zipCodeList);
}

void PermanantDialog::loadCityStateZipFromZip()
{
    vector<Address> zipCodeList = ZipCodeDAO().getZipCodeListByZip(ui->permZip->text().toStdString());
    autoLoadCityStateZip(zipCodeList);
}
void PermanantDialog::autoLoadCityStateZip(vector<Address> zipCodeList)
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
    ui->permCity->setText(QString::fromStdString(city));
    ui->permState->setText(QString::fromStdString(state));
    ui->permZip->setText(QString::fromStdString(zip));
    ui->permCounty->setFocus();
}

void PermanantDialog::printMailingLabels()
{
    vector<Customer> tempList = customerList;

    sort(tempList.begin(), tempList.end(), Customer::compareZipCodesLT);

    bool ok;
    QStringList menu;
    menu << "Mailing List" << "All";
    QString opt = QInputDialog::getItem("What to Show",
                                        "Printing labels for: '" + ui->letterComboBox->currentText() + "' customers\n"
                                        "Which customer labels do you want to print?",
                                        menu,
                                        0, false, &ok, this);

    if(ok)
    {
        MailingLabels labelReport(tempList, opt == "All");

        labelReport.text();

        deque<string> labelPages = labelReport.paginatedText();

        string labelText;

        for(unsigned int i = 0; i < labelPages.size(); i++)
        {
            if(QString::fromStdString(labelPages[i]).stripWhiteSpace().length() > 0)
            {
                int num = 6 - QString::fromStdString(labelPages[i]).count('\n');
                labelText +=  labelPages[i] + string( (num > 0) ? num : 1 , '\n');
            }
        }

        PrinterBase *printer = PrinterDAO().getPrinter(PrinterDAO::Report);
        printer->print(labelText);
        delete printer;
    }
}

Customer::Type PermanantDialog::currentType()
{
    if(ui->buyerButton->isChecked())
    {
        return Customer::Buyer;
    }

    return Customer::Seller;
}

void PermanantDialog::keyPressEvent(QKeyEvent* event)
{
    if(ui->permName->hasFocus())
    {
        int currentIndex = ui->customers->currentItem();

        bool arrowPress = false;
        switch(event->key())
        {
        case Qt::Key_Up:
            currentIndex--;
            arrowPress = true;
            break;

        case Qt::Key_Down:
            currentIndex++;
            arrowPress = true;
        }

        if(currentIndex < 0)
        {
            currentIndex = 0;
        }

        if(currentIndex > ui->customers->numRows() - 1)
        {
            currentIndex = ui->customers->numRows() - 1;
        }

        if(arrowPress && 0 <= currentIndex && currentIndex < ui->customers->numRows())
        {
            ui->customers->setCurrentItem(currentIndex);
        }
    }
    QDialog::keyPressEvent(event);
}

void PermanantDialog::onPermNumLostFocus()
{
    if ( ui->permNumberEdit->text().isEmpty()) {
        ui->relationsComboBox->hide();
    }
    else {
        ui->relationsComboBox->show();
        ui->relationsComboBox->setCurrentIndex(0);
    }

}
