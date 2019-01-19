#include "customerdao.h"
#include <sstream>
#include <QVariant>

// 09 Jul 09 rhw	Fix SellerDAO::sellerInDailyFile(string id).
// 15 Jun 09 rhw	Add method sellerInDailyFile(string id).

const QString CUSTOMER_SELECT_STR = QString("SELECT id, name, address1, address2, city, state,"
                                      "zip, county, phone, ssn, comment, credit_card, mad_cow, beef_council,"
                                      "mailing_list, company, perm_number, altered, docket, relation FROM customer ");


SetupDAO CustomerDAO::setup;

void CustomerDAO::deleteByDocket(Customer customer)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    if(customer.getDocket() != "" && customer.getSocialSecurityNumber() != "")
    {
        QSqlQuery deleteQuery;
        QString queryStr = QString("DELETE FROM CUSTOMER WHERE "
                 "type=0 AND altered=0 AND docket=:docket AND ssn=:ssn" );
        DatabaseManager::defaultManager.prepareQuery(deleteQuery,queryStr);
        deleteQuery.bindValue(":docket" , QString::fromStdString(customer.getDocket()));
        deleteQuery.bindValue(":ssn"    , QString::fromStdString(customer.getSocialSecurityNumber()));

        DatabaseManager::defaultManager.executeQuery(deleteQuery);
        int nfound = deleteQuery.numRowsAffected();
        if(nfound < 0)
        {
            cerr << "A database error seems to have occured, make sure that you are using the correct version of the auction6 database" << endl;
        }
        else if(nfound == 0)
        {
            cerr << "No matching columns were found while deleting customers by docket" << endl;
            cerr << "'" << customer.getDocket() << "', '" << customer.getSocialSecurityNumber() << "' " << endl;
        }
    }
    else
    {
        cerr << "Empty docket or tax id, too afraid to do anything (customerdao.cpp l. " << __LINE__ << ") " << endl;
    }

}

Customer CustomerDAO::loadByCondition(string whereString)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    Customer temp;

    string qryString = CUSTOMER_SELECT_STR.toStdString() + whereString;

    QSqlQuery loadQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
    if(loadQuery.first()) {
        int _id          = DatabaseManager::valueAs<int>(loadQuery,"id");
        string _name     = DatabaseManager::valueAs<QString>(loadQuery,"name").toStdString();
        string _address1 = DatabaseManager::valueAs<QString>(loadQuery,"address1").toStdString();
        string _address2 = DatabaseManager::valueAs<QString>(loadQuery,"address2").toStdString();
        string _city     = DatabaseManager::valueAs<QString>(loadQuery,"city").toStdString();
        string _state    = DatabaseManager::valueAs<QString>(loadQuery,"state").toStdString();
        string _zip      = DatabaseManager::valueAs<QString>(loadQuery,"zip").toStdString();
        string _county   = DatabaseManager::valueAs<QString>(loadQuery,"county").toStdString();
        string _phoneNum = DatabaseManager::valueAs<QString>(loadQuery,"phone").toStdString();
        string _social   = DatabaseManager::valueAs<QString>(loadQuery,"ssn").toStdString();
        string _comment  = DatabaseManager::valueAs<QString>(loadQuery,"comment").toStdString();
        string _cred_card= DatabaseManager::valueAs<QString>(loadQuery,"credit_card").toStdString();
        bool _madCowCert = DatabaseManager::valueAs<bool>(loadQuery,"mad_cow");
        bool _beef_counc = DatabaseManager::valueAs<bool>(loadQuery,"beef_council");
        bool _mail_list  = DatabaseManager::valueAs<bool>(loadQuery,"mailing_list");
        string _company  = DatabaseManager::valueAs<QString>(loadQuery,"company").toStdString();
        string _perm_num = DatabaseManager::valueAs<QString>(loadQuery,"perm_number").toStdString();
        bool _altered    = DatabaseManager::valueAs<bool>(loadQuery,"altered");
        string _docket   = DatabaseManager::valueAs<QString>(loadQuery,"docket").toStdString();
        int _relation    = DatabaseManager::valueAs<int>(loadQuery,"relation");

        temp = Customer(_id, Name(_name),
                        Address(_address1, _address2, _city, _state, _zip, "",_county),
                        ContactList(_phoneNum), "", _social, _cred_card, _comment,
                        _madCowCert, _beef_counc, _mail_list,
                        _company,_relation);

        temp.setNumber(_perm_num);
        temp.setAltered(_altered);
        temp.setDocket(_docket);
        temp.setPermNumber(QString::fromStdString(_perm_num));
    }

    return temp;
}


Customer CustomerDAO::loadByCondition(QSqlQuery &loadQuery)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    Customer temp;
    DatabaseManager::defaultManager.executeQuery(loadQuery);
    if(loadQuery.first()) {
        int _id          = DatabaseManager::valueAs<int>(loadQuery,"id");
        string _name     = DatabaseManager::valueAs<QString>(loadQuery,"name").toStdString();
        string _address1 = DatabaseManager::valueAs<QString>(loadQuery,"address1").toStdString();
        string _address2 = DatabaseManager::valueAs<QString>(loadQuery,"address2").toStdString();
        string _city     = DatabaseManager::valueAs<QString>(loadQuery,"city").toStdString();
        string _state    = DatabaseManager::valueAs<QString>(loadQuery,"state").toStdString();
        string _zip      = DatabaseManager::valueAs<QString>(loadQuery,"zip").toStdString();
        string _county   = DatabaseManager::valueAs<QString>(loadQuery,"county").toStdString();
        string _phoneNum = DatabaseManager::valueAs<QString>(loadQuery,"phone").toStdString();
        string _social   = DatabaseManager::valueAs<QString>(loadQuery,"ssn").toStdString();
        string _comment  = DatabaseManager::valueAs<QString>(loadQuery,"comment").toStdString();
        string _cred_card= DatabaseManager::valueAs<QString>(loadQuery,"credit_card").toStdString();
        bool _madCowCert = DatabaseManager::valueAs<bool>(loadQuery,"mad_cow");
        bool _beef_counc = DatabaseManager::valueAs<bool>(loadQuery,"beef_council");
        bool _mail_list  = DatabaseManager::valueAs<bool>(loadQuery,"mailing_list");
        string _company  = DatabaseManager::valueAs<QString>(loadQuery,"company").toStdString();
        string _perm_num = DatabaseManager::valueAs<QString>(loadQuery,"perm_number").toStdString();
        bool _altered    = DatabaseManager::valueAs<bool>(loadQuery,"altered");
        string _docket   = DatabaseManager::valueAs<QString>(loadQuery,"docket").toStdString();
        int _relation    = DatabaseManager::valueAs<int>(loadQuery,"relation");


        temp = Customer(_id, Name(_name),
                        Address(_address1, _address2, _city, _state, _zip, "",_county),
                        ContactList(_phoneNum), "", _social, _cred_card, _comment,
                        _madCowCert, _beef_counc, _mail_list,
                        _company,_relation);

        temp.setNumber(_perm_num);
        temp.setAltered(_altered);
        temp.setDocket(_docket);
        temp.setPermNumber(QString::fromStdString(_perm_num));
    }

    return temp;
}



Customer CustomerDAO::loadFromPermNumber(string number, bool loadSplits)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    Customer temp;
    QSqlQuery loadQuery;
    QString qryString = CUSTOMER_SELECT_STR + " WHERE perm_number=:perm_number";
    DatabaseManager::defaultManager.prepareQuery(loadQuery,qryString);
    loadQuery.bindValue(":perm_number" , QString::fromStdString(number) );

    temp = loadByCondition(loadQuery);
    temp.setNumber(number);

    if(loadSplits && temp.getId() == 0 && (number.find_first_of("-") != string::npos || number.find_first_of("/") != string::npos))
    {
        return loadFromBasePermNumber(number);
    }

    return temp;
}


Customer CustomerDAO::loadFromBasePermNumber(string number)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    string baseNumber;

    for(int i = 0; i < number.length() && !(number[i] == '-' || number[i] == '/'); i++)
    {
        baseNumber += number[i];
    }

    Customer temp;

    if(baseNumber.length() > 0)
    {
        temp = loadByCondition(string("WHERE perm_number='") + baseNumber + "'");
        temp.setNumber(number);
    }

    return temp;
}

Customer CustomerDAO::loadFromId(int id)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    QSqlQuery loadQuery;
    QString qryString = CUSTOMER_SELECT_STR + "WHERE id=:id";
    DatabaseManager::defaultManager.prepareQuery(loadQuery,qryString);
    loadQuery.bindValue(":id" , QVariant::fromValue<int>(id));

    return CustomerDAO::loadByCondition(loadQuery);
}

Customer CustomerDAO::loadFromName(string name)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    QSqlQuery loadQuery;
    QString qryString = CUSTOMER_SELECT_STR + "WHERE name=:name";
    DatabaseManager::defaultManager.prepareQuery(loadQuery,qryString);
    loadQuery.bindValue(":name" , QString::fromStdString(name));
    return CustomerDAO::loadByCondition(loadQuery);
}

Customer CustomerDAO::loadFromPhone(string phone)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    QSqlQuery loadQuery;
    QString qryString = CUSTOMER_SELECT_STR +
            "WHERE (phone like :phon) or ( CONCAT(SUBSTR(phone,-8,3),RIGHT(phone,4)) like :phon1)";
    DatabaseManager::defaultManager.prepareQuery(loadQuery,qryString);
    loadQuery.bindValue(":phon" , "%"+QString::fromStdString(phone));
    //QT doesn't allow to use same bind name twice in the statement. Used another name for same variable.
    loadQuery.bindValue(":phon1" , "%"+QString::fromStdString(phone));
    return CustomerDAO::loadByCondition(loadQuery);
}

void CustomerDAO::savePermNumber(Customer customer)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    //  string customerNumber = customer.getCustomerPartOfNumber();
    clearPermNumber(customer.getNumber());
    char buf[20];
    sprintf(buf, "%ld", customer.getId());
    string qryString = "UPDATE customer SET perm_number='" + customer.getNumber() + "' WHERE id=" + string(buf) + "";
    DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
}


bool CustomerDAO::previouslyAltered(long custId)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    QString queryStr = QString("SELECT altered FROM customer WHERE id=%1").arg(custId);
    bool result = false;

    QSqlQuery alteredQuery = DatabaseManager::defaultManager.query(queryStr);

    if(alteredQuery.first()) {
        result = DatabaseManager::valueAs<bool>(alteredQuery,"altered");
    }

    return result;
}

int CustomerDAO::saveCustomer(Customer customer, Customer::Type type, bool altered, bool saveNumber)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    QString qryString;
    char idStr[20];
    sprintf(idStr, "%ld", customer.getId());
    int custId = 0;
    char typeStr[5];
    char alteredStr[5];

    sprintf(typeStr, "%d", type);
    sprintf(alteredStr, "%d", altered);

    char madCow[3], beefCouncil[3], mailingList[3];
    sprintf(madCow, "%d", customer.isMadCowCertified());
    sprintf(beefCouncil, "%d", customer.isBeefCouncil());
    sprintf(mailingList, "%d", customer.isOnMailingList());

    if(saveNumber)
    {
        clearPermNumber(customer.getNumber());
    }

    QSqlQuery query;
    qryString = QString("REPLACE INTO customer (id,name,address1,address2,city,state,"
                        "zip,county,phone,ssn,credit_card, comment,"
                        "mad_cow, mailing_list, beef_council, "
                        "company, type, altered, perm_number,docket,relation) "
                        "VALUES (:id, :name, :address1, :address2, :city, :state,"
                        ":zip, :county, :phone, :ssn, :credit_card, :comment,"
                        ":mad_cow, :mailing_list, :beef_council, "
                        ":company, :type, :altered, :perm_number, :docket , :relation ) "
                        );

    DatabaseManager::defaultManager.prepareQuery(query,qryString);
    query.bindValue(":id"           , customer.getId());
    query.bindValue(":name"         ,QString::fromStdString(customer.getName().getLast()));
    query.bindValue(":address1"     ,QString::fromStdString(customer.getAddress().getAddress1()));
    query.bindValue(":address2"     ,QString::fromStdString(customer.getAddress().getAddress2()));
    query.bindValue(":city"         ,QString::fromStdString(customer.getAddress().getCity()));
    query.bindValue(":state"        ,QString::fromStdString(customer.getAddress().getState()));
    query.bindValue(":zip"          ,QString::fromStdString(customer.getAddress().getZip()));
    query.bindValue(":county"       ,QString::fromStdString(customer.getAddress().getCounty()));
    query.bindValue(":phone"        ,QString::fromStdString(customer.getContactList().getFirstPhone()));
    query.bindValue(":ssn"          ,QString::fromStdString(customer.getSocialSecurityNumber()));
    query.bindValue(":credit_card"  ,QString::fromStdString(customer.getCreditCardNumber()));
    query.bindValue(":comment"      ,QString::fromStdString(customer.getComment()));
    query.bindValue(":mad_cow"      ,QString::fromStdString(madCow));
    query.bindValue(":mailing_list" ,QString::fromStdString(mailingList));
    query.bindValue(":beef_council" ,QString::fromStdString(beefCouncil));
    query.bindValue(":company"      ,QString::fromStdString(customer.getCompany()));
    query.bindValue(":type"         ,QString::fromStdString(typeStr));
    query.bindValue(":altered"      ,QString::fromStdString(alteredStr));
    query.bindValue(":perm_number"  ,QString::fromStdString(saveNumber ? customer.getNumber() : ""));
    query.bindValue(":docket"       ,QString::fromStdString(customer.getDocket()));
    query.bindValue(":relation"      ,QVariant(customer.getRelation()));

    DatabaseManager::defaultManager.executeQuery(query);

    custId = customer.getId();
    if(custId == 0)
    {
        custId = DatabaseManager::defaultManager.get_last_id(query);
    }
    return custId;
}

void CustomerDAO::clearPermNumber(string number)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    string qryString = "UPDATE customer SET perm_number='' WHERE perm_number='" + number + "'";
    DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
}

void CustomerDAO::updateChildCountryOfOrigin(Customer customer)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    stringstream queryStr;
    queryStr << "UPDATE seller set mad_cow=" << int(customer.isMadCowCertified()) << " WHERE customer_id=" << customer.getId();
    DatabaseManager::defaultManager.query(QString::fromStdString(queryStr.str()));
}

bool CustomerDAO::nameExists(string name)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    QSqlQuery nameEsistsQuery;
    QString qryString = "SELECT count(*) as _recCount FROM customer WHERE name=:nameCond ";
    DatabaseManager::defaultManager.prepareQuery(nameEsistsQuery,qryString);
    nameEsistsQuery.bindValue(":nameCond",QString::fromStdString(name));

    DatabaseManager::defaultManager.executeQuery(nameEsistsQuery);
    bool found = false;
    if(nameEsistsQuery.first()) {
        int _recCount = DatabaseManager::valueAs<int>(nameEsistsQuery,"_recCount");
        found = (_recCount > 0);
    }
    return found;
}


void CustomerDAO::deleteCustomer(Customer customer)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    QString qryString = QString("DELETE FROM customer WHERE id=%1 ").arg(customer.getId());
    DatabaseManager::defaultManager.query(qryString);
}

void CustomerDAO::clearLienImports()
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    char buf[2];
    sprintf(buf, "%d", false);
    string qryString = "DELETE FROM customer WHERE altered=" + string(buf) + "";
    DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
}

vector<Customer> CustomerDAO::getCustomerList(Customer::Type type)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    return CustomerDAO::getCustomerListByCondition("", type);
}

vector<Customer> CustomerDAO::getCustomerListThatBeginsWith(string namePart, Customer::Type type, bool looseMatch)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    QString qryString = CUSTOMER_SELECT_STR;
    QString orderString = QString(" ORDER BY name ASC");

    QSqlQuery loadQuery;

    QString nameBindValue = QString::fromStdString(namePart);
    if(looseMatch) {
//        qryString += "WHERE name SOUNDS LIKE :namePart ";
        qryString += QString("WHERE name SOUNDS LIKE '%1%' ").arg(nameBindValue);
    }
    else {
        switch(namePart.length()) {
        case 0:
            qryString += QString("WHERE (true) ");
            break;
        case 1:
//            qryString += "WHERE name LIKE :namePart ";
            qryString += QString("WHERE name LIKE '%1%' ").arg(nameBindValue);
            //nameBindValue ="'" + nameBindValue + "%'";
//            nameBindValue = nameBindValue + "%";
            break;
        default:
//            qryString += "WHERE ( name REGEXP :namePart )";
           qryString += QString("WHERE ( name REGEXP '^%1.*' )").arg(nameBindValue);
//           nameBindValue="^"+nameBindValue+".*";
            break;
        }
    }

    qryString += " AND ( type="+QString("%1 )").arg(type) + orderString;
    DatabaseManager::defaultManager.prepareQuery(loadQuery,qryString);
//    loadQuery.bindValue(":namePart" , QVariant::fromValue<QString>(nameBindValue));
    return getCustomerListByCondition(loadQuery);
}

vector<Customer> CustomerDAO::getCustomerListForCompany(string company, Customer::Type type)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    QSqlQuery loadQuery;
    QString qryString = CUSTOMER_SELECT_STR +
            QString("WHERE company LIKE :company AND type=%1 ORDER BY name ASC").arg(type);
    DatabaseManager::defaultManager.prepareQuery(loadQuery,qryString);
    loadQuery.bindValue(":company"  , QString::fromStdString(company)+"%");
    return getCustomerListByCondition(loadQuery);
}

vector<Customer> CustomerDAO::getCustomerListByCondition(string condStr, Customer::Type type)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    char typeStr[5];
    sprintf(typeStr, "%d", type);
    vector<Customer> custList;
    string qryString = CUSTOMER_SELECT_STR.toStdString()
            + condStr + (condStr.length() > 0 ? " AND " : " ") + ""
            " " + (condStr.length() < 1 ? " WHERE " : "") + "type=" + string(typeStr) + " ORDER BY name ASC";

    QSqlQuery loadQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));

    while (loadQuery.next()) {

        int _id          = DatabaseManager::valueAs<int>(loadQuery,"id");
        string _name     = DatabaseManager::valueAs<QString>(loadQuery,"name").toStdString();
        string _address1 = DatabaseManager::valueAs<QString>(loadQuery,"address1").toStdString();
        string _address2 = DatabaseManager::valueAs<QString>(loadQuery,"address2").toStdString();
        string _city     = DatabaseManager::valueAs<QString>(loadQuery,"city").toStdString();
        string _state    = DatabaseManager::valueAs<QString>(loadQuery,"state").toStdString();
        string _zip      = DatabaseManager::valueAs<QString>(loadQuery,"zip").toStdString();
        string _county   = DatabaseManager::valueAs<QString>(loadQuery,"county").toStdString();
        string _phoneNum = DatabaseManager::valueAs<QString>(loadQuery,"phone").toStdString();
        string _social   = DatabaseManager::valueAs<QString>(loadQuery,"ssn").toStdString();
        string _comment  = DatabaseManager::valueAs<QString>(loadQuery,"comment").toStdString();
        string _cred_card= DatabaseManager::valueAs<QString>(loadQuery,"credit_card").toStdString();
        bool _madCowCert = DatabaseManager::valueAs<bool>(loadQuery,"mad_cow");
        bool _beef_counc = DatabaseManager::valueAs<bool>(loadQuery,"beef_council");
        bool _mail_list  = DatabaseManager::valueAs<bool>(loadQuery,"mailing_list");
        string _company  = DatabaseManager::valueAs<QString>(loadQuery,"company").toStdString();
        string _perm_num = DatabaseManager::valueAs<QString>(loadQuery,"perm_number").toStdString();
        bool _altered    = DatabaseManager::valueAs<bool>(loadQuery,"altered");
        string _docket   = DatabaseManager::valueAs<QString>(loadQuery,"docket").toStdString();
        int _relation    = DatabaseManager::valueAs<int>(loadQuery,"relation");


        Customer temp = Customer(_id, Name(_name),
                                 Address(_address1, _address2, _city, _state, _zip, "",_county),
                                 ContactList(_phoneNum), "", _social, _cred_card, _comment,
                                 _madCowCert, _beef_counc, _mail_list,
                                 _company, _relation);

        temp.setNumber(_perm_num);
        temp.setAltered(_altered);
        temp.setDocket(_docket);
        temp.setPermNumber(QString::fromStdString(_perm_num));

        custList.push_back(temp);
    }
    return custList;
}

vector<Customer> CustomerDAO::getCustomerListByCondition(QSqlQuery &loadQuery)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    vector<Customer> custList;
    DatabaseManager::defaultManager.executeQuery(loadQuery);
    qDebug() << "Last query is: " << loadQuery.lastQuery();
    while (loadQuery.next()) {

        int _id          = DatabaseManager::valueAs<int>(loadQuery,"id");
        string _name     = DatabaseManager::valueAs<QString>(loadQuery,"name").toStdString();
        string _address1 = DatabaseManager::valueAs<QString>(loadQuery,"address1").toStdString();
        string _address2 = DatabaseManager::valueAs<QString>(loadQuery,"address2").toStdString();
        string _city     = DatabaseManager::valueAs<QString>(loadQuery,"city").toStdString();
        string _state    = DatabaseManager::valueAs<QString>(loadQuery,"state").toStdString();
        string _zip      = DatabaseManager::valueAs<QString>(loadQuery,"zip").toStdString();
        string _county   = DatabaseManager::valueAs<QString>(loadQuery,"county").toStdString();
        string _phoneNum = DatabaseManager::valueAs<QString>(loadQuery,"phone").toStdString();
        string _social   = DatabaseManager::valueAs<QString>(loadQuery,"ssn").toStdString();
        string _comment  = DatabaseManager::valueAs<QString>(loadQuery,"comment").toStdString();
        string _cred_card= DatabaseManager::valueAs<QString>(loadQuery,"credit_card").toStdString();
        bool _madCowCert = DatabaseManager::valueAs<bool>(loadQuery,"mad_cow");
        bool _beef_counc = DatabaseManager::valueAs<bool>(loadQuery,"beef_council");
        bool _mail_list  = DatabaseManager::valueAs<bool>(loadQuery,"mailing_list");
        string _company  = DatabaseManager::valueAs<QString>(loadQuery,"company").toStdString();
        string _perm_num = DatabaseManager::valueAs<QString>(loadQuery,"perm_number").toStdString();
        bool _altered    = DatabaseManager::valueAs<bool>(loadQuery,"altered");
        string _docket   = DatabaseManager::valueAs<QString>(loadQuery,"docket").toStdString();
        int  _relation   = DatabaseManager::valueAs<int>(loadQuery,"relation");

        Customer temp = Customer(_id, Name(_name),
                                 Address(_address1, _address2, _city, _state, _zip, "",_county),
                                 ContactList(_phoneNum), "", _social, _cred_card, _comment,
                                 _madCowCert, _beef_counc, _mail_list,
                                 _company,_relation);

        temp.setNumber(_perm_num);
        temp.setAltered(_altered);
        temp.setDocket(_docket);
        temp.setPermNumber(QString::fromStdString(_perm_num));

        custList.push_back(temp);
    }
    return custList;
}



Seller SellerDAO::loadFromNumber(string number)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    Seller temp = loadByCondition(string("number='") + number + "'");
    temp.setNumber(number);
    return temp;
}


Seller SellerDAO::getSeller(Tag tag)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    return loadFromNumber(tag.getSellerId());
}

void SellerDAO::updateParentCountryOfOrigin(Seller seller)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    stringstream queryStr;
    queryStr << "UPDATE customer SET mad_cow=" << int(seller.isMadCowCertified()) << " WHERE id=" << seller.getId();
    DatabaseManager::defaultManager.query(QString::fromStdString(queryStr.str()));
}

Seller SellerDAO::loadByCondition(string whereString)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    Seller seller;
    string qryString =
            "SELECT " + fieldList + " FROM seller "
            "WHERE date='" + SaleManager().currentSaleDateSQLString() + "' " +
            (whereString.length() > 0 ? " AND " : "") + whereString + " ORDER BY customer_id";

    long head;
    int customerId;
    char **record;
    string number;

    QSqlQuery loadQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));

    if(loadQuery.first()) {
        seller = parseSellerFieldList(loadQuery);
    }
    return seller;
}

Seller SellerDAO::nextSeller(Seller current, Index index, bool forward)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    stringstream queryStr;

    string op("<");
    string dir("DESC");

    if(forward)
    {
        op = ">";
        dir = "ASC";
    }

    string dateStr = SaleManager().currentSaleDateSQLString();

    queryStr << "SELECT " << fieldList << " "
             << "FROM seller "
             << "WHERE "
             << "date = '" << dateStr << "' "
             << "AND ";

    QSqlQuery nextSellerQuery;
    QString queryString;
    switch(index)
    {
    case iName:
        queryStr << "((name =:safeName "
                 << "AND "
                 << "number " << op << " '" << ":safeNumber" << "') "
                 << "OR "
                 << "name " << op << " '" << ":safeName1" << "') "
                 << "ORDER BY name " << dir << ", number " << dir << " ";

        queryString = QString::fromStdString(queryStr.str());
        DatabaseManager::defaultManager.prepareQuery(nextSellerQuery,queryString);
        nextSellerQuery.bindValue(":safeName"   , QString::fromStdString(current.getName().getLast()));
        nextSellerQuery.bindValue(":safeName1"  , QString::fromStdString(current.getName().getLast()));
        nextSellerQuery.bindValue(":safeNumber" , QString::fromStdString(current.getNumber()));
        break;

    case iCompany:
        queryStr << "((mortgage = '" << ":safeName" << "' "
                 << "AND "
                 << "number " << op << " '" << ":safeNumber" << "') "
                 << "OR "
                 << "mortgage " << op <<  " '" << ":safeName1" << "') "
                 << "ORDER BY mortgage " << dir << ", number " << dir << " ";

        queryString = QString::fromStdString(queryStr.str());
        DatabaseManager::defaultManager.prepareQuery(nextSellerQuery,queryString);
        nextSellerQuery.bindValue(":safeName"   , QString::fromStdString(current.getMortgage()));
        nextSellerQuery.bindValue(":safeName1"  , QString::fromStdString(current.getMortgage()));
        nextSellerQuery.bindValue(":safeNumber" , QString::fromStdString(current.getNumber()));

        break;
    }


    queryStr << "LIMIT 1";

    DatabaseManager::defaultManager.executeQuery(nextSellerQuery);

    if(nextSellerQuery.first()) {
        current = parseSellerFieldList(nextSellerQuery);
    }

    return current;
}

const string SellerDAO::fieldList("id, head, customer_id, number,name,address1,address2,city,state,zip,mortgage,comment, beef_council, mad_cow");


Seller SellerDAO::parseSellerFieldList(QSqlQuery & sellerQuery)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    /*
("id, head, customer_id, number,name,address1,address2,city,
state,zip,mortgage,comment, beef_council, mad_cow");
*/

    Seller seller;
    long  _head      = DatabaseManager::valueAs<long>(sellerQuery,"head");
    long _customerId = DatabaseManager::valueAs<long>(sellerQuery,"customer_id");
    string _number   = DatabaseManager::valueAs<QString>(sellerQuery,"number").toStdString();
    string _name     = DatabaseManager::valueAs<QString>(sellerQuery,"name").toStdString();

    string _address1 = DatabaseManager::valueAs<QString>(sellerQuery,"address1").toStdString();
    string _address2 = DatabaseManager::valueAs<QString>(sellerQuery,"address2").toStdString();
    string _city     = DatabaseManager::valueAs<QString>(sellerQuery,"city").toStdString();
    string _state    = DatabaseManager::valueAs<QString>(sellerQuery,"state").toStdString();
    string _zip      = DatabaseManager::valueAs<QString>(sellerQuery,"zip").toStdString();

    string _mortgage = DatabaseManager::valueAs<QString>(sellerQuery,"mortgage").toStdString();
    string _comment  = DatabaseManager::valueAs<QString>(sellerQuery,"comment").toStdString();

    bool _beef_council = DatabaseManager::valueAs<bool>(sellerQuery,"beef_council");
    bool _mad_cow      = DatabaseManager::valueAs<bool>(sellerQuery,"mad_cow");

    Address _address(_address1, _address2, _city, _state, _zip);

    seller.setNumber(_number);
    seller.setHead(_head);
    seller.setName(Name(_name));
    seller.setId(_customerId);
    seller.setAddress(_address);
    seller.setMortgage(_mortgage);
    seller.setComment(_comment);
    seller.setBeefCouncil(_beef_council);
    seller.setMadCowCertified(_mad_cow);

    return seller;
}

Seller SellerDAO::findSeller(string filter, Index index)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    stringstream conditionStr;

    conditionStr << "SELECT " << fieldList << " FROM seller "
                 << "WHERE date='" << SaleManager().currentSaleDateSQLString() << "' "
                 << "AND ";

    switch(index)
    {
    case iName:
        conditionStr << "name LIKE " << ":safeFilter" << " ORDER BY name ";
    default:
        break;

    case iCompany:
        conditionStr << "mortgage LIKE " << ":safeFilter" << " ORDER BY mortgage ";
        break;
    }

    conditionStr << "LIMIT 1 ";
    QSqlQuery findSellerQuery;
    QString queryString = QString::fromStdString(conditionStr.str());
    DatabaseManager::defaultManager.prepareQuery(findSellerQuery,queryString);
    findSellerQuery.bindValue(":safeFilter",QString::fromStdString(filter)+"%");

    DatabaseManager::defaultManager.executeQuery(findSellerQuery);

    Seller result;

    if(findSellerQuery.first())  {
        result = parseSellerFieldList(findSellerQuery);
    }
    return result;
}

vector<Seller> SellerDAO::getCustomerList()
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    string qryString = "SELECT id, head, customer_id, number, name, address1,"
            "address2,city,state,zip,mortgage,comment, beef_council, mad_cow "
            "FROM seller WHERE date='" + SaleManager().currentSaleDateSQLString() + "'";
    vector<Seller> sellerList;

    QSqlQuery sellerQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));

    while (sellerQuery.next()) {
        Seller seller;

        long  _head      = DatabaseManager::valueAs<long>(sellerQuery,"head");
        long _customerId = DatabaseManager::valueAs<long>(sellerQuery,"customer_id");
        string _number   = DatabaseManager::valueAs<QString>(sellerQuery,"number").toStdString();
        string _name     = DatabaseManager::valueAs<QString>(sellerQuery,"name").toStdString();

        string _address1 = DatabaseManager::valueAs<QString>(sellerQuery,"address1").toStdString();
        string _address2 = DatabaseManager::valueAs<QString>(sellerQuery,"address2").toStdString();
        string _city     = DatabaseManager::valueAs<QString>(sellerQuery,"city").toStdString();
        string _state    = DatabaseManager::valueAs<QString>(sellerQuery,"state").toStdString();
        string _zip      = DatabaseManager::valueAs<QString>(sellerQuery,"zip").toStdString();

        string _mortgage = DatabaseManager::valueAs<QString>(sellerQuery,"mortgage").toStdString();
        string _comment  = DatabaseManager::valueAs<QString>(sellerQuery,"comment").toStdString();

        bool _beef_council = DatabaseManager::valueAs<bool>(sellerQuery,"beef_council");
        bool _mad_cow      = DatabaseManager::valueAs<bool>(sellerQuery,"mad_cow");

        Address _address(_address1, _address2, _city, _state, _zip);

        seller.setNumber(_number);
        seller.setHead(_head);
        seller.setName(Name(_name));
        seller.setId(_customerId);
        seller.setAddress(_address);
        seller.setMortgage(_mortgage);
        seller.setComment(_comment);
        seller.setBeefCouncil(_beef_council);
        seller.setMadCowCertified(_mad_cow);

        sellerList.push_back(seller);
    }
    return sellerList;
}


bool SellerDAO::saveCustomer(Seller& seller)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    // a seller must have a number to be saved

    if(seller.getNumber() == "")
    {
        return false;
    }

    QString qryString;
    bool exists = sellerExists(seller);
    long customer_id = seller.getId();

    if(customer_id != 0 && !CustomerDAO::nameExists(seller.getName().getLast()))
    {
        customer_id = 0;
        seller.setId(0);
    }

    if(customer_id == 0)
    {
        customer_id = CustomerDAO::saveCustomer((Customer)seller, Customer::Seller);
        seller.setId(customer_id);
    }

    if (!exists) {
        qryString = QString("INSERT INTO seller ( head , customer_id, date, number, name, address1, address2, city, "
                            "state, zip, mortgage, comment, beef_council, mad_cow ) "
                            "VALUES ( :head_ , :customer_id_ , :date_ , :number_ , :name_ , :address1_ , :address2_ , :city_ , "
                            ":state_ , :zip_ , :mortgage_ , :comment_ , :beef_council_ , :mad_cow_ )");
    }else {
        qryString = QString("UPDATE seller SET head=:head_ , customer_id=:customer_id_ , date=:date_ , number=:number_ , name=:name_ , "
                            "address1=:address1_ , address2=:address2_ , city=:city_ , state=:state_ , zip=:zip_ , mortgage=:mortgage_ , comment=:comment_, "
                            "beef_council=:beef_council_ , mad_cow=:mad_cow_ ");
    }

    QSqlQuery saveCustomerQuery;
    qryString += (!exists ? "" : QString(" WHERE number='%1' AND date='%2'").arg(QString::fromStdString(seller.getNumber())).
                            arg(QString::fromStdString(SaleManager().currentSaleDateSQLString())));

    DatabaseManager::defaultManager.prepareQuery(saveCustomerQuery,qryString);

    saveCustomerQuery.bindValue(":head_"         ,QVariant::fromValue<long>(seller.getHead()));
    saveCustomerQuery.bindValue(":customer_id_"  ,QVariant::fromValue<long>(customer_id));
    saveCustomerQuery.bindValue(":date_"         ,QVariant::fromValue<QString>(QString::fromStdString(SaleManager().currentSaleDateSQLString())));
    saveCustomerQuery.bindValue(":number_"       ,QVariant::fromValue<QString>(QString::fromStdString(seller.getNumber())));
    saveCustomerQuery.bindValue(":name_"         ,QVariant::fromValue<QString>(QString::fromStdString(seller.getName().getLast())));
    saveCustomerQuery.bindValue(":address1_"     ,QVariant::fromValue<QString>(QString::fromStdString(seller.getAddress().getAddress1())));
    saveCustomerQuery.bindValue(":address2_"     ,QVariant::fromValue<QString>(QString::fromStdString(seller.getAddress().getAddress2())));
    saveCustomerQuery.bindValue(":city_"         ,QVariant::fromValue<QString>(QString::fromStdString(seller.getAddress().getCity())));
    saveCustomerQuery.bindValue(":state_"        ,QVariant::fromValue<QString>(QString::fromStdString(seller.getAddress().getState())));
    saveCustomerQuery.bindValue(":zip_"          ,QVariant::fromValue<QString>(QString::fromStdString(seller.getAddress().getZip())));
    saveCustomerQuery.bindValue(":mortgage_"     ,QVariant::fromValue<QString>(QString::fromStdString(seller.getMortgage())));
    saveCustomerQuery.bindValue(":comment_"      ,QVariant::fromValue<QString>(QString::fromStdString(seller.getComment())));
    saveCustomerQuery.bindValue(":beef_council_" ,QVariant::fromValue<int>(seller.isBeefCouncil()? 1:0) );
    saveCustomerQuery.bindValue(":mad_cow_"      ,QVariant::fromValue<int>(seller.isMadCowCertified() ? 1:0) );


    DatabaseManager::defaultManager.executeQuery(saveCustomerQuery);
    if(saveCustomerQuery.numRowsAffected() < 0) {
        cerr << "error saving celler" << endl;
        return false;
    }
    return true;
}


bool SellerDAO::sellerExists(Seller seller)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    string qryString = "SELECT number FROM seller WHERE number='" + seller.getNumber() + "' AND date='" + SaleManager().currentSaleDateSQLString() + "'";;
    QSqlQuery sellerQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
    return (sellerQuery.first());
}


void SellerDAO::deleteSeller(Seller seller)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    string qryString = "DELETE FROM seller WHERE number='" + seller.getNumber() + "' AND date='" + SaleManager().currentSaleDateSQLString() + "'";;
    DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
}


Buyer BuyerDAO::loadFromNumber(string number)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    Buyer buyer;

    char buf[20];
    string qryString = "SELECT id, customer_id,name,address1, address2,city,state,zip,company,comment "
            "FROM buyer WHERE date='" + SaleManager().currentSaleDateSQLString() +
            "' AND number='" + number + "'";

    QSqlQuery numberQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));

    if(numberQuery.first()){

        int _customerId     = DatabaseManager::valueAs<int>(numberQuery,"customer_id");
        string _name        = DatabaseManager::valueAs<QString>(numberQuery,"name").toStdString();
        string _address1    = DatabaseManager::valueAs<QString>(numberQuery,"address1").toStdString();
        string _address2    = DatabaseManager::valueAs<QString>(numberQuery,"address2").toStdString();
        string _city        = DatabaseManager::valueAs<QString>(numberQuery,"city").toStdString();
        string _state       = DatabaseManager::valueAs<QString>(numberQuery,"state").toStdString();
        string _zip         = DatabaseManager::valueAs<QString>(numberQuery,"zip").toStdString();
        string _company     = DatabaseManager::valueAs<QString>(numberQuery,"company").toStdString();
        string _comment     = DatabaseManager::valueAs<QString>(numberQuery,"comment").toStdString();


        buyer.setId(_customerId);
        buyer.setName(Name(_name));
        Address address(_address1, _address2, _city, _state, _zip);
        buyer.setAddress(address);
        buyer.setCompany(_company);
        buyer.setComment(_comment);
    }

    if(buyer.getId() == 0 && buyer.getName().getLast().length() < 1) //&& Customer::compareCustomerNumbersLT(buyer.getNumber(), transientBuyer))
    {
        if(number.length() > 0) //number.find_first_of("0123456789") == 0) // perm candidate
        {
            buyer = CustomerDAO::loadFromPermNumber(number);
        }
    }
    buyer.setNumber(number);
    return buyer;
}

// loadFromBuyerByNumber(number) is like loadFromNumber except there
// is no call to load from perm file on failure to find in buyer table.
//
// buyer id == 0 indicates record not found
//
Buyer BuyerDAO::loadFromBuyerByNumber(string number)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    Buyer buyer;
    string qryString = "SELECT id, customer_id,name,address1, address2,city,state,zip,company,comment FROM buyer WHERE date='" + SaleManager().currentSaleDateSQLString() + "' AND number='" + number + "'";

    QSqlQuery numberQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));

    if(numberQuery.first()){
        int _customerId     = DatabaseManager::valueAs<int>(numberQuery,"customer_id");
        string _name        = DatabaseManager::valueAs<QString>(numberQuery,"name").toStdString();
        string _address1    = DatabaseManager::valueAs<QString>(numberQuery,"address1").toStdString();
        string _address2    = DatabaseManager::valueAs<QString>(numberQuery,"address2").toStdString();
        string _city        = DatabaseManager::valueAs<QString>(numberQuery,"city").toStdString();
        string _state       = DatabaseManager::valueAs<QString>(numberQuery,"state").toStdString();
        string _zip         = DatabaseManager::valueAs<QString>(numberQuery,"zip").toStdString();
        string _company     = DatabaseManager::valueAs<QString>(numberQuery,"company").toStdString();
        string _comment     = DatabaseManager::valueAs<QString>(numberQuery,"comment").toStdString();

        buyer.setId(_customerId);
        buyer.setName(Name(_name));
        Address address(_address1, _address2, _city, _state, _zip);
        buyer.setAddress(address);
        buyer.setCompany(_company);
        buyer.setComment(_comment);
    }
    buyer.setNumber(number);
    return buyer;
}


vector<Buyer> BuyerDAO::getCustomerList()
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    string qryString = "SELECT id, customer_id, number, name,address1, address2,city,state,zip,company,comment FROM buyer WHERE date='" + SaleManager().currentSaleDateSQLString() + "'";
    vector<Buyer> buyerList;
    //  DatabaseManager tempManager;
    QSqlQuery buyerListQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));

    while (buyerListQuery.next()) {
        Buyer buyer;
        int _customerId     = DatabaseManager::valueAs<int>(buyerListQuery,"customer_id");
        string _number      = DatabaseManager::valueAs<QString>(buyerListQuery,"number").toStdString();
        string _name        = DatabaseManager::valueAs<QString>(buyerListQuery,"name").toStdString();
        string _address1    = DatabaseManager::valueAs<QString>(buyerListQuery,"address1").toStdString();
        string _address2    = DatabaseManager::valueAs<QString>(buyerListQuery,"address2").toStdString();
        string _city        = DatabaseManager::valueAs<QString>(buyerListQuery,"city").toStdString();
        string _state       = DatabaseManager::valueAs<QString>(buyerListQuery,"state").toStdString();
        string _zip         = DatabaseManager::valueAs<QString>(buyerListQuery,"zip").toStdString();
        string _company     = DatabaseManager::valueAs<QString>(buyerListQuery,"company").toStdString();
        string _comment     = DatabaseManager::valueAs<QString>(buyerListQuery,"comment").toStdString();

        buyer.setId(_customerId);
        buyer.setNumber(_number);
        buyer.setName(Name(_name));
        Address address(_address1, _address2, _city, _state, _zip);
        buyer.setAddress(address);
        buyer.setCompany(_company);
        buyer.setComment(_comment);

        buyerList.push_back(buyer);
    }

    return buyerList;
}


bool BuyerDAO::saveCustomer(Buyer buyer, bool savePermIfAppropriate)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    // a buyer must have a number to be saved
    if(buyer.getNumber() == "")
    {
        return false;
    }

    QString qryString;
    bool exists = buyerExists(buyer);
    int customer_id = buyer.getId();

    if(customer_id != 0 && !CustomerDAO::nameExists(buyer.getName().getLast()))
    {
        customer_id = 0;
        buyer.setId(0);
    }

    if(customer_id == 0 && savePermIfAppropriate && buyer.getName().getLast() != "") {
        customer_id = CustomerDAO::saveCustomer((Customer)buyer, Customer::Buyer, true);
        buyer.setId(customer_id);
    }

    switch(exists)
    {
    case false:
        qryString = QString("INSERT INTO buyer ( customer_id, date, number, name, address1, address2, city, state, zip, company, comment) "
                            "VALUES ( :customer_id, :date, :number, :name, :address1, :address2, :city, :state, :zip, :company, :comment)");
        break;

    default:
        qryString = QString("UPDATE buyer SET customer_id=:customer_id, date=:date, number=:number, name=:name, "
                            "address1=:address1, address2=:address2, city=:city, state=:state, zip=:zip, company=:company, comment=:comment");
        break;
    }

    QSqlQuery saveCustomerQuery;
    qryString += (!exists ? "" : QString(" WHERE number=:number1 AND date=:date1"));

    DatabaseManager::defaultManager.prepareQuery(saveCustomerQuery,qryString);

    if (exists) {
        saveCustomerQuery.bindValue(":number1" ,QString::fromStdString(buyer.getNumber()));
        saveCustomerQuery.bindValue(":date1"   ,QString::fromStdString(SaleManager().currentSaleDateSQLString()));
    }
    saveCustomerQuery.bindValue(":customer_id"     ,customer_id);
    saveCustomerQuery.bindValue(":date"             ,QString::fromStdString(SaleManager().currentSaleDateSQLString()));
    saveCustomerQuery.bindValue(":number"           ,QString::fromStdString(buyer.getNumber()));
    saveCustomerQuery.bindValue(":name"             ,QString::fromStdString(buyer.getName().getLast()));
    saveCustomerQuery.bindValue(":address1"         ,QString::fromStdString(buyer.getAddress().getAddress1()));
    saveCustomerQuery.bindValue(":address2"         ,QString::fromStdString(buyer.getAddress().getAddress2()));
    saveCustomerQuery.bindValue(":city"             ,QString::fromStdString(buyer.getAddress().getCity()));
    saveCustomerQuery.bindValue(":state"            ,QString::fromStdString(buyer.getAddress().getState()));
    saveCustomerQuery.bindValue(":zip"              ,QString::fromStdString(buyer.getAddress().getZip()));
    saveCustomerQuery.bindValue(":company"          ,QString::fromStdString(buyer.getCompany()));
    saveCustomerQuery.bindValue(":comment"          ,QString::fromStdString(buyer.getComment()));
    DatabaseManager::defaultManager.executeQuery(saveCustomerQuery);

    if(saveCustomerQuery.numRowsAffected() <= 0)
    {
        cerr << "error saving buyer" << endl;
        return false;
    }
    return true;
}


bool BuyerDAO::buyerExists(Buyer buyer)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    string qryString = "SELECT number FROM buyer WHERE number='" + buyer.getNumber() + "' AND date='" + SaleManager().currentSaleDateSQLString() + "'";
//    cout << "buyerExists query: " << qryString << endl;
    QSqlQuery buyerQuery =  DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
    return buyerQuery.first();
}


void BuyerDAO::deleteBuyer(Buyer buyer)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    string qryString = "DELETE FROM buyer WHERE number='" + buyer.getNumber() + "' AND date='" + SaleManager().currentSaleDateSQLString() + "'";;
    DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
}


long SellerDAO::checkedInHead()
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    string qryString = "SELECT sum(head) AS _headSum FROM seller WHERE date=\"" + SaleManager().currentSaleDateSQLString() + "\"";
    QSqlQuery headQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
    long head = 0;

    if(headQuery.first()) {
        head = DatabaseManager::valueAs<long>(headQuery,"_headSum");
    }

    return head;
}

bool CustomerDAO::usedAsDaily(Customer cust)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    QString qryString = QString("SELECT count(*) as _cusCount FROM seller WHERE customer_id=%1 ").arg(cust.getId());

    QSqlQuery custCountQuery = DatabaseManager::defaultManager.query(qryString);

    long count = 0;
    if(custCountQuery.first()) {
        count += DatabaseManager::valueAs<long>(custCountQuery,"_cusCount");
    }

    qryString = QString("SELECT count(*) as _buyCount FROM buyer where customer_id=%1 ").arg(cust.getId());
    QSqlQuery buyerCountQuery = DatabaseManager::defaultManager.query(qryString);

    if(custCountQuery.first()) {
        count += DatabaseManager::valueAs<long>(buyerCountQuery,"_buyCount");
    }
    return count > 0;
}


string SellerDAO::idOfNextAlphabeticSeller(string prevId, bool next)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    string op = "<";
    string dir = "DESC";

    if(next)
    {
        op = ">";
        dir = "ASC";
    }

    string dateStr = SaleManager().currentSaleDateSQLString();

    string queryStr =
            "SELECT number "
            "FROM seller "
            "WHERE "
            "date='" + dateStr + "' "
            "AND "
            "name " + op + " "
            "("
            "SELECT name "
            "from SELLER "
            "where date='" + dateStr + "' "
            "AND "
            "number=:numberId "
            "ORDER BY name " + dir + " "
            "LIMIT 1"
            ") "
            "AND number IN "
            "( "
            "SELECT seller_id "
            "FROM backtags "
            "WHERE "
            "ckin_date='" + dateStr + "' "
            "AND seller_id=seller.number"
            ") "
            "LIMIT 1";
    QSqlQuery nextSellerQuery;

    QString queryString = QString::fromStdString(queryStr);
    DatabaseManager::defaultManager.prepareQuery(nextSellerQuery,queryString);
    nextSellerQuery.bindValue(":numberId"   ,  QString::fromStdString(prevId));
    DatabaseManager::defaultManager.executeQuery(nextSellerQuery);

    if(nextSellerQuery.first()) {
        prevId = DatabaseManager::valueAs<QString>(nextSellerQuery,"number").toStdString();
    }

    return prevId;
}


bool SellerDAO::sellerInDailyFile(string id)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    bool result = false;
    string dateStr = SaleManager().currentSaleDateSQLString();

    string queryStr =
            "SELECT number "
            "FROM seller "
            "WHERE "
            "date='" + dateStr + "' "
            "AND number='" + id +
            "'";

    QSqlQuery sellerQuery = DatabaseManager::defaultManager.query(QString::fromStdString(queryStr));
    result = sellerQuery.first();
    return result;
}
