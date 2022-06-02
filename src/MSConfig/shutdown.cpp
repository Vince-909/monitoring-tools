#include "MSConfig.h"

void shutdown(bool shut, SOCKET& ConnectSocket)
{
     char command[1024];
     
     strcpy(command,"OK+");
     send(ConnectSocket, command, (int)strlen(command), 0);
     closesocket(ConnectSocket);
     WSACleanup();
     if (shut) system("SHUTDOWN -s -t 00");
     else system("SHUTDOWN -r -t 00");
     return;
}
