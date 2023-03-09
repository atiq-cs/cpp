////////////////////////////////////////////////////////////////
// MSDN Magazine -- December 2002
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// Compiles with VC 6.0 or VS.NET on Windows XP. Tab size=3.
//
#include "stdafx.h"
#include "resource.h"
#include "StatLink.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////
// Typcial dialog.
// Override OnNcHitTest to allow dragging by background.
//
class CMyDialog : public CDialog {
public:
  CMyDialog(CWnd* pParent = NULL); // standard constructor
protected:
  HICON m_hIcon;
  CStaticLink m_wndLink1;
  CStaticLink m_wndLink2;
  CStaticLink m_wndLink3;
  virtual BOOL OnInitDialog();
  afx_msg UINT OnNcHitTest(CPoint pt);
  DECLARE_MESSAGE_MAP()
};

//////////////////
// Vanilla MFC app class
//
class CMyApp : public CWinApp {
public:
  CMyApp();
  virtual BOOL InitInstance();
  DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CMyApp, CWinApp)
  ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

CMyApp::CMyApp()
{
}

CMyApp theApp;

//////////////////
// InitInstance runs the dialog
//
BOOL CMyApp::InitInstance()
{
  CMyDialog dlg;
  m_pMainWnd = &dlg;
  dlg.DoModal();
  return FALSE;
}

BEGIN_MESSAGE_MAP(CMyDialog, CDialog)
  ON_WM_NCHITTEST()
END_MESSAGE_MAP()

CMyDialog::CMyDialog(CWnd* pParent) : CDialog(IDD_MYDIALOG, pParent)
{
}

BOOL CMyDialog::OnInitDialog()
{
  CDialog::OnInitDialog();

  // Set URLs for web links
  m_wndLink1.SubclassDlgItem(IDC_PDURL, this,
    _T("http://www.dilascia.com"));
  m_wndLink2.SubclassDlgItem(IDC_MSDNURL, this,
    _T("http://msdn.microsoft.com/msdnmag"));
  m_wndLink3.SubclassDlgItem(IDC_MSDNURL2, this,
    _T("http://msdn.microsoft.com/msdnmag"));

  // Set the icon for this dialog.   The framework does this automatically
  // when the application's main window is not a dialog
  //
  m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
  SetIcon(m_hIcon, TRUE);      // Set big icon
  SetIcon(m_hIcon, FALSE);    // Set small icon
  
  return TRUE;  // return TRUE  unless you set the focus to a control
}

//////////////////
// Non-client hit-test handler to move window by its client area.
// If the user clicks anywhere on the client area, pretend it's the
// caption. Windows does the rest!
//
UINT CMyDialog::OnNcHitTest(CPoint pt)
{
  CRect rc;
  GetClientRect(&rc);
  ClientToScreen(&rc);
  return rc.PtInRect(pt) ? HTCAPTION : CDialog::OnNcHitTest(pt);
}
