#include "ScrnConfig.h"

int WINAPI WinMain (HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nFunsterStil)

{
    int freq, SW, SH;
    
    //initialize parameters
    Init(SW, SH, freq);
    
    //single screenshot
    if (strcmp(lpszArgument, "ScreenShot") == 0)
    {
                             takeScreen(SW, SH, true);
                             convertJpeg(true);
                             store(true);
                             return 0;
    }
    
    //screenshot loop
    while (1)
    {
          takeScreen(SW, SH, false);
          convertJpeg(false);
          store(false);
          
          Sleep(freq * 60000);
    }
    
    return 0;
}
