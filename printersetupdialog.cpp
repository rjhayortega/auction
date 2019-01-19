//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add delete ui;
//   delete moc include at end

#include "printersetupdialog.h"
#include "ui_printersetupdialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qcheckbox.h>
#include <Q3Table>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

#include <QProcess>
#include <QMessageBox>

PrinterSetupDialog::PrinterSetupDialog( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl ), ui(new Ui::PrinterSetupDialog)
{
    ui->setupUi(this);
    // signals and slots connections
    connect( ui->cancelButton, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( ui->saveButton, SIGNAL( clicked() ), this, SLOT( save() ) );
    connect( ui->refreshButton, SIGNAL( clicked() ), this, SLOT( getPrinterMenu() ) );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
PrinterSetupDialog::~PrinterSetupDialog()
{
    delete ui;
}

#include "dao/setupdao.h"

void PrinterSetupDialog::init()
{
    SetupDAO setup;
    connect(&lpstatProc, SIGNAL(readyReadStandardOutput()), this, SLOT(processLpstatData()));

    ui->printerMapTable->setColumnWidth(0, 135);
    ui->defaultPrinterTable->setColumnWidth(0, 135);
    ui->defaultPrinterTable->setColumnWidth(1, 135);

    getPrinterMenu();

    ui->CondensedFontCheckBox->setChecked( setup.getBoolean("printAllCondensed") );
}

void PrinterSetupDialog::loadPrinterData()
{
    QStringList tempMenu;

    for(int i  = 0; i < ui->printerMapTable->numRows(); i++)
    {
        tempMenu = printerMenu;
        if(i != PrinterDAO::Ticket && i != PrinterDAO::Scale)
        {
            tempMenu << "Default";
        }
        else tempMenu << "Default" << "None";

        ui->printerMapTable->setItem(i, 0, new Q3ComboTableItem(ui->printerMapTable, tempMenu));
        ((Q3ComboTableItem*)ui->printerMapTable->item(i, 0))->setCurrentItem(tempMenu[tempMenu.size() - 1]);
    }
    loadPrinterMapTable();

    printerMenu << "None";
    for(int i = 0; i < ui->defaultPrinterTable->numRows(); i++)
    {
        ui->defaultPrinterTable->setItem(i, 1, new Q3ComboTableItem(ui->defaultPrinterTable, printerMenu));
        ((Q3ComboTableItem*)ui->defaultPrinterTable->item(i, 1))->setCurrentItem("None");
    }
    loadDefaultPrinterTable();

    if(printerMenu.size() == 0)
    {
        ui->saveButton->setEnabled(false);
    }
    else
    {
        ui->saveButton->setEnabled(true);
    }
}

void PrinterSetupDialog::processLpstatData()
{
    lpstatBuffer += lpstatProc.readAllStandardOutput();
    QStringList menuItemCandidates = QStringList::split("\n", lpstatBuffer);
    QStringList menuItem;
    lpstatBuffer = "";
    for(int i = 0; i < menuItemCandidates.size(); i++)
    {
        menuItem = QStringList::split(" ", menuItemCandidates[i]);

        if(menuItem.size() > 0 && menuItem[0] == "printer")
        {
            printerMenu += menuItem[1];
        }
        else
        {
            lpstatBuffer += menuItemCandidates[i];
        }
    }


    loadPrinterData();
    setCursor(Qt::ArrowCursor);
    setEnabled(true);

}

void PrinterSetupDialog::getPrinterMenu()
{
    setEnabled(false);
    setCursor(Qt::WaitCursor);
    QStringList args;
    printerMenu.clear();
    QStringList menuItem;
    //cmd << "lpstat" << "-p";
    args << "-p";
    //lpstatProc.setArguments(cmd);
    //lpstatProc.setCommunication(QProcess::Stdout);

    lpstatProc.start("lpstat", args);
    if(!lpstatProc.waitForStarted())
    {
        setEnabled(true);
        setCursor(Qt::ArrowCursor);
        QMessageBox::information(this, "! ERROR !", "Could not retrieve the printer list");
        return;
    }
}

void PrinterSetupDialog::savePrinterMapTable()
{
    dao.savePrinter(PrinterDAO::SellerInvoice, ui->printerMapTable->text(0, 0).toStdString());
    dao.savePrinter(PrinterDAO::BuyerInvoice, ui->printerMapTable->text(1, 0).toStdString());
    dao.savePrinter(PrinterDAO::Check, ui->printerMapTable->text(2, 0).toStdString());
    dao.savePrinter(PrinterDAO::Report, ui->printerMapTable->text(3, 0).toStdString());

    QString printerName = ui->printerMapTable->text(4, 0);

    if(printerName == "Default")
    {
        printerName = "CDefault";
    }

    dao.savePrinter(PrinterDAO::Ticket, printerName.toStdString());

    printerName = ui->printerMapTable->text(5, 0);

    if(printerName == "Default")
    {
        printerName = "CDefault";
    }

    dao.savePrinter(PrinterDAO::Scale, printerName.toStdString());

    dao.savePrinter(PrinterDAO::CheckIn, ui->printerMapTable->text(6, 0).toStdString());
    dao.savePrinter(PrinterDAO::CheckInOffice, ui->printerMapTable->text(7, 0).toStdString());
    dao.savePrinter(PrinterDAO::Loadout, ui->printerMapTable->text(8, 0).toStdString());
    dao.savePrinter(PrinterDAO::SecondCopy, ui->printerMapTable->text(9, 0).toStdString());

}

void PrinterSetupDialog::saveDefaultPrinterTable()
{
    dao.clearDefaultPrinters();
    dao.saveDefaultPrinter("localhost", ui->defaultPrinterTable->text(0, 1).toStdString());

    for(int i = 1; i < ui->defaultPrinterTable->numRows(); i++)
    {
        dao.saveDefaultPrinter(ui->defaultPrinterTable->text(i, 0).toStdString(), ui->defaultPrinterTable->text(i, 1).toStdString());
    }
}

void PrinterSetupDialog::loadPrinterMapTable()
{
    vector<string> printerMap = dao.getPrinterNames();

    ((Q3ComboTableItem*)ui->printerMapTable->item(0, 0))->setCurrentItem(QString::fromStdString(printerMap[PrinterDAO::SellerInvoice]));
    ((Q3ComboTableItem*)ui->printerMapTable->item(1, 0))->setCurrentItem(QString::fromStdString(printerMap[PrinterDAO::BuyerInvoice]));
    ((Q3ComboTableItem*)ui->printerMapTable->item(2, 0))->setCurrentItem(QString::fromStdString(printerMap[PrinterDAO::Check]));
    ((Q3ComboTableItem*)ui->printerMapTable->item(3, 0))->setCurrentItem(QString::fromStdString(printerMap[PrinterDAO::Report]));

    if(printerMap[PrinterDAO::Ticket] == "Default")
    {
        printerMap[PrinterDAO::Ticket] = "None";
    }
    else if(printerMap[PrinterDAO::Ticket] == "CDefault")
    {
        printerMap[PrinterDAO::Ticket] = "Default";
    }

    if(printerMap[PrinterDAO::Scale] == "Default")
    {
        printerMap[PrinterDAO::Scale] = "None";
    }
    else if(printerMap[PrinterDAO::Scale] == "CDefault")
    {
        printerMap[PrinterDAO::Scale] = "Default";
    }


    ((Q3ComboTableItem*)ui->printerMapTable->item(4, 0))->setCurrentItem(QString::fromStdString(printerMap[PrinterDAO::Ticket]));
    ((Q3ComboTableItem*)ui->printerMapTable->item(5, 0))->setCurrentItem(QString::fromStdString(printerMap[PrinterDAO::Scale]));
    ((Q3ComboTableItem*)ui->printerMapTable->item(6, 0))->setCurrentItem(QString::fromStdString(printerMap[PrinterDAO::CheckIn]));
    ((Q3ComboTableItem*)ui->printerMapTable->item(7, 0))->setCurrentItem(QString::fromStdString(printerMap[PrinterDAO::CheckInOffice]));
    ((Q3ComboTableItem*)ui->printerMapTable->item(8, 0))->setCurrentItem(QString::fromStdString(printerMap[PrinterDAO::Loadout]));
    ((Q3ComboTableItem*)ui->printerMapTable->item(9, 0))->setCurrentItem(QString::fromStdString(printerMap[PrinterDAO::SecondCopy]));

}

void PrinterSetupDialog::loadDefaultPrinterTable()
{
    vector<PrinterDAO::DefaultPrinter> printerList = dao.getDefaultPrinterList();

    for(unsigned int i = 0; i < printerList.size(); i++)
    {
        ui->defaultPrinterTable->setText(i, 0, QString::fromStdString(printerList[i].station));
        ((Q3ComboTableItem*)ui->defaultPrinterTable->item(i, 1))->setCurrentItem(QString::fromStdString(printerList[i].printer));
    }
}

void PrinterSetupDialog::save()
{
    SetupDAO setup;
    savePrinterMapTable();
    saveDefaultPrinterTable();
    setup.setBoolean("printAllCondensed", ui->CondensedFontCheckBox->isChecked());

    QDialog::accept();
}

