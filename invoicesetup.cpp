//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add ui->setupUi(this);
//   Add delete ui;
//   delete moc include at end

#include "invoicesetup.h"
#include "ui_invoicesetup.h"

#include <qvariant.h>
#include <qcombobox.h>
#include <qcheckbox.h>
#include <qlabel.h>
#include <qspinbox.h>
#include <qgroupbox.h>
#include <Q3Table>
#include <qtextedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

InvoiceSetup::InvoiceSetup( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl ), ui(new Ui::InvoiceSetup)
{
    ui->setupUi(this);

    // signals and slots connections
    connect( ui->saveButton, SIGNAL( clicked() ), this, SLOT( save() ) );
    connect( ui->checkOnInvoice, SIGNAL( toggled(bool) ), this, SLOT( enableCheckOnInvoiceOptions(bool) ) );

    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
InvoiceSetup::~InvoiceSetup()
{
    delete ui;
}

void InvoiceSetup::init()
{
    dao = new SellerInvoiceDAO();
    ui->transTableSetup->setLeftMargin(0);
    for(int i = 0; i < ui->transTableSetup->numCols(); i++)
    {
        ui->transTableSetup->setColumnWidth(i, (ui->transTableSetup->width() / ui->transTableSetup->numCols()) - 1);
    }
}

void InvoiceSetup::init(Customer::Type custType)
{
    //TODO need to review double initialization, doesn't make sense.

    menu << "Trans" << "Head" << "Description" << "Tag" << "Customer" << "Pen" << "$/Head"
         << "Weight" << "Avg. Weight" << "$/HW" << "Amount" << "None";

    menu[TextInvoice::TransNo] = "Trans";
    menu[TextInvoice::Head] = "Head";
    menu[TextInvoice::Descrip] = "Description";
    menu[TextInvoice::Tags] = "Tags";
    menu[TextInvoice::CustomerNo] = "Customer";
    menu[TextInvoice::Pen] = "Pen";
    menu[TextInvoice::DolPerHd] = "$/Head";
    menu[TextInvoice::TotWt] = "Weight";
    menu[TextInvoice::AvgWt] = "Avg. Weight";
    menu[TextInvoice::DolPerCW] = "$/HW";
    menu[TextInvoice::Amount] = "Amount";
    menu[TextInvoice::ColumnCount] = "None";

    customerType = custType;

    switch(custType)
    {
    case Customer::Seller:
    default:
        dao = new SellerInvoiceDAO();
        menu[TextInvoice::CustomerNo] = "Buyer";
        ui->checkOnInvoice->show();
        ui->checkStartLine->show();
        ui->checkLineLabel->show();
        ui->secondCopyPrinterOption->show();
        ui->totalNSCheckBox->hide();
        ui->prorateInvoiceCheckBox->show();
        commentKey = "genSinvComment";
        disclaimerKey = "sinvFooterText";
        ui->averageOptionCheckBox->setText("Suppress Sex Summary");
        ui->brandOptionCheckBox->hide();
        ui->checkOnInvoiceGroup->show();
        showNumberKey = "sinvShowNumber";
        showCommentKey = "sinvShowTransactionComments";
        ui->checkPrinterOption->show();
        ui->averageOnLeftCheckBox->hide();
        ui->commissionDefaultCombo->hide();
        ui->commissionDefaultLabel->hide();
        groupChargesKey = "sinvGroupCharges";
//replaceAddressCoMatchKey = "sinvReplaceAddress";
        headerSizeKey = "sinvMinHeaderSize";
        transOverrideColumnKey = "sinvTransOverrideColumn";
        transOverrideLengthKey = "sinvTransOverrideLength";
        m_laserPrinterCopyCountKey = "sinvLaserCopyCount";
        ui->checkBoxLaserCheckTop->show();
        ui->checkBoxLaserCheckMiddle->show();
        ui->checkBoxLaserCheckBottom->show();
        ui->linesPerCheck->show();
        ui->showTagsAtBottomOfInvoiceCheckBox->hide();
        break;

    case Customer::Buyer:
        menu[TextInvoice::CustomerNo] = "Seller";
        dao = new BuyerInvoiceDAO();

        ui->checkOnInvoice->hide();
        ui->checkStartLine->hide();
        ui->checkLineLabel->hide();
        ui->secondCopyPrinterOption->hide();
        ui->totalNSCheckBox->show();
        ui->prorateInvoiceCheckBox->hide();
        commentKey = "genBinvComment";
        disclaimerKey = "binvFooterText";
        showNumberKey = "binvShowNumber";
        ui->averageOnLeftCheckBox->show();
        ui->brandOptionCheckBox->show();
        ui->checkOnInvoiceGroup->hide();
        showCommentKey = "binvShowTransactionComments";
        ui->checkPrinterOption->hide();
        ui->averageOptionCheckBox->setText("Show Sex Summary");
        ui->commissionDefaultCombo->show();
        ui->commissionDefaultLabel->show();
        groupChargesKey = "binvGroupCharges";
        replaceAddressCoMatchKey = "binvReplaceAddress";
        headerSizeKey = "binvMinHeaderSize";
        transOverrideColumnKey = "binvTransOverrideColumn";
        transOverrideLengthKey = "binvTransOverrideLength";
        m_laserPrinterCopyCountKey = "binvLaserCopyCount";
        ui->checkBoxLaserCheckTop->hide();
        ui->checkBoxLaserCheckMiddle->hide();
        ui->checkBoxLaserCheckBottom->hide();
        ui->linesPerCheck->hide();
        ui->linesPerCheckLabel->hide();
        ui->checkLineCopyLabel->hide();
        ui->checkLineStartCopy->hide();
        ui->secondCopyPrinterOption->hide();
        ui->secondCopyFrame->hide();
        ui->laserPrinterChecksOnlyPrintAtLabel->hide();
        ui->showTagsAtBottomOfInvoiceCheckBox->show();
        break;
    }

    for(int i = 0; i < ui->transTableSetup->numCols(); i++)
    {
        ui->transTableSetup->setItem(0, i, new Q3ComboTableItem(ui->transTableSetup, menu));
        ((Q3ComboTableItem*)ui->transTableSetup->item(0, i))->setCurrentItem(menu.size() - 1);
    }

    load();
}

void InvoiceSetup::destroy()
{
    if(dao != NULL)
    {
        delete dao;
    }
}

void InvoiceSetup::load()
{
    vector<int> colList = dao->getColumnList();

    for(unsigned int i = 0; i < colList.size(); i++)
    {
        if(colList[i] >= 0 && colList[i] < TextInvoice::ColumnCount)
        {
            ((Q3ComboTableItem*)ui->transTableSetup->item(0, i))->setCurrentItem(colList[i]);
        }
    }

    SetupDAO setup;
    ui->topSkip->setValue(dao->topSkip());
    ui->invoiceHeight->setValue(dao->pageHeight());
    ui->checkOnInvoice->setChecked(dao->checkOnInvoice());
    ui->checkStartLine->setValue(dao->checkStart());
    ui->checkLineStartCopy->setValue(atoi(setup.get("sinvChkStartCopy").c_str())); // [KLN] add
    ui->showNameBox->setChecked(dao->showName());
    ui->prorateInvoiceCheckBox->setChecked(bool(atol(setup.get("sinvFullInvoiceOnProrate").c_str())));
    ui->marketInvoiceComment->setText(QString::fromStdString(setup.get(commentKey)));
    ui->averageOptionCheckBox->setChecked(bool(atoi(setup.get((customerType == Customer::Seller ? "sinvShowSexAvgs" : "binvShowSexAvgs")).c_str())));
    ui->checkPrinterOption->setChecked(setup.getBoolean("sinvChkOnInvoiceToChkPrinter"));
    ui->secondCopyPrinterOption->setChecked(setup.getBoolean("sinvSecCopyPrinterEnabled"));

    string temp = setup.get(disclaimerKey);
    ui->marketInvoiceDisclaimer->setText(QString::fromStdString(temp));

    ui->minHeaderSizeSpin->setValue(atol(setup.get(headerSizeKey).c_str()));

    enableCheckOnInvoiceOptions(ui->checkOnInvoice->isChecked());
    ui->brandOptionCheckBox->setChecked(bool(atoi(setup.get("binvShowBrand").c_str())));
    ui->averageOnLeftCheckBox->setChecked(setup.getBoolean("binvOverallCWTOnRight"));

    ui->totalNSCheckBox->setChecked(setup.getBoolean("binvTotalNS"));
    ui->showNumberBox->setChecked(setup.getBoolean(showNumberKey));
    ui->showTransactionCommentBox->setChecked(setup.getBoolean(showCommentKey));

    ui->commissionDefaultCombo->setCurrentItem(atoi(setup.get("binvDefaultCommissionPayee").c_str()));

    ui->groupChargesBox->setChecked(setup.getBoolean(groupChargesKey));

    ui->transOverrideColumnSpin->setValue(atoi(setup.get(transOverrideColumnKey).c_str()));
    ui->transOverrideLengthSpin->setValue(atoi(setup.get(transOverrideLengthKey).c_str()));

    QString copyCountStr = QString::fromStdString(setup.get(m_laserPrinterCopyCountKey).c_str());
    ui->lpCopyCountSpinBox->setValue(copyCountStr.toInt());

    ui->checkBoxLaserCheckTop->setChecked(setup.getBoolean("sinvLaserCheckTop"));
    ui->checkBoxLaserCheckMiddle->setChecked(setup.getBoolean("sinvLaserCheckMiddle"));
    ui->checkBoxLaserCheckBottom->setChecked(setup.getBoolean("sinvLaserCheckBottom"));
    string lineCount = setup.get("sinvLinesPerCheck");
    if (lineCount.length() < 2) {
        lineCount = "20"; // use a rational default
    }
    ui->linesPerCheck->setText(QString::fromStdString(lineCount));
    ui->showTagsAtBottomOfInvoiceCheckBox->setChecked(setup.getBoolean("showTagsAtBottomOfInvoice"));
}

void InvoiceSetup::save()
{
    vector<int> columnList(TextInvoice::ColumnCount, TextInvoice::IgnoreCol);

    for(int i = 0; i < ui->transTableSetup->numCols(); i++)
    {
        int cur = ((Q3ComboTableItem*)ui->transTableSetup->item(0, i))->currentItem();
        if(cur != menu.size() - 1)
        {
            columnList[i]  = cur ;
        }
    }

    dao->saveColumnList(columnList);
    dao->setTopSkip(ui->topSkip->value());
    dao->setPageHeight(ui->invoiceHeight->value());
    SetupDAO setup;
    dao->setShowName(ui->showNameBox->isChecked());

    setup.set(headerSizeKey, QString::number(ui->minHeaderSizeSpin->value()).toStdString());

    if(customerType == Customer::Seller)
    {
        dao->setCheckOnInvoice(ui->checkOnInvoice->isChecked());
        dao->setCheckStart(ui->checkStartLine->value());
//        setup.set("clerkTicketLength", QString::number(ui->clerkTicketLengthBox->value()).toStdString());
        setup.set("sinvChkStartCopy", QString::number(ui->checkLineStartCopy->value()).toStdString()); // [KLN] add
        setup.set("sinvFullInvoiceOnProrate", QString::number(ui->prorateInvoiceCheckBox->isChecked()).toStdString());
        setup.setBoolean("sinvChkOnInvoiceToChkPrinter", ui->checkPrinterOption->isChecked());
        setup.setBoolean("sinvSecCopyPrinterEnabled", ui->secondCopyPrinterOption->isChecked());
        setup.setBoolean("sinvLaserCheckTop", ui->checkBoxLaserCheckTop->isChecked());
        setup.setBoolean("sinvLaserCheckMiddle", ui->checkBoxLaserCheckMiddle->isChecked());
        setup.setBoolean("sinvLaserCheckBottom", ui->checkBoxLaserCheckBottom->isChecked());
        setup.set("sinvLinesPerCheck", ui->linesPerCheck->text().toStdString());
    }
    else
    {
        setup.set("binvShowBrand", QString::number(int(ui->brandOptionCheckBox->isChecked())).toStdString());
        setup.setBoolean("binvOverallCWTOnRight", ui->averageOnLeftCheckBox->isChecked());
        char buf[3];
        sprintf(buf, "%d", ui->commissionDefaultCombo->currentItem());
        setup.set("binvDefaultCommissionPayee", buf);
        setup.setBoolean("binvTotalNS", ui->totalNSCheckBox->isChecked());
    }

    setup.set(commentKey, ui->marketInvoiceComment->text().toStdString());
    setup.set(disclaimerKey, ui->marketInvoiceDisclaimer->text().toStdString());
    char buf[3];
    sprintf(buf, "%d", ui->averageOptionCheckBox->isChecked());

    setup.set(((customerType == Customer::Seller ? "sinvShowSexAvgs" : "binvShowSexAvgs")), buf);
    setup.setBoolean(showNumberKey, ui->showNumberBox->isChecked());
    setup.setBoolean(showCommentKey, ui->showTransactionCommentBox->isChecked());
    setup.setBoolean(groupChargesKey, ui->groupChargesBox->isChecked());
    // disable until we figure out what to do with this 2009-06-19 rhw
    //setup.setBoolean(replaceAddressCoMatchKey, replaceAddressCoMatchBox->isChecked());
    setup.setBoolean(replaceAddressCoMatchKey, false);
    setup.set(transOverrideColumnKey, QString::number(ui->transOverrideColumnSpin->value()).toStdString());
    setup.set(transOverrideLengthKey, QString::number(ui->transOverrideLengthSpin->value()).toStdString());

    setup.set(m_laserPrinterCopyCountKey,QString::number(ui->lpCopyCountSpinBox->value()).toStdString());

    setup.setBoolean("showTagsAtBottomOfInvoice",ui->showTagsAtBottomOfInvoiceCheckBox->isChecked());

    QDialog::accept();
}


void InvoiceSetup::enableCheckOnInvoiceOptions(bool enable)
{
    ui->prorateInvoiceCheckBox->setEnabled(enable);
    ui->checkPrinterOption->setEnabled(enable);
    ui->checkLineLabel->setEnabled(enable);
    ui->checkStartLine->setEnabled(enable);
    ui->checkBoxLaserCheckTop->setEnabled(!enable);
    ui->checkBoxLaserCheckMiddle->setEnabled(!enable);
    ui->checkBoxLaserCheckBottom->setEnabled(!enable);
    ui->linesPerCheck->setEnabled(!enable);
}
