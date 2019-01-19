//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add delete ui;
//   delete moc include at end

#include "permsearchdialog.h"
#include "ui_permsearchdialog.h"

#include <qvariant.h>
#include <Q3ListBox>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

PermSearchDialog::PermSearchDialog( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl ), ui(new Ui::PermSearchDialog)
{
    ui->setupUi(this);
    // signals and slots connections
    connect( ui->cancelButton, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( ui->okButton, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( ui->permListBox, SIGNAL( returnPressed(Q3ListBoxItem*) ), this, SLOT( accept() ) );
    connect( ui->permListBox, SIGNAL( doubleClicked(Q3ListBoxItem*) ), this, SLOT( accept() ) );

    init();
}

PermSearchDialog::~PermSearchDialog()
{
    delete ui;
}

#include <qinputdialog.h>
#include <qmessagebox.h>
#include <dailydialog.h>
#include <algorithm>

void PermSearchDialog::init()
{
    this->looseMatch = false;
}
void PermSearchDialog::setLooseMatch(bool xlooseMatch)
{
    this->looseMatch = xlooseMatch;
}

void PermSearchDialog::init(QString namePart, Customer::Type type)
{
    this->namePart = namePart;
    this->namePart = this->namePart.replace("\\", "\\\\");
    this->type = type;
    showValidNames();
}

void PermSearchDialog::clearSelection()
{
// permName->deselect();
}
#include "invoicedialog.h"

void PermSearchDialog::showValidNames()
{
    if(namePart.length() > 2)
    {
        customerList = CustomerDAO::getCustomerListThatBeginsWith(namePart.toStdString(), type, looseMatch);
        std::sort(customerList.begin(), customerList.end(), Customer::comparePermanantCustomers);
    }

    QStringList nameList;

    string address1String, address2String, cityString, companyString;

    for(unsigned int i = 0; i < customerList.size(); i++)
    {
        address1String = customerList[i].getAddress().getAddress1();
        address2String = customerList[i].getAddress().getAddress2();
        cityString = customerList[i].getAddress().cityStateZipStr();
        companyString = customerList[i].getCompany();

        nameList += QString(type == Customer::Seller && customerList[i].isAltered() ? "*" : " ")
                    +  QString(QString::fromStdString(customerList[i].getName().getLast())).leftJustify(20, ' ', true)
                    +  (address1String.length() > 0 ? " <<" : "") + QString::fromStdString(address1String)
                    +  (address2String.length() > 0 ? " <<" : "") + QString::fromStdString(address2String )
                    +  (cityString.length() > 0 ? " <<" : "") + QString::fromStdString(cityString)
                    +  (companyString.length() > 0 ? " <<" : "") + QString::fromStdString(companyString);
    }

    ui->permListBox->clear();
    ui->permListBox->insertStringList(nameList);

    if(customerList.size() > 0)
    {
        ui->permListBox->setSelected(0, true);
    }
}

Customer PermSearchDialog::getSelectedCustomer()
{
    Customer baseCustomer(0, Name(namePart.toStdString()));

    for(int i = 0; i < ui->permListBox->numRows(); i++)
    {
        if(ui->permListBox->item(i)->isSelected())
        {
            baseCustomer = customerList[i];
            break;
        }
    }

    if(type == Customer::Seller)
    {
        string mortgageString = baseCustomer.getCompany();

        for(unsigned int i = 0; i < customerList.size(); i++)
        {
            if(Customer::sameCustomer(baseCustomer, customerList[i]) && customerList[i].getCompany() != baseCustomer.getCompany())
            {
                if(customerList[i].getCompany().length() > 0)
                {
                    mortgageString += " & " + customerList[i].getCompany();
                }
            }
        }
        baseCustomer.setCompany(mortgageString);
        baseCustomer = DailyDialog::checkPayeeLength(baseCustomer, this);

        if(baseCustomer.getId() == 0)
        {
            baseCustomer = Customer(0, Name(namePart.toStdString()));
        }
    }

    return baseCustomer;
}
