/********************************************************************************
** Form generated from reading UI file 'faxsetupdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FAXSETUPDIALOG_H
#define UI_FAXSETUPDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFormLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_FaxSetupDialog
{
public:
    QGridLayout *gridLayout;
    QFormLayout *formLayout;
    QCheckBox *enableFaxCheckBox;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *FaxSetupDialog)
    {
        if (FaxSetupDialog->objectName().isEmpty())
            FaxSetupDialog->setObjectName(QString::fromUtf8("FaxSetupDialog"));
        FaxSetupDialog->setWindowModality(Qt::ApplicationModal);
        FaxSetupDialog->resize(386, 167);
        gridLayout = new QGridLayout(FaxSetupDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        enableFaxCheckBox = new QCheckBox(FaxSetupDialog);
        enableFaxCheckBox->setObjectName(QString::fromUtf8("enableFaxCheckBox"));

        formLayout->setWidget(1, QFormLayout::LabelRole, enableFaxCheckBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(2, QFormLayout::LabelRole, verticalSpacer);

        buttonBox = new QDialogButtonBox(FaxSetupDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Save);
        buttonBox->setCenterButtons(true);

        formLayout->setWidget(3, QFormLayout::FieldRole, buttonBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        formLayout->setItem(0, QFormLayout::LabelRole, horizontalSpacer);


        gridLayout->addLayout(formLayout, 0, 0, 1, 1);


        retranslateUi(FaxSetupDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), FaxSetupDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), FaxSetupDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(FaxSetupDialog);
    } // setupUi

    void retranslateUi(QDialog *FaxSetupDialog)
    {
        FaxSetupDialog->setWindowTitle(QApplication::translate("FaxSetupDialog", "Fax modem setup", 0, QApplication::UnicodeUTF8));
        enableFaxCheckBox->setText(QApplication::translate("FaxSetupDialog", "Enable Fax modem", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FaxSetupDialog: public Ui_FaxSetupDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FAXSETUPDIALOG_H
