//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add ui->setupUi(this);
//   Add delete ui;
//   delete moc include at end

#include "auctionimportdialog.h"
#include "ui_auctionimportdialog.h"

#include <qvariant.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qcombobox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

#include "sys/stat.h"
#include <QProgressDialog>
#include <QFileDialog>
#include "zlib.h"

AuctionImportDialog::AuctionImportDialog( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl ), ui(new Ui::AuctionImportDialog)
{
    ui->setupUi(this);

    // signals and slots connections
    connect( ui->browseButton, SIGNAL( clicked() ), this, SLOT( getFileNameToImport() ) );
    connect( ui->scriptButton, SIGNAL( clicked() ), this, SLOT( createScript() ) );

    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
AuctionImportDialog::~AuctionImportDialog()
{
    delete ui;
}

void AuctionImportDialog::init()
{
    lastPath = getenv("HOME");
}

///////////////////////////////////////////////////////////////////////////////
//
// name: importPermanant()
//
// purpose: imports a permanant seller or buyer list from an auction 4 text dump
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
void AuctionImportDialog::importPermanant()
{
    struct stat fileStat;
    string fileName = ui->pathEdit->text().toStdString();
    stat(fileName.c_str(), &fileStat);

    ifstream inputFile(fileName.c_str());
    bool alteredRecord;
    Customer temp;
    QProgressDialog pd(this);
    pd.setModal(true);
    pd.setMaximum(fileStat.st_size);
    pd.show();
    int lineLength;
    int totalProgress = 0;
    while(!inputFile.eof())
    {
        switch(ui->fileTypeCombo->currentItem())
        {
        case 0:
        default:
            temp = getCustomerFromFile(inputFile, alteredRecord, lineLength);
            break;

        case 1:
            temp = getBuyerFromFile(inputFile, lineLength);
            alteredRecord = true;
            break;
        }

        totalProgress += lineLength;
        pd.setValue(totalProgress);
        if(lineLength > 5 && temp.getName().getLast() != "")
        {
            CustomerDAO::saveCustomer(temp, Customer::Seller, alteredRecord);
        }
    }

    inputFile.close();
}


///////////////////////////////////////////////////////////////////////////////
//
// name: createScript()
//
// purpose: creates an import script from an auction 4 text dump
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
void AuctionImportDialog::createScript()
{
    switch(ui->fileTypeCombo->currentItem())
    {
    case 0:
    case 1:
        createCustomerImportScript();
        break;

    case 2:
        createCheckImportScript();
        break;

    case 3:
        createHistoryImportScript();
    default:
        break;
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// name: importFile()
//
// purpose: imports a file from an auction 4 text dump
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
void AuctionImportDialog::importFile()
{
    switch(ui->fileTypeCombo->currentItem())
    {
    case 0:
    case 1:
        importPermanant();
        break;

    default:
        break;
    }
}

///////////////////////////////////////////////////////////////////////////////
//
// name: createCustomerImportScript()
//
// purpose: creates an import script from an auction 4 text dump of a seller
//          permanant list or buyer permanant list
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
void AuctionImportDialog::createCustomerImportScript()
{
    struct stat inFileStat;
    stat(ui->pathEdit->text().ascii(), &inFileStat);
    ifstream inputFile(ui->pathEdit->text().ascii());

    string defaultFileName = string("/recovered_") + string(ui->fileTypeCombo->currentItem() == 0 ? "sellers" : "buyers") + string(".sql.gz");
    QString path = lastPath;
    path = QFileDialog::getSaveFileName(path + QString::fromStdString(defaultFileName), "Auction Restore/Update file (*.sql.gz )", this,
                                        "Choose the location to save the script file");

    if(path == QString::null)
    {
        return;
    }

    lastPath = QDir(path).path();
    gzFile outputFile = gzopen(path.ascii(), "w");
    Customer temp;
    bool alteredRecord;
    string outputLine;
    char alteredStr[10];
    char typeStr[10];
    char madCowStr[10];
    char mailingListStr[10];
    char beefCouncilStr[10];


    int lineLength, totalProgress = 0;

    QProgressDialog pd(this);
    pd.setMaximum(inFileStat.st_size);
    pd.setModal(true);
    pd.show();
    Customer::Type type;
    while(!inputFile.eof())
    {
        switch(ui->fileTypeCombo->currentItem())
        {
        case 0:
        default:
            temp = getCustomerFromFile(inputFile, alteredRecord, lineLength);
            type = Customer::Seller;
            break;

        case 1:
            temp = getBuyerFromFile(inputFile, lineLength);
            alteredRecord = true;
            type = Customer::Buyer;
            break;
        }

        sprintf(typeStr, "%d", type);
        totalProgress += lineLength;
        pd.setValue(totalProgress);
        sprintf(alteredStr, "%d", alteredRecord);
        sprintf(madCowStr, "%d", temp.isMadCowCertified());
        sprintf(beefCouncilStr, "%d", temp.isBeefCouncil());
        sprintf(mailingListStr, "%d", temp.isOnMailingList());
//TODO  !!!
        outputLine =
            "INSERT INTO customer SET id=0, name = '" + DatabaseManager::defaultManager.escape_string(temp.getName().getLast()) +"', "
            "address1='" + DatabaseManager::defaultManager.escape_string(temp.getAddress().getAddress1()) + "', "
            "address2='" + DatabaseManager::defaultManager.escape_string(temp.getAddress().getAddress2()) + "', "
            "city='" + DatabaseManager::defaultManager.escape_string(temp.getAddress().getCity()) + "', "
            "state='" + DatabaseManager::defaultManager.escape_string(temp.getAddress().getState()) + "', "
            "zip='" + DatabaseManager::defaultManager.escape_string(temp.getAddress().getZip()) + "', "
            "phone='" + DatabaseManager::defaultManager.escape_string(temp.getContactList().getFirstPhone()) + "', "
            "ssn='" + DatabaseManager::defaultManager.escape_string(temp.getSocialSecurityNumber()) + "', "
            "credit_card='" + DatabaseManager::defaultManager.escape_string(temp.getCreditCardNumber()) + "', "
            "county='" + DatabaseManager::defaultManager.escape_string(temp.getAddress().getCounty()) + "', "
            "comment='" + DatabaseManager::defaultManager.escape_string(temp.getComment()) + "', "
            "mad_cow=" + string(madCowStr) + ", "
            "mailing_list=" + string(mailingListStr) + ", "
            "beef_council=" + string(beefCouncilStr) + ", "
            "company='" + DatabaseManager::defaultManager.escape_string(temp.getCompany()) + "',  "
            "altered=" + string(alteredStr) + ", "
            "type=" + string(typeStr) + ", "
            "perm_number='" + temp.getNumber() + "';\n";

        if(lineLength > 5)
        {
            gzwrite(outputFile, outputLine.c_str(), outputLine.length());
        }
    }

    gzclose(outputFile);
    inputFile.close();
}


///////////////////////////////////////////////////////////////////////////////
//
// name: getCustomerFromFile(ifstream&, bool&, int&)
//
// purpose: retrieves a permanant record from a file
//
// calling params: ifstream& inputFile       - A reference to the file where
//                                             the record will be read from
//                 bool& alteredRecord       - A reference to a variable that
//                                             will show whether the current
//                                             record should be saved as an
//                                             altered record.
//                 int& lineLength           - A reference to a variable that
//                                             will show the caller how
//                                             long the line was that had the
//                                             last record
//
// return params: Customer                   - A customer record
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
Customer AuctionImportDialog::getCustomerFromFile(ifstream& inputFile, bool& alteredRecord, int& lineLength)
{
    string name, address1, address2, city, mortgage, areacode, phone, ssn, county;
    string zip, state;
    string lineText;

    bool madCow;
    bool beefCouncil;
    bool mailingList;



    if(inputFile.eof())
    {
        return Customer();
    }

    getline(inputFile, lineText);
    lineLength = lineText.length();
    QString flags;

    switch(lineText.size())
    {
    case 330:
        name = QString::fromStdString(lineText.substr(0, 32)).stripWhiteSpace().ascii();
        address1 = QString::fromStdString(lineText.substr(33, 32)).stripWhiteSpace().ascii();
        address2 = QString::fromStdString(lineText.substr(66,32)).stripWhiteSpace().ascii();

        extractCityStateZip(lineText.substr(99, 32), city, state, zip);

        mortgage = QString::fromStdString(lineText.substr(132, 32)).stripWhiteSpace().ascii();
        areacode = "";//QString(lineText.substr(165, 5)).stripWhiteSpace().ascii();
        phone = QString::fromStdString(lineText.substr(165, 32)).stripWhiteSpace().ascii();
        ssn = QString::fromStdString(lineText.substr(198, 32)).stripWhiteSpace().ascii();
        county = QString::fromStdString(lineText.substr(231, 32)).stripWhiteSpace().ascii();

        flags = QString::fromStdString(lineText.substr(264, 32));
        alteredRecord = (flags.stripWhiteSpace().length() == 0);
        madCow = false;
        beefCouncil = false;
        mailingList = false;

//    madCow = ((flags.toInt() & 0x0008) == 0x0008);
//    beefCouncil = !((flags.toInt() & 0x0010) == 0x0010);
//    mailingList = ((flags.toInt() & 0x0020) == 0x0020);
        break;

    case 344:
    case 348:
        name = QString::fromStdString(lineText.substr(0, 32)).stripWhiteSpace().ascii();
        address1 = QString::fromStdString(lineText.substr(33, 32)).stripWhiteSpace().ascii();
        address2 = QString::fromStdString(lineText.substr(66,32)).stripWhiteSpace().ascii();
        extractCityStateZip(lineText.substr(99, 32), city, state, zip);
        mortgage = QString::fromStdString(lineText.substr(132, 32)).stripWhiteSpace().ascii();
        areacode = QString::fromStdString(lineText.substr(165, 5)).stripWhiteSpace().ascii();
        phone = QString::fromStdString(lineText.substr(170, 8)).stripWhiteSpace().ascii();
        ssn = QString::fromStdString(lineText.substr(179, 32)).stripWhiteSpace().ascii();
        county = QString::fromStdString(lineText.substr(212, 32)).stripWhiteSpace().ascii();
        flags = QString::fromStdString(lineText.substr(311, 32));
        alteredRecord = ((flags.toInt() & 0x0001) == 0x0001);
        madCow = ((flags.toInt() & 0x0008) == 0x0008);
        beefCouncil = !((flags.toInt() & 0x0010) == 0x0010);
        mailingList = ((flags.toInt() & 0x0020) == 0x0020);
        break;

    case 351:
        name = QString::fromStdString(lineText.substr(0, 32)).stripWhiteSpace().ascii();
        address1 = QString::fromStdString(lineText.substr(33, 32)).stripWhiteSpace().ascii();
        address2 = QString::fromStdString(lineText.substr(66,32)).stripWhiteSpace().ascii();
        extractCityStateZip(lineText.substr(99, 32), city, state, zip);
        mortgage = QString::fromStdString(lineText.substr(132, 32)).stripWhiteSpace().ascii();
        areacode = QString::fromStdString(lineText.substr(165, 3)).stripWhiteSpace().ascii();
        phone = areacode + QString::fromStdString(lineText.substr(169, 7)).stripWhiteSpace().ascii();
        ssn = QString::fromStdString(lineText.substr(186, 32)).stripWhiteSpace().ascii();
        county = QString::fromStdString(lineText.substr(219, 32)).stripWhiteSpace().ascii();
        flags = QString::fromStdString(lineText.substr(318, 32));
        alteredRecord = ((flags.toInt() & 0x0001) == 0x0001);
        madCow = ((flags.toInt() & 0x0008) == 0x0008);
        beefCouncil = !((flags.toInt() & 0x0010) == 0x0010);
        mailingList = ((flags.toInt() & 0x0020) == 0x0020);
        break;

    case 363:
        name = QString::fromStdString(lineText.substr(0, 32)).stripWhiteSpace().ascii();
        address1 = QString::fromStdString(lineText.substr(33, 32)).stripWhiteSpace().ascii();
        address2 = QString::fromStdString(lineText.substr(66,32)).stripWhiteSpace().ascii();
        extractCityStateZip(lineText.substr(99, 32), city, state, zip);
        mortgage = QString::fromStdString(lineText.substr(132, 32)).stripWhiteSpace().ascii();
        //areacode = QString(lineText.substr(165, 32)).stripWhiteSpace().ascii();
        phone = QString::fromStdString(lineText.substr(165, 32)).stripWhiteSpace().ascii();
        ssn = QString::fromStdString(lineText.substr(198, 32)).stripWhiteSpace().ascii();
        county = QString::fromStdString(lineText.substr(231, 32)).stripWhiteSpace().ascii();
        flags = QString::fromStdString(lineText.substr(330, 32));
        alteredRecord = ((flags.toInt() & 0x0001) == 0x0001);
        madCow = ((flags.toInt() & 0x0008) == 0x0008);
        beefCouncil = !((flags.toInt() & 0x0010) == 0x0010);
        mailingList = ((flags.toInt() & 0x0020) == 0x0020);
        break;

    case 165:
        name = QString::fromStdString(lineText.substr(0, 32)).stripWhiteSpace().ascii();
        address1 = QString::fromStdString(lineText.substr(33, 32)).stripWhiteSpace().ascii();
        address2 = QString::fromStdString(lineText.substr(66,32)).stripWhiteSpace().ascii();
        extractCityStateZip(lineText.substr(99, 32), city, state, zip);
        mortgage = QString::fromStdString(lineText.substr(132, 32)).stripWhiteSpace().ascii();
        break;

    default:
    {
        cerr << "Invalid record format, " << lineText.length() << " columns" << endl;
        return Customer();
        break;
    }
    }

    return Customer(0, Name(name), Address(address1, address2,city,state,zip, "", county), ContactList(phone),
                    "", ssn, "", "", madCow, beefCouncil, mailingList, mortgage);
}


///////////////////////////////////////////////////////////////////////////////
//
// name: getBuyerFromFile(ifstream&, int&)
//
// purpose: Gets a buyer record from an input file
//
// calling params: ifstream& inputFile     - A reference to the file to be read
//                 int& lineLength         - A reference to a variable that will
//                                           hold the length of the line just read
//
// return params: Customer                 - A Permanant record
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
Customer AuctionImportDialog::getBuyerFromFile(ifstream& inputFile, int& lineLength)
{
    string lineText;
    Customer temp;
    if(!inputFile.eof())
    {
        getline(inputFile, lineText);
        lineLength = lineText.size();

        if(lineLength != 208 && lineLength != 154)
        {
            cerr << "Invalid import format, expected: 208 or 154 columns, got: " << lineLength << " columns" << endl;
            return temp;
        }

        string name, address1, address2, city, state, zip, phone, number, cardNo, company;

        switch(lineLength)
        {
        case 208:
            number = QString::fromStdString(lineText.substr(0, 10)).stripWhiteSpace().ascii();
            name = QString::fromStdString(lineText.substr(11, 32)).stripWhiteSpace().ascii();
            address1 = QString::fromStdString(lineText.substr(44, 32)).stripWhiteSpace().ascii();
            address2 = QString::fromStdString(lineText.substr(77, 32)).stripWhiteSpace().ascii();
            extractCityStateZip(lineText.substr(110, 32), city, state, zip);
            cardNo = QString::fromStdString(lineText.substr(143, 10)).stripWhiteSpace().ascii();
            phone = QString::fromStdString(lineText.substr(154, 20)).stripWhiteSpace().ascii();
            company= QString::fromStdString(lineText.substr(175, 32)).stripWhiteSpace().ascii();

            break;

        case 154:
            number = QString::fromStdString(lineText.substr(0, 10)).stripWhiteSpace().ascii();
            name = QString::fromStdString(lineText.substr(11, 32)).stripWhiteSpace().ascii();
            address1 = QString::fromStdString(lineText.substr(44, 32)).stripWhiteSpace().ascii();
            address2 = QString::fromStdString(lineText.substr(77, 32)).stripWhiteSpace().ascii();
            extractCityStateZip(lineText.substr(110, 32), city, state, zip);
            cardNo = QString::fromStdString(lineText.substr(143, 10)).stripWhiteSpace().ascii();
            phone = "";
            company = "";
            break;

        default:
            return temp;
            break;
        }

        temp =  Customer(0, Name(name), Address(address1, address2, city, state, zip), ContactList(phone),
                         number, "", cardNo, "", false, false, false, company);
    }

    return temp;
}


///////////////////////////////////////////////////////////////////////////////
//
// name: extractCityStateZip(string, string&, string&, string&)
//
// purpose: Attempts to seperate the city/state/zip field found in some formats
//          into a city field, a state field, and a zip code field
//
// calling params: string cityStZipStr   - The string that holds the formatted
//                                         city, state zip string.
//                 string& city          - A reference to the variable in which
//                                         the city portion will be stored
//                 string& state         - A reference to the variable in which
//                                         the state portion will be stored
//                 string& zip           - A reference to the variable in which
//                                         the zip portion will be stored
//
// return params:
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
void AuctionImportDialog::extractCityStateZip(string cityStZipStr, string& city, string& state, string& zip)
{
    QStringList cityStZip;
    cityStZip = QStringList::split(' ', QString::fromStdString(cityStZipStr));
    city = state = zip = "";

    if(cityStZip.size() >= 2)
    {
        zip = cityStZip[cityStZip.size() - 1].stripWhiteSpace().ascii();
        state = cityStZip[cityStZip.size() - 2].stripWhiteSpace().ascii();

        for(unsigned int i = 0; i < cityStZip.size() - 2; i++)
        {
            if(cityStZip[i].endsWith(","))
            {
                cityStZip[i] = cityStZip[i].left(cityStZip[i].length() - 1);
            }

            city += string(cityStZip[i].ascii()) + string(" ");
        }
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// name: getFileNameToImport()
//
// purpose: prompts the user for a file name with a file dialog
//
// calling params: void
//
// return params: void
//
// Notes: Defaults to the user's home directory
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
void AuctionImportDialog::getFileNameToImport()
{
    QString path = lastPath;
    path = QFileDialog::getOpenFileName(path + "/", "Auction 4 comma delimited file export (*.txt)");


    if(path != QString::null)
    {
        ui->pathEdit->setText(path);
        lastPath = QDir(path).path();
    }
}

///////////////////////////////////////////////////////////////////////////////
//
// name: createCheckImportScript()
//
// purpose: creates an import script for the check register from an auction 4
//          comma delimited text dump of the check register
//
// calling params: void
//
// return params: void
//
// Notes: Due to the changing nature of past versions of the auction 4
//        program. The particular format of the output file might not
//        be readable by this routine. To add a file format. Add the new
//        line length in the switch statement, split the string
//        appropriately in getCheckFromFile()
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
void AuctionImportDialog::createCheckImportScript()
{
    struct stat fileStat;
    string fileName = ui->pathEdit->text().toStdString();
    stat(fileName.c_str(), &fileStat);

    QString path = lastPath;
    path = QFileDialog::getSaveFileName(path + "/recovered_checkreg.sql.gz",
                                        "Auction Restore/Update file (*.sql.gz )", this,
                                        "Choose the location to save the script file");

    if(path == QString::null)
    {
        return;
    }

    lastPath = QDir(path).path();
    gzFile outputFile = gzopen(path.ascii(), "w");

    ifstream inputFile(fileName.c_str());
    int lineLength;
    int totalLength = 0;
    QProgressDialog checkFileProgress(this);
    checkFileProgress.setModal(true);
    checkFileProgress.setMaximum(fileStat.st_size);
    string outputLine;
    Check temp;
    char numberStr[20];
    char amountStr[30];
    char statusStr[30];
    char typeStr[30];
    checkFileProgress.show();
    while(!inputFile.eof())
    {
        temp = getCheckFromFile(inputFile, lineLength);

        if(lineLength > 5)
        {
            totalLength += lineLength;
            checkFileProgress.setValue(totalLength);

            sprintf(numberStr, "%ld", temp.getNumber());
            sprintf(amountStr, "%0.2f", temp.getAmount());
            sprintf(statusStr, "%d", temp.getStatus());
            sprintf(typeStr, "%d", Check::Unknown);

            outputLine =
                "INSERT INTO checkreg SET "
                "number=" + string(numberStr) + ", "
                "amount=" + string(amountStr) + ", "
                "status=" + string(statusStr) + ", "
                "comment='" + DatabaseManager::defaultManager.escape_string(temp.getComment()) +"', "
                "date='" + temp.getDate().toString("YYYY-mm-dd") + "', "
                "invoice_id=0, "
                "payee='" + DatabaseManager::defaultManager.escape_string(temp.getPayee()) + "', "
                "id=0, "
                "type=" + string(typeStr) + ";\n";

            gzwrite(outputFile, outputLine.c_str(), outputLine.length());
        }
    }

    gzclose(outputFile);
    inputFile.close();
}


///////////////////////////////////////////////////////////////////////////////
//
// name: importChecks()
//
// purpose: imports a comma delimited text dump of the check register from the
//          auction 4 program into the database
//
// calling params: void
//
// return params: void
//
// Notes: NOT USED
//
// Todo: Actually do something with this
//
///////////////////////////////////////////////////////////////////////////////
void AuctionImportDialog::importChecks()
{
}


///////////////////////////////////////////////////////////////////////////////
//
// name: getCheckFromFile(ifstream&, int&);
//
// purpose: retrieves check record from a comma delimited text dump of the
//          check register from auction 4xx
//
// calling params: ifstream& inputFile   - A reference to the file to be read
//                 int& lineLength       - A reference to a variable to store
//                                         the length of the last line read.
// return params:
//
// Notes:
//
// Todo:
//
///////////////////////////////////////////////////////////////////////////////
Check AuctionImportDialog::getCheckFromFile(ifstream& inputFile, int& lineLength)
{
    Check temp;
    string lineText;
    getline(inputFile, lineText);
    lineLength = lineText.length();

    long number;
    string payee;
    double amount;
    Date date;
    Check::STATUS status = Check::Void;
    Check::Type type = Check::Unknown;
    string comment;
    long invoiceId = 0;
    char statusChar;
    int statusCode;

    switch(lineText.length())
    {
    case 98:    // auction 434 file
        number = atol(lineText.substr(11, 10).c_str());
        payee = QString::fromStdString(lineText.substr(22, 55)).stripWhiteSpace().ascii();
        amount = atof(lineText.substr(78, 10).c_str());
        date = Date::fromString(lineText.substr(0, 10), "YYYYmmdd");
        statusChar = lineText.substr(89,1)[0];

        switch(statusChar)
        {
        case 'O':
            status = Check::Out;
            break;

        case 'C':
        default:
            status = Check::Cleared;
            break;

        case 'V':
            status = Check::Void;
            break;
        }
        break;

        if(lineText.substr(91, 4) != "CHK ")
        {
            lineLength = 0;
        }
        break;

    case 95:      // auction 43 file
    case 94:
        number = atol(lineText.substr(11, 10).c_str());
        payee = QString::fromStdString(lineText.substr(22, 55)).stripWhiteSpace().ascii();
        amount = atof(lineText.substr(78, 10).c_str());
        statusCode = atoi(lineText.substr(89, 1).c_str());
        switch(statusCode)
        {
        case 0:
            status = Check::Out;
            break;

        case 1:
            status = Check::Cleared;
            break;

        case 2:
            status = Check::Void;
            break;
        }
        date = Date::fromString(lineText.substr(0, 10), "YYYYmmdd");
        break;

    default:
        cerr << "Unrecognized format: " << lineText.length() << " columns in line" << endl;
        cout << lineText << endl;
        lineLength = 0;
        break;
    }

    temp = Check(0, number, payee, amount, status, date, comment, type, invoiceId);

    return temp;
}


void AuctionImportDialog::createHistoryImportScript()
{

    struct stat fileStat;
    string fileName = ui->pathEdit->text().toStdString();
    stat(fileName.c_str(), &fileStat);

    QString path = lastPath;
    path = QFileDialog::getSaveFileName(path + "/recovered_history.sql.gz",
                                        "Auction Restore/Update file (*.sql.gz )", this,
                                        "Choose the location to save the script file");

    if(path == QString::null)
    {
        return;
    }

    lastPath = QDir(path).path();

    gzFile outputFile = gzopen(path.ascii(), "w");
    ifstream inputFile(fileName.c_str());
    int lineLength;
    int totalLength = 0;
    QProgressDialog historyFileProgress(this);
    historyFileProgress.setModal(true);
    historyFileProgress.setMaximum(fileStat.st_size);
    string outputLine;

    historyFileProgress.show();
    HistoryItem temp;

    while(!inputFile.eof())
    {
        temp = getHistoryFromFile(inputFile, lineLength);

        if(lineLength > 5)
        {
            totalLength += lineLength;
            historyFileProgress.setValue(totalLength);

            outputLine =
                "INSERT INTO history SET "
                "date='" + temp.getDate().toString("YYYY-mm-dd")  + "', "
                "transaction_id=" + QString::number(temp.getTransactionNo()).ascii() + ", "
                "seller_number='" + DatabaseManager::defaultManager.escape_string(temp.getSellerNo()) + "', "
                "seller_name='" + DatabaseManager::defaultManager.escape_string(temp.getSellerName()) + "', "
                "buyer_number='" + DatabaseManager::defaultManager.escape_string(temp.getBuyerNo()) + "', "
                "buyer_name='" + DatabaseManager::defaultManager.escape_string(temp.getBuyerName()) + "', "
                "head=" + QString::number(temp.getHead()).ascii() + ", "
                "weight=" + QString::number(temp.getWeight()).ascii() + ", "
                "description='" + temp.getCode().toString() + "', "
                "price=" + QString::number(temp.getBid()).ascii() + ", "
                "tags='', "
                "mode=" + QString::number(int(temp.getMode())).ascii() + ", "
                "weighmaster='" + DatabaseManager::defaultManager.escape_string(temp.getWeighmaster()) + "' "
                ";\n";

            gzwrite(outputFile, outputLine.c_str(), outputLine.length());
        }
    }

    gzclose(outputFile);
    inputFile.close();
}

HistoryItem AuctionImportDialog::getHistoryFromFile(ifstream& inputFile, int& lineLength)
{
    string line;

    getline(inputFile, line);

    lineLength = line.length();

    Date date;
    long transactionId;
    string sellerNumber;
    string sellerName;
    string buyerNumber;
    string buyerName;
    long head;
    long weight;
    AnimalCode code;

    double price;
    string tags;
    Transaction::SALE_MODE mode;
    string weighMaster;

    HistoryItem result;
    switch(lineLength)
    {
    case 246:
    case 247:
        date = Date::fromString(line.substr(0, 8), "yyyymmdd");
        transactionId = atol(line.substr(16, 6).c_str());
        sellerNumber = line.substr(23, 10);
        sellerName = line.substr(34, 32);
        buyerNumber = line.substr(67, 10);
        buyerName = line.substr(78, 32);
        head = atol(line.substr(111, 4).c_str());
        weight = atol(line.substr(118, 5).c_str());

        code = AnimalCode::fromString(QString::fromStdString(line.substr(129, 6)).stripWhiteSpace().toStdString());

        price = atof(line.substr(140, 8).c_str());
        mode = Transaction::SALE_MODE(atoi(line.substr(231, 1).c_str()));
        weighMaster = line.substr(236, 3);
        result = HistoryItem(date, transactionId,
                             sellerNumber, sellerName,
                             buyerNumber, buyerName,
                             head, weight, code, price, mode, weighMaster);
        break;

    default:
        cerr << "Invalid history record format(" << lineLength << ")" << endl;
        break;
    case 0:
        break;
    }

    return result;
}
