
#include "branddao.h"

/*
*  3 Aug 09 rhw	Fix query in getInvoiceBrandList(string buyerNum) to broaden
*		match to all combinations using preceding / or no-/.
*/

BrandDAO::BrandDAO()
{
}

bool BrandDAO::saveBrand(Brand brand)
{
    removeCompetingBrands(brand);

    QSqlQuery saveBrandQuery;
    QString qryString = QString("REPLACE INTO brand SET "
                                "id=:id, image_data=:image_data, position=:position,trans_id=:trans_id, "
                                "head=:head, tag=:tag, date=:date");

    DatabaseManager::defaultManager.prepareQuery(saveBrandQuery,qryString);
    saveBrandQuery.bindValue(":id"          , QVariant::fromValue<long>(brand.getId()));
    string imageData = brand.getImageData();
    QByteArray imageDataArray = QByteArray(imageData.c_str(),imageData.size());
    saveBrandQuery.bindValue(":image_data"  , QVariant::fromValue<QByteArray>(imageDataArray));
    saveBrandQuery.bindValue(":position"    , QString::fromStdString(brand.getBrandPosition()));
    saveBrandQuery.bindValue(":trans_id"    , QVariant::fromValue<long>(brand.getTransactionId()));
    saveBrandQuery.bindValue(":head"        , QVariant::fromValue<long>(brand.getHead()));
    saveBrandQuery.bindValue(":tag"         , QString::fromStdString(brand.getTag()));
    saveBrandQuery.bindValue(":date"        , QString::fromStdString(sale.currentSaleDateSQLString()));

    DatabaseManager::defaultManager.executeQuery(saveBrandQuery);
    bool result = (saveBrandQuery.numRowsAffected() > 0);

    return result;
}

vector<Brand> BrandDAO::getTransactionBrandList(Transaction transaction)
{
    char transId[20];
    sprintf(transId, "%ld", transaction.getId());
    string condStr = "trans_id=" + string(transId) + " " + /*AND LEFT(tag, 1) != '/'*/ "ORDER BY tag";
    return getBrandListByCondition(condStr);
}

vector<Brand> BrandDAO::getLimitedBrandList(int offset, int limit)
{
    char buf[60];
    sprintf(buf, "id != 0  ORDER BY tag LIMIT %d, %d", offset, limit);
    return getBrandListByCondition(string(buf));
}

vector<Brand> BrandDAO::getBrandList()
{
    return getBrandListByCondition("");
}

vector<Brand> BrandDAO::getBrandListByCondition(string condStr)
{
    Brand brand;

    string queryStr =
            "SELECT id, image_data, position, trans_id, head, tag FROM brand "
            "WHERE date='" + sale.currentSaleDateSQLString() + "' " + (condStr.length() > 0 ? " AND " + condStr + "": "") + " ";

    QSqlQuery brandListQuery = DatabaseManager::defaultManager.query(QString::fromStdString(queryStr));
    vector<Brand> brandList;
    while (brandListQuery.next()) {
        long id=DatabaseManager::valueAs<long>(brandListQuery,"id");
        QString imageDataStr = DatabaseManager::valueAs<QString>(brandListQuery,"image_data");
        string imageData    = imageDataStr.toStdString();
        string position = DatabaseManager::valueAs<QString>(brandListQuery,"position").toStdString();
        long trans_id = DatabaseManager::valueAs<long>(brandListQuery,"trans_id");
        long head = DatabaseManager::valueAs<long>(brandListQuery,"head");
        string tag = DatabaseManager::valueAs<QString>(brandListQuery,"tag").toStdString();
        brandList.push_back(Brand(id, imageData, position, trans_id, head, tag));
    }
    return brandList;
}

void BrandDAO::deleteBrand(Brand brand)
{
    QString qryString = QString("DELETE FROM brand WHERE ID=%1").arg(brand.getId());
    DatabaseManager::defaultManager.query(qryString);
}

vector<Brand> BrandDAO::getTagBrand(Tag tag)
{
    string tagNo = tag.getTag();

    if(tagNo.length() > 1 && tagNo[0] == '/')
    {
        tagNo = tagNo.substr(1);
    }

    vector<Brand> brandList = getBrandListByCondition(string("(tag='") + tagNo + "' OR tag='/" + tagNo + "' )");

    return brandList;
}

vector<Brand> BrandDAO::getTagBrandVector(vector<Tag>& tagVector)
{
    stringstream condStr;
    vector<Brand> resultVector;
    string tagString;

    for(unsigned i = 0; i < tagVector.size(); i++)
    {
        tagString = tagVector[i].getTag();

        if(tagString.length() > 0 && tagString[0] == '/')
        {
            tagString = tagString.substr(1);
        }

        condStr << (i != 0 ? " AND " : "") << "(tag='" << tagString << "' OR tag='/" << tagString  << "')";
    }

    if(tagVector.size() > 0)
    {
        resultVector = getBrandListByCondition(condStr.str());
    }

    return resultVector;
}

void BrandDAO::removeCompetingBrands(Brand brand)
{
    string qryString =
            "DELETE FROM brand WHERE LENGTH(tag) != 0 AND LEFT(tag, 1) != '/' AND tag='" + brand.getTag() + "' "
            "AND date='" + sale.currentSaleDateSQLString() + "' ";

    DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
}


vector<Brand> BrandDAO::getInvoiceBrandList(string buyerNum)
{
    string saleDate = sale.currentSaleDateSQLString();

    stringstream queryStr;

    // allow for all combinations of preceding / on the tag matching with
    // tag number that doesn't have /.
    queryStr << "select distinct(brand.id), "
             << "brand.image_data, "
             << "brand.position, "
             << "brand.trans_id, "
             << "brand.head, "
             << "brand.tag, "
             << "brand.date "
             << "from brand cross join backtags cross join trans where "
             << "trans.date='"<< saleDate << "' "
             << "and backtags.ckin_date='" << saleDate << "' "
             << "and brand.date='" << saleDate << "' "
             << "and trans.buyerid='" << buyerNum << "' "
             << "and backtags.trans_id=trans.trans_id "
             << "and (brand.tag=backtags.tag_num or "
             << "brand.tag=concat('/',backtags.tag_num) or "
             << "concat('/',brand.tag)=backtags.tag_num)";

    QSqlQuery invoiceBrandListQuery = DatabaseManager::defaultManager.query(QString::fromStdString(queryStr.str()));

    vector<Brand> brandVector;
    while (invoiceBrandListQuery.next()) {
        long id             = DatabaseManager::valueAs<long>(invoiceBrandListQuery,"id");
        QString imageDataStr = DatabaseManager::valueAs<QString>(invoiceBrandListQuery,"image_data");
        string imageData    = imageDataStr.toStdString();
        string position     = DatabaseManager::valueAs<QString>(invoiceBrandListQuery,"position").toStdString();
        long trans_id       = DatabaseManager::valueAs<long>(invoiceBrandListQuery,"trans_id");
        long head           = DatabaseManager::valueAs<long>(invoiceBrandListQuery,"head");
        string tag          = DatabaseManager::valueAs<QString>(invoiceBrandListQuery,"tag").toStdString();
        brandVector.push_back(Brand(id, imageData, position, trans_id, head, tag));
    }
    return brandVector;
}

// [KLN] add

long BrandDAO::getBrandListSize()
{
    long size = 0L;

    string queryStr =
            "SELECT COUNT(id) AS Size FROM brand WHERE date='" + sale.currentSaleDateSQLString() + "' ";

    QSqlQuery brandListQuery = DatabaseManager::defaultManager.query(QString::fromStdString(queryStr));
    while (brandListQuery.next()) {
        size = DatabaseManager::valueAs<long>(brandListQuery,"Size");
    }
    return size;
}

// [KLN] add end
