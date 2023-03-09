////////////////////////////////////////////////////////////////
// MSDN Magazine -- December 2002
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// Compiles with VC 6.0 or VS.NET on Windows XP. Tab size=3.
//
// FSApp illustrates xxxx
// Compiles with VC++ 6.0 or later under Windows 98.

#include "StdAfx.h"
#include "FSApp.h"
#include "MainFrm.h"
#include "Doc.h"
#include "View.h"
#include "StatLink.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CMyApp, CWinApp)
  ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
END_MESSAGE_MAP()

IMPLEMENT_DYNAMIC(CMyApp, CWinApp)

CMyApp::CMyApp()
{
}

CMyApp theApp;

BOOL CMyApp::InitInstance()
{
  CSingleDocTemplate* pDocTemplate;
  pDocTemplate = new CSingleDocTemplate(
    IDR_MAINFRAME,
    RUNTIME_CLASS(CMyDoc),
    RUNTIME_CLASS(CMainFrame),       // main SDI frame window
    RUNTIME_CLASS(CMyView));
  AddDocTemplate(pDocTemplate);

  CCommandLineInfo cmdInfo;
  ParseCommandLine(cmdInfo);
  if (!ProcessShellCommand(cmdInfo))
    return FALSE;

  return TRUE;
}

//////////////////
// Custom about dialog uses CStaticLink for hyperlinks.
//    * for text control, URL is specified as text in dialog editor
//    * for icon control, URL is specified by setting m_iconLink.m_link
//
class CAboutDialog : public CDialog {
protected:
  // static controls with hyperlinks
  CStaticLink  m_wndLink1;
  CStaticLink  m_wndLink2;
  CStaticLink  m_wndLink3;

public:
  CAboutDialog() : CDialog(IDD_ABOUTBOX) { }
  virtual BOOL OnInitDialog();
};

/////////////////
// Initialize dialog: subclass static text/icon controls
//
BOOL CAboutDialog::OnInitDialog()
{
  // subclass static controls. URL is static text or 3rd arg
  m_wndLink1.SubclassDlgItem(IDC_STATICURLPD,this);
  m_wndLink2.SubclassDlgItem(IDC_STATICURLMSDN,this);
  m_wndLink3.SubclassDlgItem(IDC_MSDNLINK,this);
  return CDialog::OnInitDialog();
}

//////////////////
// Handle Help | About : run the About dialog
//
void CMyApp::OnAppAbout()
{
  static CAboutDialog dlg;
  dlg.DoModal();
}
