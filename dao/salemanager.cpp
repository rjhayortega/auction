#include "salemanager.h"

Date SaleManager::saleDate = Date();
string SaleManager::saleDateSQLString = Date().toString("YYYY-mm-dd");

bool SaleManager::saleOpen = true;

string SaleManager::currentSaleDateSQLString()
{
    return saleDateSQLString;
}

vector<Sale> SaleManager::getSaleList()
{
    QString qryString = "SELECT START, OPEN FROM sales ORDER BY START DESC";
    QSqlQuery saleListQuery = DatabaseManager::defaultManager.query(qryString);
    vector<Sale> saleList;
    while (saleListQuery.next()) {
        string _startDate = DatabaseManager::valueAs<QString>(saleListQuery,"START").toStdString();
        bool   _open      = DatabaseManager::valueAs<bool>(saleListQuery,"OPEN");

        saleList.push_back(Sale(Date::fromString(_startDate,"YYYY-mm-dd"), _open));
    }

    return saleList;
}

void SaleManager::createSale(Date newSaleDate)
{
    if(newSaleDate == Date())
    {
        newSaleDate = Date::currentDate();
    }

    string dateStr = newSaleDate.toString("YYYY-mm-dd");
    string qryString = "SELECT start FROM sales WHERE date='" + dateStr + "'";

    QSqlQuery createSaleQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
    if(!createSaleQuery.first()) {
        QSqlQuery replaceQuery;
        QString qryString = QString("REPLACE INTO sales SET START=:start, DATE=:date, "
                                    "END=:end, OPEN=1, SEL=0");
        DatabaseManager::defaultManager.prepareQuery(replaceQuery,qryString);
        replaceQuery.bindValue(":start" ,QString::fromStdString(dateStr));
        replaceQuery.bindValue(":date"  ,QString::fromStdString(dateStr));
        replaceQuery.bindValue(":end"   ,QString::fromStdString(dateStr));

        DatabaseManager::defaultManager.executeQuery(replaceQuery);
    }
}

void SaleManager::setCurrentSale(Sale sale, bool updateSystem)
{
    if(sale.open && updateSystem)
    {
        setDBCurrent(sale.date);
    }

    SaleManager::saleDate = sale.date;
    SaleManager::saleDateSQLString = saleDate.toString("YYYY-mm-dd");
    SaleManager::saleOpen = sale.open;
}

void SaleManager::setDBCurrent(Sale sale)
{
    string qryString =
            "UPDATE sales SET SEL=0";

    DatabaseManager::defaultManager.query(qryString.c_str());

    qryString = "UPDATE sales SET SEL=1 WHERE DATE='" + sale.date.toString("YYYY-mm-dd") + "'";
    DatabaseManager::defaultManager.query(qryString.c_str());
}

Date SaleManager::currentSaleDate()
{
    return SaleManager::saleDate;
}

bool SaleManager::currentSaleOpen()
{
    return SaleManager::saleOpen;
}

Sale SaleManager::mostRecentSale()
{
    string qryString = "SELECT START, OPEN FROM sales WHERE SEL=1";
    QSqlQuery mostRecentQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
    Sale sale;
    if(mostRecentQuery.first() ) {
        string _start = DatabaseManager::valueAs<QString>(mostRecentQuery,"START").toStdString();
        bool _open    = DatabaseManager::valueAs<bool>(mostRecentQuery,"OPEN");

        sale.date = Date::fromString(_start, "YYYY-mm-dd");
        sale.open = bool(_open);
    }

    return sale;
}

void SaleManager::closeSale(Sale& sale)
{
    sale.open = false;
    string qryString = "UPDATE sales SET open=0 WHERE date='" + sale.date.toString("YYYY-mm-dd") + "' ";
    cout << "closeSale query:  " << qryString << endl;
    DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
}

// KLN add
void SaleManager::openSale(Sale& sale)
{
    sale.open = true;
    string qryString = "UPDATE sales SET open=1 WHERE date='" + sale.date.toString("YYYY-mm-dd") + "' ";
    DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
}

bool SaleManager::isSaleOpen(Sale& sale)
{
    bool isOpen = false;

    string qryString = "SELECT OPEN FROM sales WHERE date='" + sale.date.toString("YYYY-mm-dd") + "' ";
    cout << ">>> qry:  " << qryString << " >>>" << endl;
    QSqlQuery mostRecentQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));

    if(mostRecentQuery.first() ) {
        isOpen = DatabaseManager::valueAs<bool>(mostRecentQuery,"OPEN");
    }

    return (isOpen);
}

bool SaleManager::isSaleActive(Sale& sale)
{
    bool isActive = false;

    string qryString = "SELECT SEL FROM sales WHERE date='" + sale.date.toString("YYYY-mm-dd") + "' ";
    QSqlQuery mostRecentQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));

    if(mostRecentQuery.first() ) {
        isActive = DatabaseManager::valueAs<bool>(mostRecentQuery,"SEL");
    }

    return (isActive);
}

// KLN add end

Date SaleManager::maxNextNonSaleDay()
{
    string qryStr = "SELECT MIN(start) AS _minStart FROM sales WHERE date > '" + currentSaleDateSQLString() + "' ";

    QSqlQuery nextSaleQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryStr));

    if(nextSaleQuery.first()) {
        QString minStart = DatabaseManager::valueAs<QString>(nextSaleQuery,"_minStart");
        if ( !minStart.isEmpty() ) {
            string _minStart = minStart.toStdString();
            Date date = Date::fromString(_minStart, "YYYY-mm-dd");
            date.addDays(-1);
            return date;
        }
    }
    return Date::currentDate();
}
