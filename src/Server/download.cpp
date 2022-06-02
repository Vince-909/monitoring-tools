#include "Server.h"

void download(SOCKET& asock, char *username)
{
     char command[1024], response[1024], detn[1024], lfeed[1024];
     int res;
     string ans, totr;
     
     do
     {
            cout << "\n What would you like to do:\n\n 1. Download logs\n 2. Download screens\n 3. Delete stored data \n 4. Nothing, exit\n\nType a number (1-3): ";
            getline(cin, ans);
     } while ((ans != "1") && (ans != "2") && (ans != "3") && (ans != "4"));
     cout << endl;
     
     if (ans == "4")
     {
             PlaySound(TEXT("Abort.wav"), NULL, SND_FILENAME | SND_ASYNC);
             cout << " Aborting..." << endl;
             strncpy(command, "Q+",1024);
             send(asock, command, (int) strlen(command), 0);
             return;
     }
     
     strncpy(command, "D+",1024);
     send(asock, command, (int) strlen(command), 0);
  
     totr.clear();
     do
     {
                  res = recv(asock, response, 1024, 0);
                  response[res] = '\0';
                  totr += response;
     } while (totr[totr.length() - 1] != '+');
     
     sprintf(command, "%s+", ans.c_str());
     send(asock, command, (int) strlen(command), 0);
     
     if (ans == "3")
     {
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
                          cout << " There is no data to be deleted." << endl;
                          strncpy(command, "NO+",1024);
                          send(asock, command, (int) strlen(command), 0);
                          return;
             }
                          
             do
             {
                          cout << "\n Delete all " << LGcount << " logs and " << SCcount << " screens?\n Type 'y' or 'n': ";
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
             int del;
             for (int k = 1 ; k <= (LGcount + SCcount) ; k ++)
             {
                 cout << " deleting file " << k << " of " << LGcount + SCcount << "  ...  ";
                 totr.clear();
                 do
                 {
                              res = recv(asock, response, 1024, 0);
                              response[res] = '\0';
                              totr += response;
                 } while (totr[totr.length() - 1] != '+');
                 totr.erase(totr.length() - 1, 1);
                 del = atoi(totr.c_str());
                 if (del != 0) cout << "complete." << endl;
                 else
                 {
                     PlaySound(TEXT("Error.wav"), NULL, SND_FILENAME | SND_ASYNC);
                     cout << "failed." << endl;
                 }
                 strncpy(command, "OK+",1024);
                 send(asock, command, (int) strlen(command), 0);
             }
             
             return;
     }
     
     int i = 1;
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
                 if (totr == "DN") break;
                 detn[0] = totr[4]; detn[1] = totr[5]; detn[2] = '/'; detn[3] = totr[2]; detn[4] = totr[3];
                 detn[5] = '/'; detn[6] = totr[0]; detn[7] = totr[1]; strncpy(detn + 8, " at ",1016); detn[12] = totr[6];
                 detn[13] = totr[7]; detn[14] = ':'; detn[15] = totr[8]; detn[16] = totr[9];
                 if (ans == "1") detn[17] = '\0';
                 else
                 {
                     detn[17] = ':'; detn[18] = totr[10]; detn[19] = totr[11]; detn[20] = '\0';
                 }
                 cout << " " << i ++ << ". ";
                 if (ans == "1") cout << "Log started on ";
                 else cout << "Screen captured on ";
                 cout << detn << endl;
                 strncpy(command, "OK+",1024);
                 send(asock, command, (int) strlen(command), 0);
     } while (true);
     if (i == 1)
     {
           PlaySound(TEXT("Error.wav"), NULL, SND_FILENAME | SND_ASYNC);
           if (ans == "1") cout << " There are no logs available for download." << endl;
           else if (ans == "2") cout << " There are no screens available for download." << endl;
           strncpy(command, "NO+",1024);
           send(asock, command, (int) strlen(command), 0);
           return;
     }
     
     int min, max;
     do
     {
           cout << "\n Enter the index range of the files to be downloaded (e.g. 2-5): ";
           cin.getline(lfeed, 1024);
           min = atoi(strtok(lfeed, "-"));
           max = atoi(strtok(NULL, "-"));
           if (max == 0) max = min;
     } while ((min < 1) || (max > (i - 1)));
     
     string mode;
     if (ans == "1") mode = "LG";
     else if (ans == "2") mode = "SC";
     
     sprintf(command, "%d-%d+", min, max);
     send(asock, command, (int) strlen(command), 0);
     
     cout << endl;
     
     for (int k = min ; k <= max ; k ++) transfer(asock, username, k - min + 1, max - min + 1, mode);

     
     return;
}
