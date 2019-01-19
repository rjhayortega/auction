#ifndef SALEMANAGERSETUPDIALOG_H
#define SALEMANAGERSETUPDIALOG_H

#include <QDialog>
#include "dao/setupdao.h"
#include <QMessageBox>
#include <QPushButton>

namespace Ui {
class SaleManagerSetupDialog;
}

class SaleManagerSetupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SaleManagerSetupDialog(QWidget *parent = 0);
    ~SaleManagerSetupDialog();

private slots:
    void saveSettings();
//    void adjustFields(bool, int);

//    void accept();
//    void reject();

    void savePressed();
    void cancelPressed();

    void setOldPassword();
    void setNewPassword();
    void setVerifyPassword();

    QString GetPassword();
    void SetPassword(QString);

    void processOldPassword();
    void processNewPassword();
    void processVerifyPassword();

//    void on_oldPasswordEdit_returnPressed();

//    void on_newPasswordEdit_returnPressed();

//    void on_verifyPasswordEdit_returnPressed();

//    void on_saveButton_clicked();

//    void on_cancelButton_clicked();

private:
    void init();

    Ui::SaleManagerSetupDialog *ui;
    SetupDAO m_setup;

    QPushButton *saveButton;
    QPushButton *cancelButton;
    QString saleManagerPassword;
    QString oldPassword;
    QString newPassword;
    QString verifyPassword;
    bool passwordsMatch;

};

#endif // SALEMANAGERSETUPDIALOG_H
