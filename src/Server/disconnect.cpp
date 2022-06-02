#include "Server.h"

void disconnect(SOCKET& asock, char *user)
{
     char command[1024], response[1024];
     int res;
     string totr;
     
     cout << "\n Ok, disconnecting..." << endl;
     strncpy(command, "Z+",1024);
     send(asock, command, (int) strlen(command), 0);
     
     totr.clear();
     do
     {
                  res = recv(asock, response, 1024, 0);
                  response[res] = '\0';
                  totr += response;
     } while (totr[totr.length() - 1] != '+');
     totr.erase(totr.length() - 1, 1);
     
     cout << "\n Connection terminated.\n New connection attempt from <" << user << "> expected in " << totr;
     if (totr == "1") cout << " minute." << endl;
     else cout << " minutes." << endl;
     
     return;
}
