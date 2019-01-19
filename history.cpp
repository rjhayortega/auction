//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add ui->setupUi(this);
//   Add delete ui;
//   delete moc include at end

#include "history.h"
#include "ui_history.h"

#include <qvariant.h>
#include <qcombobox.h>
#include <qlabel.h>
#include <qdatetimeedit.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

History::History( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl ), ui(new Ui::History)
{
    ui->setupUi(this);
    // signals and slots connections
    connect( ui->indexCombo, SIGNAL( activated(int) ), this, SLOT( initIndex(int) ) );
    connect( ui->reportButton, SIGNAL( clicked() ), this, SLOT( printHistory() ) );
 //   connect( ui->_historyParamaterEdit, SIGNAL( textChanged(const QString&) ), this, SLOT( clear() ) );
    connect( ui->endDateEntry, SIGNAL( valueChanged(const QDate&) ), this, SLOT( clear() ) );
    connect( ui->startDateEntry, SIGNAL( valueChanged(const QDate&) ), this, SLOT( clear() ) );
    connect( ui->typeCombo, SIGNAL( activated(int) ), this, SLOT( clear() ) );
    connect( ui->indexCombo, SIGNAL( activated(int) ), this, SLOT( clear() ) );
    connect( ui->_historyParamaterEdit, SIGNAL( textChanged(const QString&) ), this, SLOT( predictParamater(const QString&) ) );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
History::~History()
{
    delete ui;
}

#include "dao/transactiondao.h"
#include <iostream>
#include "previewdialog.h"
#include "reports/historyreport.h"
#include "dao/setupdao.h"


using namespace std;

///////////////////////////////////////////////////////////////////////////////
//
// name:  init()
//
// purpose:
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

void History::init()
{

    historyParamaterEdit = new AutoFillEdit(this);
    historyParamaterEdit->setGeometry(ui->_historyParamaterEdit->geometry());
    connect(historyParamaterEdit, SIGNAL(textChanged(const QString&)), this, SLOT(clear()));
    connect(historyParamaterEdit, SIGNAL(textChanged(const QString&)), this, SLOT(predictParamater(const QString&)));

    setTabOrder(ui->indexCombo, historyParamaterEdit);
    setTabOrder(historyParamaterEdit, ui->startDateEntry);
    setTabOrder(ui->startDateEntry, ui->endDateEntry);

    ui->startDateEntry->setDate(QDate::currentDate());
    ui->endDateEntry->setDate(QDate::currentDate());
    initIndex(0);
//   historyTable->setLeftMargin(0);
    ui->_historyParamaterEdit->hide();
}

void History::destroy()
{
    if(historyParamaterEdit != NULL)
    {
        delete historyParamaterEdit;
        historyParamaterEdit = NULL;
    }
}

void History::initIndex(int indexNo)
{
    QStringList labelList;

    switch(indexNo)
    {
    case 0:
    default:
        historyParamaterEdit->show();
        ui->typeCombo->hide();
        ui->paramaterLabel->setText("Seller Name:");

// historyTable->setNumCols(6);
//     labelList << "Date" << "Head" << "Weight" << "Description"   << "Bid" << "Gross";
//  historyTable->setColumnWidth(0, 120);
        break;

    case 1:
        historyParamaterEdit->show();
        ui->typeCombo->hide();
        ui->paramaterLabel->setText("Buyer Name:");
//  historyTable->setNumCols(6);
//      labelList << "Seller" << "Date" << "Head" << "Weight" << "Description" << "Bid";
//  historyTable->setColumnWidth(0, 340);
        break;

    case 2:
        historyParamaterEdit->show();
        ui->typeCombo->hide();
        ui->paramaterLabel->setText("Description:");
//    historyTable->setNumCols(6);
//        labelList << "Seller" << "Date" << "Head" << "Weight" << "Description" << "Bid";
//   historyTable->setColumnWidth(0, 340);
        break;

    case 3:
        historyParamaterEdit->hide();
        ui->typeCombo->show();
        ui->paramaterLabel->setText("Customer Type:");
//  historyTable->setNumCols(4);
//     labelList << (typeCombo->currentItem() == 0 ? "Seller" : "Buyer") << "Date" << "Head" << "Net";
//   historyTable->setColumnWidth(0, 340);
        break;
    }

//   historyTable->setColumnLabels(labelList);
}

void History::populateHistory()
{
    loadHistoryList();

//   historyTable->setNumRows(historyList.size());
    AnimalCode tempCode;

    for(unsigned int i = 0; i < historyList.size(); i++)
    {
        tempCode = historyList[i].getCode();
        historyList[i].setAnimalCode(tempCode);
//      fillLine(historyList, i);
    }
}

void History::loadHistoryList()
{
    setCursor(Qt::WaitCursor);

    historyList = vector<HistoryItem>();

    string searchString = historyParamaterEdit->text().toStdString();

    Date startDate = Date::fromString(ui->startDateEntry->date().toString("yyyy-MM-dd").toStdString(), "YYYY-mm-dd");
    Date endDate = Date::fromString(ui->endDateEntry->date().toString("yyyy-MM-dd").toStdString(), "YYYY-mm-dd");

    switch(ui->indexCombo->currentItem())
    {
    default:
        break;

    case 0:
        historyList = historyDao.getSellerHistoryList(searchString, startDate, endDate);
        break;

    case 1:
        historyList = historyDao.getBuyerHistoryList(searchString, startDate, endDate);
        break;
        break;

    case 2:
        historyList = historyDao.getAnimalHistoryList(AnimalCode::fromString(searchString), startDate, endDate);
        break;

    case 3:
        switch(ui->typeCombo->currentItem())
        {
        case 0:
        default:
            historyList = historyDao.getSellerInvoiceHistoryList(startDate, endDate);
            break;

        case 1:
            historyList = historyDao.getBuyerInvoiceHistoryList(startDate, endDate);
            break;
        }
        break;
    }
    setCursor(Qt::ArrowCursor);
}

//void History::fillLine(vector<HistoryItem> historyList, int i)
//{
// double gross = 0.00000001;
// string modeString;
//     switch(historyList[i].getMode())
// {
//   case Transaction::Invalid:
//  modeString = "i";
//  break;
//   case Transaction::SaleCWT:
//  modeString = "c";
//           break;
//    case Transaction::SaleHead:
//   modeString = "h";
//       break;
//  case Transaction::NoSaleCWT:
//   modeString = "nc";
//   break;
//  case Transaction::NoSaleHead:
//   modeString = "nh";
// break;
//case Transaction::ReSaleCWT:
// modeString = "rc";
// break;
//case Transaction::ReSaleHead:
// modeString = "rh";
// break;
//case Transaction::SwapCWT:
// modeString = "sc";
// break;
//case Transaction::SwapHead:
// modeString = "sh";
// break;
// }
//
//     gross = Transaction(0, Seller(), Buyer(), historyList[i].getHead(), historyList[i].getWeight(), historyList[i].getBid(), historyList[i].getMode()).amount();
// switch(indexCombo->currentItem())
//     {
//     case 0:
//         historyTable->setText(i, 0, historyList[i].getDate().toString("mm/dd/YYYY"));
//         historyTable->setText(i, 1, QString::number(historyList[i].getHead()));
//         historyTable->setText(i, 2, QString::number(historyList[i].getWeight()));
//     historyTable->setText(i, 3, historyList[i].getCode().getDescrip());
//     historyTable->setText(i, 4, QString::number(historyList[i].getBid(), 'f', 2) + modeString);
//     historyTable->setText(i, 5, QString::number(gross, 'f' , 2));
//
//     break;
//     case 1:
//    historyTable->setText(i, 0, historyList[i].getSellerName());
//        historyTable->setText(i, 1, historyList[i].getDate().toString("mm/dd/YYYY"));
//    historyTable->setText(i, 2, QString::number(historyList[i].getHead()));
//        historyTable->setText(i, 3, QString::number(historyList[i].getWeight()));
//    historyTable->setText(i, 4, historyList[i].getCode().getDescrip());
//         historyTable->setText(i, 5, QString::number(historyList[i].getBid(), 'f', 2) + modeString);
//       break;
//     case 2:
//    historyTable->setText(i, 0, historyList[i].getSellerName());
//        historyTable->setText(i, 1, historyList[i].getDate().toString("mm/dd/YYYY"));
//    historyTable->setText(i, 2, QString::number(historyList[i].getHead()));
//        historyTable->setText(i, 3, QString::number(historyList[i].getWeight()));
//    historyTable->setText(i, 4, historyList[i].getCode().getDescrip());
//         historyTable->setText(i, 5, QString::number(historyList[i].getBid(), 'f', 2) + modeString);
//    break;
//     case 3:
//        historyTable->setText(i, 0, historyList[i].getSellerName());
//        historyTable->setText(i, 1, historyList[i].getDate().toString("mm/dd/YYYY"));
//        historyTable->setText(i, 2, QString::number(historyList[i].getHead()));
//        historyTable->setText(i, 3, QString::number(historyList[i].getNet(), 'f', 2));
//      break;
//     };
//
//}
//
void History::printHistory()
{
    HistoryReport* report;
    string reportDescrip;
    loadHistoryList();
    switch(ui->indexCombo->currentItem())
    {
    case 0:
    default:
        report = new SellerHistoryReport(historyList);
        reportDescrip = "SELLER: ";
        if(historyList.size() > 0)
        {
            reportDescrip += historyList[0].getSellerName();
        }
        break;

    case 1:
        report = new BuyerHistoryReport(historyList);
        reportDescrip = "BUYER: ";
        if(historyList.size() > 0)
        {
            reportDescrip += historyList[0].getBuyerName();
        }
        break;

    case 2:
        report = new CodeHistoryReport(historyList);
        reportDescrip = "Animal Code: ";

        if(historyList.size() > 0)
        {
            reportDescrip += historyList[0].getCode().toString();
        }
        break;

    case 3:
        reportDescrip = string(" DATED ") + ui->startDateEntry->date().toString("MM/dd/yyyy").ascii() + string(" to ") + ui->endDateEntry->date().toString("MM/dd/yyyy").ascii();

        switch(ui->typeCombo->currentItem())
        {
        case 0:
        default:
            report = new SellerDateHistoryReport(historyList);
            reportDescrip = string("SELLERS") + reportDescrip;
            break;

        case 1:
            report = new BuyerDateHistoryReport(historyList);
            reportDescrip = string("BUYERS") + reportDescrip;
            break;
        };
        break;
    }

    report->text();
    TextReportHeader header = SetupDAO().reportHeader(string("H I S T O R Y  R E P O R T") , true);
    header.addHeaderLine(reportDescrip + (reportDescrip.length() < 80 ? string(80 - reportDescrip.length(), ' ') : ""));
    header.addHeaderLine("");
    report->setHeader(header);

    PreviewDialog preview;
    preview.setReport(report);
    preview.setShowPrint(true);
    preview.exec();

    delete report;
}

void History::predictParamater(const QString& parameter)
{
    historyList = vector<HistoryItem>();
    QString actualParameter = parameter;
    actualParameter = actualParameter.replace("\\", "\\\\");
    if(lastParameter == parameter && parameter.length() > 0)
    {
        actualParameter = parameter.left(parameter.length() - 1);
    }

    lastParameter = actualParameter;

    string prediction;
    switch(ui->indexCombo->currentItem())
    {
    case 0:
        prediction = historyDao.predictSeller(actualParameter.toStdString());
        break;

    case 1:
        prediction = historyDao.predictBuyer(actualParameter.toStdString());
        break;

    default:
        break;
    }
    if(prediction.length() > actualParameter.length())
    {
        historyParamaterEdit->setText(QString::fromStdString(prediction));
        historyParamaterEdit->setSelection(actualParameter.length(), prediction.length() - actualParameter.length());
    }

}

void History::clear()
{
    historyList = vector<HistoryItem>();
}
