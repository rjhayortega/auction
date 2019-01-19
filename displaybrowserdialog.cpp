//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add ui->setupUi(this);
//   Add delete ui;
//   delete moc include at end

#include "displaybrowserdialog.h"
#include "ui_displaybrowserdialog.h"

#include <qvariant.h>
#include <Q3ListBox>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

DisplayBrowserDialog::DisplayBrowserDialog( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl ), ui(new Ui::DisplayBrowserDialog)
{
    ui->setupUi(this);
    // signals and slots connections
    connect( ui->viewButton, SIGNAL( clicked() ), this, SLOT( editDisplay() ) );
    connect( ui->newButton, SIGNAL( clicked() ), this, SLOT( newDisplay() ) );
    connect( ui->deleteButton, SIGNAL( clicked() ), this, SLOT( deleteDisplay() ) );
    connect( ui->cancelButton, SIGNAL( clicked() ), this, SLOT( reject() ) );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
DisplayBrowserDialog::~DisplayBrowserDialog()
{
    delete ui;
}

#include "displaysetupdialog.h"
#include <qmessagebox.h>

void DisplayBrowserDialog::init()
{
    populateDisplayList();
}

void DisplayBrowserDialog::populateDisplayList()
{
    nextNum = 0;
    displayList = setup.getDisplayRecordList();
    QStringList stringList;

    for(unsigned int i = 0; i < displayList.size(); i++)
    {
        if(displayList[i].num > nextNum)
        {
            nextNum = displayList[i].num;
        }
        stringList += QString::number(displayList[i].num).leftJustify(5, ' ', true) + QString::fromStdString(displayList[i].name);
    }
    ui->displayListBox->clear();
    ui->displayListBox->insertStringList(stringList);
    nextNum++;
}

void DisplayBrowserDialog::editDisplay()
{
    for(int i = 0; i < ui->displayListBox->numRows(); i++)
    {
        if(ui->displayListBox->item(i)->isSelected())
        {
            DisplaySetupDialog dsd(this);
            dsd.init(displayList[i]);
            dsd.exec();
            populateDisplayList();
        }
    }
}

void DisplayBrowserDialog::newDisplay()
{


    string name;
    string port;
    int rows;
    int which;
    int base;

    SetupDAO::DisplayRecord display;
    display.num = nextNum;
    display.type = 0;
    display.name = "";
    display.port = "/dev/null,1200,8,N,1";
    display.rows = 0;
    display.which = 0;
    display.base = 0;
    display.rowList = vector<SetupDAO::DispRowsRecord>();

    DisplaySetupDialog dsd(this);
    dsd.init(display);
    dsd.exec();
    populateDisplayList();
}

void DisplayBrowserDialog::deleteDisplay()
{
    int index = ui->displayListBox->currentItem();

    if(0 <= index && index < displayList.size())
    {
        int confirm = QMessageBox::warning(this, "Warning",
                                           "This will permantly remove this configuration.\n"
                                           "Do you want to continue?",
                                           QMessageBox::Cancel, QMessageBox::Ok);

        if(confirm == QMessageBox::Ok)
        {
            setup.deleteDisplay(displayList[index]);
            populateDisplayList();
        }
    }
}
