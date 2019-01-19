#ifndef TEXTBUYERINVOICE_H
#define TEXTBUYERINVOICE_H
#include "textinvoice.h"

class TextBuyerInvoice : public TextInvoice
{
public:
  TextBuyerInvoice(Invoice* =NULL, int=0, unsigned int=120, bool=false, bool=false, bool=false, bool=false);
  virtual string getPen(Transaction);

protected:
  virtual string customerNum(Transaction);
  virtual string customerLabel();
  virtual string customerString();
  virtual string customerName(Transaction);
  virtual string statusString();
  virtual string companyString();
  virtual void noSaleTable();
  virtual void updateSummaryCoords(unsigned int& row, unsigned int& col, TextReportTable& summary);
  virtual void initSummaryCoords(unsigned int&, unsigned int&);
  virtual long summaryHead();
  virtual string summaryChargeTotalLabel();
  virtual string summaryTotalLabel();
  virtual void overallAverageLine(TextReportTable&, unsigned int&);
  virtual bool doShowSexSummary();
  virtual TextReportTable pageHeader();
  virtual long invoiceWeight();
  virtual long invoiceAverageWeight();
// ------ Laser printer support
  virtual void createNoSaleTable(QTextTable * noSaleTable);
  virtual void updateSummaryCoords(unsigned int&, unsigned int&, unsigned int &appendRows);
  virtual void initSummaryCoordsLaser(unsigned int& row, unsigned int& col);
  virtual void overallAverageLine(QTextTable * summaryTable, unsigned int& row);
private:
  bool m_averageOnLeft;
  bool totalNoSale;
};

#endif // TEXTBUYERINVOICE_H
