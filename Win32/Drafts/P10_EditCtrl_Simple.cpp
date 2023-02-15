#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

#include "resource.h"

//
//  PURPOSE : Simple Edit Control Demo
//  Date    : 12-08-2009
//  Remarks :
//   - Curate Edit Control by Code (via CreateWindow)
//   - Demo most actions on the edit control
//     - Cut, Copy, Wrap
//     - Resize the control when window is moved
//   In addition,
//   - How to Exit when Menu Exit option is clicked
//   - Removed common code function `WinMain` body
//
//   rel: P10_BCG (project on parent dir)
//     A full fledged program to convert literal doc to html code (blogger)
//
//   TODO: wrap ANSI string with TCHAR TEXT or _T macro
//
//   ref, EditControl_Menu
//

// Global variables

// The main window class name.
// The string that appears in the application's title bar.

// Forward declarations of functions included in this code module:
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);
void CALLBACK AboutDlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,
      HINSTANCE hPrevInstance,
      LPSTR lpCmdLine,
      int nCmdShow);


LONG APIENTRY WndProc(HWND hwnd,                // window handle 
      UINT message,             // type of message 
      WPARAM wParam,            // additional information 
      LPARAM lParam)            // additional information 
{ 
    static HWND hwndEdit; 
	  int len;
    static CHAR ecText[] =  "Sample single line text "
        " using multi line."; 
 
    switch (message)  { 
        case WM_CREATE: 
            hwndEdit = CreateWindow("EDIT",      // predefined class 
                        NULL,        // no window title 
                        WS_CHILD | WS_VISIBLE | WS_VSCROLL | 
                        ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL, 
                        0, 0, 0, 0,  // set size in WM_SIZE message 
                        hwnd,        // parent window 
                        (HMENU) ID_EDITCHILD,   // edit control ID 
                        (HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE), 
                        NULL);       // pointer not needed 
 
            // Add text to the window. 
            SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM) ecText); 
            break;
 
        case WM_COMMAND: 
          switch (wParam) { 
            case ID_FILE_EXIT:
              PostMessage(hwnd, WM_CLOSE, 0, 0);
              break;
            case IDM_EDUNDO: 
              // Send WM_UNDO only if there is something to be undone. 
              if (SendMessage(hwndEdit, EM_CANUNDO, 0, 0)) 
                  SendMessage(hwndEdit, WM_UNDO, 0, 0); 
              else 
              {
                MessageBox(hwndEdit, 
                    "Nothing to undo.", 
                    "Undo notification", 
                    MB_OK); 
              }
              break; 

            case IDM_EDCUT: 
                SendMessage(hwndEdit, WM_CUT, 0, 0); 
                break; 

            case IDM_EDCOPY: 
                SendMessage(hwndEdit, WM_COPY, 0, 0); 
                break; 

            case IDM_EDPASTE: 
                SendMessage(hwndEdit, WM_PASTE, 0, 0); 
                break; 

            case IDM_EDDEL: 
                SendMessage(hwndEdit, WM_CLEAR, 0, 0); 
                break; 

            // case IDM_PASSWORD: 
            //   DialogBox(hinst,                // current instance 
            //             "PassBox",            // resource to use 
            //             hwnd,                 // parent handle 
            //             (DLGPROC) PassProc); 
            //   break;

            case IDM_WRAP: 
              // SendMessage(hwndEdit, 
              //             EM_SETWORDBREAKPROC, 
              //             (WPARAM) 0, 
              //             (LPARAM) (EDITWORDBREAKPROC) WordBreakProc); 

              // SendMessage(hwndEdit, 
              //             EM_FMTLINES, 
              //             (WPARAM) TRUE, 
              //             (LPARAM) 0); 

              // SendMessage(hwndEdit, 
              //             EM_SETSEL, 
              //             0, -1);             // select all text 

              // SendMessage(hwndEdit, WM_CUT, 0, 0); 

              // SendMessage(hwndEdit, WM_PASTE, 0, 0);
              break; 

            case IDM_ABOUT:
              len = Edit_GetText(hwndEdit, ecText, Edit_GetTextLength(hwndEdit)+1);
              MessageBox(hwndEdit, ecText, "Test", MB_OK);
              break; 

            default: 
              return DefWindowProc(hwnd, message, wParam, lParam); 
          }
          break;

        case WM_SETFOCUS: 
            SetFocus(hwndEdit); 
            break;

        case WM_SIZE: 
            // Make the edit control the size of the window's client area. 
            MoveWindow(hwndEdit, 
                0, 0,                  // starting x- and y-coordinates 
                LOWORD(lParam),        // width of client area 
                HIWORD(lParam),        // height of client area 
                TRUE);                 // repaint window 
            break;

        case WM_DESTROY: 
            PostQuitMessage(0); 
            break;

        default: 
            return DefWindowProc(hwnd, message, wParam, lParam); 
    } 
    return FALSE; 
}
