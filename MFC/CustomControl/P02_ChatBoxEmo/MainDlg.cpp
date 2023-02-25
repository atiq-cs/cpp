
// MainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Main.h"
#include "MainDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CMainDlg dialog

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
  : CDialogEx(CMainDlg::IDD, pParent)
{
  m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_EDIT1,   m_editMsgToSend);
  DDX_Control(pDX, IDC_CUSTOM1, m_chathistory);
}

BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
  ON_WM_SYSCOMMAND()
  ON_WM_PAINT()
  ON_WM_QUERYDRAGICON()
  ON_BN_CLICKED(IDOK, &CMainDlg::OnBnClickedSend)
  ON_WM_VSCROLL()
END_MESSAGE_MAP()


// CMainDlg message handlers

BOOL CMainDlg::OnInitDialog()
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


  m_chathistory.EnableScrollBar(SB_VERT);

  return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMainDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
  if ((nID & 0xFFF0) == IDM_ABOUTBOX)
  {
    CAboutDlg dlgAbout;
    dlgAbout.DoModal();
  }
  else
  {
    CDialogEx::OnSysCommand(nID, lParam);
  }
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMainDlg::OnPaint()
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

//disable enter button close
void CMainDlg::OnOK()
{ 
  
}


// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMainDlg::OnQueryDragIcon()
{
  return static_cast<HCURSOR>(m_hIcon);
}



void CMainDlg::OnBnClickedSend()
{
  // TODO: Add your control notification handler code here
  // CDialogEx::OnOK();

  TCHAR msg[1000];
  m_editMsgToSend.GetWindowText(msg, 1000);

  if (_tcslen(msg) == 0)
  {
    AfxMessageBox(_T("Input string can not be empty!"), MB_OK);
    GotoDlgCtrl(&m_editMsgToSend);
  }
  else
  {
    m_chathistory.post(msg, CTime());
    m_editMsgToSend.SetWindowText(L"");

    GotoDlgCtrl(&m_editMsgToSend);
  }
}


void CMainDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
  // TODO: Add your message handler code here and/or call default
  CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}
