#include "databaseverifier.h"
#include <sstream>
DatabaseVerifier::DatabaseVerifier(string n, vector<Table> tv) : name(n), tableVector(tv)
{
}

string DatabaseVerifier::toString()
{
  stringstream resultStr;

  resultStr << "Database: " << name << endl;
  resultStr << string(30, '-') << endl;

  for(unsigned int i = 0; i < tableVector.size(); i++)
  {
    resultStr << tableVector[i].toString(1) << endl;
  }

  return resultStr.str();
}

DatabaseVerifier::Table::Table(string n, vector<Column> cv) : name(n), columnVector(cv) {}

string DatabaseVerifier::Table::toString(int depth)
{
  stringstream resultStr;

  resultStr << string(depth, '\t') << "Table: " << name << endl;
  resultStr << string(depth, '\t') << "+" << string(30, '-') << endl;
  
  for(unsigned int i = 0; i < columnVector.size(); i++)
  {
    resultStr << columnVector[i].toString(depth + 1);
  }

  return resultStr.str();
}

bool DatabaseVerifier::Table::compareNamesLT(Table a, Table b)
{
  return a.name < b.name;
}

string DatabaseVerifier::Table::getName()
{
  return name;
}

DatabaseVerifier::Table::Column::Column(string n, string d, bool k, string v, bool i) : name(n), definition(d), key(k), defaultValue(v), autoIncrement(i) {}

string DatabaseVerifier::Table::Column::toString(int depth)
{
  stringstream resultStr;
  resultStr << string(depth, '\t') << name << endl;
  return resultStr.str();
}

DatabaseVerifier DatabaseVerifier::auctionVerifier()
{
  vector<Table::Column> columnVector;


  // backtags
  columnVector.push_back(Table::Column("ckin_date", "date", false, "0000-00-00"));
  columnVector.push_back(Table::Column("trans_id","int(6) unsigned", false, "0"));
  columnVector.push_back(Table::Column("seller_id", "varchar(10)", false, ""));
  columnVector.push_back(Table::Column("tag_num","varchar(6)", false, ""));
  columnVector.push_back(Table::Column("old_num","varchar(6)", false, ""));
  columnVector.push_back(Table::Column("new_num", "varchar(6)", false, ""));
  columnVector.push_back(Table::Column("type", "int(2) unsigned zerofill", false, "00"));
  columnVector.push_back(Table::Column("color", "int(2) unsigned zerofill", false, "00"));
  columnVector.push_back(Table::Column("flaw", "int(2) unsigned zerofill", false, "00"));
  columnVector.push_back(Table::Column("b_tag", "varchar(14)", false, ""));
  columnVector.push_back(Table::Column("comment", "varchar(19)", false, ""));
  columnVector.push_back(Table::Column("breed", "varchar(30)", false, "HO"));
  columnVector.push_back(Table::Column("sex", "char(1)", false, "F"));
  columnVector.push_back(Table::Column("age", "int(5)",false, "0"));
  columnVector.push_back(Table::Column("vaccination", "varchar(20)", false, ""));
  columnVector.push_back(Table::Column("brucellosis", "varchar(10)", false, ""));
  columnVector.push_back(Table::Column("months_preg", "varchar(20)", false, ""));
  columnVector.push_back(Table::Column("test_date", "date", false, "0000-00-00"));
  columnVector.push_back(Table::Column("old_tag", "varchar(10)", false, ""));

  vector<Table> tableVector;

  tableVector.push_back(Table("backtags", columnVector));
  columnVector.clear();

  // brand 
  columnVector.push_back(Table::Column("id", "int(11)", true, "0", true));
  columnVector.push_back(Table::Column("image_data", "varchar(150)", false, ""));
  columnVector.push_back(Table::Column("position", "varchar(3)", false, ""));
  columnVector.push_back(Table::Column("trans_id", "int(11)", false, "0"));
  columnVector.push_back(Table::Column("head", "int(11)", false, "0"));
  columnVector.push_back(Table::Column("tag", "varchar(10)"));
  columnVector.push_back(Table::Column("date", "date", false, "0000-00-00"));

  tableVector.push_back(Table("brand", columnVector));
  columnVector.clear();

  // buyer
  columnVector.push_back(Table::Column("id"           , "int(11)"      ,true, "0", true));
  columnVector.push_back(Table::Column("customer_id"  , "int(11)", false, ""));
  columnVector.push_back(Table::Column("date"         , "date", false, "0000-00-00"));
  columnVector.push_back(Table::Column("number"       , "varchar(64)"));
  columnVector.push_back(Table::Column("name"         , "varchar(255)"));
  columnVector.push_back(Table::Column("address1"     , "varchar(255)"));
  columnVector.push_back(Table::Column("address2"     , "varchar(255)"));
  columnVector.push_back(Table::Column("city"         , "varchar(255)"));
  columnVector.push_back(Table::Column("state"        , "varchar(4)"));
  columnVector.push_back(Table::Column("zip"          , "varchar(20)"));
  columnVector.push_back(Table::Column("company"      , "varchar(255)"));
  columnVector.push_back(Table::Column("comment"      , "varchar(255)"));

  tableVector.push_back(Table("buyer", columnVector));
  columnVector.clear();

  // buyerchargesummary
  columnVector.push_back(Table::Column("charge_id"  ,"int(11)", false, "0"));
  columnVector.push_back(Table::Column("description","varchar(255)", false, ""));
  columnVector.push_back(Table::Column("total"      ,"decimal(10,2)", false, "0.00"));
  columnVector.push_back(Table::Column("invoice_id" ,"int(11)", false, "0"));

  tableVector.push_back(Table("buyerchargesummary", columnVector));
  columnVector.clear();

  //buyercommission
  columnVector.push_back(Table::Column("customer_id","varchar(255)", false, ""));
  columnVector.push_back(Table::Column("amount"     ,"decimal(10,2)", false, "0.00"));
  columnVector.push_back(Table::Column("mode"       ,"tinyint(4)", false, "0"));
  columnVector.push_back(Table::Column("date"       ,"date", false, "0000-00-00"));
  columnVector.push_back(Table::Column("checkno"    ,"int(11)", false, "0"));

  tableVector.push_back(Table("buyercommission", columnVector));
  columnVector.clear();

  // buyerinvoice
  columnVector.push_back(Table::Column("id"         ,"int(11)", true, "0", true));
  columnVector.push_back(Table::Column("status"     ,"tinyint(4)", false, "0"));
  columnVector.push_back(Table::Column("customer_id","varchar(64)"));
  columnVector.push_back(Table::Column("date"       ,"date", false, "0000-00-00"));

  tableVector.push_back(Table("buyerinvoice", columnVector));
  columnVector.clear();

  //buyerinvoicesummary
  columnVector.push_back(Table::Column("invoice_id","int(11)",true, "0"));
  columnVector.push_back(Table::Column("head", "int(11)", false, "0"));
  columnVector.push_back(Table::Column("total_bought", "decimal(10,2)", false, "0.00"));
  columnVector.push_back(Table::Column("customer_id", "varchar(10)"));
  columnVector.push_back(Table::Column("date", "date", false, "0000-00-00"));

  tableVector.push_back(Table("buyerinvoicesummary", columnVector));
  columnVector.clear();

  columnVector.push_back(Table::Column("id"               ,"int(11)"     ,true, "0", true));
  columnVector.push_back(Table::Column("description"      ,"varchar(255)"));
  columnVector.push_back(Table::Column("expression"       ,"varchar(255)"));
  columnVector.push_back(Table::Column("charge_nosale"    ,"tinyint(4)", false, "0"));
  columnVector.push_back(Table::Column("charge_resale"    ,"tinyint(4)"  ,false, "0"));
  columnVector.push_back(Table::Column("double_pairs"     ,"tinyint(4)"  ,false, "0"));
  columnVector.push_back(Table::Column("customer_type"    ,"tinyint(4)"  ,false, "0"));
  columnVector.push_back(Table::Column("needs_multiplier" ,"tinyint(1)", false, "0"));
  columnVector.push_back(Table::Column("commission_charge","tinyint(1)"  ,false, "0"));
  columnVector.push_back(Table::Column("beef_council"     ,"tinyint(1)"  , false, "0"));
  columnVector.push_back(Table::Column("scope"            ,"tinyint(4)", false, "0"));
  columnVector.push_back(Table::Column("break_type"       ,"tinyint(4)", false, "0"));

  tableVector.push_back(Table("charge", columnVector));
  columnVector.clear();

  // charge_adjustment

  columnVector.push_back(Table::Column("charge_id" ,"int(11)", false, "0"));
  columnVector.push_back(Table::Column("invoice_id","int(11)", false, "0"));
  columnVector.push_back(Table::Column("multiplier","decimal(10,2)", false, "0.00"));
  columnVector.push_back(Table::Column("adjustment","decimal(10,2)",false, "0.00"));

  tableVector.push_back(Table("charge_adjustment", columnVector));
  columnVector.clear();

  // charge_break

  columnVector.push_back(Table::Column("id", "int(11)", true, "0", true));
  columnVector.push_back(Table::Column("charge_id" , "int(11)", false, "0"));
  columnVector.push_back(Table::Column("amount"    , "decimal(10,2)", false, "0.00"));
  columnVector.push_back(Table::Column("expression", "varchar(255)"));

  tableVector.push_back(Table("charge_break", columnVector));
  columnVector.clear();


  // charge_code_rel

  columnVector.push_back(Table::Column("sex"        , "tinyint(4)", false, "0"));
  columnVector.push_back(Table::Column("charge_id"  , "int(11)", false, "0"));
  columnVector.push_back(Table::Column("flaw"       , "tinyint(4)", false, "0"));
  columnVector.push_back(Table::Column("color_group", "tinyint(4)", false, "0"));

  tableVector.push_back(Table("charge_code_rel", columnVector));
  columnVector.clear();

  // checkfactory

  columnVector.push_back(Table::Column("invoice_id"   , "int(11)", true, "0"));
  columnVector.push_back(Table::Column("mode"         , "tinyint(4)", false, "0"));
  columnVector.push_back(Table::Column("share_charges", "tinyint(1)",false, "0"));

  tableVector.push_back(Table("checkfactory", columnVector));
  columnVector.clear();

  // checkreg

  columnVector.push_back(Table::Column("number"    , "int(11)", false, "0"));
  columnVector.push_back(Table::Column("amount"    , "decimal(10,2)", false, "0.00"));
  columnVector.push_back(Table::Column("status"    , "tinyint(4)"   ,false, "0"));
  columnVector.push_back(Table::Column("comment"   , "varchar(255)"));
  columnVector.push_back(Table::Column("date"      , "date"         , false, "0000-00-00"));
  columnVector.push_back(Table::Column("invoice_id", "int(11)", false, "0"));
  columnVector.push_back(Table::Column("payee"     , "varchar(255)"));
  columnVector.push_back(Table::Column("id"        , "int(11)"      ,true, "0", true));
  columnVector.push_back(Table::Column("type"      , "tinyint(4)"   ,false, "0"));

  tableVector.push_back(Table("checkreg", columnVector));
  columnVector.clear();


  // codes

  columnVector.push_back(Table::Column("code_type"  , "smallint(2) unsigned zerofill",false, "00"));
  columnVector.push_back(Table::Column("code"       , "smallint(2) unsigned zerofill", false, "00"));
  columnVector.push_back(Table::Column("pair"       , "smallint(1)"                  , false, "0"));
  columnVector.push_back(Table::Column("descrip"    , "varchar(30)"));
  columnVector.push_back(Table::Column("color_group", "tinyint(1)", false, "4"));

  tableVector.push_back(Table("codes", columnVector));
  columnVector.clear();


  // comm_code_rel

  columnVector.push_back(Table::Column("commission_id", "int(11)", false, "0"));
  columnVector.push_back(Table::Column("sex"          , "tinyint(4)", false, "00"));
  columnVector.push_back(Table::Column("flaw"         , "tinyint(4)", false, "00"));
  columnVector.push_back(Table::Column("color_group"  , "tinyint(4)", false, "0"));

  tableVector.push_back(Table("comm_code_rel", columnVector));
  columnVector.clear();

  // commission
  columnVector.push_back(Table::Column("id"             , "int(11)"      ,true, "0", true));
  columnVector.push_back(Table::Column("commission_mode", "tinyint(4)", false, "0"));
  columnVector.push_back(Table::Column("break_mode"     , "tinyint(4)"   , false, "0"));
  columnVector.push_back(Table::Column("min"            , "decimal(10,2)", false, "0.00"));
  columnVector.push_back(Table::Column("max"            , "decimal(10,2)", false, "9999999999.99"));
  columnVector.push_back(Table::Column("no_sale_charge" , "decimal(10,2)", false, "0.00"));
  columnVector.push_back(Table::Column("name"           , "varchar(255)"));

  tableVector.push_back(Table("commission", columnVector));
  columnVector.clear();
  // commission_break


  columnVector.push_back(Table::Column("commission_id", "int(11)", false, "0"));
  columnVector.push_back(Table::Column("expression"   , "varchar(255)"));
  columnVector.push_back(Table::Column("break_value"  , "decimal(10,2)", false, "0.00"));
  columnVector.push_back(Table::Column("id"           , "int(11)"      , true, "0", true));
  columnVector.push_back(Table::Column("min"          , "decimal(10,2)", false, "0.00"));
  columnVector.push_back(Table::Column("max"          , "decimal(10,2)", false, "9999999999.99"));

  tableVector.push_back(Table("commission_break", columnVector));
  columnVector.clear();


  // customer

  columnVector.push_back(Table::Column("id"          , "int(11)"     , true, "0", true));
  columnVector.push_back(Table::Column("name"        , "varchar(255)"));
  columnVector.push_back(Table::Column("address1"    , "varchar(255)"));
  columnVector.push_back(Table::Column("address2"    , "varchar(255)"));
  columnVector.push_back(Table::Column("city"        , "varchar(255)"));
  columnVector.push_back(Table::Column("state"       , "char(2)"));
  columnVector.push_back(Table::Column("zip"         , "varchar(10)"));
  columnVector.push_back(Table::Column("phone"       , "varchar(30)"));
  columnVector.push_back(Table::Column("ssn"         , "varchar(12)"));
  columnVector.push_back(Table::Column("credit_card" , "varchar(100)"));
  columnVector.push_back(Table::Column("county"      , "varchar(100)"));
  columnVector.push_back(Table::Column("comment"     , "varchar(255)"));
  columnVector.push_back(Table::Column("mad_cow"     , "tinyint(1)", true, "0"));
  columnVector.push_back(Table::Column("mailing_list", "tinyint(1)"  ,true, "0"));
  columnVector.push_back(Table::Column("beef_council", "tinyint(1)"  , true, "0"));
  columnVector.push_back(Table::Column("company"     , "varchar(255)"));
  columnVector.push_back(Table::Column("altered"     , "tinyint(1)"  , true, "1"));
  columnVector.push_back(Table::Column("type"        , "tinyint(1)"  , true, "0"));
  columnVector.push_back(Table::Column("perm_number" , "varchar(20)"));
  columnVector.push_back(Table::Column("docket"      , "varchar(50)"));

  tableVector.push_back(Table("customer", columnVector));
  columnVector.clear();


  // default_printers

  columnVector.push_back(Table::Column("station", "varchar(100)"));
  columnVector.push_back(Table::Column("printer", "varchar(100)"));

  tableVector.push_back(Table("default_printers", columnVector));
  columnVector.clear();


  // depositreg

  columnVector.push_back(Table::Column("number" , "int(11)"      , true, "0", true));
  columnVector.push_back(Table::Column("amount" , "decimal(10,2)", false, "0.00"));
  columnVector.push_back(Table::Column("status" , "tinyint(4)"   , false, "0"));
  columnVector.push_back(Table::Column("date"   , "date"         , false, "0000-00-00"));
  columnVector.push_back(Table::Column("comment", "varchar(255)"));

  tableVector.push_back(Table("depositreg", columnVector));
  columnVector.clear();


  // displays

  columnVector.push_back(Table::Column("num"  , "int(1) unsigned", true, "0", true));
  columnVector.push_back(Table::Column("type" , "int(1) unsigned", false, "0"));
  columnVector.push_back(Table::Column("name" , "varchar(128)"));
  columnVector.push_back(Table::Column("port" , "varchar(128)"));
  columnVector.push_back(Table::Column("rows" , "int(1) unsigned"));
  columnVector.push_back(Table::Column("which", "int(1) unsigned"));
  columnVector.push_back(Table::Column("base" , "int(2) unsigned"));

  tableVector.push_back(Table("displays", columnVector));
  columnVector.clear();


  // disprows

  columnVector.push_back(Table::Column("num"  , "int(1) unsigned", true, "0"));
  columnVector.push_back(Table::Column("row"  , "int(1) unsigned", true, "0"));
  columnVector.push_back(Table::Column("item" , "int(1) unsigned", false, "0"));
  columnVector.push_back(Table::Column("len"  , "int(1) unsigned", false, "0"));
  columnVector.push_back(Table::Column("rev"  , "int(1) unsigned", false, "0"));

  tableVector.push_back(Table("disprows", columnVector));
  columnVector.clear();


  // history


  columnVector.push_back(Table::Column("date"          , "date"                ,false, "0000-00-00"));
  columnVector.push_back(Table::Column("transaction_id", "int(11)"             , false, "0"));
  columnVector.push_back(Table::Column("seller_number" , "varchar(50)"));
  columnVector.push_back(Table::Column("seller_name"   , "varchar(255)"));
  columnVector.push_back(Table::Column("buyer_number"  , "varchar(50)"));
  columnVector.push_back(Table::Column("buyer_name"    , "varchar(255)"));
  columnVector.push_back(Table::Column("head"          , "int(11)", false, "0"));
  columnVector.push_back(Table::Column("weight"        , "int(11)", false, "0"));
  columnVector.push_back(Table::Column("description"   , "varchar(50)"));
  columnVector.push_back(Table::Column("price"         , "decimal(10,2)", false, "0.00"));
  columnVector.push_back(Table::Column("tags"          , "varchar(70)"));
  columnVector.push_back(Table::Column("mode"          , "smallint(1) unsigned",false, "0"));
  columnVector.push_back(Table::Column("weighmaster"   , "varchar(25)"));

  tableVector.push_back(Table("history", columnVector));
  columnVector.clear();


  // market_report

  columnVector.push_back(Table::Column("trans_id", "int(11)", false, "0"));
  columnVector.push_back(Table::Column("date"    , "date"   ,false, "0000-00-00"));

  tableVector.push_back(Table("market_report", columnVector));
  columnVector.clear();


  // prorate

  columnVector.push_back(Table::Column("id"        , "int(11)"     , true, "0", true));
  columnVector.push_back(Table::Column("payee"     , "varchar(255)"));
  columnVector.push_back(Table::Column("invoice_id", "int(11)", false, "0"));

  tableVector.push_back(Table("prorate", columnVector));
  columnVector.clear();


  // proratedata

  columnVector.push_back(Table::Column("prorate_id", "int(11)"      ,false, "0"));
  columnVector.push_back(Table::Column("number"    , "int(11)"      , false, "0"));
  columnVector.push_back(Table::Column("amount"    , "decimal(10,2)", false, "0.00"));

  tableVector.push_back(Table("proratedata", columnVector));
  columnVector.clear();


  // rfid_tag

  columnVector.push_back(Table::Column("id"           , "int(11)"     , true, "0", true));
  columnVector.push_back(Table::Column("tag_number"   , "varchar(255)"));
  columnVector.push_back(Table::Column("seller_number", "varchar(10)"));
  columnVector.push_back(Table::Column("buyer_number" , "varchar(10)"));
  columnVector.push_back(Table::Column("date"         , "date", false, "0000-00-00"));
  columnVector.push_back(Table::Column("sale_time"    , "timestamp", false , "CURRENT_TIMESTAMP"));

  tableVector.push_back(Table("rfid_tag", columnVector));
  columnVector.clear();


  // sales

  columnVector.push_back(Table::Column("START", "date"      , true, "0000-00-00"));
  columnVector.push_back(Table::Column("DATE" , "date"      , false, "0000-00-00"));
  columnVector.push_back(Table::Column("END"  , "date"      , false, "0000-00-00"));
  columnVector.push_back(Table::Column("OPEN" , "tinyint(1)", false, "1"));
  columnVector.push_back(Table::Column("SEL"  , "tinyint(1)", false, "0"));

  tableVector.push_back(Table("sales", columnVector));
  columnVector.clear();


  // scales -- never really used, but probably should be


  columnVector.push_back(Table::Column("model" , "varchar(30)"));
  columnVector.push_back(Table::Column("format", "varchar(30)"));

  tableVector.push_back(Table("scales", columnVector));
  columnVector.clear();

  // seller


  columnVector.push_back(Table::Column("id"          , "int(11)"     , true, "0", true));
  columnVector.push_back(Table::Column("head"        , "int(11)"     , false, "0"));
  columnVector.push_back(Table::Column("customer_id" , "int(11)"     , false, "0"));
  columnVector.push_back(Table::Column("date"        , "date"        , false, "0000-00-00"));
  columnVector.push_back(Table::Column("number"      , "varchar(64)" ));
  columnVector.push_back(Table::Column("name"        , "varchar(255)"));
  columnVector.push_back(Table::Column("address1"    , "varchar(255)"));
  columnVector.push_back(Table::Column("address2"    , "varchar(255)"));
  columnVector.push_back(Table::Column("city"        , "varchar(255)"));
  columnVector.push_back(Table::Column("state"       , "varchar(4)"));
  columnVector.push_back(Table::Column("zip"         , "varchar(20)"));
  columnVector.push_back(Table::Column("mortgage"    , "varchar(255)")); 
  columnVector.push_back(Table::Column("comment"     , "varchar(255)"));
  columnVector.push_back(Table::Column("beef_council", "tinyint(1)", false, "0"));

  tableVector.push_back(Table("seller", columnVector));
  columnVector.clear();


  // sellerchargesummary

  columnVector.push_back(Table::Column("charge_id"  , "int(11)"      , false, "0"));
  columnVector.push_back(Table::Column("description", "varchar(255)"));
  columnVector.push_back(Table::Column("total"      , "decimal(10,2)", "false", "0.00"));
  columnVector.push_back(Table::Column("invoice_id" , "int(11)"      , false, "0"));

  tableVector.push_back(Table("sellerchargesummary", columnVector));
  columnVector.clear();


  // sellerinvoice

  columnVector.push_back(Table::Column("id"         , "int(11)"    , true, "0", true));
  columnVector.push_back(Table::Column("status"     , "tinyint(4)" , false, "0"));
  columnVector.push_back(Table::Column("customer_id", "varchar(64)"));
  columnVector.push_back(Table::Column("date"       , "date"       , false, "0000-00-00"));

  tableVector.push_back(Table("sellerinvoice", columnVector));
  columnVector.clear();


  // sellerinvoicesummary

  columnVector.push_back(Table::Column("invoice_id" , "int(11)"      , true, "0"));
  columnVector.push_back(Table::Column("head"       , "int(11)"      , false, "0"));
  columnVector.push_back(Table::Column("total_sale" , "decimal(10,2)", false, "0.00"));
  columnVector.push_back(Table::Column("customer_id", "varchar(10)"));
  columnVector.push_back(Table::Column("date"       , "date"         , false, "0000-00-00"));

  tableVector.push_back(Table("sellerinvoicesummary", columnVector));
  columnVector.clear();


  // setup

  columnVector.push_back(Table::Column("key_id", "bigint(20)"  , true, "0", true));
  columnVector.push_back(Table::Column("skey"  , "varchar(127)"));
  columnVector.push_back(Table::Column("svalue", "varchar(255)"));

  tableVector.push_back(Table("setup", columnVector));
  columnVector.clear();


  // trans

  columnVector.push_back(Table::Column("trans_id"     , "bigint(20)"              , true, "0", true));
  columnVector.push_back(Table::Column("sellerID"     , "varchar(10)"));
  columnVector.push_back(Table::Column("buyerID"      , "varchar(10)"));
  columnVector.push_back(Table::Column("head"         , "int(11)"                 , false, "0"));
  columnVector.push_back(Table::Column("weight"       , "int(11)"                 , false, "0"));
  columnVector.push_back(Table::Column("descrip"      , "varchar(127)"            ));
  columnVector.push_back(Table::Column("type"         , "int(2) unsigned zerofill", false, "00"));
  columnVector.push_back(Table::Column("color"        , "int(2) unsigned zerofill", false, "00"));
  columnVector.push_back(Table::Column("flaw"         , "int(2) unsigned zerofill", false, "00"));
  columnVector.push_back(Table::Column("price"        , "decimal(10,2)"           , false, "0.00"));
  columnVector.push_back(Table::Column("mode"         , "smallint(1) unsigned"    , false, "0"));
  columnVector.push_back(Table::Column("sellerpen"    , "varchar(6)"              , false, ""));
  columnVector.push_back(Table::Column("buyerpen"     , "varchar(10)"             ));
  columnVector.push_back(Table::Column("created"      , "timestamp"               , false, "0000-00-00 00:00:00"));
  columnVector.push_back(Table::Column("updated"      , "timestamp"               , false, "CURRENT_TIMESTAMP"));
  columnVector.push_back(Table::Column("weighmaster"  , "varchar(20)"             ));
  columnVector.push_back(Table::Column("active"       , "enum('f','t')"           , false, "t"));
  columnVector.push_back(Table::Column("presortnumber", "varchar(10)"             ));
  columnVector.push_back(Table::Column("comment"      , "varchar(40)"             ));
  columnVector.push_back(Table::Column("amount"       , "decimal(10,2)"           , false, "0.00"));
  columnVector.push_back(Table::Column("sinv_id"      , "bigint(20)"              , false, "0"));
  columnVector.push_back(Table::Column("binv_id"      , "bigint(20)"              , false, "0"));
  columnVector.push_back(Table::Column("manual"       , "varchar(255)"            ));
  columnVector.push_back(Table::Column("date"         , "date"                    , true, "0000-00-00"));

  tableVector.push_back(Table("trans", columnVector));
  columnVector.clear();


  // trucking_record

  columnVector.push_back(Table::Column("id"           , "int(11)"      , true, "0", true));
  columnVector.push_back(Table::Column("customer_id"  , "varchar(20)"));
  columnVector.push_back(Table::Column("trucker_name" , "varchar(255)"));
  columnVector.push_back(Table::Column("price"        , "decimal(10,2)", false, "0.00"));
  columnVector.push_back(Table::Column("quantity"     , "int(11)"      , false, "0"));
  columnVector.push_back(Table::Column("mode"         , "tinyint(4)"   , false, "0"));
  columnVector.push_back(Table::Column("date"         , "date"        , false, "0000-00-00"));
  columnVector.push_back(Table::Column("customer_type", "tinyint(1)"   , false, "0"));
  columnVector.push_back(Table::Column("checkno"      , "int(11)"      , false, "0"));

  tableVector.push_back(Table("trucking_record", columnVector));
  columnVector.clear();


  // zip_code

  columnVector.push_back(Table::Column("zip"  , "varchar(11)"));
  columnVector.push_back(Table::Column("state", "char(2)"));
  columnVector.push_back(Table::Column("city" , "varchar(255)"));

  tableVector.push_back(Table("zip_code", columnVector));
  columnVector.clear();

  return DatabaseVerifier("auction6", tableVector);
}

bool DatabaseVerifier::compareEQ(DatabaseVerifier that)
{
  sort(tableVector.begin(), tableVector.end(), DatabaseVerifier::Table::compareNamesLT);
  sort(that.tableVector.begin(), that.tableVector.end(), DatabaseVerifier::Table::compareNamesLT);

  if(this->tableVector.size() != that.tableVector.size())
  {
    return false;
  }

  for(unsigned int i = 0; i < tableVector.size(); i++)
  {
    if(tableVector[i].getName() != that.tableVector[i].getName())
    {
      return false;
    }
  }

  return true;
}

DatabaseVerifier DatabaseVerifier::fromDatabase(string host, unsigned port, string user, string pass, string dbse)
{
  //TODO Review !! DatabaseManager manager("Database Manager", host, port, user, pass, dbse);
}

void DatabaseVerifier::verify()
{
}
