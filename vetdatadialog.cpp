//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add delete ui;
//   delete moc include at end

#include "vetdatadialog.h"
#include "ui_vetdatadialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qgroupbox.h>
#include <qtextedit.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>
#include "types/person.h"

VetDataDialog::VetDataDialog( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl ), ui(new Ui::VetDataDialog)
{
    ui->setupUi(this);
    // signals and slots connections
    connect( ui->saveButton, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( ui->cancelButton, SIGNAL( clicked() ), this, SLOT( reject() ) );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
VetDataDialog::~VetDataDialog()
{
    delete ui;
}

void VetDataDialog::init()
{
    loadVetData();
}


void VetDataDialog::accept()
{
    saveVetData();
    QDialog::accept();
}


void VetDataDialog::loadVetData()
{
    string vetId = setup.get("vetId");
    Name vetName = Name(setup.get("vetName"));
    vetName.setInitials(setup.get("vetInitials"));
    string vetAddress1 = setup.get("vetAddress1");
    string vetAddress2 = setup.get("vetAddress2");
    string vetCityStateZip = setup.get("vetCityStateZip");
    string vetPhone = setup.get("vetPhone");

    Person vet = Person(atol(vetId.c_str()), vetName, Address(vetAddress1, vetAddress2, vetCityStateZip), ContactList(vetPhone));

    ui->vetEdit->setText(QString::fromStdString(QString::number(vet.getId()).toStdString() + "\n" + vet.getName().getLast() + "\n" + vet.getName().getInitials() + "\n" + vet.getAddress().getAddress1() + "\n" +  vet.getAddress().getAddress2() + "\n" + vet.getAddress().getCity() + "\n" + vet.getContactList().getFirstPhone()));
}

void VetDataDialog::saveVetData()
{
    QStringList vetDataList = QStringList::split("\n", ui->vetEdit->text(), true);

    setup.set("vetId", "0");
    setup.set("vetName", "");
    setup.set("vetInitials", "");
    setup.set("vetAddress1", "");
    setup.set("vetAddress2", "");
    setup.set("vetCityStateZip", "");

    if(0 < vetDataList.size())
    {
        setup.set("vetId", vetDataList[0].toStdString());
    }

    if(1 < vetDataList.size())
    {
        setup.set("vetName", vetDataList[1].toStdString());
    }

    if(2 < vetDataList.size())
    {
        setup.set("vetInitials", vetDataList[2].toStdString());
    }

    if(3 < vetDataList.size())
    {
        setup.set("vetAddress1", vetDataList[3].toStdString());
    }

    if(4 < vetDataList.size())
    {
        setup.set("vetAddress2", vetDataList[4].toStdString());
    }

    if(5 < vetDataList.size())
    {
        setup.set("vetCityStateZip", vetDataList[5].toStdString());
    }

    if(6 < vetDataList.size())
    {
        setup.set("vetPhone", vetDataList[6].toStdString());
    }
}
