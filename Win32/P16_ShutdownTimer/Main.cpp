/*
 * Date   : 03-16-2013
 * Notes  :
 *  Latest updates 02-2023,
 *  - generic tchar string functions
 *  - converted unsafe string functions
 * 
 * Q&A
 *    Why is there no header file for init common controls?
 *    A: microsoft sample for windows common control did the code in only one file.
 *      line 1
 *      line 2
 *
 * Demonstrates,
 *  - Painting on dialog box (notice the about box)
 *   - handles nm click message on the dialog box
 *  - Dialog Callback Procedure similar to WndProc Callback
 */


//#define _WIN32_IE 0x0800
// same header file order as in windows common controls demo microsoft sample
#include <string.h>
#include <stdio.h>
#include <windows.h>
#include <windowsx.h>// for HANDLE_MSG
#include "resource.h"
#include <commctrl.h>
#include <tchar.h>


#define HorizSpace 50
#define VertSpace 20

// ref, Tutorials\T02_VS_and_Menu\ReadMe.md
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#pragma endregion

// Following windows common controls demo sample of microsoft
HINSTANCE g_hInst;  // The handle to the instance of the current module

static HWND g_hLink;

// enum dialog status for clarity
enum DialogStatuses { Inactive, TimeDateSelection, ShutdownSituation};

// enum current focus for clarity
enum FocusControl { None, DateControl, TimeControl};

SYSTEMTIME lpSysTime;
SYSTEMTIME lpSysDate;
UINT_PTR IDT_TIMER1=10;
UINT_PTR IDT_TIMER2=20;
DialogStatuses dialogStatus = TimeDateSelection;
WORD count = 30;
BOOL secondtimerstarted = FALSE;

static HWND hwndTimeP;
static HWND hwndDateP;
static HWND hwndButton;
static HWND g_hwnd;


static TCHAR warnMsg[100] = L"";

// static COLORREF myColor1 = 0x00ffffff; //0x00919191;
// static COLORREF myColor2 = 0x00ffffff; //0x00919191;
static COLORREF myColor1 = 0x00FF8040;
static COLORREF myColor2 = 0x00FF8040;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HWND WINAPI CreateDatePick(HWND);
BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
HWND CreateSysLink(HWND, HINSTANCE, RECT);
void OnClose(HWND hWnd);

HWND WINAPI CreateTimePick(HWND);
HWND WINAPI CreateDatePick(HWND);
int verifyInputDateTime();
FocusControl reactOnClick(HWND hwnd);

int verifyInputTime(SYSTEMTIME currentLocalTime);
void runProgram(HWND hwnd);
BOOL isTimeUp();
BOOL MySystemShutdown();

static TCHAR szWindowClass[] = TEXT("STDTimer");
static TCHAR szTitle[] = TEXT("Shutdown Timer");

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow) {
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  WNDCLASSEX wcex;

  wcex.cbSize         = sizeof(WNDCLASSEX);
  wcex.style          = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc    = WndProc;
  wcex.cbClsExtra     = 0;
  wcex.cbWndExtra     = 0;
  wcex.hInstance      = hInstance;
  wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAIN_APP_ICON));
  wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
  wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
  wcex.lpszMenuName   = MAKEINTRESOURCE(IDR_MENU);
  wcex.lpszClassName  = szWindowClass;
  wcex.hIconSm        = (HICON) LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_MAIN_APP_ICON));

  if (!RegisterClassEx(&wcex))
  {
    MessageBox(NULL,
      TEXT("Call to RegisterClassEx failed!"),
      TEXT("Test prog"),
      NULL);

    return 1;
  }

  HWND hWnd = CreateWindow(
    szWindowClass,
    szTitle,
    WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
    CW_USEDEFAULT, CW_USEDEFAULT,
    360, 280,
    NULL,
    NULL,
    hInstance,
    NULL
  );

  if (!hWnd)
  {
    MessageBox(NULL,
      TEXT("Call to CreateWindow failed!"),
      TEXT("Test prog"),
      NULL);

    return 1;
  }

  g_hInst = hInstance;
  g_hwnd = hWnd;

  InitCommonControls();
  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);

  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0))
  {
  if (!IsDialogMessage(hWnd, &msg)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  }

  return (int) msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd,                // window handle 
                        UINT message,             // type of message 
                        WPARAM wParam,            // additional information 
                        LPARAM lParam)            // additional information 
{ 
  PAINTSTRUCT ps;
  static HDC hdc;
  static HWND hwndDlg = NULL;
  static LPCTSTR dayToday[7] = {TEXT("Sunday"), TEXT("Monday"), TEXT("Tuesday"), TEXT("Wednesday"),
            TEXT("Thursday"), TEXT("Friday"), TEXT("Saturday")};

  FocusControl currentFocus = None;    // had to declare here because of the error case label skipped initialization of currentfocus

  switch (message) { 
  case WM_CREATE:
    // Add date time picker
    hwndTimeP = CreateTimePick(hwnd);
    hwndDateP = CreateDatePick(hwnd);

    // Add button to the window
    hwndButton = CreateWindow( 
      TEXT("BUTTON"),   // Predefined class for Button
      TEXT("Start"),       // Button text. 
      WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_CENTER,  // Styles. 
      HorizSpace + 60,         // x position. 
      VertSpace + 130,         // y position. 
      60,        // Button width.
      30,        // Button height.
      hwnd,       // Parent window.
      NULL,       // No menu.
      g_hInst, // (HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE), 
      NULL);      // Pointer not needed.

    return 0; 

  case WM_PAINT:
    hdc = BeginPaint(hwnd, &ps);
    HFONT hFont;
    RECT rect;

    hFont = CreateFont(14,0,0,0,FW_DONTCARE,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS, 
      CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Verdana"));
    // Select font
    SelectObject(hdc, hFont);

    if (dialogStatus == TimeDateSelection) {
      //SetBkColor(hdc, 0x00606060);
      SetTextColor(hdc, myColor1);
      SetRect(&rect, HorizSpace,VertSpace,100,50);
      DrawText(hdc, TEXT("Choose Shutdown Time:"), -1,&rect, DT_NOCLIP);

      SetTextColor(hdc, myColor2);
      SetRect(&rect, HorizSpace,VertSpace+55,100,50);
      DrawText(hdc, TEXT("Choose Date:"), -1,&rect, DT_NOCLIP);

      SetTextColor(hdc, 0x000000ff);
      SetRect(&rect, HorizSpace,VertSpace+105,100,50);
      DrawText(hdc, warnMsg, -1,&rect, DT_NOCLIP);
    }
    else if (dialogStatus == ShutdownSituation){
      SYSTEMTIME lt;
      GetLocalTime(&lt);
      TCHAR greeting[100];

      // Day of the week
      _stprintf_s(greeting, sizeof(greeting), TEXT("Today is %s %d-%d-%d"),
          dayToday[lt.wDayOfWeek], lt.wDay, lt.wMonth, lt.wYear);
      TextOut(hdc, 25, 20, greeting, (int) _tcslen(greeting));

      _stprintf_s(greeting, sizeof(greeting), TEXT("Time now %d:%d:%d %s"), (lt.wHour>12)?
            lt.wHour-12:lt.wHour, lt.wMinute, lt.wSecond, (lt.wHour>11)?TEXT("PM"):TEXT("AM"));
      TextOut(hdc, 35, 40, greeting, (int) _tcslen(greeting));

      _stprintf_s(greeting, sizeof(greeting), TEXT("Windows will shutdown in %d seconds."), count);
      TextOut(hdc, 20, 70, greeting, (int) _tcslen(greeting));

      _stprintf_s(greeting, sizeof(greeting), TEXT("Please close all your applications."));
      TextOut(hdc, 25, 90, greeting, (int) _tcslen(greeting));
    }

    // End application-specific layout section.
    EndPaint(hwnd, &ps);
    break;

  case WM_COMMAND:
    switch(LOWORD (wParam)) {
      case BN_DBLCLK: case BN_CLICKED:
        // Button has been clicked
        // Retrieve time and date
        DateTime_GetSystemtime(hwndTimeP, &lpSysTime);
        DateTime_GetSystemtime(hwndDateP, &lpSysDate);

        lpSysTime.wYear = lpSysDate.wYear;
        lpSysTime.wMonth = lpSysDate.wMonth;
        lpSysTime.wDay = lpSysDate.wDay;    // Did a mistake here earlier due to lack of understanding

        // Debug statements
        // TCHAR str[200];
        // SYSTEMTIME clp;
        // GetLocalTime(&clp);

        // _stprintf_s(str, "current time: %d:%d:%d, received from user: %d:%d:%d", clp.wHour, clp.wMinute, clp.wSecond, lpSysTime.wHour, lpSysTime.wMinute, lpSysTime.wSecond);
        // MessageBoxA(hwnd, str, "current time", MB_OK);
        // _stprintf_s(str, "Local time: %d:%d:%d and date %d/%d/%d.\nInput time: %d:%d:%d and date %d/%d/%d.", clp.wHour, clp.wMinute, clp.wSecond, clp.wYear, clp.wMonth, clp.wDay, lpSysTime.wHour, lpSysTime.wMinute, lpSysTime.wSecond, lpSysDate.wYear, lpSysDate.wMonth, lpSysDate.wDay);
        // MessageBoxA(hwnd, str, "Notice", MB_OK);
        // // ShowWindow(hwnd, SW_HIDE);

        currentFocus = reactOnClick(hwnd);
        if (currentFocus == DateControl)
          SetFocus(hwndDateP);
        else if (currentFocus == TimeControl)
          SetFocus(hwndTimeP);
        break;

      case ID_ABOUT:
        hwndDlg = CreateDialog(g_hInst,
          MAKEINTRESOURCE(ABOUTDLGBOX),
          hwnd,
          (DLGPROC) DlgProc);   // Latest CL throws a casting error without explicit cast, 02-2023

        if (!hwndDlg)
          MessageBox(hwnd, TEXT("Could not create DlgBox."), TEXT("Notice"), MB_OK);
        break;

      case ID_EXIT:
        // Handle the WM_CLOSE message in OnClose
        HANDLE_MSG (hwnd, WM_CLOSE, OnClose);

      default:
        //MessageBox(hwnd, "Button not Clicked.", "Notice", MB_OK);
        break;
    }
    break;

  case WM_DESTROY:
    PostQuitMessage(0);
    if (IDT_TIMER1)
      KillTimer(hwnd, IDT_TIMER1);
    if (IDT_TIMER2)
      KillTimer(hwnd, IDT_TIMER2);
    break;

    case WM_TIMER:
    if (secondtimerstarted==FALSE && isTimeUp())
    {
      secondtimerstarted = TRUE;
      dialogStatus = ShutdownSituation;

      ShowWindow(hwnd, SW_SHOWNORMAL);
      UpdateWindow(hwnd);
      SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE);

      KillTimer(hwnd, IDT_TIMER1);
      SetTimer(hwnd, IDT_TIMER2, 1000, (TIMERPROC)NULL);

      HMENU hmenu = GetMenu(hwnd);    // hwnd is the handle of the window containing the menu
      EnableMenuItem(hmenu, ID_EXIT, MF_GRAYED);
      DrawMenuBar(hwnd);
    }
    else if (secondtimerstarted==TRUE)
    {
      if ((UINT) wParam == IDT_TIMER2)
        InvalidateRect(hwnd, NULL, true);

        if (count-- == 0)
        {
          if (!MySystemShutdown())
            MessageBox(hwnd, TEXT("Error in shutdown. Check if user account has previlege."), TEXT("Shutdown error"), MB_OK);

          PostMessage(hwnd, WM_CLOSE, 0, 0);
        }
    }

    break;

  default:
    // MessageBox(hwnd, "Default procedurec called.", "Notice", MB_OK);
    return DefWindowProc(hwnd, message, wParam, lParam); 
  }

  return 0; 
}


HWND WINAPI CreateTimePick(HWND hwndMain)
{
  HWND hwndTimePick = NULL;
  INITCOMMONCONTROLSEX icex;

  icex.dwSize = sizeof(icex);
  icex.dwICC = ICC_DATE_CLASSES;

  InitCommonControlsEx(&icex);

  hwndTimePick = CreateWindowEx(0,
        DATETIMEPICK_CLASS,
        TEXT("DateTime"),
        WS_BORDER|WS_CHILD|WS_VISIBLE|DTS_TIMEFORMAT|WS_TABSTOP,
        HorizSpace,VertSpace+20,180,20,
        hwndMain,
        NULL,
        g_hInst,
        NULL);

  return (hwndTimePick);
}

//  CreateDatePick creates a DTP control within a dialog box.
//  Returns the handle to the new DTP control if successful, or NULL 
//  otherwise.
//
//    hwndMain - The handle to the main window.
//    g_hInst  - global handle to the program instance.
//
HWND WINAPI CreateDatePick(HWND hwndMain)
{
  HWND hwndDatePick = NULL;
  INITCOMMONCONTROLSEX icex;

  icex.dwSize = sizeof(icex);
  icex.dwICC = ICC_DATE_CLASSES;

  InitCommonControlsEx(&icex);

  hwndDatePick = CreateWindowEx(0,
      DATETIMEPICK_CLASS,
      TEXT("DateTime"),
      WS_BORDER|WS_CHILD|WS_VISIBLE|WS_TABSTOP,
      HorizSpace,VertSpace+75,180,20,
      hwndMain,
      NULL,
      g_hInst,
      NULL);

  return (hwndDatePick);
}

// Take input, verify and set the vairables
//
FocusControl reactOnClick(HWND hwnd) {
  // verify input
  /************************************************
  Return Codes
  11 - Date is past
  12 - Time is past
  2 = Input too near to current Time
  3 = input too far
  4 = ok
  ************************************************/

  int ret = verifyInputDateTime();
  // invalid input
  if (ret == 11) {
    myColor1 = 0x00aaaaaa;
    myColor2 = 0x000000ff;
    // change_font color for time
    _stprintf_s(warnMsg, sizeof(warnMsg), TEXT("Entered date is in past!"));
    InvalidateRgn(hwnd, NULL, FALSE);
    return DateControl;
  }
  else if (ret == 12) {
    myColor1 = 0x000000ff;
    myColor2 = 0x00aaaaaa;
    _stprintf_s(warnMsg, sizeof(warnMsg), TEXT("Entered time is in past!"));
    InvalidateRgn(hwnd, NULL, FALSE);
    return TimeControl;
  }

  // Shutdown too near to current time
  else if (ret == 2) {
    if (MessageBox(hwnd,
      TEXT("Shutdown time too near. Click yes to continue, no to choose time again."),
      TEXT("Time too near."), MB_YESNO | MB_ICONINFORMATION) == IDYES)
    {
      // MessageBox(hwnd, "Yes selected", "Notice", MB_OK);
      // if time is already up update the window to show notification to user
      // skip first timer, start second timer
      if (isTimeUp()) {
        warnMsg[0] = '\0';
        DestroyWindow(hwndDateP);
        DestroyWindow(hwndTimeP);
        DestroyWindow(hwndButton);
        InvalidateRgn(hwnd, NULL, TRUE);

        secondtimerstarted = TRUE;
        dialogStatus = ShutdownSituation;
        // ShowWindow(hwnd, SW_SHOWNORMAL);
        UpdateWindow(hwnd);
        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE);

        SetTimer(hwnd, IDT_TIMER2, 1000, (TIMERPROC)NULL);
        HMENU hmenu = GetMenu(hwnd);    // hwnd is the handle of the window containing the menu
        EnableMenuItem(hmenu, ID_EXIT, MF_GRAYED);
        DrawMenuBar(hwnd);
      }
      // Start timer etc to shutdown and hide window
      else {
        runProgram(hwnd);
      }
    }
  }
  // Time too far, confirm from user
  else if (ret == 3){
    if (MessageBox(hwnd,
      TEXT("Shutdown time too far. Click yes to continue, no to choose time again."),
      TEXT("Time too far."), MB_YESNO | MB_ICONINFORMATION) == IDYES)
    {
      // MessageBox(hwnd, "Yes selected", "Notice", MB_OK);
      // and hide window
      // start timer etc to shutdown
      runProgram(hwnd);
    }
  }
  else if (ret == 4) {
    runProgram(hwnd);
  }
  return None;
}

int verifyInputDateTime() {
  // get current system time
  SYSTEMTIME currentLocalTime;
  GetLocalTime(&currentLocalTime);

  // if date time all matches return 1
  if (lpSysDate.wYear < currentLocalTime.wYear)
    return 11;
  else if (lpSysDate.wYear == currentLocalTime.wYear)
  {
    if (lpSysDate.wMonth < currentLocalTime.wMonth)
      return 11;
    else if (lpSysDate.wMonth == currentLocalTime.wMonth)
    {
      if (lpSysDate.wDay < currentLocalTime.wDay)
        return 11;
      else if (lpSysDate.wDay == currentLocalTime.wDay)
        return verifyInputTime(currentLocalTime);
      else if (lpSysDate.wDay > currentLocalTime.wDay + 1)
        return 3;
      else if (lpSysDate.wDay > currentLocalTime.wDay)
        return 4;
    }
    else
      return 3;
  }
  else
    return 3;

  return -1;
}


// Verify the input data received from the shutdown window
//
int verifyInputTime(SYSTEMTIME currentLocalTime) {
  // 12: Time in past
  // 2: Time too near
  // 4: Ok
  if (lpSysTime.wHour < currentLocalTime.wHour)
    return 12;
  else if (lpSysTime.wHour == currentLocalTime.wHour) {
    if (lpSysTime.wMinute < currentLocalTime.wMinute)
      return 12;
    else if (lpSysTime.wMinute == currentLocalTime.wMinute) {
      if (lpSysTime.wSecond < currentLocalTime.wSecond) {
        // char str[200];
        // _stprintf_s(str, "current time: %d:%d:%d, received from user: %d:%d:%d", currentLocalTime.wHour, currentLocalTime.wMinute, currentLocalTime.wSecond, lpSysTime.wHour, lpSysTime.wMinute, lpSysTime.wSecond);
        // MessageBoxA(NULL, str, "current time", MB_OK);
        return 12;
      }
      else
        return 2;
    }
    else if (currentLocalTime.wMinute - lpSysTime.wMinute < 3) {
      return 2;
    }
    else
      return 4;
  }
  else
    return 4;
}

/*
 * Input dialog (which is actually a winow)
 * has received positive response from user
 * It's time to start the timer and wait for time expiry
 * when we shall start procedure for shutting system down
 */
void runProgram(HWND hwnd) {
  myColor1 = 0x00aaaaaa;
  myColor2 = 0x00aaaaaa;
  warnMsg[0] = '\0';

  DestroyWindow(hwndDateP);
  DestroyWindow(hwndTimeP);
  DestroyWindow(hwndButton);
  InvalidateRgn(hwnd, NULL, TRUE);
  ShowWindow(hwnd, SW_HIDE);

  SetTimer(hwnd, IDT_TIMER1, 60000, (TIMERPROC)NULL);
  dialogStatus = Inactive;
}

// Checks if the shutdown minute is current minute
//
BOOL isTimeUp () {
  SYSTEMTIME currentLocalTime;
  GetLocalTime(&currentLocalTime);

  if (lpSysTime.wYear == currentLocalTime.wYear && lpSysTime.wMonth == currentLocalTime.wMonth &&
      lpSysTime.wDay == currentLocalTime.wDay && lpSysTime.wHour == currentLocalTime.wHour &&
      lpSysTime.wMinute >= currentLocalTime.wMinute)
    return TRUE;

  return FALSE;
}

BOOL CALLBACK DlgProc(HWND hwndDlg, 
                      UINT message, 
                      WPARAM wParam, 
                      LPARAM lParam) 
{
  PAINTSTRUCT Ps;
  HDC hDC, MemDC;
  HBITMAP hBmp;

  switch (message) {
    case WM_PAINT:
      hDC = BeginPaint(hwndDlg, &Ps);

      // Load the bitmap from the resource
      hBmp = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BMP));
      // Create a memory device compatible with the above DC variable
      MemDC = CreateCompatibleDC(hDC);
      // Select the new bitmap
      SelectObject(MemDC, hBmp);

      // Copy the bits from the memory DC into the current dc
      BitBlt(hDC, 0, 0, 450, 400, MemDC, 0, 0, SRCCOPY);

      // Restore the old bitmap
      DeleteDC(MemDC);
      DeleteObject(hBmp);
      EndPaint(hwndDlg, &Ps);
      break;
    // g_hLink is the handle of the SysLink control.
    case WM_NOTIFY:
      switch (((LPNMHDR)lParam)->code)
      {
        case NM_CLICK:
        case NM_RETURN:
        {
          PNMLINK pNMLink = (PNMLINK)lParam;
          LITEM item = pNMLink->item;

          if ((((LPNMHDR)lParam)->hwndFrom == g_hLink) && (item.iLink == 0))
            ShellExecute(NULL, TEXT("open"), item.szUrl, NULL, NULL, SW_SHOW);

          // else if (wcscmp(item.szID, TEXT("idInfo")) == 0)
          //   MessageBox(hwndDlg, TEXT("This isn't much help.", L"Example"), MB_OK);

          break;
        }
      }
      break;
    case WM_INITDIALOG:
      EnableWindow(g_hwnd, FALSE);
      RECT rect;
      SetRect(&rect, 80,151,160,15);

      INITCOMMONCONTROLSEX icex;

      icex.dwSize = sizeof(icex);
      icex.dwICC = ICC_LINK_CLASS;

      InitCommonControlsEx(&icex);

      g_hLink = CreateSysLink(hwndDlg, g_hInst, rect);
      return TRUE;

    case WM_COMMAND: 
      switch (LOWORD(wParam)) {
      case IDOK:
        EndDialog(hwndDlg, IDOK);
        break;
      }

      break;

    case WM_CLOSE:
      EndDialog(hwndDlg, TRUE);
      break;

    case WM_DESTROY:
      EnableWindow(g_hwnd, TRUE);
      break;

    default:
      return FALSE;
    }

    return FALSE; 
}

HWND CreateSysLink(HWND hDlg, HINSTANCE hInst, RECT rect) {
  return CreateWindowEx(0,
    // Fix for WC_LINK wchar_t which is no more required as we are adopting unicode
    // ref http://www.cplusplus.com/forum/windows/46297/
    WC_LINK,
    TEXT("<A HREF=\"https://note.iqubit.xyz\">iQubit</A>"),
    WS_VISIBLE | WS_CHILD | WS_TABSTOP, 
    rect.left, rect.top, rect.right, rect.bottom, 
    hDlg, NULL, hInst, NULL);
}

BOOL MySystemShutdown()
{
  HANDLE hToken; 
  TOKEN_PRIVILEGES tkp; 

  // Get a token for this process.
  if (!OpenProcessToken(GetCurrentProcess(), 
      TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) 
    return( FALSE ); 

  // Get the LUID for the shutdown privilege.
  LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,
      &tkp.Privileges[0].Luid); 

  tkp.PrivilegeCount = 1;  // one privilege to set
  tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 

  // Get the shutdown privilege for this process. 
  AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, 
      (PTOKEN_PRIVILEGES)NULL, 0); 

  if (GetLastError() != ERROR_SUCCESS) 
    return FALSE; 

  // Shut down the system and force all applications to close.
  if (!ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE, 
          SHTDN_REASON_MAJOR_OPERATINGSYSTEM |
          SHTDN_REASON_MINOR_UPGRADE |
          SHTDN_REASON_FLAG_PLANNED))
    return FALSE; 

  //shutdown was successful
  return TRUE;
}

//
//   FUNCTION: OnClose(HWND)
//
//   PURPOSE: Process the WM_CLOSE message
//
void OnClose(HWND hWnd)
{
  // EndDialog(hWnd, 0);      // our app is window, not dialog
  PostMessage(hWnd, WM_CLOSE, 0, 0);
}
