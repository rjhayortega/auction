/********************************************************************************
** Form generated from reading UI file 'history.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HISTORY_H
#define UI_HISTORY_H

#include <Qt3Support/Q3DateEdit>
#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include "autofilledit.h"
#include "dao/animalcodedao.h"
#include "dao/historydao.h"
#include "dao/salemanager.h"
#include "types/historyitem.h"

QT_BEGIN_NAMESPACE

class Ui_History
{
public:
    QComboBox *indexCombo;
    QLabel *paramaterLabel;
    Q3DateEdit *startDateEntry;
    Q3DateEdit *endDateEntry;
    QPushButton *reportButton;
    QLabel *textLabel3_2;
    QLabel *nameLabel;
    QComboBox *typeCombo;
    QLabel *textLabel3;
    QLineEdit *_historyParamaterEdit;
    QLabel *textLabel2;

    void setupUi(QDialog *History)
    {
        if (History->objectName().isEmpty())
            History->setObjectName(QString::fromUtf8("History"));
        History->setWindowModality(Qt::ApplicationModal);
        History->resize(676, 257);
        QFont font;
        font.setPointSize(13);
        History->setFont(font);
        indexCombo = new QComboBox(History);
        indexCombo->setObjectName(QString::fromUtf8("indexCombo"));
        indexCombo->setGeometry(QRect(200, 70, 181, 30));
        paramaterLabel = new QLabel(History);
        paramaterLabel->setObjectName(QString::fromUtf8("paramaterLabel"));
        paramaterLabel->setGeometry(QRect(11, 110, 180, 31));
        paramaterLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        paramaterLabel->setWordWrap(false);
        startDateEntry = new Q3DateEdit(History);
        startDateEntry->setObjectName(QString::fromUtf8("startDateEntry"));
        startDateEntry->setGeometry(QRect(160, 160, 160, 30));
        endDateEntry = new Q3DateEdit(History);
        endDateEntry->setObjectName(QString::fromUtf8("endDateEntry"));
        endDateEntry->setGeometry(QRect(490, 161, 160, 30));
        reportButton = new QPushButton(History);
        reportButton->setObjectName(QString::fromUtf8("reportButton"));
        reportButton->setGeometry(QRect(550, 210, 100, 31));
        reportButton->setAutoDefault(true);
        textLabel3_2 = new QLabel(History);
        textLabel3_2->setObjectName(QString::fromUtf8("textLabel3_2"));
        textLabel3_2->setGeometry(QRect(340, 160, 141, 31));
        textLabel3_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel3_2->setWordWrap(false);
        nameLabel = new QLabel(History);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));
        nameLabel->setGeometry(QRect(10, 70, 180, 30));
        nameLabel->setFont(font);
        nameLabel->setFrameShape(QFrame::NoFrame);
        nameLabel->setFrameShadow(QFrame::Plain);
        nameLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        nameLabel->setWordWrap(false);
        typeCombo = new QComboBox(History);
        typeCombo->setObjectName(QString::fromUtf8("typeCombo"));
        typeCombo->setGeometry(QRect(200, 110, 450, 31));
        textLabel3 = new QLabel(History);
        textLabel3->setObjectName(QString::fromUtf8("textLabel3"));
        textLabel3->setGeometry(QRect(10, 160, 141, 31));
        textLabel3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel3->setWordWrap(false);
        _historyParamaterEdit = new QLineEdit(History);
        _historyParamaterEdit->setObjectName(QString::fromUtf8("_historyParamaterEdit"));
        _historyParamaterEdit->setGeometry(QRect(200, 110, 450, 31));
        textLabel2 = new QLabel(History);
        textLabel2->setObjectName(QString::fromUtf8("textLabel2"));
        textLabel2->setGeometry(QRect(10, 10, 391, 50));
        textLabel2->setWordWrap(false);

        retranslateUi(History);

        QMetaObject::connectSlotsByName(History);
    } // setupUi

    void retranslateUi(QDialog *History)
    {
        History->setWindowTitle(QApplication::translate("History", "History", 0, QApplication::UnicodeUTF8));
        indexCombo->clear();
        indexCombo->insertItems(0, QStringList()
         << QApplication::translate("History", "Seller", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("History", "Buyer", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("History", "Animal", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("History", "Date", 0, QApplication::UnicodeUTF8)
        );
        paramaterLabel->setText(QApplication::translate("History", "History Param:", 0, QApplication::UnicodeUTF8));
        reportButton->setText(QApplication::translate("History", "Report", 0, QApplication::UnicodeUTF8));
        textLabel3_2->setText(QApplication::translate("History", "Date Ending", 0, QApplication::UnicodeUTF8));
        nameLabel->setText(QApplication::translate("History", "Index By:", 0, QApplication::UnicodeUTF8));
        typeCombo->clear();
        typeCombo->insertItems(0, QStringList()
         << QApplication::translate("History", "Seller", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("History", "Buyer", 0, QApplication::UnicodeUTF8)
        );
        textLabel3->setText(QApplication::translate("History", "Date Starting:", 0, QApplication::UnicodeUTF8));
        textLabel2->setText(QApplication::translate("History", "<h1>History</h1>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class History: public Ui_History {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HISTORY_H
