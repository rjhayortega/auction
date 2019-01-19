#include <iostream> // For [KLN] debugs

#include "invoicedao.h"
#include "../types/customer.h"

unsigned long InvoiceDAO::chargeInterval = 0;
unsigned long InvoiceDAO::transactionInterval = 0;
unsigned long InvoiceDAO::queryInterval = 0;
unsigned long InvoiceDAO::customerInterval = 0;
unsigned long InvoiceDAO::truckingInterval = 0;

#ifdef DEBUG_INVOICE_TIME
Timer InvoiceDAO::timer;
#endif

InvoiceDAO::InvoiceDAO()
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    progressCallback = NULL;
    invoiceReference = NULL;
    loadCustomerData = true;
//    std:cout << "InvoiceDAO constructor" << endl;
}

void InvoiceDAO::setProgressCallback(ProgressCallback progressCallback)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    this->progressCallback = progressCallback;
}

void InvoiceDAO::resetTiming()
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    chargeInterval      = 0;
    transactionInterval = 0;
    queryInterval       = 0;
    customerInterval    = 0;
    truckingInterval    = 0;
}

void InvoiceDAO::printTiming()
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    cout << "| Charge Time        | Transaction Time   | Query Time         | Customer Time      | Trucking Time     |" << endl;
    printf("|%12ld %3.2f(s)|%12ld %3.2f(s)|%12ld %3.2f(s)|%12ld %3.2f(s)|%12ld %3.2f(s)|\n",
           chargeInterval,  double(chargeInterval) / 1000000,
           transactionInterval, double(transactionInterval) / 1000000,
           queryInterval, double(queryInterval) / 1000000,
           customerInterval, double(customerInterval) / 1000000,
           truckingInterval, double(truckingInterval) / 1000000);
}

InvoiceDAO::~InvoiceDAO()
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    freeInvoice();
}

Invoice* InvoiceDAO::getInvoiceByCondition(string whereString, CommissionDAO::COLOR_GROUP group, bool getChargeStubs)
{
    INVOICE_INTERVAL;
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    QString qryString =
            QString("SELECT "
                    "id, "
                    "status, "
                    "customer_id, "
                    "date "
                    "FROM ") + QString::fromStdString(invoiceTableName()) + " "
            "WHERE date='" + QString::fromStdString(sale.currentSaleDateSQLString()) + "' ";
    if(whereString.length() > 0)
    {
        qryString += " AND " +  QString::fromStdString(whereString);
    }

    QSqlQuery invoiceQuery = DatabaseManager::defaultManager.query(qryString);

    long id = 0;
    short status = 0;
    string customerId = "0";
    Date date;

    if (invoiceQuery.first()) {
        id = DatabaseManager::valueAs<long>(invoiceQuery,"id");
        status = DatabaseManager::valueAs<long>(invoiceQuery,"status");
        customerId = DatabaseManager::valueAs<QString>(invoiceQuery,"customer_id").toStdString();
        QString dateStr = DatabaseManager::valueAs<QString>(invoiceQuery,"date");
        date = Date::fromString(dateStr.toStdString(), "YYYY-mm-dd");
    } else {
        GRIPE("Error accessing invoice record");
        GRIPE("Query string:" + qryString.toStdString());
    }
    //  if(nfound < 1)
    //  {

    //  }
    //  else
    //  {
    //    char **record = DatabaseManager::defaultManager.get_record();
    //    id = atoi(record[0]);
    //    status = atoi(record[1]);
    //    customerId = record[2];
    //    date = Date::fromString(record[3], "YYYY-mm-dd");
    //  }

    //  DatabaseManager::defaultManager.release_result();

    queryInterval += INVOICE_INTERVAL;

    Customer cust;
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    if(loadCustomerData)
    {
        cust = getCustomer(customerId);
    }
    else
    {
        cust.setNumber(customerId);
    }

    customerInterval += INVOICE_INTERVAL;

    invoiceReference = createInvoice(id, date, customerId,Invoice::STATUS(status));
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    loadInvoiceTrans(invoiceReference);
    transactionInterval += INVOICE_INTERVAL;

    invoiceReference->setTruckingList(truckingDao.getTruckingRecordList(cust, chargeType()));
    truckingInterval += INVOICE_INTERVAL;

    if(group == CommissionDAO::INVALID)
    {
        if(invoiceReference->getTransactionList().size() > 0)
        {
            group = CommissionDAO::COLOR_GROUP(invoiceReference->getTransactionList()[0].getAnimalCode().group());
        }
    }
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    if(sale.currentSaleOpen())
    {

        invoiceReference->setManualCharges(getManualChargeList(group));

        if(getChargeStubs)
        {
            invoiceReference->setChargeStubList(getCompleteChargeList(group));
        }

        vector<Charge>chargeList = invoiceReference->getUniqueChargeList(true);


        adjustChargeList(chargeList, invoiceReference);

        invoiceReference->adjustCharges(chargeList);

    }
    else
    {
        qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
        invoiceReference->setTransactionChargeList(0, getInvoiceChargeHistory(invoiceReference));
    }
    chargeInterval += INVOICE_INTERVAL;

    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return invoiceReference;
}

vector<Charge> InvoiceDAO::getInvoiceChargeHistory(Invoice* invoice)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return vector<Charge>();
}

vector<Charge> SellerInvoiceDAO::getInvoiceChargeHistory(Invoice* invoice)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return chargeDao.getChargeHistory(invoice, Customer::Seller);
}

vector<Charge> BuyerInvoiceDAO::getInvoiceChargeHistory(Invoice* invoice)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return chargeDao.getChargeHistory(invoice, Customer::Buyer);
}


void InvoiceDAO::adjustChargeList(vector<Charge>& chargeList, Invoice* invoice)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    vector<Charge>::iterator current;

    vector<ChargeAdjustment> adjustmentList = chargeDao.getAdjustments(invoice);

    for(unsigned int i = 0; i < adjustmentList.size(); i++)
    {
        for(unsigned int j = 0; j < chargeList.size(); j++)
        {
            if(adjustmentList[i].getChargeId() == chargeList[j].getId())
            {
                if(!(customerType() == Customer::Buyer && chargeList[j].getId() == 0))
                {
                    chargeList[j].setAdjustment(adjustmentList[i]);
                    break;
                }
            }
        }
    }
    /*
 for(current = chargeList.begin(); current != chargeList.end(); current++)
 {
   ChargeAdjustment temp = chargeDao.getAdjustment(*current, &invoice, customerType());
   current->setAdjustment(temp);
 }
*/
}

vector<string> InvoiceDAO::getNumbersMatching(string baseNumber)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    string qryString =
            "SELECT distinct(" + customerTypeString() + "ID) as _custNum FROM trans "
            "WHERE (" + customerTypeString() + "ID LIKE '" + baseNumber + "/%' "
            "OR " + customerTypeString() + "ID LIKE '" + baseNumber + "-%' "
            "OR " + customerTypeString() + "ID ='" + baseNumber + "') "
            "AND date='" + sale.currentSaleDateSQLString() + "'";

    //    [KLN] start
    cout << "getNumbersMatching qryString: " << qryString << endl;
    //    [KLN] end
    QSqlQuery numberQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
    vector<string> numberList;

    while (numberQuery.next()) {
        string _number = DatabaseManager::valueAs<QString>(numberQuery,"_custNum").toStdString();
        //    [KLN] start
        cout << "  _number: " << _number << endl;
        //    [KLN] end
        numberList.push_back(_number);
    }
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return numberList;
}

vector<Charge> InvoiceDAO::getManualChargeList(CommissionDAO::COLOR_GROUP cg)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return vector<Charge>();
}

vector<Charge> SellerInvoiceDAO::getManualChargeList(CommissionDAO::COLOR_GROUP cg)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return chargeDao.getManualChargeList(cg, ChargeDAO::Seller);
}

vector<Charge> BuyerInvoiceDAO::getManualChargeList(CommissionDAO::COLOR_GROUP cg)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return chargeDao.getManualChargeList(cg, ChargeDAO::Buyer);
}

vector<Charge> InvoiceDAO::getCompleteChargeList(CommissionDAO::COLOR_GROUP cg)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return vector<Charge>();
}


vector<Charge> SellerInvoiceDAO::getCompleteChargeList(CommissionDAO::COLOR_GROUP cg)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return chargeDao.getChargeList(ChargeDAO::Seller, cg);
}

vector<Charge> BuyerInvoiceDAO::getCompleteChargeList(CommissionDAO::COLOR_GROUP cg)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return chargeDao.getChargeList(ChargeDAO::Buyer, cg);
}

void InvoiceDAO::freeInvoice()
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    if(invoiceReference != NULL)
    {
        delete invoiceReference;
        invoiceReference = NULL;
    }
}


void InvoiceDAO::saveInvoice(Invoice invoice)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    char buf[30];
    sprintf(buf, "%ld", invoice.getNumber());
    QSqlQuery saveInvoiceQuery;
    QString qryString = QString("REPLACE INTO " + QString::fromStdString(invoiceTableName()) + " SET "
                                "id=:id, status=:status, customer_id=:customer_id, date=:date");

    DatabaseManager::defaultManager.prepareQuery(saveInvoiceQuery,qryString);
    saveInvoiceQuery.bindValue(":id"             , QVariant::fromValue<long>(invoice.getNumber()));
    saveInvoiceQuery.bindValue(":status"         , QVariant::fromValue<int>(invoice.getStatus()));
    saveInvoiceQuery.bindValue(":customer_id"    , QString::fromStdString(invoice.getCustomer().getNumber()));
    saveInvoiceQuery.bindValue(":date"           , QString::fromStdString(sale.currentSaleDateSQLString()));
    DatabaseManager::defaultManager.executeQuery(saveInvoiceQuery);
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
}

bool InvoiceDAO::printed(Invoice invoice)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    char invId[20];
    sprintf(invId, "%ld", invoice.getNumber());
    string qryString =
            "SELECT * FROM " + summaryTableName() + " WHERE invoice_id=" + string(invId) + "";

    QSqlQuery printQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
    return (printQuery.first());
}

SellerInvoice SellerInvoiceDAO::getInvoiceByNum(long invoice_number)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    //  TransactionDAO transactionDao;
    //  list<Transaction> transactionList = transactionDao.getTransactionListByInvoice(invoice_number);

    char number[20];
    sprintf(number, "%ld", invoice_number);

    string qryString = "SELECT id, status, customer_id, date FROM " + invoiceTableName() + " WHERE id=" + string(number);

    QSqlQuery invoiceNumQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));

    long id;
    short status;
    int customerId;
    Date date;

    if(invoiceNumQuery.first()){

        id           = DatabaseManager::valueAs<int>(invoiceNumQuery,"id");
        status       = DatabaseManager::valueAs<int>(invoiceNumQuery,"status");
        customerId   = DatabaseManager::valueAs<int>(invoiceNumQuery,"customer_id");
        string _date = DatabaseManager::valueAs<QString>(invoiceNumQuery,"date").toStdString();
        date = Date::fromString(_date, "YYYY-mm-dd");

        SellerInvoice invoice(id, date, CustomerDAO::loadFromId(customerId));
        vector<Transaction> transactionList = transDao.getTransactionListByInvoice(invoice.getNumber());

        vector<Transaction>::iterator currentTrans;

        for(currentTrans = transactionList.begin(); currentTrans != transactionList.end(); currentTrans++)
        {
            invoice += *currentTrans;
        }
        qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
        return invoice;
    }
    else
    {
        GRIPE("Incorrect number of results for seller invoice");
    }
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return SellerInvoice();
}


void InvoiceDAO::loadInvoiceTrans(Invoice *invoice)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    invoice->setTransactionList(transDao.getTransactionListByInvoice(invoice->getNumber()));
}

string InvoiceDAO::printedCustomerString(CommissionDAO::COLOR_GROUP)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    string queryString = "SELECT customer_id from " + customerTypeString() + "invoicesummary where date='" + sale.currentSaleDateSQLString() + "'";

    QSqlQuery printedCustomerQuery = DatabaseManager::defaultManager.query(QString::fromStdString(queryString));
    string result;

    int nfound = printedCustomerQuery.size();
    int i = 0;
    while (printedCustomerQuery.next()) {
            result += "'";
            result += DatabaseManager::valueAs<QString>(printedCustomerQuery,"customer_id").toStdString();
            result += "'";
            if(i != nfound - 1)
            {
                result += ", ";
            }
            i++;
    }
    return result;
}

vector<string> InvoiceDAO::getUnprintedCustomerList(CommissionDAO::COLOR_GROUP colorGroup)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    string printedCustomers = printedCustomerString(colorGroup);

    string qryString =
            "SELECT " + customerTypeString() + "ID  as _customerType "
            "FROM trans "
            "WHERE "
            "date='" + sale.currentSaleDateSQLString() + "' " + extraTransConditions() + " "
            "AND "
            "mode != 0 ";

    if(printedCustomers.length() > 0)
    {
        qryString +=  "AND " + customerTypeString() + "ID not in (" + printedCustomerString(colorGroup) + ") ";
    }

    if(colorGroup != CommissionDAO::INVALID)
    {
        string codeRange;

        switch(colorGroup)
        {
        case CommissionDAO::FIRST:
            codeRange = "0 <= color AND color < 70";
            break;

        case CommissionDAO::SECOND:
            codeRange = "70 <= color AND color < 80";
            break;

        case CommissionDAO::THIRD:
            codeRange = "80 <= color AND color < 90";
            break;

        case CommissionDAO::FOURTH:
            codeRange = "90 <= color AND color < 100";
            break;

        case CommissionDAO::INVALID:
            cerr << "REALITY ERROR, RE-INSTALL UNIVERSE AND REBOOT" << endl;
            break;
        }

        qryString +=
                " AND " + codeRange + "";
    }

    qryString +=  " GROUP BY " + customerTypeString() +"ID ";

    QSqlQuery unprintedCustomerQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));

    vector<string> unprinted;
    int i = 0;
    int nfound = unprintedCustomerQuery.size();

    while (unprintedCustomerQuery.next()) {
        string _customerType = DatabaseManager::valueAs<QString>(unprintedCustomerQuery,"_customerType").toStdString();
        unprinted.push_back(_customerType);
        if(progressCallback != NULL)
        {
            progressCallback(i++, nfound);
        }

    }
    return unprinted;
}

string InvoiceDAO::extraTransConditions()
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return "";
}

string SellerInvoiceDAO::extraTransConditions()
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return "AND (mode != 7 AND mode != 8)";
}

vector<InvoiceDAO::DISCREPANCY> InvoiceDAO::getDiscrepancyList(CommissionDAO::COLOR_GROUP colorGroup)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    string qryString =
            "SELECT invoice_id, customer_id, " + totalColumnName() + " as _totalColumn, head FROM " + summaryTableName() + " "
            "WHERE date='" + sale.currentSaleDateSQLString() + "'";


    if(colorGroup != CommissionDAO::INVALID)
    {
        string codeRange;

        switch(colorGroup)
        {
        case CommissionDAO::FIRST:
            codeRange = "0 <= color AND color < 70";
            break;

        case CommissionDAO::SECOND:
            codeRange = "70 <= color AND color < 80";
            break;

        case CommissionDAO::THIRD:
            codeRange = "80 <= color AND color < 90";
            break;

        case CommissionDAO::FOURTH:
            codeRange = "90 <= color AND color < 100";
            break;

        case CommissionDAO::INVALID:
            cerr << "REALITY ERROR, RE-INSTALL UNIVERSE AND REBOOT" << endl;
            break;
        }

        qryString +=
                " AND customer_id IN ("
                "SELECT " + customerTypeString() + "ID FROM trans WHERE "+ codeRange + (codeRange.length() > 0 ? " and " : "") + "date='" + sale.currentSaleDateSQLString() + "')";
    }

    transDao.startBatchMode(false, false, true);
    QSqlQuery listQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));

    DISCREPANCY discrep;
    vector<DISCREPANCY> discrepancyList;

    //long head;
    double net;
    unsigned long summaryChargeInterval = 0;

    int nfound;
    int i=0;
    nfound = listQuery.size();
    long head;
    while (listQuery.next()) {
        string _invoice_id   = DatabaseManager::valueAs<QString>(listQuery,"invoice_id").toStdString();
        double _totalColumn  = DatabaseManager::valueAs<double>(listQuery,"_totalColumn");
        string _customerId     = DatabaseManager::valueAs<QString>(listQuery,"customer_id").toStdString();
        long _head = DatabaseManager::valueAs<long>(listQuery,"head");


        INVOICE_INTERVAL;
        qryString = "SELECT sum(total) as _sumTotal FROM " + chargeSummaryTable() +
                " WHERE invoice_id=" + _invoice_id + " GROUP BY invoice_id";

        QSqlQuery tempQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));

        discrep.originalValue = _totalColumn;

        if(tempQuery.first()) {
            double _sumTotal = DatabaseManager::valueAs<double>(tempQuery,"_sumTotal");
            discrep.originalValue = addCharge(_totalColumn, _sumTotal);
        }

        summaryChargeInterval += INVOICE_INTERVAL;

#ifdef DEBUG_INVOICE_TIME
        printf("Summary Charge Time: %10.2f s\n", double(summaryChargeInterval) / 1000000);
#endif

        discrep.originalHead = _head;
        qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
        net = getInvoiceNet(_customerId, head);

        if(discrep.originalValue - net <= -0.01 || discrep.originalValue - net >= 0.01
                || discrep.originalHead != head)
        {
            discrep.recalculatedValue = net;
            discrep.customer = _customerId;
            discrep.recalculatedHead = head;
            discrep.checkDiscrep = false;
            discrepancyList.push_back(discrep);
        }
        else
        {
            if(otherDiscrep(discrep, atol(_invoice_id.c_str())))
            {
                discrep.customer = _customerId;
                discrepancyList.push_back(discrep);
            }
        }

        if(progressCallback != NULL)
        {
            progressCallback(i++, nfound);
        }
    }
qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    loadCustomerData = true;

    if(nfound < 0)
    {
        cerr << "Access error, please ensure that the following tables exist and are the correct version:" << endl
             << "\tsellerinvoicesummary," << endl
             << "\tsellerchargesummary,"  << endl
             << "\tbuyerinvoicesummary,"  << endl
             << "\tbuyerchargesummary"    << endl;
    }

    transDao.endBatchMode();

#ifdef DEBUG_INVOICE_TIME
    printTiming();
#endif

    return discrepancyList;
}

bool InvoiceDAO::otherDiscrep(DISCREPANCY& discrep, long extraLong)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return false;
}

bool SellerInvoiceDAO::otherDiscrep(DISCREPANCY& discrep, long invoiceId)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    discrep.recalculatedValue = checkDao.invoiceAmount(invoiceId);
    double diff = discrep.recalculatedValue - discrep.originalValue;

    if(diff <= -0.01 || diff >= 0.01)
    {
        discrep.checkDiscrep = true;
        return true;
    }

    return false;
}

bool SellerInvoiceDAO::isSecondCopyPrintNeeded()
{
    return SetupDAO().getBoolean("sinvSecCopyPrinterEnabled");
}



double InvoiceDAO::addCharge(double gross, double charge)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return 0;
}

double SellerInvoiceDAO::addCharge(double gross, double charge)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return gross - charge;
}

double BuyerInvoiceDAO::addCharge(double gross, double charge)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return gross + charge;
}

double InvoiceDAO::getInvoiceNet(string customer, long& head)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    head = 0;
    return 0;
}

double SellerInvoiceDAO::getInvoiceNet(string customer, long& head)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    SellerInvoice *inv = getInvoiceByCustomer(customer);

    double net = ((SellerInvoice*)inv)->net();
    head = inv->head(true, true);

    freeInvoice();
    return net;
}

double BuyerInvoiceDAO::getInvoiceNet(string customer, long& head)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    Invoice *inv = getInvoiceByCustomer(customer);
    double net = inv->net();
    head = inv->head(true, true);


    freeInvoice();
    return net;
}

string InvoiceDAO::customerTypeString()
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return "Stars I have seen them fall; but no star is lost at all; from all the star sown sky";
}

string SellerInvoiceDAO::customerTypeString()
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return "seller";
}

string BuyerInvoiceDAO::customerTypeString()
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return "buyer";
}

vector<string> SellerInvoiceDAO::getCustomersCheckList(vector<Seller> sellerList)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    string baseStartQry =
            "SELECT number FROM checkreg "
            "WHERE invoice_id=(SELECT id FROM sellerinvoice WHERE customer_id='";

    string baseEndQry =
            "' AND date='" + sale.currentSaleDateSQLString() + "') ";

    vector<string> checkNoList;
    char **record;
    long nfound;

    for(unsigned int i = 0; i < sellerList.size(); i++)
    {
        QSqlQuery checkListQuery = DatabaseManager::defaultManager.query(QString::fromStdString(baseStartQry + sellerList[i].getNumber() + baseEndQry));

        nfound = checkListQuery.size();
        if(checkListQuery.first()) {
            string _number = DatabaseManager::valueAs<QString>(checkListQuery,"number").toStdString();
            checkNoList.push_back(string((nfound > 1 ? "*" : "")) + _number);
        }
        else {
            checkNoList.push_back("");
        }
    }
    return checkNoList;
}



// void SellerInvoiceDAO::saveInvoice(SellerInvoice invoice)
// {
//   char buf[20];
//   char idStr[20];
//   sprintf(idStr, "%d", invoice.getNumber());
//   string qryString = "SELECT COUNT(*) FROM invoice WHERE id=" + string(idStr);

//   int nfound = DatabaseManager::defaultManager.query(qryString.c_str());
//   DatabaseManager::defaultManager.release_result();

//   if(nfound == 1)
//   {
//     qryString = "UPDATE ";
//   }
//   else
//   {
//     qryString = "INSERT INTO ";
//   }

//   qryString += "invoice SET ";
//   sprintf(buf, "%d", -1);
//   qryString += " status=" + string(buf);
//   sprintf(buf, "%d", invoice.getCustomer().getId());
//   qryString += "customer_id=" + string(buf);
//   qryString += "date='" + invoice.getDate().toString() + "' ";
//   qryString += (nfound > 0 ? "WHERE id=" + string(idStr) : "") + " ";
// }


bool InvoiceDAO::invoiceExists(string custId)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    string qryString = "SELECT * FROM " + invoiceTableName() + " WHERE customer_id='" + custId + "' AND date='" + sale.currentSaleDateSQLString() + "'";
    QSqlQuery invoiceExistsQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
    return (invoiceExistsQuery.first());
}

Invoice* InvoiceDAO::getInvoiceByCustomer(string custId, CommissionDAO::COLOR_GROUP group, bool getChargeStubs)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    if(!invoiceExists(custId))
    {
        saveInvoice(Invoice(0, Date::currentDate(), getCustomer(custId)));
    }

    return getInvoiceByCondition(string("customer_id='" + custId + "' "), group, getChargeStubs);
}

Customer InvoiceDAO::getCustomer(string number)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return Customer();
}

Customer SellerInvoiceDAO::getCustomer(string number)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return SellerDAO::loadFromNumber(number);
}

Customer BuyerInvoiceDAO::getCustomer(string number)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return BuyerDAO::loadFromNumber(number);
}


SellerInvoice* SellerInvoiceDAO::getInvoiceByCustomer(string custId, CommissionDAO::COLOR_GROUP group, bool getChargeStubs)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    if(!invoiceExists(custId))
    {
        saveInvoice(Invoice(0, Date::currentDate(), SellerDAO::loadFromNumber(custId)));
    }

    return (SellerInvoice*)getInvoiceByCondition("customer_id='" + custId + "' ", group, getChargeStubs);
}

BuyerInvoice* BuyerInvoiceDAO::getInvoiceByCustomer(string custId, CommissionDAO::COLOR_GROUP group, bool getChargeStubs)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    if(!invoiceExists(custId))
    {
        saveInvoice(Invoice(0, Date::currentDate(), BuyerDAO::loadFromNumber(custId)));
    }

    return (BuyerInvoice*)getInvoiceByCondition("customer_id='" + custId + "' ", group, getChargeStubs);
}

void SellerInvoiceDAO::loadInvoiceTrans(Invoice *invoice)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    invoice->setTransactionList(transDao.getTransactionListBySeller(invoice->getCustomer(), invoice->getCustomer().isBeefCouncil()));
}

SellerInvoiceDAO::SellerInvoiceDAO() : InvoiceDAO()
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
}

BuyerInvoiceDAO::BuyerInvoiceDAO() : InvoiceDAO()
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
}

BuyerInvoiceDAO::~BuyerInvoiceDAO()
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
}

void BuyerInvoiceDAO::loadInvoiceTrans(Invoice *invoice)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    invoice->setTransactionList(transDao.getTransactionListByBuyer(invoice->getCustomer()));
}


Invoice *InvoiceDAO::createInvoice(long id, Date date, string customerId, Invoice::STATUS status)
{   // Should be called only overloaded functions.
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return 0;
}

Invoice *SellerInvoiceDAO::createInvoice(long id, Date date, string customerId, Invoice::STATUS status)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return new SellerInvoice(id, date, SellerDAO::loadFromNumber(customerId),status);
}

Invoice *BuyerInvoiceDAO::createInvoice(long id, Date date, string customerId, Invoice::STATUS status)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return new BuyerInvoice(id, date, BuyerDAO::loadFromNumber(customerId),status);
}

void InvoiceDAO::saveSummary(Invoice invoice)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    char invId[20];
    char head[20];
    char gross[30];

    sprintf(invId, "%ld", invoice.getNumber());
    sprintf(head, "%ld", invoice.head(true, true));
    sprintf(gross, "%0.2f", invoice.gross());

    QString qryString = QString("REPLACE INTO " + QString::fromStdString(summaryTableName()) +
                                " SET invoice_id=:invoice_id, "
                                "head=:head, " + QString::fromStdString(totalColumnName()) + "=:totalColumnName,"
                                "customer_id=:customer_id, date=:date ");
    QSqlQuery saveQuery;
    DatabaseManager::defaultManager.prepareQuery( saveQuery,qryString);

    saveQuery.bindValue(":invoice_id"      , QVariant::fromValue<long>(invoice.getNumber()));
    saveQuery.bindValue(":head"            , QVariant::fromValue<long>(invoice.head(true, true)));
    saveQuery.bindValue(":totalColumnName" , invoice.gross());
    saveQuery.bindValue(":customer_id"     , QString::fromStdString(invoice.getCustomer().getNumber()));
    saveQuery.bindValue(":date"            , QString::fromStdString(sale.currentSaleDateSQLString()));

    DatabaseManager::defaultManager.executeQuery(saveQuery);

    saveChargeList(invoice);
}

void InvoiceDAO::deleteSummary(Customer customer)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    string qryString = "DELETE FROM " + summaryTableName() + " WHERE customer_id='" + customer.getNumber() + "' AND date='" + sale.currentSaleDateSQLString() + "' ";
    DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
}

long InvoiceDAO::noSaleHead(CommissionDAO::COLOR_GROUP)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return 0;
}

long SellerInvoiceDAO::noSaleHead(CommissionDAO::COLOR_GROUP colorGroup)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return transDao.getNoSaleHead(colorGroup);
}

InvoiceDAO::SUMMARY InvoiceDAO::getSummary(CommissionDAO::COLOR_GROUP colorGroup)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    string qryString =
            "SELECT sum(head) as _sumHead, sum(" + totalColumnName() + ") as _sumTotalColumn FROM " + summaryTableName() + " WHERE date='" + sale.currentSaleDateSQLString() + "' ";

    if(colorGroup != CommissionDAO::INVALID)
    {
        string codeRange;

        switch(colorGroup)
        {
        case CommissionDAO::FIRST:
            codeRange = "0 <= color AND color < 70";
            break;

        case CommissionDAO::SECOND:
            codeRange = "70 <= color AND color < 80";
            break;

        case CommissionDAO::THIRD:
            codeRange = "80 <= color AND color < 90";
            break;

        case CommissionDAO::FOURTH:
            codeRange = "90 <= color AND color < 100";
            break;

        case CommissionDAO::INVALID:
            cerr << "REALITY ERROR, RE-INSTALL UNIVERSE AND REBOOT" << endl;
            break;
        }

        qryString +=
                " AND customer_id IN ("
                "SELECT " + customerTypeString() + "ID FROM trans WHERE "+ codeRange + (codeRange.length() > 0 ? " and " : "") + "date='" + sale.currentSaleDateSQLString() + "')";
    }

    // [KLN] debug
//    cout << "getSummary qryString: [ " << qryString << " ]" << endl;
    // [KLN] debug end

    QSqlQuery summaryQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
    SUMMARY summary;

    summary.head = 0;
    summary.total = 0.0;
    summary.noSaleHead = 0;
    if(summaryQuery.first()) {
        long _sumHead           = DatabaseManager::valueAs<long>(summaryQuery,"_sumHead");
        double _sumTotalColumn    = DatabaseManager::valueAs<double>(summaryQuery,"_sumTotalColumn");
        summary.noSaleHead = noSaleHead(colorGroup);
        summary.head = _sumHead - summary.noSaleHead;
        summary.total = _sumTotalColumn;
        // [KLN] debug start
//        cout << "=================================================================" << endl;
//        cout << "InvoiceDAO::SUMMARY InvoiceDAO::getSummary for:" << customerTypeString() << endl;
//        cout << "  noSaleHead: " << summary.noSaleHead << endl;
//        cout << "        head: " << summary.head << endl;
//        cout << "       total: " << summary.total << endl;
//        cout << "=================================================================" << endl;
        // [KLN] debug start
    }
    return summary;
}

void InvoiceDAO::saveChargeList(Invoice inv)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    vector<ChargeRecord> chargeList = inv.getChargeRecordList();
    char invId[20], chgId[20];
    sprintf(invId, "%ld", inv.getNumber());
    char total[30];

    string qryString =
            "DELETE FROM " + chargeSummaryTable() + " WHERE invoice_id=" + string(invId) + " ";

    DatabaseManager::defaultManager.query(QString::fromStdString(qryString));

    for(unsigned int i = 0; i < chargeList.size(); i++)
    {
        QSqlQuery saveChargeQuery;
        QString qryString = QString("INSERT INTO " + QString::fromStdString(chargeSummaryTable()) + " SET "
                                    "invoice_id=:invoice_id, charge_id=:charge_id, total=:total, "
                                    "description=:description");
        DatabaseManager::defaultManager.prepareQuery(saveChargeQuery,qryString);

        saveChargeQuery.bindValue(":invoice_id" , QVariant::fromValue<long>(inv.getNumber()));
        saveChargeQuery.bindValue(":charge_id"  , QVariant::fromValue<long>(chargeList[i].getId()));
        saveChargeQuery.bindValue(":total"      , QVariant::fromValue<double>(chargeList[i].getAdjustedTotal()));
        saveChargeQuery.bindValue(":description", QString::fromStdString(chargeList[i].getDescrip()));

        DatabaseManager::defaultManager.executeQuery(saveChargeQuery);
    }

    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    sprintf(chgId, "0");

    sprintf(total, "%0.2f", inv.getCommissionTotal(true));
    qryString =
            "INSERT INTO " + chargeSummaryTable() + " SET invoice_id=" + string(invId) + ", "
            "charge_id="+ string(chgId) + ", total=" + string(total) + ", description='COMMISSION' ";

    DatabaseManager::defaultManager.query(QString::fromStdString(qryString));

    // probably a bad idea, but this is the quickest way I could think of to include trucking in the summary

    sprintf(chgId, "-1");
    sprintf(total, "%0.2f", inv.truckingTotal());
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    qryString =
            "INSERT INTO " + chargeSummaryTable() + " SET invoice_id=" + string(invId) + ", "
            "charge_id="+ string(chgId) + ", total=" + string(total) + ", description='TRUCKING' ";

    DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
}



string InvoiceDAO::summaryTableName()
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return "UNDEF";
}

string InvoiceDAO::totalColumnName()
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return "UNDEF";
}

string InvoiceDAO::chargeSummaryTable()
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return "";
}

string SellerInvoiceDAO::chargeSummaryTable()
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return "sellerchargesummary";
}

string BuyerInvoiceDAO::chargeSummaryTable()
{
   qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return "buyerchargesummary";
}

string BuyerInvoiceDAO::summaryTableName()
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return "buyerinvoicesummary";
}

string BuyerInvoiceDAO::totalColumnName()
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return "total_bought";
}


string SellerInvoiceDAO::summaryTableName()
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return "sellerinvoicesummary";
}

string SellerInvoiceDAO::totalColumnName()
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return "total_sale";
}

/////////////////////////////////////////////////////////
//  everything below this line involves the setup table;
//

vector<int> InvoiceDAO::getColumnList()
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    vector<string> keyList = getInvKeyList();
    vector<string> colStrings;
    colStrings = setupDao.get(keyList);
    vector<int> colList(TextInvoice::ColumnCount, TextInvoice::IgnoreCol);

    colList[TextInvoice::TransNo] = atoi(colStrings[TextInvoice::TransNo].c_str()) - 1;
    colList[TextInvoice::Head] = atoi(colStrings[TextInvoice::Head].c_str()) - 1 ;
    colList[TextInvoice::Descrip] = atoi(colStrings[TextInvoice::Descrip].c_str()) - 1;
    colList[TextInvoice::CustomerNo] = atoi(colStrings[TextInvoice::CustomerNo].c_str()) - 1;
    colList[TextInvoice::Tags] = atoi(colStrings[TextInvoice::Tags].c_str()) - 1;
    colList[TextInvoice::TotWt] = atoi(colStrings[TextInvoice::TotWt].c_str()) - 1;
    colList[TextInvoice::AvgWt] = atoi(colStrings[TextInvoice::AvgWt].c_str()) - 1;
    colList[TextInvoice::DolPerHd] = atoi(colStrings[TextInvoice::DolPerHd].c_str()) - 1;
    colList[TextInvoice::DolPerCW] = atoi(colStrings[TextInvoice::DolPerCW].c_str()) - 1;
    colList[TextInvoice::Amount] = atoi(colStrings[TextInvoice::Amount].c_str()) - 1;
    colList[TextInvoice::Pen] = atoi(colStrings[TextInvoice::Pen].c_str()) - 1;

    return colList;
}

void InvoiceDAO::saveColumnList(vector<int> colList)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    vector<string> colStrings;
    vector<int>::iterator current;
    char buf[5];
    for(current = colList.begin(); current != colList.end(); current++)
    {
        sprintf(buf, "%d", (*current) + 1);
        colStrings.push_back(buf);
    }

    setupDao.set(getInvKeyList(), colStrings);
}

vector<string> InvoiceDAO::getInvKeyList()
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    vector<string> keyList(TextInvoice::ColumnCount, "");

    keyList[TextInvoice::TransNo]    = keyPrefix() + "ColTrans";
    keyList[TextInvoice::Head]       = keyPrefix() + "ColHead";
    keyList[TextInvoice::Descrip]    = keyPrefix() + "ColDesc";
    keyList[TextInvoice::CustomerNo] = keyPrefix() + "ColCustNo";
    keyList[TextInvoice::Tags]       = keyPrefix() + "ColTags";
    keyList[TextInvoice::TotWt]      = keyPrefix() + "ColWeight";
    keyList[TextInvoice::AvgWt]      = keyPrefix() + "ColAvgWt";
    keyList[TextInvoice::DolPerHd]   = keyPrefix() + "ColPPHd";
    keyList[TextInvoice::DolPerCW]   = keyPrefix() + "ColPPHW";
    keyList[TextInvoice::Amount]     = keyPrefix() + "ColAmount";
    keyList[TextInvoice::Pen]        = keyPrefix() + "ColPen";

    return keyList;
}

string InvoiceDAO::keyPrefix()
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return "";
}

string SellerInvoiceDAO::keyPrefix()
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return "sinv";
}

string BuyerInvoiceDAO::keyPrefix()
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return "binv";
}

bool InvoiceDAO::checkOnInvoice()
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return false;
}

void InvoiceDAO::setCheckOnInvoice(bool chkOnInvoice)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    char coiStr[3];
    sprintf(coiStr, "%d", chkOnInvoice);
    setupDao.set("sinvChkOnInvoice", coiStr);
}

bool SellerInvoiceDAO::checkOnInvoice()
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return bool(atoi(setupDao.get("sinvChkOnInvoice").c_str()));
}

void SellerInvoiceDAO::setCheckOnInvoice(bool chkOnInvoice)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    char buf[4];
    sprintf(buf, "%d", chkOnInvoice);
    setupDao.set("sinvChkOnInvoice", buf);
}

unsigned int InvoiceDAO::checkStart()
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return 0;
}

unsigned int SellerInvoiceDAO::checkStart()
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return atoi(setupDao.get("sinvChkStart").c_str());
}

void InvoiceDAO::setCheckStart(unsigned int whocares)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    // this exists only so that the interface will be common
    // check data should only be saved for Seller invoices
}

void InvoiceDAO::setShowName(bool showName)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
}

void SellerInvoiceDAO::setShowName(bool showName)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    char buf[3];
    sprintf(buf, "%d", showName);
    setup.set("sinvShowBuyerName", buf);
}

void BuyerInvoiceDAO::setShowName(bool showName)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    char buf[3];
    sprintf(buf, "%d", showName);
    setup.set("binvShowSellerName", buf);
}

bool InvoiceDAO::showName()
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return false;
}

bool SellerInvoiceDAO::showName()
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return bool(atoi(setup.get("sinvShowBuyerName").c_str()));
}

bool BuyerInvoiceDAO::showName()
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return bool(atoi(setup.get("binvShowSellerName").c_str()));
}


void SellerInvoiceDAO::setCheckStart(unsigned int chkStart)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    char buf[10];
    sprintf(buf, "%d", chkStart);
    setupDao.set("sinvChkStart", buf);
}

unsigned int InvoiceDAO::pageHeight()
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return (unsigned int)atoi(SetupDAO().get(keyPrefix() + "PageLen").c_str());;
}

unsigned int InvoiceDAO::chkStartCopy()
{
    return (unsigned int)atoi(SetupDAO().get(keyPrefix() + "ChkStartCopy").c_str());;
}



void InvoiceDAO::setPageHeight(unsigned int lineCount)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    char buf[10];
    sprintf(buf, "%d", lineCount);
    setupDao.set(keyPrefix() + "PageLen", buf);
}


unsigned int InvoiceDAO::topSkip()
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return (unsigned int)atoi(SetupDAO().get(keyPrefix() + "TopSkip").c_str());
}

void InvoiceDAO::setTopSkip(unsigned int lineCount)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    char buf[10];
    sprintf(buf, "%d", lineCount);
    setupDao.set(keyPrefix() + "TopSkip", buf);
}

vector<string> InvoiceDAO::getReadyList(bool getName)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    char status[20];

    vector<string> readyList;

    sprintf(status, "%d", Invoice::UNPAID);
    string dateString = sale.currentSaleDateSQLString();

    string qryString = "SELECT id FROM " + customerTypeString() + "invoice WHERE date='" + dateString + "' ";

    QSqlQuery readyListQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));

    string invoiceIdString;
    int nfound = readyListQuery.size();
    int i = 0;
    while (readyListQuery.next()) {
        string _id = DatabaseManager::valueAs<QString>(readyListQuery,"id").toStdString();
        invoiceIdString += _id + string(i == nfound - 1 ? "" : ",");
        i++;
    }

    string customerIdString;
qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    if(invoiceIdString.length() > 0)
    {
        qryString =
                "SELECT customer_id FROM " + customerTypeString() + "invoicesummary WHERE invoice_id IN(" + invoiceIdString + ") ";


        QSqlQuery invoiceSummaryQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
        nfound = invoiceSummaryQuery.size();
        i = 0;
        while (invoiceSummaryQuery.next()) {
            string _customer_id = DatabaseManager::valueAs<QString>(invoiceSummaryQuery,"customer_id").toStdString();
            customerIdString += string("'") + _customer_id + "'" + string(i == nfound - 1 ? "" : ",");
            i++;
        }
    }
qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    //  qryString =
    //    "SELECT id, number, name FROM " + customerTypeString() + " WHERE date='" + dateString + "' AND number NOT IN("
    //    "SELECT customer_id FROM " + customerTypeString() + "invoicesummary WHERE invoice_id IN("
    //    "SELECT id FROM " + customerTypeString() + "invoice WHERE date='" + dateString + "')) ";

    qryString =
            "SELECT id, number, name FROM " + customerTypeString() + " WHERE date='" + dateString + "' "
            "" + (customerIdString.length() > 0 ? "AND number NOT IN(" + customerIdString + ") " : "") + "";

    QSqlQuery customQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));

    i=0;
    nfound = customQuery.size();
qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    if( nfound == 0 ) {
        cerr << "Error accessing the correct tables, ensure that the following tables are installed and the correct version:" << endl
             << "\t" << customerTypeString()                     << endl
             << "\t" << customerTypeString() << "invoicesummary" << endl
             << "\t" << customerTypeString() << "invoice"        << endl;

        return readyList;
    }

    string customer;

    transDao.startBatchMode(false, false, false);
    AnimalCodeDAO::startBatchMode();

qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    while (customQuery.next())  {
        customer = DatabaseManager::valueAs<QString>(customQuery,"number").toStdString();
        string _name = DatabaseManager::valueAs<QString>(customQuery,"name").toStdString();
        if(invoiceReady(customer))
        {
            readyList.push_back(customer + (getName ? string(", ") +  _name : ""));
        }

        if(progressCallback != NULL)
        {
            progressCallback(i++, nfound);
        }
    }
    transDao.endBatchMode();
    AnimalCodeDAO::endBatchMode();
qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return readyList;
}


bool InvoiceDAO::invoiceReady(string)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return true;
}

bool SellerInvoiceDAO::invoiceReady(string customer)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    bool ready = false;

    /*
    string qryString =
      "SELECT sum(trans.head) - " + customerTypeString() + ".head FROM trans CROSS JOIN seller WHERE "
      "trans." + customerTypeString() + "ID='" + customer + "' AND trans.date='" + sale.currentSaleDateSQLString() + "' AND "
      + customerTypeString() + ".date='" + sale.currentSaleDateSQLString() + "' AND " + customerTypeString() + ".number='" + customer + "'";
*/

    //  string qryString = "SELECT head FROM seller WHERE date='" + sale.currentSaleDateSQLString() + "' AND number='" + customer + "' ";
    Seller seller = SellerDAO::loadFromNumber(customer);
qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    SellerInvoice invoice = *getInvoiceByCustomer(customer);
    /*
    if(DatabaseManager::defaultManager.query(qryString.c_str()) > 0)
    {
      char **record;
      record = DatabaseManager::defaultManager.get_record();

      if(record[0] != NULL)// && atoi(record[0]) == 0)
      {
ready = seller = 
//	ready = true;
      }
    }

    DatabaseManager::defaultManager.release_result();
*/
qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return (seller.getHead() != 0 && seller.getHead() == invoice.head(true, false));
}

string InvoiceDAO::invoiceTableName()
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return "invoice";
}


string SellerInvoiceDAO::invoiceTableName()
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return "sellerinvoice";
}


string BuyerInvoiceDAO::invoiceTableName()
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return "buyerinvoice";
}

vector<BuyerInvoice> BuyerInvoiceDAO::getBuyerInvoiceList(bool loadCustomerInfo, bool loadTags, bool loadCharges)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    vector<string> buyerNumberList = transDao.uniqueBuyerIdList();
    sort(buyerNumberList.begin(), buyerNumberList.end(), Customer::compareCustomerNumbersLT);

    vector<BuyerInvoice> buyerInvoiceList;
    BuyerInvoice* temp;

    transDao.startBatchMode(loadCustomerInfo, loadTags, loadCharges);

    for(unsigned int i = 0; i < buyerNumberList.size(); i++)
    {
        temp = getInvoiceByCustomer(buyerNumberList[i]);

        if(temp->getTransactionList().size() > 0)
        {
            buyerInvoiceList.push_back(*temp);
        }

        freeInvoice();

        if(progressCallback != NULL)
        {
            progressCallback(i + 1, buyerNumberList.size());
        }
    }
    transDao.endBatchMode();
    return buyerInvoiceList;
}

BuyerRecap BuyerInvoiceDAO::getBuyerRecap(vector<string> buyerNumberList, string reportName, bool consolidateCharges, vector<ChargeRecord> recapCharges)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    vector<BuyerInvoice> buyerInvoiceList;
    BuyerInvoice* temp;

    for(unsigned int i = 0; i < buyerNumberList.size(); i++)
    {
        temp = getInvoiceByCustomer(buyerNumberList[i]);

        if(temp->getTransactionList().size() > 0)
        {
            buyerInvoiceList.push_back(*temp);
        }

        freeInvoice();
    }
qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    vector<string> unprintedBuyers = getUnprintedCustomerList();
    return  BuyerRecap(buyerInvoiceList, reportName , Date::currentDate(), unprintedBuyers, consolidateCharges, recapCharges);
}



ChargeDAO::CUST_TYPE InvoiceDAO::chargeType()
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return ChargeDAO::Seller;
}

ChargeDAO::CUST_TYPE SellerInvoiceDAO::chargeType()
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return ChargeDAO::Seller;
}

ChargeDAO::CUST_TYPE BuyerInvoiceDAO::chargeType()
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return ChargeDAO::Buyer;
}

vector<string> BuyerInvoiceDAO::getReadyList(bool getNames)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return getUnprintedCustomerList();
}

vector<BuyerAR::Record> BuyerInvoiceDAO::getBuyerAccountsList()
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    string qryString = "SELECT distinct(buyerID) as _buyerId FROM trans WHERE date='" + sale.currentSaleDateSQLString() + "' AND mode!=0";

    QSqlQuery buyerQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
    vector<BuyerAR::Record> recordList;
    AnimalCodeDAO::startBatchMode();
    transDao.startBatchMode(true, false, true);
    BuyerInvoice *tempInvoice;

    long nfound = buyerQuery.size();
    long i= 1;
    while (buyerQuery.next()) {
        string _buyerId = DatabaseManager::valueAs<QString>(buyerQuery,"_buyerId").toStdString();
        tempInvoice = getInvoiceByCustomer(_buyerId);
            recordList.push_back(BuyerAR::Record(tempInvoice->getCustomer().getNumber(),
                                                 tempInvoice->getCustomer().getName().getLast(),
                                                 tempInvoice->getCustomer().getCompany(),
                                                 tempInvoice->getStatus(),
                                                 ((BuyerInvoice*)tempInvoice)->net(),
                                                 printed(*tempInvoice)));
            freeInvoice();

            if(progressCallback != NULL)
            {
                progressCallback(i++, nfound);
            }
    }
    transDao.endBatchMode();
    AnimalCodeDAO::endBatchMode();
    return recordList;
}

vector<InvoiceSummaryRecord> InvoiceDAO::getInvoiceSummaryRecordList(AnimalCode::Group colorGroup)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    string dateString = sale.currentSaleDateSQLString();

    string qryString =
            "SELECT invoice_id, " + summaryTableName() + ".head as _head, " + totalColumnName() + " as _colName, " + summaryTableName() + ".customer_id as custom_id, name "
            "FROM " + summaryTableName() + " CROSS JOIN " + customerTypeString() + " "
            "WHERE " + summaryTableName() +".date='" + dateString + "' "
            "AND (" + summaryTableName() + ".customer_id=number AND " + customerTypeString() + ".date='" + dateString + "') ";
    string codeRange;
    if(colorGroup != AnimalCode::Invalid)
    {


        switch(colorGroup)
        {
        case AnimalCode::First:
            codeRange = "0 <= color AND color < 70";
            break;

        case AnimalCode::Second:
            codeRange = "70 <= color AND color < 80";
            break;

        case AnimalCode::Third:
            codeRange = "80 <= color AND color < 90";
            break;

        case AnimalCode::Fourth:
            codeRange = "90 <= color AND color < 100";
            break;

        case AnimalCode::Invalid:
            cerr << "REALITY ERROR, RE-INSTALL UNIVERSE AND REBOOT" << endl;
            break;
        }

        qryString +=
                " AND " + summaryTableName() + ".customer_id IN ("
                "SELECT " + customerTypeString() + "ID FROM trans WHERE "+ codeRange + (codeRange.length() > 0 ? " and " : "") + "date='" + dateString + "')";
    }


qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    QSqlQuery summaryQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
    vector<InvoiceSummaryRecord> recordList;

    long nfound = summaryQuery.size();
    long i = 0;
    while (summaryQuery.next()) {

        long _invoice_id   = DatabaseManager::valueAs<long>(summaryQuery,"invoice_id");
        long _head         = DatabaseManager::valueAs<long>(summaryQuery,"_head");
        double _colName    = DatabaseManager::valueAs<double>(summaryQuery,"_colName");
        string custom_id   = DatabaseManager::valueAs<QString>(summaryQuery,"custom_id").toStdString();
        string _name       = DatabaseManager::valueAs<QString>(summaryQuery,"name").toStdString();

        recordList.push_back(InvoiceSummaryRecord(custom_id, _name, _head, _colName,
                                                  chargeDao.getChargeSummaryRecordList(_invoice_id, chargeType()), getCustomerCheckList(custom_id)));
        if(progressCallback != NULL)
        {
            progressCallback(i++, nfound);
        }
    }
qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return recordList;
}

vector<string> InvoiceDAO::getCustomerCheckList(string customerNumber)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return vector<string>();
}

vector<string> SellerInvoiceDAO::getCustomerCheckList(string customerNumber)
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return checkDao.getCustomerCheckNumberList(customerNumber);
}

vector<string> SellerInvoiceDAO::customersPrintedWithoutChecks()
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    string qryString =
            "SELECT customer_id from sellerinvoicesummary "
            "where invoice_id not in "
            "(select invoice_id from checkreg where status != 1 and type=1) and "
            "date='" + sale.currentSaleDateSQLString() + "'";

    vector<string> customerList;

    QSqlQuery customerIdQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));

    while (customerIdQuery.next()) {
        string _customerId = DatabaseManager::valueAs<QString>(customerIdQuery,"customer_id").toStdString();
        customerList.push_back(_customerId);
    }
qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return customerList;
}

Customer::Type InvoiceDAO::customerType()
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return Customer::Seller;
}

Customer::Type SellerInvoiceDAO::customerType()
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return Customer::Seller;
}

Customer::Type BuyerInvoiceDAO::customerType()
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return Customer::Buyer;
}

InvoiceDAO::ProgressCallback InvoiceDAO::getProgressCallback()
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    return progressCallback;
}

unsigned int InvoiceDAO::laserCopyCount()
{
    qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;
    unsigned int copyCount = (unsigned int)atoi(SetupDAO().get(keyPrefix() + "LaserCopyCount").c_str());
    if (copyCount == 0) {
        copyCount = 1;
    }
    return copyCount;
}

bool InvoiceDAO::isSecondCopyPrintNeeded()
{
    return false;
}
