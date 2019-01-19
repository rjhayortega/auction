/********************************************************************************
** Form generated from reading UI file 'truckingdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRUCKINGDIALOG_H
#define UI_TRUCKINGDIALOG_H

#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3ListBox>
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
#include <vector>
#include "dao/truckingrecorddao.h"
#include "types/invoice.h"

QT_BEGIN_NAMESPACE

class Ui_TruckingDialog
{
public:
    QLabel *textLabel1;
    Q3ListBox *truckerListBox;
    QPushButton *savetruckers;
    QPushButton *truckingCancel;
    QPushButton *truckingDone;
    QPushButton *truckingDel;
    QLineEdit *Qprice;
    QLabel *textLabel1_2;
    QLabel *textLabel2_2;
    QLineEdit *Qqty;
    QLineEdit *Qextend;
    QLineEdit *Qtrucker;
    QLabel *textLabel2;
    QLabel *qtyLabel;
    QComboBox *Qunit;

    void setupUi(QDialog *TruckingDialog)
    {
        if (TruckingDialog->objectName().isEmpty())
            TruckingDialog->setObjectName(QString::fromUtf8("TruckingDialog"));
        TruckingDialog->setWindowModality(Qt::ApplicationModal);
        TruckingDialog->resize(590, 272);
        QFont font;
        font.setPointSize(13);
        TruckingDialog->setFont(font);
        textLabel1 = new QLabel(TruckingDialog);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
        textLabel1->setGeometry(QRect(10, 20, 101, 30));
        textLabel1->setFrameShape(QFrame::NoFrame);
        textLabel1->setFrameShadow(QFrame::Plain);
        textLabel1->setWordWrap(false);
        truckerListBox = new Q3ListBox(TruckingDialog);
        truckerListBox->setObjectName(QString::fromUtf8("truckerListBox"));
        truckerListBox->setGeometry(QRect(10, 90, 570, 127));
        savetruckers = new QPushButton(TruckingDialog);
        savetruckers->setObjectName(QString::fromUtf8("savetruckers"));
        savetruckers->setGeometry(QRect(260, 230, 100, 30));
        savetruckers->setAutoDefault(true);
        truckingCancel = new QPushButton(TruckingDialog);
        truckingCancel->setObjectName(QString::fromUtf8("truckingCancel"));
        truckingCancel->setGeometry(QRect(370, 230, 100, 30));
        truckingCancel->setAutoDefault(false);
        truckingDone = new QPushButton(TruckingDialog);
        truckingDone->setObjectName(QString::fromUtf8("truckingDone"));
        truckingDone->setGeometry(QRect(480, 230, 100, 30));
        truckingDone->setAutoDefault(false);
        truckingDel = new QPushButton(TruckingDialog);
        truckingDel->setObjectName(QString::fromUtf8("truckingDel"));
        truckingDel->setGeometry(QRect(140, 230, 100, 30));
        truckingDel->setAutoDefault(false);
        Qprice = new QLineEdit(TruckingDialog);
        Qprice->setObjectName(QString::fromUtf8("Qprice"));
        Qprice->setGeometry(QRect(300, 50, 80, 30));
        textLabel1_2 = new QLabel(TruckingDialog);
        textLabel1_2->setObjectName(QString::fromUtf8("textLabel1_2"));
        textLabel1_2->setGeometry(QRect(190, 20, 100, 30));
        textLabel1_2->setWordWrap(false);
        textLabel2_2 = new QLabel(TruckingDialog);
        textLabel2_2->setObjectName(QString::fromUtf8("textLabel2_2"));
        textLabel2_2->setGeometry(QRect(480, 20, 101, 30));
        textLabel2_2->setWordWrap(false);
        Qqty = new QLineEdit(TruckingDialog);
        Qqty->setObjectName(QString::fromUtf8("Qqty"));
        Qqty->setEnabled(true);
        Qqty->setGeometry(QRect(390, 50, 80, 30));
        Qextend = new QLineEdit(TruckingDialog);
        Qextend->setObjectName(QString::fromUtf8("Qextend"));
        Qextend->setGeometry(QRect(480, 50, 101, 28));
        Qextend->setFocusPolicy(Qt::NoFocus);
        Qtrucker = new QLineEdit(TruckingDialog);
        Qtrucker->setObjectName(QString::fromUtf8("Qtrucker"));
        Qtrucker->setGeometry(QRect(10, 50, 170, 30));
        textLabel2 = new QLabel(TruckingDialog);
        textLabel2->setObjectName(QString::fromUtf8("textLabel2"));
        textLabel2->setGeometry(QRect(300, 20, 80, 30));
        textLabel2->setWordWrap(false);
        qtyLabel = new QLabel(TruckingDialog);
        qtyLabel->setObjectName(QString::fromUtf8("qtyLabel"));
        qtyLabel->setEnabled(true);
        qtyLabel->setGeometry(QRect(390, 20, 80, 30));
        qtyLabel->setAlignment(Qt::AlignVCenter);
        qtyLabel->setWordWrap(false);
        Qunit = new QComboBox(TruckingDialog);
        Qunit->setObjectName(QString::fromUtf8("Qunit"));
        Qunit->setGeometry(QRect(190, 50, 100, 30));
        QWidget::setTabOrder(Qtrucker, Qunit);
        QWidget::setTabOrder(Qunit, Qprice);
        QWidget::setTabOrder(Qprice, Qqty);
        QWidget::setTabOrder(Qqty, truckerListBox);
        QWidget::setTabOrder(truckerListBox, savetruckers);
        QWidget::setTabOrder(savetruckers, truckingCancel);
        QWidget::setTabOrder(truckingCancel, truckingDel);
        QWidget::setTabOrder(truckingDel, Qextend);
        QWidget::setTabOrder(Qextend, truckingDone);

        retranslateUi(TruckingDialog);

        QMetaObject::connectSlotsByName(TruckingDialog);
    } // setupUi

    void retranslateUi(QDialog *TruckingDialog)
    {
        TruckingDialog->setWindowTitle(QApplication::translate("TruckingDialog", "Trucking", 0, QApplication::UnicodeUTF8));
        textLabel1->setText(QApplication::translate("TruckingDialog", "Trucker", 0, QApplication::UnicodeUTF8));
        savetruckers->setText(QApplication::translate("TruckingDialog", "Save", 0, QApplication::UnicodeUTF8));
        truckingCancel->setText(QApplication::translate("TruckingDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        truckingDone->setText(QApplication::translate("TruckingDialog", "Ok", 0, QApplication::UnicodeUTF8));
        truckingDel->setText(QApplication::translate("TruckingDialog", "Delete", 0, QApplication::UnicodeUTF8));
        textLabel1_2->setText(QApplication::translate("TruckingDialog", "Per", 0, QApplication::UnicodeUTF8));
        textLabel2_2->setText(QApplication::translate("TruckingDialog", "Extended", 0, QApplication::UnicodeUTF8));
        textLabel2->setText(QApplication::translate("TruckingDialog", "Price", 0, QApplication::UnicodeUTF8));
        qtyLabel->setText(QApplication::translate("TruckingDialog", "Qty", 0, QApplication::UnicodeUTF8));
        Qunit->clear();
        Qunit->insertItems(0, QStringList()
         << QApplication::translate("TruckingDialog", "Load", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("TruckingDialog", "CWT", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("TruckingDialog", "Head", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("TruckingDialog", "Mile", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("TruckingDialog", "Other", 0, QApplication::UnicodeUTF8)
        );
    } // retranslateUi

};

namespace Ui {
    class TruckingDialog: public Ui_TruckingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRUCKINGDIALOG_H
