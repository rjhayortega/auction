
#ifndef _DATABASE_VERIFIER_H_
#define _DATABASE_VERIFIER_H_

#include <string> 
#include <vector>
#include <iostream>

#include "databasemanager.h"

using namespace std;

class DatabaseVerifier
{
public:
  class Table
    {
    public:
      class Column
	{
	public:
	  Column(string="", string="", bool=false, string="", bool=false);
	  string toString(int=0);
	private:
          string name;
          string definition;
	  bool key;
	  string defaultValue;
	  bool autoIncrement;
	};

      Table(string="", vector<Column> =vector<Column>());
      static bool compareNamesLT(Table, Table);
      string getName();
      string toString(int=0);
    private:
      string name;
      vector<Column> columnVector;
    };
  DatabaseVerifier(string="", vector<Table> =vector<Table>());
  string toString();
  static DatabaseVerifier auctionVerifier();
  static DatabaseVerifier fromDatabase(string, unsigned, string, string, string);
  void verify();
  bool compareEQ(DatabaseVerifier);
private:
  string name;
  vector<Table> tableVector;
  DatabaseManager databaseManager;
};
#endif
