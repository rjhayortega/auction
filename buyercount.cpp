
#include "buyercount.h"

BuyerCount::BuyerCount(vector<BuyerInvoice> _buyerInvoiceList, Date _saleDate)
    : buyerInvoiceList(_buyerInvoiceList), saleDate(_saleDate)
{}

string BuyerCount::text()
{
    addTable(headerTable());
    setPageHeader(headerTable());
    addTable(buyerTable());

    return TextReport::text();
}

TextReportTable BuyerCount::headerTable()
{
    TextReportTable table(2);

    table.insertRows(3);

    table.setColumnAlignment(0, TextReportTable::RIGHT);
    table.setColumnAlignment(1, TextReportTable::RIGHT);

    table.setColumnWidth(0, 45);
    table.setColumnWidth(1, 44);

    table.setText(0, 0, "Buyer Head");
    table.setText(0, 1, "Date:" + saleDate.toString("mm/dd/YYYY"));
    table.setText(1, 0, string(string("Buyer Head").length(), '-'));

    return table;
}

TextReportTable BuyerCount::buyerTable()
{
    stringstream bufStream;

    TextReportTable table(4);

    table.setHeader(0, "Buyer Num");
    table.setHeader(1, "Head Count");
    table.setHeader(2, "No Sale");
    table.setHeader(3, "Buyer Name");

    table.setColumnWidth(0, 12);
    table.setColumnWidth(1, 12);
    table.setColumnWidth(2, 12);
    table.setColumnWidth(3, 43);

    table.setColumnAlignment(0, TextReportItem::LEFT);
    table.setColumnAlignment(1, TextReportItem::LEFT);
    table.setColumnAlignment(2, TextReportItem::LEFT);
    table.setColumnAlignment(3, TextReportItem::LEFT);

    table.setHeaderSeperator(' ', '-');
    table.setHeaderStyle(TextReportTable::NoHeader, TextReportTable::Broken);
    string name;

    for(unsigned int i = 0; i < buyerInvoiceList.size(); i++)
    {
        table.insertRows(1);
        table.setText(i, 0, buyerInvoiceList[i].getCustomer().getNumber());
        table.setText(i, 1, buyerInvoiceList[i].head(true, false));
        table.setText(i, 2, buyerInvoiceList[i].head(true, true) - buyerInvoiceList[i].head(true, false));
        name = buyerInvoiceList[i].getCustomer().getName().getLast();

        if(name == "")
        {
            name = "Buyer Name Not Found";
        }

        table.setText(i, 3, name);
    }

    return table;
}
