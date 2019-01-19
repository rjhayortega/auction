/********************************************************************************
** Form generated from reading UI file 'transfercheckdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRANSFERCHECKDIALOG_H
#define UI_TRANSFERCHECKDIALOG_H

#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3ListBox>
#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <vector>
#include "dao/chargedao.h"
#include "dao/checkdao.h"
#include "dao/printerdao.h"

QT_BEGIN_NAMESPACE

class Ui_TransferCheckDialog
{
public:
    QPushButton *writeCheckButton;
    Q3ListBox *chargeSummaryListBox;
    QComboBox *colorCombo;
    QLabel *textLabel2;

    void setupUi(QDialog *TransferCheckDialog)
    {
        if (TransferCheckDialog->objectName().isEmpty())
            TransferCheckDialog->setObjectName(QString::fromUtf8("TransferCheckDialog"));
        TransferCheckDialog->setWindowModality(Qt::ApplicationModal);
        TransferCheckDialog->resize(462, 316);
        QFont font;
        font.setPointSize(13);
        TransferCheckDialog->setFont(font);
        writeCheckButton = new QPushButton(TransferCheckDialog);
        writeCheckButton->setObjectName(QString::fromUtf8("writeCheckButton"));
        writeCheckButton->setGeometry(QRect(310, 270, 140, 30));
        chargeSummaryListBox = new Q3ListBox(TransferCheckDialog);
        chargeSummaryListBox->setObjectName(QString::fromUtf8("chargeSummaryListBox"));
        chargeSummaryListBox->setGeometry(QRect(10, 10, 440, 250));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Bitstream Vera Sans Mono"));
        font1.setPointSize(13);
        chargeSummaryListBox->setFont(font1);
        chargeSummaryListBox->setSelectionMode(Q3ListBox::Multi);
        colorCombo = new QComboBox(TransferCheckDialog);
        colorCombo->setObjectName(QString::fromUtf8("colorCombo"));
        colorCombo->setGeometry(QRect(180, 270, 100, 31));
        textLabel2 = new QLabel(TransferCheckDialog);
        textLabel2->setObjectName(QString::fromUtf8("textLabel2"));
        textLabel2->setGeometry(QRect(40, 270, 121, 31));
        textLabel2->setWordWrap(false);

        retranslateUi(TransferCheckDialog);

        QMetaObject::connectSlotsByName(TransferCheckDialog);
    } // setupUi

    void retranslateUi(QDialog *TransferCheckDialog)
    {
        TransferCheckDialog->setWindowTitle(QApplication::translate("TransferCheckDialog", "Transfer Checks", 0, QApplication::UnicodeUTF8));
        writeCheckButton->setText(QApplication::translate("TransferCheckDialog", "Write Check", 0, QApplication::UnicodeUTF8));
        colorCombo->clear();
        colorCombo->insertItems(0, QStringList()
         << QApplication::translate("TransferCheckDialog", "0-69", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("TransferCheckDialog", "70-79", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("TransferCheckDialog", "80-89", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("TransferCheckDialog", "90-99", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("TransferCheckDialog", "All", 0, QApplication::UnicodeUTF8)
        );
        textLabel2->setText(QApplication::translate("TransferCheckDialog", "Color Group", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TransferCheckDialog: public Ui_TransferCheckDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRANSFERCHECKDIALOG_H
