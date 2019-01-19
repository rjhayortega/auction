//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add ui->setupUi(this);
//   Add delete ui;
//   delete moc include at end

#include "brandbrowserdialog.h"
#include "ui_brandbrowserdialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <Q3Table>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

BrandBrowserDialog::BrandBrowserDialog( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl ), ui(new Ui::BrandBrowserDialog)
{
    ui->setupUi(this);
    // signals and slots connections
    connect( ui->backButton, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( ui->pageDownButton, SIGNAL( clicked() ), this, SLOT( nextGroup() ) );
    connect( ui->pageUpButton, SIGNAL( clicked() ), this, SLOT( previousGroup() ) );
    // [KLN] add
    connect( ui->goTopButton, SIGNAL( clicked() ), this, SLOT( firstGroup() ) );
    connect( ui->goBottomButton, SIGNAL( clicked() ), this, SLOT( lastGroup() ) );
    // [KLN] add end
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
BrandBrowserDialog::~BrandBrowserDialog()
{
    delete ui;
}

/*
 * allows greater control over alignment of table items
 */

class LeftTableItem : public Q3TableItem
{
public:
    LeftTableItem(Q3Table* parent, Q3TableItem::EditType editType, QString text) : Q3TableItem(parent, editType, text) {}
protected:
    virtual int alignment()
    {
        return Qt::AlignLeft;
    }
};


///////////////////////////////////////////////////////////////////////////////
//
// name: init()
//
// purpose: constructor like function, used called upon dialog object creation
//          sets up initial dialog state
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
void BrandBrowserDialog::init()
{
    offset = 0;
    initBrandTable();
    loadBrandList();
    currentIndex = -1;

}

///////////////////////////////////////////////////////////////////////////////
//
// name: loadBrandList()
//
// purpose: loads the list of brands from the database into the brand table
//
// calling params: void
//
// return params: void
//
// Notes: loads only 4 brands at a time
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
void BrandBrowserDialog::loadBrandList()
{
    brandList = brandDao.getLimitedBrandList(offset, 4);
    clearBrandTable();
    for(unsigned int i = 0; i < brandList.size(); i++)
    {
        ui->brandTable->setItem(0, i, new Q3TableItem(ui->brandTable, Q3TableItem::Never, "", QPixmap(brandList[i].getBrandImage().scaled(96, 96))));
        ui->brandTable->setItem(1, i, new LeftTableItem(ui->brandTable, Q3TableItem::Always, QString::fromStdString(brandList[i].getTag())));
        ui->brandTable->setItem(2, i, new LeftTableItem(ui->brandTable, Q3TableItem::Always, QString::number(brandList[i].getHead())));
        ui->brandTable->setItem(3, i, new LeftTableItem(ui->brandTable, Q3TableItem::Always, QString::fromStdString(brandList[i].getBrandPosition())));
        ui->brandTable->setItem(4, i, new LeftTableItem(ui->brandTable, Q3TableItem::Always, QString::number(brandList[i].getTransactionId())));

        ui->brandTable->cellWidget(5, i)->setEnabled(true);
        ui->brandTable->cellWidget(6, i)->setEnabled(true);
        ui->brandTable->cellWidget(7, i)->setEnabled(true);
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// name: nextGroup()
//
// purpose: loads the next 4 brands from the brand database
//
// calling params: none
//
// return params: none
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
void BrandBrowserDialog::nextGroup()
{
    if(brandList.size() > 0)
    {
        offset += 4;
        loadBrandList();
    }
}

///////////////////////////////////////////////////////////////////////////////
//
// name: previousGroup()
//
// purpose: loads the previous 4 brands from the database
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
void BrandBrowserDialog::previousGroup()
{

    if(offset >= 4)
    {
        offset -= 4;
    }
    else
    {
        offset = 0;
    }
    loadBrandList();
}

// [KLN] add

///////////////////////////////////////////////////////////////////////////////
//
// name: lastGroup()
//
// purpose: loads the last 4 brands from the brand database
//
// calling params: none
//
// return params: none
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
void BrandBrowserDialog::lastGroup()
{
    long size = brandDao.getBrandListSize();
    if(size > 4)
    {
        offset = size - 4;
        loadBrandList();
    }
}

///////////////////////////////////////////////////////////////////////////////
//
// name: firstGroup()
//
// purpose: loads the first 4 brands from the brand database
//
// calling params: none
//
// return params: none
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
void BrandBrowserDialog::firstGroup()
{
    if(brandList.size() > 0)
    {
        offset = 0;
        loadBrandList();
    }
}

// [KLN] add end

///////////////////////////////////////////////////////////////////////////////
//
// name: clearBrandTable()
//
// purpose: clears the brand table
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
void BrandBrowserDialog::clearBrandTable()
{
    QPixmap temp(96, 96);
    temp.fill();
    for(unsigned int i = 0; i < ui->brandTable->numCols(); i++)
    {
        ui->brandTable->setPixmap(0, i, temp);
        ui->brandTable->setText(1, i, "");
        ui->brandTable->setText(2, i, "");
        ui->brandTable->setText(3, i, "");
        ui->brandTable->setText(4, i, "");
        ui->brandTable->cellWidget(5, i)->setEnabled(false);
        ui->brandTable->cellWidget(6, i)->setEnabled(false);
        ui->brandTable->cellWidget(7, i)->setEnabled(false);
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// name: initBrandTable()
//
// purpose: initializes the brand table, sets up the buttons and the connections
//          to the buttons
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
void BrandBrowserDialog::initBrandTable()
{
    ui->brandTable->setRowHeight(0,  96);
    QPushButton* button;
    QPushButton* deleteButton;
    QPushButton* copyButton;

    for(unsigned int i = 0; i < ui->brandTable->numCols(); i++)
    {
        ui->brandTable->setColumnWidth(i, 100);

        switch(i)
        {
        case 0:
            button = new QPushButton("Save", ui->brandTable, "save1");
            connect(button, SIGNAL(clicked()), this, SLOT(processColumn1()));

            deleteButton = new QPushButton("Delete", ui->brandTable, "delete1");
            connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteColumn1()));

            copyButton = new QPushButton("Copy", ui->brandTable, "copy1");
            connect(copyButton, SIGNAL(clicked()), this, SLOT(copyColumn1()));
            break;
        case 1:
            button = new QPushButton("Save", ui->brandTable, "save2");
            connect(button, SIGNAL(clicked()), this, SLOT(processColumn2()));

            deleteButton = new QPushButton("Delete", ui->brandTable, "delete2");
            connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteColumn2()));

            copyButton = new QPushButton("Copy", ui->brandTable, "copy2");
            connect(copyButton, SIGNAL(clicked()), this, SLOT(copyColumn2()));
            break;
        case 2:
            button = new QPushButton("Save", ui->brandTable, "save3");
            connect(button, SIGNAL(clicked()), this, SLOT(processColumn3()));

            deleteButton = new QPushButton("Delete", ui->brandTable, "delete3");
            connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteColumn3()));

            copyButton = new QPushButton("Copy", ui->brandTable, "copy3");
            connect(copyButton, SIGNAL(clicked()), this, SLOT(copyColumn3()));
            break;
        case 3:
            button = new QPushButton("Save", ui->brandTable, "save4");
            connect(button, SIGNAL(clicked()), this, SLOT(processColumn4()));

            deleteButton = new QPushButton("Delete", ui->brandTable, "delete4");
            connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteColumn4()));


            copyButton = new QPushButton("Copy", ui->brandTable, "copy4");
            connect(copyButton, SIGNAL(clicked()), this, SLOT(copyColumn4()));
            break;
        }

        ui->brandTable->setCellWidget(5, i, button);
        ui->brandTable->setCellWidget(6, i, deleteButton);
        ui->brandTable->setCellWidget(7, i, copyButton);
        ui->brandTable->setRowHeight(5, 50);
        ui->brandTable->setRowHeight(6, 50);
        ui->brandTable->setRowHeight(7, 50);
    }
}



///////////////////////////////////////////////////////////////////////////////
//
// name: processColumn1()
//
// purpose: interface to save the first column
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
void BrandBrowserDialog::processColumn1()
{
    processItem(0);
}



///////////////////////////////////////////////////////////////////////////////
//
// name: processColumn2()
//
// purpose: interface to save the second column
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
void BrandBrowserDialog::processColumn2()
{
    processItem(1);
}

///////////////////////////////////////////////////////////////////////////////
//
// name: processColumn3()
//
// purpose: interface to save the third column
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
void BrandBrowserDialog::processColumn3()
{
    processItem(2);
}

///////////////////////////////////////////////////////////////////////////////
//
// name: processColumn4()
//
// purpose: interface to save the fourth column
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
void BrandBrowserDialog::processColumn4()
{
    processItem(3);
}


///////////////////////////////////////////////////////////////////////////////
//
// name: processItem(int)
//
// purpose: saves the brand represented at column 'col'
//
// calling params: int col - the column to process
//
// return params: void
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
void BrandBrowserDialog::processItem(int col)
{
    brandList[col].setTag(ui->brandTable->text(1, col).toStdString());
    brandList[col].setHead(ui->brandTable->text(2, col).toLong());
    brandList[col].setBrandPosition(ui->brandTable->text(3, col).toStdString());
    brandList[col].setTransactionId(ui->brandTable->text(4, col).toLong());

    brandDao.saveBrand(brandList[col]);
    loadBrandList();
}


///////////////////////////////////////////////////////////////////////////////
//
// name: deleteColumn1()
//
// purpose: interface to delete the first column
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
void BrandBrowserDialog::deleteColumn1()
{
    deleteBrand(0);
}


///////////////////////////////////////////////////////////////////////////////
//
// name: deleteColumn2()
//
// purpose: interface to delete the second column
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
void BrandBrowserDialog::deleteColumn2()
{
    deleteBrand(1);
}


///////////////////////////////////////////////////////////////////////////////
//
// name: deleteColumn3()
//
// purpose: interface to delete the third column
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
void BrandBrowserDialog::deleteColumn3()
{
    deleteBrand(2);
}


///////////////////////////////////////////////////////////////////////////////
//
// name: deleteColumn4()
//
// purpose: interface to delete the fourth column
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
void BrandBrowserDialog::deleteColumn4()
{
    deleteBrand(3);
}


///////////////////////////////////////////////////////////////////////////////
//
// name: deleteBrand()
//
// purpose: deletes the brand represented at column 'column' in the brand table
//
// calling params: int column  - the column of the brand to delete
//
// return params: void
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
void BrandBrowserDialog::deleteBrand(int column)
{
    brandDao.deleteBrand(brandList[column]);
    loadBrandList();
}


///////////////////////////////////////////////////////////////////////////////
//
// name: copyColumn1()
//
// purpose: interface to copy the first column
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
void BrandBrowserDialog::copyColumn1()
{
    copyColumn(0);
}

///////////////////////////////////////////////////////////////////////////////
//
// name: copyColumn2()
//
// purpose: interface to copy the second column
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
void BrandBrowserDialog::copyColumn2()
{
    copyColumn(1);
}


///////////////////////////////////////////////////////////////////////////////
//
// name: copyColumn3()
//
// purpose: interface to copy the third column
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
void BrandBrowserDialog::copyColumn3()
{
    copyColumn(2);
}

///////////////////////////////////////////////////////////////////////////////
//
// name: copyColumn4()
//
// purpose: interface to copy the fourth column
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
void BrandBrowserDialog::copyColumn4()
{
    copyColumn(3);
}

///////////////////////////////////////////////////////////////////////////////
//
// name: copyColumn(int column)
//
// purpose: creates a copy of the brand represented at column: 'column'
//
// calling params: int column - the column of the brand table to create a copy of
//
// return params: void
//
// Notes: comments out the tag, so that there is not a conflict between tags.
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
void BrandBrowserDialog::copyColumn(int column)
{
    Brand tempBrand = brandList[column];
    tempBrand.setId(0);
    string tempTag = tempBrand.getTag();

    if(tempTag.length() > 0 && tempTag[0] != '/')
    {
        tempBrand.setTag("/" + tempTag);
    }

    brandDao.saveBrand(tempBrand);
    loadBrandList();
}
