#include "animalcodedao.h"

bool AnimalCodeDAO::batchMode = false;

string AnimalCodeDAO::batchColorArray[100];
string AnimalCodeDAO::batchFlawArray[100];
string AnimalCodeDAO::batchSexArray[40];
bool   AnimalCodeDAO::batchPairArray[40];

void AnimalCodeDAO::startBatchMode()
{
    for(unsigned int i = 0; i < 100; i++)
    {
        if(i < 40)
        {
            batchSexArray[i] = "";
        }

        batchFlawArray[i] = "";
        batchColorArray[i] = "";
    }

    batchMode = true;
}

void AnimalCodeDAO::endBatchMode()
{
    batchMode = false;
}

AnimalCodeDAO::AnimalCodeDAO()
{}

AnimalCodeDAO::~AnimalCodeDAO()
{}


void AnimalCodeDAO::saveType(short code, string descrip, bool isPair, CommissionDAO::COLOR_GROUP colorGroup)
{
    saveCode(code, descrip, sex, isPair, colorGroup);
}

void AnimalCodeDAO::saveColor(short code, string descrip)
{
    saveCode(code, descrip, color);
}

void AnimalCodeDAO::saveFlaw(short code, string descrip)
{
    saveCode(code, descrip, flaw);
}


void AnimalCodeDAO::createCode(short code, CodeType type, CommissionDAO::COLOR_GROUP colorGroup)
{
    QString qryString = QString("SELECT code FROM codes WHERE code=%1").arg(code) +
            QString(" AND code_type=%1").arg(type) +
            QString(" AND color_group=%1").arg(colorGroup) + " ";

    QSqlQuery codeQuery = DatabaseManager::defaultManager.query(qryString);

    // Code didn't exist, insert it.
    if ( !codeQuery.first()) {
        QSqlQuery insertQuery;
        qryString = QString("INSERT INTO codes SET code=:code, code_type=:code_type , color_group=:color_group ");
        DatabaseManager::defaultManager.prepareQuery(insertQuery,qryString);
        insertQuery.bindValue(":code",code);
        insertQuery.bindValue(":code_type",type);
        insertQuery.bindValue(":color_group",colorGroup);
        DatabaseManager::defaultManager.executeQuery(insertQuery);
    }
    else {
        return;
    }
}

void AnimalCodeDAO::saveCode(short code, string descrip, CodeType type, bool isPair, CommissionDAO::COLOR_GROUP colorGroup)
{
    createCode(code, type, colorGroup);

    QString qryString = QString("UPDATE codes SET descrip=:descrip, pair=:pair "
                                "WHERE code_type=%1 AND code=%2 AND color_group=%3").arg(type).arg(code).arg(colorGroup);
    QSqlQuery updateCodeQuery;
    DatabaseManager::defaultManager.prepareQuery(updateCodeQuery,qryString);

    updateCodeQuery.bindValue(":descrip",QString::fromStdString(descrip));
    updateCodeQuery.bindValue(":pair",isPair);
    DatabaseManager::defaultManager.executeQuery(updateCodeQuery);
}


string AnimalCodeDAO::getTypeDescrip(short typeCode, CommissionDAO::COLOR_GROUP colorGroup)
{
    string result;

    if(batchMode)
    {
        result = batchSexArray[colorGroup * 10 + typeCode];
    }

    if(result == "")
    {
        QString qryString = QString("SELECT descrip, pair FROM codes where code=%1 "
                                    " AND code_type= %2 AND color_group= %3 ").arg(typeCode).arg(sex).arg(colorGroup) ;

        QSqlQuery typeDescrQuery = DatabaseManager::defaultManager.query(qryString);

        //Query empty, return.
        if(!typeDescrQuery.first())
        {
            batchSexArray[colorGroup * 10 + sex] = " ";
            batchPairArray[colorGroup * 10 + sex] = false;
            return " ";
        }
        result = DatabaseManager::valueAs<QString>(typeDescrQuery,"descrip").toStdString();
        string pairStr = DatabaseManager::valueAs<QString>(typeDescrQuery,"pair").toStdString();
        if(batchMode)
        {
            batchSexArray[colorGroup * 10 + typeCode] = result;
            batchPairArray[colorGroup * 10 + typeCode] = bool(atoi(pairStr.c_str()));
        }
    }

    return result;
}


string AnimalCodeDAO::getColorDescrip(short colorCode)
{
    string result;

    if(batchMode)
    {
        result = batchColorArray[colorCode];
    }

    if(result == "")
    {
        QString qryString = QString("SELECT descrip FROM codes WHERE code=%1 AND code_type=%2 ")
                .arg(colorCode).arg(color);

        QSqlQuery colorDescrQuery = DatabaseManager::defaultManager.query(qryString);

        if(!colorDescrQuery.first())
        {
            batchColorArray[colorCode] = " ";
            return " ";
        }

        result = DatabaseManager::valueAs<QString>(colorDescrQuery,"descrip").toStdString();

        if(batchMode)
        {
            batchColorArray[colorCode] = result;
        }

    }
    return result;
}

string AnimalCodeDAO::getFlawDescrip(short flawCode)
{
    string result;

    if(batchMode) {
        result = batchFlawArray[flawCode];
    }

    if(result == "") {
        QString qryString = QString("SELECT descrip FROM codes WHERE code=%1 AND code_type=%2").arg(flawCode).arg(flaw);

        QSqlQuery flawQuery = DatabaseManager::defaultManager.query(qryString);

        if(!flawQuery.first()) {
            batchFlawArray[flawCode] = " ";
            return " ";
        }
        result = DatabaseManager::valueAs<QString>(flawQuery,"descrip").toStdString();
        if(batchMode)
        {
            batchFlawArray[flawCode] = result;
        }
    }
    return result;
}

string AnimalCodeDAO::getTypeDescrip(AnimalCode code)
{
    return getTypeDescrip(code.getType(), CommissionDAO::getColorGroup(code.getColor()));
}

string AnimalCodeDAO::getColorDescrip(AnimalCode code)
{
    return getColorDescrip(code.getColor());
}

string AnimalCodeDAO::getFlawDescrip(AnimalCode code)
{
    return getFlawDescrip(code.getFlaw());
}


// string AnimalCodeDAO::getDescrip(AnimalCode code)
// {
//   return getDescrip(code.getType(), code.getColor(), code.getFlaw());
// }


// string AnimalCodeDAO::getDescrip(short type, short color, short flaw)
// {
//   return getColorDescrip(color) + "-" + getTypeDescrip(type) + "-" + getFlawDescrip(flaw);
// }

AnimalCode AnimalCodeDAO::getAnimalCode(short type, short color, short flaw)
{
    AnimalCode temp(type, color, flaw);
    CommissionDAO::COLOR_GROUP group = CommissionDAO::getColorGroup(color);
    string typeDescrip, colorDescrip, flawDescrip;
    bool pair;
    if(batchMode)
    {
        typeDescrip = batchSexArray[group * 10 + type];
        pair = batchPairArray[group * 10 + type];
    }

    int colorGroup = CommissionDAO::getColorGroup(color);

    QString queryStr;

    if(typeDescrip == "")
    {
        queryStr = QString("SELECT descrip, pair FROM codes WHERE code=%1 AND code_type=0 AND color_group=%2 ").arg(type).arg(colorGroup);

        QSqlQuery typeDescrQuery = DatabaseManager::defaultManager.query(queryStr);

        if(typeDescrQuery.first())
        {
            typeDescrip = DatabaseManager::valueAs<QString>(typeDescrQuery,"descrip").toStdString();
            pair = DatabaseManager::valueAs<bool>(typeDescrQuery,"pair");

            if(batchMode)
            {
                batchSexArray[group * 10 + type] = typeDescrip;
                batchPairArray[group * 10 + type] = pair;
            }

        }
        else if(batchMode) {
            batchSexArray[group * 10 + type] = " ";
            batchPairArray[group * 10 + type] = false;
        }
    }

    if(batchMode)
    {
        colorDescrip = batchColorArray[color];
    }

    if(colorDescrip == "") {
        queryStr = QString("SELECT descrip FROM codes WHERE code=%1 AND code_type=1 ").arg(color);

        QSqlQuery colorDescrQuery = DatabaseManager::defaultManager.query(queryStr);

        if(colorDescrQuery.first()) {

            colorDescrip = DatabaseManager::valueAs<QString>(colorDescrQuery,"descrip").toStdString();

            if(batchMode) {
                batchColorArray[color] = colorDescrip;
            }
        } else {
            batchColorArray[color] = " ";
        }
    }

    if(batchMode) {
        flawDescrip = batchFlawArray[flaw];
    }

    if(flawDescrip == "") {
        queryStr = QString("SELECT descrip FROM codes WHERE code=%1 AND code_type=2 ").arg(flaw);

        QSqlQuery flawDescrQuesry = DatabaseManager::defaultManager.query(queryStr);

        if(flawDescrQuesry.first()) {
                flawDescrip = DatabaseManager::valueAs<QString>(flawDescrQuesry,"descrip").toStdString();
                batchFlawArray[flaw] = flawDescrip;
        }
        else {
            batchFlawArray[flaw] = " ";
        }
    }

    temp.setTypeDescrip(typeDescrip);
    temp.setIsPair(pair);
    temp.setColorDescrip(colorDescrip);
    temp.setFlawDescrip(flawDescrip);

    /*
  string qryString =
     "SELECT descrip, code_type, pair FROM codes WHERE "
     "code=" + string(typeStr)  + " AND code_type=0 AND color_group=" + string(colorGroup) + " OR "
     "code=" + string(colorStr) + " AND code_type=1 OR "
     "code=" + string(flawStr)  + " AND code_type=2";



  long nfound = DatabaseManager::defaultManager.query(qryString.c_str());
  char **record;
  for(unsigned int i = 0; i < nfound; i++)
  {
    record = DatabaseManager::defaultManager.get_record();
    switch(atoi(record[1]))
    {
    case 0:
      temp.setTypeDescrip(record[0]);
      temp.setIsPair(bool(atoi(record[2])));
      break;
    case 1:
      temp.setColorDescrip(record[0]);
      break;
    case 2:
      temp.setFlawDescrip(record[0]);
      break;
    }
  }
  DatabaseManager::defaultManager.release_result();
*/

    return temp;
}

AnimalCode AnimalCodeDAO::fillAnimalCode(AnimalCode& code)
{
    code = getAnimalCode(code.getType(), code.getColor(), code.getFlaw());
    return code;
}

bool AnimalCodeDAO::isPair(short type)
{
    bool isPair = false;
    QString qryString = QString("SELECT pair FROM codes WHERE code_type=0 AND code=%1 ").arg(type);
    QSqlQuery pairQuery = DatabaseManager::defaultManager.query(qryString);

    if(pairQuery.first())
    {
        isPair = DatabaseManager::valueAs<bool>(pairQuery,"pair");
    }
    return isPair;
}

vector<AnimalCode> AnimalCodeDAO::getCodeList(CommissionDAO::COLOR_GROUP colorGroup)
{
    char cgStr[3];
    sprintf(cgStr, "%d", colorGroup);
    return getAnimalCodeListByCondition("WHERE code_type != 0 OR (code_type=0 AND color_group=" + string(cgStr) + ")");
}

void AnimalCodeDAO::deleteCode(CodeType type, short code, CommissionDAO::COLOR_GROUP group)
{
    char typeStr[10], codeStr[10], cgStr[3];
    sprintf(typeStr, "%d", type);
    sprintf(codeStr, "%d", code);
    sprintf(cgStr, "%d", group);
    string qryString = "DELETE FROM codes WHERE code=" + string(codeStr) + " AND code_type=" + string(typeStr) + " AND color_group=" + string(cgStr) + "";
    DatabaseManager::defaultManager.query(QString::fromStdString(qryString));
}

void AnimalCodeDAO::deleteCodeRow(short codeRow)
{
    QString qryString = QString("DELETE FROM codes WHERE code=%1 ").arg(codeRow);
    DatabaseManager::defaultManager.query(qryString);
}


vector<AnimalCode> AnimalCodeDAO::getAnimalCodeListByCondition(string condStr)
{
    QString qryString = QString("SELECT code, code_type, descrip, pair FROM codes %1  ORDER BY code ASC").arg(QString::fromStdString(condStr));

    vector<AnimalCode> codeList;

    QSqlQuery codeListQuery = DatabaseManager::defaultManager.query(qryString);
    short code;
    string typeDescrip, colorDescrip, flawDescrip;

    CodeType type;
    bool isPair;

    while (codeListQuery.next()) {

        code = DatabaseManager::valueAs<int>(codeListQuery,"code");
        type = CodeType(DatabaseManager::valueAs<int>(codeListQuery,"code_type"));
        isPair = DatabaseManager::valueAs<bool>(codeListQuery,"pair");
        QString description = DatabaseManager::valueAs<QString>(codeListQuery,"descrip");

        typeDescrip = "";
        colorDescrip = "";
        flawDescrip = "";

        bool found;

        switch(type)
        {
        case sex:
            typeDescrip = description.toStdString();
            break;
        case color:
            colorDescrip = description.toStdString();
            break;

        case flaw:
            flawDescrip = description.toStdString();
            break;
        };

        found = false;
        for(unsigned int i = 0; i < codeList.size() && !found; i++)
        {
            if(codeList[i].getType() == code)
            {
                found = true;
                switch(type)
                {
                case sex:
                    codeList[i].setTypeDescrip(typeDescrip);
                    codeList[i].setIsPair(isPair);
                    break;

                case color:
                    codeList[i].setColorDescrip(colorDescrip);

                    break;

                case flaw:
                    codeList[i].setFlawDescrip(flawDescrip);
                    break;
                }
            }
        }
        if(!found)
        {
            codeList.push_back(AnimalCode(code, code, code, typeDescrip, colorDescrip, flawDescrip, isPair));
        }
    }

    return codeList;
}
