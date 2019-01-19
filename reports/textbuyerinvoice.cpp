#include "textbuyerinvoice.h"

TextBuyerInvoice::TextBuyerInvoice(Invoice *invoice, int skipLine, unsigned int pageLen, bool showSexSummary, bool averageOnLeft, bool groupChargesByName, bool totalNS)
    : TextInvoice(invoice, skipLine, pageLen, showSexSummary, groupChargesByName)
{
  m_averageOnLeft = averageOnLeft;
  totalNoSale = totalNS;
//TODO Remove this flag, not OOP.
  isBuyerInvoice = true;
}

string TextBuyerInvoice::getPen(Transaction trans)
{
  return trans.getBuyerPen();
}

TextReportTable TextBuyerInvoice::pageHeader()
{
    TextReportTable table(1);
    table.insertRows(minimumHeaderSize() < 3 ? 3 : minimumHeaderSize());
    table.setText(0, 0, string("Buyer #: ") + invoice->getCustomer().getNumber());
    table.setText(1, 0, string("         ") + invoice->getCustomer().formattedName());
    return table;
}

string TextBuyerInvoice::customerName(Transaction trans)
{
    return trans.getSeller().getName().getLast();
}

long TextBuyerInvoice::invoiceWeight()
{
    return invoice->weight(totalNoSale);
}

long TextBuyerInvoice::invoiceAverageWeight()
{
    return invoice->averageWeight(totalNoSale);
}

long TextBuyerInvoice::summaryHead()
{
    return invoice->head(true, totalNoSale);
}

void TextBuyerInvoice::noSaleTable()
{
    long noSaleHead = invoice->noSaleHead(true);
    if(noSaleHead != 0)
    {
        char buf[30];
        sprintf(buf, "Total N/S: %ld", noSaleHead);
        string data = buf;

        if(totalNoSale)
        {
            sprintf(buf, " hd %ld lbs", invoice->noSaleWeight());
            data += buf;
        }

        TextReportTable table(1);
        table.setColumnWidth(0, 79);
        table.setColumnAlignment(0, TextReportTable::LEFT);
        table.insertRows(1);
        table.setText(0, 0, data);
        addTable(table);
    }
}

void TextBuyerInvoice::createNoSaleTable(QTextTable * noSaleTable)
{
    QTextTableFormat tableFormat;
    tableFormat.setBorderStyle(QTextFrameFormat::BorderStyle_None);
    tableFormat.setCellPadding(-1);
    tableFormat.setCellSpacing(0);
    noSaleTable->setFormat(tableFormat);

    long noSaleHead = invoice->noSaleHead(true);
    if(noSaleHead != 0) {
        char buf[30];
        sprintf(buf, "Total N/S: %ld", noSaleHead);
        string data = buf;

        if(totalNoSale)
        {
            sprintf(buf, " hd %ld lbs", invoice->noSaleWeight());
            data += buf;
        }
        setCellText(noSaleTable,0,0,data,false,Qt::AlignLeft);
    }

}


bool TextBuyerInvoice::doShowSexSummary()
{
    return showSexSummary;
}

void TextBuyerInvoice::initSummaryCoords(unsigned int& row, unsigned int& col)
{
    row = 0;
    col = 3;
}

void TextBuyerInvoice::initSummaryCoordsLaser(unsigned int& row, unsigned int& col)
{
    row = 0;
    col = 8;
}


string TextBuyerInvoice::summaryChargeTotalLabel()
{
    return "TOTAL FEES";
}

string TextBuyerInvoice::summaryTotalLabel()
{
    return "TOTAL COST";
}

void TextBuyerInvoice::overallAverageLine(TextReportTable& summary, unsigned int& row)
{
    summary.insertRows(2);
    char buf[80];
    double cwt = invoice->cwt();

    sprintf(buf, "Overall average per cwt   $%8.2f", (cwt != 0 ? ((BuyerInvoice*)invoice)->net() / cwt : 0));
    row += 2;

    unsigned int col = (m_averageOnLeft ? 0 : 3);
    summary.setText(row, col, buf, true);
}


void TextBuyerInvoice::updateSummaryCoords(unsigned int& row, unsigned int& col, TextReportTable& summary)
{
    row++;
    col = 3;
    summary.insertRows(1);
}

void TextBuyerInvoice::updateSummaryCoords(unsigned int& row, unsigned int& col, unsigned int & appendRows)
{
    row++;
    col = 8;
    appendRows=1;
}



string TextBuyerInvoice::customerNum(Transaction trans)
{
  return trans.getSeller().getNumber();
}

string TextBuyerInvoice::customerLabel()
{
  return "Seller";
}

string TextBuyerInvoice::customerString()
{
  return "Buyer";
}

string TextBuyerInvoice::companyString()
{
  return invoice->getCustomer().getCompany();
}


string TextBuyerInvoice::statusString()
{
  switch(invoice->getStatus())
  {
  case Invoice::PAID:
    return "PAID";

  case Invoice::UNPAID:
  default:
    return "UNPAID";

  case Invoice::BILLED:
    return "COMPANY";
  }
}

void TextBuyerInvoice::overallAverageLine(QTextTable * summaryTable, unsigned int& row)
{
    summaryTable->appendRows(2);
    char buf[80];
    double cwt = invoice->cwt();
    sprintf(buf, "Overall average per cwt   $%8.2f", (cwt != 0 ? ((BuyerInvoice*)invoice)->net() / cwt : 0));
    row += 2;

    if ( m_averageOnLeft) {
        setCellText(summaryTable,row,0,buf,true,Qt::AlignLeft);
    }
    else {
        setCellText(summaryTable,row,0,buf,true,Qt::AlignRight);
    }
}

