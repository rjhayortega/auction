#include "faxsetupdialog.h"
#include "ui_faxsetupdialog.h"

FaxSetupDialog::FaxSetupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FaxSetupDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(saveSettings()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    init();
}

FaxSetupDialog::~FaxSetupDialog()
{
    delete ui;
}
void FaxSetupDialog::saveSettings()
{
    m_setup.setBoolean("faxModemEnabled",ui->enableFaxCheckBox->isChecked());
    accept();
}

void FaxSetupDialog::init()
{
    bool enableFaxModem = m_setup.getBoolean("faxModemEnabled");
    ui->enableFaxCheckBox->setChecked(enableFaxModem);

}

