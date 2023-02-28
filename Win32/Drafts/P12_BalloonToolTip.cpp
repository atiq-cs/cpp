
//
//  PURPOSE : Show Balloon Tool Tip (not working)
//  Date    : 10-12-2009
//  Remarks :
//   * Working code for Balloon Tool Tip is at CD Eject project
//   - Removed common code function `WinMain` body
//   - Header and top of the source file is exactly same as in P13_SysTray.cpp
//
//    ref, 'SysTray.cpp'
//


// In WM_CREATE, we create the ToolTip object,
  // case WM_CREATE:
  //   hwndToolTip = CreateToolTip(hwndButton, hWnd, _T("Click the button. No effect though!"));
  //   SendMessage(hwndToolTip, TTM_ACTIVATE, 1, 0);


// In WM_TIMER, we create the function to show Balloon Notification,
  // case WM_TIMER:
  //   if (TipNotifyStatus)
  //   {
  //     TipNotifyStatus = FALSE;

  //     if (ShowPrintJobBalloon() == FALSE)
  //       MessageBox(NULL, _T("Shell_notify fail"), _T("Error"), NULL);

  //     MessageBox(NULL, _T("WMTIMER Event!"), _T("Systray test"), NULL);

// In addition, after above line, we had following code segment related to icon data
//  however, it was already commented out (hence, most likely not tested)
  // NOTIFYICONDATA IconData = {0};

  // IconData.cbSize = sizeof(IconData);
  // IconData.hWnd = hWnd;
  // IconData.uFlags = NIF_INFO;

  // HRESULT hr = StringCchCopy(IconData.szInfo, sizeof(IconData.szInfo)/sizeof(IconData.szInfo[0]), TEXT("Notification!"));
  // if(FAILED(hr))
  // {
  //   MessageBox(NULL,
  //     _T("Error occurred!"),
  //     _T("Tray Notification"),
  //     NULL);
  // }

  // StringCchCopy(IconData.szInfoTitle, sizeof(IconData.szInfoTitle)/sizeof(IconData.szInfoTitle[0]), TEXT("Notification Title!"));
  // IconData.uTimeout = 15000; // in milliseconds

  // Shell_NotifyIcon(NIM_MODIFY, &IconData);


HWND CreateToolTip(const HWND hwndTool, const HWND hWndMain, PTSTR pszText) {
  if (!hwndTool || !hWndMain || !pszText)
  {
      return FALSE;
  }

  // Get the window of the tool.
  // HWND hwndTool = GetDlgItem(hWndMain, toolID);
  
  // Create the tooltip. g_hInst is the global instance handle.
  HWND hwndTip = CreateWindowEx(NULL, TOOLTIPS_CLASS, NULL,
                            WS_POPUP |TTS_ALWAYSTIP | TTS_BALLOON,
                            CW_USEDEFAULT, CW_USEDEFAULT,
                            CW_USEDEFAULT, CW_USEDEFAULT,
                            hWndMain, NULL, 
                            g_hInst, NULL);
  
  if (!hwndTool || !hwndTip)
  {
      return (HWND)NULL;
  }

  // Associate the tooltip with the tool.
  TOOLINFO toolInfo = { 0 };
  toolInfo.cbSize = sizeof(toolInfo);
  toolInfo.hwnd = hWndMain;
  toolInfo.uFlags = TTF_IDISHWND | TTF_SUBCLASS;
  toolInfo.uId = (UINT_PTR)hwndTool;
  toolInfo.lpszText = pszText;

  // Instead of below line we had following in 'SysTray -Button Tip.cpp'
  // SendMessage(hwndTip, TTM_ADDTOOL, 0, (LPARAM)&toolInfo);
  if (!SendMessage(hwndTip, TTM_ADDTOOL, 0, (LPARAM)&toolInfo))
        MessageBox(NULL, _T("ADDTOOL SendMessage Failed!"), _T("Systray test"), NULL);

  return hwndTip;
}


BOOL ShowBalloonToolTip()
{
  return ShowBalloon( _T("Some title"), _T("Some text..."), IDI_BALLOONICON );
}


BOOL ShowBalloon(LPCTSTR pszTitle, LPCTSTR pszText, DWORD dwIcon)
{
  HRESULT hr;
  NOTIFYICONDATA nid={0};
  nid.cbSize = sizeof(NOTIFYICONDATA);
  nid.uFlags = NIF_INFO | NIF_SHOWTIP;
  nid.uID = ID_MINTRAYICON;
  nid.hWnd = hWnd;

  // In another example, 'SysTray -Button Tip.cpp', we didn't have below
  // `StringCchCopy` calls.
  // It just ended with 
  //  return Shell_NotifyIcon(NIM_MODIFY, &nid);
  //
  hr = StringCchCopy(nid.szInfoTitle, ARRAYSIZE(nid.szInfoTitle), pszTitle);
  if(FAILED(hr))
  {
  // TODO: Write an error handler in case the call to StringCchCopy fails.
    MessageBox(NULL,
    _T("Error occurred!"),
    _T("Tray Notification"),
    NULL);
  }

  hr = StringCchCopy(nid.szInfo, ARRAYSIZE(nid.szInfo), pszText);
  if(FAILED(hr))
  {
  // TODO: error handler for StringCchCopy
    MessageBox(NULL,
      _T("Error occurred!"),
      _T("Tray Notification"),
      NULL);
  }
  return Shell_NotifyIcon(NIM_MODIFY, &nid);
}

// ref: 'SysTray -Button Tip.cpp'
//  Not sure if it's tested either!
void ShowBalloonTooltip() {
  // CREATE A BALLOON TIP WINDOW FOR THE IP ADDRESS EDIT
  HWND hIPAddBalloonTip;
  LPTSTR TipText = _T("You cd operation completed!");

  hIPAddBalloonTip = CreateWindowEx(WS_EX_TOPMOST, TOOLTIPS_CLASS, NULL,
                    WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP | TTS_BALLOON,
                    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                    hWnd, NULL, m_hInstance, NULL);

  SetWindowPos(hIPAddBalloonTip, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

  /*hwndTip = CreateWindowEx(NULL, TOOLTIPS_CLASS, NULL,
                WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP,
                CW_USEDEFAULT, CW_USEDEFAULT,
                CW_USEDEFAULT, CW_USEDEFAULT,
                hWnd, NULL, hinstMyDll,
                NULL);

  SetWindowPos(hwndTip, HWND_TOPMOST,0, 0, 0, 0,
                SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);*/

  /*RECT rect;

  // GET COORDINATES OF THE MAIN CLIENT AREA
  GetClientRect (hWnd, &rect);

  // struct specifying info about tool in ToolTip control
  TOOLINFO ti3;

  // INITIALIZE MEMBERS OF THE TOOLINFO STRUCTURE
  ti3.cbSize    = sizeof(TOOLINFO);
  ti3.uFlags    = TTF_CENTERTIP | TTF_SUBCLASS;
  ti3.hwnd    = hWnd;
  ti3.hinst    = m_hInstance;
  ti3.uId      = (UINT_PTR) hIPAddBalloonTip;
  ti3.lpszText  = TipText;

  // ToolTip control will cover the whole window
  ti3.rect.left  = rect.left;
  ti3.rect.top  = rect.top;
  ti3.rect.right  = rect.right;
  ti3.rect.bottom  = rect.bottom;

  // Activate the close button tooltip
  SendMessage(hIPAddBalloonTip, TTM_ADDTOOL, 0, (LPARAM) (LPTOOLINFO) &ti3); */
}


// Not sure if it was useful but after CreateWindow call we had this in,
//  'SysTray -Button Tip.cpp' WinMain

int WINAPI WinMain() {
  // ... ...

  // System Tray
  NOTIFYICONDATA nid = {0};

  // ZeroMemory(&nid, sizeof(NOTIFYICONDATA)); //intialize struct to 0.
  nid.cbSize = sizeof(NOTIFYICONDATA); //this helps the OS determine stuff. (I have no idea, but it is necessary.
  nid.hWnd = hWnd; //the hWnd and uID members allow the OS to uniquely identify your icon. One window (the hWnd) can have more than one icon, as long as they have unique uIDs.
  nid.uFlags = //some flags that determine the tray's behavior:
  NIF_ICON //we're adding an icon
  | NIF_MESSAGE //we want the tray to send a message to the window identified by hWnd when something happens to our icon (see uCallbackMesage member below).
  | NIF_TIP; //our icon has a tooltip.
  // | NIF_GUID;

  nid.uCallbackMessage = MSG_MINTRAYICON; //this message must be handled in hwnd's window procedure. more info below.
  nid.uID = ID_MINTRAYICON;
  nid.hIcon = (HICON)LoadImage( //load up the icon:
  GetModuleHandle(NULL), //get the HINSTANCE to this program
  MAKEINTRESOURCE(IDI_PROGICON), //grab the icon out of our resource file
  IMAGE_ICON, //tells the versatile LoadImage function that we are loading an icon
  16, 16, //x and y values. we want a 16x16-pixel icon for the tray.
  0); //no flags necessary. these flags specify special behavior, such as loading the icon from a file instead of a resource. see source list below for MSDN docs on LoadImage.

  _tcscpy_s(nid.szTip, _T("My very own system tray icon!")); //this string cannot be longer than 64 characters including the NULL terminator (which is added by default to string literals).
  //There are some more members of the NOTIFYICONDATA struct that are for advanced features we aren't using. See sources below for MSDN docs if you want to use balloon tips (only Win2000/XP).
  //nid.guidItem = myGUID;


  if (Shell_NotifyIcon(NIM_ADD, &nid) == FALSE) {//NIM_ADD=add an icon to the tray. Then I pass a pointer to the struct that we set up above. You should error-check this function (it returns a BOOL) but I didn't since this is just an example.
    //MessageBox(hWnd, "Error", "Notice", MB_OK);
        ErrorExit(TEXT("Shell_NotifyIcon "));

    return 1;
  }
  
  ShowWindow(hWnd, SW_HIDE);
  // ... ...
  // Message Loop
}