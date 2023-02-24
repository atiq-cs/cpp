### Templates
Two Templates extracted from VS 2022. In general, note,
- use of `TRACE`

To learn from this template,
- There's a pointer to the Main Window
- Shell Manager needs to be initialized
- Requires activating "Windows Native" visual manager for enabling themes in MFC controls
- Enabled registry entries for the App

#### T01_Dlg
A Basic Dialog Based Template with most features stripped down.

To note, the new template includes,
- An rc2 file under resources dir
- pch header file that includes all the framework component header files and the manifest.
- The version of common control seem to be same through out the new Win32/MFC Templates, defined in 'framework.h'

    name='Microsoft.Windows.Common-Controls' version='6.0.0.0'

manifest pragma statement is only enabled when UNICODE is enabled though,

```cpp
#ifdef _UNICODE
  #if defined _M_IX86
    #pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
  #elif defined _M_X64
    #pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
  #else
    #pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
  #endif
#endif
```


- has a sys menu enabled with an About menu option for the App.
- Primary dialog has following message mapping enabled by default.

```cpp
BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
  ON_WM_SYSCOMMAND()
  ON_WM_PAINT()
  ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()
```
- `OnPaint` and `OnQueryDragIcon` are as usual.
- Primary Dialog is derived from `CDialogEx` and is bound to a resource dialog id.

**InitCommonControlsEx**  
Mentioned in comments of the template,

> InitCommonControlsEx() is required on Windows XP if an application manifest
> specifies use of ComCtl32.dll version 6 or later to enable visual styles. 
> Otherwise, any window creation will fail.

`InitCommonControlsEx` indeed has an ICC named `ICC_WIN95_CLASSES`!

    InitCtrls.dwICC = ICC_WIN95_CLASSES;

#### T02_SDI
What's different than Template 1?
- Exception behavior seems to be modified on this template.

`noexcept` is specified with a few class object declarations,

```cpp
public:
  CMainApp() noexcept;
```

- It does a Modal Dialog box to show "About App".
- Has more debug diag statements. (also `TRACE0`)

This template has,
- a file menu
- register the application and the document extension via Registry
- parses command line using `CCommandLineInfo`
- Accepts `DragAcceptFiles`

Single document interface app template has,
- Frame/Window
- Doc
- View

Main Frame has following members (properties / methods),
- `PreCreateWindow`
- CToolBar
- CStatusBar



![T02 SDI App Template Screenshot](https://user-images.githubusercontent.com/7858031/220487325-f2b60d66-066c-474c-a212-e0b3c735277b.png)
