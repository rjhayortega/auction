/********************************************************************************
** Form generated from reading UI file 'auctiondatabasewizard.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUCTIONDATABASEWIZARD_H
#define UI_AUCTIONDATABASEWIZARD_H

#include <Qt3Support/Q3ButtonGroup>
#include <Qt3Support/Q3GroupBox>
#include <Qt3Support/Q3MimeSourceFactory>
#include <Qt3Support/Q3Wizard>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QRadioButton>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>
#include <Qt3Support/Q3Process>

QT_BEGIN_NAMESPACE

class Ui_AuctionDatabaseWizard
{
public:
    QWidget *WizardPage1;
    QLabel *textLabel1;
    QWidget *WizardPage2;
    QLabel *textLabel3_2;
    QSpinBox *portSpinbox;
    QLabel *textLabel3;
    QLineEdit *hostnameEdit;
    QWidget *WizardPage3;
    QLabel *textLabel4;
    QLabel *databaseLabel;
    QLineEdit *databaseEdit;
    QWidget *WizardPage4;
    QLabel *passwordLabel;
    QLabel *usernameLabel;
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QLabel *textLabel5;
    QWidget *WizardPage5;
    QLabel *authOkDisplay;
    QLabel *serverOkDisplay;
    QLabel *dbOkDisplay;
    QWidget *WizardPage6;
    QCheckBox *correctMyCNFCheckbox;
    Q3ButtonGroup *buttonGroup1;
    QRadioButton *radioButton3;
    QRadioButton *radioButton1;
    QRadioButton *radioButton1_2;

    void setupUi(Q3Wizard *AuctionDatabaseWizard)
    {
        if (AuctionDatabaseWizard->objectName().isEmpty())
            AuctionDatabaseWizard->setObjectName(QString::fromUtf8("AuctionDatabaseWizard"));
        AuctionDatabaseWizard->setWindowModality(Qt::ApplicationModal);
        AuctionDatabaseWizard->resize(555, 341);
        QFont font;
        font.setPointSize(13);
        AuctionDatabaseWizard->setFont(font);
        AuctionDatabaseWizard->setTitleFont(font);
        WizardPage1 = new QWidget(AuctionDatabaseWizard);
        WizardPage1->setObjectName(QString::fromUtf8("WizardPage1"));
        WizardPage1->setGeometry(QRect(6, 37, 543, 257));
        textLabel1 = new QLabel(WizardPage1);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
        textLabel1->setGeometry(QRect(10, 10, 540, 240));
        textLabel1->setFont(font);
        textLabel1->setAlignment(Qt::AlignCenter);
        textLabel1->setWordWrap(false);
        AuctionDatabaseWizard->addPage(WizardPage1, QString::fromUtf8("Welcome"));
        WizardPage2 = new QWidget(AuctionDatabaseWizard);
        WizardPage2->setObjectName(QString::fromUtf8("WizardPage2"));
        WizardPage2->setGeometry(QRect(6, 37, 543, 257));
        textLabel3_2 = new QLabel(WizardPage2);
        textLabel3_2->setObjectName(QString::fromUtf8("textLabel3_2"));
        textLabel3_2->setGeometry(QRect(130, 140, 330, 51));
        textLabel3_2->setAlignment(Qt::AlignCenter);
        textLabel3_2->setWordWrap(true);
        portSpinbox = new QSpinBox(WizardPage2);
        portSpinbox->setObjectName(QString::fromUtf8("portSpinbox"));
        portSpinbox->setGeometry(QRect(230, 210, 130, 31));
        portSpinbox->setMinimum(1);
        portSpinbox->setMaximum(99999);
        portSpinbox->setValue(3306);
        textLabel3 = new QLabel(WizardPage2);
        textLabel3->setObjectName(QString::fromUtf8("textLabel3"));
        textLabel3->setGeometry(QRect(130, 10, 330, 70));
        textLabel3->setAlignment(Qt::AlignCenter);
        textLabel3->setWordWrap(true);
        hostnameEdit = new QLineEdit(WizardPage2);
        hostnameEdit->setObjectName(QString::fromUtf8("hostnameEdit"));
        hostnameEdit->setGeometry(QRect(130, 90, 328, 30));
        AuctionDatabaseWizard->addPage(WizardPage2, QString::fromUtf8("Set Hostname"));
        WizardPage3 = new QWidget(AuctionDatabaseWizard);
        WizardPage3->setObjectName(QString::fromUtf8("WizardPage3"));
        WizardPage3->setGeometry(QRect(6, 37, 543, 257));
        textLabel4 = new QLabel(WizardPage3);
        textLabel4->setObjectName(QString::fromUtf8("textLabel4"));
        textLabel4->setGeometry(QRect(140, 70, 341, 51));
        textLabel4->setAlignment(Qt::AlignCenter);
        textLabel4->setWordWrap(true);
        databaseLabel = new QLabel(WizardPage3);
        databaseLabel->setObjectName(QString::fromUtf8("databaseLabel"));
        databaseLabel->setGeometry(QRect(136, 138, 75, 27));
        databaseLabel->setWordWrap(false);
        databaseEdit = new QLineEdit(WizardPage3);
        databaseEdit->setObjectName(QString::fromUtf8("databaseEdit"));
        databaseEdit->setGeometry(QRect(217, 138, 247, 27));
        AuctionDatabaseWizard->addPage(WizardPage3, QString::fromUtf8("Set database name"));
        WizardPage4 = new QWidget(AuctionDatabaseWizard);
        WizardPage4->setObjectName(QString::fromUtf8("WizardPage4"));
        WizardPage4->setGeometry(QRect(6, 37, 543, 257));
        passwordLabel = new QLabel(WizardPage4);
        passwordLabel->setObjectName(QString::fromUtf8("passwordLabel"));
        passwordLabel->setGeometry(QRect(130, 169, 75, 27));
        passwordLabel->setWordWrap(false);
        usernameLabel = new QLabel(WizardPage4);
        usernameLabel->setObjectName(QString::fromUtf8("usernameLabel"));
        usernameLabel->setGeometry(QRect(130, 130, 75, 27));
        usernameLabel->setWordWrap(false);
        usernameEdit = new QLineEdit(WizardPage4);
        usernameEdit->setObjectName(QString::fromUtf8("usernameEdit"));
        usernameEdit->setGeometry(QRect(210, 130, 247, 27));
        passwordEdit = new QLineEdit(WizardPage4);
        passwordEdit->setObjectName(QString::fromUtf8("passwordEdit"));
        passwordEdit->setGeometry(QRect(210, 170, 247, 27));
        textLabel5 = new QLabel(WizardPage4);
        textLabel5->setObjectName(QString::fromUtf8("textLabel5"));
        textLabel5->setGeometry(QRect(130, 20, 321, 91));
        textLabel5->setAlignment(Qt::AlignCenter);
        textLabel5->setWordWrap(true);
        AuctionDatabaseWizard->addPage(WizardPage4, QString::fromUtf8("Set username:password"));
        WizardPage5 = new QWidget(AuctionDatabaseWizard);
        WizardPage5->setObjectName(QString::fromUtf8("WizardPage5"));
        WizardPage5->setGeometry(QRect(6, 37, 543, 257));
        authOkDisplay = new QLabel(WizardPage5);
        authOkDisplay->setObjectName(QString::fromUtf8("authOkDisplay"));
        authOkDisplay->setEnabled(false);
        authOkDisplay->setGeometry(QRect(10, 60, 361, 30));
        authOkDisplay->setWordWrap(false);
        serverOkDisplay = new QLabel(WizardPage5);
        serverOkDisplay->setObjectName(QString::fromUtf8("serverOkDisplay"));
        serverOkDisplay->setEnabled(false);
        serverOkDisplay->setGeometry(QRect(10, 20, 361, 30));
        serverOkDisplay->setWordWrap(false);
        dbOkDisplay = new QLabel(WizardPage5);
        dbOkDisplay->setObjectName(QString::fromUtf8("dbOkDisplay"));
        dbOkDisplay->setEnabled(false);
        dbOkDisplay->setGeometry(QRect(10, 100, 361, 30));
        dbOkDisplay->setWordWrap(false);
        AuctionDatabaseWizard->addPage(WizardPage5, QString::fromUtf8("Test Connection"));
        WizardPage6 = new QWidget(AuctionDatabaseWizard);
        WizardPage6->setObjectName(QString::fromUtf8("WizardPage6"));
        correctMyCNFCheckbox = new QCheckBox(WizardPage6);
        correctMyCNFCheckbox->setObjectName(QString::fromUtf8("correctMyCNFCheckbox"));
        correctMyCNFCheckbox->setGeometry(QRect(10, 180, 521, 40));
        buttonGroup1 = new Q3ButtonGroup(WizardPage6);
        buttonGroup1->setObjectName(QString::fromUtf8("buttonGroup1"));
        buttonGroup1->setGeometry(QRect(16, 28, 520, 140));
        radioButton3 = new QRadioButton(buttonGroup1);
        radioButton3->setObjectName(QString::fromUtf8("radioButton3"));
        radioButton3->setGeometry(QRect(10, 100, 501, 31));
        radioButton1 = new QRadioButton(buttonGroup1);
        radioButton1->setObjectName(QString::fromUtf8("radioButton1"));
        radioButton1->setGeometry(QRect(10, 20, 490, 31));
        radioButton1_2 = new QRadioButton(buttonGroup1);
        radioButton1_2->setObjectName(QString::fromUtf8("radioButton1_2"));
        radioButton1_2->setGeometry(QRect(10, 60, 480, 31));
        AuctionDatabaseWizard->addPage(WizardPage6, QString::fromUtf8("Save Changes"));

        retranslateUi(AuctionDatabaseWizard);

        QMetaObject::connectSlotsByName(AuctionDatabaseWizard);
    } // setupUi

    void retranslateUi(Q3Wizard *AuctionDatabaseWizard)
    {
        AuctionDatabaseWizard->setWindowTitle(QApplication::translate("AuctionDatabaseWizard", "Set up an auction database", 0, QApplication::UnicodeUTF8));
        textLabel1->setText(QApplication::translate("AuctionDatabaseWizard", "This Wizard will help you set up your\n"
" auction database for the first time.\n"
"To begin setting up the database\n"
"press the \"Next\" button", 0, QApplication::UnicodeUTF8));
        AuctionDatabaseWizard->setTitle(WizardPage1, QApplication::translate("AuctionDatabaseWizard", "Welcome", 0, QApplication::UnicodeUTF8));
        textLabel3_2->setText(QApplication::translate("AuctionDatabaseWizard", "Enter the port number of the mysql server\n"
" (Default: 3306)", 0, QApplication::UnicodeUTF8));
        textLabel3->setText(QApplication::translate("AuctionDatabaseWizard", "Enter the name of the host where the mysql server is running. \n"
"(Default: localhost)", 0, QApplication::UnicodeUTF8));
        hostnameEdit->setText(QApplication::translate("AuctionDatabaseWizard", "localhost", 0, QApplication::UnicodeUTF8));
        AuctionDatabaseWizard->setTitle(WizardPage2, QApplication::translate("AuctionDatabaseWizard", "Set Hostname", 0, QApplication::UnicodeUTF8));
        textLabel4->setText(QApplication::translate("AuctionDatabaseWizard", "Enter the name of the database that the auction program will use (Default: auction6)", 0, QApplication::UnicodeUTF8));
        databaseLabel->setText(QApplication::translate("AuctionDatabaseWizard", "Database", 0, QApplication::UnicodeUTF8));
        databaseEdit->setText(QApplication::translate("AuctionDatabaseWizard", "auction6", 0, QApplication::UnicodeUTF8));
        AuctionDatabaseWizard->setTitle(WizardPage3, QApplication::translate("AuctionDatabaseWizard", "Set database name", 0, QApplication::UnicodeUTF8));
        passwordLabel->setText(QApplication::translate("AuctionDatabaseWizard", "Password", 0, QApplication::UnicodeUTF8));
        usernameLabel->setText(QApplication::translate("AuctionDatabaseWizard", "User Name", 0, QApplication::UnicodeUTF8));
        usernameEdit->setText(QApplication::translate("AuctionDatabaseWizard", "auction", 0, QApplication::UnicodeUTF8));
        passwordEdit->setText(QApplication::translate("AuctionDatabaseWizard", "auction", 0, QApplication::UnicodeUTF8));
        textLabel5->setText(QApplication::translate("AuctionDatabaseWizard", "Enter the credentials the auction program will use to identify itself to the database.\n"
" (Default: auction:auction)", 0, QApplication::UnicodeUTF8));
        AuctionDatabaseWizard->setTitle(WizardPage4, QApplication::translate("AuctionDatabaseWizard", "Set username:password", 0, QApplication::UnicodeUTF8));
        authOkDisplay->setText(QApplication::translate("AuctionDatabaseWizard", "x Authentication accepted", 0, QApplication::UnicodeUTF8));
        serverOkDisplay->setText(QApplication::translate("AuctionDatabaseWizard", "x Mysql server is running", 0, QApplication::UnicodeUTF8));
        dbOkDisplay->setText(QApplication::translate("AuctionDatabaseWizard", "x Database is present and of the correct format", 0, QApplication::UnicodeUTF8));
        AuctionDatabaseWizard->setTitle(WizardPage5, QApplication::translate("AuctionDatabaseWizard", "Test Connection", 0, QApplication::UnicodeUTF8));
        correctMyCNFCheckbox->setText(QApplication::translate("AuctionDatabaseWizard", "Correct the mysql server configuration file (my.cnf).", 0, QApplication::UnicodeUTF8));
        buttonGroup1->setTitle(QApplication::translate("AuctionDatabaseWizard", "Setup Options", 0, QApplication::UnicodeUTF8));
        radioButton3->setText(QApplication::translate("AuctionDatabaseWizard", "Write the configuration file only.", 0, QApplication::UnicodeUTF8));
        radioButton1->setText(QApplication::translate("AuctionDatabaseWizard", "Create The database, set up privileges, and write the configuration file.", 0, QApplication::UnicodeUTF8));
        radioButton1_2->setText(QApplication::translate("AuctionDatabaseWizard", "Set up privileges and write configuration files.", 0, QApplication::UnicodeUTF8));
        AuctionDatabaseWizard->setTitle(WizardPage6, QApplication::translate("AuctionDatabaseWizard", "Save Changes", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AuctionDatabaseWizard: public Ui_AuctionDatabaseWizard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUCTIONDATABASEWIZARD_H
