#include "setupdao.h"
#include "../reports/textinvoice.h"

SetupDAO::SetupDAO()
{
    checkEmptyDB();
}

string SetupDAO::get(string key)
{
    string qryString = "SELECT svalue FROM setup WHERE skey='" + key + "' ";
    QSqlQuery getQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
    string result = "";

    if(getQuery.first()) {
        result = DatabaseManager::valueAs<QString>(getQuery,"svalue").toStdString();
    }
    return result;
}

void SetupDAO::set(string key, string value)
{
    string qryString = "DELETE FROM setup WHERE skey='" + key + "' ";
    DatabaseManager::defaultManager.query(QString::fromStdString(qryString));

    QSqlQuery setupQuery;
    QString setQryString = QString("REPLACE INTO setup SET skey=:skey, svalue=:svalue" );
    DatabaseManager::defaultManager.prepareQuery(setupQuery,setQryString);
    setupQuery.bindValue(":skey"        , QString::fromStdString(key));
    setupQuery.bindValue(":svalue"      , QString::fromStdString(value));

    DatabaseManager::defaultManager.executeQuery(setupQuery);
}

void SetupDAO::del(string key) {
    string qryString = "DELETE FROM setup WHERE skey='" + key + "' ";
    DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
}

void SetupDAO::setBoolean(string key, bool value)
{
    char buf[3];
    sprintf(buf, "%d", int(value));
    set(key, string(buf));
}

vector<string> SetupDAO::get(vector<string> keyList)
{
    vector<string> valueList;
    vector<string>::iterator current;

    for(current = keyList.begin(); current != keyList.end(); current++)
    {
        valueList.push_back(get(*current));
    }

    return valueList;
}

bool SetupDAO::getBoolean(string key, bool defaultValue)
{
    string value = get(key);

    if(value.length() == 0)
    {
        return defaultValue;
    }

    return bool(atol(value.c_str()));
}

void SetupDAO::set(vector<string> keyList, vector<string> valueList)
{
    for(unsigned int i = 0; i < keyList.size(); i++)
    {
        set(keyList[i], (i < valueList.size() ? valueList[i] : ""));
    }
}

string SetupDAO::getMarketInfo()
{
    string result;
    result = get("genMktName");
    result += "  " + get("genMktAddress");
    return result;
}

TextReportHeader SetupDAO::reportHeader(string tableHeading, bool includeDate, string commentKey, bool useActualDate)
{
    string buf;
    buf = get("genMktName");

    TextReportHeader header(get("genMktName"));
    header.addHeaderLine(" ");
    header.addHeaderLine(get("genMktAddress"));
    buf = get("genMktCity") + ", " + get("genMktState") + " " + get("genMktZip");

    if(buf != ",  ")
    {
        header.addHeaderLine(buf);
    }

//    //KLN debug start
//    cout << "TextReportHeader SetupDAO::reportHeader" << endl;
//    cout << "    useActualDate: " << useActualDate << endl;
//    //KLN debug end

    Date repDate;
    if(includeDate) {
        // KLN mod start
        if (useActualDate) {
            repDate = Date::currentDate();
          } else {
            repDate = sale.currentSaleDate();
          }
        // KLN mod end
        header.addHeaderLine(repDate.toString("mm/dd/YYYY"));
        header.addHeaderLine(" ");
      }

    buf = get(commentKey);

    if(buf.length() > 0)
    {
        int nlPos = string::npos;

        do
        {
            nlPos = buf.find_first_of('\n');

            if(nlPos == 0)
            {
                header.addHeaderLine(" ");
                if(buf.length() > 1)
                {
                    buf = buf.substr(1);
                }
                else buf = "";
            }
            else if(nlPos != string::npos)
            {
                header.addHeaderLine(buf.substr(0, nlPos));

                if(buf.length() > nlPos)
                {
                    buf = buf.substr(nlPos + 1);
                }
                else buf = "";
            }
        }
        while(nlPos != string::npos);

        if(buf.length() > 0)
        {
            header.addHeaderLine(buf);
        }
    }

    if(tableHeading != "")
    {
        header.addHeaderLine(tableHeading);
        header.addHeaderLine(string(tableHeading.length(), '-'));
        header.addHeaderLine(" ");
    }

    return header;
}

vector<SetupDAO::DisplayRecord> SetupDAO::getDisplayRecordList()
{
    QString qryString = "SELECT num, type, name, port, `rows`, which, base FROM displays";

    QSqlQuery displayListQuery = DatabaseManager::defaultManager.query(qryString);
    vector<DisplayRecord> recordList;
    DisplayRecord temp;

    while (displayListQuery.next()) {
        long _num    = DatabaseManager::valueAs<long>(displayListQuery,"num");
        int _type    = DatabaseManager::valueAs<int>(displayListQuery,"type");
        string _name = DatabaseManager::valueAs<QString>(displayListQuery,"name").toStdString();
        string _port = DatabaseManager::valueAs<QString>(displayListQuery,"port").toStdString();
        int _rows    = DatabaseManager::valueAs<int>(displayListQuery,"rows");
        int _which   = DatabaseManager::valueAs<int>(displayListQuery,"which");
        int _base    = DatabaseManager::valueAs<int>(displayListQuery,"base");

        temp.num = _num;
        temp.type = _type;
        temp.name = _name;
        temp.port = _port;
        temp.rows = _rows;
        temp.which = _which;
        temp.base = _base;
        temp.rowList = getDispRowsRecordList(temp.num);
        recordList.push_back(temp);
    }
    return recordList;
}

vector<SetupDAO::DispRowsRecord> SetupDAO::getDispRowsRecordList(int num)
{
    QString qryString = QString("SELECT num, row, item, len, rev FROM disprows WHERE num=%1"
                                " ORDER BY ROW").arg(num);

    QSqlQuery dispRowsQuery = DatabaseManager::defaultManager.query(qryString);
    vector<DispRowsRecord> recordList;
    DispRowsRecord temp;

    while (dispRowsQuery.next()) {
        int _row = DatabaseManager::valueAs<int>(dispRowsQuery,"row");
        int _item = DatabaseManager::valueAs<int>(dispRowsQuery,"item");
        int _length = DatabaseManager::valueAs<int>(dispRowsQuery,"len");
        bool _reversed = DatabaseManager::valueAs<bool>(dispRowsQuery,"rev");

        temp.row        = _row;
        temp.item       = _item;
        temp.length     = _length;
        temp.reversed   = _reversed;
        recordList.push_back(temp);
    }
    return recordList;
}

void SetupDAO::deleteDisplay(DisplayRecord record)
{
    char buf[20];
    sprintf(buf, "%d", record.num);
    string qryString = "DELETE FROM displays WHERE num=" + string(buf) + "";
    DatabaseManager::defaultManager.query(qryString.c_str());
    qryString = "DELETE FROM disprows WHERE num=" + string(buf) + "";
    DatabaseManager::defaultManager.query(qryString.c_str());
}

void SetupDAO::saveDisplay(DisplayRecord record)
{
    QSqlQuery saveDisplayQuery;
    QString qryString = QString("REPLACE INTO displays SET num=:num, type=:type,"
                                "name=:name, port=:port, rows=:rows, "
                                "which=:which, base=:base ");
    DatabaseManager::defaultManager.prepareQuery(saveDisplayQuery,qryString);

    saveDisplayQuery.bindValue(":num"   , QVariant::fromValue<long>(record.num));
    saveDisplayQuery.bindValue(":type"  , QVariant::fromValue<long>(record.type));
    saveDisplayQuery.bindValue(":name"  , QString::fromStdString(record.name));
    saveDisplayQuery.bindValue(":port"  , QString::fromStdString(record.port));
    saveDisplayQuery.bindValue(":rows"  , QVariant::fromValue<long>(record.rows));
    saveDisplayQuery.bindValue(":which" , QVariant::fromValue<long>(record.which));
    saveDisplayQuery.bindValue(":base"  , QVariant::fromValue<long>(record.base));

    DatabaseManager::defaultManager.executeQuery(saveDisplayQuery);
    saveDispRowsRecordList(record.num, record.rowList);
}

void SetupDAO::saveDispRowsRecordList(int num, vector<DispRowsRecord> rowList)
{
    char numStr[5], row[5], item[5], length[10], rev[3];
    sprintf(numStr, "%d", num);

    string qryString = "DELETE FROM disprows WHERE num=" + string(numStr) + "";
    DatabaseManager::defaultManager.query(qryString.c_str());

    for(unsigned int i = 0; i < rowList.size(); i++)
    {
        sprintf(row, "%d", rowList[i].row);
        sprintf(item, "%d", rowList[i].item);
        sprintf(length, "%d", rowList[i].length);
        sprintf(rev, "%d", (int)rowList[i].reversed);

        qryString = "REPLACE INTO disprows SET num=" + string(numStr) + ", row=" + string(row) + ", item=" + string(item) + ", len=" + string(length) + ", rev=" + string(rev) + "";
        DatabaseManager::defaultManager.query(qryString.c_str());
    }
}

bool SetupDAO::checkEmptyDB() {

    bool result = false;
    string qryString = "SELECT * FROM setup";
    QSqlQuery getQuery = DatabaseManager::defaultManager.query(QString::fromStdString(qryString));

    if(!getQuery.first()) {
        result = true;
    }
    return result;
}

