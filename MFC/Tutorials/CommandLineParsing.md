### MFC - Command Line Parsing
Call `ParseCommandLine` during App Instance initialization.

    BOOL CSAApp::InitInstance() {    
      // Code
      ParseCommandLine(m_cmdInfo);

      // Code
    }

This code sample below shows how easy it is to use the CL arguments as variables once parsing is complete!

Wondering what `SetConsoleMode` is about in below code sample!
 ref, same file `EnableIDMInt.cpp`

```cpp
int CSAApp::Run() {
  HANDLE hStdin;
  DWORD fdwMode;

  // If enable switch has been tried
  if (m_cmdInfo.m_bEnable) {
    _tprintf(_T("Enabled..\n"));
    // Code Here
    hStdin = GetStdHandle(STD_INPUT_HANDLE);
    if (hStdin == INVALID_HANDLE_VALUE)
      _tprintf(_T("Std error..\n"));

    fdwMode = ENABLE_LINE_INPUT;
    if (!SetConsoleMode(hStdin, fdwMode))
      _tprintf(_T("Console mode enable error..\n"));
  }
  else if (m_cmdInfo.m_bDisable) {
    _tprintf(_T("Disabled..\n"));
    hStdin = GetStdHandle(STD_INPUT_HANDLE);
    if (hStdin == INVALID_HANDLE_VALUE)
      _tprintf(_T("Std error disable..\n"));

    fdwMode = ENABLE_MOUSE_INPUT;
    if (!SetConsoleMode(hStdin, fdwMode))
      _tprintf(_T("Console mode disable error..\n"));
  }
  else if (m_cmdInfo.m_bSuccess == FALSE) {
    _tprintf(_T("\nBad command line switch\n"));
    _tprintf(_T("Usage: [ProgramName /?]\n"));
  }

  _tprintf(_T("Exiting\n"));

  return CWinApp::Run(); // calls ExitInstance and exits right away when m_pMainWnd=NULL
}
```


- [codeguru - Console app using MFC](https://www.codeguru.com/cplusplus/console-app-using-mfc)
