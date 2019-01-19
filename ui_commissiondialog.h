/********************************************************************************
** Form generated from reading UI file 'commissiondialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMMISSIONDIALOG_H
#define UI_COMMISSIONDIALOG_H

#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3GroupBox>
#include <Qt3Support/Q3Header>
#include <Qt3Support/Q3ListBox>
#include <Qt3Support/Q3MimeSourceFactory>
#include <Qt3Support/Q3Table>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include "dao/animalcodedao.h"
#include "dao/commissiondao.h"
#include "Qt3Support/Q3ListViewItemIterator"

QT_BEGIN_NAMESPACE

class Ui_CommissionDialog
{
public:
    QPushButton *commResetButt;
    QPushButton *commDelButt;
    QLineEdit *noSaleEdit;
    Q3GroupBox *limitBox;
    QLineEdit *minEdit;
    QLabel *textLabel1_3_2_2_4;
    QLabel *textLabel1_3_2_2_4_2;
    QLineEdit *maxEdit;
    QLabel *textLabel1_3_2_2_3;
    QLabel *textLabel1;
    QLineEdit *codeRelLineEdit;
    Q3GroupBox *groupBox3;
    QComboBox *calculationMode;
    QPushButton *commSaveButt;
    QComboBox *colorComboBox;
    QLabel *messageArea;
    QLabel *textLabel1_3_2;
    QLabel *textLabel1_3_2_3;
    Q3Table *codeTable;
    QLabel *textLabel1_3;
    QLabel *textLabel1_2;
    Q3GroupBox *groupBox2_2;
    QComboBox *breakMode;
    QLineEdit *commissionDescriptionEdit;
    Q3ListBox *commissionListBox;
    QPushButton *testCommissionButton;

    void setupUi(QDialog *CommissionDialog)
    {
        if (CommissionDialog->objectName().isEmpty())
            CommissionDialog->setObjectName(QString::fromUtf8("CommissionDialog"));
        CommissionDialog->setWindowModality(Qt::ApplicationModal);
        CommissionDialog->resize(740, 533);
        QFont font;
        font.setPointSize(13);
        CommissionDialog->setFont(font);
        CommissionDialog->setMouseTracking(false);
        commResetButt = new QPushButton(CommissionDialog);
        commResetButt->setObjectName(QString::fromUtf8("commResetButt"));
        commResetButt->setGeometry(QRect(620, 480, 100, 30));
        commDelButt = new QPushButton(CommissionDialog);
        commDelButt->setObjectName(QString::fromUtf8("commDelButt"));
        commDelButt->setGeometry(QRect(180, 480, 100, 30));
        noSaleEdit = new QLineEdit(CommissionDialog);
        noSaleEdit->setObjectName(QString::fromUtf8("noSaleEdit"));
        noSaleEdit->setGeometry(QRect(490, 130, 70, 30));
        limitBox = new Q3GroupBox(CommissionDialog);
        limitBox->setObjectName(QString::fromUtf8("limitBox"));
        limitBox->setGeometry(QRect(400, 20, 160, 100));
        minEdit = new QLineEdit(limitBox);
        minEdit->setObjectName(QString::fromUtf8("minEdit"));
        minEdit->setGeometry(QRect(60, 20, 90, 30));
        textLabel1_3_2_2_4 = new QLabel(limitBox);
        textLabel1_3_2_2_4->setObjectName(QString::fromUtf8("textLabel1_3_2_2_4"));
        textLabel1_3_2_2_4->setGeometry(QRect(10, 20, 50, 30));
        textLabel1_3_2_2_4->setWordWrap(false);
        textLabel1_3_2_2_4_2 = new QLabel(limitBox);
        textLabel1_3_2_2_4_2->setObjectName(QString::fromUtf8("textLabel1_3_2_2_4_2"));
        textLabel1_3_2_2_4_2->setGeometry(QRect(10, 60, 50, 30));
        textLabel1_3_2_2_4_2->setWordWrap(false);
        maxEdit = new QLineEdit(limitBox);
        maxEdit->setObjectName(QString::fromUtf8("maxEdit"));
        maxEdit->setGeometry(QRect(60, 60, 90, 30));
        textLabel1_3_2_2_3 = new QLabel(CommissionDialog);
        textLabel1_3_2_2_3->setObjectName(QString::fromUtf8("textLabel1_3_2_2_3"));
        textLabel1_3_2_2_3->setGeometry(QRect(580, 100, 140, 30));
        textLabel1_3_2_2_3->setWordWrap(false);
        textLabel1 = new QLabel(CommissionDialog);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
        textLabel1->setGeometry(QRect(580, 20, 130, 30));
        textLabel1->setWordWrap(false);
        codeRelLineEdit = new QLineEdit(CommissionDialog);
        codeRelLineEdit->setObjectName(QString::fromUtf8("codeRelLineEdit"));
        codeRelLineEdit->setGeometry(QRect(580, 130, 140, 30));
        groupBox3 = new Q3GroupBox(CommissionDialog);
        groupBox3->setObjectName(QString::fromUtf8("groupBox3"));
        groupBox3->setGeometry(QRect(20, 20, 210, 90));
        calculationMode = new QComboBox(groupBox3);
        calculationMode->setObjectName(QString::fromUtf8("calculationMode"));
        calculationMode->setGeometry(QRect(10, 30, 190, 30));
        commSaveButt = new QPushButton(CommissionDialog);
        commSaveButt->setObjectName(QString::fromUtf8("commSaveButt"));
        commSaveButt->setGeometry(QRect(290, 480, 100, 30));
        colorComboBox = new QComboBox(CommissionDialog);
        colorComboBox->setObjectName(QString::fromUtf8("colorComboBox"));
        colorComboBox->setGeometry(QRect(580, 50, 130, 30));
        messageArea = new QLabel(CommissionDialog);
        messageArea->setObjectName(QString::fromUtf8("messageArea"));
        messageArea->setGeometry(QRect(460, 480, 151, 31));
        messageArea->setWordWrap(false);
        textLabel1_3_2 = new QLabel(CommissionDialog);
        textLabel1_3_2->setObjectName(QString::fromUtf8("textLabel1_3_2"));
        textLabel1_3_2->setGeometry(QRect(460, 170, 260, 31));
        textLabel1_3_2->setAlignment(Qt::AlignCenter);
        textLabel1_3_2->setWordWrap(false);
        textLabel1_3_2_3 = new QLabel(CommissionDialog);
        textLabel1_3_2_3->setObjectName(QString::fromUtf8("textLabel1_3_2_3"));
        textLabel1_3_2_3->setGeometry(QRect(420, 210, 31, 260));
        textLabel1_3_2_3->setAlignment(Qt::AlignCenter);
        textLabel1_3_2_3->setWordWrap(true);
        codeTable = new Q3Table(CommissionDialog);
        codeTable->setObjectName(QString::fromUtf8("codeTable"));
        codeTable->setGeometry(QRect(460, 210, 260, 260));
        codeTable->setMouseTracking(false);
        codeTable->setFocusPolicy(Qt::NoFocus);
        codeTable->setFrameShadow(QFrame::Raised);
        codeTable->setResizePolicy(Q3ScrollView::Manual);
        codeTable->setNumRows(10);
        codeTable->setNumCols(10);
        codeTable->setSelectionMode(Q3Table::NoSelection);
        codeTable->setFocusStyle(Q3Table::FollowStyle);
        textLabel1_3 = new QLabel(CommissionDialog);
        textLabel1_3->setObjectName(QString::fromUtf8("textLabel1_3"));
        textLabel1_3->setGeometry(QRect(400, 130, 80, 31));
        textLabel1_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel1_3->setWordWrap(false);
        textLabel1_2 = new QLabel(CommissionDialog);
        textLabel1_2->setObjectName(QString::fromUtf8("textLabel1_2"));
        textLabel1_2->setGeometry(QRect(180, 140, 211, 31));
        textLabel1_2->setWordWrap(false);
        groupBox2_2 = new Q3GroupBox(CommissionDialog);
        groupBox2_2->setObjectName(QString::fromUtf8("groupBox2_2"));
        groupBox2_2->setGeometry(QRect(20, 120, 150, 80));
        breakMode = new QComboBox(groupBox2_2);
        breakMode->setObjectName(QString::fromUtf8("breakMode"));
        breakMode->setGeometry(QRect(10, 30, 130, 30));
        commissionDescriptionEdit = new QLineEdit(CommissionDialog);
        commissionDescriptionEdit->setObjectName(QString::fromUtf8("commissionDescriptionEdit"));
        commissionDescriptionEdit->setGeometry(QRect(180, 170, 211, 31));
        commissionListBox = new Q3ListBox(CommissionDialog);
        commissionListBox->setObjectName(QString::fromUtf8("commissionListBox"));
        commissionListBox->setGeometry(QRect(20, 210, 370, 260));
        testCommissionButton = new QPushButton(CommissionDialog);
        testCommissionButton->setObjectName(QString::fromUtf8("testCommissionButton"));
        testCommissionButton->setEnabled(false);
        testCommissionButton->setGeometry(QRect(20, 480, 90, 31));
        QWidget::setTabOrder(minEdit, maxEdit);
        QWidget::setTabOrder(maxEdit, codeRelLineEdit);
        QWidget::setTabOrder(codeRelLineEdit, calculationMode);
        QWidget::setTabOrder(calculationMode, breakMode);
        QWidget::setTabOrder(breakMode, colorComboBox);
        QWidget::setTabOrder(colorComboBox, commSaveButt);
        QWidget::setTabOrder(commSaveButt, commResetButt);
        QWidget::setTabOrder(commResetButt, commDelButt);
        QWidget::setTabOrder(commDelButt, codeTable);

        retranslateUi(CommissionDialog);

        QMetaObject::connectSlotsByName(CommissionDialog);
    } // setupUi

    void retranslateUi(QDialog *CommissionDialog)
    {
        CommissionDialog->setWindowTitle(QApplication::translate("CommissionDialog", "Commission Edit", 0, QApplication::UnicodeUTF8));
        commResetButt->setText(QApplication::translate("CommissionDialog", "New", 0, QApplication::UnicodeUTF8));
        commDelButt->setText(QApplication::translate("CommissionDialog", "Delete", 0, QApplication::UnicodeUTF8));
        limitBox->setTitle(QApplication::translate("CommissionDialog", "Limits", 0, QApplication::UnicodeUTF8));
        textLabel1_3_2_2_4->setText(QApplication::translate("CommissionDialog", "Min", 0, QApplication::UnicodeUTF8));
        textLabel1_3_2_2_4_2->setText(QApplication::translate("CommissionDialog", "Max", 0, QApplication::UnicodeUTF8));
        textLabel1_3_2_2_3->setText(QApplication::translate("CommissionDialog", "Quick Fill", 0, QApplication::UnicodeUTF8));
        textLabel1->setText(QApplication::translate("CommissionDialog", "Color Code", 0, QApplication::UnicodeUTF8));
        groupBox3->setTitle(QApplication::translate("CommissionDialog", "Calculate", 0, QApplication::UnicodeUTF8));
        calculationMode->clear();
        calculationMode->insertItems(0, QStringList()
         << QApplication::translate("CommissionDialog", "By Transaction", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CommissionDialog", "By Invoice", 0, QApplication::UnicodeUTF8)
        );
        commSaveButt->setText(QApplication::translate("CommissionDialog", "Save", 0, QApplication::UnicodeUTF8));
        colorComboBox->clear();
        colorComboBox->insertItems(0, QStringList()
         << QApplication::translate("CommissionDialog", "0-69", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CommissionDialog", "70-79", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CommissionDialog", "80-89", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CommissionDialog", "90-99", 0, QApplication::UnicodeUTF8)
        );
        messageArea->setText(QString());
        textLabel1_3_2->setText(QApplication::translate("CommissionDialog", "Sex", 0, QApplication::UnicodeUTF8));
        textLabel1_3_2_3->setText(QApplication::translate("CommissionDialog", "F<BR>L<BR>A<BR>W", 0, QApplication::UnicodeUTF8));
        codeTable->horizontalHeader()->setLabel(0, QApplication::translate("CommissionDialog", "0", 0, QApplication::UnicodeUTF8));
        codeTable->horizontalHeader()->setLabel(1, QApplication::translate("CommissionDialog", "1", 0, QApplication::UnicodeUTF8));
        codeTable->horizontalHeader()->setLabel(2, QApplication::translate("CommissionDialog", "2", 0, QApplication::UnicodeUTF8));
        codeTable->horizontalHeader()->setLabel(3, QApplication::translate("CommissionDialog", "3", 0, QApplication::UnicodeUTF8));
        codeTable->horizontalHeader()->setLabel(4, QApplication::translate("CommissionDialog", "4", 0, QApplication::UnicodeUTF8));
        codeTable->horizontalHeader()->setLabel(5, QApplication::translate("CommissionDialog", "5", 0, QApplication::UnicodeUTF8));
        codeTable->horizontalHeader()->setLabel(6, QApplication::translate("CommissionDialog", "6", 0, QApplication::UnicodeUTF8));
        codeTable->horizontalHeader()->setLabel(7, QApplication::translate("CommissionDialog", "7", 0, QApplication::UnicodeUTF8));
        codeTable->horizontalHeader()->setLabel(8, QApplication::translate("CommissionDialog", "8", 0, QApplication::UnicodeUTF8));
        codeTable->horizontalHeader()->setLabel(9, QApplication::translate("CommissionDialog", "9", 0, QApplication::UnicodeUTF8));
        codeTable->verticalHeader()->setLabel(0, QApplication::translate("CommissionDialog", "0", 0, QApplication::UnicodeUTF8));
        codeTable->verticalHeader()->setLabel(1, QApplication::translate("CommissionDialog", "1", 0, QApplication::UnicodeUTF8));
        codeTable->verticalHeader()->setLabel(2, QApplication::translate("CommissionDialog", "2", 0, QApplication::UnicodeUTF8));
        codeTable->verticalHeader()->setLabel(3, QApplication::translate("CommissionDialog", "3", 0, QApplication::UnicodeUTF8));
        codeTable->verticalHeader()->setLabel(4, QApplication::translate("CommissionDialog", "4", 0, QApplication::UnicodeUTF8));
        codeTable->verticalHeader()->setLabel(5, QApplication::translate("CommissionDialog", "5", 0, QApplication::UnicodeUTF8));
        codeTable->verticalHeader()->setLabel(6, QApplication::translate("CommissionDialog", "6", 0, QApplication::UnicodeUTF8));
        codeTable->verticalHeader()->setLabel(7, QApplication::translate("CommissionDialog", "7", 0, QApplication::UnicodeUTF8));
        codeTable->verticalHeader()->setLabel(8, QApplication::translate("CommissionDialog", "8", 0, QApplication::UnicodeUTF8));
        codeTable->verticalHeader()->setLabel(9, QApplication::translate("CommissionDialog", "9", 0, QApplication::UnicodeUTF8));
        textLabel1_3->setText(QApplication::translate("CommissionDialog", "N/S Fee:", 0, QApplication::UnicodeUTF8));
        textLabel1_2->setText(QApplication::translate("CommissionDialog", "Commission Description", 0, QApplication::UnicodeUTF8));
        groupBox2_2->setTitle(QApplication::translate("CommissionDialog", "Break", 0, QApplication::UnicodeUTF8));
        breakMode->clear();
        breakMode->insertItems(0, QStringList()
         << QApplication::translate("CommissionDialog", "By Weight", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CommissionDialog", "By Head", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CommissionDialog", "By Price", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CommissionDialog", "By Total", 0, QApplication::UnicodeUTF8)
        );
        testCommissionButton->setText(QApplication::translate("CommissionDialog", "Test", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CommissionDialog: public Ui_CommissionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMMISSIONDIALOG_H
