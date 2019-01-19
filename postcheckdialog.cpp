//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add delete ui;
//   delete moc include at end

#include "postcheckdialog.h"
#include "ui_postcheckdialog.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

PostCheckDialog::PostCheckDialog(QWidget* parent) : QDialog( parent)
{
    ui.setupUi(this);
    // signals and slots connections
    connect( ui.exitButton, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( ui.checkAmountEdit, SIGNAL( returnPressed() ), this, SLOT( proccessPost() ) );
    connect( ui.checkNoEdit, SIGNAL( returnPressed() ), this, SLOT( loadCheck() ) );

    // tab order
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
PostCheckDialog::~PostCheckDialog()
{

}

void PostCheckDialog::init()
{
} 


void PostCheckDialog::loadCheck()
{
    long checkNo = ui.checkNoEdit->text().toLong();

    vector<Check> checkList = checkDao.getCheckListByNumber(checkNo);
    check = Check();
    int outstandingCount = 0;

    for(unsigned int i = 0; i < checkList.size(); i++)
    {
        if(checkList[i].getStatus() == Check::Out)
        {
            outstandingCount++;
            check = checkList[i];
        }
    }

    if(check.getId() == 0)
    {
        QMessageBox::information(this, "Error",
                                 "No outstanding  checks with this number were found\n"
                                 "Can not post", QMessageBox::Ok);
        displayCheckInfo();
        return;
    }

    if(outstandingCount > 1)
    {
        check = getRealCheck(checkList);
    }

    if(check.getId() == 0)
    {
        ui.checkNoEdit->setFocus();
    }
    else
    {
        ui.checkAmountEdit->setFocus();
    }
    displayCheckInfo();
}

void PostCheckDialog::proccessPost()
{
    if(check.getId() == 0)
    {
        ui.checkNoEdit->setFocus();
    }
    else
    {
        double diff = check.getAmount() - ui.checkAmountEdit->text().toDouble();

        cout << diff << endl;
        if(diff > -0.00999999 && diff < 0.00999999)
        {
            checkDao.setCheckStatus(check, Check::Cleared);
        }
        else
        {
            QMessageBox::information(this, "Error",
                                     "Could not post.\n"
                                     "Entered amount: " + ui.checkAmountEdit->text() + ", does not match\n"
                                     "Check amount:   " + QString::number(check.getAmount(), 'f', 2) + "",
                                     QMessageBox::Ok);

            return;
        }
    }

    check = Check();
    displayCheckInfo();
    ui.checkNoEdit->setText("");
    ui.checkAmountEdit->setText("");
    ui.checkNoEdit->setFocus();
}

Check PostCheckDialog::getRealCheck(vector<Check> checkList)
{
    vector<Check> tempList;

    for(unsigned int i = 0; i < checkList.size(); i++)
    {
        if(checkList[i].getStatus() == Check::Out)
        {
            tempList.push_back(checkList[i]);
        }
    }

    QStringList checkStringList;

    for(unsigned int i = 0; i < tempList.size(); i++)
    {
        checkStringList += QString::fromStdString(tempList[i].getDate().toString("mm/dd/YYYY") + ", " + tempList[i].getPayee() + ", " + QString::number(tempList[i].getAmount(), 'f', 2).ascii());
    }

    bool ok;

    QString option = QInputDialog:: getItem("Multiple Checks",
                                            "There is more than one outstanding check with this number.\n"
                                            "Which of these checks are to be posted?",
                                            checkStringList, 0, false, &ok, this);

    Check realCheck;

    for(unsigned int i = 0; i < tempList.size() && ok && realCheck.getId() == 0; i++)
    {
        if(option == checkStringList[i])
        {
            realCheck = tempList[i];
        }
    }

    return realCheck;
}

void PostCheckDialog::displayCheckInfo()
{
    if(check.getId() == 0)
    {
        ui.checkDateDisplay->setText("");
        ui.checkPayeeDisplay->setText("");
        ui.checkAmountDisplay->setText("");
    }
    else
    {
        ui.checkDateDisplay->setText(QString::fromStdString(check.getDate().toString("mm/dd/YYYY")));
        ui.checkPayeeDisplay->setText(QString::fromStdString(check.getPayee()));
        ui.checkAmountDisplay->setText(QString::number(check.getAmount(), 'f', 2));
    }
}

