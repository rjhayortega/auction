/********************************************************************************
** Form generated from reading UI file 'buyerrecapdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUYERRECAPDIALOG_H
#define UI_BUYERRECAPDIALOG_H

#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3Header>
#include <Qt3Support/Q3MimeSourceFactory>
#include <Qt3Support/Q3Table>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_BuyerRecapDialog
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    Q3Table *extraChargeTable;
    QLabel *textLabel5;
    QVBoxLayout *verticalLayout;
    QPushButton *allBuyersButton;
    QPushButton *generateReportButton;
    QPushButton *printReportButton;
    QPushButton *faxRecapButton;
    QSpacerItem *verticalSpacer;
    QLineEdit *nameEdit;
    QLabel *textLabel1;
    QLabel *textLabel4;
    QLineEdit *buyerEdit;
    QListWidget *buyerListBox;
    QCheckBox *consolidateBox;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *BuyerRecapDialog)
    {
        if (BuyerRecapDialog->objectName().isEmpty())
            BuyerRecapDialog->setObjectName(QString::fromUtf8("BuyerRecapDialog"));
        BuyerRecapDialog->setWindowModality(Qt::ApplicationModal);
        BuyerRecapDialog->resize(544, 327);
        QFont font;
        font.setPointSize(13);
        BuyerRecapDialog->setFont(font);
        gridLayout_2 = new QGridLayout(BuyerRecapDialog);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        extraChargeTable = new Q3Table(BuyerRecapDialog);
        extraChargeTable->setObjectName(QString::fromUtf8("extraChargeTable"));
        extraChargeTable->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(extraChargeTable->sizePolicy().hasHeightForWidth());
        extraChargeTable->setSizePolicy(sizePolicy);
        extraChargeTable->setResizePolicy(Q3ScrollView::Default);
        extraChargeTable->setNumRows(10);
        extraChargeTable->setNumCols(2);

        gridLayout->addWidget(extraChargeTable, 1, 3, 2, 1);

        textLabel5 = new QLabel(BuyerRecapDialog);
        textLabel5->setObjectName(QString::fromUtf8("textLabel5"));
        textLabel5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel5->setWordWrap(false);

        gridLayout->addWidget(textLabel5, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        allBuyersButton = new QPushButton(BuyerRecapDialog);
        allBuyersButton->setObjectName(QString::fromUtf8("allBuyersButton"));
        allBuyersButton->setAutoDefault(false);

        verticalLayout->addWidget(allBuyersButton);

        generateReportButton = new QPushButton(BuyerRecapDialog);
        generateReportButton->setObjectName(QString::fromUtf8("generateReportButton"));
        generateReportButton->setAutoDefault(false);

        verticalLayout->addWidget(generateReportButton);

        printReportButton = new QPushButton(BuyerRecapDialog);
        printReportButton->setObjectName(QString::fromUtf8("printReportButton"));
        printReportButton->setAutoDefault(false);

        verticalLayout->addWidget(printReportButton);

        faxRecapButton = new QPushButton(BuyerRecapDialog);
        faxRecapButton->setObjectName(QString::fromUtf8("faxRecapButton"));
        faxRecapButton->setAutoDefault(false);

        verticalLayout->addWidget(faxRecapButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        gridLayout->addLayout(verticalLayout, 2, 1, 1, 1);

        nameEdit = new QLineEdit(BuyerRecapDialog);
        nameEdit->setObjectName(QString::fromUtf8("nameEdit"));

        gridLayout->addWidget(nameEdit, 0, 1, 1, 2);

        textLabel1 = new QLabel(BuyerRecapDialog);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
        textLabel1->setWordWrap(false);

        gridLayout->addWidget(textLabel1, 0, 3, 1, 1);

        textLabel4 = new QLabel(BuyerRecapDialog);
        textLabel4->setObjectName(QString::fromUtf8("textLabel4"));
        textLabel4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel4->setWordWrap(false);

        gridLayout->addWidget(textLabel4, 1, 0, 1, 1);

        buyerEdit = new QLineEdit(BuyerRecapDialog);
        buyerEdit->setObjectName(QString::fromUtf8("buyerEdit"));

        gridLayout->addWidget(buyerEdit, 1, 1, 1, 1);

        buyerListBox = new QListWidget(BuyerRecapDialog);
        buyerListBox->setObjectName(QString::fromUtf8("buyerListBox"));

        gridLayout->addWidget(buyerListBox, 1, 2, 2, 1);

        consolidateBox = new QCheckBox(BuyerRecapDialog);
        consolidateBox->setObjectName(QString::fromUtf8("consolidateBox"));

        gridLayout->addWidget(consolidateBox, 3, 1, 1, 3);

        gridLayout->setColumnStretch(3, 10);
        gridLayout->setColumnMinimumWidth(3, 150);

        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 1, 1, 1);

        QWidget::setTabOrder(nameEdit, buyerEdit);
        QWidget::setTabOrder(buyerEdit, generateReportButton);

        retranslateUi(BuyerRecapDialog);

        QMetaObject::connectSlotsByName(BuyerRecapDialog);
    } // setupUi

    void retranslateUi(QDialog *BuyerRecapDialog)
    {
        BuyerRecapDialog->setWindowTitle(QApplication::translate("BuyerRecapDialog", "Generate Buyer Recap", 0, QApplication::UnicodeUTF8));
        extraChargeTable->horizontalHeader()->setLabel(0, QApplication::translate("BuyerRecapDialog", "Description", 0, QApplication::UnicodeUTF8));
        extraChargeTable->horizontalHeader()->setLabel(1, QApplication::translate("BuyerRecapDialog", "Amount", 0, QApplication::UnicodeUTF8));
        extraChargeTable->verticalHeader()->setLabel(0, QApplication::translate("BuyerRecapDialog", "1", 0, QApplication::UnicodeUTF8));
        extraChargeTable->verticalHeader()->setLabel(1, QApplication::translate("BuyerRecapDialog", "2", 0, QApplication::UnicodeUTF8));
        extraChargeTable->verticalHeader()->setLabel(2, QApplication::translate("BuyerRecapDialog", "3", 0, QApplication::UnicodeUTF8));
        extraChargeTable->verticalHeader()->setLabel(3, QApplication::translate("BuyerRecapDialog", "4", 0, QApplication::UnicodeUTF8));
        extraChargeTable->verticalHeader()->setLabel(4, QApplication::translate("BuyerRecapDialog", "5", 0, QApplication::UnicodeUTF8));
        extraChargeTable->verticalHeader()->setLabel(5, QApplication::translate("BuyerRecapDialog", "6", 0, QApplication::UnicodeUTF8));
        extraChargeTable->verticalHeader()->setLabel(6, QApplication::translate("BuyerRecapDialog", "7", 0, QApplication::UnicodeUTF8));
        extraChargeTable->verticalHeader()->setLabel(7, QApplication::translate("BuyerRecapDialog", "8", 0, QApplication::UnicodeUTF8));
        extraChargeTable->verticalHeader()->setLabel(8, QApplication::translate("BuyerRecapDialog", "9", 0, QApplication::UnicodeUTF8));
        extraChargeTable->verticalHeader()->setLabel(9, QApplication::translate("BuyerRecapDialog", "10", 0, QApplication::UnicodeUTF8));
        textLabel5->setText(QApplication::translate("BuyerRecapDialog", "Name", 0, QApplication::UnicodeUTF8));
        allBuyersButton->setText(QApplication::translate("BuyerRecapDialog", "&All", 0, QApplication::UnicodeUTF8));
        allBuyersButton->setShortcut(QApplication::translate("BuyerRecapDialog", "Alt+A", 0, QApplication::UnicodeUTF8));
        generateReportButton->setText(QApplication::translate("BuyerRecapDialog", "Pre&view", 0, QApplication::UnicodeUTF8));
        generateReportButton->setShortcut(QApplication::translate("BuyerRecapDialog", "Alt+V", 0, QApplication::UnicodeUTF8));
        printReportButton->setText(QApplication::translate("BuyerRecapDialog", "&Print", 0, QApplication::UnicodeUTF8));
        printReportButton->setShortcut(QApplication::translate("BuyerRecapDialog", "Alt+P", 0, QApplication::UnicodeUTF8));
        faxRecapButton->setText(QApplication::translate("BuyerRecapDialog", "&Fax", 0, QApplication::UnicodeUTF8));
        faxRecapButton->setShortcut(QApplication::translate("BuyerRecapDialog", "Alt+P", 0, QApplication::UnicodeUTF8));
        textLabel1->setText(QApplication::translate("BuyerRecapDialog", "Extra Recap Charges", 0, QApplication::UnicodeUTF8));
        textLabel4->setText(QApplication::translate("BuyerRecapDialog", "Buyer ID", 0, QApplication::UnicodeUTF8));
        consolidateBox->setText(QApplication::translate("BuyerRecapDialog", "Consolidate Charges?", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class BuyerRecapDialog: public Ui_BuyerRecapDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUYERRECAPDIALOG_H
