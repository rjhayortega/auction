/********************************************************************************
** Form generated from reading UI file 'tagbrowser.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TAGBROWSER_H
#define UI_TAGBROWSER_H

#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3Header>
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
#include <vector>
#include "dao/tagdao.h"
#include "dao/transactiondao.h"

QT_BEGIN_NAMESPACE

class Ui_TagBrowser
{
public:
    QLabel *textLabel1;
    QComboBox *sortCombo;
    Q3Table *tagTable;

    void setupUi(QDialog *TagBrowser)
    {
        if (TagBrowser->objectName().isEmpty())
            TagBrowser->setObjectName(QString::fromUtf8("TagBrowser"));
        TagBrowser->setWindowModality(Qt::ApplicationModal);
        TagBrowser->resize(576, 229);
        textLabel1 = new QLabel(TagBrowser);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
        textLabel1->setGeometry(QRect(20, 10, 121, 31));
        textLabel1->setWordWrap(false);
        sortCombo = new QComboBox(TagBrowser);
        sortCombo->setObjectName(QString::fromUtf8("sortCombo"));
        sortCombo->setGeometry(QRect(150, 10, 121, 31));
        tagTable = new Q3Table(TagBrowser);
        tagTable->setObjectName(QString::fromUtf8("tagTable"));
        tagTable->setGeometry(QRect(10, 50, 550, 161));
        tagTable->setNumRows(3);
        tagTable->setNumCols(5);
        tagTable->setReadOnly(true);
        tagTable->setSelectionMode(Q3Table::SingleRow);

        retranslateUi(TagBrowser);

        QMetaObject::connectSlotsByName(TagBrowser);
    } // setupUi

    void retranslateUi(QDialog *TagBrowser)
    {
        TagBrowser->setWindowTitle(QApplication::translate("TagBrowser", "Tag Browser", 0, QApplication::UnicodeUTF8));
        textLabel1->setText(QApplication::translate("TagBrowser", "Sort By:", 0, QApplication::UnicodeUTF8));
        sortCombo->clear();
        sortCombo->insertItems(0, QStringList()
         << QApplication::translate("TagBrowser", "Tag", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("TagBrowser", "Trans", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("TagBrowser", "Seller", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("TagBrowser", "Buyer", 0, QApplication::UnicodeUTF8)
        );
        tagTable->horizontalHeader()->setLabel(0, QApplication::translate("TagBrowser", "Tag #", 0, QApplication::UnicodeUTF8));
        tagTable->horizontalHeader()->setLabel(1, QApplication::translate("TagBrowser", "Trans #", 0, QApplication::UnicodeUTF8));
        tagTable->horizontalHeader()->setLabel(2, QApplication::translate("TagBrowser", "Seller#", 0, QApplication::UnicodeUTF8));
        tagTable->horizontalHeader()->setLabel(3, QApplication::translate("TagBrowser", "Buyer#", 0, QApplication::UnicodeUTF8));
        tagTable->horizontalHeader()->setLabel(4, QApplication::translate("TagBrowser", "Pen# ", 0, QApplication::UnicodeUTF8));
        tagTable->verticalHeader()->setLabel(0, QApplication::translate("TagBrowser", "1", 0, QApplication::UnicodeUTF8));
        tagTable->verticalHeader()->setLabel(1, QApplication::translate("TagBrowser", "2", 0, QApplication::UnicodeUTF8));
        tagTable->verticalHeader()->setLabel(2, QApplication::translate("TagBrowser", "3", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TagBrowser: public Ui_TagBrowser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TAGBROWSER_H
