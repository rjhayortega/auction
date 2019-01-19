#ifndef _TUBERCULOSIS_RECORD_H_
#define _TUBERCULOSIS_RECORD_H_

#include "textreport.h"
#include "../types/healthrecord.h"

class TuberculosisRecord : public TextReport
{
public:
  TuberculosisRecord(HealthRecord=HealthRecord(), Person=Person());

  virtual string text();

private:
  HealthRecord record;
  TextReportTable recordHeader();
  TextReportTable recordBody();
  Person vet;
};
#endif
