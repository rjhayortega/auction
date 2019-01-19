#include "tagdao.h"
#include <sstream>
#include "customerdao.h"
#include "dbug.h"

// User of this string have to bind variable value for :ckin_date in caller function.
const QString TAG_LIST_QUERY_STR = QString("SELECT trans_id, tag_num, type, color, "
                                           "flaw, seller_id, b_tag, test_date, breed, sex, old_tag, age, vaccination,"
                                           "brucellosis, months_preg, comment, id, deleted, rfid, tbInjDate "
                                           "FROM backtags WHERE ckin_date=:ckin_date" );


vector<Tag> TagDAO::getTagListByCondition(QSqlQuery &tagListQuery)
{
    vector<Tag> tagList;
    DatabaseManager::defaultManager.executeQuery(tagListQuery);

    while (tagListQuery.next()) {

        long transactionId  = DatabaseManager::valueAs<long>(tagListQuery,"trans_id");
        string _tag         = DatabaseManager::valueAs<QString>(tagListQuery,"tag_num").toStdString();
        int _type           = DatabaseManager::valueAs<int>(tagListQuery,"type");
        int _color          = DatabaseManager::valueAs<int>(tagListQuery,"color");
        int _flaw           = DatabaseManager::valueAs<int>(tagListQuery,"flaw");
        string _seller      = DatabaseManager::valueAs<QString>(tagListQuery,"seller_id").toStdString();
        string _burcelTag   = DatabaseManager::valueAs<QString>(tagListQuery,"b_tag").toStdString();
        string _testDate    = DatabaseManager::valueAs<QString>(tagListQuery,"test_date").toStdString();
        string _breed       = DatabaseManager::valueAs<QString>(tagListQuery,"breed").toStdString();
        string _sex         = DatabaseManager::valueAs<QString>(tagListQuery,"sex").toStdString();
        string _old_tag     = DatabaseManager::valueAs<QString>(tagListQuery,"old_tag").toStdString();
        long _age           = DatabaseManager::valueAs<long>(tagListQuery,"age");
        string _vaccination = DatabaseManager::valueAs<QString>(tagListQuery,"vaccination").toStdString();
        string _brucellosis = DatabaseManager::valueAs<QString>(tagListQuery,"brucellosis").toStdString();
        string _months_preg = DatabaseManager::valueAs<QString>(tagListQuery,"months_preg").toStdString();
        string _comment     = DatabaseManager::valueAs<QString>(tagListQuery,"comment").toStdString();
        long  _id           = DatabaseManager::valueAs<long>(tagListQuery,"id");
        bool  _deleted      = DatabaseManager::valueAs<bool>(tagListQuery,"deleted");
        string  _rfid       = DatabaseManager::valueAs<QString>(tagListQuery,"rfid").toStdString();
        string _tbInjDate   = DatabaseManager::valueAs<QString>(tagListQuery,"tbInjDate").toStdString();

        tagList.push_back(Tag(_tag, _seller, transactionId,
                              codeDao.getAnimalCode(_type,_color, _flaw),_burcelTag, _breed,
                              _sex[0], _age, _vaccination, _brucellosis, _months_preg,
                          Date::fromString(_testDate, "YYYY-mm-dd"),
                          _old_tag, _comment, _id, _deleted,
                          _rfid, Date::fromString(_tbInjDate, "YYYY-mm-dd")));
    }
    return tagList;


}



vector<Tag> TagDAO::getTagListByCondition(string condStr)
{
    vector<Tag> tagList;
    string qryString =
            "SELECT "
            "trans_id, "    // 0
            "tag_num, "     // 1
            "type, "        // 2
            "color, "       // 3
            "flaw, "        // 4
            "seller_id, "   // 5
            "b_tag, "       // 6
            "test_date, "   // 7
            "breed, "       // 8
            "sex, "         // 9
            "old_tag, "     // 10
            "age, "         // 11
            "vaccination, " // 12
            "brucellosis, " // 13
            "months_preg, " // 14
            "comment, "      // 15
            "id, "           // 16
            "deleted, "      // 17
            "rfid, "         // 18 2/1/10
            "tbInjDate "     // 19 2/1/10
            "FROM backtags "
            "WHERE "
            "ckin_date='" + sale.currentSaleDateSQLString() + "' "
            "" + (condStr.length() > 0 ? " AND " : "") + condStr + "";

    QSqlQuery tagListQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));

    while (tagListQuery.next()) {

        long transactionId  = DatabaseManager::valueAs<long>(tagListQuery,"trans_id");
        string _tag         = DatabaseManager::valueAs<QString>(tagListQuery,"tag_num").toStdString();
        int _type           = DatabaseManager::valueAs<int>(tagListQuery,"type");
        int _color          = DatabaseManager::valueAs<int>(tagListQuery,"color");
        int _flaw           = DatabaseManager::valueAs<int>(tagListQuery,"flaw");
        string _seller      = DatabaseManager::valueAs<QString>(tagListQuery,"seller_id").toStdString();
        string _burcelTag   = DatabaseManager::valueAs<QString>(tagListQuery,"b_tag").toStdString();
        string _testDate    = DatabaseManager::valueAs<QString>(tagListQuery,"test_date").toStdString();
        string _breed       = DatabaseManager::valueAs<QString>(tagListQuery,"breed").toStdString();
        string _sex         = DatabaseManager::valueAs<QString>(tagListQuery,"sex").toStdString();
        string _old_tag     = DatabaseManager::valueAs<QString>(tagListQuery,"old_tag").toStdString();
        long _age           = DatabaseManager::valueAs<long>(tagListQuery,"age");
        string _vaccination = DatabaseManager::valueAs<QString>(tagListQuery,"vaccination").toStdString();
        string _brucellosis = DatabaseManager::valueAs<QString>(tagListQuery,"brucellosis").toStdString();
        string _months_preg = DatabaseManager::valueAs<QString>(tagListQuery,"months_preg").toStdString();
        string _comment     = DatabaseManager::valueAs<QString>(tagListQuery,"comment").toStdString();
        long  _id           = DatabaseManager::valueAs<long>(tagListQuery,"id");
        bool  _deleted      = DatabaseManager::valueAs<bool>(tagListQuery,"deleted");
        string  _rfid       = DatabaseManager::valueAs<QString>(tagListQuery,"rfid").toStdString();
        string _tbInjDate   = DatabaseManager::valueAs<QString>(tagListQuery,"tbInjDate").toStdString();

        tagList.push_back(Tag(_tag, _seller, transactionId,
                              codeDao.getAnimalCode(_type,_color, _flaw),_burcelTag, _breed,
                              _sex[0], _age, _vaccination, _brucellosis, _months_preg,
                          Date::fromString(_testDate, "YYYY-mm-dd"),
                          _old_tag, _comment, _id, _deleted,
                          _rfid, Date::fromString(_tbInjDate, "YYYY-mm-dd")));
    }
    return tagList;
}

int TagDAO::tagCount(Seller& seller)
{
    int result = 0;

    stringstream queryStr;
    queryStr << "SELECT COUNT(*) AS _countTag FROM backtags "
             << "WHERE "
             << "ckin_date=:ckin_date" << " AND " << "seller_id=:seller_id";

    QSqlQuery tagCountQuery;
    QString queryString = QString::fromStdString(queryStr.str());
    DatabaseManager::defaultManager.prepareQuery(tagCountQuery,queryString);

    tagCountQuery.bindValue("ckin_date"     ,QString::fromStdString(sale.currentSaleDateSQLString()));
    tagCountQuery.bindValue("seller_id"     ,QString::fromStdString(seller.getNumber()));

    DatabaseManager::defaultManager.executeQuery(tagCountQuery);
    if(tagCountQuery.first()) {
        result = DatabaseManager::valueAs<int>(tagCountQuery,"_countTag");
    }
    return result;
}

void TagDAO::fillTag(Tag& tag)
{
    QSqlQuery tagListQuery;

    QString queryString = TAG_LIST_QUERY_STR + QString(" AND seller_id=:seller_id AND tag_num=:tag_num LIMIT 1");
    DatabaseManager::defaultManager.prepareQuery(tagListQuery,queryString);

    tagListQuery.bindValue(":ckin_date" , QString::fromStdString(sale.currentSaleDateSQLString()));
    tagListQuery.bindValue(":seller_id" , QString::fromStdString(tag.getSellerId()));
    tagListQuery.bindValue(":tag_num"   , QString::fromStdString(tag.getTag()));

    vector<Tag> tagVector = getTagListByCondition(tagListQuery);

    if(tagVector.size() > 0) {
        tag = tagVector[0];
    }
}

Tag TagDAO::findTag(string filter, Index index)
{
    Tag result;

    QSqlQuery findTagQuery;
    QString queryString = TAG_LIST_QUERY_STR + " AND ";
    QString safeFilter = QString::fromStdString(filter);

    switch(index)
    {
    case PlasticTag:
        queryString += "tag_num=:tagFilter";
        break;

    case Owner:
    {
        Seller seller;
        vector<Tag> tagList;

        seller = SellerDAO::findSeller(filter, SellerDAO::iName);
        tagList = sortedTagList(seller);

        if(tagList.size() > 0)
        {
            return tagList.front();
        }
        else
        {
            return result;
        }
    }
        break;

    case MetalTag:
        queryString += "b_tag=:tagFilter ORDER BY tag_num LIMIT 1";
        break;

    case Age:
        queryString += "age=:tagFilter ORDER BY tag_num LIMIT 1";
        break;

    case Breed:
        queryString += "breed=:tagFilter ORDER BY tag_num LIMIT 1";
        break;

    default:
        break;
    }
    DatabaseManager::defaultManager.prepareQuery(findTagQuery,queryString);
    findTagQuery.bindValue(":ckin_date" , QString::fromStdString(sale.currentSaleDateSQLString()));
    findTagQuery.bindValue(":tagFilter" , safeFilter);

    vector<Tag> resultVector = getTagListByCondition(findTagQuery);

    if(resultVector.size() > 0)
    {
        result = resultVector.front();
    }

    return result;
}

vector<Tag> TagDAO::sortedTagList(Seller seller)
{
    QSqlQuery sortedTagQuery;
    QString queryString = TAG_LIST_QUERY_STR + " AND seller_id=:seller_id ORDER BY tag_num";
    DatabaseManager::defaultManager.prepareQuery(sortedTagQuery,queryString);

    sortedTagQuery.bindValue(":ckin_date" , QString::fromStdString(sale.currentSaleDateSQLString()));
    sortedTagQuery.bindValue(":seller_id" , QString::fromStdString(seller.getNumber()));

    return getTagListByCondition(sortedTagQuery);
}

void TagDAO::setShowBrand(bool showBrand)
{
    this->showBrand = showBrand;
}

bool TagDAO::doShowBrand()
{
    return showBrand;
}

vector<Tag> TagDAO::getTagList()
{
    return getTagListByCondition("");
}

string TagDAO::getIndexField(Index index)
{
    string indexStr = "id";

    switch(index)
    {
    case PlasticTag:
        indexStr = "tag_num";
        break;

    case Owner:
        indexStr = "id";
        break;

    case MetalTag:
        indexStr = "b_tag";
        break;

    case Age:
        indexStr = "age";
        break;

    case Breed:
        indexStr = "breed";
        break;

    case Record:
    default:
        indexStr = "id";
        break;
    }
    return indexStr;
}

vector<Tag> TagDAO::getTagVector(Index index, bool showDeleted, bool showNonDeleted, string startField, string endField)
{
    stringstream condStr;
    condStr << "id=id ";


    if((!showDeleted && showNonDeleted) || (showDeleted && !showNonDeleted))
    {
        if(showDeleted)
        {
            condStr << "AND deleted = 1 ";
        }

        if(showNonDeleted)
        {
            condStr << "AND deleted = 0 ";
        }
    }

    string indexStr = getIndexField(index);

    if(endField != "") {
        condStr << "AND " << indexStr << " <= :endField ";
    }

    if(startField != "") {
        condStr << "AND :startField' <= " << indexStr << " ";
    }
    condStr << "ORDER BY " << indexStr << " ";
    QString queryString = TAG_LIST_QUERY_STR+" AND "+ QString::fromStdString(condStr.str());
    QSqlQuery tagListQuery;

    DatabaseManager::defaultManager.prepareQuery(tagListQuery,queryString);
    tagListQuery.bindValue(":ckin_date" , QString::fromStdString(sale.currentSaleDateSQLString()));

    if(endField != "") {
        tagListQuery.bindValue(":endField" , QString::fromStdString(endField));
    }
    if(startField != "") {
        tagListQuery.bindValue(":startField" , QString::fromStdString(startField));
    }

    return getTagListByCondition(tagListQuery);
}

vector<Tag> TagDAO::getTagList(Seller seller)
{
    string condStr = "seller_id='" + seller.getNumber() + "'";
    return getTagListByCondition(condStr);
}

vector<Tag> TagDAO::getTagList(Transaction& trans)
{
    char transNo[20];
    sprintf(transNo, "%ld", trans.getId());
    string condStr = "trans_id=" + string(transNo) + "";
    return getTagListByCondition(condStr);
}

void TagDAO::saveTag(Tag& tag)
{
    char transId[20];
    char type[4], color[4], flaw[4];
    char ageStr[4];
    char idBuf[20];
    char deletedBuf[20];


    sprintf(ageStr, "%d", tag.getAge());
    AnimalCode code = tag.getAnimalCode();
    sprintf(transId, "%ld", tag.getTransactionId());
    sprintf(type, "%d", code.getType());
    sprintf(color, "%d", code.getColor());
    sprintf(flaw, "%d", code.getFlaw());
    sprintf(idBuf, "%ld", tag.getId());
    sprintf(deletedBuf, "%d", int(tag.isDeleted()));

    deleteTag(tag);
    QSqlQuery saveTagQuery;
    QString qryString = QString("INSERT INTO backtags SET "
                                "tag_num=:tag_num, trans_id=:trans_id, seller_id=:seller_id, type=:type, "
                                "color=:color, flaw=:flaw, ckin_date=:ckin_date, b_tag=:b_tag, breed=:breed, "
                                "sex=:sex, age=:age, vaccination=:vaccination, brucellosis=:brucellosis, "
                                "months_preg=:months_preg, test_date=:test_date, old_tag=:old_tag, "
                                "comment=:comment, id=:id, deleted=:deleted, rfid=:rfid, tbinjdate=:tbinjdate");

    DatabaseManager::defaultManager.prepareQuery(saveTagQuery,qryString);

    saveTagQuery.bindValue(":tag_num"       ,QString::fromStdString(tag.getTag()));
    saveTagQuery.bindValue(":trans_id"      ,QVariant::fromValue<long>(tag.getTransactionId()));
    saveTagQuery.bindValue(":seller_id"     ,QString::fromStdString(tag.getSellerId()));
    saveTagQuery.bindValue(":type"          ,QVariant::fromValue<long>(code.getType()));
    saveTagQuery.bindValue(":color"         ,code.getColor());
    saveTagQuery.bindValue(":flaw"          ,code.getFlaw());
    saveTagQuery.bindValue(":ckin_date"     ,QString::fromStdString(sale.currentSaleDateSQLString()));
    saveTagQuery.bindValue(":b_tag"         ,QString::fromStdString(tag.getBurcellosisTag()));
    saveTagQuery.bindValue(":breed"         ,QString::fromStdString(tag.getBreed()));
    saveTagQuery.bindValue(":sex"           ,QChar(tag.getSex()));
    saveTagQuery.bindValue(":age"           ,tag.getAge());
    saveTagQuery.bindValue(":vaccination"   ,QString::fromStdString(tag.getVaccination()));
    saveTagQuery.bindValue(":brucellosis"   ,QString::fromStdString(tag.getBrucellosis()));
    saveTagQuery.bindValue(":months_preg"   ,QString::fromStdString(tag.getMonthsPreg()));
    saveTagQuery.bindValue(":test_date"     ,QString::fromStdString(tag.getTestDate().toString("YYYY-mm-dd")));
    saveTagQuery.bindValue(":old_tag"       ,QString::fromStdString(tag.getOldTag()));
    saveTagQuery.bindValue(":comment"       ,QString::fromStdString(tag.getComment()));
    saveTagQuery.bindValue(":id"            ,QVariant::fromValue<long>(tag.getId()));
    saveTagQuery.bindValue(":deleted"       ,QVariant::fromValue<bool>(tag.isDeleted()));
    saveTagQuery.bindValue(":rfid"          ,QString::fromStdString(tag.getRfid()));
    saveTagQuery.bindValue(":tbinjdate"     ,QString::fromStdString(tag.getTbInjDate().toString("YYYY-mm-dd")));

    DatabaseManager::defaultManager.executeQuery(saveTagQuery);
    if(tag.getId() == 0)
    {
        tag.setId(DatabaseManager::defaultManager.get_last_id(saveTagQuery));
    }
}

void TagDAO::deleteTag(Tag tag)
{
    //  char transIdStr[20];
    //  sprintf(transIdStr, "%ld", tag.getTransactionId());

    //  bool comment = false;

    //  comment = (tag.getTag().length() > 0 && tag.getTag()[0] == '/');

    //  string qryString =
    //    "DELETE FROM backtags WHERE tag_num='" + tag.getTag() + "' "
    //    "AND ckin_date='" + sale.currentSaleDateSQLString() + "' ";


    //  if(comment)
    //  {
    //    qryString +=  "AND trans_id=" + string(transIdStr) + "";
    //  }

    char idStr[20];
    sprintf(idStr, "%ld", tag.getId());
    string qryString =
            "DELETE FROM backtags where id=" + string(idStr) + " ";
    DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
}

bool TagDAO::conflict(Tag tag, string& sellerId)
{

    if(tag.getTag().length() > 0 && tag.getTag()[0] == '/')
    {
        return false;
    }

    sellerId = "";
    string qryString = "SELECT tag_num, seller_id FROM backtags WHERE tag_num='" + tag.getTag() + "' AND seller_id!='" + tag.getSellerId() + "' AND ckin_date = '" + sale.currentSaleDateSQLString() + "'";
    QSqlQuery conflictQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
    bool result = conflictQuery.first();
    if(result) {
        sellerId = DatabaseManager::valueAs<QString>(conflictQuery,"seller_id").toStdString();
    }

    return result;
}

bool TagDAO::conflict(Tag tag, long& transactionNo)
{
    if(tag.getTag().length() > 0 && tag.getTag()[0] == '/')
    {
        return false;
    }

    string qryString = "SELECT tag_num, trans_id FROM backtags WHERE tag_num='" + tag.getTag() + "' AND ckin_date = '" + sale.currentSaleDateSQLString() + "'";

    QSqlQuery conflictQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
    bool result = conflictQuery.first();
    if(result) {
        transactionNo = DatabaseManager::valueAs<long>(conflictQuery,"trans_id");
    }
    return result;
}


void TagDAO::updateTransactionTagList(long transNo, string sellerNo)
{
    char trans[20];
    sprintf(trans, "%ld", transNo);
    string qryString = "UPDATE backtags SET seller_id='" + sellerNo + "' WHERE trans_id=" + string(trans) + " AND ckin_date='" + sale.currentSaleDateSQLString() + "'";
    DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
}

void TagDAO::clearTransactionTags(Transaction transaction)
{
    if(transaction.getId() != 0)
    {
        char transIdStr[20];
        sprintf(transIdStr, "%ld", transaction.getId());
        string qryString =
                "DELETE FROM backtags "
                "WHERE trans_id=" + string(transIdStr) + " "
                "AND ckin_date='" + sale.currentSaleDateSQLString() + "' ";

        DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
    }
}

Tag TagDAO::getNextTag(Tag tag, Index index)
{
    return getRelatedTag(tag, index, true);
}

Tag TagDAO::getRelatedTag(Tag tag, Index index, bool next)
{
    string op;
    string dir;

    Tag temp;

    op = "<";
    dir = "DESC";

    if(next)
    {
        op = ">";
        dir = "ASC";
    }
    stringstream queryStr;

    QSqlQuery tagListQuery;
    QString  queryString;
    switch(index)
    {
    case Owner:
        if(next) {
            temp = getNextSellerTag(tag);
        }
        else {
            temp = getPreviousSellerTag(tag);
        }

        if(temp.getTag() == "") {
            vector<Tag> tagList;
            Seller current;

            do {
                current = SellerDAO::loadFromNumber(tag.getSellerId());
                current = SellerDAO::nextSeller(current, SellerDAO::iName, next);
                tag.setSellerId(current.getNumber());
                tagList = sortedTagList(current);
            } while(current.getId() != 0 && tagList.size() == 0);

            if(tagList.size() > 0) {
                if(next) {
                    tag = tagList.front();
                }
                else {
                    tag = tagList.back();
                }
            }
        }
        else {
            tag = temp;
        }
        return tag;

        break;
    case PlasticTag:
        queryStr
                << "tag_num " << op <<  " :safeTag "
                   "AND "
                   "LEFT(1, tag_num) != '/' "
                   "ORDER BY tag_num " << dir << " ";

        queryString = TAG_LIST_QUERY_STR + " AND " + QString::fromStdString(queryStr.str())+ " LIMIT 1";
        DatabaseManager::defaultManager.prepareQuery(tagListQuery,queryString);
        tagListQuery.bindValue(":safeTag",QString::fromStdString(tag.getTag()));
        break;

    case MetalTag:
        queryStr
                << "("
                <<  "(b_tag = :safeBTag "
                 << "AND tag_num " << op << " :safeTag) "
                 << "OR "
                 << "b_tag " << op << " :safeBTag1 "
                 << ")"
                 << "ORDER BY b_tag " << dir << ", tag_num " << dir << " ";
        queryString = TAG_LIST_QUERY_STR + " AND " + QString::fromStdString(queryStr.str())+ " LIMIT 1";
        DatabaseManager::defaultManager.prepareQuery(tagListQuery,queryString);
        tagListQuery.bindValue(":safeTag"   ,QString::fromStdString(tag.getTag()));
        tagListQuery.bindValue(":safeBTag"  ,QString::fromStdString(tag.getBurcellosisTag()));
        tagListQuery.bindValue(":safeBTag1" ,QString::fromStdString(tag.getBurcellosisTag()));
        break;

    case Age:
        queryStr
                << "("
                << "("
                << "age = " << tag.getAge() << " "
                << "AND "
                << "tag_num " << op <<  " :safeTag "
                << ") "
                << "OR "
                << "age " << op <<  " " << tag.getAge() << " "
                << ") "
                << "ORDER BY age " << dir << ", tag_num " << dir << " ";

        queryString = TAG_LIST_QUERY_STR + " AND " + QString::fromStdString(queryStr.str())+ " LIMIT 1";
        DatabaseManager::defaultManager.prepareQuery(tagListQuery,queryString);
        tagListQuery.bindValue(":safeTag"   ,QString::fromStdString(tag.getTag()));
        break;

    case Breed:
        queryStr
                << "("
                << "("
                << "breed=:safeBreed "
                << "AND "
                << "tag_num " << op << " :safeTag "
                << ")"
                << "OR "
                << "breed " << op << " :safeBreed1 "
                << ") "
                << "ORDER BY breed " << dir << ", tag_num " << dir << " ";

        queryString = TAG_LIST_QUERY_STR + " AND " + QString::fromStdString(queryStr.str()) + " LIMIT 1";
        DatabaseManager::defaultManager.prepareQuery(tagListQuery,queryString);
        tagListQuery.bindValue(":safeTag"       ,QString::fromStdString(tag.getTag()));
        tagListQuery.bindValue(":safeBreed"     ,QString::fromStdString(tag.getBreed()));
        tagListQuery.bindValue(":safeBreed1"    ,QString::fromStdString(tag.getBreed()));
        break;

    default:
        return tag;
        break;
    }

    tagListQuery.bindValue(":ckin_date" ,QString::fromStdString(sale.currentSaleDateSQLString()));

    vector<Tag> resultVector = getTagListByCondition(tagListQuery);

    if(resultVector.size() < 1)
    {
        return Tag();
    }

    return resultVector[0];
}

Tag TagDAO::maxSellerTag(Seller seller)
{
    stringstream queryStr;
    QSqlQuery maxTagQuery;

    queryStr << "SELECT MAX(tag_num) AS _maxTagNum "
             << "FROM backtags "
             << "WHERE "
             << "ckin_date='" << sale.currentSaleDateSQLString() << "' "
             << "AND "
             << "seller_id=:seller_id";

    QString queryString = QString::fromStdString(queryStr.str());
    DatabaseManager::defaultManager.prepareQuery(maxTagQuery,queryString);
    maxTagQuery.bindValue(":seller_id"  , QString::fromStdString(seller.getNumber()));

    Tag result;
    DatabaseManager::defaultManager.executeQuery(maxTagQuery);

    if(maxTagQuery.first()) {
        string _maxTag = DatabaseManager::valueAs<QString>(maxTagQuery,"_maxTagNum").toStdString();
        queryStr.str("");
        queryStr.flush();
        queryStr << "tag_num='" << _maxTag << "' ";
        vector<Tag> resultVector = getTagListByCondition(queryStr.str());

        if(resultVector.size() > 0)
        {
            result  = resultVector[0];
        }
    }
    return result;
}

Tag TagDAO::getNextSellerTag(Tag tag)
{
    QSqlQuery tagListQuery;
    QString queryString = TAG_LIST_QUERY_STR +
            QString(" AND seller_id =:seller_id AND tag_num > :tag_num "
                    " AND LEFT(1, tag_num) != '/' ORDER BY tag_num LIMIT 1 ");

    DatabaseManager::defaultManager.prepareQuery(tagListQuery,queryString);
    tagListQuery.bindValue(":ckin_date" ,QString::fromStdString(sale.currentSaleDateSQLString()));
    tagListQuery.bindValue(":seller_id" ,QString::fromStdString(tag.getSellerId()));
    tagListQuery.bindValue(":tag_num"   ,QString::fromStdString(tag.getTag()));

    vector<Tag> resultVector = getTagListByCondition(tagListQuery);

    if(resultVector.size() < 1)
    {
        return Tag();
    }

    return resultVector[0];
}


Tag TagDAO::getPreviousTag(Tag tag, Index index)
{
    return getRelatedTag(tag, index, false);
}

Tag TagDAO::getPreviousSellerTag(Tag tag)
{
    QSqlQuery tagListQuery;
    QString queryString = TAG_LIST_QUERY_STR +
            QString(" AND seller_id=:seller_id AND "
                    "tag_num < :tag_num AND LEFT(1, tag_num) != '/' "
                    "ORDER BY tag_num DESC LIMIT 1 ");

    DatabaseManager::defaultManager.prepareQuery(tagListQuery,queryString);
    tagListQuery.bindValue(":ckin_date" ,QString::fromStdString(sale.currentSaleDateSQLString()));
    tagListQuery.bindValue(":seller_id" ,QString::fromStdString(tag.getSellerId()));
    tagListQuery.bindValue(":tag_num"   ,QString::fromStdString(tag.getTag()));

    vector<Tag> resultVector = getTagListByCondition(tagListQuery);
    if(resultVector.size() < 1)
    {
        return Tag();
    }
    return resultVector[0];
}


vector<Tag> TagDAO::getTagList(Seller seller, Buyer buyer)
{
    QSqlQuery tagListQuery;
    QString queryString = TAG_LIST_QUERY_STR + QString(" AND seller_id=:seller_id AND "
                                                       "trans_id IN (SELECT trans_id FROM trans WHERE date=:date"
                                                       " AND buyerID=:buyerID ");
    DatabaseManager::defaultManager.prepareQuery(tagListQuery,queryString);
    tagListQuery.bindValue(":ckin_date" ,QString::fromStdString(sale.currentSaleDateSQLString()));
    tagListQuery.bindValue(":seller_id" ,QString::fromStdString(seller.getNumber()));
    tagListQuery.bindValue(":date"      ,QString::fromStdString(sale.currentSaleDateSQLString()));
    tagListQuery.bindValue(":buyerID"   ,QString::fromStdString(buyer.getNumber()));

    return getTagListByCondition(tagListQuery);
}

bool TagDAO::brucellosisTagConflict(Tag tag, Date& date, string& sellerNum)
{
    bool result = false;
    QString queryString = QString("SELECT seller_id, ckin_date FROM backtags "
                                  "WHERE b_tag=:b_tag AND id !=:tagId LIMIT 1 ");

    QSqlQuery tagConflictQuery;
    DatabaseManager::defaultManager.prepareQuery(tagConflictQuery,queryString);

    tagConflictQuery.bindValue(":b_tag"     , QString::fromStdString(tag.getBurcellosisTag()));
    tagConflictQuery.bindValue(":tagId"     , QVariant::fromValue<long>(tag.getId()));

    DatabaseManager::defaultManager.executeQuery(tagConflictQuery);

    if(tagConflictQuery.first()) {
        string _date = DatabaseManager::valueAs<QString>(tagConflictQuery,"ckin_date").toStdString();
        result = true;
        sellerNum = DatabaseManager::valueAs<QString>(tagConflictQuery,"seller_id").toStdString();;
        date = Date::fromString(_date, "YYYY-mm-dd");

    }

    return result;
}

vector<string> TagDAO::getIndexRange(Index index)
{
    vector<string> result;
    stringstream queryStr;

    string indexField = getIndexField(index);

    queryStr << "SELECT DISTINCT(" << indexField << ") AS _index "
             << "FROM backtags "
             << "WHERE "
             << "ckin_date='" << sale.currentSaleDateSQLString() << "' "
             << "ORDER BY " << indexField << " ";


    QSqlQuery indexRangeQuery = DatabaseManager::defaultManager.query(QString::fromStdString(queryStr.str()));

    while (indexRangeQuery.next()) {
        string _index = DatabaseManager::valueAs<QString>(indexRangeQuery,"_index").toStdString();
        result.push_back(_index);
    }
    return result;
}

bool TagDAO::existsRfidForSale(Tag tag, string rfidToMatch)
{
    bool result = false;

    stringstream queryStr;
    queryStr << "SELECT count(*) AS _rfCount "
             << "FROM backtags "
             << "WHERE "
             << "rfid='" << rfidToMatch << "' "
             << "AND ckin_date='" << sale.currentSaleDateSQLString() << "' "
             << "AND id != " << tag.getId();



    QSqlQuery rfidQuery = DatabaseManager::defaultManager.query(QString::fromStdString(queryStr.str()));

    if(rfidQuery.first()) {
        int _count = DatabaseManager::valueAs<int>(rfidQuery,"_rfCount");
        result = (_count > 0);
    }
    return result;
}
