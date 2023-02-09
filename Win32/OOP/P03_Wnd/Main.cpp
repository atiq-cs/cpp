//
// PURPOSE: OOP Template for Win32 App Dev based on Wnd
//
// Author : Atiq Rahman
// Date   : 11-15-2010
// Status : Builds and runs great, screenshot in ReadMe
// Remarks: updated to get rid of warnings etc 02-08-2023
//   TODO :
//         - update this template as per latest VS 
//           - header files to reorder based 
//           - method signatures
//         - NULL to replace with nullptr



#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>


template <class DERIVED_TYPE> 
class BaseWindow
{
public:
  static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
  {
    DERIVED_TYPE *pThis = NULL;

    if (uMsg == WM_CREATE)
    {
      CREATESTRUCT* pCreate = (CREATESTRUCT*) lParam;
      pThis = (DERIVED_TYPE*) pCreate->lpCreateParams;
      SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR) pThis);
    }
    else
    {
      pThis = (DERIVED_TYPE*) GetWindowLongPtr(hwnd, GWLP_USERDATA);
    }
    if (pThis)
    {
      return pThis->HandleMessage(uMsg, wParam, lParam);
    }
    else
    {
      return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
  }

  BaseWindow() : m_hwnd(NULL) { }

  BOOL Create(
    PCWSTR lpWindowName,
    DWORD dwStyle,
    DWORD dwExStyle = 0,
    int x = CW_USEDEFAULT,
    int y = CW_USEDEFAULT,
    // Tried fixed custom width 400x300 too
    // In addition, CW_USEDEFAULT/2 doesn't work to set as proportion to Screen Size
    int nWidth =  CW_USEDEFAULT,
    int nHeight = CW_USEDEFAULT,
    HWND hWndParent = 0,
    HMENU hMenu = 0
    )
  {
    WNDCLASSEX wcex = {0};
 
    // Fill in the window class structure with parameters
    // that describe the main window. 
    wcex.cbSize = sizeof(wcex);          // size of structure
    wcex.style = CS_HREDRAW | 
        CS_VREDRAW;                    // redraw if size changes
    wcex.lpfnWndProc = DERIVED_TYPE::WindowProc;     // points to window procedure
    wcex.cbClsExtra = 0;                // no extra class memory
    wcex.cbWndExtra = 0;                // no extra window memory
    wcex.hInstance = GetModuleHandle(NULL);         // handle to instance
    wcex.hIcon = LoadIcon(NULL, 
        IDI_APPLICATION);              // predefined app. icon
    wcex.hCursor = LoadCursor(NULL, 
        IDC_ARROW);                    // predefined arrow
    // Was this to change Window Background to Whitish ?
    // wcex.hbrBackground  = (HBRUSH) (COLOR_WINDOW+1);
    wcex.hbrBackground = (HBRUSH) GetStockObject( 
        WHITE_BRUSH);                  // white background brush
    // Utilize valid menu resource, otherwise Registering Window and ShowWindow won't work
    // wcex.lpszMenuName =  L"MainMenu";    // name of menu resource
    wcex.lpszClassName = ClassName();  // name of window class
    // wcex.hIconSm = LoadImage(wcex.hInstance, // small class icon
    //     MAKEINTRESOURCE(5),
    //     IMAGE_ICON,
    //     GetSystemMetrics(SM_CXSMICON),
    //     GetSystemMetrics(SM_CYSMICON),
    //     LR_DEFAULTCOLOR);
 
    // Register the window class.
    RegisterClassEx(&wcex);


    m_hwnd = CreateWindowEx(
      dwExStyle, ClassName(), lpWindowName, dwStyle, x, y,
      nWidth, nHeight, hWndParent, hMenu, GetModuleHandle(NULL), this
      );

    return (m_hwnd ? TRUE : FALSE);
  }

  HWND Window() const { return m_hwnd; }

protected:

  virtual PCWSTR  ClassName() const = 0;
  virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

  HWND m_hwnd;
};


class MainWindow : public BaseWindow<MainWindow>
{
public:
  PCWSTR  ClassName() const { return L"Window Default Class"; }
  LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg)
  {
  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;

  case WM_PAINT:
    {
      PAINTSTRUCT ps;
      HDC hdc = BeginPaint(m_hwnd, &ps);
      FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));
			LPCWSTR TestStr = L"A Sample Win32 Window! :) ";
			TextOut(hdc, 25, 85, TestStr, (int) _tcslen(TestStr));
      EndPaint(m_hwnd, &ps);
    }
    return 0;

  default:
    return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
  }

  // Unreachable code warning
  // return TRUE;
}

//
// PURPOSE: Win32 Entry Point Function
//
// COMMENTS:
//  Create and show a Window
//  Changing PWSTR to PTSTR throws a cast error.
//  Changed to wide char version of WinMain which is wWinMain
//  In earlier version, we used following signature of the function:
//
/*
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR pCmdLine, int nCmdShow)
*/

int APIENTRY wWinMain(_In_ HINSTANCE /* hInstance */,
    _In_opt_ HINSTANCE /* hPrevInstance */,
    _In_ LPWSTR    /* lpCmdLine */,
    _In_ int       nCmdShow)
{
  MainWindow win;

  if (!win.Create(L"P03 Wnd Template", WS_OVERLAPPEDWINDOW))
  {
    return 0;
  }

  ShowWindow(win.Window(), nCmdShow);
  UpdateWindow(win.Window());


  MSG msg = { };
  // Main Window message loop.
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}
