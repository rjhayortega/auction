#ifndef _SOUTH_DAKOTA_HEALTH_CERTIFICATE
#define _SOUTH_DAKOTA_HEALTH_CERTIFICATE
#include "textreport.h"
#include "../types/healthrecord.h"
#include "../types/address.h"

#include <vector>
using namespace std;
class SouthDakotaHealthCertificate : public TextReport
{
public:
  SouthDakotaHealthCertificate(HealthRecord=HealthRecord());
  virtual string text();

private:
  TextReportTable headerTable();
  TextReportTable body();
  TextReportTable footer();
  HealthRecord healthRecord;
  Person vet;
};
#endif
