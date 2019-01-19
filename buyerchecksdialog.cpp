//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add ui->setupUi(this);
//   Add delete ui;
//   delete moc include at end

#include "buyerchecksdialog.h"
#include "ui_buyerchecksdialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <Q3ListBox>
#include <qcheckbox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>
#include <QDebug>

BuyerChecksDialog::BuyerChecksDialog(QWidget* parent )
    : QDialog( parent), ui(new Ui::BuyerChecksDialog)
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
BuyerChecksDialog::~BuyerChecksDialog()
{
    delete ui;
    delete m_checkPrinter;
    delete m_reportPrinter;
    delete m_invoicePrinter;
    delete m_secondCopyPrinter;

}

#include "reports/buyercheckreport.h"
#include <qprogressdialog.h>

///////////////////////////////////////////////////////////////////////////////
//
// name: init()
//
// purpose: sets up the printers and fills the list with the current available
//          buyer commissions
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
void BuyerChecksDialog::init()
{
    m_checkPrinter = PrinterDAO().getPrinter(PrinterDAO::Check);
    m_reportPrinter = PrinterDAO().getPrinter(PrinterDAO::Report);
    m_invoicePrinter = PrinterDAO().getPrinter(PrinterDAO::SellerInvoice);
    m_secondCopyPrinter = PrinterDAO().getPrinter(PrinterDAO::SecondCopy);
    populateBuyerChecksList();
}


///////////////////////////////////////////////////////////////////////////////
//
// name: populateBuyerChecksList()
//
// purpose: loads the list with buyer commissions from the database
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
void BuyerChecksDialog::populateBuyerChecksList()
{
    vector<string> buyerIdList = commDao.getCommissionedBuyerIdList();
    QProgressDialog progressDialog("Loading Buyers", QString::null, 0, buyerIdList.size(), this);
    progressDialog.setModal(true);
    progressDialog.show();
    QStringList displayList;
    buyerInvoiceList.clear(); // [KLN] add

    for(unsigned int i = 0; i < buyerIdList.size(); i++)
    {
        progressDialog.setValue(i);
        buyerInvoiceList.push_back(*(binvDao.getInvoiceByCustomer(buyerIdList[i])));
        binvDao.freeInvoice();
    }
    std::sort(buyerInvoiceList.begin(), buyerInvoiceList.end(), BuyerInvoice::compareInvoiceCustomerNamesLT);
    CommissionBreak::BuyerMode mode;
    double amount;
    string displayName;
    for(unsigned int i = 0; i < buyerInvoiceList.size(); i++)
    {
        commDao.getBuyerCommissionData(mode, amount, buyerInvoiceList[i].getCustomer().getNumber());
        displayName = buyerInvoiceList[i].getCustomer().getName().getLast();

        if(int(mode) > 2)
        {
            displayName = buyerInvoiceList[i].getCustomer().getCompany();
        }

        QString item = QString(QString("(") \
                + QString::number(commDao.getBuyerCheckNo(buyerInvoiceList[i].getCustomer().getNumber())) \
                + ")" + QString::fromStdString(displayName)).leftJustify(30, ' ', true) \
                + " " + QString::number(buyerInvoiceList[i].getCommissionTotal(), 'f', 2);

        displayList += item;

        //        displayList += QString(QString("(") + QString::number(commDao.getBuyerCheckNo(buyerInvoiceList[i].getCustomer().getNumber())) + ")" + QString::fromStdString(displayName)).leftJustify(30, ' ', true) + " " + QString::number(buyerInvoiceList[i].getCommissionTotal(), 'f', 2);
    }

    ui->buyerList->clear();
    ui->buyerList->setMultiSelection(true); // [KLN]
    ui->buyerList->insertStringList(displayList);
    progressDialog.hide();
}

///////////////////////////////////////////////////////////////////////////////
//
// name: printChecks()
//
// purpose: writes checks to the selected buyer commissions
//
// calling params: void
//
// return params: void
//
// Notes: unless specified otherwise by the user, this also prints out a
//        report
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
void BuyerChecksDialog::printChecks()
{
    vector<BuyerCheckReport::BuyerRecord> recordList;
    vector<BuyerCheckReport::BuyerRecord>::iterator buyerLoc;
    string name, company;
    double amount;
    CommissionBreak::BuyerMode mode;
    string number;
    string payee;

    for(int i = 0; i < ui->buyerList->numRows(); i++)
    {
        commDao.getBuyerCommissionData(mode, amount, buyerInvoiceList[i].getCustomer().getNumber());
        name = buyerInvoiceList[i].getCustomer().getName().getLast();
        company = buyerInvoiceList[i].getCustomer().getCompany();
        amount = buyerInvoiceList[i].getCommissionTotal();
        number = buyerInvoiceList[i].getCustomer().getNumber();

        payee = name;

        if(mode > 2)
        {
            payee = company;
        }

        if(ui->buyerList->isSelected(i))
        {
            if((buyerLoc = std::find(recordList.begin(), recordList.end(), payee)) == recordList.end())
            {
                recordList.push_back(BuyerCheckReport::BuyerRecord(
                                         Check(0, 0, payee, amount),
                                         BuyerCheckReport::BuyerCommissionRecord(name, company, amount, number)));
            }
            else
            {
                buyerLoc->setCheckAmount(buyerLoc->getCheck().getAmount() + amount);
                buyerLoc->addCommissionRecord(BuyerCheckReport::BuyerCommissionRecord(name, company, amount, number));
            }
        }
    }

    string checkText = "";
    string reportText = "";
    unsigned topSkip = setupInvoiceDao.topSkip();
    unsigned pageLength = setupInvoiceDao.pageHeight();
    unsigned firstCheckLine = setupInvoiceDao.checkStart();
    string mixedPage;
    string mixedText;
    string checkPage;
    string reportPage;
    deque<string> reportPageList;

    bool chkOnInvoice = setupInvoiceDao.checkOnInvoice();
    unsigned laserCopyCount = setupInvoiceDao.laserCopyCount();
    unsigned secondCopyCount = 0;
    bool needSecondCopy = setupInvoiceDao.isSecondCopyPrintNeeded();
    if (laserCopyCount > 1 && needSecondCopy) {
        secondCopyCount = laserCopyCount - 1;
        laserCopyCount = 1;
    }

    mixedText = ""; // [KLN] add
    int lineTotal = atoi(setup.get("sinvLinesPerCheck").c_str());

    for(unsigned int i = 0; i < recordList.size(); i++)
    {
        mixedPage = "";
        //        // [KLN] add
        //        cout << "i = " << i << " -- recordList.size = " << recordList.size() << endl;
        //        // [KLN] add end

        // we need to know the correct check number, before printing the actual report
        // since we won't know the actual check number until after the report is printed, create
        // a report with a fake check number of 0 first // KLN -- WHY? we just need to read next check number...

        TextCheck txtCheck(recordList[i].getCheck(), checkDao.getCheckFormat());
        checkPage = txtCheck.text();
        BuyerCheckReport report(recordList[i]);
        report.setPageLength(pageLength);
        reportPage = report.text();
        reportPageList = report.paginatedText(topSkip);

        long nextCheckNo = checkDao.peekAtNextCheckNo() + (reportPageList.size() - 1);

        Check check = recordList[i].getCheck();
        check.setType(Check::Buyer);
        check.setNumber(nextCheckNo);
        recordList[i].setCheck(check);

        // regenerate the report with the correct check No.

        report = BuyerCheckReport(recordList[i]);
        report.setPageLength(pageLength);
        reportPage = report.text();
        reportPageList = report.paginatedText(topSkip);

        reportText += reportPage + getFormFeed(i, recordList.size(), true); // true = report
        // [KLN] add
        //        cout << "i = " << i << " -- recordList.size = " << recordList.size() << endl;
        // [KLN] add end
        checkText += fixLaserCheckFormat(checkPage, lineTotal, i, recordList.size());
        //        checkText += txtCheck.getPreSpace() + checkPage; // + "\f";
        //        checkText += (chkOnInvoice ? "" : txtCheck.getPreSpace()) + checkPage + "\f";

        string voidCheckPage;

        for(unsigned int j = 0; j < reportPageList.size(); j++)
        {
            voidCheckPage = "";
            if(j != reportPageList.size() - 1)
            {
                voidCheckPage = TextCheck(Check(0,checkDao.getNextCheckNo(), "VOID", 0.00), checkDao.getCheckFormat()).text();
            }
            qDebug()<< QString::fromStdString(reportPageList[j]);
            int curPageLen = QString::fromStdString(reportPageList[j]).count("\n") + topSkip;

            if(ui->reportCheckBox->isChecked())
            {
                string pad = (firstCheckLine > curPageLen ? string(firstCheckLine - curPageLen, '\n') : string(""));
                mixedPage = string(topSkip, '\n') + reportPageList[j] + pad + (voidCheckPage.length() == 0 ? checkPage : voidCheckPage);
            }
            else
            {
                string pad = string(firstCheckLine, '\n');
                mixedPage = pad + checkPage;
                j = reportPageList.size();
            }
            // [KLN] add
            //            cout << "i / j = " << i << " / " << j << " -- reportPageList.size = " << reportPageList.size() << " -- recordList.size = " << recordList.size() << endl;
            // [KLN] add end

            mixedText += mixedPage + getFormFeed(i, recordList.size(), false);

        }
        // update the check number here (we set it before the page loop)
        checkDao.getNextCheckNo();

        report.setHeader(setup.reportHeader("BUYER DETAIL REPORT"));
        string pad = "";


        //	Check check = recordList[i].getCheck();
        //	check.setType(Check::Buyer);
        //	check.setNumber(checkDao.getNextCheckNo());

        vector<BuyerCheckReport::BuyerCommissionRecord> commissionList = recordList[i].getCommissionList();

        for(unsigned int j = 0; j < commissionList.size(); j++)
        {
            commDao.setBuyerCheckNo(commissionList[j].number, check.getNumber());
        }

        checkDao.saveCheck(check);
    }

    if(chkOnInvoice)
    {
        // [KLN] add
        //         cout << "checkOnInvoice" << endl;
        //         freopen ("/tmp/mixed-text.txt","w",stdout);
        //         cout << mixedText;
        //         fclose (stdout);
        // [KLN] add end


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
            } // dot matrix
            else  {
                m_checkPrinter->print(mixedText);
            }
        }
        else // check on invoice printer
        {
            if (m_invoicePrinter->isLaser()){
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
            }
            else {
                m_invoicePrinter->print(mixedText);
            }
        }
    }
    else // separate check printer
    {
        // [KLN] add
        //            cout << "separate check printer" << endl;
        //            freopen ("/tmp/check-text.txt","w",stdout);
        //            cout << checkText;
        //            fclose (stdout);
        // [KLN] add end

        //        m_checkPrinter->print(checkText + "\f");
        if (m_checkPrinter->isLaser()) {  // No form feed on check end on laser printer.
            int lineTotal = atoi(setup.get("sinvLinesPerCheck").c_str());
            checkText = m_checkPrinter->adjustCheck(checkText, lineTotal); // this prints checks, too, on laser only
        } else { // dot matrix
            m_checkPrinter->print(checkText + "\f");
        }

        if(ui->reportCheckBox->isChecked())
        {
            m_reportPrinter->print(reportText);
        }

        // [KLN] add
        //        cout << "separate check printer" << endl;
        //        freopen ("/tmp/check-text.txt","w",stdout);
        //        cout << checkText;
        //        fclose (stdout);
        //        freopen ("/tmp/report-text.txt","w",stdout);
        //        cout << reportText;
        //        fclose (stdout);
        // [KLN] add end

    }

    populateBuyerChecksList(); // [KLN] add (this clears selections on screen like in Trucker Checks
}

string BuyerChecksDialog::getFormFeed(int i, int listSize, bool isReport) {
  string result = "\f";
  bool chkOnInv = false;
  bool isLaser = false;

//  cout << "i = " << i << " -- listSize = " << listSize << endl;

  if (setupInvoiceDao.checkOnInvoice()) {
      chkOnInv = true;
    }

  if (isReport) {
      if (m_reportPrinter->isLaser()) {
            isLaser = true;
          }
    }
  else { // is check
      if ( setup.getBoolean("sinvChkOnInvoiceToChkPrinter") && m_checkPrinter->isLaser() ) {
          isLaser = true;
        } else if (chkOnInv && m_invoicePrinter->isLaser()) {
          isLaser = true;
        } else if (!chkOnInv && m_checkPrinter->isLaser()) {
          isLaser = true;
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

/*
 * This can only print one check at a time, up to three posistions on page (top, middle, bottom).
 * If there are multiple checks, this needs to be called for each check in the loop, adding
 * a formfeed to each check except the last.
 *
 * The "useFF" defaults to false in virtual function so there is no effect on Seller Invoice printing,
 * or anywhere else where only one check is printed. When printed from an external loop, the loop must
 * specifically set "useFF" true until the last check, otherwise they all run together.
 *
 */
string BuyerChecksDialog::fixLaserCheckFormat(string checkText, int lines, int i, int listSize) {
//    cout << "Laser Printer, not on invoice" << endl;
    // get line count of printed check:
    int count = 0, lineTotal = lines;
    int chkLen, blankLen;
    bool chkOnInv = false;
    bool isLaser = false;

    if (setupInvoiceDao.checkOnInvoice()) {
        chkOnInv = true;
      }

    if ( setup.getBoolean("sinvChkOnInvoiceToChkPrinter") && m_checkPrinter->isLaser() ) {
        isLaser = true;
      } else if (chkOnInv && m_invoicePrinter->isLaser()) {
        isLaser = true;
      } else if (!chkOnInv && m_checkPrinter->isLaser()) {
        isLaser = true;
      }

    if (!chkOnInv && isLaser) {
        for (int i=0; i<checkText.length(); i++) {
            if (checkText[i] == '\n') {
                count++;
              }
          }
        chkLen = count;
        // Make sure it's 1/3 of a page (20 lines assumed at 12 points and ten inches)
        for (int i = count; i < lineTotal; i++) {
            checkText += "\n";
            chkLen++; // [KLN] debug
          }

        string checkPage = "";
        string blankCheck = "";
        blankLen = 0; // [KLN] debug
        for(int i = 0; i < lineTotal; i++) {
            blankCheck += "\n";
            blankLen++; // [KLN] debug
          }
        //    cout << "       lineTotal: [" << lineTotal << "]" << endl;
        //    cout << " checkText lines: [" << chkLen << "]" << endl;
        //    cout << "blankCheck lines: [" << blankLen << "]" << endl;
        bool top,middle,bottom;
        top = SetupDAO().getBoolean("sinvLaserCheckTop");
        middle = SetupDAO().getBoolean("sinvLaserCheckMiddle");
        bottom = SetupDAO().getBoolean("sinvLaserCheckBottom");
        //    cout << "top, middle, bottom: " << top << ", " << middle << ", " << bottom << endl;
        if (top || middle || bottom) {
            if (top) {
                //            cout << "top is set" << endl;
                checkPage = checkText;
              } else {
                //            cout << "top is not set" << endl;
                checkPage = blankCheck;
              }
            if (middle) {
                //            cout << "middle is set" << endl;
                checkPage += checkText;
              } else {
                //            cout << "middle is not set" << endl;
                checkPage += blankCheck;
              }
            if (bottom) {
                //            cout << "bottom is set" << endl;
                checkPage += checkText;
              } else {
                //            cout << "bottom is not set" << endl;
                checkPage += blankCheck;
              }
            //        cout << "checkPage: [" << checkPage << "]" << endl;
            //        checkText = checkPage;
            //        cout << "checkText: [" << checkText << "]" << endl;
          } else { // single check,
            checkPage = blankCheck;
            checkPage += blankCheck;
            checkPage += checkText;
          }
        if (chkLen <= lineTotal) { // lineTotal is lines per check as set in Seller Invoice (usually 20)
            checkText = checkPage;
          } else { // most likely using chkPreSpaceLines which is set in the Setup -> Documents -> Check screen

          }
      }

    checkText += getFormFeed(i, listSize, false); // false = checks [KLN] add

    return checkText;
}

