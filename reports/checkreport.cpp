

#include "checkreport.h"


CheckReport::CheckReport(vector<Check> checkList, vector<Deposit> depositList, bool showCleared, bool showVoid, bool showOut, DisplayMode mode)
{
  this->checkList = checkList;
  this->depositList = depositList;
  this->showCleared = showCleared;
  this->showVoid = showVoid;
  this->showOut = showOut;
  this->mode = mode;
  clearCheckTotals();
  clearDepositTotals();
  showStatementBalance = false;
  statementBalance = 0.0000001;
}


string CheckReport::text()
{
  clearTables();

  if(mode == OnlyCheck || mode == CheckAndDeposit)
    {
      addTable(checkTableHeader());
      addTable(checkTable());
      addTable(checkSummaryTable());
    }

  if(mode == OnlyDeposit || mode == CheckAndDeposit)
    {
      addTable(depositTableHeader());
      addTable(depositTable());
      addTable(depositSummaryTable());
    }

  if(mode == CheckAndDeposit)
    {
      addTable(totalSummaryTableHeader());
      addTable(totalSummaryTable());
    }

  return TextReport::text();
}

void CheckReport::setStatementBalance(double statementBalance)
{
  showStatementBalance = true;
  this->statementBalance = statementBalance;
}

void CheckReport::clearCheckTotals()
{
  clearedTotal = 0.00;
  voidTotal    = 0.00;
  outTotal     = 0.00;
  uncodedTotal = 0.00;

  invoiceTotal = 0.00;
  truckerTotal = 0.00;
  miscTotal    = 0.00;
  buyerTotal   = 0.00;
  unknownTotal = 0.00;
}

void CheckReport::clearDepositTotals()
{
  clearedDepositTotal = 0.00;
  voidDepositTotal = 0.00;
  outDepositTotal = 0.00;
  uncodedDepositTotal = 0.00;
}

TextReportTable CheckReport::checkTable()
{
  TextReportTable table(7);

  clearCheckTotals();

  table.setColumnWidth(0, 6);
  table.setColumnWidth(1, 10);
  table.setColumnWidth(2, 10);
  table.setColumnWidth(3, 29);
  table.setColumnWidth(4, 10);
  table.setColumnWidth(5, 5);
  table.setColumnWidth(6, 10);


  table.setColumnAlignment(0, TextReportTable::CENTER);
  table.setColumnAlignment(1, TextReportTable::CENTER);
  table.setColumnAlignment(2, TextReportTable::RIGHT);
  table.setColumnAlignment(3, TextReportTable::LEFT);
  table.setColumnAlignment(4, TextReportTable::RIGHT);
  table.setColumnAlignment(5, TextReportTable::RIGHT);
  table.setColumnAlignment(6, TextReportTable::RIGHT);

  table.setHeader(0, "STAT");
  table.setHeader(1, "DATE");
  table.setHeader(2, "NUMBER");
  table.setHeader(3, " PAYEE");
  table.setHeader(4, "");
  table.setHeader(5, "TYPE");
  table.setHeader(6, "AMOUNT");

  char statChar;

  unsigned int row = 0;
  string typeString;

  for(unsigned int i = 0; i < checkList.size(); i++)
    {
      if(checkList[i].getStatus() == Check::Void && showVoid ||
         checkList[i].getStatus() == Check::Cleared && showCleared ||
         checkList[i].getStatus() == Check::Out && showOut)
        {
          table.insertRows(1);
          switch(checkList[i].getStatus())
            {
            case Check::Void:
              statChar = 'V';
              voidTotal += checkList[i].getAmount();
              break;

            case Check::Out:
              statChar = 'O';
              outTotal += checkList[i].getAmount();
              break;

            case Check::Cleared:
              statChar = 'C';
              clearedTotal += checkList[i].getAmount();
              break;

            default:
              statChar = '?';
              uncodedTotal += checkList[i].getAmount();
            }

          if(checkList[i].getStatus() != Check::Void)
            {
              switch(checkList[i].getType())
                {
                case Check::Invoice:
                  invoiceTotal += checkList[i].getAmount();
                  break;

                case Check::Trucker:
                  truckerTotal += checkList[i].getAmount();
                  break;

                case Check::Misc:
                  miscTotal += checkList[i].getAmount();
                  break;

                case Check::Buyer:
                  buyerTotal += checkList[i].getAmount();
                  break;

                case Check::Unknown:
                  unknownTotal += checkList[i].getAmount();
                  break;
                }
            }

          typeString = "";

          switch(checkList[i].getType())
            {
            case Check::Invoice:
              typeString = "INVC";
              break;

            case Check::Trucker:
              typeString = "TRKR";
              break;

            case Check::Misc:
              typeString = "MISC";
              break;

            case Check::Buyer:
              typeString = "BUYR";
              break;

            case Check::Unknown:
            default:
              typeString = "????";
              break;
            }

          table.setText(row, 0, string(1, statChar));
          table.setText(row, 1, checkList[i].getDate().toString("mm/dd/YYYY"));
          table.setText(row, 2, checkList[i].getNumber());
          table.setText(row, 3, string("  ") + checkList[i].getPayee());
          table.setText(row, 4, "");
          table.setText(row, 5, typeString);
          table.setText(row, 6, checkList[i].getAmount());

          row++;
        }

    }

  return table;
}

TextReportTable CheckReport::checkSummaryTable()
{
  TextReportTable table(7);

  table.setColumnAlignment(0, TextReportTable::LEFT);
  table.setColumnAlignment(1, TextReportTable::CENTER);
  table.setColumnAlignment(2, TextReportTable::RIGHT);
  table.setColumnAlignment(3, TextReportTable::CENTER);
  table.setColumnAlignment(4, TextReportTable::LEFT);
  table.setColumnAlignment(5, TextReportTable::CENTER);
  table.setColumnAlignment(6, TextReportTable::RIGHT);

  table.setColumnWidth(0, 18);
  table.setColumnWidth(1, 2);
  table.setColumnWidth(2, 10);
  table.setColumnWidth(3, 20);
  table.setColumnWidth(4, 18);
  table.setColumnWidth(5, 2);
  table.setColumnWidth(6, 10);

  table.insertRows(6);

  table.setText(1, 0, "Outstanding total:");
  table.setText(1, 2, outTotal);
  table.setText(2, 0, "Cleared total:");
  table.setText(2, 2, clearedTotal);
  table.setText(3, 0, "Void total:");
  table.setText(3, 2, voidTotal);
  table.setText(4, 0, "Uncoded total:");
  table.setText(4, 2, uncodedTotal);


  table.setText(1, 4, "Invoice total:");
  table.setText(1, 6, invoiceTotal);
  table.setText(2, 4, "Trucker total:");
  table.setText(2, 6, truckerTotal);
  table.setText(3, 4, "Misc total:");
  table.setText(3, 6, miscTotal);
  table.setText(4, 4, "Buyer Total:");
  table.setText(4, 6, buyerTotal);
  table.setText(5, 4, "Unknown total:");
  table.setText(5, 6, unknownTotal);

  for(unsigned int i = 1; i < 5; i++)
    {
      table.setText(i, 1, "$");
      table.setText(i, 5, "$");
    }

  table.setText(5, 5, "$");

  return table;
}

TextReportTable CheckReport::depositTable()
{
  clearDepositTotals();
  TextReportTable table(5);

  table.setColumnWidth(0, 5);
  table.setColumnWidth(1, 12);
  table.setColumnWidth(2, 12);
  table.setColumnWidth(3, 35);
  table.setColumnWidth(4, 12);

  table.setColumnAlignment(0, TextReportTable::CENTER);
  table.setColumnAlignment(1, TextReportTable::CENTER);
  table.setColumnAlignment(2, TextReportTable::LEFT);
  table.setColumnAlignment(3, TextReportTable::LEFT);
  table.setColumnAlignment(4, TextReportTable::RIGHT);

  table.setHeader(0, "STAT");
  table.setHeader(1, "DATE");
  table.setHeader(2, "NUMBER");
  table.setHeader(3, "COMMENT");
  table.setHeader(4, "AMOUNT");
  char statusChar;

  table.insertRows(depositList.size());

  for(unsigned int i = 0; i < depositList.size(); i++)
    {
      switch(depositList[i].getStatus())
        {
        case Check::Out:
          statusChar = 'O';
          outDepositTotal += depositList[i].getAmount();
          break;

        case Check::Void:
          statusChar = 'V';
          voidDepositTotal += depositList[i].getAmount();
          break;

        case Check::Cleared:
          statusChar = 'C';
          clearedDepositTotal += depositList[i].getAmount();
          break;

        default:
          statusChar = 'U';
          uncodedDepositTotal += depositList[i].getAmount();
          break;
        }

      table.setText(i, 0, string(1, statusChar));
      table.setText(i, 1, depositList[i].getDate().toString("mm/dd/YYYY"));
      table.setText(i, 2, depositList[i].getNumber());
      table.setText(i, 3, depositList[i].getComment());
      table.setText(i, 4, depositList[i].getAmount());
    }

  return table;
}

TextReportTable CheckReport::depositSummaryTable()
{
  TextReportTable table(2);

  table.setColumnWidth(0, 60);
  table.setColumnWidth(1, 19);

  table.setColumnAlignment(0, TextReportTable::RIGHT);
  table.setColumnAlignment(1, TextReportTable::RIGHT);

  unsigned int row = 0;

  if(showCleared)
    {
      table.insertRows(1);
      table.setText(row, 0, "CLEARED DEPOSIT TOTAL:");
      table.setText(row, 1, clearedDepositTotal);
      row++;
    }


  if(showVoid)
    {
      table.insertRows(1);
      table.setText(row, 0, "VOIDED DEPOSIT TOTAL:");
      table.setText(row, 1, voidDepositTotal);
      row++;
    }


  if(showOut)
    {
      table.insertRows(1);
      table.setText(row, 0, "OUTSTANDING DEPOSIT TOTAL:");
      table.setText(row, 1, outDepositTotal);
      row++;
    }

  if(uncodedTotal > 0.00)
    {
      table.insertRows(1);
      table.setText(row, 0, "UNCODED DEPOSIT TOTAL:");
      table.setText(row, 1, uncodedDepositTotal);
    }

  return table;
}


TextReportTable CheckReport::totalSummaryTable()
{
  TextReportTable table(4);

  table.setColumnWidth(0, 19);
  table.setColumnWidth(1, 20);
  table.setColumnWidth(2, 20);
  table.setColumnWidth(3, 20);

  table.insertRows(3);

  table.setColumnAlignment(0, TextReportTable::LEFT);
  table.setColumnAlignment(1, TextReportTable::RIGHT);
  table.setColumnAlignment(2, TextReportTable::RIGHT);
  table.setColumnAlignment(3, TextReportTable::RIGHT);

  table.setHeader(1, "DEPOSIT");
  table.setHeader(2, "CHECK");
  table.setHeader(3, "BALANCE");

  table.setText(0, 0, "CLEARED TOTAL:");
  table.setText(0, 1, clearedDepositTotal);
  table.setText(0, 2, clearedTotal);
  table.setText(0, 3, clearedDepositTotal - clearedTotal);

  table.setText(1, 0, "OUTSTANDING TOTAL:");
  table.setText(1, 1, outDepositTotal);
  table.setText(1, 2, outTotal);
  table.setText(1, 3, outDepositTotal - outTotal);

  table.setText(2, 0, "COMBINED TOTAL:");
  table.setText(2, 1, clearedDepositTotal + outDepositTotal);
  table.setText(2, 2, clearedTotal + outTotal);
  double combinedTotal = (clearedDepositTotal + outDepositTotal) - (clearedTotal + outTotal);
  table.setText(2, 3, combinedTotal);

  if(showStatementBalance)
    {
      table.insertRows(4);
      table.setText(4, 1, "Bank Statement Balance:", true);
      table.setText(4, 3, statementBalance);
      table.setText(5, 1, "Your Register Balance:", true);
      table.setText(5, 3, statementBalance + (outDepositTotal - outTotal));
    }
  return table;
}

TextReportTable CheckReport::checkTableHeader()
{
  TextReportTable table(1);
  table.setColumnWidth(0, 79);
  table.setColumnAlignment(0, TextReportTable::CENTER);
  table.insertRows(4);
  table.setText(2, 0, "CHECK REPORT");
  table.setText(3, 0, "------------");
  return table;
}


TextReportTable CheckReport::depositTableHeader()
{
  TextReportTable table(1);
  table.setColumnWidth(0, 79);
  table.setColumnAlignment(0, TextReportTable::CENTER);
  table.insertRows(4);
  table.setText(2, 0, "DEPOSIT REPORT");
  table.setText(3, 0, "--------------");
  return table;
}

TextReportTable CheckReport::totalSummaryTableHeader()
{
  TextReportTable table(1);
  table.setColumnWidth(0, 79);
  table.setColumnAlignment(0, TextReportTable::CENTER);
  table.insertRows(4);
  table.setText(2, 0, "DEPOSIT / CHECK SUMMARY");
  table.setText(3, 0, "-----------------------");
  return table;

}
