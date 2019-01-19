#ifndef _AUCTION_DATABASE_H_
#define _AUCTION_DATABASE_H_

#include "databasemanager.h"
#include "invoicedao.h"
#include "setupdao.h"
#include "commissiondao.h"
#include "tagdao.h"
#include "transactiondao.h"
#include "proratedao.h"
#include <qmessagebox.h>
#include <QString>

QString DatabaseManager::m_dbm_cfg_file = QString("/etc/myauct.conf");
int DatabaseManager::debug_level = 0;

DatabaseManager DatabaseManager::defaultManager("defaultManager");


void resetConnections()
{
  DatabaseManager::defaultManager.close();
  DatabaseManager::defaultManager.open();

}

#endif
