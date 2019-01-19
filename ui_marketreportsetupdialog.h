/********************************************************************************
** Form generated from reading UI file 'marketreportsetupdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MARKETREPORTSETUPDIALOG_H
#define UI_MARKETREPORTSETUPDIALOG_H

#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3GroupBox>
#include <Qt3Support/Q3Header>
#include <Qt3Support/Q3MimeSourceFactory>
#include <Qt3Support/Q3Table>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include "dao/setupdao.h"

QT_BEGIN_NAMESPACE

class Ui_MarketReportSetupDialog
{
public:
    Q3GroupBox *groupBox22;
    Q3Table *sortTable;
    QPushButton *cancelButton;
    QPushButton *acceptButton;
    QPushButton *okButton;
    QGroupBox *groupByWeightGroupBox;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *startWeightEdit;
    QLabel *label_2;
    QLineEdit *sizeEdit;
    QLineEdit *endWeightEdit;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *MarketReportSetupDialog)
    {
        if (MarketReportSetupDialog->objectName().isEmpty())
            MarketReportSetupDialog->setObjectName(QString::fromUtf8("MarketReportSetupDialog"));
        MarketReportSetupDialog->setWindowModality(Qt::ApplicationModal);
        MarketReportSetupDialog->resize(371, 463);
        QFont font;
        font.setPointSize(13);
        MarketReportSetupDialog->setFont(font);
        groupBox22 = new Q3GroupBox(MarketReportSetupDialog);
        groupBox22->setObjectName(QString::fromUtf8("groupBox22"));
        groupBox22->setGeometry(QRect(10, 10, 351, 411));
        sortTable = new Q3Table(groupBox22);
        sortTable->setObjectName(QString::fromUtf8("sortTable"));
        sortTable->setGeometry(QRect(10, 30, 311, 180));
        sortTable->setNumRows(6);
        sortTable->setNumCols(2);
        cancelButton = new QPushButton(groupBox22);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(10, 359, 100, 30));
        acceptButton = new QPushButton(groupBox22);
        acceptButton->setObjectName(QString::fromUtf8("acceptButton"));
        acceptButton->setGeometry(QRect(120, 359, 100, 30));
        okButton = new QPushButton(groupBox22);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setGeometry(QRect(230, 360, 100, 30));
        groupByWeightGroupBox = new QGroupBox(groupBox22);
        groupByWeightGroupBox->setObjectName(QString::fromUtf8("groupByWeightGroupBox"));
        groupByWeightGroupBox->setGeometry(QRect(10, 220, 311, 136));
        groupByWeightGroupBox->setCheckable(true);
        gridLayout_2 = new QGridLayout(groupByWeightGroupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(groupByWeightGroupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        startWeightEdit = new QLineEdit(groupByWeightGroupBox);
        startWeightEdit->setObjectName(QString::fromUtf8("startWeightEdit"));

        gridLayout->addWidget(startWeightEdit, 0, 1, 1, 1);

        label_2 = new QLabel(groupByWeightGroupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        sizeEdit = new QLineEdit(groupByWeightGroupBox);
        sizeEdit->setObjectName(QString::fromUtf8("sizeEdit"));

        gridLayout->addWidget(sizeEdit, 2, 1, 1, 1);

        endWeightEdit = new QLineEdit(groupByWeightGroupBox);
        endWeightEdit->setObjectName(QString::fromUtf8("endWeightEdit"));

        gridLayout->addWidget(endWeightEdit, 1, 1, 1, 1);

        label_3 = new QLabel(groupByWeightGroupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 2, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        QWidget::setTabOrder(sortTable, groupByWeightGroupBox);
        QWidget::setTabOrder(groupByWeightGroupBox, startWeightEdit);
        QWidget::setTabOrder(startWeightEdit, endWeightEdit);
        QWidget::setTabOrder(endWeightEdit, sizeEdit);
        QWidget::setTabOrder(sizeEdit, cancelButton);
        QWidget::setTabOrder(cancelButton, acceptButton);
        QWidget::setTabOrder(acceptButton, okButton);

        retranslateUi(MarketReportSetupDialog);

        QMetaObject::connectSlotsByName(MarketReportSetupDialog);
    } // setupUi

    void retranslateUi(QDialog *MarketReportSetupDialog)
    {
        MarketReportSetupDialog->setWindowTitle(QApplication::translate("MarketReportSetupDialog", "Setup Market Report", 0, QApplication::UnicodeUTF8));
        groupBox22->setTitle(QApplication::translate("MarketReportSetupDialog", "Setup Market Report", 0, QApplication::UnicodeUTF8));
        sortTable->horizontalHeader()->setLabel(0, QApplication::translate("MarketReportSetupDialog", "Sort By", 0, QApplication::UnicodeUTF8));
        sortTable->horizontalHeader()->setLabel(1, QApplication::translate("MarketReportSetupDialog", "Descending?", 0, QApplication::UnicodeUTF8));
        sortTable->verticalHeader()->setLabel(0, QApplication::translate("MarketReportSetupDialog", "1", 0, QApplication::UnicodeUTF8));
        sortTable->verticalHeader()->setLabel(1, QApplication::translate("MarketReportSetupDialog", "2", 0, QApplication::UnicodeUTF8));
        sortTable->verticalHeader()->setLabel(2, QApplication::translate("MarketReportSetupDialog", "3", 0, QApplication::UnicodeUTF8));
        sortTable->verticalHeader()->setLabel(3, QApplication::translate("MarketReportSetupDialog", "4", 0, QApplication::UnicodeUTF8));
        sortTable->verticalHeader()->setLabel(4, QApplication::translate("MarketReportSetupDialog", "5", 0, QApplication::UnicodeUTF8));
        sortTable->verticalHeader()->setLabel(5, QApplication::translate("MarketReportSetupDialog", "6", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("MarketReportSetupDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        acceptButton->setText(QApplication::translate("MarketReportSetupDialog", "Accept", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("MarketReportSetupDialog", "Ok", 0, QApplication::UnicodeUTF8));
        groupByWeightGroupBox->setTitle(QApplication::translate("MarketReportSetupDialog", "Group by weight", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MarketReportSetupDialog", "Starting weight", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MarketReportSetupDialog", "Ending weight", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MarketReportSetupDialog", "Size of class  ", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MarketReportSetupDialog: public Ui_MarketReportSetupDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MARKETREPORTSETUPDIALOG_H
