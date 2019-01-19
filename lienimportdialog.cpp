//   Update to Qt4
//   Add ui(new Ui::ClassName)
//   Add ui->setupUi(this);
//   Add delete ui;
//   delete moc include at end

#include "lienimportdialog.h"
#include "ui_lienimportdialog.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qcombobox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

#include <QFileDialog>
#include <QMessageBox>

LienImportDialog::LienImportDialog( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl ), ui(new Ui::LienImportDialog)
{

    ui->setupUi(this);
    // signals and slots connections
    connect( ui->browseButton, SIGNAL( clicked() ), this, SLOT( browse() ) );
    connect( ui->importButton, SIGNAL( clicked() ), this, SLOT( importLiens() ) );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
LienImportDialog::~LienImportDialog()
{
    delete ui;
}

void LienImportDialog::init()
{
}

void LienImportDialog::timerEvent(QTimerEvent* event)
{
}

void LienImportDialog::browse()
{
    QString home = getenv("HOME");

    if(ui->stateComboBox->currentText() == "NE")
    {
        ui->lienPathEdit->setText(QFileDialog::getOpenFileName(home + "/mefscom.txt"));
    }
    else if(ui->stateComboBox->currentText() == "SD")
    {
        ui->lienPathEdit->setText(QFileDialog::getOpenFileName(home + "/stock2.asc"));
    }
    else if(ui->stateComboBox->currentText() == "ID")
    {
        ui->lienPathEdit->setText(QFileDialog::getExistingDirectory(home, this));
    }
    if(ui->stateComboBox->currentText() == "ND")
    {
        ui->lienPathEdit->setText(QFileDialog::getOpenFileName(home));
    }
}


void LienImportDialog::importLiens()
{

    if(!QFile(ui->lienPathEdit->text()).exists())
    {
        QMessageBox::information(this, "ERROR", "The file listed in the path does not exist");
        return;
    }
    bool deleteOldImports = true;
    start = time(&start);
    vector<LienRecord> lienList;

    if(ui->stateComboBox->currentText() == "NE")
    {
        lienList = getNebraskaLienList(ui->lienPathEdit->text());
    }
    else if(ui->stateComboBox->currentText() == "SD")
    {
        lienList = getSouthDakotaLienList(ui->lienPathEdit->text());
    }
    else if(ui->stateComboBox->currentText() == "ID")
    {
        lienList = getIdahoLienList(ui->lienPathEdit->text(), deleteOldImports);
    }
    else if(ui->stateComboBox->currentText() == "ND")
    {
        lienList = getNorthDakotaLienList(ui->lienPathEdit->text());
    }

    if(lienList.size() == 0)
    {
        return;
    }

    QProgressDialog cleanProgress( "Removing Duplicate Records", "Abort", 0, 4, this);
    cleanProgress.show();
    cleanProgress.setValue(0);
    std::sort(lienList.begin(), lienList.end(), LienRecord::compareLT);
    cleanProgress.setValue(1);
    vector<LienRecord>::iterator last = std::unique(lienList.begin(), lienList.end(), LienRecord::compareEQ);
    cleanProgress.setValue(2);
    lienList.erase(last, lienList.end());
    cleanProgress.setValue(3);

    if(deleteOldImports)
    {
        CustomerDAO::clearLienImports();
    }

    cleanProgress.hide();
    insertLiens(lienList);

    end = time(&end);

    QMessageBox::information(this, "Finished Importing Liens",
                             "Imported: " + QString::number(lienList.size()) + " records\n"
                             "In " + QString::number(difftime(end, start)) + " seconds",
                             QMessageBox::Ok);
}


#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

vector<LienRecord> LienImportDialog::getNebraskaLienList(QString fileName)
{
    struct stat results;
    stat(fileName.ascii(), &results);
    QProgressDialog loadProgress( "Retrieving Records From File", "Cancel", 0, results.st_size, this);
    loadProgress.show();

    ifstream lienFile(fileName);
    string line;
    string docket;
    string ssn;

    string name;
    string address;
    string city;
    string state;
    string zip;
    string type;
    string customerType;

    vector<LienRecord> debtorList;
    vector<LienRecord> securitorList;
    LienRecord temp;

    long lineCount = 0;
    int count = 0;
    loadProgress.show();
    int lastCount = count;

    while(!lienFile.eof())
    {
        customerType == "";
        lineCount++;
        getline(lienFile, line);
        count += line.length();

        if(count - lastCount > 10000)
        {
            loadProgress.setValue(count);
            lastCount = count;
        }

        if(line.length() > 15)
        {
            customerType = line.substr(15, 1);
        }

        if(customerType == "D" || customerType == "S")
        {
            type = line.substr(12, 3);

            // according to the chop.c file from the auct4 version
            // these are the only types that apply to our customers

            if(type == "201" || type == "202" || type == "203" || type == "204" || type == "217")
            {
                //                 docket = QString::fromStdString(line.substr(0, 12)).stripWhiteSpace().ascii();
                //                 ssn = QString::fromStdString(line.substr(16, 9)).stripWhiteSpace().ascii();
                //                 name = QString::fromStdString(line.substr(25, 30)).stripWhiteSpace().ascii();
                //                 address = QString::fromStdString(line.substr(55, 30)).stripWhiteSpace().ascii();
                //                 city = QString::fromStdString(line.substr(85, 17)).stripWhiteSpace().ascii();
                //                 state = QString::fromStdString(line.substr(102, 2)).stripWhiteSpace().ascii();
                //                 zip = QString::fromStdString(line.substr(104, 5)).stripWhiteSpace().ascii();

                docket = QString::fromStdString(line.substr(0, 12)).stripWhiteSpace().ascii();
                ssn = QString::fromStdString(line.substr(17, 9)).stripWhiteSpace().ascii();
                name = QString::fromStdString(line.substr(26, 30)).stripWhiteSpace().ascii();
                address = QString::fromStdString(line.substr(56, 30)).stripWhiteSpace().ascii();
                city = QString::fromStdString(line.substr(86, 17)).stripWhiteSpace().ascii();
                state = QString::fromStdString(line.substr(104, 2)).stripWhiteSpace().ascii();
                zip = QString::fromStdString(line.substr(106, 5)).stripWhiteSpace().ascii();


                if(name.find_first_of("0123456789") == string::npos)
                {
                    QStringList nameList = QStringList::split(' ', QString::fromStdString(name));
                    for(unsigned int i = 0; i < nameList.size(); i++)
                    {
                        nameList[i] = nameList[i].stripWhiteSpace();
                    }

                    if(nameList.size() == 2)
                    {
                        string first = nameList[1].ascii();
                        string last = nameList[0].ascii();
                        name = last + "/" + first;

                    }
                    else if(nameList.size() > 2)
                    {
                        string lastFirst = nameList[nameList.size() - 1].ascii();
                        const char* cPtr = strstr (
                                    "A.B.C.D.E.F.G.H.I.J.K.L.M.N.O.P.Q.R.S.T.U.V.W.X.Y.Z.JR.SR.",
                                    lastFirst.c_str() );

                        if(cPtr != NULL)
                        {
                            string last = nameList[0].ascii();
                            string first;
                            for(unsigned int i = 1; i < nameList.size(); i++)
                            {
                                first += string(nameList[i].ascii()) + (i < nameList.size() - 1 ? " " :  "");
                            }
                            name = last + "/" + first;
                        }
                    }
                }

                temp = LienRecord(docket, ssn, name, address, "", city, state, zip);
                vector<LienRecord>::iterator loc;

                switch(customerType[0])
                {
                case 'D':
                    debtorList.push_back(temp);
                    break;

                case 'S':
                    securitorList.push_back(temp);
                    break;
                };
            }
        }

        if(loadProgress.wasCanceled())
        {
            return vector<LienRecord>();
        }
    }
    loadProgress.hide();

    sort(securitorList.begin(), securitorList.end());
    vector<LienRecord>::iterator securitor;
    QProgressDialog mortgageProgress( "Finding Customer Mortgages", "Cancel", 0, debtorList.size(), this);
    mortgageProgress.show();
    for(unsigned int i = 0; i < debtorList.size(); i++)
    {
        if(i % 1000 == 0)
        {
            mortgageProgress.setValue(i + 1);
        }
        securitor = lower_bound(securitorList.begin(), securitorList.end(), debtorList[i]);

        if(securitor == securitorList.end() || !(debtorList[i] == *securitor))
        {
            cerr << "Could not find mortgage for:" << debtorList[i].getName() << " " << endl;
        }
        else
        {
            debtorList[i].mortgage = securitor->getName();
        }
        if(mortgageProgress.wasCanceled())
        {
            return vector<LienRecord>();
        }
    }

    mortgageProgress.hide();
    lienFile.close();
    return debtorList;
}

vector<LienRecord> LienImportDialog::getSouthDakotaLienList(QString fileName)
{
    struct stat results;
    stat(fileName.ascii(), &results);
    QProgressDialog loadProgress( "Retrieving Records From File", "Cancel", 0, results.st_size, this);
    loadProgress.show();

    ifstream lienFile(fileName);

    string ssn;
    string name;
    string address1;
    string address2;
    string cityStateZipStr;

    string city;
    string state;
    string zip;
    string mortgage;
    string whoToPay;
    string county;

    string line;
    LienRecord temp;
    vector<LienRecord> recordList;
    int count = 0;
    int lastCount = count;
    int addrLen;
    QStringList nameList;
    QStringList cityStateZip;
    QStringList stateZip;
    QString first, last;

    while(!lienFile.eof())
    {
        getline(lienFile, line);
        count += line.length();

        if(count - lastCount > 1000)
        {
            loadProgress.setValue(count);
            lastCount = count;
        }

        switch(line.length()) {
        case 463:
            ssn = QString::fromStdString(line.substr(1, 11)).stripWhiteSpace().ascii();
            name = QString::fromStdString(line.substr(15, 50)).stripWhiteSpace().ascii();
            address1 = QString::fromStdString(line.substr(68,29)).stripWhiteSpace().ascii();
            address2 = QString::fromStdString(line.substr(101, 29)).stripWhiteSpace().ascii();
            cityStateZipStr = QString::fromStdString(line.substr(134, 29)).stripWhiteSpace().ascii();
            mortgage = QString::fromStdString(line.substr(184,30)).stripWhiteSpace().ascii();
            whoToPay = QString::fromStdString(line.substr(316, 24)).stripWhiteSpace().ascii();
            county = QString::fromStdString(line.substr(371, 2)).stripWhiteSpace().ascii();

            nameList = QStringList::split(',', QString::fromStdString(name));

            if(nameList.size() == 2)
            {
                first = nameList[1].stripWhiteSpace();
                last = nameList[0].stripWhiteSpace();

                if(first.upper() != "LTD" && first.upper() != "INC")
                {
                    name = string(last.ascii()) + "/" + first.ascii();
                }
            }
            if(cityStateZipStr.length() == 0)
            {
                if(address2.length() > 0)
                {
                    cityStateZipStr = address2;
                    address2 = "";
                }
                else if(address1.length() > 0)
                {
                    cityStateZipStr = address1;
                    address1 = "";
                }
                else
                {
                    cerr << "Could not extract city, state zip" << endl;
                }
            }

            cityStateZip = QStringList::split(',', QString::fromStdString(cityStateZipStr));

            if(cityStateZip.size() == 2)
            {
                stateZip = QStringList::split(' ', cityStateZip[1]);

                city = cityStateZip[0].ascii();
                if(stateZip.size() == 2)
                {
                    state = stateZip[0].ascii();
                    zip = stateZip[1].ascii();
                }
            }

            // not sure what to do here, the old program gets the mortgage
            // regardless

            //  if(whoToPay == "DEBTOR ONLY")
            //   {
            //           mortgage = "";
            //           }
            //           else if(whoToPay != "DEBTOR AND SECURED PARTY")
            //           {
            //      cerr << "Unkown payout type: " << whoToPay << endl;
            //   }

            temp = LienRecord("", ssn, name, address1, address2, city, state, zip, county);
            temp.mortgage = mortgage;

            recordList.push_back(temp);
            break;

        case 513:
        case 515:
            addrLen = 29;
            if (line.length() == 515) {
                addrLen = 30;
            }
            ssn = QString::fromStdString(line.substr(1, 11)).stripWhiteSpace().ascii();
            name = QString::fromStdString(line.substr(15, 50)).stripWhiteSpace().ascii();
            address1 = QString::fromStdString(line.substr(68,addrLen)).stripWhiteSpace().ascii();
            address2 = QString::fromStdString(line.substr(101, addrLen)).stripWhiteSpace().ascii();
            cityStateZipStr = QString::fromStdString(line.substr(134, addrLen)).stripWhiteSpace().ascii();
            mortgage = QString::fromStdString(line.substr(184,80)).stripWhiteSpace().ascii();
            whoToPay = QString::fromStdString(line.substr(366, 24)).stripWhiteSpace().ascii();
            county = QString::fromStdString(line.substr(421, 2)).stripWhiteSpace().ascii();

            nameList = QStringList::split(',', QString::fromStdString(name));

            if(nameList.size() == 2)
            {
                first = nameList[1].stripWhiteSpace();
                last = nameList[0].stripWhiteSpace();

                if(first.upper() != "LTD" && first.upper() != "INC")
                {
                    name = string(last.ascii()) + "/" + first.ascii();
                }
            }
            if(cityStateZipStr.length() == 0)
            {
                if(address2.length() > 0)
                {
                    cityStateZipStr = address2;
                    address2 = "";
                }
                else if(address1.length() > 0)
                {
                    cityStateZipStr = address1;
                    address1 = "";
                }
                else
                {
                    cerr << "Could not extract city, state zip" << endl;
                }
            }

            cityStateZip = QStringList::split(',', QString::fromStdString(cityStateZipStr));

            if(cityStateZip.size() == 2)
            {
                stateZip = QStringList::split(' ', cityStateZip[1]);

                city = cityStateZip[0].ascii();
                if(stateZip.size() == 2)
                {
                    state = stateZip[0].ascii();
                    zip = stateZip[1].ascii();
                }
            }

            temp = LienRecord("", ssn, name, address1, address2, city, state, zip, county);
            temp.mortgage = mortgage;

            recordList.push_back(temp);
            break;

        default:
            cerr << "Invalid line length: " << line.length() << ", check type" << endl;
            break;

        }

        if(loadProgress.wasCanceled())
        {
            return vector<LienRecord>();
        }

    }

    lienFile.close();
    return recordList;
}

vector<LienRecord> LienImportDialog::getIdahoLienList(QString folderPath, bool& master)
{
    master = true;
    QDir importDirectory(folderPath);

    QFileInfoList fileList = importDirectory.entryInfoList();
    vector<LienRecord> tempList;
    vector<LienRecord> resultVector;

    if(!fileList.empty())
    {
        QString fileName;

        for(unsigned int i = 0; i < fileList.count(); i++)
        {
            fileName = fileList.at(i).fileName();

            if(fileName.startsWith("pmp") &&
                    (fileName.endsWith("50.txt") ||
                     fileName.endsWith("51.txt") ||
                     fileName.endsWith("52.txt") ||
                     fileName.endsWith("53.txt") ||
                     fileName.endsWith("54.txt")))
            {
                tempList.clear();

                tempList = getIdahoLienMasterList(const_cast<QFileInfo*>(&fileList.at(i)));

                resultVector.insert(resultVector.end(), tempList.begin(), tempList.end());
            }
            else if(fileName.startsWith("csp") &&
                    (fileName.endsWith("50.txt") ||
                     fileName.endsWith("51.txt") ||
                     fileName.endsWith("52.txt") ||
                     fileName.endsWith("53.txt") ||
                     fileName.endsWith( "54.txt")))
            {
                vector<Customer> deleteVector;
                master = false;
                tempList = getIdahoLienSupplementList(const_cast<QFileInfo*>(&fileList.at(i)), deleteVector);
                resultVector.insert(resultVector.end(), tempList.begin(), tempList.end());

                for(unsigned int i = 0; i < deleteVector.size(); i++)
                {
                    CustomerDAO::deleteByDocket(deleteVector[i]);
                }
            }
            else
            {
                cerr << "file: '" << fileList.at(i).filePath().toStdString() << "' is not recognized as importable" << endl;
            }
        }
    }

    return resultVector;
}

vector<LienRecord> LienImportDialog::getIdahoLienMasterList(QFileInfo* fileInfo)
{
    QString fileName = fileInfo->filePath();
    vector<LienRecord> resultVector;

    struct stat results;
    stat(fileName.ascii(), &results);
    QProgressDialog loadProgress( QString("Retrieving Records From File:'") + fileName + "' ", "Cancel", 0, results.st_size, this);
    loadProgress.show();

    ifstream lienFile(fileName);
    string line;

    string docket = "";
    string id="";
    string name="";
    string address1="";
    string address2 = "";
    string city = "";
    string mortgage = "";
    string state="";
    string zip="";
    string county="";

    string firstRecordLine;
    string secondRecordLine;
    string thirdRecordLine;

    long progressCount = 0;

    while(!lienFile.eof())
    {
        // find the beginning of the next record
        getline(lienFile, line);
        progressCount += line.size();

        if(line.substr(0, 28) == "  ITEM   DEBTOR INFORMATION:")
        {
            docket = id = name = address1= address2 = city = mortgage = state= zip= county="";
            getline(lienFile, firstRecordLine);

            if(firstRecordLine.size() > 0 && firstRecordLine[0] == '\f')
            {
                for(int i = 0; i < 12; i++) {
                    getline(lienFile, line);
                }
                getline(lienFile, firstRecordLine);
            }

            getline(lienFile, secondRecordLine);

            if(secondRecordLine.size() > 0 && secondRecordLine[0] == '\f')
            {
                for(int i = 0; i < 12; i++) {
                    getline(lienFile, line);
                }
                getline(lienFile, secondRecordLine);
            }

            getline(lienFile, thirdRecordLine);

            if(thirdRecordLine.size() > 0 && thirdRecordLine[0] == '\f')
            {
                for(int i = 0; i < 12; i++) {
                    getline(lienFile, line);
                }
                getline(lienFile, thirdRecordLine);
            }

            progressCount += firstRecordLine.size() + secondRecordLine.size() + thirdRecordLine.size();

            name = firstRecordLine.substr(9, 60);
            docket = firstRecordLine.substr(78, 14);
            mortgage = firstRecordLine.substr(95);

            address1 = secondRecordLine.substr(9, 60);

            int seperatorIndex = address1.find_first_of(",");

            if(seperatorIndex != string::npos)
            {
                if(seperatorIndex + 1 < address1.length())
                {
                    address2 = address1.substr(seperatorIndex + 1);
                }

                address1 = address1.substr(0, seperatorIndex);
            }


            city = thirdRecordLine.substr(9, 60);
            id = thirdRecordLine.substr(78, 24);

            QStringList cityParts = QStringList::split(",", QString::fromStdString(city));

            if(cityParts.size() == 2)
            {
                city = cityParts[0].ascii();
                QStringList stateZip = QStringList::split(" ", cityParts[1]);

                state = "";

                for(int i = 0; i < stateZip.size(); i++)
                {
                    if(i != stateZip.size() - 1)
                    {
                        state += stateZip[i].ascii();
                    }
                    else
                    {
                        zip = stateZip[i].ascii();
                    }
                }
            }


            docket = QString::fromStdString(docket).stripWhiteSpace().ascii();
            id = QString::fromStdString(id).stripWhiteSpace().ascii();
            name = QString::fromStdString(name).stripWhiteSpace().replace(", ", "/").ascii();
            address1 = QString::fromStdString(address1).stripWhiteSpace().ascii();
            address2 = QString::fromStdString(address2).stripWhiteSpace().ascii();
            city = QString::fromStdString(city).stripWhiteSpace().ascii();
            state = QString::fromStdString(state).stripWhiteSpace().ascii();
            zip = QString::fromStdString(zip).stripWhiteSpace().ascii();
            county = "";
            mortgage = QString::fromStdString(mortgage).stripWhiteSpace().ascii();
            LienRecord record(docket, id, name, address1, address2, city, state, zip, county);
            record.mortgage = mortgage;

            resultVector.push_back(record);
            loadProgress.setValue(progressCount);
        }
    }

    return resultVector;
}

vector<LienRecord> LienImportDialog::getIdahoLienSupplementList(QFileInfo* fileInfo, vector<Customer>& deleteVector)
{

    QString fileName = fileInfo->filePath();
    vector<LienRecord> resultVector;

    QProgressDialog loadProgress( QString("Retrieving Records From File:'") + fileName + "' ", "Cancel", 0, fileInfo->size(), this);
    loadProgress.show();

    ifstream lienFile(fileName);
    string line;

    string docket = "";
    string id="";
    string name="";
    string address1="";
    string address2 = "";
    string city = "";
    string mortgage = "";
    string state="";
    string zip="";
    string county="";

    string firstRecordLine;
    string secondRecordLine;
    string thirdRecordLine;

    long progressCount = 0;

    bool addDeletions = false;

    while(!lienFile.eof())
    {   // find the beginning of the next record

        getline(lienFile, line);
        progressCount += line.size();

        if(!addDeletions && line.length() >= 28 && line.substr(0, 28) == "  ITEM   DEBTOR INFORMATION:")
        {

            docket = id = name = address1= address2 = city = mortgage = state= zip= county="";
            getline(lienFile, firstRecordLine);

            if(firstRecordLine.size() > 0 && firstRecordLine[0] == '\f')
            {
                for(int i = 0; i < 13; i++) {
                    getline(lienFile, line);
                }
                getline(lienFile, firstRecordLine);
            }

            getline(lienFile, secondRecordLine);

            if(secondRecordLine.size() > 0 && secondRecordLine[0] == '\f')
            {
                for(int i = 0; i < 13; i++) {
                    getline(lienFile, line);
                }
                getline(lienFile, secondRecordLine);
            }

            getline(lienFile, thirdRecordLine);

            if(thirdRecordLine.size() > 0 && thirdRecordLine[0] == '\f')
            {
                for(int i = 0; i < 13; i++) {
                    getline(lienFile, line);
                }
                getline(lienFile, thirdRecordLine);
            }

            progressCount += firstRecordLine.size() + secondRecordLine.size() + thirdRecordLine.size();
            name = firstRecordLine.substr(9, 60);
            docket = firstRecordLine.substr(78, 14);
            mortgage = firstRecordLine.substr(101);

            address1 = secondRecordLine.substr(9, 60);

            int seperatorIndex = address1.find_first_of(",");

            if(seperatorIndex != string::npos)
            {
                if(seperatorIndex + 1 < address1.length())
                {
                    address2 = address1.substr(seperatorIndex + 1);
                }

                address1 = address1.substr(0, seperatorIndex);
            }


            city = thirdRecordLine.substr(9, 60);
            id = thirdRecordLine.substr(78, 24);

            QStringList cityParts = QStringList::split(",", QString::fromStdString(city));

            if(cityParts.size() == 2)
            {
                city = cityParts[0].ascii();
                QStringList stateZip = QStringList::split(" ", cityParts[1]);

                state = "";

                for(int i = 0; i < stateZip.size(); i++)
                {
                    if(i != stateZip.size() - 1)
                    {
                        state += stateZip[i].ascii();
                    }
                    else
                    {
                        zip = stateZip[i].ascii();
                    }
                }
            }

            docket = QString::fromStdString(docket).stripWhiteSpace().ascii();
            id = QString::fromStdString(id).stripWhiteSpace().ascii();
            name = QString::fromStdString(name).stripWhiteSpace().replace(", ", "/").ascii();
            address1 = QString::fromStdString(address1).stripWhiteSpace().ascii();
            address2 = QString::fromStdString(address2).stripWhiteSpace().ascii();
            city = QString::fromStdString(city).stripWhiteSpace().ascii();
            state = QString::fromStdString(state).stripWhiteSpace().ascii();
            zip = QString::fromStdString(zip).stripWhiteSpace().ascii();
            county = "";
            mortgage = QString::fromStdString(mortgage).stripWhiteSpace().ascii();
            LienRecord record(docket, id, name, address1, address2, city, state, zip, county);
            record.mortgage = mortgage;
            resultVector.push_back(record);
        }
        else
        {
            if(addDeletions)
            {
                if(line.length() > 87 && line.substr(0, 88) == "                                                              * * * END OF LISTING * * *")
                {
                    addDeletions = false;
                }
                else if( line.length() == 112)
                {
                    docket = QString::fromStdString(line.substr(94, 7)).stripWhiteSpace().ascii();
                    id = QString::fromStdString(line.substr(79, 15)).stripWhiteSpace().ascii();
                    name = QString::fromStdString(line.substr(27, 52)).stripWhiteSpace().ascii();


                    Customer customer;
                    customer.setDocket(docket);
                    customer.setSocialSecurityNumber(id);
                    customer.setName(name);

                    deleteVector.push_back(customer);
                }
            }
            else if(line.substr(0, 87) == "                                             - TERMINATIONS, LAPSES, DEBTOR DELETIONS -")
            {
                addDeletions = true;
            }
        }
        loadProgress.setValue(progressCount);
    }
    return resultVector;
}

void LienImportDialog::insertLiens(vector<LienRecord> recordList)
{
    QString name, mortgage, address, city, state, zip, ssn;
    QProgressDialog insertProgress( "Inserting Records", "Cancel", 0, recordList.size(), this);

    insertProgress.show();

    Customer tempCust;
    Address tempAddr;

    for(unsigned int i = 0; i < recordList.size(); i++)
    {
        if(i % 1000 == 0)
        {
            insertProgress.setValue(i);
        }

        if(insertProgress.wasCanceled())
        {
            return;
        }
        tempCust.setName(recordList[i].name);

        tempAddr.setAddress1(recordList[i].address1);
        tempAddr.setAddress2(recordList[i].address2);
        tempAddr.setCity(recordList[i].city);
        tempAddr.setState(recordList[i].state);
        tempAddr.setZip(recordList[i].zip);
        tempAddr.setCounty(recordList[i].county);
        tempCust.setAddress(tempAddr);
        tempCust.setSocialSecurityNumber(recordList[i].id);
        tempCust.setCompany(recordList[i].mortgage);
        tempCust.setDocket(recordList[i].docket);
        CustomerDAO::saveCustomer(tempCust, Customer::Seller, false);
    }
    insertProgress.hide();
}

vector<LienRecord> LienImportDialog::getNorthDakotaLienList(QString fileName)
{
    struct stat results;
    stat(fileName.ascii(), &results);
    QProgressDialog loadProgress( "Retrieving Records From File", "Cancel", 0, results.st_size, this);
    loadProgress.show();

    ifstream lienFile(fileName);

    string ssn;
    string name;
    string address1;
    string address2;
    string cityStateZipStr;

    string city;
    string state;
    string zip;
    string mortgage;
    string whoToPay;
    string county;

    string line;
    LienRecord temp;
    vector<LienRecord> recordList;
    int count = 0;
    int lastCount = count;
    QStringList record;

    while(!lienFile.eof())
    {
        getline(lienFile, line);
        count += line.length();

        if(count - lastCount > 1000)
        {
            loadProgress.setValue(count);
            lastCount = count;
        }


        int startQuotePos = string::npos;
        int lastPos = 0;
        QString actualLine = QString::fromStdString(line);

        do
        {
            if(lastPos < line.length())
            {
                startQuotePos = line.find_first_of("\"", lastPos);
                if(startQuotePos != string::npos && startQuotePos + 1 < line.length())
                {
                    int endQuotePos = line.find_first_of("\"", startQuotePos + 1);

                    if(endQuotePos != string::npos)
                    {
                        QString toReplace = QString::fromStdString(line.substr(startQuotePos, (endQuotePos - startQuotePos) + 1));
                        QString replaceStr = toReplace;
                        replaceStr.replace("\"", "");
                        replaceStr = replaceStr.replace(",", "&comma;");
                        actualLine = actualLine.replace(toReplace, replaceStr);
                        lastPos = endQuotePos + 1;
                    }
                    else
                    {
                        lastPos = line.length();
                    }
                }
            }
        } while(startQuotePos != string::npos);

        record = QStringList::split(",", actualLine, true);
        if(record.size() > 6 && record[0] != "DebtorName" )
        {
            name        = (record[0].length() > 0 ? record[0].replace("&comma;", ",").ascii() : "");
            ssn            = (record[1].length() > 0 ? record[1].replace("&comma;", ",").ascii() : "");
            address1 = (record[2].length() > 0 ? record[2].replace("&comma;", ",").ascii() : "");
            address2 = "";
            city            = (record[3].length() > 0 ? record[3].replace("&comma;", ",").ascii() : "");
            state          = (record[4].length() > 0 ? record[4].replace("&comma;", ",").ascii() : "");
            zip             = (record[5].length() > 0 ? record[5].replace("&comma;", ",").ascii() : "");
            mortgage = (record[6].length() > 0 ? record[6].replace("&comma;", ",").ascii() : "");
            county      = "";


            temp = LienRecord("", ssn, name, address1, address2, city, state, zip, county);
            temp.mortgage = mortgage;

            recordList.push_back(temp);
        }

        if(loadProgress.wasCanceled())
        {
            return vector<LienRecord>();
        }
    }

    lienFile.close();
    return recordList;
}

void LienImportDialog::on_lienImportCancelButton_clicked()
{
    reject();
}
