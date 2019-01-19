#include "auctionapp.h"
#include <QMessageBox>
#include <QString>
#include <QPlastiqueStyle>
#include <QDateTime>
#include <QFile>

AuctionApp::AuctionApp(int& argc, char* argv[]) :
    QApplication(argc,argv)
{
    setStyle(new QPlastiqueStyle);
}


bool AuctionApp::notify(QObject* receiver, QEvent* event)
{
    try
    {
        return QApplication::notify(receiver, event);
    }
    catch(const SqlException& ex)
    {
        reportException(ex);
        return false;
    }
    catch(const std::exception& ex)
    {
        reportException(ex.what());
        return false;
    }
    catch(const QString& ex)
    {
        reportException(ex);
        return false;
    }
    catch(const char* ex)
    {
        reportException(ex);
        return false;
    }

    catch(...)
    {
        reportException("Unrecognized exception - aborting !");
        std::exit(EXIT_FAILURE); // Crash ASAP
        return false;
    }

}


void AuctionApp::reportException(const SqlException &ex) const
{
    QString msg = QString("Exception: %0 \n %1 \n %2 \n %3 \n %4").arg(ex.getMsg())
            .arg(ex.getType()).arg(ex.getFile()).arg(ex.getLine()).arg(ex.getExceptionDetails());
    QMessageBox::information(0,"Error",msg);
}

void AuctionApp::reportException(QString msg)
{
    QMessageBox::information(0,"Error",msg);
}



