/********************************************************************************
** Form generated from reading UI file 'vetdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VETDIALOG_H
#define UI_VETDIALOG_H

#include <Qt3Support/Q3DateEdit>
#include <Qt3Support/Q3GroupBox>
#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <Qt3Support/Q3Process>
#include <QtGui/QRegExpValidator>
#include <vector>
#include "dao/salemanager.h"
#include "dao/setupdao.h"
#include "dao/tagdao.h"
#include "dao/transactiondao.h"
#include "lineprinter.h"
#include "reports/tuberculosisrecord.h"
#include "types/healthrecord.h"

QT_BEGIN_NAMESPACE

class Ui_VetDialog
{
public:
    QWidget *layout34;
    QHBoxLayout *hboxLayout;
    QGridLayout *gridLayout;
    QLabel *textLabel1;
    QHBoxLayout *hboxLayout1;
    QLabel *textLabel2;
    QLabel *tagCountDisplay;
    QLabel *consignorDisplay;
    QVBoxLayout *vboxLayout;
    QLabel *textLabel1_2;
    QLabel *consigneeDisplay;
    QPushButton *vetEditButton;
    Q3GroupBox *printerGroupBox;
    QGridLayout *gridLayout1;
    QComboBox *printerComboBox;
    QPushButton *nextButton;
    QWidget *layout15;
    QGridLayout *gridLayout2;
    QLabel *textLabel3_2_2_2;
    QLineEdit *breedEdit;
    QLabel *textLabel3_2_2;
    QLabel *textLabel1_5;
    QLabel *textLabel3_2_2_2_3_2;
    Q3DateEdit *testDateEdit;
    QSpinBox *ageSpinBox;
    QLabel *textLabel3_2;
    QLabel *textLabel3;
    QLineEdit *brucTagEdit;
    QLineEdit *sexEdit;
    QLabel *textLabel3_2_2_2_3_2_2;
    QLabel *textLabel1_4;
    QLabel *textLabel3_2_2_2_3;
    QLineEdit *rfid;
    QLineEdit *auctionTagEdit;
    QLabel *textLabel3_2_2_2_2;
    QLineEdit *oldTagEdit;
    QLineEdit *chvEdit;
    Q3DateEdit *tbInjDate;
    QWidget *layout7;
    QHBoxLayout *hboxLayout2;
    QLineEdit *searchEdit;
    QPushButton *searchButton;
    QWidget *layout32;
    QHBoxLayout *hboxLayout3;
    QVBoxLayout *vboxLayout1;
    QLabel *textLabel3_2_2_2_4;
    QLabel *textLabel3_2_2_2_4_2;
    QLabel *textLabel3_2_2_2_4_2_2;
    QGridLayout *gridLayout3;
    QSpacerItem *spacer1;
    QLineEdit *brucEdit;
    QLineEdit *commentEdit;
    QLineEdit *pregDurationEdit;
    Q3GroupBox *formGroupBox;
    QGridLayout *gridLayout4;
    QComboBox *formComboBox;
    QPushButton *formMetricsButton;
    QCheckBox *deletedCheckBox;
    QWidget *layout11;
    QGridLayout *gridLayout5;
    QLabel *textLabel1_3;
    QLabel *recordNumberDisplay;
    QPushButton *prevButton;
    Q3GroupBox *indexGroupBox;
    QComboBox *indexCombo;
    QPushButton *browseButton;
    QPushButton *addRecordButton;

    void setupUi(QDialog *VetDialog)
    {
        if (VetDialog->objectName().isEmpty())
            VetDialog->setObjectName(QString::fromUtf8("VetDialog"));
        VetDialog->setWindowModality(Qt::ApplicationModal);
        VetDialog->resize(1010, 689);
        QFont font;
        font.setPointSize(13);
        VetDialog->setFont(font);
        layout34 = new QWidget(VetDialog);
        layout34->setObjectName(QString::fromUtf8("layout34"));
        layout34->setGeometry(QRect(11, 11, 988, 130));
        hboxLayout = new QHBoxLayout(layout34);
        hboxLayout->setSpacing(6);
        hboxLayout->setContentsMargins(11, 11, 11, 11);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        textLabel1 = new QLabel(layout34);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
        textLabel1->setWordWrap(false);

        gridLayout->addWidget(textLabel1, 0, 0, 1, 1);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        textLabel2 = new QLabel(layout34);
        textLabel2->setObjectName(QString::fromUtf8("textLabel2"));
        textLabel2->setWordWrap(false);

        hboxLayout1->addWidget(textLabel2);

        tagCountDisplay = new QLabel(layout34);
        tagCountDisplay->setObjectName(QString::fromUtf8("tagCountDisplay"));
        tagCountDisplay->setWordWrap(false);

        hboxLayout1->addWidget(tagCountDisplay);


        gridLayout->addLayout(hboxLayout1, 0, 1, 1, 1);

        consignorDisplay = new QLabel(layout34);
        consignorDisplay->setObjectName(QString::fromUtf8("consignorDisplay"));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(244, 244, 244, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(255, 255, 255, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(249, 249, 249, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(122, 122, 122, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(162, 162, 162, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush2);
        QBrush brush6(QColor(247, 247, 247, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush6);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
        QBrush brush7(QColor(0, 0, 128, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Highlight, brush7);
        palette.setBrush(QPalette::Active, QPalette::HighlightedText, brush2);
        palette.setBrush(QPalette::Active, QPalette::Link, brush);
        palette.setBrush(QPalette::Active, QPalette::LinkVisited, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Highlight, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::HighlightedText, brush2);
        QBrush brush8(QColor(83, 83, 120, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Inactive, QPalette::Link, brush8);
        QBrush brush9(QColor(0, 64, 0, 255));
        brush9.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Inactive, QPalette::LinkVisited, brush9);
        QBrush brush10(QColor(128, 128, 128, 255));
        brush10.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush10);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush10);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush10);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Highlight, brush7);
        palette.setBrush(QPalette::Disabled, QPalette::HighlightedText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Link, brush8);
        palette.setBrush(QPalette::Disabled, QPalette::LinkVisited, brush9);
        consignorDisplay->setPalette(palette);
        consignorDisplay->setWordWrap(false);

        gridLayout->addWidget(consignorDisplay, 1, 0, 1, 2);


        hboxLayout->addLayout(gridLayout);

        vboxLayout = new QVBoxLayout();
        vboxLayout->setSpacing(6);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        textLabel1_2 = new QLabel(layout34);
        textLabel1_2->setObjectName(QString::fromUtf8("textLabel1_2"));
        textLabel1_2->setWordWrap(false);

        vboxLayout->addWidget(textLabel1_2);

        consigneeDisplay = new QLabel(layout34);
        consigneeDisplay->setObjectName(QString::fromUtf8("consigneeDisplay"));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Light, brush2);
        palette1.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        palette1.setBrush(QPalette::Active, QPalette::Dark, brush4);
        palette1.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        palette1.setBrush(QPalette::Active, QPalette::BrightText, brush2);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush6);
        palette1.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette1.setBrush(QPalette::Active, QPalette::Highlight, brush7);
        palette1.setBrush(QPalette::Active, QPalette::HighlightedText, brush2);
        palette1.setBrush(QPalette::Active, QPalette::Link, brush);
        palette1.setBrush(QPalette::Active, QPalette::LinkVisited, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Midlight, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette1.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::BrightText, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Highlight, brush7);
        palette1.setBrush(QPalette::Inactive, QPalette::HighlightedText, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Link, brush8);
        palette1.setBrush(QPalette::Inactive, QPalette::LinkVisited, brush9);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush10);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Midlight, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush10);
        palette1.setBrush(QPalette::Disabled, QPalette::BrightText, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush10);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush6);
        palette1.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Highlight, brush7);
        palette1.setBrush(QPalette::Disabled, QPalette::HighlightedText, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Link, brush8);
        palette1.setBrush(QPalette::Disabled, QPalette::LinkVisited, brush9);
        consigneeDisplay->setPalette(palette1);
        consigneeDisplay->setWordWrap(false);

        vboxLayout->addWidget(consigneeDisplay);


        hboxLayout->addLayout(vboxLayout);

        vetEditButton = new QPushButton(VetDialog);
        vetEditButton->setObjectName(QString::fromUtf8("vetEditButton"));
        vetEditButton->setEnabled(false);
        vetEditButton->setGeometry(QRect(328, 504, 204, 32));
        vetEditButton->setAutoDefault(false);
        printerGroupBox = new Q3GroupBox(VetDialog);
        printerGroupBox->setObjectName(QString::fromUtf8("printerGroupBox"));
        printerGroupBox->setGeometry(QRect(11, 488, 311, 105));
        printerGroupBox->setColumnLayout(0, Qt::Vertical);
        printerGroupBox->layout()->setSpacing(6);
        printerGroupBox->layout()->setContentsMargins(11, 11, 11, 11);
        gridLayout1 = new QGridLayout();
        QBoxLayout *boxlayout = qobject_cast<QBoxLayout *>(printerGroupBox->layout());
        if (boxlayout)
            boxlayout->addLayout(gridLayout1);
        gridLayout1->setAlignment(Qt::AlignTop);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        printerComboBox = new QComboBox(printerGroupBox);
        printerComboBox->setObjectName(QString::fromUtf8("printerComboBox"));
        printerComboBox->setInsertPolicy(QComboBox::NoInsert);
        printerComboBox->setDuplicatesEnabled(false);

        gridLayout1->addWidget(printerComboBox, 0, 0, 1, 1);

        nextButton = new QPushButton(VetDialog);
        nextButton->setObjectName(QString::fromUtf8("nextButton"));
        nextButton->setGeometry(QRect(846, 630, 150, 32));
        nextButton->setAutoDefault(false);
        nextButton->setDefault(false);
        layout15 = new QWidget(VetDialog);
        layout15->setObjectName(QString::fromUtf8("layout15"));
        layout15->setGeometry(QRect(10, 150, 990, 70));
        gridLayout2 = new QGridLayout(layout15);
        gridLayout2->setSpacing(6);
        gridLayout2->setContentsMargins(11, 11, 11, 11);
        gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
        gridLayout2->setContentsMargins(0, 0, 0, 0);
        textLabel3_2_2_2 = new QLabel(layout15);
        textLabel3_2_2_2->setObjectName(QString::fromUtf8("textLabel3_2_2_2"));
        textLabel3_2_2_2->setWordWrap(false);

        gridLayout2->addWidget(textLabel3_2_2_2, 0, 3, 1, 1);

        breedEdit = new QLineEdit(layout15);
        breedEdit->setObjectName(QString::fromUtf8("breedEdit"));
        breedEdit->setMaximumSize(QSize(200, 32767));

        gridLayout2->addWidget(breedEdit, 1, 1, 1, 1);

        textLabel3_2_2 = new QLabel(layout15);
        textLabel3_2_2->setObjectName(QString::fromUtf8("textLabel3_2_2"));
        textLabel3_2_2->setWordWrap(false);

        gridLayout2->addWidget(textLabel3_2_2, 0, 2, 1, 1);

        textLabel1_5 = new QLabel(layout15);
        textLabel1_5->setObjectName(QString::fromUtf8("textLabel1_5"));
        textLabel1_5->setWordWrap(false);

        gridLayout2->addWidget(textLabel1_5, 0, 8, 1, 1);

        textLabel3_2_2_2_3_2 = new QLabel(layout15);
        textLabel3_2_2_2_3_2->setObjectName(QString::fromUtf8("textLabel3_2_2_2_3_2"));
        textLabel3_2_2_2_3_2->setWordWrap(false);

        gridLayout2->addWidget(textLabel3_2_2_2_3_2, 0, 7, 1, 1);

        testDateEdit = new Q3DateEdit(layout15);
        testDateEdit->setObjectName(QString::fromUtf8("testDateEdit"));
        testDateEdit->setMaximumSize(QSize(32767, 32767));

        gridLayout2->addWidget(testDateEdit, 1, 0, 1, 1);

        ageSpinBox = new QSpinBox(layout15);
        ageSpinBox->setObjectName(QString::fromUtf8("ageSpinBox"));
        ageSpinBox->setMaximumSize(QSize(150, 32767));

        gridLayout2->addWidget(ageSpinBox, 1, 4, 1, 1);

        textLabel3_2 = new QLabel(layout15);
        textLabel3_2->setObjectName(QString::fromUtf8("textLabel3_2"));
        textLabel3_2->setWordWrap(false);

        gridLayout2->addWidget(textLabel3_2, 0, 1, 1, 1);

        textLabel3 = new QLabel(layout15);
        textLabel3->setObjectName(QString::fromUtf8("textLabel3"));
        textLabel3->setWordWrap(false);

        gridLayout2->addWidget(textLabel3, 0, 0, 1, 1);

        brucTagEdit = new QLineEdit(layout15);
        brucTagEdit->setObjectName(QString::fromUtf8("brucTagEdit"));
        brucTagEdit->setMaximumSize(QSize(200, 32767));

        gridLayout2->addWidget(brucTagEdit, 1, 5, 1, 1);

        sexEdit = new QLineEdit(layout15);
        sexEdit->setObjectName(QString::fromUtf8("sexEdit"));
        sexEdit->setMaximumSize(QSize(100, 32767));

        gridLayout2->addWidget(sexEdit, 1, 2, 1, 1);

        textLabel3_2_2_2_3_2_2 = new QLabel(layout15);
        textLabel3_2_2_2_3_2_2->setObjectName(QString::fromUtf8("textLabel3_2_2_2_3_2_2"));
        textLabel3_2_2_2_3_2_2->setWordWrap(false);

        gridLayout2->addWidget(textLabel3_2_2_2_3_2_2, 0, 9, 1, 1);

        textLabel1_4 = new QLabel(layout15);
        textLabel1_4->setObjectName(QString::fromUtf8("textLabel1_4"));
        textLabel1_4->setWordWrap(false);

        gridLayout2->addWidget(textLabel1_4, 0, 6, 1, 1);

        textLabel3_2_2_2_3 = new QLabel(layout15);
        textLabel3_2_2_2_3->setObjectName(QString::fromUtf8("textLabel3_2_2_2_3"));
        textLabel3_2_2_2_3->setWordWrap(false);

        gridLayout2->addWidget(textLabel3_2_2_2_3, 0, 5, 1, 1);

        rfid = new QLineEdit(layout15);
        rfid->setObjectName(QString::fromUtf8("rfid"));
        rfid->setMaximumSize(QSize(200, 32767));

        gridLayout2->addWidget(rfid, 1, 6, 1, 1);

        auctionTagEdit = new QLineEdit(layout15);
        auctionTagEdit->setObjectName(QString::fromUtf8("auctionTagEdit"));
        auctionTagEdit->setMaximumSize(QSize(200, 32767));

        gridLayout2->addWidget(auctionTagEdit, 1, 9, 1, 1);

        textLabel3_2_2_2_2 = new QLabel(layout15);
        textLabel3_2_2_2_2->setObjectName(QString::fromUtf8("textLabel3_2_2_2_2"));
        textLabel3_2_2_2_2->setWordWrap(false);

        gridLayout2->addWidget(textLabel3_2_2_2_2, 0, 4, 1, 1);

        oldTagEdit = new QLineEdit(layout15);
        oldTagEdit->setObjectName(QString::fromUtf8("oldTagEdit"));
        oldTagEdit->setMaximumSize(QSize(100, 32767));

        gridLayout2->addWidget(oldTagEdit, 1, 3, 1, 1);

        chvEdit = new QLineEdit(layout15);
        chvEdit->setObjectName(QString::fromUtf8("chvEdit"));
        chvEdit->setMaximumSize(QSize(200, 32767));

        gridLayout2->addWidget(chvEdit, 1, 7, 1, 1);

        tbInjDate = new Q3DateEdit(layout15);
        tbInjDate->setObjectName(QString::fromUtf8("tbInjDate"));

        gridLayout2->addWidget(tbInjDate, 1, 8, 1, 1);

        layout7 = new QWidget(VetDialog);
        layout7->setObjectName(QString::fromUtf8("layout7"));
        layout7->setGeometry(QRect(328, 549, 671, 50));
        hboxLayout2 = new QHBoxLayout(layout7);
        hboxLayout2->setSpacing(6);
        hboxLayout2->setContentsMargins(11, 11, 11, 11);
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        hboxLayout2->setContentsMargins(0, 0, 0, 0);
        searchEdit = new QLineEdit(layout7);
        searchEdit->setObjectName(QString::fromUtf8("searchEdit"));

        hboxLayout2->addWidget(searchEdit);

        searchButton = new QPushButton(layout7);
        searchButton->setObjectName(QString::fromUtf8("searchButton"));
        searchButton->setAutoDefault(false);
        searchButton->setDefault(false);

        hboxLayout2->addWidget(searchButton);

        layout32 = new QWidget(VetDialog);
        layout32->setObjectName(QString::fromUtf8("layout32"));
        layout32->setGeometry(QRect(10, 226, 521, 110));
        hboxLayout3 = new QHBoxLayout(layout32);
        hboxLayout3->setSpacing(6);
        hboxLayout3->setContentsMargins(11, 11, 11, 11);
        hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
        hboxLayout3->setContentsMargins(0, 0, 0, 0);
        vboxLayout1 = new QVBoxLayout();
        vboxLayout1->setSpacing(6);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        textLabel3_2_2_2_4 = new QLabel(layout32);
        textLabel3_2_2_2_4->setObjectName(QString::fromUtf8("textLabel3_2_2_2_4"));
        textLabel3_2_2_2_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel3_2_2_2_4->setWordWrap(false);

        vboxLayout1->addWidget(textLabel3_2_2_2_4);

        textLabel3_2_2_2_4_2 = new QLabel(layout32);
        textLabel3_2_2_2_4_2->setObjectName(QString::fromUtf8("textLabel3_2_2_2_4_2"));
        textLabel3_2_2_2_4_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel3_2_2_2_4_2->setWordWrap(false);

        vboxLayout1->addWidget(textLabel3_2_2_2_4_2);

        textLabel3_2_2_2_4_2_2 = new QLabel(layout32);
        textLabel3_2_2_2_4_2_2->setObjectName(QString::fromUtf8("textLabel3_2_2_2_4_2_2"));
        textLabel3_2_2_2_4_2_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel3_2_2_2_4_2_2->setWordWrap(false);

        vboxLayout1->addWidget(textLabel3_2_2_2_4_2_2);


        hboxLayout3->addLayout(vboxLayout1);

        gridLayout3 = new QGridLayout();
        gridLayout3->setSpacing(6);
        gridLayout3->setObjectName(QString::fromUtf8("gridLayout3"));
        spacer1 = new QSpacerItem(150, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout3->addItem(spacer1, 0, 1, 1, 1);

        brucEdit = new QLineEdit(layout32);
        brucEdit->setObjectName(QString::fromUtf8("brucEdit"));
        brucEdit->setMinimumSize(QSize(1, 0));
        brucEdit->setMaximumSize(QSize(25, 32767));

        gridLayout3->addWidget(brucEdit, 0, 0, 1, 1);

        commentEdit = new QLineEdit(layout32);
        commentEdit->setObjectName(QString::fromUtf8("commentEdit"));

        gridLayout3->addWidget(commentEdit, 2, 0, 1, 2);

        pregDurationEdit = new QLineEdit(layout32);
        pregDurationEdit->setObjectName(QString::fromUtf8("pregDurationEdit"));

        gridLayout3->addWidget(pregDurationEdit, 1, 0, 1, 2);


        hboxLayout3->addLayout(gridLayout3);

        formGroupBox = new Q3GroupBox(VetDialog);
        formGroupBox->setObjectName(QString::fromUtf8("formGroupBox"));
        formGroupBox->setGeometry(QRect(11, 409, 521, 73));
        formGroupBox->setColumnLayout(0, Qt::Vertical);
        formGroupBox->layout()->setSpacing(6);
        formGroupBox->layout()->setContentsMargins(11, 11, 11, 11);
        gridLayout4 = new QGridLayout();
        QBoxLayout *boxlayout1 = qobject_cast<QBoxLayout *>(formGroupBox->layout());
        if (boxlayout1)
            boxlayout1->addLayout(gridLayout4);
        gridLayout4->setAlignment(Qt::AlignTop);
        gridLayout4->setObjectName(QString::fromUtf8("gridLayout4"));
        formComboBox = new QComboBox(formGroupBox);
        formComboBox->setObjectName(QString::fromUtf8("formComboBox"));

        gridLayout4->addWidget(formComboBox, 0, 0, 1, 1);

        formMetricsButton = new QPushButton(formGroupBox);
        formMetricsButton->setObjectName(QString::fromUtf8("formMetricsButton"));
        formMetricsButton->setEnabled(false);
        formMetricsButton->setAutoDefault(false);
        formMetricsButton->setDefault(false);

        gridLayout4->addWidget(formMetricsButton, 0, 1, 1, 1);

        deletedCheckBox = new QCheckBox(VetDialog);
        deletedCheckBox->setObjectName(QString::fromUtf8("deletedCheckBox"));
        deletedCheckBox->setEnabled(true);
        deletedCheckBox->setGeometry(QRect(200, 360, 330, 28));
        layout11 = new QWidget(VetDialog);
        layout11->setObjectName(QString::fromUtf8("layout11"));
        layout11->setGeometry(QRect(10, 360, 129, 30));
        gridLayout5 = new QGridLayout(layout11);
        gridLayout5->setSpacing(6);
        gridLayout5->setContentsMargins(11, 11, 11, 11);
        gridLayout5->setObjectName(QString::fromUtf8("gridLayout5"));
        gridLayout5->setContentsMargins(0, 0, 0, 0);
        textLabel1_3 = new QLabel(layout11);
        textLabel1_3->setObjectName(QString::fromUtf8("textLabel1_3"));
        textLabel1_3->setFrameShape(QFrame::NoFrame);
        textLabel1_3->setFrameShadow(QFrame::Plain);
        textLabel1_3->setWordWrap(false);

        gridLayout5->addWidget(textLabel1_3, 0, 0, 1, 1);

        recordNumberDisplay = new QLabel(layout11);
        recordNumberDisplay->setObjectName(QString::fromUtf8("recordNumberDisplay"));
        recordNumberDisplay->setMinimumSize(QSize(40, 0));
        recordNumberDisplay->setTextFormat(Qt::AutoText);
        recordNumberDisplay->setWordWrap(false);

        gridLayout5->addWidget(recordNumberDisplay, 0, 1, 1, 1);

        prevButton = new QPushButton(VetDialog);
        prevButton->setObjectName(QString::fromUtf8("prevButton"));
        prevButton->setGeometry(QRect(691, 630, 149, 32));
        prevButton->setAutoDefault(false);
        prevButton->setDefault(false);
        indexGroupBox = new Q3GroupBox(VetDialog);
        indexGroupBox->setObjectName(QString::fromUtf8("indexGroupBox"));
        indexGroupBox->setGeometry(QRect(427, 612, 256, 60));
        indexCombo = new QComboBox(indexGroupBox);
        indexCombo->setObjectName(QString::fromUtf8("indexCombo"));
        indexCombo->setGeometry(QRect(10, 20, 234, 30));
        browseButton = new QPushButton(VetDialog);
        browseButton->setObjectName(QString::fromUtf8("browseButton"));
        browseButton->setGeometry(QRect(8, 630, 206, 32));
        browseButton->setAutoDefault(false);
        browseButton->setDefault(false);
        addRecordButton = new QPushButton(VetDialog);
        addRecordButton->setObjectName(QString::fromUtf8("addRecordButton"));
        addRecordButton->setGeometry(QRect(220, 630, 190, 32));
        addRecordButton->setAutoDefault(false);
        addRecordButton->setDefault(false);
        QWidget::setTabOrder(testDateEdit, breedEdit);
        QWidget::setTabOrder(breedEdit, sexEdit);
        QWidget::setTabOrder(sexEdit, oldTagEdit);
        QWidget::setTabOrder(oldTagEdit, ageSpinBox);
        QWidget::setTabOrder(ageSpinBox, brucTagEdit);
        QWidget::setTabOrder(brucTagEdit, rfid);
        QWidget::setTabOrder(rfid, chvEdit);
        QWidget::setTabOrder(chvEdit, tbInjDate);
        QWidget::setTabOrder(tbInjDate, auctionTagEdit);
        QWidget::setTabOrder(auctionTagEdit, brucEdit);
        QWidget::setTabOrder(brucEdit, pregDurationEdit);
        QWidget::setTabOrder(pregDurationEdit, commentEdit);
        QWidget::setTabOrder(commentEdit, deletedCheckBox);
        QWidget::setTabOrder(deletedCheckBox, formComboBox);
        QWidget::setTabOrder(formComboBox, formMetricsButton);
        QWidget::setTabOrder(formMetricsButton, printerComboBox);
        QWidget::setTabOrder(printerComboBox, vetEditButton);
        QWidget::setTabOrder(vetEditButton, searchEdit);
        QWidget::setTabOrder(searchEdit, searchButton);
        QWidget::setTabOrder(searchButton, browseButton);
        QWidget::setTabOrder(browseButton, addRecordButton);
        QWidget::setTabOrder(addRecordButton, indexCombo);
        QWidget::setTabOrder(indexCombo, prevButton);
        QWidget::setTabOrder(prevButton, nextButton);

        retranslateUi(VetDialog);

        QMetaObject::connectSlotsByName(VetDialog);
    } // setupUi

    void retranslateUi(QDialog *VetDialog)
    {
        VetDialog->setWindowTitle(QApplication::translate("VetDialog", "Enter Vet Data", 0, QApplication::UnicodeUTF8));
        textLabel1->setText(QApplication::translate("VetDialog", "Seller", 0, QApplication::UnicodeUTF8));
        textLabel2->setText(QApplication::translate("VetDialog", "Tag Count:", 0, QApplication::UnicodeUTF8));
        tagCountDisplay->setText(QApplication::translate("VetDialog", "0", 0, QApplication::UnicodeUTF8));
        consignorDisplay->setText(QApplication::translate("VetDialog", "Consignor Name\n"
"Consignor Address Line 1\n"
"Consignor Address Line 2\n"
"Consignor City, State Zip", 0, QApplication::UnicodeUTF8));
        textLabel1_2->setText(QApplication::translate("VetDialog", "Buyer", 0, QApplication::UnicodeUTF8));
        consigneeDisplay->setText(QApplication::translate("VetDialog", "Consignee Name\n"
"Consignee Address Line 1\n"
"Consignee Address Line 2\n"
"Consignee City, State Zip", 0, QApplication::UnicodeUTF8));
        vetEditButton->setText(QApplication::translate("VetDialog", "Edit Vet Data", 0, QApplication::UnicodeUTF8));
        printerGroupBox->setTitle(QApplication::translate("VetDialog", "Printer", 0, QApplication::UnicodeUTF8));
        nextButton->setText(QApplication::translate("VetDialog", "&Next >", 0, QApplication::UnicodeUTF8));
        textLabel3_2_2_2->setText(QApplication::translate("VetDialog", "Old Tag", 0, QApplication::UnicodeUTF8));
        breedEdit->setInputMask(QApplication::translate("VetDialog", "NN; ", 0, QApplication::UnicodeUTF8));
        breedEdit->setText(QString());
        textLabel3_2_2->setText(QApplication::translate("VetDialog", "Sex", 0, QApplication::UnicodeUTF8));
        textLabel1_5->setText(QApplication::translate("VetDialog", "TB Inj Date", 0, QApplication::UnicodeUTF8));
        textLabel3_2_2_2_3_2->setText(QApplication::translate("VetDialog", "CHV", 0, QApplication::UnicodeUTF8));
        textLabel3_2->setText(QApplication::translate("VetDialog", "Breed", 0, QApplication::UnicodeUTF8));
        textLabel3->setText(QApplication::translate("VetDialog", "Test Date", 0, QApplication::UnicodeUTF8));
        brucTagEdit->setInputMask(QApplication::translate("VetDialog", "99AAA9999; ", 0, QApplication::UnicodeUTF8));
        brucTagEdit->setText(QString());
        sexEdit->setInputMask(QApplication::translate("VetDialog", "A; ", 0, QApplication::UnicodeUTF8));
        sexEdit->setText(QString());
        textLabel3_2_2_2_3_2_2->setText(QApplication::translate("VetDialog", "Auction Tag", 0, QApplication::UnicodeUTF8));
        textLabel1_4->setText(QApplication::translate("VetDialog", "RFID", 0, QApplication::UnicodeUTF8));
        textLabel3_2_2_2_3->setText(QApplication::translate("VetDialog", "Bruc Tag", 0, QApplication::UnicodeUTF8));
        textLabel3_2_2_2_2->setText(QApplication::translate("VetDialog", "Age", 0, QApplication::UnicodeUTF8));
        oldTagEdit->setInputMask(QString());
        oldTagEdit->setText(QString());
        chvEdit->setText(QString());
        searchButton->setText(QApplication::translate("VetDialog", "Search", 0, QApplication::UnicodeUTF8));
        textLabel3_2_2_2_4->setText(QApplication::translate("VetDialog", "Bruc", 0, QApplication::UnicodeUTF8));
        textLabel3_2_2_2_4_2->setText(QApplication::translate("VetDialog", "Mo. Preg", 0, QApplication::UnicodeUTF8));
        textLabel3_2_2_2_4_2_2->setText(QApplication::translate("VetDialog", "Comments", 0, QApplication::UnicodeUTF8));
        brucEdit->setInputMask(QApplication::translate("VetDialog", "N; ", 0, QApplication::UnicodeUTF8));
        brucEdit->setText(QString());
        commentEdit->setText(QString());
        pregDurationEdit->setText(QString());
        formGroupBox->setTitle(QApplication::translate("VetDialog", "Forms", 0, QApplication::UnicodeUTF8));
        formComboBox->clear();
        formComboBox->insertItems(0, QStringList()
         << QApplication::translate("VetDialog", "<Select A Form>", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VetDialog", "Certificate(SD)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VetDialog", "Certificate(MN)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VetDialog", "Brucellosis", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VetDialog", "Tuberculosis", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VetDialog", "Allflex Report", 0, QApplication::UnicodeUTF8)
        );
        formMetricsButton->setText(QApplication::translate("VetDialog", "Metrics", 0, QApplication::UnicodeUTF8));
        deletedCheckBox->setText(QApplication::translate("VetDialog", "Mar&k Deleted", 0, QApplication::UnicodeUTF8));
        deletedCheckBox->setShortcut(QApplication::translate("VetDialog", "Alt+K", 0, QApplication::UnicodeUTF8));
        textLabel1_3->setText(QApplication::translate("VetDialog", "Record #", 0, QApplication::UnicodeUTF8));
        recordNumberDisplay->setText(QApplication::translate("VetDialog", "0", 0, QApplication::UnicodeUTF8));
        prevButton->setText(QApplication::translate("VetDialog", "< Prev", 0, QApplication::UnicodeUTF8));
        indexGroupBox->setTitle(QApplication::translate("VetDialog", "&Index", 0, QApplication::UnicodeUTF8));
        indexCombo->clear();
        indexCombo->insertItems(0, QStringList()
         << QApplication::translate("VetDialog", "Tag", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VetDialog", "Owner", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VetDialog", "Bruc Tag", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VetDialog", "Age", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("VetDialog", "Breed", 0, QApplication::UnicodeUTF8)
        );
        browseButton->setText(QApplication::translate("VetDialog", "&Browse", 0, QApplication::UnicodeUTF8));
        browseButton->setShortcut(QApplication::translate("VetDialog", "Alt+B", 0, QApplication::UnicodeUTF8));
        addRecordButton->setText(QApplication::translate("VetDialog", "&Add", 0, QApplication::UnicodeUTF8));
        addRecordButton->setShortcut(QApplication::translate("VetDialog", "Alt+A", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class VetDialog: public Ui_VetDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VETDIALOG_H
