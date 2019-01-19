//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add ui->setupUi(this);
//   Add delete ui;
//   delete moc include at end

#include "clerksetupdialog.h"
#include "ui_clerksetupdialog.h"

#include <qvariant.h>
#include <qgroupbox.h>
#include <Q3Table>
#include <qcheckbox.h>
#include <qlabel.h>
#include <qspinbox.h>
#include <qbuttongroup.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

ClerkSetupDialog::ClerkSetupDialog( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl ), ui(new Ui::ClerkSetupDialog)
{
    ui->setupUi(this);
    // signals and slots connections
    connect( ui->cancelButton, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( ui->acceptButton, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( ui->ticketFormatCheckBox, SIGNAL( toggled(bool) ), this, SLOT( enableAlternateTicketOption(bool) ) );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
ClerkSetupDialog::~ClerkSetupDialog()
{
    delete ui;
}

void ClerkSetupDialog::init()
{
    QStringList menu;
    menu << "Head"<< "Weight"<< "Seller" << "Seller Pen" << "Description" << "Buyer"
         << "Buyer Pen" << "Bid" << "Tag" << "Mode" << "None";

    keyList << "cOrderHead" << "cOrderWeight" << "cOrderSeller" << "cOrderSPen" << "cOrderDesc"
            << "cOrderBuyer" << "cOrderBPen" << "cOrderBid" << "cOrderTag" << "cOrderMode";
    ui->clerkInputTable->setColumnWidth(0, ui->clerkInputTable->width() - 50);
    for(int i = 0; i < ui->clerkInputTable->numRows(); i++)
    {
        ui->clerkInputTable->setItem(i, 0, new Q3ComboTableItem(ui->clerkInputTable, menu));
        ((Q3ComboTableItem*)ui->clerkInputTable->item(i, 0))->setCurrentItem(menu.size() - 1);
    }

    loadClerkSetup();
    loadPennerSetup();
}

void ClerkSetupDialog::loadClerkSetup()
{
    int current;
    for(int i = 0; i < keyList.size(); i++)
    {
        current = atoi(setup.get(keyList[i].toStdString()).c_str());
        current = (current > 0 && current <= keyList.size() ? current - 1 : keyList.size());

        if( current < keyList.size())
        {
            ((Q3ComboTableItem*)ui->clerkInputTable->item(current, 0))->setCurrentItem(i);
        }
    }

    ui->clerkBuyerNamesCheckBox->setChecked(bool(atoi(setup.get("clerkEnterBuyerName").c_str())));
    ui->clerkTicketLengthBox->setValue(atoi(setup.get("clerkTicketLength").c_str()));
    ui->clerkTicketTopSkipLinesBox->setValue(atoi(setup.get("clerkSkipLinesFromTop").c_str()));
    ui->tagSearchBox->setChecked(bool(atoi(setup.get("clerkSearchTagForSeller").c_str())));
    ui->skipSellerIfFoundBox->setChecked(atoi(setup.get("clerkSkipSellerIfFound").c_str()));
    ui->sellerOnTicketBox->setChecked(bool(atoi(setup.get("clerkSellerOnTicket").c_str())));
    ui->ticketFormatCheckBox->setChecked(setup.getBoolean("clerkAlternateTicket1"));
    ui->ticketHeadingEdit->setText(QString::fromStdString(setup.get("clerkTicketHeading")));
    enableAlternateTicketOption(ui->ticketFormatCheckBox->isChecked());
    ui->printPermBuyersCheckBox->setChecked(setup.getBoolean("clerkPrintPermBuyers"));
    ui->zeroBalNotifycheckBox->setChecked(setup.getBoolean("clerkZeroBalNotify"));
    ui->scaleMaxWeightTextEdit->setText(QString::fromStdString(setup.get("clerkScaleMaxWeight")));
    enableZeroBalNotifyOption(ui->zeroBalNotifycheckBox->isChecked());
    ui->clerkLoadLastSellerNumberCheckBox->setChecked(setup.getBoolean("clerkLoadLastSellerNumber"));

    bool presort = false;
    if ( setup.get("clerkPresortDefault") == ""  ) {
        presort = false; // default to FALSE if doesn't exist (this is almost everyone!)
    } else {
        presort = setup.getBoolean("clerkPresortDefault");
    }
//    cout << "presort: " << presort << endl;
    ui->presortCheckBox->setChecked(presort);

    bool sellingLeft = true; // Most customers have Selling on the left side of the display
    if ( setup.get("clerkSellingOnLeft") == ""  ) {
        sellingLeft = true; // default to FALSE if doesn't exist (this is almost everyone!)
    } else {
        sellingLeft = setup.getBoolean("clerkSellingOnLeft");
    }
    ui->sellingOnLeftcheckBox->setChecked(sellingLeft);

}

void ClerkSetupDialog::enableAlternateTicketOption(bool enable)
{
    if(enable){}; // stop compile error
    ui->ticketHeadingEdit->setEnabled(ui->ticketFormatCheckBox->isChecked());
    ui->ticketHeadingLabel->setEnabled(ui->ticketFormatCheckBox->isChecked());
}

void ClerkSetupDialog::enableZeroBalNotifyOption(bool enable)
{
    if(enable){}; // stop compile error
    ui->scaleMaxWeightlabel->setEnabled(ui->zeroBalNotifycheckBox->isChecked());
    ui->scaleMaxWeightTextEdit->setEnabled(ui->zeroBalNotifycheckBox->isChecked());
}

void ClerkSetupDialog::loadPennerSetup()
{
    ui->pennerBidEditable->    setChecked(bool(atoi(setup.get("pennerBidEditable")    .c_str())));
    ui->pennerBuyerEditable->setChecked(bool(atoi(setup.get("pennerBuyerEditable").c_str())));
    ui->pennerPenEditable->   setChecked(bool(atoi(setup.get("pennerPenEditable")  .c_str())));
}

void ClerkSetupDialog::accept()
{
    saveClerkSetup();
    savePennerSetup();
    QDialog::accept();
}

void ClerkSetupDialog::saveClerkSetup()
{
    int currentItem;

    for(int i = 0; i < keyList.size(); i++)
    {
        setup.set(keyList[i].toStdString(), "Unused");
    }

    for(int i = 0; i < ui->clerkInputTable->numRows(); i++)
    {
        currentItem = ((Q3ComboTableItem*)ui->clerkInputTable->item(i, 0))->currentItem();

        if(0 <= currentItem && currentItem < keyList.size())
        {
            setup.set(keyList[currentItem].toStdString(), QString::number(i + 1).toStdString());
        }
    }

    setup.set("clerkEnterBuyerName", QString::number(int(ui->clerkBuyerNamesCheckBox->isChecked())).toStdString());;
    setup.set("clerkTicketLength", QString::number(ui->clerkTicketLengthBox->value()).toStdString());
    setup.set("clerkSkipLinesFromTop", QString::number(ui->clerkTicketTopSkipLinesBox->value()).toStdString());
    setup.set("clerkSearchTagForSeller", QString::number(int(ui->tagSearchBox->isChecked())).toStdString());
    setup.set("clerkSkipSellerIfFound", QString::number(int(ui->skipSellerIfFoundBox->isChecked())).toStdString());
    setup.set("clerkSellerOnTicket", QString::number(int(ui->sellerOnTicketBox->isChecked())).toStdString());
    setup.setBoolean("clerkAlternateTicket1", ui->ticketFormatCheckBox->isChecked());
    setup.set("clerkTicketHeading", ui->ticketHeadingEdit->text().toStdString());
    setup.setBoolean("clerkPrintPermBuyers",  ui->printPermBuyersCheckBox->isChecked());
    setup.setBoolean("clerkZeroBalNotify",  ui->zeroBalNotifycheckBox->isChecked());
    setup.set("clerkScaleMaxWeight", ui->scaleMaxWeightTextEdit->text().toStdString());
    setup.setBoolean("clerkPresortDefault", ui->presortCheckBox->isChecked());
    setup.setBoolean("clerkLoadLastSellerNumber", ui->clerkLoadLastSellerNumberCheckBox->isChecked());
    setup.setBoolean("clerkSellingOnLeft", ui->sellingOnLeftcheckBox->isChecked());
}

void ClerkSetupDialog::savePennerSetup()
{
    setup.set("pennerBidEditable", QString::number(int(ui->pennerBidEditable->isChecked())).toStdString());
    setup.set("pennerBuyerEditable", QString::number(int(ui->pennerBuyerEditable->isChecked())).toStdString());
    setup.set("pennerPenEditable",  QString::number(int(ui->pennerPenEditable->isChecked())).toStdString());
}

void ClerkSetupDialog::on_zeroBalNotifycheckBox_toggled(bool checked)
{
    ui->scaleMaxWeightlabel->setEnabled(checked);
    ui->scaleMaxWeightTextEdit->setEnabled(checked);

}
