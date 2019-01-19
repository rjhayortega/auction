/********************************************************************************
** Form generated from reading UI file 'vetreportdialogbase.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VETREPORTDIALOGBASE_H
#define UI_VETREPORTDIALOGBASE_H

#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3GroupBox>
#include <Qt3Support/Q3MimeSourceFactory>
#include <Qt3Support/Q3TextEdit>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <string>
#include <vector>
#include "dao/setupdao.h"
#include "dao/tagdao.h"
#include "lineprinter.h"
#include "types/tag.h"

QT_BEGIN_NAMESPACE

class Ui_VetReportDialogBase
{
public:
    QGridLayout *gridLayout;
    QPushButton *printButton;
    QLabel *footerRowDisplay;
    QLabel *textLabel2_2_2;
    QLabel *textLabel2_3;
    QLabel *footerLabel;
    QLabel *footerColDisplay;
    QSpacerItem *spacer4;
    Q3GroupBox *rangeGroup;
    QGridLayout *gridLayout1;
    QLabel *textLabel4;
    QComboBox *firstRecordComboBox;
    QLabel *textLabel5;
    QComboBox *lastRecordComboBox;
    QLabel *indexLabel;
    QComboBox *indexComboBox;
    QLabel *showLabel;
    QComboBox *showComboBox;
    QPushButton *cancelButton;
    Q3TextEdit *footerEdit;
    Q3TextEdit *headerEdit;
    QLabel *headerLabel;
    QLabel *textLabel2;
    QLabel *headerRowDisplay;
    QLabel *textLabel2_2;
    QLabel *headerColDisplay;
    QLabel *textLabel1;
    QSpinBox *heightSpinBox;
    QComboBox *importRecordComboBox;

    void setupUi(QDialog *VetReportDialogBase)
    {
        if (VetReportDialogBase->objectName().isEmpty())
            VetReportDialogBase->setObjectName(QString::fromUtf8("VetReportDialogBase"));
        VetReportDialogBase->setWindowModality(Qt::ApplicationModal);
        VetReportDialogBase->resize(762, 556);
        QFont font;
        font.setFamily(QString::fromUtf8("Bitstream Vera Sans Mono"));
        font.setPointSize(13);
        VetReportDialogBase->setFont(font);
        gridLayout = new QGridLayout(VetReportDialogBase);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        printButton = new QPushButton(VetReportDialogBase);
        printButton->setObjectName(QString::fromUtf8("printButton"));

        gridLayout->addWidget(printButton, 5, 16, 1, 1);

        footerRowDisplay = new QLabel(VetReportDialogBase);
        footerRowDisplay->setObjectName(QString::fromUtf8("footerRowDisplay"));
        footerRowDisplay->setWordWrap(false);

        gridLayout->addWidget(footerRowDisplay, 2, 8, 1, 2);

        textLabel2_2_2 = new QLabel(VetReportDialogBase);
        textLabel2_2_2->setObjectName(QString::fromUtf8("textLabel2_2_2"));
        textLabel2_2_2->setWordWrap(false);

        gridLayout->addWidget(textLabel2_2_2, 2, 10, 1, 1);

        textLabel2_3 = new QLabel(VetReportDialogBase);
        textLabel2_3->setObjectName(QString::fromUtf8("textLabel2_3"));
        textLabel2_3->setWordWrap(false);

        gridLayout->addWidget(textLabel2_3, 2, 6, 1, 2);

        footerLabel = new QLabel(VetReportDialogBase);
        footerLabel->setObjectName(QString::fromUtf8("footerLabel"));
        footerLabel->setWordWrap(false);

        gridLayout->addWidget(footerLabel, 2, 0, 1, 6);

        footerColDisplay = new QLabel(VetReportDialogBase);
        footerColDisplay->setObjectName(QString::fromUtf8("footerColDisplay"));
        footerColDisplay->setWordWrap(false);

        gridLayout->addWidget(footerColDisplay, 2, 11, 1, 1);

        spacer4 = new QSpacerItem(281, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(spacer4, 2, 12, 1, 5);

        rangeGroup = new Q3GroupBox(VetReportDialogBase);
        rangeGroup->setObjectName(QString::fromUtf8("rangeGroup"));
        rangeGroup->setColumnLayout(0, Qt::Vertical);
        rangeGroup->layout()->setSpacing(6);
        rangeGroup->layout()->setContentsMargins(11, 11, 11, 11);
        gridLayout1 = new QGridLayout();
        QBoxLayout *boxlayout = qobject_cast<QBoxLayout *>(rangeGroup->layout());
        if (boxlayout)
            boxlayout->addLayout(gridLayout1);
        gridLayout1->setAlignment(Qt::AlignTop);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        textLabel4 = new QLabel(rangeGroup);
        textLabel4->setObjectName(QString::fromUtf8("textLabel4"));
        textLabel4->setWordWrap(false);

        gridLayout1->addWidget(textLabel4, 0, 0, 1, 1);

        firstRecordComboBox = new QComboBox(rangeGroup);
        firstRecordComboBox->setObjectName(QString::fromUtf8("firstRecordComboBox"));

        gridLayout1->addWidget(firstRecordComboBox, 0, 1, 1, 1);

        textLabel5 = new QLabel(rangeGroup);
        textLabel5->setObjectName(QString::fromUtf8("textLabel5"));
        textLabel5->setWordWrap(false);

        gridLayout1->addWidget(textLabel5, 0, 2, 1, 1);

        lastRecordComboBox = new QComboBox(rangeGroup);
        lastRecordComboBox->setObjectName(QString::fromUtf8("lastRecordComboBox"));

        gridLayout1->addWidget(lastRecordComboBox, 0, 3, 1, 1);


        gridLayout->addWidget(rangeGroup, 4, 0, 1, 11);

        indexLabel = new QLabel(VetReportDialogBase);
        indexLabel->setObjectName(QString::fromUtf8("indexLabel"));
        indexLabel->setWordWrap(false);

        gridLayout->addWidget(indexLabel, 5, 0, 1, 1);

        indexComboBox = new QComboBox(VetReportDialogBase);
        indexComboBox->setObjectName(QString::fromUtf8("indexComboBox"));

        gridLayout->addWidget(indexComboBox, 5, 1, 1, 5);

        showLabel = new QLabel(VetReportDialogBase);
        showLabel->setObjectName(QString::fromUtf8("showLabel"));
        showLabel->setWordWrap(false);

        gridLayout->addWidget(showLabel, 5, 6, 1, 3);

        showComboBox = new QComboBox(VetReportDialogBase);
        showComboBox->setObjectName(QString::fromUtf8("showComboBox"));

        gridLayout->addWidget(showComboBox, 5, 9, 1, 5);

        cancelButton = new QPushButton(VetReportDialogBase);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        gridLayout->addWidget(cancelButton, 5, 14, 1, 2);

        footerEdit = new Q3TextEdit(VetReportDialogBase);
        footerEdit->setObjectName(QString::fromUtf8("footerEdit"));
        footerEdit->setFont(font);
        footerEdit->setTextFormat(Qt::PlainText);
        footerEdit->setWordWrap(Q3TextEdit::NoWrap);

        gridLayout->addWidget(footerEdit, 3, 0, 1, 17);

        headerEdit = new Q3TextEdit(VetReportDialogBase);
        headerEdit->setObjectName(QString::fromUtf8("headerEdit"));
        headerEdit->setFont(font);
        headerEdit->setTextFormat(Qt::PlainText);
        headerEdit->setWordWrap(Q3TextEdit::NoWrap);
        headerEdit->setOverwriteMode(false);
        headerEdit->setAutoFormatting(Q3TextEdit::AutoAll);

        gridLayout->addWidget(headerEdit, 1, 0, 1, 17);

        headerLabel = new QLabel(VetReportDialogBase);
        headerLabel->setObjectName(QString::fromUtf8("headerLabel"));
        headerLabel->setWordWrap(false);

        gridLayout->addWidget(headerLabel, 0, 0, 1, 2);

        textLabel2 = new QLabel(VetReportDialogBase);
        textLabel2->setObjectName(QString::fromUtf8("textLabel2"));
        textLabel2->setWordWrap(false);

        gridLayout->addWidget(textLabel2, 0, 2, 1, 1);

        headerRowDisplay = new QLabel(VetReportDialogBase);
        headerRowDisplay->setObjectName(QString::fromUtf8("headerRowDisplay"));
        headerRowDisplay->setWordWrap(false);

        gridLayout->addWidget(headerRowDisplay, 0, 3, 1, 1);

        textLabel2_2 = new QLabel(VetReportDialogBase);
        textLabel2_2->setObjectName(QString::fromUtf8("textLabel2_2"));
        textLabel2_2->setWordWrap(false);

        gridLayout->addWidget(textLabel2_2, 0, 4, 1, 1);

        headerColDisplay = new QLabel(VetReportDialogBase);
        headerColDisplay->setObjectName(QString::fromUtf8("headerColDisplay"));
        headerColDisplay->setWordWrap(false);

        gridLayout->addWidget(headerColDisplay, 0, 5, 1, 2);

        textLabel1 = new QLabel(VetReportDialogBase);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
        textLabel1->setWordWrap(false);

        gridLayout->addWidget(textLabel1, 0, 7, 1, 6);

        heightSpinBox = new QSpinBox(VetReportDialogBase);
        heightSpinBox->setObjectName(QString::fromUtf8("heightSpinBox"));
        heightSpinBox->setValue(48);

        gridLayout->addWidget(heightSpinBox, 0, 13, 1, 2);

        importRecordComboBox = new QComboBox(VetReportDialogBase);
        importRecordComboBox->setObjectName(QString::fromUtf8("importRecordComboBox"));

        gridLayout->addWidget(importRecordComboBox, 0, 15, 1, 2);


        retranslateUi(VetReportDialogBase);

        QMetaObject::connectSlotsByName(VetReportDialogBase);
    } // setupUi

    void retranslateUi(QDialog *VetReportDialogBase)
    {
        VetReportDialogBase->setWindowTitle(QApplication::translate("VetReportDialogBase", "Vet Report Dialog Base", 0, QApplication::UnicodeUTF8));
        printButton->setText(QApplication::translate("VetReportDialogBase", "Print", 0, QApplication::UnicodeUTF8));
        footerRowDisplay->setText(QString());
        textLabel2_2_2->setText(QApplication::translate("VetReportDialogBase", "Col:", 0, QApplication::UnicodeUTF8));
        textLabel2_3->setText(QApplication::translate("VetReportDialogBase", "Row:", 0, QApplication::UnicodeUTF8));
        footerLabel->setText(QApplication::translate("VetReportDialogBase", "Footer", 0, QApplication::UnicodeUTF8));
        footerColDisplay->setText(QString());
        rangeGroup->setTitle(QApplication::translate("VetReportDialogBase", "Range", 0, QApplication::UnicodeUTF8));
        textLabel4->setText(QApplication::translate("VetReportDialogBase", "First", 0, QApplication::UnicodeUTF8));
        textLabel5->setText(QApplication::translate("VetReportDialogBase", "Last", 0, QApplication::UnicodeUTF8));
        indexLabel->setText(QApplication::translate("VetReportDialogBase", "Index", 0, QApplication::UnicodeUTF8));
        indexComboBox->clear();
        indexComboBox->insertItems(0, QStringList()
         << QApplication::translate("VetReportDialogBase", "Record Number", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VetReportDialogBase", "Age", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VetReportDialogBase", "Allflex", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VetReportDialogBase", "Breed", 0, QApplication::UnicodeUTF8)
        );
        showLabel->setText(QApplication::translate("VetReportDialogBase", "Show", 0, QApplication::UnicodeUTF8));
        showComboBox->clear();
        showComboBox->insertItems(0, QStringList()
         << QApplication::translate("VetReportDialogBase", "All", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VetReportDialogBase", "Deleted", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VetReportDialogBase", "Non-Deleted", 0, QApplication::UnicodeUTF8)
        );
        cancelButton->setText(QApplication::translate("VetReportDialogBase", "Cancel", 0, QApplication::UnicodeUTF8));
        headerLabel->setText(QApplication::translate("VetReportDialogBase", "Header", 0, QApplication::UnicodeUTF8));
        textLabel2->setText(QApplication::translate("VetReportDialogBase", "Row:", 0, QApplication::UnicodeUTF8));
        headerRowDisplay->setText(QString());
        textLabel2_2->setText(QApplication::translate("VetReportDialogBase", "Col:", 0, QApplication::UnicodeUTF8));
        headerColDisplay->setText(QString());
        textLabel1->setText(QApplication::translate("VetReportDialogBase", "Height of form (in lines)", 0, QApplication::UnicodeUTF8));
        importRecordComboBox->clear();
        importRecordComboBox->insertItems(0, QStringList()
         << QApplication::translate("VetReportDialogBase", "Import Daily Buyer", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VetReportDialogBase", "Import Perm Buyer", 0, QApplication::UnicodeUTF8)
        );
    } // retranslateUi

};

namespace Ui {
    class VetReportDialogBase: public Ui_VetReportDialogBase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VETREPORTDIALOGBASE_H
