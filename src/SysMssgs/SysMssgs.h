#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <string>
#include <fstream>
#include <ctime>

struct HEADER
{
       int index;
       bool addi;
       bool addl;
       char title[512];
};

using namespace std;

