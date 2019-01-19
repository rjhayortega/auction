#ifndef _VET_REPORT_DIALOG_H_
#define _VET_REPORT_DIALOG_H_

#include "vetreportdialogbase.h"
#include "dao/customerdao.h"

class BrucellosisReportDialog : public VetReportDialogBase 
{
public:
  BrucellosisReportDialog(QWidget* p);

protected:
  virtual string headerKey();
  virtual string headerColKey();
  virtual string headerRowKey();
  virtual string footerKey();
  virtual string heightKey();

  virtual QStringList tagLine(Tag);

private:
};

class VetInspectionReportDialog : public VetReportDialogBase
{
public:
  VetInspectionReportDialog(QWidget*);
protected:
  virtual string headerKey();
  virtual string headerColKey();
  virtual string headerRowKey();
  virtual string footerKey();
  virtual string heightKey();
  QStringList tagLine(Tag);
private:
};

class MinnesotaInspectionReportDialog : public VetReportDialogBase
{
public:
  MinnesotaInspectionReportDialog(QWidget*);
protected:
  virtual string headerKey();
  virtual string headerColKey();
  virtual string headerRowKey();
  virtual string footerKey();
  virtual string heightKey();
  QStringList tagLine(Tag);
private:
};


class SouthDakotaInspectionReportDialog : public VetReportDialogBase
{
public:
  SouthDakotaInspectionReportDialog(QWidget*);
protected:
  virtual string headerKey();
  virtual string headerColKey();
  virtual string headerRowKey();
  virtual string footerKey();
  virtual string heightKey();
  QStringList tagLine(Tag);
private:
};

class TuberculosisReportDialog : public VetReportDialogBase
{
public:
  TuberculosisReportDialog(QWidget*);
protected:
  virtual string headerKey();
  virtual string headerColKey();
  virtual string headerRowKey();
  virtual string footerKey();
  virtual string heightKey();
  QStringList tagLine(Tag);
private:
};

#endif
