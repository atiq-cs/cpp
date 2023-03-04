#define _WIN32_IE 0x0501

#include <windows.h>
#include <windowsx.h>
#include <Mmsystem.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <strsafe.h>
#include <stdio.h>
#include "resource.h"

// ref, Win32/Common/Shell
#include "TrayNotification.h"

//
//  PURPOSE : CD Ejector Software
//  Date    : 12-12-2010
//  Remarks : Working code from release version, features,
//   - Hide in Sys Tray
//   - Balloon Notification
//

#pragma comment(linker, "\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "Winmm.lib")


#define HOTKEY01 101

// Function declarations Begins
void OpenCloseMediaDrive(BOOL bOpenDrive, TCHAR cDrive);

// Function declarations Ends
BOOL CDEJECTSTATUS = TRUE;

// Class and Title are literally unused, the app doesn't have a face, it is hid in Sys Tray
// The main window class name.
static TCHAR szWindowClass[] = _T("CDEjectApp");

// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("CD Eject");

HINSTANCE g_hInst;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// TODO: update the structure of this function following
//  https://learn.microsoft.com/en-us/windows/win32/winmsg/using-window-classes
int WINAPI WinMain(HINSTANCE hInstance,
      HINSTANCE hPrevInstance,
      LPSTR lpCmdLine,
      int nCmdShow)
{
  WNDCLASSEX wcex;

  wcex.cbSize         = sizeof(WNDCLASSEX);
  wcex.style          = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc    = WndProc;
  wcex.cbClsExtra     = 0;
  wcex.cbWndExtra     = 0;
  wcex.hInstance      = hInstance;
  wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
  wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
  wcex.hbrBackground  = (HBRUSH) (COLOR_WINDOW + 1);
  wcex.lpszMenuName   = NULL;
  wcex.lpszClassName  = szWindowClass;
  wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

  if (!RegisterClassEx(&wcex))
  {
    MessageBox(NULL,
      _T("Call to RegisterClassEx failed!"),
      _T("CD Eject App"),
      NULL);

    return 1;
  }

  g_hInst = hInstance; // Store instance handle in our global variable

  HWND hWnd = CreateWindow(
    szWindowClass,
    szTitle,
    WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
    CW_USEDEFAULT, CW_USEDEFAULT,
    360, 220,
    NULL,
    NULL,
    hInstance,
    NULL
  );

  if (!hWnd)
  {
    MessageBox(NULL,
      _T("Call to CreateWindow failed!"),
      _T("CD Eject App"),
      NULL);

    return 1;
  }

  if (!RegisterHotKey(hWnd, HOTKEY01, MOD_CONTROL | MOD_NOREPEAT, 0x4A))
  {
    MessageBox(NULL,
      _T("HotKey Registration Failed"),
      _T("CD Eject App"),
      NULL);

    return -1;
  }

  // Not tested yet with common shell tray notif.
  HICON hicon = (HICON) LoadImage(    // load up the icon:
    g_hInst,                       // get the HINSTANCE to this program
    MAKEINTRESOURCE(IDI_MAIN_APP), // grab the icon out of our resource file
    IMAGE_ICON,                    // tells the versatile LoadImage function that we are loading an icon
    16, 16,                        // x and y values. we want a 16x16-pixel icon for the tray.
    0);                            // no flags necessary. these flags specify special behavior, such as loading the icon from a file instead of a resource. see source list below for MSDN docs on LoadImage.

  if (AddNotificationIcon(hWnd, ID_MINTRAYICON, UM_TRAYNOTIFY,
    hicon, _T("Press Ctrl + J to eject CD/DVDROM.")) == FALSE)
  {
    MessageBox(_T("AddNotificationIcon: error on taskbar notification!"));
    return ;
  }


  ShowWindow(hWnd, SW_HIDE);
  // UpdateWindow(hWnd);

  // Main message loop
  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return (int) msg.wParam;
}


HMENU myMenu = NULL;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message)
  {
  case WM_CREATE:
    // Create our menu. You'll want to error-check this, because if it fails the next few functions
    // may produce segmentation faults, and your menu won't work.
    myMenu = CreatePopupMenu();

    AppendMenu(myMenu, MF_STRING, ID_ABOUT, _T("About"));
    AppendMenu(myMenu, MF_STRING, ID_EXIT, _T("Exit"));
    break;

  case WM_COMMAND:
    switch (LOWORD(wParam))
    {
    case ID_ABOUT:
      MessageBox(hWnd, _T("About Menu SAFF CD Eject Software"), _T("CD Eject"), MB_OK | MB_ICONINFORMATION);
      break;
    case ID_EXIT:
      PostMessage(hWnd, WM_CLOSE, 0, 0);
      break;
    default:
      break;
    }
    break;

  case WM_HOTKEY:
    switch (LOWORD(wParam))
    {
    case HOTKEY01:
      OpenCloseMediaDrive(CDEJECTSTATUS, 0x01);

      if (CDEJECTSTATUS == TRUE)
      {
        CDEJECTSTATUS = FALSE;

        // Show notification
        if (ShowBalloon(g_hInst, hWnd, ID_MINTRAYICON, _T("CD Eject"),
          _T("CD/DVDROM has been ejected. Press Ctrl + J again to close the tray."),
          ID_EJECTICON) == FALSE)
        {
          MessageBox(hWnd, _T("ShowBalloon: tray notification error!"), _T("CDEject App"), MB_OK | MB_ICONERROR);
          return ;
        }

      } 
      else
      {
        CDEJECTSTATUS = TRUE;

        if (ShowBalloon((g_hInst, hWnd, ID_MINTRAYICON, _T("CD Eject"),
          _T("CD/DVDROM has been closed."), ID_CLOSEICON) == FALSE
        )
          MessageBox(hWnd, _T("ShowBalloon: tray notification error!"), _T("CDEject App"), MB_OK | MB_ICONERROR);
      }
      break;
    }
    break;

  case MSG_MINTRAYICON: // aha! something happened, and the tray has dutifully notified us of the event. WPARAM is the uID member of nid, and LPARAM is one of the Window mouse messages (such as WM_LBUTTONUP).
    if (wParam != ID_MINTRAYICON)
      break; // if it's not the icon we planted, then go away.

    if (lParam == WM_LBUTTONUP) // the mouse button has been released. it's time to re-maximize our window. this is basically done using the reverse of the minimizing process. make sure you look for wm_lbuttonup and not wm_lbuttondown. most tray icons handle the release, so if your icon disappears on mousedown, the next icon will get notified of a mouseup. this is not what you want to happen.
      // MessageBox(hWnd, _T("CD Eject Software"), _T("SA-OS Win32 Tutorial"), MB_OK | MB_ICONINFORMATION);
      ;
    else if (lParam == WM_RBUTTONUP) // time to display a menu.
    {
      SetForegroundWindow(hWnd);  // even though the window is hidden, we must set it to the foreground window because of popup-menu peculiarities. See the Remarks section of the MSDN page for TrackPopupMenu.
      DWORD mp = GetMessagePos(); // get the position of the mouse at the time the icon was clicked (or, at least, the time this message was generated).
      POINT cursorPos;
      GetCursorPos(&cursorPos);
      int x = (int)cursorPos.x;
      int y = (int)cursorPos.y;

      // TrackPopupMenu(myMenu, 0, GET_X_LPARAM(mp) , GET_Y_LPARAM(mp), 0, hWnd, NULL); //display the menu. you MUST #include <windowsx.h> to use those two macros.
      TrackPopupMenu(myMenu, 0, x, y, 0, hWnd, NULL); // display the menu. you MUST #include <windowsx.h> to use those two macros.
      SendMessage(hWnd, WM_NULL, 0, 0);               // send benign message to window to make sure the menu goes away.
    }                                                 // end case handler
    break;

  case WM_DESTROY:
    UnregisterHotKey(hWnd, HOTKEY01);
    PostQuitMessage(0);
    break;

  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
    break;
  }

  return 0;
}

//
// Open or Close CD Drive
// cDrive is Drive Letter to Open, or 0x01 for 'Default' drive
// Examples:
//  OpenCloseMediaDrive(TRUE, 'G');  //Open CD Door for Drive G:
//  OpenCloseMediaDrive(FALSE, 'G'); //Close CD Door for Drive G:
//  OpenCloseMediaDrive(TRUE, 1);    //Open First Logical CD Door
//
// Base code of this function from Jagdish Bhimbha (more on ReadMe)
//
void OpenCloseMediaDrive(BOOL bOpenDrive, TCHAR cDrive)
{
  MCI_OPEN_PARMS op;
  MCI_STATUS_PARMS st;
  DWORD flags;

  TCHAR szDriveName[4];
  _tcscpy_s(szDriveName, _T("X:"));

  ZeroMemory(&op, sizeof(MCI_OPEN_PARMS));
  op.lpstrDeviceType = (LPCTSTR)MCI_DEVTYPE_CD_AUDIO;

  if (cDrive > 1)
  {
    szDriveName[0] = cDrive;
    op.lpstrElementName = szDriveName;
    flags = MCI_OPEN_TYPE | MCI_OPEN_TYPE_ID | MCI_OPEN_ELEMENT | MCI_OPEN_SHAREABLE;
  }
  else
    flags = MCI_OPEN_TYPE | MCI_OPEN_TYPE_ID | MCI_OPEN_SHAREABLE;

  if (!mciSendCommand(0, MCI_OPEN, flags, (unsigned long) &op))
  {
    st.dwItem = MCI_STATUS_READY;

    if (bOpenDrive)
      mciSendCommand(op.wDeviceID, MCI_SET, MCI_SET_DOOR_OPEN, 0);
    else
      mciSendCommand(op.wDeviceID, MCI_SET, MCI_SET_DOOR_CLOSED, 0);

    mciSendCommand(op.wDeviceID, MCI_CLOSE, MCI_WAIT, 0);
  }
}
