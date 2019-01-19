
#ifndef _DISPLAY_ROW_H_
#define _DISPLAY_ROW_H_

class DisplayRow
{
public:
  typedef enum 
  {
    CurrentTrans,				// display 'current' transaction
    PreviousTrans				// display previous (last) trans
  } WhichTrans;

  typedef enum
  {
    Nothing,				// 0 => row isn't used
    HeadCount,				// 1 => head count
    AverageWeight,				// 2 => avg weight (total/head)
    TotalWeight,				// 3 => total weight
    BidPrice,				// 4 => bid price
    AlternateBidPrice,				// 5 => alternate ("reciprocal") bid
    SellerNumber,				// 6 => seller number
    SellerPen,				// 7 => seller's pen (symmetry)
    BuyerNumber,				// 8 => buyer number
    BuyerPen				// 9 => buyer's pen
  } Item;

private:
  long address;
  unsigned int rowLength;
  string text;

};
#endif
