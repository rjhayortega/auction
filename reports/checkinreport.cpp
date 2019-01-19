/***************************************************************************
 *   Copyright (C) 2006 by Sargent Communications                          *
 *   krws@digitaldevelopment.net                                           *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "checkinreport.h"

#include <cstdio>

namespace std {

CheckinReport::CheckinReport() : TextReport()
{
}


CheckinReport::~CheckinReport()
{
}

///////////////////////////////////////////////////////////////////////////////

CheckinReport::CheckinReport(
        int head,
        string id,
        string seller,
        string address1,
        string address2,
        string citystzip,
        string market,
        string saledate,
        string trucker,
        string opini,
        string description,
        string comment
        )
{
  this->head = head;
  this->id = id;
  this->seller = seller;
  this->address1 = address1;
  this->address2 = address2;
  this->citystzip = citystzip;
  this->market = market;
  this->saledate = saledate;
  this->trucker = trucker;
  this->opini = opini;
  this->description = description;
  this->comment = comment;
}


///////////////////////////////////////////////////////////////////////////////


string CheckinReport::reportText()
{
  char timestring[40];
  time_t rawtime;
  struct tm * timeinfo;
  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  sprintf ( timestring, "%s", asctime (timeinfo) );
  string ts(timestring);
  int pos = ts.rfind(":");
  if ( pos > 0 && pos < ts.length() )	ts = ts.substr(0,pos);

  TextReportTable ckinHeadTable;
  TextReportTable ckinTable;
  TextReportTable ckin2Table;
  TextReportTable ckinFootTable;

  clearTables();

  // heading lines
  //
  initHeadingTable(ckinHeadTable);
  ckinHeadTable.insertRows(9);
  ckinHeadTable.setText(0, 0, market);
  //ckinHeadTable.setText(0, 1, saledate);
  ckinHeadTable.setText(0, 1, ts);

  ckinHeadTable.setText(1, 0, "==============================");
  ckinHeadTable.setText(1, 1, "====================");

  //ckinHeadTable.setText(2, 0, "");
  //ckinHeadTable.setText(2, 1, "");

  ckinHeadTable.setText(2, 0, id);

  ckinHeadTable.setText(3, 0, seller);

  ckinHeadTable.setText(4, 0, address1 + " " + address2);
  //ckinHeadTable.setText(5, 0, address2);
  ckinHeadTable.setText(5, 0, citystzip);
  ckinHeadTable.setText(6, 0, "-------------------------------------------------------");
  ckinHeadTable.setText(6, 1, "-------------------------");

  ckinHeadTable.setText(7, 0, "Trucker: " + trucker);
  ckinHeadTable.setText(7, 1, "Checked in by: " + opini);

  ckinHeadTable.setText(8, 0, "");

  // detail lines
  //
  initDetailTable(ckinTable);
  ckinTable.insertRows(1);
  initDetail2Table(ckin2Table);
  ckin2Table.insertRows(1);


  ckinTable.setText(0, 0, head);
  ckinTable.setText(0, 1, "  ");
  ckinTable.setText(0, 2, description);
  //ckinTable.setText(0, 3, comment);

  if ( comment.length() > 50 )	comment.erase(50);
  ckin2Table.setText(0, 0, comment);


  // footer lines
  //
  initFootTable(ckinFootTable);
  ckinFootTable.insertRows(5);
  ckinFootTable.setText(0, 0, " ");
  ckinFootTable.setText(1, 0, " ");
  ckinFootTable.setText(2, 0, " ");
  ckinFootTable.setText(3, 0, " ");
  ckinFootTable.setText(4, 0, " ");

  addTable(ckinHeadTable);
  addTable(ckinTable);
  addTable(ckin2Table);
  addTable(ckinFootTable);
  return TextReport::text();
}

///////////////////////////////////////////////////////////////////////////////


void CheckinReport::initDetailTable(TextReportTable& table)
{
  table = TextReportTable(3);

  table.setColumnWidth(0, 5);
  table.setColumnWidth(1,  2);
  table.setColumnWidth(2, 43);

  table.setColumnAlignment(0, TextReportTable::RIGHT);
  table.setColumnAlignment(1, TextReportTable::LEFT);
  table.setColumnAlignment(2, TextReportTable::LEFT);

  table.setHeader(0, "Head");
  table.setHeader(1, "  ");
  table.setHeader(2, "Description / Comment");

  table.setHeaderStyle(TextReportTable::NoHeader, TextReportTable::Broken);
  table.setFooterStyle(TextReportTable::NoHeader, TextReportTable::NoHeader);
}

///////////////////////////////////////////////////////////////////////////////


void CheckinReport::initDetail2Table(TextReportTable& table)
{
  table = TextReportTable(1);

  table.setColumnWidth(0, 50);

  table.setColumnAlignment(0, TextReportTable::LEFT);

  table.setHeaderStyle(TextReportTable::NoHeader, TextReportTable::Broken);
  table.setFooterStyle(TextReportTable::NoHeader, TextReportTable::NoHeader);
}


///////////////////////////////////////////////////////////////////////////////


void CheckinReport::initHeadingTable(TextReportTable& table)
{
  table = TextReportTable(2);

  table.setColumnWidth(0, 30);
  table.setColumnWidth(1, 20);

  table.setColumnAlignment(0, TextReportTable::LEFT);
  table.setColumnAlignment(1, TextReportTable::RIGHT);

  //table.setHeader(0, "");
  //table.setHeader(1, "");

  table.setHeaderStyle(TextReportTable::NoHeader, TextReportTable::Broken);
  table.setFooterStyle(TextReportTable::NoHeader, TextReportTable::NoHeader);
}


///////////////////////////////////////////////////////////////////////////////


void CheckinReport::initFootTable(TextReportTable& table)
{
  table = TextReportTable(1);

  table.setColumnWidth(0, 50);

  table.setColumnAlignment(0, TextReportTable::RIGHT);

  table.setHeaderStyle(TextReportTable::NoHeader, TextReportTable::Broken);
  table.setFooterStyle(TextReportTable::NoHeader, TextReportTable::NoHeader);
}


}
