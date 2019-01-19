#include "sqlexception.h"
#include <QSqlError>

SqlException::SqlException(const QSqlDatabase& database, QString file, long line, QString msg)
    : AppException(file, line, msg, "SqlException", getDetails(database.lastError()))
{

}

SqlException::SqlException(const QSqlQuery& query, QString file, long line, QString msg)
    : AppException(file, line, msg, "SqlException", getDetails(query))
{

}

QString SqlException::getDetails(const QSqlQuery& query)
{
    QSqlError error = query.lastError();

    if (!error.isValid())
    {
        return "No Error";
    }

    QString dbError = error.databaseText();
    QString driverError = error.driverText();

    QString result = "An error occurred during execution of the query: " + query.lastQuery() + "\n\nError: ";

    result += dbError;

    if (!driverError.isEmpty())
    {
        result += "\n" + driverError;
    }

    return result;
}

QString SqlException::getDetails(const QSqlError& error)
{
    if (!error.isValid())
    {
        return "No Error";
    }

    QString dbError = error.databaseText();
    QString driverError = error.driverText();

    QString result = dbError;
    if (!driverError.isEmpty())
    {
        result += "\n" + driverError;
    }

    return result;
}

