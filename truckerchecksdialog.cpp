//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add delete ui;
//   delete moc include at end

#include "truckerchecksdialog.h"
#include "ui_truckerchecksdialog.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <Q3ListBox>
#include <qcheckbox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>
#include "previewdialog.h"
#include <QPrinter>

TruckerChecksDialog::TruckerChecksDialog( QWidget* parent)
    : QDialog( parent), ui(new Ui::TruckerChecksDialog)
{
    ui->setupUi(this);
    // signals and slots connections
    connect( ui->cancelButton, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( ui->printButton, SIGNAL( clicked() ), this, SLOT( printChecks() ) );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
TruckerChecksDialog::~TruckerChecksDialog()
{
    delete ui;
    delete m_checkPrinter;
    delete m_reportPrinter;
    delete m_invoicePrinter;
    delete m_secondCopyPrinter;
}

#include "dao/printerdao.h"

void TruckerChecksDialog::init()
{
    populateTruckerList();
    m_checkPrinter = PrinterDAO().getPrinter(PrinterDAO::Check);
    m_reportPrinter = PrinterDAO().getPrinter(PrinterDAO::Report);
    m_invoicePrinter = PrinterDAO().getPrinter(PrinterDAO::SellerInvoice);
    m_secondCopyPrinter = PrinterDAO().getPrinter(PrinterDAO::SecondCopy);
}

void TruckerChecksDialog::populateTruckerList()
{
    // [KLN] add
    ui->sellerTruckerList->setMultiSelection(true);
    ui->buyerTruckerList->setMultiSelection(true);
    // [KLN] add end
    populateTruckerList(ui->sellerTruckerList, sellerTruckingList, Customer::Seller);
    populateTruckerList(ui->buyerTruckerList, buyerTruckingList, Customer::Buyer);
}

void TruckerChecksDialog::populateTruckerList(Q3ListBox* truckerList, vector<TruckingRecord>& truckingList, Customer::Type customerType)
{
    truckingList = truckingDao.getTruckingRecordList(customerType);

    std::sort(truckingList.begin(), truckingList.end(), TruckingRecord::compareTruckerNamesLT);
    QStringList truckingStringList;

    for(unsigned int i = 0; i < truckingList.size(); i++)
    {
        QString checkNoStr = (truckingList[i].getCheckNo() > 0 ? QString("(") + QString::number(truckingList[i].getCheckNo()) + ")" : QString(""));
        truckingStringList += QString(checkNoStr + QString::fromStdString(truckingList[i].getTruckerName())).leftJustify(25, ' ', true) + " " +  QString::number(truckingList[i].amount(), 'f', 2).rightJustify(10, ' ', false);;
    }
    truckerList->clear();
    truckerList->insertStringList(truckingStringList);
}

void TruckerChecksDialog::printChecks()
{
    printChecks(ui->sellerTruckerList, sellerTruckingList);
    printChecks(ui->buyerTruckerList, buyerTruckingList);
    populateTruckerList();
}

void TruckerChecksDialog::printChecks(Q3ListBox* truckerList, vector<TruckingRecord>truckingList)
{
    vector<TruckerCheckReport::TruckerRecord> recordList;
    vector<TruckerCheckReport::TruckerRecord>::iterator truckerLoc;
    double cwt = 0.0000;
    double amount = 0.0000;
    Invoice invoice;
    long checkNo;
    bool chkOnInvoice = setupInvoiceDao.checkOnInvoice();
    unsigned laserCopyCount = setupInvoiceDao.laserCopyCount();
    unsigned secondCopyCount = 0;
    bool needSecondCopy = setupInvoiceDao.isSecondCopyPrintNeeded();
    if (laserCopyCount > 1 && needSecondCopy) {
        secondCopyCount = laserCopyCount - 1;
        laserCopyCount = 1;
    }

//    unsigned laserCopyCount = setupInvoiceDao.laserCopyCount();

    for(int i = 0 ; i < truckerList->numRows(); i++)
    {
        qDebug(" printChecks i: " + i);
//        cout << " printChecks i: " << i << endl; // [KLN] add
        if(truckerList->item(i)->isSelected())
        {
            qDebug("    selected");
            invoice = getInvoice(truckingList[i].getConsignerNo(), truckingList[i].getConsignerType());
            cwt = invoice.cwt();

            amount = truckingList[i].amount();
            TruckerCheckReport::TruckerCheckRecord record(truckingList[i], invoice.getCustomer().getNumber(), invoice.getCustomer().getName().getLast(), 0);

            if((truckerLoc = std::find(recordList.begin(), recordList.end(), truckingList[i].getTruckerName())) == recordList.end())
            {
                checkNo = checkDao.getNextCheckNo();
                qDebug("    (mult) checkNo: " + checkNo);
                Check check(0, checkNo, truckingList[i].getTruckerName(), amount);
                recordList.push_back(TruckerCheckReport::TruckerRecord(check, record));
            }
            else
            {
                checkNo = truckerLoc->getCheck().getNumber();
                qDebug("    (sngl) checkNo: " + checkNo);
                truckerLoc->setCheckAmount(truckerLoc->getCheck().getAmount() + amount);
                truckerLoc->addRecord(record);
            }

            truckingList[i].setCheckNo(checkNo);
            Customer temp;

            temp.setNumber(truckingList[i].getConsignerNo());
            truckingDao.saveTruckingRecord(truckingList[i],temp, ChargeDAO::CUST_TYPE(truckingList[i].getConsignerType()));
        }
    }

    string checkText = "";
    string reportText = "";
    string mixedText = "";
    SellerInvoiceDAO invoiceDao;
    QString laserReportText;
    QStringList checkTxtList;
    QStringList reportsList;

    unsigned int skipLine = invoiceDao.topSkip();
    unsigned int pageLen= invoiceDao.pageHeight();
    unsigned int firstCheckLine = invoiceDao.checkStart();
    deque<string> reportPages;

    for(unsigned int i = 0; i < recordList.size(); i++)
    {
        Check check = recordList[i].getCheck();
        check.setType(Check::Trucker);
        checkDao.saveCheck(check);
        TruckerCheckReport report(recordList[i]);
        report.setHeader(setup.reportHeader("T R U C K E R     R E P O R T", false));
        report.setPageLength(pageLen);
        string temp;

//        if(invoiceDao.checkOnInvoice())
        if(chkOnInvoice)

        {
            laserReportText = QString::fromStdString(report.text());

            reportPages = report.paginatedText(skipLine);
            TextCheck textCheck(check, checkDao.getCheckFormat());
            checkTxtList << QString::fromStdString(textCheck.text());


            if(reportPages.size() > 0)
            {
                if(ui->reportCheckBox->isChecked())
                {
                    // Page for laser printer
                    reportsList << laserReportText;
                    int actualPageLength = QString::fromStdString(reportPages[0]).count("\n");
                    temp = string(firstCheckLine - actualPageLength, '\n') +  textCheck.text();
                    mixedText += reportPages[0] + temp + getFormFeed(i, recordList.size());
                }
                else
                {
//                    reportsList << QString::fromStdString(string(firstCheckLine-skipLine, '\n'));
                    reportsList << "";
                    temp.clear();
                    temp = string(firstCheckLine, '\n') + textCheck.text();
//                    cout << "temp: [" << temp << "]" << endl; // KLN
                    mixedText += temp + "\f";
                }
            }
        }

        else // KLN separate check printer
        {
            TextCheck txtCheck(check, checkDao.getCheckFormat());

            checkTxtList << QString::fromStdString(txtCheck.text());
            reportsList  << QString::fromStdString(report.text());

//            cout << "  (printChecks)[1] checkText: <<<" << checkText << ">>>" << endl;
//            checkText += txtCheck.getPreSpace() + txtCheck.text() + "\f"; // original line
            // KLN mods
            checkText += txtCheck.getPreSpace() + txtCheck.text();
//            cout << "  (printChecks)[2] checkText: <<<" << checkText << ">>>" << endl;
            if (!m_checkPrinter->isLaser()) {  //Don't add form feed to check end on laser printer.
                checkText += "\f";
            } else { // we have a laser printer
                int lineTotal = atoi(setup.get("sinvLinesPerCheck").c_str());
                m_checkPrinter->adjustCheck(checkText, lineTotal, false);
                checkText = "";
            }
            // KLN end mods
            reportText += report.text() + getFormFeed(i, recordList.size());
        }
    }

    if(chkOnInvoice)
    {
        if(setup.getBoolean("sinvChkOnInvoiceToChkPrinter"))
        {
            if (m_checkPrinter->isLaser()) {
                unsigned i = 0;
                do {
                    m_checkPrinter->print(mixedText);
                    i++;
                } while (i < laserCopyCount);
                if (needSecondCopy && secondCopyCount > 0) {
                    unsigned i = 0;
                    do {
                        m_secondCopyPrinter->print(mixedText);
                        i++;
                    } while (i < secondCopyCount);
                }
            }
//                printLaserReportWithCheck(*m_checkPrinter, checkTxtList, reportsList);
//            }
            else {
                m_checkPrinter->print(mixedText);
            }
        }
        else // check on invoice printer
        {
            if (m_invoicePrinter->isLaser()) {
                unsigned i = 0;
                do {
                    m_invoicePrinter->print(mixedText);
                    i++;
                } while (i < laserCopyCount);
                if (needSecondCopy && secondCopyCount > 0) {
                    unsigned i = 0;
                    do {
                        m_secondCopyPrinter->print(mixedText);
                        i++;
                    } while (i < secondCopyCount);
                }
//                printLaserReportWithCheck(*m_invoicePrinter, checkTxtList, reportsList);
            }
            else {
                m_invoicePrinter->print(mixedText);
            }
        }
    }
    else // separate check printer
    {
        if ( m_checkPrinter->isLaser()  ) {
            // KLN mods
            // was printed above, in "adjustCheck" routine
//            QStringList emptyList;
//            emptyList << QString::fromStdString(string(firstCheckLine-skipLine, '\n'));
//            printLaserReportWithCheck(*m_checkPrinter, checkTxtList, emptyList);
            // KLN end mods
        }
        else {  //Matrix print ( as before )
            m_checkPrinter->print(checkText);
        }

        if(ui->reportCheckBox->isChecked())
        {
            m_reportPrinter->print(reportText);
//            if ( m_reportPrinter->isLaser() ) {
//                m_reportPrinter->print(reportText);
////                QStringList emptyCheckList;
////                printLaserReportWithCheck(*m_reportPrinter, emptyCheckList, reportsList);
//            }
//            else { //Matrix print ( as before )
//                m_reportPrinter->print(reportText);
//            }
        }
    }
}

Invoice TruckerChecksDialog::getInvoice(string consignerNo, Customer::Type consignerType)
{
    Invoice tempInv;

    switch(consignerType)
    {
    case Customer::Seller:
        tempInv = *(sinvDao.getInvoiceByCustomer(consignerNo));
        sinvDao.freeInvoice();
        break;

    case Customer::Buyer:
        tempInv = *(binvDao.getInvoiceByCustomer(consignerNo));
        binvDao.freeInvoice();
        break;
    }

    return tempInv;
}


void TruckerChecksDialog::printLaserReportWithCheck(PrinterBase &printer, QStringList &checkTextList, QStringList &reportText)
{
    // [KLN] add
//    cout << "reportText: " << reportText.size() << endl;
//    cout << "checkTest: " << checkTextList.size() << endl;
    // [KLN] add end

    for (int i = 0 ; i < reportText.size(); i++) {
        SellerInvoiceDAO invoiceDao;
        PreviewDialog prev;
        unsigned int topSkip =  invoiceDao.topSkip();
        unsigned int pageHeight = invoiceDao.pageHeight();
        unsigned int firstCheckLine = invoiceDao.checkStart();

        prev.setPageHeight(pageHeight);
        prev.setTopSkipLines(topSkip);
        prev.setText(reportText[i]);
        // [KLN] add
//        cout << "   reportText[" << i << "]: " << reportText[i].toStdString() << endl;
        // [KLN] add end



        QPrinter currentPrinter;
        currentPrinter.setPaperSize(QPrinter::Letter);
        currentPrinter.setPrinterName(printer.printerName());

        QStringList currentCheck;

        if (checkTextList.size() > 0) {
            // [KLN] add
//            cout << "   checkText[" << i << "]: " << checkTextList[i].toStdString() << endl;
            // [KLN] add end


            prev.setCheckStartLine(firstCheckLine);
            prev.setCheckPrint(true);

            currentCheck << checkTextList[i];
            prev.setCheckTextList(currentCheck);
        }

        unsigned copies = 1;
        unsigned laserCopyCount = invoiceDao.laserCopyCount();
        if (laserCopyCount > 1) copies = laserCopyCount;
        prev.printDocument(currentPrinter,copies);
    }
}

string TruckerChecksDialog::getFormFeed(int i, int listSize) {
  string result = "\f";
  bool chkOnInv = false;
  bool isLaser = false;

  if (setupInvoiceDao.checkOnInvoice()) {
      chkOnInv = true;
    }

  if ( setup.getBoolean("sinvChkOnInvoiceToChkPrinter") && m_checkPrinter->isLaser() ) {
      isLaser = true;
    } else {
      if (chkOnInv && m_invoicePrinter->isLaser()) {
          isLaser = true;
        } else {
          if (!chkOnInv && m_reportPrinter->isLaser()) {
              isLaser = true;
            }
        }
    }

  if ( i == 0 ) {
      // first page
      if (isLaser) {
          result = "\f\f";
        }
    }

  if ( (i+1) == listSize ) {
      // last page
      if (isLaser) {
          result = "";
        }
    }

  return result;
}

