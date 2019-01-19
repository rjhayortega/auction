#ifndef _HEALTH_RECORD_H_
#define _HEALTH_RECORD_H_

#include "customer.h"
#include "tag.h"

#include <vector>
#include "address.h"
using namespace std;

class HealthRecord
{
public:
  HealthRecord(Person=Person() ,Seller=Seller(), Buyer=Buyer(), vector<Tag> =vector<Tag>());
  HealthRecord(const HealthRecord&);
  void setVet(Person);
  void setMarketAddress(Address);
  Address getMarketAddress();
  void setSeller(Seller);
  void setBuyer(Buyer);
  void setTagVector(vector<Tag>);

  Person getVet();
  Seller getSeller();
  Buyer getBuyer();
  Tag& operator[](int);
  int size();

  vector<HealthRecord> frameHealthRecord(int);

private:
  Person vet;
  Seller seller;
  Buyer buyer;
  vector<Tag> tagVector;
  Address marketAddress;
};

#endif
