/********************************************************************************
** Form generated from reading UI file 'permbuyersearchdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PERMBUYERSEARCHDIALOG_H
#define UI_PERMBUYERSEARCHDIALOG_H

#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3Header>
#include <Qt3Support/Q3MimeSourceFactory>
#include <Qt3Support/Q3Table>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_PermBuyerSearch
{
public:
    QGridLayout *gridLayout;
    Q3Table *permBuyerTable;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacer1;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *PermBuyerSearch)
    {
        if (PermBuyerSearch->objectName().isEmpty())
            PermBuyerSearch->setObjectName(QString::fromUtf8("PermBuyerSearch"));
        PermBuyerSearch->setWindowModality(Qt::ApplicationModal);
        PermBuyerSearch->resize(760, 274);
        gridLayout = new QGridLayout(PermBuyerSearch);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        permBuyerTable = new Q3Table(PermBuyerSearch);
        permBuyerTable->setObjectName(QString::fromUtf8("permBuyerTable"));
        permBuyerTable->setNumRows(0);
        permBuyerTable->setNumCols(1);

        gridLayout->addWidget(permBuyerTable, 0, 0, 1, 1);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        spacer1 = new QSpacerItem(481, 51, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacer1);

        okButton = new QPushButton(PermBuyerSearch);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(PermBuyerSearch);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        hboxLayout->addWidget(cancelButton);


        gridLayout->addLayout(hboxLayout, 1, 0, 1, 1);


        retranslateUi(PermBuyerSearch);

        QMetaObject::connectSlotsByName(PermBuyerSearch);
    } // setupUi

    void retranslateUi(QDialog *PermBuyerSearch)
    {
        PermBuyerSearch->setWindowTitle(QApplication::translate("PermBuyerSearch", "Form1", 0, QApplication::UnicodeUTF8));
        permBuyerTable->horizontalHeader()->setLabel(0, QApplication::translate("PermBuyerSearch", "Buyer", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("PermBuyerSearch", "Ok", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("PermBuyerSearch", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PermBuyerSearch: public Ui_PermBuyerSearch {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PERMBUYERSEARCHDIALOG_H
