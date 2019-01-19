
#include "textreport.h"

#include <cmath>
#include <cstdio>

TextReportItem::TextReportItem()
{}

string TextReportItem::fillString(char fillChar, int length)
{
    return string(length, fillChar);
}

string TextReportItem::reAlign(string text, ALIGNMENT align, unsigned int space)
{
    int wsLength = space - text.length();
    string whiteSpace= (wsLength > 0 ? string(space - text.length(), ' ') : "");

    // there is command data embedded in the text, so assume that the caller
    // has manually done the alignment

    if(text.length() > 0 && text[0] <= 27)
    {
        return text;
    }

    switch(align)
    {
    case LEFT:
    default:
        text = text + whiteSpace;
        break;

    case RIGHT:
        text = whiteSpace + text;
        break;

    case CENTER:
        whiteSpace.insert(whiteSpace.length() / 2, text);
        text = whiteSpace;
        break;
    }

    if(text.length() >= space)
    {
        return text.substr(0, space);
    }

    return text;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////////////


TextReportHeader::TextReportHeader(string firstLine)
{
    if(firstLine.length() > 0)
    {
        headerLines.push_back(firstLine);
    }
}

void TextReportHeader::addHeaderLine(string lineText)
{
    if(lineText.length() > 0)
    {
        headerLines.push_back(lineText);
    }
}

string TextReportHeader::toString(int pageWidth, ALIGNMENT align)
{
    deque<string>::iterator current;
    string whiteSpace;
    string headerText;


    for(current = headerLines.begin(); current != headerLines.end(); current++)
    {
        headerText += reAlign(*current, align, pageWidth) + "\n";
    }

    return headerText;
}

unsigned int TextReportHeader::size()
{
    return headerLines.size();
}

deque<string> TextReportHeader::paginatedText(unsigned int pageHeight, string *page, double *lineCount)
{
    // [KLN] add
//    cout << "Entering TextReportHeader::paginatedText" << endl;
//    cout << "lineCount: " << *lineCount << endl;
//    cout << "pageHeight: " << pageHeight << endl;
    // [KLN] add end
    deque<string> pageList;
    deque<string>::iterator current;

    // [KLN] add
//    cout << "  In FOR loop" << endl;
    // [KLN] add end
    for(current = headerLines.begin(); current != headerLines.end(); current++)
    {
        *page += reAlign(*current, TextReportItem::CENTER, 80) + "\n";
        (*lineCount) += 1.00000001;

        // [KLN] add
//        cout << "    lineCount: " << *lineCount << endl;
        // [KLN] add end
        if((*lineCount) >= pageHeight)
        {
            pageList.push_back(*page);
            *page = "";
            (*lineCount) = 0.0000001;
        }
    }
    // [KLN] add
//    cout << "lineCount: " << *lineCount << endl;
//    cout << "Leaving TextReportHeader::paginatedText" << endl;
    // [KLN] add end

    return pageList;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////////////

TextReportTable::TextReportTable(int numCols)
{
    headerTopSep = headerBotSep = footerTopSep = footerBotSep = '-';
    topHeaderStyle = botHeaderStyle = topFooterStyle = botFooterStyle = Continuous;
    if(numCols > MAX_TABLE_COLS)
    {
        cerr << "In TextReportTable:" << endl;
        cerr << "Number of columns out of bounds, max number of columns is " << MAX_TABLE_COLS << ", table will have " << MAX_TABLE_COLS << " columns." << endl;
        numCols = MAX_TABLE_COLS;
    }

    if(numCols < 1)
    {
        cerr << "In TextReportTable:" << endl;
        cerr << "Table must have at least 1 column, creating a table with 1 column" << endl;
        numCols = 1;
    }

    this->numCols = numCols;

    int rem = 80 % numCols;

    for(int i = 0; i < MAX_TABLE_COLS; i++)
    {
        columnWidths[i] = 80 / numCols + (rem > 0 ? 1 : 0);
        columnAlignments[i] = LEFT;
        rem--;
    }
    preText = "";
    postText = "";
}

TextReportTable::TextReportTable(const TextReportTable& old) : TextReportItem()
{
    this->footerBotSep = old.footerBotSep;
    this->footerTopSep = old.footerTopSep;
    this->headerTopSep = old.headerTopSep;
    this->headerBotSep = old.headerBotSep;

    topHeaderStyle = old.topHeaderStyle;
    botHeaderStyle = old.botHeaderStyle;
    topFooterStyle = old.topFooterStyle;
    botFooterStyle = old.botFooterStyle;

    this->numCols = old.numCols;

    for(unsigned int i = 0; i < numCols; i++)
    {
        this->columnWidths[i] = old.columnWidths[i];
        this->columnAlignments[i] = old.columnAlignments[i];
    }

    this->tableHeader = old.tableHeader;
    this->tableBody = old.tableBody;
    this->tableFooter = old.tableFooter;
    this->plainText = old.plainText;
    this->plainTextLineCount = old.plainTextLineCount;
    this->preText = old.preText;
    this->postText = old.postText;
}

TextReportTable::~TextReportTable()
{
}

void TextReportTable::setHeader(unsigned int col, string text)
{

    if(col >= numCols)
    {
        cerr << "In TextReportTable::setHeader:" << endl;
        cerr << "Column: " << col << " is out of bounds in attempt to set header text" << endl;
        return;
    }

    if(tableHeader.size() < numCols)
    {
        for(unsigned int i = tableHeader.size(); i < numCols; i++)
        {
            tableHeader.push_back(string(""));
        }
    }

    deque<string>::iterator current = tableHeader.begin() + col;
    (*current) = string(text);
}

// warning, post and pre - text are not used in calculating paginating
// so any non-control strings will take pagination off

void TextReportTable::setSurroundingText(string preText, string postText)
{
    this->preText = preText;
    this->postText = postText;
}

void TextReportTable::setFooter(unsigned int col, string text, bool span)
{
    if(col >= numCols)
    {
        cerr << "In TextReportTable::setFooter:" << endl;
        cerr << "Column: " << col << " is out of bounds in attempt to set header text" << endl;
        return;
    }

    if(tableFooter.size() < numCols)
    {
        for(unsigned int i = tableFooter.size(); i < numCols; i++)
        {
            tableFooter.push_back(string(""));
        }
    }

    if(!span)
    {
        tableFooter[col] = text;
    }
    else
    {
        string buf = "";
        while(col < numCols && text.length() > 0)
        {
            if(text.length() < columnWidths[col])
            {
                buf = text;
                text = "";
            }
            else
            {
                buf = text.substr(0, columnWidths[col]);
                text = text.substr(columnWidths[col]);
            }
            setFooter(col, buf);
            col++;
        }
    }
}

void TextReportTable::setFooter(unsigned int col, double num, bool span)
{
    char buf[30];
    sprintf(buf, "%0.2f", num);
    setFooter(col, buf, span);
}

void TextReportTable::setFooter(unsigned int col, long num, bool span)
{
    char buf[20];
    sprintf(buf, "%ld", num);
    setFooter(col, buf, span);
}

void TextReportTable::setColumnWidth(unsigned int col, int width)
{
    if(col >= numCols)
    {
        cerr << "In TextReportTable::setColumnWidth:" << endl;
        cerr << "Column " << col << " is out of bounds" << endl;
        return;
    }

    if(width < 0)
    {
        cerr << "In TextReportTable::setColumnWidth:" << endl;
        cerr << "Width is invalid " << endl;
        return;
    }

    columnWidths[col] = width;
}

void TextReportTable::setColumnAlignment(unsigned int col, ALIGNMENT align)
{
    if(col >= numCols)
    {
        cerr << "In TextReportTable::setColumnAlignment:" << endl;
        cerr << "Can't set alignment for column: " << col << " column is out of bounds" << endl;
    }

    columnAlignments[col] = align;
}

string TextReportTable::text(int row, int col)
{
    deque<string>::iterator current = tableBody.begin() + (row * numCols) + col;
    return *current;
}

void TextReportTable::setText(unsigned int row, unsigned int col, string text, bool span, bool truncate)
{
    if(tableBody.size() <= row || numCols <= col)
    {
        // out of bounds
        return;
    }

    if(span)
    {
        string buf;

        do
        {
            buf = (text.length() > columnWidth(col) ? text.substr(0, columnWidth(col)) : text);
            text = (text.length() > buf.length() ? text.substr(buf.length()) : "");

            if(buf.length() > 0)
            {
                buf += string(columnWidth(col) - buf.length(), ' ');
                setText(row, col, buf);
                col++;
            }
        }
        while(buf.length() > 0 && col < numCols);
    }
    else
    {
        deque<string>::iterator current = tableBody.begin() + (row * numCols) + col;
        (*current) = text;
    }
}

void TextReportTable::setText(unsigned int row, unsigned int col, double num)
{
    char buf[30];
    sprintf(buf, "%0.2f", num);
    setText(row, col, buf);
}

void TextReportTable::setText(unsigned int row, unsigned int col, long num)
{
    char buf[20];
    sprintf(buf, "%ld", num);
    setText(row, col, buf);
}

void TextReportTable::setText(unsigned int row, unsigned int col, int num)
{
    char buf[20];
    sprintf(buf, "%d", num);
    setText(row, col, buf);
}

int TextReportTable::columnWidth(unsigned int col)
{
    return columnWidths[col];
}

void TextReportTable::insertRows(int numRowsToInsert)
{
    for(int i = 0; i < numRowsToInsert; i++)
    {
        for(unsigned int j = 0; j < numCols; j++)
        {
            tableBody.push_back(string(""));
        }
        plainText.push_back(deque<string>(0,string("")));
        plainTextLineCount.push_back(vector<double>(0, 0));
    }
}

void TextReportTable::setPlainText(unsigned int row, string data)
{
    if(0 <= row && row < plainText.size())
    {
        plainText[row] = deque<string>(1, data);
    }
}

void TextReportTable::setPlainTextLineCount(unsigned int row, double count)
{
    if(0 <= row && row < plainTextLineCount.size())
    {
        plainTextLineCount[row] = vector<double>(1, count);
    }
}

void TextReportTable::increasePlainTextLineCount(unsigned int row, double count)
{
    if(0 <= row && row < plainTextLineCount.size())
    {
        plainTextLineCount[row].push_back(count);
    }
}

vector<double> TextReportTable::getPlainTextLineCount(unsigned int row)
{
    vector<double> countVector;

    if(0 <= row && row < plainTextLineCount.size())
    {
        countVector = plainTextLineCount[row];
    }
    return countVector;
}

void TextReportTable::appendPlainText(unsigned int row, string data)
{
    if(0 <= row && row < plainText.size())
    {
        plainText[row].push_back(data);
    }
}

void TextReportTable::setHeaderSeperator(char top, char bot)
{
    this->headerTopSep = top;
    this->headerBotSep = bot;
}

void TextReportTable::setFooterSeperator(char top, char bot)
{
    this->footerTopSep = top;
    this->footerBotSep = bot;
}

void TextReportTable::setHeaderStyle(HEADER_STYLE topStyle, HEADER_STYLE botStyle)
{
    topHeaderStyle = topStyle;
    botHeaderStyle = botStyle;
}

void TextReportTable::setFooterStyle(HEADER_STYLE topStyle, HEADER_STYLE botStyle)
{
    topFooterStyle = topStyle;
    botFooterStyle = botStyle;
}

int TextReportTable::numRows()
{
    return tableBody.size() / numCols;
}

string TextReportTable::headerString(char topSeperator, char bottomSeperator)
{
    string hdrStr = "";
    string sep = "";
    deque<string>::iterator current;

    int curCol = 0;
    string botSepStr;
    string topSepStr;

    for(current = tableHeader.begin(); current != tableHeader.end(); current++)
    {
        topSepStr += sepStringPart(current->length(), topHeaderStyle, topSeperator, curCol);
        hdrStr += reAlign(*current, columnAlignments[curCol], columnWidths[curCol]);
        botSepStr += sepStringPart(current->length(), botHeaderStyle, bottomSeperator, curCol);
        curCol++;
    }

    return topSepStr + (topSepStr.length() > 0 ? "\n" : "") +
            hdrStr + (hdrStr.length() > 0 ? "\n" : "") +
            botSepStr + (botSepStr.length() > 0 ? "\n" : "");
}

string TextReportTable::footerString(char topSeperator, char bottomSeperator)
{
    string ftrStr = "";
    string topSep = "";
    string botSep = "";

    deque<string>::iterator current;

    int curCol = 0;

    for(current = tableFooter.begin(); current != tableFooter.end(); current++)
    {
        topSep += sepStringPart(current->length(), topFooterStyle, topSeperator, curCol);
        ftrStr += reAlign(*current, columnAlignments[curCol], columnWidths[curCol]);
        botSep += sepStringPart(current->length(), botFooterStyle, bottomSeperator, curCol);
        curCol++;
    }


    return topSep + (topSep.length() > 0 ? "\n" : "") + ftrStr + (ftrStr.length() > 0 ? "\n" : "") + botSep + (botSep.length() > 0 ? "\n" : "");
}

string TextReportTable::sepStringPart(unsigned int length, HEADER_STYLE style, char sepChar, unsigned int curCol)
{
    string sepPart;

    switch(style)
    {
    case Continuous:
    default:
        sepPart = string(columnWidths[curCol], sepChar);
        break;
    case Broken:
        sepPart = reAlign((length > 0 ? string(columnWidths[curCol] - 2, sepChar) : ""), columnAlignments[curCol], columnWidths[curCol]);
        break;

    case BrokenContinuous:
        sepPart = reAlign(string(columnWidths[curCol] - 2, sepChar), columnAlignments[curCol], columnWidths[curCol]);
        break;

    case ContinuousBroken:
        sepPart = reAlign((length > 0 ? string(columnWidths[curCol], sepChar) : ""), columnAlignments[curCol], columnWidths[curCol]);
        break;

    case NoHeader:
        sepPart = "";
        break;

    case Shadow:
        if(curCol < tableHeader.size())
        {
            sepPart = reAlign(tableHeader[curCol], columnAlignments[curCol], columnWidths[curCol]);

            for(unsigned int i = 0; i < sepPart.length(); i++)
            {
                if(sepPart[i] != ' ')
                {
                    sepPart[i] = sepChar;
                }
            }
        }

        break;
    };

    return sepPart;
}

void TextReportTable::appendTable(TextReportTable toInsert, APPEND_DIR dir)
{
    if(dir == APPEND_TOP || dir == APPEND_BOTTOM)
    {
        deque<string> tempTable = normalizeWidth(toInsert).tableBody;
        deque<string>::iterator insertPoint = (dir == APPEND_TOP ? tableBody.begin() : tableBody.end());

        tableBody.insert(insertPoint, tempTable.begin(), tempTable.end());
        return;
    }

    toInsert = normalizeHeight(toInsert);

    if(numCols + toInsert.numCols > MAX_TABLE_COLS)
    {
        cerr << "Result of append operation exceeds maximum table size, aborting the append" << endl;
        return;
    }

    deque<string>::iterator leftOfRow;

    deque<string>::iterator insertRowBegin;
    deque<string>::iterator insertRowEnd;

    // insert the new header to the left

    leftOfRow = (dir == APPEND_LEFT ? tableHeader.begin() : tableHeader.end());
    insertRowBegin = toInsert.tableHeader.begin();
    insertRowEnd = toInsert.tableHeader.end();

    tableHeader.insert(leftOfRow, insertRowBegin, insertRowEnd);


    // insert the new table body to the left

    int currentRow = 0;

    deque<string> workingTable;
    deque<string> tempTable = toInsert.tableBody;

    int nextBegin;
    int nextEnd;

    for(leftOfRow = tableBody.begin(); leftOfRow != tableBody.end(); leftOfRow += numCols)
    {
        nextBegin    = toInsert.numCols * currentRow;
        nextEnd      = toInsert.numCols * (currentRow + 1);

        if(dir == APPEND_LEFT)
        {
            workingTable.insert(workingTable.end(), tempTable.begin() + nextBegin, tempTable.begin() + nextEnd);
            workingTable.insert(workingTable.end(), leftOfRow, leftOfRow + numCols);
        }
        else
        {
            workingTable.insert(workingTable.end(), leftOfRow, leftOfRow + numCols);
            workingTable.insert(workingTable.end(), tempTable.begin() + nextBegin, tempTable.begin() + nextEnd);
        }

        currentRow++;
    }

    tableBody = workingTable;

    // insert the new footer to the left

    leftOfRow = (dir == APPEND_LEFT ? tableFooter.begin() : tableFooter.end());
    insertRowBegin = toInsert.tableFooter.begin();
    insertRowEnd = toInsert.tableFooter.end();

    tableFooter.insert(leftOfRow, insertRowBegin, insertRowEnd);

    // adjust meta-data

    for(unsigned int i = numCols; i < toInsert.numCols + numCols; i++)
    {
        if(dir == APPEND_LEFT)
        {
            columnWidths[i] = columnWidths[i - numCols];
            columnWidths[i - numCols] = toInsert.columnWidths[i - numCols];

            columnAlignments[i] = columnAlignments[i - numCols];
            columnAlignments[i - numCols] = toInsert.columnAlignments[i - numCols];
        }
        else
        {
            columnWidths[i] = toInsert.columnWidths[i - numCols];
            columnAlignments[i] = toInsert.columnAlignments[i - numCols];
        }
    }

    numCols += toInsert.numCols;
}


TextReportTable TextReportTable::normalizeHeight(TextReportTable toInsert)
{
    int numRows = tableBody.size() / numCols;
    int insertNumRows = toInsert.tableBody.size() / toInsert.numCols;

    if(numRows > insertNumRows)
    {
        insertNumRows = numRows - insertNumRows;
        toInsert.insertRows(numRows);
        return toInsert;
    }

    insertNumRows = insertNumRows - numRows;
    insertRows(numRows);
    return toInsert;
}


TextReportTable TextReportTable::normalizeWidth(TextReportTable toInsert)
{
    if(numCols == toInsert.numCols)
    {
        return toInsert;
    }

    TextReportTable fillTable(abs(int(numCols - toInsert.numCols)));

    if(numCols < toInsert.numCols)
    {
        appendTable(fillTable, APPEND_RIGHT);
        numCols = toInsert.numCols;
    }
    else
    {
        toInsert.appendTable(fillTable, APPEND_RIGHT);
        toInsert.numCols = numCols;
    }
    return toInsert;
}

string TextReportTable::toString()
{
    string tableString = "";

    // print the header line

    deque<string>::iterator current;
    unsigned int currentCol = 0;

    string hdr = headerString(headerTopSep, headerBotSep);
    tableString += hdr;

    currentCol = 0;
    unsigned int row = 0;

    for(current = tableBody.begin(); current != tableBody.end(); current++)
    {
        tableString += reAlign(*current, columnAlignments[currentCol], columnWidths[currentCol]);

        currentCol++;

        if(currentCol == numCols)
        {
            tableString += "\n";

            for(unsigned int i = 0; i < plainText[row].size(); i++)
            {
                if (!plainText[row][i].empty()) {
                    tableString += plainText[row][i];
                }
            }

            row++;
            currentCol = 0;
        }
    }

    tableString += footerString(footerTopSep, footerBotSep);

    return preText + tableString + postText;
}

deque<string> TextReportTable::paginatedText(unsigned int pageHeight, string *page, double *pageLines, TextReportTable pageHeader)
{
    // [KLN] add
//    cout << "Entering TextReportTable::paginatedText" << endl;
//    cout << "   pageLines: " << *pageLines << endl;
    // [KLN] add end
    deque<string> pageList;
    string buf = "";

    buf = headerString();

    if((*pageLines) + 3 >= pageHeight)  // if the passed page is already full add it to the page list
    {
        pageList.push_back(*page);
        *page = pageHeader.toString();
        (*pageLines) = pageHeader.numRows();
    }

    if(buf.size() > 0)
    {
        *page += preText + buf + postText;
        (*pageLines) += 3.00000001;
    }

    for(int i = 0; i < numRows(); i++)
    {
        vector<string> currentPlainText;

        *page += preText + tableRow(i) + postText;// + plainText[i];
        (*pageLines) += 1.0000001;
        //    (*pageLines) += plainTextLineCount[i];

        for(unsigned int j = 0; j < plainText[i].size(); j++)
        {
            *page += plainText[i][j];
            *pageLines += plainTextLineCount[i][j];

            if(*pageLines > pageHeight)
            {
                pageList.push_back(*page);
                (*pageLines) = pageHeader.numRows();
                *page = pageHeader.toString();
            }
        }


        if((*pageLines) >= pageHeight)
        {
            pageList.push_back(*page);
            (*pageLines) = pageHeader.numRows();
            *page = pageHeader.toString();
        }
    }

    buf = footerString();

    if((*pageLines) + 3.0000001 >= pageHeight)
    {
        pageList.push_back(*page);

        *page = pageHeader.toString();
        (*pageLines) = pageHeader.numRows();
    }

    if(buf.size() > 0)
    {
        *page += preText + buf + postText;
        (*pageLines) += 3.000001;
    }
    // [KLN] add
//    cout << "   pageLines: " << *pageLines << endl;
//    cout << "   pageList.size: " << pageList.size() << endl;
//    cout << "Leaving TextReportTable::paginatedText" << endl;
    // [KLN] add end

    return pageList;
}

void TextReportTable::adjustWidth(int desired)
{
    int currentWidth = 0;
    for(int i = 0; i < numCols; i++)
    {
        currentWidth += columnWidths[i];
    }

    int currentCol = 0;
    while(currentWidth != desired)
    {
        if(currentWidth < desired)
        {
            columnWidths[currentCol] += 1;
            currentWidth++;
        }
        else if(columnWidths[currentCol] > 0)
        {
            columnWidths[currentCol]--;
            currentWidth--;
        }

        currentCol++;

        if(currentCol >= numCols)
        {
            currentCol = 0;
        }
    }
}

string TextReportTable::tableRow(unsigned int row)
{
    deque<string>::iterator current;
    unsigned int currentCol = 0;
    string rowString = "";

    for(current = tableBody.begin() + (row * numCols); current != (tableBody.begin() + (row * numCols)) + numCols; current++)
    {
        rowString += reAlign(*current, columnAlignments[currentCol], columnWidths[currentCol]);

        currentCol++;

        if(currentCol == numCols)
        {
            rowString += "\n";
            currentCol = 0;
        }
    }
    return rowString;
}

void TextReportTable::retroFitColumns(int numRefitColumns, int desiredLength)
{
    int currentLength = 0;

    vector<int> weightVector;

    // get the scaling data for the items to be scaled;
    for(unsigned int i = numCols - numRefitColumns; i < numCols; i++)
    {
        weightVector.push_back(columnWidths[i]);
        currentLength += columnWidths[i];
    }

    int colDiff = desiredLength - currentLength;

    // adjust the columns not being forced

    while(colDiff != 0 && currentLength != 0)
    {
        for(unsigned int i = 0; i < numCols - numRefitColumns; i++)
        {
            if(colDiff < 0)
            {
                columnWidths[i]++;
                colDiff++;
            }
            else if(colDiff > 0)
            {
                columnWidths[i]--;
                colDiff--;
            }
            else
            {
                break;
            }
        }
    }

    int currentWeight = 0;
    int attainedLength = 0;

    for(unsigned int i = numCols - numRefitColumns; i < numCols - 1; i++)
    {
        cout << weightVector[currentWeight] << ", " << currentLength << ", " << desiredLength << endl;
        columnWidths[i] = (double(weightVector[currentWeight]) / currentLength) * desiredLength;
        attainedLength += columnWidths[i];
        currentWeight++;
    }

    if(numRefitColumns != 0)
    {
        columnWidths[numCols - 1] = desiredLength - attainedLength;
    }

    for(unsigned int i = 0; i < numCols; i++)
    {
        cout << columnWidths[i] << (i == numCols - 1 ? "" : ", ");
    }
    cout << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Notes: Normally I would use 1 constructor with default values instead of different constructors
//        for each possibility. In this case, the problems that this might cause make it more sensible to
//        use different constructors. An example of this is that a person might want to make a 
//        report with an empty table at the top, but if they do not, and they want to create the
//        report without creating a table first, the default constructor using default values will
//        create an empty table at the top anyway. So it would be very difficult to make this semantically
//        correct with a constructor using default values
////////////////////////////////////////////////////////////////////////////////////////////////////////

TextReport::TextReport(unsigned int pageHeight)
{
    this->pageHeight = pageHeight;
}

void TextReport::setPageHeader(TextReportTable pageHeader)
{
    this->pageHeader = pageHeader;
}

TextReport::TextReport(TextReportHeader header, TextReportTable table)
{
    setHeader(header);
    addTable(table);
}

TextReport::TextReport(TextReportHeader header, TextReportTable table, TextReportTable summary)
{
    setHeader(header);
    addTable(table);
    addSummary(summary);

    numTables = 0;
}

TextReport::~TextReport()
{}

void TextReport::setHeader(TextReportHeader header)
{
    this->header = header;
}


void TextReport::addTable(TextReportTable table, bool isLoadout)
{
    if ( !isLoadout ) {
        tableList.push_back(table);
    }
    else {
        m_loadOutTableList.push_back(table);
    }
}

void TextReport::addSummary(TextReportTable summary)
{
    summaryList.push_back(summary);
}

string TextReport::text()
{
    string reportString = header.toString(80, TextReportItem::CENTER);
    deque<TextReportTable>::iterator currentTable;
    for(currentTable = tableList.begin(); currentTable != tableList.end(); currentTable++)
    {
        reportString += currentTable->toString();
    }

    deque<TextReportTable>::iterator currentSummary;

    for(currentSummary = summaryList.begin(); currentSummary != summaryList.end(); currentSummary++)
    {
        reportString += currentSummary->toString();
    }

    return reportString ;
}

string TextReport::loadoutText()
{
    string reportString = header.toString(80, TextReportItem::CENTER);
    deque<TextReportTable>::iterator currentTable;
    for(currentTable = m_loadOutTableList.begin(); currentTable != m_loadOutTableList.end(); currentTable++)
    {
        reportString += currentTable->toString();
    }
    return reportString ;
}



void TextReport::setPageLength(unsigned int pageLength)
{
    this->pageHeight = pageLength;
}

deque<string> TextReport::paginatedText(unsigned int topSkip, bool isLoadout )
{
    // [KLN] add
//    cout << "Entering TextReport::paginatedText" << endl;
//    cout << "   no line counter in this function!" << endl;
    // [KLN] add end
    deque<TextReportTable>::iterator current;
    deque<string> pageList;
    string tail = "";
    double extraLines = 0.000000001;
    deque<string> newList = header.paginatedText(pageHeight - topSkip, &tail, &extraLines);
    pageList.insert(pageList.end(), newList.begin(), newList.end());

    if (!isLoadout) {
        for(current = tableList.begin(); current != tableList.end(); current++)
        {
            newList = current->paginatedText(pageHeight - topSkip, &tail, &extraLines, pageHeader);
            pageList.insert(pageList.end(), newList.begin(), newList.end());
        }
    }
    else {
        for(current = m_loadOutTableList.begin(); current != m_loadOutTableList.end(); current++)
        {
            newList = current->paginatedText(pageHeight - topSkip, &tail, &extraLines, pageHeader);
            pageList.insert(pageList.end(), newList.begin(), newList.end());
        }
    }

    if(extraLines > 0)
    {
        pageList.push_back(tail);
    }

    deque<string>::iterator page;

    for(page = pageList.begin(); page != pageList.end(); page++)
    {
        string buf = string(topSkip, '\n');
        page->insert(0, buf);
    }

    deque<string> actualPageList;

    for(unsigned int i = 0; i < pageList.size(); i++)
    {
        if(pageList[i] != pageHeader.toString())
        {
            actualPageList.push_back(pageList[i]);
        }
    }

//   cout << "Leaving TextReport::paginatedText" << endl; // [KLN]
   return actualPageList;
}

void TextReport::clearTables(bool isLoadout)
{
    if (!isLoadout) {
        tableList = deque<TextReportTable>();
    }
    else {
        m_loadOutTableList.clear();
        m_loadOutTableList = deque<TextReportTable>();
    }
}


string TextReport::headerText()
{
    string headerString = header.toString(80, TextReportItem::CENTER);
    return headerString;
}
