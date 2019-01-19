
#include "healthrecord.h"

#include <cstdio>

HealthRecord::HealthRecord(Person _vet, Seller _seller, Buyer _buyer, vector<Tag> _tagVector) 
  : vet(_vet), seller(_seller), buyer(_buyer), tagVector(_tagVector)
 {}

HealthRecord::HealthRecord(const HealthRecord& _healthRecord)
{
  vet = _healthRecord.vet;
  seller = _healthRecord.seller;
  buyer = _healthRecord.buyer;
  tagVector = _healthRecord.tagVector;
  marketAddress = _healthRecord.marketAddress;
}

void HealthRecord::setVet(Person vet)
{
  this->vet = vet;
}

void HealthRecord::setSeller(Seller seller)
{
  this->seller = seller;
}

void HealthRecord::setBuyer(Buyer buyer)
{
  this->buyer = buyer;

}

void HealthRecord::setTagVector(vector<Tag> tagVector)
{
  this->tagVector = tagVector;
}


Person HealthRecord::getVet()
{
  return vet;
}

Seller HealthRecord::getSeller()
{
  return seller;
}

Buyer HealthRecord::getBuyer()
{
  return buyer;
}

Tag& HealthRecord::operator[](int index)
{
  if(index < 0 || index >= tagVector.size())
  {
    perror("Index out of range\n");
  }

  return tagVector[index];
}

int HealthRecord::size()
{
  return tagVector.size();
}

void HealthRecord::setMarketAddress(Address address)
{
  marketAddress = address;
}

Address HealthRecord::getMarketAddress()
{
  return marketAddress;
}


vector<HealthRecord> HealthRecord::frameHealthRecord(int frameSize)
{
  vector<HealthRecord> resultVector;

  HealthRecord tempRecord(*this);
  vector<Tag> tempTagVector;

  for(unsigned int i = 0; i < tagVector.size(); i++)
  {
    tempTagVector.push_back(tagVector[i]);

    if(tempTagVector.size() == frameSize || i == tagVector.size() - 1)
    {
      tempRecord.setTagVector(tempTagVector);
      tempTagVector.clear();
      resultVector.push_back(tempRecord);
    }
  }  
  return resultVector;
}
