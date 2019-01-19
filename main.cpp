/***************************************************************************
 *   Copyright (C) 2006 by Sargent Communications                          *
 *   krws@digitaldevelopment.net                                           *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
/*
 * Copyright (C) 2006 Sargent Communications <krws@digitaldevelopment.net>
 */

#include <QMessageBox>
#include <QMainWindow>
#include <string> 
#include <iostream>
#include<QCoreApplication>
#include<QSqlDatabase>

//[KLN]
//#include "git_revision.h"
#include "globals.h"
//[KLN]

#include "dao/databasemanager.h"

#include "auctionmain.h"
#include "dao/invoicedao.h"
#include "dao/auctiondatabase.h"
#include "ui_auctiondatabasewizard.h"
#include "auctionapp.h"
#include "types/dbug.h"
#include <QtPlugin>

Timer DBug::traceTimer;
ofstream DBug::logFile;


//string DatabaseManager::dbm_cfg_file = "/etc/myauct.conf";
//int DatabaseManager::debug_level = 0;

//DatabaseManager DatabaseManager::defaultManager("defaultManager");
//DatabaseManager InvoiceDAO::listManager("InvoiceDAO::listManager");
//DatabaseManager SetupDAO::listManager("SetupDAO::listManager");
//DatabaseManager CommissionDAO::listManager("CommissionDAO::listManager");
//DatabaseManager TagDAO::listManager("TagDAO::listManager");
//DatabaseManager TransactionDAO::listManager("TransactionDAO::listManager");

#include <string>

#include <sys/stat.h> // [KLN]

using namespace std;

bool commissionDebug = false;
bool invoiceDebug = false;
bool debugPrint = false;


//static const char description[] =
//    I18N_NOOP("A KDE KPart Application");

static const char version[] = "7";
static const char release[] = "01";
static const char fix_release[] = "00";

// static KCmdLineOptions options[] =
// {
//   { "+[URL]", I18N_NOOP( "Document to open" ), 0 },
//   KCmdLineLastOption
// };


void catostrophicErrorCallback(string message)
{
  QMessageBox::critical(NULL, "Error", QString::fromStdString(message));
//  AuctionDatabaseWizard(NULL).exec();
  exit(1);
}

bool logPathExists = false;
QString homeDir = getenv("HOME");
QString logDir = "logs/auction";
QString pathDir = homeDir + "/" + logDir;

void setupLoggingDir() {
  //  cout << "In setupLoggingDir" << endl;
  //  cout << "homeDir: " << homeDir.toStdString() << endl;
  //  cout << " logDir: " << logDir.toStdString() << endl;
  //  cout << "pathDir: " << pathDir.toStdString() << endl;

  struct stat buf;
  stat(pathDir.toLatin1(), &buf);
  if (S_ISDIR(buf.st_mode) ) {
      cout << "Is a directory!" << endl;
      logPathExists = true;
    }
  else { // does not exist
      cout << "is NOT a directory!" << endl;
      const int dir_err = system("mkdir -p " + pathDir);
      if (-1 == dir_err) { cout << "Error creating directory: " << pathDir.toStdString() << "!" << endl;
        }
    }
}

QString fileName =QString("auction_log_%1_%2.txt").arg(QDateTime::currentDateTime().toString("MM_dd_yyyy")).arg(QDateTime::currentMSecsSinceEpoch());
QFile file( pathDir + "/" + fileName );
bool isNeedLogging = false;

void LogMessageOutput(QtMsgType type, const char *msg)
{
  if (!isNeedLogging) {
      return;
    }
  if (!logPathExists ) {
      setupLoggingDir();
    }

  if (! file.isOpen()) {
      file.open(QIODevice::ReadWrite);
    }
  else {
      QTextStream stream( &file );
      switch (type) {
        case QtDebugMsg:
          stream << "Debug: "<< QDateTime::currentDateTime().toString("MM-dd-yy hh:mm:ss:zzz ") << msg << endl;
          break;
        case QtWarningMsg:
          stream << "Warning:" << QDateTime::currentDateTime().toString("MM-dd-yy hh:mm:ss:zzz ") << msg << endl;
          break;
        case QtCriticalMsg:
          stream << "Critical:" << QDateTime::currentDateTime().toString("MM-dd-yy hh:mm:ss:zzz ") <<  msg << endl;
          break;
        case QtFatalMsg:
          stream << "Fatal:" << QDateTime::currentDateTime().toString("MM-dd-yy hh:mm:ss:zzz ") << msg << endl;
        }
    }
}


//Q_IMPORT_PLUGIN(qsqlmysql)
int main(int argc, char **argv)
{
//  Q_INIT_RESOURCE(icons); // [KLN] moved from transactiondialog.cpp
//  Q_INIT_RESOURCE(fonts); // [KLN] add

    qInstallMsgHandler(LogMessageOutput); //install : set the callback
  // Turn on debug of sql statements. Use this method because KCmdLineArgs is
  // not initialized when we need to init logging.
//   for ( int iargs=1; iargs<argc; iargs++ )	{
// 	if (strcmp(argv[iargs],"-d") == 0 )	{
// 		DatabaseManager::writeDbug = true;
// 		cout << "turned writeDbug on" << endl;
// 		break;
// 	}
//   }


    string actualVersion = string(version) + "." + release + "." + fix_release;
    QByteArray QBA_actualVersion(actualVersion.c_str(), actualVersion.length());


//    KAboutData about("auction", I18N_NOOP("auction"), ki18n("auction"), QBA_actualVersion, ki18n(description),
//                     KAboutData::License_GPL, ki18n("(C) 2006 Sargent Communications"), ki18n(""), 0, "krws@digitaldevelopment.net");

//    KCmdLineArgs::init(argc, argv, &about);
  
//    KCmdLineOptions options; //new
//    options.add("+[file]", ki18n("Document to open")); //new
//    KCmdLineArgs::addCmdLineOptions(options); //new
 
//    KApplication app;



    AuctionApp app(argc, argv);

    if (DatabaseManager::writeDbug) {DBug::initLogFile();}
    DatabaseManager::defaultManager.errorCallback = catostrophicErrorCallback;

    DatabaseManager::defaultManager.set_debug_level(0);

    app.setFont(QFont("Bitstream Vera Sans", 13), true);

    QStringList appArguments = app.arguments();
    int status = 1;
    /*
     * We need this enabled for Cottonwood's annual Consignment sales
     */
    //
    QString configFile;
    int argumentsSize = appArguments.size();
    for (int i = 0; i< argumentsSize; i++) {
        if ( (appArguments[i].trimmed() == "-c") && (i < (argumentsSize-1)) ) {
            // Arguments written without quotes, -c filename.
            // In that case -c is separate argument, and filename is in the next memeber.
            configFile = appArguments[i+1].trimmed();
            break;
        }
        else if (appArguments[i].trimmed().contains("-c")) {
            //Arguments written with quotes "-c filename"
            configFile= appArguments[i].trimmed().right(appArguments[i].trimmed().size()-3).trimmed();
            break;
        }
        else if (appArguments[i].trimmed() == "-l") {
            isNeedLogging = true;
        }
        else if (appArguments[i].trimmed() == "-d") {
            debugPrint = true;
        }
        else if (appArguments[i].trimmed() == "-o") {
            commissionDebug = true;
        }
        else if (appArguments[i].trimmed() == "-i") {
            invoiceDebug = true;
        }
        else if (appArguments[i].trimmed() == "-h") {
            std::cout << "Commandline Options for the Auction program:\n"
                         "-c filename -- pass a different database config file\n"
                         "-l -- turn on logging (in $HOME/logs/auction)\n"
                         "-d -- turn on general debug prints\n"
                         "-o -- turn on commission debug prints\n"
                         "-i -- turn on invoice debug prints\n"
                         "-h -- this help screen\n";
            exit(1);
        }
    }
    if( !configFile.isEmpty() ) {
       DatabaseManager::set_config_file(configFile);
       resetConnections();
     }

    AuctionMain w;

    // Get current git pseudo-revision for title bar
    QString revision;
    revision = QString::fromStdString("ASDSAD");
    QString curRev = QString(" (r") + revision + QString(") ");

    QString builtTime = curRev + QString(" Built:") + QString::fromStdString(__DATE__) + " " +QString::fromStdString( __TIME__);
//    qDebug("setCaption");
    w.setCaption(QString("Sale Day Auction Market System By Sargent Communications. V ").append(QBA_actualVersion).append(builtTime));
    w.show();

    //app.setMainWidget( w );

//    args->clear();

    status = app.exec();

    // make sure to delete main win so that the destructor is called.
    return status;
}

