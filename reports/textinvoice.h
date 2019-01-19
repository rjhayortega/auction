
#ifndef _TEXT_INVOICE_H_
#define _TEXT_INVOICE_H_

#include "../types/invoice.h"
#include "../types/buyerinvoice.h"
#include "textreport.h"
#include "textcheck.h"
#include "../types/check.h"
#include <QTextDocument>
#include <QTextTable>
#include <QVector>
#include <QTextLength>
#include <QTextCursor>

#include <vector>
#include <string>

using namespace std;


class TextInvoice : public TextReport
{
public:
  typedef enum {IgnoreCol=-1} SPECIAL;
  typedef enum columns
  {
    TransNo     = 0,
    Head        = 1,
    Descrip     = 2,
    CustomerNo  = 3,
    Tags        = 4,
    TotWt       = 5,
    AvgWt       = 6,
    DolPerHd    = 7,
    DolPerCW    = 8,
    Amount      = 9,
    Pen         = 10,
    ColumnCount = 11
  }COLUMNS;

  TextInvoice(Invoice* =NULL, int=0, unsigned int=120, bool=false, bool=false);
  virtual ~TextInvoice();
  void setShowNames(bool);
  bool showNames();
  void setShowId(bool);
  void setInvoice(Invoice*);
  void setSkipLines(int);

  void setFooterText(string);

  string invoiceReportText();

  void setTransColumns(int, int, int, 
                       int, int, int, 
                       int, int, int, 
                       int, int);

/*   void setTransColumns(COLUMNS=None,COLUMNS=None,COLUMNS=None, */
/* 		       COLUMNS=None,COLUMNS=None,COLUMNS=None, */
/* 		       COLUMNS=None,COLUMNS=None,COLUMNS=None, */
/* 		       COLUMNS=None,COLUMNS=None,COLUMNS=None); */

  void setTransColumns(vector<int>);
  void setProrateList(vector<Check>, vector<double>);
  void setShowBrand(bool);
  void setShowTransactionComments(bool);
  void setMinimumHeaderSize(int);
  int minimumHeaderSize();

  void setTransFit(int, int);
  QTextDocument* invoiceTextDocument();
  QTextDocument* loadoutTextDocument();
  string formatName(string);

protected:
  Invoice *invoice;
  TextReportTable totalTable();
  virtual double totalValue();
  virtual string customerLabel();
  virtual string customerNum(Transaction);
  virtual string mortgageString();
  virtual string customerString();
  virtual string customerName(Transaction);
  virtual string statusString();
  vector<Check> checkList;
  vector<double> chargeShareList;
  virtual TextReportTable prorateTable();
  virtual string companyString();
  virtual void updateSummaryCoords(unsigned int&, unsigned int&, TextReportTable&);
  virtual void initSummaryCoords(unsigned int&, unsigned int&);
  virtual void noSaleTable();
  virtual long invoiceWeight();
  virtual long invoiceAverageWeight();
  virtual string summaryChargeTotalLabel();
  virtual string summaryTotalLabel();
  virtual long summaryHead();
  bool showSexSummary;
  bool showId;
  bool showTransactionComments;
  virtual TextReportTable footerTable();
  virtual void sexSummaryLine(TextReportTable& summary, unsigned int& row);
  virtual void overallAverageLine(TextReportTable&, unsigned int&);
  virtual bool doShowSexSummary();
  virtual TextReportTable pageHeader();

  virtual TextReportTable getTagsTable();
  virtual TextReportTable createDisclaimerTable();

  bool isBuyerInvoice;
  bool showTags;
// ================ Additions for laser printer support
  virtual void createNoSaleTable(QTextTable *noSaleTable);
  virtual void createProrateTable(QTextTable *proRateTable);
  virtual void createSummaryTable(QTextTable *summaryTable, bool isLoadout = false);
  void setCellText(QTextTable *textTable, int row, int col, string text, bool span = false, Qt::Alignment alignment = Qt::AlignRight);
  void setCellText(QTextTable* textTable, int row, int col,string text,bool span,int endSpanCol,Qt::Alignment alignment);
  virtual void updateSummaryCoords(unsigned int& row, unsigned int& col, unsigned int & appendRows);
  void sexSummaryLine(QTextTable* summaryTable, unsigned int& row);
  virtual void initSummaryCoordsLaser(unsigned int& row, unsigned int& col);
  virtual void overallAverageLine(QTextTable * summaryTable, unsigned int& row);
  virtual QVector<QTextLength> summaryTableColumnsConstraints();
  virtual void createDisclaimerTable(QTextCursor &cursor);

  void setTransCellImage(QTextTable *textTable, int row, int col, QImage image, bool span = false, Qt::Alignment alignment= Qt::AlignLeft);

private:
  TextReportTable transactionTable(bool isLoadout = false);
  TextReportTable getInvoiceTable();
  virtual TextReportTable summaryTable();
  virtual string getPen(Transaction);

  void initTransColWeights();
  TextCheck check;
  int getTagCount();
  bool inBounds(COLUMNS, int, int);
  int getMaxTransCol();
  int getMinTransCol();
  void setTransItem(TextReportTable&,unsigned int, int, string, int=0);
  int skipLines;

  int getTransLineCount(int, TextReportTable&);
  bool doShowNames;
  int transactionColumns[ColumnCount];
  TextReportItem::ALIGNMENT transactionAlignments[13];

  unsigned int transColWeight[ColumnCount];
  double transColWeightPrc[ColumnCount] ;

  int transColCount;
  int remainingTransCols;
  unsigned int transColWidth(COLUMNS);
  void initTransactionAlignments();
  void initTransactionTableHeader(TextReportTable&, int, int);
  string footerString;
  bool showBrand;
  bool groupChargesByName;
  int _minimumHeaderSize;

  int transFitColumns;
  int transFitLength;

  //================ Additions for laser printer support
  void setTransCellText(QTextTable *textTable, int row, int col, string text, bool span = false,Qt::Alignment alignment = Qt::AlignRight,int fontSize = 10);
  void createMarketInfoTable(QTextTable * marketInfoTable);
  void createCustomerInfoTable(QTextTable * customerInfoTable );
  void createTransactionTable(QTextTable * transactionTable , bool isLoadout = false);
  void createTagsTable(QTextTable *tagsTable);
  void createFooterTable(QTextTable *footerTable);
  void initTransactionTableHeader(QTextTable *transTable, int colCount);

  void initTransColWeightsPercents();
  void setCellTextAlignment(QTextTable* textTable, int row, int col,Qt::Alignment alignment);


  QTextDocument m_invoiceDoc;
  QTextDocument m_loadOutDoc;
};




#endif
