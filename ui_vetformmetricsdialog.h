/********************************************************************************
** Form generated from reading UI file 'vetformmetricsdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VETFORMMETRICSDIALOG_H
#define UI_VETFORMMETRICSDIALOG_H

#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3Header>
#include <Qt3Support/Q3MimeSourceFactory>
#include <Qt3Support/Q3Table>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include "dao/setupdao.h"

QT_BEGIN_NAMESPACE

class Ui_VetFormMetricsDialog
{
public:
    Q3Table *metricsTable;
    QPushButton *cancelButton;
    QPushButton *okButton;

    void setupUi(QDialog *VetFormMetricsDialog)
    {
        if (VetFormMetricsDialog->objectName().isEmpty())
            VetFormMetricsDialog->setObjectName(QString::fromUtf8("VetFormMetricsDialog"));
        VetFormMetricsDialog->setWindowModality(Qt::ApplicationModal);
        VetFormMetricsDialog->resize(426, 243);
        QFont font;
        font.setPointSize(13);
        VetFormMetricsDialog->setFont(font);
        metricsTable = new Q3Table(VetFormMetricsDialog);
        metricsTable->setObjectName(QString::fromUtf8("metricsTable"));
        metricsTable->setGeometry(QRect(20, 20, 380, 140));
        metricsTable->setNumRows(5);
        metricsTable->setNumCols(2);
        cancelButton = new QPushButton(VetFormMetricsDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(220, 170, 81, 31));
        okButton = new QPushButton(VetFormMetricsDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setGeometry(QRect(320, 170, 81, 31));

        retranslateUi(VetFormMetricsDialog);

        QMetaObject::connectSlotsByName(VetFormMetricsDialog);
    } // setupUi

    void retranslateUi(QDialog *VetFormMetricsDialog)
    {
        VetFormMetricsDialog->setWindowTitle(QApplication::translate("VetFormMetricsDialog", "Form Metrics For Vet Manager", 0, QApplication::UnicodeUTF8));
        metricsTable->horizontalHeader()->setLabel(0, QApplication::translate("VetFormMetricsDialog", "Start", 0, QApplication::UnicodeUTF8));
        metricsTable->horizontalHeader()->setLabel(1, QApplication::translate("VetFormMetricsDialog", "Height", 0, QApplication::UnicodeUTF8));
        metricsTable->verticalHeader()->setLabel(0, QApplication::translate("VetFormMetricsDialog", "SD Certificate", 0, QApplication::UnicodeUTF8));
        metricsTable->verticalHeader()->setLabel(1, QApplication::translate("VetFormMetricsDialog", "MN Certificate", 0, QApplication::UnicodeUTF8));
        metricsTable->verticalHeader()->setLabel(2, QApplication::translate("VetFormMetricsDialog", "Bruc. Certificate", 0, QApplication::UnicodeUTF8));
        metricsTable->verticalHeader()->setLabel(3, QApplication::translate("VetFormMetricsDialog", "TB Certificate", 0, QApplication::UnicodeUTF8));
        metricsTable->verticalHeader()->setLabel(4, QApplication::translate("VetFormMetricsDialog", "ALLFLEX Report", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("VetFormMetricsDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("VetFormMetricsDialog", "Ok", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class VetFormMetricsDialog: public Ui_VetFormMetricsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VETFORMMETRICSDIALOG_H
