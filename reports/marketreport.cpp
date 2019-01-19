#include "marketreport.h"
#include <fstream>
#include <QMap>

MarketReport::MarketReport(vector<Transaction> transactionList, bool splitSexes, bool hideSeller) :
    m_minWegth(0),
    m_maxWegth(2400),
    m_step(200),
    m_isGroup(false)
{
    this->transactionList = transactionList;
    this->splitSexes = splitSexes;

    for(int i = 0; i < 5; i++)
    {
        SortRecord sr;
        sr.sort = SortItem(i);
        sr.reverse = false;
        sortOrder[i] = sr;
    }
    listSorted = false;
    this->hideSeller = hideSeller;
}

void MarketReport::setSortOrder(SortRecord first, SortRecord second, SortRecord third, SortRecord fourth, SortRecord fifth, SortRecord sixth)
{
    sortOrder[0] = first;
    sortOrder[1] = second;
    sortOrder[2] = third;
    sortOrder[3] = fourth;
    sortOrder[4] = fifth;
    sortOrder[5] = sixth;
}

void MarketReport::setCommentList(vector<string> commentList)
{
    this->commentList = commentList;
}

string MarketReport::text()
{
    cout << "MarketReport"<< endl;
    clearTables();
    usedSexes = vector<short>();
    short sex = 0;
    addTable(headerTable());

    if(!listSorted)
    {
        sortList();
    }
    int sexTableCount = 0;
    if(sortOrder[0].sort == Sex)
        //if(sortOrder[0].sort != Sex)  // used this in testing to see report run.
        //if ( true )
    {
        for(unsigned int i = 0; i < transactionList.size(); i++)
        {
            cout << "MarketReport trans " << i << endl;
            if(splitSexes == true)
            {
                sex = transactionList[i].getAnimalCode().getType();
                cout << "    MarketReport sex " << sex << endl;

                if(find(usedSexes.begin(), usedSexes.end(), sex) == usedSexes.end())
                {
                    cout << "    MarketReport sexTableCount " << sexTableCount << endl;

                    if(sexTableCount < commentList.size())
                    {
                        addTable(commentTable(commentList[sexTableCount]));
                    }
                    sexTableCount++;
                    cout << "    MarketReport sexTableCount " << sexTableCount << endl;
                    addTable(sexTable(sex));
                    usedSexes.push_back(sex);
                }
                cout << "    MarketReport ...sex" << endl;

            }
            else
            {
            }
        }
    }
    else
    {
        addTable(transactionTable());
    }

    return TextReport::text();
}

TextReportTable MarketReport::commentTable(string comment)
{
    TextReportTable table(1);
    table.setColumnWidth(0, 79);
    vector<string> commentLines;

    int startLine = 0;
    int endLine = 0;
    int row = 0;

    if(comment.length() > 0)
    {
        table.insertRows(2);
        row = 2;
    }

    do
    {
        endLine = comment.find_first_of("\n", startLine);

        if(endLine == string::npos)
        {
            table.insertRows(1);
            table.setText(row, 0, comment.substr(startLine), true);
            row++;
            endLine = comment.length();
            startLine = string::npos;
        }
        else
        {
            table.insertRows(1);
            table.setText(row, 0, comment.substr(startLine, endLine - startLine), true);
            row++;
            startLine = (endLine + 1 < comment.length() ? endLine + 1 : string::npos);
        }

    }while(startLine != string::npos);

    return table;
}

TextReportTable MarketReport::headerTable()
{
    TextReportTable table = tableTemplate();

    if(!hideSeller)
    {
        table.setHeader(0, "Name");
        table.setHeader(1, "Address");
    }

    int offset = (hideSeller ? 2 : 0);

    table.setHeader(2 - offset, "Head");
    table.setHeader(3 - offset, " Description");
    table.setHeader(4 - offset, "Avg Wt");
    table.setHeader(5 - offset, "Bid");
    table.setHeader(6 - offset, "Trans#");


    table.insertRows(1);

    return table;
}

TextReportTable MarketReport::tableTemplate()
{
    TextReportTable table;

    if(hideSeller)
    {
        table = TextReportTable(5);
        table.setColumnWidth(0, 6);
        table.setColumnWidth(1, 22);
        table.setColumnWidth(2, 17);
        table.setColumnWidth(3, 17);
        table.setColumnWidth(4, 17);
        table.setColumnAlignment(0, TextReportTable::CENTER);
        table.setColumnAlignment(1, TextReportTable::LEFT);
        table.setColumnAlignment(2, TextReportTable::RIGHT);
        table.setColumnAlignment(3, TextReportTable::RIGHT);
        table.setColumnAlignment(4, TextReportTable::RIGHT);
    }
    else
    {
        table = TextReportTable(7);
        table.setColumnWidth(0, 21);
        table.setColumnWidth(1, 20);
        table.setColumnWidth(2, 5);
        table.setColumnWidth(3, 12);
        table.setColumnWidth(4, 7);
        table.setColumnWidth(5, 7);
        table.setColumnWidth(6, 7);
        table.setColumnAlignment(0, TextReportTable::LEFT);
        table.setColumnAlignment(1, TextReportTable::LEFT);
        table.setColumnAlignment(2, TextReportTable::CENTER);
        table.setColumnAlignment(3, TextReportTable::LEFT);
        table.setColumnAlignment(4, TextReportTable::RIGHT);
        table.setColumnAlignment(5, TextReportTable::RIGHT);
        table.setColumnAlignment(6, TextReportTable::RIGHT);
    }


    table.setHeaderStyle(TextReportTable::Broken, TextReportTable::Broken);
    table.setHeaderSeperator(' ', '-');
    return table;
}

TextReportTable MarketReport::transactionTable()
{

    TextReportTable table = tableTemplate();

    table.insertRows(transactionList.size());

    for(unsigned int i = 0; i < transactionList.size(); i++)
    {
        fillTableRow(table, i, transactionList[i]);
    }
    return table;
}

void MarketReport::fillTableRow(TextReportTable& table, unsigned int row, Transaction trans,bool emptyRow)
{
    char buf[30];

    if(!hideSeller)
    {
        table.setText(row, 0, trans.getSeller().getName().getLast());
        if (!emptyRow) {
            table.setText(row, 1, string(" ") + trans.getSeller().getAddress().cityStateZipStr());
        }
        else {
            table.setText(row, 1, string(" "));
        }
    }

    sprintf(buf, " %ld", trans.getHead());
    int offset = (hideSeller ? 2 : 0);

    if (!emptyRow) {
        table.setText(row, 2 - offset, buf);
        table.setText(row, 3 - offset, string(" ") + trans.getAnimalCode().getDescrip());
        sprintf(buf, " %0.0f", trans.getAverageWeight());
        table.setText(row, 4 - offset, buf);
        sprintf(buf, " %0.2f", trans.getPrice());
        table.setText(row, 5 - offset, buf);
        sprintf(buf, " %ld%c", trans.getId(), (trans.isManual() ? 'M' : ' '));
        table.setText(row, 6 - offset, buf);
    }
    else {
        table.setText(row, 2 - offset, string(" "));
        table.setText(row, 3 - offset, string(" "));
        table.setText(row, 4 - offset, string(" "));
        table.setText(row, 5 - offset, string(" "));
        table.setText(row, 6 - offset, string(" "));
    }


}

vector<string> MarketReport::getUniqueSexList()
{
    if(!listSorted)
    {
        sortList();
    }

    vector<string> sexList;
    vector<string> usedList;
    string sex;

    for(unsigned int i = 0; i < transactionList.size(); i++)
    {
        sex = transactionList[i].getAnimalCode().getTypeDescrip();

        if(find(usedList.begin(), usedList.end(), sex) == usedList.end())
        {
            usedList.push_back(sex);
            sexList.push_back(transactionList[i].getAnimalCode().getTypeDescrip());
        }
    }

    return sexList;
}

TextReportTable MarketReport::sexTable(short sex)
{
    QMap< int, vector<Transaction> > entryList;
    int minWeigth = m_minWegth;
    int maxWeigth = m_maxWegth;
    int step = m_step;

    TextReportTable table = tableTemplate();
    vector<Transaction> sexList = getSexList(sex);

    if (m_isGroup) {

        for (int i = minWeigth; i< maxWeigth; i+=step) {
            for (int j = 0; j < sexList.size(); j++) {
                if ((sexList[j].getAverageWeight() >= i) && (sexList[j].getAverageWeight() < (i+step))) {
                    entryList[i].push_back(sexList[j]);
                }
            }
        }

        QList<int> keyList = entryList.keys();
        int row = 0;

        if (sexList.size() > 0) {
            table.setHeader(0, sexList[0].getAnimalCode().getTypeDescrip());
        }

        for (int k = 0; k < keyList.size(); k++) {
            vector<Transaction> sexList1 = entryList.value(keyList[k]);
            int key = keyList[k];
            table.insertRows(sexList1.size()+3);
            for(unsigned int i = 0; i < sexList1.size(); i++)
            {
                if(i == 0) {
                    char buf[25];
                    row++;
                    sprintf(buf,"\x1B\x45%d Weights\x1B\x46",key);


                    table.setText(row, 0, buf);
                    row++;
                    table.setText(row, 0, "\x1B\x45----------------\x1B\x46");
                    row++;
                }
                fillTableRow(table, row, sexList1[i]);
                row++;
            }
        }
    }
    else {
        table.insertRows(sexList.size());
        for(unsigned int i = 0; i < sexList.size(); i++) {
            if(i == 0) {
                table.setHeader(0, sexList[0].getAnimalCode().getTypeDescrip());
            }
            fillTableRow(table, i, sexList[i]);
        }
    }

    return table;

}


vector<Transaction> MarketReport::getSexList(short sex)
{
    vector<Transaction> list;

    for(unsigned int i = 0; i < transactionList.size(); i++)
    {
        if(transactionList[i].getAnimalCode().getType() == sex)
        {
            list.push_back(transactionList[i]);
        }
    }

    return list;
}

void MarketReport::sortList()
{
    vector<TransactionGroup> tempList;
    vector<TransactionGroup> addGroup;

    groupList.push_back(transactionList);

    for(unsigned int i = 0; i < 5; i++)
    {
        tempList = groupList;
        groupList = vector<TransactionGroup>();

        for(unsigned int j = 0; j < tempList.size(); j++)
        {
            sortGroup(tempList[j], sortOrder[i]);
            addGroup = splitGroup(tempList[j], sortOrder[i]);

            for(unsigned int k = 0; k < addGroup.size(); k++)
            {
                groupList.push_back(addGroup[k]);
            }
        }
    }

    transactionList = vector<Transaction>();

    for(unsigned int i = 0; i < groupList.size(); i++)
    {
        for(unsigned int j = 0; j < groupList[i].size(); j++)
        {
            transactionList.push_back(groupList[i][j]);
        }
    }

    listSorted = true;
}

void MarketReport::sortGroup(TransactionGroup& group, SortRecord sortRecord)
{
    switch(sortRecord.sort)
    {
    case Sex:
        sort(group.begin(), group.end(), (sortRecord.reverse ?  MarketReport::compareSexRev : MarketReport::compareSex ));
        break;
    case Head :
        sort(group.begin(), group.end(), (sortRecord.reverse ? MarketReport::compareHeadRev : MarketReport::compareHead ));
        break;
    case Seller:
        sort(group.begin(), group.end(), (sortRecord.reverse ? MarketReport::compareSellerRev : MarketReport::compareSeller));
        break;
    case Weight:
        sort(group.begin(), group.end(), (sortRecord.reverse ? MarketReport::compareWeightRev : MarketReport::compareWeight));
        break;
    case Price:
        sort(group.begin(), group.end(), (sortRecord.reverse ? MarketReport::comparePriceRev : MarketReport::comparePrice));
        break;
    case TransId:
        sort(group.begin(), group.end(), (sortRecord.reverse ? MarketReport::compareIdsRev : Transaction::compareIdsLT));
    case None:
    default:
        break;
    }
}

vector<MarketReport::TransactionGroup> MarketReport::splitGroup(TransactionGroup group, SortRecord sortRecord)
{

    vector<TransactionGroup> newGroups;
    TransactionGroup temp;
    bool split = false;

    if(group.size() > 0)
    {
        temp.push_back(group[0]);
    }

    for(unsigned int i = 1; i < group.size(); i++)
    {
        split = false;
        switch(sortRecord.sort)
        {
        case Sex:
            if(group[i].getAnimalCode().getTypeDescrip() != group[i - 1].getAnimalCode().getTypeDescrip())
            {
                split = true;
            }
            break;

        case Head :
            if(!(group[i].getHead() == group[i - 1].getHead()))
            {
                split = true;
            }
            break;

        case Seller:
            if(!(group[i].getSeller().getName() == group[i - 1].getSeller().getName()))
            {
                split = true;
            }

            break;

        case Weight:
            if(group[i].getAverageWeight() != group[i - 1].getAverageWeight())
            {
                split = true;
            }
            break;

        case Price:
            if(group[i].getPrice() != group[i - 1].getPrice())
            {
                split = true;
            }
            break;

        case TransId:
        case None:
            split = true;
            break;
        }

        if(split)
        {
            newGroups.push_back(temp);
            temp = TransactionGroup();
        }

        temp.push_back(group[i]);
    }

    if(temp.size() > 0)
    {
        newGroups.push_back(temp);
    }

    return newGroups;
}

bool MarketReport::compareSex(Transaction a, Transaction b)
{
    return a.getAnimalCode().getTypeDescrip() < b.getAnimalCode().getTypeDescrip();
}

bool MarketReport::compareHead(Transaction a, Transaction b)
{
    return a.getHead() < b.getHead();
}

bool MarketReport::compareSeller(Transaction a, Transaction b)
{
    return a.getSeller().getNumber() < b.getSeller().getNumber();
}

bool MarketReport::comparePrice(Transaction a, Transaction b)
{
    return a.getPrice() < b.getPrice();
}

bool MarketReport::compareWeight(Transaction a, Transaction b)
{
    return a.getAverageWeight() < b.getAverageWeight();
}


bool MarketReport::compareSexRev(Transaction a, Transaction b)
{
    return b.getAnimalCode().getTypeDescrip() < a.getAnimalCode().getTypeDescrip();
}

bool MarketReport::compareHeadRev(Transaction a, Transaction b)
{
    return b.getHead() < a.getHead();
}

bool MarketReport::compareSellerRev(Transaction a, Transaction b)
{
    return b.getSeller().getNumber() < a.getSeller().getNumber();
}

bool MarketReport::comparePriceRev(Transaction a, Transaction b)
{
    return b.getPrice() < a.getPrice();
}

bool MarketReport::compareWeightRev(Transaction a, Transaction b)
{
    return b.getAverageWeight() < a.getAverageWeight();
}

bool MarketReport::compareIdsRev(Transaction a, Transaction b)
{
    return b.getId() < a.getId();
}

string MarketReport::exportText()
{
    if(!listSorted)
    {
        sortList();
    }

    ostringstream textStream;

    for(unsigned int i = 0; i < transactionList.size(); i++)
    {
        textStream << (hideSeller ? "" : transactionList[i].getSeller().getName().getLast() + "," +  transactionList[i].getSeller().getAddress().cityStateZipStr()) <<  ","
                   << transactionList[i].getHead() << "," << transactionList[i].getAnimalCode().getDescrip() << ","
                   << transactionList[i].getAverageWeight() << "," << transactionList[i].getPrice() << endl;
    }

    return textStream.str();
}

void MarketReport::setWegthRanges(int minW, int maxW, int stepW,bool isGroupEnabled)
{
    m_minWegth = minW;
    m_maxWegth = maxW;
    m_step = stepW;
    m_isGroup = isGroupEnabled;

}
