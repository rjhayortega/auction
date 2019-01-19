#ifndef _CODE_REPORT_H_
#define _CODE_REPORT_H_

#include "textreport.h"
#include "../types/animalcode.h"

class CodeReport : public TextReport
{
public:
  typedef enum{Color, Sex, Flaw}CodeType;

  CodeReport(vector<AnimalCode> =vector<AnimalCode>(), CodeType=Color);
  virtual string text();
private:

  TextReportTable codeTable();
  vector<AnimalCode> codeList;
  CodeType codeType;
};
#endif
