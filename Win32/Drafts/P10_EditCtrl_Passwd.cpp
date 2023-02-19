#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

#include "resource.h"

//
//  PURPOSE : Password Edit Control
//  Date    : 10-12-2009
//  Remarks : 
//   - On top of OOP Template: P02_Modeless_KB, Create this DialogBox
//   - Get the hDlg, and send messages as in WndProc below
//   Or create IDC_EDIT_PASSWD during WM_CREATE or INIT as part of a regular Window
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


// On .rc file DLG def for this source file
/////////////////////////////////////////////////////////////////////////////
//
// Dialog
//
/*
DLGX_PASSWD DIALOGEX 25, 25, 288, 125
STYLE DS_SETFONT | DS_MODALFRAME | WS_POPUP | WS_CAPTION | WS_SYSMENU
CAPTION "About Box"
FONT 8, "MS Sans Serif", 0, 0, 0x0
BEGIN
    DEFPUSHBUTTON   "OK",IDOK,98,95,50,14
    PUSHBUTTON      "Cancel",IDCANCEL,179,95,50,14
    GROUPBOX        "About this program...",IDC_STATIC,7,7,225,52
    CTEXT           "An example program showing how to use Dialog Boxes",IDC_STATIC,16,18,144,33
    EDITTEXT        IDC_EDIT_PASSWD,95,69,133,14,ES_AUTOHSCROLL
END */


LRESULT CALLBACK WndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) 
{ 
    CHAR lpszPassword[16]; 
    WORD cchPassword; 

    switch (message) {
      case WM_INITDIALOG: 
        // Set password character to a plus sign (+) 
        SendDlgItemMessage(hDlg, 
                  IDC_EDIT_PASSWD, 
                  EM_SETPASSWORDCHAR, 
                  (WPARAM) '+', 
                  (LPARAM) 0); 

        // Set the default push button to "Cancel." 
        SendMessage(hDlg, 
                  DM_SETDEFID, 
                  (WPARAM) IDCANCEL, 
                  (LPARAM) 0); 

        return TRUE; 

      case WM_COMMAND: 
        // Set the default push button to "OK" when the user enters text. 
        if(HIWORD (wParam) == EN_CHANGE && 
                            LOWORD(wParam) == IDC_EDIT_PASSWD) 
        {
            SendMessage(hDlg, 
                  DM_SETDEFID, 
                  (WPARAM) IDOK, 
                  (LPARAM) 0); 
        }
        switch(wParam) 
        { 
          case IDOK: 
            // Get number of characters. 
            cchPassword = (WORD) SendDlgItemMessage(hDlg, 
                                  IDC_EDIT_PASSWD, 
                                  EM_LINELENGTH, 
                                  (WPARAM) 0, 
                                  (LPARAM) 0); 

            if (cchPassword >= 16) 
            { 
              MessageBox(hDlg, 
                  _T("Too many characters."),
                  _T("Error"),
                          MB_OK); 

              EndDialog(hDlg, TRUE); 
              return FALSE; 
            } 
            else if (cchPassword == 0) 
            { 
              MessageBox(hDlg, 
                  _T("No characters entered."),
                  _T("Error"),
                          MB_OK); 

              EndDialog(hDlg, TRUE); 
              return FALSE; 
            } 

            // Put the number of characters into first word of buffer. 
            *((LPWORD) lpszPassword) = cchPassword; 

            // Get the characters. 
            SendDlgItemMessage(hDlg, 
                  IDC_EDIT_PASSWD, 
                  EM_GETLINE, 
                  (WPARAM) 0,       // line 0 
                  (LPARAM) lpszPassword); 

            // Null-terminate the string. 
            lpszPassword[cchPassword] = 0; 

            MessageBox(hDlg, 
                  lpszPassword, 
                  _T("Did it work?"),
                  MB_OK); 

            // Call a local password-parsing function. 
            // ParsePassword(lpszPassword); 

            EndDialog(hDlg, TRUE); 
            return TRUE; 

          case IDCANCEL: 
            EndDialog(hDlg, TRUE); 
            return TRUE; 
        } 
        return 0; 
    } 
    return FALSE; 
    
    UNREFERENCED_PARAMETER(lParam); 
}
