// -*- C++ -*-
/***************************************************************************
                          cdbm.h  -  description
                             -------------------
    begin                : Fri Apr 9 2004
    copyright            : (C) 2004 by Al Sargent
    email                : al@digitaldevelopment.net
 ***************************************************************************/

#ifndef _DATABASE_MANAGER_H_
#define _DATABASE_MANAGER_H_

#include <QtSql>
//#include <QtSql/QMYSQLDriver>
//#include <mysql/mysql.h>
//#include <mysql/errmsg.h>

#include <string>
#include <vector>
#define DB_LOCK_WAIT_TIME 0	// time to wait for record lock

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QMutex>
#include "types/sqlexception.h"

using namespace std;

class DatabaseManager
{
public: 
    typedef void (*ErrorCallback)(string);
    static ErrorCallback errorCallback;
    DatabaseManager(QString originator=QString(), QString host="localhost", unsigned port=3306, QString user="root",
                    QString pass="123wet", QString dbse="auction6", QString sock = "" );

    ~DatabaseManager();
    static DatabaseManager defaultManager;

    static int instanceCount;
    static int connectionCount;
    static bool writeDbug;

    QString getHostname();
    QString getUsername();
    QString getPassword();
    QString getDatabasename();
    void open();

    long		get_last_id(QSqlQuery &query);

    string escape_string(string);

    void		set_debug_level(int);
    int           get_debug_level();
    static void set_config_file(QString & fileName);
    static void suppressDisconnect();
    void close();
    void disableDebug();

    QSqlQuery query(QString queryStr);
    void executeQuery(QSqlQuery& query);
    void prepareQuery(QSqlQuery& query,QString & queryString);


    /**
       * \brief Return value for given field name if record exist.
  */
    template<typename T>
    static T valueAs(const QSqlQuery& query,const QString& fieldName)
    {
        int fieldIndex = query.record().indexOf(fieldName);
        // If field doesn't exist out debug message
        //if ( query.isNull(fieldIndex) || (fieldIndex == -1) )
        if (fieldIndex == -1)
        {
            throw CreateSqlException(query,"Unexpected field name: "+ fieldName + "\nQuery:" + query.executedQuery());
        }
        QVariant value = query.value(fieldIndex);
        if (!value.canConvert<T>())
        {
            throw CreateSqlException(query,"Failed to convert:" + value.toString());
        }
        return value.value<T>();
    }
protected:
    QMutex *m_dbMutex;
private: // Private data

    static int	debug_level;
    static QString    m_dbm_cfg_file;
    QString	m_dbm_alt_cfg;


    static bool          disconnectOnExit;
    bool localDebug;

private:
    int		get_numeric_result();
    void		get_dbm_options();
    bool          connected;

    // connections paramaters that may be set by the constructor to override config file

    QString m_hostname;
    unsigned m_portnumb;
    QString m_databaseName;
    QString m_username;
    QString m_password;
    QString m_unixSocket;
    QString m_originator;

    // QT MySQL support;
    QSqlDatabase m_db;

};

#endif // CDBM_H
