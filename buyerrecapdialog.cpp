#include "buyerrecapdialog.h"
#include "previewdialog.h"
#include "types/customer.h"
#include "printerbase.h"
#include <algorithm>
#include <dao/invoicedao.h>
#include <QPrinter>
#include <QMessageBox>

BuyerRecapDialog::BuyerRecapDialog(QWidget *parent) :
    QDialog(parent)
{
    ui.setupUi(this);
    m_reportPrinter = PrinterDAO().getPrinter(PrinterDAO::BuyerInvoice);

    connect( ui.buyerEdit, SIGNAL( returnPressed() ), this , SLOT( addBuyer() ) );
    connect( ui.buyerListBox, SIGNAL( clicked ( const QModelIndex &)),this,
             SLOT( removeBuyer(const QModelIndex & )) );

    connect( ui.allBuyersButton, SIGNAL( clicked() ), this, SLOT( allBuyers() ) );
    connect( ui.generateReportButton, SIGNAL( clicked() ), this, SLOT( generateReport() ) );
    connect( ui.printReportButton, SIGNAL( clicked() ), this, SLOT( printBuyers() ) );
    connect( ui.faxRecapButton, SIGNAL( clicked() ), this, SLOT( faxBuyers() ) );

    bool enableFaxModem = SetupDAO().getBoolean("faxModemEnabled");
    ui.faxRecapButton->setHidden(!enableFaxModem);
    ui.faxRecapButton->setStyleSheet(QString("background-color: #ADFF2F"));

    ui.nameEdit->setFocus();
}

BuyerRecapDialog::~BuyerRecapDialog()
{

}


///////////////////////////////////////////////////////////////////////////////
//
// name: addBuyer()
//
// purpose: adds the user entered buyer number to the list of buyer ids to
//          generate the report
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
void BuyerRecapDialog::addBuyer()
{
    if (! ui.buyerEdit->text().isEmpty()) {
        ui.buyerListBox->addItem(ui.buyerEdit->text());
        ui.buyerEdit->setText("");
        ui.buyerEdit->setFocus();
    }
}

///////////////////////////////////////////////////////////////////////////////
//
// name: removeBuyer(QListBoxItem*)
//
// purpose: removes a buyer id of the list of buyer ids to use to generate the
//          report
//
// calling params: QListBoxItem* item - a pointer to the item to be removed
//                                      from the list
//
// return params: void
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
void BuyerRecapDialog::removeBuyer(const QModelIndex & index)
{
    if (index.isValid()) {
        ui.buyerListBox->takeItem(index.row());
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// name: allBuyers()
//
// purpose: loads all of the buyer ids with the base number into the list of
//          ids to use to generate the report
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
void BuyerRecapDialog::allBuyers()
{
    QString baseBuyer = ui.buyerEdit->text();
    vector<string> numberList = BuyerInvoiceDAO().getNumbersMatching(baseBuyer.toStdString());
    std::sort(numberList.begin(), numberList.end(), Customer::compareCustomerNumbersLT);
    for(unsigned int i = 0; i < numberList.size(); i++)
    {
        ui.buyerListBox->addItem(QString::fromStdString(numberList[i]));
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// name: printBuyers()
//
// purpose: sends a buyer recap of all the user entered ids directly to the
//          report printer
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
void BuyerRecapDialog::printBuyers()
{
    SetupDAO setup;
    vector<string> buyerList;
    setCursor(Qt::WaitCursor);

    for(int i = 0; i < ui.buyerListBox->count(); i++)
    {
        buyerList.push_back(ui.buyerListBox->item(i)->text().toStdString());
    }
    BuyerInvoiceDAO dao;
    if(buyerList.size() > 0)
    {
        vector<ChargeRecord> recapCharges = getBuyerRecapCharges();
        BuyerRecap buyerRecap = dao.getBuyerRecap(buyerList, ui.nameEdit->text().toStdString(),
                                                  ui.consolidateBox->isChecked(),
                                                  recapCharges);
        buyerRecap.setHeader(setup.reportHeader("Buyer Recap", false));
        setCursor(Qt::ArrowCursor);
        buyerRecap.text();
        int pageLength = dao.pageHeight();
        int topSkip = dao.topSkip();
        int copyCount = dao.laserCopyCount();
        buyerRecap.setPageLength((pageLength > 1 ? pageLength : 60));
        deque<string> pageList = buyerRecap.paginatedText(topSkip);
        string text;

        for(unsigned int i = 0; i < pageList.size(); i++)
        {
            text += pageList[i];
            if ( !m_reportPrinter->isLaser() ) {  //Don't add form feed to end on laser printer.
                text += "\f";
            }
        }

        if (m_reportPrinter->isLaser()) {
            PreviewDialog prev;
            prev.setPageHeight(pageLength);
            prev.setTopSkipLines(topSkip);
            QPrinter currentPrinter;
            currentPrinter.setPaperSize(QPrinter::Letter);
            currentPrinter.setPrinterName(m_reportPrinter->printerName());
            QString textToPrint = QString ::fromStdString(text);
            prev.setText(textToPrint);
            prev.printDocument(currentPrinter,copyCount);
        }
        else {
            m_reportPrinter->print(text);
        }
        this->hide();
    }
}

///////////////////////////////////////////////////////////////////////////////
//
// name: generateReport()
//
// purpose: displays a buyer recap of the user entered buyer ids into a preview
//          dialog
//
// calling params: void
//
// return params: void
//
// Notes: The report can be printed from the preview dialog
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
void BuyerRecapDialog::generateReport()
{
    SetupDAO setup;
    vector<string> buyerList;
    setCursor(Qt::WaitCursor);

    for( int i = 0; i < ui.buyerListBox->count(); i++)
    {
        buyerList.push_back(ui.buyerListBox->item(i)->text().toStdString());
    }

    if(buyerList.size() > 0)
    {
        vector<ChargeRecord> recapCharges = getBuyerRecapCharges();
        BuyerRecap buyerRecap =
                BuyerInvoiceDAO().getBuyerRecap(buyerList, ui.nameEdit->text().toStdString(),
                                                ui.consolidateBox->isChecked(), recapCharges);
        buyerRecap.setHeader(setup.reportHeader("Buyer Recap"));
        setCursor(Qt::ArrowCursor);
        PreviewDialog prev;
        prev.setText(QString::fromStdString(buyerRecap.text()));
        prev.setReport(&buyerRecap);
        prev.setShowPrint(true, PrinterDAO::BuyerInvoice);
        prev.exec();

    }
    setCursor(Qt::ArrowCursor);
}


vector<ChargeRecord> BuyerRecapDialog::getBuyerRecapCharges()
{
    vector<ChargeRecord> resultVector;
    for(unsigned int i = 0; i < 10; i++)
    {
        if(ui.extraChargeTable->text(i, 0) != "" || ui.extraChargeTable->text(i, 1) != "")
        {
            resultVector.push_back(
                        ChargeRecord(-(i + 2),ui.extraChargeTable->text(i, 0).toStdString(),
                                     ui.extraChargeTable->text(i, 1).toDouble()));
        }
    }

    return resultVector;
}

void BuyerRecapDialog::faxBuyers()
{

    SetupDAO setup;
    vector<string> buyerList;
    ui.faxRecapButton->setStyleSheet(QString("background-color: #FF0000"));
    ui.faxRecapButton->setDisabled(true);


    for( int i = 0; i < ui.buyerListBox->count(); i++)
    {
        buyerList.push_back(ui.buyerListBox->item(i)->text().toStdString());
    }

    if(buyerList.size() > 0)
    {
        vector<ChargeRecord> recapCharges = getBuyerRecapCharges();
        BuyerRecap buyerRecap =
                BuyerInvoiceDAO().getBuyerRecap(buyerList, ui.nameEdit->text().toStdString(),
                                                ui.consolidateBox->isChecked(), recapCharges);
        buyerRecap.setHeader(setup.reportHeader("Buyer Recap"));
        PreviewDialog prev;
        prev.setText(QString::fromStdString(buyerRecap.text()));
        prev.setReport(&buyerRecap);
        prev.setShowPrint(true, PrinterDAO::BuyerInvoice);

        QDialog sendFaxDlg;
        sendFaxDialog.setupUi(&sendFaxDlg);
        if (sendFaxDlg.exec() == QDialog::Accepted) {
            setCursor(Qt::WaitCursor);
            QPrinter faxPrinter;
            faxPrinter.setPaperSize(QPrinter::Letter);
            faxPrinter.setOutputFileName("fax.pdf");
            prev.printDocument(faxPrinter);

            QStringList convertArgs;
            convertArgs << "fax.pdf" <<  "fax.ps";
            QProcess convertProcess;
            convertProcess.start("pdf2ps", convertArgs);
            if(!convertProcess.waitForStarted()) {
                setCursor(Qt::ArrowCursor);
                QMessageBox::information(this, "Error", "Could not convert FAX output file");
            }
            if(!convertProcess.waitForFinished()) {
                setCursor(Qt::ArrowCursor);
                QMessageBox::information(this, "Error", "Could not convert FAX output file");
            }



            QString faxNumber = sendFaxDialog.lineEdit->text();
            if (faxNumber.isEmpty()) {
                setCursor(Qt::ArrowCursor);
                QMessageBox::information(this, "Error", "Please enter FAX number!");
            }
            else {

                //Prepare Customer name
                string nameString = ui.nameEdit->text().toStdString();
                unsigned int slashIndex = 0;
                if((slashIndex = nameString.find_first_of('/')) != string::npos)
                {
                    string lastName = nameString.substr(0, slashIndex);
                    string firstName = (slashIndex + 1 < nameString.length()? nameString.substr(slashIndex + 1) : "");
                    nameString = firstName + " " + lastName;
                }
                QString marketName = QString::fromStdString(setup.getMarketInfo());
                //

                QProcess faxSendProcess;
                QStringList faxArgs;
                faxArgs << "-r " + QString::fromStdString(nameString)   // "RE:" field on fax cover
                        << "-f " + marketName   // "FROM" field on fax cover
                        << "-d "+ faxNumber << "fax.ps";
                faxSendProcess.start("sendfax",faxArgs);
                if(!faxSendProcess.waitForStarted()) {
                    setCursor(Qt::ArrowCursor);
                    QMessageBox::information(this, "Error", "Could not send FAX");
                }
                if(!faxSendProcess.waitForFinished(300000)) {
                    setCursor(Qt::ArrowCursor);
                    QMessageBox::information(this, "Error", "Could not send FAX");
                }
            }
        }

    }
    ui.faxRecapButton->setStyleSheet(QString("background-color: #ADFF2F"));
    ui.faxRecapButton->setDisabled(false);

    setCursor(Qt::ArrowCursor);
}


