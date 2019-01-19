/********************************************************************************
** Form generated from reading UI file 'lienimportdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LIENIMPORTDIALOG_H
#define UI_LIENIMPORTDIALOG_H

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
#include <Qt3Support/Q3ProgressDialog>
#include <QtCore/QFileInfoListIterator>
#include <string>
#include <time.h>
#include <vector>
#include "dao/customerdao.h"
#include "lienrecord.h"

QT_BEGIN_NAMESPACE

class Ui_LienImportDialog
{
public:
    QLabel *textLabel1;
    QLabel *textLabel2;
    QPushButton *importButton;
    QLineEdit *lienPathEdit;
    QPushButton *browseButton;
    QComboBox *stateComboBox;
    QLabel *label;
    QPushButton *lienImportCancelButton;

    void setupUi(QDialog *LienImportDialog)
    {
        if (LienImportDialog->objectName().isEmpty())
            LienImportDialog->setObjectName(QString::fromUtf8("LienImportDialog"));
        LienImportDialog->setWindowModality(Qt::ApplicationModal);
        LienImportDialog->resize(516, 374);
        QFont font;
        font.setPointSize(13);
        LienImportDialog->setFont(font);
        textLabel1 = new QLabel(LienImportDialog);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
        textLabel1->setGeometry(QRect(20, 10, 120, 30));
        textLabel1->setWordWrap(false);
        textLabel2 = new QLabel(LienImportDialog);
        textLabel2->setObjectName(QString::fromUtf8("textLabel2"));
        textLabel2->setGeometry(QRect(20, 90, 120, 30));
        textLabel2->setWordWrap(false);
        importButton = new QPushButton(LienImportDialog);
        importButton->setObjectName(QString::fromUtf8("importButton"));
        importButton->setGeometry(QRect(80, 180, 130, 30));
        lienPathEdit = new QLineEdit(LienImportDialog);
        lienPathEdit->setObjectName(QString::fromUtf8("lienPathEdit"));
        lienPathEdit->setGeometry(QRect(20, 120, 331, 31));
        browseButton = new QPushButton(LienImportDialog);
        browseButton->setObjectName(QString::fromUtf8("browseButton"));
        browseButton->setGeometry(QRect(370, 120, 130, 30));
        stateComboBox = new QComboBox(LienImportDialog);
        stateComboBox->setObjectName(QString::fromUtf8("stateComboBox"));
        stateComboBox->setGeometry(QRect(20, 40, 120, 30));
        label = new QLabel(LienImportDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(60, 250, 401, 91));
        label->setFrameShape(QFrame::Box);
        label->setWordWrap(true);
        lienImportCancelButton = new QPushButton(LienImportDialog);
        lienImportCancelButton->setObjectName(QString::fromUtf8("lienImportCancelButton"));
        lienImportCancelButton->setGeometry(QRect(300, 180, 131, 31));

        retranslateUi(LienImportDialog);

        QMetaObject::connectSlotsByName(LienImportDialog);
    } // setupUi

    void retranslateUi(QDialog *LienImportDialog)
    {
        LienImportDialog->setWindowTitle(QApplication::translate("LienImportDialog", "ImportLiens", 0, QApplication::UnicodeUTF8));
        textLabel1->setText(QApplication::translate("LienImportDialog", "State", 0, QApplication::UnicodeUTF8));
        textLabel2->setText(QApplication::translate("LienImportDialog", "Lien File", 0, QApplication::UnicodeUTF8));
        importButton->setText(QApplication::translate("LienImportDialog", "Import Liens", 0, QApplication::UnicodeUTF8));
        browseButton->setText(QApplication::translate("LienImportDialog", "Browse", 0, QApplication::UnicodeUTF8));
        stateComboBox->clear();
        stateComboBox->insertItems(0, QStringList()
         << QApplication::translate("LienImportDialog", "NE", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("LienImportDialog", "SD", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("LienImportDialog", "ID", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("LienImportDialog", "ND", 0, QApplication::UnicodeUTF8)
        );
        label->setText(QApplication::translate("LienImportDialog", "<html><head/><body><p><span style=\" color:#ff0000;\">Sargent Communications, Inc. is not responsible for the accuracy of data imported from any state lien file.</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        lienImportCancelButton->setText(QApplication::translate("LienImportDialog", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class LienImportDialog: public Ui_LienImportDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LIENIMPORTDIALOG_H
