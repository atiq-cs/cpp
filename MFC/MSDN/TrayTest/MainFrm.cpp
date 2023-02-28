////////////////////////////////////////////////////////////////
// MSDN Magazine -- November 2002
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// Compiles with Visual Studio 6.0 on Windows XP.
//
// Main frame window implementation
//
#include "stdafx.h"
#include "TrayTest.h"
#include "mainfrm.h"

// Message ID used for tray notifications
#define WM_MY_TRAY_NOTIFICATION WM_USER+0

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
  //{{AFX_MSG_MAP(CMainFrame)
  ON_MESSAGE(WM_MY_TRAY_NOTIFICATION, OnTrayNotification)
  ON_WM_CREATE()
  ON_COMMAND(ID_VIEW_CLEAR,        OnViewClear)
  ON_COMMAND(ID_TOGGLE_ICON,        OnToggleIcon)
  ON_COMMAND(ID_VIEW_NOTIFICATIONS,  OnViewNotifications)
  ON_UPDATE_COMMAND_UI(ID_VIEW_CLEAR, OnUpdateViewClear)
  ON_UPDATE_COMMAND_UI(ID_VIEW_NOTIFICATIONS, OnUpdateViewNotifications)
  ON_WM_CLOSE()
  ON_COMMAND(ID_APP_OPEN, OnAppOpen)
  ON_COMMAND(ID_APP_SUSPEND, OnAppSuspend)
  ON_COMMAND(ID_VIEW_SHOWBALLOONTIP, OnShowBalloonTip)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT BASED_CODE indicators[] = {
  ID_SEPARATOR,        // status line indicator
};

CMainFrame::CMainFrame() : m_trayIcon(IDR_TRAYICON)
{
  m_bShowTrayNotifications = TRUE;
  m_bShutdown = FALSE;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
  if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
    return -1;

  if (!m_wndStatusBar.Create(this) ||
      !m_wndStatusBar.SetIndicators(indicators,sizeof(indicators)/sizeof(UINT)))
    return -1;     // fail to create

  // Create child edit control for displaying messages
  CRect rc;
  if (!m_wndEdit.Create(
      WS_VISIBLE | WS_CHILD | WS_VSCROLL | ES_MULTILINE | ES_READONLY,
      rc, this, AFX_IDW_PANE_FIRST))
    return -1;

  // Set up tray icon
  m_trayIcon.SetNotificationWnd(this, WM_MY_TRAY_NOTIFICATION);
  m_iWhichIcon = 1;

  m_trayIcon.SetIcon(IDI_MYICON);

  return 0;
}

//////////////////
// Close window. Unless we are shutting down, just hide it.
//
void CMainFrame::OnClose()
{
  if (m_bShutdown)
    CFrameWnd::OnClose();
  else
    ShowWindow(SW_HIDE);
}

#ifdef  NIN_BALLOONSHOW
#define NIN_BALLOONFIRST NIN_BALLOONSHOW
#define NIN_BALLOONLAST  NIN_BALLOONUSERCLICK
#endif

//////////////////
// Handle notification from tray icon: display a message.
//
LRESULT CMainFrame::OnTrayNotification(WPARAM uID, LPARAM lEvent)
{
  if (m_bShowTrayNotifications)
  {
    CString msg;
    if (WM_MOUSEFIRST<=lEvent && lEvent<=WM_MOUSELAST) {
      static LPCSTR MouseMsgs[] = { _T("WM_MOUSEMOVE"),
        _T("WM_LBUTTONDOWN"), _T("WM_LBUTTONUP"), _T("WM_LBUTTONDBLCLK"),
        _T("WM_RBUTTONDOWN"), _T("WM_RBUTTONUP"), _T("WM_RBUTTONDBLCLK"),
        _T("WM_MBUTTONDOWN"), _T("WM_MBUTTONUP"), _T("WM_MBUTTONDBLCLK") };
      msg = MouseMsgs[lEvent-WM_MOUSEFIRST];

#ifdef NIN_BALLOONSHOW
    } else if (NIN_BALLOONFIRST<=lEvent && lEvent<=NIN_BALLOONLAST) {
      static LPCSTR BalloonMsgs[] = { _T("NIN_BALLOONSHOW"),
        _T("NIN_BALLOONHIDE"),
        _T("NIN_BALLOONTIMEOUT"),
        _T("NIN_BALLOONUSERCLICK") };
      msg = BalloonMsgs[lEvent-NIN_BALLOONFIRST];
#endif
    }
    else
      msg = _T("(Unknown)");

    CString s;
    s.Format(_T("Tray notification: ID=%d, lEvent=0x%04x %s\r\n"),
      uID, lEvent, (LPCTSTR)msg);

    m_wndEdit.SetSel(-1, -1);    // end of edit text
    m_wndEdit.ReplaceSel(s);    // append string..
    m_wndEdit.SendMessage(EM_SCROLLCARET); // ..and make visible
  }

  return 0;
}

////////////////////////////////////////////////////////////////
// Command handlers below.
//
void CMainFrame::OnViewClear()
{
  m_wndEdit.SetWindowText(NULL); 
}

void CMainFrame::OnUpdateViewClear(CCmdUI* pCmdUI)
{
  pCmdUI->Enable(m_wndEdit.GetLineCount() > 1 || m_wndEdit.LineLength() > 0);
}

void CMainFrame::OnToggleIcon()
{
  m_iWhichIcon=!m_iWhichIcon;
  m_trayIcon.SetIcon(m_iWhichIcon ? IDI_MYICON : IDI_MYICON2);
}

void CMainFrame::OnViewNotifications()
{
  m_bShowTrayNotifications = !m_bShowTrayNotifications;
}

void CMainFrame::OnUpdateViewNotifications(CCmdUI* pCmdUI)
{
  pCmdUI->SetCheck(m_bShowTrayNotifications);
}

void CMainFrame::OnAppOpen()
{
  ShowWindow(SW_NORMAL); 
  SetForegroundWindow();
}

void CMainFrame::OnAppSuspend()
{
  m_bShutdown = TRUE;    // really exit
  SendMessage(WM_CLOSE); 
}

//////////////////
// Show balloon tip: call CTrayIcon to do it
//
void CMainFrame::OnShowBalloonTip()
{
  m_trayIcon.ShowBalloonTip(IDS_BALLOONTIP, "TrayTest", 4000);
}
