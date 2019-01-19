//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add delete ui;
//   delete moc include at end


#include "proratedialog.h"
#include "ui_proratedialog.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <Q3Table>
#include <qcheckbox.h>
#include <qcombobox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>


ProrateDialog::ProrateDialog( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl ), ui(new Ui::ProrateDialog)
{
    ui->setupUi(this);
    // signals and slots connections
    connect( ui->buttonOk, SIGNAL( clicked() ), this, SLOT( save() ) );
    connect( ui->buttonCancel, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( ui->prorateTable, SIGNAL( valueChanged(int,int) ), this, SLOT( updateProrates() ) );
    connect( ui->comboProrateMode, SIGNAL( activated(int) ), this, SLOT( initTable() ) );
    connect( ui->buttonNew, SIGNAL( clicked() ), this, SLOT( createPayee() ) );
    connect( ui->prorateTable, SIGNAL( currentChanged(int,int) ), this, SLOT( startSpecialProrate(int,int) ) );
    connect( ui->chkShareChgs, SIGNAL( toggled(bool) ), this, SLOT( updateProrates() ) );
    connect( ui->buttonDelete, SIGNAL( clicked() ), this, SLOT( removeCurrentPayee() ) );
    init();
}

ProrateDialog::~ProrateDialog()
{
    delete ui;
}


#include "proratetransactiondialog.h"
#include "proratesexdialog.h"

#include "qmessagebox.h"

void ProrateDialog::init()
{
    block = false;
    checkFactory = NULL;
}

void ProrateDialog::destroy()
{
    if(checkFactory != NULL)
    {
        delete checkFactory;
    }
}

void ProrateDialog::init(Invoice invoice)
{
    ProrateDAO::Mode mode = ProrateDAO::Percentage;

    checkFactory = prorateDao.getCheckFactory(invoice, &mode);

    switch(mode)
    {
    case ProrateDAO::Percentage:
    default:
        ui->comboProrateMode->setCurrentItem(BY_PER);
        ui->prorateTable->horizontalHeader()->setLabel(1, "Percent");
        break;
    case ProrateDAO::Transaction:
        ui->comboProrateMode->setCurrentItem(BY_TRANS);
        ui->prorateTable->horizontalHeader()->setLabel(1, "Trans:Head");
        break;
    case ProrateDAO::Sex:
        ui->prorateTable->horizontalHeader()->setLabel(1, "Sex:Head");
        ui->comboProrateMode->setCurrentItem(BY_SEX);
        break;
    case ProrateDAO::Head:
        ui->prorateTable->horizontalHeader()->setLabel(1, "Head Cnt");
        ui->comboProrateMode->setCurrentItem(BY_HEAD);
        break;
    case ProrateDAO::Flat:
        ui->prorateTable->horizontalHeader()->setLabel(1, "Amount");
        ui->comboProrateMode->setCurrentItem(BY_FLAT);
        break;
    }

    if(checkFactory != NULL)
    {
        if(checkFactory->getProrateList().size() > 1)
        {
            ui->prorateTable->insertRows(0, checkFactory->getProrateList().size() - 1);
        }
        updateShareList();
        bool sharesCharges = checkFactory->sharesCharges();
        prorateDao.releaseCheckFactory();
        checkFactory = NULL;

        block = true;
        ui->chkShareChgs->setChecked(sharesCharges);
        block = false;
    }




    this->invoice = invoice;

    ui->primaryPayee->setText(QString::fromStdString(invoice.getCustomer().getName().getLast()));
    ui->primaryShare->setText(QString::number(invoice.gross(), 'f', 2));
    ui->primaryCharge->setText(QString::number(invoice.chargeTotal() + invoice.getCommissionTotal(true) + invoice.truckingTotal(), 'f', 2));


    Prorate primaryProrate(invoice.getCustomer().getName().getLast(), primaryDataList());
}

void ProrateDialog::changeProrateMode(int selected)
{
}

void ProrateDialog::updateProrates()
{
    if(block)
    {
        return;
    }
    prorates = vector<Prorate>();
    Prorate::Data data;

    for(unsigned int i = 0; i < ui->prorateTable->numRows(); i++)
    {
        switch(ui->comboProrateMode->currentItem())
        {
        default:
            data.number = 0;
            data.amount = ui->prorateTable->text(i, 1).toDouble();
            prorates.push_back(Prorate(ui->prorateTable->text(i, 0).toStdString(), data));
            break;

        case BY_TRANS:
        case BY_SEX:

            vector<Prorate::Data> dataList;
            QStringList pairList = QStringList::split(",", ui->prorateTable->text(i, 1));

            for(int j = 0; j < pairList.size(); j++)
            {
                QStringList transPair = QStringList::split(":", pairList[j]);
                if (transPair.size() > 1 ) { //Sanity check, pair should exists before take it.
                    data.number = transPair[0].toLong();
                    data.amount = transPair[1].toDouble();
                    dataList.push_back(data);
                }
            }
            prorates.push_back(Prorate(ui->prorateTable->text(i, 0).toStdString(), dataList));

            break;
        }
    }
    prorates.push_back(Prorate(ui->primaryPayee->text().toStdString(), primaryDataList()));
    initCheckFactory();
    updateShareList();
}

void ProrateDialog::updateShareList()
{
    vector<Check> checkList = checkFactory->checkList();
    prorates = checkFactory->getProrateList();
    vector<double> chargeList = checkFactory->getChargeShares();

    for(unsigned int i = 0; i < checkList.size(); i++)
    {

        if(i != checkList.size() - 1)
        {
            ui->prorateTable->setText(i, 0, QString::fromStdString(prorates[i].getPayee()));

            switch(ui->comboProrateMode->currentItem())
            {
            default:
                ui->prorateTable->setText(i, 1, QString::number(prorates[i].getAmount(), 'f', 2));
                break;

            case BY_TRANS:
            case BY_SEX:
                ui->prorateTable->setText(i, 1, getProrateDataString(prorates[i].getDataList()));
                break;
            }

            ui->prorateTable->setText(i, 2, QString::number(checkList[i].getAmount(), 'f', 2));
            ui->prorateTable->setText(i, 3, QString::number(chargeList[i], 'f', 2));
        }
        else
        {
            bool shareCharge = ui->chkShareChgs->isChecked();
            ui->primaryShare->setText(QString::number(checkList[i].getAmount(), 'f', 2));
            ui->primaryCharge->setText(QString::number(
                                           (shareCharge ? chargeList[i] : invoice.chargeTotal() + invoice.getCommissionTotal(true) + invoice.truckingTotal()), 'f', 2));

            if(ui->primaryShare->text().toDouble() < 0)
            {
                ui->prorateTable->setNumRows(0);
                QMessageBox::information(this, "ERROR",
                                         "An attempt to create a negative check has occured\n"
                                         "If the prorate amount exceeds the net amount, you may "
                                         "need to share the charges",
                                         QMessageBox::Ok);
            }

        }
    }
}

void ProrateDialog::initTable()
{
    string valueLabel;
    switch(ui->comboProrateMode->currentItem())
    {
    case BY_PER:
    default:
        valueLabel = "Percent";
        break;

    case BY_TRANS:
        valueLabel="Trans:Head";
        break;

    case BY_HEAD:
        valueLabel ="Head Count";
        break;

    case BY_SEX:
        valueLabel="Sex:Head";
        break;

    case BY_FLAT:
        valueLabel="Amount";
        break;
    }
    ui->prorateTable->horizontalHeader()->setLabel(1, QString::fromStdString(valueLabel));

    for(unsigned int i = 0; i < ui->prorateTable->numRows(); i++)
    {
        initTableRow(i);
    }
    if(ui->prorateTable->numRows() > 0)
    {
        ui->prorateTable->setCurrentCell(0, 0);
    }
    updateProrates();
}

void ProrateDialog::initTableRow(unsigned int row)
{
//    QStringList menu;
//
    ui->prorateTable->setItem(row, 3, new Q3TableItem(ui->prorateTable, Q3TableItem::Never, "0"));
    ui->prorateTable->setItem(row, 2, new Q3TableItem(ui->prorateTable, Q3TableItem::Never, "0"));
//    prorateTable->setItem(row, 0, new QTableItem(prorateTable, QTableItem::Always, ""));
//
//    if(comboProrateMode->currentItem() != BY_TRANS)
//    {
//       prorateTable->setItem(row, 1, new QTableItem(prorateTable, QTableItem::Always, "0"));
// }
// else if(comboProrateMode->currentItem() == BY_TRANS)
//  {
//         prorateTable->setItem(row, 1, new QComboTableItem(prorateTable, menu));
//     }

}

void ProrateDialog::startSpecialProrate(int row, int col)
{

    if(col != 1)
    {
        return;
    }
    switch(ui->comboProrateMode->currentItem())
    {
    case BY_TRANS:
        startTransactionProrate(row);
        break;

    case BY_SEX:
        startSexProrate(row);
        break;
    default:
        break;
    }
}

void ProrateDialog::startTransactionProrate(int row)
{
    ProrateTransactionDialog proTrans(this);


    proTrans.init(CheckFactory::invoiceTransactions(&invoice), prorates, row);
    if(proTrans.exec() == QDialog::Accepted)
    {
        vector<Prorate::Data> dataList = proTrans.getProrateData();
        ui->prorateTable->setText(row, 1, getProrateDataString(dataList));
        ui->prorateTable->setCurrentCell(row, 0);
        updateProrates();
    }
}

void ProrateDialog::startSexProrate(int row)
{
    ProrateSexDialog proSex(this);
    proSex.init(SexCheckFactory::getCodeList(invoice), prorates, row);
    if(proSex.exec() == QDialog::Accepted)
    {
        vector<Prorate::Data> dataList = proSex.getProrateData();
        ui->prorateTable->setText(row, 1, getProrateDataString(dataList));
        ui->prorateTable->setCurrentCell(row, 0);
        updateProrates();
    }
}

void ProrateDialog::createPayee()
{
    ui->prorateTable->insertRows(ui->prorateTable->numRows());
    initTable();
}

vector<Prorate::Data> ProrateDialog::primaryDataList()
{
    Prorate::Data data;
    vector<Prorate::Data> dataList;
    vector<Transaction> transList;
    vector<SexCheckFactory::CodeRecord> codeList;
    unsigned int i;
    switch(ui->comboProrateMode->currentItem())
    {
    case BY_PER:
        data.number = 0;
        data.amount = 100;
        dataList.push_back(data);
        break;

    case BY_HEAD:
        data.number = 0;
        data.amount = invoice.head();
        dataList.push_back(data);
        break;

    case BY_FLAT:
        data.number = 0;
        data.amount = invoice.gross();
        dataList.push_back(data);
        break;

    case BY_TRANS:
        transList = invoice.getTransactionList();
        for(i = 0; i < transList.size(); i++)
        {
//            cout << "BY_TRANS start:" << endl;
            data.number = transList[i].getId();
            data.amount = transList[i].getHead();
//            cout << "  number: " << data.number << " -- amount: " << data.amount << endl;
            dataList.push_back(data);
//            cout << "BY_TRANS end." << endl;
        }
        break;

    case BY_SEX:
        codeList = SexCheckFactory::getCodeList(invoice);
        for(i = 0; i < codeList.size(); i++)
        {
            data.number = codeList[i].sex;
            data.amount = codeList[i].head;
        }
        break;

    }

    return dataList;
}

void ProrateDialog::initCheckFactory()
{
    if(checkFactory != NULL)
    {
        delete checkFactory;
    }

    bool shareCharge = ui->chkShareChgs->isChecked();
    switch(ui->comboProrateMode->currentItem())
    {
    case BY_PER:
    default:
        checkFactory = new PercentageCheckFactory(invoice, shareCharge, prorates);
        break;

    case BY_FLAT:
        checkFactory = new FlatCheckFactory(invoice, shareCharge, prorates);
        break;

    case BY_HEAD:
        checkFactory = new HeadCheckFactory(invoice, shareCharge, prorates);
        break;

    case BY_TRANS:
        checkFactory = new TransactionCheckFactory(invoice, shareCharge, prorates);
        break;

    case BY_SEX:
        checkFactory = new SexCheckFactory(invoice, shareCharge, prorates);
        break;
    }
}

void ProrateDialog::save()
{
    if(checkFactory == NULL)
    {
        QDialog::accept();
    }

    if(ui->prorateTable->numRows() > 0)
    {
        updateProrates();
        ProrateDAO::Mode mode;
        switch(ui->comboProrateMode->currentItem())
        {
        case BY_PER:
            mode = ProrateDAO::Percentage;
            break;

        case BY_HEAD:
            mode = ProrateDAO::Head;
            break;

        case BY_SEX:
            mode = ProrateDAO::Sex;
            break;

        case BY_TRANS:
            mode = ProrateDAO::Transaction;
            break;

        case BY_FLAT:
            mode = ProrateDAO::Flat;
            break;
        }

        prorateDao.saveCheckFactory(checkFactory, mode);
    }
    else
    {
        prorateDao.deleteCheckFactory(checkFactory);
    }
    QDialog::accept();
}

void ProrateDialog::removeCurrentPayee()
{
    if(ui->prorateTable->currentRow() >= 0 && ui->prorateTable->currentRow() < ui->prorateTable->numRows())
    {
        ui->prorateTable->removeRow(ui->prorateTable->currentRow());
        updateProrates();
    }
}


QString ProrateDialog::getProrateDataString(vector<Prorate::Data> dataList)
{
    QStringList data;
    for(unsigned int i = 0; i < dataList.size(); i++)
    {
        data += QString::number(dataList[i].number) + ":" + QString::number(dataList[i].amount);
    }
    return data.join(",");
}


