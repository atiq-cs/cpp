//
// PURPOSE: OOP Base with Win32
//
// Author : Atiq Rahman
// Date   : 02-16-2010
// Status : Builds and runs great, HourHand appears though
//


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
      CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
      pThis = (DERIVED_TYPE*)pCreate->lpCreateParams;
      SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);
    }
    else
    {
      pThis = (DERIVED_TYPE*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
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
    int nWidth = CW_USEDEFAULT,
    int nHeight = CW_USEDEFAULT,
    HWND hWndParent = 0,
    HMENU hMenu = 0
    )
  {
    WNDCLASS wc = {0};

    wc.lpfnWndProc   = DERIVED_TYPE::WindowProc;
    wc.hInstance   = GetModuleHandle(NULL);
    wc.lpszClassName = ClassName();

    RegisterClass(&wc);

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
  PCWSTR  ClassName() const { return TEXT("Window Default Class"); }
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
			LPCWSTR TestStr = L"OOP Base Class for Win32 App";
			TextOut(hdc, 25, 85, TestStr, (int) _tcslen(TestStr));
      EndPaint(m_hwnd, &ps);
    }
    return 0;

  default:
    return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
  }
}

//
// PURPOSE: Win32 Entry Point Function
//
// COMMENTS:
//  Create and show the dialog, we changed the application to support Modeless dialog
//  through MainDialog
//
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
  UNREFERENCED_PARAMETER(hInstance);
  UNREFERENCED_PARAMETER(pCmdLine);


  MainWindow win;

  if (!win.Create(TEXT("Win32 OOP"), WS_OVERLAPPEDWINDOW))
  {
    return 0;
  }

  ShowWindow(win.Window(), nCmdShow);


  MSG msg = { };
  // Windows message loop.
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}
