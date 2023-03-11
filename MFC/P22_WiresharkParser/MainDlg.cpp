// Primary Dialog box / Window
//

#include "stdafx.h"
#include "Main.h"
#include "MainDlg.h"
#include "afxdialogex.h"
#include "ParserUtils.h"

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


// WSPDlg dialog
WSPDlg::WSPDlg(CWnd* pParent /*=NULL*/)
  : CDialogEx(WSPDlg::IDD, pParent)
  , m_SignalingHeaderLength(14),   m_stunKeysCount(0)
{
  m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void WSPDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
  DDX_Text(pDX, IDC_INPUTEDIT, m_InputText);
  DDX_Text(pDX, IDC_EDIT1, m_SignalingHeaderLength);
}

BEGIN_MESSAGE_MAP(WSPDlg, CDialogEx)
  ON_WM_SYSCOMMAND()
  ON_WM_PAINT()
  ON_WM_QUERYDRAGICON()
  ON_WM_QUERYDRAGICON()
  ON_WM_DROPFILES()
  ON_EN_UPDATE(IDC_FILEBROWSE, &WSPDlg::OnEnUpdateMfceditbrowse1)
  ON_BN_CLICKED(IDC_PARSEBTN, &WSPDlg::OnBnClickedParsebtn)
  ON_NOTIFY(NM_CLICK, IDC_SETTINGS, &WSPDlg::OnNMClickSettings)
END_MESSAGE_MAP()


// WSPDlg message handlers
BOOL WSPDlg::OnInitDialog()
{
  CDialogEx::OnInitDialog();

  // Initializations
  IsFileLoadOnProgress = FALSE;
  IsParsingOnProgress = FALSE;

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
  CEdit *InputEdit = (CEdit *) GetDlgItem(IDC_INPUTEDIT);
  InputEdit->SetLimitText(600000);
  // InputEdit->LimitText(60000);

  return TRUE;  // return TRUE  unless you set the focus to a control
}

void WSPDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void WSPDlg::OnPaint()
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
HCURSOR WSPDlg::OnQueryDragIcon()
{
  return static_cast<HCURSOR>(m_hIcon);
}


void WSPDlg::UpdateEditControlFromFile(CString FilePath) {
  // FilePath must exist
  if (IsFileLoadOnProgress == FALSE) {
    CWaitCursor wait;
    CFile wscapFile;  // Wireshark capture file
      CHAR szBuffer[600000];
      // Notify File Load on Progress
      SetDlgItemText(IDC_INPUTLOADSTATUS, _T("[Loading file..]"));
      IsFileLoadOnProgress = TRUE;
      // open file and load into textbox
      if ( wscapFile.Open(FilePath, CFile::modeRead) ) {
        int nActual = wscapFile.Read(szBuffer, sizeof(szBuffer)-1);
        szBuffer[nActual] = NULL;
        //MessageBox(_T("Content of file: ") + CString(szBuffer));
        if (nActual>0) 
          SetDlgItemText(IDC_INPUTEDIT, CString(szBuffer));
      }
      wscapFile.Close();
      IsFileLoadOnProgress = FALSE;
      SetDlgItemText(IDC_INPUTLOADSTATUS, _T("[Loading complete]"));
      wait.Restore();
  }
}

void WSPDlg::OnEnUpdateMfceditbrowse1()
{
  // TODO:  If this is a RICHEDIT control, the control will not
  // send this notification unless you override the CDialogEx::OnInitDialog()
  // function to send the EM_SETEVENTMASK message to the control
  // with the ENM_UPDATE flag ORed into the lParam mask.

  // TODO:  Add your control notification handler code here
  CString FBText;  // Filebrowse text
  GetDlgItemText(IDC_FILEBROWSE, FBText);
  if (doesFileExist(FBText))
    WSPDlg::UpdateEditControlFromFile(FBText);
}


void WSPDlg::OnBnClickedParsebtn()
{
  // TODO: Add your control notification handler code here
  // Data exchange and validation
  UpdateData(TRUE);
  if (IsParsingOnProgress == FALSE) {
    IsParsingOnProgress = TRUE;
    SetDlgItemText(IDC_OUTPUTSTATUS, _T("[Parsing. Please wait..]"));
    GetDlgItemText(IDC_INPUTEDIT, m_InputText);
    
    if (m_InputText == _T("")) {
      MessageBox(_T("Empty input!"));
    }
    else {
      CWaitCursor wait;
      ParseWiresharkUDP();
      wait.Restore();

      SetDlgItemText(IDC_OUTPUTEDIT, m_OutputText);
    }
    IsParsingOnProgress = FALSE;
    SetDlgItemText(IDC_OUTPUTSTATUS, _T("[Parsing is done.]"));
  }
}

// Load the file when a file is dragged and dropped
void WSPDlg::OnDropFiles(HDROP hDropInfo) {
  LPTSTR FPath;
  UINT Length = DragQueryFile(hDropInfo, 0, 0, 0);
  if (Length == 0) {
    MessageBox(_T("Drag file: an error ocurred."));
    return ;
  }

  // Remember to avoid memory leak
  FPath = new TCHAR[Length+1];
  Length = DragQueryFile(hDropInfo, 0, FPath, Length+1);
  if (Length == 0) {
    MessageBox(_T("Drag file: another error ocurred."));
    return ;
  }

  // It will automatically update the input edit control
  SetDlgItemText(IDC_FILEBROWSE, FPath);

  // UpdateEditControlFromFile(FPath);
  DragFinish(hDropInfo);
  delete FPath;
}

void WSPDlg::ParseWiresharkUDP() {
  CString LineStr;
  int i = 0;
  int len;
  int linetype;
  CString temp;
  int SN = 0;
  int TotalBytes;

  TCHAR TimeStamp[20];
  TimeType PreTime = {0, 0, 0, 0}, CurTime;
  CString SourceIP, DestIP, DataSegment, DecryptData;
  m_OutputText = _T("");

  while (AfxExtractSubString(LineStr, m_InputText, i)) {
    i++;

    len = LineStr.GetLength();
    linetype = GetLineType((LPCTSTR)LineStr, len);
    // temp.Format(_T("Got linetype %d\r\n"), linetype);
    // m_OutputText += temp;

    switch(linetype) {
    case 1:        // 1 is timestamp line
      SN++;
      temp.Format(_T("%04d:"), SN);
      m_OutputText += temp;

      // get and write timestamp
      GetTimeStamp((LPTSTR) &TimeStamp, (LPCTSTR) LineStr);
      m_OutputText += "\t";
      m_OutputText += TimeStamp;

      // write timestamp diff
      // First time pretimeval will acquire newtimeval
      if (PreTime.milisec == 0) {
        LoadTime((LPTSTR) &TimeStamp, &CurTime);
        CopyTime(&PreTime, &CurTime);
      }
      else {
        LoadTime(TimeStamp, &CurTime);
      }

      // WriteTime(&CurTime);
      // WriteTime(&PreTime);
      // CopyTime(&TempTime, &PreTime);
      // CopyTime(&PreTime, &CurTime);
      // SubtractTime(&CurTime, &TempTime);
      SubtractTime(&CurTime, &PreTime);
      temp.Format(_T("\t%02d:%02d:%02d,%03d"), CurTime.hour, CurTime.minute, CurTime.second, CurTime.milisec);
      m_OutputText += temp;
      break;

    case 2:        // Data line
      if (IsUDPPacket((LPCTSTR) LineStr, len)) {
        // Get the source IP address and write to file
        SourceIP = GetIPAddress(LineStr, len, 1);
        m_OutputText += _T("\t");
        m_OutputText += SourceIP;

        // Get the destination IP address and write to file
        DestIP = GetIPAddress(LineStr, len, 2);
        m_OutputText += _T("\t");
        m_OutputText += DestIP;

        TotalBytes = (len - 133) / 3;
        temp.Format(_T("\t%d"), TotalBytes);
        m_OutputText += _T("\t");
        m_OutputText += temp;

        // Possible signaling packet if length is greater than 150
        if (TotalBytes > 150) {
          // Get data and write to file
          DataSegment = GetDataSegment((LPCTSTR) LineStr, len);

          if ((LPCTSTR) DataSegment != NULL) {
            m_OutputText += _T("\r\n");

            // m_OutputText += _T("\r\nData: ");
            // m_OutputText += DataSegment;
            // m_OutputText += _T("\r\n");

            // Decrypt data segment
            DecryptData = DecryptSignaling(DataSegment, m_SignalingHeaderLength,   m_stunKeysCount, m_StunKeys);
            m_OutputText += DecryptData;
            m_OutputText += _T("\r\n\r\n");
          }
        }
      }

      m_OutputText += _T("\r\n");
      break;

    default:
      break;
    }
  }
}


void WSPDlg::OnNMClickSettings(NMHDR *pNMHDR, LRESULT *pResult)
{
  *pResult = 0;

  #ifdef STUN_KEYS_ENABLED
  StunKeySettings SettingsDialog;
  if (SettingsDialog.DoModal() == IDOK) {
    // Process here..
    GetKeyInfo(&SettingsDialog);

    // CString Temp;
    // Temp.Format(_T("Number of keys: %d"),   m_stunKeysCount);
    // MessageBox(Temp);
    //
    // for (int i=0; i<  m_stunKeysCount; i++) {
    //   Temp.Format(_T("Key: %d"), m_StunKeys[i]);
    //   MessageBox(Temp);
    // }
  }
  #endif
}

#ifdef STUN_KEYS_ENABLED
void WSPDlg::GetKeyInfo(StunKeySettings *keydlgobj) {
  m_stunKeysCount = keydlgobj->NumberOfKeys;
  memcpy(m_StunKeys, keydlgobj->StunKeys, /*sizeof(int) *   m_stunKeysCount*/ sizeof(keydlgobj->StunKeys));
}
#endif