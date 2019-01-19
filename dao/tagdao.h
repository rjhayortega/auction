
#ifndef _TAG_DAO_H_
#define _TAG_DAO_H_

#include "../types/tag.h"
#include "../types/customer.h"
#include "databasemanager.h"
#include "salemanager.h"
#include "animalcodedao.h"
#include "../types/transaction.h"
#include "setupdao.h"
#include "branddao.h"

#include <vector>
using namespace std;


class TagDAO
{
public:
  typedef enum {PlasticTag, Owner, MetalTag, Age, Breed, Record}Index;

  vector<Tag> getTagList();
  vector<Tag> getTagVector(Index, bool, bool, string, string);

  vector<Tag> getTagList(Seller);
  vector<Tag> getTagList(Transaction&);
  vector<string> getIndexRange(Index);

  void saveTag(Tag&);
  void deleteTag(Tag);

  bool conflict(Tag, string&);
  bool conflict(Tag, long&);
  void updateTransactionTagList(long, string);
  void clearTransactionTags(Transaction);
  void setShowBrand(bool);
  vector<Tag> sortedTagList(Seller);
  Tag getPreviousTag(Tag, Index=PlasticTag);
  Tag getNextTag(Tag, Index=PlasticTag);
  Tag getNextSellerTag(Tag);
  Tag getPreviousSellerTag(Tag);
  vector<Tag> getTagList(Seller, Buyer);
  Tag maxSellerTag(Seller);
  Tag findTag(string, Index);
  int tagCount(Seller&);

  bool brucellosisTagConflict(Tag, Date&, string&);
  void fillTag(Tag&);

  bool doShowBrand();
  bool existsRfidForSale(Tag, string);

private:
  Tag getRelatedTag(Tag, Index, bool);
  bool showBrand;
  vector<Tag> getTagListByCondition(string);
  vector<Tag> getTagListByCondition(QSqlQuery &tagListQuery);
  SaleManager sale;

  AnimalCodeDAO codeDao;
  SetupDAO setup;
  BrandDAO brandDao;
  static string getIndexField(Index);

};
#endif
