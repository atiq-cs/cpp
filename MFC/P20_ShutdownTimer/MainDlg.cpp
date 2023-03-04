// Date: 12-27-2011
// MainDlg.cpp : implementation file
//
// One line change on top of the version from 07-25-2011
// pMenu->SetWindowPos(&CWnd::wndTopMost, *)
//  instead of SetForegroundWindow
//
#include "stdafx.h"
#include "Main.h"
#include "MainDlg.h"
#include "afxdialogex.h"
// ref, Win32/Common/Shell
#include "TrayNotification.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define UM_TRAYNOTIFY  (WM_USER + 200)
#define ID_MINTRAYICON (WM_USER + 201)

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
  CAboutDlg();

// Dialog Data
  enum { IDD = IDD_ABOUTBOX };

  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
  DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// MainDlg dialog
MainDlg::MainDlg(CWnd* pParent /*=NULL*/)
  : CDialogEx(MainDlg::IDD, pParent)
  , isTrayIconAdded(FALSE)
  , m_Time(COleDateTime::GetCurrentTime())
{
  m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

MainDlg::~MainDlg()
{
  if (isTrayIconAdded == TRUE && DeleteNotificationIcon(this->GetSafeHwnd(), ID_MINTRAYICON) == FALSE)
    MessageBox(_T("Destructor: could not delete taskbar icon!"), nullptr, MB_OK | MB_ICONERROR);

  if (m_hIcon)
    DestroyIcon(m_hIcon);

}

void MainDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
  DDX_Control(pDX, COMBO_ACTIONS, cbAction);
  DDX_DateTimeCtrl(pDX, IDC_TIMEPICKER, m_Time);
}

BEGIN_MESSAGE_MAP(MainDlg, CDialogEx)
  ON_WM_SYSCOMMAND()
  ON_WM_PAINT()
  ON_WM_QUERYDRAGICON()
  ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
  ON_COMMAND(ID_APP_EXIT, OnAppExit)
  ON_COMMAND(ID_APP_OPEN, OnAppOpen)
  ON_MESSAGE(UM_TRAYNOTIFY, OnTrayNotify)
  ON_BN_CLICKED(IDOKHIDE, &MainDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// MainDlg message handlers

BOOL MainDlg::OnInitDialog()
{
  CDialogEx::OnInitDialog();

  // Add "About..." menu item to system menu.

  // IDM_ABOUTBOX must be in the system command range.
  ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
  ASSERT(IDM_ABOUTBOX < 0xF000);

  CMenu* pSysMenu = GetSystemMenu(FALSE);
  if (pSysMenu != NULL)
  {
    BOOL bNameValid;
    CString strAboutMenu;
    bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
    ASSERT(bNameValid);
    if (!strAboutMenu.IsEmpty())
    {
      pSysMenu->AppendMenu(MF_SEPARATOR);
      pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
    }
  }

  // Set the icon for this dialog.  The framework does this automatically
  //  when the application's main window is not a dialog
  SetIcon(m_hIcon, TRUE);      // Set big icon
  SetIcon(m_hIcon, FALSE);    // Set small icon

  // TODO: Add extra initialization here
  // Add Actions in Listbox
  /*lbAction.AddString(_T("Shutdown"));
  lbAction.AddString(_T("Restart"));
  lbAction.AddString(_T("Reserved"));
  //lbAction.SetCurSel(1);
  lbAction.SetCaretIndex(2);*/
  cbAction.SetCurSel(2);
  return TRUE;  // return TRUE  unless you set the focus to a control
}

void MainDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
  if ((nID & 0xFFF0) == IDM_ABOUTBOX)
  {
    OnAppAbout();
  }
  else
  {
    CDialogEx::OnSysCommand(nID, lParam);
  }
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

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR MainDlg::OnQueryDragIcon()
{
  return static_cast<HCURSOR>(m_hIcon);
}

LRESULT MainDlg::OnTrayNotify(WPARAM /*wp*/, LPARAM lp)
{
  UINT uiMsg = (UINT) lp;

  switch (uiMsg)
  {
  case WM_RBUTTONUP:
    OnTrayContextMenu ();
    return 1;

  case WM_LBUTTONDBLCLK:
    ShowWindow (SW_SHOWNORMAL);
    return 1;
  }

  return 0;
}

void MainDlg::OnTrayContextMenu ()
{
  CPoint point;
  ::GetCursorPos (&point);

  CMenu menu;
  menu.LoadMenu (IDR_TRAYMENU);

  CMFCPopupMenu::SetForceShadow (TRUE);

  HMENU hMenu = menu.GetSubMenu (0)->Detach ();
  CMFCPopupMenu* pMenu = theApp.GetContextMenuManager()->ShowPopupMenu(hMenu, point.x, point.y, this, TRUE);

  // pMenu->SetForegroundWindow();
  // Set window position to topmost window.
  // solve background problem in windows 7
  pMenu->SetWindowPos(
    &CWnd::wndTopMost,
    0, 0, 0, 0,
    SWP_NOMOVE | SWP_NOREDRAW | SWP_NOSIZE
  ); 
}

void MainDlg::OnAppAbout() 
{
  CAboutDlg dlgAbout;
  dlgAbout.DoModal();
}

void MainDlg::OnAppExit() 
{
  PostMessage (WM_CLOSE);
}

void MainDlg::OnAppOpen() 
{
  ShowWindow (SW_SHOWNORMAL);
}

void MainDlg::OnBnClickedOk()
{
  // add the icon in taskbar before showing notification
  // ** Don't add if already added
  if (isTrayIconAdded == FALSE) {
    if (AddNotificationIcon(this->GetSafeHwnd(), ID_MINTRAYICON, UM_TRAYNOTIFY,
      m_hIcon, _T("Shutdown Timer")) == FALSE)
    {
      MessageBox(_T("AddNotificationIcon: error on taskbar notification!"), nullptr, MB_OK | MB_ICONERROR);
      return ;
    }
    
    isTrayIconAdded = TRUE;
  }

  // Update associated variables with the dialog controls, we have changed the ID of OK button hence update has to be called manually
  UpdateData();
  // Get date time in str
  CString timeStr = m_Time.Format(_T("%H:%M:%S"));
  ASSERT(timeStr != _T("0:0:0"));

  // Show notification
  if (isTrayIconAdded && ShowBalloon(theApp.m_hInstance, this->GetSafeHwnd(), ID_MINTRAYICON, _T("Shutdown Timer"),
    _T("System will be shutdown at ") + timeStr, IDR_MAINFRAME) == FALSE
  ) {
    MessageBox(_T("ShowBalloon: error on taskbar notification!"), nullptr, MB_OK | MB_ICONERROR);
    return ;
  }

  theApp.HideApplication();
}
