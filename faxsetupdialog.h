#ifndef FAXSETUPDIALOG_H
#define FAXSETUPDIALOG_H

#include <QDialog>
#include "dao/setupdao.h"

namespace Ui {
class FaxSetupDialog;
}

class FaxSetupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FaxSetupDialog(QWidget *parent = 0);
    ~FaxSetupDialog();

private slots:
    void saveSettings();

private:
    void init();
    Ui::FaxSetupDialog *ui;
    SetupDAO m_setup;
};

#endif // FAXSETUPDIALOG_H
