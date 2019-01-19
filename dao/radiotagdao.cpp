#include "radiotagdao.h"

RadioTagDAO::RadioTagDAO()
{}

void RadioTagDAO::saveRadioTag(RadioTag tag)
{
    QSqlQuery saveRadioTagQuery;

    QString qryString = QString("REPLACE INTO rfid_tag SET "
                                "id=:id, tag_number=:tag_number, seller_number=:seller_number, "
                                "buyer_number=:buyer_number, date=:date " );

    DatabaseManager::defaultManager.prepareQuery(saveRadioTagQuery,qryString);
    saveRadioTagQuery.bindValue(":id"               , QVariant::fromValue<long>(tag.getId()));
    saveRadioTagQuery.bindValue(":tag_number"       , QString::fromStdString(tag.getNumber()));
    saveRadioTagQuery.bindValue(":seller_number"    , QString::fromStdString(tag.getSellerNumber()));
    saveRadioTagQuery.bindValue(":buyer_number"     , QString::fromStdString(tag.getBuyerNumber()));
    saveRadioTagQuery.bindValue(":date"             , QString::fromStdString(sale.currentSaleDateSQLString()));
    DatabaseManager::defaultManager.executeQuery(saveRadioTagQuery);
}

vector<RadioTag> RadioTagDAO::getSellerRadioTagList(Seller seller)
{
    return getRadioTagListByCondition("WHERE seller_number='" + seller.getNumber() + "'");
}

RadioTag RadioTagDAO::getRadioTagByCondition(string condStr)
{
    vector<RadioTag> tempList = getRadioTagListByCondition(condStr);

    if(tempList.size() < 1)
    {
        return RadioTag();
    }

    return tempList[0];
}

vector<RadioTag> RadioTagDAO::getRadioTagListByCondition(string condStr)
{
    string qryString =
            "SELECT id, tag_number, seller_number, buyer_number, date, sale_time "
            "FROM rfid_tag " + condStr + (condStr.length() > 0 ? " AND " : " WHERE " ) + "date='" + sale.currentSaleDateSQLString() + "'";

    QSqlQuery tagListQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));

    vector<RadioTag> tagList;
    while (tagListQuery.next()) {
        long _id              = DatabaseManager::valueAs<long>(tagListQuery,"id");
        string _tag_number    = DatabaseManager::valueAs<QString>(tagListQuery,"tag_number").toStdString();
        string _seller_number = DatabaseManager::valueAs<QString>(tagListQuery,"seller_number").toStdString();
        string _buyer_number  = DatabaseManager::valueAs<QString>(tagListQuery,"buyer_number").toStdString();
        string _date          = DatabaseManager::valueAs<QString>(tagListQuery,"date").toStdString();
        string _sale_time     = DatabaseManager::valueAs<QString>(tagListQuery,"sale_time").toStdString();
        tagList.push_back(RadioTag(_id, _tag_number, _seller_number, _buyer_number,
                                   Date::fromString(_date, "YYYY-mm-dd"), DateTime::fromString(_sale_time, "YYYY-mm-dd")));
    }
    return tagList;
}
