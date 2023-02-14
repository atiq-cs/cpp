//
//  PURPOSE : Custom Date Time Picker
//  Date    : 2009-11-15
//  Remarks : 
//   - 2 Edit Controls looks like as if I was implementing a custom date time picker
//   - Tracks/shows message when Tab or any other Key is pressed and released
//   - Removed common code function `WinMain` body
//   ref, MultiObjectGUI

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

// #include "resource.h"

// Global variables

// The main window class name.
static TCHAR szWindowClass[] = "myWindowClass";

// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("Window with Multiple Controls");

HINSTANCE hInst;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow);

LONG APIENTRY MainWndProc(HWND hwnd,                // window handle 
                          UINT message,             // type of message 
                          WPARAM wParam,            // additional information 
                          LPARAM lParam)            // additional information 
{ 
  static HWND hwndEdit1; 
  static HWND hwndEdit2; 

  switch (message) 
  { 
    case WM_CREATE:
      hwndEdit1 = CreateWindow("EDIT",      // predefined class
                    NULL,        // no window title
                    WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
                    100, 100, 50, 20,  // set size in WM_SIZE message
                    hwnd,        // parent window
                    NULL,			// no control id
                    //(HMENU) ID_EDITCHILD,   // edit control ID 
                    (HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE), 
                    NULL);       // pointer not needed 

      // Add text to the window. 
      SendMessage(hwndEdit1, WM_SETTEXT, 0, (LPARAM) "10");

      hwndEdit2 = CreateWindow("EDIT",      // predefined class 
                      NULL,        // no window title 
                      WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
                      160, 100, 50, 20,  // set size in WM_SIZE message 
                      hwnd,        // parent window 
                      NULL,			// no control id
                      //(HMENU) ID_EDITCHILD,   // edit control ID 
                      (HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE), 
                      NULL);       // pointer not needed 

      // Add text to the window. 
      SendMessage(hwndEdit2, WM_SETTEXT, 0, (LPARAM) "00");
      break; 

    // case WM_COMMAND: 
    //   switch (wParam) 
    //   { 

    //       default: 
    //           return DefWindowProc(hwnd, message, wParam, lParam); 
    //   } 
    //   break;

    case WM_SETFOCUS: 
        //SetFocus(hwndEdit2); 
        return 0; 

    case WM_SIZE:
      // Probably experiment letting the edit control use the full client area
      // Make the edit control the size of the window's client area. 

      // MoveWindow(hwndEdit1, 
            // 0, 0,                  // starting x- and y-coordinates 
            // LOWORD(lParam),        // width of client area 
            // HIWORD(lParam),        // height of client area 
            // TRUE);                 // repaint window
        break;

    case WM_DESTROY:
        PostQuitMessage(0); 
        break;

    default: 
        return DefWindowProc(hwnd, message, wParam, lParam); 
  } 

  return FALSE; 
}
