#include "mailinglabels.h"

MailingLabels::MailingLabels(vector<Customer> customerList, bool showAll) : TextReport(4)
{
  this->customerList = customerList;
  this->showAll = showAll;
}

string MailingLabels::text()
{
  clearTables();
  addTable(labelsTable());
  return TextReport::text();
}

TextReportTable MailingLabels::labelsTable()
{
    TextReportTable table(1);

    unsigned int baseRow = 0;
    unsigned int nextRow = 0;

    for(unsigned int i = 0; i < customerList.size(); i++)
    {
        if(customerList[i].isOnMailingList() || showAll)
        {
            Name tmp = tmp.fromString(customerList[i].getName().getLast());
            string adjustedName =  tmp.getFirst() + " " + tmp.getLast();

            table.insertRows(4);
//            table.setText(baseRow + nextRow, 0, customerList[i].getName().getLast());
            table.setText(baseRow + nextRow, 0, adjustedName);
            // [KLN[ debug
//            cout << "customerList.getName().getLast(): " << customerList[i].getName().getLast() << endl;
//            cout << "customerList.getName().getFirst(): " << customerList[i].getName().getFirst() << endl;
//            cout << "customerList.getName().informal_midsize(): " << customerList[i].getName().informal_midsize() << endl;
//            cout << "tmp.getLast(): " << tmp.getLast() << endl;
//            cout << "tmp.getFirst(): " << tmp.getFirst() << endl;
//            cout << endl;
            // [KLN[ debug end
            nextRow++;

            if(customerList[i].getAddress().getAddress1().length() > 0)
            {
                table.insertRows(1);
                table.setText(baseRow + nextRow, 0, customerList[i].getAddress().getAddress1());
                nextRow++;
            }

            if(customerList[i].getAddress().getAddress2().length() > 0)
            {
                table.insertRows(1);
                table.setText(baseRow + nextRow, 0, customerList[i].getAddress().getAddress2());
                nextRow++;
            }

            table.insertRows(1);
            table.setText(baseRow + nextRow, 0, customerList[i].getAddress().cityStateZipStr());

            baseRow += 4;
            nextRow = 0;
        }
    }

    return table;
}
