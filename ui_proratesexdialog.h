/********************************************************************************
** Form generated from reading UI file 'proratesexdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRORATESEXDIALOG_H
#define UI_PRORATESEXDIALOG_H

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
#include "Qt3Support/Q3Table"
#include "types/checkfactory.h"
#include "types/prorate.h"

QT_BEGIN_NAMESPACE

class Ui_ProrateSexDialog
{
public:
    Q3Table *sexTable;
    QPushButton *buttonOk;

    void setupUi(QDialog *ProrateSexDialog)
    {
        if (ProrateSexDialog->objectName().isEmpty())
            ProrateSexDialog->setObjectName(QString::fromUtf8("ProrateSexDialog"));
        ProrateSexDialog->setWindowModality(Qt::ApplicationModal);
        ProrateSexDialog->resize(520, 407);
        QFont font;
        font.setPointSize(13);
        ProrateSexDialog->setFont(font);
        sexTable = new Q3Table(ProrateSexDialog);
        sexTable->setObjectName(QString::fromUtf8("sexTable"));
        sexTable->setGeometry(QRect(10, 20, 490, 330));
        sexTable->setNumRows(0);
        sexTable->setNumCols(4);
        sexTable->setShowGrid(true);
        sexTable->setSelectionMode(Q3Table::Single);
        buttonOk = new QPushButton(ProrateSexDialog);
        buttonOk->setObjectName(QString::fromUtf8("buttonOk"));
        buttonOk->setGeometry(QRect(400, 360, 100, 30));

        retranslateUi(ProrateSexDialog);

        QMetaObject::connectSlotsByName(ProrateSexDialog);
    } // setupUi

    void retranslateUi(QDialog *ProrateSexDialog)
    {
        ProrateSexDialog->setWindowTitle(QApplication::translate("ProrateSexDialog", "Choose types and amounts", 0, QApplication::UnicodeUTF8));
        sexTable->horizontalHeader()->setLabel(0, QApplication::translate("ProrateSexDialog", "X", 0, QApplication::UnicodeUTF8));
        sexTable->horizontalHeader()->setLabel(1, QApplication::translate("ProrateSexDialog", "Sex", 0, QApplication::UnicodeUTF8));
        sexTable->horizontalHeader()->setLabel(2, QApplication::translate("ProrateSexDialog", "Desired Head", 0, QApplication::UnicodeUTF8));
        sexTable->horizontalHeader()->setLabel(3, QApplication::translate("ProrateSexDialog", "Available Head", 0, QApplication::UnicodeUTF8));
        buttonOk->setText(QApplication::translate("ProrateSexDialog", "OK", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ProrateSexDialog: public Ui_ProrateSexDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRORATESEXDIALOG_H
