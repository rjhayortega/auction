//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add delete ui;
//   delete moc include at end

#include "vetdialog.h"
#include "ui_vetdialog.h"

#include <QVariant>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qgroupbox.h>
#include <qcombobox.h>
#include <qlineedit.h>
#include <qdatetimeedit.h>
#include <qspinbox.h>
#include <qcheckbox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

#include "tablebrowserdialog.h"
#include <qmessagebox.h>
#include <qvalidator.h>
#include <iostream>
#include "types/healthrecord.h"
#include "reports/minnesotavetcertificate.h"
#include "reports/brucellosistestrecord.h"
#include "reports/southdakotahealthcertificate.h"
#include "tablebrowserdialog.h"
#include "previewdialog.h"
#include "reports/allflexreport.h"
#include <q3listbox.h>
#include <qprocess.h>
#include "vetformmetricsdialog.h"
#include "vetdatadialog.h"
#include "vetreportdialog.h"
#include "printerfactory.h"


VetDialog::VetDialog( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl ), ui(new Ui::VetDialog)
{
    m_printer = 0;
    ui->setupUi(this);
    // signals and slots connections
    connect( ui->nextButton, SIGNAL( clicked() ), this, SLOT( loadNextTag() ) );
    connect( ui->prevButton, SIGNAL( clicked() ), this, SLOT( loadPreviousTag() ) );
    connect( ui->sexEdit, SIGNAL( lostFocus() ), this, SLOT( validateSex() ) );
    connect( ui->addRecordButton, SIGNAL( clicked() ), this, SLOT( setupTagToAdd() ) );
    connect( ui->browseButton, SIGNAL( clicked() ), this, SLOT( browseTags() ) );
    connect( ui->formComboBox, SIGNAL( activated(int) ), this, SLOT( printForm(int) ) );
    connect( ui->searchButton, SIGNAL( clicked() ), this, SLOT( search() ) );
    connect( ui->searchEdit, SIGNAL( returnPressed() ), this, SLOT( search() ) );
    connect( ui->indexGroupBox, SIGNAL( toggled(bool) ), this, SLOT( autoChangeIndex() ) );
    connect( ui->formMetricsButton, SIGNAL( clicked() ), this, SLOT( editFormMetrics() ) );
    connect( ui->vetEditButton, SIGNAL( clicked() ), this, SLOT( editVet() ) );
    connect( ui->auctionTagEdit, SIGNAL( lostFocus() ), this, SLOT( autoSave() ) );
    connect( ui->printerComboBox, SIGNAL( activated(const QString&) ), this, SLOT( updateVetPrinter(const QString&) ) );
    connect( ui->brucEdit, SIGNAL( textChanged(const QString&) ), this, SLOT( validateBrucellosis(const QString&) ) );

    init();
}

VetDialog::~VetDialog()
{
    delete ui;
    delete m_printer;
}

class BTagValidator : public QValidator
{
public:
    BTagValidator(QObject* parent=NULL, const char* name=0) : QValidator(parent, name) {}

    virtual QValidator::State validate(QString& string, int& position) const
    {
        if(string.length() != QString("00aaa0000").length())
        {
            return Invalid;
        }

        for(unsigned int i = 0; i < position; i++)
        {
            switch(i)
            {
            case 0:
            case 1:
            case 5:
            case 6:
            case 7:
            case 8:
                if(!string[i].isDigit())
                {
                    return Invalid;
                }
                break;

            case 2:
            case 3:
            case 4:
                if(!string[i].isLetter())
                {
                    return Invalid;
                }
                break;

            default:
                return Invalid;
                break;
            }
        }

        if(position == string.length() - 1)
        {
            return Acceptable;
        }

        return Intermediate;
    }
};

void VetDialog::init()
{
    //connect(&lpstatProc, SIGNAL(readyReadStdout()), this, SLOT(processLpstatData()));
    loadVetData();
    btagValidator = NULL;
    btagValidator = new BTagValidator(ui->brucTagEdit, "");
    //    brucTagEdit->setValidator(btagValidator);
    loadNextTag();
    ui->auctionTagEdit->setEnabled(false);
    ui->addRecordButton->hide();
    oldBrucellosisText = "";
    vet = Person(0, Name("Unknown Vet"), Address("Unknown Address",  "", "Unknown City", "Unknown State", "00000"));
    setupPrinterList();
    loadVetFormMetrics();
}

void VetDialog::initSeller(Seller seller)
{
    this->seller = seller;
    ui->auctionTagEdit->setEnabled(true);
    ui->addRecordButton->show();
    currentTag = tagDao.getNextSellerTag(Tag("", seller.getNumber()));
    showCurrentTag();
}

void VetDialog::showCurrentTag()
{
    setCaption("Edit Vet Data For Tag: " + QString::fromStdString(currentTag.getTag() + ""));
    Transaction transaction = transactionDao.getTransactionById(currentTag.getTransactionId());

    Seller consignor;

    if(seller.getId() != 0)
    {
        consignor = seller;
    }
    else
    {
        consignor = transaction.getSeller();
    }

    ui->tagCountDisplay->setText(QString::number(tagDao.tagCount(consignor) + (currentTag.getTag() == "" ? 1 : 0)));

    Buyer consignee = transaction.getBuyer();

    if(consignor.getId() == 0)
    {
        consignor = SellerDAO::loadFromNumber(currentTag.getSellerId());
    }

    QString consignorText = QString::fromStdString(
                                "" + consignor.getName().getLast() + "\n"
                                "" + consignor.getAddress().getAddress1() + "\n"
                                "" + consignor.getAddress().getAddress2() + "\n"
                                "" + consignor.getAddress().cityStateZipStr());

    QString consigneeText = QString::fromStdString(
                                "" + consignee.getName().getLast() + "\n"
                                "" + consignee.getAddress().getAddress1() + "\n"
                                "" + consignee.getAddress().getAddress2() + "\n"
                                "" + consignee.getAddress().cityStateZipStr());


    ui->consignorDisplay->setText(consignorText);
    ui->consigneeDisplay->setText(consigneeText);
    ui->auctionTagEdit->setText(QString::fromStdString(currentTag.getTag()));
    ui->breedEdit->setText(QString::fromStdString(currentTag.getBreed()));

    QDate tempDate = QDate::fromString(QString::fromStdString(currentTag.getTestDate().toString("YYYY-mm-dd")), Qt::ISODate);

    if(tempDate.isNull())
    {
        tempDate = QDate::fromString(QString::fromStdString(Date::currentDate().toString("YYYY-mm-dd")), Qt::ISODate);
    }

    ui->testDateEdit->setDate(tempDate);
    ui->sexEdit->setText(QString::fromStdString(string(1, currentTag.getSex())));
    ui->oldTagEdit->setText(QString::fromStdString(currentTag.getOldTag()));
    ui->ageSpinBox->setValue(currentTag.getAge());
    ui->recordNumberDisplay->setText(QString::number(currentTag.getId()));
    ui->deletedCheckBox->setChecked(currentTag.isDeleted());

    if(currentTag.getBurcellosisTag() == "")
    {
        ui->brucTagEdit->setText("00AAA0000");
    }
    else
    {
        ui->brucTagEdit->setText(QString::fromStdString(currentTag.getBurcellosisTag()));
    }

    ui->chvEdit->setText(QString::fromStdString(currentTag.getVaccination()));
    ui->brucEdit->setText(QString::fromStdString(currentTag.getBrucellosis()));
    ui->pregDurationEdit->setText(QString::fromStdString(currentTag.getMonthsPreg()));
    ui->commentEdit->setText(QString::fromStdString(currentTag.getComment()));

    // new 2/2/10 ***********
    ui->rfid->setText(QString::fromStdString(currentTag.getRfid()));
    QDate tempTbDate = QDate::fromString(QString::fromStdString(currentTag.getTbInjDate().toString("YYYY-mm-dd")), Qt::ISODate);
    if(tempTbDate.isNull())
    {
        tempTbDate = QDate::fromString(QString::fromStdString(Date::currentDate().toString("YYYY-mm-dd")), Qt::ISODate);
    }
    ui->tbInjDate->setDate(tempTbDate);
    // ************ new 2/2/10

    ui->testDateEdit->setFocus();
}

void VetDialog::loadNextTag()
{
    if(saveCurrentTag())
    {
        Tag temp;

        if(seller.getNumber() == "NOLOT")
        {
            temp = tagDao.getNextTag(currentTag, TagDAO::Index(ui->indexCombo->currentItem()));
        }
        else
        {
            temp = tagDao.getNextSellerTag(currentTag);
        }

        if(temp.getTag() != "")
        {
            currentTag = temp;
        }

        showCurrentTag();

        oldBrucellosisText = ui->brucEdit->text();
    }
}

void VetDialog::loadPreviousTag()
{
    if(saveCurrentTag())
    {
        Tag temp;

        if(seller.getNumber() == "NOLOT")
        {
            temp = tagDao.getPreviousTag(currentTag, TagDAO::Index(ui->indexCombo->currentItem()));
        }
        else
        {
            temp = tagDao.getPreviousSellerTag(currentTag);
        }

        if(temp.getTag() != "")
        {
            currentTag = temp;
        }
        showCurrentTag();
        oldBrucellosisText = ui->brucEdit->text();
    }
}

void VetDialog::autoSave()
{
    if(saveCurrentTag())
    {
        showCurrentTag();
        ui->brucEdit->setFocus();
    }
    else
    {
        ui->auctionTagEdit->setFocus();
        ui->auctionTagEdit->selectAll();
    }
}

void VetDialog::browseTags()
{
    vector<Tag> tagVector;

    if(seller.getNumber() == "NOLOT")
    {
        tagVector = tagDao.getTagList();
    }
    else
    {
        tagVector = tagDao.getTagList(seller);
    }


    std::sort(tagVector.begin(), tagVector.end(), Tag::compareTagsLT);
    QStringList tagList;
    for(unsigned int i = 0; i < tagVector.size(); i++)
    {
        tagList += QString::fromStdString(tagVector[i].getTag()).leftJustify(10, ' ') + " " +
                   QString::fromStdString(tagVector[i].getBurcellosisTag()).leftJustify(10, ' ') +
                   QString::fromStdString(tagVector[i].getBreed()).leftJustify(3, ' ') +
                   tagVector[i].getSex();

    }
    TableBrowserDialog tbd(this);
    tbd.setCaption("Select a tag record");

    tbd.init(tagList, ui->auctionTagEdit->text());

    if(tbd.exec() == QDialog::Accepted)
    {
        if(saveCurrentTag())
        {
            int index = tbd.selectedIndex();

            if(0 <= index && index < tagVector.size())
            {
                currentTag = tagVector[index];
                showCurrentTag();
            }
        }
    }
}

void VetDialog::printForm(int formId)
{
    if (m_printer != 0) {
        delete m_printer;
    }
    m_printer = PrinterFactory::createPrinter(ui->printerComboBox->currentText());
    ui->formComboBox->setCurrentItem(0);
    if(formId == 5)
    {
        printAllflexReport();
        return;
    }

    //loadVetData();

    if(formId != 0)
    {
        ui->formComboBox->setCurrentItem(0);
    }
    else
    {
        return;
    }

    saveCurrentTag();
    /*
        vector<Buyer> buyerList;

        Transaction transaction = transactionDao.getTransactionById(currentTag.getTransactionId());
        Seller certSeller = SellerDAO::loadFromNumber(currentTag.getSellerId());


        Buyer certBuyer = transaction.getBuyer();

        vector<Tag> tagVector;


        if(formId != 0)
        {
    	vector<Seller> sellerList = SellerDAO::getCustomerList();
    	std::sort(sellerList.begin(), sellerList.end(), Customer::compareCustomerNames);
    	QStringList sellerStringList;

    	for(unsigned int i = 0; i < sellerList.size(); i++)
    	{
    	    sellerStringList += QString(sellerList[i].getNumber()).leftJustify(15, ' ') + sellerList[i].getName().getLast();
    	}

    	TableBrowserDialog browserDialog(this);
    	browserDialog.init(sellerStringList, QString(certSeller.getNumber()).leftJustify(15, ' ') + certSeller.getName().getLast());
    	certSeller = Seller();
    	if(browserDialog.exec() == QDialog::Accepted)
    	{
    	    int index = browserDialog.selectedIndex();

    	    if(0 <= index && index < sellerList.size())
    	    {
    		certSeller = sellerList[index];
    	    }
    	    else
    	    {
    		cerr << "Seller out of bounds error" << endl;
    	    }
    	}

    	if(certSeller.getId() == 0)
    	{
    	    formComboBox->setCurrentItem(0);
    	    return;
    	}
        }

        switch(formId)
        {
        default: // do nothing
    	break;

        case 1:
        case 2:
    	buyerList = transactionDao.getBuyerList(certSeller);

    	if(buyerList.size() == 0)
    	{
    	    QMessageBox::information(this, "No Buyers", "No buyers have bought from this seller yet");
    	    return;
    	}
    	break;
        }

        if(buyerList.size() != 0)
        {
    	QStringList buyerStringList;
    	for(unsigned int i = 0; i < buyerList.size(); i++)
    	{
    	    buyerStringList += QString(buyerList[i].getNumber()).leftJustify(15, ' ') + buyerList[i].getName().getLast();
    	}

    	TableBrowserDialog browserDialog(this);
    	browserDialog.init(buyerStringList, QString(certBuyer.getNumber()).leftJustify(15, ' ') + certBuyer.getName().getLast());

    	if(!browserDialog.exec())
    	{
    	    formComboBox->setCurrentItem(0);
    	    return;
    	}

    	int index = browserDialog.selectedIndex();

    	if(0 <= index && index < buyerList.size())
    	{
    	    certBuyer = buyerList[index];
    	}
    	else
    	{
    	    formComboBox->setCurrentItem(0);
    	    return;
    	}
        }

        vector<Tag> tagList;


        switch(formId)
        {
        case 1:
        case 2:
    	tagList = tagDao.getTagList(certSeller, certBuyer);
    	break;

        default:
    	tagList = tagDao.getTagList(certSeller);
    	break;
        }

        if(tagList.size() == 0)
        {
    	switch(formId)
    	{
    	case 1:
    	case 2:
    	    QMessageBox::information(this, "No Tags",
    				     "No tags match both the selected\n"
    				     "buyer (# '" + certBuyer.getNumber() + "' ) and the selected seller (# '" + certSeller.getNumber() + "' )\n"
    				     );
    	    break;

    	default:
    	    QMessageBox::information(this, "No Tags",
    				     "No tags match the selected seller (# '" + certSeller.getNumber() + "' )");
    	    break;
    	}
    	return;
        }

    */
    /*
        vector<Tag> tagVector;

        tagVector = tagDao.getTagList();

        HealthRecord healthRecord(vet, certSeller, certBuyer, tagList);

        Address marketAddress(setup.get("genMktName"),
    			  setup.get("genMktAddress"),
    			  setup.get("genMktCity"),
    			  setup.get("genMktState"),
    			  setup.get("genMktZip"),
    			  setup.get("genMktId"));

        healthRecord.setMarketAddress(marketAddress);

        TableBrowserDialog recordBrowser(this);

        QStringList healthRecordStringList;

        for(unsigned int i = 0; i < healthRecord.size(); i++)
        {
    	healthRecordStringList += healthRecord[i].getTag() + " - " + healthRecord[i].getBurcellosisTag();
        }

        recordBrowser.init(healthRecordStringList);
        recordBrowser.setMulti(true);
        recordBrowser.setCaption("Select the tag records to include on this form");

        if(recordBrowser.exec() == QDialog::Accepted)
        {
    	vector<Tag> actualTagVector;

    	vector<int> selectedIndexVector = recordBrowser.selectedIndexVector();

    	for(unsigned i = 0; i < selectedIndexVector.size(); i++)
    	{
    	    actua
        BrucellosisReportDialog reportDialog(this);
        reportDialog.delayedInit();
        reportDialog.setPrinter(printer);
        reportDialog.exec();lTagVector.push_back(healthRecord[selectedIndexVector[i]]);
    	}

    	healthRecord.setTagVector(actualTagVector);
        }
        else
        {
    	return;
        }

        switch(formId)
        {
        case 0: // do nothing
        default:
    	break;

        case 1:      // sd veterinary certificate
    	printSouthDakotaHealthCertificate(healthRecord);
    	break;

        case 2:     // mn veterinary certificate
    	printMinnesotaVetCert(healthRecord);
    	break;

        case 3:   // brucellosis certficate
    	cellosisTestRecord(healthRecord);
    	break;

        case 4:  // tb certificate
    	printTuberculosisRecord(healthRecord);
    	break;
        }
    */

    switch(formId)
    {
    case 0:
    default:
        break;

    case 1:
        printSouthDakotaHealthCertificate();
        break;

    case 2:
        printMinnesotaVeterinaryCertificate();
        break;

    case 3: // brucellosis cert
        printBrucellosisTestRecord();
        break;

    case 4:
        printTuberculosisTestRecord();
        break;

    case 5:
        printAlternateMinnesotaVetInspection();
        break;
    }
}

void VetDialog::printSouthDakotaHealthCertificate()
{
    SouthDakotaInspectionReportDialog reportDialog(this);
    reportDialog.delayedInit();
    reportDialog.setPrinter(m_printer);
    reportDialog.exec();
}

void VetDialog::printMinnesotaVeterinaryCertificate()
{
    MinnesotaInspectionReportDialog reportDialog(this);
    reportDialog.delayedInit();
    reportDialog.setPrinter(m_printer);
    reportDialog.exec();
}

void VetDialog::printTuberculosisTestRecord()
{
    TuberculosisReportDialog reportDialog(this);
    reportDialog.delayedInit();
    reportDialog.setPrinter(m_printer);
    reportDialog.exec();
}

void VetDialog::printAlternateMinnesotaVetInspection()
{
    VetInspectionReportDialog reportDialog(this);
    reportDialog.delayedInit();
    reportDialog.setPrinter(m_printer);
    reportDialog.exec();
}

void VetDialog::printMinnesotaVetCert(HealthRecord healthRecord)
{

    QString metricsString = vetFormMetrics[1];
    QStringList metricsList = QStringList::split(":", metricsString);

    MinnesotaVetCertificate certificate(healthRecord);
    certificate.setPageLength(metricsList[1].toInt());
    certificate.text();

    printForm(&certificate, metricsList[0].toInt());
    /*
    PreviewDialog preview(this);
    preview.setReport(&certificate);
    preview.setShowPrint(true);
    preview.exec();
    */
}

void VetDialog::printTuberculosisRecord(HealthRecord record)
{
    QStringList metricsList = QStringList::split(":", vetFormMetrics[3]);
    TuberculosisRecord report(record, vet);
    report.text();
    report.setPageLength(metricsList[1].toInt());
    printForm(&report, metricsList[0].toInt());
    /*
    PreviewDialog preview(this);
    preview.setReport(&report);
    preview.setShowPrint(true);
    preview.exec();
    */
}

bool VetDialog::saveCurrentTag()
{
    int option = 0;
    if(ui->auctionTagEdit->text().length() > 0 && (seller.getNumber() != "NOLOT" || currentTag.getSellerId() != ""))
    {
        Tag backupTag = currentTag;
        currentTag.setTestDate(Date::fromString(ui->testDateEdit->date().toString("yyyy-MM-dd").toStdString(), "YYYY-mm-dd"));
        currentTag.setBreed(ui->breedEdit->text().toStdString());
        currentTag.setSex((ui->sexEdit->text().length() > 0 ? ui->sexEdit->text().upper().ascii()[0] : 'F'));
        currentTag.setOldTag(ui->oldTagEdit->text().toStdString());
        currentTag.setAge(ui->ageSpinBox->value());
        currentTag.setBurcellosisTag(ui->brucTagEdit->text().toStdString());
        currentTag.setVaccination(ui->chvEdit->text().toStdString());
        currentTag.setBrucellosis(ui->brucEdit->text().toStdString());
        currentTag.setMonthsPreg(ui->pregDurationEdit->text().toStdString());
        currentTag.setComment(ui->commentEdit->text().toStdString());
        currentTag.setTag(ui->auctionTagEdit->text().toStdString());
        currentTag.setDeleted(ui->deletedCheckBox->isChecked());
        currentTag.setRfid(ui->rfid->text().toStdString());			// new 2/2/10
        currentTag.setTbInjDate(Date::fromString(ui->tbInjDate->date().toString("yyyy-MM-dd").toStdString(), "YYYY-mm-dd"));	// new 2/2/10
        if(seller.getNumber() != "NOLOT")
        {
            currentTag.setSellerId(seller.getNumber());
        }

        QStringList validationErrors = validateEntry();

        if(validationErrors.size() > 0)
        {

            option = QMessageBox::warning(this, "! ERROR !",
                                          "This entry may not be valid for the following reasons:\n" +
                                          validationErrors.join("\n"), "Continue anyway", "Edit Entry", "Exit Vet Without Saving");

            if(option == 2)
            {
                QDialog::reject();
            }
        }

        if(option == 0)
        {
            tagDao.saveTag(currentTag);
        }
        else
        {
            currentTag = backupTag;
        }
    }

    return (option == 0);
}

void VetDialog::reject()
{
    if(saveCurrentTag())
    {
        QDialog::reject();
    }
}

void VetDialog::accept()
{
    if(saveCurrentTag())
    {
        QDialog::accept();
    }
}

void VetDialog::validateBrucellosis(const QString& data)
{
    QString text = data.upper();

    if(text == "")
    {
        text = "0";
    }

    if(text == "0" || text == "Z")
    {
        ui->brucEdit->setText(text);
    }
    else
    {
        ui->brucEdit->setText(oldBrucellosisText);
    }

    if(ui->brucEdit->text() == "")
    {
        ui->brucEdit->setText("0");
    }

    ui->brucEdit->setCursorPosition(0);
    oldBrucellosisText = ui->brucEdit->text();
}

void VetDialog::validateSex()
{
    ui->sexEdit->setText(ui->sexEdit->text().upper());
    if(!(ui->sexEdit->hasAcceptableInput() && (ui->sexEdit->text() == "F" || ui->sexEdit->text() == "M")))
    {
        ui->sexEdit->setText("F");
    }
}

QStringList VetDialog::validateEntry()
{
    QStringList errors;

    if(!ui->brucTagEdit->hasAcceptableInput())
    {
        errors += "Brucellosis tag is not in 00AAA0000 format";
    }

    if(!(ui->sexEdit->hasAcceptableInput() && (ui->sexEdit->text() == "F" || ui->sexEdit->text() == "M")))
    {
        errors += "Sex field is not correct. It should only be 'M' or 'F'";
    }

    string conflictSellerId;
    Date conflictDate;

    if(tagDao.conflict(currentTag, conflictSellerId))
    {

        errors += QString("This tag already is already used for seller# " + QString::fromStdString(conflictSellerId) + ". Continuing will delete this tag for that seller.");
    }

    if(currentTag.getTag() == "")
    {
        errors += "There is nothing entered in the tag field, this record will not be saved";
    }

    if(currentTag.getBurcellosisTag() != "00AAA0000" && tagDao.brucellosisTagConflict(currentTag, conflictDate, conflictSellerId))
    {
        errors += "This burcellosis tag has already been used on: '" + QString::fromStdString(conflictDate.toString("mm/dd/YYYY")) + "' for seller# '" + QString::fromStdString(conflictSellerId) + "' ";
    }

    if ( currentTag.getRfid() != "" )	{
        if ( tagDao.existsRfidForSale(currentTag, currentTag.getRfid() ) )	{
            errors += "The RFID tag has already been used this sale date: '";
        }
    }

    return errors;
}

void VetDialog::setupTagToAdd()
{
    if(saveCurrentTag())
    {
        currentTag = Tag("", seller.getNumber(), 0, AnimalCode(), "00AAA0000", "HO", 'F', 0, "", "0", "", Date::currentDate(),"", "");
        showCurrentTag();
    }
}

void VetDialog::search()
{
    Tag tag = tagDao.findTag(ui->searchEdit->text().toStdString(), TagDAO::Index((ui->indexCombo->currentItem())));

    if(tag.getTag() != "")
    {
        currentTag = tag;
        oldBrucellosisText = QString::fromStdString(currentTag.getBurcellosisTag());
        showCurrentTag();
    }
}


void VetDialog::loadVetData()
{
    string vetId = setup.get("vetId");
    Name vetName = Name(setup.get("vetName"));
    vetName.setInitials(setup.get("vetInitials"));
    string vetAddress1 = setup.get("vetAddress1");
    string vetAddress2 = setup.get("vetAddress2");
    string vetCityStateZip = setup.get("vetCityStateZip");
    string vetPhone = setup.get("vetPhone");

    vet = Person(atol(vetId.c_str()), vetName, Address(vetAddress1, vetAddress2, vetCityStateZip), ContactList(vetPhone));

//    vetEdit->setText(QString::number(vet.getId()) + "\n" + vet.getName().getLast() + "\n" + vet.getName().getInitials() + "\n" + vet.getAddress().getAddress1() + "\n" +  vet.getAddress().getAddress2() + "\n" + vet.getAddress().getCity() + "\n" + vet.getContactList().getFirstPhone());
}

/*
void VetDialog::saveVetData()
{
    QStringList vetDataList = QStringList::split("\n", vetEdit->text(), true);

    setup.set("vetId", "0");
    setup.set("vetName", "");
    setup.set("vetInitials", "");
    setup.set("vetAddress1", "");
    setup.set("vetAddress2", "");
    setup.set("vetCityStateZip", "");

    if(0 < vetDataList.size())
    {
	setup.set("vetId", vetDataList[0]);
    }

    if(1 < vetDataList.size())
    {
	setup.set("vetName", vetDataList[1]);
    }

    if(2 < vetDataList.size())
    {
	setup.set("vetInitials", vetDataList[2]);
    }

    if(3 < vetDataList.size())
    {
	setup.set("vetAddress1", vetDataList[3]);
    }

    if(4 < vetDataList.size())
    {
	setup.set("vetAddress2", vetDataList[4]);
    }

    if(5 < vetDataList.size())
    {
	setup.set("vetCityStateZip", vetDataList[5]);
    }

    if(6 < vetDataList.size())
    {
	setup.set("vetPhone", vetDataList[6]);
    }
}
*/

void VetDialog::editVet()
{
    VetDataDialog(this).exec();
    loadVetData();
}

void VetDialog::printAllflexReport()
{
    vector<Seller> sellerList;

    if(seller.getNumber() == "NOLOT")
    {
        sellerList = SellerDAO::getCustomerList();
    }
    else
    {
        sellerList.push_back(SellerDAO::loadFromNumber(currentTag.getSellerId()));
    }

    for(unsigned int i = 0; i < sellerList.size(); i++)
    {
        sellerList[i].setTagList(tagDao.getTagList(sellerList[i]));
    }

    AllFlexReport report(sellerList);
    report.text();

    PreviewDialog preview(this);

    preview.setReport(&report);
    preview.setShowPrint(true);
    preview.exec();
}

void VetDialog::printBrucellosisTestRecord()
{
    BrucellosisReportDialog reportDialog(this);
    reportDialog.delayedInit();
    reportDialog.setPrinter(m_printer);
    reportDialog.exec();
}

void VetDialog::printBrucellosisTestRecord(HealthRecord record)
{
    QStringList metricsList = QStringList::split(":", vetFormMetrics[2]);
    BrucellosisTestRecord cert(record);
    cert.text();
    cert.setPageLength(metricsList[1].toInt());
    printForm(&cert, metricsList[0].toInt());

    /*
    PreviewDialog preview(this);
    preview.setReport(&cert);
    preview.setShowPrint(true);
    preview.exec();
    */
}

void VetDialog::printSouthDakotaHealthCertificate(HealthRecord record)
{
    QStringList metricsList = QStringList::split(":", vetFormMetrics[0]);

    vector<HealthRecord> recordFrames = record.frameHealthRecord(20);

    for(unsigned  int i = 0 ; i < recordFrames.size(); i++)
    {
        SouthDakotaHealthCertificate cert(recordFrames[i]);
        cert.text();
        cert.setPageLength(metricsList[1].toInt());
        printForm(&cert, metricsList[0].toInt());
        /*
        PreviewDialog preview(this);
        preview.setReport(&cert);
        preview.setShowPrint(true);
        preview.exec();
        */
    }
}

void VetDialog::autoChangeIndex()
{
    //ui->indexCombo->setCurrentItem(ui->indexCombo->currentItem() % ui->indexCombo->view()->numRows());
}

void VetDialog::printForm(TextReport* cert, int topSkip)
{
    deque<string> pageList = cert->paginatedText(topSkip);

    for(unsigned int i = 0; i < pageList.size(); i++)
    {
        m_printer->print(pageList[i],QTextDocument());
    }
}


void VetDialog::processLpstatData()
{
    //lpstatBuffer += lpstatProc.readStdout();

    QStringList menuItemCandidates = QStringList::split("\n", lpstatBuffer);
    QStringList menuItem;
    lpstatBuffer = "";

    bool printerPresent = false;
    string vetPrinter = setup.get("vetPrinter");

    for(int i = 0; i < menuItemCandidates.size(); i++)
    {
        menuItem = QStringList::split(" ", menuItemCandidates[i]);

        if(menuItem.size() > 1)
        {
            if(menuItem[0] == "printer")
            {
                printerMenu += menuItem[1];
                ui->printerComboBox->clear();
                ui->printerComboBox->insertStringList(printerMenu);

                if(QString::fromStdString(vetPrinter) == menuItem[1])
                {
                    printerPresent = true;
                }
            }
            else
            {
                lpstatBuffer += menuItemCandidates[i];
            }
        }
    }

    if(printerPresent)
    {
        ui->printerComboBox->setCurrentText(QString::fromStdString(vetPrinter));
    }
}

void VetDialog::setupPrinterList()
{
    QStringList cmdArgs;
    QString cmd;
    cmd = "lpstat";
    cmdArgs << "-p";

    printerMenu.clear();
//     lpstatProc.setArguments(cmdArgs);
//     lpstatProc.setCommunication(QProcess::Stdout);

    lpstatProc.start(cmd, cmdArgs);
    if(!lpstatProc.waitForStarted())
    {
        QMessageBox::information(this, "ERROR !", "Could not load list of available printers.");
        return;
    }
}

void VetDialog::editFormMetrics()
{
    if(VetFormMetricsDialog(this).exec() == QDialog::Accepted)
    {
        loadVetFormMetrics();
    }
}

void VetDialog::loadVetFormMetrics()
{
    vetFormMetrics = QStringList::split(";", QString::fromStdString(setup.get("vetFormMetrics")));

    for(int i = 0; i < 5; i++)
    {
        if(i >= vetFormMetrics.size())
        {
            vetFormMetrics += "0:64";
        }
    }
}

void VetDialog::sellerSummary()
{
    Seller consignor;

    if(seller.getId() == 0)
    {
        consignor = seller;
    }
    else
    {
        Transaction transaction = transactionDao.getTransactionById(currentTag.getTransactionId());
        consignor = transaction.getSeller();
    }

    vector<Tag> tagVector= tagDao.getTagList(consignor);
}


void VetDialog::updateVetPrinter(const QString& vetPrinter)
{
    setup.set("vetPrinter", vetPrinter.toStdString());
}
