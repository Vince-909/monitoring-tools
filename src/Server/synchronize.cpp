#include "Server.h"

void synchronize(SOCKET& asock, char *username)
{
     char command[1024], response[1024];
     int res, totalSize;
     float roundSz;
     string totr, ans, unit;
     
     strncpy(command, "X+",1024);
     send(asock, command, (int) strlen(command), 0);
     
     int LGcount;
     totr.clear();
     do
     {
                  res = recv(asock, response, 1024, 0);
                  response[res] = '\0';
                  totr += response;
     } while (totr[totr.length() - 1] != '+');
     totr.erase(totr.length() - 1, 1);
     LGcount = atoi(totr.c_str());
     strncpy(command, "OK+",1024);
     send(asock, command, (int)strlen(command), 0);
     
     int SCcount;
     totr.clear();
     do
     {
                  res = recv(asock, response, 1024, 0);
                  response[res] = '\0';
                  totr += response;
     } while (totr[totr.length() - 1] != '+');
     totr.erase(totr.length() - 1, 1);
     SCcount = atoi(totr.c_str());
     
     if ((LGcount == 0) && (SCcount == 0))
     {
                  PlaySound(TEXT("Error.wav"), NULL, SND_FILENAME | SND_ASYNC);
                  cout << "\n There is no data available for download." << endl;
                  strncpy(command, "NO+",1024);
                  send(asock, command, (int) strlen(command), 0);
                  return;
     }
     
     send(asock, command, (int)strlen(command), 0);
     
     totr.clear();
     do
     {
                  res = recv(asock, response, 1024, 0);
                  response[res] = '\0';
                  totr += response;
     } while (totr[totr.length() - 1] != '+');
     totr.erase(totr.length() - 1, 1);

     totalSize = atoi(totr.c_str());
     if (totalSize < 1024)
     {
                   roundSz = 1;
                   unit = "KB";
     }
     else if (totalSize < 1048576)
     {
          roundSz = ((float) totalSize) / ((float) 1024);
          unit = "KBs";
     }
     else
     {
         roundSz = ((float) totalSize) / ((float) 1048576);
         unit = "MBs";
     }
     
     do
     {
             cout << "\n Download all " << LGcount << " logs and " << SCcount << " screens (Total ";
             if (unit == "MBs") cout << setiosflags(ios::fixed) << setprecision(1) << roundSz;
             else cout << (int) roundSz;
             cout << " " << unit << ")?\n Type 'y' or 'n': ";
             getline(cin, ans);
     } while ((ans != "y") && (ans != "n"));
     if (ans == "n")
     {
             PlaySound(TEXT("Abort.wav"), NULL, SND_FILENAME | SND_ASYNC);
             cout << " Aborting..." << endl;
             strncpy(command, "NO+",1024);
             send(asock, command, (int) strlen(command), 0);
             return;
     }
     strncpy(command, "OK+",1024);
     send(asock, command, (int) strlen(command), 0);

     cout << endl;
     //receive logs 
     for (int i = 1 ; i <= LGcount ; i ++) transfer(asock, username, i, LGcount + SCcount, "LG");
     
     //receive screens
     for (int i = 1 ; i <= SCcount ; i ++) transfer(asock, username, i + LGcount, LGcount + SCcount, "SC");
     
     return;
}
