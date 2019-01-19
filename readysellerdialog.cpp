//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add delete ui;
//   delete moc include at end

#include "readysellerdialog.h"
#include "ui_readysellerdialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <Q3ListBox>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

ReadySellerDialog::ReadySellerDialog( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl ), ui(new Ui::ReadySellerDialog)
{
    ui->setupUi(this);
    // signals and slots connections
    connect( ui->readySellerList, SIGNAL( highlighted(int) ), this, SLOT( accept(int) ) );
    connect( ui->buttonCancel, SIGNAL( clicked() ), this, SLOT( reject() ) );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
ReadySellerDialog::~ReadySellerDialog()
{
    delete ui;
}

QProgressDialog* ReadySellerDialog::progressDialog = NULL;

void ReadySellerDialog::init()
{
    invoiceDao = NULL;
}

void ReadySellerDialog::setDAO(InvoiceDAO* invoiceDao)
{
    progressDialog = NULL;
    this->invoiceDao = invoiceDao;
    InvoiceDAO::ProgressCallback initialCallback = NULL;

    if(this->invoiceDao != NULL && invoiceDao->customerType() == Customer::Seller)
    {
        if(progressDialog == NULL)
        {
            progressDialog = new QProgressDialog(this);
            progressDialog->setModal(true);
            progressDialog->setCaption("Searching Customer");
            progressDialog->setLabelText("Looking for customers that may be ready to print");
            progressDialog->show();
            initialCallback = this->invoiceDao->getProgressCallback();
            this->invoiceDao->setProgressCallback(progressCallback);
        }
    }

    populateReadyList();

    if(this->invoiceDao != NULL && invoiceDao->customerType() == Customer::Seller)
    {
        if(progressDialog != NULL)
        {
            progressDialog->hide();
            delete progressDialog;
            progressDialog = NULL;
            this->invoiceDao->setProgressCallback(initialCallback);
        }
    }
}

void ReadySellerDialog::populateReadyList()
{
    if(invoiceDao == NULL)
    {
        return;
    }
    readyList = invoiceDao->getReadyList(true);

    QStringList list;
    for(unsigned int i = 0; i < readyList.size(); i++)
    {
        list += QString::fromStdString(readyList[i]);
    }
    ui->readySellerList->insertStringList(list);
}

void ReadySellerDialog::accept(int row)
{
    QStringList customerItems = QStringList::split(',', QString::fromStdString(readyList[row]));
    number = (customerItems.size() > 0 ? customerItems[0] : "");
    QDialog::accept();
}

QString ReadySellerDialog::getNumber()
{
    return number;
}

void ReadySellerDialog::progressCallback(int completed, int total)
{
//    cout << "got callback: " << completed <<  ", " << total << endl;
    if(progressDialog != NULL)
    {
        progressDialog->setMaximum(total);
        progressDialog->setValue(completed);
    }
}
