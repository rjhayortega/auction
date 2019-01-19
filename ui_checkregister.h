/********************************************************************************
** Form generated from reading UI file 'checkregister.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHECKREGISTER_H
#define UI_CHECKREGISTER_H

#include <Qt3Support/Q3ButtonGroup>
#include <Qt3Support/Q3DateEdit>
#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3GroupBox>
#include <Qt3Support/Q3Header>
#include <Qt3Support/Q3ListView>
#include <Qt3Support/Q3MimeSourceFactory>
#include <Qt3Support/Q3Table>
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
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>
#include <vector>
#include "dao/checkdao.h"
#include "dao/salemanager.h"
#include "dao/setupdao.h"

QT_BEGIN_NAMESPACE

class Ui_CheckRegister
{
public:
    QPushButton *deleteChecksButtons;
    Q3GroupBox *groupBox1;
    QPushButton *buttonClearSel;
    QPushButton *buttonVoidSel;
    QPushButton *buttonOutSel;
    Q3Table *tabSummary;
    Q3ButtonGroup *filterGroup;
    QRadioButton *dateOption;
    Q3DateEdit *registerFromDate;
    QCheckBox *showOutBox;
    QCheckBox *showVoidBox;
    QCheckBox *showClearBox;
    Q3DateEdit *registerToDate;
    QLabel *textLabel1_2;
    QLabel *textLabel1_2_2;
    QLineEdit *toNumberEdit;
    QLineEdit *fromNumberEdit;
    QRadioButton *numberOption;
    QPushButton *buttonReport;
    QPushButton *buttonNewDep;
    QPushButton *postChecksButton;
    QPushButton *buttChkNo;
    QPushButton *buttonNewChk;
    QPushButton *buttonDone;
    QTabWidget *tabChecks;
    QWidget *tab_chks;
    QLabel *textLabel1_2_3;
    QPushButton *searchButton;
    QComboBox *indexCombo;
    QLineEdit *searchEdit;
    QLabel *textLabel1;
    QLineEdit *payeeFilterEdit;
    Q3Table *checkTable;
    QWidget *tab_dep;
    Q3ListView *listViewDeposits;

    void setupUi(QDialog *CheckRegister)
    {
        if (CheckRegister->objectName().isEmpty())
            CheckRegister->setObjectName(QString::fromUtf8("CheckRegister"));
        CheckRegister->setWindowModality(Qt::ApplicationModal);
        CheckRegister->resize(894, 634);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CheckRegister->sizePolicy().hasHeightForWidth());
        CheckRegister->setSizePolicy(sizePolicy);
        CheckRegister->setMinimumSize(QSize(800, 600));
        CheckRegister->setBaseSize(QSize(800, 600));
        QFont font;
        font.setPointSize(13);
        CheckRegister->setFont(font);
        CheckRegister->setSizeGripEnabled(false);
        deleteChecksButtons = new QPushButton(CheckRegister);
        deleteChecksButtons->setObjectName(QString::fromUtf8("deleteChecksButtons"));
        deleteChecksButtons->setGeometry(QRect(10, 590, 100, 30));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(deleteChecksButtons->sizePolicy().hasHeightForWidth());
        deleteChecksButtons->setSizePolicy(sizePolicy1);
        deleteChecksButtons->setAutoDefault(false);
        groupBox1 = new Q3GroupBox(CheckRegister);
        groupBox1->setObjectName(QString::fromUtf8("groupBox1"));
        groupBox1->setGeometry(QRect(10, 360, 430, 80));
        groupBox1->setAlignment(Qt::AlignHCenter);
        buttonClearSel = new QPushButton(groupBox1);
        buttonClearSel->setObjectName(QString::fromUtf8("buttonClearSel"));
        buttonClearSel->setGeometry(QRect(10, 30, 130, 30));
        sizePolicy1.setHeightForWidth(buttonClearSel->sizePolicy().hasHeightForWidth());
        buttonClearSel->setSizePolicy(sizePolicy1);
        buttonClearSel->setAutoDefault(false);
        buttonVoidSel = new QPushButton(groupBox1);
        buttonVoidSel->setObjectName(QString::fromUtf8("buttonVoidSel"));
        buttonVoidSel->setGeometry(QRect(150, 30, 130, 30));
        sizePolicy1.setHeightForWidth(buttonVoidSel->sizePolicy().hasHeightForWidth());
        buttonVoidSel->setSizePolicy(sizePolicy1);
        buttonVoidSel->setAutoDefault(false);
        buttonOutSel = new QPushButton(groupBox1);
        buttonOutSel->setObjectName(QString::fromUtf8("buttonOutSel"));
        buttonOutSel->setGeometry(QRect(290, 30, 130, 30));
        sizePolicy1.setHeightForWidth(buttonOutSel->sizePolicy().hasHeightForWidth());
        buttonOutSel->setSizePolicy(sizePolicy1);
        buttonOutSel->setAutoDefault(false);
        tabSummary = new Q3Table(CheckRegister);
        tabSummary->setObjectName(QString::fromUtf8("tabSummary"));
        tabSummary->setGeometry(QRect(460, 360, 420, 210));
        tabSummary->setFocusPolicy(Qt::NoFocus);
        tabSummary->setNumRows(3);
        tabSummary->setNumCols(3);
        tabSummary->setReadOnly(true);
        filterGroup = new Q3ButtonGroup(CheckRegister);
        filterGroup->setObjectName(QString::fromUtf8("filterGroup"));
        filterGroup->setGeometry(QRect(10, 440, 440, 140));
        filterGroup->setAlignment(Qt::AlignLeading);
        dateOption = new QRadioButton(filterGroup);
        dateOption->setObjectName(QString::fromUtf8("dateOption"));
        dateOption->setGeometry(QRect(10, 60, 90, 30));
        dateOption->setChecked(true);
        registerFromDate = new Q3DateEdit(filterGroup);
        registerFromDate->setObjectName(QString::fromUtf8("registerFromDate"));
        registerFromDate->setGeometry(QRect(100, 60, 140, 32));
        showOutBox = new QCheckBox(filterGroup);
        showOutBox->setObjectName(QString::fromUtf8("showOutBox"));
        showOutBox->setGeometry(QRect(290, 20, 140, 30));
        showOutBox->setChecked(true);
        showVoidBox = new QCheckBox(filterGroup);
        showVoidBox->setObjectName(QString::fromUtf8("showVoidBox"));
        showVoidBox->setGeometry(QRect(160, 20, 120, 30));
        showVoidBox->setChecked(true);
        showClearBox = new QCheckBox(filterGroup);
        showClearBox->setObjectName(QString::fromUtf8("showClearBox"));
        showClearBox->setGeometry(QRect(10, 20, 130, 30));
        showClearBox->setChecked(true);
        registerToDate = new Q3DateEdit(filterGroup);
        registerToDate->setObjectName(QString::fromUtf8("registerToDate"));
        registerToDate->setGeometry(QRect(290, 60, 140, 32));
        textLabel1_2 = new QLabel(filterGroup);
        textLabel1_2->setObjectName(QString::fromUtf8("textLabel1_2"));
        textLabel1_2->setGeometry(QRect(240, 60, 40, 30));
        textLabel1_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel1_2->setWordWrap(false);
        textLabel1_2_2 = new QLabel(filterGroup);
        textLabel1_2_2->setObjectName(QString::fromUtf8("textLabel1_2_2"));
        textLabel1_2_2->setGeometry(QRect(240, 100, 40, 30));
        textLabel1_2_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel1_2_2->setWordWrap(false);
        toNumberEdit = new QLineEdit(filterGroup);
        toNumberEdit->setObjectName(QString::fromUtf8("toNumberEdit"));
        toNumberEdit->setGeometry(QRect(290, 100, 100, 31));
        fromNumberEdit = new QLineEdit(filterGroup);
        fromNumberEdit->setObjectName(QString::fromUtf8("fromNumberEdit"));
        fromNumberEdit->setGeometry(QRect(140, 100, 100, 31));
        numberOption = new QRadioButton(filterGroup);
        numberOption->setObjectName(QString::fromUtf8("numberOption"));
        numberOption->setGeometry(QRect(10, 100, 120, 30));
        buttonReport = new QPushButton(CheckRegister);
        buttonReport->setObjectName(QString::fromUtf8("buttonReport"));
        buttonReport->setGeometry(QRect(630, 590, 120, 32));
        sizePolicy1.setHeightForWidth(buttonReport->sizePolicy().hasHeightForWidth());
        buttonReport->setSizePolicy(sizePolicy1);
        buttonReport->setAutoDefault(false);
        buttonNewDep = new QPushButton(CheckRegister);
        buttonNewDep->setObjectName(QString::fromUtf8("buttonNewDep"));
        buttonNewDep->setGeometry(QRect(500, 590, 120, 32));
        sizePolicy1.setHeightForWidth(buttonNewDep->sizePolicy().hasHeightForWidth());
        buttonNewDep->setSizePolicy(sizePolicy1);
        buttonNewDep->setAutoDefault(false);
        postChecksButton = new QPushButton(CheckRegister);
        postChecksButton->setObjectName(QString::fromUtf8("postChecksButton"));
        postChecksButton->setGeometry(QRect(120, 590, 100, 32));
        sizePolicy1.setHeightForWidth(postChecksButton->sizePolicy().hasHeightForWidth());
        postChecksButton->setSizePolicy(sizePolicy1);
        postChecksButton->setAutoDefault(false);
        buttChkNo = new QPushButton(CheckRegister);
        buttChkNo->setObjectName(QString::fromUtf8("buttChkNo"));
        buttChkNo->setGeometry(QRect(240, 590, 120, 32));
        sizePolicy1.setHeightForWidth(buttChkNo->sizePolicy().hasHeightForWidth());
        buttChkNo->setSizePolicy(sizePolicy1);
        buttChkNo->setAutoDefault(false);
        buttonNewChk = new QPushButton(CheckRegister);
        buttonNewChk->setObjectName(QString::fromUtf8("buttonNewChk"));
        buttonNewChk->setGeometry(QRect(370, 590, 120, 32));
        sizePolicy1.setHeightForWidth(buttonNewChk->sizePolicy().hasHeightForWidth());
        buttonNewChk->setSizePolicy(sizePolicy1);
        buttonNewChk->setAutoDefault(false);
        buttonDone = new QPushButton(CheckRegister);
        buttonDone->setObjectName(QString::fromUtf8("buttonDone"));
        buttonDone->setGeometry(QRect(760, 590, 120, 32));
        sizePolicy1.setHeightForWidth(buttonDone->sizePolicy().hasHeightForWidth());
        buttonDone->setSizePolicy(sizePolicy1);
        buttonDone->setAutoDefault(false);
        buttonDone->setDefault(false);
        tabChecks = new QTabWidget(CheckRegister);
        tabChecks->setObjectName(QString::fromUtf8("tabChecks"));
        tabChecks->setGeometry(QRect(10, 10, 870, 340));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tabChecks->sizePolicy().hasHeightForWidth());
        tabChecks->setSizePolicy(sizePolicy2);
        tab_chks = new QWidget();
        tab_chks->setObjectName(QString::fromUtf8("tab_chks"));
        textLabel1_2_3 = new QLabel(tab_chks);
        textLabel1_2_3->setObjectName(QString::fromUtf8("textLabel1_2_3"));
        textLabel1_2_3->setGeometry(QRect(13, 10, 120, 30));
        textLabel1_2_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel1_2_3->setWordWrap(false);
        searchButton = new QPushButton(tab_chks);
        searchButton->setObjectName(QString::fromUtf8("searchButton"));
        searchButton->setGeometry(QRect(380, 10, 90, 30));
        searchButton->setAutoDefault(false);
        indexCombo = new QComboBox(tab_chks);
        indexCombo->setObjectName(QString::fromUtf8("indexCombo"));
        indexCombo->setGeometry(QRect(140, 10, 120, 30));
        searchEdit = new QLineEdit(tab_chks);
        searchEdit->setObjectName(QString::fromUtf8("searchEdit"));
        searchEdit->setGeometry(QRect(280, 10, 80, 30));
        textLabel1 = new QLabel(tab_chks);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
        textLabel1->setGeometry(QRect(490, 10, 110, 31));
        textLabel1->setWordWrap(false);
        payeeFilterEdit = new QLineEdit(tab_chks);
        payeeFilterEdit->setObjectName(QString::fromUtf8("payeeFilterEdit"));
        payeeFilterEdit->setGeometry(QRect(600, 10, 260, 30));
        checkTable = new Q3Table(tab_chks);
        checkTable->setObjectName(QString::fromUtf8("checkTable"));
        checkTable->setGeometry(QRect(10, 50, 850, 240));
        checkTable->setDragAutoScroll(false);
        checkTable->setNumRows(0);
        checkTable->setNumCols(5);
        checkTable->setShowGrid(false);
        checkTable->setReadOnly(true);
        checkTable->setSelectionMode(Q3Table::MultiRow);
        checkTable->setFocusStyle(Q3Table::FollowStyle);
        tabChecks->addTab(tab_chks, QString());
        tab_dep = new QWidget();
        tab_dep->setObjectName(QString::fromUtf8("tab_dep"));
        listViewDeposits = new Q3ListView(tab_dep);
        listViewDeposits->addColumn(QApplication::translate("CheckRegister", "S", 0, QApplication::UnicodeUTF8));
        listViewDeposits->header()->setClickEnabled(true, listViewDeposits->header()->count() - 1);
        listViewDeposits->header()->setResizeEnabled(true, listViewDeposits->header()->count() - 1);
        listViewDeposits->addColumn(QApplication::translate("CheckRegister", "Number", 0, QApplication::UnicodeUTF8));
        listViewDeposits->header()->setClickEnabled(true, listViewDeposits->header()->count() - 1);
        listViewDeposits->header()->setResizeEnabled(true, listViewDeposits->header()->count() - 1);
        listViewDeposits->addColumn(QApplication::translate("CheckRegister", "Date", 0, QApplication::UnicodeUTF8));
        listViewDeposits->header()->setClickEnabled(true, listViewDeposits->header()->count() - 1);
        listViewDeposits->header()->setResizeEnabled(true, listViewDeposits->header()->count() - 1);
        listViewDeposits->addColumn(QApplication::translate("CheckRegister", "Amount", 0, QApplication::UnicodeUTF8));
        listViewDeposits->header()->setClickEnabled(true, listViewDeposits->header()->count() - 1);
        listViewDeposits->header()->setResizeEnabled(true, listViewDeposits->header()->count() - 1);
        listViewDeposits->addColumn(QApplication::translate("CheckRegister", "Memo", 0, QApplication::UnicodeUTF8));
        listViewDeposits->header()->setClickEnabled(true, listViewDeposits->header()->count() - 1);
        listViewDeposits->header()->setResizeEnabled(true, listViewDeposits->header()->count() - 1);
        listViewDeposits->setObjectName(QString::fromUtf8("listViewDeposits"));
        listViewDeposits->setGeometry(QRect(10, 10, 770, 290));
        listViewDeposits->setSelectionMode(Q3ListView::Multi);
        listViewDeposits->setAllColumnsShowFocus(true);
        tabChecks->addTab(tab_dep, QString());
        QWidget::setTabOrder(tabChecks, buttonClearSel);
        QWidget::setTabOrder(buttonClearSel, buttonVoidSel);
        QWidget::setTabOrder(buttonVoidSel, buttonOutSel);
        QWidget::setTabOrder(buttonOutSel, showClearBox);
        QWidget::setTabOrder(showClearBox, showVoidBox);
        QWidget::setTabOrder(showVoidBox, showOutBox);
        QWidget::setTabOrder(showOutBox, dateOption);
        QWidget::setTabOrder(dateOption, registerFromDate);
        QWidget::setTabOrder(registerFromDate, registerToDate);
        QWidget::setTabOrder(registerToDate, numberOption);
        QWidget::setTabOrder(numberOption, fromNumberEdit);
        QWidget::setTabOrder(fromNumberEdit, toNumberEdit);
        QWidget::setTabOrder(toNumberEdit, deleteChecksButtons);
        QWidget::setTabOrder(deleteChecksButtons, postChecksButton);
        QWidget::setTabOrder(postChecksButton, buttChkNo);
        QWidget::setTabOrder(buttChkNo, buttonNewChk);
        QWidget::setTabOrder(buttonNewChk, buttonNewDep);
        QWidget::setTabOrder(buttonNewDep, buttonReport);
        QWidget::setTabOrder(buttonReport, buttonDone);
        QWidget::setTabOrder(buttonDone, tabSummary);
        QWidget::setTabOrder(tabSummary, listViewDeposits);

        retranslateUi(CheckRegister);

        tabChecks->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(CheckRegister);
    } // setupUi

    void retranslateUi(QDialog *CheckRegister)
    {
        CheckRegister->setWindowTitle(QApplication::translate("CheckRegister", "Check Register", 0, QApplication::UnicodeUTF8));
        deleteChecksButtons->setText(QApplication::translate("CheckRegister", "De&lete", 0, QApplication::UnicodeUTF8));
        deleteChecksButtons->setShortcut(QApplication::translate("CheckRegister", "Alt+L", 0, QApplication::UnicodeUTF8));
        groupBox1->setTitle(QApplication::translate("CheckRegister", "Mark Selected Checks", 0, QApplication::UnicodeUTF8));
        buttonClearSel->setText(QApplication::translate("CheckRegister", "Cleared", 0, QApplication::UnicodeUTF8));
        buttonClearSel->setShortcut(QString());
        buttonVoidSel->setText(QApplication::translate("CheckRegister", "Void", 0, QApplication::UnicodeUTF8));
        buttonOutSel->setText(QApplication::translate("CheckRegister", "Outstanding", 0, QApplication::UnicodeUTF8));
        tabSummary->horizontalHeader()->setLabel(0, QApplication::translate("CheckRegister", "Deposits", 0, QApplication::UnicodeUTF8));
        tabSummary->horizontalHeader()->setLabel(1, QApplication::translate("CheckRegister", "Checks", 0, QApplication::UnicodeUTF8));
        tabSummary->horizontalHeader()->setLabel(2, QApplication::translate("CheckRegister", "Balance", 0, QApplication::UnicodeUTF8));
        tabSummary->verticalHeader()->setLabel(0, QApplication::translate("CheckRegister", "Cleared", 0, QApplication::UnicodeUTF8));
        tabSummary->verticalHeader()->setLabel(1, QApplication::translate("CheckRegister", "Outstanding", 0, QApplication::UnicodeUTF8));
        tabSummary->verticalHeader()->setLabel(2, QApplication::translate("CheckRegister", "Total", 0, QApplication::UnicodeUTF8));
        filterGroup->setTitle(QApplication::translate("CheckRegister", "Show", 0, QApplication::UnicodeUTF8));
        dateOption->setText(QApplication::translate("CheckRegister", "Dated:", 0, QApplication::UnicodeUTF8));
        dateOption->setShortcut(QString());
        showOutBox->setText(QApplication::translate("CheckRegister", "Outstanding", 0, QApplication::UnicodeUTF8));
        showVoidBox->setText(QApplication::translate("CheckRegister", "Void", 0, QApplication::UnicodeUTF8));
        showClearBox->setText(QApplication::translate("CheckRegister", "Cleared", 0, QApplication::UnicodeUTF8));
        textLabel1_2->setText(QApplication::translate("CheckRegister", "To:", 0, QApplication::UnicodeUTF8));
        textLabel1_2_2->setText(QApplication::translate("CheckRegister", "To:", 0, QApplication::UnicodeUTF8));
        numberOption->setText(QApplication::translate("CheckRegister", "&Numbered:", 0, QApplication::UnicodeUTF8));
        buttonReport->setText(QApplication::translate("CheckRegister", "&Report", 0, QApplication::UnicodeUTF8));
        buttonReport->setShortcut(QApplication::translate("CheckRegister", "Alt+R", 0, QApplication::UnicodeUTF8));
        buttonNewDep->setText(QApplication::translate("CheckRegister", "New &Deposit", 0, QApplication::UnicodeUTF8));
        buttonNewDep->setShortcut(QApplication::translate("CheckRegister", "Alt+D", 0, QApplication::UnicodeUTF8));
        postChecksButton->setText(QApplication::translate("CheckRegister", "Po&st", 0, QApplication::UnicodeUTF8));
        postChecksButton->setShortcut(QApplication::translate("CheckRegister", "Alt+S", 0, QApplication::UnicodeUTF8));
        buttChkNo->setText(QApplication::translate("CheckRegister", "&Next Chk #", 0, QApplication::UnicodeUTF8));
        buttChkNo->setShortcut(QApplication::translate("CheckRegister", "Alt+N", 0, QApplication::UnicodeUTF8));
        buttonNewChk->setText(QApplication::translate("CheckRegister", "New &Check", 0, QApplication::UnicodeUTF8));
        buttonNewChk->setShortcut(QApplication::translate("CheckRegister", "Alt+C", 0, QApplication::UnicodeUTF8));
        buttonDone->setText(QApplication::translate("CheckRegister", "Done", 0, QApplication::UnicodeUTF8));
        buttonDone->setShortcut(QString());
        textLabel1_2_3->setText(QApplication::translate("CheckRegister", "Index By:", 0, QApplication::UnicodeUTF8));
        searchButton->setText(QApplication::translate("CheckRegister", "Search", 0, QApplication::UnicodeUTF8));
        indexCombo->clear();
        indexCombo->insertItems(0, QStringList()
         << QApplication::translate("CheckRegister", "Date", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CheckRegister", "Number", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CheckRegister", "Payee", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CheckRegister", "Amount", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CheckRegister", "Status", 0, QApplication::UnicodeUTF8)
        );
        textLabel1->setText(QApplication::translate("CheckRegister", "Filter Payee:", 0, QApplication::UnicodeUTF8));
        checkTable->horizontalHeader()->setLabel(0, QApplication::translate("CheckRegister", "Date", 0, QApplication::UnicodeUTF8));
        checkTable->horizontalHeader()->setLabel(1, QApplication::translate("CheckRegister", "Number", 0, QApplication::UnicodeUTF8));
        checkTable->horizontalHeader()->setLabel(2, QApplication::translate("CheckRegister", "Payee", 0, QApplication::UnicodeUTF8));
        checkTable->horizontalHeader()->setLabel(3, QApplication::translate("CheckRegister", "Amount", 0, QApplication::UnicodeUTF8));
        checkTable->horizontalHeader()->setLabel(4, QApplication::translate("CheckRegister", "S", 0, QApplication::UnicodeUTF8));
        tabChecks->setTabText(tabChecks->indexOf(tab_chks), QApplication::translate("CheckRegister", "Checks", 0, QApplication::UnicodeUTF8));
        listViewDeposits->header()->setLabel(0, QApplication::translate("CheckRegister", "S", 0, QApplication::UnicodeUTF8));
        listViewDeposits->header()->setLabel(1, QApplication::translate("CheckRegister", "Number", 0, QApplication::UnicodeUTF8));
        listViewDeposits->header()->setLabel(2, QApplication::translate("CheckRegister", "Date", 0, QApplication::UnicodeUTF8));
        listViewDeposits->header()->setLabel(3, QApplication::translate("CheckRegister", "Amount", 0, QApplication::UnicodeUTF8));
        listViewDeposits->header()->setLabel(4, QApplication::translate("CheckRegister", "Memo", 0, QApplication::UnicodeUTF8));
        tabChecks->setTabText(tabChecks->indexOf(tab_dep), QApplication::translate("CheckRegister", "Deposits", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CheckRegister: public Ui_CheckRegister {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHECKREGISTER_H
