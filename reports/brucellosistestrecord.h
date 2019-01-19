#ifndef _BRUCELLOSIS_TEST_RECORD_H_
#define _BRUCELLOSIS_TEST_RECORD_H_

#include "textreport.h"
#include "../types/healthrecord.h"

class BrucellosisTestRecord : public TextReport
{
public:
  BrucellosisTestRecord(HealthRecord=HealthRecord());
  virtual string text();
private:
  HealthRecord healthRecord;
  TextReportTable header();
  TextReportTable body();

};

#endif
