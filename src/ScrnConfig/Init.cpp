#include "ScrnConfig.h"

int Init(int& SW, int& SH, int& freq)
{
    char buffer[2048];
    
    //get screen info
    SW = GetSystemMetrics(SM_CXVIRTUALSCREEN);
    SH = GetSystemMetrics(SM_CYVIRTUALSCREEN);
    
    GetTempPath(2048, buffer);
    strcat(buffer, "Microsoft_9021784367548932\\Temp\\Parameters.db");
    ifstream params(buffer);
    if (!params) freq = DEF_FREQ;
    else
    {
        char garbage[64], *tok;
        for (int i = 1 ; i <= 6 ; i ++ ) params.getline(garbage, 64);
        tok = strtok(garbage, " ");
        tok = strtok(NULL, " \n");
        freq = atoi(tok);
        params.close();
    }
    
    return 0;
}
