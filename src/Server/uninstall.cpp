#include "Server.h"

void uninstall(SOCKET& asock)
{
     char command[1024], response[1024], lfeed[1024];
     int res;
     string totr, ans;
     
     cout << endl << " IMPORTANT!" << endl;
     cout << " The entire software package will be uninstalled." << endl;
     cout << " Type 'AGREE' to proceed: ";
     cin.getline(lfeed, 1024);
     
     if (strcmp(lfeed, "AGREE") != 0)
     {
                       PlaySound(TEXT("Abort.wav"), NULL, SND_FILENAME | SND_ASYNC);
                       cout << " Aborting..." << endl;
                       strncpy(command, "Q+",1024);
                       send(asock, command, (int) strlen(command), 0);
                       return;
     }
     
     cout << "\n Initiating uninstallation process.." << endl;
     strncpy(command, "U+",1024);
     send(asock, command, (int) strlen(command), 0);
     
     totr.clear();
     do
     {
                  res = recv(asock, response, 1024, 0);
                  response[res] = '\0';
                  totr += response;
     } while (totr[totr.length() - 1] != '+');
     

 	cout << " A system restart is needed to complete the uninstallation proccess.\n Restart now?" << endl;
 	do {
 		cout << " Type 'y' or 'n': ";
 		getline(cin, ans);
	 } while ((ans != "y") && (ans != "n"));
	 if (ans == "y") strncpy(command, "OK+", 1024);
	 else strncpy(command, "NO+", 1024);
	 send(asock, command, (int) strlen(command), 0);

     
     return;
}
