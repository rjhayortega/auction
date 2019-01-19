#include "chargedao.h"
#include <sstream>

ChargeDAO::ChargeDAO()
{

}

vector<Charge> ChargeDAO::getChargeList(AnimalCode code, CUST_TYPE custType, bool includeBeefCouncil)
{
    char type[2];
    sprintf(type, "%d", custType);

    char sex[10];
    char flaw[10];
    char codeGroup[10];


    sprintf(sex, "%d", code.getType());
    sprintf(flaw, "%d", (code.getFlaw() < 10 ? code.getFlaw() : 0));
    sprintf(codeGroup, "%d", CommissionDAO::getColorGroup(code.getColor()));

    /*
  string codeIdList = codeList(code);

  string condString =
    string("WHERE customer_type=") + string(type) + " AND expression != '0' AND id IN (" + codeIdList + ") "
    "" + (includeBeefCouncil ? "" : "AND beef_council=0") + " ";
*/

    string condString =
            "CROSS JOIN charge_code_rel "
            "WHERE "
            "charge_code_rel.color_group=" + string(codeGroup) + " "
            "AND "
            "charge_code_rel.sex=" + string(sex) + " "
            "AND "
            "charge_code_rel.flaw=" + string(flaw) + " "
            "AND "
            "expression != '0' "
            "" + string(includeBeefCouncil ? "" : "AND beef_council=0") + " "
            "AND "
            "charge.id=charge_code_rel.charge_id "

            "AND "
            "customer_type=" + string(type) + " "

            "";

    return getChargeListByCondition(condString);
}

vector<Charge> ChargeDAO::getChargeHistory(Invoice* invoice, Customer::Type type)
{
    char buf[20];
    sprintf(buf, "%ld", invoice->getNumber());

    string qryString =
            "SELECT charge_id, description, total "
            "FROM " + string(type == Customer::Seller ? "seller" : "buyer") + "chargesummary "
            "WHERE invoice_id=" + string(buf) + " AND charge_id != -1";

    vector<Charge> chargeList;

    QSqlQuery chargeHistoryQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
    while (chargeHistoryQuery.next()) {
        long id             = DatabaseManager::valueAs<long>(chargeHistoryQuery,"charge_id");
        string descrip      = DatabaseManager::valueAs<QString>(chargeHistoryQuery,"description").toStdString();
        string expression   = DatabaseManager::valueAs<QString>(chargeHistoryQuery,"total").toStdString();
        chargeList.push_back(Charge(id,descrip,expression, true, true, false, false, false, false));
    }
    return chargeList;
}

string ChargeDAO::codeList(AnimalCode code)
{
    char sex[10];
    char flaw[10];
    char codeGroup[10];

    string result;

    sprintf(sex, "%d", code.getType());
    sprintf(flaw, "%d", (code.getFlaw() < 10 ? code.getFlaw() : 0));
    sprintf(codeGroup, "%d", CommissionDAO::getColorGroup(code.getColor()));

    string queryString = "SELECT charge_id FROM charge_code_rel WHERE sex=" + string(sex) + " AND flaw=" + string(flaw) + " AND color_group=" + string(codeGroup) +" GROUP BY charge_id";

    QSqlQuery codeListQuery = DatabaseManager::defaultManager.query(QString::fromStdString(queryString));

    int querySize = codeListQuery.size();
    int i = 0;
    while (codeListQuery.next()) {
        result += DatabaseManager::valueAs<QString>(codeListQuery,"charge_id").toStdString();
        if(i != querySize - 1){
            result += ", ";
            i++;
        }
    }
    return result;
}

string ChargeDAO::groupIdList(CommissionDAO::COLOR_GROUP group)
{
    char buf[4];
    sprintf(buf, "%d", group);
    string groupChargeList;

    string queryStr = "SELECT DISTINCT(charge_id) FROM charge_code_rel WHERE color_group=" + string(buf);
    QSqlQuery groupListQuery = DatabaseManager::defaultManager.query(QString::fromStdString(queryStr));

    int i = 0;
    int listSize = groupListQuery.size();
    while (groupListQuery.next()) {

        groupChargeList += DatabaseManager::valueAs<QString>(groupListQuery,"charge_id").toStdString();
        groupChargeList += (i == listSize - 1 ? "" : ", ");
        i++;
    }
    return groupChargeList;
}

vector<Charge> ChargeDAO::getManualChargeList(CommissionDAO::COLOR_GROUP group, CUST_TYPE custType)
{
    char buf[4];
    char type[4];
    sprintf(buf, "%d", group);
    sprintf(type, "%d", custType);

    //  string groupChargeList = groupIdList(group);
    /*
  if(groupChargeList.length() > 0)
  {
    string condStr = "WHERE expression='0' AND id in (" + groupChargeList + ") AND customer_type=" + string(type) + "";
    return getChargeListByCondition(condStr);
  }
*/

    string condStr =
            "CROSS JOIN charge_code_rel "
            "WHERE "
            "charge.expression='0' "
            "AND "
            "charge_code_rel.color_group=" + string(buf) + " "
            "AND "
            "charge.customer_type=" + string(type) + " "
            "AND "
            "charge.id=charge_code_rel.charge_id "
            "";

    return getChargeListByCondition(condStr);

    return vector<Charge>();
}

vector <Charge> ChargeDAO::getChargeList(CUST_TYPE customerCharge, CommissionDAO::COLOR_GROUP cg)
{
    char custType[4], colorGroup[4];
    sprintf(custType, "%d", customerCharge);
    string condStr = "WHERE customer_type=" + string(custType) + " AND expression != '0' ";
    string groupChargeList = groupIdList(cg);

    if(cg != CommissionDAO::INVALID)
    {
        sprintf(colorGroup, "%d", cg);
        condStr += "AND id IN (" + groupChargeList + ") ";

        if(groupChargeList.size() == 0)
        {
            return vector<Charge>();
        }
    }

    return getChargeListByCondition(condStr);
}

vector <Charge> ChargeDAO::getChargeListByCondition(string condStr)
{
    string qryString =
            "SELECT "
            "DISTINCT(id), "
            "description, "
            "expression, "
            "charge_nosale, "
            "charge_resale, "
            "double_pairs, "
            "needs_multiplier, "
            "commission_charge, "
            "beef_council, "
            "break_type, "
            "scope "
            "FROM charge "
            "" + condStr + " ";

    QSqlQuery chargeListQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
    vector<Charge> chargeList;

    while (chargeListQuery.next()) {
        ChargeBreak::Type breakType = ChargeBreak::None;
        Charge::Scope scope = Charge::Transaction;


        int _id                  = DatabaseManager::valueAs<int>(chargeListQuery,"id");
        string _description      = DatabaseManager::valueAs<QString>(chargeListQuery,"description").toStdString();
        string _expression       = DatabaseManager::valueAs<QString>(chargeListQuery,"expression").toStdString();
        bool _charge_nosale      = DatabaseManager::valueAs<bool>(chargeListQuery,"charge_nosale");
        bool _charge_resale      = DatabaseManager::valueAs<bool>(chargeListQuery,"charge_resale");
        bool _double_pairs       = DatabaseManager::valueAs<bool>(chargeListQuery,"double_pairs");
        bool _needs_multiplier   = DatabaseManager::valueAs<bool>(chargeListQuery,"needs_multiplier");
        bool _commission_charge  = DatabaseManager::valueAs<bool>(chargeListQuery,"commission_charge");
        bool _beef_council       = DatabaseManager::valueAs<bool>(chargeListQuery,"beef_council");
        int  _break_type         = DatabaseManager::valueAs<int>(chargeListQuery,"break_type");
        int  _scope              = DatabaseManager::valueAs<int>(chargeListQuery,"scope");

        chargeList.push_back(Charge(_id, _description, _expression,
                                    _charge_nosale, _charge_resale,
                                    _double_pairs, _needs_multiplier,
                                    _commission_charge, _beef_council));

        breakType = ChargeBreak::Type(_break_type);
        chargeList.back().setBreakType(breakType);
        chargeList.back().setBreakList(getChargeBreakList(chargeList.back()));
        scope = Charge::Scope(_scope);
        chargeList.back().setScope(scope);
    }

    return chargeList;
}

void ChargeDAO::clearBeefCouncil()
{
    string qryString = "UPDATE charge SET beef_council=0";

    if(!DatabaseManager::defaultManager.query(QString::fromStdString(qryString)).first())
    {
        cerr << "Error clearing beef council charge, ensure database is running and check version" << endl;
    }
}

void ChargeDAO::saveCharge(Charge newCharge, CUST_TYPE custType, list<AnimalCode> codeList)
{
    if(newCharge.isBeefCouncil())
    {
        clearBeefCouncil();
    }

    QSqlQuery saveChargeQuery;
    QString qryString = QString("REPLACE INTO charge SET id=:id, description=:description, expression=:expression, "
                                "charge_nosale=:charge_nosale, charge_resale=:charge_resale, double_pairs=:double_pairs, "
                                "customer_type=:customer_type, needs_multiplier=:needs_multiplier, commission_charge=:commission_charge,"
                                " beef_council=:beef_council, break_type=:break_type, scope=:scope ");

    DatabaseManager::defaultManager.prepareQuery(saveChargeQuery,qryString);


    saveChargeQuery.bindValue(":id"                 , QVariant::fromValue<long>(newCharge.getId()));
    saveChargeQuery.bindValue(":description"        , QString::fromStdString(newCharge.getDescrip()));
    saveChargeQuery.bindValue(":expression"         , QString::fromStdString(newCharge.getExpression()));
    saveChargeQuery.bindValue(":charge_nosale"      , newCharge.chargesOnNoSale());
    saveChargeQuery.bindValue(":charge_resale"      , newCharge.chargesOnReSale());
    saveChargeQuery.bindValue(":double_pairs"       , newCharge.doublesOnPairs());
    saveChargeQuery.bindValue(":customer_type"      , custType);
    saveChargeQuery.bindValue(":needs_multiplier"   , newCharge.needsMultiplier());
    saveChargeQuery.bindValue(":commission_charge"  , newCharge.isCommissionCharge());
    saveChargeQuery.bindValue(":beef_council"       , newCharge.isBeefCouncil());
    saveChargeQuery.bindValue(":break_type"         , newCharge.getBreakType());
    saveChargeQuery.bindValue(":scope"              , newCharge.getScope());

    DatabaseManager::defaultManager.executeQuery(saveChargeQuery);

    if(newCharge.getId() == 0)
    {
        newCharge.setId(DatabaseManager::defaultManager.get_last_id(saveChargeQuery));
    }


    list<AnimalCode>::iterator currentCode;
    qryString = QString("DELETE FROM charge_code_rel WHERE charge_id=%1").arg(newCharge.getId());
    DatabaseManager::defaultManager.query(qryString);

    for(currentCode = codeList.begin(); currentCode != codeList.end(); currentCode++)
    {
//        if(currentCode == codeList.begin())
//        {
//            sprintf(colorGroup, "%d", currentCode->getColor());
//        }

        QSqlQuery insertQuery;
        qryString = QString("INSERT INTO charge_code_rel SET charge_id=:charge_id, sex=:sex, flaw=:flaw, color_group=:color_group");
        DatabaseManager::defaultManager.prepareQuery(insertQuery,qryString);

        insertQuery.bindValue(":charge_id"      , QVariant::fromValue<long>(newCharge.getId()));
        insertQuery.bindValue(":sex"            , currentCode->getType());
        insertQuery.bindValue(":flaw"           , currentCode->getFlaw());
        insertQuery.bindValue(":color_group"    , currentCode->getColor());
        DatabaseManager::defaultManager.executeQuery(insertQuery);
    }

    saveChargeBreakList(newCharge);
}

void ChargeDAO::deleteCharge(Charge charge)
{
    char id[20];
    sprintf(id, "%ld", charge.getId());

    string condStr = "DELETE FROM charge WHERE id=" + string(id) + " ";
    DatabaseManager::defaultManager.query(QString::fromStdString(condStr));

    condStr = "DELETE FROM charge_code_rel WHERE charge_id=" + string(id) + " ";
    DatabaseManager::defaultManager.query(QString::fromStdString(condStr));

}

list<AnimalCode> ChargeDAO::getCodeList(Charge charge)
{
    QString qryString = QString("SELECT sex, flaw, color_group FROM charge_code_rel WHERE charge_id=%1 ").arg(charge.getId());

    QSqlQuery codeListQuery = DatabaseManager::defaultManager.query(qryString);
    list<AnimalCode> codeList;

    while (codeListQuery.next()) {
        int _sex         = DatabaseManager::valueAs<int>(codeListQuery,"sex");
        int _flaw        = DatabaseManager::valueAs<int>(codeListQuery,"flaw");
        int _color_group = DatabaseManager::valueAs<int>(codeListQuery,"color_group");

        codeList.push_back(AnimalCode(_sex, _color_group, _flaw ));
    }
    return codeList;
}

ChargeAdjustment ChargeDAO::getAdjustment(Charge charge, Invoice* invoice, Customer::Type type)
{
    ChargeAdjustment adjustment;

    // buyer commission can't be adjusted
    if(type == Customer::Buyer && charge.getId() == 0)
    {
        return adjustment;
    }

    char chgId[20], invId[20];
    sprintf(chgId, "%ld", charge.getId());
    sprintf(invId, "%ld", invoice->getNumber());

    string qryString =
            "SELECT "
            "multiplier, "
            "adjustment "
            "FROM charge_adjustment "
            "WHERE "
            "invoice_id=" + string(invId) + " "
            "AND "
            "charge_id = " + string(chgId) + " "
            "";

    QSqlQuery adjustmentQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));

    if(adjustmentQuery.first()) {
        float _multiplier = DatabaseManager::valueAs<float>(adjustmentQuery,"multiplier");
        float _adjustment = DatabaseManager::valueAs<float>(adjustmentQuery,"adjustment");
        adjustment = ChargeAdjustment(_multiplier, _adjustment);
    }
    return adjustment;
}

vector<ChargeAdjustment> ChargeDAO::getAdjustments(Invoice* invoice)
{
    QString queryStr = QString("SELECT multiplier, adjustment, charge_id "
                               "FROM charge_adjustment WHERE invoice_id=%1 ").arg(invoice->getNumber());

    QSqlQuery adjustmentQuery = DatabaseManager::defaultManager.query(queryStr);

    vector<ChargeAdjustment> resultVector;
    while (adjustmentQuery.next()) {
        ChargeAdjustment temp;
        float _multiplier = DatabaseManager::valueAs<float>(adjustmentQuery,"multiplier");
        float _adjustment = DatabaseManager::valueAs<float>(adjustmentQuery,"adjustment");
        long  _charge_id  = DatabaseManager::valueAs<long>(adjustmentQuery,"charge_id");
        temp.setMultiplier(_multiplier);
        temp.setAdjustment(_adjustment);
        temp.setChargeId(_charge_id);
        resultVector.push_back(temp);
    }
    return resultVector;
}

void ChargeDAO::saveAdjustment(Charge charge, Invoice invoice, ChargeAdjustment adjustment)
{
    char chgId[20], invId[20], multiplier[20], adjust[30];

    sprintf(chgId, "%ld", charge.getId());
    sprintf(invId, "%ld", invoice.getNumber());
    sprintf(multiplier, "%0.2f", adjustment.getMultiplier());
    sprintf(adjust, "%0.2f", adjustment.getAdjustment());

    string qryString = "DELETE FROM charge_adjustment WHERE charge_id=" + string(chgId) + " AND invoice_id=" + string(invId) + " ";
    DatabaseManager::defaultManager.query(QString::fromStdString(qryString));

    QSqlQuery insertQuery;
    QString insertQryString = QString("INSERT INTO charge_adjustment SET charge_id=:charge_id, invoice_id=:invoice_id, "
                                      "multiplier=:multiplier, adjustment=:adjustment ");

    DatabaseManager::defaultManager.prepareQuery(insertQuery,insertQryString);
    insertQuery.bindValue(":charge_id"  , QVariant::fromValue<long>(charge.getId()));
    insertQuery.bindValue(":invoice_id" , QVariant::fromValue<long>(invoice.getNumber()));
    insertQuery.bindValue(":multiplier" , adjustment.getMultiplier());
    insertQuery.bindValue(":adjustment" , adjustment.getAdjustment());

    DatabaseManager::defaultManager.executeQuery(insertQuery);

}

void ChargeDAO::deleteChargeSummary(Customer customer, Customer::Type customerType)
{
    string qryString =
            "DELETE FROM " + string(customerType == Customer::Seller ? "seller" : "buyer") +  "chargesummary WHERE "
            " invoice_id = (SELECT id FROM " + string(customerType == Customer::Seller ? "seller" : "buyer") + "invoice WHERE customer_id='" + customer.getNumber() + "' AND date='" + sale.currentSaleDateSQLString() + "')";

    DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
}

void ChargeDAO::deleteAdjustment(Customer customer, Customer::Type customerType)
{
    char typeBuf[3];
    sprintf(typeBuf, "%d", customerType);

    string qryString = "DELETE FROM charge_adjustment WHERE invoice_id="
            "(SELECT id FROM " + string(customerType == Customer::Seller ? "seller" : "buyer") + "invoice where customer_id='" + customer.getNumber() + "' AND date='" + sale.currentSaleDateSQLString() + "') "
            "AND charge_id in (SELECT id FROM charge WHERE customer_type=" + string(typeBuf) + ")";

    DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
}


vector<ChargeDAO::SUMMARY_ITEM> ChargeDAO::getChargeSummary(CUST_TYPE custType, AnimalCode::Group colorGroup)
{
    string chargeQuery =
            string("SELECT description, sum(total) as _totalSum, charge_id FROM ") + string((custType == Seller ? "seller" : "buyer")) + "chargesummary WHERE invoice_id IN";

    string invoiceQuery = "SELECT id FROM " + string((custType == Seller ? "seller" : "buyer")) + "invoice WHERE "
            "date='" + sale.currentSaleDateSQLString() + "'";


    if(colorGroup != AnimalCode::Invalid)
    {
        string codeRange;

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
            codeRange = "90 <= color";
            break;

        case AnimalCode::Invalid:
            cerr << "INVALID UNIVERSE ERROR -- REINSTALL REALITY AND REBOOT" << endl;
            break;
        }

        invoiceQuery +=
                " AND customer_id IN(SELECT " + string((custType == Seller ? "seller" : "buyer")) + "ID FROM trans WHERE " + codeRange +
                " and date = '" + sale.currentSaleDateSQLString() + "')";
    }


    string qryString = chargeQuery + "(" + invoiceQuery + ")";

    qryString += " GROUP BY charge_id";

    QSqlQuery chargeSummaryQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
    vector<SUMMARY_ITEM> chargeSummary;
    SUMMARY_ITEM item;

    while (chargeSummaryQuery.next()) {
        item.descrip = DatabaseManager::valueAs<QString>(chargeSummaryQuery,"description").toStdString();
        item.total   = DatabaseManager::valueAs<float>(chargeSummaryQuery,"_totalSum");
        item.id      = DatabaseManager::valueAs<long>(chargeSummaryQuery,"charge_id");
        chargeSummary.push_back(item);
    }
    return chargeSummary;
}


vector<ChargeSummaryRecord> ChargeDAO::getChargeSummaryRecordList(long invoiceId, ChargeDAO::CUST_TYPE chargeType)
{
    char buf[20];
    sprintf(buf, "%ld", invoiceId);
    string qryString =
            "SELECT "
            "charge_id, "
            "description, "
            "total "
            "FROM " + string((chargeType == Seller ? "seller" : "buyer")) + "chargesummary "
            "WHERE "
            "invoice_id=" + string(buf) + "";

    QSqlQuery chargeSummaryQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
    vector<ChargeSummaryRecord> recordList;

    while (chargeSummaryQuery.next()) {
        long _charge_id     = DatabaseManager::valueAs<long>(chargeSummaryQuery,"charge_id");
        string _description = DatabaseManager::valueAs<QString>(chargeSummaryQuery,"description").toStdString();
        float _total        = DatabaseManager::valueAs<float>(chargeSummaryQuery,"total");
        recordList.push_back(ChargeSummaryRecord(_charge_id, _description, _total));
    }
    return recordList;
}


void ChargeDAO::swapChargeAdjustmentIds(Charge a, Charge b)
{
    string commandPart = "UPDATE charge_adjustment SET charge_id=";
    string conditionPart = " WHERE charge_id=";

    char aBuf[20], bBuf[20], tmpBuf[20];

    sprintf(aBuf, "%ld", a.getId());
    sprintf(bBuf, "%ld", b.getId());
    sprintf(tmpBuf, "%ld", -9999L);

    DatabaseManager::defaultManager.query(QString::fromStdString(commandPart + string(tmpBuf) + conditionPart + string(aBuf)));
    DatabaseManager::defaultManager.query(QString::fromStdString(commandPart + string(aBuf) + conditionPart + string(bBuf)));
    DatabaseManager::defaultManager.query(QString::fromStdString(commandPart + string(bBuf) + conditionPart + string(tmpBuf)));
}

void ChargeDAO::swapChargeBreakIds(Charge a, Charge b)
{
    string commandPart = "UPDATE charge_break SET charge_id=";
    string conditionPart = " WHERE charge_id=";;


    char aBuf[20], bBuf[20], tmpBuf[20];

    sprintf(aBuf, "%ld", a.getId());
    sprintf(bBuf, "%ld", b.getId());
    sprintf(tmpBuf, "%ld", -9999L);

    DatabaseManager::defaultManager.query(QString::fromStdString(commandPart + string(tmpBuf) + conditionPart + string(aBuf)));
    DatabaseManager::defaultManager.query(QString::fromStdString(commandPart + string(aBuf) + conditionPart + string(bBuf)));
    DatabaseManager::defaultManager.query(QString::fromStdString(commandPart + string(bBuf) + conditionPart + string(tmpBuf)));
}

void ChargeDAO::saveChargeBreakList(Charge& charge)
{
    vector<ChargeBreak> breakList = charge.getBreakList();
    decimateChargeBreakList(charge);

    QString queryStr = QString("INSERT INTO charge_break SET id=:id, charge_id=:charge_id, amount=:amount, expression=:expression");

    for(unsigned int i = 0; i < breakList.size(); i++)
    {
        QSqlQuery insertQuery;
        DatabaseManager::defaultManager.prepareQuery(insertQuery,queryStr);

        insertQuery.bindValue(":id"         , 0);
        insertQuery.bindValue(":charge_id"  , QVariant::fromValue<long>(charge.getId()));
        insertQuery.bindValue(":amount"     , breakList[i].getAmount());
        insertQuery.bindValue(":expression" , QString::fromStdString(breakList[i].getExpression()));
        DatabaseManager::defaultManager.executeQuery(insertQuery);
    }
}


void ChargeDAO::decimateChargeBreakList(Charge& charge)
{
    stringstream queryStr;
    queryStr << "DELETE FROM charge_break WHERE charge_id=" << charge.getId() << "";

    DatabaseManager::defaultManager.query(QString::fromStdString(queryStr.str()));
}

vector<ChargeBreak> ChargeDAO::getChargeBreakList(Charge& charge)
{
    QString queryStr = QString("SELECT id, amount, expression FROM charge_break WHERE charge_id=%1 ").arg(charge.getId());
    QSqlQuery chargeBreakListQuery = DatabaseManager::defaultManager.query(queryStr);

    vector<ChargeBreak> resultVector;

    while (chargeBreakListQuery.next()) {
        ChargeBreak baseBreak;
        long _id            = DatabaseManager::valueAs<long>(chargeBreakListQuery,"id");
        float _amount       = DatabaseManager::valueAs<float>(chargeBreakListQuery,"amount");
        string _expression  = DatabaseManager::valueAs<QString>(chargeBreakListQuery,"expression").toStdString();
        baseBreak.setId(_id);
        baseBreak.setAmount(_amount);
        baseBreak.setExpression(_expression);
        resultVector.push_back(baseBreak);

    }
    return resultVector;
}
