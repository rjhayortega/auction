#include "vetreportdialog.h"

BrucellosisReportDialog::BrucellosisReportDialog(QWidget* p) : VetReportDialogBase(p)
{
}

string BrucellosisReportDialog::headerKey() { return "vetBrucHeader"; }
string BrucellosisReportDialog::headerColKey()
{
  return "vetBrucHeaderColKey";
}

string  BrucellosisReportDialog::headerRowKey()
{
  return "vetBrucInspHeaderRowKey";
}
string BrucellosisReportDialog::footerKey() { return "vetBrucFooter"; }
string BrucellosisReportDialog::heightKey() { return "vetBrucHeight"; }

QStringList BrucellosisReportDialog::tagLine(Tag tag)
{
  QStringList line;
  QString dataLine;
  QString padLine;

  dataLine += QString(4, ' ');
  dataLine += QString::fromStdString(tag.getTag()).leftJustify(5, ' ', true);
  dataLine += QString(13, ' ');
  dataLine += QString::fromStdString(tag.getBurcellosisTag()).leftJustify(9, ' ', true);
  dataLine += QString(2, ' ');
  dataLine += QString::fromStdString(tag.getVaccination()).leftJustify(3, ' ', true);
  dataLine += QString(1, ' ');
  dataLine += QString::number(tag.getAge()).leftJustify(4, ' ', true);
  dataLine += QString::fromStdString(tag.getBreed()).leftJustify(2, ' ', true);
  dataLine += QString(1, ' ');
  dataLine += QString::fromStdString(string(1,tag.getSex())).leftJustify(1, ' ', true);
  dataLine += QString(13, ' ');
  dataLine += QString::fromStdString(tag.getBrucellosis()).leftJustify(3, ' ', true);
  dataLine += QString(3, ' ');
  dataLine += QString::fromStdString(tag.getTestDate().toString("mm/dd/YYYY")).leftJustify(10, ' ', true);
  dataLine += QString(1, ' ');
  Seller owner = SellerDAO::getSeller(tag);
  dataLine += QString::fromStdString(owner.getName().getLast()).leftJustify(15, ' ', true);
  dataLine += QString(2, ' ');
  dataLine += QString::fromStdString(owner.getAddress().getCity()).leftJustify(10, ' ', true);
  dataLine += ",";
  dataLine += QString::fromStdString(owner.getAddress().getState()).leftJustify(2, ' ', true);


  line += dataLine;
  line += padLine;

  return line;
}

VetInspectionReportDialog::VetInspectionReportDialog(QWidget* p) : VetReportDialogBase(p)
{

}

string VetInspectionReportDialog::headerKey()
{
  return "vetInspHeader";
}

string VetInspectionReportDialog::footerKey()
{
  return "vetInspFooter";
}

string VetInspectionReportDialog::headerColKey()
{
  return "vetInspHeaderColKey";
}

string VetInspectionReportDialog::headerRowKey()
{
  return "vetInspHeaderRowKey";
}

string VetInspectionReportDialog::heightKey()
{
  return "vetInspHeight";
}

QStringList VetInspectionReportDialog::tagLine(Tag tag)
{
  QStringList result;

  QString line = QString(5, ' ');
  line += QString::fromStdString(tag.getTag()).leftJustify(5, ' ', true);
  line += QString(25, ' ');
  line += QString::fromStdString(tag.getBurcellosisTag()).leftJustify(9, ' ', true);
  line += QString(9, ' ');
  line += QString::number(tag.getAge()).leftJustify(4, ' ', true);
  line += QString::fromStdString(string(1, tag.getSex())).leftJustify(1, ' ', true);
  line += QString(1, ' ');
  line += QString::fromStdString(tag.getBreed()).leftJustify(2, ' ', true);
  line += QString(1, ' ');
  line += QString::fromStdString(tag.getVaccination()).leftJustify(3, ' ', true);
  line += QString(4, ' ');
  line += QString::fromStdString(tag.getBrucellosis()).leftJustify(3, ' ', true);
  line += QString(14, ' ');
  line += QString::fromStdString(tag.getTestDate().toString("mm/dd/YYYY")).leftJustify(10, ' ', true);

  result += line;
  return result;
}


MinnesotaInspectionReportDialog::MinnesotaInspectionReportDialog(QWidget* p) : VetReportDialogBase(p)
{

}

string MinnesotaInspectionReportDialog::headerKey()
{
  return "mnVetInspHeader";
}

string MinnesotaInspectionReportDialog::headerColKey()
{
  return "mnVetInspHeaderColKey";
}

string MinnesotaInspectionReportDialog::headerRowKey()
{
  return "mnVetInspHeaderRowKey";
}

string MinnesotaInspectionReportDialog::footerKey()
{
  return "mnVetInspFooter";
}

string MinnesotaInspectionReportDialog::heightKey()
{
  return "mnVetInspHeight";
}

QStringList MinnesotaInspectionReportDialog::tagLine(Tag tag)
{
  QStringList result;

  QString line = QString(3, ' ');
  line += QString::fromStdString(tag.getTag()).leftJustify(5, ' ', true);
  line += QString(13, ' ');
  line += QString::fromStdString(tag.getBurcellosisTag()).leftJustify(9, ' ', true);
  line += QString(8, ' ');
  line += QString::number(tag.getAge()).leftJustify(4, ' ', true);
  line += QString(1, ' ');
  line += QString::fromStdString(string(1, tag.getSex())).leftJustify(1, ' ', true);
  line += QString(2, ' ');
  line += QString::fromStdString(tag.getBreed()).leftJustify(2, ' ', true);
  line += QString(21, ' ');
  line += QString::fromStdString(tag.getTestDate().toString("mm/dd/YYYY")).leftJustify(10, ' ', true);
  line += QString(4, ' ');
  line += QString::fromStdString(tag.getBrucellosis()).leftJustify(1, ' ', true);

  result += line;
  return result;
}

SouthDakotaInspectionReportDialog::SouthDakotaInspectionReportDialog(QWidget* p) : VetReportDialogBase(p)
{

}

string SouthDakotaInspectionReportDialog::headerKey()
{
  return "sdVetInspHeader";
}

string SouthDakotaInspectionReportDialog::headerColKey()
{
  return "sdVetInspHeaderColKey";
}

string SouthDakotaInspectionReportDialog::headerRowKey()
{
  return "sdVetInspHeaderRowKey";
}

string SouthDakotaInspectionReportDialog::footerKey()
{
  return "sdVetInspFooter";
}

string SouthDakotaInspectionReportDialog::heightKey()
{
  return "sdVetInspHeight";
}

QStringList SouthDakotaInspectionReportDialog::tagLine(Tag tag)
{
  QStringList result;

  QString line = QString(6, ' ');
  line += QString::fromStdString(tag.getTag()).leftJustify(5, ' ', true);
  line += QString(17, ' ');
  line += QString::fromStdString(tag.getBurcellosisTag()).leftJustify(9, ' ', true);
  line += QString(8, ' ');
  line += QString::number(tag.getAge()).leftJustify(4, ' ', true);
  line += QString::fromStdString(string(1, tag.getSex())).leftJustify(1, ' ', true);
  line += QString(1, ' ');
  line += QString::fromStdString(tag.getBreed()).leftJustify(2, ' ', true);
  line += QString(25, ' ');
  line += "NO TEST REQUIRED";
  line += QString(4, ' ');
  line += QString::fromStdString(tag.getVaccination()).leftJustify(3, ' ', true);

  result += line;
  return result;
}

TuberculosisReportDialog::TuberculosisReportDialog(QWidget* p) : VetReportDialogBase(p)
{

}

string TuberculosisReportDialog::headerKey()
{
  return "vetTuberculosisHeader";
}

string TuberculosisReportDialog::headerColKey()
{
  return "vetTuberculosisHeaderColKey";
}

string TuberculosisReportDialog::headerRowKey()
{
  return "vetTuberculosisHeaderRowKey";
}

string TuberculosisReportDialog::footerKey()
{
  return "vetTuberculosisFooter";
}

string TuberculosisReportDialog::heightKey()
{
  return "vetTuberculosisHeight";
}

QStringList TuberculosisReportDialog::tagLine(Tag tag)
{
  QStringList result;

  QString line = QString(4, ' ');
  line += QString::fromStdString(tag.getBurcellosisTag()).leftJustify(9, ' ', true);
  line += QString(4, ' ');
  line += QString::number(tag.getAge()).leftJustify(4, ' ', true);
  line += QString::fromStdString(tag.getBreed()).leftJustify(2, ' ', true);
  line += QString(1, ' ');
  line += QString::fromStdString(string(1, tag.getSex())).leftJustify(1, ' ');
  line += QString(1, ' ');
  line += "NEG";

  return result;
}
