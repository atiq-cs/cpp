### Win32 Tutorial Series
Here are few tutorials to provides inside into Win32 App Dev using C++. Please feel free to click the links to find them.
1. [Hello World](./T01_Font/): change Font and draw text using Unicode (ANSI example below in this README)
2. [Enabling Visual Style, Menu and Icon](./T02_VS_and_Menu/): change Font and draw text using Unicode (ANSI example below in this README)
3. [Timer](#timer-example)
4. [Mouse KeyBoard WM Messaging](https://github.com/atiq-cs/cpp/blob/dev/Win32/Tutorials/tut_KB_Mouse.md)
5. [Accelerator Tables](https://github.com/atiq-cs/cpp/blob/dev/Win32/Tutorials/tut_AccelTbl.md)


**Refs**  
- [earlier Tutorial Series in blog around 2009](http://sa-os.blogspot.com/search/label/Win32%20Tutorial)
- [MSFT Docs - Your First Windows Program](https://learn.microsoft.com/en-us/windows/win32/learnwin32/your-first-windows-program) 3rd part is important which is about "Window Messages (Get Started with Win32 and C++)"



### Quick Start Tutorial
**(Quick Start for Win32 Programming)**  

We use VS Code to edit these code.
We use the command line to compile, link and run the code. Due to that it is a misnomer to say that it is a tutorial for beginners.

If you prefer Visual Studio instead please follow the earlier article on this.

Here's a starter article on [Desktop Applications \(Visual C++\) - MSFT Docs](https://learn.microsoft.com/en-us/cpp/windows/walkthrough-creating-windows-desktop-applications-cpp)


**WinMain Function**  
Win32 programs are different than ANSI C programs. Maintianing GUI state is a complex job. WinAPI raw, lowlevel, strong however tidious ways to create GUI Apps on Windows. Entry Point function for Win32 Apps are called `WinMain` which is main function in ANSI C programs. winMain has 4 parameters and a special return type. Signature looks like below,

```cpp
int WINAPI WinMain(HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPSTR lpCmdLine,
        int nCmdShow);
```

**Short Description of Parameters**  
*hInstance*  
      Handle to the current instance of the application.  

*hPrevInstance*  
      Handle to the previous instance of the application.  

*lpCmdLine*  
      Command line String.

*nCmdShow*  
      Specifies how the window is to be shown. It can have one of the following values,

  - *SW_HIDE*: Hides the window and activates another window.
  - *SW_MAXIMIZE*: Maximizes the specified window.
  - *SW_MINIMIZE*: Minimizes the specified window and activates the next top-level window in the Z order.
  - *SW_RESTORE*: Activates and displays the window. If the window is minimized or maximized, the system restores it to its original size and position. An application should specify this flag when restoring a minimized window.
  - *SW_SHOW*: Activates the window and displays it in its current size and position.
  and so on..


**CALLBACK Function WndProc**  
*WndProc is well known Windows Procedure.*  

To handle messages from Operating System a windows procedure is used. Actually we can give it any name and specify in the WNDCLASS class property. In our case it is WndProc.

Syntax:
```cpp
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
```

Here is a tested program that will help you to start with. The program is well-documented.

Press Ctrl + Shift + B to build the program and then Ctrl + F5 to run the program. Download project files from here in case you cannot build and test the code yourself successfully.


*[MSFT Docs - Using Messages and Message Queues](https://learn.microsoft.com/en-us/windows/win32/winmsg/using-messages-and-message-queues)* shows how to do message loop, working with message queue and sending/posting messages to the Window!


**String Type Basics**  
And _T() macro is used to set L before a string to represent Unicode string. The purpose of TEXT() macro is also the same.
TODO: link TCHAR article

- "P" means "pointer"
- "W" means "wide"
- "L" means "LONG"
- "STR" means "string"
- "C" means "const"

Hence,
- PWSTR means "pointer of wide string", that is, unsigned short* (or wchar_t*)
- LPSTR means "long pointer of string", that is, char*
- WCHAR means "wide char", that is, unsigned short (or wchar_t)
- LPCSTR means "const pointer of string", that is, const char* (Value assigned once cannot be altered at all)

When you are done with this program, check these links to complete your knowledge.

- WinMain on msdn
- WindowProc on msdn
- Windows Data Types


For ANSI C Programmers it helps to be able to code with non-unicode string methods. Next section shows how to do it.


**Drawing on a Window**  
Invalidate a specified area of the window,

```cpp
InvalidateRect(hWnd, &curRect, true);
```

Best practice, is not to draw inside any other Message than `WM_PAINT`. For example, this is definite **DON"T DO**,

```cpp
case WM_TIMER:
  tmpDC= GetDC(hWnd);
  // declared somewhere in the class to maintain state or as static var
  // TCHAR greeting[100];
  sprintf(greeting, "Current value in main: %d", count);
  TextOut(tmpDC, 5, 5, greeting, strlen(greeting));
  ReleaseDC(hWnd, tmpDC);
```

*To get client rectangle*, for example, when we need to know the dimension of the window,

```cpp
RECT curRect;
GetClientRect(hWnd, &curRect);
```

Rectangle initialization example,
```cpp
RECT curRect={5, 5, 50, 400};
```

In one of the example, I did draw on `WM_DESTROY` though which looks like below,

```cpp
case WM_DESTROY:
  tmpDC= GetDC(hWnd);
  sprintf(greeting, "Exiting program..");
  TextOut(tmpDC, 5, 5, greeting, strlen(greeting));
  ReleaseDC(hWnd, tmpDC);

  
  if (IDT_TIMER1)
    KillTimer(hWnd, IDT_TIMER1);

  PostQuitMessage(0);

  break;
```

I wonder if in above example drawing really works though!

### T03: Timer Example
A timer is instantiated like this,

```cpp
SetTimer(hWnd, IDT_TIMER, 1000, (TIMERPROC) nullptr);
```

Last argument can be used to set a CALLBACK procedure.

For the Timer implementation this is how we modify our `WndProc` function,

```cpp
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  // Maintain the time id in the class
  UINT_PTR IDT_TIMER=10;
  static TCHAR greeting[100];

  switch (message)
  {
  case WM_CREATE:
    // Create a Timer
    SetTimer(hWnd, IDT_TIMER, 1000, (TIMERPROC) nullptr);
    break;

  case WM_PAINT:
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);

    _stprintf_s(greeting, sizeof(greeting) / sizeof(TCHAR), TEXT("Seconds counted: %d"), count);
    TextOut(hdc, 5, 5, greeting, _tcslen(greeting));

    EndPaint(hWnd, &ps);
    break;
  case WM_TIMER:
    count++;
    InvalidateRect(hWnd, nullptr, false);
    break;

  case WM_DESTROY:
    PostQuitMessage(0);

    if (IDT_TIMER)
      KillTimer(hWnd, IDT_TIMER);
    break;

  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
    break;
  }

  return 0;
}
```

### Modal Dialog Example
Probably it is an anti-pattern to make a WndProc like below to make it wait with a modal dialog box!

```cpp
switch (message) {
  case WM_COMMAND:
    if (LOWORD (wParam) == IDM_APP_ABOUT) {
      int ret = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(ABOUTDLGBOX), hwnd, AboutDlgProc);

      swithc(ret) {
        case IDOK:
          MessageBox(hwnd, "Dialog exited with IDOK.", "Notice", MB_OK | MB_ICONINFORMATION);
          break;
        case IDCANCEL:
          MessageBox(hwnd, "Dialog exited with IDCANCEL.", "Notice", MB_OK | MB_ICONINFORMATION);
          break;
        case -1:
          MessageBox(hwnd, "Dialog failed!", "Error", MB_OK | MB_ICONINFORMATION);
          break;
        default:
          MessageBox(hwnd, "Unknown value.", "Notice", MB_OK | MB_ICONINFORMATION);
      }
    }
    break;
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
}
```

And the resources: DIALOG and MENU are defined as below in rc file,

    /////////////////////////////////////////////////////////////////////////////
    //
    // Dialog
    //

    ABOUTDLGBOX DIALOG DISCARDABLE 25, 25, 288, 125
    STYLE DS_MODALFRAME | WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_VISIBLE
    CAPTION "About Box"
    FONT 8, "MS Sans Serif"
    BEGIN
        DEFPUSHBUTTON   "OK",IDOK,174,18,50,14
        PUSHBUTTON      "Cancel",IDCANCEL,174,35,50,14
        GROUPBOX        "About this program...",IDC_STATIC,7,7,225,52
        CTEXT           "An example program showing how to use Dialog Boxes\r\n\r\nby theForger",
                        IDC_STATIC,16,18,144,33
    END

    /////////////////////////////////////////////////////////////////////////////
    //
    // Menu
    //

    ABOUT_MENU MENU DISCARDABLE
    BEGIN
      POPUP "&Help"
      BEGIN
        MENUITEM "&About", IDM_APP_ABOUT
      END
    END


*ref, Dialog Box, 11-15-2009*


**Win32 Programming: Programming in ANSI C (non Unicode)**  
Since we are using VS Code for editing code and manually compiling code. To get ANSI support back all we need to is follow the compile instruction.
ref, [ReadMe doc](https://github.com/atiq-cs/cpp/blob/dev/Console/README.md).

Example code using ANSI C only the `WM_PAINT` part,

```cpp
switch (message)
{
// ... ...
case WM_PAINT:
  PAINTSTRUCT ps;
  HDC hdc = BeginPaint(hWnd, &ps);

  char* str = "ANSI C (Non-unicode) program";
  TextOut(hdc, 25, 75, str, strlen(str));

  char* len_str = new TCHAR[101];
  sprintf_s(len_str, 101, "Length of the string: %d", strlen(str));
  TextOut(hdc, 25, 95, len_str, strlen(len_str));

  EndPaint(hWnd, &ps);
  break;
// ... ...
```

Entire code can be found in link on next line.

If you are using Visual Studio please follow, [Win32 Programming: How to Disable Unicode - Earlier blog on blogspot](http://sa-os.blogspot.com/2009/12/win32-programming-making-it.html)

*repro-ed from link above*  

**Win32 Programming: How to Disable Unicode in Visual Studio**  
It can feel overwhelming to traditional C programmers to start with win32 with Unicode enabled! All the text strings need to be preceded with `L` or `_T` feel abstruse. Most Windows Functions have an ANSI version and a Unicode version. ANSI versions feel intuitive and easy to grasp to usual ANSI C programmers.

We need to make a little change in project configuration. Open your project in Visual Studio IDE. Press Alt + F7.

There is an option named "General" under Configuration properties in the right side of the dialog box. Click it.

Under 'project defaults', there is a property called 'Character Set'. Change its value from "Use Unicode Character Set" to "Use Multi-Byte Character Set" selecting from the drop down list as shown in the image below. Click the image to enlarge.

(screenshot is in linked earlier above in blogspot)

Now you can use normal string functions like `strlen`, `sprintf` etc in this program to manipulate strings. Here is a sample program demonstrating ANSI C behavior.

### Target Platforms (Win32)
This is for all frameworks that are based on Win32. So that's for MFC, VC++ CLR and so on.

**winver.h**  
As per [MSFT - winver.h header](https://learn.microsoft.com/en-us/windows/win32/api/winver),  
- This header is used by Menus and Other Resources.
- Lists header files/APIs that utilize it including link to [MSFT - Using the Windows Headers](https://learn.microsoft.com/en-us/windows/win32/WinProg/using-the-windows-headers) which is thorough details on the macros and when to use them.


**Porting and upgrading**  
[MSFT - cpp - Upgrade projects from earlier versions - Update WINVER and _WIN32_WINNT](https://learn.microsoft.com/en-us/cpp/porting/modifying-winver-and-win32-winnt) provides more detais. This lists all version code for target OS.



