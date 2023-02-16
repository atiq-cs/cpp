#include <windows.h>
#include <Mmsystem.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <stdio.h>
// Date: 11-09-2010

#pragma comment(linker, "\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "Winmm.lib")

TCHAR str[100] = L"Click the button";

// Class and Title are literally unused, the app doesn't have a face, it is hid in Sys Tray
// The main window class name.
static TCHAR szWindowClass[] = _T("win32app");

// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("CD Eject");

HINSTANCE g_hInst;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void showTime(WCHAR *str, HDC tDC);

int WINAPI WinMain(HINSTANCE hInstance,
            HINSTANCE hPrevInstance,
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
  wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
  wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
  wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
  wcex.lpszMenuName   = NULL;
  wcex.lpszClassName  = szWindowClass;
  wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

  if (!RegisterClassEx(&wcex))
  {
      MessageBox(NULL,
          _T("Call to RegisterClassEx failed!"),
          _T("S A Win32 Tutorial"),
          NULL);

      return 1;
  }

  g_hInst = hInstance; // Store instance handle in our global variable

  // The parameters to CreateWindow explained:
  // szWindowClass: the name of the application
  // szTitle: the text that appears in the title bar
  // WS_OVERLAPPEDWINDOW: the type of window to create
  // CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
  // 500, 100: initial size (width, length)
  // NULL: the parent of this window
  // NULL: this application dows not have a menu bar
  // hInstance: the first parameter from WinMain
  // NULL: not used in this application

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
          _T("S A Win32 Tutorial"),
          NULL);

      return 1;
  }

  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);

  // Main message loop
  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return (int) msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  PAINTSTRUCT ps;
  HDC hdc;
	static HWND hwndButton;

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

  case WM_PAINT:
    HFONT hFont;
    RECT rect;
    hdc = BeginPaint(hWnd, &ps);
    // SetBkMode(hdc, TRANSPARENT);			// Does not clear the area before drawing
    // set font
    hFont = CreateFont(24,0,0,0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
    // Select font
    SelectObject(hdc, hFont);

    SetRect(&rect, 100,20,700,200);
    SetTextColor(hdc, RGB(0,141,119));
    TextOut(hdc, 80, 40, str, _tcslen(str));
    DeleteObject(hFont);

    EndPaint(hWnd, &ps);
    break;

  case WM_COMMAND: 
    switch (LOWORD(wParam)) {
    case BN_CLICKED:
      // check if click is in Button control
      if (lParam == (LPARAM) hwndButton)	{
        wsprintf(str, L"CD EJECT Success!!");

        TCHAR tmp[10];
        _stprintf(tmp, _T("\\\\.\\%c:"), 'K');
        HANDLE handle = ::CreateFile(tmp, GENERIC_READ, FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
        DWORD bytes = 0;
        DeviceIoControl(handle, FSCTL_LOCK_VOLUME, 0, 0, 0, 0, &bytes, 0);
        DeviceIoControl(handle, FSCTL_DISMOUNT_VOLUME, 0, 0, 0, 0, &bytes, 0);
        DeviceIoControl(handle, IOCTL_STORAGE_EJECT_MEDIA, 0, 0, 0, 0, &bytes, 0);
        CloseHandle(handle);

        //SendMessage(hWnd, WM_PAINT, NULL, NULL);
        InvalidateRect(hWnd, NULL, TRUE);
      }
      break;
    default:
      break;
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
