/********************************************************************************
** Form generated from reading UI file 'reportsetupdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REPORTSETUPDIALOG_H
#define UI_REPORTSETUPDIALOG_H

#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3MimeSourceFactory>
#include <Qt3Support/Q3TextEdit>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include "dao/setupdao.h"

QT_BEGIN_NAMESPACE

class Ui_ReportSetupDialog
{
public:
    QSpinBox *firstLineSpinBox;
    QSpinBox *pageLengthSpinBox;
    QLabel *textLabel1_2;
    QLabel *textLabel1;
    Q3TextEdit *marketReportComment;
    QPushButton *cancelButton;
    QPushButton *okButton;
    QLabel *textLabel1_2_2;

    void setupUi(QDialog *ReportSetupDialog)
    {
        if (ReportSetupDialog->objectName().isEmpty())
            ReportSetupDialog->setObjectName(QString::fromUtf8("ReportSetupDialog"));
        ReportSetupDialog->setWindowModality(Qt::ApplicationModal);
        ReportSetupDialog->resize(534, 310);
        QFont font;
        font.setPointSize(13);
        ReportSetupDialog->setFont(font);
        firstLineSpinBox = new QSpinBox(ReportSetupDialog);
        firstLineSpinBox->setObjectName(QString::fromUtf8("firstLineSpinBox"));
        firstLineSpinBox->setGeometry(QRect(20, 10, 80, 30));
        firstLineSpinBox->setMinimum(0);
        firstLineSpinBox->setMaximum(20);
        firstLineSpinBox->setValue(0);
        pageLengthSpinBox = new QSpinBox(ReportSetupDialog);
        pageLengthSpinBox->setObjectName(QString::fromUtf8("pageLengthSpinBox"));
        pageLengthSpinBox->setGeometry(QRect(20, 50, 80, 30));
        pageLengthSpinBox->setMinimum(30);
        pageLengthSpinBox->setMaximum(80);
        pageLengthSpinBox->setValue(64);
        textLabel1_2 = new QLabel(ReportSetupDialog);
        textLabel1_2->setObjectName(QString::fromUtf8("textLabel1_2"));
        textLabel1_2->setGeometry(QRect(120, 50, 140, 30));
        textLabel1_2->setWordWrap(false);
        textLabel1 = new QLabel(ReportSetupDialog);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
        textLabel1->setGeometry(QRect(120, 10, 140, 30));
        textLabel1->setWordWrap(false);
        marketReportComment = new Q3TextEdit(ReportSetupDialog);
        marketReportComment->setObjectName(QString::fromUtf8("marketReportComment"));
        marketReportComment->setGeometry(QRect(10, 120, 510, 110));
        marketReportComment->setTextFormat(Qt::PlainText);
        cancelButton = new QPushButton(ReportSetupDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(310, 270, 100, 30));
        okButton = new QPushButton(ReportSetupDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setGeometry(QRect(420, 270, 100, 30));
        textLabel1_2_2 = new QLabel(ReportSetupDialog);
        textLabel1_2_2->setObjectName(QString::fromUtf8("textLabel1_2_2"));
        textLabel1_2_2->setGeometry(QRect(10, 90, 480, 21));
        textLabel1_2_2->setWordWrap(false);

        retranslateUi(ReportSetupDialog);

        QMetaObject::connectSlotsByName(ReportSetupDialog);
    } // setupUi

    void retranslateUi(QDialog *ReportSetupDialog)
    {
        ReportSetupDialog->setWindowTitle(QApplication::translate("ReportSetupDialog", "Setup Reports", 0, QApplication::UnicodeUTF8));
        textLabel1_2->setText(QApplication::translate("ReportSetupDialog", "Page Length", 0, QApplication::UnicodeUTF8));
        textLabel1->setText(QApplication::translate("ReportSetupDialog", "First Line", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("ReportSetupDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("ReportSetupDialog", "Ok", 0, QApplication::UnicodeUTF8));
        textLabel1_2_2->setText(QApplication::translate("ReportSetupDialog", "Reports Header Comment", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ReportSetupDialog: public Ui_ReportSetupDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REPORTSETUPDIALOG_H
