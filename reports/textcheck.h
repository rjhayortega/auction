
#ifndef _TEXT_CHECK_H_
#define _TEXT_CHECK_H_

#include <vector>
#include <string>
#include <algorithm>
#include "../types/check.h"
#include "../okiml320image.h"
#include "../types/invoice.h"
#include "../dao/setupdao.h"

#define OOB_CHECK 81

using namespace std;

class CheckItemCoord
{
public:
  CheckItemCoord(unsigned int=0, unsigned int=80);

  bool operator==(CheckItemCoord);
  bool operator< (CheckItemCoord)const;
  unsigned int getRow();
  unsigned int getCol();
  void setRow(unsigned int);
  void setCol(unsigned int);
  friend ostream& operator<<(ostream&, CheckItemCoord&);
private:
  unsigned int row;
  unsigned int col;
};

class CheckFormatData
{
public:

CheckFormatData(CheckItemCoord=CheckItemCoord(0, 81), CheckItemCoord=CheckItemCoord(0, 81),
                CheckItemCoord=CheckItemCoord(0, 81), CheckItemCoord=CheckItemCoord(0, 81), 
                CheckItemCoord=CheckItemCoord(0, 81), CheckItemCoord=CheckItemCoord(0, 81), string="",
                CheckItemCoord=CheckItemCoord(0, 81), CheckItemCoord=CheckItemCoord(0, 81), 
                CheckItemCoord=CheckItemCoord(0, 81), CheckItemCoord=CheckItemCoord(0, 81),
                CheckItemCoord=CheckItemCoord(0, 81));

void setAmountCoord(CheckItemCoord);
void setPayeeCoord(CheckItemCoord);
void setTextAmountCoord(CheckItemCoord);
void setCommentCoord(CheckItemCoord);
void setDateCoord(CheckItemCoord);
void setSignatureCoord(CheckItemCoord);
void setSignaturePath(string);
void setAddress1Coord(CheckItemCoord);
void setAddress2Coord(CheckItemCoord);
void setCityStZipCoord(CheckItemCoord);
void setHeadCoord(CheckItemCoord);
void setNumberCoord(CheckItemCoord);

CheckItemCoord getAmountCoord();
CheckItemCoord getPayeeCoord();
CheckItemCoord getTextAmountCoord();
CheckItemCoord getCommentCoord();
CheckItemCoord getDateCoord();
CheckItemCoord getSignatureCoord();
CheckItemCoord getAddress1Coord();
CheckItemCoord getAddress2Coord();
CheckItemCoord getCityStZipCoord();
CheckItemCoord getHeadCoord();
CheckItemCoord getNumberCoord();

string getSignaturePath();

unsigned int numRows();
bool payeeFitsOnLine(string);

private:
CheckItemCoord amountCoord;
CheckItemCoord payeeCoord;
CheckItemCoord textAmountCoord;
CheckItemCoord commentCoord;
CheckItemCoord dateCoord;
CheckItemCoord signatureCoord;
CheckItemCoord address1Coord;
CheckItemCoord address2Coord;
CheckItemCoord cityStZipCoord;
CheckItemCoord headCoord;
CheckItemCoord numberCoord;

string         signatureFilePath;

void setCoord(CheckItemCoord&, CheckItemCoord);
unsigned int maxRow;
};

class TextCheck
{
public:
  TextCheck(Check=Check(), CheckFormatData=CheckFormatData(), Invoice=Invoice(), bool=false);
  void setCheck(Check);
  unsigned int numRows();
  string text();
  int getLinesPreSpace();
  void setLinesPreSpace(int);
  string getPreSpace();
  void setPrintOnlyCheck(bool val) {
      m_printOnlyCheck = val;
  }
  bool isPrintOnlyCheck() {
      return m_printOnlyCheck;
  }

private:
  Check check;
  CheckFormatData formData;
  Invoice invoice;
  bool showInvoiceData;
  int linesPreSpace;
  bool m_printOnlyCheck;
};

#endif
