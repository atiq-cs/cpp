//
//  PURPOSE : HTTP Requests/ File Downloader Demo
//  Date    : 06-04-2010
//  Remarks : Look at ReadMe
//

// #define WINVER  0x0601
#include <afxwin.h>
#include <afxinet.h>
#include <afxcmn.h>
#include <afxdlgs.h>
#include <shlobj.h>    // For SHBrowse
#define ID_TIMER 101
using namespace std;


// Main Frame Derivation, declaration
class MainFrame : public CFrameWnd
{
public:
  MainFrame();

protected:
  BOOL PreCreateWindow(CREATESTRUCT &cs);
  BOOL PreTranslateMessage(MSG* pMsg);

  CFont m_Font;
  CStatic m_Label_SelectQFile;
  CStatic m_Label_Message;
  CStatic m_Label_SelectDestDir;
  CEdit m_Edit;
  CComboBox m_ComboQFile;
  CComboBox m_ComboDestDir;
  CButton m_ButtonDwn;
  CButton m_ButtonBrowseFile;
  CButton m_ButtonBrowseFolder;
  CToolTipCtrl m_pToolTip;
  CBrush m_Brush;
  static void CALLBACK EXPORT TimerProc (HWND hWnd, UINT nMsg, UINT nTimerID, DWORD dwTime);
  HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

  // Message Mapping Methods
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnPaint();
  afx_msg void OnComboEditUpdateQFile();
  afx_msg void OnComboEditUpdateDestDir();
  afx_msg void OnComboSelEndCancel();
  afx_msg void OnComboSelChange();
  afx_msg void OnBrowseButtonFileClick();
  afx_msg void OnBrowseButtonFolderClick();
  afx_msg void OnDwnButtonClickDownload();
  DECLARE_MESSAGE_MAP()


private:
  BOOL GetValidFolder(CString &buffer);
  CString InputPathCombo1;
  CString InputPathCombo2;
  BOOL ButtonDisabled;
  void DownloadFile(CString URL, CString& DestDir);
};

BOOL MainFrame::PreTranslateMessage(MSG* pMsg) {
    if (NULL != m_pToolTip)
        m_pToolTip.RelayEvent(pMsg);

  return CFrameWnd::PreTranslateMessage(pMsg);
}

BOOL MainFrame::PreCreateWindow(CREATESTRUCT &cs) {
  // call default implementation
  if( !CFrameWnd::PreCreateWindow(cs) )
    return FALSE;

  // fix the dimension
  cs.cx = 640;
  cs.cy = 480;

  // disable sizing
  cs.style &= ~WS_THICKFRAME;
  cs.style &= ~WS_MAXIMIZEBOX;

  return TRUE;
}

// Body of MainFrame constructor function
MainFrame::MainFrame() {
  m_Brush.CreateSolidBrush(RGB(53, 53, 53));

  CString MyWinClass = AfxRegisterWndClass (
    CS_HREDRAW|CS_VREDRAW,      // even in your code this can be the same, look in help for more detail
    // ::LoadCursor(AfxGetResourceHandle()),
    ::LoadCursor(NULL, IDC_ARROW),
    //AfxGetApp()->LoadStandardCursor(IDC_ARROW),  // Deals with the cursor the window uses.
    (HBRUSH) m_Brush,    //<- this is what you want, client area color. black is obviously RGB(0,0,0)
    //AfxGetApp()->LoadStandardIcon(IDI_APPLICATION)    // deals with icon
    ::LoadIcon(NULL, IDI_APPLICATION)
    );

  // Create the window's frame
  Create(MyWinClass, _T("HTTP File Download Demo"), WS_OVERLAPPEDWINDOW,
         CRect(120, 100, 700, 480), NULL);

  // SetTimer (ID_TIMER, 1000, &MainFrame::TimerProc);

  // Create Font
  LOGFONT lf = {0};                        // Used to create the CFont.
  // memset(&lf, 0, sizeof(LOGFONT));   // Clear out structure.
  lf.lfHeight = 20;                  // Request a 20-pixel-high font, earlier value 15
  _tcscpy_s(lf.lfFaceName, LF_FACESIZE, _T("Serge UI"));    //    with face name Serge UI
  m_Font.CreateFontIndirect(&lf);    // Create the font.
  m_ComboQFile.SetFont(&m_Font);
  m_ComboDestDir.SetFont(&m_Font);
  m_ButtonDwn.SetFont(&m_Font);

  ButtonDisabled = TRUE;
}


// Main Window Class Declaration
class CSApp: public CWinApp {
public:
  BOOL InitInstance();
};

// Window Messaging
BEGIN_MESSAGE_MAP(MainFrame, CFrameWnd)
  ON_WM_CREATE()
  ON_WM_PAINT()
  ON_WM_CTLCOLOR()
  ON_CBN_EDITUPDATE(0x189, OnComboEditUpdateQFile)
  ON_CBN_EDITUPDATE(0x191, OnComboEditUpdateDestDir)
  //ON_CBN_SELENDCANCEL(0x189, OnComboSelEndCancel)
  //ON_CBN_CLOSEUP(0x189, OnComboSelEndCancel)
  ON_CBN_SELCHANGE(0x189, OnComboSelChange)
  ON_BN_CLICKED(0x196, OnBrowseButtonFileClick)
  ON_BN_CLICKED(0x193, OnBrowseButtonFolderClick)
  ON_BN_CLICKED(0x190, OnDwnButtonClickDownload)
END_MESSAGE_MAP()

// Create Message handling
int MainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
  // Call the base class to create the window
  if( CFrameWnd::OnCreate(lpCreateStruct) != 0)
    return -1;

  m_Label_SelectQFile.Create(_T("Select your file containing download URLs"), WS_CHILD | WS_VISIBLE,
        CRect(50, 20, 400, 50), this, 0x188);

  m_Label_Message.Create(_T("\tDebug Message Box"), WS_CHILD | WS_VISIBLE,
        CRect(50, 240, 415, 330), this, 0x192);

  //m_ComboQFile
  m_ComboQFile.Create(WS_CHILD|WS_VISIBLE|WS_VSCROLL|CBS_DROPDOWN|CBS_AUTOHSCROLL|CBS_DISABLENOSCROLL,
        CRect(50, 50, 400, 80), this, 0x189);

  m_Label_SelectDestDir.Create(_T("Select your destination folder"), WS_CHILD | WS_VISIBLE,
        CRect(50, 90, 245, 110), this, 0x195);    // Reserved 194

  m_ComboDestDir.Create(WS_CHILD|WS_VISIBLE|WS_VSCROLL|CBS_DROPDOWN|CBS_AUTOHSCROLL|CBS_DISABLENOSCROLL,
        CRect(50, 120, 400, 150), this, 0x191);

  m_ButtonBrowseFile.Create(_T(".."), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_CENTER,
        CRect(410, 52, 435, 73), this, 0x196);

  m_ButtonDwn.Create(_T("Download"), WS_DISABLED | WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_CENTER,
        CRect(190, 180, 260, 205), this, 0x190);

  m_ButtonBrowseFolder.Create(_T(".."), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_CENTER,
        CRect(410, 122, 435, 143), this, 0x193);

  ASSERT(m_pToolTip.Create(this));
  // ASSERT(m_pToolTip.AddTool(this, _T("About Box")));
  ASSERT(m_pToolTip.AddTool(&m_ComboQFile, _T("Enter file path here")));
  ASSERT(m_pToolTip.AddTool(&m_ButtonDwn, _T("Click to start download")));
  ASSERT(m_pToolTip.AddTool(&m_ButtonBrowseFile, _T("Select file, browse folders")));
  ASSERT(m_pToolTip.AddTool(&m_ComboDestDir, _T("Enter folder path here")));
  ASSERT(m_pToolTip.AddTool(&m_ButtonBrowseFolder, _T("Select destination folders")));
  m_pToolTip.Activate(TRUE);

  // Disable Button
  // m_ButtonDwn.EnableWindow(FALSE);
  // Since the window was successfully created, return 0
  return 0;
}

// Paint Message handling
void MainFrame::OnPaint() {
  CFrameWnd::OnPaint();
  m_ComboQFile.SetFocus();
}

HBRUSH MainFrame::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) {
   // Call the base class implementation first! Otherwise, it may
   // undo what we're trying to accomplish here.
  HBRUSH hbr = CWnd::OnCtlColor(pDC, pWnd, nCtlColor);

   // Are we painting the IDC_MYSTATIC control? We can use
   // CWnd::GetDlgCtrlID() to perform the most efficient test.
  if (pWnd->GetDlgCtrlID() == m_Label_SelectQFile.GetDlgCtrlID() || pWnd->GetDlgCtrlID() == m_Label_SelectDestDir.GetDlgCtrlID()) {
    // Set the text color to red
    pDC->SetTextColor(RGB(0x38, 0x9A, 0x4C));

    // Set the background mode for text to transparent
    // so background will show thru.
    pDC->SetBkMode(TRANSPARENT);

    // Return handle to our CBrush object
    hbr = m_Brush;
   }

   return hbr;
}

BOOL MainFrame::GetValidFolder(CString &buffer) {
    int pos = -1;
    do {
        DWORD attrib = GetFileAttributes(buffer);
        if (attrib != 0xffffffff && (attrib & FILE_ATTRIBUTE_DIRECTORY))
        {
          // the path is a valid folder
          if (buffer[buffer.GetLength() - 1] != '\\')
            buffer += "\\";

          return TRUE;
        }

        pos = buffer.ReverseFind('\\');
        if (pos > 0)
        {
            int len = buffer.GetLength();
            buffer.Delete(pos, len - pos);
        }
    } while (pos > 0);

    return FALSE;
}

void MainFrame::OnComboEditUpdateQFile() {
  int i;
  CString DestDirEnteredPath, QFileEnteredPath, ValidPath;

  BOOL ListUpdated = FALSE;

  m_ComboDestDir.GetWindowText(DestDirEnteredPath);
  m_ComboQFile.GetWindowText(QFileEnteredPath);

  // Disable/Enable Download Button
  if (ButtonDisabled) {
    if (DestDirEnteredPath.GetLength() > 0 && QFileEnteredPath.GetLength() > 0) {
      m_ButtonDwn.EnableWindow();
      ButtonDisabled = FALSE;
    }
  }
  else {
    if (DestDirEnteredPath.GetLength() == 0 || QFileEnteredPath.GetLength() == 0) {
      m_ButtonDwn.EnableWindow(FALSE);
      ButtonDisabled = TRUE;
    }
  }

  for (i = m_ComboQFile.GetCount()-1; i>=0; i--)
    m_ComboQFile.DeleteString(i);

  InputPathCombo1 = QFileEnteredPath;
  ValidPath = QFileEnteredPath;
  if (GetValidFolder(ValidPath)) {
    m_Label_Message.SetWindowText(_T("Valid Path = ") + ValidPath);
    CFileFind finder;
    CString fileName;

    fileName = ValidPath;
    fileName += _T("\\*.*");

    BOOL bOk = finder.FindFile(fileName);

    while (bOk) {
      bOk = finder.FindNextFile();

      /** skip . and .. files */
      if (finder.IsDots())
       continue;

      /** Add to list if its a directory */
      // if (finder.IsDirectory()) {
      CString curFilePath = finder.GetFilePath();
      if (!curFilePath.MakeLower().Find(QFileEnteredPath.MakeLower())) {
        m_ComboQFile.AddString(curFilePath);
        ListUpdated = TRUE;
      }
      // }
    }
    // MessageBox(_T("Path is valid"));
  }
  else
    m_Label_Message.SetWindowText(_T("Invalid Path = ") + ValidPath);


  if (ListUpdated) {
    m_ComboQFile.ShowDropDown();
    m_ComboQFile.SetWindowText(InputPathCombo1);
    int len = InputPathCombo1.GetLength();
    m_ComboQFile.SetEditSel(len, len);
  }
  else
    m_ComboQFile.ShowDropDown(FALSE);
}

void MainFrame::OnComboEditUpdateDestDir() {
  int i;
  CString DestDirEnteredPath, QFileEnteredPath, ValidPath;

  BOOL ListUpdated = FALSE;

  m_ComboDestDir.GetWindowText(DestDirEnteredPath);
  m_ComboQFile.GetWindowText(QFileEnteredPath);

  // Disable/Enable Download Button
  if (ButtonDisabled) {
    if (DestDirEnteredPath.GetLength() > 0 && QFileEnteredPath.GetLength() > 0) {
      m_ButtonDwn.EnableWindow();
      ButtonDisabled = FALSE;
    }
  }
  else {
    if (DestDirEnteredPath.GetLength() == 0 || QFileEnteredPath.GetLength() == 0) {
      m_ButtonDwn.EnableWindow(FALSE);
      ButtonDisabled = TRUE;
    }
  }

  for (i=m_ComboDestDir.GetCount()-1; i>=0; i--)
    m_ComboDestDir.DeleteString(i);

  InputPathCombo2 = DestDirEnteredPath;
  ValidPath = DestDirEnteredPath;
  if (GetValidFolder(ValidPath)) {
    m_Label_Message.SetWindowText(_T("Valid Path = ") + ValidPath);
    CFileFind finder;
    CString fileName;

    fileName = ValidPath;
    fileName += _T("\\*.*");

    BOOL bOk = finder.FindFile(fileName);

    while (bOk) {
      bOk = finder.FindNextFile();

      // ** skip . and .. files
      if (finder.IsDots())
       continue;

      // ** Add to list if its a directory
      if (finder.IsDirectory()) {
        CString curFilePath = finder.GetFilePath();
        if (!curFilePath.MakeLower().Find(DestDirEnteredPath.MakeLower())) {
          m_ComboDestDir.AddString(curFilePath);
          ListUpdated = TRUE;
        }
      }
    }
    // MessageBox(_T("Path is valid"));
  }
  else
    m_Label_Message.SetWindowText(_T("Invalid Path = ") + ValidPath);


  if (ListUpdated) {
    m_ComboDestDir.ShowDropDown();
    m_ComboDestDir.SetWindowText(InputPathCombo2);
    int len = InputPathCombo2.GetLength();
    m_ComboDestDir.SetEditSel(len, len);
  }
  else
    m_ComboDestDir.ShowDropDown(FALSE);
}

void MainFrame::OnComboSelEndCancel()
{
  m_ComboQFile.SetWindowText(InputPathCombo1);
  int len = InputPathCombo1.GetLength();
  m_ComboQFile.SetEditSel(len, len);
  // MessageBox(_T("Cancellation: ") +InputPathCombo1);
  // m_ComboQFile.SetWindowText();
}

void MainFrame::OnComboSelChange() {
  CString tmp;
  m_ComboQFile.GetWindowText(tmp);

  int len = tmp.GetLength();
  m_ComboQFile.SetEditSel(len, len);
}

void MainFrame::OnBrowseButtonFileClick() {
  CFileDialog fOpenDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY|OFN_FILEMUSTEXIST,
  _T("Text Files (*.txt)|*.txt"), this);

  fOpenDlg.m_pOFN->lpstrTitle=_T("Text File");
  fOpenDlg.m_pOFN->lpstrInitialDir=_T("h:");

  if(fOpenDlg.DoModal() == IDOK)
  {
    // Do something useful here
    m_ComboQFile.SetWindowText(fOpenDlg.GetPathName());
    if (ButtonDisabled) {
        m_ButtonDwn.EnableWindow();
        ButtonDisabled = FALSE;
    }
  }
}

void MainFrame::OnBrowseButtonFolderClick() {
  BROWSEINFO bi;
    ZeroMemory(&bi, sizeof(bi));
    TCHAR   szDisplayName[MAX_PATH];
    szDisplayName[0] = _T(' ');

    bi.hwndOwner        =   NULL;
    bi.pidlRoot         =   NULL;
    bi.pszDisplayName   =   szDisplayName;
    bi.lpszTitle        =   _T("Select destination folder of downloaded files");
    bi.ulFlags          =   BIF_RETURNONLYFSDIRS;
    bi.lParam           =   NULL;
    bi.iImage           =   0;

    LPITEMIDLIST   pidl   =   SHBrowseForFolder(&bi);
    TCHAR   szPathName[MAX_PATH];
    if   (NULL   !=   pidl)
    {
      BOOL bRet = SHGetPathFromIDList(pidl, szPathName);
      if(FALSE == bRet)
          return ;

      m_ComboDestDir.SetWindowText(szPathName);
    }
}

void MainFrame::OnDwnButtonClickDownload() {
  CStdioFile myFile;
  CString QueueFilePath, DestDirPath;
  CFileException fileException;
  CString FileURL;

  m_ComboQFile.GetWindowText(QueueFilePath);
  m_ComboDestDir.GetWindowText(DestDirPath);

  if ( GetFileAttributes( QueueFilePath ) == INVALID_FILE_ATTRIBUTES ) {
    MessageBox(_T("The file path you entered is not valid. Enter valid file path."));
    return ;
  }

  DWORD attrib = GetFileAttributes(DestDirPath);

  if ((attrib == INVALID_FILE_ATTRIBUTES) || (attrib & FILE_ATTRIBUTE_DIRECTORY) == 0 ) {
    MessageBox(_T("The destination directory is not valid. Select a valid folder."));
    return ;
  }

  // Read file URLS
  // Input text file is properly delimetered
  MessageBox(_T("Input file is valid."));

  if ( !myFile.Open( QueueFilePath, CFile::modeRead | CFile::typeText, &fileException ) ) {
    TRACE( "Can't open file %s, error = %u\n", QueueFilePath, fileException.m_cause );
  }

  while(myFile.ReadString(FileURL)) {
    if (FileURL.IsEmpty())
      continue;

    // Remove 'http://' from URL to get base URL
    m_Label_Message.SetWindowText(_T("Processing ") + FileURL);

    if (FileURL.Find(_T("http://")) == 0)
      FileURL.Delete(0, 7);

    // MessageBox(FileURL);
    DownloadFile(FileURL, DestDirPath);
  }

}

void MainFrame::DownloadFile(CString URL, CString& DestDir) {
  CInternetSession MyInternetSession;
  CHttpConnection *MyHttpConnection=NULL;
  CString ServerURL = _T("github.com");
  CHttpFile *pFile=NULL;
  CString sHeaders= _T("Accept: text/*\\r\\n\
          User-Agent: FFTSys DN Agent 0.01\\r\\n\
          Content-Type: application/x-www-form-urlencoded\\r\\n");

  // Example URL for test
  //  https://github.com/openssh/openssh-portable/archive/refs/tags/V_9_1_P1.zip
  CString pszFileName;
  CString tempFileName = _T("D:\\Doc\\openssh-9.1.P1.zip");
  CString InfoStr;
  CString& pObjectStr = URL;
  CFile myFile;
  CFileException fileException;

  // Extract only domain name
  int pos = URL.Find('/');
  ServerURL = URL.Left(pos);
  if (ServerURL.Find(_T("github.com")) >= 0) {
    URL.Delete(0, pos);
    pos = pObjectStr.ReverseFind('/');
    int len = pObjectStr.GetLength();
    pszFileName = pObjectStr.Right(len - pos -1);
    pszFileName = DestDir + pszFileName;
    pObjectStr += _T("/index.html");
    MessageBox(pszFileName);


    if ( !myFile.Open( tempFileName, CFile::modeCreate |
      CFile::modeWrite, &fileException ) ) {
      TRACE( "Can't open file %s, error = %u\n", pszFileName, fileException.m_cause );
    }

    try {
      m_Label_Message.SetWindowText(_T("Connecting ") + ServerURL);
      MyHttpConnection = MyInternetSession.GetHttpConnection(ServerURL, 80, _T(""), _T(""));
      pFile = MyHttpConnection->OpenRequest(CHttpConnection::HTTP_VERB_GET, pObjectStr);

      // dFile->SenSendRequest(sHeaders, (LPVOID)(LPCSTR)sFormData, sFormData.GetLength());
      if (pFile->SendRequest(sHeaders) == TRUE ) {
        DWORD dwreturn ;
        pFile->QueryInfoStatusCode (dwReturn);

        if (dwReturn == HTTP_STATUS_OK) {
          char szBuffer [1024];
          UINT nRead, total = 0;

          do {
            nRead = pFile->Read(szBuffer, 1023);
            total += nRead;
            InfoStr.Format(_T("Total Downloaded %u bytes"), total);
            m_Label_Message.SetWindowText(InfoStr);
            myFile.Write(szBuffer, nRead);
            // CString strBuffer = szBuffer;
            // pMainWnd->MessageBox(strBuffer);
          } while (nRead >0 );

          MessageBox(_T("index.html fetched"));
        }
        else {
          // MessageBox(_T("Status not OK"));
        }
      }

      // pMainWnd->MessageBox(_T("passed"));
    }
    catch (CInternetException *e) {
      if (e)
        e->ReportError();
    }

    // Clean Up Resources
    delete pFile;
    pFile = 0;
    MyInternetSession.Close();
  }
}


// Commented out and not used right now
void CALLBACK EXPORT MainFrame::TimerProc(HWND hWnd, UINT nMsg, UINT nTimerID, DWORD dwTime) {
  // Code
  MainFrame* pMainWnd = (MainFrame*) AfxGetMainWnd ();
  pMainWnd->KillTimer(ID_TIMER);

  // Process downloads
  CInternetSession MyInternetSession;
  CHttpConnection *MyHttpConnection = NULL;

  CString ServerURL = _T("github.com");
  CHttpFile *pFile = NULL;
  CString sHeaders= _T("Accept: text/*\\r\\n\
             User-Agent: FFTSys DN Agent 0.01\\r\\n\
             Content-Type: application/x-www-form-urlencoded\\r\\n");

  CString pszFileName = ".\\myfile.html";
  CFile myFile;
  CFileException fileException;

  if ( !myFile.Open( pszFileName, CFile::modeCreate |
    CFile::modeReadWrite, &fileException ) ) {
    TRACE( "Can't open file %s, error = %u\n", pszFileName, fileException.m_cause );
  }

  try {
    MyHttpConnection = MyInternetSession.GetHttpConnection(ServerURL, 80, _T(""), _T(""));
    pFile = MyHttpConnection->OpenRequest(CHttpConnection::HTTP_VERB_GET, _T("/openssh/openssh-portable/archive/refs/tags/V_9_1_P1.zip"));

    // dFile->SenSendRequest(sHeaders, (LPVOID)(LPCSTR)sFormData, sFormData.GetLength());

    if (pFile->SendRequest(sHeaders) == TRUE ) {
      DWORD dwreturn ;
      pFile->QueryInfoStatusCode (dwReturn);

      if (dwReturn == HTTP_STATUS_OK) {
        // char szBuffer[2048];
        // UINT nRead;

        // do {
        //   nRead = pFile->Read(szBuffer, 2047);
        //   myFile.Write(szBuffer, nRead);
        //   // CString strBuffer = szBuffer;
        //   // pMainWnd->MessageBox(strBuffer);
        // } while (nRead > 0);

        // pMainWnd->MessageBox(_T("passed"));
      }
      else {
        pMainWnd->MessageBox(_T("Status not OK"));
      }
    }

    // pMainWnd->MessageBox(_T("passed"));
  }
  catch (CInternetException *e) {
    if (e)
      e->ReportError();
  }

  delete pFile;
  pFile = 0;
  MyInternetSession.Close();
}

// Body of Window initialization function
BOOL CSApp::InitInstance() {
  m_pMainWnd = new MainFrame ;
  m_pMainWnd->ShowWindow(SW_SHOW);
  m_pMainWnd->UpdateWindow();

  return TRUE;
}

// Creating an instance of Main Window Class
CSApp theApp;
