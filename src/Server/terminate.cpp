#include "Server.h"

void terminate(SOCKET& asock)
{
     char command[1024], response[1024];
     int res;
     string title, totr;
     
     cout << "\n Creating a list of all the running Processes...\n" << endl;
     Sleep(1500);
     strncpy(command, "T+",1024);
     send(asock, command, (int) strlen(command), 0);
     
     do
     {
                      totr.clear();
                      do
                      {
                                   res = recv(asock, response, 1024, 0);
                                   response[res] = '\0';
                                   totr += response;
                      } while (totr[totr.length() - 1] != '+');
                      totr.erase(totr.length() - 1, 1);
                      if (totr == "\n") break;
                      cout << " " << totr << endl;
                      strncpy(command, "N+",1024);
                      send(asock, command, (int) strlen(command), 0);
     } while (true);
     
     do
     {
             cout << "\n Type the name of the Process to be Terminated: ";
             getline(cin, title);
     } while (title.empty());
     title += '+';
     
     strncpy(command, title.c_str(),1024);
     send(asock, command, (int) strlen(command), 0);
     
     totr.clear();
     do
     {
                  res = recv(asock, response, 1024, 0);
                  response[res] = '\0';
                  totr += response;
     } while (totr[totr.length() - 1] != '+');
     totr.erase(totr.length() - 1, 1);
     
     title.erase(title.length() - 1, 1);
     if (totr == "OK") cout << " Process \"" << title << "\" Terminated!" << endl;
     else
     {
         PlaySound(TEXT("Error.wav"), NULL, SND_FILENAME | SND_ASYNC);
         cout << " Error: failed to terminate process \"" << title << "\"." << endl;
     }
     
     return;
}
