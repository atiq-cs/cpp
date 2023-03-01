// MainDlg.cpp : implementation file
//
#include "stdafx.h"
#include "Main.h"
#include "ProvideNetInfoDialog.h"
#include "NetUtil.h"
#include "MainDlg.h"
#include "afxdialogex.h"
#include "Shell/TrayNotification.h"
#include "AboutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define UM_TRAYNOTIFY    (WM_USER + 200)
#define ID_MINTRAYICON   (WM_USER + 201)
#define PING_TIMER_ID    (WM_USER + 202)
#define DNS_TIMER_ID     (WM_USER + 203)

/////////////////////////////////////////////////////////////////////////////
// MainDlg dialog

BEGIN_MESSAGE_MAP(MainDlg, CDialogEx)
  //{{AFX_MSG_MAP(NetInfoDialog)
    // NOTE: the ClassWizard will add message map macros here
  ON_WM_TIMER()
  ON_WM_PAINT()
  ON_WM_QUERYDRAGICON()
  ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
  ON_COMMAND(ID_APP_EXIT, OnAppExit)
  ON_COMMAND(ID_APP_RESTORE, OnAppRestore)
  ON_WM_SYSCOMMAND()
  ON_MESSAGE(UM_TRAYNOTIFY, OnTrayNotify)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

MainDlg::MainDlg(CWnd* pParent /*=NULL*/)
  : CDialogEx(MainDlg::IDD, pParent)
  , noReq(0)
  , noReplies(0)
  , IsSingleHost(false)
  , IsNotifyEnabled(false)
  , MaxPingReqs(0)
  , RunStage(0)
  , CurReportStatic(NULL)
  , m_DlgVisible(TRUE)
{
  // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
  m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

MainDlg::~MainDlg() {
  // if we do a killtimer here the application crashes
  //Shell_NotifyIcon( NIM_DELETE, &m_nid ); // delete from the status area
}

void MainDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
  //DDX_Control(pDX, IDC_PINGPROGRESS, ProgressPingReq);
}

BOOL MainDlg::OnInitDialog()
{
  CDialogEx::OnInitDialog();

  // Set the icon for this dialog.  The framework does this automatically
  // when the application's main window is not a dialog
  SetIcon(m_hIcon, TRUE);      // Set big icon
  SetIcon(m_hIcon, FALSE);    // Set small icon

  // TODO: Add extra initialization here
  // Set the range for progress control
  ProgressPingReq = (CProgressCtrl *) GetDlgItem(IDC_PINGPROGRESS);
  ProgressPingReq->SetRange(0, MaxPingReqs);
  ProgressPingReq->SetStep(1);
  ProgressPingReq->SetPos(1);

  PingIP = &mainIP;
  SetDlgItemText(IDC_TARGETIP, *PingIP);

  // Static text on the dialog box changes according to selection of singlehost or not
  if (IsSingleHost) {
    ReportStaticDefaultText = _T("Single Host");
    SetDlgItemText(IDC_TARGETTYPE, ReportStaticDefaultText);
    RunStage = 3;
    // For single host select the middle static control for writing
    CurReportStatic = (CStatic *) GetDlgItem(IDC_REPORT_PDNS);
  }
  else {
    ReportStaticDefaultText = _T("Default Gateway");
    SetDlgItemText(IDC_TARGETTYPE, ReportStaticDefaultText);
    CurReportStatic = (CStatic *) GetDlgItem(IDC_REPORT_DG);
  }

  if (IsNotifyEnabled) {
    SetDlgItemText(IDC_STATUSBAR, _T("You can minimize the window if you wish. We will notify you when internet is available."));
  }

  // add the icon in taskbar before showing notification
  if (AddNotificationIcon(this->GetSafeHwnd(), ID_MINTRAYICON, UM_TRAYNOTIFY, m_hIcon, _T("Ping GUI Net Notifier")) == FALSE)
    MessageBox(_T("Could not create taskbar icon!"));

  m_PingTimer = SetTimer(PING_TIMER_ID, 2000, NULL);
  m_DNSLookUpTimer = SetTimer(DNS_TIMER_ID, 5000, NULL);

  return TRUE;  // return TRUE  unless you set the focus to a control
}

void MainDlg::OnClose( ) {
  // And remove the icon, what a magic!!
  if (!KillTimer (m_PingTimer))
    MessageBox(_T("Could not kill ping timer!"));
  if (!KillTimer (m_DNSLookUpTimer))
    MessageBox(_T("Could not kill dns timer!"));

  if ((m_DlgVisible == TRUE) && (DeleteNotificationIcon(this->GetSafeHwnd(), ID_MINTRAYICON) == FALSE))
    MessageBox(_T("Could not delete taskbar icon!"));

  CDialogEx::OnClose();
}

void MainDlg::OnSysCommand(UINT nID, LPARAM lParam) {
  if ((nID & 0xFFF0) == SC_MINIMIZE)
    // Hide app and activate tray
    HideApp();
  else
    CDialogEx::OnSysCommand(nID, lParam);
}

void MainDlg::HideApp()
{
  theApp.HideApplication();
  // if (!AddNotificationIcon(this->GetSafeHwnd(), ID_MINTRAYICON, UM_TRAYNOTIFY, m_hIcon, _T("PingGUI Net Notifier")))
  //   MessageBox(_T("Could not create taskbar icon!"));
  // this->ShowWindow(SW_HIDE);
  m_DlgVisible = FALSE;
}

LRESULT MainDlg::OnTrayNotify(WPARAM wParam, LPARAM lParam)
{
  UINT uiMsg = (UINT) lParam;

  switch(uiMsg)
  {
  case WM_RBUTTONUP: //on double-click the left mouse button restore the dialog
    OnTrayContextMenu();
    return 1;
  case WM_LBUTTONDBLCLK: //on double-click the left mouse button restore the dialog
    // m_nid.hIcon = NULL;
    // Shell_NotifyIcon (NIM_DELETE, &m_nid);
    m_DlgVisible = TRUE;
    this->ShowWindow( SW_RESTORE );
    // if (!DeleteNotificationIcon(this->GetSafeHwnd(), ID_MINTRAYICON))
    //   MessageBox(_T("Could not delete taskbar icon!"));

    // this->ShowWindow( SW_SHOW );
    return 1;
  }
  return 0;
}

void MainDlg::OnTrayContextMenu ()
{
  CPoint point;
  ::GetCursorPos (&point);

  CMenu menu;
  menu.LoadMenu (IDR_SYSMENU);
  ASSERT(menu);

  CMFCPopupMenu::SetForceShadow (TRUE);

  HMENU hMenu = menu.GetSubMenu (0)->Detach ();
  CMFCPopupMenu* pMenu = theApp.GetContextMenuManager()->ShowPopupMenu(hMenu, point.x, point.y, this, TRUE);
  pMenu->SetForegroundWindow ();
}

void MainDlg::OnAppAbout()
{
  CAboutDlg aboutdlg;
  aboutdlg.DoModal();
}

void MainDlg::OnAppRestore()
{
  ShowWindow(SW_RESTORE);
}

void MainDlg::OnAppExit()
{
  PostMessage(WM_CLOSE);
}



// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void MainDlg::OnPaint()
{
  if (IsIconic())
  {
    CPaintDC dc(this); // device context for painting

    SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

    // Center icon in client rectangle
    int cxIcon = GetSystemMetrics(SM_CXICON);
    int cyIcon = GetSystemMetrics(SM_CYICON);
    CRect rect;
    GetClientRect(&rect);
    int x = (rect.Width() - cxIcon + 1) / 2;
    int y = (rect.Height() - cyIcon + 1) / 2;

    // Draw the icon
    dc.DrawIcon(x, y, m_hIcon);
  }
  else
  {
    CDialogEx::OnPaint();
  }
}

void MainDlg::InitVars(NetInfoDialog *obj) {
  mainIP = obj->m_GWIP;
  DNS[0] = obj->m_PRIDNS;
  DNS[1] = obj->m_SecDNS;
  IsSingleHost = obj->m_IsSingleHost;
  IsNotifyEnabled = obj->m_isNotifyOn;
  MaxPingReqs = obj->m_MaxPingReqs;
}

void MainDlg::OnTimer(UINT_PTR nIDEvent) {
  switch (nIDEvent) {
  case PING_TIMER_ID:
  {
    CString temp;

    // Update static target IP
    // if (noReq==0)
    //   SetDlgItemText(IDC_TARGETIP, mainIP);

    // if requests reached max
    if (noReq == 0) {
      // Set progress bar to initial position
      ProgressPingReq->SetPos(1);
      switch (RunStage) {
        // For each case change the text and IP address
      case 1:
        PingIP = &DNS[0];
        ReportStaticDefaultText = _T("Primary DNS Server");
        SetDlgItemText(IDC_TARGETTYPE, ReportStaticDefaultText);
        SetDlgItemText(IDC_TARGETIP, *PingIP);
        CurReportStatic = (CStatic *) GetDlgItem(IDC_REPORT_PDNS);
        break;

      case 2:
        ReportStaticDefaultText = _T("Secondary DNS Server");
        SetDlgItemText(IDC_TARGETTYPE, ReportStaticDefaultText);
        PingIP = &DNS[1];
        SetDlgItemText(IDC_TARGETIP, *PingIP);
        CurReportStatic = (CStatic *) GetDlgItem(IDC_REPORT_SDNS);
        break;

      default:
        break;
      }
    }

    // increment Request Number
    noReq++;
    // Progress the progress control

    // Update number of request static box
    temp.Format(_T("%d"), noReq);
    SetDlgItemText(IDC_REQ, temp);

    // received reply
    if (PingHost(*PingIP) == 1) {
      // increment Reply number
      noReplies++;
      // Update number of reply static box
      temp.Format(_T("%d"), noReplies);
      SetDlgItemText(IDC_NOREPLY, temp);

      /*switch (RunStage) {
        // For each case chane the text and IP address
      case 0:
        SetDlgItemText(IDC_REPORT_DG, temp);
        break;
      case 1:
        temp.Format(_T("Primary DNS replied %d%% of requests"), PercentageOfReplies);
        SetDlgItemText(IDC_REPORT_PDNS, temp);
        break;
      case 2:
        temp.Format(_T("Secondary DNS replied %d%% of requests"), PercentageOfReplies);
        SetDlgItemText(IDC_REPORT_SDNS, temp);
        break;
      default:
        break;
      }*/
    }

    int PercentageOfReplies = noReplies * 100 / noReq;
    temp.Format(_T(" replied %d%% requests"), PercentageOfReplies);
    CurReportStatic->SetWindowText(ReportStaticDefaultText+temp);

    // if requests reached max
    if (noReq == MaxPingReqs) {
      noReq = 0;
      noReplies = 0;

      RunStage++;
      if (RunStage >= 3) {
        if (!KillTimer (m_PingTimer))
          MessageBox(_T("Could not kill timer!"));

        // KillTimer(m_PingTimer);

        SetDlgItemText(IDC_STATUSBAR, _T("                                      You may close the window now."));
      }
    }
    else
      ProgressPingReq->StepIt();
  }
  break;
  case DNS_TIMER_ID:
  {
    // DNS request hardcoded to use google, TODO: take input from user
    if (DNSLookUpPossible("google.com")) {
      KillTimer(m_DNSLookUpTimer);

      // if (ShowBalloon(theApp.m_hInstance, this->GetSafeHwnd(), ID_MINTRAYICON, _T("Ping GUI"), _T("Internet is available."), IDR_MAINFRAME) == FALSE)
      if (ShowBalloon(theApp.m_hInstance, this->GetSafeHwnd(), ID_MINTRAYICON, _T("Ping GUI"), _T("Internet is available."), IDR_MAINFRAME) == FALSE)
        MessageBox(_T("Error on taskbar notification!"));

      SetDlgItemText(IDC_STATUSBAR, _T("                                               Internet is available."));
      SetDlgItemText(IDC_DNS, _T("DNS Lookup successful."));
    }
  }
  break;
  }

  CDialogEx::OnTimer(nIDEvent);
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR MainDlg::OnQueryDragIcon()
{
  return static_cast<HCURSOR>(m_hIcon);
}

/*UINT WorkerThreadDNSLookUpProc( LPVOID pParam ) {
  MainDlg* pObject = (MainDlg *) pParam;

    if (pObject == NULL ||
        !pObject->IsKindOf(RUNTIME_CLASS(MainDlg)))
    return 1;   // if pObject is not valid

  // made friend function to access private members
  if (pObject->IsSingleHost)
    AfxMessageBox(_T("Success in thread singe host!"));
  else
    AfxMessageBox(_T("Success in thread but not singe host!"));
  return 0;
}*/
