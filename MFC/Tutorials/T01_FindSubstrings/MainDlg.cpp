// ref, SubStringSearchnIndexingDlg.cpp
// Date: 07-19-2014
//

#include "stdafx.h"
#include "SubStringSearchnIndexing.h"
#include "SubStringSearchnIndexingDlg.h"
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


// CSubStringSearchnIndexingDlg dialog

CSubStringSearchnIndexingDlg::CSubStringSearchnIndexingDlg(CWnd* pParent /*=NULL*/)
  : CDialogEx(CSubStringSearchnIndexingDlg::IDD, pParent)
  , m_staticOutput(_T(""))
{
  m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSubStringSearchnIndexingDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_EDIT1, longstr);
  DDX_Control(pDX, IDC_EDIT2, shortstr);
  DDX_Text(pDX, IDC_STATIC1, m_staticOutput);
}

BEGIN_MESSAGE_MAP(CSubStringSearchnIndexingDlg, CDialogEx)
  ON_WM_SYSCOMMAND()
  ON_WM_PAINT()
  ON_WM_QUERYDRAGICON()
  ON_BN_CLICKED(IDC_BUTTON1, &CSubStringSearchnIndexingDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CSubStringSearchnIndexingDlg message handlers

BOOL CSubStringSearchnIndexingDlg::OnInitDialog()
{
  CDialogEx::OnInitDialog();
  count=0;

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

  return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSubStringSearchnIndexingDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSubStringSearchnIndexingDlg::OnPaint()
{
  CPaintDC dc(this); // device context for painting
  if (IsIconic())
  {

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
    // dc.TextOut(10, 10, _T("Outline this!"));
  }
  else
  {
    CDialogEx::OnPaint();
  }
  //CRect rect(0, 0, 100, 100);
  // GetClientRect(&rect);
  dc.DrawText(_T("Hello, MFC"), -1, CRect(0, 0, 100, 30), DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSubStringSearchnIndexingDlg::OnQueryDragIcon()
{
  return static_cast<HCURSOR>(m_hIcon);
}


// Not really a fan of how string occurrence finding is coded
// Could do better but keeping it for reference for other functions
//  CStatic::Format()
//  
void CSubStringSearchnIndexingDlg::OnBnClickedButton1()
{
  wchar_t wcs2[1000], wcs3[1000];
  //CStatic* cs;
  longstr.GetWindowTextW(wcs2, 1000);
  shortstr.GetWindowText(wcs3, 1000);
  wchar_t keys[] = L"a";

  wchar_t * pwc;
  
    
  //wcsncpy (pwc,L"a",1);
  while(true)
  {
    if(_tcslen(wcs3) == 0)
      break;

    pwc = _tcsstr(wcs2, wcs3);
    if(pwc)
    {
      count++;
      // why??
      _tcsncpy (pwc,L"a",1);
    }
    else
      break;
  }

      
  int i = _tcscspn (wcs2,keys);
  if(_tcslen(wcs2) && _tcslen(wcs3))
  {
    m_staticOutput.Format(_T("Number of occurance %d and position of first occurence is %d"), count, i+1);
  }
  else
  {
    m_staticOutput.Format(_T("Please don't leave the fields empty"));
  }

  UpdateData(FALSE);
  count = 0;

  //std::string str = to_string(count);
  //wchar_t vOut = to_wstring(count);
  //cs->SetWindowTextW(vOut);
}
