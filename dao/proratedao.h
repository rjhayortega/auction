#ifndef _PRORATE_DAO_H_
#define _PRORATE_DAO_H_

#include "../types/prorate.h"
#include "../types/checkfactory.h"
#include "databasemanager.h"
#include <string>
#include <vector>

using namespace std;

class ProrateDAO
{
public:
typedef enum prorateMode
{
  Percentage,
  Flat,
  Head,
  Transaction,
  Sex
}Mode;

  ProrateDAO();
  CheckFactory* getCheckFactory(Invoice, Mode* =NULL);
  void releaseCheckFactory();

  void saveCheckFactory(CheckFactory*, Mode);
  void deleteCheckFactory(CheckFactory*);
private:
  CheckFactory *checkFactory;
  vector<Prorate> getProrateList(long);
  vector<Prorate::Data> getProrateData(long);

  void saveProrateList(long, vector<Prorate>);
  void saveProrate(long, Prorate);
  void saveDataList(long, vector<Prorate::Data>);
  void saveProrateData(long, Prorate::Data);

};
#endif
