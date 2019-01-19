#include "checkfactory.h"

// [KLN] adds
#include "globals.h"

CheckFactory::CheckFactory(Invoice invoice, bool shareCharges, vector<Prorate> prorateList)
{
  this->id = id;
  this->invoice = invoice;
  this->shareCharges = shareCharges;
  this->prorateList = prorateList;
  chargeShares = vector<double>(prorateList.size(), 0.0);
  current = prorateList.end();
}

CheckFactory::~CheckFactory()
{}

PercentageCheckFactory::~PercentageCheckFactory()
{}

FlatCheckFactory::~FlatCheckFactory()
{}

HeadCheckFactory::~HeadCheckFactory()
{}

TransactionCheckFactory::~TransactionCheckFactory()
{}


bool CheckFactory::sharesCharges()
{
  return shareCharges;
}

Invoice CheckFactory::getInvoice()
{
  return invoice;
}


PercentageCheckFactory::PercentageCheckFactory(Invoice invoice, bool shareCharges, vector<Prorate> prorateList) :
  CheckFactory(invoice, shareCharges, prorateList)
{
  totalPercentage = 0;
}

void PercentageCheckFactory::init()
{
  totalPercentage = 0;
}

vector<Check> CheckFactory::checkList()
{
    if (commissionDebug) {
        cout << "Entering CheckFactory::checkList --" << endl;
    }
  vector<Prorate>::iterator prorate;
  vector<Check> checkList;
  double amount;
  string payee;
  double remaining = invoice.gross();
  double remainingCharge = invoice.chargeTotal() + invoice.getCommissionTotal(true) + invoice.truckingTotal();
  init();

  if (commissionDebug) {
      cout << "        remaining: " << remaining << endl;
      cout << "  remainingCharge: " << remainingCharge << endl;
  }

  for(unsigned int i = 0; i < prorateList.size(); i++)
  {
    if(i != prorateList.size() - 1)
    {
        amount = getDollarAmount(getAmount(prorateList[i]));
	remaining -= amount;
		
    }
    else
    {
      amount = remaining;
    }

    if (commissionDebug) {
        cout << "  i = " << i << endl;
    }

    payee = prorateList[i].getPayee();

    if (commissionDebug) {
        cout << "    payee: " << payee << endl;
    }

    int splitIndex = payee.find_first_of("/");

    if(splitIndex != string::npos)
    {
       payee = payee.substr(splitIndex + 1) + " " + payee.substr(0, splitIndex);
    }

    if (commissionDebug) {
        cout << "    payee (split): " << payee << endl;
    }

    if(shareCharges)
    {
        if (commissionDebug) {
            cout << "    shareCharges start -- " << endl;
        }
      if(i == prorateList.size() - 1)
      {
	chargeShares[i] = remainingCharge;
      }
      else 
      {
          if (commissionDebug) {
              cout << "    amount: " << amount << endl;
              cout << "    invoice.gross(): " << invoice.gross() << endl;
              cout << "    invoice.chargeTotal(): " << invoice.chargeTotal() << endl;
              cout << "    invoice.getCommissionTotal(true): " << invoice.getCommissionTotal(true) << endl;
              cout << "    invoice.truckingTotal()): " << invoice.truckingTotal() << endl;
              cout << "    -----" << endl;
              cout << "    (amount / invoice.gross()): " << (amount / invoice.gross()) << endl;
              cout << "    (invoice.chargeTotal() + invoice.getCommissionTotal(true) + invoice.truckingTotal()): " << (invoice.chargeTotal() + invoice.getCommissionTotal(true) + invoice.truckingTotal()) << endl;
          }

           chargeShares[i] = getDollarAmount((amount / invoice.gross()) * (invoice.chargeTotal() + invoice.getCommissionTotal(true) + invoice.truckingTotal()));
	   remainingCharge -= chargeShares[i];

       if (commissionDebug) {
           cout << "    chargeShares[i]" << chargeShares[i] << endl;
           cout << "    remainingCharge: " << remainingCharge << endl;
       }
      }

      if (commissionDebug) {
          cout << "       chargeShares: " << chargeShares[i] << endl;
          cout << "    remainingCharge: " << remainingCharge << endl;
          cout << "    shareCharges end." << endl;
      }

      }

    else if(i == prorateList.size() - 1)
    {
      chargeShares[i] = invoice.chargeTotal() + invoice.getCommissionTotal(true) + invoice.truckingTotal();
    }

    if(i == prorateList.size() - 1)
    {
       payee += (invoice.getCustomer().getCompany().length() > 0 ? string(" & ") + invoice.getCustomer().getCompany() : "");
    }

    if (commissionDebug) {
        cout << "  End of loop -- payee: " << payee << " -- check amount: " << amount - chargeShares[i] << endl;
    }
    checkList.push_back(Check(0, 0, payee, amount - chargeShares[i]));
  }

  if (commissionDebug) {
      cout << "Leaving CheckFactory::checkList --" << endl;
  }
  return checkList;
}

vector<double> CheckFactory::getChargeShares()
{
  return chargeShares;
}

double CheckFactory::invoiceGross()
{
  return invoice.gross();
}

long CheckFactory::invoiceHead()
{
  return invoice.head();
}

vector<Transaction> CheckFactory::invoiceTransactions(Invoice* inv)
{
  vector<Transaction> initialVector = inv->getTransactionList();
  vector<Transaction> resultVector;

  for(unsigned int i = 0; i < initialVector.size(); i++)
  {
    switch(initialVector[i].getMode())
    {
    case Transaction::NoSaleHead:
    case Transaction::NoSaleCWT:
    case Transaction::Invalid:
      break;

    default:
      resultVector.push_back(initialVector[i]);
      break;
    }
  }
  return resultVector;
}

vector<Prorate> CheckFactory::getProrateList()
{
  return prorateList;
}

double PercentageCheckFactory::getAmount(Prorate &prorate)
{
  double percentage = prorate.getAmount();

  if(percentage < 0)
  {
    return 0;
  }

  if(totalPercentage + percentage > 100)
  {
    percentage = 100 - totalPercentage;
    totalPercentage = 100;
  }
  else
  {
    totalPercentage += percentage;
  }

  prorate.setAmount(percentage);

  if (commissionDebug) {
      cout << "getAmount in PercentageCheckFactory: " << (percentage / 100.00) * invoiceGross() << endl;
  }

  return (percentage / 100.00) * invoiceGross();
}

FlatCheckFactory::FlatCheckFactory(Invoice invoice, bool shareCharges, vector<Prorate> prorateList) : CheckFactory(invoice, shareCharges, prorateList)
{
  totalAmount = 0.0;
}

void FlatCheckFactory::init()
{
  totalAmount = 0;
}

double FlatCheckFactory::getAmount(Prorate &prorate)
{
  double amount = prorate.getAmount();

  if(amount < 0)
  {
    return 0;
  }

  if(totalAmount + amount > invoiceGross())
  {
    amount = invoiceGross() - totalAmount;
    totalAmount = invoiceGross();
  }
  else
  {
    totalAmount += amount;
  }

  if (commissionDebug) {
      cout << "getAmount in FlatCheckFactory: " << amount << endl;
  }

  return amount;
}

HeadCheckFactory::HeadCheckFactory(Invoice invoice, bool shareCharges, vector<Prorate> prorateList) : CheckFactory(invoice, shareCharges, prorateList)
{
  totalHead = 0;
}

void HeadCheckFactory::init()
{
  totalHead = 0;
}

double HeadCheckFactory::getAmount(Prorate &prorate)
{
    if (commissionDebug) {
        cout << "Entering HeadCheckFactory::getAmount" << endl;
    }

  double head = prorate.getAmount();

  if(head < 0)
  {
    return 0;
  }

  if(head + totalHead > invoiceHead())
  {
    head = invoiceHead() - totalHead;
    totalHead = invoiceHead();
  }
  else
  {
    totalHead += head;
  }
  if (commissionDebug) {
      cout << "       head: " << head << endl;
      cout << "  totalHead: " << totalHead << endl;
  }
  prorate.setAmount(head);
  if (commissionDebug) {
      cout << "       head: " << head << endl;
      cout << "  totalHead: " << totalHead << endl;
  }

  return invoiceGross() * (invoiceHead() > 0 ? double(head) / double(invoiceHead()) : 0);
}


TransactionCheckFactory::TransactionCheckFactory(Invoice invoice, bool shareCharges, vector<Prorate> prorateList) :
                         CheckFactory(invoice, shareCharges, prorateList)
{
  availableTransactions = invoiceTransactions(&invoice);
}

void TransactionCheckFactory::init()
{
  availableTransactions = invoiceTransactions(&invoice);
  lessHead = vector<long>(availableTransactions.size(), 0);
}

double TransactionCheckFactory::getAmount(Prorate &prorate)
{
  vector<Prorate::Data> dataList = prorate.getDataList();
  vector<Transaction>::iterator trans;
  double totalAmount = 0.0;

  if (commissionDebug) {
      cout << "Entering TransactionCheckFactory::getAmount" << endl;
  }

  for(unsigned int i = 0; i < dataList.size(); i++)
  {
      if (commissionDebug) {
          cout << "  totalAmount: " << totalAmount << endl;
          cout << "  i = " << i << endl;
      }

    for(unsigned int j = 0; j < availableTransactions.size(); j++)
    {
        if (commissionDebug) {
            cout << "  totalAmount: " << totalAmount << endl;
            cout << "  i = " << i << endl;
        }

        if(availableTransactions[j] == dataList[i].number)
      {
	if(dataList[i].amount > (availableTransactions[j].getHead() - lessHead[j]))
	{
	  dataList[i].amount = availableTransactions[j].getHead() - lessHead[j];
	}
    if (commissionDebug) {
        cout << "      dataList[i].amount: " << dataList[i].amount << endl;
        cout << "      availableTransactions[j].getHead(): " << availableTransactions[j].getHead() << endl;
        cout << "      availableTransactions[j].amount(): " << availableTransactions[j].amount() << endl;
        cout << "      first divided by second: " << dataList[i].amount / availableTransactions[j].getHead() << endl;
        cout << "      last value times amount: " << (dataList[i].amount / availableTransactions[j].getHead()) * availableTransactions[j].amount() << endl;
    }

	totalAmount += (dataList[i].amount / availableTransactions[j].getHead()) * availableTransactions[j].amount();

	lessHead[j] += dataList[i].amount;

	if(lessHead[j] >= availableTransactions[j].getHead())
	{
	  lessHead.erase(lessHead.begin() + j, lessHead.begin() + j);
	  availableTransactions.erase(availableTransactions.begin() + j, availableTransactions.begin() + j);
	}
         
        break;
      }
      else if(j == availableTransactions.size() - 1)
      {
	dataList.erase(dataList.begin() + i, dataList.begin() + i);
	totalAmount += 0;
      }
    }
  }
  prorate.setDataList(dataList);

  if (commissionDebug) {
      cout << "  getAmount in TransactionCheckFactory: " << totalAmount << endl;
      cout << "Leaving TransactionCheckFactory::getAmount" << endl;
  }

  return totalAmount;
}


SexCheckFactory::SexCheckFactory(Invoice invoice, bool shareCharges, vector<Prorate> prorateList) : CheckFactory(invoice, shareCharges, prorateList)
{
}

SexCheckFactory::~SexCheckFactory()
{
}

void SexCheckFactory::init()
{
  availableCodes = SexCheckFactory::getCodeList(getInvoice());
  lessHead = vector<long>(availableCodes.size(), 0);
}

vector<SexCheckFactory::CodeRecord> SexCheckFactory::getCodeList(Invoice invoice)
{
  CodeRecord code;
  vector<CodeRecord> codeList;
  vector<Transaction> transList = invoiceTransactions(&invoice);

 bool found;

  for(unsigned int i = 0; i < transList.size(); i++)
  {
    if(transList[i].getMode() != Transaction::NoSaleCWT && transList[i].getMode() != Transaction::NoSaleHead)
    {
      found = false;
      long sex = long(transList[i].getAnimalCode().getType());
      double head = double(transList[i].getHead());
      double amount = transList[i].amount();

      for(unsigned int j = 0; j < codeList.size(); j++)
      {
        if(sex == codeList[j].sex)
        {
   	  found = true;
	  codeList[j].head += head;
	  codeList[j].amount += amount;
        }
      }

      if(!found)
      {
        code.sex = sex;
        code.head = head;
        code.amount = amount;

        codeList.push_back(code);
      }
    }
  }

  return codeList;
}


double SexCheckFactory::getAmount(Prorate& prorate)
{
  vector<Prorate::Data> dataList = prorate.getDataList();
  double totalAmount = 0.00;
  double adjustedAmount = 0.00;
  
  for(unsigned int i = 0; i < dataList.size(); i++)
  {
    for(unsigned int j = 0; j < availableCodes.size(); j++)
    {
      if(dataList[i].number == availableCodes[j].sex)
      {
	if(dataList[i].amount + lessHead[j] > availableCodes[j].head)
	{
	  adjustedAmount = availableCodes[j].head - lessHead[j];
	  dataList[i].amount = (adjustedAmount > 0 ? adjustedAmount : 0);
	}

	totalAmount += (dataList[i].amount / availableCodes[j].head) * availableCodes[j].amount;
	lessHead[j] += dataList[i].amount;

	if(availableCodes[j].head - lessHead[j] <= 0)
	{
	  availableCodes.erase(availableCodes.begin() + j);
	  lessHead.erase(lessHead.begin() + j);
	}
      }
//      else if(j == availableCodes.size() - 1)
//      {
//	dataList.erase(dataList.begin() + i);
//      }
    }
  }
  return totalAmount;
}
