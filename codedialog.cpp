#include "codedialog.h"
#include "ui_codedialog.h"

#include <qvariant.h>
#include <Q3ListBox>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qcombobox.h>
#include <qcheckbox.h>
#include <qbuttongroup.h>
#include <qradiobutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

#include "reports/codereport.h"
#include "dao/setupdao.h"
#include "previewdialog.h"


CodeDialog::CodeDialog( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl ), ui(new Ui::CodeDialog)
{
    ui->setupUi(this);
    // signals and slots connections
    connect( ui->codeEditModeGroup, SIGNAL( clicked(int) ), this, SLOT( populateCodeList() ) );
    connect( ui->codeListBox, SIGNAL( highlighted(int) ), this, SLOT( loadCurrentCode(int) ) );
    connect( ui->codeSaveButt, SIGNAL( clicked() ), this, SLOT( saveCurrentCode() ) );
    connect( ui->codeDelButt, SIGNAL( clicked() ), this, SLOT( deleteCurrentCode() ) );
    connect( ui->colorComboBox, SIGNAL( activated(int) ), this, SLOT( populateCodeList() ) );
    connect( ui->printListButton, SIGNAL( clicked() ), this, SLOT( printCodeList() ) );

    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CodeDialog::~CodeDialog()
{
    delete ui;
}

///////////////////////////////////////////////////////////////////////////////
//
// name:    init()
//
// purpose: constructor like class
//
// calling params:
//
// return params:
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void CodeDialog::init()
{
    populateCodeList();
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    populateCodeList()
//
// purpose: populates the listbox of codes from values retrieved from the
//          database into the objects STL vector of AnimalCode's
//
// calling params:
//
// return params:
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void CodeDialog::populateCodeList()
{
    colorGroup = CommissionDAO::INVALID;

    if(ui->codeEditModeGroup->selectedId() == 1)
    {
        ui->codePair->show();
        ui->colorComboBox->show();
        ui->colorGroupLabel->show();
        colorGroup = CommissionDAO::COLOR_GROUP(ui->colorComboBox->currentItem());
    }
    else
    {
        ui->codePair->hide();
        ui->colorComboBox->hide();
        ui->colorGroupLabel->hide();
    }

    codeList = AnimalCodeDAO().getCodeList(colorGroup);

    vector<AnimalCode>::iterator current;
    QStringList codeStringList;
    short code;
    QString descrip;

    vector<AnimalCode> actualCodeList;

    for(unsigned int i = 0; i < codeList.size(); i++)
    {
        switch(ui->codeEditModeGroup->selectedId())
        {
        case 0:
        default:
            if(codeList[i].getColor() <= 99 && codeList[i].getColorDescrip().length() > 0)
            {
                actualCodeList.push_back(codeList[i]);
            }
            break;

        case 1:
            if(codeList[i].getType() <= 9 && codeList[i].getTypeDescrip().length() > 0)
            {
                actualCodeList.push_back(codeList[i]);
            }
            break;

        case 2:
            if(codeList[i].getFlaw() <= 99 && codeList[i].getFlawDescrip().length() > 0)
            {
                actualCodeList.push_back(codeList[i]);
            }
            break;
        }
    }

    codeList = actualCodeList;
    for(current = codeList.begin(); current != codeList.end(); current++)
    {
        switch(ui->codeEditModeGroup->selectedId())
        {
        case 0:
        default:
            code = current->getColor();
            descrip = QString::fromStdString(current->getColorDescrip());
            if(code <= 99 && descrip.length() > 0)
            {
                codeStringList += QString::number(code) + ", " + descrip;
            }
            break;

        case 1:
            code = current->getType();
            descrip = QString::fromStdString(current->getTypeDescrip());
            if(code <= 9 && descrip.length() >=0)
            {
                codeStringList += QString::number(code) + ", " + descrip;
            }
            break;

        case 2:
            code = current->getFlaw();
            descrip = QString::fromStdString(current->getFlawDescrip());
            if(code <= 99 && descrip.length() > 0)
            {
                codeStringList += QString::number(code) + ", " + descrip;
            }
            break;
        }
    }

    ui->codeListBox->clear();
    ui->codeListBox->insertStringList(codeStringList);
    resetFields();
    ui->lineEditCode->setFocus();
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    loadCurrentCode(int)
//
// purpose: loads the code at row 'row' into the form of the dialog
//
// calling params: int row, the row of the code in the STL vector and the
//                          list box
//
// return params:
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void CodeDialog::loadCurrentCode(int row)
{
    short code;
    string descrip;

    switch(ui->codeEditModeGroup->selectedId())
    {
    case 0:
    default:
        code = codeList[row].getColor();
        descrip = codeList[row].getColorDescrip();

        break;
    case 1:
        code = codeList[row].getType();
        descrip = codeList[row].getTypeDescrip();
        ui->codePair->setChecked(codeList[row].isPair());
        break;
    case 2:
        code = codeList[row].getFlaw();
        descrip = codeList[row].getFlawDescrip();
        break;
    }

    ui->lineEditCode->setText(QString::number(code));
    ui->codeDescrip->setText(QString::fromStdString(descrip));
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    saveCurrentCode()
//
// purpose: saves the data in the form to the database
//
// calling params:
//
// return params:
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void CodeDialog::saveCurrentCode()
{
    short code = ui->lineEditCode->text().toShort();
    QString descrip = ui->codeDescrip->text();

    AnimalCodeDAO dao;
    switch(ui->codeEditModeGroup->selectedId())
    {
    case 0:
    default:
        if(code < 100)
        {
            dao.saveColor(code, descrip.toStdString());
        }
        break;

    case 2:
        if(code < 100)
        {
            dao.saveFlaw(code, descrip.toStdString());
        }
        break;

    case 1:
        if(code < 10)
        {
            dao.saveType(code, descrip.toStdString(), ui->codePair->isChecked(), CommissionDAO::COLOR_GROUP(ui->colorComboBox->currentItem()));
        }
        break;
    }
    populateCodeList();
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    deleteCurrentCode()
//
// purpose: sets the description of the current code to be an empty string
//
// calling params:
//
// return params:
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void CodeDialog::deleteCurrentCode()
{
    short code = ui->lineEditCode->text().toShort();
    AnimalCodeDAO::CodeType type = AnimalCodeDAO::sex;
    CommissionDAO::COLOR_GROUP colorGroup = CommissionDAO::INVALID;

    switch(ui->codeEditModeGroup->selectedId())
    {
    case 1:
        type = AnimalCodeDAO::sex;
        colorGroup = CommissionDAO::COLOR_GROUP(ui->colorComboBox->currentItem());
        break;

    case 0:
        type = AnimalCodeDAO::color;
        break;

    case 2:
        type = AnimalCodeDAO::flaw;
        break;
    }
    AnimalCodeDAO().deleteCode(type, code, colorGroup);
    populateCodeList();
}


///////////////////////////////////////////////////////////////////////////////
//
// name:    resetFields()
//
// purpose: sets the fields of the dialog to be empty strings
//
// calling params:
//
// return params:
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void CodeDialog::resetFields()
{
    ui->lineEditCode->setText("");
    ui->codeDescrip->setText("");
    ui->codePair->setChecked(false);
}

void CodeDialog::printCodeList()
{
    CodeReport::CodeType codeType;
    string headerText = "";

    switch(ui->codeEditModeGroup->selectedId())
    {
    case 0:
    default:
        codeType = CodeReport::Color;
        headerText = "COLOR LIST";
        break;

    case 1:
        codeType = CodeReport::Sex;
        headerText = string("SEX LIST - ") + ui->colorComboBox->currentText().ascii();
        break;

    case 2:
        codeType = CodeReport::Flaw;
        headerText = "FLAW LIST";
        break;
    }
    CodeReport report(codeList, codeType);
    report.setHeader(SetupDAO().reportHeader(headerText));
    PreviewDialog preview(this);
    preview.setText(QString::fromStdString(report.text()));
    preview.setShowPrint(true);
    preview.setReport(&report);
    preview.exec();
}
