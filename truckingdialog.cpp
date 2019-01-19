//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add delete ui;
//   delete moc include at end

#include "truckingdialog.h"
#include "ui_truckingdialog.h"

#include <qvariant.h>
#include <qlabel.h>
#include <Q3ListBox>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qcombobox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

#include <QMessageBox>

TruckingDialog::TruckingDialog( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl ), ui(new Ui::TruckingDialog)
{
    ui->setupUi(this);
    // signals and slots connections
    connect( ui->truckingCancel, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( ui->Qqty, SIGNAL( textChanged(const QString&) ), this, SLOT( recalc() ) );
    connect( ui->Qprice, SIGNAL( textChanged(const QString&) ), this, SLOT( recalc() ) );
    connect( ui->Qunit, SIGNAL( activated(int) ), this, SLOT( reformatForm() ) );
    connect( ui->truckingDone, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( ui->savetruckers, SIGNAL( clicked() ), this, SLOT( saveTrucker() ) );
    connect( ui->truckerListBox, SIGNAL( highlighted(int) ), this, SLOT( loadTrucker(int) ) );
    connect( ui->truckingDel, SIGNAL( clicked() ), this, SLOT( deleteTrucker() ) );
    connect( ui->truckingDone, SIGNAL( clicked() ), this, SLOT( autoSaveTrucker() ) );

    // tab order
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
TruckingDialog::~TruckingDialog()
{
    delete ui;
}

#include <qmessagebox.h>

using namespace std;

void TruckingDialog::init()
{
    newTrucker = true;
    ui->Qqty->setText("1");
}

void TruckingDialog::init(Invoice invoice, ChargeDAO::CUST_TYPE customerType)
{
    this->invoice = invoice;
    this->customerType = customerType;
    populateTruckerList();
    ui->Qtrucker->setFocus();
    reformatForm();
}

void TruckingDialog::destroy()
{

}

void TruckingDialog::autoSaveTrucker()
{
    if(ui->Qtrucker->text().length() > 0)
    {
        saveTrucker();
    }
}

void TruckingDialog::reformatForm()
{
    if(ui->Qunit->currentText() == "Load")
    {
        ui->qtyLabel->setText("# Loads");
    }
    else if(ui->Qunit->currentText() == "CWT")
    {
        ui->qtyLabel->setText("Weight");
        if(ui->Qqty->text() == "" || ui->Qqty->text() == "1")
        {
            ui->Qqty->setText(QString::number(invoice.weight()));
        }
    }
    else if(ui->Qunit->currentText() == "Head")
    {
        ui->qtyLabel->setText("# Head");
    }
    else if(ui->Qunit->currentText() == "Mile")
    {
        ui->qtyLabel->setText("# Miles");
    }
    else
    {
        ui->qtyLabel->setText("Qty");
    }

    recalc();
}

void TruckingDialog::saveTrucker()
{
    TruckingRecord record;

    if(newTrucker)
    {
        record = TruckingRecord(0);
    }
    else
    {
        if(truckingList[ui->truckerListBox->currentItem()].getCheckNo() != 0)
        {
            return;
        }

        record = truckingList[ui->truckerListBox->currentItem()];
    }

    record.setTruckerName(ui->Qtrucker->text().toStdString());
    record.setPrice(ui->Qprice->text().toDouble());

    long qty = 1;

    if(ui->Qqty->text().length() > 0)
    {
        qty = ui->Qqty->text().toLong();
    }

    record.setQuantity(qty);
    record.setMode(TruckingRecord::MODE(ui->Qunit->currentItem()));

    dao.saveTruckingRecord(record, invoice.getCustomer(), customerType);
    populateTruckerList();
    reset();
}


void TruckingDialog::populateTruckerList()
{
    truckingList = dao.getTruckingRecordList(invoice.getCustomer(), customerType);
    vector<TruckingRecord>::iterator current;
    QStringList truckerStringList;

    for(current = truckingList.begin(); current != truckingList.end(); current++)
    {
        truckerStringList += QString::fromStdString(current->getTruckerName());
    }
    ui->truckerListBox->clear();
    ui->truckerListBox->insertStringList(truckerStringList);
}


void TruckingDialog::loadTrucker(int row)
{
    ui->Qtrucker->setText(QString::fromStdString(truckingList[row].getTruckerName()));
    ui->Qqty->setText(QString::number(truckingList[row].getQuantity()));
    ui->Qprice->setText(QString::number(truckingList[row].getPrice()));
    ui->Qunit->setCurrentItem(int(truckingList[row].getMode()));
    reformatForm();
    newTrucker = false;
}

void TruckingDialog::recalc()
{
    ui->Qextend->setText(QString::number(TruckingRecord(0, "",ui->Qprice->text().toDouble(),
                                         ui->Qqty->text().toLong(),
                                         TruckingRecord::MODE(ui->Qunit->currentItem())).amount(),
                                         'f', 2));
}


void TruckingDialog::deleteTrucker()
{
    if(0 <= ui->truckerListBox->currentItem() && ui->truckerListBox->currentItem() < ui->truckerListBox->numRows())
    {
        int confirm = QMessageBox::warning(this, "Warning",
                                           "You are about to remove a trucking record.\n"
                                           "Are you sure that you want to do this?",
                                           QMessageBox::Cancel, QMessageBox::Ok);

        if(confirm == QMessageBox::Ok)
        {
            dao.deleteTruckingRecord(truckingList[ui->truckerListBox->currentItem()]);
            populateTruckerList();
            reset();
        }
    }
}

void TruckingDialog::reset()
{
    ui->Qtrucker->setText("");
    ui->Qqty->setText("");
    ui->Qprice->setText("");
    ui->Qunit->setCurrentItem(0);
    newTrucker = true;
    reformatForm();
    ui->Qtrucker->setFocus();
}

