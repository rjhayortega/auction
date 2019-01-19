#ifndef _SETUP_H_
#define _SETUP_H_
#include "databasemanager.h"
#include <string>
#include <vector>
#include "../reports/textreport.h"
#include "salemanager.h"

using namespace std;

class SetupDAO
{
public:
    // The DispRowsRecord and DisplayRecord types exist only to maintain backward compatability with clerk 5.0
    // without having to re-write a good portion of clerk.
    // for the love of god, as soon as work begins on clerk 6.0, remove these types and all functions that
    // have anything to do with them. PS. I'm keeping these ugly and dirty on purpose to try to speed the
    // day that they are replaced

    typedef struct dispRowsRecord
    {
        int row;
        int item;
        int length;
        bool reversed;
    }DispRowsRecord;

    typedef struct displayRecord
    {
        long num;
        int type;
        string name;
        string port;
        int rows;
        int which;
        int base;
        vector<DispRowsRecord> rowList;
    }DisplayRecord;

    SetupDAO();
    string get(string);
    void set(string, string);
    void del(string);
    void setBoolean(string, bool);
    vector<string> get(vector<string>);
    void set(vector<string>, vector<string>);
    TextReportHeader reportHeader(string="", bool=true, string="genMktComment", bool=false);

    bool getBoolean(string, bool=false);
    vector<DisplayRecord> getDisplayRecordList();
    void deleteDisplay(DisplayRecord);
    void saveDisplay(DisplayRecord);
    bool checkEmptyDB();
    string getMarketInfo();
private:
    vector<DispRowsRecord> getDispRowsRecordList(int num);
    void saveDispRowsRecordList(int num, vector<DispRowsRecord>);

    SaleManager sale;
};

#endif
