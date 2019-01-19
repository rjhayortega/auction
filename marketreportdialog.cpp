//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add ui->setupUi(this);
//   Add delete ui;
//   delete moc include at end

#include "marketreportdialog.h"
#include "ui_marketreportdialog.h"

#include "previewdialog.h"
#include "textdialog.h"

MarketReportDialog::MarketReportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MarketReportDialog)
{
    ui->setupUi(this);

    // signals and slots connections
    connect( ui->applyFiltersButton, SIGNAL( clicked() ), this, SLOT( populateTransactionList() ) );
    connect( ui->includePushButton, SIGNAL( clicked() ), this, SLOT( copySelectedToInclude() ) );
    connect( ui->excludePushButton, SIGNAL( clicked() ), this, SLOT( removeSelectedFromInclude() ) );
    connect( ui->exitButton, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( ui->printButton, SIGNAL( clicked() ), this, SLOT( printReport() ) );
    connect( ui->includeAllPushButton, SIGNAL( clicked() ), this, SLOT( copyAllToInclude() ) );
    connect( ui->excludeAllPushButton, SIGNAL( clicked() ), this, SLOT( clearIncludeList() ) );
    connect( ui->minHead, SIGNAL( returnPressed() ), this, SLOT( populateTransactionList() ) );
    connect( ui->minPrice, SIGNAL( returnPressed() ), this, SLOT( populateTransactionList() ) );
    connect( ui->idIncludeFilter, SIGNAL( returnPressed() ), this, SLOT( moveTransactionToIncluded() ) );
    connect( ui->idExcludeFilter, SIGNAL( returnPressed() ), this, SLOT( removeTransactionFromIncluded() ) );
    connect( ui->colorCombo, SIGNAL( activated(int) ), this, SLOT( populateTransactionList() ) );
    connect( ui->indexComboBox, SIGNAL( activated(int) ), this, SLOT( sortTransactionList(int) ) );
    init();
}

MarketReportDialog::~MarketReportDialog()
{
    delete ui;
}


void MarketReportDialog::init()
{
    ui->minHead->setText("0");
    ui->minPrice->setText("0");
    populateTransactionList();
    restoreMarketList();
}

void MarketReportDialog::populateTransactionList()
{
    AnimalCode::Group group = AnimalCode::Invalid;

    switch(ui->colorCombo->currentItem())
    {
    case 0:
        group =  AnimalCode::First;
        break;

    case 1:
        group = AnimalCode::Second;
        break;

    case 2:
        group = AnimalCode::Third;
        break;

    case 3:
        group = AnimalCode::Fourth;
        break;

    default:
        group = AnimalCode::Invalid;
        break;
    }

    AnimalCodeDAO::startBatchMode();
    transactionList = dao.getMarketTransactionList(ui->minHead->text().toLong(), ui->minPrice->text().toDouble(), group);
    AnimalCodeDAO::endBatchMode();

    showTransactionList();

}

void MarketReportDialog::sortTransactionList(int index)
{
    switch(index)
    {
    case 0:
        std::sort(transactionList.begin(), transactionList.end(), Transaction::compareSellerNamesLT);
        break;
    case 1:
        std::sort(transactionList.begin(), transactionList.end(), Transaction::compareSellerIdsLT);
        break;
    case 2:
        std::sort(transactionList.begin(), transactionList.end(), Transaction::compareHeadLT);
        break;
    case 3:
        std::sort(transactionList.begin(), transactionList.end(), Transaction::compareDescriptionLT);
        break;
    case 4:
        std::sort(transactionList.begin(), transactionList.end(), Transaction::compareAverageWeightLT);
        break;
    case 5:
        std::sort(transactionList.begin(), transactionList.end(), Transaction::comparePricePerCWTLT);
        break;
    case 6:
        std::sort(transactionList.begin(), transactionList.end(), Transaction::comparePricePerHeadLT);
        break;
    case 7:
        std::sort(transactionList.begin(), transactionList.end(), Transaction::compareAmountLT);
        break;
    case 8:
        std::sort(transactionList.begin(), transactionList.end(), Transaction::compareIdsLT);
        break;
    }

    showTransactionList();
}

void MarketReportDialog::showTransactionList()
{
    ui->transactionTable->setNumRows(transactionList.size());
    for(unsigned int i = 0; i < transactionList.size(); i++)
    {
        fillTableRow(ui->transactionTable, i, transactionList[i]);
    }
}


void MarketReportDialog::copySelectedToInclude()
{
    for(int i = 0; i < ui->transactionTable->numRows(); i++)
    {
        if(ui->transactionTable->isRowSelected(i, true))
        {
            if(std::find(includeList.begin(), includeList.end(), transactionList[i]) == includeList.end())
            {
                includeList.push_back(transactionList[i]);
            }
        }
    }
    displayIncludeList();
}

void MarketReportDialog::restoreMarketList()
{
    vector<long> transactionIdList = dao.getMarketReportTransactionIdList();

    for(unsigned int i = 0; i < transactionIdList.size(); i++)
    {
        includeTransaction(transactionIdList[i], false);
    }

    displayIncludeList();
}

void MarketReportDialog::moveTransactionToIncluded()
{
    long transNo = ui->idIncludeFilter->text().toLong();
    includeTransaction(transNo);
    ui->idIncludeFilter->setText("");
    ui->idIncludeFilter->setFocus();
}

void MarketReportDialog::includeTransaction(long transNo)
{
    includeTransaction(transNo, true);
}

void MarketReportDialog::includeTransaction(long transNo, bool redisplay)
{
    vector<Transaction>::iterator transLoc;
    if((transLoc = std::find(transactionList.begin(), transactionList.end(), Transaction(transNo))) != transactionList.end())
    {
        if(std::find(includeList.begin(), includeList.end(), *transLoc) == includeList.end())
        {
            includeList.push_back(*transLoc);
        }
    }

    if(redisplay)
    {
        displayIncludeList();
    }
}

void MarketReportDialog::removeTransactionFromIncluded()
{
    long transNo = ui->idExcludeFilter->text().toLong();
    vector<Transaction>::iterator transLoc;

    if((transLoc = std::find(includeList.begin(), includeList.end(), Transaction(transNo))) != includeList.end())
    {
        includeList.erase(transLoc);
    }
    displayIncludeList();
    ui->idExcludeFilter->setText("");
    ui->idExcludeFilter->setFocus();
}

void MarketReportDialog::displayIncludeList()
{
    ui->includeTable->setNumRows(includeList.size());

    for(unsigned int i = 0; i < includeList.size(); i++)
    {
        fillTableRow(ui->includeTable, i, includeList[i]);
    }
}

void MarketReportDialog::fillTableRow(Q3Table *table, unsigned int i, Transaction transaction)
{
    table->setText(i, 0, QString::fromStdString(transaction.getSeller().getName().getLast()));
    table->setText(i, 1, QString::fromStdString(transaction.getSeller().getNumber()));
    table->setText(i, 2, QString::number(transaction.getHead()));
    table->setText(i, 3, QString::fromStdString(transaction.getAnimalCode().getDescrip()));
    table->setText(i, 4, QString::number(transaction.getAverageWeight()));
    table->setText(i, 5, QString::number(transaction.getPricePerCWT(), 'f', 2));
    table->setText(i, 6, QString::number(transaction.getPricePerHead(), 'f', 2));
    table->setText(i, 7, QString::number(transaction.amount(), 'f', 2));
    table->setText(i, 8, QString::number(transaction.getId()));
}

void MarketReportDialog::clearIncludeList()
{
    includeList = vector<Transaction>();
    displayIncludeList();
}

void MarketReportDialog::copyAllToInclude()
{
    includeList = transactionList;
    displayIncludeList();
}

void MarketReportDialog::removeSelectedFromInclude()
{
    vector<Transaction> tempList;
    tempList.clear();

    for(unsigned int i =0; i < includeList.size(); i++)
    {
        if(!(ui->includeTable->isRowSelected(i)))
        {
            tempList.push_back(includeList[i]);
        }
    }

    includeList.clear();
    includeList =  tempList;

    displayIncludeList();
}

void MarketReportDialog::reject()
{
    dao.saveMarketReportTransactionIdList(includeList);
    QDialog::reject();
}
#include <fstream>

void MarketReportDialog::printReport()
{
    string outFilePath = string(getenv("HOME")) + string("/market.txt");
    ofstream outFile(outFilePath.c_str(), ios::trunc);

    QStringList keyList;
    keyList << "firstMarketReportSort" << "secondMarketReportSort" << "thirdMarketReportSort"
            << "fourthMarketReportSort" << "fifthMarketReportSort" << "sixthMarketReportSort";

    MarketReport::SortRecord sorts[keyList.size()];
    QStringList options;

    for(int i = 0; i <keyList.size(); i++) {
        QString optionsString = QString::fromStdString(setup.get(keyList[i].toStdString()));
        if (!optionsString.isEmpty()) { //Safety check, options string was empty and cause program crash.
            options = optionsString.split(" ", QString::KeepEmptyParts);

            sorts[i].sort = MarketReport::SortItem(options[0].toInt());
            sorts[i].reverse = bool(options[1].toInt());
        }
    }

    QString startWeight = QString::fromStdString(setup.get("MarketReportClassStarting"));
    QString endWeight = QString::fromStdString(setup.get("MarketReportClassEnding"));
    QString classSize = QString::fromStdString(setup.get("MarketReportClassSize"));


    MarketReport report(includeList, true, ui->suppressSellerBox->isChecked());
    report.setSortOrder(sorts[0], sorts[1], sorts[2], sorts[3], sorts[4], sorts[5]);
    report.setWegthRanges(startWeight.toInt(),endWeight.toInt(),classSize.toInt(),setup.getBoolean("MarketReportClassEnabled",false));

    PreviewDialog prev;
    report.setHeader(setup.reportHeader("Market Report"));

    if(sorts[0].sort == MarketReport::Sex)
    {
        setComments(report);
    }

    outFile << report.exportText() << endl;
    outFile.close();
    prev.setText(QString::fromStdString(report.text()));

    prev.setReport(&report);
    prev.setShowPrint(true);
    prev.exec();
}

void MarketReportDialog::setComments(MarketReport& marketReport)
{
    vector<string> animalDescriptions = marketReport.getUniqueSexList();
    vector<string> commentList;
    for(unsigned int i = 0; i < animalDescriptions.size(); i++)
    {
        TextDialog textDialog(this);
        textDialog.init(QString("Enter Comments For ") + QString::fromStdString(animalDescriptions[i]), QString(""));
        textDialog.exec();
        commentList.push_back(textDialog.text().toStdString());
    }

    marketReport.setCommentList(commentList);
}
