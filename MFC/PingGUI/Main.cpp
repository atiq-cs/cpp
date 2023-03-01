//
//  PURPOSE : ICMP/Ping GUI App
//  Date    : 04-17-2011
//  Remarks :
//  * Remember to run this project from path that doesn't contain spaces
//     Otherwise, arguments gets messed up. It's due to parsing of argument
//     string after `CommandLineToArgvW`
//
//    Demos,
//    - System Tray
//    - Tray Balloon Notification
//    - DNS Lookup
//    - Timer
//
//
//  TODO: replace `sprintf` with `_stprintf` and some ANSI C Functions
//
//   Refs,
//   - look at ReadMe
//   - prev name, ping.cpp
//

#include "stdafx.h"
#include "Main.h"
#include "ProvideNetInfoDialog.h"
#include "MainDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PingGUI App

// Global variables declarations
static CString ipAddress[3];
static CString ipAddrStr;
static CStringA ipAddrStrA;

BOOL isNotifyOn = FALSE;
/*  RunStage 1 means current target host is Gateway IP Address
 *  2 means Primary DNS Server
 *  3 means Secondary DNS Server
 */
BYTE RunStage = 1;

void CCustomCommandLineInfo::ParseParam(LPCTSTR pszParam, BOOL bFlag, BOOL bLast) {
  if (bFlag) {
    // this is a "flag" (begins with / or -)
    m_options [pszParam] = "TRUE"; // default value is "TRUE"
    m_sLastOption = pszParam; // save in case other value specified
  }
  else if (!m_sLastOption.IsEmpty ()) {
    // last token was option: set value
    m_options [m_sLastOption] = pszParam;
    m_sLastOption.Empty (); // clear
  }

  // Call base class so MFC can see this param/token.
  CCommandLineInfo::ParseParam (pszParam, bFlag, bLast);
}

// Retrieve the value for option provided
BOOL CCustomCommandLineInfo::GetOption (LPCTSTR option, CString& val) {
  return m_options.Lookup (option, val);
}

BOOL CCustomCommandLineInfo::GetOption (LPCTSTR option) {
  return GetOption (option, CString ());
}

BOOL CMyApp::InitInstance() {
  // sdk sample menu goes to background!
  // Hence, trying my example from CDEject project
  AfxEnableControlContainer();
  InitContextMenuManager ();
  CMFCVisualManager::SetDefaultManager (RUNTIME_CLASS (CMFCVisualManagerOffice2003));

  // InitCommonControlsEx() is required on Windows XP if an application
  // manifest specifies use of ComCtl32.dll version 6 or later to enable
  // visual styles.  Otherwise, any window creation will fail.
  INITCOMMONCONTROLSEX InitCtrls;
  InitCtrls.dwSize = sizeof(InitCtrls);
  // Set this to include all the common control classes you want to use
  // in your application.
  InitCtrls.dwICC = ICC_WIN95_CLASSES;
  InitCommonControlsEx(&InitCtrls);

  CWinApp::InitInstance();

  BOOL ClProvided = FALSE;
  CCustomCommandLineInfo cmdInfo;
  ParseCommandLine(cmdInfo);

  if (cmdInfo.GetOption (_T("t"))) {
    isNotifyOn = TRUE;
  }

  if (cmdInfo.GetOption (_T("gw"), ipAddrStr)) {
    ipAddress[0] = ipAddrStr;
    ClProvided = TRUE;
  }

  if (cmdInfo.GetOption (_T("pd"), ipAddrStr)) {
    ipAddress[1] = ipAddrStr;
    ClProvided = TRUE;
  }

  if (cmdInfo.GetOption (_T("sd"), ipAddrStr)) {
    ipAddress[2] = ipAddrStr;
    ClProvided = TRUE;
  }

  // Create the main window dialog required for data transfer
  MainDlg *mainDlg;

  if (ClProvided == FALSE) {
    // This is the way to create modal dialog
    NetInfoDialog* inputDlg = new NetInfoDialog;
    INT_PTR nRet = -1;
    nRet = inputDlg->DoModal();

    // Handle the return value from DoModal
    switch (nRet) {
      case -1:
        AfxMessageBox(_T("Dialog box could not be created!"));
        break;
      case IDABORT:
        // Do something
        break;
      case IDOK:
        // Transfer info from previous dialog
        mainDlg = new MainDlg;
        mainDlg->InitVars(inputDlg);
        break;
      case IDCANCEL:
        return FALSE;
        break;
      default:
        // Do something
        break;
    };
    delete inputDlg;
  }

  m_pMainWnd = mainDlg;

  INT_PTR nResponse = mainDlg->DoModal();
  /* Commented to avoid the sound during closing the window
  if (nResponse == IDOK)
  {
    // TODO: Place code here to handle when the dialog is
    //  dismissed with OK
    AfxMessageBox(_T("You clicked close!"));
  }
  AfxMessageBox(_T("Reached here!"));*/

  // Clean up
  delete mainDlg;
  mainDlg = NULL;
  m_pMainWnd = NULL;

  return FALSE;
}

CMyApp theApp;
