/********************************************************************************
** Form generated from reading UI file 'zipcodedialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ZIPCODEDIALOG_H
#define UI_ZIPCODEDIALOG_H

#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3ListBox>
#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <vector>
#include "types/address.h"

QT_BEGIN_NAMESPACE

class Ui_ZipCodeDialog
{
public:
    QLabel *textLabel1;
    Q3ListBox *cityStateZipListBox;

    void setupUi(QDialog *ZipCodeDialog)
    {
        if (ZipCodeDialog->objectName().isEmpty())
            ZipCodeDialog->setObjectName(QString::fromUtf8("ZipCodeDialog"));
        ZipCodeDialog->setWindowModality(Qt::ApplicationModal);
        ZipCodeDialog->resize(352, 252);
        QFont font;
        font.setPointSize(13);
        ZipCodeDialog->setFont(font);
        textLabel1 = new QLabel(ZipCodeDialog);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
        textLabel1->setGeometry(QRect(10, 10, 330, 21));
        textLabel1->setWordWrap(false);
        cityStateZipListBox = new Q3ListBox(ZipCodeDialog);
        cityStateZipListBox->setObjectName(QString::fromUtf8("cityStateZipListBox"));
        cityStateZipListBox->setGeometry(QRect(10, 40, 330, 191));

        retranslateUi(ZipCodeDialog);

        QMetaObject::connectSlotsByName(ZipCodeDialog);
    } // setupUi

    void retranslateUi(QDialog *ZipCodeDialog)
    {
        ZipCodeDialog->setWindowTitle(QApplication::translate("ZipCodeDialog", "Multiple Zip Codes Found", 0, QApplication::UnicodeUTF8));
        textLabel1->setText(QApplication::translate("ZipCodeDialog", "Which City, State Zip is appropriate?", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ZipCodeDialog: public Ui_ZipCodeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ZIPCODEDIALOG_H
