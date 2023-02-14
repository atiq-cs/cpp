//
// PURPOSE: Tutorial 1
//
// Author : Atiq Rahman
// Date   : 11-15-2010
// Status : Builds and runs great, screenshot in ReadMe
// Remarks: updated to get rid of warnings etc 02-08-2023
//   TODO :
//         - update this template as per latest VS 
//           - header files to reorder based 
//           - method signatures
//

#include "framework.h"
#include "Template.h"


template <class DERIVED_TYPE> 
class BaseWindow
{
public:
  static LRESULT CALLBACK s_WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
  {
    DERIVED_TYPE *pThis = nullptr;

    if (uMsg == WM_NCCREATE) {
      // Recover the "this" pointer which was passed as a parameter
      // to CreateWindow(Ex).
      LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
      pThis = static_cast<DERIVED_TYPE *>(lpcs->lpCreateParams);

      // Put the value in a safe place for future use
      SetWindowLongPtr(hWnd, GWLP_USERDATA,
                      reinterpret_cast<LONG_PTR>(pThis));

      pThis->m_hWnd = hWnd;
    } else {
      // Recover the "this" pointer from where our WM_NCCREATE handler
      // stashed it.
      pThis = reinterpret_cast<DERIVED_TYPE *>(
                  GetWindowLongPtr(hWnd, GWLP_USERDATA));
    }


    if (pThis)
      return pThis->WndProc(uMsg, wParam, lParam);

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
  }

  BaseWindow(_In_ HINSTANCE hInst):
    m_hWnd(nullptr),
    hInstance(hInst),
    MAX_LOADSTRING(100)
  {
    szTitle = new TCHAR[MAX_LOADSTRING];
    szWindowClass = new TCHAR[MAX_LOADSTRING];

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MAIN_APP, szWindowClass, MAX_LOADSTRING);
  }

  BOOL Create(
    DWORD dwStyle,
    // DWORD dwExStyle = 0,
    int x = CW_USEDEFAULT,
    int y = CW_USEDEFAULT,
    // Tried fixed custom width 400x300 too
    // In addition, CW_USEDEFAULT/2 doesn't work to set as proportion to Screen Size
    // TODO: try passing 0 for nWidth and nHeight
    int nWidth =  CW_USEDEFAULT,
    int nHeight = CW_USEDEFAULT,
    HWND hWndParent = nullptr,
    HMENU hMenu = nullptr
    )
  {
    MyRegisterClass();

    // The parameters to CreateWindow,
    //  szWindowClass: the name of the application
    //  szTitle: the text that appears in the title bar
    //  WS_OVERLAPPEDWINDOW: the type of window to create
    //  CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
    //   x, y: initial size (width, length)
    //  NULL: the parent of this window
    //  NULL: this application dows not have a menu bar
    //  hInstance: the first parameter from WinMain
    //  NULL: not used in this application
    //
    // Use of CreateWindowEx for extended window style, not needed yet
    //  ** last argument 'this' is important
    m_hWnd = CreateWindow(szWindowClass, szTitle, dwStyle,
      x, nWidth, y, nHeight, hWndParent, hMenu, hInstance, this);

    return (m_hWnd ? TRUE : FALSE);
  }

  HWND Window() const { return m_hWnd; }

protected:
  // Every Window needs these two
  LPTSTR szTitle;                  // The title bar text
  LPTSTR szWindowClass;            // the main window class name

  virtual LRESULT WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
  ATOM MyRegisterClass();

  HWND m_hWnd;
  HINSTANCE hInstance;
  
private:
  const int MAX_LOADSTRING;       // Max length of szTitle and szWindowClass
};

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  Remark : Had to learn this syntax for defining C++ Template Class Member Method
//   ref, SO - How to define a template member function of a template class
//     https://stackoverflow.com/q/11394832
template <class DERIVED_TYPE> 
ATOM BaseWindow<DERIVED_TYPE>::MyRegisterClass()
{
    // ref, https://github.com/atiq-cs/cpp/blob/dev/Win32/RegisterClass.md
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = DERIVED_TYPE::s_WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAIN_APP));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MAIN_APP);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


class MainWindow : public BaseWindow<MainWindow>
{
public:
  MainWindow(_In_ HINSTANCE hInstance):BaseWindow(hInstance) {  }
  LRESULT WndProc(UINT message, WPARAM wParam, LPARAM lParam);

  // Message handler for about box.
  static INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
  {
      UNREFERENCED_PARAMETER(lParam);

      switch (message)
      {
      case WM_INITDIALOG:
          return (INT_PTR)TRUE;

      case WM_COMMAND:
          if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
          {
              EndDialog(hDlg, LOWORD(wParam));
              return (INT_PTR) TRUE;
          }
          break;
      }
      return (INT_PTR) FALSE;
  }
};


//
// PURPOSE: Our Custom WndProc
//
// COMMENTS:
//  Custom WndProc Callback method Hooked via lpParam. ref, s_WndProc
//  RETURNs TRUE when no case matches indicating Error/Exception!
//

//
//  FUNCTION: WndProc(UINT, WPARAM, LPARAM)
//    No HWND param since it is stored as class member
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//  WM_COMMAND  - respond to MENU Commands and so on..
//
LRESULT MainWindow::WndProc(UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message)
  {
  case WM_PAINT: {
    PAINTSTRUCT ps;
    // Start application-specific layout section.
    HDC hdc = BeginPaint(m_hWnd, &ps);

    // Set font
    // To use Bold font use FW_BOLD instead of FW_DONTCARE
    HFONT hFont = CreateFont(20,0,0,0,FW_DONTCARE,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
      CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Verdana"));
    // Select font for the device context
    SelectObject(hdc, hFont);

    // Set drawing rectangle
    RECT rect;
    SetRect(&rect, 25,70, 300, 100);

    // Set color for the text: Red
    SetTextColor(hdc, RGB(255, 0, 0));

    // Need to wrap all string literals with TEXT(*) or _T(*) Macro
    DrawText(hdc, TEXT("Tutorial 1: custom font text (using DrawText)!"), -1, &rect, DT_LEFT);
    // LPCTSTR equivalent to const char *
    LPCTSTR str = TEXT("Regular font text (using TextOut)!");
    // _tcslen equivalent to strlen
    TextOut(hdc, 25, 140, str, (int) _tcslen(str));

    // End application-specific layout section.
    EndPaint(m_hWnd, &ps);
    break;
  }
 
  case WM_COMMAND: {
    int wmId = LOWORD(wParam);

    // Parse the menu selections
    switch (wmId) {
    case IDM_ABOUT:
        DialogBox(hInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), m_hWnd, MainWindow::About);
        break;
    case IDM_EXIT:
        DestroyWindow(m_hWnd);
        break;
    default:
        return DefWindowProc(m_hWnd, message, wParam, lParam);
    }

    break;
  }

  case WM_DESTROY:
    PostQuitMessage(0);
    break;

  default:
    return DefWindowProc(m_hWnd, message, wParam, lParam);
  }

  return TRUE;
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
// REMARKS:
//  Example of earlier signature,
//
//    int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR pCmdLine, int nCmdShow)
//
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE /* hPrevInstance */,
    _In_ LPWSTR    /* lpCmdLine */,
    _In_ int       nCmdShow)
{
  // Store instance handle in MainWindow Class Object
  MainWindow win(hInstance);

  if (!win.Create(WS_OVERLAPPEDWINDOW))
  {
    return FALSE;
  }

  // The parameters to ShowWindow,
  //  hWnd: the value returned from CreateWindow
  //  nCmdShow: the fourth parameter from WinMain
  ShowWindow(win.Window(), nCmdShow);
  UpdateWindow(win.Window());

  HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MAIN_APP));

  MSG msg;

  // Main Window message loop.
  while (GetMessage(&msg, nullptr, 0, 0))
  {
    if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
  }

  return (int) msg.wParam;
}
