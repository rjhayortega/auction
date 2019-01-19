#include "checkdao.h"

CheckDAO::CheckDAO()
{}

Check CheckDAO::getCheckById(long id)
{
    char buf[20];
    sprintf(buf, "%ld", id);
    string condStr = "WHERE id=" + string(buf);
    return getCheckByCondition(condStr);
}

double CheckDAO::invoiceAmount(long invoiceId)
{
    char buf[20];

    sprintf(buf, "%ld", invoiceId);
    string qryString =
            "SELECT SUM(amount) as _sumAmount "
            "FROM checkreg "
            "WHERE invoice_id=" + string(buf) + " "
            "AND status!=1 "
            "GROUP BY invoice_id";

    double amount = 0.00000001;

    QSqlQuery invoiceAmountQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));

    if(invoiceAmountQuery.first())
    {
        amount = DatabaseManager::valueAs<double>(invoiceAmountQuery, "_sumAmount");
    }
    return amount;
}

Check CheckDAO::getCheckByNumber(long number)
{
    char buf[20];
    sprintf(buf, "%ld", number);

    string condString = "WHERE number=" + string(buf) + " ";

    return getCheckByCondition(condString);
}

vector<Check> CheckDAO::getCheckListByNumber(long number)
{
    char buf[20];
    sprintf(buf, "%ld", number);

    return getCheckListByCondition("WHERE number=" + string(buf) + "");
}

vector<Check> CheckDAO::getInvoiceCheckList(long invoiceId)
{

    if(invoiceId == 0)
    {
        return vector<Check>();
    }

    char invIdStr[20];
    char voidStatusStr[3];
    sprintf(invIdStr, "%ld", invoiceId);
    sprintf(voidStatusStr, "%ld", Check::Void);

    string condString = "WHERE invoice_id=" + string(invIdStr) + " AND status != " + string(voidStatusStr) + "";
    return getCheckListByCondition(condString);
}

Check CheckDAO::getCheckByInvoice(Invoice invoice, Check::STATUS checkStatus)
{
    char invId[20], status[4];

    sprintf(invId, "%ld", invoice.getNumber());
    sprintf(status, "%d", checkStatus);

    string condString = "WHERE invoice_id=" + string(invId) + " AND status=" + string(status) + " ";
    return getCheckByCondition(condString);
}


vector<Check> CheckDAO::getCheckList(Date fromDate, Date toDate, bool includeVoid, bool includeOut, bool includeCleared, string payeeFilter)
{
    char voidStr[4];
    char outStr[4];
    char clrStr[4];

    sprintf(voidStr, "%d", Check::Void);
    sprintf(outStr, "%d", Check::Out);
    sprintf(clrStr, "%d", Check::Cleared);

    string baseCondition = "WHERE date>='" + fromDate.toString("YYYY-mm-dd") + "' AND date<='" + toDate.toString("YYYY-mm-dd") + "' ";
    string excludeVoidCond = (includeVoid ? "" : "AND status !=" + string(voidStr) + " ");
    string excludeOutCond = (includeOut ? "" : "AND status !=" + string(outStr) + " ");
    string excludeClrCond = (includeCleared ? "" : "AND status !=" + string(clrStr) + " ");

    string filterPayeeCondition = "";

    if(payeeFilter != "")
    {
        filterPayeeCondition = " AND payee='" + payeeFilter + "'";
    }

    return getCheckListByCondition(baseCondition + excludeVoidCond + excludeOutCond + excludeClrCond + filterPayeeCondition);
}

vector<Check> CheckDAO::getCheckList(long fromNumber, long toNumber, bool includeVoid, bool includeOut, bool includeCleared, string payeeFilter)
{
    char voidStr[4];
    char outStr[4];
    char clrStr[4];
    char fromNoStr[20];
    char toNoStr[20];

    sprintf(voidStr, "%d", Check::Void);
    sprintf(outStr, "%d", Check::Out);
    sprintf(clrStr, "%d", Check::Cleared);

    sprintf(fromNoStr, "%ld", fromNumber);
    sprintf(toNoStr, "%ld", toNumber);

    string excludeVoidCond = (includeVoid ? "" : "AND status !=" + string(voidStr) + " ");
    string excludeOutCond = (includeOut ? "" : "AND status !=" + string(outStr) + " ");
    string excludeClrCond = (includeCleared ? "" : "AND status !=" + string(clrStr) + " ");

    string baseCondition = "WHERE number>=" + string(fromNoStr) + " AND number <=" + string(toNoStr) + " ";
    string filterPayeeCondition = "";

    if(payeeFilter != "")
    {
        filterPayeeCondition = " AND payee='" + payeeFilter + "'";
    }

    return getCheckListByCondition(baseCondition + excludeVoidCond + excludeOutCond + excludeClrCond + filterPayeeCondition);
}

vector<Deposit> CheckDAO::getDepositList(Date fromDate, Date toDate, bool includeVoid, bool includeOut, bool includeCleared)
{
    char voidStr[4];
    char outStr[4];
    char clrStr[4];

    sprintf(voidStr, "%d", Check::Void);
    sprintf(outStr, "%d", Check::Out);
    sprintf(clrStr, "%d", Check::Cleared);

    string baseCondition = "WHERE date>='" + fromDate.toString("YYYY-mm-dd") + "' AND date<='" + toDate.toString("YYYY-mm-dd") + "' ";
    string excludeVoidCond = (includeVoid ? "" : "AND status !=" + string(voidStr) + " ");
    string excludeOutCond = (includeOut ? "" : "AND status !=" + string(outStr) + " ");
    string excludeClrCond = (includeCleared ? "" : "AND status !=" + string(clrStr) + " ");

    return getDepositListByCondition(baseCondition + excludeVoidCond + excludeOutCond + excludeClrCond);
}

vector<Check> CheckDAO::getCheckList(Check::STATUS checkStatus)
{
    char status[4];
    sprintf(status, "%d", checkStatus);

    string condStr = "WHERE status=" + string(status) + " ";
    return getCheckListByCondition(condStr);
}

Check CheckDAO::saveCheck(Check check)
{
    QSqlQuery saveCheckQuery;
    QString qryString = QString("REPLACE INTO checkreg SET id=:id_ , number=:number_ , payee=:payee_ ,"
            "amount=:amount_ , status=:status_ , comment=:comment_ ,"
            "date=:date_ , invoice_id=:invoice_id_ , type=:type_ ");

    DatabaseManager::defaultManager.prepareQuery(saveCheckQuery,qryString);

    saveCheckQuery.bindValue(":id_"          , QVariant::fromValue<long>(check.getId()));
    saveCheckQuery.bindValue(":number_"      , QVariant::fromValue<long>(check.getNumber()));
    saveCheckQuery.bindValue(":payee_"       , QString::fromStdString(check.getPayee()));
    saveCheckQuery.bindValue(":amount_"      , QVariant::fromValue<double>(check.getAmount()));
    saveCheckQuery.bindValue(":status_"      , QVariant::fromValue<int>(check.getStatus()));
    saveCheckQuery.bindValue(":comment_"     , QString::fromStdString(check.getComment()));
    saveCheckQuery.bindValue(":date_"        , QString::fromStdString(check.getDate().toString("YYYY-mm-dd")));
    saveCheckQuery.bindValue(":invoice_id_"  , QVariant::fromValue<long>(check.getInvoiceId()));
    saveCheckQuery.bindValue(":type_"        , check.getType());

    DatabaseManager::defaultManager.executeQuery(saveCheckQuery);

    if(check.getNumber() == 0)
    {
        check.setNumber(DatabaseManager::defaultManager.get_last_id(saveCheckQuery));
    }

    if(check.getId() == 0)
    {
        check.setId(DatabaseManager::defaultManager.get_last_id(saveCheckQuery));
    }

    return check;
}

void CheckDAO::voidChecksByInvoice(Invoice invoice)
{
    char invId[20];
    sprintf(invId, "%ld", invoice.getNumber());
    string condStr = "WHERE invoice_id=" + string(invId) + " ";
    voidChecksByCondition(condStr);
}

void CheckDAO::setCheckStatus(Check check, Check::STATUS checkStatus)
{
    char id[20];
    sprintf(id, "%ld", check.getId());
    string condStr = "WHERE id=" + string(id) + " ";
    setCheckStatusByCondition(condStr, checkStatus);
}

Deposit CheckDAO::getDepositByNumber(long number)
{
    char num[20];
    sprintf(num, "%ld", number);
    string condStr = "WHERE number=" + string(num);

    return getDepositByCondition(condStr);
}

vector<Deposit> CheckDAO::getDepositList()
{
    return getDepositListByCondition("");
}

void CheckDAO::setDepositStatus(Deposit deposit, Deposit::STATUS status)
{
    char number[20];
    sprintf(number, "%ld", deposit.getNumber());

    string condStr = "WHERE number=" + string(number);

    setDepositStatusByCondition(condStr, status);
}

Deposit CheckDAO::saveDeposit(Deposit deposit)
{
    QSqlQuery saveDepositQuery;
    QString qryString = QString("REPLACE INTO depositreg SET number=:number, amount=:amount, "
                                "status=:status, date=:date, comment=:comment ");
    DatabaseManager::defaultManager.prepareQuery(saveDepositQuery,qryString);
    saveDepositQuery.bindValue(":number"    , QVariant::fromValue<long>(deposit.getNumber()));
    saveDepositQuery.bindValue(":amount"    , deposit.getAmount());
    saveDepositQuery.bindValue(":status"    , deposit.getStatus());
    saveDepositQuery.bindValue(":date"      , QString::fromStdString(deposit.getDate().toString("YYYY-mm-dd")));
    saveDepositQuery.bindValue(":comment"   , QString::fromStdString(deposit.getComment()));

    DatabaseManager::defaultManager.executeQuery(saveDepositQuery);

    if(deposit.getNumber() == 0) {
        deposit.setNumber(DatabaseManager::defaultManager.get_last_id(saveDepositQuery));
    }
    return deposit;
}

double CheckDAO::getCheckTotal(Check::STATUS status)
{
    double result = 0.0;

    QString qryString = QString("SELECT sum(amount) as _sumAmount FROM checkreg WHERE status=%1 ").arg(status);
    QSqlQuery checkTotalQuery = DatabaseManager::defaultManager.query(qryString);

    if(checkTotalQuery.first()) {
        result = DatabaseManager::valueAs<double>(checkTotalQuery,"_sumAmount");
    }
    return result;
}

bool CheckDAO::checkExists(long number)
{
    QString qryString = QString("SELECT * FROM checkreg WHERE number=%1 ").arg(number);
    QSqlQuery checkExistsQuery = DatabaseManager::defaultManager.query(qryString);
    bool exists = checkExistsQuery.first();
    return exists;
}


long CheckDAO::getNextCheckNo(bool saveNextNo)
{

    long nextCheckNo = peekAtNextCheckNo();

    char buf[20];
    sprintf(buf, "%ld", nextCheckNo + 1);
    // Automatically save nextCheckNo , but in some cases it need to be avoided.
    // Added for solve situation descibed in the ticket #84.
    if ( saveNextNo ) {
        setup.set("nextCheckNo", buf);
    }
    return nextCheckNo;
}

long CheckDAO::peekAtNextCheckNo()
{
    string checkNoStr = setup.get("nextCheckNo");
    return atol(checkNoStr.c_str());
}

double CheckDAO::getDepositTotal(Deposit::STATUS status)
{
    double result = 0.0;
    QString qryString = QString("SELECT sum(amount) as _sumAmount FROM depositreg WHERE status=%1 ").arg(status);
    QSqlQuery depositQuery = DatabaseManager::defaultManager.query(qryString);

    if(depositQuery.first())
    {
        result = DatabaseManager::valueAs<double>(depositQuery,"_sumAmount");
    }
    return result;
}

void CheckDAO::setNextCheck(long nextNumber)
{
    char next[20];
    sprintf(next, "%ld", nextNumber);
    //   string qryString = "ALTER TABLE checkreg AUTO_INCREMENT=" + string(next);
    //   DatabaseManager::defaultManager.query(qryString.c_str());

    setup.set("nextCheckNo", next);
}

void CheckDAO::deleteCheck(Check check)
{
    char id[20];
    sprintf(id, "%ld", check.getId());

    string qryString = "DELETE FROM checkreg WHERE id=" + string(id);
    DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
}

///////////////////////////////////////////////////////////
// private methods

Check CheckDAO::getCheckByCondition(string condStr)
{
    vector<Check> temp = getCheckListByCondition(condStr);
    if(temp.size() > 0)
    {
        return temp[0];
    }

    return Check();
}


vector<Check> CheckDAO::getCheckListByCondition(string condStr)
{
    string qryString =
            "SELECT number, payee, amount, status, comment, date, invoice_id, id, type FROM checkreg " + condStr + " ORDER BY number";

    vector<Check> checkList;

    QSqlQuery checkListQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));

    while (checkListQuery.next()) {

        long _id       = DatabaseManager::valueAs<long>(checkListQuery,"id");
        long _number   = DatabaseManager::valueAs<long>(checkListQuery,"number");
        string _payee  = DatabaseManager::valueAs<QString>(checkListQuery,"payee").toStdString();
        double _amount = DatabaseManager::valueAs<double>(checkListQuery,"amount");
        int _status    = DatabaseManager::valueAs<int>(checkListQuery,"status");
        string _date   = DatabaseManager::valueAs<QString>(checkListQuery,"date").toStdString();
        string _comment= DatabaseManager::valueAs<QString>(checkListQuery,"comment").toStdString();
        int _type      = DatabaseManager::valueAs<int>(checkListQuery,"type");
        long _invoiceId= DatabaseManager::valueAs<long>(checkListQuery,"invoice_id");

        checkList.push_back(Check(_id, _number, _payee, _amount,
                Check::STATUS(_status), Date::fromString(_date, "YYYY-mm-dd"),
                _comment, Check::Type(_type), _invoiceId));
    }

    return checkList;
}

void CheckDAO::voidChecksByCondition(string condString)
{
    setCheckStatusByCondition(condString, Check::Void);
}

void CheckDAO::setCheckStatusByCondition(string condString, Check::STATUS checkStatus)
{
    char status[4];
    sprintf(status, "%d", checkStatus);
    string qryString = "UPDATE checkreg SET status=" + string(status) + " " + condString + " ";
    DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
}

Deposit CheckDAO::getDepositByCondition(string condStr)
{
    return getDepositListByCondition(condStr)[0];
}


vector<Deposit> CheckDAO::getDepositListByCondition(string condStr)
{
    string qryString = "SELECT number, amount, status, date, comment FROM depositreg " + condStr;
    vector<Deposit> depositList;
    QSqlQuery depositListQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));

    while (depositListQuery.next()) {

        int _number     = DatabaseManager::valueAs<int>(depositListQuery,"number");
        double _amount  = DatabaseManager::valueAs<double>(depositListQuery,"amount");
        int _status     = DatabaseManager::valueAs<int>(depositListQuery,"status");
        string _date    = DatabaseManager::valueAs<QString>(depositListQuery,"date").toStdString();
        string _comment = DatabaseManager::valueAs<QString>(depositListQuery,"comment").toStdString();

        depositList.push_back(Deposit(0, _number,_amount, Deposit::STATUS(_status),
                Date::fromString(_date, "YYYY-mm-dd"), _comment));
    }
    return depositList;
}

vector<string> CheckDAO::getCustomerCheckNumberList(string customerId)
{

    string queryStr =
            "SELECT id "
            "FROM sellerinvoice "
            "WHERE "
            "date='" + sale.currentSaleDateSQLString() + "' "
            "AND "
            "customer_id='" + customerId + "' ";

    QSqlQuery customerCheckQuery = DatabaseManager::defaultManager.query(QString::fromStdString(queryStr));
    string invoiceId;

    if( customerCheckQuery.first())
    {
        invoiceId = DatabaseManager::valueAs<QString>(customerCheckQuery,"id").toStdString();
    }
    else {
        return vector<string>();
    }

    queryStr =
            "SELECT number FROM checkreg "
            "WHERE "
            "invoice_id=" + invoiceId + " "
            "";


    vector<string> checkNumberList;

    QSqlQuery checkNumberQuery = DatabaseManager::defaultManager.query(QString::fromStdString(queryStr));

    while(checkNumberQuery.next()) {
        string _number = DatabaseManager::valueAs<QString>(checkNumberQuery,"number").toStdString();
        checkNumberList.push_back(_number);
    }
    return checkNumberList;
}

void CheckDAO::setDepositStatusByCondition(string condStr, Deposit::STATUS depositStatus)
{
    char status[4];

    sprintf(status, "%d", depositStatus);
    string qryString = "UPDATE depositreg SET status=" + string(status) + " " + condStr + " ";

    DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
}


CheckFormatData CheckDAO::getCheckFormat(bool includeAddressData)
{
    SetupDAO setup;

    string numberColBuf = setup.get("checkNumberCol");

    if(numberColBuf == "")
    {
        numberColBuf = "81";
    }

    if(includeAddressData)
    {
        string colBuf;
        colBuf = setup.get("checkAddress1Col");
        int address1Col = (colBuf.length() > 0 ? atoi(colBuf.c_str()) : 81);

        colBuf = setup.get("checkAddress2Col");
        int address2Col = (colBuf.length() > 0 ? atoi(colBuf.c_str()) : 81);

        colBuf = setup.get("checkCityStZipCol");

        int cityStZipCol = (colBuf.length() > 0 ? atoi(colBuf.c_str()) : 81);


        return CheckFormatData(CheckItemCoord(atoi(setup.get("checkAmountRow").c_str()),     atoi(setup.get("checkAmountCol").c_str())),
                               CheckItemCoord(atoi(setup.get("checkPayeeRow").c_str()),      atoi(setup.get("checkPayeeCol").c_str())),
                               CheckItemCoord(atoi(setup.get("checkTextAmountRow").c_str()), atoi(setup.get("checkTextAmountCol").c_str())),
                               CheckItemCoord(atoi(setup.get("checkMemoRow").c_str()),       atoi(setup.get("checkMemoCol").c_str())),
                               CheckItemCoord(atoi(setup.get("checkDateRow").c_str()),       atoi(setup.get("checkDateCol").c_str())),
                               CheckItemCoord(atoi(setup.get("checkSignatureRow").c_str()),  atoi(setup.get("checkSignatureCol").c_str())),
                               setup.get("chkSigFileName"),
                               CheckItemCoord(atoi(setup.get("checkAddress1Row").c_str()),  address1Col),
                               CheckItemCoord(atoi(setup.get("checkAddress2Row").c_str()),  address2Col),
                               CheckItemCoord(atoi(setup.get("checkCityStZipRow").c_str()), cityStZipCol),
                               CheckItemCoord(atoi(setup.get("checkHeadRow").c_str()), atoi(setup.get("checkHeadCol").c_str())),
                               CheckItemCoord(atoi(setup.get("checkNumberRow").c_str()), atoi(numberColBuf.c_str())));
    }
    else
    {
        return CheckFormatData(CheckItemCoord(atoi(setup.get("checkAmountRow").c_str()),     atoi(setup.get("checkAmountCol").c_str())),
                               CheckItemCoord(atoi(setup.get("checkPayeeRow").c_str()),      atoi(setup.get("checkPayeeCol").c_str())),
                               CheckItemCoord(atoi(setup.get("checkTextAmountRow").c_str()), atoi(setup.get("checkTextAmountCol").c_str())),
                               CheckItemCoord(atoi(setup.get("checkMemoRow").c_str()),       atoi(setup.get("checkMemoCol").c_str())),
                               CheckItemCoord(atoi(setup.get("checkDateRow").c_str()),       atoi(setup.get("checkDateCol").c_str())),
                               CheckItemCoord(atoi(setup.get("checkSignatureRow").c_str()),  atoi(setup.get("checkSignatureCol").c_str())),
                               setup.get("chkSigFileName"), CheckItemCoord(), CheckItemCoord(), CheckItemCoord(), CheckItemCoord(),
                               CheckItemCoord(atoi(setup.get("checkNumberRow").c_str()), atoi(numberColBuf.c_str())));
    }
}

void CheckDAO::saveCheckFormat(CheckFormatData format)
{
    char colBuf[10], rowBuf[10];
    SetupDAO setup;

    sprintf(rowBuf, "%d", format.getAmountCoord().getRow());
    sprintf(colBuf, "%d", format.getAmountCoord().getCol());
    setup.set("checkAmountRow", rowBuf);
    setup.set("checkAmountCol", colBuf);

    sprintf(rowBuf, "%d", format.getPayeeCoord().getRow());
    sprintf(colBuf, "%d", format.getPayeeCoord().getCol());
    setup.set("checkPayeeRow", rowBuf);
    setup.set("checkPayeeCol", colBuf);

    sprintf(rowBuf, "%d", format.getTextAmountCoord().getRow());
    sprintf(colBuf, "%d", format.getTextAmountCoord().getCol());
    setup.set("checkTextAmountRow", rowBuf);
    setup.set("checkTextAmountCol", colBuf);

    sprintf(rowBuf, "%d", format.getCommentCoord().getRow());
    sprintf(colBuf, "%d", format.getCommentCoord().getCol());
    setup.set("checkMemoRow", rowBuf);
    setup.set("checkMemoCol", colBuf);

    sprintf(rowBuf, "%d", format.getDateCoord().getRow());
    sprintf(colBuf, "%d", format.getDateCoord().getCol());
    setup.set("checkDateRow", rowBuf);
    setup.set("checkDateCol",  colBuf);


    sprintf(rowBuf, "%d", format.getSignatureCoord().getRow());
    sprintf(colBuf, "%d", format.getSignatureCoord().getCol());
    setup.set("checkSignatureRow", rowBuf);
    setup.set("checkSignatureCol", colBuf);

    sprintf(rowBuf, "%d", format.getAddress1Coord().getRow());
    sprintf(colBuf, "%d", format.getAddress1Coord().getCol());
    setup.set("checkAddress1Row", rowBuf);
    setup.set("checkAddress1Col", colBuf);

    sprintf(rowBuf, "%d", format.getAddress2Coord().getRow());
    sprintf(colBuf, "%d", format.getAddress2Coord().getCol());
    setup.set("checkAddress2Row", rowBuf);
    setup.set("checkAddress2Col", colBuf);

    sprintf(rowBuf, "%d", format.getCityStZipCoord().getRow());
    sprintf(colBuf, "%d", format.getCityStZipCoord().getCol());
    setup.set("checkCityStZipRow", rowBuf);
    setup.set("checkCityStZipCol", colBuf);

    sprintf(rowBuf, "%d", format.getHeadCoord().getRow());
    sprintf(colBuf, "%d", format.getHeadCoord().getCol());
    setup.set("checkHeadRow", rowBuf);
    setup.set("checkHeadCol", colBuf);

    sprintf(rowBuf, "%d", format.getNumberCoord().getRow());
    sprintf(colBuf, "%d", format.getNumberCoord().getCol());
    setup.set("checkNumberRow", rowBuf);
    setup.set("checkNumberCol", colBuf);

    setup.set("chkSigFileName", format.getSignaturePath());
}


