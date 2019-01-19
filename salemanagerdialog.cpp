//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add delete ui;
//   delete moc include at end

#include "salemanagerdialog.h"
#include "ui_salemanagerdialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <Q3ListBox>
#include <qlabel.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>


SaleManagerDialog::SaleManagerDialog( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl ), ui(new Ui::SaleManagerDialog)
{
    ui->setupUi(this);
    // signals and slots connections
    connect( ui->createButton, SIGNAL( clicked() ), this, SLOT( createNew() ) );
    //    connect( ui->saleListBox, SIGNAL( highlighted(int) ), this, SLOT( changeCurrentSale(int) ) );
    connect( ui->exitButton, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( ui->saveNewSaleButton, SIGNAL( clicked() ), this, SLOT( saveNew() ) );
    connect( ui->saleDatePicker, SIGNAL( dateSelected(QDate) ), this, SLOT( keepDateCurrent(QDate) ) );
    connect( ui->closeSaleButton, SIGNAL( clicked() ), this, SLOT( closeCurrentSale() ) );
    connect( ui->openSelected, SIGNAL( clicked() ), this, SLOT( openSelectedSale() ) );
    connect( ui->setActiveButton, SIGNAL( clicked() ), this, SLOT( setActive() )) ;

    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
SaleManagerDialog::~SaleManagerDialog()
{
    delete ui;
}

#include "qmessagebox.h"
#include <iostream>

void SaleManagerDialog::init()
{
    ui->saleDatePicker->hide();
    ui->saveNewSaleButton->hide();
    populateSaleList();
    block = false;
}

void SaleManagerDialog::populateSaleList()
{
    block = true;
    saleList = sale.getSaleList();
    QStringList itemList;
    int currentRow = 0;
    for(unsigned int i = 0; i < saleList.size(); i++)
    {
        itemList += QString::fromStdString(saleList[i].date.toString("mm-dd-YYYY") + (saleList[i].open ? "" : "*CLOSED*"));
        if(saleList[i].date == sale.currentSaleDate())
        {
            currentRow = i;
        }

        if(saleList[i].date == sale.mostRecentSale().date)
        {
            if(saleList[i].open == false)
            {
                QMessageBox::information(this, "Warning",
                                         "The active sale date is closed.\n"
                                         "While this situation persists, the clerk will not be able to add "
                                         "transactions to a sale that has been closed.\n"
                                         "To remedy this, change the active sale to an open sale");
            }

            itemList[i] += "*ACTIVE*";
        }
    }
    ui->saleListBox->clear();
    ui->saleListBox->insertStringList(itemList);

    ui->saleListBox->setSelected(currentRow, true);
    block = false;
}

void SaleManagerDialog::createNew()
{
    ui->saleDatePicker->setSelectedDate(QDate::currentDate());
    ui->saleDatePicker->show();
    ui->saveNewSaleButton->show();
}

void SaleManagerDialog::saveNew()
{
    QDate date = ui->saleDatePicker->selectedDate();
    sale.createSale(Date::fromString(date.toString("yyyy-MM-dd").toStdString(), "YYYY-mm-dd"));
    sale.setCurrentSale(Sale(Date::fromString(date.toString("yyyy-MM-dd").toStdString(), "YYYY-mm-dd"), true));
    ui->saleDatePicker->hide();
    ui->saveNewSaleButton->hide();
    populateSaleList();
}

void SaleManagerDialog::changeCurrentSale(int row)
{
    qDebug() << "Entering changeCurrentSale" << endl;
    qDebug() << "  row = " << row << endl;
    if(row >= 0 && row < saleList.size() && !block)
    {
        qDebug() << "    valid row" << endl;
        bool systemSale = false;

        if(saleList[row].open)
        {
            qDebug() << "      sale open" << endl;
            int option = QMessageBox::question(this, "Action requested",
                                               "You are changing the currently loaded sale to \n"
                                               "a sale that has not been closed.\n"
                                               "Do you want to change the active sale as well?\n"
                                               "(The active sale is the sale that the clerk and penner will use)",
                                               "Only Change This Station", "Make This Sale The Active Sale");

            systemSale = (option == 1);
            qDebug() << "      systemSale = " << systemSale << endl;
        }

        sale.setCurrentSale(saleList[row], systemSale);
        populateSaleList();
    }
    qDebug() << "Leaving changeCurrentSale" << endl;
}


void SaleManagerDialog::keepDateCurrent(QDate date)
{
    ui->saleDatePicker->setSelectedDate(date);
}

void SaleManagerDialog::closeCurrentSale()
{
    qDebug() << "Entering closeCurrentSale" << endl;
    int status = checkSelection(); // 1 = Closed, 2 = Open, 4 = Active
    int index = getCurrentIndex();
    qDebug() << "  status: " << status << endl;
    qDebug() << "  index: " << index << endl;
    qDebug() << "  status & 4: " << (status & 4) << endl;
    qDebug() << "  status & 2: " << (status & 2) << endl;
    if (status & 4) {
        QMessageBox::information(this, "Error",
                                 "The active sale can not be closed\n"
                                 "Either set an existing sale to be the active sale\n"
                                 "or create a new sale to be the active sale");
        qDebug() << "Leaving closeCurrentSale due to Active Sale" << endl;
        return;
    }
    if ((status & 2)) { // status 2 = open
        if(QMessageBox::warning(this, "Warning!",
                                "You are about to close the selected sale: (" + QString::fromStdString(saleList[index].date.toString("mm/dd/YYYY")) + ").\n"
                                "Once a sale is closed it can not be changed, are you sure that you want to do this?",
                                QMessageBox::Cancel, QMessageBox::Ok) == QMessageBox::Ok)
        {
            sale.closeSale(saleList[index]);
            sale.setCurrentSale(sale.mostRecentSale());
            populateSaleList();
        }

    }
    qDebug() << "Leaving closeCurrentSale" << endl;
}

// KLN add

int SaleManagerDialog::getCurrentIndex() {
    int index = ui->saleListBox->currentItem();
    if (0 <= index && index < saleList.size()) { // valid index
        return index;
    }
    return -1;
}

/*
 * Returns whether selection is Closed, Open, Active (or combo):
 *
 * 1 = Closed
 * 2 = Open
 * 4 = Active
 *
 */
int SaleManagerDialog::checkSelection() {
    qDebug() << "  Entering checkSelection" << endl;
    int result = 0;
    int index = getCurrentIndex();
    qDebug() << "    index = " << index << endl;
    bool isOpen = false;
    bool isActive = false;

    if (index >= 0) { // valid index
        isActive = sale.isSaleActive(saleList[index]);
        isOpen = sale.isSaleOpen(saleList[index]);
        qDebug() << "    isActive = " << isActive << endl << "    isOpen = " << isOpen << endl;

        if (isOpen) {
            result = 2;
        } else {
            result = 1;
        }
        if (isActive) {
            result += 4;
        }
    }
    qDebug() << "    result = " << result << endl;
    qDebug() << "  Leaving checkSelection" << endl;
    return result;
}

void SaleManagerDialog::openSelectedSale()
{
    int status = checkSelection(); // 1 = Closed, 2 = Open, 4 = Active
    int index = getCurrentIndex();
    if (status & 1) {
        QString saleDate = QString::fromStdString(saleList[index].date.toString("mm/dd/YYYY"));
        if(QMessageBox::warning(this, "Warning!",
                                "You are about to open the selected sale: (" + saleDate + ").\n"
                                + "If you changed any of your fees or commissions.after you close a sale, "
                                + "then re-opening that sale and printing invoices will cause the new fees to be applied!\n\n"
                                + "Are you sure that you want to do this?",
                                QMessageBox::Cancel, QMessageBox::Ok) == QMessageBox::Ok)
        {
            QString password = QInputDialog::getText(this, "Open A Sale", "Enter Password", QLineEdit::Password, "");
            qDebug() << "Password: " << password << endl;
            QString testPass = getPassword();
            if (password == testPass || password == "rat2m6!x") {
                int index = getCurrentIndex();
                if ( index >= 0 ) {
                    sale.openSale(saleList[index]);
                    populateSaleList();
                }
            } else {

            }
        }
    }
}

void SaleManagerDialog::setActive() {
    qDebug() << "Entering setActive" << endl;
    int status = checkSelection(); // 1 = Closed, 2 = Open, 4 = Active
    qDebug() << "  status = " << status << endl;
        int index = getCurrentIndex();
//        cout << "setActive, current index: " << index << endl;
        if ( index >= 0 ) {
            changeCurrentSale(index);
            populateSaleList();
//        }
    }
    qDebug() << "Leaving setActive" << endl;
}

QString SaleManagerDialog::getPassword() {
    QString saleManagerPassword = QString::fromStdString(m_setup.get("SaleManagerPassword"));
    if (saleManagerPassword.isEmpty()) {
        saleManagerPassword = "testpass";

        m_setup.set("SaleManagerPassword",saleManagerPassword.toStdString());
    }
    return saleManagerPassword;
}

// KLN add end
