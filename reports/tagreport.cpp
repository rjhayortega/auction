

#include "tagreport.h"

TagReport::TagReport(vector<Transaction> transactionList, Date date, string marketId)
{
  this->transactionList = transactionList;
  this->date = date;
  this->marketId = marketId;
}


string TagReport::text()
{
  clearTables();

  addTable(tagTableHeader());
  addTable(tagTable());
  return TextReport::text();
}


TextReportTable TagReport::tagTableHeader()
{
  TextReportTable table(2);
   table.setColumnAlignment(0, TextReportTable::LEFT);
   table.setColumnAlignment(1, TextReportTable::RIGHT);

   table.setColumnWidth(0, 40);
   table.setColumnWidth(1, 40);

   table.setHeaderStyle(TextReportTable::NoHeader, TextReportTable::Continuous);
   table.setFooterStyle(TextReportTable::Continuous, TextReportTable::NoHeader);

   table.setHeader(0, " ");
   table.setFooter(0, " ");
   table.insertRows(2);

   table.setText(0, 0, "Animal Board");
   table.setText(1, 0, "Tags Applied: " + date.toString("mm/dd/YYYY"));

   table.setText(0, 1, "Cattle Backtag Report");
   table.setText(1, 1, "Market ID: " + marketId);

  return table;
}


TextReportTable TagReport::tagTable()
{
  TextReportTable table(5);
//  table.insertRows(calculateTableRows());

  table.setHeaderStyle(TextReportTable::Broken, TextReportTable::Broken);
  table.setHeader(0, "Backtag#");
  table.setHeader(1, "Tags");
  table.setHeader(2, "Description");
  table.setHeader(3, "Seller Name");
  table.setHeader(4, "Address");

  table.setColumnWidth(0,10);
  table.setColumnWidth(1,10);
  table.setColumnWidth(2,16);
  table.setColumnWidth(3,22);
  table.setColumnWidth(4,22);

  table.setColumnAlignment(0, TextReportTable::LEFT);
  table.setColumnAlignment(1, TextReportTable::LEFT);
  table.setColumnAlignment(2, TextReportTable::LEFT);
  table.setColumnAlignment(3, TextReportTable::LEFT);
  table.setColumnAlignment(4, TextReportTable::LEFT);

  vector<Tag> tagList;
  unsigned int row = 0;
  unsigned int baseRow = 0;
  string tagString, nextTag;

  sort(transactionList.begin(), transactionList.end(), TagReport::compareTransactionTags);

  for(unsigned int i = 0; i < transactionList.size(); i++)
  {
    tagList = transactionList[i].getTagList();
    sort(tagList.begin(), tagList.end(), Tag::compareTagsLT);

    if(tagList.size() > 0)
    {
      baseRow = row;

      for(unsigned int j = 0; j < tagList.size(); j++)
      {
	tagString += tagList[j].getTag();
	nextTag = "";

	if(j != tagList.size() - 1)
	{
	  tagString += ", ";
	  nextTag = tagList[j + 1].getTag() + ", ";
	}

        if(tagString.length() + nextTag.length() >= 20 || j == tagList.size() - 1)
	{
	  table.insertRows(1);
	   table.setText(row, 0, tagString.substr(0, tagString.length() > 10 ? 10 : tagString.length()));
	   if(tagString.length() > 10)
	   {
	     table.setText(row, 1, tagString.substr(10));
	   }
	   tagString = "";
	   row++;
	}
      }

      table.insertRows(1);
      table.setText(baseRow, 2, transactionList[i].getAnimalCode().getDescrip());
      table.setText(baseRow, 3, string(" ") + transactionList[i].getSeller().getName().getLast());
      table.setText(baseRow, 4, string(" ") + transactionList[i].getSeller().getAddress().getAddress1());

      table.insertRows(1);
      table.setText(baseRow + 1, 4, string(" ") + transactionList[i].getSeller().getAddress().cityStateZipStr());

      row = (baseRow + 3 > row ? baseRow + 3 : row);
    }
  }
  return table;
}


// unsigned int TagReport::calculateTableRows()
// {
//   unsigned int result = 0;
//   vector<Tag> tagList;
//   string tagString;
//   unsigned int minRowsPerTrans = 3;
//   unsigned int neededRows = 0;

//   for(unsigned int i = 0; i < transactionList.size(); i++)
//   {
//     tagList = transactionList[i].getTagList();
//     tagString = "";

//     for(unsigned int j = 0; j < tagList.size(); j++)
//     {
//       tagString += tagList[j].getTag();

//       if(j != tagList.size() -1)
//       {
// 	tagString += ", ";
//       }
//     }
//     neededRows = (tagString.length() / 20) + 1;
//     result += (neededRows < minRowsPerTrans ? minRowsPerTrans : neededRows);
//   }

//   return result;
// }

bool TagReport::compareTransactionTags(Transaction a, Transaction b)
{
  vector<Tag> aList, bList;
  aList = a.getTagList();
  bList = b.getTagList();

  sort(aList.begin(), aList.end(), Tag::compareTagsLT);
  sort(bList.begin(), bList.end(), Tag::compareTagsLT);
  return (aList.size() > 0 ? aList[0].digitPart() : 0) < (bList.size() > 0 ? bList[0].digitPart() : 0);
}
