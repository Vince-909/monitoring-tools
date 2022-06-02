#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <ctime>
#include <fstream>
#include <cstring>

#define DEF_FREQ 15

using namespace std;

int Init(int&, int&, int&);
void takeScreen(int, int, bool);
void convertJpeg(bool);
void store(bool);
void SaveBitmap(char*, HBITMAP);
