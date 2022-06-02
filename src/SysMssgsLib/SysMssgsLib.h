#ifndef _DLL_H_
#define _DLL_H_

#if BUILDING_DLL
# define DLLIMPORT __declspec (dllexport)
#else
# define DLLIMPORT __declspec (dllimport)
#endif

#include <windows.h>
#include <fstream>
#include <iostream>
#include <ctime>
#include <string.h>

class DLLIMPORT DllClass
{
  public:
    DllClass();
    virtual ~DllClass(void);

  private:

};

struct HEADER
{
       int index;
       bool addi;
       bool addl;
       char title[512];
};

using namespace std;

#endif
