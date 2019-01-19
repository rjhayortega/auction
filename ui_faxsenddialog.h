/********************************************************************************
** Form generated from reading UI file 'faxsenddialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FAXSENDDIALOG_H
#define UI_FAXSENDDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_sendFaxDialog
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout_3;
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit;
    QLabel *label;

    void setupUi(QDialog *sendFaxDialog)
    {
        if (sendFaxDialog->objectName().isEmpty())
            sendFaxDialog->setObjectName(QString::fromUtf8("sendFaxDialog"));
        sendFaxDialog->setWindowModality(Qt::ApplicationModal);
        sendFaxDialog->resize(395, 245);
        gridLayout_2 = new QGridLayout(sendFaxDialog);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        buttonBox = new QDialogButtonBox(sendFaxDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_3->addWidget(buttonBox, 2, 0, 1, 1);

        groupBox = new QGroupBox(sendFaxDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 1, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);


        horizontalLayout->addLayout(gridLayout);


        gridLayout_3->addWidget(groupBox, 1, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout_3, 0, 0, 1, 1);


        retranslateUi(sendFaxDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), sendFaxDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), sendFaxDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(sendFaxDialog);
    } // setupUi

    void retranslateUi(QDialog *sendFaxDialog)
    {
        sendFaxDialog->setWindowTitle(QApplication::translate("sendFaxDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("sendFaxDialog", "Fax number", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("sendFaxDialog", "Fax number", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class sendFaxDialog: public Ui_sendFaxDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FAXSENDDIALOG_H
