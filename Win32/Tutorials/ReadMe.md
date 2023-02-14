### Win32 Tutorial Series
Here are few tutorials to provides inside into Win32 App Dev using C++. Please feel free to click the links to find them.
1. [Hello World](./T01_Font/): change Font and draw text using Unicode (ANSI example below in this README)
2. [Enabling Visual Style, Menu and Icon](./T02_VS_and_Menu/): change Font and draw text using Unicode (ANSI example below in this README)
3. [Accelerator Tables](https://github.com/atiq-cs/cpp/blob/dev/Win32/Tutorials/tut_AccelTbl.md)

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

**Win32 Programming: How to Disable Unicode**  
Since we are using VS Code for editing code and manually compiling code. To get ANSI support back all we need to is follow the compile instruction.
ref, [ReadMe doc](https://github.com/atiq-cs/cpp/blob/dev/Console/README.md).

Example code using ANSI C only the `WM_PAINT` part,

```cpp
switch (message)
{
// ... ...
case WM_PAINT:
    PAINTSTRUCT ps;
    char *inst = "ANSI C (Non-unicode) program";
    HDC hdc = BeginPaint(hWnd, &ps);

    TextOutA(hdc, 25, 75, inst, strlen(inst));
    inst = new char[101];
    sprintf_s(inst, 100, "Length of the string: %d", strlen(inst));
    TextOutA(hdc, 25, 95, inst, strlen(inst));

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

TODO: link the screenshot

Now you can use normal string functions like `strlen`, `sprintf` etc in this program to manipulate strings. Here is a sample program demonstrating ANSI C behavior.
