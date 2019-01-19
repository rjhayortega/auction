//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add ui->setupUi(this);
//   Add delete ui;
//   delete moc include at end

#include "breakeditdialog.h"
#include "ui_breakeditdialog.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qtextedit.h>
#include <Q3Table>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

BreakEditDialog::BreakEditDialog( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl ), ui(new Ui::BreakEditDialog)
{
    ui->setupUi(this);
    // signals and slots connections
    connect( ui->cancelButton, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( ui->okButton, SIGNAL( clicked() ), this, SLOT( accept() ) );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
BreakEditDialog::~BreakEditDialog()
{
    delete ui;
}

/******************************************************************************
 *
 * class: commissionGroupItem
 *
 * purpose: encapsulates the sex / flaw ordered pairs as a list of flaws for
 *          each sex, in an attempt to display these associations quickly and
 *          presentably
 *****************************************************************************/

class CommissionGroupItem
{
public:
    string sex;
    vector<string> flawList;

    CommissionGroupItem(string sex="", string flaw="")
    {
        this->sex = sex;
        this->flawList.push_back(flaw);
    }

    bool operator==(string sex)
    {
        return this->sex == sex;
    }
};


///////////////////////////////////////////////////////////////////////////////
//
// name: init()
//
// purpose: constructor like function, called when a dialog is created.
//          in this case, sets the focus on the break table
//
// calling params: void
//
// return params: void
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
void BreakEditDialog::init()
{
    ui->breakTable->setFocus();
    ui->breakTable->setColumnWidth(2, 30);
}


///////////////////////////////////////////////////////////////////////////////
//
// name: init(Commission)
//
// purpose: initializes the dialog to use a specific commission to show the
//          breaks from
//
// calling params: Commission commission - the commission we are editing
//
// return params: void
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
void BreakEditDialog::init(Commission commission)
{
    this->commission = commission;
    ui->breakTable->setLeftMargin(0);
    this->breakList = commission.getBreakList();
    showCodeAssociation(CommissionDAO().getCodeRelList(commission.getId()));


    string unitString;

    switch(commission.getBreakType())
    {
    case Commission::AtHead:
        unitString = "Head";
        break;

    case Commission::AtWeight:
        unitString = "Lbs";
        break;

    case Commission::AtTotal:
        unitString = "Total $";
        break;

    case Commission::AtPrice:
        unitString = "Price $";
        break;
    }

    for(unsigned int i = 0; i < ui->breakTable->numRows(); i++)
    {
        ui->breakTable->setItem(i,0, new Q3TableItem(ui->breakTable, Q3TableItem::OnTyping, ""));
        ui->breakTable->setItem(i,1, new Q3TableItem(ui->breakTable, Q3TableItem::OnTyping, ""));
        ui->breakTable->setItem(i, 2, new Q3TableItem(ui->breakTable, Q3TableItem::Never, QString::fromStdString(unitString)));
    }
    populateBreakTable();
}

///////////////////////////////////////////////////////////////////////////////
//
// name: showCodeAssociation(list<AnimalCode> codeList)
//
// purpose: gives textual descriptions of which animal flaw code pairs that
//          these breaks will apply to
//
// calling params: list<AnimalCode> codeList - the list of codes to show
//
// return params: void
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
void BreakEditDialog::showCodeAssociation(list<AnimalCode> codeList)
{
    AnimalCodeDAO codeDao;
    vector<CommissionGroupItem> commItemList;
    vector<CommissionGroupItem>::iterator currentCommItem;
    list<AnimalCode>::iterator codeIt;

    for(codeIt = codeList.begin(); codeIt != codeList.end(); codeIt++)
    {
        switch(codeIt->getColor())
        {
        case 0:
            break;
        case 1:
            codeIt->setColor(70);
            break;

        case 2:
            codeIt->setColor(80);
            break;

        case 3:
            codeIt->setColor(90);
            break;
        }
        codeDao.fillAnimalCode(*codeIt);

        if(codeIt->getFlaw() == 0)
        {
            codeIt->setFlawDescrip("NORMAL");
        }

        if(codeIt->getTypeDescrip() == "")
        {
            codeIt->setTypeDescrip(QString("UNASSIGNED[").append(QString::number(codeIt->getType())).append("]").toStdString());
        }

        if((currentCommItem = std::find(commItemList.begin(), commItemList.end(), codeIt->getTypeDescrip())) == commItemList.end())
        {
            commItemList.push_back(CommissionGroupItem(codeIt->getTypeDescrip(), codeIt->getFlawDescrip()));
        }
        else
        {
            currentCommItem->flawList.push_back(codeIt->getFlawDescrip());
        }
    }

    string commString;

    for(unsigned int i = 0; i < commItemList.size(); i++)
    {
        commString += commItemList[i].sex + "<br><hr>";
        commString += "{";
        for(unsigned int j = 0; j < commItemList[i].flawList.size(); j++)
        {
            commString += commItemList[i].flawList[j];

            commString += (j == commItemList[i].flawList.size() - 1 ? "": ", ");
        }

        commString += "}<br><br>";
    }
    ui->commissionDescripText->setText(QString::fromStdString(commString));
}


///////////////////////////////////////////////////////////////////////////////
//
// name: populateBreakTable()
//
// purpose: fills the break table with the initial values from the commission
//
// calling params: void
//
// return params: void
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
void BreakEditDialog::populateBreakTable()
{
    for(unsigned int i = 0; i < breakList.size(); i++)
    {
        ui->breakTable->setText(i, 0, QString::fromStdString(breakList[i].getExpression()));
        ui->breakTable->setText(i, 1, QString::number(breakList[i].getBreakValue(), 'f', 2));
        ui->breakTable->setText(i, 3, QString::number(breakList[i].getMin(), 'f', 2));
        ui->breakTable->setText(i, 4, QString::number(breakList[i].getMax(), 'f', 2));
    }
}



///////////////////////////////////////////////////////////////////////////////
//
// name: accept()
//
// purpose: handles the 'Ok' button being pressed
//
// calling params: void
//
// return params: void
//
// Notes: saves the break list and exits the dialog with an Accepted status
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////

void BreakEditDialog::accept()
{
    saveBreakList();
    QDialog::accept();
}


///////////////////////////////////////////////////////////////////////////////
//
// name: saveBreakList()
//
// purpose: saves the current break list to the database
//
// calling params: void
//
// return params: void
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
void BreakEditDialog::saveBreakList()
{
    string expression;
    double breakValue;
    double min = 0.00000001;
    double max = 99999999.99;
    CommissionDAO commDao;
    commDao.deleteBreaks(commission);
    for(unsigned int i = 0; i < ui->breakTable->numRows(); i++)
    {
        expression = ui->breakTable->text(i, 0).stripWhiteSpace().ascii();

        if(expression != "")
        {
            breakValue = ui->breakTable->text(i, 1).toDouble();

            if(ui->breakTable->text(i, 3) != "")
            {
                min = ui->breakTable->text(i, 3).toDouble();
            }
            if(ui->breakTable->text(i, 4) != "")
            {
                max = ui->breakTable->text(i, 4).toDouble();
            }
            CommissionBreak newBreak(0, expression, breakValue);
            newBreak.setMin(min);
            newBreak.setMax(max);
            commDao.saveBreak(newBreak, commission.getId());
        }
    }
}

