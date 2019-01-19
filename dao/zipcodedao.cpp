#include "zipcodedao.h"

ZipCodeDAO::ZipCodeDAO()
{
}

vector<Address> ZipCodeDAO::getZipCodeListByCity(string cityName)
{
    QSqlQuery zipListQuery;
    QString qryString = QString("SELECT zip, state, city FROM zip_code WHERE city=:city_ ");
    DatabaseManager::defaultManager.prepareQuery(zipListQuery,qryString);
    zipListQuery.bindValue(":city_", QString::fromStdString(cityName));
    return getZipCodeListByCondition(zipListQuery);
}

vector<Address> ZipCodeDAO::getZipCodeListByZip(string zipCode)
{
    QSqlQuery zipListQuery;
    QString qryString = QString("SELECT zip, state, city FROM zip_code WHERE zip=:zip_");
    DatabaseManager::defaultManager.prepareQuery(zipListQuery,qryString);
    zipListQuery.bindValue(":zip_", QString::fromStdString(zipCode));
    return getZipCodeListByCondition(zipListQuery);

}

vector<Address> ZipCodeDAO::getZipCodeListByCondition(QSqlQuery& zipCodeListQuery)
{
    DatabaseManager::defaultManager.executeQuery(zipCodeListQuery);

    vector<Address> zipCodeList;
    Address temp;
    zipCodeList.clear();

    while (zipCodeListQuery.next()) {
        string _zip     = DatabaseManager::valueAs<QString>(zipCodeListQuery,"zip").toStdString();
        string _state   = DatabaseManager::valueAs<QString>(zipCodeListQuery,"state").toStdString();;
        string _city    = DatabaseManager::valueAs<QString>(zipCodeListQuery,"city").toStdString();;
        temp = Address();
        temp.setZip(_zip);
        temp.setState(_state);
        temp.setCity(_city);
        zipCodeList.push_back(temp);
    }
    return zipCodeList;
}
