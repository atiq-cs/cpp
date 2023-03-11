//#define _WIN32_IE 0x0800
#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <wchar.h>
#include <tchar.h>
#include <commctrl.h>      // header file InitCommonControls
#include "resource.h"

//
//  PURPOSE : Blogger/HTML Code Generator
//  Date    : 01-02-2010
//  Remarks : NULL to nullptr refactor requires careful review due to use in string literals
//    Lang feature wise,
//    - It is literally a C Program, doesn't use C++ features
//    - not based on my OOP Template
//
//    I created a simple new language to represent document formatting. Let's
//     call it SBDF (Simple Blog Document Format)
//   - This program takes SBDF text on first input text edit
//   - Writes the converted output on second text edit
//    ref, Tags.txt for example (supported token list)
//
//   Demos,
//   - Win FileAPI: ReadFile
//
//   Tags.txt
//   - Be aware that this was in UTF16 LE Encoding
//    - re-saved it in UTF8 encoding which might break reading of the program when built and ran again
//
//   Trouble shooting:
//     Operator `new` on global scope seems to be not working oaky! Probably it's
//     not a good idea to use new op on Global Scope!
//
//   Not sure why we did an Init of CommonControls! I don't see visible difference
//    in app appearance!
//   Link: Add Comctl32.lib for `InitCommonControls`
//
//   ref, EditControl_BCG
//

#define insize  40000
#define outsize  45000
#define maxTag  20

// Global variables
const WORD strsize = 500;
WCHAR str[strsize];
WCHAR inputText[insize];
//[(const int)insize] =  L"<Input Text here>";
WCHAR outText[outsize];
WCHAR tagName[maxTag][20];
WORD alignment[maxTag];
BOOL isDynamicCode[maxTag];
BOOL spanInCode[maxTag];
WCHAR BeginCode[maxTag][300];
WCHAR EndCode[maxTag][50];
WORD BCLen[maxTag];
int whichTag = -1;
WORD tagTot;
DWORD outWritten;

WORD codingMode;

// The main window class name.
static TCHAR szWindowClass[] = _T("win32app");

// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("HTML Code Generator");

HINSTANCE hInst;
HWND hwndPB;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void CALLBACK AboutDlgProc(HWND, UINT, WPARAM, LPARAM);

void processInput();
BOOL endTagS(PBOOL);
BOOL endTag(PBOOL, PWORD);
BOOL writeCodeForTag(LPWSTR, PBOOL, PWORD, PBOOL);
void writeError(int);
void DisplayError(LPTSTR lpszFunction);
BOOL loadTagFromFile();
int getLine(HANDLE, WORD, PDWORD);
BOOL WriteToOutBuffer(LPWSTR, DWORD);

int WINAPI WinMain(HINSTANCE hInstance,
            HINSTANCE hPrevInstance,
            // ** Don't use LPWSTR lpCmdLine here, looks like some of my old
            // projects have LPWSTR with ANSI WinMain
            LPSTR lpCmdLine,
            int nCmdShow)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROGICON));
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCE(IDR_MENU1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = (HICON) LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_PROGICON));

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Unicode blogger code generator"),
            NULL);

        return 1;
    }

    hInst = hInstance; // Store instance handle in our global variable

    // 600, 515: custom window size (width, length)
    HWND hWnd = CreateWindow(
      szWindowClass,
      szTitle,
      WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, CW_USEDEFAULT,
      600, 515,
      NULL,
      NULL,
      hInstance,
      NULL
    );

    if (!hWnd)
    {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Win32 Guided Tour"),
            NULL);

        return 1;
    }

    // The parameters to ShowWindow explained:
    // hWnd: the value returned from CreateWindow
    // nCmdShow: the fourth parameter from WinMain
    InitCommonControls();
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // Main message loop:
    MSG msg;
    BOOL bRet;

    HACCEL haccel;      // handle to accelerator table 
    // Load the accelerator table. 
    haccel = LoadAccelerators(hInst, MAKEINTRESOURCE(CtrlAccl));
    if (haccel == NULL)
    {
      TCHAR str[100];
      wsprintf(str, TEXT("Accelerator Loading Error %d"), GetLastError());
      MessageBox(hWnd, str, TEXT("SA-OS Win32 Tutorial"), MB_OK | MB_ICONEXCLAMATION);
      return 1;
    }

    while ( (bRet = GetMessage(&msg, (HWND) NULL, 0, 0)) != 0) {
      if (bRet == -1) {
        // handle the error and possibly exit
        MessageBox(hWnd, L"Getmessage Error",L"Error", MB_OK | MB_ICONEXCLAMATION);
        return 0;
      }
      else {
        // Check for accelerator keystrokes
        if (!TranslateAccelerator( 
            hWnd,          // handle to receiving window 
            haccel,        // handle to active accelerator table 
            &msg))         // message data 
        {
          TranslateMessage(&msg); 
          DispatchMessage(&msg); 
        } 
      } 
    }

    return (int) msg.wParam;
}

LONG APIENTRY WndProc(HWND hwnd,          // window handle 
                UINT message,             // type of message 
                WPARAM wParam,            // additional information 
                LPARAM lParam)            // additional information
{ 
  static HWND hwndEdit_input; 
  static HWND hwndEdit_output;
  HFONT hFont;
  static HWND hwndButton;
  static HWND hwndFocus;
  int len;
 
  switch (message) {
    case WM_CREATE: 
      hwndButton = CreateWindow( 
          L"BUTTON",   // Predefined class; Unicode assumed. 
          L"Code",       // Button text. 
          WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_CENTER,  // Styles. 
          2,         // x position. 
          5,         // y position. 
          45,        // Button width.
          30,        // Button height.
          hwnd,       // Parent window.
          NULL,       // No menu.
          hInst,    // program instance
          NULL);      // Pointer not needed.

      hwndEdit_input = CreateWindow(L"EDIT",      // predefined class 
          NULL,        // no window title 
          WS_BORDER | WS_CHILD | WS_VISIBLE | WS_VSCROLL | 
          ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL, 
          50, 5, 530, 230,  // set size in WM_SIZE message 
          hwnd,        // parent window 
          NULL,   // edit control ID 
          hInst, 
          NULL);       // pointer not needed 

      hwndPB = CreateWindowEx(0, PROGRESS_CLASS,
          (LPTSTR) NULL, WS_CHILD | WS_VISIBLE,
          50, 245, 510, 20, 
          hwnd,
          (HMENU) 0,
          hInst,
          NULL); 

      hwndEdit_output = CreateWindow(L"EDIT",      // predefined class 
                                    NULL,        // no window title 
                                    WS_BORDER | WS_CHILD | WS_VISIBLE | WS_VSCROLL | 
                                    ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL, 
                                    50, 280, 530, 172,  // set size in WM_SIZE message 
                                    hwnd,        // parent window 
                                    NULL,   // edit control ID 
                                    hInst, 
                                    NULL);       // pointer not needed 

      // Set font for button
      hFont = CreateFont(13,0,0,0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Verdana"));
      SendMessage(hwndButton, WM_SETFONT, (WPARAM) hFont, (LPARAM)FALSE);

      // set font for input textBox
      hFont = CreateFont(15,0,0,0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Courier New"));
      SendMessage(hwndEdit_input, WM_SETFONT, (WPARAM) hFont, (LPARAM)FALSE);

      // Add text to the edit control window. 
      wcscpy_s(inputText, insize, L"<Input Text here>");
            SendMessage(hwndEdit_input, WM_SETTEXT, 0, (LPARAM) inputText);
      // Select all text
      //Edit_SetSel(hwndEdit_input, 0, _tcslen(inputText));
      SendMessage(hwndEdit_input, EM_SETSEL, 0, -1);

      // set font for output textBox
      hFont = CreateFont(14,0,0,0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Verdana"));
      SendMessage(hwndEdit_output, WM_SETFONT, (WPARAM) hFont, (LPARAM)FALSE);
      // Set text in output textBox
      wcscpy_s(outText, outsize, L"< Press the Code button to get output here >"); 
      SendMessage(hwndEdit_output, WM_SETTEXT, 0, (LPARAM) outText);

      //outText[0] = NULL;
      break;
 
    case WM_COMMAND:
      switch (LOWORD(wParam)) {
        // Process Button is clicked
        case BN_CLICKED:
          // check if click is in Button control
          if (lParam == (LPARAM) hwndButton)  {
            // process input texts and get output
            SetFocus(hwndEdit_input);
            len = SendMessage(hwndEdit_input, WM_GETTEXTLENGTH, (WPARAM) NULL, (LPARAM)NULL);
            if (len > insize) {
              MessageBox(hwnd, L"Input Buffer too small", L"Input Buffer Overflow", MB_OK | MB_ICONEXCLAMATION);
              return 0;
            }

            SendMessage(hwndPB, PBM_SETRANGE, 0, MAKELPARAM(0, len));
            SendMessage(hwndPB, PBM_SETSTEP, (WPARAM) 1, 0);
            SendMessage(hwndPB, PBM_SETPOS, (WPARAM) 0, 0); 
            len = SendMessage(hwndEdit_input, WM_GETTEXT, (WPARAM) len+1, (LPARAM) inputText);
            // inputText[len] = NULL;

            //wsprintf(str, L"string: %s\n length: %d", inputText, len);
            //MessageBox(hwndEdit_input, str, L"Notice", MB_OK);
            if (loadTagFromFile() == FALSE) {
              wcscpy_s(outText, outsize, L"< Error!! Could not load tag info from file. >"); 
            }
            else
              processInput();

            if (outText[0] != NULL) {
              SendMessage(hwndEdit_output, WM_SETTEXT, 0, (LPARAM) outText);
              SetFocus(hwndEdit_output);
              SendMessage(hwndEdit_output, EM_SETSEL, 0, -1);
            }
            else {
              wsprintf(str, L"No output for specified input.", inputText, len);
              MessageBox(hwndEdit_input, str, L"Notice", MB_OK);
            }
          }
          break;

        case ID_SEL:
          hwndFocus = GetFocus();
          if (hwndFocus == hwndEdit_input) {
              SetFocus(hwndEdit_input);
              SendMessage(hwndEdit_input, EM_SETSEL, 0, -1);
          }
          else if (hwndFocus == hwndEdit_output) {
              SetFocus(hwndEdit_output);
              SendMessage(hwndEdit_output, EM_SETSEL, 0, -1);
          }
          break;

        case ID_EXIT:
          PostMessage(hwnd, WM_CLOSE, 0, 0);
          break;

        case IDM_EDUNDO: 
          // Send WM_UNDO only if there is something to be undone. 
          if (SendMessage(hwndEdit_input, EM_CANUNDO, 0, 0)) 
              SendMessage(hwndEdit_input, WM_UNDO, 0, 0); 
          else
              MessageBox(hwndEdit_input, 
                  L"Nothing to undo.", 
                  L"Undo notification", 
                  MB_OK); 

          break; 

        case IDM_EDCUT: 
          SendMessage(hwndEdit_input, WM_CUT, 0, 0); 
          break; 

        case IDM_WRAP: 
          /*SendMessage(hwndEdit_input, 
                      EM_SETWORDBREAKPROC, 
                      (WPARAM) 0, 
                      (LPARAM) (EDITWORDBREAKPROC) WordBreakProc); 

          SendMessage(hwndEdit_input, 
                      EM_FMTLINES, 
                      (WPARAM) TRUE, 
                      (LPARAM) 0); 

          SendMessage(hwndEdit_input, 
                      EM_SETSEL, 
                      0, -1);             // select all text 

          SendMessage(hwndEdit_input, WM_CUT, 0, 0); 

          SendMessage(hwndEdit_input, WM_PASTE, 0, 0); */

          break; 
        default:
          return DefWindowProc(hwnd, message, wParam, lParam); 
      }

      break; 

    case WM_SETFOCUS: 
      SetFocus(hwndEdit_input); 
      break;

    case WM_SIZE: 
      // Make the edit control the size of the window's client area. 

      // MoveWindow(hwndEdit_input, 
      //             0, 0,                  // starting x- and y-coordinates 
      //             LOWORD(lParam),        // width of client area 
      //             HIWORD(lParam),        // height of client area 
      //             TRUE);                 // repaint window 
      break;

    case WM_DESTROY: 
      PostQuitMessage(0); 
      break;

    default:
      return DefWindowProc(hwnd, message, wParam, lParam);
        
  }
}

//
// PURPOSE : Parser and Document Converter
//
// PARAMS  :
//  inputText: the input doc
//
// COMMENTS:
//  Custom WndProc Callback method Hooked via lpParam. ref, s_WndProc
//  RETURNs TRUE when no case matches indicating Error/Exception!
//

void processInput() {
  // assume normal text for no tag
  // maximum length of tag string is 15
  // does not alter newline or space

  int i, len, tagIndex = 0;
  DWORD bIndex=0;
  /*static PWSTR currentTag= new WCHAR[20];
  static PWSTR currentStartTag = new WCHAR[20];*/
  const WORD tagLimit = 2000;
  WCHAR currentTag[tagLimit+1];
//  WCHAR currentStartTag[20];

  const DWORD buffsize=30000;
  static WCHAR buff[buffsize];
  WCHAR ch;
  BOOL LOpfound = FALSE;
  BOOL tagStarted = FALSE;
  BOOL endTagMarkFound = FALSE;
  BOOL spanActive = FALSE;
  WORD divActive = 0;
  codingMode = 0;
  outWritten = 0;
  str[0] = NULL;

  len = wcslen(inputText);
  //wsprintf(str, L"string: %ls\n length: %d", inputText, len);
  //MessageBox(NULL, str, L"Notice", MB_OK);
  outText[0] = NULL;

  for (i=0; i<len; i++) {
    // Take input
    ch = inputText[i];
    //wsprintf(str, L"string: %ls\n length: %d", inputText, len);
    //MessageBox(NULL, str, L"Notice", MB_OK);


    // Take every char and judge
    if (codingMode == 5) {
      if (ch == L'>') {
        if (inputText[i-1] == L'/' && inputText[i-2] == L'<') {
          codingMode = 0;
          bIndex -= 2;
          buff[bIndex] = L'\0';
          if (WriteToOutBuffer(buff, bIndex) == FALSE)
            return ;
          bIndex = 0;

        }
        else { 
          if (bIndex + 1 > buffsize) {
            WriteToOutBuffer(L"Text Buffer Overflow!!", 22);
            return ;
          }
          else
            buff[bIndex++] = ch;
        }

      }
      else { 
        if (bIndex + 1 > buffsize) {
          WriteToOutBuffer(L"Text Buffer Overflow!!", 22);
          return ;
        }
        else
          buff[bIndex++] = ch;
      }
    }
    else if (ch == '<') {
      LOpfound = TRUE;
      tagIndex = 0;
      if (tagStarted == TRUE) {
        tagStarted = FALSE;
      }
      buff[bIndex] = NULL;
      // write texts from buffer to output
      if (bIndex != 0) {
        if (WriteToOutBuffer(buff, bIndex) == FALSE)
          return ;
        bIndex = 0;
      }

      if (whichTag != -1 && EndCode[whichTag][0] != NULL) {
        if (WriteToOutBuffer(EndCode[whichTag], wcslen(EndCode[whichTag])) == FALSE)
          return ;
        whichTag = -1;
      }
      if (endTagS(&spanActive) == FALSE)
        return ;
    }
    else if (ch == '>') {
      if (LOpfound == TRUE) {
        if (endTagMarkFound == TRUE) {
          endTagMarkFound = FALSE;
          tagStarted = FALSE;
          buff[bIndex] = NULL;
          // write texts from buffer to output
          if (bIndex != 0) {
            if (WriteToOutBuffer(buff, bIndex) == FALSE)
              return ;
            bIndex = 0;
          }

          if (endTagS(&spanActive) == FALSE)
            return ;
          if (codingMode == 1)
            codingMode = 0;
        }
        else {
          // beginning tag
          currentTag[tagIndex] = NULL;
          // filterTag(currentTag);

          // save currnet Start Tag
          //wcscpy_s(currentTag, 250, currentTag);
          if (writeCodeForTag(currentTag, &spanActive, &divActive, &tagStarted) == FALSE) {
            writeError(10);
            return ;
          }

          //wsprintf(str, L"string: %ls", currentStarttag);
          //MessageBox(NULL, str, L"Notice", MB_OK);
        }
        LOpfound = FALSE;
      }
      else {
        if (tagStarted == TRUE) {
          if (bIndex+4>buffsize) {
            WriteToOutBuffer(L"Text Buffer Overflow!!", 22);
            return ;
          }
          else {
            buff[bIndex] = NULL;
            wcscat_s(buff, buffsize, L"&gt;");
            bIndex += 4;
          }
        }
        // else ignore >
      }
    }
    else if (ch == '/') {
      if (inputText[i-1] == L'<') {
        endTagMarkFound = TRUE;
      }
      else if (LOpfound == TRUE) {
        if (tagIndex > tagLimit) {
          writeError(2);
          return ;
        }
        currentTag[tagIndex++] = ch;
      }
      else if (tagStarted == TRUE)
        if (bIndex + 1 > buffsize) {
          WriteToOutBuffer(L"Text Buffer Overflow!!", 22);
          return ;
        }
        else
          buff[bIndex++] = ch;
    }
    else {
      if (LOpfound == TRUE) {
        if (tagIndex > tagLimit) {
          writeError(2);
          return ;
        }
        currentTag[tagIndex++] = ch;
      }
      else if (tagStarted == TRUE) {
        // handle space
        if (codingMode == 1) {
          switch (ch) {
            case L' ':
              if (bIndex+6>buffsize) {
                WriteToOutBuffer(L"Text Buffer Overflow!!", 22);
                return ;
              }
              else {
                buff[bIndex] = NULL;
                wcscat_s(buff, buffsize, L"&nbsp;");
                bIndex += 6;
              }
              break;
            case L'\t':
              if (bIndex+24>buffsize) {
                WriteToOutBuffer(L"Text Buffer Overflow!!", 22);
                return ;
              }
              else {
                buff[bIndex] = NULL;
                wcscat_s(buff, buffsize, L"&nbsp;&nbsp;&nbsp;&nbsp;");
                bIndex += 24;
              }
              break;
            default:
              if (bIndex + 1 > buffsize) {
                WriteToOutBuffer(L"Text Buffer Overflow!!", 22);
                return ;
              }
              else
                buff[bIndex++] = ch;
          }
        }
        else {
          if (bIndex + 1 > buffsize) {
            WriteToOutBuffer(L"Text Buffer Overflow!!", 22);
            return ;
          }
          else
            buff[bIndex++] = ch;
        }
      }
      else {
        // assume normal text
        // start normal tag
        if (ch != L'\n') {
          tagStarted = TRUE;

          bIndex = 0;

          if (bIndex + 1 > buffsize) {
            WriteToOutBuffer(L"Text Buffer Overflow!!", 22);
            return ;
          }
          else
            buff[bIndex++] = ch;

          if (writeCodeForTag(L"normal", &spanActive, &divActive, &tagStarted) == FALSE) {
            writeError(10);
            return ;
          }
        }

        //writeError(1);
        //return ;
      }

    }
    SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
  }
  buff[bIndex] = 0;

  if (bIndex != 0) {
    if (WriteToOutBuffer(buff, bIndex) == FALSE)
      return ;
    bIndex = 0;
  }
  endTag(&spanActive, &divActive);
}

BOOL endTagS(PBOOL s) {
  if (*s == TRUE) {
    if (WriteToOutBuffer(L"</span>", 8) == FALSE)
      return FALSE;
    *s = 0;
  }
  return TRUE;
}

BOOL endTag(PBOOL s, PWORD d) {
  if (*s == TRUE) {
    if (WriteToOutBuffer(L"</span>", 8) == FALSE)
      return FALSE;
    *s = 0;
  }
  if (*d != 0) {
    if (WriteToOutBuffer(L"</div>", 6) == FALSE)
      return FALSE;
    *d = 0;
  }
  return TRUE;
}

// Tag to HTML Code Mapping
BOOL writeCodeForTag(LPWSTR tag, PBOOL s, PWORD d, PBOOL tagStart) {
  int tagLen, i, j, propNo=0;
  BOOL acceptspace = FALSE;

  WCHAR p1[1000], p2[200];

  i = 0;
  while (tag[i] != ' ' && tag[i] != NULL)
    i++;
  // Careful Invalid syntax will cause access violation error
  if (tag[i] != NULL) {
    propNo++;

    tagLen = i;
    while (tag[i] == ' ')  // ignores extra spaces
      i++;
    while (tag[i] != '=')  // check for equal sign
      i++;
    i++;            // ignore equal sign
    if (tag[i] == L'"') {
      acceptspace = TRUE;
      i++;
    }


    // Save First Property
    j = 0;
    if (acceptspace == TRUE) {
      while (tag[i] != L'"' && tag[i] != NULL) {
        if (j == 1000) {
          writeError(7);
          return FALSE;
        }
        else
          p1[j++] = tag[i++];
      }
      acceptspace = FALSE;
      if (tag[i] == L'"')
        i++;
    }
    else {
      while (tag[i] != ' ' && tag[i] != NULL) {
        if (j == 1000) {
          writeError(7);
          return FALSE;
        }
        else
          p1[j++] = tag[i++];
      }
    }

    p1[j] = NULL;

    if (tag[i] != NULL) {
      propNo++;
      while (tag[i] != '=')  // check for equal sign
        i++;
      i++;            // ignore equal sign

      // Save Second Property
      j = 0;
      while (tag[i] != NULL)
        if (j == 200) {
          writeError(8);
          return FALSE;
        }
        else
          p2[j++] = tag[i++];
      
      p2[j] = NULL;
    }
  }
  /*if (propNo > 0) {
    wsprintf(str, L"p1= %ls", p1);
    MessageBox(NULL, str, L"Info", MB_OK);
  }
  if (propNo > 1) {
    wsprintf(str, L"p2= %ls", p2);
    MessageBox(NULL, str, L"Info", MB_OK);
  }*/


  // Exclude properties from tag if there are one or more properties
  if (propNo > 0)
    tag[tagLen] = NULL;
  /*wsprintf(str, L"Parsed tag: %ls", tag);
  MessageBox(NULL, str, L"Info", MB_OK);*/


  // d =1 for left
  // d =2 for justify
  // d =3 for right
  // d =4 for center
  //MessageBoxA(NULL, "Reached here", "Debug", MB_OK);
  for (i=0; i<tagTot; i++) {
    //wsprintf(str, L"comparing current tag: (%ls) length: %d with tag: (%ls)", tag, wcslen(tag), tagName[i]);
    //MessageBox(NULL, str, L"Debug", MB_OK);
    int result = wcscmp(tagName[i],tag);
    /*unsigned j;
    for (j = 0; j < wcslen(tagName[i]); j++) {
      //wsprintf(str, L"tag char: %lc cur char: %lc", tag[j], tagName[i][j]);
      //MessageBox(NULL, str, L"Debug", MB_OK);
    }*/

    if (result == 0) {
      whichTag = i;
      //MessageBox(NULL, L"Finally matched", L"Match", MB_OK);
      if (*d != alignment[i]) {
        if (endTag(s, d) == FALSE)
          return FALSE;
        *d = alignment[i];

        switch (*d) {
          case 0:
            break;
          case 1:
            wcscpy_s(str, strsize, L"<div style=\"text-align: left;\">");
            if (WriteToOutBuffer(str, _tcslen(str)) == FALSE)
              return FALSE;
            break;
          case 2:
            wcscpy_s(str, strsize, L"<div style=\"text-align: justify;\">");
            if (WriteToOutBuffer(str, _tcslen(str)) == FALSE)
              return FALSE;
            break;
          case 3:
            wcscpy_s(str, strsize, L"<div style=\"text-align: right;\">");
            if (WriteToOutBuffer(str, _tcslen(str)) == FALSE)
              return FALSE;
            break;
          case 4:
            wcscpy_s(str, strsize, L"<div style=\"text-align: center;\">");
            if (WriteToOutBuffer(str, _tcslen(str)) == FALSE)
              return FALSE;
            break;
          case 5:
            wcscpy_s(str, strsize, L"<div class=\"separator\" style=\"clear: both; text-align: center;\">");
            if (WriteToOutBuffer(str, _tcslen(str)) == FALSE)
              return FALSE;
            break;
          default:
            wcscat_s(outText, outsize, L"<-- Unknown div alignment property -->");
            return FALSE;
            break;
        }
      }

      if (spanInCode[i] == TRUE)
        *s = TRUE;

      if (isDynamicCode[i] == 1 || isDynamicCode[i] == 4) {
        if (propNo == 0) {
          wsprintf(str, L"<-- You forgot to provide property for tag %ls -->", tag);
          if (WriteToOutBuffer(str, _tcslen(str)) == FALSE)
            return FALSE;
        }
        else {
          int startWritePos = 0;
          // parse and replace $p with values
          j = 0;
          while (TRUE) {    // continuous check until expected pattern not found
            while (BeginCode[i][j] != L'$' && BeginCode[i][j] != NULL)
              j++;
            if (BeginCode[i][j] == NULL) {
              if (j-startWritePos + outWritten > outsize) {
                wsprintf(str, L"Request for total write: %d.", j -startWritePos + outWritten);
                MessageBox(NULL, str, L"Overflow!", MB_OK | MB_ICONEXCLAMATION);
                return FALSE;
              }
              else {
                wcsncat_s(outText, outsize, &BeginCode[i][startWritePos], j-startWritePos);
                outWritten += j-startWritePos;
              }

              break;
            }
            j++;    // skip to next char
            if (BeginCode[i][j] == L'p') {
              j++;
              if (BeginCode[i][j] == L'1' || BeginCode[i][j] == L'2') {
                // pattern found, write code
                if (j-startWritePos + outWritten - 2> outsize) {
                  wsprintf(str, L"Request for total append: %d.", j -startWritePos + outWritten - 2);
                  MessageBox(NULL, str, L"Overflow!", MB_OK | MB_ICONEXCLAMATION);
                  return FALSE;
                }
                else {
                  wcsncat_s(outText, outsize, &BeginCode[i][startWritePos], j-startWritePos-2);
                  outWritten += j-startWritePos - 2;
                }
                startWritePos = j+1;

                if (BeginCode[i][j] == L'1') {
                  if (WriteToOutBuffer(p1, _tcslen(p1)) == FALSE)
                    return FALSE;
                }
                else {
                  if (WriteToOutBuffer(p2, _tcslen(p2)) == FALSE)
                    return FALSE;
                }

                //wsprintf(str, L"str: %ls", outText);  
                //MessageBox(NULL, str, L"Debug", MB_OK);
              }
              else  {
                //wsprintf(str, L"<-- Invalid pattern for tag %ls -->", tag);
                //wcscat_s(outText, outsize, str);
              }
            }

          }
          if (isDynamicCode[i] == 4) {
            *tagStart = TRUE;
          }
          else {
            // write ending code
            if (EndCode[whichTag][0] != NULL) {
              if (WriteToOutBuffer(EndCode[i], wcslen(EndCode[i])) == FALSE)
                return FALSE;
              whichTag = -1;
            }

            endTagS(s);
          }
        }
      }
      else if (isDynamicCode[i] == 2) {
        // mark beginning tag
        *tagStart = TRUE;
        if (WriteToOutBuffer(BeginCode[i], BCLen[i]) == FALSE)
          return FALSE;
        // codingmode 1 means converts spaces & tabs to &npsp;
        codingMode = 1;
      }
      else if (isDynamicCode[i] == 3) {
        // mark beginning tag
        *tagStart = TRUE;
        if (BeginCode[i][0] != NULL)
          if (WriteToOutBuffer(BeginCode[i], BCLen[i]) == FALSE)
            return FALSE;

        // coding mode 5 means no change
        codingMode = 5;
      }
      else {
        // mark beginning tag
        *tagStart = TRUE;
        if (WriteToOutBuffer(BeginCode[i], BCLen[i]) == FALSE)
          return FALSE;
      }
      break;
    }
  }
  if (i == tagTot) {
    whichTag = -1;
    wsprintf(str, L"<-- The tag: %ls is unknown. Please check spelling. -->", tag);
    if (WriteToOutBuffer(str, _tcslen(str)) == FALSE)
      return FALSE;
    return FALSE;
  }

  return TRUE;
}

void writeError(int errorcode) {
  // Error 1: no beginning tag started
  switch (errorcode) {
    case 1:
      wcscat_s(outText, outsize, L"\n -- No Beginning Tag Found!! -- \n");
      break;
    case 2:
      wcscat_s(outText, outsize, L"\n -- Tag Name Limit Exceeds!! -- \n");
      break;
    case 3:
      DisplayError(TEXT("CreateFile"));
      wcscat_s(outText, outsize, L"\n -- CreateFile: Terminal failure: unable to open file for read. -- \n");
      break;
    case 4:
      DisplayError(TEXT("ReadFile"));
      wcscat_s(outText, outsize, L"\n -- ReadFile: Terminal failure: Unable to read from file -- \n");
      break;
    case 5:
      wcscat_s(outText, outsize, L"\n -- No data read from file -- \n");
      break;
    case 6:
      wcscat_s(outText, outsize, L"\n ** Unexpected value for dwBytesRead ** \n");
      break;
    case 7:
      wcscat_s(outText, outsize, L"\n -- Loading tags from file failed!! -- \n");
      break;
    case 8:
      wcscat_s(outText, outsize, L"\n -- tag Property 1 Limit Exceed!! -- \n");
      break;
    case 9:
      wcscat_s(outText, outsize, L"\n -- tag Property 2 Limit Exceed!! -- \n");
      break;
    case 10:    // error in other functions
      wcscat_s(outText, outsize, L"\n -- Code write failure! -- \n");
      break;
    default:
      wcscat_s(outText, outsize, L"\n -- Unknown error code!! -- \n");
  }
  SendMessage(hwndPB, PBM_SETPOS, (WPARAM) wcslen(inputText), 0); 
}

void DisplayError(LPTSTR lpszFunction)
// Routine Description:
// Retrieve and output the system error message for the last-error code
{ 
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
        0, 
        NULL );

    lpDisplayBuf = 
        (LPVOID)LocalAlloc( LMEM_ZEROINIT, 
                            ( lstrlen((LPCTSTR)lpMsgBuf)
                              + lstrlen((LPCTSTR)lpszFunction)
                              + 40) // account for format string
                            * sizeof(TCHAR) );
    
    if (FAILED( wsprintfA((LPSTR)lpDisplayBuf, 
                     "%s failed with error code %d as follows:\n%s ERROR: %s",  
                     lpszFunction, 
                     dw, 
                     lpMsgBuf, (LPCSTR)lpDisplayBuf)))
    {
        MessageBoxA(NULL, "FATAL ERROR: Unable to output error code.\n", "Notice", MB_OK);
    }
    
    //_tprintf(TEXT("ERROR: %s\n"), (LPCTSTR)lpDisplayBuf);

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
}

#define TEMPSIZE  2000
WCHAR temp[TEMPSIZE];
WCHAR line[300]=L"";

//LPWSTR temp = new WCHAR[BUFFERSIZE];
//LPWSTR line = new WCHAR[300];

BOOL loadTagFromFile() {
  int pos = 0, lineno =0, i, lPos;
  DWORD br;
  tagTot = 0;
  temp[0] = NULL;

  // read file and load
  HANDLE hFile = CreateFile(L"Tags.txt",   // file to open
          GENERIC_READ,          // open for reading
          FILE_SHARE_READ,       // share for reading
          NULL,                  // default security
          OPEN_EXISTING,         // existing file only
          FILE_ATTRIBUTE_NORMAL, // normal file
          NULL);

  if (hFile == INVALID_HANDLE_VALUE) { 
    writeError(3);
        return FALSE; 
    }

  while ((hFile != NULL) && (pos = getLine(hFile, pos, &br)) != 0) {
    // we get one line from the file in variable line
    if (line[0] == NULL)
      continue;
    // Parse Tagname
    i = lPos = 0;
    while (line[lPos] != L' ') {
      tagName[lineno][i++] = line[lPos++];
      //i++;
      //lPos++;
    }

    tagName[lineno][i] = NULL;
    /*wsprintf(str, L"tagName: %ls", tagName[lineno]);
    MessageBox(NULL, str, L"Line", MB_OK);*/

    // Parse div alignment property
    while (line[lPos] == L' ')    //ignore spaces
      lPos++;
    alignment[lineno] = line[lPos++] - '0';

    // Parse span property
    while (line[lPos] == L' ')    //ignore spaces
      lPos++;
    spanInCode[lineno] = BOOL(line[lPos++] - '0');


    // Parse dynamic property
    while (line[lPos] == L' ')    //ignore spaces
      lPos++;
    isDynamicCode[lineno] = line[lPos++] - '0';

    // Parse beginning Code
    while (line[lPos] != L'@')    //ignore until @ sign found
      lPos++;lPos++;

    i = 0;
    while (line[lPos] != L'@')
      BeginCode[lineno][i++] = line[lPos++];

    BeginCode[lineno][i] = NULL;
    BCLen[lineno] = i;

    // Parse Ending Code
    lPos++;
    while (line[lPos] != L'@')    //ignore until @ sign found
      lPos++;lPos++;

    i = 0;
    while (line[lPos] != L'@')
      EndCode[lineno][i++] = line[lPos++];

    EndCode[lineno][i] = NULL;
    //wsprintf(str, L"current line: %ls", line);
    //MessageBox(NULL, str, L"Line", MB_OK);
    //wsprintf(str, L"current tagname: %ls, current alignment: %hd, begin code: %ls, ending code: %ls", tagName[lineno], alignment[lineno], BeginCode[lineno], EndCode[lineno]);
    //MessageBox(NULL, str, L"tag", MB_OK);
    lineno++;
  }

  tagTot = lineno;
  if (tagTot > maxTag)
    return FALSE;

  if (hFile)
    CloseHandle(hFile);
  return TRUE;
}

int getLine(HANDLE hFile, WORD startPos, PDWORD br) {
  DWORD  dwBytesRead = 0, i, j;
  if (temp[0] == NULL) {
    //MessageBox(NULL, L"Reached here", L"Notice", MB_OK);
    if( FALSE == ReadFile(hFile, temp, (TEMPSIZE-1) * 2, &dwBytesRead, NULL) ) {
      writeError(4);
      CloseHandle(hFile);
      return 0;
    }

    *br = dwBytesRead/ 2;
    //wsprintf(str, L"Read total %d wchars", *br);
    //MessageBox(NULL, str, L"Info", MB_OK);

    if (dwBytesRead > 0 || dwBytesRead <= TEMPSIZE)
    {
      temp[*br] = NULL;

      for (i=1; temp[i] != NULL && temp[i] != L'\n'; i++) {
        line[i-1] = temp[i];
      }
      if (temp[i] == L'\n') {
        line[i-1] = NULL;
        // wsprintf(str, L"string: %ls.", temp);
        // MessageBox(NULL, str, L"Info", MB_OK);
        // wsprintf(str, L"line: %ls.", line);
        // MessageBox(NULL, str, L"Info", MB_OK);
      }
      else {
        // read again and append to line

      }
      return i;
    }
    else if (dwBytesRead == 0)
    {
      writeError(5);
      CloseHandle(hFile);
      return 0; 
    }
    else
    {
      writeError(6);
      CloseHandle(hFile);

      return 0; 
    }
  }
  else {
    for (j = 0, i = startPos+1; temp[i] != NULL && temp[i] != L'\n'; i++, j++) {
      line[j] = temp[i];
    }
    if (temp[i] == L'\n')
      line[j] = NULL;
    else {
      //MessageBox(NULL, L"return on eof", L"Notice", MB_OK);
      // read again and append to line
      return 0;
    }
    //MessageBox(NULL, L"got newline in 2", L"Notice", MB_OK);

    return i;
  }
}

BOOL WriteToOutBuffer(LPWSTR instr, DWORD len) {
  if (len + outWritten > outsize) {
    wsprintf(str, L"Request for total write: %d.", len + outWritten);
    MessageBox(NULL, str, L"OutBuffer Overflow", MB_OK | MB_ICONEXCLAMATION);

    return FALSE;
  }
  else {
    wcscat_s(outText, outsize, instr);
    outWritten += len;
  }
  return TRUE;
}
