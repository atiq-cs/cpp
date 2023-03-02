### MFC - Command Line Parsing
Call `ParseCommandLine` during App Instance initialization.

    BOOL CMyApp::InitInstance() {    
      // Code
      ParseCommandLine(m_cmdInfo);

      // Code
    }

This code sample below shows how easy it is to use the CL arguments as variables once parsing is complete!

In another example, we had,

```cpp
class CCustomCommandLineInfo : public CCommandLineInfo {
public:
  CCustomCommandLineInfo() {}
  INT m_nError;

  // This function will retrieve the value of the option provided
  BOOL GetOption (LPCTSTR option, CString& val);

  // This function will check for the commandline without ny options
  BOOL GetOption (LPCTSTR option);

protected:
  CMapStringToString m_options; // hash of options
  CString m_sLastOption; // last option encountered

  // Parse param overrided
  virtual void ParseParam (const TCHAR* pszParam, BOOL bFlag, BOOL bLast);
};

void CCustomCommandLineInfo::ParseParam(LPCTSTR pszParam, BOOL bFlag, BOOL bLast) {
  if (bFlag) {
    // this is a "flag" (begins with / or -)
    m_options [pszParam] = "TRUE"; // default value is "TRUE"
    m_sLastOption = pszParam; // save in case other value specified 
  }
  else if (!m_sLastOption.IsEmpty ()) 
  {
    // last token was option: set value
    m_options [m_sLastOption] = pszParam;
    m_sLastOption.Empty (); // clear
  } 

  // Call base class so MFC can see this param/token.
  CCommandLineInfo::ParseParam(pszParam, bFlag, bLast);
}

// Retrieve the balue for option provided
BOOL CCustomCommandLineInfo::GetOption (LPCTSTR option, CString& val) {
  return m_options.Lookup (option, val);
}

BOOL CCustomCommandLineInfo::GetOption (LPCTSTR option) {
  return GetOption (option, CString ());
}
```

Note the base class call on last line of `ParseParam`.

ref, *P07_CommandLineArgs/CLA.cpp*, 05-2010

Wondering what `SetConsoleMode` is about in below code sample!
 ref, same file `EnableIDMInt.cpp`

```cpp
int CMyApp::Run() {
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
