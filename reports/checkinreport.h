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
#ifndef STDCHECKINREPORT_H
#define STDCHECKINREPORT_H

#include "textreport.h"
//#include "../dao/invoicedao.h"
#include <iostream>
#include <string>

namespace std {

/**
	@author Bob Worthy <bworthy@keycomputerconsultants.com>
*/
class CheckinReport : public TextReport
{
public:
    CheckinReport();
    CheckinReport(
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
        );

    ~CheckinReport();
    void initDetailTable(TextReportTable& table);
    void initDetail2Table(TextReportTable& table);
    void initHeadingTable(TextReportTable& table);
    void initFootTable(TextReportTable& table);
    virtual string reportText();

private:

    int head;
    string id;
    string seller;
    string address1;
    string address2;
    string citystzip;
    string market;
    string saledate;
    string trucker;
    string opini;
    string description;
    string comment;

};

}

#endif
