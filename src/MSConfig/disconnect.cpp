#include "MSConfig.h"

void disconnect(SOCKET& ConnectSocket, int freq)
{
     char command[1024], response[1024];
     int res;
     string totr;
     
     sprintf(command, "%d+", freq);
     send(ConnectSocket, command, (int) strlen(command), 0);
     
     return;
}
