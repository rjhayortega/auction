#ifndef SQLEXCEPTION_H
#define SQLEXCEPTION_H

#include "appexception.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

class SqlException : public AppException
{

/**
 * \brief An exception class derived from AppException.
 *
 * The Details() will be filled with the QSqlError error message
 * returned by the QSqlDatabase or QSqlQuery.
 */
public:
    /**
     * \brief Constructor. Do not use directly; use CreateSqlException instead.
     */
    SqlException(const QSqlDatabase& database, QString file, long line, QString msg);

    /**
     * \brief Constructor. Do not use directly; use CreateSqlException instead.
     */
    SqlException(const QSqlQuery& query, QString file, long line, QString msg);

private:
    /**
     * \brief Convert a QSqlQuery to a human readable error message.
     *
     * Note: the resulting QString is not internationalized!
     */
    static QString getDetails(const QSqlQuery& query);

    /**
     * \brief Convert a QSqlError to a human readable error message.
     *
     * Note: the resulting QString is not internationalized!
     */
    static QString getDetails(const QSqlError& query);

};

/**
 * \brief Macro for easy throwing.
 *
 * The CreateSqlException macro adds __FILE__ and __LINE__ arguments
 * to the constructor of SqlException.
 *
 * Usage: throw CreateSqlException(database, "Something went wrong");
 */
#define CreateSqlException(cause,msg) SqlException(cause, __FILE__, __LINE__, msg)

#endif // SQLEXCEPTION_H
