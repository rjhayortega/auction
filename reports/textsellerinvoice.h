#ifndef TEXTSELLERINVOICE_H
#define TEXTSELLERINVOICE_H
#include "textinvoice.h"
#include <QStringList>

class TextSellerInvoice : public TextInvoice
{
public:
  TextSellerInvoice(Invoice* =NULL, int=0, unsigned int=120,bool=false, bool=false);
  virtual ~TextSellerInvoice();
  virtual string getPen(Transaction);

protected:
  virtual string customerNum(Transaction);
  virtual string customerLabel();
  virtual string mortgageString();
  virtual string customerString();
  virtual string customerName(Transaction);
  virtual TextReportTable prorateTable();
  virtual void updateSummaryCoords(unsigned int&, unsigned int&, TextReportTable&);
  virtual void initSummaryCoords(unsigned int&, unsigned int&);
  virtual string summaryChargeTotalLabel();
  virtual string summaryTotalLabel();
  virtual long invoiceWeight();
  virtual long invoiceAverageWeight();
  virtual bool doShowSexSummary();
  virtual TextReportTable pageHeader();
  virtual TextReportTable createDisclaimerTable();

// ------ Laser printer support
  virtual void updateSummaryCoords(unsigned int&, unsigned int&, unsigned int &appendRows);
  virtual QVector<QTextLength> summaryTableColumnsConstraints();
  virtual void createProrateTable(QTextTable *proRateTable);

  virtual void createDisclaimerTable(QTextCursor &cursor);


  QStringList getDisclaimerLines();
private:
};

#endif // TEXTSELLERINVOICE_H
