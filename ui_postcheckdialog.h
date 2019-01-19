/********************************************************************************
** Form generated from reading UI file 'postcheckdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POSTCHECKDIALOG_H
#define UI_POSTCHECKDIALOG_H

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
#include "dao/checkdao.h"

QT_BEGIN_NAMESPACE

class Ui_PostCheckDialog
{
public:
    QLabel *textLabel1;
    QLineEdit *checkNoEdit;
    QLabel *textLabel1_2;
    QLineEdit *checkAmountEdit;
    QLabel *checkDateDisplay;
    QLabel *checkPayeeDisplay;
    QLabel *checkAmountDisplay;
    QLabel *textLabel2_3_2;
    QLabel *textLabel2_3;
    QLabel *textLabel2;
    QPushButton *exitButton;

    void setupUi(QDialog *PostCheckDialog)
    {
        if (PostCheckDialog->objectName().isEmpty())
            PostCheckDialog->setObjectName(QString::fromUtf8("PostCheckDialog"));
        PostCheckDialog->setWindowModality(Qt::ApplicationModal);
        PostCheckDialog->resize(355, 319);
        QFont font;
        font.setPointSize(13);
        PostCheckDialog->setFont(font);
        textLabel1 = new QLabel(PostCheckDialog);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
        textLabel1->setGeometry(QRect(20, 10, 140, 30));
        textLabel1->setWordWrap(false);
        checkNoEdit = new QLineEdit(PostCheckDialog);
        checkNoEdit->setObjectName(QString::fromUtf8("checkNoEdit"));
        checkNoEdit->setGeometry(QRect(20, 50, 140, 30));
        textLabel1_2 = new QLabel(PostCheckDialog);
        textLabel1_2->setObjectName(QString::fromUtf8("textLabel1_2"));
        textLabel1_2->setGeometry(QRect(180, 10, 140, 30));
        textLabel1_2->setWordWrap(false);
        checkAmountEdit = new QLineEdit(PostCheckDialog);
        checkAmountEdit->setObjectName(QString::fromUtf8("checkAmountEdit"));
        checkAmountEdit->setGeometry(QRect(180, 50, 140, 30));
        checkDateDisplay = new QLabel(PostCheckDialog);
        checkDateDisplay->setObjectName(QString::fromUtf8("checkDateDisplay"));
        checkDateDisplay->setGeometry(QRect(180, 90, 140, 30));
        checkDateDisplay->setWordWrap(false);
        checkPayeeDisplay = new QLabel(PostCheckDialog);
        checkPayeeDisplay->setObjectName(QString::fromUtf8("checkPayeeDisplay"));
        checkPayeeDisplay->setGeometry(QRect(180, 150, 140, 30));
        checkPayeeDisplay->setWordWrap(false);
        checkAmountDisplay = new QLabel(PostCheckDialog);
        checkAmountDisplay->setObjectName(QString::fromUtf8("checkAmountDisplay"));
        checkAmountDisplay->setGeometry(QRect(180, 210, 140, 30));
        checkAmountDisplay->setWordWrap(false);
        textLabel2_3_2 = new QLabel(PostCheckDialog);
        textLabel2_3_2->setObjectName(QString::fromUtf8("textLabel2_3_2"));
        textLabel2_3_2->setGeometry(QRect(20, 210, 140, 30));
        textLabel2_3_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel2_3_2->setWordWrap(false);
        textLabel2_3 = new QLabel(PostCheckDialog);
        textLabel2_3->setObjectName(QString::fromUtf8("textLabel2_3"));
        textLabel2_3->setGeometry(QRect(20, 150, 140, 30));
        textLabel2_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel2_3->setWordWrap(false);
        textLabel2 = new QLabel(PostCheckDialog);
        textLabel2->setObjectName(QString::fromUtf8("textLabel2"));
        textLabel2->setGeometry(QRect(20, 90, 140, 30));
        textLabel2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel2->setWordWrap(false);
        exitButton = new QPushButton(PostCheckDialog);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));
        exitButton->setGeometry(QRect(221, 270, 100, 30));
        exitButton->setAutoDefault(false);
        QWidget::setTabOrder(checkNoEdit, checkAmountEdit);
        QWidget::setTabOrder(checkAmountEdit, exitButton);

        retranslateUi(PostCheckDialog);

        QMetaObject::connectSlotsByName(PostCheckDialog);
    } // setupUi

    void retranslateUi(QDialog *PostCheckDialog)
    {
        PostCheckDialog->setWindowTitle(QApplication::translate("PostCheckDialog", "Post Checks", 0, QApplication::UnicodeUTF8));
        textLabel1->setText(QApplication::translate("PostCheckDialog", "Check Number", 0, QApplication::UnicodeUTF8));
        textLabel1_2->setText(QApplication::translate("PostCheckDialog", "Amount", 0, QApplication::UnicodeUTF8));
        checkDateDisplay->setText(QString());
        checkPayeeDisplay->setText(QString());
        checkAmountDisplay->setText(QString());
        textLabel2_3_2->setText(QApplication::translate("PostCheckDialog", "Amount:", 0, QApplication::UnicodeUTF8));
        textLabel2_3->setText(QApplication::translate("PostCheckDialog", "Payee:", 0, QApplication::UnicodeUTF8));
        textLabel2->setText(QApplication::translate("PostCheckDialog", "Date:", 0, QApplication::UnicodeUTF8));
        exitButton->setText(QApplication::translate("PostCheckDialog", "E&xit", 0, QApplication::UnicodeUTF8));
        exitButton->setShortcut(QApplication::translate("PostCheckDialog", "Alt+X", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PostCheckDialog: public Ui_PostCheckDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POSTCHECKDIALOG_H
