### Templates
Two Templates extracted from VS 2022.

#### T01_Dlg
A Basic Dialog Based Template with most features stripped down.

To note, the new template includes,
- An rc2 file under resources dir
- pch header file that includes all the framework component header files and the manifest. The version of common control seem to be same through out the new Win32/MFC Templates.

    name='Microsoft.Windows.Common-Controls' version='6.0.0.0'

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

#### T02_SPA
Single page/document architecture.
