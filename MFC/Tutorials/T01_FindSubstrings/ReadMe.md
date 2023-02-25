### Find Substring
Sample MFC Tutorial to show a bunch of noob functions for example,

- Note the drawing in `CSubStringSearchnIndexingDlg::OnPaint()`
- `GetWindowText` resolves to `GetWindowTextW` for Unicode.
- Uses `wchar_t`, TODO was to replace them with `TCHAR` to make it culture agnostic.
- string manipulation methods which is not really necessary to demo in an MFC app. These are generally available to any C++ project.
  - `_tcslen`
  - `_tcsstr`
  - `_tcsncpy`


Only the Main Dlg code is added for reference.
  
*Tutorial app screenshot*  
  
![Screenshot of the substring tutorial app](https://user-images.githubusercontent.com/7858031/221332743-2ecf7700-3a16-407e-a2a1-f5f696ce9210.png)

Custom Control Projects are separated out of the tutorials since those require slightly advance knowledge on controls deriving from `CWnd`.