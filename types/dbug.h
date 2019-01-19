// -*- C++ -*-
/***************************************************************************
                          dbug.h  -  description
                             -------------------
    begin                : Fri Apr 16 2004
    copyright            : (C) 2004 by Sargent Communications
    email                : al@digitaldevelopment.net
 ***************************************************************************/

#ifndef _DBUG_H_
#define _DBUG_H_

#include <iostream>
#include <cstdlib>
#include <assert.h>

#include "timer.h"
#include <string>
#include <fstream>

class DBug
{
  private:
    static std::ofstream logFile;
  public:
    static Timer traceTimer;

    static void Trace(std::string text)
    {
      logFile << "Query: '" << text << "' took " << traceTimer.usecInterval() << " usecs " << std::endl;
    }

  static void log(std::string text)
  {
    logFile << text << std::endl;
  }

  static void log(unsigned int num)
  {
    logFile << num << std::endl;
  }
  static void initLogFile()
  {
    logFile.open(std::string(std::string(getenv("HOME")) + "/auction.dbg").c_str(), std::ios::app);
  }
};

#define KLNGRIPE(x) std::cerr << "[KLN DEBUG] " << (x) << " [KLN DEBUG END]" << std::endl

#ifndef NDEBUG
#define GRIPE(x) std::cerr << (x) << " at " << __FILE__ << ":" << __LINE__ << std::endl
#define CROAK(x) do { std::cerr << (x) << std::endl; assert(0); } while(0)
#define DBUG_LVL 1
#else
#define CROAK(x)
#define GRIPE(x) 
#define DBUG_LVL 0

#ifdef _DO_PROFILE_
#else
#define TRACE
#endif

#endif /* NDEBUG   */

#endif /* _DBUG_H_ */
