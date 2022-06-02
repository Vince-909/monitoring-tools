#include "Server.h"

void shutdown(bool shut, SOCKET& asock)
{
     char command[1024], response[1024];
     int res;
     string totr, ans;
     
     do
     {
            cout << "\n The remote PC will be ";
            if (shut) cout << "shut down.";
            else cout << "rebooted.";
            cout << "\n Proceed?\nType 'y' or 'n': ";
            getline(cin, ans);
     } while ((ans != "y") && (ans != "n"));
     if (ans == "n")
     {
             PlaySound(TEXT("Abort.wav"), NULL, SND_FILENAME | SND_ASYNC);
             cout << " Aborting..." << endl;
             strncpy(command, "Q+",1024);
             send(asock, command, (int) strlen(command), 0);
             return;
     }
     
     if (shut)
     {
              cout << "\n Ok, trying to Shut Down..." << endl;
              strncpy(command, "S+",1024);
     }         
     else
     {
         cout << "\n Ok, trying to Restart..." << endl;
         strncpy(command, "R+",1024);
     }
     
     send(asock, command, (int) strlen(command), 0);
     
     totr.clear();
     do
     {
                  res = recv(asock, response, 1024, 0);
                  response[res] = '\0';
                  totr += response;
     } while (totr[totr.length() - 1] != '+');
     
     if (shut) cout << " Shut Down Initiated." << endl;
     else cout << " Restart Initiated." << endl;
     return;
}

                
