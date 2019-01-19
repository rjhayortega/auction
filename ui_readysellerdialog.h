/********************************************************************************
** Form generated from reading UI file 'readysellerdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_READYSELLERDIALOG_H
#define UI_READYSELLERDIALOG_H

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
#include <Qt3Support/Q3ProgressDialog>
#include "dao/invoicedao.h"

QT_BEGIN_NAMESPACE

class Ui_ReadySellerDialog
{
public:
    QPushButton *buttonCancel;
    Q3ListBox *readySellerList;

    void setupUi(QDialog *ReadySellerDialog)
    {
        if (ReadySellerDialog->objectName().isEmpty())
            ReadySellerDialog->setObjectName(QString::fromUtf8("ReadySellerDialog"));
        ReadySellerDialog->setWindowModality(Qt::ApplicationModal);
        ReadySellerDialog->resize(361, 354);
        QFont font;
        font.setPointSize(13);
        ReadySellerDialog->setFont(font);
        buttonCancel = new QPushButton(ReadySellerDialog);
        buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));
        buttonCancel->setGeometry(QRect(250, 310, 100, 30));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(buttonCancel->sizePolicy().hasHeightForWidth());
        buttonCancel->setSizePolicy(sizePolicy);
        buttonCancel->setMinimumSize(QSize(80, 27));
        buttonCancel->setAutoDefault(true);
        readySellerList = new Q3ListBox(ReadySellerDialog);
        readySellerList->setObjectName(QString::fromUtf8("readySellerList"));
        readySellerList->setGeometry(QRect(10, 20, 340, 280));

        retranslateUi(ReadySellerDialog);

        QMetaObject::connectSlotsByName(ReadySellerDialog);
    } // setupUi

    void retranslateUi(QDialog *ReadySellerDialog)
    {
        ReadySellerDialog->setWindowTitle(QApplication::translate("ReadySellerDialog", "Ready Sellers", 0, QApplication::UnicodeUTF8));
        buttonCancel->setText(QApplication::translate("ReadySellerDialog", "&Cancel", 0, QApplication::UnicodeUTF8));
        buttonCancel->setShortcut(QString());
    } // retranslateUi

};

namespace Ui {
    class ReadySellerDialog: public Ui_ReadySellerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_READYSELLERDIALOG_H
