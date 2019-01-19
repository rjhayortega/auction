#include "salemanagersetupdialog.h"
#include "ui_salemanagersetupdialog.h"

SaleManagerSetupDialog::SaleManagerSetupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaleManagerSetupDialog)
{
    ui->setupUi(this);

    connect( ui->oldPasswordEdit, SIGNAL( returnPressed() ), this, SLOT( setOldPassword() ) );
    connect( ui->newPasswordEdit, SIGNAL( returnPressed() ), this, SLOT( setNewPassword() ) );
    connect( ui->verifyPasswordEdit, SIGNAL( returnPressed() ), this, SLOT( setVerifyPassword() ) );

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(savePressed()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(cancelPressed()));

    init();
}

SaleManagerSetupDialog::~SaleManagerSetupDialog()
{
    delete ui;
}

void SaleManagerSetupDialog::init()
{
    cout << "Entering init" << endl;

    // I need more time to figure out proper usage of a validator
//    // regexp: word chars, minimum of 6
//    QRegExp rx("^\\w{6,}&");
//    QValidator *validator = new QRegExpValidator(rx, this);
//    ui->newPasswordEdit->setValidator(validator);
//    ui->verifyPasswordEdit->setValidator(validator);

    ui->oldPasswordEdit->setEchoMode(QLineEdit::Password);
    ui->newPasswordEdit->setEchoMode(QLineEdit::Password);
    ui->verifyPasswordEdit->setEchoMode(QLineEdit::Password);

    oldPassword = "";
    newPassword = "";
    verifyPassword = "";
    passwordsMatch = false;
    saleManagerPassword = GetPassword();
    ui->newPasswordLabel->setHidden(false);
    ui->newPasswordEdit->setHidden(false);
    ui->verifyPasswordLabel->setHidden(false);
    ui->verifyPasswordEdit->setHidden(false);

    ui->errMsgLabel->setHidden(true);
    ui->oldPasswordEdit->setFocus();
    cout << "Leaving init" << endl;
}

QString SaleManagerSetupDialog::GetPassword() {
    QString pword = QString::fromStdString(m_setup.get("SaleManagerPassword"));
    if (pword.isEmpty()) {
        pword = "testpass";
        SetPassword(pword);
    }
    return pword;
}

void SaleManagerSetupDialog::SetPassword(QString pword) {
    m_setup.set("SaleManagerPassword",pword.toStdString());
}

void SaleManagerSetupDialog::setOldPassword() {
    cout << "Entering setOldPassword" << endl;
    oldPassword = ui->oldPasswordEdit->text();
    processOldPassword();
    cout << "Leaving setOldPassword" << endl;
}

void SaleManagerSetupDialog::setNewPassword() {
    cout << "Entering setNewPassword" << endl;
    newPassword = ui->newPasswordEdit->text();
    processNewPassword();
    cout << "Leaving setNewPassword" << endl;
}

void SaleManagerSetupDialog::setVerifyPassword() {
    cout << "Entering setVerifyPassword" << endl;
    verifyPassword = ui->verifyPasswordEdit->text();
    processVerifyPassword();
//    saveButton->setEnabled(true);
    cout << "Leaving setVerifyPassword" << endl;
}

void SaleManagerSetupDialog::processOldPassword()
{
    cout << "Entering processOldPassword" << endl;
    if (oldPassword.isEmpty()) {
        cout << "  OldPassword is empty." << endl;
        ui->errMsgLabel->setText("No password entered!");
        ui->errMsgLabel->setStyleSheet("border: 2px solid yellow");
        ui->errMsgLabel->setHidden(false);
        ui->oldPasswordEdit->setText("");
        ui->oldPasswordEdit->setFocus();
    } else if (oldPassword != saleManagerPassword) {
        cout << "  OldPassword does not match saved password." << endl;
        oldPassword = "";
        ui->errMsgLabel->setText("Password incorrect!");
        ui->errMsgLabel->setStyleSheet("border: 2px solid red");
        ui->errMsgLabel->setHidden(false);
        ui->oldPasswordEdit->setText("");
        ui->oldPasswordEdit->setFocus();
    } else {
        cout << "  OldPassword matches saved password." << endl;
        ui->errMsgLabel->setHidden(true);
        ui->newPasswordEdit->setFocus();
    }

    cout << "Leaving processOldPassword" << endl;
}

void SaleManagerSetupDialog::processNewPassword()
{
    cout << "Entering processNewPassword" << endl;
    if (newPassword.isEmpty()) {
        ui->errMsgLabel->setText("No password entered!");
        ui->errMsgLabel->setStyleSheet("border: 2px solid red");
        ui->errMsgLabel->setHidden(false);
        ui->newPasswordEdit->setText("");
        ui->newPasswordEdit->setFocus();
    } else if (newPassword == saleManagerPassword) {
        newPassword = "";
        ui->errMsgLabel->setText("Password same as current!");
        ui->errMsgLabel->setStyleSheet("border: 2px solid yellow");
        ui->errMsgLabel->setHidden(false);
        ui->newPasswordEdit->setText("");
        ui->newPasswordEdit->setFocus();
    } else {
        ui->errMsgLabel->setHidden(true);
        ui->verifyPasswordEdit->setFocus();
    }

    cout << "Leaving processNewPassword" << endl;
}

void SaleManagerSetupDialog::processVerifyPassword()
{
    cout << "Entering processVerifyPassword" << endl;
    if (verifyPassword.isEmpty() || verifyPassword != newPassword) {
        passwordsMatch = false;
        cout << "     newPassword: " << newPassword.toStdString() << endl;
        cout << "  verifyPassword: " << verifyPassword.toStdString() << endl;
        ui->errMsgLabel->setText("Passwords do not match!");
        ui->errMsgLabel->setStyleSheet("border: 2px solid red");
        ui->errMsgLabel->setHidden(false);
        ui->newPasswordEdit->setText("");
        ui->verifyPasswordEdit->setText("");
        ui->newPasswordEdit->setFocus();
    } else {
        ui->errMsgLabel->setText("Passwords match!");
        ui->errMsgLabel->setStyleSheet("border: 2px solid green");
        ui->errMsgLabel->setHidden(false);
//        ui->buttonBox->setEnabled(true);
//        ui->verifyPasswordEdit->setFocus();
        passwordsMatch = true;
    }
    cout << "Leaving processVerifyPassword" << endl;
}

void SaleManagerSetupDialog::saveSettings()
{
    cout << "Entering saveSettings" << endl;
    if (passwordsMatch) {
        cout << "  Changing password!" << " (new password: " << newPassword.toStdString() << endl;
        SetPassword(newPassword);
    }
    cout << "Leaving saveSettings" << endl;
}

void SaleManagerSetupDialog::savePressed()
{
    cout << "savePressed" << endl;
    if (passwordsMatch) {
        saveSettings();
        QDialog::accept();
    }
}

void SaleManagerSetupDialog::cancelPressed()
{
    cout << "cancelPressed" << endl;
    QDialog::reject();
}
