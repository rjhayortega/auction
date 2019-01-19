
#include "textinvoice.h"
#include "../dao/setupdao.h"
#include <QTextTable>
#include <QTextTableCell>
#include <QTextCursor>
#include <QPrinter>
#include <QPainter>
#include <QProgressDialog>
#include <QImage>

const int ColNumber = 96;
QTextFrameFormat::BorderStyle tableBoarderStyle = QTextFrameFormat::BorderStyle_None;
//QTextFrameFormat::BorderStyle tableBoarderStyle = QTextFrameFormat::BorderStyle_Solid;


string itoa(int x, char * b, int base=10)	{
    sprintf(b, "%d", x);
    return b;
}

string ltoa(long x, char * b, int base=10)	{
    sprintf(b, "%ld", x);
    return b;
}


TextInvoice::TextInvoice(Invoice *invoice, int skipLines, unsigned int pageLen, bool showSexSummary, bool groupChargesByName) 
    : TextReport(pageLen)
{
    SetupDAO setup;
    this->showTags = setup.getBoolean("showTagsAtBottomOfInvoice");

    setInvoice(invoice);
    setSkipLines(skipLines);
    checkList = vector<Check>();
    initTransColWeights();
    initTransColWeightsPercents();
    transColCount = 1;
    doShowNames = false;
    this->showSexSummary = showSexSummary;
    this->showBrand = false;
    this->showId = false;
    this->showTransactionComments = false;
    this->groupChargesByName = groupChargesByName;
    this->_minimumHeaderSize = 0;
    this->transFitColumns = 0;
    this->transFitLength = 0;

    this->isBuyerInvoice = false; //default value
}

void TextInvoice::setTransFit(int transFitColumns, int transFitLength)
{
    this->transFitColumns = transFitColumns;
    this->transFitLength = transFitLength;
}

TextReportTable TextInvoice::pageHeader()
{
    return TextReportTable();
}



void TextInvoice::setShowId(bool showId)
{
    this->showId = showId;
}

void TextInvoice::setFooterText(string footerString)
{
    this->footerString = footerString;
}

void TextInvoice::setShowBrand(bool showBrand)
{
    this->showBrand = showBrand;
}

void TextInvoice::setMinimumHeaderSize(int minimumHeaderSize)
{
    this->_minimumHeaderSize = minimumHeaderSize;
}

void TextInvoice::setShowTransactionComments(bool showComments)
{
    this->showTransactionComments = showComments;
}

TextInvoice::~TextInvoice()
{}

void TextInvoice::setShowNames(bool doShowNames)
{
    this->doShowNames = doShowNames;
}

bool TextInvoice::showNames()
{
    return doShowNames;
}

void TextInvoice::initTransColWeights()
{
    transColWeight[TransNo]    = 6;
    transColWeight[Head]       = 6;
    transColWeight[Descrip]    = 12;
    transColWeight[CustomerNo] = 8;
    transColWeight[Tags]       = 6;
    transColWeight[TotWt]      = 7;
    transColWeight[AvgWt]      = 6;
    transColWeight[DolPerHd]   = 11;
    transColWeight[DolPerCW]   = 10;
    transColWeight[Amount]     = 13;
    transColWeight[Pen]        = 10;
}

// This structure stores % of column width. If some columns not present
// the rest of the space extended proportianal to this number.
// Formula:  ScaleKoeff = (X1+X2+...+X11)/100  Actual width =  X[i]* ScaleKoeff

void TextInvoice::initTransColWeightsPercents()
{
    transColWeightPrc[TransNo]    = 6.3;
    transColWeightPrc[Head]       = 6.3;
    transColWeightPrc[Descrip]    = 12.6;
    transColWeightPrc[CustomerNo] = 8.4;
    transColWeightPrc[Tags]       = 6.3;
    transColWeightPrc[TotWt]      = 7.4;
    transColWeightPrc[AvgWt]      = 6.3;
    transColWeightPrc[DolPerHd]   = 11.6;
    transColWeightPrc[DolPerCW]   = 10.5;
    transColWeightPrc[Amount]     = 13.7;
    transColWeightPrc[Pen]        = 10.5;
}


void TextInvoice::setInvoice(Invoice *invoice)
{
    this->invoice = invoice;
}

int TextInvoice::minimumHeaderSize()
{
    return _minimumHeaderSize;
}

void TextInvoice::setSkipLines(int skipLines)
{
    this->skipLines = skipLines;
}

void TextInvoice::setProrateList(vector<Check> checkList, vector<double> chargeShareList)
{
    this->checkList = checkList;
    this->chargeShareList = chargeShareList;
}

string TextInvoice::invoiceReportText()
{
    return text();
}

TextReportTable TextInvoice::getInvoiceTable()
{
    TextReportTable invoiceTable(3);

    invoiceTable.insertRows(minimumHeaderSize());

    invoiceTable.setColumnWidth(0, 10);
    invoiceTable.setColumnWidth(1, 50);
    invoiceTable.setColumnWidth(2, 20);

    string nameString = formatName(invoice->getCustomer().getName().getLast());

    unsigned int dataRow = 2;
    Address addr = invoice->getCustomer().getAddress();

    int numRows = invoiceTable.numRows();

    if(invoiceTable.numRows() < 2)
    {
        invoiceTable.insertRows(2 - invoiceTable.numRows());
    }

    invoiceTable.setText(0, 0, customerString() + " #  ");
    invoiceTable.setText(0, 1, invoice->getCustomer().getNumber());
    invoiceTable.setText(0, 2, string("Date: ") + invoice->getDate().toString("mm-dd-yyyy"));

    invoiceTable.setText(1, 1, nameString);

    if(mortgageString().length() > 0)
    {
        invoiceTable.setText(1, 2, mortgageString());
    }

    if(statusString().length() > 0)
    {
        invoiceTable.setText(1, 2, statusString());
    }

    if(companyString().length() > 0)
    {
        if(invoiceTable.numRows() <= dataRow)
        {
            invoiceTable.insertRows(dataRow - invoiceTable.numRows() + 1);
        }

        invoiceTable.setText(dataRow, 1, companyString());
        dataRow++;
    }

    if(addr.getAddress1().length() > 0)
    {

        if(invoiceTable.numRows() <= dataRow)
        {
            invoiceTable.insertRows(dataRow - invoiceTable.numRows() + 1);
        }

        invoiceTable.setText(dataRow, 1, addr.getAddress1());
        dataRow++;
    }

    if(addr.getAddress2().length() > 0)
    {
        if(invoiceTable.numRows() <= dataRow)
        {
            invoiceTable.insertRows(dataRow - invoiceTable.numRows() + 1);
        }

        invoiceTable.setText(dataRow, 1, addr.getAddress2());
        dataRow++;
    }

    if(addr.cityStateZipStr().length() > 0)
    {
        if(invoiceTable.numRows() <= dataRow)
        {
            invoiceTable.insertRows(dataRow - invoiceTable.numRows() + 1);
        }

        invoiceTable.setText(dataRow, 1, addr.cityStateZipStr());
        dataRow++;
    }


    if(invoice->getCustomer().getComment().length() > 0 && invoice->getCustomer().getComment()[0] != '*')
    {
        if(invoiceTable.numRows() <= dataRow)
        {
            invoiceTable.insertRows(dataRow - invoiceTable.numRows() + 1);
        }

        invoiceTable.setText(dataRow, 0, invoice->getCustomer().getComment(), true);
        dataRow++;
    }

    if(showId)
    {

        if(invoiceTable.numRows() <= dataRow)
        {
            invoiceTable.insertRows(dataRow - invoiceTable.numRows() + 1);
        }

        if(dataRow == 2)
        {
            if(invoiceTable.numRows() < 2)
            {
                invoiceTable.insertRows(1);
            }
        }
        else
        {
            dataRow--;
        }

        char buf[20];
        sprintf(buf, "%7ld", invoice->getNumber());
        invoiceTable.setText(dataRow, 2, string("Invoice #") + string(buf));
    }

    invoiceTable.insertRows(1);
    return invoiceTable;
}
//-------------- Laser printer support  --------------------------------

//Fill market information to table
void TextInvoice::createMarketInfoTable(QTextTable * marketInfoTable)
{
    QTextTableFormat tableFormat;
    tableFormat.setBorderStyle(tableBoarderStyle);
//    marketInfoTable->appendRows(3);
    QVector<QTextLength> columnSizeConstraints(1);
    columnSizeConstraints[0] = QTextLength(QTextLength::PercentageLength,100.0);
    tableFormat.setColumnWidthConstraints(columnSizeConstraints);
    tableFormat.setCellPadding(-1);
    tableFormat.setCellSpacing(0);
    marketInfoTable->setFormat(tableFormat);
    setCellText(marketInfoTable,0, 0, headerText(),false,Qt::AlignCenter);
}


// Fill customer information to table
void TextInvoice::createCustomerInfoTable(QTextTable * customerInfoTable )
{
    // Table initialized with 1 row and 1 column.
    // Make it 3 columns wide.
    customerInfoTable->appendColumns(2);
    int minHeaderSize = minimumHeaderSize();
    if (minHeaderSize > 0) {
        customerInfoTable->appendRows(minHeaderSize);
    }
    // Initialize column width in %%.
    QVector<QTextLength> columnSizeConstraints(9);
    columnSizeConstraints[0] = QTextLength(QTextLength::PercentageLength,15.0);
    columnSizeConstraints[1] = QTextLength(QTextLength::PercentageLength,60.0);
    columnSizeConstraints[2] = QTextLength(QTextLength::PercentageLength,25.0);

    QTextTableFormat tableFormat;
    tableFormat.setBorderStyle(tableBoarderStyle);
    tableFormat.setColumnWidthConstraints(columnSizeConstraints);
    tableFormat.setCellPadding(-1);
    tableFormat.setCellSpacing(0);
    customerInfoTable->setFormat(tableFormat);

    string nameString = formatName(invoice->getCustomer().getName().getLast());

    int dataRow = 2;
    Address addr = invoice->getCustomer().getAddress();

    int rowsCount = customerInfoTable->rows();

    if(rowsCount < 2)
    {
        customerInfoTable->appendRows(2 - rowsCount);
    }
    for (int k = 0 ; k < customerInfoTable->rows(); k++) {
        for (int colIdx = 0 ; colIdx < customerInfoTable->columns(); colIdx++) {
            setCellText(customerInfoTable,k, colIdx, " "); // fill empty cells.
        }
    }



    setCellText(customerInfoTable,0, 0, customerString() + " #  ",false,Qt::AlignLeft);
    setCellText(customerInfoTable,0, 1, invoice->getCustomer().getNumber(),false,Qt::AlignLeft);
    setCellText(customerInfoTable,0, 2, string("Date: ") + invoice->getDate().toString("mm-dd-yyyy"),false,Qt::AlignLeft);

    setCellText(customerInfoTable,1, 1, nameString,false,Qt::AlignLeft);

    if(mortgageString().length() > 0)
    {
        setCellText(customerInfoTable,1, 2, mortgageString(),false,Qt::AlignLeft);
    }

    if(statusString().length() > 0)
    {
        setCellText(customerInfoTable,1, 2, statusString(),false,Qt::AlignLeft);
    }

    if(companyString().length() > 0)
    {
        if(customerInfoTable->rows() <= dataRow)
        {
            customerInfoTable->appendRows(dataRow - customerInfoTable->rows() + 1);
        }

        setCellText(customerInfoTable,dataRow, 0, " ");
        setCellText(customerInfoTable,dataRow, 2, " ");
        setCellText(customerInfoTable,dataRow, 1, companyString(),false,Qt::AlignLeft);
        dataRow++;
    }

    if(addr.getAddress1().length() > 0)
    {

        if(customerInfoTable->rows() <= dataRow)
        {
            customerInfoTable->appendRows(dataRow - customerInfoTable->rows() + 1);
        }

        setCellText(customerInfoTable,dataRow, 0, " ");
        setCellText(customerInfoTable,dataRow, 2, " ");
        setCellText(customerInfoTable,dataRow, 1, addr.getAddress1(),false,Qt::AlignLeft);
        dataRow++;
    }

    if(addr.getAddress2().length() > 0)
    {
        if(customerInfoTable->rows() <= dataRow)
        {
            customerInfoTable->appendRows(dataRow - customerInfoTable->rows() + 1);
        }
        setCellText(customerInfoTable,dataRow, 0, " ");
        setCellText(customerInfoTable,dataRow, 2, " ");
        setCellText(customerInfoTable,dataRow, 1, addr.getAddress2(),false,Qt::AlignLeft);
        dataRow++;
    }

    if(addr.cityStateZipStr().length() > 0)
    {
        if(customerInfoTable->rows() <= dataRow)
        {
            customerInfoTable->appendRows(dataRow - customerInfoTable->rows() + 1);
        }
        setCellText(customerInfoTable,dataRow, 0, " ");
        setCellText(customerInfoTable,dataRow, 2, " ");
        setCellText(customerInfoTable,dataRow, 1, addr.cityStateZipStr(),false,Qt::AlignLeft);
        dataRow++;
    }


    if(invoice->getCustomer().getComment().length() > 0 && invoice->getCustomer().getComment()[0] != '*')
    {
        if(customerInfoTable->rows() <= dataRow)
        {
            customerInfoTable->appendRows(dataRow - customerInfoTable->rows() + 1);
        }
        setCellText(customerInfoTable,dataRow, 1, " ");
        setCellText(customerInfoTable,dataRow, 2, " ");
        setCellText(customerInfoTable,dataRow, 0, invoice->getCustomer().getComment(),true,Qt::AlignLeft);
        dataRow++;
    }

    if(showId)
    {

        if(customerInfoTable->rows() <= dataRow)
        {
            customerInfoTable->appendRows(dataRow - customerInfoTable->rows() + 1);
        }

        if(dataRow == 2)
        {
            if(customerInfoTable->rows() < 2)
            {
                customerInfoTable->appendRows(1);
            }
        }
        else
        {
            dataRow--;
        }

        char buf[20];
        sprintf(buf, "%7ld", invoice->getNumber());
        setCellText(customerInfoTable,dataRow, 2, string("Invoice #") + string(buf),false,Qt::AlignLeft);
    }

    customerInfoTable->appendRows(1);
    int lastRow = customerInfoTable->rows()-1;
    for (int colIdx = 0 ; colIdx < customerInfoTable->columns(); colIdx++) {
        setCellText(customerInfoTable,lastRow, colIdx, " "); // fill empty cells.
    }
}

// ------------- Invoice table for laser printer.
void TextInvoice::createTransactionTable(QTextTable * transactionTable, bool isLoadout )
{

    SetupDAO setup;
    vector<Transaction> transList = invoice->getTransactionList();
    vector<Transaction>::iterator current;

    unsigned int row = 3;
    int columnCount = 0;
    double totalColWidthPercent = 0.0;

    for (int i = 0; i< TextInvoice::ColumnCount; i++) {
        if (transactionColumns[i] != TextInvoice::IgnoreCol) {
            columnCount++;
            totalColWidthPercent+= transColWeightPrc[transactionColumns[i]];
        }
    }

    // Initialize column width in %%.
    QVector<QTextLength> columnSizeConstraints(columnCount);
    for (int i = 0; i < columnCount; i++) {
        columnSizeConstraints[i] = QTextLength(QTextLength::PercentageLength,transColWeightPrc[transactionColumns[i]]*100.0/totalColWidthPercent);
    }

    QTextTableFormat tableFormat;
    tableFormat.setBorderStyle(tableBoarderStyle);
    tableFormat.setColumnWidthConstraints(columnSizeConstraints);
    tableFormat.setCellPadding(-1);
    tableFormat.setCellSpacing(0);
    tableFormat.setAlignment(Qt::AlignLeft);
    // First row is header, which will be repeated on other pages.
    tableFormat.setHeaderRowCount( 3 );
    //Table initialized with 1 column when created, so extract it from total column count.

    tableFormat.setWidth(QTextLength(QTextLength::PercentageLength, 100));

    transactionTable->appendColumns(columnCount-1);
    transactionTable->setFormat(tableFormat);

    //Initialize header table.
    initTransactionTableHeader(transactionTable, columnCount);

    bool lastItem = false;

    unsigned int usedRows;
    int brandCount = 0;
    int footerInfoRow = 0;
    //cout << "for transList iteration" << endl;
    for(current = transList.begin(); current != transList.end(); current++)
    {
//        char abuf[20];
//        vector<Brand> blist = current->getBrandList();
//        cout << "    blist size=" << itoa(blist.size(),abuf,10) << endl;
//        // debug stuff to show brands


        if(doShowNames) {
            QString custName = QString::fromStdString(customerName(*current));
            if (! custName.trimmed().isEmpty()) {
                transactionTable->appendRows(1);
                for (int i = 0; i < columnCount; i++) {
                    setCellText(transactionTable,row, i, "");
                }
                setCellText(transactionTable,row, 0, custName.toStdString(), true,Qt::AlignLeft);
                row++;
            }
        }

        usedRows = 1;
        lastItem = (current + 1 == transList.end());
        if (!lastItem) {
            transactionTable->appendRows(1);
            for (int i = 0; i < columnCount; i++) {
                setCellText(transactionTable,row, i, "");
            }

        }

        char transNo[20];
        char head[20];
        string descrip;
        char totWt[30];
        char avgWt[30];
        char dolPerHd[30];
        char focusChar;
        char dolPerCw[30];
        char amt[30];
        string extraTags = "";
        vector<Tag> tagList;

        for (int curColumn = 0; curColumn < columnCount; curColumn ++) {

            switch (transactionColumns[curColumn]) {
            case TransNo:
                setCellText(transactionTable,row, curColumn, current->transactionNumber().toStdString());
                break;
            case Head:
                setCellText(transactionTable,row, curColumn, current->headStr().toStdString());
                break;
            case Descrip:
                descrip = current->getAnimalCode().getDescrip();
                descrip = " "+descrip;
                //TODO REVIEW !!!
                setTransCellText(transactionTable,row, curColumn, descrip,false,Qt::AlignLeft | Qt::AlignVCenter,7);
                break;
            case CustomerNo:
                setCellText(transactionTable, row, curColumn, customerNum(*current));
                break;
            case Tags:
                tagList = current->getTagList();
                usedRows = 1;
                for(unsigned int j = 0; j < tagList.size(); j++)
                {
                    if(j == 0)
                    {
                        setCellText(transactionTable,row, curColumn,tagList[j].getTag() + (tagList.size() > 1 ? "->" : ""));
                    }
                    else
                    {
                        extraTags += (j == 1 ? string("->") : string(", ")) + tagList[j].getTag();
                    }
                }

                if(extraTags.length() > 0)
                {
                    usedRows+=1;
                    transactionTable->appendRows(1);
                    setCellText(transactionTable,row+1, 1,extraTags,true,Qt::AlignLeft);
                    setCellText(transactionTable,row+1, 0,"",false,Qt::AlignLeft);
                }
                break;
            case TotWt:
                sprintf(totWt, "%ld", current->getWeight(false));
                setCellText(transactionTable,row, curColumn, totWt);
                break;
            case AvgWt:
                sprintf(avgWt, "%ld", long(current->getAverageWeight(false)));
                setCellText(transactionTable,row, curColumn, avgWt);
                break;
            case DolPerHd:
                if (!isLoadout) {
                    focusChar = (current->getMode() == Transaction::SaleHead || current->getMode() == Transaction::NoSaleHead ||
                                 current->getMode() == Transaction::ReSaleHead || current->getMode() == Transaction::SwapHead ? '*' : ' ');
                    sprintf(dolPerHd, "%0.2f%c", current->getPricePerHead(false), focusChar);
                    setCellText(transactionTable,row, curColumn, dolPerHd);
                }
                break;
            case DolPerCW:
                if (!isLoadout) {
                    focusChar = (current->getMode() == Transaction::SaleCWT || current->getMode() == Transaction::NoSaleCWT ||
                                 current->getMode() == Transaction::ReSaleCWT || current->getMode() == Transaction::SwapCWT ? '*' : ' ');

                    sprintf(dolPerCw, "%0.2f%c", current->getPricePerCWT(false), focusChar);
                    setCellText(transactionTable,row,curColumn, dolPerCw);
                }
                break;
            case Amount:
                if (!isLoadout) {
                    if(current->getMode() == Transaction::NoSaleCWT || current->getMode() == Transaction::NoSaleHead)
                    {
                        setCellText(transactionTable,row,transactionColumns[Amount], "N/S");
                    }
                    else
                    {
                        sprintf(amt, "%0.2f", current->amount());
                        setCellText(transactionTable,row, curColumn, amt,false,Qt::AlignRight);
                    }
                }
                break;
            case Pen:
                setCellText(transactionTable,row,curColumn, getPen(*current));
                break;

            }

            if (curColumn == 0) {
                setCellTextAlignment(transactionTable, row,curColumn,Qt::AlignLeft);
            }
        }

        row += usedRows;

        if(showTransactionComments && current->getComment().length() > 0 )
        {
            transactionTable->appendRows(1);
            setCellText(transactionTable,row, 0, string("     ") + current->getComment(), true,Qt::AlignLeft);
            row++;
        }

        if(showBrand)  {
            vector<Tag> tagList = current->getTagList();
            char colBuf[30];
            vector<Brand> brandList = current->getBrandList();
            // merge any brands loaded for the tags into brands loaded for the transaction
            vector<Brand>::iterator brandIt;
            vector<Brand> tagBrandList;

            for(unsigned int j = 0; j < tagList.size(); j++) {
                tagBrandList = tagList[j].getBrand();

                for(unsigned int k = 0; k < tagBrandList.size(); k++) {
                    if((brandIt = find(brandList.begin(), brandList.end(), tagBrandList[k])) == brandList.end() && !(tagBrandList[k] == 0)) {
                        brandList.push_back(tagBrandList[k]);
                    }
                }
            }

            // adjust this variable to change the available width for text between the brands
            unsigned int columnCount = 0;
            for(unsigned int i = 0; i < brandList.size(); i++) {
                transactionTable->appendRows(1);
                brandCount++;
                columnCount++;
                // add the current image to the first image line of the current brand line
                QImage brandImage = brandList[i].getBrandImage(); //.scaled(48,24);
                setTransCellImage(transactionTable,row, 0,brandImage);
                sprintf(colBuf, "%4s %4ld %4s %10s ",brandList[i].getBrandPosition().c_str(), brandList[i].getHead(), brandList[i].getTag().c_str(), brandList[i].getBurcellosisTag().c_str());
                setTransCellText(transactionTable,row,1, colBuf,true,Qt::AlignLeft);
                row++;
            }
        }
    // Process totals
        if (lastItem) {
            //Add footer rows
            transactionTable->appendRows(3);

            setCellText(transactionTable,row, 0,    "=====================================================================================================", true,Qt::AlignLeft);
            footerInfoRow = row+1;
            setCellText(transactionTable,row+2, 0,  "-----------------------------------------------------------------------------------------------------", true,Qt::AlignLeft);
            for (int curColumn = 0; curColumn < columnCount; curColumn ++) {
                setCellText(transactionTable,footerInfoRow, curColumn, ""); // Init cell with empty value first.
                switch (transactionColumns[curColumn]) {
                case TransNo:
                    if(lastItem) {   //Transactions total count
                       sprintf(transNo, "%d ", invoice->transactionListLength());
                       setCellText(transactionTable,footerInfoRow, curColumn, transNo);
                    }
                    break;
                case Head:
                    if(lastItem) {    //Head total
                        sprintf(head, "%ld", summaryHead());//totalHead);
                        setCellText(transactionTable,footerInfoRow, curColumn, head);
                    }
                    break;
                case TotWt:
                    if(lastItem) {
                        sprintf(totWt, "%ld", invoiceWeight());
                        setCellText(transactionTable,footerInfoRow,curColumn,totWt);
                    }
                    break;
                case AvgWt:
                    if(lastItem) {
                        sprintf(avgWt, "%ld", invoiceAverageWeight());
                        setCellText(transactionTable,footerInfoRow,curColumn,avgWt);
                    }
                    break;
                case DolPerHd:
                    if(lastItem) {
                        if (!isLoadout) {
                            sprintf(dolPerHd, "%0.2f%c", invoice->averageDolPerHead(),' ' );
                            setCellText(transactionTable,footerInfoRow,curColumn,dolPerHd);
                        }
                    }
                    break;
                case DolPerCW:
                    if(lastItem) {
                        if (!isLoadout) {
                            sprintf(dolPerCw, "%0.2f%c", invoice->averageDolPerCW(),' ');
                            setCellText(transactionTable,footerInfoRow,curColumn, dolPerCw);
                        }
                    }

                    break;
                case Amount:
                    if(lastItem) {
                        if (!isLoadout) {
                            sprintf(amt, "%0.2f", invoice->gross());
                            setCellText(transactionTable,footerInfoRow, curColumn, amt,false,Qt::AlignRight);
                        }
                    }

                    break;
                }
                if (curColumn == 0) {
                    setCellTextAlignment(transactionTable, row,curColumn,Qt::AlignLeft);
                }
            }
        }


    }

}

void TextInvoice::setCellTextAlignment(QTextTable* textTable, int row, int col,Qt::Alignment alignment)
{
    QTextTableCell cell = textTable->cellAt( row,col );
    if ( cell.isValid() ) {
        QTextCursor cellCursor = cell.firstCursorPosition();
        QTextBlockFormat blockFormat = cellCursor.blockFormat();
        blockFormat.setAlignment(alignment);
        cellCursor.setBlockFormat(blockFormat);
    }
}

void TextInvoice::setCellText(QTextTable* textTable, int row, int col,string text,bool span,int endSpanCol,Qt::Alignment alignment)
{
    QTextTableCellFormat tableCellFormat;
    QFont cellFont;
//
    cellFont.setFamily("Bitstream Vera Sans Mono");
    cellFont.setPointSize(8);
    cellFont.setBold(true);
    cellFont.setKerning(true);
    tableCellFormat.setFont(cellFont);

    QTextTableCell cell = textTable->cellAt( row,col );
    if ( cell.isValid() ) {
        cell.setFormat(tableCellFormat);
        QTextCursor cellCursor = cell.firstCursorPosition();
        QString cellText = QString::fromStdString(text);

        QTextBlockFormat blockFormat = cellCursor.blockFormat();
        blockFormat.setAlignment(alignment);
        cellCursor.setBlockFormat(blockFormat);

        cellCursor.insertText( cellText );
        if (span) {
            textTable->mergeCells(row,col, 1,endSpanCol);
        }
    }

}
void TextInvoice::setCellText(QTextTable* textTable, int row, int col,string text,bool span,Qt::Alignment alignment)
{
    setCellText(textTable, row,col,text, span, textTable->columns()-col+1,alignment);
}

void TextInvoice::setTransCellText(QTextTable *textTable, int row, int col, string text, bool span , Qt::Alignment alignment, int fontSize)
{
    QTextTableCellFormat tableCellFormat;
    QFont cellFont;
    cellFont.setFamily("Bitstream Vera Sans Mono");
    cellFont.setPointSize(fontSize);
    cellFont.setBold(true);
    cellFont.setKerning(true);
    tableCellFormat.setFont(cellFont);

    QTextTableCell cell = textTable->cellAt( row,col );
    if ( cell.isValid() ) {
        QTextCursor cellCursor = cell.firstCursorPosition();
        QString cellText = QString::fromStdString(text);
        QTextBlockFormat blockFormat = cellCursor.blockFormat();
        blockFormat.setAlignment(alignment);
        cellCursor.setBlockFormat(blockFormat);
        cell.setFormat(tableCellFormat);

        cellCursor.insertText( cellText );
        if (span) {
            textTable->mergeCells(row,col, 1,textTable->columns()-col+1);
        }
    }

}

void TextInvoice::setTransCellImage(QTextTable *textTable, int row, int col, QImage image, bool span , Qt::Alignment alignment)
{
    QTextTableCellFormat tableCellFormat;
    QTextTableCell cell = textTable->cellAt( row,col );
    if ( cell.isValid() ) {
        QTextCursor cellCursor = cell.firstCursorPosition();
        QTextBlockFormat blockFormat = cellCursor.blockFormat();
        blockFormat.setAlignment(alignment);
        cellCursor.setBlockFormat(blockFormat);
        cell.setFormat(tableCellFormat);

        cellCursor.insertImage( image );
        if (span) {
            textTable->mergeCells(row,col, 1,textTable->columns()-col+1);
        }
    }
}

void TextInvoice::initTransactionAlignments()
{
    transactionAlignments[TransNo]    = TextReportItem::RIGHT;
    transactionAlignments[Head]       = TextReportItem::RIGHT;
    transactionAlignments[Descrip]    = TextReportItem::CENTER;
    transactionAlignments[CustomerNo] = TextReportItem::RIGHT;
    transactionAlignments[Tags]       = TextReportItem::CENTER;
    transactionAlignments[TotWt]      = TextReportItem::RIGHT;
    transactionAlignments[AvgWt]      = TextReportItem::RIGHT;
    transactionAlignments[DolPerHd]   = TextReportItem::RIGHT;
    transactionAlignments[DolPerCW]   = TextReportItem::RIGHT;
    transactionAlignments[Amount]     = TextReportItem::RIGHT;
    transactionAlignments[Pen]        = TextReportItem::RIGHT;
}

void TextInvoice::initTransactionTableHeader(TextReportTable& transTable, int minCol, int maxCol)
{

    string labelString[TextInvoice::ColumnCount] = {"Trans", "No/Hd", "Description", customerLabel(), "Tag", "Weight", "Av.Wt.", "$/Head", "$/HW", "Amount", "Pen"};

    initTransactionAlignments();

    for(int i = 0; i < ColumnCount - 1; i++)
    {
        transTable.setColumnWidth(i, 0);
    }

    for(int i = 0; i < maxCol; i++)
   // for(int i = 0; i < ColumnCount; i++)
    {
   //     if(inBounds(COLUMNS(i), minCol, maxCol))
        {
            if (i==0) //First column always aligned left
            {
                transTable.setColumnAlignment(i, TextReportItem::LEFT);
            }
            else {
                transTable.setColumnAlignment(i, transactionAlignments[transactionColumns[i]]);
            }
            transTable.setColumnWidth(i, transColWidth(COLUMNS(transactionColumns[i])));
            transTable.setHeader(i,string(" " + labelString[transactionColumns[i]]));
        }
    }
}

void TextInvoice::initTransactionTableHeader(QTextTable *transTable, int colCount)
{
    string labelString[TextInvoice::ColumnCount] = {"Trans", "No/Hd", "Description", customerLabel(), "Tag", "Weight", "Av.Wt", "$/Head", "$/HW", "Amount", "Pen"};

    transTable->appendRows(3); //Header rows
    setCellText(transTable,0,0,"-----------------------------------------------------------------------------------------------------",true,Qt::AlignLeft);
    setCellText(transTable,2,0,"-----------------------------------------------------------------------------------------------------",true,Qt::AlignLeft);
    Qt::Alignment alignCell;
    for(int i = 0; i < colCount; i++) {
        if (i == 0 ) {
            alignCell = Qt::AlignLeft;
        }
        else {
            alignCell = Qt::AlignRight;
        }
      setCellText(transTable,1,i,labelString[transactionColumns[i]],false,0,alignCell);
    }
}


string TextInvoice::customerName(Transaction trans)
{
    return "";
}



TextReportTable TextInvoice::transactionTable(bool isLoadout)
{
    SetupDAO setup;
    //cout << "ENTERING TextInvoice::transactionTable" << endl;
    vector<Transaction> transList = invoice->getTransactionList();
    vector<Transaction>::iterator current;

    unsigned int row = 0;

    int columnCount = 0;
    for (int i = 0; i< TextInvoice::ColumnCount; i++) {
        if (transactionColumns[i] != TextInvoice::IgnoreCol) {
            columnCount++;
        }
    }



    //   int maxCol = getMaxTransCol();
    //   int minCol = getMinTransCol();

    int maxCol = columnCount;
    int minCol = 0;




    //    TextReportTable transTable(maxCol + 1);
    TextReportTable transTable(columnCount);
    transTable.setSurroundingText(string(1, char(27)) + string(1, char(77)), string(1, char(27)) + string(1, char(80)));

    initTransactionTableHeader(transTable, 0, columnCount);
    transTable.adjustWidth(ColNumber);


    if(transFitColumns != 0)
    {
        //cout << "retrofitting transaction table: " << transFitColumns << ", " << transFitLength << endl;
        transTable.retroFitColumns(transFitColumns, transFitLength);
    }

    bool lastItem = false;

    transTable.setFooterSeperator('=', '-');
    transTable.setFooterStyle(TextReportTable::Continuous, TextReportTable::Continuous);
    unsigned int usedRows;
    int brandCount = 0;
    //cout << "for transList iteration" << endl;
    for(current = transList.begin(); current != transList.end(); current++)
    {
        //cout << "...next transList" << endl;

        // debug stuff to show brands
        //vector<Brand> Transaction::getBrandList()
        char abuf[20];
        vector<Brand> blist = current->getBrandList();
//        cout << "    blist size=" << itoa(blist.size(),abuf,10) << endl;
        // debug stuff to show brands


        if(doShowNames){
            QString custName = QString::fromStdString(customerName(*current));
            if (! custName.trimmed().isEmpty()) {
                transTable.insertRows(1);
                transTable.setText(row, 0, custName.toStdString() , true);
                row++;
            }
        }

        transTable.insertRows(1);
        usedRows = 1;
        lastItem = (current + 1 == transList.end());

        for (int curColumn = 0; curColumn < columnCount; curColumn ++) {

            int currentColumn = transactionColumns[curColumn];

            if( currentColumn == TransNo )
            {
                char transNo[20];

                if(current->swapped())
                {
                    sprintf(transNo, "%ld-%cS", current->getId(), (current->isManual() ? 'M' : ' '));
                }
                else
                {
                    sprintf(transNo, "%ld%c", current->getId(), (current->isManual() ? 'M' : ' '));
                }

                setTransItem(transTable, row, curColumn, transNo);

                if(lastItem)
                {
                    sprintf(transNo, "%d", invoice->transactionListLength());
                    transTable.setFooter(curColumn, transNo);
                }
                //cout << "transNo buffer: " << transNo << endl;
            }

            if( currentColumn == Head )
            {
                char head[20];
                if(current->getAnimalCode().isPair())
                {
                    sprintf(head, "%ld/%ld", current->getHead(false, false), current->getHead(false, false));
                }
                else
                {
                    sprintf(head, "%ld", current->getHead(false, false));
                }

                //      totalHead += current->getHead(true);

                setTransItem(transTable, row, curColumn, head);

                if(lastItem)
                {
                    char totHead[20];
                    sprintf(totHead, " %ld", summaryHead());//totalHead);
                    transTable.setFooter(curColumn, totHead);
                }
            }

            if( currentColumn == Descrip )
            {
                string descrip = current->getAnimalCode().getDescrip();

                unsigned int oldLength = transTable.columnWidth(transactionColumns[Descrip]);
                unsigned int newLength = oldLength;
                double availableInches = double(oldLength) / 12.000;
                newLength = 18.000 * availableInches;
                descrip = descrip.substr(0, newLength);
                descrip = descrip + string((newLength + 1) - descrip.length(), ' ');

                if (setup.getBoolean("printAllCondensed"))
                {
                    // don't turn on or off the condensed print
                    descrip = " " + descrip ;
                } else {
                    descrip = string(1, char(15)) + " " + descrip + string(1, char(18));// + string(1, char(27)) + string(1, char(77));
                }

                transTable.setText(row, curColumn, descrip, false, false);
                //      setTransItem(transTable, row, Descrip, descrip);
            }

            if( currentColumn == CustomerNo )
            {
                setTransItem(transTable, row, curColumn, customerNum(*current));
            }


            if( currentColumn == Tags )
            {
                vector<Tag> tagList = current->getTagList();
                usedRows = 1;
                string extraTags = "";
                for(unsigned int j = 0; j < tagList.size(); j++)
                {
                    if(j == 0)
                    {
                        setTransItem(transTable, row, curColumn, tagList[j].getTag() + (tagList.size() > 1 ? "->" : ""));
                    }
                    else
                    {
                        extraTags += (j == 1 ? string("->") : string(", ")) + tagList[j].getTag();
                    }
                }

                int currentCol = 1;
                int currentRow = row + 1;
                string tagBuf = "";

                if(extraTags.length() > 0)
                {
                    transTable.insertRows(1);
                }

                for(unsigned int i = 0; i < extraTags.length(); i++)
                {
                    if(tagBuf.length() == transTable.columnWidth(curColumn))
                    {
                        transTable.setText(currentRow, currentCol, tagBuf);
                        tagBuf = "";
                        currentCol++;

                        if(currentCol > maxCol && i < extraTags.length() - 1)
                        {
                            transTable.insertRows(1);
                            currentCol = 1;
                            currentRow++;
                            usedRows++;
                        }
                    }

                    tagBuf += extraTags[i];

                    if(i == extraTags.length() - 1)
                    {
                        transTable.setText(currentRow, currentCol, tagBuf + string(transTable.columnWidth(curColumn) - tagBuf.length(), ' '));
                        usedRows++;
                    }
                }

            }

            if( currentColumn == TotWt )
            {
                char totWt[30];
                sprintf(totWt, "%ld", current->getWeight(false));
                setTransItem(transTable, row, curColumn, totWt);
                //      totalTotWeight += current->getWeight();

                if(lastItem)
                {
                    sprintf(totWt, " %ld", invoiceWeight()); //totalTotWeight /*/ invoice->transactionListLength()*/);
                    transTable.setFooter(curColumn, totWt);
                }
            }

            if( currentColumn == AvgWt )
            {
                char avgWt[30];
                sprintf(avgWt, "%ld", long(current->getAverageWeight(false)));
                setTransItem(transTable, row, curColumn, avgWt);
                //      totalAvgWeight += long(current->getAverageWeight());

                if(lastItem)
                {
                    sprintf(avgWt, " %ld", invoiceAverageWeight());
                    transTable.setFooter(curColumn, avgWt);
                }
            }

            if( currentColumn == DolPerHd )
            {
                if (!isLoadout) {
                    char dolPerHd[30];

                    char focusChar = (current->getMode() == Transaction::SaleHead || current->getMode() == Transaction::NoSaleHead ||
                                      current->getMode() == Transaction::ReSaleHead || current->getMode() == Transaction::SwapHead ? '*' : ' ');

                    sprintf(dolPerHd, "%0.2f%c", current->getPricePerHead(false), focusChar);
                    //    totalDolPerHd += (current->getPricePerHead() / invoice->transactionListLength());
                    setTransItem(transTable, row, curColumn, dolPerHd);

                    if(lastItem)
                    {
                        sprintf(dolPerHd, " %0.2f ", invoice->averageDolPerHead());
                        transTable.setFooter(curColumn, dolPerHd);
                    }
                }
            }


            if( currentColumn == DolPerCW )
            {
                if (!isLoadout) {
                    char dolPerCw[30];
                    char focusChar = (current->getMode() == Transaction::SaleCWT || current->getMode() == Transaction::NoSaleCWT ||
                                      current->getMode() == Transaction::ReSaleCWT || current->getMode() == Transaction::SwapCWT ? '*' : ' ');

                    sprintf(dolPerCw, "%0.2f%c", current->getPricePerCWT(false), focusChar);
                    setTransItem(transTable, row, curColumn, dolPerCw);
                    //      totalDolPerCW += current->getPricePerCWT();

                    if(lastItem)
                    {
                        sprintf(dolPerCw, " %0.2f ", invoice->averageDolPerCW());
                        transTable.setFooter(curColumn, dolPerCw);
                    }
                }
            }

            if( currentColumn == Amount )
            {
                if (!isLoadout) {
                    char amt[30];
                    if(current->getMode() == Transaction::NoSaleCWT || current->getMode() == Transaction::NoSaleHead)
                    {
                        setTransItem(transTable, row, curColumn, "N/S");
                    }
                    else
                    {
                        sprintf(amt, "%0.2f", current->amount());
                        setTransItem(transTable, row, curColumn, amt);
                        //	totalAmount += current->amount();
                    }

                    if(lastItem)
                    {
                        sprintf(amt, " %0.2f", invoice->gross());//totalAmount);
                        transTable.setFooter(curColumn, amt);
                    }
                }
            }

            if( currentColumn == Pen)
            {
                setTransItem(transTable, row, curColumn, getPen(*current));
            }
        }
        row += usedRows;

        if(showTransactionComments && current->getComment().length() > 0 )
        {
            transTable.insertRows(1);
            transTable.setText(row, 0, string("     ") + current->getComment(), true);
            row++;
        }

        if(showBrand)
        {
            char dbuf[100];

            vector<Tag> tagList = current->getTagList();
            string imageLine;

            string imageLine1, imageLine2, imageLine3;
            char colBuf[30];
            string textLine1, textLine2, textLine3;
            string temp;
            vector<Brand> brandList = current->getBrandList();

            //cout << "showBrand  taglist size=" << itoa(tagList.size(),dbuf,10) << "  brandList size=" << itoa(brandList.size(),dbuf,10) << endl;

            // merge any brands loaded for the tags into brands loaded for the transaction
            vector<Brand>::iterator brandIt;
            vector<Brand> tagBrandList;


            for(unsigned int j = 0; j < tagList.size(); j++)
            {
                //cout << "loop through tagList.size : " << itoa(j,dbuf,10) << endl;
                tagBrandList = tagList[j].getBrand();

                for(unsigned int k = 0; k < tagBrandList.size(); k++)
                {
                    //cout << "loop through tagBrandList.size : " << itoa(k,dbuf,10) << endl;
                    if((brandIt = find(brandList.begin(), brandList.end(), tagBrandList[k])) == brandList.end() && !(tagBrandList[k] == 0))
                    {
                        brandList.push_back(tagBrandList[k]);
                        //cout << "brandList.push_back entry k, tagBrandList size=" << itoa(tagBrandList.size(),dbuf,10) << endl;
                    }
                    //	  else if((brandIt = find(brandList.begin(), brandList.end(), tagList[j].getTag())) != brandList.end())
                    //	  {
                    //	    brandIt->setBurcellosisTag(tagList[j].getBurcellosisTag());
                    //	  }
                }
            }

            // adjust this variable to change the available width for text between the brands

            unsigned int brandTextWidth = 40;
            unsigned int columnCount = 0;
            string spacer = string(7, ' ');

            for(unsigned int i = 0; i < brandList.size(); i++)
            {
                brandCount++;
                columnCount++;
                //cout << "brandCount: " << itoa(brandCount,dbuf,10) << "  columnCount: " << itoa(columnCount,dbuf,10) <<  "  brandList id: " << ltoa(brandList[i].getId(),dbuf,10) <<  endl;

                // add the current image to the first image line of the current brand line

                string buf = brandList[i].brandImageToPrintMatrix().substr(0, 48);
                buf = string(1, char(27)) + string(1, 'L') + string(1, char(48)) + string(1, char(0)) + buf;
                imageLine1 += buf + string(brandTextWidth, ' ');


                sprintf(colBuf, "%4ld %4s %10s ", brandList[i].getHead(), brandList[i].getTag().c_str(), brandList[i].getBurcellosisTag().c_str());
                //cout << "printing colBuf: " << colBuf << endl;

                // ensure that the data fits in the width allotted
                temp = string(colBuf);

                if(brandTextWidth > temp.length())
                {
                    temp += string(brandTextWidth - temp.length(), ' ');
                }

                if(temp.length() > brandTextWidth)
                {
                    temp = temp.substr(0, brandTextWidth);
                }

                textLine1 += string(4, ' ') + temp;

                //	  sprintf(colBuf, "H %ld", brandList[i].getHead());
                sprintf(colBuf, "%4s", brandList[i].getBrandPosition().c_str());

                temp = string(colBuf);

                if(brandTextWidth > temp.length())
                {
                    temp += string(brandTextWidth - temp.length(), ' ');
                }

                if(temp.length() > brandTextWidth)
                {
                    temp = temp.substr(0, brandTextWidth);
                }

                // skip over the image in the 2nd text line
                textLine2 +=  string(4, ' ') + temp;

                buf = brandList[i].brandImageToPrintMatrix().substr(48, 48);
                buf = string(1, char(27)) + string(1, 'L') + string(1, char(48)) + string(1, char(0)) + buf;
                imageLine2 += buf + string(brandTextWidth, ' ') ;

                //	  sprintf(colBuf, "P %s", brandList[i].getBrandPosition().c_str());
                sprintf(colBuf, "");

                temp = string(colBuf);

                if(brandTextWidth > temp.length())
                {
                    temp += string(brandTextWidth - temp.length(), ' ');
                }

                if(temp.length() > brandTextWidth)
                {
                    temp = temp.substr(0, brandTextWidth);
                }

                // skip over the image in the 3rd text line
                textLine3 += string(4, ' ') + temp;

                buf = brandList[i].brandImageToPrintMatrix().substr(ColNumber);
                buf = string(1, char(27)) + string(1, 'L') + string(1, char(48)) + string(1, char(0)) + buf;
                imageLine3 += buf + string(brandTextWidth, ' ');

                if(columnCount == (80 / brandTextWidth) - 1 || i == brandList.size() - 1)
                {
                    columnCount = 0;
                    string jump = string(1, char(27)) + string(1, 'J');

                    // merge the text lines and image lines, inserting line jump commands for the epson printer command set.

                    imageLine =  spacer + imageLine1 + "\r"; // don't have to calculate jump here, as first image line is on same line as first text line
                    imageLine += spacer + textLine1  + jump + string(1, char(21)) + "\r";
                    imageLine += spacer + imageLine2 + jump + string(1, char(3)) + "\r";
                    imageLine += spacer + textLine2  + jump + string(1, char(18)) + "\r";
                    imageLine += spacer + imageLine3 + jump + string(1, char(6)) + "\r";
                    imageLine += spacer + textLine3  + "\n";

                    transTable.appendPlainText(row - 1, imageLine);
                    transTable.increasePlainTextLineCount(row - 1, 3.00);
                    imageLine1 = imageLine2 = imageLine3 = textLine1 = textLine2 = textLine3 = "";
                }
            }

        }
    }
    //cout << "return transTable" << endl;
    return transTable;
}

long TextInvoice::invoiceWeight()
{
    return invoice->weight();
}



long TextInvoice::invoiceAverageWeight()
{
    return invoice->averageWeight();
}




long TextInvoice::summaryHead()
{
    return invoice->head(true, true);
}


void TextInvoice::setTransItem(TextReportTable &transTable, unsigned int row, int column, string text, int columnOffset)
{
  //transTable.setText(row, transactionColumns[column] + columnOffset, " " + text);
  transTable.setText(row, column + columnOffset, " " + text);
}

bool TextInvoice::inBounds(COLUMNS col, int min, int max)
{
    return (transactionColumns[col] >= min && transactionColumns[col] <= max);
}


int TextInvoice::getMaxTransCol()
{
    int maxTrans = 0;

    for(int i = 0; i < 11; i++)
    {
        if(transactionColumns[i] > maxTrans)
        {
            maxTrans = transactionColumns[i];
        }
    }

    if(maxTrans > 11)
    {
        maxTrans = 11;
    }

    return maxTrans;
}

int TextInvoice::getMinTransCol()
{
    int minTrans = 11;

    for(int i = 0; i < 12; i++)
    {
        if(transactionColumns[i] < minTrans)
        {
            minTrans = transactionColumns[i];
        }
    }

    if(minTrans < 0)
    {
        minTrans = 0;
    }

    return minTrans;
}

void TextInvoice::setTransColumns(int transCol,    int headCol,     int descripCol,
                                  int customerNoCol, int tagCol,
                                  int totWtCol,    int avgWtCol,    int dolPerHeadCol,
                                  int dolPerCWCol, int amountCol,   int penCol )
{


//    transactionColumns[TransNo]    = transCol;
//    transactionColumns[Head]       = headCol;
//    transactionColumns[Descrip]    = descripCol;
//    transactionColumns[CustomerNo] = customerNoCol;
//    transactionColumns[Tags]       = tagCol;
//    transactionColumns[TotWt]      = totWtCol;
//    transactionColumns[AvgWt]      = avgWtCol;
//    transactionColumns[DolPerHd]   = dolPerHeadCol;
//    transactionColumns[DolPerCW]   = dolPerCWCol;
//    transactionColumns[Amount]     =  amountCol;
//    transactionColumns[Pen]        = penCol;

    transColCount = 0;

    for(int i = 0; i < ColumnCount; i++)
    {
        if(0 <= transactionColumns[i] && transactionColumns[i] < ColumnCount)
        {
            transColCount += transColWeight[i];
        }
    }

    remainingTransCols = ColNumber - transColCount;

    clearTables();
    addTable(getInvoiceTable());
    addTable(transactionTable());
    noSaleTable();
    addTable(summaryTable());
    //  addTable(totalTable());
    addTable(prorateTable());
    addTable(footerTable());

    if ( isBuyerInvoice && showTags ) {
        //cout << "adding tags table for buyers invoice" << endl;
        addTable(getTagsTable());
    }
    addTable(createDisclaimerTable());

    setPageHeader(pageHeader());

    //----------- Laser printer support -------
    m_invoiceDoc.clear();
    QTextCursor cursor(&m_invoiceDoc);
    //Information about market
    QTextTable* marketInfoTable = cursor.insertTable( 1,1);
    createMarketInfoTable(marketInfoTable);
    //cursor.movePosition( QTextCursor::End );
    cursor.movePosition( QTextCursor::Down);

    //Information about customer
    QTextTable* customerInfoTable = cursor.insertTable( 1,1);
    createCustomerInfoTable(customerInfoTable);
    cursor.movePosition( QTextCursor::Down);
    //cursor.movePosition( QTextCursor::End );
    //Transaction table
    QTextTable* transactiondTable = cursor.insertTable( 1,1);
    createTransactionTable(transactiondTable);
    cursor.movePosition( QTextCursor::Down);
    //cursor.movePosition( QTextCursor::End );

    long noSaleHead = invoice->noSaleHead(true);
    if (noSaleHead != 0) {
        //NoSale Table
        QTextTable* noSaleTable = cursor.insertTable( 1,1);
        createNoSaleTable(noSaleTable);
        cursor.movePosition( QTextCursor::Down);
        //cursor.movePosition( QTextCursor::End );
    }
    //Summary table
    QTextTable* summaryTbl = cursor.insertTable( 1,1);
    createSummaryTable(summaryTbl);
    cursor.movePosition( QTextCursor::Down);
    //cursor.movePosition( QTextCursor::End );

    //Prorate Table
    QTextTable* proRateTbl = cursor.insertTable( 1,1);
    createProrateTable(proRateTbl);
    cursor.movePosition( QTextCursor::Down);
    //cursor.movePosition( QTextCursor::End );

    //Footer table
    QString footerStr = QString::fromStdString(footerString);
    if (!footerStr.trimmed().isEmpty()) {
        QTextTable* footerTbl = cursor.insertTable( 1,1);
        createFooterTable(footerTbl);
        cursor.movePosition( QTextCursor::Down);
        //cursor.movePosition( QTextCursor::End );
    }

    if ( isBuyerInvoice && showTags ) {
        //Tags table
        QTextTable* tagsTable = cursor.insertTable( 1,1);
        createTagsTable(tagsTable);
        cursor.movePosition( QTextCursor::Down);
        //cursor.movePosition( QTextCursor::End );
    }

    createDisclaimerTable(cursor);
    cursor.movePosition( QTextCursor::Down);
    //cursor.movePosition( QTextCursor::End );


    { // Loadout support

        clearTables(true);
        addTable(getInvoiceTable(),true);
        addTable(transactionTable(true),true);
        noSaleTable();
        //addTable(summaryTable(),true);
        //  addTable(totalTable());
//        addTable(prorateTable(),true);
        addTable(footerTable(),true);

        if ( isBuyerInvoice && showTags ) {
            //cout << "adding tags table for buyers invoice" << endl;
            addTable(getTagsTable(),true);
        }

        setPageHeader(pageHeader());



        //----------- Laser printer support -------
        m_loadOutDoc.clear();
        QTextCursor cursor(&m_loadOutDoc);
        //Information about market
        QTextTable* marketInfoTable = cursor.insertTable( 1,1);
        createMarketInfoTable(marketInfoTable);
        cursor.movePosition( QTextCursor::End );
        //Information about customer
        QTextTable* customerInfoTable = cursor.insertTable( 1,1);
        createCustomerInfoTable(customerInfoTable);
        cursor.movePosition( QTextCursor::End );
        //Transaction table
        QTextTable* transactiondTable = cursor.insertTable( 1,1);
        createTransactionTable(transactiondTable,true);
        cursor.movePosition( QTextCursor::End );

        long noSaleHead = invoice->noSaleHead(true);
        if (noSaleHead != 0) {
            //NoSale Table
            QTextTable* noSaleTable = cursor.insertTable( 1,1);
            createNoSaleTable(noSaleTable);
            cursor.movePosition( QTextCursor::End );
        }
        //Summary table
/*
        QTextTable* summaryTable = cursor.insertTable( 1,1);
        createSummaryTable(summaryTable,true);
        cursor.movePosition( QTextCursor::End );

        //Prorate Table
        QTextTable* proRateTable = cursor.insertTable( 1,1);
        createProrateTable(proRateTable);
        cursor.movePosition( QTextCursor::End );
*/
        //Footer table
        QTextTable* footerTbl = cursor.insertTable( 1,1);
        createFooterTable(footerTbl);
        cursor.movePosition( QTextCursor::End );

        if ( isBuyerInvoice && showTags ) {
            //Tags table
            QTextTable* tagsTable = cursor.insertTable( 1,1);
            createTagsTable(tagsTable);
            cursor.movePosition( QTextCursor::End );
        }


    }



}

void TextInvoice::noSaleTable()
{
}

// Virtual function, overloaded in derived classes
void TextInvoice::createNoSaleTable(QTextTable * noSaleTable)
{
    QTextTableFormat tableFormat;
    tableFormat.setBorderStyle(tableBoarderStyle);
    noSaleTable->setFormat(tableFormat);
}

void TextInvoice::setTransColumns(vector<int> colList)
{
    if(colList.size() < ColumnCount)
    {
        return;
    }

    int k = 0;
    for (int i =0; i< colList.size(); i++) {
        if (colList[i] != IgnoreCol) {
            transactionColumns[k] = colList[i];
            k++;
        }
    }
    for (int i=k; i< colList.size(); i++) {
        transactionColumns[i] = IgnoreCol;
    }



    setTransColumns(colList[TransNo], colList[Head], colList[Descrip], colList[CustomerNo],
                    colList[Tags], colList[TotWt], colList[AvgWt], colList[DolPerHd],
                    colList[DolPerCW], colList[Amount], colList[Pen]);
}

TextReportTable TextInvoice::summaryTable()
{
    vector<ChargeRecord> chargeList = invoice->getChargeRecordList(true);
    sort(chargeList.begin(), chargeList.end(), ChargeRecord::compareIdsLT);

    vector<ChargeRecord>::iterator currentChg;
    TextReportTable summary(5);
    summary.setFooterSeperator('=', ' ');

    summary.setColumnWidth(0, 20);
    summary.setColumnWidth(1, 15);
    summary.setColumnWidth(2, 10);
    summary.setColumnWidth(3, 20);
    summary.setColumnWidth(4, 15);

    summary.setColumnAlignment(0, TextReportItem::LEFT);
    summary.setColumnAlignment(1, TextReportItem::RIGHT);

    summary.setColumnAlignment(3, TextReportItem::LEFT);
    summary.setColumnAlignment(4, TextReportItem::RIGHT);

    summary.setFooterStyle(TextReportTable::ContinuousBroken, TextReportTable::Broken);

    double chargeTotal = 0.0;
    unsigned int row = 0;
    char chgStr[30];
    unsigned int col = 0;
    summary.insertRows(1);

    initSummaryCoords(row, col);

    double commission = invoice->getCommissionTotal();
    vector<ChargeRecord>::iterator commLoc = find(chargeList.begin(), chargeList.end(), 0);

    if(commLoc == chargeList.end())
    {
        cerr << "error finding commission charge record" << endl;
    }

    for(currentChg = chargeList.begin(); currentChg != chargeList.end() && commLoc != chargeList.end(); currentChg++)
    {
        if(currentChg->isCommissionCharge())
        {
            commLoc->increaseTotal(currentChg->getAdjustedTotal());
        }
    }

    chargeList.insert(chargeList.begin() + 1, ChargeRecord(0, "Trucking"  , invoice->truckingTotal()));


    if(groupChargesByName)
    {
        vector<ChargeRecord> tempList;

        for(unsigned int i = 0; i < chargeList.size(); i++)
        {
            if(tempList.size() == 0 || chargeList[i].getDescrip() != tempList.back().getDescrip())
            {
                tempList.push_back(chargeList[i]);
            }
            else
            {
                tempList.back().increaseTotal(chargeList[i].getTotal());
            }
        }

        chargeList = tempList;
    }

    for(currentChg = chargeList.begin(); currentChg != chargeList.end(); currentChg++)
    {
        if(!currentChg->isCommissionCharge())
        {
            if(currentChg->getId() == 0 || currentChg->getAdjustedTotal() < -0.009 || currentChg->getAdjustedTotal() > 0.009)
            {
                sprintf(chgStr, "%0.2f", currentChg->getAdjustedTotal());
                summary.setText(row, col, currentChg->getDescrip());
                summary.setText(row, col + 1, chgStr);
                chargeTotal += currentChg->getAdjustedTotal();

                if(currentChg->getId() == 0 && currentChg->getDescrip() == "Trucking")
                {
                    vector<TruckingRecord> truckingList = invoice->getTruckingList();

                    for(unsigned int j = 0; j < truckingList.size(); j++)
                    {
                        summary.insertRows(1);
                        row++;
                        summary.setText(row, 3, "TRUCKER");
                        summary.setText(row, 4, truckingList[j].getTruckerName());
                    }
                }

                if(currentChg + 1 != chargeList.end())
                {
                    updateSummaryCoords(row, col, summary);
                }
            }
        }
    }

    summary.insertRows(3);
    summary.setText(row + 1, 3, string(35, '='), true);
    summary.setText(row + 2, 3, summaryChargeTotalLabel());
    summary.setText(row + 2, 4, chargeTotal);
    summary.setText(row + 3, 3, summaryTotalLabel());
    summary.setText(row + 3, 4, totalValue());
    row += 3;

    if(doShowSexSummary())
    {
        sexSummaryLine(summary, row);
    }

    overallAverageLine(summary, row);

    //  summary.setFooter(3, "Total Fees: ");
    //  sprintf(chgStr, "%0.2f", chargeTotal);
    //  summary.setFooter(4, chgStr);

    return summary;
}

/*
 * don't give our users any nasty surprises
 * default of seller invoice is to show the sex summary
 * default of buyer invoice is to hide the sex summary
 */

bool TextInvoice::doShowSexSummary()
{
    return false;
}



TextReportTable TextInvoice::footerTable()
{
    TextReportTable table(1);

    table.setHeaderStyle(TextReportTable::NoHeader, TextReportTable::NoHeader);
    table.setFooterStyle(TextReportTable::NoHeader, TextReportTable::NoHeader);

    table.setColumnWidth(0, 79);
    table.setColumnAlignment(0, TextReportTable::CENTER);
    string buf;

    string temp = footerString;
    unsigned int row = 0;
    int i = 0;

    do
    {
        i = temp.find_first_of("\n");

        if(i != string::npos)
        {
            if(i == 0)
            {
                buf = " ";
            }
            else
            {
                buf = temp.substr(0, i);
            }

            if(i + 1 < temp.length())
            {
                temp = temp.substr(i + 1);
            }
            else
            {
                temp = "";
            }
        }
        else
        {
            buf = temp;
        }

        if(buf.length() > 0)
        {
            table.insertRows(1);
            table.setText(row, 0, buf);
            row++;
        }

    }while(i != string::npos);

    return table;
}

void TextInvoice::initSummaryCoords(unsigned int& row, unsigned int& col)
{
    row = 0;
    col = 0;
}

void TextInvoice::initSummaryCoordsLaser(unsigned int& row, unsigned int& col)
{
    row = 0;
    col = 0;
}




void TextInvoice::updateSummaryCoords(unsigned int& row, unsigned int& col, TextReportTable& summary)
{
    row = 0;
    col = 0;
    summary.insertRows(0);
}
void TextInvoice::updateSummaryCoords(unsigned int& row, unsigned int& col, unsigned int & appendRows)
{
    row = 0;
    col = 0;
    appendRows = 0;
}



string TextInvoice::summaryChargeTotalLabel()
{
    return "CHARGE TOTAL";
}

string TextInvoice::summaryTotalLabel()
{
    return "INVOICE TOTAL";
}




void TextInvoice::sexSummaryLine(TextReportTable& summary, unsigned int& row)
{
    SetupDAO setup;

    vector<AnimalCode> uniqueSexList = invoice->getUniqueSexList();
    string label  = "TYPE   HD  AVG  $/cwt";
    string footer = "----- --- ---- ------";


    label += string(" ") + label;
    footer += string(" ") + footer;

    char buf[60];
    string line;
    long headCount = 0;

    bool headerPrinted = false;

    for(int i = 0; i < uniqueSexList.size(); i++)
    {
        headCount = invoice->getSexHead(uniqueSexList[i]);

        if(headCount > 0)
        {
            sprintf(buf, "%5s%4ld%5ld%7.2f", uniqueSexList[i].getTypeDescrip().substr(0, 5).c_str(), headCount, invoice->getSexAverageWeight(uniqueSexList[i]), invoice->getSexAvgDolPerCWT(uniqueSexList[i]));
            line += (line.length() > 0 ? string(" ") : string("")) + buf;
        }


        if(line.length() > strlen(buf) || (i == uniqueSexList.size() - 1 && line.length() > 0))
        {

            if(!headerPrinted)
            {
                headerPrinted = true;

                summary.setText(row - 2, 0, label, true);
                summary.setText(row - 1, 0, footer, true);
            }

            summary.setText(row, 0, line, true);
            line = "";
            summary.insertRows(1);
            row++;
        }
    }

    if(headerPrinted)
    {
        string disclaimer;
        if ( setup.getBoolean("printAllCondensed") ) {
            // don't turn on or off condensed print
            disclaimer = "Sex Summary DOES NOT include sales by Head";
        } else {
            disclaimer = string(1, char(15)) + "Sex Summary DOES NOT include sales by Head" + string(
                        1, char(18));
        }
        summary.setText(row, 0, disclaimer, true);
    }

}

void TextInvoice::overallAverageLine(TextReportTable& summary, unsigned int& row)
{
}

//Virtual function , called in derived class
void TextInvoice::overallAverageLine(QTextTable * summaryTable, unsigned int& row)
{

}


TextReportTable TextInvoice::totalTable()
{
    TextReportTable totalLine(3);
    totalLine.setColumnWidth(0, 45);
    totalLine.setColumnWidth(1, 20);
    totalLine.setColumnWidth(2, 15);

    totalLine.insertRows(1);
    totalLine.setColumnAlignment(1, TextReportTable::LEFT);
    totalLine.setColumnAlignment(2, TextReportTable::RIGHT);

    char total[30];
    sprintf(total, "%0.2f", totalValue());
    totalLine.setText(0, 1, "TOTAL: ");
    totalLine.setText(0, 2, total);
    return totalLine;
}

TextReportTable TextInvoice::prorateTable()
{
    return TextReportTable();
}

TextReportTable TextInvoice::createDisclaimerTable()
{
    return TextReportTable();
}



// void TextInvoice::setTransColumns(COLUMNS col0, COLUMNS col1, COLUMNS col2, 
//                      COLUMNS col3, COLUMNS col4, COLUMNS col5,
//                      COLUMNS col6, COLUMNS col7, COLUMNS col8,
//                      COLUMNS col9, COLUMNS col10, COLUMNS col11)
// {
//   for(int i = 0; i < 13; i++)
//   {
//     transactionColumns[i] = IgnoreCol;
//   }

//   transactionColumns[col0] = 0;
//   transactionColumns[col1] = 1;
//   transactionColumns[col2] = 2;
//   transactionColumns[col3] = 3;
//   transactionColumns[col4] = 4;
//   transactionColumns[col5] = 5;
//   transactionColumns[col6] = 6;
//   transactionColumns[col7] = 7;
//   transactionColumns[col8] = 8;
//   transactionColumns[col9] = 9;
//   transactionColumns[col10] = 10;
//   transactionColumns[col11] = 11;

//     clearTables();
//     addTable(getInvoiceTable());
//     addTable(transactionTable());
//     addTable(summaryTable());
//     addTable(totalTable());
// }

string TextInvoice::getPen(Transaction trans)
{
    return trans.getSellerPen();
}

unsigned int TextInvoice::transColWidth(COLUMNS column)
{
    unsigned int extra = 0;
    if(remainingTransCols > 0)
    {
        extra = 1;
        remainingTransCols--;
    }

    return (unsigned int)((transColWeight[column] * ColNumber / transColCount) );// + extra;
}


double TextInvoice::totalValue()
{
    return invoice->net();
}



string TextInvoice::customerNum(Transaction trans)
{
    return "ERROR";
}



string TextInvoice::customerLabel()
{
    return "Customer";
}



string TextInvoice::customerString()
{
    return "Customer";
}



int TextInvoice::getTransLineCount(int maxCol, TextReportTable& transTable)
{
    vector<Transaction> transList = invoice->getTransactionList();
    vector<Tag> tagList;

    int lineCount = 0;
    int temp = 0;

    for(unsigned int i = 0; i < transList.size(); i++)
    {
        if(doShowNames)
        {
            lineCount++;
        }

        tagList = transList[i].getTagList();
        temp = 0;

        for(unsigned int j = 1; j < tagList.size(); j++)
        {
            temp += (string(", ") + tagList[j].getTag()).length();
        }

        lineCount += 1 + (temp > 0 ? (temp / (80 - transTable.columnWidth(0))) + 1 : 0) ;
    }

    return lineCount;
}

string TextInvoice::mortgageString()
{
    return "";
}

string TextInvoice::companyString()
{
    return "";
}


string TextInvoice::statusString()
{
    return "";
}



/////////////////////////////////////////////////
// tags lines on bottom of invoice

TextReportTable TextInvoice::getTagsTable()
{
    vector<Transaction> transList = invoice->getTransactionList();
    vector<Transaction>::iterator current;

    vector<Tag> allTagsList;

    int columnsize = 78;

    TextReportTable tagsTable(2);

    if ( isBuyerInvoice && showTags )
    {
        tagsTable.setColumnWidth(0, 2);
        tagsTable.setColumnWidth(1, columnsize);

        // stuff all the tags for the transaction into one list
        for(current = transList.begin(); current != transList.end(); current++)
        {
            vector<Tag> tagList = current->getTagList();
            for(unsigned int i = 0; i < tagList.size(); i++)
            {
                allTagsList.push_back(tagList[i].getTag());
            }
        }

        sort(allTagsList.begin(), allTagsList.end(), Tag::compareTagsLT);

        // build a string with the tags that is less than columnsize.
        // When it exceeds columnsize put that string in tagsTable,
        // reset the string and continue with the rest of the tags.
        string allTags = "";
        unsigned int currentrow = 0;
        for(unsigned int j = 0; j < allTagsList.size(); )
        {
            string addtag = allTagsList[j].getTag();
            // << " working on tag " << addtag << "  for j=" << j << endl;
            if ( allTags.length() + addtag.length() + 2 > columnsize )
            {
                // stop the line here and add to table
                tagsTable.insertRows(1);
                tagsTable.setText(currentrow, 0, "");
                tagsTable.setText(currentrow, 1, allTags);
                currentrow++;
                allTags = "";
                continue;
            }
            allTags += (j == 0 ? string("") : string(", ")) + addtag;
            j++;
            //cout << " allTags : " << allTags << endl;
        }
        // and kick out the last line
        tagsTable.insertRows(1);
        tagsTable.setText(currentrow, 0, "");
        tagsTable.setText(currentrow, 1, allTags);


    } else {
        //tagsTable.insertRows(1);
        //tagsTable.setColumnWidth(0, 1);
        //tagsTable.setText(0, 0, "");
    }
    return tagsTable;
}


// --------------------- Laser printer support
void TextInvoice::createTagsTable(QTextTable *tagsTable)
{
    if ( isBuyerInvoice && showTags ) {
        QTextTableFormat tableFormat;
        tableFormat.setBorderStyle(tableBoarderStyle);
        tableFormat.setCellPadding(-1);
        tableFormat.setCellSpacing(0);
        tagsTable->setFormat(tableFormat);

        vector<Transaction> transList = invoice->getTransactionList();
        vector<Transaction>::iterator current;

        vector<Tag> allTagsList;

        // stuff all the tags for the transaction into one list
        for(current = transList.begin(); current != transList.end(); current++)
        {
            vector<Tag> tagList = current->getTagList();
            for(unsigned int i = 0; i < tagList.size(); i++)
            {
                allTagsList.push_back(tagList[i].getTag());
            }
        }

        sort(allTagsList.begin(), allTagsList.end(), Tag::compareTagsLT);

        // build a string with the tags that is less than columnsize.
        // When it exceeds columnsize put that string in tagsTable,
        // reset the string and continue with the rest of the tags.
        string allTags = "";
        unsigned int currentrow = 0;
        for(unsigned int j = 0; j < allTagsList.size(); )
        {
            string addtag = allTagsList[j].getTag();
            // << " working on tag " << addtag << "  for j=" << j << endl;
            //            if ( allTags.length() + addtag.length() + 2 > columnsize )
            //            {
            //                // stop the line here and add to table
            //                tagsTable.insertRows(1);
            //                tagsTable.setText(currentrow, 0, "");
            //                tagsTable.setText(currentrow, 1, allTags);
            //                currentrow++;
            //                allTags = "";
            //                continue;
            //            }
            allTags += (j == 0 ? string("") : string(", ")) + addtag;
            j++;
            //cout << " allTags : " << allTags << endl;
        }
        // and kick out the last line
        //        tagsTable.insertRows(1);
        //        tagsTable.setText(currentrow, 0, "");
        //        tagsTable.setText(currentrow, 1, allTags);
        setCellText(tagsTable,0,0,allTags,false,Qt::AlignCenter);

    }
}

// ----- Footer table for laser printer.
void TextInvoice::createFooterTable(QTextTable *footerTable)
{
    QTextTableFormat tableFormat;
    tableFormat.setBorderStyle(tableBoarderStyle);
    footerTable->setFormat(tableFormat);
    setCellText(footerTable,0,0,footerString,false,Qt::AlignCenter);
}

//virtual function, called in derived class.
void TextInvoice::createProrateTable(QTextTable *proRateTable)
{
    QTextTableFormat tableFormat;
    tableFormat.setBorderStyle(tableBoarderStyle);
    proRateTable->setFormat(tableFormat);
}

void  TextInvoice::createSummaryTable(QTextTable *summaryTable, bool isLoadout)
{
    int columnNum = 9;
    QTextTableFormat tableFormat;
    tableFormat.setBorderStyle(tableBoarderStyle);

    vector<ChargeRecord> chargeList = invoice->getChargeRecordList(true);
    sort(chargeList.begin(), chargeList.end(), ChargeRecord::compareIdsLT);

    vector<ChargeRecord>::iterator currentChg;
    QVector<QTextLength> columnSizeConstraints = summaryTableColumnsConstraints();
    tableFormat.setColumnWidthConstraints(columnSizeConstraints);
    summaryTable->appendColumns(columnNum);
    tableFormat.setCellPadding(-1);
    tableFormat.setCellSpacing(0);
    summaryTable->setFormat(tableFormat);

    double chargeTotal = 0.0;
    unsigned int row = 0;
    char chgStr[30];
    unsigned int col = 0;
    summaryTable->appendRows(1);
    for (int j = 0; j < summaryTable->rows(); j++) {
        for (int k = 0; k < summaryTable->columns(); k++ ) {
            setCellText(summaryTable, j, k, ""); // Init with clean cell
        }
    }

    initSummaryCoordsLaser(row, col);

    double commission = invoice->getCommissionTotal();
    vector<ChargeRecord>::iterator commLoc = find(chargeList.begin(), chargeList.end(), 0);

    if(commLoc == chargeList.end())
    {
        cerr << "error finding commission charge record" << endl;
    }

    for(currentChg = chargeList.begin(); currentChg != chargeList.end() && commLoc != chargeList.end(); currentChg++)
    {
        if(currentChg->isCommissionCharge())
        {
            commLoc->increaseTotal(currentChg->getAdjustedTotal());
        }
    }

    chargeList.insert(chargeList.begin() + 1, ChargeRecord(0, "Trucking"  , invoice->truckingTotal()));


    if(groupChargesByName)
    {
        vector<ChargeRecord> tempList;

        for(unsigned int i = 0; i < chargeList.size(); i++)
        {
            if(tempList.size() == 0 || chargeList[i].getDescrip() != tempList.back().getDescrip())
            {
                tempList.push_back(chargeList[i]);
            }
            else
            {
                tempList.back().increaseTotal(chargeList[i].getTotal());
            }
        }

        chargeList = tempList;
    }

    for(currentChg = chargeList.begin(); currentChg != chargeList.end(); currentChg++)
    {
        if(!currentChg->isCommissionCharge())
        {
            if(currentChg->getId() == 0 || currentChg->getAdjustedTotal() < -0.009 || currentChg->getAdjustedTotal() > 0.009)
            {
                sprintf(chgStr, "%0.2f", currentChg->getAdjustedTotal());
                for (int k = col + 1; k < summaryTable->columns(); k++ ) {
                    setCellText(summaryTable,row, k, ""); // Init with clean cell
                }

                setCellText(summaryTable,row, col, currentChg->getDescrip(),false,Qt::AlignLeft);
                setCellText(summaryTable,row, col + 1, chgStr,false,Qt::AlignRight);
                chargeTotal += currentChg->getAdjustedTotal();

                if(currentChg->getId() == 0 && currentChg->getDescrip() == "Trucking")
                {
                    vector<TruckingRecord> truckingList = invoice->getTruckingList();

                    for(unsigned int j = 0; j < truckingList.size(); j++)
                    {
                        summaryTable->appendRows(1);
                        row++;
                        setCellText(summaryTable,row, 8, "TRUCKER",false,Qt::AlignLeft);
                        setCellText(summaryTable,row, 9, truckingList[j].getTruckerName(),false,Qt::AlignRight);
                    }
                }

                if(currentChg + 1 != chargeList.end())
                {
                    unsigned int appendRows = 0;
                    updateSummaryCoords(row, col, appendRows);
                    if (appendRows>0)  {
                        summaryTable->appendRows(appendRows);
                        for (int j = 0; j < appendRows; j++) {
                            for (int k = 0; k < summaryTable->columns(); k++ ) {
                                setCellText(summaryTable,summaryTable->rows()-1-j, k, ""); // Init with clean cell
                            }
                        }
                    }
                }
            }
        }
    }
    summaryTable->appendRows(3);
    for (int j = 0; j < 3; j++) {
        for (int k = 0; k < summaryTable->columns(); k++ ) {
            setCellText(summaryTable,summaryTable->rows()-1-j, k, ""); // Init with clean cell
        }
    }
    setCellText(summaryTable,row + 1, 8, string(39, '='), true);
    setCellText(summaryTable,row + 2, 8, summaryChargeTotalLabel(),false,Qt::AlignLeft);
    setCellText(summaryTable,row + 2, 9, QString::number( chargeTotal, 'f', 2 ).toStdString(),false,Qt::AlignRight);
    setCellText(summaryTable,row + 3, 8, summaryTotalLabel(),false,Qt::AlignLeft);
    setCellText(summaryTable,row + 3, 9, QString::number( totalValue(), 'f', 2 ).toStdString(),false,Qt::AlignRight);
    row += 3;

    if(doShowSexSummary())
    {
        sexSummaryLine(summaryTable, row);
    }

    overallAverageLine(summaryTable, row);

//    setCellText(summaryTable,row, 8, "Total Fees: ",false,Qt::AlignLeft);
//    sprintf(chgStr, "%0.2f", chargeTotal);
//    setCellText(summaryTable,row, 8, chgStr,false,Qt::AlignRight);

}


QTextDocument *TextInvoice::invoiceTextDocument()
{
   return m_invoiceDoc.clone();
}
QTextDocument *TextInvoice::loadoutTextDocument()
{
   return m_loadOutDoc.clone();
}


void TextInvoice::sexSummaryLine(QTextTable* summaryTable, unsigned int& row)
{
 //   SetupDAO setup;

    vector<AnimalCode> uniqueSexList = invoice->getUniqueSexList();
    string label  = "TYPE   HD  AVG  $/cwt";
    string footer = "----- --- ---- ------";


    label += string(" ") + label;
    footer += string(" ") + footer;

    char buf[60];
    string line;
    long headCount = 0;

    bool headerPrinted = false;

    for(int i = 0; i < uniqueSexList.size(); i++)
    {
        headCount = invoice->getSexHead(uniqueSexList[i]);

        if(headCount > 0)
        {
            sprintf(buf, "%5s%4ld%5ld%7.2f", uniqueSexList[i].getTypeDescrip().substr(0, 5).c_str(), headCount, invoice->getSexAverageWeight(uniqueSexList[i]), invoice->getSexAvgDolPerCWT(uniqueSexList[i]));
            line += (line.length() > 0 ? string(" ") : string("")) + buf;
        }


        if(line.length() > strlen(buf) || (i == uniqueSexList.size() - 1 && line.length() > 0))
        {

            if(!headerPrinted)
            {
                headerPrinted = true;

                setCellText(summaryTable,row - 2, 0, label, true,7,Qt::AlignLeft);
                setCellText(summaryTable,row - 1, 0, footer, true,7,Qt::AlignLeft);
            }

             setCellText(summaryTable,row, 0, line, true,7,Qt::AlignLeft);
            line = "";
            summaryTable->appendRows(1);
            row++;

            for (int i = 1; i< summaryTable->columns(); i++) {
                setCellText(summaryTable,summaryTable->rows()-1, i, " ");
            }
        }
    }

    if(headerPrinted)
    {
        string disclaimer = "Sex Summary DOES NOT include sales by Head";
        setCellText(summaryTable,row, 0, disclaimer, true,7,Qt::AlignLeft);
        for (int i = 7; i< summaryTable->columns(); i++) {
            setCellText(summaryTable,row, i, " ");
        }
    }
    for (int i = 1; i< summaryTable->columns(); i++) {
        setCellText(summaryTable,summaryTable->rows()-1, i, " ");
    }

}

QVector<QTextLength> TextInvoice::summaryTableColumnsConstraints()
{
    QVector<QTextLength> columnSizeConstraints(10);
    columnSizeConstraints[0] = QTextLength(QTextLength::PercentageLength,7.0);
    columnSizeConstraints[1] = QTextLength(QTextLength::PercentageLength,7.0);
    columnSizeConstraints[2] = QTextLength(QTextLength::PercentageLength,7.0);
    columnSizeConstraints[3] = QTextLength(QTextLength::PercentageLength,7.0);
    columnSizeConstraints[4] = QTextLength(QTextLength::PercentageLength,7.0);
    columnSizeConstraints[5] = QTextLength(QTextLength::PercentageLength,7.0);
    columnSizeConstraints[6] = QTextLength(QTextLength::PercentageLength,7.0);
    columnSizeConstraints[7] = QTextLength(QTextLength::PercentageLength,7.0);
    columnSizeConstraints[8] = QTextLength(QTextLength::PercentageLength,25.0);
    columnSizeConstraints[9] = QTextLength(QTextLength::PercentageLength,18.75);
    return columnSizeConstraints;
}


void TextInvoice::createDisclaimerTable(QTextCursor &cursor)
{

}

string TextInvoice::formatName(string nameString) {
    unsigned short nameLength = nameString.length();
    unsigned short slashIndex = 0;

    if((slashIndex = nameString.find_first_of('/')) < nameLength)
    {
        string lastName = nameString.substr(0, slashIndex);
        string firstName = (slashIndex + 1 < nameString.length()? nameString.substr(slashIndex + 1) : "");
        if (firstName.length() > 0 && lastName.length() > 0) {
            nameString = firstName + " " + lastName;
        } else if (firstName.length() > 0) {
            nameString = firstName;
        } else if (lastName.length() > 0) {
            nameString = lastName;
        }
    }
    return nameString;
}
