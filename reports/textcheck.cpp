
#include "textcheck.h"

CheckItemCoord::CheckItemCoord(unsigned int row, unsigned int col)
{
    this->row = row;
    this->col = col;
}

unsigned int CheckItemCoord::getRow()
{
    return row;
}
unsigned int CheckItemCoord::getCol()
{
    return col;
}

bool CheckItemCoord::operator==(CheckItemCoord comparator)
{
    return this->row == comparator.row && this->col == comparator.col;
}

bool CheckItemCoord::operator<(CheckItemCoord comparator) const
{
    return (this->row < comparator.row ? true : this->row == comparator.row && this->col < comparator.col ? true : false );
}

void CheckItemCoord::setRow(unsigned int row)
{
    this->row = row;
}

void CheckItemCoord::setCol(unsigned int col)
{
    this->col = col;
}

ostream& operator<<(ostream& stream, CheckItemCoord& coord)
{
    return stream << "{" << coord.getRow() << ", " << coord.getCol() << "}";
}

CheckFormatData::CheckFormatData(CheckItemCoord amountCoord,   CheckItemCoord payeeCoord,    CheckItemCoord textAmountCoord,
                                 CheckItemCoord memoCoord,     CheckItemCoord dateCoord,     CheckItemCoord signatureCoord, string signatureFilePath,
                                 CheckItemCoord address1Coord, CheckItemCoord address2Coord, CheckItemCoord cityStZipCoord,
                                 CheckItemCoord headCoord, CheckItemCoord numberCoord)
{
    maxRow = 0;
    setAmountCoord(amountCoord);
    setPayeeCoord(payeeCoord);
    setTextAmountCoord(textAmountCoord);
    setCommentCoord(memoCoord);
    setDateCoord(dateCoord);
    setSignatureCoord(signatureCoord);
    this->signatureFilePath = signatureFilePath;

    setAddress1Coord(address1Coord);
    setAddress2Coord(address2Coord);
    setCityStZipCoord(cityStZipCoord);
    setHeadCoord(headCoord);
    setNumberCoord(numberCoord);
}

bool CheckFormatData::payeeFitsOnLine(string payee)
{
    return (130 - payeeCoord.getCol() > payee.length());
}

void CheckFormatData::setCoord(CheckItemCoord& dest, CheckItemCoord src)
{
    if(src.getRow() > maxRow && src.getCol() < 80)
    {
        maxRow = src.getRow();
    }

    dest = src;
}

void CheckFormatData::setAmountCoord(CheckItemCoord coord)
{
    if(coord.getRow() > maxRow && coord.getCol() < 80)
    {
        maxRow = coord.getRow();
    }

    this->amountCoord = coord;
}

void CheckFormatData::setNumberCoord(CheckItemCoord coord)
{
    if(coord.getRow() > maxRow && coord.getCol() < 80)
    {
        maxRow = coord.getRow();
    }

    this->numberCoord = coord;
}

void CheckFormatData::setPayeeCoord(CheckItemCoord coord)
{
    if(coord.getRow() > maxRow && coord.getCol() < 80)
    {
        maxRow = coord.getRow();
    }

    this->payeeCoord = coord;
}

void CheckFormatData::setTextAmountCoord(CheckItemCoord coord)
{
    if(coord.getRow() > maxRow && coord.getCol() < 80)
    {
        maxRow = coord.getRow();
    }
    this->textAmountCoord = coord;
}

void CheckFormatData::setCommentCoord(CheckItemCoord coord)
{
    if(coord.getRow() > maxRow && coord.getCol() < 80)
    {
        maxRow = coord.getRow();
    }
    this->commentCoord = coord;
}

void CheckFormatData::setDateCoord(CheckItemCoord coord)
{
    if(coord.getRow() > maxRow && coord.getCol() < 80)
    {
        maxRow = coord.getRow();
    }
    this->dateCoord = coord;
}

void CheckFormatData::setSignatureCoord(CheckItemCoord coord)
{ 

    if(coord.getRow() > maxRow && coord.getCol() < 80)
    {
        maxRow = coord.getRow();
    }

    this->signatureCoord = coord;
}

void CheckFormatData::setAddress1Coord(CheckItemCoord coord)
{ 

    if(coord.getRow() > maxRow && coord.getCol() < 80)
    {
        maxRow = coord.getRow();
    }

    this->address1Coord = coord;
}

void CheckFormatData::setAddress2Coord(CheckItemCoord coord)
{ 

    if(coord.getRow() > maxRow && coord.getCol() < 80)
    {
        maxRow = coord.getRow();
    }

    this->address2Coord = coord;
}

void CheckFormatData::setCityStZipCoord(CheckItemCoord coord)
{ 

    if(coord.getRow() > maxRow && coord.getCol() < 80)
    {
        maxRow = coord.getRow();
    }

    this->cityStZipCoord = coord;
}

void CheckFormatData::setHeadCoord(CheckItemCoord coord)
{ 
    if(coord.getRow() > maxRow && coord.getCol() < 80)
    {
        maxRow = coord.getRow();
    }

    this->headCoord = coord;
}

void CheckFormatData::setSignaturePath(string path)
{
    this->signatureFilePath = path;
}

unsigned int CheckFormatData::numRows()
{
    return maxRow + 1;
}

CheckItemCoord CheckFormatData::getAmountCoord()
{
    return amountCoord;
}

CheckItemCoord CheckFormatData::getPayeeCoord()
{
    return payeeCoord;
}

CheckItemCoord CheckFormatData::getTextAmountCoord()
{
    return textAmountCoord;
}

CheckItemCoord CheckFormatData::getCommentCoord()
{
    return commentCoord;
}

CheckItemCoord CheckFormatData::getDateCoord()
{
    return dateCoord;
}

CheckItemCoord CheckFormatData::getSignatureCoord()
{
    return signatureCoord;
}

CheckItemCoord CheckFormatData::getAddress1Coord()
{
    return address1Coord;
}

CheckItemCoord CheckFormatData::getAddress2Coord()
{
    return address2Coord;
}

CheckItemCoord CheckFormatData::getCityStZipCoord()
{
    return cityStZipCoord;
}

CheckItemCoord CheckFormatData::getHeadCoord()
{
    return headCoord;
}

CheckItemCoord CheckFormatData::getNumberCoord()
{
    return numberCoord;
}

string CheckFormatData::getSignaturePath()
{
    return signatureFilePath;
}


TextCheck::TextCheck(Check check, CheckFormatData positionData, Invoice invoice, bool showInvoiceData):
    m_printOnlyCheck(false)
{
    setCheck(check);
    this->formData = positionData;
    this->invoice = invoice;
    this->showInvoiceData = showInvoiceData;

    // setup lines to pre space before printing check. Value is pulled from
    // setup database.
    SetupDAO setup;
    this->setLinesPreSpace(atoi(setup.get("chkPreSpaceLines").c_str()));
}

void TextCheck::setCheck(Check check)
{
    this->check = check;
}


string TextCheck::text()
{
    vector<string> checkBody(formData.numRows(), string(80, ' '));
    vector<string>::iterator current;
    char buf[255];
    sprintf(buf, "%10.2f", check.getAmount());
    string bufStr(buf);
    unsigned int row, col;

    row = formData.getAmountCoord().getRow();
    col = formData.getAmountCoord().getCol();
    // [KLN] debug start
    // cout << "check amount: " << bufStr << " -- row: " << row << " col: " << col << endl;
    // [KLN] debug end
    col = (col > 80 ? 80 : col);
    bufStr = bufStr.substr(0, 80 - col);
    checkBody[row].replace(col, bufStr.length(), bufStr);

    row = formData.getCommentCoord().getRow();
    col = formData.getCommentCoord().getCol();
    col = (col > 80 ? 80 : col);
    bufStr = check.getComment().substr(0, 80 - (col < 80 ? col : 80));
    checkBody[row].replace(col, bufStr.length(), bufStr);

    row = formData.getDateCoord().getRow();
    col = formData.getDateCoord().getCol();
    col = (col > 80 ? 80 : col);
    bufStr = check.getDate().toString("mm-dd-YYYY").substr(0, 80 - (col < 80 ? col : 80));
    checkBody[row].replace(col, bufStr.length(), bufStr);

    row = formData.getNumberCoord().getRow();
    col = formData.getNumberCoord().getCol();
    col = (col > 80 ? 80 : col);
    sprintf(buf, "%ld", check.getNumber());
    bufStr = string(buf);
    bufStr = bufStr.substr(0, 80 - (col < 80 ? col : 80));
    checkBody[row].replace(col, bufStr.length(), bufStr);

    if(showInvoiceData)
    {
        row = formData.getAddress1Coord().getRow();
        col = formData.getAddress1Coord().getCol();
        col = (col > 80 ? 80 : col);

        if(invoice.getNumber() != 0)
        {
            bufStr = invoice.getCustomer().getAddress().getAddress1().substr(0, 80 - (col < 80 ? col : 80));
            checkBody[row].replace(col, bufStr.length(), bufStr);
        }

        row = formData.getAddress2Coord().getRow();
        col = formData.getAddress2Coord().getCol();
        col = (col > 80 ? 80 : col);

        if(invoice.getNumber() != 0)
        {
            bufStr = invoice.getCustomer().getAddress().getAddress2().substr(0, 80 - (col < 80 ? col : 80));
            checkBody[row].replace(col, bufStr.length(), bufStr);
        }

        row = formData.getCityStZipCoord().getRow();
        col = formData.getCityStZipCoord().getCol();
        col = (col > 80 ? 80 : col);

        if(invoice.getNumber() != 0)
        {
            bufStr = invoice.getCustomer().getAddress().cityStateZipStr().substr(0, 80 - (col < 80 ? col : 80));
            checkBody[row].replace(col, bufStr.length(), bufStr);
        }

        row = formData.getHeadCoord().getRow();
        col = formData.getHeadCoord().getCol();
        col = (col > 80 ? 80 : col);

        if(invoice.getNumber() != 0)
        {
            char buf[30];
            sprintf(buf, "Head: %ld", invoice.head(true, true));
            string bufStr = string(buf).substr(0, 80 - (col < 80 ? col : 80));
            checkBody[row].replace(col, bufStr.length(), bufStr);
        }
    }

    // payee line

    row = formData.getPayeeCoord().getRow();
    col = formData.getPayeeCoord().getCol();
    col = (col > 130 ? 130 : col);
    bufStr = check.getPayee().substr(0,  130 - (col < 130 ? col : 130));

    bool shrink = bufStr.length() + col >= 80;

//    string payeeStr = string(col, ' ') // Armen changed next line to this line and that doesn't work!
    checkBody[row] += "\r" + string(col, ' ')
            + (shrink ? string(1, char(15)) : string(""))
            + bufStr
            + (shrink ? string(1, char(18)) : string(""));
//    checkBody[row].replace(0,payeeStr.length(),payeeStr); // Armen added this line and that doesn't work!


    // Signatures

    row = formData.getSignatureCoord().getRow();
    col = formData.getSignatureCoord().getCol();

    string sigPath = formData.getSignaturePath();
    string text("");

    if(col < 80 && sigPath.length() > 0)
    {
        if(check.getStatus() != Check::Void)
        {
            OkiML320Image sig(QString::fromStdString(formData.getSignaturePath()));

            if(sig.getImageSize() > 0)
            {
                string padLine = string(col, ' ');

                string pad = "";

                for(unsigned int i = 0; i < 4; i++)
                {
                    pad += padLine;
                }

                sig.prependText(pad.c_str(), col, 4);
                unsigned char imageBuf[sig.getImageSize()];
                int debugSize = sig.retrieveImage(imageBuf);
                int debugImageSize = sig.getImageSize();
                string sigStr = string(sig.getImageSize(), ' ');

                for(unsigned int i = 0; i < sigStr.length(); i++)
                {
                    sigStr[i] = imageBuf[i];
                }

                checkBody[row] += string(1, '\r') + sigStr;
            }
        }
        else
        {
            bufStr = string(" VOID VOID VOID VOID VOID VOID VOID VOID VOID VOID VOID VOID", 80 - (col > 80 ? 80 : col));
            checkBody[row].replace(col, bufStr.length(), bufStr);
        }
    }

    row = formData.getTextAmountCoord().getRow();
    col = formData.getTextAmountCoord().getCol();

    if(col <= 80)
    {
        col = (col > 80 ? 80 : col);
        bufStr = check.getTextAmount().substr(0, 106 - (col < 106 ? col : 106));
        bufStr = string(col, ' ') + string(1, char(15)) + bufStr + string(1, char(18));
        // + string(1, char(80));
        checkBody[row] = checkBody[row] + '\r' + bufStr;
//        checkBody[row] = checkBody[row].replace(0,bufStr.length(),bufStr); // + '\r' + bufStr; // Armen added this line and removed previous line. This does not work!
    }

    for(current = checkBody.begin(); current != checkBody.end(); current++)
    {
        text += *current + "\n";
    }


    return text;
}

int TextCheck::getLinesPreSpace()
{
    return linesPreSpace;
}

void TextCheck::setLinesPreSpace(int lines)
{
    linesPreSpace = lines;
}

string TextCheck::getPreSpace()
{
    string prespace = "";
    int lines = getLinesPreSpace();
    for ( int i=0; i < lines; i++ )	{
        prespace += "\n";
    }
    return prespace;
}
