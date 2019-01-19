
#include "truckingrecorddao.h"

TruckingRecordDAO::TruckingRecordDAO()
{}

TruckingRecord TruckingRecordDAO::getCustomerTruckingRecord(Customer customer, ChargeDAO::CUST_TYPE customerType)
{
    char type[3];
    sprintf(type, "%d", customerType);
    string condStr = "WHERE customer_id = '" + customer.getNumber() + "' AND customer_type=" + string(type) + " ";;
    return getTruckingRecordByCondition(condStr);
}

void TruckingRecordDAO::deleteTruckingRecordList(Customer customer, Customer::Type customerType)
{
    char typeBuf[3];
    sprintf(typeBuf, "%d", customerType);

    string qryString = "DELETE FROM trucking_record WHERE customer_id='" + customer.getNumber() + "' AND customer_type=" + string(typeBuf) + " AND date='" + sale.currentSaleDateSQLString() + "' ";
    DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
}

vector<TruckingRecord> TruckingRecordDAO::getTruckingRecordList()
{
    return getTruckingRecordListByCondition("");
}

vector<TruckingRecord> TruckingRecordDAO::getTruckingRecordList(Customer customer, ChargeDAO::CUST_TYPE customerType)
{
    char type[3];
    sprintf(type, "%d", customerType);
    string condStr = "customer_id='" + customer.getNumber() + "' AND customer_type=" + string(type) + "";
    return getTruckingRecordListByCondition(condStr);
}

vector<TruckingRecord> TruckingRecordDAO::getTruckingRecordList(Customer::Type customerType)
{
    char type[3];
    sprintf(type, "%d", customerType);
    string condStr = "customer_type=" + string(type) + "";
    return getTruckingRecordListByCondition(condStr);

}

vector<TruckingRecordDAO::TruckerCustomer> TruckingRecordDAO::getTruckingCustomerList(bool allowDuplicate, Customer::Type customerType)
{
    char type[4];
    sprintf(type, "%d", customerType);

    string qryString =
            "SELECT "
            "customer_id, "
            "customer_type "
            "FROM trucking_record "
            "WHERE "
            "date = '" + sale.currentSaleDateSQLString() + "' "
            "" + (customerType != Customer::Both ? "AND " : "") + ""
            "" + (customerType != Customer::Both ? "customer_type=" + string(type) + " " : "") + ""
            "ORDER BY customer_id";
    QSqlQuery trackQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
    vector<TruckerCustomer> customerList;

    TruckerCustomer temp;
    while (trackQuery.next()) {
        temp.number = DatabaseManager::valueAs<QString>(trackQuery,"customer_id").toStdString();
        int _type   = DatabaseManager::valueAs<int>(trackQuery,"customer_type");
        temp.type = ChargeDAO::CUST_TYPE(_type);

        if(allowDuplicate || find(customerList.begin(), customerList.end(), temp) == customerList.end())
        {
            customerList.push_back(temp);
        }
    }

    return customerList;
}

void TruckingRecordDAO::saveTruckingRecord(TruckingRecord record, Customer customer, ChargeDAO::CUST_TYPE customerType)
{
    if(record.getTruckerName().length() < 1 || record.getTruckerName().find_first_not_of(' ') == string::npos)
    {
        return;
    }
    QSqlQuery saveTruckRecQuery;
    QString qryString = QString("REPLACE INTO trucking_record SET id=:id, customer_id=:customer_id, "
                                "trucker_name=:trucker_name, price=:price, quantity=:quantity, mode=:mode,"
                                "date=:date, customer_type=:customer_type, checkno=:checkno ");
    DatabaseManager::defaultManager.prepareQuery(saveTruckRecQuery,qryString);

    saveTruckRecQuery.bindValue(":id"            , QVariant::fromValue<long>(record.getId()));
    saveTruckRecQuery.bindValue(":customer_id"   , QString::fromStdString(customer.getNumber()));
    saveTruckRecQuery.bindValue(":trucker_name"  , QString::fromStdString(record.getTruckerName()));
    saveTruckRecQuery.bindValue(":price"         , QVariant::fromValue<double>(record.getPrice()));
    saveTruckRecQuery.bindValue(":quantity"      , QVariant::fromValue<long>(record.getQuantity()));
    saveTruckRecQuery.bindValue(":mode"          , record.getMode());
    saveTruckRecQuery.bindValue(":date"          , QString::fromStdString(sale.currentSaleDateSQLString()));
    saveTruckRecQuery.bindValue(":customer_type" , customerType);
    saveTruckRecQuery.bindValue(":checkno"       , QVariant::fromValue<long>(record.getCheckNo()));

    DatabaseManager::defaultManager.executeQuery(saveTruckRecQuery);
}

void TruckingRecordDAO::deleteTruckingRecord(TruckingRecord record)
{
    char id[20];
    sprintf(id, "%ld", record.getId());
    string qryString = "DELETE FROM trucking_record WHERE id=" + string(id) + " ";
    DatabaseManager::defaultManager.query(qryString.c_str());
}

TruckingRecord TruckingRecordDAO::getTruckingRecordByCondition(string condStr)
{
    vector<TruckingRecord> temp = getTruckingRecordListByCondition(condStr);
    return (temp.size() > 0 ? temp[0] : TruckingRecord());
}

vector<TruckingRecord> TruckingRecordDAO::getTruckingRecordListByCondition(string condStr)
{
    string dateStr = sale.currentSaleDateSQLString();
    string qryString =
            "SELECT "
            "id, "
            "customer_id, "
            "trucker_name, "
            "price, quantity, "
            "mode, "
            "date, "
            "checkno, "
            "customer_type "
            "FROM trucking_record "
            "WHERE date='" + dateStr + "' "
            "" + (condStr.length() > 0 ? " AND " : "") + condStr + " "
            " ORDER BY customer_id ";

    //    + (condStr.length() > 0 ? " AND " : "WHERE ") + "date='" + sale.currentSaleDateSQLString + "' order by customer_id";

    QSqlQuery truckingRecQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
    vector<TruckingRecord> truckingList;


    while (truckingRecQuery.next()) {

        long _id              = DatabaseManager::valueAs<long>(truckingRecQuery,"id");
        string _truckerName   = DatabaseManager::valueAs<QString>(truckingRecQuery,"trucker_name").toStdString();
        double _price         = DatabaseManager::valueAs<double>(truckingRecQuery,"price");
        long _quantity        = DatabaseManager::valueAs<long>(truckingRecQuery,"quantity");
        int _mode             = DatabaseManager::valueAs<int>(truckingRecQuery,"mode");

        long _checkno         = DatabaseManager::valueAs<long>(truckingRecQuery,"checkno");
        string _consignerNo   = DatabaseManager::valueAs<QString>(truckingRecQuery,"customer_id").toStdString();
        int _customer_type    = DatabaseManager::valueAs<int>(truckingRecQuery,"customer_type");

        truckingList.push_back(TruckingRecord(_id, _truckerName, _price,
                                              _quantity, TruckingRecord::MODE(_mode),
                                              sale.currentSaleDate(),
                                              _checkno, _consignerNo, Customer::Type(_customer_type)));
    }

    return truckingList;
}
