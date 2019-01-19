/********************************************************************************
** Form generated from reading UI file 'tageditdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TAGEDITDIALOG_H
#define UI_TAGEDITDIALOG_H

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
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include "dao/tagdao.h"
#include "types/animalcode.h"
#include "types/customer.h"
#include "types/transaction.h"

QT_BEGIN_NAMESPACE

class Ui_TagEditDialog
{
public:
    QPushButton *exitButton;
    QPushButton *deleteButton;
    QLabel *tagDescripText;
    QLabel *textLabel1;
    QLabel *textLabel1_3;
    QLabel *textLabel1_2;
    QLineEdit *tagEdit;
    QLineEdit *tagDescrip;
    QLineEdit *burcellosisTagEdit;
    Q3ListBox *tagListBox;

    void setupUi(QDialog *TagEditDialog)
    {
        if (TagEditDialog->objectName().isEmpty())
            TagEditDialog->setObjectName(QString::fromUtf8("TagEditDialog"));
        TagEditDialog->setWindowModality(Qt::ApplicationModal);
        TagEditDialog->resize(419, 229);
        QFont font;
        font.setPointSize(13);
        TagEditDialog->setFont(font);
        exitButton = new QPushButton(TagEditDialog);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));
        exitButton->setGeometry(QRect(230, 180, 80, 30));
        exitButton->setAutoDefault(false);
        deleteButton = new QPushButton(TagEditDialog);
        deleteButton->setObjectName(QString::fromUtf8("deleteButton"));
        deleteButton->setGeometry(QRect(330, 180, 80, 30));
        deleteButton->setAutoDefault(false);
        tagDescripText = new QLabel(TagEditDialog);
        tagDescripText->setObjectName(QString::fromUtf8("tagDescripText"));
        tagDescripText->setGeometry(QRect(250, 140, 120, 30));
        tagDescripText->setWordWrap(false);
        textLabel1 = new QLabel(TagEditDialog);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
        textLabel1->setGeometry(QRect(10, 10, 120, 31));
        textLabel1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel1->setWordWrap(false);
        textLabel1_3 = new QLabel(TagEditDialog);
        textLabel1_3->setObjectName(QString::fromUtf8("textLabel1_3"));
        textLabel1_3->setGeometry(QRect(10, 140, 120, 31));
        textLabel1_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel1_3->setWordWrap(false);
        textLabel1_2 = new QLabel(TagEditDialog);
        textLabel1_2->setObjectName(QString::fromUtf8("textLabel1_2"));
        textLabel1_2->setGeometry(QRect(1, 70, 130, 31));
        textLabel1_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel1_2->setWordWrap(false);
        tagEdit = new QLineEdit(TagEditDialog);
        tagEdit->setObjectName(QString::fromUtf8("tagEdit"));
        tagEdit->setGeometry(QRect(140, 10, 100, 30));
        tagDescrip = new QLineEdit(TagEditDialog);
        tagDescrip->setObjectName(QString::fromUtf8("tagDescrip"));
        tagDescrip->setGeometry(QRect(140, 140, 100, 30));
        burcellosisTagEdit = new QLineEdit(TagEditDialog);
        burcellosisTagEdit->setObjectName(QString::fromUtf8("burcellosisTagEdit"));
        burcellosisTagEdit->setGeometry(QRect(140, 70, 100, 30));
        tagListBox = new Q3ListBox(TagEditDialog);
        tagListBox->setObjectName(QString::fromUtf8("tagListBox"));
        tagListBox->setGeometry(QRect(250, 10, 160, 120));
        tagListBox->setSelectionMode(Q3ListBox::Multi);
        QWidget::setTabOrder(tagEdit, burcellosisTagEdit);
        QWidget::setTabOrder(burcellosisTagEdit, tagDescrip);
        QWidget::setTabOrder(tagDescrip, tagListBox);
        QWidget::setTabOrder(tagListBox, exitButton);
        QWidget::setTabOrder(exitButton, deleteButton);

        retranslateUi(TagEditDialog);

        QMetaObject::connectSlotsByName(TagEditDialog);
    } // setupUi

    void retranslateUi(QDialog *TagEditDialog)
    {
        TagEditDialog->setWindowTitle(QApplication::translate("TagEditDialog", "Edit Tags", 0, QApplication::UnicodeUTF8));
        exitButton->setText(QApplication::translate("TagEditDialog", "Exit", 0, QApplication::UnicodeUTF8));
        deleteButton->setText(QApplication::translate("TagEditDialog", "Delete", 0, QApplication::UnicodeUTF8));
        tagDescripText->setText(QString());
        textLabel1->setText(QApplication::translate("TagEditDialog", "Tag:", 0, QApplication::UnicodeUTF8));
        textLabel1_3->setText(QApplication::translate("TagEditDialog", "Description:", 0, QApplication::UnicodeUTF8));
        textLabel1_2->setText(QApplication::translate("TagEditDialog", "Brucellosis Tag:", 0, QApplication::UnicodeUTF8));
        tagDescrip->setText(QString());
        burcellosisTagEdit->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class TagEditDialog: public Ui_TagEditDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TAGEDITDIALOG_H
