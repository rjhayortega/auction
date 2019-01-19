/********************************************************************************
** Form generated from reading UI file 'permsearchdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PERMSEARCHDIALOG_H
#define UI_PERMSEARCHDIALOG_H

#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3ListBox>
#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include "dao/checkdao.h"
#include "dao/customerdao.h"

QT_BEGIN_NAMESPACE

class Ui_PermSearchDialog
{
public:
    Q3ListBox *permListBox;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *PermSearchDialog)
    {
        if (PermSearchDialog->objectName().isEmpty())
            PermSearchDialog->setObjectName(QString::fromUtf8("PermSearchDialog"));
        PermSearchDialog->setWindowModality(Qt::ApplicationModal);
        PermSearchDialog->resize(998, 199);
        QFont font;
        font.setPointSize(13);
        PermSearchDialog->setFont(font);
        permListBox = new Q3ListBox(PermSearchDialog);
        permListBox->setObjectName(QString::fromUtf8("permListBox"));
        permListBox->setGeometry(QRect(10, 10, 980, 140));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Bitstream Vera Sans Mono"));
        font1.setPointSize(13);
        permListBox->setFont(font1);
        okButton = new QPushButton(PermSearchDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setGeometry(QRect(890, 160, 100, 30));
        cancelButton = new QPushButton(PermSearchDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(780, 160, 100, 30));
        cancelButton->setAutoDefault(false);
        QWidget::setTabOrder(permListBox, cancelButton);
        QWidget::setTabOrder(cancelButton, okButton);

        retranslateUi(PermSearchDialog);

        QMetaObject::connectSlotsByName(PermSearchDialog);
    } // setupUi

    void retranslateUi(QDialog *PermSearchDialog)
    {
        PermSearchDialog->setWindowTitle(QApplication::translate("PermSearchDialog", "Search The Permanant Table", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("PermSearchDialog", "Ok", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("PermSearchDialog", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PermSearchDialog: public Ui_PermSearchDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PERMSEARCHDIALOG_H
