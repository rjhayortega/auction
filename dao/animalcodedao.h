
#ifndef _ANIMAL_CODE_DAO_H_
#define _ANIMAL_CODE_DAO_H_

#include "../types/animalcode.h"
#include "databasemanager.h"
#include "commissiondao.h"
#include <string> 
#include <vector>
#include <iostream> 
using namespace std;

class AnimalCodeDAO
{
public:
typedef enum code_type
{
  sex=0,
  color=1,
  flaw=2
}CodeType;

  AnimalCodeDAO();
  ~AnimalCodeDAO();

  void saveType(short, string, bool=false, CommissionDAO::COLOR_GROUP=CommissionDAO::INVALID);
  void saveColor(short, string);
  void saveFlaw(short, string);

  string getTypeDescrip(AnimalCode);
  string getColorDescrip(AnimalCode);
  string getFlawDescrip(AnimalCode);

  string getTypeDescrip(short, CommissionDAO::COLOR_GROUP=CommissionDAO::INVALID);
  string getColorDescrip(short);
  string getFlawDescrip(short);

//  string getDescrip(short, short, short);
/*   string getDescrip(AnimalCode); */

  AnimalCode getAnimalCode(short, short, short);
  AnimalCode fillAnimalCode(AnimalCode& );

  vector<AnimalCode> getCodeList(CommissionDAO::COLOR_GROUP=CommissionDAO::INVALID);
  void deleteCodeRow(short);
  void deleteCode(CodeType, short, CommissionDAO::COLOR_GROUP=CommissionDAO::INVALID);
  bool isPair(short);

  static void startBatchMode();
  static void endBatchMode();
private:
  static bool batchMode;
  static string batchColorArray[100];
  static string batchFlawArray[100];
  static string batchSexArray[40];
  static bool   batchPairArray[40];
  vector<AnimalCode> getAnimalCodeListByCondition(string);
  void createCode(short, CodeType, CommissionDAO::COLOR_GROUP=CommissionDAO::INVALID);
  void saveCode(short, string, CodeType, bool=false, CommissionDAO::COLOR_GROUP=CommissionDAO::INVALID);
};
#endif
