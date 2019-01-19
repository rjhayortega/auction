//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add delete ui;
//   delete moc include at end

#include "vetreportdialogbase.h"
#include "ui_vetreportdialogbase.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qgroupbox.h>
#include <qcombobox.h>
#include <qtextedit.h>
#include <qspinbox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

VetReportDialogBase::VetReportDialogBase( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl )
    , ui(new Ui::VetReportDialogBase)
    ,m_printer(0)

{
    ui->setupUi(this);
    // signals and slots connections
    connect( ui->cancelButton, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( ui->printButton, SIGNAL( clicked() ), this, SLOT( print() ) );
    connect( ui->footerEdit, SIGNAL( textChanged() ), this, SLOT( footerChanged() ) );
    connect( ui->headerEdit, SIGNAL( textChanged() ), this, SLOT( headerChanged() ) );
    connect( ui->heightSpinBox, SIGNAL( valueChanged(int) ), this, SLOT( heightChanged(int) ) );
    connect( ui->headerEdit, SIGNAL( cursorPositionChanged(int,int) ), this, SLOT( headerCursorMoved(int,int) ) );
    connect( ui->footerEdit, SIGNAL( cursorPositionChanged(int,int) ), this, SLOT( footCursorMoved(int,int) ) );
    connect( ui->indexComboBox, SIGNAL( activated(const QString&) ), this, SLOT( setIndexRange() ) );
    connect( ui->importRecordComboBox, SIGNAL( activated(int) ), this, SLOT( importText(int) ) );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
VetReportDialogBase::~VetReportDialogBase()
{
    delete ui;
    delete m_printer;
}

#include "tablebrowserdialog.h"
#include "dao/customerdao.h"
#include "permsearchdialog.h"
#include <qinputdialog.h>

string VetReportDialogBase::heightKey()
{
    return "";
}


string VetReportDialogBase::headerKey()
{
    return "";
}


string VetReportDialogBase::footerKey()
{
    return "";
}

string VetReportDialogBase::headerColKey()
{
    return "";
}


string VetReportDialogBase::headerRowKey()
{
    return "";
}

void VetReportDialogBase::init()
{
 showMaximized();
 setIndexRange();
}

void VetReportDialogBase::delayedInit()
{
 initHeight();
 initHeader();
 initFooter();
 initHeaderCursorPos();
 currentTag = 0;
}

void VetReportDialogBase::setPrinter(PrinterBase *p)
{
    if (m_printer != 0) {
        delete m_printer;
    }
    m_printer = p;
}

void VetReportDialogBase::initHeight()
{
    string heightStr = setup.get(heightKey());
    
    if(heightStr.length() > 0)
    {
	ui->heightSpinBox->setValue(atoi(heightStr.c_str()));
    }
    else if(heightKey().length() > 0)
    {
	setup.set(heightKey(), QString::number(ui->heightSpinBox->value()).toStdString());
    }
}

void VetReportDialogBase::initHeader()
{
    string headerStr = setup.get(headerKey());  
    ui->headerEdit->setText(QString::fromStdString(headerStr));
}

void VetReportDialogBase::initHeaderCursorPos()
{
  int headerCol = QString::fromStdString(setup.get(headerColKey())).toInt();
  int headerRow = QString::fromStdString(setup.get(headerRowKey())).toInt();

  ui->headerEdit->setCursorPosition(headerRow, headerCol);
}

void VetReportDialogBase::initFooter()
{
    string footerStr = setup.get(footerKey());
    ui->footerEdit->setText(QString::fromStdString(footerStr));
}

void VetReportDialogBase::heightChanged(int value)
{
    setup.set(heightKey(), QString::number(value).toStdString());
}

void VetReportDialogBase::headerChanged()
{
    headerChanged(ui->headerEdit->text());
}

void VetReportDialogBase::footerChanged()
{
    footerChanged(ui->footerEdit->text());
}

void VetReportDialogBase::headerChanged(const QString& text)
{
    setup.set(headerKey(), text.toStdString());
}

void VetReportDialogBase::footerChanged(const QString& text)
{
    setup.set(footerKey(), text.toStdString());
}

QString VetReportDialogBase::makePage(QStringList headerText, QStringList bodyText, QStringList footerText, int bodySpace)
{
    QString pad = "";
	    
    if(bodyText.size() < bodySpace)
    {
	pad = QString(bodySpace - bodyText.size(), '\n');
    }
    
    QString header = headerText.join("\n");
    QString body = bodyText.join("\n");
    QString footer = footerText.join("\n");
	      
    return header + (header.length() > 0 ? "\n" : "") 
	+   body + (body.length() > 0 ? "\n" : " ")
	+ pad 
	+ footer + "\f";   
}

void VetReportDialogBase::print()
{
    QStringList headerText = QStringList::split("\n", ui->headerEdit->text(), true);
    QStringList footerText = QStringList::split("\n", ui->footerEdit->text(), true);
    QStringList bodyText;
    QStringList bodyLine;
    
    int height = ui->heightSpinBox->value();
    int bodySpace = height - (headerText.size() + footerText.size());
    
    
    bool last = false;
 
    QString line;
    QString document;
 
    initTagVector();
    
    while(!last && tagVector.size() > 0)
    {
	bodyLine = nextBodyLine(&last);
	
	if(last)
	{
	    if(bodyText.size() + bodyLine.size() > bodySpace)
	    {
		document += makePage(headerText, bodyText, footerText, bodySpace);
		bodyText.clear();
	    }
	    
 	    bodyText += bodyLine;
	    document += makePage(headerText, bodyText, footerText, bodySpace);
	    bodyText.clear();
	}
	else if(bodyText.size() + bodyLine.size() > bodySpace)
	{
	    document += makePage(headerText, bodyText, footerText, bodySpace);
	    bodyText.clear();
	    bodyText += bodyLine;
	}
	else
	{
	    bodyText += bodyLine;
	}
    }
    if (m_printer != 0) {
        m_printer->print(document.toStdString(),QTextDocument());
    }
    QDialog::accept();
}

TagDAO::Index VetReportDialogBase::getIndex()
{   
    QString indexText = ui->indexComboBox->currentText().stripWhiteSpace();
    TagDAO::Index index = TagDAO::Record;
    
    if(indexText == "Record Number")
    {
	index = TagDAO::Record;
    }
    else if(indexText == "Age")
    {
	index = TagDAO::Age;
    }
    else if(indexText == "Allflex")
    {
	index = TagDAO::PlasticTag;
    }
    else if(indexText == "Breed")
    {
	index = TagDAO::Breed;
    }
    
    return index;
}

void VetReportDialogBase::initTagVector()
{   
    TagDAO::Index index = getIndex();
    QString showText = ui->showComboBox->currentText().stripWhiteSpace();
    
    bool showDeleted = false;
    bool showNonDeleted = false;
    
    if(showText == "All")
    {
	showDeleted = true;
	showNonDeleted = true;
    }
    else if(showText == "Deleted")
    {
	showDeleted = true;
    }
    else if(showText == "Non-Deleted")
    {
	showNonDeleted = true;
    }
    else
    {
	cerr << "Nothing selected for printing(" << showText.toStdString() << ")" << endl;
    }
    
    tagVector = tagDao.getTagVector(index, showDeleted, showNonDeleted,
				    ui->firstRecordComboBox->currentText().toStdString(), ui->lastRecordComboBox->currentText().toStdString());
    currentTag = 0;
}

QStringList VetReportDialogBase::nextBodyLine(bool* last)
{
    QStringList result;
    if(last != NULL)
    {
	*last = false;
    }
    
    if(currentTag >= tagVector.size() - 1 && last != NULL)
    {
	*last = true;
    }
    
    if(0 <= currentTag && currentTag < tagVector.size())
    {
	result = tagLine(tagVector[currentTag]);
	currentTag++;
    }
    
    return result;
}

QStringList VetReportDialogBase::tagLine(Tag t)
{
    return QStringList();
}

void VetReportDialogBase::headerCursorMoved(int para, int pos)
{
    ui->headerRowDisplay->setText(QString::number(para + 1));
    ui->headerColDisplay->setText(QString::number(pos + 1));
    
    setup.set(headerColKey(), QString::number(pos).toStdString());
    setup.set(headerRowKey(), QString::number(para).toStdString());
}

void VetReportDialogBase::footCursorMoved(int para, int pos)
{    
    ui->footerRowDisplay->setText(QString::number(para + 1));
    ui->footerColDisplay->setText(QString::number(pos + 1));
}

void VetReportDialogBase::setIndexRange()
{
    TagDAO::Index index = getIndex();
    
    vector<string> range = tagDao.getIndexRange(index);
    
    QStringList rangeStringList;
    
    for(unsigned i = 0; i < range.size(); i++)
    {
	rangeStringList += QString::fromStdString(range[i]);
    }
    
    ui->firstRecordComboBox->clear();
    ui->firstRecordComboBox->insertStringList(rangeStringList);
    
    ui->lastRecordComboBox->clear();
    ui->lastRecordComboBox->insertStringList(rangeStringList);
    
    if(range.size() > 0)
    {
	ui->firstRecordComboBox->setCurrentItem(0);
	ui->lastRecordComboBox->setCurrentItem(range.size() - 1);
    }
}

void VetReportDialogBase::importText(int index)
{
    if(index == 0)
    {
	importDailyBuyerText();
    }
    else if(index == 1)
    {
	importPermBuyerText();
    }
}

void VetReportDialogBase::importDailyBuyerText()
{
    TableBrowserDialog tableBrowser(this);
    
    vector<Buyer>  buyerVector = BuyerDAO::getCustomerList();    
    QStringList buyerMenu;
    
    for(unsigned i = 0; i < buyerVector.size(); i++)
    {
	buyerMenu += QString::fromStdString(buyerVector[i].getName().getLast()).leftJustify(19, ' ', true) + " Of: " + QString::fromStdString(buyerVector[i].getCompany()).leftJustify(19, ' ', true);
    }
    
    tableBrowser.init(buyerMenu);
    
    if(tableBrowser.exec() == QDialog::Accepted)
    {
	int index = tableBrowser.selectedIndex();
	
	if(0 <= index && index < buyerVector.size())
	{
	    QStringList text;
	    text += QString::fromStdString(buyerVector[index].getName().getLast());
	    text += QString::fromStdString(buyerVector[index].getAddress().getAddress1());
	    text += QString::fromStdString(buyerVector[index].getAddress().getAddress2());
	    text += QString::fromStdString(buyerVector[index].getAddress().cityStateZipStr());
	    
	    insertText(text);
	}
    }
}

void VetReportDialogBase::importPermBuyerText()
{
    bool ok = false;
    QString filter = QInputDialog::getText ("Enter at least 3 letters", "Enter at least 3 letters of the name", QLineEdit::Normal, "", &ok, this, NULL );
		     
    if(ok)
    {
	PermSearchDialog permDialog(this);
	permDialog.init(filter, Customer::Buyer);
	if(permDialog.exec() == QDialog::Accepted)
	{
	    Buyer buyer = permDialog.getSelectedCustomer();
	    QStringList text;
	    text += QString::fromStdString(buyer.getName().getLast());
	    text += QString::fromStdString(buyer.getAddress().getAddress1());
	    text += QString::fromStdString(buyer.getAddress().getAddress2());
	    text += QString::fromStdString(buyer.getAddress().cityStateZipStr());
	    insertText(text);
	}
    }
}

void VetReportDialogBase::insertText(QStringList insert)
{
    QStringList existing = QStringList::split("\n", ui->headerEdit->text(), true);
    
    int para = 0, pos=0;
    
    ui->headerEdit->getCursorPosition(&para, &pos);

    if(para == 0 && pos == 0)
    {
	cerr << "Can't insert text at row 0, column 0" << endl;
	return;
    }
    
   for(int i = 0; i < insert.size(); i++)
    {
       int actualPara = para + i;
       
       if(!(actualPara < existing.size()))
       {
	   existing += "";
       }
        
       existing[actualPara] = existing[actualPara].leftJustify(pos, ' ', true);
       existing[actualPara] += insert[i];
       
   }
   
   ui->headerEdit->setText(existing.join("\n"));
   ui->headerEdit->setCursorPosition(para, pos);
}

