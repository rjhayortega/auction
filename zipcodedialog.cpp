//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add delete ui;
//   delete moc include at end

#include "zipcodedialog.h"
#include "ui_zipcodedialog.h"

#include <qvariant.h>
#include <qlabel.h>
#include <Q3ListBox>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

ZipCodeDialog::ZipCodeDialog( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl ), ui(new Ui::ZipCodeDialog)
{
    ui->setupUi(this);
    // signals and slots connections
    connect( ui->cityStateZipListBox, SIGNAL( returnPressed(Q3ListBoxItem*) ), this, SLOT( accept() ) );
    connect( ui->cityStateZipListBox, SIGNAL( doubleClicked(Q3ListBoxItem*) ), this, SLOT( accept() ) );
    init();
}

ZipCodeDialog::~ZipCodeDialog()
{
    delete ui;
}

#include "dao/setupdao.h"

void ZipCodeDialog::init()
{
}

void ZipCodeDialog::init(vector<Address> zipCodeList)
{
    this->zipCodeList = zipCodeList;
    QStringList cityStateZipStringList;
    int initialIndex = -1;
    string marketState = SetupDAO().get("genMktState");
    for(unsigned int i = 0; i < zipCodeList.size(); i++)
    {
        cityStateZipStringList += QString::fromStdString(zipCodeList[i].getCity()) + ", " + QString::fromStdString(zipCodeList[i].getState()) + " " + QString::fromStdString(zipCodeList[i].getZip());

        if(initialIndex == -1 && zipCodeList[i].getState() == marketState)
        {
            initialIndex = i;
        }
    }

    initialIndex = (initialIndex == -1 ? 0 : initialIndex);
    ui->cityStateZipListBox->clear();
    ui->cityStateZipListBox->insertStringList(cityStateZipStringList);
    ui->cityStateZipListBox->setCurrentItem(initialIndex);
}

Address ZipCodeDialog::getCurrentAddress()
{
    int currentItem = ui->cityStateZipListBox->currentItem();

    if(0 <= currentItem && currentItem < zipCodeList.size())
    {
        return zipCodeList[currentItem];
    }

    return Address();
}


