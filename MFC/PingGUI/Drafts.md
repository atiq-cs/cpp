### Drafts from Earlier Versions of Ping GUI a.k.a Pingguin

Earlier version of `MainDlg::HideApp()` in 'MainDlg.cpp',

```cpp
// Set tray notification window:
CString strToolTip = _T("Ping GUI Notifier");
m_nid.hWnd = GetSafeHwnd ();
m_nid.uCallbackMessage = UM_TRAYNOTIFY;
// Initialize NOTIFYICONDATA
memset(&m_nid, 0 , sizeof(m_nid));
m_nid.cbSize = sizeof(m_nid);
m_nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;


m_nid.dwInfoFlags      = NIIF_INFO; // add an icon to a balloon ToolTip
// Set tray icon and tooltip:
m_nid.hIcon = m_hIcon;
_tcsncpy_s (m_nid.szTip, strToolTip, strToolTip.GetLength ());
Shell_NotifyIcon (NIM_ADD, &m_nid);

LoadToTray( this,
  UM_TRAYNOTIFY, // user defined
  _T("Easy App - (title)"),
  _T("string 1 - body text"),
  _T("Easy App - (tool tip)"),
  15, //sec
  AfxGetApp()->LoadIcon(IDR_MAINFRAME));
```

Earlier thread creation in same file inside `OnInitDialog`,

```cpp
AfxBeginThread(WorkerThreadProc,NULL,THREAD_PRIORITY_NORMAL,0,0,NULL);
AfxBeginThread(WorkerThreadDNSLookUpProc, this);
```

Further customizations in 'MainDlg.cpp',

```cpp
BOOL MainDlg::PreTranslateMessage(MSG* pMsg)
{
  if( pMsg->message == WM_MOUSEMOVE )
  {
    _ToolTipCtrl.RelayEvent( pMsg ); // pass the mouse message to the ToolTip control for processing
  }

  // NO ESCAPE or RETURN key
  if (pMsg->message == WM_KEYDOWN)
  {
    if( pMsg->wParam == VK_RETURN ||
      pMsg->wParam == VK_ESCAPE )
    {
      ::TranslateMessage(pMsg);
      ::DispatchMessage(pMsg);

      return TRUE;        // DO NOT process further
    }
  }

  // NO ALT+ key
  if (pMsg->message == WM_SYSCOMMAND)
  {
    return TRUE;
  }

  return CDialogEx::PreTranslateMessage(pMsg);
}

// (MSDN) The framework calls this member function when the size, position,
// or Z-order is about to change as a result of a call to theSetWindowPos member
// function or another window-management function
void MainDlg::OnWindowPosChanging( WINDOWPOS FAR* lpwndpos )
{
  if( !m_DlgVisible ) //do this only once to hide the dialog on start
  {
    lpwndpos->flags &= ~SWP_SHOWWINDOW;
  }

  CDialogEx::OnWindowPosChanging( lpwndpos );
}
```

And, here's `MainDlg::LoadToTray`,

```cpp
void MainDlg::LoadToTray( CWnd    *pWnd,
      UINT    uCallbackMessage,
      CString sInfoTitle, // title for a balloon ToolTip.
      // This title appears in boldface above the text.
      // It can have a maximum of 63 characters
      CString sInfo, // the text for a balloon ToolTip, it can have
      // a maximum of 255 characters
      CString sTip, // the text for a standard ToolTip.
      // It can have a maximum of 128 characters,
      // including the terminating NULL.
      int     uTimeout, // in sec.
      HICON    icon )
{
  //NOTIFYICONDATA contains information that the system needs to process taskbar status area messages
  ZeroMemory( &m_nid, sizeof( NOTIFYICONDATA ) );
  m_nid.cbSize          = sizeof( NOTIFYICONDATA );
  m_nid.hWnd        = pWnd->GetSafeHwnd();
  m_nid.uID        = 0;
  m_nid.uFlags          = NIF_MESSAGE | NIF_ICON | NIF_TIP | NIF_INFO;
  // Flag Description:
  // - NIF_ICON   The hIcon member is valid.
  // - NIF_MESSAGE The uCallbackMessage member is valid.
  // - NIF_TIP   The szTip member is valid.
  // - NIF_STATE   The dwState and dwStateMask members are valid.
  // - NIF_INFO   Use a balloon ToolTip instead of a standard ToolTip. The szInfo, uTimeout, szInfoTitle, and dwInfoFlags members are valid.
  // - NIF_GUID   Reserved.

  m_nid.dwInfoFlags      = NIIF_INFO; // add an icon to a balloon ToolTip
  // Flag Description
  // - NIIF_ERROR     An error icon.
  // - NIIF_INFO      An information icon.
  // - NIIF_NONE      No icon.
  // - NIIF_WARNING   A warning icon.
  // - NIIF_ICON_MASK Version 6.0. Reserved.
  // - NIIF_NOSOUND   Version 6.0. Do not play the associated sound. Applies only to balloon ToolTips

  m_nid.uCallbackMessage = uCallbackMessage;
  m_nid.uTimeout         = uTimeout * 1000;
  if (IsWin7OrLater())
    m_nid.hBalloonIcon  = icon;
  else
    m_nid.hIcon  = icon;
  m_nid.hIcon           = icon;

  _tcscpy_s( m_nid.szInfoTitle, sInfoTitle );
  _tcscpy_s( m_nid.szInfo,      sInfo      );
  _tcscpy_s( m_nid.szTip,       sTip       );

  Shell_NotifyIcon( NIM_ADD, &m_nid ); // add to the taskbar's status area
}
```

Earlier Tray Inits in same Dlg `::OnInitDialog`,

```cpp
_ToolTipCtrl.Create( this,
      // the ToolTip control's style
      TTS_NOPREFIX | // prevents the system from stripping the ampersand (&)
                     // character from a string

      TTS_BALLOON  | // the ToolTip control has the appearance of
      // 0x40        // a cartoon "balloon," with rounded corners
                    // and a stem pointing to the item.

      TTS_ALWAYSTIP  // the ToolTip will appear when the
                    // cursor is on a tool, regardless of
                    // whether the ToolTip control's owner
                    // window is active or inactive
);

SetIconAndTitleForBalloonTip( &_ToolTipCtrl, TTI_INFO, _T("Easy App - (title)"));
```

'Main.cpp' early version,

```cpp
void MainFrame::PingQuit(TCHAR *str) {
  if (!IsWindowVisible())
    ShowWindow(SW_RESTORE);

  PostMessage(WM_PAINT, (LPARAM)0, (LPARAM)0);
  KillTimer(ID_TIMER);
  SetForegroundWindow();
  SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
}

BOOL MainFrame::PreCreateWindow(CREATESTRUCT &cs) {
  // call default implementation
  if( !CFrameWnd::PreCreateWindow(cs) )
    return FALSE;

  // fix the dimension
  cs.cx = 380;
  cs.cy = 185;

  // disable sizing
  cs.style &= ~WS_THICKFRAME;
  cs.style &= ~WS_MAXIMIZEBOX;

  return TRUE;
}

// Create Message handling
int MainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
  // Call the base class to create the window
  if( CFrameWnd::OnCreate(lpCreateStruct) != 0)
    return -1;

  CRect PRect;
  this->GetClientRect(PRect);
  m_Edit01.Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_AUTOVSCROLL | ES_READONLY,
              PRect, this, 0x188);

  // Since the window was successfully created, return 0
  return 0;
}

void MainFrame::OnPaint() {
  CFrameWnd::OnPaint();
  MainFrame* pMainWnd = (MainFrame*) AfxGetMainWnd ();
  if (pMainWnd->TextStr[0])
    m_Edit01.SetWindowText(CString(pMainWnd->TextStr));
}

void MainFrame::OnSize(UINT nType, int cx, int cy) {
  CFrameWnd::OnSize(nType, cx, cy);

  // Track the window minimizing message
   if(nType == SIZE_MINIMIZED) {
    NOTIFYICONDATA niData;
    ZeroMemory(&niData,sizeof(NOTIFYICONDATA));

    niData.cbSize = sizeof(niData);
    niData.hWnd   = this->m_hWnd;
    niData.uID    = 100;
    niData.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    //u could load ur own icon here
    niData.hIcon  = AfxGetApp()->LoadIcon(IDI_APPLICATION);

    //set the CALLBACK message ID
    niData.uCallbackMessage =  UM_TRAYNOTIFY;

    //Adds our App. icon to the taskbar status area
    Shell_NotifyIcon( NIM_ADD, &niData);

    //hide our application/window
    this->ShowWindow(SW_HIDE);
  }
}

void MainFrame::OnMaximizeApp()
{
   ShowWindow(SW_RESTORE);
}

void MainFrame::OnExit() {
  PostMessage(WM_QUIT, (LPARAM)0, (LPARAM)0);
}

void MainFrame::OnClose() {
  this->KillTimer(ID_TIMER);
  DestroyWindow();
}

LRESULT MainFrame::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) {
  //if  the message is from our application
  //which is hiding in the tray area
  if( message == UM_TRAYNOTIFY )
  {
    //trace the right mouse click msg
    if(lParam == WM_RBUTTONDOWN)
    {
      CMenu myMenu;
      myMenu.CreatePopupMenu();

      POINT pt;
      //Get the current cursor point
      GetCursorPos(&pt);

      //add menu items
      myMenu.AppendMenu( MF_POPUP, WM_USER + 1, _T("Maximize App.") );
      myMenu.AppendMenu( MF_POPUP, WM_USER + 2, _T("Exit") );

      myMenu.TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON,pt.x,pt.y,this );
    }
  }

  return CFrameWnd::WindowProc(message, wParam, lParam);
}
```

Following example code from earlier version (06-24-2010), inside `MainFrame::TimerProc` is for reference,

```cpp
MainFrame *pMainWnd = (MainFrame *)AfxGetMainWnd();
TCHAR *pstr = pMainWnd->TextStr;
pstr[0] = '\0';

HANDLE hIcmpFile;
unsigned long ipaddr = INADDR_NONE;
DWORD dwRetVal = 0;

TCHAR SendData[] = _T("Data Buffer");
LPVOID ReplyBuffer = NULL;
DWORD ReplySize = 0;
pMainWnd->CountRequest++;

ipaddr = inet_addr(ipaddrstrA);
if (ipaddr == INADDR_NONE)
{
  _stprintf_s(pstr, MSGSIZE, _T("\n\tUsage: pinggui /t [optional] /ip IPAddress\n"));
  PingQuit(pMainWnd, pstr);
  return;
}

hIcmpFile = IcmpCreateFile();
if (hIcmpFile == INVALID_HANDLE_VALUE)
{
  _stprintf_s(pstr, MSGSIZE, _T("\tUnable to open handle.\n"));
  _stprintf_s(&pstr[_tcslen(pstr)], MSGSIZE, _T("IcmpCreatefile returned error: %ld\n"), GetLastError());
  PingQuit(pMainWnd, pstr);
  return;
}

ReplySize = sizeof(ICMP_ECHO_REPLY) + sizeof(SendData);
ReplyBuffer = (VOID *)malloc(ReplySize);
if (ReplyBuffer == NULL)
{
  _stprintf_s(pstr, MSGSIZE, _T("\tUnable to allocate memory\n"));
  pMainWnd->MessageBox(pstr);
  PingQuit(pMainWnd, pstr);
  return;
}

_stprintf_s(&pstr[_tcslen(pstr)], MSGSIZE, _T("\n\tRequest [%d] "), pMainWnd->CountRequest);

dwRetVal = IcmpSendEcho(hIcmpFile, ipaddr, SendData, sizeof(SendData),
            NULL, ReplyBuffer, ReplySize, 1000);

if (dwRetVal != 0)
{
  PICMP_ECHO_REPLY pEchoReply = (PICMP_ECHO_REPLY) ReplyBuffer;
  struct in_addr ReplyAddr;
  ReplyAddr.S_un.S_addr = pEchoReply->Address;
  _stprintf_s(&pstr[_tcslen(pstr)], MSGSIZE, _T(" sent to %s\n"), ipaddrstr);

  if (dwRetVal > 1)
  {
    _stprintf_s(&pstr[_tcslen(pstr)], MSGSIZE, _T("\tReceived %ld icmp message responses\n\n"), dwRetVal);
    _stprintf_s(&pstr[_tcslen(pstr)], MSGSIZE, _T("\tInformation from the first response:\n"));
  }
  else
  {
    _stprintf_s(&pstr[_tcslen(pstr)], MSGSIZE, _T("\tReceived %ld icmp message response\n\n"), dwRetVal);
    _stprintf_s(&pstr[_tcslen(pstr)], MSGSIZE, _T("\tInformation from this response:\n"));
  }

  _stprintf_s(&pstr[_tcslen(pstr)], MSGSIZE, _T("\t  Received from %s\n"), CString(inet_ntoa(ReplyAddr)));

  if (pEchoReply->Status == 11003)
    _stprintf_s(&pstr[_tcslen(pstr)], MSGSIZE, _T("\t  Status = Request timed out.\n"));
  else
    _stprintf_s(&pstr[_tcslen(pstr)], MSGSIZE, _T("\t  Status = %ld\n"),
      pEchoReply->Status);

  _stprintf_s(&pstr[_tcslen(pstr)], MSGSIZE, _T("\t  Roundtrip time = %ld milliseconds\n"),
    pEchoReply->RoundTripTime);

  if (IsToggleMode == TRUE && pEchoReply->Status != 11003)
  {
    _stprintf_s(pstr, MSGSIZE, _T("\n\tServer is up.\n\n\tClick close button to quit the program."));
    PingQuit(pMainWnd, pstr);
  }

  pMainWnd->CountResponse = 0;
}
else
{
  int errorno = GetLastError();
  _stprintf_s(&pstr[_tcslen(pstr)], MSGSIZE, _T("lost in the network\n"));
  switch (errorno)
  {
  case 11010:
    _stprintf_s(&pstr[_tcslen(pstr)], MSGSIZE, _T("\tTimed out due to possible unreachability\n"), errno);
    pMainWnd->CountResponse++;
    break;

  default:
    _stprintf_s(&pstr[_tcslen(pstr)], MSGSIZE, _T("\tIcmpSendEcho returned error: %ld\n"), errorno);
  }

  if (IsToggleMode == FALSE)
  {
    if (pMainWnd->CountResponse >= 48)
    {
      _stprintf_s(pstr, MSGSIZE, _T("\tTarget client is possibly down.\n\n\tClick close button to quit the program."));
      PingQuit(pMainWnd, pstr);
      return;
    }
    else
    {
      _stprintf_s(&pstr[_tcslen(pstr)], MSGSIZE, _T("\n\n\tAnalyzing target host's unavailability.\n"));
      _stprintf_s(&pstr[_tcslen(pstr)], MSGSIZE, _T("\tAbsence of reply count %d.\n"), pMainWnd->CountResponse);

      pMainWnd->PostMessage(WM_PAINT, (LPARAM) 0, (LPARAM) 0);
      return;
    }
  }
  else
    _stprintf_s(&pstr[_tcslen(pstr)], MSGSIZE, _T("\n\tServer is not responding!"));
}

pMainWnd->PostMessage(WM_PAINT, (LPARAM) 0, (LPARAM) 0);
```


Dropped VS Setup Project from the sln file, probably was planning to create an installer using VS Setup project!

    Project("{54435603-DBB4-11D2-8724-00A0C9A8B90C}") = "PingGUI_Setup", "PingGUI_Setup\PingGUI_Setup.vdproj", "{F9CAA75A-7CE9-4808-A871-85C13C093271}"
    EndProject

ref, previous repo: [gitlab/pinggui](https://gitlab.com/atiq-cs/merged_pinggui/-/blob/dev/mfc-code/PingGUI.sln)