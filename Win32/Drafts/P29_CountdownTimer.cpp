#include "resource.h"
#include <windows.h>
#include <windowsx.h>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <fstream>
#include <string>
#include <sstream>
#include <strsafe.h>
#define _WIN32_IE 0x0500
#include <commctrl.h>
using namespace std;


//
//  PURPOSE: Timer Demo
//
//  Remark : noted following,
//   - `SetBkMode` to transparent
//   - `CreateFont` call seems different as well
//   - `itoa` implementation is in Console Root ReadMe; FILE I/O examples follow
//   Code doesn't compile!
//

const bool BEEP = false;
const int winx = 375;
const int winy = 180;
long seconds = 0;
long secondsold = time (NULL);
long elapsedtime = 0; 
long lastactiveseconds = 0;
long daytime = 0;
long startdaytime = time (NULL);
long starttime = time (NULL);
int posx = 0;
int posy = 0;
int oldposx = 0;
int oldposy = 0;
bool closingdown = false;
NOTIFYICONDATA nid;


void sendtotray(HWND hwnd);
void update(HWND hwnd);
std::string get_time_string();
void ShowBalloonTip(HWND hwnd);

const char g_szClassName[] = "Time Demo";

// Used to read from file, just moved here before adding to repo
int elapsedtime = 2040;
int starttime = 1281872212;

// The Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
  HDC hDC;
  PAINTSTRUCT ps;
  RECT rect;
  HFONT hf;
  HFONT hfb;

    switch(msg) {
    case WM_CREATE:
      SetTimer(hwnd, 1, 20, NULL);
      sendtotray(hwnd);
      break;

    case WM_TIMER:
      update(hwnd);
      break;

    case WM_PAINT: {
      hDC = BeginPaint(hwnd, &ps);
      int lfHeight = -MulDiv(9, GetDeviceCaps(hDC, LOGPIXELSY), 72);
      hf = CreateFont(lfHeight, 0, 0, 0, 0, FALSE, 0, 0, 0, 0, 0, 0, 0, "Arial");
      hfb = CreateFont(lfHeight, 0, 0, 0, 700, FALSE, 0, 0, 0, 0, 0, 0, 0, "Arial");
      SetBkMode(hDC, TRANSPARENT);

      string str;
      std::ostringstream ostr;
      std::ostringstream ostr2;

      rect.left = 5; rect.right = winx; rect.top = 5; rect.bottom = 45;
      SelectObject(hDC, hfb);
      DrawText(hDC, TEXT("Overall Time:"), -1, &rect, DT_SINGLELINE);
      int years = (elapsedtime - (elapsedtime % 31536000)) / 31536000;
      int days = (elapsedtime - (elapsedtime % 86400)) / 86400  - years * 365;
      int hours = (elapsedtime - (elapsedtime % 3600)) / 3600 - years * 8760 - days * 24;
      int minutes = (elapsedtime - (elapsedtime % 60)) / 60 - years * 525600 - days * 1440 - hours * 60;
      int secs = elapsedtime - years * 31536000 - days * 86400 - hours * 3600 - minutes * 60;
      str.clear();
      if(years)
        str.append(itoa(years)+ " years ");
      if(days)
        str.append(itoa(days)+ " days ");
      if(hours)
        str.append(itoa(hours)+ " hours ");
      if(minutes)
        str.append(itoa(minutes)+ " minutes ");
      str.append(itoa(secs)+ " seconds");
      rect.left = 100;
      SelectObject(hDC, hf);
      DrawText(hDC, str.c_str(), -1, &rect, DT_SINGLELINE);
      rect.left = 5; rect.right = winx; rect.top = 25; rect.bottom = 45;
      str.clear();
      ostr << floor(double(elapsedtime)/double(seconds-starttime)*10000+.5)/100;
      str = ostr.str();
      str.append("%");
      DrawText(hDC, str.c_str(), -1, &rect, DT_SINGLELINE);
      str.clear();
      years = ((seconds-starttime) - ((seconds-starttime) % 31536000)) / 31536000;
      days = ((seconds-starttime) - ((seconds-starttime) % 86400)) / 86400  - years * 365;
      hours = ((seconds-starttime) - ((seconds-starttime) % 3600)) / 3600 - years * 8760 - days * 24;
      minutes = ((seconds-starttime) - ((seconds-starttime) % 60)) / 60 - years * 525600 - days * 1440 - hours * 60;
      str = "since ";
      if(years)
        str.append(itoa(years)+ " years ");
      if(days)
        str.append(itoa(days)+ " days ");
      if(hours)
        str.append(itoa(hours)+ " hours ");
      str.append(itoa(minutes)+ " minutes ago");
      rect.left = 100;
      DrawText(hDC, str.c_str(), -1, &rect, DT_SINGLELINE);

      rect.left = 5; rect.right = winx; rect.top = 45; rect.bottom = 85;
      SelectObject(hDC, hfb);
      DrawText(hDC, TEXT("Daily Time:"), -1, &rect, DT_SINGLELINE);
      years = (daytime - (daytime % 31536000)) / 31536000;
      days = (daytime - (daytime % 86400)) / 86400  - years * 365;
      hours = (daytime - (daytime % 3600)) / 3600 - years * 8760 - days * 24;
      minutes = (daytime - (daytime % 60)) / 60 - years * 525600 - days * 1440 - hours * 60;
      secs = daytime - years * 31536000 - days * 86400 - hours * 3600 - minutes * 60;
      str.clear();
      if(years)
        str.append(itoa(years)+ " years ");
      if(days)
        str.append(itoa(days)+ " days ");
      if(hours)
        str.append(itoa(hours)+ " hours ");
      if(minutes)
        str.append(itoa(minutes)+ " minutes ");
      str.append(itoa(secs)+ " seconds");
      rect.left = 100;
      SelectObject(hDC, hf);
      DrawText(hDC, str.c_str(), -1, &rect, DT_SINGLELINE);
      rect.left = 5; rect.right = winx; rect.top = 65; rect.bottom = 85;
      str.clear();
      ostr2 << floor(double(daytime)/double(seconds-startdaytime)*10000+.5)/100;
      str = ostr2.str();
      str.append("%");
      DrawText(hDC, str.c_str(), -1, &rect, DT_SINGLELINE);
      str.clear();
      years = ((seconds-startdaytime) - ((seconds-startdaytime) % 31536000)) / 31536000;
      days = ((seconds-startdaytime) - ((seconds-startdaytime) % 86400)) / 86400  - years * 365;
      hours = ((seconds-startdaytime) - ((seconds-startdaytime) % 3600)) / 3600 - years * 8760 - days * 24;
      minutes = ((seconds-startdaytime) - ((seconds-startdaytime) % 60)) / 60 - years * 525600 - days * 1440 - hours * 60;
      str = "since ";
      if(years)
        str.append(itoa(years)+ " years ");
      if(days)
        str.append(itoa(days)+ " days ");
      if(hours)
        str.append(itoa(hours)+ " hours ");
      str.append(itoa(minutes)+ " minutes ago");
      rect.left = 100;
      DrawText(hDC, str.c_str(), -1, &rect, DT_SINGLELINE);

      rect.left = 5; rect.right = winx; rect.top = 85; rect.bottom = 105;
      SelectObject(hDC, hfb);
      DrawText(hDC, TEXT("Total Seconds:"), -1, &rect, DT_SINGLELINE);
      str.clear();
      str = itoa(elapsedtime);
      rect.left = 100;
      SelectObject(hDC, hf);
      DrawText(hDC, str.c_str(), -1, &rect, DT_SINGLELINE);

      rect.left = 5; rect.right = winx; rect.top = 105; rect.bottom = 125;
      SelectObject(hDC, hfb);
      DrawText(hDC, TEXT("Idle:"), -1, &rect, DT_SINGLELINE);
      str.clear();
      str.append(itoa(seconds - lastactiveseconds)+ " seconds");
      rect.left = 100;
      SelectObject(hDC, hf);
      DrawText(hDC, str.c_str(), -1, &rect, DT_SINGLELINE);

      DeleteObject(hf);
      DeleteObject(hfb);
      EndPaint(hwnd, &ps);
      break;
    }

    case WM_CLOSE:
      sendtotray(hwnd);
        break;

        case WM_DESTROY:
            PostQuitMessage(0);
        break;

        case WM_ACTIVATE:
    {
      /*if((wParam == WA_INACTIVE) && (!closingdown))
      {
        sendtotray(hwnd);
      }*/
    }
        break;

    case WM_COMMAND:
      switch(LOWORD(wParam))
      {
        case ID_FILE_EXIT:
          PostQuitMessage(0);
          break;
        case ID_SEND_TRAY:
          sendtotray(hwnd);
          break;
        case IDM_TRAYEXIT:
        {
          NOTIFYICONDATA nid = { 0 };
          nid.cbSize = sizeof(NOTIFYICONDATA);
          nid.hWnd = hwnd;
          nid.uID = ID_MINTRAYICON;
          Shell_NotifyIcon(NIM_DELETE, &nid);
          PostQuitMessage(0);
          break;
        }
        case IDM_TRAYSHOW:
        {
          NOTIFYICONDATA nid = { 0 };
          nid.cbSize = sizeof(NOTIFYICONDATA);
          nid.hWnd = hwnd;
          nid.uID = ID_MINTRAYICON;
          Shell_NotifyIcon(NIM_DELETE, &nid);
          ShowWindow(hwnd, SW_SHOW);
          break;
        }
      }

    case MSG_MINTRAYICON:
      if (wParam == ID_MINTRAYICON)
      {
        if (lParam == WM_LBUTTONUP)
        {
          NOTIFYICONDATA nid = { 0 };
          nid.cbSize = sizeof(NOTIFYICONDATA);
          nid.hWnd = hwnd;
          nid.uID = ID_MINTRAYICON;
          Shell_NotifyIcon(NIM_DELETE, &nid);
          ShowWindow(hwnd, SW_SHOW);
        }
        else if (lParam == WM_RBUTTONUP) //time to display a menu.
        {
          HMENU myMenu = NULL;
          myMenu = CreatePopupMenu(); //create our menu. You'll want to error-check this, because if it fails the next few functions may produce segmentation faults, and your menu won't work.

          //IDM_TRAYEXIT, IDM_TRAYABOUT, and IDM_TRAYHELP are #defined constants.
          AppendMenu(myMenu, MF_STRING, IDM_TRAYEXIT, "Exit");
          AppendMenu(myMenu, MF_STRING, IDM_TRAYSHOW, "Show");

          DWORD mp = GetMessagePos(); //get the position of the mouse at the time the icon was clicked (or, at least, the time this message was generated).

          SetForegroundWindow(hwnd); //even though the window is hidden, we must set it to the foreground window because of popup-menu peculiarities. See the Remarks section of the MSDN page for TrackPopupMenu.
          TrackPopupMenu(myMenu, 0, GET_X_LPARAM(mp) , GET_Y_LPARAM(mp), 0, hwnd, NULL); //display the menu. you MUST #include <windowsx.h> to use those two macros.
          SendMessage(hwnd, WM_NULL, 0, 0); //send benign message to window to make sure the menu goes away.
        }
      }
      break;

    default:
      return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
  WNDCLASSEX wc;
  HWND hwnd;
  MSG Msg;

  //Step 1: Registering the Window Class
  wc.cbSize        = sizeof(WNDCLASSEX);
  wc.style         = 0;
  wc.lpfnWndProc   = WndProc;
  wc.cbClsExtra    = 0;
  wc.cbWndExtra    = 0;
  wc.hInstance     = hInstance;
  wc.hIcon         = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICONLG));
  wc.hIconSm       = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICONSM), IMAGE_ICON, 16, 16, 0);
  wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = CreateSolidBrush(RGB(236, 236, 236));
  wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MYMENU);
  wc.lpszClassName = g_szClassName;

  if(!RegisterClassEx(&wc))
  {
    MessageBox(NULL, "Window Registration Failed!", "Error!",
        MB_ICONEXCLAMATION | MB_OK);
    return 0;
  }

  // Step 2: Creating the Window
  hwnd = CreateWindowEx(
    NULL,
    g_szClassName,
    "TimeCounter 2",
    WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
    CW_USEDEFAULT, CW_USEDEFAULT, winx, winy,
    NULL, NULL, hInstance, NULL);

  if(hwnd == NULL)
  {
    MessageBox(NULL, "Window Creation Failed!", "Error!",
        MB_ICONEXCLAMATION | MB_OK);
    return 0;
  }

    // Step 3: The Message Loop
  while(GetMessage(&Msg, NULL, 0, 0) > 0)
  {
      TranslateMessage(&Msg);
      DispatchMessage(&Msg);
  }
    return Msg.wParam;
}

void sendtotray(HWND hwnd)
{
  string str = get_time_string();
  ZeroMemory(&nid, sizeof(NOTIFYICONDATA)); 
  nid.cbSize = sizeof(NOTIFYICONDATA); 
  nid.hWnd = hwnd; 
  nid.uID = ID_MINTRAYICON;
  nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
  nid.uCallbackMessage = MSG_MINTRAYICON;
  nid.hIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICONSM), IMAGE_ICON, 16, 16, 0);
  strcpy(nid.szTip, str.c_str());
  bool valid = false;
  valid = Shell_NotifyIcon(NIM_ADD, &nid);
  if(valid)
    ShowWindow(hwnd, SW_HIDE);
  /*else
    ShowWindow(hwnd, SW_SHOW);*/
}

void ShowBalloonTip(HWND hwnd)
{
  HWND hShellTrayWnd=FindWindowEx(NULL,NULL,TEXT("Shell_TrayWnd"),NULL);
  HINSTANCE hShellTrayInst = (HINSTANCE)hShellTrayWnd;
  RECT rect;
    char strTT[60] = "Switch To Unskinned Mode";
    LPTSTR lptstr = strTT;
    unsigned int uid = 0;       // for ti initialization

  // CREATE A BALLOON TIP WINDOW FOR THE IP ADDRESS EDIT
  HWND hIPAddBalloonTip;

  hIPAddBalloonTip = CreateWindowEx(WS_EX_TOPMOST, TOOLTIPS_CLASS, NULL,
                                    WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP | TTS_BALLOON,
                                    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                                    hShellTrayWnd, NULL, hShellTrayInst, NULL);

  SetWindowPos(hIPAddBalloonTip, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

  // GET COORDINATES OF THE MAIN CLIENT AREA
  GetClientRect (hShellTrayWnd, &rect);

  // struct specifying info about tool in ToolTip control
  TOOLINFO ti3;

  strcpy(strTT, "Enter an IP Address Here");
  lptstr = strTT;

  // INITIALIZE MEMBERS OF THE TOOLINFO STRUCTURE
  ti3.cbSize    = sizeof(TOOLINFO);
  ti3.uFlags    = TTF_CENTERTIP | TTF_SUBCLASS;
  ti3.hwnd    = hShellTrayWnd;
  ti3.hinst    = hShellTrayInst;
  ti3.uId      = uid;
  ti3.lpszText  = lptstr;

  // ToolTip control will cover the whole window
  ti3.rect.left  = rect.left;
  ti3.rect.top  = rect.top;
  ti3.rect.right  = rect.right;
  ti3.rect.bottom  = rect.bottom;

  // Activate the close button tooltip
  SendMessage(hIPAddBalloonTip, TTM_ADDTOOL, 0, (LPARAM) (LPTOOLINFO) &ti3);
}

void update(HWND hwnd)
{
  seconds = time (NULL);

  POINT pos;
  GetCursorPos(&pos);
  posx = pos.x;
  posy = pos.y;
  if((posx != oldposx) || (posy != oldposy))
    lastactiveseconds = seconds;
  oldposx = posx;
  oldposy = posy;
    
  if(seconds != secondsold)
  {
    if(daytime % 60 == 0)
    {
      string str = get_time_string();
      NOTIFYICONDATA nid;
      ZeroMemory(&nid, sizeof(NOTIFYICONDATA)); 
      nid.cbSize = sizeof(NOTIFYICONDATA); 
      nid.hWnd = hwnd; 
      nid.uID = ID_MINTRAYICON;
      nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
      nid.uCallbackMessage = MSG_MINTRAYICON;
      nid.hIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICONSM), IMAGE_ICON, 16, 16, 0);
      strcpy(nid.szTip, str.c_str());
      Shell_NotifyIcon(NIM_MODIFY, &nid);
    }

    InvalidateRgn(hwnd, NULL, true);
    UpdateWindow(hwnd);

    if(seconds - lastactiveseconds < 30)
    {
      elapsedtime += seconds-secondsold;
      daytime += seconds-secondsold;
    }
  }

  if((elapsedtime % 900 == 0) && (BEEP))
    Beep(523,500);
  if(elapsedtime % 20 == 0)
  {
    ofstream of;
    of.open("comptime.cnt");
    of << elapsedtime;
    of << "\n";
    of << starttime;
    of.close();
  }
  
  secondsold = seconds;
}

std::string get_time_string()
{
  string str;
  int years = (daytime - (daytime % 31536000)) / 31536000;
  int days = (daytime - (daytime % 86400)) / 86400  - years * 365;
  int hours = (daytime - (daytime % 3600)) / 3600 - years * 8760 - days * 24;
  int minutes = (daytime - (daytime % 60)) / 60 - years * 525600 - days * 1440 - hours * 60;
  int secs = daytime - years * 31536000 - days * 86400 - hours * 3600 - minutes * 60;
  if(years)
    str.append(itoa(years)+ " years ");
  if(days)
    str.append(itoa(days)+ " days ");
  if(hours)
    str.append(itoa(hours)+ " hours ");
  str.append(itoa(minutes)+ " minutes");

  return str;
}