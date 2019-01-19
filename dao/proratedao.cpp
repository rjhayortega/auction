
#include "proratedao.h"

ProrateDAO::ProrateDAO()
{
    checkFactory = NULL;
}

CheckFactory* ProrateDAO::getCheckFactory(Invoice invoice, Mode *modeOut)
{
    checkFactory = NULL;
    char invId[20];
    sprintf(invId, "%ld", invoice.getNumber());

    string qryString = "SELECT mode, share_charges FROM checkfactory WHERE invoice_id=" + string(invId) + " ";

    QSqlQuery checkQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));

    if(checkQuery.first()) {
        int _mode = DatabaseManager::valueAs<int>(checkQuery,"mode");
        bool shareCharges = DatabaseManager::valueAs<bool>(checkQuery,"share_charges");
        Mode mode = Mode(_mode);
        vector<Prorate> prorateList = getProrateList(invoice.getNumber());

        if(modeOut != NULL)
        {
            *modeOut = mode;
        }

        switch(mode)
        {
        case Percentage:
            checkFactory = new PercentageCheckFactory(invoice, shareCharges, prorateList);
            break;

        case Flat:
            checkFactory = new FlatCheckFactory(invoice, shareCharges, prorateList);
            break;

        case Head:
            checkFactory = new HeadCheckFactory(invoice, shareCharges, prorateList);
            break;

        case Transaction:
            checkFactory = new TransactionCheckFactory(invoice, shareCharges, prorateList);
            break;

        case Sex:
            checkFactory = new SexCheckFactory(invoice, shareCharges, prorateList);
            break;

        default:
            checkFactory = NULL;
            break;
        };
    }
    return checkFactory;
}


vector<Prorate> ProrateDAO::getProrateList(long invoiceId)
{
    char invId[20];
    sprintf(invId, "%ld", invoiceId);

    string qryString = "SELECT id, payee FROM prorate WHERE invoice_id=" + string(invId) + " ORDER BY id ";
    QSqlQuery prorateListQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
    string payee;
    vector<Prorate> prorateList;
    vector<Prorate::Data> dataList;

    while (prorateListQuery.next()){
        long _id = DatabaseManager::valueAs<int>(prorateListQuery,"id");
        payee = DatabaseManager::valueAs<QString>(prorateListQuery,"payee").toStdString();
        dataList = getProrateData(_id);
        prorateList.push_back(Prorate(payee, dataList));
    }
    return prorateList;
}

vector<Prorate::Data> ProrateDAO::getProrateData(long prorateId)
{
    QString qryString = QString("SELECT number, amount FROM proratedata WHERE prorate_id=%1 ").arg(prorateId);
    QSqlQuery prorateDataListQuery  = DatabaseManager::defaultManager.query(qryString);
    Prorate::Data data;
    vector<Prorate::Data> dataList;

    while(prorateDataListQuery.next()) {
        data.number = DatabaseManager::valueAs<long>(prorateDataListQuery,"number");
        data.amount = DatabaseManager::valueAs<double>(prorateDataListQuery,"amount");
        dataList.push_back(data);
    }
    return dataList;
}

void ProrateDAO::releaseCheckFactory()
{
    if(checkFactory != NULL)
    {
        delete checkFactory;
    }
}

void ProrateDAO::saveCheckFactory(CheckFactory * checkFactory, Mode prorateMode)
{
    QSqlQuery saveCheckQuery;
    QString qryString = QString("REPLACE INTO checkfactory SET mode=:mode, "
                                "share_charges=:share_charges, invoice_id=:invoice_id");
    DatabaseManager::defaultManager.prepareQuery(saveCheckQuery,qryString);
    saveCheckQuery.bindValue(":mode"         , QVariant::fromValue<long>(prorateMode));
    saveCheckQuery.bindValue(":share_charges", QVariant::fromValue<long>(checkFactory->sharesCharges()));
    saveCheckQuery.bindValue(":invoice_id"   , QVariant::fromValue<long>(checkFactory->getInvoice().getNumber()));

    DatabaseManager::defaultManager.executeQuery(saveCheckQuery);
    saveProrateList(checkFactory->getInvoice().getNumber(), checkFactory->getProrateList());
}

void ProrateDAO::saveProrateList(long invoiceId, vector<Prorate> prorateList)
{
    char invId[20];
    sprintf(invId, "%ld", invoiceId);

    string qryString = "DELETE FROM proratedata WHERE prorate_id in (SELECT id FROM prorate where invoice_id=" + string(invId) + ") ";
    DatabaseManager::defaultManager.query(qryString.c_str());

    qryString = "DELETE FROM prorate WHERE invoice_id=" + string(invId) + " ";
    DatabaseManager::defaultManager.query(qryString.c_str());

    for(unsigned int i = 0; i < prorateList.size(); i++)
    {
        saveProrate(invoiceId, prorateList[i]);
    }
}


void ProrateDAO::saveProrate(long invoiceId, Prorate prorate)
{
    QSqlQuery saveProrateQuery;
    QString qryString = QString("INSERT INTO prorate SET payee=:payee, invoice_id=:invoice_id ");
    DatabaseManager::defaultManager.prepareQuery(saveProrateQuery,qryString);
    saveProrateQuery.bindValue(":payee"         , QString::fromStdString(prorate.getPayee()));
    saveProrateQuery.bindValue(":invoice_id"    , QVariant::fromValue<long>(invoiceId));
    DatabaseManager::defaultManager.executeQuery(saveProrateQuery);

    long prorateId = DatabaseManager::defaultManager.get_last_id(saveProrateQuery);
    saveDataList(prorateId, prorate.getDataList());
}


void ProrateDAO::saveDataList(long prorateId, vector<Prorate::Data> dataList)
{
    for(unsigned int i = 0; i < dataList.size(); i++)
    {
        saveProrateData(prorateId, dataList[i]);
    }
}

void ProrateDAO::saveProrateData(long prorateId, Prorate::Data data)
{
    char id[20];
    char number[20];
    char amount[30];
    sprintf(id, "%ld", prorateId);
    sprintf(number, "%ld", data.number);
    sprintf(amount, "%0.2f", data.amount);

    string qryString = "INSERT INTO proratedata SET prorate_id=" + string(id) + ", number=" + string(number) + ", amount=" + string(amount) + " ";
    DatabaseManager::defaultManager.query(qryString.c_str());
}


void ProrateDAO::deleteCheckFactory(CheckFactory* checkFactory)
{
    if(checkFactory == NULL)
    {
        return;
    }

    char invId[20];
    sprintf(invId, "%ld", checkFactory->getInvoice().getNumber());
    string qryString = "DELETE FROM proratedata WHERE prorate_id IN (SELECT id FROM prorate WHERE invoice_id=" + string(invId) + ")";
    DatabaseManager::defaultManager.query(qryString.c_str());
    qryString = "DELETE FROM prorate WHERE invoice_id=" + string(invId) + "";
    DatabaseManager::defaultManager.query(qryString.c_str());
    qryString = "DELETE FROM checkfactory WHERE invoice_id=" + string(invId) + "";
    DatabaseManager::defaultManager.query(qryString.c_str());
}
