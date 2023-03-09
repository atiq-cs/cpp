////////////////////////////////////////////////////////////////
// MSDN Magazine -- November 2002
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// Compiles with Visual Studio 6.0 on Windows XP.
//
// TRAYTEST illustrates how to use CTrayIcon.
//
#include "stdafx.h"
#include "TrayTest.h"
#include "mainfrm.h"
#include "StatLink.h"

CMyApp theApp;

BEGIN_MESSAGE_MAP(CMyApp, CWinApp)
  ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
END_MESSAGE_MAP()

BOOL CMyApp::InitInstance()
{
  // Create main frame window (don't use doc/view stuff)
  CMainFrame* pMainFrame = new CMainFrame;
  if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
    return FALSE;

  pMainFrame->ShowWindow(SW_HIDE);
  pMainFrame->UpdateWindow();
  m_pMainWnd = pMainFrame;
  OnAppAbout();
  return TRUE;
}

//////////////////
// Custom about dialog uses CStaticLink for hyperlinks.
// * for text control, URL is specified as text in dialog editor
// * for icon control, URL is specified by setting m_iconLink.m_link
//
class CAboutDialog : public CDialog {
protected:
  // static controls with hyperlinks
  CStaticLink  m_wndLink1;

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
  m_wndLink1.SubclassDlgItem(IDC_URLPD,this);
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
