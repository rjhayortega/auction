#include "textsellerinvoice.h"
#include "dao/customerdao.h"

TextSellerInvoice::TextSellerInvoice(Invoice *invoice, int skipLine, unsigned int pageLen, bool showSexSummary, bool groupChargesByName)
    : TextInvoice(invoice, skipLine, pageLen, showSexSummary, groupChargesByName)
{
    //TODO this flag should be reworked (not OOP ).
    isBuyerInvoice = false;
}

string TextSellerInvoice::getPen(Transaction trans)
{
    return trans.getBuyerPen();
}


TextSellerInvoice::~TextSellerInvoice()
{
}


TextReportTable TextSellerInvoice::pageHeader()
{
    TextReportTable table(1);
    table.insertRows(minimumHeaderSize() < 3 ? 3 : minimumHeaderSize());
    string mortgageStr = invoice->getCustomer().getCompany();
    table.setText(0, 0, string("Seller #: ") + invoice->getCustomer().getNumber());
    table.setText(1, 0, string("          ") + invoice->getCustomer().formattedName() + (mortgageStr.length() > 0 ? string(" & ") + mortgageStr : string()));
    return table;
}


string TextSellerInvoice::customerName(Transaction trans)
{
    return trans.getBuyer().getName().getLast();
}


long TextSellerInvoice::invoiceWeight()
{
    return invoice->weight(true);
}

long TextSellerInvoice::invoiceAverageWeight()
{
    return invoice->averageWeight(true);
}

bool TextSellerInvoice::doShowSexSummary()
{
    return !showSexSummary;
}

void TextSellerInvoice::initSummaryCoords(unsigned int& row, unsigned int& col)
{
    row = 0;
    col = 0;
}
string TextSellerInvoice::summaryChargeTotalLabel()
{
    return "SUB TOTAL CHARGES";
}

string TextSellerInvoice::summaryTotalLabel()
{
    return "TOTAL PROCEEDS";
}

void TextSellerInvoice::updateSummaryCoords(unsigned int& row, unsigned int& col, TextReportTable& summary)
{
    col += 3;
    if(col > 4)
    {
        summary.insertRows(1);
        col = 0;
        row++;
    }
}

void TextSellerInvoice::updateSummaryCoords(unsigned int& row, unsigned int& col, unsigned int &appendRows)
{
    col += 8;
    if(col > 8)
    {
        appendRows = 1;
        col = 0;
        row++;
    }
}

TextReportTable TextSellerInvoice::prorateTable()
{

    TextReportTable table(6);
    table.setColumnWidth(0, 2);
    table.setColumnWidth(1, 8);

    table.setColumnWidth(2, 22);
    table.setColumnWidth(3, 2);
    table.setColumnWidth(4, 10);
    table.setColumnWidth(5, 15);

    table.insertRows(checkList.size());

    table.setHeaderStyle(TextReportTable::ContinuousBroken, TextReportTable::ContinuousBroken);
    table.setColumnAlignment(4, TextReportTable::RIGHT);
    table.setColumnAlignment(5, TextReportTable::RIGHT);
    unsigned int row = 0;
    unsigned int col = 0;
    table.setHeader(0, "Ch");
    table.setHeader(1, "ecks Wri");
    table.setHeader(2, "tten:");

    if(chargeShareList.size() > 0)
    {
        table.setHeader(5, "Charges:");
    }

    if(checkList.size() == 0)
    {
        table.insertRows(1);
        table.setText(0, 0, "No checks written.", true);
    }

    if(checkList.size() == 1)
    {
        char buf[55];
        sprintf(buf, "# %ld", checkList[0].getNumber());
        table.setText(0, 0, buf, true);
    }
    else
    {
        for(unsigned int i = 0; i < checkList.size(); i++)
        {
            table.setText(i, 0, "#");
            table.setText(i, 1, checkList[i].getNumber());
            table.setText(i, 2, checkList[i].getPayee());
            table.setText(i, 3, "$");
            table.setText(i, 4, checkList[i].getAmount());

            if(i < chargeShareList.size())
            {
                table.setText(i, 5, chargeShareList[i]);
            }
        }
    }
    return table;
}

string TextSellerInvoice::customerNum(Transaction trans)
{
    return trans.getBuyer().getNumber();
}
string TextSellerInvoice::customerLabel()
{
    return "Buyer";
}
string TextSellerInvoice::customerString()
{
    return "Seller";
}
string TextSellerInvoice::mortgageString()
{
    return invoice->getCustomer().getCompany();
}


QVector<QTextLength> TextSellerInvoice::summaryTableColumnsConstraints()
{
    QVector<QTextLength> columnSizeConstraints(10);
    columnSizeConstraints[0] = QTextLength(QTextLength::PercentageLength,25.0);
    columnSizeConstraints[1] = QTextLength(QTextLength::PercentageLength,18.75);
    columnSizeConstraints[2] = QTextLength(QTextLength::PercentageLength,2.0);
    columnSizeConstraints[3] = QTextLength(QTextLength::PercentageLength,2.0);
    columnSizeConstraints[4] = QTextLength(QTextLength::PercentageLength,2.0);
    columnSizeConstraints[5] = QTextLength(QTextLength::PercentageLength,2.0);
    columnSizeConstraints[6] = QTextLength(QTextLength::PercentageLength,2.0);
    columnSizeConstraints[7] = QTextLength(QTextLength::PercentageLength,2.0);
    columnSizeConstraints[8] = QTextLength(QTextLength::PercentageLength,25.0);
    columnSizeConstraints[9] = QTextLength(QTextLength::PercentageLength,18.75);
    return columnSizeConstraints;
}

void TextSellerInvoice::createProrateTable(QTextTable *proRateTable)
{
    QVector<QTextLength> columnSizeConstraints(4);
    columnSizeConstraints[0] = QTextLength(QTextLength::PercentageLength,15.0);
    columnSizeConstraints[1] = QTextLength(QTextLength::PercentageLength,25.0);
    columnSizeConstraints[2] = QTextLength(QTextLength::PercentageLength,15.0);
    columnSizeConstraints[3] = QTextLength(QTextLength::PercentageLength,15.0);

    QTextTableFormat tableFormat;
    tableFormat.setBorderStyle(QTextFrameFormat::BorderStyle_None);
    //tableFormat.setBorderStyle(QTextFrameFormat::BorderStyle_Solid);

    tableFormat.setColumnWidthConstraints(columnSizeConstraints);
    tableFormat.setCellPadding(-1);
    tableFormat.setCellSpacing(0);
   // tableFormat.setHeaderRowCount(3);
    proRateTable->appendColumns(3);
    //tableFormat.setPageBreakPolicy(QTextFormat::PageBreak_AlwaysBefore);
    proRateTable->setFormat(tableFormat);
    // 1 row added when table created,+2 for header(3-1) + number of checks to print.

    //proRateTable->appendRows(2+checkList.size());
    //setCellText(proRateTable,0,0,"------------------------------------",true,2,Qt::AlignLeft);
    //setCellText(proRateTable,1,0,"Checks Written:",true,2,Qt::AlignLeft);
    //setCellText(proRateTable,2,0,"------------------------------------",true,2,Qt::AlignLeft);

    proRateTable->appendRows(checkList.size());
    setCellText(proRateTable,0,0,"Checks Written:",true,2,Qt::AlignLeft);
    setCellText(proRateTable,0,2," ");
    setCellText(proRateTable,0,3," ");

    if(chargeShareList.size() > 0) {
        setCellText(proRateTable,0,3,"Charges:");
    }

    unsigned int row = 1;
    unsigned int col = 0;

    if(checkList.size() == 0) {
        proRateTable->appendRows(1);
        setCellText(proRateTable,row,0,"No checks written.",true,Qt::AlignLeft);
    }
    else {
        for(unsigned int i = 0; i < checkList.size(); i++) {
            QString checkNumber = QString("# %1").arg(checkList[i].getNumber());
            setCellText(proRateTable,row+i, 0, checkNumber.toStdString(),false,Qt::AlignLeft);
            setCellText(proRateTable,row+i, 1, checkList[i].getPayee(),false,Qt::AlignLeft);

            QString checkAmount = QString("$ %1").arg(QString::number(checkList[i].getAmount(),'f',2));
            setCellText(proRateTable,row+i, 2, checkAmount.toStdString(),false,Qt::AlignRight);
            setCellText(proRateTable,row+i, 3," "); //clean cell
            if(chargeShareList.size() > i) {
                setCellText(proRateTable,row+i, 3, QString::number(chargeShareList[i],'f',2).toStdString(),false,Qt::AlignRight);
            }
        }
    }
}


QStringList TextSellerInvoice::getDisclaimerLines()
{
    QStringList listOfBuyers;
    listOfBuyers.clear();
    QString disclaimerStr;
    QStringList disclaimerList;

    SetupDAO setup;
    QString marketName = QString::fromStdString(setup.get ( "genMktName" ));

    vector<Transaction> transList = invoice->getTransactionList();
    for (int i = 0; i < transList.size(); i++) {
        Transaction trans = transList[i];
        QString buyerNumber = QString::fromStdString(trans.getBuyer().getNumber());

        if (buyerNumber.isEmpty()) {
            continue;
        }
        if ( listOfBuyers.contains(buyerNumber) ){
            continue;  // Buyer number already processed.
        }
        listOfBuyers<<buyerNumber; //Add buyer number to list of processed items.


        //Split buyer number
        QStringList buyerNums = buyerNumber.split("/");
        if (buyerNums.size() == 1 ) {
            buyerNums.clear();
            buyerNums = buyerNumber.split("-");
        }

//        Buyer singleBuyer = BuyerDAO::loadFromNumber(buyerNums[0].toStdString());
//        int customerId = singleBuyer.getId();
//        Customer cust = CustomerDAO::loadFromId(customerId);

        Customer cust = CustomerDAO::loadFromPermNumber(buyerNums[0].toStdString());
        if ( cust.getId() == 0 ) { //customer not found
            continue;
        }

        QString permNumber = cust.getPermNumber();
        QString relationString = cust.getRelationString();

        if (permNumber.trimmed().isEmpty()) {
            continue;  //Disclaimer printed only on permanent number filled buyers.
        }

        if (relationString.trimmed().isEmpty()) {
            continue;  //No relation set, nothing to do.
        }

        if (buyerNums.size() == 1)  {// Buyer number is single number.
            disclaimerStr =  QString("%1, %2 of %3 bidding for a non-affiliated buyer")
                    .arg(QString::fromStdString(cust.formattedName()))
                    .arg(relationString)
                    .arg(marketName.isEmpty() ? QString::fromStdString(cust.getCompany()) : marketName );

        }
        else { // Load second buyer info from splitted buyer num
//            Buyer forBuyer = BuyerDAO::loadFromNumber(buyerNums[1].toStdString());

            Customer secCust = CustomerDAO::loadFromPermNumber(buyerNums[1].toStdString());
            if ( secCust.getId() == 0 ) { //customer not found
                //Print non-affiliated disclaimer.
                disclaimerStr =  QString("%1, %2 of %3 bidding for a non-affiliated buyer")
                          .arg(QString::fromStdString(cust.formattedName()))
                          .arg(relationString)
                          .arg(marketName.isEmpty() ? QString::fromStdString(cust.getCompany()) : marketName);
            } else {
                //            int secCustomerId = forBuyer.getId();
                //            Customer secCust = CustomerDAO::loadFromId(secCustomerId);
                QString secPermNumber = secCust.getPermNumber();
                QString secRelationString = secCust.getRelationString();

                if ( !secPermNumber.trimmed().isEmpty() && !secRelationString.trimmed().isEmpty()) {
                    // Print complete disclaimer
                    disclaimerStr =  QString("%1, %2 of %3 bidding for %4, %5 of %6")
                            .arg(QString::fromStdString(cust.formattedName()))
                            .arg(relationString)
                            .arg(marketName.isEmpty() ? QString::fromStdString(cust.getCompany()) : marketName)
                            .arg(QString::fromStdString(secCust.formattedName()))
                            .arg(secRelationString)
                            .arg(marketName.isEmpty() ? QString::fromStdString(secCust.getCompany()) : marketName);
                }
                else {
                    //Print non-affiliated disclaimer.
                    disclaimerStr =  QString("%1, %2 of %3 bidding for a non-affiliated buyer")
                            .arg(QString::fromStdString(cust.formattedName()))
                            .arg(relationString)
                            .arg(marketName.isEmpty() ? QString::fromStdString(cust.getCompany()) : marketName);

                }
            }
        }
        disclaimerList << disclaimerStr.simplifyWhiteSpace();
    }

    return disclaimerList;


}

void TextSellerInvoice::createDisclaimerTable(QTextCursor &cursor)
{
    QStringList disclaimerList = getDisclaimerLines();
    if (disclaimerList.isEmpty()){
        return;
    }

    QTextTable* disclTbl = cursor.insertTable( 1,1);

    QVector<QTextLength> columnSizeConstraints(1);
    columnSizeConstraints[0] = QTextLength(QTextLength::PercentageLength,100.0);
    QTextTableFormat tableFormat;
    tableFormat.setBorderStyle(QTextFrameFormat::BorderStyle_None);
    //tableFormat.setBorderStyle(QTextFrameFormat::BorderStyle_Solid);

    tableFormat.setColumnWidthConstraints(columnSizeConstraints);
    tableFormat.setCellPadding(-1);
    tableFormat.setCellSpacing(0);
   // tableFormat.setHeaderRowCount(3);

    disclTbl->setFormat(tableFormat);
    disclTbl->appendColumns(1);

    disclTbl->appendRows(4);
    setCellText(disclTbl,1, 0, "Buyer Disclaimer:",false,Qt::AlignLeft);

    for (int i = 0 ; i< disclaimerList.size(); i++ ) {
        disclTbl->appendRows(1);
        setCellText(disclTbl,2+i, 0, disclaimerList[i].toStdString(),true,Qt::AlignLeft);
    }
}

TextReportTable TextSellerInvoice::createDisclaimerTable()
{
    QStringList disclaimerList = getDisclaimerLines();
    if (disclaimerList.isEmpty()){
        return TextReportTable();
    }


    TextReportTable table(1);
    table.setColumnWidth(0, 100);

    table.insertRows(disclaimerList.size()+2);

    table.setHeaderStyle(TextReportTable::NoHeader, TextReportTable::NoHeader);
    unsigned int row = 0;
    unsigned int col = 0;
    table.setHeader(0, "Buyer Disclaimer:");


    for(unsigned int i = 0; i < disclaimerList.size(); i++)
    {
        table.setText(i, 0, disclaimerList[i].toStdString());
        cout << "disclaimerList[" << i << "] = " << disclaimerList[i].toStdString() << endl; // [KLN]
    }
    return table;

}
