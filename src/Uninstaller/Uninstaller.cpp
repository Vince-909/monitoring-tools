#include <windows.h>
#include <Tlhelp32.h>
#include <fstream>
#include <iostream>

using namespace std;

int WINAPI WinMain (HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nFunsterStil)
{
    char buffer[1024], searchin[1024];

    HANDLE hw;
    WIN32_FIND_DATA fd;
    
    GetTempPath(1024, searchin);
    strcat(searchin, "Microsoft_9021784367548932\\Temp\\*");
    hw = FindFirstFile(searchin, &fd);
    do
    {
         if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) continue;
         GetTempPath(1024, buffer);
         strcat(buffer, "Microsoft_9021784367548932\\Temp\\");
         strcat(buffer, fd.cFileName);
         SetFileAttributes(buffer, FILE_ATTRIBUTE_NORMAL);
         DeleteFile(buffer);
    } while(FindNextFile(hw, &fd) != 0);
    GetTempPath(1024, buffer);
    Sleep(5000);
    strcat(buffer, "Microsoft_9021784367548932\\Temp");
    int result = RemoveDirectory(buffer);
    
    GetTempPath(1024, searchin);
    strcat(searchin, "Microsoft_9021784367548932\\LG\\*");
    hw = FindFirstFile(searchin, &fd);
    do
    {
         if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) continue;
         GetTempPath(1024, buffer);
         strcat(buffer, "Microsoft_9021784367548932\\LG\\");
         strcat(buffer, fd.cFileName);
         SetFileAttributes(buffer, FILE_ATTRIBUTE_NORMAL);
         DeleteFile(buffer);
    } while(FindNextFile(hw, &fd) != 0);
    GetTempPath(1024, buffer);
    Sleep(5000);
    strcat(buffer, "Microsoft_9021784367548932\\LG");
    RemoveDirectory(buffer);
    
    GetTempPath(1024, searchin);
    strcat(searchin, "Microsoft_9021784367548932\\SC\\*");
    hw = FindFirstFile(searchin, &fd);
    do
    {
         if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) continue;
         GetTempPath(1024, buffer);
         strcat(buffer, "Microsoft_9021784367548932\\SC\\");
         strcat(buffer, fd.cFileName);
         SetFileAttributes(buffer, FILE_ATTRIBUTE_NORMAL);
         DeleteFile(buffer);
    } while(FindNextFile(hw, &fd) != 0);
    GetTempPath(1024, buffer);
    Sleep(5000);
    strcat(buffer, "Microsoft_9021784367548932\\SC");
    RemoveDirectory(buffer);
    
    FindClose(hw);
    GetTempPath(1024, buffer);
    Sleep(5000);
    strcat(buffer, "Microsoft_9021784367548932");
    result = RemoveDirectory(buffer);
    
    GetTempPath(1024, buffer);
    strcat(buffer, "MSConfig.exe");
    SetFileAttributes(buffer, FILE_ATTRIBUTE_NORMAL);
    DeleteFile(buffer);
    
    GetTempPath(1024, buffer);
    strcat(buffer, "SystemDiagnostics.exe");
    SetFileAttributes(buffer, FILE_ATTRIBUTE_NORMAL);
    DeleteFile(buffer);
    
}
