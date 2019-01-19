// -*- C++ -*-
/***************************************************************************
                          cdbm.cpp  -  description
                             -------------------
    begin                : Fri Apr 9 2004
    copyright            : (C) 2004 by Al Sargent
    email                : al@digitaldevelopment.net
***************************************************************************/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <stdlib.h>
#include "dbug.h"

#include "databasemanager.h"

//#include <QtSql>
#include <mysql.h>

#include <limits.h>
#include <dirent.h>
#include <fnmatch.h>
#include <unistd.h>
#include <QSettings>
#include <QDebug>
#include <QMutexLocker>

int DatabaseManager::instanceCount = 0;
int DatabaseManager::connectionCount = 0;
bool DatabaseManager::disconnectOnExit = true;
DatabaseManager::ErrorCallback DatabaseManager::errorCallback = NULL;
bool DatabaseManager::writeDbug = false;	// control for DBug write on/off


void DatabaseManager::suppressDisconnect()
{
    disconnectOnExit = false;
}

void DatabaseManager::disableDebug()
{
    this->localDebug = false;
}

QString DatabaseManager::getHostname()
{
    return m_hostname;
}

QString DatabaseManager::getUsername()
{
    return m_username;
}

QString DatabaseManager::getPassword()
{
    return m_password;
}

QString DatabaseManager::getDatabasename()
{
    return m_databaseName;
}

void DatabaseManager::set_config_file(QString &fileName)
{
    DatabaseManager::m_dbm_cfg_file = fileName;
}

////////////////////////////////////////////////////////////////////////
//
// default constructor
//
// initialize database engine here
//
DatabaseManager::DatabaseManager(QString originator, QString host, unsigned port, QString user,
                                 QString pass, QString dbse, QString sock)
{
    m_hostname = host;
    m_portnumb = port;
    m_username = user;
    m_password = pass;
    m_databaseName = dbse;
    m_unixSocket = sock;
    m_originator = originator;

	m_hostname = "localhost";
    m_portnumb = 3306;
    m_username = "root";
    m_password = "123wet";

    connected = false;
    localDebug = true;
    m_dbMutex = new QMutex();

#ifdef DATABASE_MANAGER_DEBUG_CONNECT
    QDebug() << "Connecting for: " << originator << "\n";
#endif
    m_dbm_alt_cfg = QString(getenv("HOME")) + QString("/.config/auction/myauct.conf");

#ifdef DATABASE_MANAGER_DEBUG_CONNECT
    QDebug() << "Connect success: Open connections: <" << instanceCount << ">, Connections since start: <" << connectionCount << ">" << "\n";
#endif
}

void DatabaseManager::open()
{
    m_db = QSqlDatabase::addDatabase("QMYSQL","m_db_connect");
    // retrieve connection parameters
    get_dbm_options();

    m_db.setHostName(m_hostname);
    m_db.setPort(m_portnumb);
    m_db.setDatabaseName(m_databaseName);
    m_db.setUserName(m_username);
    m_db.setPassword(m_password);
    m_db.setConnectOptions(QString("UNIX_SOCKET=%1").arg(m_unixSocket));

    const bool ok = m_db.open();

    if( !ok )
    {
        cout << errorCallback << endl;
        if(errorCallback != NULL)
        {
            errorCallback("Could not initilize the database interface, \n"
                          "for the Sargent Communications Auction Market\n"
                          "software, check that the mysql server is running.\n"
                          "If the mysql server is running but is on a\n"
                          "seperate computer, check the physical connection.\n"
                          " Error reported:" + m_db.lastError().text().toStdString() );
        }
    } else {
        connected = true;
        // diagnostic routines
        if( (DatabaseManager::debug_level >= 1 && localDebug) /* || (DBUG_LVL) */ )
        {
            qDebug() << "Connected to server on " << m_hostname
                     << " using " << m_databaseName << "\n";
        }
        instanceCount++;
        connectionCount++;
    }
}

////////////////////////////////////////////////////////////////////////
//
// destructor
//
DatabaseManager::~DatabaseManager()
{ 
    if(disconnectOnExit)
    {
#ifdef DATABASE_MANAGER_DEBUG_CONNECT
        qDebug() << "Open Connections: <" << instanceCount << ">" << "\n";
#endif
        close();
    }
    delete m_dbMutex;
}

void DatabaseManager::close()
{
    connected = false;
    instanceCount--;
    m_db.close();
}

////////////////////////////////////////////////////////////////////////
//
// database query
//
// input parameter: ascii text string for query
//
// returns: QSqlQuery
//
QSqlQuery DatabaseManager::query(QString queryStr)
{
    QMutexLocker locker(m_dbMutex);
    if (!connected) {
        open();
    }
    QSqlQuery query(m_db);
    query.setForwardOnly(true);

    const bool ok = query.exec(queryStr);
    //Debug queries
    if(DatabaseManager::debug_level > 0 && localDebug) {
        QString msg = query.lastQuery();
        QMapIterator<QString, QVariant> i(query.boundValues());
        while (i.hasNext()) {
            i.next();
            msg += "\n  - " + i.key() + ": " + i.value().toString();
        }

        if (!ok) msg += "\n--- FAILED!";

        qDebug() << msg;
    }
    if (!ok) {
//        // [KLN] debug start
//        string dbgQry = queryStr.toStdString();
//        cout << "In DatabaseManager::query" << endl;
//        cout << "  queryStr: " << dbgQry << endl;
//        // [KLN] debug end
        throw CreateSqlException(query, "Query failed:" + queryStr);
    }
    return query;
}

//#define DEBUG_QUERIES

////////////////////////////////////////////////////////////////////////
//
// Execute database query
//
// input parameter: QSqlQuery. Used in caller side with binded parameters.
//
// returns: void
//
void DatabaseManager::executeQuery(QSqlQuery& query)
{
    QMutexLocker locker(m_dbMutex);
    if (!connected) {
        open();
    }
    const bool ok = query.exec();

#ifdef DEBUG_QUERIES
    qDebug() << query.executedQuery();
    if (!ok)	qDebug() << ">> FAILED";
#endif // DEBUG_QUERIES

    if (!ok)
    {
        throw CreateSqlException(query, "Query couldn't exec.\n Query:" + query.executedQuery()+
                                 "\n Reason:" +query.lastError().text());
    }
}

////////////////////////////////////////////////////////////////////////
//
// get_dbm_options: read database options from system-wide or per-user file
// and store it in the class members;
// 
// calling parms: 
// return value:  none
// 
// See documentation for 'mysql_real_connect() for more information
//
void DatabaseManager::get_dbm_options()
{
    QString cfgFileName = DatabaseManager::m_dbm_cfg_file;
    QFile cfgFile(cfgFileName);
    if( !cfgFile.exists() )  // failed
    {
        cfgFileName = m_dbm_alt_cfg;
        cfgFile.setName(cfgFileName);
        if(!cfgFile.exists())	// failed also
        {
            return;				// just use builtin defaults
        }
    }

    QSettings settings(cfgFileName,QSettings::IniFormat);
    settings.beginGroup("MySQL");
    m_hostname       = settings.value("host", "localhost").toString();
    m_portnumb       = settings.value("port", 3306).toUInt();
    m_databaseName   = settings.value("database", "auction6").toString();
    m_username       = settings.value("username", "auction").toString();
    m_password       = settings.value("password", "auction").toString();
    m_unixSocket     = settings.value("socket", "/var/run/mysql/mysql.sock").toString();
    settings.endGroup();
}

////////////////////////////////////////////////////////////////////////
//
// name:		DatabaseManager::get_last_id
//
// purpose:		returns serial number of last database insert
//
// calling parms:	none
//
// return parms:	long		- last serial number
//
// NOTES:
//   * a little uncomfortable about this, verify always unique
//
// TODO:
//
////////////////////////////////////////////////////////////////////////
long DatabaseManager::get_last_id(QSqlQuery & query)
{
    return(query.lastInsertId().value<long>());
}


 void DatabaseManager::prepareQuery(QSqlQuery& query,QString & queryString)
 {
     QMutexLocker locker(m_dbMutex);
     if (!connected) {
         open();
     }
     query.prepare(queryString);
 }

////////////////////////////////////////////////////////////////////////
//
// name:		DatabaseManager::set_debug_level
//
// purpose:		sets error reporting verbosity
//
// calling parms:	int	dbg_lvl		- how verbose to be
//
// return parms:	none
//
// NOTES:
//
// TODO:
//
////////////////////////////////////////////////////////////////////////
void DatabaseManager::set_debug_level(int dbg_lvl)
{
    DatabaseManager::debug_level = dbg_lvl;
}

int DatabaseManager::get_debug_level()
{
    return DatabaseManager::debug_level;
}

//////////////////////////////////////////////////////////
//  Generate an escaped string that Mysql can use
//
string DatabaseManager::escape_string(string src)
{
    char dest[(src.length() * 2) + 1];
    //mysql_real_escape_string(sock, dest, src.c_str(), src.size());
//    return string(dest);
    return src;
}

/*
  ;;; Local Variables: ***
  ;;; mode:c++ ***
  ;;; c-indentation-style:"bsd" ***
  ;;; comment-column:40 ***
  ;;; comment-start: "// "  ***
  ;;; comment-end:"" ***
  ;;; End: ***
*/
