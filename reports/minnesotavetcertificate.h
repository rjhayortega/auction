#ifndef _MINNESOTA_VET_CERTIFICATE_H_
#define _MINNESOTA_VET_CERTIFICATE_H_

#include "../types/healthrecord.h"
#include "textreport.h"

class MinnesotaVetCertificate : public TextReport
{

public:
  MinnesotaVetCertificate(HealthRecord=HealthRecord());

  virtual string text();

private:
  HealthRecord healthRecord;
  TextReportTable generateCustomerTable();
  TextReportTable generateTagTable();

};
#endif
