#include "printerdao.h"
#include "printerfactory.h"

PrinterDAO::PrinterDAO()
{
    keys[Check] = "genLpCheck";        keys[SellerInvoice] = "genLpSinv";
    keys[BuyerInvoice] = "genLpBinv";  keys[Report] = "genLpRpt";
    keys[Ticket] = "genLpTkt";         keys[Scale] = "genLpScale";
    keys[CheckIn] = "genLpCkin";       keys[CheckInOffice] = "genLpCkinOff";
    keys[Loadout] = "genLpLoadout";     keys[SecondCopy]="genLpSecCopy";
}

//Create and return pointer to printer object.
// Caller reponsible to delete after work return, in destructor or dynamically to avoid memory leaks.
PrinterBase *PrinterDAO::getPrinter(PrinterType printer)
{
    string tableName;
    QString printerName;

    switch(printer)
    {
    case UseDefault:
        printerName = QString::fromStdString(getDefaultPrinterName());
        break;
    default:
        tableName = keys[printer];
        break;
    };

    //TODO switch DAO objecs to QString instead of string. Remove STD library.
    printerName = QString::fromStdString(SetupDAO().get(tableName));
    if (printerName == "Default")  {
        printerName = QString::fromStdString(getDefaultPrinterName());
    }
    return PrinterFactory::createPrinter(printerName);
}

void PrinterDAO::clearDefaultPrinters()
{
    string qryString = "DELETE FROM default_printers";
    DatabaseManager::defaultManager.query(qryString.c_str());
}

void PrinterDAO::savePrinter(PrinterType printerType, string printerName)
{
    if(printerType != UseDefault)
    {
        SetupDAO().set(keys[printerType], printerName);
    }
}

string PrinterDAO::getDefaultPrinterName()
{
//    cout << "Top of PrinterDAO::getDefaultPrinterName" << endl;
    string stationName = getenv("DISPLAY");
    stationName = stationName.substr(0, stationName.find_first_of(':'));

    // KLN start
    string sshName;
    if (getenv("SSH_CLIENT") == NULL) {
        sshName = "";
    } else {
       sshName = getenv("SSH_CLIENT");
    }
//    cout << "stationName: " << stationName << endl;
    sshName = sshName.substr(0, sshName.find_first_of(' '));
//    cout << "sshName: " << sshName << endl;
    if (sshName.size() > 0) {
        stationName = sshName;
    }
    // KLN end

    if(stationName.size() == 0)
    {
        stationName = "localhost";
    }
//    cout << "stationName: " << stationName << endl;

    return getDefaultPrinterName(stationName);
}


string PrinterDAO::getDefaultPrinterName(string stationName)
{
    string qryString = "SELECT printer FROM default_printers WHERE station='" + stationName + "'";
    QSqlQuery printerQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));

    string printerName = "";

    if(printerQuery.first()) {
        printerName = DatabaseManager::valueAs<QString>(printerQuery,"printer").toStdString();
    }
    return printerName;
}


void PrinterDAO::saveDefaultPrinter(string station, string printer)
{
    string qryString = "DELETE FROM default_printers WHERE station='" + station + "'";
    DatabaseManager::defaultManager.query(qryString.c_str());
    qryString = "INSERT INTO default_printers SET station='" + station + "', printer='" + printer + "'";
    DatabaseManager::defaultManager.query(qryString.c_str());
}

vector<string> PrinterDAO::getPrinterNames()
{
    SetupDAO setup;
    vector<string> printerList(UseDefault, "");

    printerList[Check] = setup.get(keys[Check]);
    printerList[SellerInvoice] = setup.get(keys[SellerInvoice]);
    printerList[BuyerInvoice] = setup.get(keys[BuyerInvoice]);
    printerList[Report] = setup.get(keys[Report]);
    printerList[Ticket] = setup.get(keys[Ticket]);
    printerList[Scale] = setup.get(keys[Scale]);
    printerList[CheckIn] = setup.get(keys[CheckIn]);
    printerList[CheckInOffice] = setup.get(keys[CheckInOffice]);
    printerList[Loadout] = setup.get(keys[Loadout]);
    printerList[SecondCopy] = setup.get(keys[SecondCopy]);

    return printerList;
}

vector<PrinterDAO::DefaultPrinter> PrinterDAO::getDefaultPrinterList()
{
    vector<DefaultPrinter> printerList;
    string qryString = "SELECT station, printer FROM default_printers";
    QSqlQuery printerQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
    DefaultPrinter def;

    while (printerQuery.next()) {
        string _printer = DatabaseManager::valueAs<QString>(printerQuery,"printer").toStdString();
        string _station = DatabaseManager::valueAs<QString>(printerQuery,"station").toStdString();
        def.printer = _printer;
        def.station = _station;
        printerList.push_back(def);
    }
    return printerList;
}
