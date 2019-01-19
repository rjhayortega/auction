/********************************************************************************
** Form generated from reading UI file 'previewdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREVIEWDIALOG_H
#define UI_PREVIEWDIALOG_H

#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3MimeSourceFactory>
#include <Qt3Support/Q3TextEdit>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include "dao/printerdao.h"
#include "dao/setupdao.h"
#include "reports/textreport.h"

QT_BEGIN_NAMESPACE

class Ui_PreviewDialog
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    Q3TextEdit *previewText;
    QHBoxLayout *horizontalLayout;
    QPushButton *printPostscriptButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *printButton;

    void setupUi(QDialog *PreviewDialog)
    {
        if (PreviewDialog->objectName().isEmpty())
            PreviewDialog->setObjectName(QString::fromUtf8("PreviewDialog"));
        PreviewDialog->setWindowModality(Qt::ApplicationModal);
        PreviewDialog->resize(1017, 613);
        QFont font;
        font.setPointSize(13);
        PreviewDialog->setFont(font);
        gridLayout = new QGridLayout(PreviewDialog);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        previewText = new Q3TextEdit(PreviewDialog);
        previewText->setObjectName(QString::fromUtf8("previewText"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Bitstream Vera Sans Mono"));
        font1.setPointSize(13);
        font1.setBold(true);
        font1.setWeight(75);
        previewText->setFont(font1);
        previewText->setProperty("readOnly", QVariant(true));

        verticalLayout->addWidget(previewText);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        printPostscriptButton = new QPushButton(PreviewDialog);
        printPostscriptButton->setObjectName(QString::fromUtf8("printPostscriptButton"));

        horizontalLayout->addWidget(printPostscriptButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        printButton = new QPushButton(PreviewDialog);
        printButton->setObjectName(QString::fromUtf8("printButton"));

        horizontalLayout->addWidget(printButton);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(PreviewDialog);

        QMetaObject::connectSlotsByName(PreviewDialog);
    } // setupUi

    void retranslateUi(QDialog *PreviewDialog)
    {
        PreviewDialog->setWindowTitle(QApplication::translate("PreviewDialog", "Preview", 0, QApplication::UnicodeUTF8));
        previewText->setProperty("text", QVariant(QString()));
        printPostscriptButton->setText(QApplication::translate("PreviewDialog", "Print (Postscript)", 0, QApplication::UnicodeUTF8));
        printButton->setText(QApplication::translate("PreviewDialog", "Print", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PreviewDialog: public Ui_PreviewDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREVIEWDIALOG_H
