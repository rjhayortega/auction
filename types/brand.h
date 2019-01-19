
#ifndef _BRAND_H_
#define _BRAND_H_
#include <string>
#include <QImage>


using namespace std;

class Brand
{
public:

  Brand(long id=0, string=string(512, '\0'), string="", long=0, long=0, string="", string="");
  long getId();
  string getImageData();
  string getBrandPosition();
  long getTransactionId();
  long getHead();
  string getTag();
  string getBurcellosisTag();

  void setId(long);
  void setBrandPosition(string);
  void setTransactionId(long);
  void setHead(long);
  void setTag(string);
  void setBurcellosisTag(string);
  bool operator==(Brand);
  bool operator==(string);
  bool operator==(long);
  static bool compareTagsLT(Brand, Brand);
  QImage getBrandImage();
  string brandImageToPrintMatrix();
private:
  long id;
  string imageData;
  string brandPosition;
  long transactionNo;
  long headCount;
  string tag;
  string burcellosisTag;
};
#endif
