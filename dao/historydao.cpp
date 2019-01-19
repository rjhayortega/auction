
#include "historydao.h"

vector<HistoryItem> HistoryDAO::getBuyerHistoryList(string buyerName, Date startDate, Date endDate)
{
    string condStr = string("buyer.number = trans.buyerID and buyer.date = trans.date and buyer.name=:buyerName") +
            string(" and seller.number=trans.sellerID and seller.date=trans.date");
    string altCondStr = "buyer_name=:buyer_name1 ";

    QSqlQuery buyerHistoryQuery;
    string qryString = getQueryString(condStr, altCondStr, startDate, endDate);
    QString queryString = QString::fromStdString(qryString);
    DatabaseManager::defaultManager.prepareQuery(buyerHistoryQuery,queryString);
    buyerHistoryQuery.bindValue(":buyerName"  , (buyerName.empty())? QVariant(QVariant::String) : QString::fromStdString(buyerName));
    buyerHistoryQuery.bindValue(":buyerName1" , (buyerName.empty())? QVariant(QVariant::String) : QString::fromStdString(buyerName));
    return getHistoryListByCondition(buyerHistoryQuery);
}

vector<HistoryItem> HistoryDAO::getSellerHistoryList(string sellerName, Date startDate, Date endDate)
{
    string condStr = string("buyer.number = trans.buyerID and buyer.date = trans.date and seller.name=:sellerName")
            + string(" and seller.number=trans.sellerID and seller.date=trans.date");
    string altCondStr = "seller_name =:seller_name1";

    QSqlQuery sellerHistoryQuery;
    string qryString = getQueryString(condStr, altCondStr, startDate, endDate);
    QString queryString = QString::fromStdString(qryString);
    DatabaseManager::defaultManager.prepareQuery(sellerHistoryQuery,queryString);
    sellerHistoryQuery.bindValue(":sellerName"   , (sellerName.empty())? QVariant(QVariant::String) : QString::fromStdString(sellerName));
    sellerHistoryQuery.bindValue(":seller_name1" , (sellerName.empty())? QVariant(QVariant::String) : QString::fromStdString(sellerName));
    return getHistoryListByCondition(sellerHistoryQuery);

}

vector<HistoryItem> HistoryDAO::getDateHistoryList(Date startDate, Date endDate)
{
    string condStr = "buyer.number = trans.buyerID and buyer.date = trans.date and seller.number=trans.sellerID and seller.date=trans.date";
    string altCondStr;
    return getHistoryListByCondition(condStr, altCondStr, startDate, endDate);
}

vector<HistoryItem> HistoryDAO::getAnimalHistoryList(AnimalCode code, Date startDate, Date endDate)
{
    char type[3], color[3], flaw[3];
    sprintf(type, "%d", code.getType());
    sprintf(color, "%d", code.getColor());
    sprintf(flaw, "%d", code.getFlaw());

    string condStr = "buyer.number = trans.buyerID and buyer.date = trans.date and trans.color=" + string(color) + " and trans.type=" + string(type) + " and trans.flaw=" + string(flaw) + " and seller.number=trans.sellerID and seller.date=trans.date";
    string altCondStr = "description like '%" + code.getDescrip() + "%' ";

    return getHistoryListByCondition(condStr, altCondStr, startDate, endDate);
}


vector<HistoryItem> HistoryDAO::getHistoryListByCondition(string condStr, string altCondStr, Date startDate, Date endDate)
{
    string qryStr =
            "SELECT trans.date, trans.trans_id, seller.number, seller.name, buyer.number as _number, "
            "buyer.name as _name, trans.head, trans.weight, trans.type, trans.color, "
            "trans.flaw, trans.descrip, trans.price, trans.mode, trans.weighmaster, trans.descrip "
            "from buyer cross join trans cross join seller where ";


    string dateCondStr =
            " AND trans.date >= '" + startDate.toString("YYYY-mm-dd") + "' AND trans.date <= '" + endDate.toString("YYYY-mm-dd") + "' AND "
            "buyer.date >= '" + startDate.toString("YYYY-mm-dd") + "' AND buyer.date <= '" + endDate.toString("YYYY-mm-dd") + "' AND "
            "seller.date >= '" + startDate.toString("YYYY-mm-dd") + "' AND seller.date <= '" + endDate.toString("YYYY-mm-dd") + "'";


    string altQryStr;
    altQryStr =
            "SELECT "
            "date, "
            "transaction_id, "
            "seller_number, "
            "seller_name, "
            "buyer_number, "
            "buyer_name, "
            "head, "
            "weight, "
            "0,0,0, "
            "description, "
            "price, "
            "mode, "
            "weighmaster, "
            "description "
            "FROM history "
            "WHERE "
            "date >= '" + startDate.toString("YYYY-mm-dd") + "' AND date <= '" + endDate.toString("YYYY-mm-dd") + "' "
            "" + (altCondStr.length() > 0 ? "AND " : "") + ""
            "" + (altCondStr.length() > 0 ? "(" + altCondStr + ")" : "") + ""
            "";

    qryStr += condStr + dateCondStr + (altQryStr.length() > 0 ? " UNION " : "") + altQryStr;

    QSqlQuery historyQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryStr));

    vector<HistoryItem> historyList;
    int sex = 0;
    int color = 0;
    int flaw = 0;

    while (historyQuery.next()) {
        sex   = DatabaseManager::valueAs<int>(historyQuery,"type");
        color = DatabaseManager::valueAs<int>(historyQuery,"color");
        flaw  = DatabaseManager::valueAs<int>(historyQuery,"flaw");
        string  _animalDescript = DatabaseManager::valueAs<QString>(historyQuery,"descrip").toStdString();

        string _date            = DatabaseManager::valueAs<QString>(historyQuery,"date").toStdString();
        long _trans_id          = DatabaseManager::valueAs<long>(historyQuery,"trans_id");
        string _seller_number   = DatabaseManager::valueAs<QString>(historyQuery,"number").toStdString();
        string _seller_name     = DatabaseManager::valueAs<QString>(historyQuery,"name").toStdString();

        string _buyer_number    = DatabaseManager::valueAs<QString>(historyQuery,"_number").toStdString();
        string _buyer_name      = DatabaseManager::valueAs<QString>(historyQuery,"_name").toStdString();

        long _trans_head        = DatabaseManager::valueAs<long>(historyQuery,"head");
        long _trans_weight      = DatabaseManager::valueAs<long>(historyQuery,"weight");

        double _trans_price     = DatabaseManager::valueAs<long>(historyQuery,"price");
        int    _trans_mode      = DatabaseManager::valueAs<int>(historyQuery,"mode");
        string _trans_weighmaster = DatabaseManager::valueAs<QString>(historyQuery,"weighmaster").toStdString();

        AnimalCode tempCode;

        if(sex == 0 && color == 0 && flaw == 0) {
            tempCode = AnimalCode::fromString(_animalDescript);
            tempCode.setDescrip("");
        }
        else {
            tempCode = AnimalCode(sex, color, flaw);
            tempCode.setDescrip(_animalDescript);
        }

        historyList.push_back(HistoryItem(Date::fromString(_date, "YYYY-mm-dd"), _trans_id, _seller_number, _seller_name,
                                          _buyer_number, _buyer_name, _trans_head, _trans_weight, tempCode,
                                          _trans_price, Transaction::SALE_MODE(_trans_mode), _trans_weighmaster));
    }
    AnimalCodeDAO codeDao;

    for(unsigned int i = 0; i < historyList.size(); i++) {
        if(historyList[i].getCode().getDescrip() == "-") {
            AnimalCode temp = historyList[i].getCode();
            codeDao.fillAnimalCode(temp);
            historyList[i].setAnimalCode(temp);
        }
    }
    return historyList;
}


vector<HistoryItem> HistoryDAO::getSellerInvoiceHistoryList(Date startDate, Date endDate)
{
    string qryString =
            "SELECT "
            "sellerinvoicesummary.head, "
            "sellerinvoicesummary.total_sale, " //- sum(sellerchargesummary.total), "
            "seller.name, sellerinvoicesummary.date "
            "from sellerinvoicesummary cross join seller cross join sellerchargesummary "
            "where seller.number=sellerinvoicesummary.customer_id and "
            "seller.date=sellerinvoicesummary.date and "
            "sellerchargesummary.invoice_id=sellerinvoicesummary.invoice_id and "
            "sellerinvoicesummary.date >= '" + startDate.toString("YYYY-mm-dd") + "' and sellerinvoicesummary.date <= '" + endDate.toString("YYYY-mm-dd") + "' and "
            "seller.date >= '" + startDate.toString("YYYY-mm-dd") + "' and seller.date <= '" + endDate.toString("YYYY-mm-dd") + "' "
            "group by sellerchargesummary.invoice_id";

    string altQryStr =
            "SELECT "
            "head, (weight / 100) * price, seller_name, date "
            "FROM history WHERE date >= '" + startDate.toString("YYYY-mm-dd") + "' AND date <= '" + endDate.toString("YYYY-mm-dd") + "' AND (mode=1 OR mode=5) "
            "UNION "
            "SELECT "
            "head, head * price, seller_name, date "
            "FROM history WHERE date >= '" + startDate.toString("YYYY-mm-dd") + "' AND date <= '" + endDate.toString("YYYY-mm-dd") + "' AND (mode=2 OR mode=6) ";


    vector<HistoryItem> historyList;
    QSqlQuery sellerHistoryQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString + " UNION " + altQryStr));


    while (sellerHistoryQuery.next()) {
        long head               = DatabaseManager::valueAs<long>(sellerHistoryQuery,"head");
        string _date            = DatabaseManager::valueAs<QString>(sellerHistoryQuery,"date").toStdString();
        string customerName     = DatabaseManager::valueAs<QString>(sellerHistoryQuery,"name").toStdString();
        double net              = DatabaseManager::valueAs<double>(sellerHistoryQuery,"total_sale");
        Date date = Date::fromString(_date, "YYYY-mm-dd");
        historyList.push_back(HistoryItem(date, head, customerName, net));
    }
    sort(historyList.begin(), historyList.end(), HistoryItem::compareSellerNamesLT);
    stable_sort(historyList.begin(), historyList.end(), HistoryItem::compareDatesLT);
    return historyList;
}

vector<HistoryItem> HistoryDAO::getBuyerInvoiceHistoryList(Date startDate, Date endDate)
{
    string qryString =
            "SELECT "
            "buyerinvoicesummary.head, "
            "buyerinvoicesummary.total_bought, " // - sum(buyerchargesummary.total), "
            "buyer.name, buyerinvoicesummary.date "
            "from buyerinvoicesummary cross join buyer cross join buyerchargesummary "
            "where buyer.number=buyerinvoicesummary.customer_id and "
            "buyer.date=buyerinvoicesummary.date and "
            "buyerchargesummary.invoice_id=buyerinvoicesummary.invoice_id and "
            "buyerinvoicesummary.date >= '" + startDate.toString("YYYY-mm-dd") + "' and buyerinvoicesummary.date <= '" + endDate.toString("YYYY-mm-dd") + "' and "
            "buyer.date >= '" + startDate.toString("YYYY-mm-dd") + "' and buyer.date <= '" + endDate.toString("YYYY-mm-dd") + "' "
            "group by buyerchargesummary.invoice_id";

    string altQryStr =
            "SELECT "
            "head, (weight / 100) * price, buyer_name, date "
            "FROM history WHERE date >= '" + startDate.toString("YYYY-mm-dd") + "' AND date <= '" + endDate.toString("YYYY-mm-dd") + "' AND (mode=1 OR mode=5)"
            "UNION "
            "SELECT "
            "head, head * price, buyer_name, date "
            "FROM history WHERE date >= '" + startDate.toString("YYYY-mm-dd") + "' AND date <= '" + endDate.toString("YYYY-mm-dd") + "' AND (mode=2 OR mode=6)";


    vector<HistoryItem> historyList;
    QSqlQuery buyerHistoryQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString + " UNION " + altQryStr));


    while (buyerHistoryQuery.next()) {

        long head               = DatabaseManager::valueAs<long>(buyerHistoryQuery,"head");
        string _date            = DatabaseManager::valueAs<QString>(buyerHistoryQuery,"date").toStdString();
        Date date;
        string customerName     = DatabaseManager::valueAs<QString>(buyerHistoryQuery,"name").toStdString();
        double net              = DatabaseManager::valueAs<double>(buyerHistoryQuery,"total_bought");
        date = Date::fromString(_date, "YYYY-mm-dd");

        historyList.push_back(HistoryItem(date, head, customerName, net));
    }
    sort(historyList.begin(), historyList.end(), HistoryItem::compareBuyerNamesLT);
    stable_sort(historyList.begin(), historyList.end(), HistoryItem::compareDatesLT);
    return historyList;
}


string HistoryDAO::predictSeller(string namePart)
{
    QString qryString = QString("SELECT MIN(UCASE(name)) as _userName FROM seller WHERE name like :name"
                                " UNION SELECT MIN(UCASE(seller_name)) FROM history"
                                " WHERE seller_name like :name1");
    QSqlQuery predictQuery;
    DatabaseManager::defaultManager.prepareQuery(predictQuery,qryString);
    predictQuery.bindValue(":name"  , QString::fromStdString(namePart)+"%");
    predictQuery.bindValue(":name1" , QString::fromStdString(namePart)+"%");

    DatabaseManager::defaultManager.executeQuery(predictQuery);

    string initialValue = "ZZZZZZZZZ";
    string altNamePart = initialValue;
    namePart = initialValue;

    if(predictQuery.first()) {
        namePart = DatabaseManager::valueAs<QString>(predictQuery,"_userName").toStdString();

        if(predictQuery.next()) {
            altNamePart = DatabaseManager::valueAs<QString>(predictQuery,"_userName").toStdString();
        }
    }

    if(altNamePart.length() > namePart.length())
    {
        namePart = altNamePart;
    }

    if(namePart == initialValue)
    {
        namePart = "";
    }

    return namePart;
}

string HistoryDAO::predictBuyer(string namePart)
{
    string qryString = "SELECT MIN(UCASE(name)) as _userName FROM buyer WHERE name like '" + namePart + "%' UNION SELECT MIN(UCASE(buyer_name)) from history where buyer_name like '" + namePart + "%' ";

    QSqlQuery predictQuery =DatabaseManager::defaultManager.query(QString::fromStdString(qryString));

    string initialValue = "ZZZZZZZZZ";
    string altNamePart= initialValue;
    namePart = initialValue;

    if(predictQuery.first()) {
        namePart = DatabaseManager::valueAs<QString>(predictQuery,"_userName").toStdString();

        if(predictQuery.next()) {
            altNamePart = DatabaseManager::valueAs<QString>(predictQuery,"_userName").toStdString();
        }
    }
    if(altNamePart.length() > namePart.length())
    {
        namePart = altNamePart;
    }

    if(namePart == initialValue)
    {
        namePart = "";
    }
    return namePart;
}


string HistoryDAO::getQueryString(string condStr, string altCondStr, Date startDate, Date endDate)
{
    string qryStr =
            "SELECT trans.date, trans.trans_id, seller.number, seller.name, buyer.number as _number, "
            "buyer.name as _name, trans.head, trans.weight, trans.type, trans.color, "
            "trans.flaw, trans.descrip, trans.price, trans.mode, trans.weighmaster, trans.descrip "
            "from buyer cross join trans cross join seller where ";


    string dateCondStr =
            " AND trans.date >= '" + startDate.toString("YYYY-mm-dd") + "' AND trans.date <= '" + endDate.toString("YYYY-mm-dd") + "' AND "
            "buyer.date >= '" + startDate.toString("YYYY-mm-dd") + "' AND buyer.date <= '" + endDate.toString("YYYY-mm-dd") + "' AND "
            "seller.date >= '" + startDate.toString("YYYY-mm-dd") + "' AND seller.date <= '" + endDate.toString("YYYY-mm-dd") + "'";


    string altQryStr;
    altQryStr =
            "SELECT "
            "date, "
            "transaction_id, "
            "seller_number, "
            "seller_name, "
            "buyer_number, "
            "buyer_name, "
            "head, "
            "weight, "
            "0,0,0, "
            "description, "
            "price, "
            "mode, "
            "weighmaster, "
            "description "
            "FROM history "
            "WHERE "
            "date >= '" + startDate.toString("YYYY-mm-dd") + "' AND date <= '" + endDate.toString("YYYY-mm-dd") + "' "
            "" + (altCondStr.length() > 0 ? "AND " : "") + ""
            "" + (altCondStr.length() > 0 ? "(" + altCondStr + ")" : "") + ""
            "";

    qryStr += condStr + dateCondStr + (altQryStr.length() > 0 ? " UNION " : "") + altQryStr;
    return qryStr;
}


vector<HistoryItem> HistoryDAO::getHistoryListByCondition(QSqlQuery &historyQuery)
{

    DatabaseManager::defaultManager.executeQuery(historyQuery);

    vector<HistoryItem> historyList;
    int sex = 0;
    int color = 0;
    int flaw = 0;

    while (historyQuery.next()) {
        sex   = DatabaseManager::valueAs<int>(historyQuery,"type");
        color = DatabaseManager::valueAs<int>(historyQuery,"color");
        flaw  = DatabaseManager::valueAs<int>(historyQuery,"flaw");
        string  _animalDescript = DatabaseManager::valueAs<QString>(historyQuery,"descrip").toStdString();

        string _date            = DatabaseManager::valueAs<QString>(historyQuery,"date").toStdString();
        long _trans_id          = DatabaseManager::valueAs<long>(historyQuery,"trans_id");
        string _seller_number   = DatabaseManager::valueAs<QString>(historyQuery,"number").toStdString();
        string _seller_name     = DatabaseManager::valueAs<QString>(historyQuery,"name").toStdString();

        string _buyer_number    = DatabaseManager::valueAs<QString>(historyQuery,"_number").toStdString();
        string _buyer_name      = DatabaseManager::valueAs<QString>(historyQuery,"_name").toStdString();

        long _trans_head        = DatabaseManager::valueAs<long>(historyQuery,"head");
        long _trans_weight      = DatabaseManager::valueAs<long>(historyQuery,"weight");

        double _trans_price     = DatabaseManager::valueAs<long>(historyQuery,"price");
        int    _trans_mode      = DatabaseManager::valueAs<int>(historyQuery,"mode");
        string _trans_weighmaster = DatabaseManager::valueAs<QString>(historyQuery,"weighmaster").toStdString();

        AnimalCode tempCode;

        if(sex == 0 && color == 0 && flaw == 0) {
            tempCode = AnimalCode::fromString(_animalDescript);
            tempCode.setDescrip("");
        }
        else {
            tempCode = AnimalCode(sex, color, flaw);
            tempCode.setDescrip(_animalDescript);
        }

        historyList.push_back(HistoryItem(Date::fromString(_date, "YYYY-mm-dd"), _trans_id, _seller_number, _seller_name,
                                          _buyer_number, _buyer_name, _trans_head, _trans_weight, tempCode,
                                          _trans_price, Transaction::SALE_MODE(_trans_mode), _trans_weighmaster));
    }
    AnimalCodeDAO codeDao;

    for(unsigned int i = 0; i < historyList.size(); i++) {
        if(historyList[i].getCode().getDescrip() == "-") {
            AnimalCode temp = historyList[i].getCode();
            codeDao.fillAnimalCode(temp);
            historyList[i].setAnimalCode(temp);
        }
    }
    return historyList;
}

