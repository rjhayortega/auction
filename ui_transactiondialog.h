/********************************************************************************
** Form generated from reading UI file 'transactiondialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRANSACTIONDIALOG_H
#define UI_TRANSACTIONDIALOG_H

#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3ListBox>
#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QSplitter>
#include <QtGui/QWidget>
#include "dao/printerdao.h"
#include "dao/salemanager.h"
#include "dao/setupdao.h"
#include "types/transaction.h"

QT_BEGIN_NAMESPACE

class Ui_TransactionDialog
{
public:
    QGridLayout *gridLayout_2;
    QLabel *textLabel1;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *tranEditBuyer;
    QLabel *tranEditBPen;
    QLabel *transeditAvgWt;
    QLineEdit *transeditBuyer;
    QLabel *tranEditHead;
    QLineEdit *transeditHead;
    QLabel *tranEditWeight;
    QLineEdit *transeditBPen;
    QLineEdit *transeditWeight;
    QLabel *averageLabel;
    QHBoxLayout *horizontalLayout;
    QPushButton *videoPushButton;
    QPushButton *printTicketButton;
    QPushButton *cancelTransaction;
    QPushButton *buttSaveTransaction;
    QLabel *tranEditDesc;
    QLineEdit *transeditDesc;
    QLabel *transedTextDesc;
    QLabel *tranEditBid;
    QLineEdit *transeditBid;
    QLabel *tranEditMode;
    QSpinBox *modeSpinBox;
    QComboBox *transeditMode;
    QLabel *tranEditSeller;
    QLabel *transeditNumber;
    QPushButton *deleteTagButton;
    QLabel *averageLabel_2;
    QLabel *manLabel;
    QLineEdit *tagEdit;
    Q3ListBox *tagListBox;
    QLineEdit *transeditSPen;
    QLabel *tranEditSPen;
    QLabel *tranEditBPen_2;
    QLineEdit *transeditComment;
    QLineEdit *transeditSeller;
    QLabel *editNumberLabel;
    QWidget *videoWidget;

    void setupUi(QDialog *TransactionDialog)
    {
        if (TransactionDialog->objectName().isEmpty())
            TransactionDialog->setObjectName(QString::fromUtf8("TransactionDialog"));
        TransactionDialog->setWindowModality(Qt::ApplicationModal);
        TransactionDialog->setEnabled(true);
        TransactionDialog->resize(812, 529);
        QFont font;
        font.setPointSize(13);
        TransactionDialog->setFont(font);
        gridLayout_2 = new QGridLayout(TransactionDialog);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        textLabel1 = new QLabel(TransactionDialog);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
        textLabel1->setFrameShape(QFrame::NoFrame);
        textLabel1->setFrameShadow(QFrame::Plain);
        textLabel1->setAlignment(Qt::AlignCenter);
        textLabel1->setWordWrap(true);

        gridLayout_2->addWidget(textLabel1, 0, 0, 1, 1);

        splitter = new QSplitter(TransactionDialog);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        splitter->setChildrenCollapsible(true);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        tranEditBuyer = new QLabel(layoutWidget);
        tranEditBuyer->setObjectName(QString::fromUtf8("tranEditBuyer"));
        tranEditBuyer->setFrameShape(QFrame::NoFrame);
        tranEditBuyer->setFrameShadow(QFrame::Plain);
        tranEditBuyer->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        tranEditBuyer->setWordWrap(false);

        gridLayout->addWidget(tranEditBuyer, 4, 0, 1, 1);

        tranEditBPen = new QLabel(layoutWidget);
        tranEditBPen->setObjectName(QString::fromUtf8("tranEditBPen"));
        tranEditBPen->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        tranEditBPen->setWordWrap(false);

        gridLayout->addWidget(tranEditBPen, 11, 0, 1, 1);

        transeditAvgWt = new QLabel(layoutWidget);
        transeditAvgWt->setObjectName(QString::fromUtf8("transeditAvgWt"));
        transeditAvgWt->setWordWrap(false);

        gridLayout->addWidget(transeditAvgWt, 6, 4, 1, 1);

        transeditBuyer = new QLineEdit(layoutWidget);
        transeditBuyer->setObjectName(QString::fromUtf8("transeditBuyer"));

        gridLayout->addWidget(transeditBuyer, 4, 1, 1, 2);

        tranEditHead = new QLabel(layoutWidget);
        tranEditHead->setObjectName(QString::fromUtf8("tranEditHead"));
        tranEditHead->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        tranEditHead->setWordWrap(false);

        gridLayout->addWidget(tranEditHead, 5, 0, 1, 1);

        transeditHead = new QLineEdit(layoutWidget);
        transeditHead->setObjectName(QString::fromUtf8("transeditHead"));

        gridLayout->addWidget(transeditHead, 5, 1, 1, 1);

        tranEditWeight = new QLabel(layoutWidget);
        tranEditWeight->setObjectName(QString::fromUtf8("tranEditWeight"));
        tranEditWeight->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        tranEditWeight->setWordWrap(false);

        gridLayout->addWidget(tranEditWeight, 6, 0, 1, 1);

        transeditBPen = new QLineEdit(layoutWidget);
        transeditBPen->setObjectName(QString::fromUtf8("transeditBPen"));

        gridLayout->addWidget(transeditBPen, 11, 1, 1, 2);

        transeditWeight = new QLineEdit(layoutWidget);
        transeditWeight->setObjectName(QString::fromUtf8("transeditWeight"));

        gridLayout->addWidget(transeditWeight, 6, 1, 1, 2);

        averageLabel = new QLabel(layoutWidget);
        averageLabel->setObjectName(QString::fromUtf8("averageLabel"));
        averageLabel->setWordWrap(false);

        gridLayout->addWidget(averageLabel, 6, 3, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        videoPushButton = new QPushButton(layoutWidget);
        videoPushButton->setObjectName(QString::fromUtf8("videoPushButton"));
        videoPushButton->setAutoDefault(false);

        horizontalLayout->addWidget(videoPushButton);

        printTicketButton = new QPushButton(layoutWidget);
        printTicketButton->setObjectName(QString::fromUtf8("printTicketButton"));
        printTicketButton->setAutoDefault(false);

        horizontalLayout->addWidget(printTicketButton);

        cancelTransaction = new QPushButton(layoutWidget);
        cancelTransaction->setObjectName(QString::fromUtf8("cancelTransaction"));
        cancelTransaction->setAutoDefault(false);

        horizontalLayout->addWidget(cancelTransaction);

        buttSaveTransaction = new QPushButton(layoutWidget);
        buttSaveTransaction->setObjectName(QString::fromUtf8("buttSaveTransaction"));
        buttSaveTransaction->setAutoDefault(false);

        horizontalLayout->addWidget(buttSaveTransaction);


        gridLayout->addLayout(horizontalLayout, 13, 2, 1, 4);

        tranEditDesc = new QLabel(layoutWidget);
        tranEditDesc->setObjectName(QString::fromUtf8("tranEditDesc"));
        tranEditDesc->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        tranEditDesc->setWordWrap(false);

        gridLayout->addWidget(tranEditDesc, 7, 0, 1, 1);

        transeditDesc = new QLineEdit(layoutWidget);
        transeditDesc->setObjectName(QString::fromUtf8("transeditDesc"));
        transeditDesc->setMaxLength(32767);
        transeditDesc->setAlignment(Qt::AlignRight);
        transeditDesc->setReadOnly(false);

        gridLayout->addWidget(transeditDesc, 7, 1, 1, 2);

        transedTextDesc = new QLabel(layoutWidget);
        transedTextDesc->setObjectName(QString::fromUtf8("transedTextDesc"));
        transedTextDesc->setWordWrap(false);

        gridLayout->addWidget(transedTextDesc, 7, 3, 1, 2);

        tranEditBid = new QLabel(layoutWidget);
        tranEditBid->setObjectName(QString::fromUtf8("tranEditBid"));
        tranEditBid->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        tranEditBid->setWordWrap(false);

        gridLayout->addWidget(tranEditBid, 8, 0, 1, 1);

        transeditBid = new QLineEdit(layoutWidget);
        transeditBid->setObjectName(QString::fromUtf8("transeditBid"));
        transeditBid->setAlignment(Qt::AlignRight);

        gridLayout->addWidget(transeditBid, 8, 1, 1, 2);

        tranEditMode = new QLabel(layoutWidget);
        tranEditMode->setObjectName(QString::fromUtf8("tranEditMode"));
        tranEditMode->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        tranEditMode->setWordWrap(false);

        gridLayout->addWidget(tranEditMode, 9, 0, 1, 1);

        modeSpinBox = new QSpinBox(layoutWidget);
        modeSpinBox->setObjectName(QString::fromUtf8("modeSpinBox"));
        modeSpinBox->setMaximum(8);

        gridLayout->addWidget(modeSpinBox, 9, 1, 1, 2);

        transeditMode = new QComboBox(layoutWidget);
        transeditMode->setObjectName(QString::fromUtf8("transeditMode"));
        transeditMode->setMinimumSize(QSize(180, 0));
        transeditMode->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        gridLayout->addWidget(transeditMode, 9, 3, 1, 2);

        tranEditSeller = new QLabel(layoutWidget);
        tranEditSeller->setObjectName(QString::fromUtf8("tranEditSeller"));
        tranEditSeller->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        tranEditSeller->setWordWrap(false);

        gridLayout->addWidget(tranEditSeller, 2, 0, 2, 1);

        transeditNumber = new QLabel(layoutWidget);
        transeditNumber->setObjectName(QString::fromUtf8("transeditNumber"));
        transeditNumber->setWordWrap(false);

        gridLayout->addWidget(transeditNumber, 0, 1, 2, 2);

        deleteTagButton = new QPushButton(layoutWidget);
        deleteTagButton->setObjectName(QString::fromUtf8("deleteTagButton"));
        deleteTagButton->setAutoDefault(false);

        gridLayout->addWidget(deleteTagButton, 10, 5, 1, 1);

        averageLabel_2 = new QLabel(layoutWidget);
        averageLabel_2->setObjectName(QString::fromUtf8("averageLabel_2"));
        averageLabel_2->setWordWrap(false);

        gridLayout->addWidget(averageLabel_2, 0, 5, 1, 1);

        manLabel = new QLabel(layoutWidget);
        manLabel->setObjectName(QString::fromUtf8("manLabel"));
        manLabel->setWordWrap(false);

        gridLayout->addWidget(manLabel, 0, 3, 2, 2);

        tagEdit = new QLineEdit(layoutWidget);
        tagEdit->setObjectName(QString::fromUtf8("tagEdit"));

        gridLayout->addWidget(tagEdit, 1, 5, 2, 1);

        tagListBox = new Q3ListBox(layoutWidget);
        tagListBox->setObjectName(QString::fromUtf8("tagListBox"));
        tagListBox->setSelectionMode(Q3ListBox::Multi);

        gridLayout->addWidget(tagListBox, 3, 5, 7, 1);

        transeditSPen = new QLineEdit(layoutWidget);
        transeditSPen->setObjectName(QString::fromUtf8("transeditSPen"));

        gridLayout->addWidget(transeditSPen, 10, 1, 1, 2);

        tranEditSPen = new QLabel(layoutWidget);
        tranEditSPen->setObjectName(QString::fromUtf8("tranEditSPen"));
        tranEditSPen->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        tranEditSPen->setWordWrap(false);

        gridLayout->addWidget(tranEditSPen, 10, 0, 1, 1);

        tranEditBPen_2 = new QLabel(layoutWidget);
        tranEditBPen_2->setObjectName(QString::fromUtf8("tranEditBPen_2"));
        tranEditBPen_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        tranEditBPen_2->setWordWrap(false);

        gridLayout->addWidget(tranEditBPen_2, 12, 0, 1, 1);

        transeditComment = new QLineEdit(layoutWidget);
        transeditComment->setObjectName(QString::fromUtf8("transeditComment"));

        gridLayout->addWidget(transeditComment, 12, 1, 1, 4);

        transeditSeller = new QLineEdit(layoutWidget);
        transeditSeller->setObjectName(QString::fromUtf8("transeditSeller"));
        transeditSeller->setReadOnly(false);

        gridLayout->addWidget(transeditSeller, 2, 1, 2, 2);

        editNumberLabel = new QLabel(layoutWidget);
        editNumberLabel->setObjectName(QString::fromUtf8("editNumberLabel"));
        editNumberLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        editNumberLabel->setWordWrap(false);

        gridLayout->addWidget(editNumberLabel, 0, 0, 2, 1);

        gridLayout->setRowStretch(0, 1);
        splitter->addWidget(layoutWidget);
        videoWidget = new QWidget(splitter);
        videoWidget->setObjectName(QString::fromUtf8("videoWidget"));
        splitter->addWidget(videoWidget);

        gridLayout_2->addWidget(splitter, 1, 0, 1, 1);

        QWidget::setTabOrder(transeditSeller, transeditBuyer);
        QWidget::setTabOrder(transeditBuyer, transeditHead);
        QWidget::setTabOrder(transeditHead, transeditWeight);
        QWidget::setTabOrder(transeditWeight, transeditDesc);
        QWidget::setTabOrder(transeditDesc, transeditBid);
        QWidget::setTabOrder(transeditBid, modeSpinBox);
        QWidget::setTabOrder(modeSpinBox, transeditSPen);
        QWidget::setTabOrder(transeditSPen, transeditBPen);
        QWidget::setTabOrder(transeditBPen, transeditComment);
        QWidget::setTabOrder(transeditComment, buttSaveTransaction);
        QWidget::setTabOrder(buttSaveTransaction, cancelTransaction);
        QWidget::setTabOrder(cancelTransaction, transeditMode);

        retranslateUi(TransactionDialog);

        QMetaObject::connectSlotsByName(TransactionDialog);
    } // setupUi

    void retranslateUi(QDialog *TransactionDialog)
    {
        TransactionDialog->setWindowTitle(QApplication::translate("TransactionDialog", "Transaction Edit", 0, QApplication::UnicodeUTF8));
        textLabel1->setText(QApplication::translate("TransactionDialog", "<font face=\"Arial\"><font size=\"+3\"><font face=\"Arial\">Transaction Edit</font></font></font>", 0, QApplication::UnicodeUTF8));
        tranEditBuyer->setText(QApplication::translate("TransactionDialog", "Buyer", 0, QApplication::UnicodeUTF8));
        tranEditBPen->setText(QApplication::translate("TransactionDialog", "Buyer Pen", 0, QApplication::UnicodeUTF8));
        transeditAvgWt->setText(QString());
        tranEditHead->setText(QApplication::translate("TransactionDialog", "Head", 0, QApplication::UnicodeUTF8));
        tranEditWeight->setText(QApplication::translate("TransactionDialog", "Weight", 0, QApplication::UnicodeUTF8));
        averageLabel->setText(QApplication::translate("TransactionDialog", "Avg.", 0, QApplication::UnicodeUTF8));
        videoPushButton->setText(QApplication::translate("TransactionDialog", "Video", 0, QApplication::UnicodeUTF8));
        videoPushButton->setShortcut(QString());
        printTicketButton->setText(QApplication::translate("TransactionDialog", "Print", 0, QApplication::UnicodeUTF8));
        printTicketButton->setShortcut(QString());
        cancelTransaction->setText(QApplication::translate("TransactionDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        cancelTransaction->setShortcut(QString());
        buttSaveTransaction->setText(QApplication::translate("TransactionDialog", "Save", 0, QApplication::UnicodeUTF8));
        buttSaveTransaction->setShortcut(QString());
        tranEditDesc->setText(QApplication::translate("TransactionDialog", "Description", 0, QApplication::UnicodeUTF8));
        transeditDesc->setText(QString());
        transedTextDesc->setText(QApplication::translate("TransactionDialog", "Description Text", 0, QApplication::UnicodeUTF8));
        tranEditBid->setText(QApplication::translate("TransactionDialog", "Bid", 0, QApplication::UnicodeUTF8));
        tranEditMode->setText(QApplication::translate("TransactionDialog", "Mode", 0, QApplication::UnicodeUTF8));
        transeditMode->clear();
        transeditMode->insertItems(0, QStringList()
         << QApplication::translate("TransactionDialog", "Invalid", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("TransactionDialog", "Sale/CWT", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("TransactionDialog", "Sale/Head", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("TransactionDialog", "NoSale/CWT", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("TransactionDialog", "NoSale/Head", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("TransactionDialog", "Resale/CWT", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("TransactionDialog", "Resale/Head", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("TransactionDialog", "Buyer Swap/CWT", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("TransactionDialog", "Buyer Swap/Head", 0, QApplication::UnicodeUTF8)
        );
        tranEditSeller->setText(QApplication::translate("TransactionDialog", "Seller", 0, QApplication::UnicodeUTF8));
        transeditNumber->setText(QString());
        deleteTagButton->setText(QApplication::translate("TransactionDialog", "Delete Tags", 0, QApplication::UnicodeUTF8));
        averageLabel_2->setText(QApplication::translate("TransactionDialog", "Tags", 0, QApplication::UnicodeUTF8));
        manLabel->setText(QString());
        tranEditSPen->setText(QApplication::translate("TransactionDialog", "Seller Pen", 0, QApplication::UnicodeUTF8));
        tranEditBPen_2->setText(QApplication::translate("TransactionDialog", "Comment", 0, QApplication::UnicodeUTF8));
        editNumberLabel->setText(QApplication::translate("TransactionDialog", "Number", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TransactionDialog: public Ui_TransactionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRANSACTIONDIALOG_H
