#include "Server.h"

void browse(SOCKET& asock, char *username)
{
     char command[1024], response[1024], tbtk[1024];
     int res, cres;
     string totr, temp, path, input, check, stored[20];
     
     strncpy(command, "B+",1024);
     send(asock, command, (int) strlen(command), 0);
     
     totr.clear();
     do
     {
                  res = recv(asock, response, 1024, 0);
                  response[res] = '\0';
                  totr += response;
     } while (totr[totr.length() - 1] != '+');
     totr.erase(totr.length() - 1, 1);
     path = totr;
     
     
     while (1)
     {
           cout << endl << " $" << path << "> ";
           getline(cin, input);
           if (input.empty()) continue;
           strcpy(tbtk, input.c_str());
           char *t = strtok(tbtk, " ");
           check = t;
           if ((check == "ls") || (check == "rls"))
           {
                     if (check == "ls") cres = ls(asock, false);
                     else cres = ls(asock, true);
                     if (cres == 1)
                     {
                              temp.clear();
                              temp = "cd ..";
                              cd(asock, temp, path);
                     }
           }
           else if (check == "cd") cd(asock, input, path);
           else if (check == "dl")
           {
                int counter = -1;
                t = strtok(NULL, " ");
                while (t != NULL)
                {
                      stored[++ counter] = t;
                      t = strtok(NULL, " ");
                }
                for (int k = 0 ; k <= counter ; k ++) dl(asock, username, stored[k]);
           }
           else if (check == "rm")
           {
                t = strtok(NULL, " ");
                if (t != NULL) rm(asock, t);
           }
           else if (check == "exec") exec(asock, input);
           else if (check == "upl") upl(asock);
           else if (check == "mkdir") mkdir(asock, input);
           else if (check == "rmdir") rmdir(asock, input);
           else if (check == "clear") system("cls");
           else if (check == "exit")
           {
                strncpy(command, "exit+",1024);
                send(asock, command, (int) strlen(command), 0);
                return;
           }
     }
     
     
     
     
     
     return;
}


int upl(SOCKET& asock)
{
    char command[4096], response[1024], file[1024], tbdel[1024];
    int res, n, totalSize;
    float roundSz;
    string totr, ans, unit;
    HANDLE hw;
    WIN32_FIND_DATA fd;
    FILE * source;
    
    int fcount = 0;
    hw = FindFirstFile("CAPSULE\\*", &fd);
    do
    {
         if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) continue;
         fcount ++;
         totalSize += fd.nFileSizeLow;
    } while ((FindNextFile(hw, &fd) != 0));
    
    if (fcount == 0)
    {
               cout << " Failed. Capsule is empty." << endl;
               PlaySound(TEXT("Error.wav"), NULL, SND_FILENAME);
               return 1;
    }
    
    if (totalSize < 1024)
    {
                  roundSz = 1;
                  unit = "KB";
    }
    else if (totalSize < 1048576)
    {
         roundSz = ((float) totalSize) / ((float) 1024);
         unit = "KBs";
    }
    else
    {
        roundSz = ((float) totalSize) / ((float) 1048576);
        unit = "MBs";
    }
    
    do
    {
           cout << " Upload all " << fcount << " capsule files to the remote pc? (Total ";
           if (unit == "MBs") cout << setiosflags(ios::fixed) << setprecision(1) << roundSz;
           else cout << (int) roundSz;
           cout << " " << unit << ")\nType 'y' or 'n': ";
           getline(cin, ans);
    } while ((ans != "y") && (ans != "n"));
    if (ans == "n") return 1;
    
    strncpy(command, "upl+",1024);
    send(asock, command, (int) strlen(command), 0);
    totr.clear();
    do
    {
                 res = recv(asock, response, 1024, 0);
                 response[res] = '\0';
                 totr += response;
    } while (totr[totr.length() - 1] != '+');
    totr.erase(totr.length() - 1, 1);
    
    if (totr == "NO_FAIL_QQ")
    {
             cout << " can not write in the current directory." << endl;
             PlaySound(TEXT("Error.wav"), NULL, SND_FILENAME | SND_ASYNC);
             return 1;
    }
    
    hw = FindFirstFile("CAPSULE\\*", &fd);
    do
    {
           if  ((strcmp(fd.cFileName, ".") == 0) ||(strcmp(fd.cFileName, "..") == 0)) continue;
           cout << " uploading file \"" << fd.cFileName << "\"  ...  ";
           sprintf(command, "%s+", fd.cFileName);
           send(asock, command, (int) strlen(command), 0);
           totr.clear();
           do
           {
                        res = recv(asock, response, 1024, 0);
                        response[res] = '\0';
                        totr += response;
           } while (totr[totr.length() - 1] != '+');
           totr.erase(totr.length() - 1, 1);
           if (totr == "NO_FAIL_QQ")
           {
                    cout << "failed." << endl;
                    PlaySound(TEXT("Error.wav"), NULL, SND_FILENAME | SND_ASYNC);
                    continue;
           }
           sprintf(command, "%d+", fd.nFileSizeLow);
           send(asock, command, (int) strlen(command), 0);
           totr.clear();
           do
           {
                        res = recv(asock, response, 1024, 0);
                        response[res] = '\0';
                        totr += response;
           } while (totr[totr.length() - 1] != '+');
           totr.erase(totr.length() - 1, 1);
           
           sprintf(file, "CAPSULE\\%s", fd.cFileName);
           source = fopen(file, "rb");
           while (!feof(source))
           {
                 n = fread(command, sizeof(char), sizeof(command), source);
                 send(asock, command, n, 0);
           }
           fclose(source);
           totr.clear();
           do
           {
                        res = recv(asock, response, 1024, 0);
                        response[res] = '\0';
                        totr += response;
           } while (totr[totr.length() - 1] != '+');
           totr.erase(totr.length() - 1, 1);
           
           cout << "complete." << endl;
           sprintf(tbdel, "CAPSULE\\%s", fd.cFileName);
           DeleteFile(tbdel);
           
    } while ((FindNextFile(hw, &fd) != 0));
    
    strncpy(command, "DONE_THE_END_QQ+",1024);
    send(asock, command, (int) strlen(command), 0);
    
    return 0;   
}


int rmdir(SOCKET& asock, string input)
{
    char command[1024], response[1024], tbtk[1024], *t;
    int res;
    string totr, name;
    
    strncpy(tbtk, input.c_str(),1024);
    t = strtok(tbtk, " ");
    t = strtok(NULL, " ");
    if (t == NULL) return 0;
    
    strncpy(command, "rmdir+",1024);
    send(asock, command, (int) strlen(command), 0);
    
    totr.clear();
    do
    {
                 res = recv(asock, response, 1024, 0);
                 response[res] = '\0';
                 totr += response;
    } while (totr[totr.length() - 1] != '+');
    totr.erase(totr.length() - 1, 1);
    
    sprintf(command, "%s+", t);
    send(asock, command, (int) strlen(command), 0);
    
    totr.clear();
    do
    {
                 res = recv(asock, response, 1024, 0);
                 response[res] = '\0';
                 totr += response;
    } while (totr[totr.length() - 1] != '+');
    totr.erase(totr.length() - 1, 1);
    if (totr == "NO_FAILED_QQ") return 1;
    name = totr;
    
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
    
    if (totr == "NO_FAIL_QQ")
    {
             cout << " failed to delete directory \"" << name << "\"." << endl;
             PlaySound(TEXT("Error.wav"), NULL, SND_FILENAME | SND_ASYNC);
    }
    else cout << " directory \"" << name << "\" deleted successfully." << endl;

    return 0;
}


int mkdir(SOCKET& asock, string input)
{
    char command[1024], response[1024], tbtk[1024], *t;
    int res;
    string totr;
    
    strncpy(tbtk, input.c_str(),1024);
    t = strtok(tbtk, " ");
    t = strtok(NULL, " ");
    if (t == NULL) return 0;
    
    strncpy(command, "mkdir+",1024);
    send(asock, command, (int) strlen(command), 0);
    
    totr.clear();
    do
    {
                 res = recv(asock, response, 1024, 0);
                 response[res] = '\0';
                 totr += response;
    } while (totr[totr.length() - 1] != '+');
    totr.erase(totr.length() - 1, 1);
    
    sprintf(command, "%s+", t);
    send(asock, command, (int) strlen(command), 0);
    totr.clear();
    do
    {
                 res = recv(asock, response, 1024, 0);
                 response[res] = '\0';
                 totr += response;
    } while (totr[totr.length() - 1] != '+');
    totr.erase(totr.length() - 1, 1);
    
    if (totr == "NO_FAIL_QQ")
    {
             cout << " failed to create directory \"" << t << "\"." << endl;
             PlaySound(TEXT("Error.wav"), NULL, SND_FILENAME | SND_ASYNC);
    }
    else cout << " directory \"" << t << "\" created successfully." << endl;

    return 0;
}


int exec(SOCKET& asock, string input)
{
    char command[1024], response[1024], tbtk[1024], name[1024], *t;
    int res;
    string totr;
    
    strncpy(tbtk, input.c_str(),1024);
    t = strtok(tbtk, " ");
    t = strtok(NULL, " ");
    if (t == NULL) return 0;
    
    strncpy(command, "exec+",1024);
    send(asock, command, (int) strlen(command), 0);
    
    totr.clear();
    do
    {
                 res = recv(asock, response, 1024, 0);
                 response[res] = '\0';
                 totr += response;
    } while (totr[totr.length() - 1] != '+');
    totr.erase(totr.length() - 1, 1);
    
    sprintf(command, "%s+", t);
    send(asock, command, (int) strlen(command), 0);
    
    if ((command[0] >= 48) && (command[0] <= 57))
    {
		    totr.clear();
		    do
		    {
		                 res = recv(asock, response, 1024, 0);
		                 response[res] = '\0';
		                 totr += response;
		    } while (totr[totr.length() - 1] != '+');
		    totr.erase(totr.length() - 1, 1);
		    if (totr == "NO_FAILED_QQ") return 1;
		    strncpy(name, totr.c_str(),1024);
		    
		    strncpy(command, "OK+",1024);
		    send(asock, command, (int) strlen(command), 0);
	}
	else strncpy(name, t, 1024);
    totr.clear();
    do
    {
                 res = recv(asock, response, 1024, 0);
                 response[res] = '\0';
                 totr += response;
    } while (totr[totr.length() - 1] != '+');
    totr.erase(totr.length() - 1, 1);
    if (totr == "NO_FAIL_QQ")
    {
             cout << " failed to launch \"" << name << "\"." << endl;
             PlaySound(TEXT("Error.wav"), NULL, SND_FILENAME | SND_ASYNC);
    }
    else cout << " \"" << name << "\" launched successfully." << endl;

    return 0;
}


int rm(SOCKET& asock, char *arg)
{
    char command[1024], response[1024];
    int res, min, max;
    string totr, name;
    
    strncpy(command, "rm+",1024);
    send(asock, command, (int) strlen(command), 0);
    
    totr.clear();
    do
    {
                 res = recv(asock, response, 1024, 0);
                 response[res] = '\0';
                 totr += response;
    } while (totr[totr.length() - 1] != '+');
    totr.erase(totr.length() - 1, 1);
    
    min = atoi(strtok(arg, "-"));
    max = atoi(strtok(NULL, "-"));
    if (max == 0) max = min;
    sprintf(command, "%d-%d+", min, max);
    send(asock, command, (int) strlen(command), 0);
    
    for ( int i = min ; i <= max ; i ++)
    {
        totr.clear();
        do
        {
                     res = recv(asock, response, 1024, 0);
                     response[res] = '\0';
                     totr += response;
        } while (totr[totr.length() - 1] != '+');
        totr.erase(totr.length() - 1, 1);
        if (totr == "END_QQ_THE_END") return 1;
        name = totr;
        
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
        if (totr == "NO_FAIL_QQ")
        {
                 cout << " failed to delete file \"" << name << "\"." << endl;
                 PlaySound(TEXT("Error.wav"), NULL, SND_FILENAME | SND_ASYNC);
        }
        else cout << " file \"" << name << "\" deleted successfully." << endl;
        
        strncpy(command, "NEXT+",1024);
        send(asock, command, (int) strlen(command), 0);
        
    }
    
    totr.clear();
    do
    {
                 res = recv(asock, response, 1024, 0);
                 response[res] = '\0';
                 totr += response;
    } while (totr[totr.length() - 1] != '+');
    totr.erase(totr.length() - 1, 1);
    
    return 0;
}


int dl(SOCKET& asock, char *username, string arg)
{
    char command[1024], response[1024], cparg[1024];
    int min, max, res;
    string totr;
    
    strncpy(cparg, arg.c_str(),1024);
    strncpy(command, "dl+",1024);
    send(asock, command, (int) strlen(command), 0);
    
    totr.clear();
    do
    {
                 res = recv(asock, response, 1024, 0);
                 response[res] = '\0';
                 totr += response;
    } while (totr[totr.length() - 1] != '+');
    totr.erase(totr.length() - 1, 1);
    
    min = atoi(strtok(cparg, "-"));
    max = atoi(strtok(NULL, "-"));
    if (max == 0) max = min;
    sprintf(command, "%d-%d+", min, max);
    send(asock, command, (int) strlen(command), 0);
    
    for ( int i = min ; i <= max ; i ++)
    {
        totr.clear();
        do
        {
                     res = recv(asock, response, 1024, 0);
                     response[res] = '\0';
                     totr += response;
        } while (totr[totr.length() - 1] != '+');
        totr.erase(totr.length() - 1, 1);
        if (totr == "END_FAIL_THE_END") return 1;
    
        cout << " downloading file \"" << totr << "\"  ...   ";
    
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
        if (totr == "NO_FAIL_QQ")
        {
                 cout << "failed." << endl;
                 PlaySound(TEXT("Error.wav"), NULL, SND_FILENAME | SND_ASYNC);
                 continue;
        }
        strncpy(command, "OK+",1024);
        send(asock, command, (int) strlen(command), 0);
    
        transfer(asock, username, 0, 0, "WE");
    }
    
    totr.clear();
    do
    {
                 res = recv(asock, response, 1024, 0);
                 response[res] = '\0';
                 totr += response;
    } while (totr[totr.length() - 1] != '+');
    totr.erase(totr.length() - 1, 1);
    
    return 0;
}


int ls(SOCKET& asock, bool r)
{
    char command[1024], response[1024], name[2048];
    int i = 1, res, totalSize;
    float roundSz;
    string totr, unit;
    ofstream lsexit;
    
    if (r) lsexit.open("ls.txt");
    
    strncpy(command, "ls+",1024);
    send(asock, command, (int) strlen(command), 0);
    
    while (1)
    {
          totr.clear();
          do
          {
                       res = recv(asock, response, 1024, 0);
                       response[res] = '\0';
                       totr += response;
          } while (totr[totr.length() - 1] != '+');
          totr.erase(totr.length() - 1, 1);
          if ((totr == "DONE_QQ_THE_END") || (totr == "NO_FAIL_QQ")) break;
          strncpy(name, totr.c_str(),2048);
          
          if (r) lsexit << setw(3) << "[" << i ++ << "] ";
          else cout << " " << setw(3) << "[" << i ++ << "] ";
          
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
          if (totr == "DIR_FTW")
          {
                   if (r) lsexit << "\\\\";
                   else cout << "\\\\";
          }
          if (r) lsexit << name << "  ";
          else wprintf(L"%s ", name);
          
          if (totr != "DIR_FTW")
          {
                   totalSize = atoi(totr.c_str());
                   if (totalSize < 1024)
                   {
                                 roundSz = 1;
                                 unit = "KB";
                   }
                   else if (totalSize < 1048576)
                   {
                        roundSz = ((float) totalSize) / ((float) 1024);
                        unit = "KBs";
                   }
                   else
                   {
                       roundSz = ((float) totalSize) / ((float) 1048576);
                       unit = "MBs";
                   }
          
                   if (unit == "MBs")
                   {
                            if (r) lsexit << setiosflags(ios::fixed) << setprecision(1) << roundSz << unit;
                            else cout << setiosflags(ios::fixed) << setprecision(1) << roundSz << unit;
                   }
                   else
                   {
                       if (r) lsexit << setiosflags(ios::fixed) << setprecision(1) << roundSz << unit;
                       else cout << (int) roundSz << unit;
                   }
          }
          
          if (r) lsexit << endl;
          else cout << endl;
          
          strncpy(command, "OK+",1024);
          send(asock, command, (int) strlen(command), 0);
          
    }
    
    if (r)
    {
          lsexit.close();
          ShellExecute(NULL, "open", "ls.txt", NULL, NULL, SW_SHOWNORMAL);
    }
    
    if (totr == "NO_FAIL_QQ")
    {
             cout << " Failed." << endl;
             PlaySound(TEXT("Error.wav"), NULL, SND_FILENAME | SND_ASYNC);
             return 1;
    }
          
    return 0;
}


int cd(SOCKET& asock, string input, string& path)
{
    char command[1024], response[1024], tbtk[1024], name[2048], *t;
    int res;
    string totr;
    
    strncpy(tbtk, input.c_str(),1024);
    t = strtok(tbtk, " ");
    t = strtok(NULL, " ");
    if (t == NULL) return 0;
    if ((strcmp(t, "..") == 0) && (path.size() == 3)) return 0;
    if (strcmp(t, ".") == 0) return 0;
    if (((strcmp(t, "1") == 0) || (strcmp(t, "2") == 0)) && (path.size() != 3))  return 0;
    
    strncpy(command, "cd+",1024);
    send(asock, command, (int) strlen(command), 0);
    
    totr.clear();
    do
    {
                 res = recv(asock, response, 1024, 0);
                 response[res] = '\0';
                 totr += response;
    } while (totr[totr.length() - 1] != '+');
    totr.erase(totr.length() - 1, 1);
    
    
    sprintf(command, "%s+", t);
    send(asock, command, (int) strlen(command), 0);
    
    totr.clear();
    do
    {
                 res = recv(asock, response, 1024, 0);
                 response[res] = '\0';
                 totr += response;
    } while (totr[totr.length() - 1] != '+');
    totr.erase(totr.length() - 1, 1);
    strncpy(name, totr.c_str(),2048);
    
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
    if (totr == "NO_FAIL_QQ_1")
    {
             PlaySound(TEXT("Error.wav"), NULL, SND_FILENAME | SND_ASYNC);
             cout << " Failed. Directory #" << t << " does not exist." << endl;
             return 1;
    }
    else if (totr == "NO_FAIL_QQ_2")
    {
         PlaySound(TEXT("Error.wav"), NULL, SND_FILENAME | SND_ASYNC);
         cout << " Failed. \"" << name << "\" is not a directory." << endl;
         return 1;
    }
    
    path.clear();
    path = totr;
    
    return 0;
}

