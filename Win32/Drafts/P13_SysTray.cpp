
//
//  PURPOSE : System Tray Example
//  Date    : 10-15-2010 (last updated)
//  Remarks : Working code with
//   functionalities
//   - Hide in Sys Tray
//   - Restore Window
//   - Clicking Menu options don't work yet though!
//   However, it's interesting to note how MENU is dynamically added to the
//    Sys Tray App Icon
//
//   From the same source file, not working content is moved to 'P12_BalloonToolTip.cpp'
//
//   * We might have improved version of this in CD Eject project
//   - Removed common code function `WinMain` body
//
//

// #define _WIN32_IE 0x0501
// Win 7 Target Platform
#define WINVER	0x0601

#include <windows.h>
#include <windowsx.h>		// Track Pop UP Menu
#include <string.h>
#include <shellapi.h>
#include <tchar.h>
#include <strsafe.h>		// for StrCchCopy
#include <commctrl.h>		// for LoadIconMetric

// For linker manifest:
//  "Tutorials\T02_VS_and_Menu\ReadMe.md"
// link against library comctl32.lib, ref: above ReadMe

#include "resource.h"

void ErrorExit(LPTSTR lpszFunction);

int WINAPI WinMain(*);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hwndButton, hwndToolTip;

  switch (message) {
  case WM_CREATE:
    hwndButton = CreateWindow( 
        L"BUTTON",   // Predefined class; Unicode assumed. 
        L"Click",       // Button text. 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_CENTER,  // Styles. 
        120,         // x position. 
        80,         // y position. 
        80,        // Button width.
        25,        // Button height.
        hWnd,       // Parent window.
        NULL,       // No menu.
        g_hInst, 
        NULL);      // Pointer not needed.
    break;

  // aha! something happened, and the tray has dutifully notified us of the event. WPARAM is the uID
  // member of nid, and LPARAM is one of the Window mouse messages (such as WM_LBUTTONUP).
  case MSG_MINTRAYICON: 
    if (wParam != ID_MINTRAYICON)   //if it's not the icon we planted, then go away.
      break;

    // the mouse button has been released. it's time to re-maximize our window. this is basically
    // done using the reverse of the minimizing process. make sure you look for wm_lbuttonup and
    // not wm_lbuttondown. most tray icons handle the release, so if your icon disappears on
    // mousedown, the next icon will get notified of a mouseup. this is not what you want to happen.
    if (lParam == WM_LBUTTONUP) 
    {
      ShowWindow(hWnd, SW_SHOWDEFAULT);
      // here you can repeat the same magic with drawanimatedrects as before. just call findwindow
      // and getwindowrect for the tray, and gettitlebarinfo() for your window again (it's still
      // there, just invisible). basically, follow the exact same process given above, except switch
      // the order of the last two parameters of drawanimatedrects (the pointers to the rects) so
      // that the animation goes in reverse.
      NOTIFYICONDATA nid = { 0 };
      nid.cbSize = sizeof(NOTIFYICONDATA);
      nid.hWnd = hWnd;
      nid.uID = ID_MINTRAYICON;
      // the os only needs the hwnd and id number to know which icon to delete.
      Shell_NotifyIcon(NIM_DELETE, &nid);
    }
    // Time to display a menu
    else if (lParam == WM_RBUTTONUP)  
    {
      HMENU myMenu = NULL;
      // Create our menu. You'll want to error-check this, because if it fails the next few
      // functions may produce segmentation faults, and your menu won't work.
      myMenu = CreatePopupMenu();

      //IDM_TRAYEXIT, IDM_TRAYABOUT, and IDM_TRAYHELP are #defined constants.
      AppendMenu(myMenu, MF_STRING, IDM_TRAYEXIT, _T("Exit"));
      AppendMenu(myMenu, MF_STRING, IDM_TRAYSHOW, _T("Show"));

      // Get the position of the mouse at the time the icon was clicked (or, at least, the time this message was generated).
      DWORD mp = GetMessagePos();

      SetForegroundWindow(hWnd); //even though the window is hidden, we must set it to the foreground window because of popup-menu peculiarities. See the Remarks section of the MSDN page for TrackPopupMenu.
      TrackPopupMenu(myMenu, 0, GET_X_LPARAM(mp) , GET_Y_LPARAM(mp), 0, hWnd, NULL); //display the menu. you MUST #include <windowsx.h> to use those two macros.
      SendMessage(hWnd, WM_NULL, 0, 0); //send benign message to window to make sure the menu goes away.
    } //end case handler
    break;

  case WM_SIZE:
    if (wParam == SIZE_MINIMIZED) {
      ShowWindow(hWnd, SW_HIDE);
      //MessageBox(NULL, _T("minimized"), _T("Systray test"), NULL);
      // System Tray
      NOTIFYICONDATA nid = {0};

      // ZeroMemory(&nid, sizeof(NOTIFYICONDATA)); //intialize struct to 0.
      nid.cbSize = sizeof(NOTIFYICONDATA); //this helps the OS determine stuff. (I have no idea, but it is necessary.
      nid.hWnd = hWnd; //the hWnd and uID members allow the OS to uniquely identify your icon. One window (the hWnd) can have more than one icon, as long as they have unique uIDs.
      nid.uFlags = //some flags that determine the tray's behavior:
      NIF_ICON //we're adding an icon
      | NIF_MESSAGE //we want the tray to send a message to the window identified by hWnd when something happens to our icon (see uCallbackMesage member below).
      | NIF_TIP; //our icon has a tooltip.
      // | NIF_GUID;

      nid.uCallbackMessage = MSG_MINTRAYICON; //this message must be handled in hwnd's window procedure. more info below.
      nid.uID = ID_MINTRAYICON;
      nid.hIcon = (HICON)LoadImage( //load up the icon:
          g_hInst, //get the HINSTANCE to this program
          MAKEINTRESOURCE(IDI_PROGICON), //grab the icon out of our resource file
          IMAGE_ICON, //tells the versatile LoadImage function that we are loading an icon
          16, 16, //x and y values. we want a 16x16-pixel icon for the tray.
           // no flags necessary. these flags specify special behavior, such as loading the icon from
           // a file instead of a resource. see source list below for MSDN docs on LoadImage.
          0
        );

      _tcscpy_s(nid.szTip, _T("My very own system tray icon!")); //this string cannot be longer than 64 characters including the NULL terminator (which is added by default to string literals).
      //There are some more members of the NOTIFYICONDATA struct that are for advanced features we aren't using. See sources below for MSDN docs if you want to use balloon tips (only Win2000/XP).
      //nid.guidItem = myGUID;


      if (Shell_NotifyIcon(NIM_ADD, &nid) == FALSE) {//NIM_ADD=add an icon to the tray. Then I pass a pointer to the struct that we set up above. You should error-check this function (it returns a BOOL) but I didn't since this is just an example.
        //MessageBox(hWnd, "Error", "Notice", MB_OK);
        ErrorExit(TEXT("Shell_NotifyIcon "));
      }
    }
    break;

  case WM_DESTROY:
    PostQuitMessage(0);
    break;

  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
    break;
  }

  return 0;
}

void ErrorExit(LPTSTR lpszFunction) {
  // Retrieve the system error message for the last-error code
  LPVOID lpMsgBuf;
  LPVOID lpDisplayBuf;
  DWORD dw = GetLastError();

  FormatMessage(
    FORMAT_MESSAGE_ALLOCATE_BUFFER | 
    FORMAT_MESSAGE_FROM_SYSTEM |
    FORMAT_MESSAGE_IGNORE_INSERTS,
    NULL,
    dw,
    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
    (LPTSTR) &lpMsgBuf,
    0, NULL );

  // Display the error message and exit the process
  lpDisplayBuf = (LPVOID) LocalAlloc(LMEM_ZEROINIT, 
    (lstrlen((LPCTSTR) lpMsgBuf) + lstrlen((LPCTSTR) lpszFunction) + 40) * sizeof(TCHAR)); 

  StringCchPrintf((LPTSTR) lpDisplayBuf, 
    LocalSize(lpDisplayBuf) / sizeof(TCHAR),
    TEXT("%s failed with error %d: %s"), 
    lpszFunction, dw, lpMsgBuf);

  MessageBox(NULL, (LPCTSTR) lpDisplayBuf, TEXT("Error"), MB_OK); 

  LocalFree(lpMsgBuf);
  LocalFree(lpDisplayBuf);
  ExitProcess(dw); 
}


// MENU def in rc file looks like this
/////////////////////////////////////////////////////////////////////////////
//
// Menu
//
// IDI_SYS_TRAY_MENU MENU
// BEGIN
//     POPUP "&Menu"
//     BEGIN
//         MENUITEM "&About",                       ID_ABOUT
//         MENUITEM "&Exit",                        ID_EXIT
//     END
// END
