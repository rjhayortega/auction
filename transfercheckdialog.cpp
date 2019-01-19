//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add delete ui;
//   delete moc include at end

#include "transfercheckdialog.h"
#include "ui_transfercheckdialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <Q3ListBox>
#include <qcombobox.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

#include <QInputDialog>
#include "dao/invoicedao.h"


TransferCheckDialog::TransferCheckDialog( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl ), ui(new Ui::TransferCheckDialog)
{
    ui->setupUi(this);
    // signals and slots connections
    connect( ui->writeCheckButton, SIGNAL( clicked() ), this, SLOT( writeCheck() ) );
    connect( ui->colorCombo, SIGNAL( activated(int) ), this, SLOT( populateChargeSummaryList() ) );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
TransferCheckDialog::~TransferCheckDialog()
{
    delete ui;
    delete m_checkPrinter;
    delete m_invoicePrinter;
    delete m_secondCopyPrinter;
}

void TransferCheckDialog::init()
{
    populateChargeSummaryList();
    m_checkPrinter = PrinterDAO().getPrinter(PrinterDAO::Check);
    m_invoicePrinter = PrinterDAO().getPrinter(PrinterDAO::SellerInvoice);
    m_secondCopyPrinter = PrinterDAO().getPrinter(PrinterDAO::SecondCopy);
}

void TransferCheckDialog::populateChargeSummaryList()
{
    AnimalCode::Group colorGroup;

    switch(ui->colorCombo->currentItem())
    {
    case 0:
        colorGroup = AnimalCode::First;
        break;

    case 1:
        colorGroup = AnimalCode::Second;
        break;

    case 2:
        colorGroup = AnimalCode::Third;
        break;

    case 3:
        colorGroup = AnimalCode::Fourth;
        break;

    default:
        colorGroup = AnimalCode::Invalid;
        break;
    }
    summaryList = dao.getChargeSummary(ChargeDAO::Seller, colorGroup);
    vector<ChargeDAO::SUMMARY_ITEM> buyerChargeSummary = dao.getChargeSummary(ChargeDAO::Buyer, colorGroup);
    summaryList.insert(summaryList.end(), buyerChargeSummary.begin(), buyerChargeSummary.end());
    QStringList summaryStringList;

    for(unsigned int i = 0; i < summaryList.size(); i++)
    {
        summaryStringList << QString(" ") + QString::fromStdString(summaryList[i].descrip).leftJustify(20, ' ', true) + ", " + QString::number(summaryList[i].total, 'f', 2);
    }
    ui->chargeSummaryListBox->clear();
    ui->chargeSummaryListBox->insertStringList(summaryStringList);
}


void TransferCheckDialog::writeCheck()
{
    bool ok;
    bool chkOnInvoice = SellerInvoiceDAO().checkOnInvoice();
    unsigned laserCopyCount = SellerInvoiceDAO().laserCopyCount();
    unsigned secondCopyCount = 0;
    bool needSecondCopy = SellerInvoiceDAO().isSecondCopyPrintNeeded();
    if (laserCopyCount > 1 && needSecondCopy) {
        secondCopyCount = laserCopyCount - 1;
        laserCopyCount = 1;
    }

    QString payee = QInputDialog::getText("Payee",
                                          "To Whom Should The Check Be Written?",
                                          QLineEdit::Normal,
                                          QString::null, &ok, this, 0);

    if(ok)
    {
        double amount = 0.000;

        for(unsigned int i = 0; i < summaryList.size(); i++)
        {
            if(ui->chargeSummaryListBox->isSelected(i))
            {
                amount += summaryList[i].total;
                ui->chargeSummaryListBox->setSelected(i, false); // KLN add
            }
        }

        Check check(0, checkDao.getNextCheckNo(), payee.toStdString(), amount, Check::Out, Date::currentDate(), "", Check::Misc);

        int topSkip = SellerInvoiceDAO().checkStart();

        checkDao.saveCheck(check);
        TextCheck textCheck(check, checkDao.getCheckFormat());

        string pad = "";
        string textToPrint;
        LinePrinter printer;

        string checkText = textCheck.text();
        SetupDAO setup;
        if(chkOnInvoice)
        {
            pad = string(topSkip, '\n');
            textToPrint = pad + checkText;
            if(setup.getBoolean("sinvChkOnInvoiceToChkPrinter")) {
                if (m_checkPrinter->isLaser()) {
                    unsigned i = 0;
                    do {
                        m_checkPrinter->print(checkText);
                        i++;
                    } while (i < laserCopyCount);
                    if (needSecondCopy && secondCopyCount > 0) {
                        unsigned i = 0;
                        do {
                            m_secondCopyPrinter->print(checkText);
                            i++;
                        } while (i < secondCopyCount);
                    }
                }
                else  { // dot matrix
                    m_checkPrinter->print(checkText + "\f");
                }
            }
            else // check on invoice printer
            {
                if (m_invoicePrinter->isLaser()) {
                    unsigned i = 0;
                    do {
                        m_invoicePrinter->print(checkText);
                        i++;
                    } while (i < laserCopyCount);
                    if (needSecondCopy && secondCopyCount > 0) {
                        unsigned i = 0;
                        do {
                            m_secondCopyPrinter->print(checkText);
                            i++;
                        } while (i < secondCopyCount);
                    }
                }
                else { // dot matrix
                    m_invoicePrinter->print(checkText + "\f");
                }
            }
        }
        else // KLN separate check printer
        {
//            m_checkPrinter->print(textCheck.getPreSpace() + checkText + "\f",QTextDocument()); // original line
            // KLN mods
            checkText = textCheck.getPreSpace() + textCheck.text();
            if (!m_checkPrinter->isLaser()) {  //Don't add form feed to check end on laser printer.
                checkText += "\f";
                m_checkPrinter->print(checkText);
            } else { // we have a laser printer
                int lineTotal = atoi(setup.get("sinvLinesPerCheck").c_str());
                checkText = m_checkPrinter->adjustCheck(checkText, lineTotal);
            }
            // KLN end mods
        }
    }
}
