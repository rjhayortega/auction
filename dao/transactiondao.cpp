
#include "transactiondao.h"
#include "commissiondao.h"
#include "animalcodedao.h"
#include <QDebug>

TransactionDAO::TransactionDAO()
{
    //////qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    batchMode = false;

    loadTags = true;
    loadCustomerInfo = true;
    loadCharges = true;
    progressCallback = NULL;
}

void TransactionDAO::setProgressCallback(ProgressCallback pc)
{
    ////qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    this->progressCallback = pc;
}

void TransactionDAO::resetLoaded()
{
    ////qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    for(unsigned int i = 0; i < 400; i++)
    {
        sellerChargeTable[i].current = false;
        sellerChargeTableNoBeefCouncil[i].current = false;
        buyerChargeTable[i].current = false;
        commissionTable[i].setId(0);
    }
    buyerCommissionTable.clear();

    chargeInterval += TIMER_INTERVAL;
}

TransactionDAO::~TransactionDAO()
{
    ////qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

}

vector<string> TransactionDAO::uniqueBuyerIdList()
{
    ////qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    vector<string> buyerIdList;

    string queryString =
            "SELECT DISTINCT(buyerId) AS _buyerId FROM trans WHERE date='" + sale.currentSaleDateSQLString() + "' ";

    QSqlQuery buyerListQuery = DatabaseManager::defaultManager.query(QString::fromStdString(queryString));

    while (buyerListQuery.next()) {
        string _buyerId = DatabaseManager::valueAs<QString>(buyerListQuery,"_buyerId").toStdString();
        buyerIdList.push_back(_buyerId);

    }
    return buyerIdList;
}

void TransactionDAO::startBatchMode(bool loadCustomerInfo, bool loadTags, bool loadCharges)
{
    ////qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    batchMode = true;

    this->loadTags = loadTags;
    this->loadCharges = loadCharges;
    this->loadCustomerInfo = loadCustomerInfo;

    if(loadCustomerInfo)
    {
        sellerList = SellerDAO::getCustomerList();
        buyerList = BuyerDAO::getCustomerList();
    }

    //sort(sellerList.begin(), sellerList.end());
    //sort(buyerList.begin(), buyerList.end());

    buyerChargeList = vector<ChargeDAO::ChargeTable>();
    sellerChargeList = vector<ChargeDAO::ChargeTable>();
    sellerChargeListNoBeefCouncil = vector<ChargeDAO::ChargeTable>();
    sellerCommissionList = vector<CommissionDAO::CommissionTable>();

    //  memset(sellerChargeTable, 0, sizeof(ChargeDAO::ChargeTable) * 400);
    //  memset(sellerChargeTableNoBeefCouncil, 0, sizeof(ChargeDAO::ChargeTable) * 400);
    //  memset(buyerChargeTable, 0, sizeof(ChargeDAO::ChargeTable) * 400);

    resetLoaded();
}

void TransactionDAO::endBatchMode()
{
    ////qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    loadTags = true;
    loadCustomerInfo = true;
    loadCharges = true;

    batchMode = false;

    sellerList = vector<Seller>();
    buyerList = vector<Buyer>();
    buyerChargeList = vector<ChargeDAO::ChargeTable>();
    sellerChargeList = vector<ChargeDAO::ChargeTable>();
    sellerChargeListNoBeefCouncil = vector<ChargeDAO::ChargeTable>();

    //  memset(sellerChargeTable, 0, sizeof(ChargeDAO::ChargeTable) * 400);
    //  memset(sellerChargeTableNoBeefCouncil, 0, sizeof(ChargeDAO::ChargeTable) * 400);
    //  memset(buyerChargeTable, 0, sizeof(ChargeDAO::ChargeTable) * 400);
    resetLoaded();
}

vector<Transaction> TransactionDAO::getTransactionListByInvoice(long invoiceId, ChargeDAO::CUST_TYPE chargeType, bool loadBeefCouncil)
{
    ////qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    char buf[20];
    sprintf(buf, "%ld", invoiceId);
    return getTransactionListByCondition(string("sinv_id=") + string(buf), chargeType, loadBeefCouncil);
}

#include <time.h> // included for time trials (trying to make this more efficient)

unsigned long TransactionDAO::queryInterval      = 0;
unsigned long TransactionDAO::sellerInterval     = 0;
unsigned long TransactionDAO::buyerInterval      = 0;
unsigned long TransactionDAO::chargeInterval     = 0;
unsigned long TransactionDAO::commissionInterval = 0;
unsigned long TransactionDAO::codeInterval       = 0;
unsigned long TransactionDAO::tagInterval        = 0;


void TransactionDAO::resetTiming()
{
    ////qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    queryInterval      = 0;
    sellerInterval     = 0;
    buyerInterval      = 0;
    chargeInterval     = 0;
    commissionInterval = 0;
    codeInterval = 0;
    tagInterval        = 0;
}

void TransactionDAO::printTiming()
{
    ////qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    cout << "Transaction loader profile: " << endl;
    cout << "| Query Time    | Seller Time   | Buyer Time    | Charge Time   |Commission Time | Code Time     | Tag Time      |" << endl;
    printf("|%10.2f (s)|%10.2f (s)|%10.2f (s)|%10.2f (s)| %10.2f (s)|%10.2f (s)|%10.2f (s)|\n",
           double(queryInterval) / 1000000,
           double(sellerInterval) / 1000000,
           double(buyerInterval) / 1000000,
           double(chargeInterval) / 1000000,
           double(commissionInterval) / 1000000,
           double(codeInterval) / 1000000,
           double(tagInterval) / 1000000);
}



vector<Transaction> TransactionDAO::getTransactionListByCondition(string whereString, ChargeDAO::CUST_TYPE chargeCust, bool loadBeefCouncil, Date startDate, Date endDate)
{
    ////qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    //cout << endl << "TransactionDAO::getTransactionListByCondition " << whereString << endl;
    bool showBrand = setup.getBoolean("binvShowBrand") && chargeCust == ChargeDAO::Buyer;
    tagDao.setShowBrand(showBrand);

    if(!batchMode)
    {
        resetLoaded();
    }

    string dateString;

    if(startDate == Date() && endDate == Date())
    {
        dateString = "date='" + sale.currentSaleDateSQLString() + "'";
    }
    else
    {
        dateString = "(date >= '" + startDate.toString("YYYY-mm-dd") + "' AND date <= '" + endDate.toString("YYYY-mm-dd") + "'";
    }

    string qryString =
            "SELECT trans_id, sellerID, buyerID, head, weight, descrip, "
            "type, color, flaw, price, mode, sellerpen, buyerpen, created, "
            "updated, weighmaster, active, comment, amount, sinv_id, binv_id, manual,videostart "
            "FROM trans WHERE " + dateString + (whereString.length() > 0 ? " AND " : "") + whereString + "";

    vector<Transaction> transactionList;
    int nfound;

    int transId;
    string sellerId, buyerId;
    int head, weight;
    string descrip;
    int type, color, flaw;
    double price;
    Transaction::SALE_MODE mode;
    string sellerpen;
    string buyerpen;
    DateTime created, updated,videoStart;
    string weighmaster;
    string active, comment;
    double amount;
    Seller seller;
    Buyer buyer;
    vector<Charge> chargeList;
    bool manual;

    AnimalCodeDAO acDao;

    QSqlQuery transactionListQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
    int transListSize = transactionListQuery.size();
    if( transListSize < 1 )
    {
        return transactionList;
    }

    Transaction temp;
    AnimalCode animalCode;
    //  CommissionDAO commDao;
    //  ChargeDAO chargeDao;
    Commission comm;


    vector<Seller>::iterator sellerLoc;
    vector<Buyer>::iterator buyerLoc;

    vector<ChargeDAO::ChargeTable>::iterator chargeLoc;
    vector<ChargeDAO::ChargeTable> *clRef;

    vector<CommissionDAO::CommissionTable>::iterator commLoc;
    vector<CommissionDAO::CommissionTable> *commListRef;
    bool saleOpen = sale.currentSaleOpen();
    queryInterval += TIMER_INTERVAL;

    ChargeDAO::ChargeTable* chargeTable = NULL;

    switch(chargeCust)
    {
    case ChargeDAO::Seller:
    default:
        if(loadBeefCouncil)
        {
            chargeTable = sellerChargeTable;
        }
        else
        {
            chargeTable = sellerChargeTableNoBeefCouncil;
        }
        break;

    case ChargeDAO::Buyer:
        chargeTable = buyerChargeTable;
        break;
    }
    vector<Brand> brandVector;

    // for each transaction found in query .........................
    //
    int i = 0;
    nfound = transactionListQuery.size();
    while (transactionListQuery.next()) {

        transId     = DatabaseManager::valueAs<int>(transactionListQuery,"trans_id");
        sellerId    = DatabaseManager::valueAs<QString>(transactionListQuery,"sellerID").toStdString();
        buyerId     = DatabaseManager::valueAs<QString>(transactionListQuery,"buyerID").toStdString();
        head        = DatabaseManager::valueAs<int>(transactionListQuery,"head");
        weight      = DatabaseManager::valueAs<int>(transactionListQuery,"weight");
        descrip     = DatabaseManager::valueAs<QString>(transactionListQuery,"descrip").toStdString();
        type        = DatabaseManager::valueAs<int>(transactionListQuery,"type");
        color       = DatabaseManager::valueAs<int>(transactionListQuery,"color");
        flaw        = DatabaseManager::valueAs<int>(transactionListQuery,"flaw");
        price       = DatabaseManager::valueAs<double>(transactionListQuery,"price");

        int _mode   = DatabaseManager::valueAs<int>(transactionListQuery,"mode");
        mode        = Transaction::SALE_MODE(_mode);
        sellerpen   = DatabaseManager::valueAs<QString>(transactionListQuery,"sellerpen").toStdString();
        buyerpen    = DatabaseManager::valueAs<QString>(transactionListQuery,"buyerpen").toStdString();
        string  strCreated = DatabaseManager::valueAs<QDateTime>(transactionListQuery,"created").toString("yyyy-MM-dd hh:mm:ss").toStdString();
        created       = DateTime::fromString(strCreated , "YYYY-mm-dd");
        string  strUpdated = DatabaseManager::valueAs<QDateTime>(transactionListQuery,"updated").toString("yyyy-MM-dd hh:mm:ss").toStdString();
        updated       = DateTime::fromString(strUpdated, "YYYY-mm-dd");
        string  strVideoStart = DatabaseManager::valueAs<QDateTime>(transactionListQuery,"videostart").toString("yyyy-MM-dd hh:mm:ss").toStdString();
        videoStart       = DateTime::fromString(strVideoStart, "YYYY-mm-dd");
        weighmaster = DatabaseManager::valueAs<QString>(transactionListQuery,"weighmaster").toStdString();
        active      = DatabaseManager::valueAs<QString>(transactionListQuery,"active").toStdString();
        comment     = DatabaseManager::valueAs<QString>(transactionListQuery,"comment").toStdString();
        amount      = DatabaseManager::valueAs<double>(transactionListQuery,"amount");
        manual      = (DatabaseManager::valueAs<QString>(transactionListQuery,"manual") == "MAN");


        animalCode = acDao.getAnimalCode(type, color, flaw);
        codeInterval += TIMER_INTERVAL;

        if(batchMode)
        {
            //cout << "batchMode is true" << endl;
            sellerLoc = find(sellerList.begin(), sellerList.end(), sellerId);
            sellerInterval += TIMER_INTERVAL;

            buyerLoc = find(buyerList.begin(), buyerList.end(), buyerId);
            buyerInterval += TIMER_INTERVAL;

            seller = (sellerLoc == sellerList.end() ?  Seller() : *sellerLoc);
            sellerInterval += TIMER_INTERVAL;

            buyer = (buyerLoc == buyerList.end() ? Buyer() : *buyerLoc);
            buyerInterval += TIMER_INTERVAL;

            seller.setNumber(sellerId);
            sellerInterval += TIMER_INTERVAL;

            buyer.setNumber(buyerId);
            buyerInterval += TIMER_INTERVAL;
        }
        else
        {
            //cout << "batchMode is false" << endl;
            sellerLoc = find(sellerList.begin(), sellerList.end(), sellerId);

            if(sellerLoc == sellerList.end())
            {
                sellerList.push_back(SellerDAO::loadFromNumber(sellerId));
                sellerLoc = sellerList.end() - 1;
            }

            seller = *sellerLoc;

            sellerInterval += TIMER_INTERVAL;

            buyerLoc = find(buyerList.begin(), buyerList.end(), buyerId);

            if(buyerLoc == buyerList.end())
            {
                buyerList.push_back(BuyerDAO::loadFromNumber(buyerId));
                buyerLoc = buyerList.end() - 1;
            }

            buyer = *buyerLoc;

            buyerInterval += TIMER_INTERVAL;
        }

        if((!batchMode || loadCharges) && saleOpen)
        {
            int chargeIndex = animalCode.group() * 100 + animalCode.getType() * 10 + animalCode.chargeFlaw();

            if(chargeTable != NULL && 0 <= chargeIndex && chargeIndex < 400)
            {
                if(!chargeTable[chargeIndex].current)
                {
                    chargeTable[chargeIndex] =  ChargeDAO::ChargeTable(animalCode, chargeDao.getChargeList(animalCode, chargeCust, loadBeefCouncil));
                    chargeTable[chargeIndex].current = true;
                }

                chargeList = chargeTable[chargeIndex].chargeList;
            }
            chargeInterval += TIMER_INTERVAL;
            //    chargeList = chargeDao.getChargeList(animalCode, chargeCust, loadBeefCouncil);
            switch(chargeCust)
            {
            case ChargeDAO::Seller:
            default:
                if(0 <= chargeIndex && chargeIndex < 400)
                {
                    if(commissionTable[chargeIndex].getId() == 0)
                    {
                        commissionTable[chargeIndex] = commDao.getCommission(animalCode);
                    }
                    comm = commissionTable[chargeIndex];
                }

                break;

            case ChargeDAO::Buyer:
                vector<CommissionDAO::BuyerCommissionTable>::iterator currentBuyerComm;
                currentBuyerComm = find(buyerCommissionTable.begin(), buyerCommissionTable.end(), buyerId);

                if(currentBuyerComm == buyerCommissionTable.end())
                {
                    comm = commDao.getBuyerCommission(buyerId);
                    buyerCommissionTable.push_back(CommissionDAO::BuyerCommissionTable(buyerId, comm));
                }
                else
                {
                    comm = currentBuyerComm->commission;
                }

                break;
            }
            //comm = (chargeCust == ChargeDAO::Seller ? commDao.getCommission(animalCode): commDao.getBuyerCommission(buyerId));
        }


        commissionInterval += TIMER_INTERVAL;
        /*
    temp = Transaction(transId, seller, buyer, head,
               weight, price, mode, animalCode,
                       animalCode.getDescrip(), sellerpen, buyerpen,
               created, updated, comment,
                       comm, vector<Tag>(), weighmaster, manual);
*/
        // set up the temp transaction object from results of query
        // and processing so far ...
        temp.setId(transId);
        temp.setSeller(seller);
        temp.setBuyer(buyer);
        temp.setHead(head);
        temp.setWeight(weight);
        temp.setPrice(price);
        temp.setMode(mode);
        temp.setAnimalCode(animalCode);
        temp.setDescription(animalCode.getDescrip());
        temp.setSellerPen(sellerpen);
        temp.setBuyerPen(buyerpen);
        temp.setCreated(created);
        temp.setUpdated(updated);
        temp.setVideoStart(videoStart);
        temp.setComment(comment);
        temp.setCommission(comm);
        temp.setTagList(vector<Tag>());
        temp.setWeighmaster(weighmaster);
        temp.setManual(manual);


        if(loadCharges && saleOpen)
        {
            temp.setChargeList(chargeList);                                                  ;
        }

        if(loadTags)
        {
            //cout << "transactiondao: loadTags true" << endl;
            vector<Tag> tagVector = tagDao.getTagList(temp);
            //cout << "  tagVector size = " << tagVector.size() << endl;

            if(showBrand)
            {
                //cout << "showBrand true" << endl;
                if(i == 0)
                {
                    //cout << "  call brandDao.getInvoiceBrandList( " << buyerId << " )" << endl;
                    brandVector = brandDao.getInvoiceBrandList(buyerId);
                    //cout << "Brand vector size " << brandVector.size() << endl;
                }

                //cout << "  call Tag::mergeBrands(tagVector,brandVector)" << endl;
                Tag::mergeBrands(tagVector, brandVector);

                //        vector<Brand> brandList = brandDao.getTagBrandVector(tagList);
                //	Tag::mergeBrands(tagList, brandList);
                //	temp.setBrandList(brandDao.getTransactionBrandList(temp));
            }

            //cout << "set temp tagVector temp.setTagList(tagVector) size = " << tagVector.size() << endl;
            temp.setTagList(tagVector);
        }

        tagInterval += TIMER_INTERVAL;
        transactionList.push_back(temp);

        if(progressCallback != NULL)
        {
            progressCallback(i + 1, nfound);
        }
        i++;
    }

    //
    // ............................ for each transaction found in query


    // unless we will be processing several transaction lists at one time (batch mode)
    // we do not want to save accumulated data between processing separate transaction
    // lists, as the data may change
    if(!batchMode)
    {
        sellerList = vector<Seller>();
        buyerList = vector<Buyer>();
    }

#ifdef DEBUG_TRANS_TIMING
    printTiming();
#endif
    //cout << endl << "end of   TransactionDAO::getTransactionListByCondition " << whereString << endl;
    ////qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    return transactionList;

}

vector<Transaction> TransactionDAO::getTransactionListBySeller(Seller seller, bool loadBeefCouncil)
{
    ////qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    char buf[255];
    sprintf(buf, "(mode != %d AND mode != %d AND mode != 0)", Transaction::SwapCWT, Transaction::SwapHead);
    string condString = "(sellerID='" + seller.getNumber() + "' AND " + string(buf) + ")";
    return getTransactionListByCondition(condString, ChargeDAO::Seller, loadBeefCouncil);
}


vector<Transaction> TransactionDAO::getTransactionListByBuyer(Buyer buyer)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    char buf[255];
    sprintf(buf, "((mode=%d OR mode=%d) AND sellerID='%s')", Transaction::SwapCWT, Transaction::SwapHead, buyer.getNumber().c_str());
    string condString = "(buyerID='" + buyer.getNumber()+ "' OR " + string(buf) + ") AND mode != 0 ";
    vector<Transaction> transList = getTransactionListByCondition(condString, ChargeDAO::Buyer);
    return transList;
}


Transaction TransactionDAO::getTransactionById(long id, ChargeDAO::CUST_TYPE chargeType, bool isBeefCouncil)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    char idStr[20];
    sprintf(idStr, "%ld", id);
    return getTransactionByCondition(string("trans_id=") + string(idStr), chargeType, isBeefCouncil);
}


Transaction TransactionDAO::getTransactionByCondition(string condStr, ChargeDAO::CUST_TYPE custType, bool isBeefCouncil)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    string qryString =
            "SELECT trans_id, sellerID, buyerID, head, weight, descrip, "
            "type, color, flaw, price, mode, sellerpen, buyerpen, created, "
            "updated, weighmaster, active, comment, amount, sinv_id, binv_id, manual, videostart "
            "FROM trans WHERE date = '" + sale.currentSaleDateSQLString() + "'"
            "" + (condStr.length() > 0 ? " AND " : "") + condStr;



    Transaction transaction;
    int nfound;

    long transId;
    string sellerId, buyerId;
    long head, weight;
    string descrip;
    short type, color, flaw;
    double price;
    Transaction::SALE_MODE mode;
    string sellerpen;
    string buyerpen;
    DateTime created, updated, videostart;
    string weighmaster;
    string active, comment;
    double amount;
    int sinv_id, binv_id;

    QSqlQuery transactionQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));

    nfound = transactionQuery.size();
    bool isFound = (nfound > 0);
    if(!isFound)
    {
        GRIPE("Error performing trans query");
        return transaction;
    }

    bool showBrand = false;

    if(isFound && (custType == ChargeDAO::Buyer))
    {
        showBrand = setup.getBoolean("binvShowBrand");
        tagDao.setShowBrand(showBrand);
    }

    vector<Brand> brandVector;
    AnimalCodeDAO acDao;
    bool manual;
    int i = 0;

    while (transactionQuery.next())    {
        transId       = DatabaseManager::valueAs<int>(transactionQuery,"trans_id");
        sellerId      = DatabaseManager::valueAs<QString>(transactionQuery,"sellerID").toStdString();
        buyerId       = DatabaseManager::valueAs<QString>(transactionQuery,"buyerID").toStdString();
        head          = DatabaseManager::valueAs<int>(transactionQuery,"head");
        weight        = DatabaseManager::valueAs<int>(transactionQuery,"weight");
        descrip       = DatabaseManager::valueAs<QString>(transactionQuery,"descrip").toStdString();
        type          = DatabaseManager::valueAs<int>(transactionQuery,"type");
        color         = DatabaseManager::valueAs<int>(transactionQuery,"color");
        flaw          = DatabaseManager::valueAs<int>(transactionQuery,"flaw");
        price         = DatabaseManager::valueAs<double>(transactionQuery,"price");

        int _mode     = DatabaseManager::valueAs<int>(transactionQuery,"mode");
        mode          = Transaction::SALE_MODE(_mode);
        sellerpen     = DatabaseManager::valueAs<QString>(transactionQuery,"sellerpen").toStdString();
        buyerpen      = DatabaseManager::valueAs<QString>(transactionQuery,"buyerpen").toStdString();

        string  strCreated = DatabaseManager::valueAs<QDateTime>(transactionQuery,"created").toString("yyyy-MM-dd hh:mm:ss").toStdString();
        created       = DateTime::fromString(strCreated , "YYYY-mm-dd");
        string  strUpdated = DatabaseManager::valueAs<QDateTime>(transactionQuery,"updated").toString("yyyy-MM-dd hh:mm:ss").toStdString();
        updated       = DateTime::fromString(strUpdated, "YYYY-mm-dd");

        string  strVideoStart = DatabaseManager::valueAs<QDateTime>(transactionQuery,"videostart").toString("yyyy-MM-dd hh:mm:ss").toStdString();
        videostart       = DateTime::fromString(strVideoStart, "YYYY-mm-dd");

        weighmaster   = DatabaseManager::valueAs<QString>(transactionQuery,"weighmaster").toStdString();
        active        = DatabaseManager::valueAs<QString>(transactionQuery,"active").toStdString();
        comment       = DatabaseManager::valueAs<QString>(transactionQuery,"comment").toStdString();
        amount        = DatabaseManager::valueAs<double>(transactionQuery,"amount");
        manual        = (DatabaseManager::valueAs<QString>(transactionQuery,"manual") == "MAN");

        AnimalCode animalCode = acDao.getAnimalCode(type, color, flaw);
        CommissionDAO commDao;
        transaction = Transaction(transId, SellerDAO::loadFromNumber(sellerId), BuyerDAO::loadFromNumber(buyerId), head,
                                  weight, price, mode, animalCode, descrip, sellerpen, buyerpen,
                                  created, updated, comment, commDao.getCommission(animalCode), vector<Tag>(),
                                  weighmaster, manual,videostart);

        if(sale.currentSaleOpen())
        {
            transaction.setChargeList(ChargeDAO().getChargeList(animalCode, custType, isBeefCouncil));
        }

        vector<Tag> tagVector = TagDAO().getTagList(transaction);

        if(showBrand)
        {
            if(i == 0)
            {
                //	brandVector = brandDao.getInvoiceBrandList(buyerId);
                //	cout << "Brand vector size " << brandVector.size() << endl;
            }

            //      Tag::mergeBrands(tagVector, brandVector);
            //      vector<Brand> brandList = brandDao.getTagBrandVector(tagList);
            //      Tag::mergeBrands(tagList, brandList);
            //      transaction.setBrandList(brandDao.getTransactionBrandList(transaction));
        }

        transaction.setTagList(tagVector);
    }
    return transaction;
}


long TransactionDAO::saveTransaction(Transaction transaction)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    if(!sale.currentSaleOpen())
    {
        return 0;
    }

    AnimalCode code = transaction.getAnimalCode();
    string dateStr = (transaction.getCreated() == DateTime() ? DateTime::currentDateTime().toString("YYYY-mm-dd") : transaction.getCreated().toString("YYYY-mm-dd"));

    QSqlQuery saveTransactionQuery;
    QString qryString = QString("REPLACE INTO trans set trans_id=:trans_id, sellerID=:sellerID, "
                                "buyerID=:buyerID, head=:head, weight=:weight, descrip=:descrip, "
                                "type=:type, color=:color, flaw=:flaw, price=:price, mode=:mode, "
                                "sellerPen=:sellerPen, buyerPen=:buyerPen, created=:created, updated=:updated, "
                                "weighmaster=:weighmaster, active=:active, comment=:comment,"
                                "amount=:amount, date=:date, manual=:manual ");

    DatabaseManager::defaultManager.prepareQuery(saveTransactionQuery,qryString);

    saveTransactionQuery.bindValue(":trans_id"  , QVariant::fromValue<long>(transaction.getId()));
    saveTransactionQuery.bindValue(":sellerID"  , QString::fromStdString(transaction.getSeller().getNumber()));
    saveTransactionQuery.bindValue(":buyerID"   , QString::fromStdString(transaction.getBuyer().getNumber()));
    saveTransactionQuery.bindValue(":head"      , QVariant::fromValue<long>(transaction.getHead(false, false, true)));
    saveTransactionQuery.bindValue(":weight"    , QVariant::fromValue<long>(transaction.getWeight()));
    saveTransactionQuery.bindValue(":descrip"   , QString::fromStdString(code.getDescrip()));
    saveTransactionQuery.bindValue(":type"      , code.getType());
    saveTransactionQuery.bindValue(":color"     , code.getColor());
    saveTransactionQuery.bindValue(":flaw"      , code.getFlaw());
    saveTransactionQuery.bindValue(":price"     , transaction.getPrice());
    saveTransactionQuery.bindValue(":mode"      , transaction.getMode());
    saveTransactionQuery.bindValue(":sellerPen" , QString::fromStdString(transaction.getSellerPen()));
    saveTransactionQuery.bindValue(":buyerPen"  , QString::fromStdString(transaction.getBuyerPen()));
    saveTransactionQuery.bindValue(":created"   , QString::fromStdString(dateStr));
    saveTransactionQuery.bindValue(":updated"   , QString::fromStdString(DateTime::currentDateTime().toString("YYYY-mm-dd")));
    saveTransactionQuery.bindValue(":weighmaster", QString::fromStdString(transaction.getWeighmaster()));
    saveTransactionQuery.bindValue(":active"    , 1);
    saveTransactionQuery.bindValue(":comment"   , QString::fromStdString(transaction.getComment()));
    saveTransactionQuery.bindValue(":amount"    , transaction.amount());
    saveTransactionQuery.bindValue(":date"      , QString::fromStdString(sale.currentSaleDateSQLString()));
    saveTransactionQuery.bindValue(":manual"    , QString::fromStdString((transaction.isManual() ? "MAN" : "AUTO")));

    DatabaseManager::defaultManager.executeQuery(saveTransactionQuery);
    long id = transaction.getId();

    if(id == 0)
    {
        id = DatabaseManager::defaultManager.get_last_id(saveTransactionQuery);
        transaction.setId(id);
    }

    TagDAO().updateTransactionTagList(transaction.getId(), transaction.getSeller().getNumber());

    if(saveTransactionQuery.numRowsAffected()<=0)
    {
        GRIPE("Error performing trans query");
    }

    return id;
}


vector<Transaction> TransactionDAO::getTransactionList()
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    return getTransactionListByCondition("");
}

vector<Transaction> TransactionDAO::getTransactionList(vector<short> sexList)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    sort(sexList.begin(), sexList.end());
    vector<short>::iterator newEnd = unique(sexList.begin(), sexList.end());

    string sexCodeString;

    char buf[20];

    for(vector<short>::iterator current = sexList.begin(); current != newEnd; current++)
    {
        sprintf(buf, "%d", *current);
        sexCodeString += string(buf) + (current + 1 != newEnd ? "," : "");
    }

    if(sexCodeString.length() > 0)
    {
        string condition = "type in(" + sexCodeString + ")";
        return getTransactionListByCondition(condition);
    }

    return vector<Transaction>();
}

void TransactionDAO::removeTransaction(long transNo)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    char transId[20];
    sprintf(transId, "%ld", transNo);

    string qryString = "DELETE FROM trans WHERE trans_id=" + string(transId) + " AND date='" + sale.currentSaleDateSQLString() + "' ";
    DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
}

vector<Transaction> TransactionDAO::getMarketTransactionList(long minHead, double minPrice, AnimalCode::Group colorGroup)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    char minHd[20], minPr[20];

    sprintf(minHd, "%ld", minHead);
    sprintf(minPr, "%0.2f", minPrice);
    string codeRange;

    if(colorGroup != AnimalCode::Invalid)
    {
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
            codeRange = "90 <= color AND color < 100";
            break;

        case AnimalCode::Invalid:
            cerr << "REALITY ERROR, RE-INSTALL UNIVERSE AND REBOOT" << endl;
            break;
        }
    }

    SetupDAO setup;
    string firstSort  = setup.get("firstMarketReportSort");
    string secondSort = setup.get("secondMarketReportSort");
    string thirdSort  = setup.get("thirdMarketReportSort");
    string fourthSort = setup.get("fourthMarketReportSort");
    string fifthSort  = setup.get("fifthMarketReportSort");

    string condStr =
            "head >= " + string(minHd) + " AND price >= " + string(minPr) + " AND mode!=7 AND mode!=8 AND mode != 0 AND mode != 3 AND mode != 4"
            " " + (codeRange.length() > 0 ? " AND " : "") + codeRange;

    startBatchMode(true, false, false);
    vector<Transaction> transactionList = getTransactionListByCondition(condStr);
    endBatchMode();

    return transactionList;
}

PenReport TransactionDAO::getPenReport(PenReport::SortOption option)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    vector<PenReport::Item> penReportList;

    string dateStr = sale.currentSaleDateSQLString();

    string qryString =
            "SELECT buyerpen, sum(head) As sumHead, "
            "buyerID, (select name from buyer where buyer.number=trans.buyerID and date='" + dateStr + "') as _name , "
            "sum(weight) as sumWeight "
            "from trans WHERE trans.date='" + dateStr + "' AND mode != 0 GROUP BY buyerpen, buyerid";

    QSqlQuery penReportQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));

    string buyerName;
    while (penReportQuery.next()) {
        string buyerName = DatabaseManager::valueAs<QString>(penReportQuery,"_name").toStdString();
        if (buyerName.empty()) {
            buyerName = "No Name Found";
        }
        string _buyerpen = DatabaseManager::valueAs<QString>(penReportQuery,"buyerpen").toStdString();
        long _sumHead    = DatabaseManager::valueAs<long>(penReportQuery,"sumHead");
        string _buyerID  = DatabaseManager::valueAs<QString>(penReportQuery,"buyerID").toStdString();
        long _sumWeight  = DatabaseManager::valueAs<long>(penReportQuery,"sumWeight");

        penReportList.push_back(PenReport::Item(_buyerpen,
                                _sumHead, 0, _buyerID, buyerName, _sumWeight));
    }
    return PenReport(penReportList, option);

}


long TransactionDAO::getNoSaleHead(CommissionDAO::COLOR_GROUP colorGroup)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    char trueStr[3];
    sprintf(trueStr, "%d", int(true));

    char groupBuf[3];
    sprintf(groupBuf, "%d", colorGroup);

    string qryString =
            "SELECT sum(head) AS _sumHead FROM trans WHERE date='" + sale.currentSaleDateSQLString() + "' AND (mode=3 OR mode=4) "
            "AND type not in (SELECT code FROM codes WHERE pair=" + string(trueStr) + " AND code_type=00" + (colorGroup != CommissionDAO::INVALID ? string(" AND color_group=") + string(groupBuf) : string("")) + ")";

    string pairQryString =
            "SELECT sum(head * 2) AS _sumPairHead FROM trans WHERE date='" + sale.currentSaleDateSQLString() + "' AND (mode=3 OR mode=4) "
            "AND type in (SELECT code FROM codes WHERE pair=" + string(trueStr) + " AND code_type=00" + (colorGroup != CommissionDAO::INVALID ? string(" AND color_group=") + string(groupBuf) : string("")) + ")";
    long retval = 0;

    if(colorGroup != CommissionDAO::INVALID)
    {
        string codeRange;

        switch(colorGroup)
        {
        case CommissionDAO::FIRST:
            codeRange = "0 <= color AND color < 70";
            break;

        case CommissionDAO::SECOND:
            codeRange = "70 <= color AND color < 80";
            break;

        case CommissionDAO::THIRD:
            codeRange = "80 <= color AND color < 90";
            break;

        case CommissionDAO::FOURTH:
            codeRange = "90 <= color AND color < 100";
            break;

        case CommissionDAO::INVALID:
            cerr << "REALITY ERROR, INSTALL UNIVERSE AGAIN AND REBOOT" << endl;
            break;
        }

        qryString += string(" AND (") + codeRange + ")";
        pairQryString += string(" AND (") + codeRange + ")";
    }

    // [KLN] debug start
//    cout << "qryString: " << qryString << endl;
//    cout << "pairQryString: " << pairQryString << endl;
    // [KLN] debug end

    QSqlQuery headQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));

    retval = 0;

    if(headQuery.first()) {
        retval = DatabaseManager::valueAs<long>(headQuery,"_sumHead");
    }
    QSqlQuery headPairQuery =  DatabaseManager::defaultManager.query(QString::fromStdString(pairQryString));

    if(headPairQuery.first()) {
        retval += DatabaseManager::valueAs<long>(headPairQuery,"_sumPairHead");
    }
    return retval;
}


long TransactionDAO::soldHead()
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    //   string qryString =
    //     "SELECT sum(head) FROM trans WHERE date='" + sale.currentSaleDateSQLString() + "' ";

    //   long nfound = DatabaseManager::defaultManager.query(qryString.c_str());
    //   long head = 0;

    //   if(nfound > 0)
    //   {
    //     char **record = DatabaseManager::defaultManager.get_record();
    //     if(record != NULL && record[0] != NULL)
    //     {
    //       head = atol(record[0]);
    //     }

    //     DatabaseManager::defaultManager.release_result();
    //   }

//    cerr << endl << "AnimalCode::First: " << int(AnimalCode::First)
//            << " AnimalCode::Second: " << int(AnimalCode::Second)
//            << " AnimalCode::Third: " << int(AnimalCode::Third)
//            << " AnimalCode::Fourth: " << int(AnimalCode::Fourth)
//            << endl;

    return soldHeadByGroup(AnimalCode::First) + soldHeadByGroup(AnimalCode::Second) + soldHeadByGroup(AnimalCode::Third) + soldHeadByGroup(AnimalCode::Fourth);
}

long TransactionDAO::soldHeadByGroup(AnimalCode::Group codeGroup)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    long pairCount = 0;
    long straightCount = 0;
    char groupBuf[3];
    string colorCondition;
    sprintf(groupBuf, "%d", codeGroup);

    switch(codeGroup)
    {
    case AnimalCode::First:
        colorCondition = "(0 <= trans.color AND trans.color <= 69)";
        break;
    case AnimalCode::Second:
        colorCondition = "(70 <= trans.color AND trans.color <= 79)";
        break;
    case AnimalCode::Third:
        colorCondition = "(80 <= trans.color AND trans.color <= 89)";
        break;
    case AnimalCode::Fourth:
        colorCondition = "(90 <= trans.color AND trans.color <= 99)";
        break;

    default:
        return 0;
    }

    char** record = NULL;

    string dateString = sale.currentSaleDateSQLString();

    string queryString =
            "SELECT SUM(trans.head * 2) AS _sumHead FROM trans CROSS JOIN codes "
            "WHERE trans.date='" + dateString + "' "
            "AND trans.mode !=0 "
            "AND " + colorCondition + " "
            "AND trans.type=codes.code AND codes.code_type=0 "
            "AND codes.color_group=" +  string(groupBuf) + " "
            "AND codes.pair=1";

    QSqlQuery sumQuery = DatabaseManager::defaultManager.query(QString::fromStdString(queryString));

    if (sumQuery.first()) {
        pairCount = DatabaseManager::valueAs<long>(sumQuery,"_sumHead");
    }

    queryString =
            "SELECT SUM(trans.head) as _transHead FROM trans CROSS JOIN codes "
            "WHERE trans.date='" + dateString + "' "
            "AND trans.mode!= 0 "
            "AND " + colorCondition + " "
            "AND trans.type=codes.code AND codes.code_type=0 "
            "AND codes.color_group=" +  string(groupBuf) + " "
            "AND codes.pair=0";

    QSqlQuery sumHeadQuery = DatabaseManager::defaultManager.query(QString::fromStdString(queryString));

    if (sumHeadQuery.first()) {
        straightCount = DatabaseManager::valueAs<long>(sumHeadQuery,"_transHead");
    }
    return pairCount + straightCount;
}

double TransactionDAO::currentSaleLength(DateTime& endTime)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    string qryString = "select MIN(created) as _minCreated, MAX(created) as _maxCreated FROM trans WHERE date='" + sale.currentSaleDateSQLString() + "'";
    QSqlQuery saleQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
    double result = 0.00;
    bool saleOpen = sale.currentSaleOpen();

    if(saleQuery.first()) {
        string _minCreated = DatabaseManager::valueAs<QString>(saleQuery,"_minCreated").toStdString();
        string _maxCreated = DatabaseManager::valueAs<QString>(saleQuery,"_maxCreated").toStdString();

        DateTime current = DateTime::currentDateTime();
        DateTime start = DateTime::fromString(_minCreated, "YYYY-mm-dd");
        endTime = DateTime::fromString(_maxCreated, "YYYY-mm-dd");
        result = (saleOpen ? current.hoursFrom(start) : endTime.hoursFrom(start));
    }
    return result;
}

double TransactionDAO::currentSaleLength(QDateTime& endTime)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    string qryString = "select MIN(created) as _minCreated, MAX(created) as _maxCreated FROM trans WHERE date='" + sale.currentSaleDateSQLString() + "'";
    QSqlQuery saleQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
    double result = 0.00;
    bool saleOpen = sale.currentSaleOpen();

    if(saleQuery.first()) {
        QString _minCreated = DatabaseManager::valueAs<QString>(saleQuery,"_minCreated");
        QString _maxCreated = DatabaseManager::valueAs<QString>(saleQuery,"_maxCreated");

        QDateTime current = QDateTime::currentDateTime();
        QDateTime start = QDateTime::fromString(_minCreated, "YYYY-mm-dd");
        endTime = QDateTime::fromString(_maxCreated, "YYYY-mm-dd");
        result = (saleOpen ? current.time().hour()-start.time().hour() : endTime.time().hour()-start.time().hour());
    }
    return result;
}



void TransactionDAO::saveMarketReportTransactionIdList(vector<Transaction> transactionList)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    char buf[20];
    string dateStr = sale.currentSaleDateSQLString();

    string qryString = "DELETE FROM market_report WHERE date='" + dateStr + "' ";
    DatabaseManager::defaultManager.query(QString::fromStdString(qryString));

    qryString = "INSERT INTO market_report SET date='" + dateStr + "', trans_id=";

    for(unsigned int i = 0; i < transactionList.size(); i++)
    {
        sprintf(buf, "%ld", transactionList[i].getId());
        DatabaseManager::defaultManager.query(QString::fromStdString(qryString + string(buf)));
    }
}


vector<long> TransactionDAO::getMarketReportTransactionIdList()
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    string qryString = "SELECT trans_id FROM market_report WHERE date='" + sale.currentSaleDateSQLString() + "'";
    vector<long> transactionIdList;

    QSqlQuery transListQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));

    while (transListQuery.next())  {
        long _trans_id = DatabaseManager::valueAs<long>(transListQuery,"trans_id");
        transactionIdList.push_back(_trans_id);
    }
    return transactionIdList;
}

bool TransactionDAO::globalBuyerChange(string oldBuyerNumber, string newBuyerNumber)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    string qryString =
            "UPDATE trans SET buyerID='" + newBuyerNumber + "' "
            "WHERE date='" + sale.currentSaleDateSQLString() + "' "
            "AND buyerID='" + oldBuyerNumber + "' ";

    QSqlQuery buyerQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));

    if(!buyerQuery.first())
    {
        cerr << "Error performing global buyer change" << endl;
        return false;
    }

    return true;
}

bool TransactionDAO::globalPenChange(string buyerNumber, string oldPen, string newPen)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    string qryString =
            "UPDATE trans SET buyerpen='" + newPen + "' "
            "WHERE date='" + sale.currentSaleDateSQLString() + "' "
            "AND buyerpen='" + oldPen + "' "
            "AND buyerID='" + buyerNumber + "' ";

    QSqlQuery penQuery =  DatabaseManager::defaultManager.query(QString::fromStdString(qryString));

    if(!penQuery.first()) {
        cerr << "Error performing global pen change" << endl;
        return false;
    }
    return true;
}

long TransactionDAO::lastTransactionId()
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    long result = 0;

    stringstream queryStr;
    queryStr << "SELECT Max(trans_id) AS _maxID FROM trans WHERE date='" << sale.currentSaleDateSQLString() << "'";

    QSqlQuery transIdQuery = DatabaseManager::defaultManager.query(QString::fromStdString(queryStr.str()));

    while(transIdQuery.next()) {
        result = DatabaseManager::valueAs<long>(transIdQuery,"_maxID");
    }
    return result;
}

vector<Buyer> TransactionDAO::getBuyerList(Seller seller)
{
    //qDebug() << QString("%1 %2 %3").arg(__FILE__).arg(__LINE__).arg(__func__) ;

    vector<Buyer> resultVector;

    stringstream queryStr;
    queryStr << "SELECT DISTINCT buyerID FROM trans WHERE date='" << sale.currentSaleDateSQLString() << "' AND sellerID='" << seller.getNumber() << "' ";
    QSqlQuery buyerListQuery = DatabaseManager::defaultManager.query(QString::fromStdString(queryStr.str()));

    while (buyerListQuery.next()) {
        string _buyerID = DatabaseManager::valueAs<QString>(buyerListQuery,"buyerID").toStdString();
        resultVector.push_back(BuyerDAO::loadFromNumber(_buyerID));
    }
    return resultVector;
}

