
#ifndef _PRINTER_DAO_H_
#define _PRINTER_DAO_H_

#include "databasemanager.h"
#include "setupdao.h"
#include "../lineprinter.h"
#include "../laserprinter.h"
#include "../printerbase.h"
#include <string>
#include <vector>
using namespace std;

class PrinterDAO
{
public:
    typedef enum
    {
        // NOTA BENE!! for some strange reason 'UseDefault' MUST BE the last entry.
        // (Not related to the setup of key[] in private.)
        Check,
        SellerInvoice,
        BuyerInvoice,
        Report,
        Ticket,
        Scale,
        CheckIn,
        CheckInOffice,
        Loadout,
        SecondCopy,
        UseDefault
    }PrinterType;

typedef struct defRec
{
  string station;
  string printer;
}DefaultPrinter;

PrinterDAO();
PrinterBase * getPrinter(PrinterType);
void savePrinter(PrinterType, string);
void saveDefaultPrinter(string, string);
void clearDefaultPrinters();
vector<string> getPrinterNames();
vector<DefaultPrinter> getDefaultPrinterList();

private:
string getDefaultPrinterName();
string getDefaultPrinterName(string);
string keys[UseDefault];

};

#endif
