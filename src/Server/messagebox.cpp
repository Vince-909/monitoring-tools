#include "Server.h"

void messagebox(SOCKET& asock)
{
     string part, title, message, totr;
     int press, res;
     char command[1024], response[1024];
     string ans;
     
                 do
                 {
                     cout << "\n Create a Message Box?\n Type 'y' or 'n': ";
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
                 cout << "\n Enter the Message Box title:" << endl;
                 getline(cin, title);
                 cout << "\n Enter the Message, end  with \".-\" on a line by themselves:" << endl;
                 while (1)
                 {
                       getline(cin, part);
                       if (part != ".-") message += (part += '\n');
                       else break;
                 }
                 string butch;
                 do
                 {
                       cout << "\n What buttons should the Box have?" << endl;
                       cout << " 1. OK" << endl;
                       cout << " 2. OK, Cancel" << endl;
                       cout << " 3. Yes, No" << endl;
                       cout << " 4. Yes, No, Cancel" << endl;
                       cout << " Type a number (1-4): ";
                       getline(cin, butch);
                 } while ((butch != "1") && (butch != "2") && (butch != "3") && (butch != "4"));

                 string iconch;
                 do
                 {
                       cout << "\n What Icon should the Box use?" << endl;
                       cout << " 1. X" << endl;
                       cout << " 2. ?" << endl;
                       cout << " 3. !" << endl;
                       cout << " 4. i" << endl;
                       cout << " Type a number (1-4): ";
                       getline(cin, iconch);
                 } while ((iconch != "1") && (iconch != "2") && (iconch != "3") && (iconch != "4"));
                 
                 strncpy(command, "M+",1024);
                 send(asock, command, (int) strlen(command), 0);
                 totr.clear();
                 do
                 {
                              res = recv(asock, response, 1024, 0);
                              response[res] = '\0';
                              totr += response;
                 } while (totr[totr.length() - 1] != '+');
                 
                 char tempbuff[128];
                 strncpy(tempbuff, title.c_str(),128);
                 strcat(tempbuff, "+");
                 send(asock, tempbuff, (int)strlen(tempbuff), 0);
                 totr.clear();
                 do
                 {
                              res = recv(asock, response, 1024, 0);
                              response[res] = '\0';
                              totr += response;
                 } while (totr[totr.length() - 1] != '+');
                 
                 strncpy(tempbuff, message.c_str(),128);
                 strcat(tempbuff, "+");
                 send(asock, tempbuff, (int)strlen(tempbuff), 0);
                 totr.clear();
                 do
                 {
                              res = recv(asock, response, 1024, 0);
                              response[res] = '\0';
                              totr += response;
                 } while (totr[totr.length() - 1] != '+');
                 
                 sprintf(command, "%s+", butch.c_str());
                 send(asock, command, (int)strlen(command), 0);
                 totr.clear();
                 do
                 {
                              res = recv(asock, response, 1024, 0);
                              response[res] = '\0';
                              totr += response;
                 } while (totr[totr.length() - 1] != '+');
                 
                 sprintf(command, "%s+", iconch.c_str());
                 send(asock, command, (int)strlen(command), 0);
                 totr.clear();
                 do
                 {
                              res = recv(asock, response, 1024, 0);
                              response[res] = '\0';
                              totr += response;
                 } while (totr[totr.length() - 1] != '+');
                 
                 strncpy(command, "GG+",1024);
                 send(asock, command, (int) strlen(command), 0);
                 
                 totr.clear();
                 do
                 {
                              res = recv(asock, response, 1024, 0);
                              response[res] = '\0';
                              totr += response;
                 } while (totr[totr.length() - 1] != '+');
                 cout << "\n Message Box Created.\nWaiting for user reaction..." << endl << endl;
                 
                 strncpy(command, "GG+",1024);
                 send(asock, command, (int) strlen(command), 0);
                 
                 totr.clear();
                 do
                 {
                              res = recv(asock, response, 1024, 0);
                              response[res] = '\0';
                              totr += response;
                 } while (totr[totr.length() - 1] != '+');
                 
                 totr.erase(totr.length() - 1, 1);
                 press = atoi(totr.c_str());
                 switch (press)
                 {
                        case 1: cout << " Button \"OK\" was pressed." << endl; break;
                        case 2: cout << " Button \"Cancel\" was pressed." << endl; break;
                        case 6: cout << " Button \"Yes\" was pressed." << endl; break;
                        case 7: cout << " Button \"No\" was pressed." << endl; break;
                 }
                 
                 Sleep(2000);
                 
                 return;
}
