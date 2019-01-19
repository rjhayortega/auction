//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add ui->setupUi(this);
//   Add delete ui;
//   delete moc include at end

#include "checkeditdialog.h"
#include "ui_checkeditdialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qdatetimeedit.h>
#include <qspinbox.h>
#include <qcombobox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

CheckEditDialog::CheckEditDialog( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl ), ui(new Ui::CheckEditDialog)
{
    ui->setupUi(this);
    // signals and slots connections
    connect( ui->buttonOk, SIGNAL( clicked() ), this, SLOT( okPressed() ) );
    connect( ui->buttonCancel, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( ui->lineEditNumAmt, SIGNAL( textChanged(const QString&) ), this, SLOT( setAmountText(const QString&) ) );
    connect( ui->buttonOutst, SIGNAL( clicked() ), this, SLOT( setStatusOutstanding() ) );
    connect( ui->buttonCleared, SIGNAL( clicked() ), this, SLOT( setStatusCleared() ) );
    connect( ui->buttonVoid, SIGNAL( clicked() ), this, SLOT( setStatusVoid() ) );
    connect( ui->printButton, SIGNAL( clicked() ), this, SLOT( printCheck() ) );
    connect( ui->checkNumberSpinBox, SIGNAL( valueChanged(int) ), this, SLOT( updateCheckNumber(int) ) );

    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CheckEditDialog::~CheckEditDialog()
{
    delete ui;
    delete m_checkPrinter;
    delete m_invoicePrinter;
    delete m_secondCopyPrinter;
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
// Notes: newCheck is a class variable that should be set by init(Check, bool)
//        when creating a dialog from this class. The newCheck variable is
//        a flag that determines which information can be changed in the
//        database by this dialog
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
void CheckEditDialog::init()
{
    newCheck = false;

    m_checkPrinter = PrinterDAO().getPrinter(PrinterDAO::Check);
    m_invoicePrinter = PrinterDAO().getPrinter(PrinterDAO::SellerInvoice);
    m_secondCopyPrinter = PrinterDAO().getPrinter(PrinterDAO::SecondCopy);
}



///////////////////////////////////////////////////////////////////////////////
//
// name:    init(Check, bool)
//
// purpose: initializes the data members of this dialog
//
// calling params: Check check    - The check that this dialog will edit
//                 bool  newCheck - Determines if data other than the status
//                                  can be saved in the database for this check
//
// return params:
//
// Notes: if newCheck == true then this check has not been printed and
//        information other than the status can be saved for this check
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void CheckEditDialog::init(Check check, bool newCheck)
{
    this->check = check;
    this->newCheck = newCheck;
//  textLabelChkNum->setText(QString::number(check.getNumber()));
    blockSignal = true;
    ui->checkNumberSpinBox->setValue(check.getNumber());
    blockSignal = false;

    ui->lineEditPayTo->setText(QString::fromStdString(check.getPayee()));
    ui->lineEditNumAmt->setText(QString::number(check.getAmount(), 'f', 2));
    ui->lineEditChkMemo->setText(QString::fromStdString(check.getComment()));
    Date date = check.getDate();
    ui->chkDate->setDate(QDate(date.getYear(), date.getMonth(), date.getDay()));

    int typeMap[] = {0, 1, 2, 3, 0};
    ui->checkTypeCombo->setCurrentItem(int(typeMap[check.getType()]));
}



///////////////////////////////////////////////////////////////////////////////
//
// name: updateCheckNumber(int number)
//
// purpose: changes the number of the current check in the database to 'number'
//
// calling params: int number
//
// return params: void
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
void CheckEditDialog::updateCheckNumber(int number)
{
    if(blockSignal)
    {
        return;
    }

    dao.deleteCheck(check);
    check.setNumber(number);
    dao.saveCheck(check);
}


///////////////////////////////////////////////////////////////////////////////
//
// name: setCheckType()
//
// purpose: sets the type of the check
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
void CheckEditDialog::setCheckType()
{

    Check::Type type = Check::Misc;

    if(ui->checkTypeCombo->currentText() == "Invoice")
    {
        if(check.getInvoiceId() == 0)
        {
            QMessageBox::information(this, "Warning",
                                     "This check was not created by a seller invoice, and will not "
                                     "be associated with a seller, so it will not be automatically "
                                     "voided if another check is printed for this seller.",
                                     QMessageBox::Ok);
        }
        type = Check::Invoice;
    }
    else if(ui->checkTypeCombo->currentText() == "Trucker")
    {
        type = Check::Trucker;
    }
    else if(ui->checkTypeCombo->currentText() == "Buyer")
    {
        type = Check::Buyer;
    }

    check.setType(type);

}

///////////////////////////////////////////////////////////////////////////////
//
// name:    setAmountText(const QString &numAmount)
//
// purpose: Sets the text of the Textual Amount Line Edit from the check object
//
// calling params: const QString &numAmount - a string representing the the
//                                            numerical dollar amount of the
//                                            check
//
// return params:
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void CheckEditDialog::setAmountText(const QString &numAmount)
{
    ui->lineEditTxtAmt->setText(QString::fromStdString(Check(0, 0, "", numAmount.toDouble()).getTextAmount()));
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    setStatusCleared()
//
// purpose: sets the status of the check in the database to cleared
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

void CheckEditDialog::setStatusCleared()
{
    check.setStatus(Check::Cleared);
    saveCheck();

    QDialog::accept();
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    setStatusVoid()
//
// purpose: sets the status of the current check in to void in the database
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

void CheckEditDialog::setStatusVoid()
{
    check.setStatus(Check::Void);
    saveCheck();

    QDialog::accept();
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    setStatusOutstanding()
//
// purpose: sets the status of the current check to Outstanding in the database
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

void CheckEditDialog::setStatusOutstanding()
{
    check.setStatus(Check::Out);
    saveCheck();
    QDialog::accept();
}



///////////////////////////////////////////////////////////////////////////////
//
// name:    okPressed()
//
// purpose: closes the dialog and returns control to the originator, saving and
//          printing the check if the check has not been printed
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

void CheckEditDialog::okPressed()
{

    saveCheck();

    QDialog::accept();
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    saveCheck()
//
// purpose: saves the current check to the database
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

void CheckEditDialog::saveCheck()
{
    dao.deleteCheck(check);
    QDate date = ui->chkDate->date();
    check.setPayee(ui->lineEditPayTo->text().toStdString());
    check.setDate(Date(date.day(), date.month(), date.year()));
    check.setAmount(ui->lineEditNumAmt->text().toDouble());
    check.setComment(ui->lineEditChkMemo->text().toStdString());
    setCheckType();

    dao.saveCheck(check);
}



///////////////////////////////////////////////////////////////////////////////
//
// name: printCheck()
//
// purpose: prints the current check
//
// calling params: void
//
// return params: void
//
// Notes: after the check has been sent to the printer, the dialog is closed
//        with an 'Accepted' status
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
void CheckEditDialog::printCheck()
{
    unsigned topSkip = invoiceDao.checkStart();
    bool chkOnInvoice = invoiceDao.checkOnInvoice();
    unsigned laserCopyCount = invoiceDao.laserCopyCount();
    unsigned secondCopyCount = 0;
    bool needSecondCopy = invoiceDao.isSecondCopyPrintNeeded();
    if (laserCopyCount > 1 && needSecondCopy) {
        secondCopyCount = laserCopyCount - 1;
        laserCopyCount = 1;
    }

    dao.setNextCheck(check.getNumber() + 1);
    saveCheck();
    TextCheck textCheck(check, dao.getCheckFormat());

    string pad = "";
    LinePrinter printer;

    string checkText = textCheck.text();
    SetupDAO setup;

    if(chkOnInvoice)
    {
        pad = string(topSkip, '\n');

        if(setup.getBoolean("sinvChkOnInvoiceToChkPrinter"))
        {
            if (m_checkPrinter->isLaser()) {
                unsigned i = 0;
                do {
                    m_checkPrinter->print(pad + checkText + "\f");
                    i++;
                } while (i < laserCopyCount);
                if (needSecondCopy && secondCopyCount > 0) {
                    unsigned i = 0;
                    do {
                        m_secondCopyPrinter->print(pad + checkText + "\f");
                        i++;
                    } while (i < secondCopyCount);
                }
            }
            else  { // dot matrix
                m_checkPrinter->print(pad + checkText + "\f");
            }
        }
        else // check on invoice printer
        {
            if (m_invoicePrinter->isLaser()){
                unsigned i = 0;
                do {
                    m_invoicePrinter->print(pad + checkText + "\f");
                    i++;
                } while (i < laserCopyCount);
                if (needSecondCopy && secondCopyCount > 0) {
                    unsigned i = 0;
                    do {
                        m_secondCopyPrinter->print(pad + checkText + "\f");
                        i++;
                    } while (i < secondCopyCount);
                }
            }
            else {
                m_invoicePrinter->print(pad + checkText + "\f");
            }
        }
    }
    else // separate check printer
    {
        //        m_checkPrinter->print(checkText + "\f");
        if (m_checkPrinter->isLaser()) // No form feed on check end on laser printer.
        {
            int lineTotal = atoi(setup.get("sinvLinesPerCheck").c_str());
            checkText = m_checkPrinter->adjustCheck(checkText, lineTotal); // this prints checks, too, on laser only
        }
        if (!m_checkPrinter->isLaser()) {
            m_checkPrinter->print(pad + checkText + "\f");
        }
    }

    QDialog::accept();
}

///////////////////////////////////////////////////////////////////////////////
//
// name:    reject()
//
// purpose: Overrides the QDialog::reject() function
//
// calling params:
//
// return params:
//
// Notes: if the check has not been printed, it is deleted from the database
//        and the check number is rolled back in the database
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void CheckEditDialog::reject()
{
    if(newCheck)
    {
        dao.deleteCheck(check);
        dao.setNextCheck(check.getNumber());
    }
    QDialog::reject();
}

