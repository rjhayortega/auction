#ifndef AUCTIONAPP_H
#define AUCTIONAPP_H

#include <QApplication>
#include "types/sqlexception.h"

class AuctionApp : public QApplication
{
    Q_OBJECT
public:
    explicit AuctionApp(int& argc, char* argv[]);
    bool notify(QObject* receiver, QEvent* event);
private:
    void reportException(const SqlException &ex) const;
    void reportException(QString msg);

};

#endif // AUCTIONAPP_H
