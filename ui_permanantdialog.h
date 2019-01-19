/********************************************************************************
** Form generated from reading UI file 'permanantdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PERMANANTDIALOG_H
#define UI_PERMANANTDIALOG_H

#include <Qt3Support/Q3ButtonGroup>
#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3GroupBox>
#include <Qt3Support/Q3ListBox>
#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <vector>
#include "dao/customerdao.h"

QT_BEGIN_NAMESPACE

class Ui_PermanantDialog
{
public:
    QLabel *textLabel3_9_2;
    QLabel *textLabel2_10;
    QLineEdit *permAddress2;
    QLabel *textLabel2_2_2;
    QLabel *textLabel1_5;
    QLabel *textLabel1_3;
    QLineEdit *permName;
    QLineEdit *permZip;
    QLabel *textLabel2_2;
    QLabel *companyLabel;
    QComboBox *letterComboBox;
    QLabel *textLabel3_3;
    QLabel *SSAN;
    QPushButton *printLabelsButton;
    QPushButton *permSave;
    QLineEdit *permCity;
    QPushButton *printPermButton;
    QLabel *textLabel1_2;
    QLineEdit *permCounty;
    QLineEdit *permAddress1;
    QLineEdit *permState;
    QLabel *textLabel1;
    QPushButton *deletePerm;
    Q3ButtonGroup *customerTypeButtonGroup;
    QRadioButton *sellerButton;
    QRadioButton *buyerButton;
    QLineEdit *permSSN;
    QLineEdit *permPhone;
    QLineEdit *permMortgage;
    QLineEdit *permCCNo;
    QLabel *currentDate;
    QLineEdit *permComment;
    QLabel *permNumberLabel;
    Q3ListBox *customers;
    QLineEdit *permNumberEdit;
    QCheckBox *permMadCow;
    QCheckBox *permBCouncil;
    QCheckBox *permMailList;
    QComboBox *relationsComboBox;

    void setupUi(QDialog *PermanantDialog)
    {
        if (PermanantDialog->objectName().isEmpty())
            PermanantDialog->setObjectName(QString::fromUtf8("PermanantDialog"));
        PermanantDialog->setWindowModality(Qt::ApplicationModal);
        PermanantDialog->resize(865, 599);
        QFont font;
        font.setPointSize(13);
        PermanantDialog->setFont(font);
        textLabel3_9_2 = new QLabel(PermanantDialog);
        textLabel3_9_2->setObjectName(QString::fromUtf8("textLabel3_9_2"));
        textLabel3_9_2->setGeometry(QRect(10, 10, 480, 64));
        textLabel3_9_2->setScaledContents(true);
        textLabel3_9_2->setAlignment(Qt::AlignVCenter);
        textLabel3_9_2->setWordWrap(false);
        textLabel3_9_2->setIndent(0);
        textLabel2_10 = new QLabel(PermanantDialog);
        textLabel2_10->setObjectName(QString::fromUtf8("textLabel2_10"));
        textLabel2_10->setGeometry(QRect(20, 250, 80, 21));
        textLabel2_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel2_10->setWordWrap(false);
        permAddress2 = new QLineEdit(PermanantDialog);
        permAddress2->setObjectName(QString::fromUtf8("permAddress2"));
        permAddress2->setGeometry(QRect(110, 170, 250, 31));
        textLabel2_2_2 = new QLabel(PermanantDialog);
        textLabel2_2_2->setObjectName(QString::fromUtf8("textLabel2_2_2"));
        textLabel2_2_2->setGeometry(QRect(-10, 210, 110, 30));
        textLabel2_2_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel2_2_2->setWordWrap(false);
        textLabel1_5 = new QLabel(PermanantDialog);
        textLabel1_5->setObjectName(QString::fromUtf8("textLabel1_5"));
        textLabel1_5->setGeometry(QRect(20, 90, 80, 30));
        textLabel1_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel1_5->setWordWrap(false);
        textLabel1_3 = new QLabel(PermanantDialog);
        textLabel1_3->setObjectName(QString::fromUtf8("textLabel1_3"));
        textLabel1_3->setGeometry(QRect(450, 550, 300, 30));
        textLabel1_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel1_3->setWordWrap(false);
        permName = new QLineEdit(PermanantDialog);
        permName->setObjectName(QString::fromUtf8("permName"));
        permName->setGeometry(QRect(110, 90, 250, 31));
        permZip = new QLineEdit(PermanantDialog);
        permZip->setObjectName(QString::fromUtf8("permZip"));
        permZip->setGeometry(QRect(300, 210, 60, 30));
        textLabel2_2 = new QLabel(PermanantDialog);
        textLabel2_2->setObjectName(QString::fromUtf8("textLabel2_2"));
        textLabel2_2->setGeometry(QRect(11, 130, 90, 30));
        textLabel2_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel2_2->setWordWrap(false);
        companyLabel = new QLabel(PermanantDialog);
        companyLabel->setObjectName(QString::fromUtf8("companyLabel"));
        companyLabel->setGeometry(QRect(363, 170, 110, 30));
        companyLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        companyLabel->setWordWrap(false);
        letterComboBox = new QComboBox(PermanantDialog);
        letterComboBox->setObjectName(QString::fromUtf8("letterComboBox"));
        letterComboBox->setGeometry(QRect(760, 550, 100, 30));
        textLabel3_3 = new QLabel(PermanantDialog);
        textLabel3_3->setObjectName(QString::fromUtf8("textLabel3_3"));
        textLabel3_3->setGeometry(QRect(5, 290, 100, 30));
        textLabel3_3->setWordWrap(false);
        SSAN = new QLabel(PermanantDialog);
        SSAN->setObjectName(QString::fromUtf8("SSAN"));
        SSAN->setGeometry(QRect(370, 130, 100, 30));
        SSAN->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        SSAN->setWordWrap(false);
        printLabelsButton = new QPushButton(PermanantDialog);
        printLabelsButton->setObjectName(QString::fromUtf8("printLabelsButton"));
        printLabelsButton->setGeometry(QRect(340, 550, 100, 31));
        printLabelsButton->setAutoDefault(false);
        permSave = new QPushButton(PermanantDialog);
        permSave->setObjectName(QString::fromUtf8("permSave"));
        permSave->setGeometry(QRect(10, 550, 100, 30));
        permSave->setAutoDefault(false);
        permCity = new QLineEdit(PermanantDialog);
        permCity->setObjectName(QString::fromUtf8("permCity"));
        permCity->setGeometry(QRect(110, 210, 130, 31));
        printPermButton = new QPushButton(PermanantDialog);
        printPermButton->setObjectName(QString::fromUtf8("printPermButton"));
        printPermButton->setGeometry(QRect(230, 550, 100, 30));
        printPermButton->setAutoDefault(false);
        textLabel1_2 = new QLabel(PermanantDialog);
        textLabel1_2->setObjectName(QString::fromUtf8("textLabel1_2"));
        textLabel1_2->setGeometry(QRect(368, 90, 110, 30));
        textLabel1_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel1_2->setWordWrap(false);
        permCounty = new QLineEdit(PermanantDialog);
        permCounty->setObjectName(QString::fromUtf8("permCounty"));
        permCounty->setGeometry(QRect(110, 250, 90, 30));
        permAddress1 = new QLineEdit(PermanantDialog);
        permAddress1->setObjectName(QString::fromUtf8("permAddress1"));
        permAddress1->setGeometry(QRect(110, 130, 250, 31));
        permState = new QLineEdit(PermanantDialog);
        permState->setObjectName(QString::fromUtf8("permState"));
        permState->setGeometry(QRect(250, 210, 40, 30));
        textLabel1 = new QLabel(PermanantDialog);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
        textLabel1->setGeometry(QRect(370, 210, 100, 30));
        textLabel1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel1->setWordWrap(false);
        deletePerm = new QPushButton(PermanantDialog);
        deletePerm->setObjectName(QString::fromUtf8("deletePerm"));
        deletePerm->setGeometry(QRect(120, 550, 100, 30));
        deletePerm->setAutoDefault(false);
        customerTypeButtonGroup = new Q3ButtonGroup(PermanantDialog);
        customerTypeButtonGroup->setObjectName(QString::fromUtf8("customerTypeButtonGroup"));
        customerTypeButtonGroup->setGeometry(QRect(680, 10, 180, 100));
        sellerButton = new QRadioButton(customerTypeButtonGroup);
        sellerButton->setObjectName(QString::fromUtf8("sellerButton"));
        sellerButton->setGeometry(QRect(10, 30, 130, 30));
        sellerButton->setChecked(true);
        buyerButton = new QRadioButton(customerTypeButtonGroup);
        buyerButton->setObjectName(QString::fromUtf8("buyerButton"));
        buyerButton->setGeometry(QRect(10, 60, 130, 30));
        buyerButton->setChecked(false);
        permSSN = new QLineEdit(PermanantDialog);
        permSSN->setObjectName(QString::fromUtf8("permSSN"));
        permSSN->setGeometry(QRect(480, 130, 190, 31));
        permSSN->setAlignment(Qt::AlignLeading);
        permPhone = new QLineEdit(PermanantDialog);
        permPhone->setObjectName(QString::fromUtf8("permPhone"));
        permPhone->setGeometry(QRect(480, 90, 190, 31));
        permPhone->setAlignment(Qt::AlignLeading);
        permMortgage = new QLineEdit(PermanantDialog);
        permMortgage->setObjectName(QString::fromUtf8("permMortgage"));
        permMortgage->setGeometry(QRect(480, 170, 380, 31));
        permMortgage->setAlignment(Qt::AlignLeading);
        permCCNo = new QLineEdit(PermanantDialog);
        permCCNo->setObjectName(QString::fromUtf8("permCCNo"));
        permCCNo->setGeometry(QRect(480, 210, 380, 31));
        permCCNo->setAlignment(Qt::AlignLeading);
        currentDate = new QLabel(PermanantDialog);
        currentDate->setObjectName(QString::fromUtf8("currentDate"));
        currentDate->setGeometry(QRect(510, 20, 150, 30));
        currentDate->setWordWrap(false);
        permComment = new QLineEdit(PermanantDialog);
        permComment->setObjectName(QString::fromUtf8("permComment"));
        permComment->setGeometry(QRect(110, 290, 570, 31));
        permNumberLabel = new QLabel(PermanantDialog);
        permNumberLabel->setObjectName(QString::fromUtf8("permNumberLabel"));
        permNumberLabel->setGeometry(QRect(210, 250, 70, 30));
        permNumberLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        permNumberLabel->setWordWrap(false);
        customers = new Q3ListBox(PermanantDialog);
        customers->setObjectName(QString::fromUtf8("customers"));
        customers->setGeometry(QRect(10, 350, 850, 190));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Bitstream Vera Sans Mono"));
        font1.setPointSize(13);
        customers->setFont(font1);
        customers->setFocusPolicy(Qt::NoFocus);
        customers->setColumnMode(Q3ListBox::FixedNumber);
        customers->setRowMode(Q3ListBox::Variable);
        customers->setVariableWidth(true);
        customers->setVariableHeight(false);
        permNumberEdit = new QLineEdit(PermanantDialog);
        permNumberEdit->setObjectName(QString::fromUtf8("permNumberEdit"));
        permNumberEdit->setGeometry(QRect(290, 250, 91, 31));
        permMadCow = new QCheckBox(PermanantDialog);
        permMadCow->setObjectName(QString::fromUtf8("permMadCow"));
        permMadCow->setGeometry(QRect(690, 250, 170, 30));
        permBCouncil = new QCheckBox(PermanantDialog);
        permBCouncil->setObjectName(QString::fromUtf8("permBCouncil"));
        permBCouncil->setGeometry(QRect(690, 280, 170, 30));
        permMailList = new QCheckBox(PermanantDialog);
        permMailList->setObjectName(QString::fromUtf8("permMailList"));
        permMailList->setGeometry(QRect(690, 310, 170, 30));
        relationsComboBox = new QComboBox(PermanantDialog);
        relationsComboBox->setObjectName(QString::fromUtf8("relationsComboBox"));
        relationsComboBox->setGeometry(QRect(420, 250, 211, 31));
        QWidget::setTabOrder(permName, permAddress1);
        QWidget::setTabOrder(permAddress1, permAddress2);
        QWidget::setTabOrder(permAddress2, permCity);
        QWidget::setTabOrder(permCity, permState);
        QWidget::setTabOrder(permState, permZip);
        QWidget::setTabOrder(permZip, permCounty);
        QWidget::setTabOrder(permCounty, permPhone);
        QWidget::setTabOrder(permPhone, permSSN);
        QWidget::setTabOrder(permSSN, permMortgage);
        QWidget::setTabOrder(permMortgage, permCCNo);
        QWidget::setTabOrder(permCCNo, permComment);
        QWidget::setTabOrder(permComment, permMadCow);
        QWidget::setTabOrder(permMadCow, permBCouncil);
        QWidget::setTabOrder(permBCouncil, permMailList);
        QWidget::setTabOrder(permMailList, permSave);
        QWidget::setTabOrder(permSave, deletePerm);
        QWidget::setTabOrder(deletePerm, printPermButton);

        retranslateUi(PermanantDialog);

        QMetaObject::connectSlotsByName(PermanantDialog);
    } // setupUi

    void retranslateUi(QDialog *PermanantDialog)
    {
        PermanantDialog->setWindowTitle(QApplication::translate("PermanantDialog", "Permanent F/M", 0, QApplication::UnicodeUTF8));
        textLabel3_9_2->setText(QApplication::translate("PermanantDialog", "<i><b><font size=\"+4\">Permanent File</font></b></i>", 0, QApplication::UnicodeUTF8));
        textLabel2_10->setText(QApplication::translate("PermanantDialog", "County:", 0, QApplication::UnicodeUTF8));
        textLabel2_2_2->setText(QApplication::translate("PermanantDialog", "City/St/Zip:", 0, QApplication::UnicodeUTF8));
        textLabel1_5->setText(QApplication::translate("PermanantDialog", "Name:", 0, QApplication::UnicodeUTF8));
        textLabel1_3->setText(QApplication::translate("PermanantDialog", "List Only Entries Starting With:", 0, QApplication::UnicodeUTF8));
        textLabel2_2->setText(QApplication::translate("PermanantDialog", "Address:", 0, QApplication::UnicodeUTF8));
        companyLabel->setText(QApplication::translate("PermanantDialog", "Company:", 0, QApplication::UnicodeUTF8));
        textLabel3_3->setText(QApplication::translate("PermanantDialog", "Comment:", 0, QApplication::UnicodeUTF8));
        SSAN->setText(QApplication::translate("PermanantDialog", "Tax ID:", 0, QApplication::UnicodeUTF8));
        printLabelsButton->setText(QApplication::translate("PermanantDialog", "&Labels", 0, QApplication::UnicodeUTF8));
        printLabelsButton->setShortcut(QApplication::translate("PermanantDialog", "Alt+L", 0, QApplication::UnicodeUTF8));
        permSave->setText(QApplication::translate("PermanantDialog", "Sa&ve", 0, QApplication::UnicodeUTF8));
        permSave->setShortcut(QApplication::translate("PermanantDialog", "Alt+V", 0, QApplication::UnicodeUTF8));
        printPermButton->setText(QApplication::translate("PermanantDialog", "&Print List", 0, QApplication::UnicodeUTF8));
        printPermButton->setShortcut(QApplication::translate("PermanantDialog", "Alt+P", 0, QApplication::UnicodeUTF8));
        textLabel1_2->setText(QApplication::translate("PermanantDialog", "AC/Phone:", 0, QApplication::UnicodeUTF8));
        textLabel1->setText(QApplication::translate("PermanantDialog", "CC #:", 0, QApplication::UnicodeUTF8));
        deletePerm->setText(QApplication::translate("PermanantDialog", "&Delete", 0, QApplication::UnicodeUTF8));
        deletePerm->setShortcut(QApplication::translate("PermanantDialog", "Alt+D", 0, QApplication::UnicodeUTF8));
        customerTypeButtonGroup->setTitle(QApplication::translate("PermanantDialog", "Customer Type", 0, QApplication::UnicodeUTF8));
        sellerButton->setText(QApplication::translate("PermanantDialog", "&Seller", 0, QApplication::UnicodeUTF8));
        sellerButton->setShortcut(QApplication::translate("PermanantDialog", "Alt+S", 0, QApplication::UnicodeUTF8));
        buyerButton->setText(QApplication::translate("PermanantDialog", "&Buyer", 0, QApplication::UnicodeUTF8));
        buyerButton->setShortcut(QApplication::translate("PermanantDialog", "Alt+B", 0, QApplication::UnicodeUTF8));
        permSSN->setText(QString());
        permPhone->setText(QString());
        currentDate->setText(QApplication::translate("PermanantDialog", "saleDate", 0, QApplication::UnicodeUTF8));
        permNumberLabel->setText(QApplication::translate("PermanantDialog", "Perm#:", 0, QApplication::UnicodeUTF8));
        permMadCow->setText(QApplication::translate("PermanantDialog", "Country Of Origin", 0, QApplication::UnicodeUTF8));
        permBCouncil->setText(QApplication::translate("PermanantDialog", "Beef Council", 0, QApplication::UnicodeUTF8));
        permMailList->setText(QApplication::translate("PermanantDialog", "Mailing List", 0, QApplication::UnicodeUTF8));
        relationsComboBox->clear();
        relationsComboBox->insertItems(0, QStringList()
         << QApplication::translate("PermanantDialog", "None", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("PermanantDialog", "Owner", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("PermanantDialog", "Officer", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("PermanantDialog", "Agent", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("PermanantDialog", "Employee", 0, QApplication::UnicodeUTF8)
        );
    } // retranslateUi

};

namespace Ui {
    class PermanantDialog: public Ui_PermanantDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PERMANANTDIALOG_H
