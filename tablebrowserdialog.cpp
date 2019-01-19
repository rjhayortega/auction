//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add delete ui;
//   delete moc include at end

#include "tablebrowserdialog.h"
#include "ui_tablebrowserdialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <Q3ListBox>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

TableBrowserDialog::TableBrowserDialog( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl ), ui(new Ui::TableBrowserDialog)
{
    ui->setupUi(this);
    // signals and slots connections
    connect( ui->cancelButton, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( ui->okButton, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( ui->itemListBox, SIGNAL( doubleClicked(QListBoxItem*) ), this, SLOT( accept() ) );
    connect( ui->itemListBox, SIGNAL( returnPressed(QListBoxItem*) ), this, SLOT( accept() ) );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
TableBrowserDialog::~TableBrowserDialog()
{
    delete ui;
}

void TableBrowserDialog::init()
{
}

void TableBrowserDialog::init(QStringList itemList)
{
    init(itemList, "");
}

void TableBrowserDialog::setMulti(bool selectAll)
{
    ui->itemListBox->setSelectionMode(Q3ListBox::Multi);

    if(selectAll)
    {
        ui->itemListBox->clearSelection();
        ui->itemListBox->invertSelection();
    }
}

void TableBrowserDialog::init(QStringList itemList, QString item)
{
    ui->itemListBox->clear();
    ui->itemListBox->insertStringList(itemList);

    if(item != "")
    {
        int index = itemList.findIndex(item);

        if(0 <= index && index < itemList.size())
        {
            ui->itemListBox->setCurrentItem(index);
            ui->itemListBox->setSelected(index, true);
        }
    }

    repaint(false);
    QApplication::flush();
}

int TableBrowserDialog::selectedIndex()
{
    Q3ListBoxItem*selectedItem = ui->itemListBox->selectedItem();
    int index = -1;
    if(selectedItem != NULL)
    {
        index = ui->itemListBox->index(selectedItem);
    }

    return index;
}

std::vector<int> TableBrowserDialog::selectedIndexVector()
{
    std::vector<int> resultVector;

    for(int i = 0; i < ui->itemListBox->numRows(); i++)
    {
        if(ui->itemListBox->isSelected(i))
        {
            resultVector.push_back(i);
        }
    }

    return resultVector;
}
