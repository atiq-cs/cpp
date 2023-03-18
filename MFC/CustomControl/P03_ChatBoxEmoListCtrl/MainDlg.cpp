
// MainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Main.h"
#include "MainDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainDlg dialog

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
  : CDialogEx(CMainDlg::IDD, pParent)
{
  m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
  //  DDX_Control(pDX, IDC_LIST_EMO, m_lcEmo);
  DDX_Control(pDX, IDC_LIST_EMO, m_emoListControl);
}

BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
  ON_WM_PAINT()
  ON_WM_QUERYDRAGICON()
  // ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_EMO, OnNMCustomdrawListEmo)
  ON_BN_CLICKED(IDC_BUTTON_SEND, &CMainDlg::OnBnClickedButtonSend)
END_MESSAGE_MAP()


// CMainDlg message handlers

BOOL CMainDlg::OnInitDialog()
{
  CDialogEx::OnInitDialog();

  // Set the icon for this dialog.  The framework does this automatically
  //  when the application's main window is not a dialog
  SetIcon(m_hIcon, TRUE);      // Set big icon
  SetIcon(m_hIcon, FALSE);    // Set small icon

  // Inserting colums using second function from
  // ref: http://msdn.microsoft.com/en-us/library/wz5b6131(v=vs.110).aspx
  m_emoListControl.InsertColumn(0, TEXT("Message"));
  m_emoListControl.InsertColumn(1, TEXT("Time"));
  //m_emoListControl.InsertColumn(2, TEXT("Message"));

  // Get number of columns, same procedure mentioned everywhere
  // int ncColumn = m_lcEmo.GetHeaderCtrl()->GetItemCount();

  /*// insert item example ref: http://msdn.microsoft.com/en-us/library/8b9s12fc(v=vs.110).aspx  
  CString strText;
  int nColumnCount = m_emoListControl.GetHeaderCtrl()->GetItemCount();

  // Insert 10 items in the list view control. 
  for (int i = 0; i < 10; i++)
  {
    strText.Format(TEXT("item %d"), i);

    // Insert the item, select every other item.
    m_emoListControl.InsertItem(LVIF_TEXT | LVIF_STATE, i, strText, /*(i % 2) == 0 ? LVIS_SELECTED :*//* 0, LVIS_SELECTED, 0, 0);

    // Initialize the text of the subitems. 
    for (int j = 1; j < nColumnCount; j++)
    {
      strText.Format(TEXT("sub-item %d %d"), i+1, j+1);
      m_emoListControl.SetItemText(i, j, strText);
    }
    // ref: http://msdn.microsoft.com/en-us/library/bb761163.aspx
    // LVSCW_AUTOSIZE_USEHEADER fits header; 
    // m_emoListControl.SetColumnWidth(i, LVSCW_AUTOSIZE);
    m_emoListControl.SetColumnWidth(i, 200);
  }*/

  m_emoListControl.SetColumnWidth(0, 555);
  m_emoListControl.SetColumnWidth(1, 210);

  return TRUE;  // return TRUE  unless you set the focus to a control
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

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMainDlg::OnQueryDragIcon()
{
  return static_cast<HCURSOR>(m_hIcon);
}


void CMainDlg::OnBnClickedButtonSend()
{
  // TODO: Add your control notification handler code here
  /*CRect rect;
  m_emoListControl.GetWindowRect(&rect);
  CString dbgStr;
  //dbgStr.Format(TEXT("%d %d %d %d", rc.TopLeft.x, rc.TopLeft.y, rc.Width,  rc.Height));
  dbgStr.Format(TEXT("width: %ld", rect.));
  AfxMessageBox(dbgStr, MB_OK);*/

  CString m_chInText;    // chat input text
  CEdit *chatBoxEditCtrl = (CEdit *) GetDlgItem(IDC_EDIT_CHAT_IN);
  if (chatBoxEditCtrl == NULL)
    return ;
  chatBoxEditCtrl->GetWindowText(m_chInText);

  // GetDlgItemText(IDC_EDIT_CHAT_IN, m_chInText);
  if (m_chInText.GetLength() > 0) {
    int n = m_emoListControl.GetItemCount();
    m_emoListControl.InsertItemEmo(n, m_chInText);
    CTime t = CTime::GetCurrentTime();

    // ref: http://msdn.microsoft.com/en-us/library/29btb3sw.aspx
    //  & http://msdn.microsoft.com/en-us/library/fe06s4ak.aspx
    CString tmStr = t.Format(_T("%I:%M:%S %p    %A, %B %d, %Y"));
    // ATLASSERT(s == _T("Friday, March 19, 1999"));   
    m_emoListControl.SetItemText(n, 1, tmStr);
    // SetDlgItemText(IDC_EDIT_CHAT_IN, _T(""));
    chatBoxEditCtrl->SetWindowText(_T(""));
  }

  // ref: http://blogs.msdn.com/b/oldnewthing/archive/2004/08/02/205624.aspx
  GotoDlgCtrl(chatBoxEditCtrl);
}
