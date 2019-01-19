#include "setupdao.h"
#include "commissiondao.h"
#include "salemanager.h"


CommissionDAO::CommissionDAO()
{
}

string CommissionDAO::getCommissionIdString(AnimalCode code)
{
    string idStr="0";
    char sex[20], flaw[20], colorGroup[20];
    sprintf(sex, "%d", code.getType());
    sprintf(flaw, "%d", (code.getFlaw() > 9 ? 0 : code.getFlaw()));

    COLOR_GROUP cg = CommissionDAO::getColorGroup(code.getColor());
    sprintf(colorGroup, "%d", cg);

    string queryStr = "SELECT commission_id FROM comm_code_rel WHERE sex=" + string(sex) + " AND flaw=" + string(flaw) + " AND color_group=" + string(colorGroup) + "";
    QSqlQuery commistionQuery = DatabaseManager::defaultManager.query(QString::fromStdString(queryStr));

    if(commistionQuery.first()) {
        idStr = DatabaseManager::valueAs<QString>(commistionQuery,"commission_id").toStdString();
    }
    return idStr;
}

Commission CommissionDAO::getCommission(AnimalCode code)
{
    char sex[20], flaw[20], colorGroup[20];
    short flawCode = code.getFlaw();
    flawCode = (flawCode < 10 ? flawCode : 0);
    sprintf(sex, "%d", code.getType());
    sprintf(flaw, "%d", flawCode);

    COLOR_GROUP cg = CommissionDAO::getColorGroup(code.getColor());
    sprintf(colorGroup, "%d", cg);

    //  string commIdStr = getCommissionIdString(code);

    //  string qryString =
    //    "SELECT id, commission_mode, break_mode, min, max, no_sale_charge FROM commission where id=" + commIdStr + "";

    string qryString =
            "SELECT "
            "DISTINCT(id), "
            "commission_mode, "
            "break_mode, "
            "min, "
            "max, "
            "no_sale_charge, "
            "name "
            "FROM comm_code_rel CROSS JOIN commission "
            "WHERE "
            "comm_code_rel.color_group=" + string(colorGroup) + " "
            "AND "
            "comm_code_rel.sex=" + string(sex) + " "
            "AND "
            "comm_code_rel.flaw=" + string(flaw) + " "
            "AND "
            "commission.id = comm_code_rel.commission_id "
            "";

    // [KLN] debug
//    cout << "CommissionDAO::getCommission qryString --" << endl << "   " << qryString << endl;
    // [KLN] debug end

    QSqlQuery commissionQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));

    if(!commissionQuery.first()) {
        /*
    DatabaseManager::defaultManager.release_result();
    if(code != AnimalCode(0, 0, 0))
    {
      return getCommission(AnimalCode(0, 0, 0)); // attempt to retrieve the 'default' commission
    }
*/
        return Commission();
    }


    long _id             = DatabaseManager::valueAs<long>(commissionQuery,"id");
    int _type            = DatabaseManager::valueAs<int>(commissionQuery,"commission_mode");
    int _breakType       = DatabaseManager::valueAs<int>(commissionQuery,"break_mode");
    double _min          = DatabaseManager::valueAs<double>(commissionQuery,"min");
    double _max          = DatabaseManager::valueAs<double>(commissionQuery,"max");
    double _noSaleCharge = DatabaseManager::valueAs<double>(commissionQuery,"no_sale_charge");
    string _name         = DatabaseManager::valueAs<QString>(commissionQuery,"name").toStdString();

    Commission::TYPE type = Commission::TYPE(_type);
    Commission::BREAK_TYPE breakType = Commission::BREAK_TYPE(_breakType);

    return Commission(_id, type, breakType, getBreakList(_id), _min, _max, _noSaleCharge, _name);
}


vector<CommissionBreak> CommissionDAO::getBreakList(long commId)
{
    char commIdStr[20];
    sprintf(commIdStr, "%ld", commId);

    string qryString =
            "SELECT "
            "id, "
            "commission_id, "
            "expression, "
            "break_value, "
            "min, "
            "max "
            "FROM commission_break "
            "WHERE "
            "commission_id=" + string(commIdStr) + " "
            "ORDER BY break_value ASC ";
    //"" + (commId > 0 ? "WHERE commission_id=" + string(commIdStr) + " ": " ") + "ORDER BY break_value ASC";

    QSqlQuery breakListQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
    vector<CommissionBreak> breakList;

    while (breakListQuery.next())  {
        long _id            = DatabaseManager::valueAs<long>(breakListQuery,"id");
        string _expression  = DatabaseManager::valueAs<QString>(breakListQuery,"expression").toStdString();
        double _break_value = DatabaseManager::valueAs<double>(breakListQuery,"break_value");
        double _min         = DatabaseManager::valueAs<double>(breakListQuery,"min");
        double _max         = DatabaseManager::valueAs<double>(breakListQuery,"max");

        breakList.push_back(CommissionBreak(_id, _expression, _break_value));
        breakList.back().setMin(_min);
        breakList.back().setMax(_max);
    }
    return breakList;
}


long CommissionDAO::saveCommission(Commission comm, list<AnimalCode> codeList, COLOR_GROUP colorGroup)
{
    long commId;
    QSqlQuery saveCommissionQuery;
    QString qryString = QString("REPLACE INTO commission set id=:id, commission_mode=:commission_mode, "
                                "break_mode=:break_mode, min=:min, max=:max, "
                                "no_sale_charge=:no_sale_charge, name=:name " );

    DatabaseManager::defaultManager.prepareQuery(saveCommissionQuery,qryString);
    saveCommissionQuery.bindValue(":id"                 , QVariant::fromValue<long>(comm.getId()));
    saveCommissionQuery.bindValue(":commission_mode"    , comm.getType());
    saveCommissionQuery.bindValue(":break_mode"         , comm.getBreakType());
    saveCommissionQuery.bindValue(":min"                , comm.getMin());
    saveCommissionQuery.bindValue(":max"                , comm.getMax());
    saveCommissionQuery.bindValue(":no_sale_charge"     , comm.getNoSaleCharge());
    saveCommissionQuery.bindValue(":name"               , QString::fromStdString(comm.getName()));

    DatabaseManager::defaultManager.executeQuery(saveCommissionQuery);
    commId = DatabaseManager::defaultManager.get_last_id(saveCommissionQuery);
    if(commId == 0) {
        commId = comm.getId();
    }

    long id;

    if(comm.getId() == 0) {
        id = DatabaseManager::defaultManager.get_last_id(saveCommissionQuery);
    }
    else {
        id = comm.getId();
    }
    saveBreakList(comm.getBreakList(), id);
    saveCodeRelationships(codeList, colorGroup, id);
    return commId;
}


void CommissionDAO::saveBreak(CommissionBreak commBreak, long commId)
{
    QString qryString = QString("REPLACE INTO commission_break SET commission_id=:commission_id, "
                                "id=:id, break_value=:break_value, expression=:expression, "
                                "min=:min, max=:max ");

    QSqlQuery saveBreakQuery;
    DatabaseManager::defaultManager.prepareQuery(saveBreakQuery,qryString);

    saveBreakQuery.bindValue(":commission_id"   , QVariant::fromValue<long>(commId));
    saveBreakQuery.bindValue(":id"              , QVariant::fromValue<long>(commBreak.getId()));
    saveBreakQuery.bindValue(":break_value"     , commBreak.getBreakValue());
    saveBreakQuery.bindValue(":expression"      , QString::fromStdString(commBreak.getExpression()));
    saveBreakQuery.bindValue(":min"             ,commBreak.getMin());
    saveBreakQuery.bindValue(":max"             ,commBreak.getMax());

    DatabaseManager::defaultManager.executeQuery(saveBreakQuery);
}


void CommissionDAO::saveBreakList(vector<CommissionBreak> breakList, long commId)
{
    vector<CommissionBreak>::iterator current;
    for(current = breakList.begin(); current != breakList.end(); current++)
    {
        saveBreak(*current, commId);
    }
}


void CommissionDAO::saveCodeRelationships(list<AnimalCode> codeList, COLOR_GROUP cg, long commId)
{
    list<AnimalCode>::iterator current;
    char sex[20], flaw[20], colorGroup[5], commIdStr[20];
    sprintf(commIdStr, "%ld", commId);
    sprintf(colorGroup, "%d", cg);

    string clearQry = "DELETE FROM comm_code_rel WHERE commission_id=" + string(commIdStr);
    DatabaseManager::defaultManager.query(QString::fromStdString(clearQry));

    clearQry = "DELETE FROM comm_code_rel ";
    QString insertQry = QString("INSERT INTO comm_code_rel SET commission_id=:commission_id, "
                                "sex=:sex, flaw=:flaw, color_group=:color_group  ");

    for(current = codeList.begin(); current != codeList.end(); current++)
    {
        sprintf(sex, "%d", current->getType());
        sprintf(flaw, "%d", current->getFlaw());
        string qryString = clearQry + "WHERE sex=" + string(sex) + " AND flaw=" + string(flaw) + " AND color_group=" + string(colorGroup) + " ";
        DatabaseManager::defaultManager.query(QString::fromStdString(qryString));

        QSqlQuery insertQuery;
        DatabaseManager::defaultManager.prepareQuery(insertQuery,insertQry);

        insertQuery.bindValue(":commission_id"  ,QVariant::fromValue<long>(commId));
        insertQuery.bindValue(":sex"            ,current->getType());
        insertQuery.bindValue(":flaw"           ,current->getFlaw());
        insertQuery.bindValue(":color_group"    ,cg);
        DatabaseManager::defaultManager.executeQuery(insertQuery);
    }
}

vector<string> CommissionDAO::getCommissionedBuyerIdList()
{
    string qryString = "SELECT customer_id from buyercommission WHERE date='" + sale.currentSaleDateSQLString() + "' AND amount > 0.00";
    QSqlQuery buyerListQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));

    vector<string> buyerIdList;
    while (buyerListQuery.next()) {
        string _customer_id = DatabaseManager::valueAs<QString>(buyerListQuery,"customer_id").toStdString();
        buyerIdList.push_back(_customer_id);
    }
    return buyerIdList;
}

vector<Commission> CommissionDAO::getCommissionList(COLOR_GROUP cg)
{
    char colorGroup[20];

    string qryString =
            "SELECT id, commission_mode, break_mode, min, max, no_sale_charge, name FROM commission ";

    if(cg != INVALID)
    {
        sprintf(colorGroup, "%d", cg);
        qryString += "WHERE id IN (SELECT commission_id FROM comm_code_rel WHERE color_group=" + string(colorGroup) + ") ";
    }

    QSqlQuery commisionListQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
    Commission::TYPE commType;
    Commission::BREAK_TYPE breakType;
    double min;
    double max;
    double noSaleCharge = 0.0000;
    vector<CommissionBreak> breakList;
    string name;
    long id;

    vector<Commission> commList;
    while (commisionListQuery.next()) {
        id           = DatabaseManager::valueAs<long>(commisionListQuery,"id");
        commType     = Commission::TYPE(DatabaseManager::valueAs<int>(commisionListQuery,"commission_mode"));
        breakType    = Commission::BREAK_TYPE(DatabaseManager::valueAs<int>(commisionListQuery,"break_mode"));
        breakList    = getBreakList(id);
        min          = DatabaseManager::valueAs<double>(commisionListQuery,"min");
        max          = DatabaseManager::valueAs<double>(commisionListQuery,"max");
        noSaleCharge = DatabaseManager::valueAs<double>(commisionListQuery,"no_sale_charge");
        name         = DatabaseManager::valueAs<QString>(commisionListQuery,"name").toStdString();
        commList.push_back(Commission(id, commType, breakType, breakList, min, max, noSaleCharge, name));
    }

    return commList;
}


list<AnimalCode> CommissionDAO::getCodeRelList(long commId)
{
    char idStr[20];
    sprintf(idStr, "%ld", commId);
    string qryString = "SELECT commission_id, sex, flaw, color_group FROM comm_code_rel " + (commId > 0 ? "WHERE commission_id=" + string(idStr) : "") + " ";

    QSqlQuery codeRelQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
    list<AnimalCode> codeList;
    short sex;
    short flaw;
    COLOR_GROUP colorGroup;

    while (codeRelQuery.next()) {
        sex         = DatabaseManager::valueAs<int>(codeRelQuery,"sex");
        flaw        = DatabaseManager::valueAs<int>(codeRelQuery,"flaw");
        colorGroup  = COLOR_GROUP(DatabaseManager::valueAs<int>(codeRelQuery,"color_group"));
        codeList.push_back(AnimalCode(sex, short(colorGroup), flaw));
    }
    return codeList;
}

void CommissionDAO::deleteBreaks(Commission comm)
{
    char commId[20];
    sprintf(commId, "%ld", comm.getId());

    string qryStr = "DELETE FROM commission_break WHERE commission_id=" + string(commId) + "";

    DatabaseManager::defaultManager.query(QString::fromStdString(qryStr));
}

void CommissionDAO::deleteCommission(Commission comm)
{
    char commId[20];
    sprintf(commId, "%ld", comm.getId());

    string deleteCommQryString =    "DELETE FROM commission WHERE id=" + string(commId) + "\n";
    string deleteCodeRelQryString = "DELETE FROM comm_code_rel WHERE commission_id=" + string(commId) + "\n";
    string deleteBreaksQryString =  "DELETE FROM commission_break WHERE commission_id=" + string(commId) + "\n";

    DatabaseManager::defaultManager.query(QString::fromStdString(deleteCommQryString));
    DatabaseManager::defaultManager.query(QString::fromStdString(deleteCodeRelQryString));
    DatabaseManager::defaultManager.query(QString::fromStdString(deleteBreaksQryString));
}

void CommissionDAO::deleteBreak(CommissionBreak commBreak)
{
    char breakId[20];
    sprintf(breakId, "%ld", commBreak.getId());

    string qryString = "DELETE FROM commission_break WHERE id=" + string(breakId) + " ";

    DatabaseManager::defaultManager.query(QString::fromStdString(qryString));

}

CommissionDAO::COLOR_GROUP CommissionDAO::getColorGroup(short color)
{
    return COLOR_GROUP(color < 70 ? FIRST : (color < 80 ? SECOND : (color < 90 ? THIRD : FOURTH)));
}

Commission CommissionDAO::getBuyerCommission(string customerId)
{

    double amount = 0.00;
    CommissionBreak::BuyerMode mode = CommissionBreak::CWT;

    getBuyerCommissionData(mode, amount, customerId);
    return Commission::buyerCommission(mode, amount);
}

void CommissionDAO::getBuyerCommissionData(CommissionBreak::BuyerMode& mode, double& amount, string customerId)
{
    string qryString =
            "SELECT "
            "mode, "
            "amount "
            "FROM buyercommission "
            "WHERE "
            "date='" + sale.currentSaleDateSQLString() + "'"
            "AND "
            "customer_id='" + customerId + "' "
            "";

    amount = 0.00000001;

    defaultMode = CommissionBreak::CWT;

    string defaultPayee = SetupDAO().get("binvDefaultCommissionPayee");

    if(defaultPayee == "1")
    {
        defaultMode = CommissionBreak::CompanyCWT;
    }

    mode = defaultMode;

    QSqlQuery buyerQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));

    if(buyerQuery.first()) {
        amount = DatabaseManager::valueAs<double>(buyerQuery,"amount");
        mode = CommissionBreak::BuyerMode(DatabaseManager::valueAs<int>(buyerQuery,"mode"));
    }
}

void CommissionDAO::saveBuyerCommission(double amount, CommissionBreak::BuyerMode mode, string customerId)
{
    char amtStr[30], modeStr[4];
    sprintf(amtStr, "%0.2f", amount);
    sprintf(modeStr, "%d", mode);
    string qryString = "DELETE FROM buyercommission WHERE customer_id='" + customerId + "' AND date='" + sale.currentSaleDateSQLString() + "'";
    DatabaseManager::defaultManager.query(QString::fromStdString(qryString));

    qryString = "INSERT INTO buyercommission SET customer_id='" + customerId +"', amount=" + string(amtStr) + ", mode=" + string(modeStr) +
            + ", date='" + sale.currentSaleDateSQLString() + "'";
    DatabaseManager::defaultManager.query(QString::fromStdString(qryString));

}

void CommissionDAO::setBuyerCheckNo(string buyerNo, long checkNo)
{
    char buf[20];
    sprintf(buf, "%ld", checkNo);
    string qryString = "UPDATE buyercommission SET checkno=" + string(buf) + " WHERE customer_id='" + buyerNo + "' AND date='" + sale.currentSaleDateSQLString() + "' ";
    DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
}


long CommissionDAO::getBuyerCheckNo(string buyerNo)
{
    long checkNo = 0;
    string qryString = "SELECT checkno FROM buyercommission WHERE customer_id='" + buyerNo + "' AND date='" + sale.currentSaleDateSQLString() + "'";
    QSqlQuery buyerQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));

    if(buyerQuery.first()) {
        checkNo = DatabaseManager::valueAs<long>(buyerQuery,"checkno");
    }
    return checkNo;
}
