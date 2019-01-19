//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add ui->setupUi(this);
//   Add delete ui;
//   delete moc include at end

#include "depositeditdialog.h"
#include "ui_depositeditdialog.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qdatetimeedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

DepositEditDialog::DepositEditDialog( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl ), ui(new Ui::DepositEditDialog)
{
    ui->setupUi(this);
    // signals and slots connections
    connect( ui->buttonOk, SIGNAL( clicked() ), this, SLOT( saveDeposit() ) );
    connect( ui->buttonCancel, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( ui->buttonVoid, SIGNAL( clicked() ), this, SLOT( saveVoided() ) );
    connect( ui->buttonCleared, SIGNAL( clicked() ), this, SLOT( saveCleared() ) );
    connect( ui->buttonOutst, SIGNAL( clicked() ), this, SLOT( saveOutstanding() ) );

    init();
}

DepositEditDialog::~DepositEditDialog()
{
    delete ui;
}



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
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void DepositEditDialog::init()
{
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    init(Deposit deposit)
//
// purpose: sets the deposit object of this dialog
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

void DepositEditDialog::init(Deposit deposit)
{
    this->deposit = deposit;
    Date date = deposit.getDate();
    ui->depositDate->setDate(QDate(date.getYear(), date.getMonth(), date.getDay()));
    ui->lineEditAmt->setText(QString::number(deposit.getAmount(), 'f', 2));
    ui->lineEditMemo->setText(QString::fromStdString(deposit.getComment()));
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    saveCleared()
//
// purpose: saves the deposit with a cleared status
//
// calling params:
//
// return params:
//
// Notes: causes the dialog to be accepted
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void DepositEditDialog::saveCleared()
{
    deposit.setStatus(Deposit::Cleared);
    saveDeposit();
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    saveOutstanding()
//
// purpose: saves the deposit with a outstanding status
//
// calling params:
//
// return params:
//
// Notes: causes the dialog to be accepted
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void DepositEditDialog::saveOutstanding()
{
    deposit.setStatus(Deposit::Out);
    saveDeposit();
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    saveVoided()
//
// purpose: saves the deposit with a void status
//
// calling params:
//
// return params:
//
// Notes: causes the dialog to be accepted
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void DepositEditDialog::saveVoided()
{
    deposit.setStatus(Deposit::Void);
    saveDeposit();
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    saveDeposit()
//
// purpose: saves the deposit
//
// calling params:
//
// return params:
//
// Notes: accepts the dialog
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void DepositEditDialog::saveDeposit()
{
    QDate date = ui->depositDate->date();
    deposit.setDate(Date(date.day(), date.month(), date.year()));
    deposit.setAmount(ui->lineEditAmt->text().toDouble());
    deposit.setComment(ui->lineEditMemo->text().toStdString());
    dao.saveDeposit(deposit);
    QDialog::accept();
}
