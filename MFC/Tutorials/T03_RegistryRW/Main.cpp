//
//  PURPOSE : Enable IDM Integration
//  Date    : 06-16-2010
//  Remarks : Look at ReadMe
//    if "/1" is passed in argument it is enabled.
//     else disabled.
//
//    Modifies windows registry
//    CLA Usage:
//      EnableIDMInt.exe /help /h?
//
//   ref, EnableIDMInt.cpp
//

#define WINVER  0x501
#define _AFXDLL
#include <afxwin.h>
#include <atlbase.h>      // For CRegKey

#if !defined(_CONSOLE)
   #error Make it a console application project
#endif

/////////////////////////////////////////////////////////////////////////////
// DECLARE_CONSOLEAPP - Enables MFC-like Console App

#ifdef _CONSOLE
   #define DECLARE_CONSOLEAPP \
      extern int AFXAPI AfxWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPTSTR lpCmdLine, int nCmdShow);\
      extern "C" int _tmain( int /*argc*/, TCHAR** /*argv*/, TCHAR** /*envp*/)\
      {\
         return AfxWinMain(GetModuleHandle(NULL), NULL, GetCommandLine(), SW_SHOW);\
      }
      // remember to instantiate app class
#endif // _CONSOLE

/////////////////////////////////////////////////////////////////////////////
// Interface of CMyCommandLineInfo

class CMyCommandLineInfo : public CCommandLineInfo {
// Attributes
public:
   BOOL    m_bHelp;        // /H /? /HELP
   BOOL    m_bSetIntegration;
   BOOL    m_bSuccess;     // all switches ok


// Construction
public:
   CMyCommandLineInfo(void);

// Overrides
public:
   virtual void ParseParam( LPCTSTR lpszParam, BOOL bFlag, BOOL bLast );
};

/////////////////////////////////////////////////////////////////////////////
// Implementation of CMyCommandLineInfo

CMyCommandLineInfo::CMyCommandLineInfo(void) : CCommandLineInfo(), m_bHelp(FALSE), m_bSuccess(TRUE) {
  m_bSuccess = TRUE;
  m_bHelp = FALSE;
}

void CMyCommandLineInfo::ParseParam(
  LPCTSTR lpszParam, BOOL bSwitch, BOOL /*bLast*/)
{
  if (bSwitch)
  {
    if (0 == lstrcmpi(_T("help"), lpszParam) || 0 == lstrcmpi(_T("h"), lpszParam) ||
      0 == lstrcmpi(_T("?"), lpszParam))
    {
      m_bHelp = TRUE;
      _tprintf(_T("\nFollowing switches are supported\n/0  disable integration\n/1  enable integration\n"));
    }
    else if (0 == lstrcmpi(_T("1"), lpszParam))
      m_bSetIntegration = TRUE;
    else if (0 == lstrcmpi(_T("0"), lpszParam))
      m_bSetIntegration = FALSE;
    else
      m_bSuccess = FALSE;
  }
  else
    m_bSuccess = FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Interface of some application class

class CSAApp : public CWinApp
{
// Construction
public:
   CSAApp(void);

// Attributes
public:
  CMyCommandLineInfo m_cmdInfo;


public:
  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CSAApp)
  virtual BOOL InitInstance();
  virtual int Run();
  virtual int ExitInstance();
  //}}AFX_VIRTUAL

// Implementation
public:
   virtual ~CSAApp(void);
};

/////////////////////////////////////////////////////////////////////////////
// Instatiate the application class

DECLARE_CONSOLEAPP

CSAApp theApp;

/////////////////////////////////////////////////////////////////////////////
// Implementation of the application class

CSAApp::CSAApp(void) : CWinApp()
{
}

CSAApp::~CSAApp(void)
{
}

BOOL CSAApp::InitInstance() {
  if (!CWinApp::InitInstance())
  {
    return FALSE;
  }

  _tprintf(_T("Cmd Tool to Enable or Disable IDM Integration 1.0\n"));
  SetRegistryKey(_T("IDM Integration Kit"));
  ParseCommandLine(m_cmdInfo);

  return TRUE;
}

int CSAApp::Run()
{
  if (!m_cmdInfo.m_bSuccess)
  {
    _tprintf(_T("\nBad command line switch\n"));
    _tprintf(_T("Usage: [ProgramName /?]\n"));
  }
  else if (!m_cmdInfo.m_bHelp) {
    _tprintf(_T("\n"));

    CRegKey key;
    LPCTSTR KeyName = _T("int");
    LPCTSTR KeyPath = _T("Software\\DownloadManager\\IDMBI\\chrome");
    DWORD IntegrationStatus;

    // Open registry key and query dword value
    long nError = key.Open(HKEY_CURRENT_USER, KeyPath, KEY_READ);
    ASSERT(nError == ERROR_SUCCESS);

    // Query
    nError = key.QueryDWORDValue(KeyName, IntegrationStatus);
    if(nError == ERROR_SUCCESS) {
      _tprintf(_T("Retrieved value: %d\n"), IntegrationStatus);
    }
    else {
      // Release the key
      key.Close();
      ASSERT(FALSE);
    }

    // If does not match then write
    if (IntegrationStatus != (DWORD) m_cmdInfo.m_bSetIntegration) {
      IntegrationStatus = (DWORD) m_cmdInfo.m_bSetIntegration;

      // Release the key
      key.Close();

      // Open registry key for writing
      nError = key.Open(HKEY_CURRENT_USER, KeyPath, KEY_WRITE);
      ASSERT(nError == ERROR_SUCCESS);

      _tprintf(_T("Writing to registry. Value = %d\n"), IntegrationStatus);
      nError = key.SetDWORDValue(KeyName, IntegrationStatus);
      
      if(nError == ERROR_SUCCESS) {
        _tprintf(_T("Write success\n"));
      }
      else {
        _tprintf(_T("following error occurred: %d\n"), nError);
        // Release the key
        key.Close();
        ASSERT(FALSE);
      }
    }
    else
      _tprintf(_T("Write skipped.\n"));

    // Release the key
    key.Close();
  }

  return CWinApp::Run(); // calls ExitInstance and exits right away when m_pMainWnd=NULL
}

int CSAApp::ExitInstance()
{
   //_tprintf(_T("Done\n"));
   return CWinApp::ExitInstance();
}
