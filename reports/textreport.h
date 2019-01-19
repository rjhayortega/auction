
#ifndef _TEXT_REPORT_H_
#define _TEXT_REPORT_H_

#include <deque>
#include <vector>
#include <string>
#include <iostream>
#include "math.h"

using namespace std;
#define MAX_TABLE_COLS 80

class TextReportItem
{
public:
typedef enum alignment
{
  LEFT,
  CENTER,
  RIGHT 
}ALIGNMENT;

  TextReportItem();
  string fillString(char,int);

protected:
  string reAlign(string, ALIGNMENT, unsigned int);
};

class TextReportHeader : public TextReportItem
{
public:
  TextReportHeader(string="");
  void addHeaderLine(string);
  string toString(int, ALIGNMENT);
  unsigned int size();
  deque<string> paginatedText(unsigned int, string*, double*);

private:
  deque<string> headerLines;
};


////////////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////////////

class TextReportTable : public TextReportItem
{
public:
  typedef enum
  {
    APPEND_LEFT,
    APPEND_RIGHT,
    APPEND_TOP,
    APPEND_BOTTOM
  }APPEND_DIR;

  typedef enum
  {
    Broken,
    Continuous,
    BrokenContinuous,
    ContinuousBroken,
    NoHeader,
    Shadow
  }HEADER_STYLE;

  TextReportTable(int=1);
  TextReportTable(const TextReportTable&);
  virtual ~TextReportTable();
  void setColumnWidth(unsigned int, int);
  void setColumnAlignment(unsigned int, ALIGNMENT);

  string text(int, int);
  void setHeader(unsigned int, string);
  void setFooter(unsigned int, string, bool=false);
  void setFooter(unsigned int, double, bool=false);
  void setFooter(unsigned int, long, bool=false);

  void setText(unsigned int, unsigned int, string, bool span=false, bool=true);
  void setText(unsigned int, unsigned int, double);
  void setText(unsigned int, unsigned int, long);
  void setText(unsigned int, unsigned int, int);
  void insertRows(int);
  void adjustWidth(int);
  void setHeaderSeperator(char, char='-');
  void setFooterSeperator(char, char='-');
  void setFooterStyle(HEADER_STYLE, HEADER_STYLE);
  void setHeaderStyle(HEADER_STYLE, HEADER_STYLE);
  int numRows();

  virtual string headerString(char='-', char='-');
  virtual string footerString(char='=', char='-');

  void appendTable(TextReportTable, APPEND_DIR);
  deque<string>paginatedText(unsigned int,string*,double*, TextReportTable=TextReportTable());
  string toString();
  int columnWidth(unsigned int);
  void setSurroundingText(string, string);
  void setPlainText(unsigned int, string);
  void appendPlainText(unsigned int, string);
  void setPlainTextLineCount(unsigned int, double);
  void increasePlainTextLineCount(unsigned int, double);
  vector<double> getPlainTextLineCount(unsigned int);
  void retroFitColumns(int, int);

private:
  unsigned int numCols;
  string tableRow(unsigned int);
  int columnWidths[MAX_TABLE_COLS];
  ALIGNMENT columnAlignments[MAX_TABLE_COLS];

  deque<string> tableHeader;
  deque<string> tableBody;
  deque<string> tableFooter;
  deque< deque<string> > plainText;
  vector< vector<double> > plainTextLineCount;

  char headerTopSep;
  char headerBotSep;
  char footerTopSep;
  char footerBotSep;

  HEADER_STYLE topHeaderStyle;
  HEADER_STYLE botHeaderStyle;
  HEADER_STYLE topFooterStyle;
  HEADER_STYLE botFooterStyle;

  TextReportTable normalizeHeight(TextReportTable);
  TextReportTable normalizeWidth(TextReportTable);
  string sepStringPart(unsigned int, HEADER_STYLE, char, unsigned int);
  string preText;
  string postText;
};


////////////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////////////


class TextReport
{
public:
  TextReport(unsigned int pageHeight=120);
  TextReport(TextReportHeader, TextReportTable);
  TextReport(TextReportHeader, TextReportTable, TextReportTable);
  virtual ~TextReport();
  void setHeader(TextReportHeader);
  void setPageHeader(TextReportTable);
  void addTable(TextReportTable, bool isLoadout = false);
  void addSummary(TextReportTable);
  void clearTables(bool isLoadout = false);
  virtual string text();
  virtual string loadoutText();
  void setPageLength(unsigned int=80);
  deque<string> paginatedText(unsigned int=0, bool isLoadout = false);
protected:
    string headerText();
private:
  unsigned int pageHeight;
  int numTables;
  TextReportHeader header;
  TextReportTable pageHeader;
  deque<TextReportTable>   tableList;
  deque<TextReportTable> summaryList;

  deque<TextReportTable>   m_loadOutTableList;

};
#endif
