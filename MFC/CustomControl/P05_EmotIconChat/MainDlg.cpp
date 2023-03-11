
// MainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Main.h"
#include "MainDlg.h"
#include "EmoListPopUp.h" // for emo pop up
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMainDlg dialog
CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
  : CDialog(CMainDlg::IDD, pParent),
  m_emoListPopUpDlg(NULL),
  m_ChatEmoBox(this)
  // isMinimized(false)
{
  m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
  if (! emoPopUpBmp.LoadBitmaps(_T("IDB_BMP_EMOPOP_UP"), _T("IDB_BMP_EMOPOP_DOWN"), _T("IDB_BMP_EMOPOP_FOCUS"), _T("IDB_BMP_EMOPOP_UP"))) {
  // require definition in resource.h
  //if (! emoPopUpBmp.LoadBitmaps(IDB_BMP_EMOPOP_UP, IDB_BMP_EMOPOP_DOWN, IDB_BMP_EMOPOP_FOCUS, IDB_BMP_EMOPOP_UP)) {
    AfxMessageBox(_T("Failed to load bitmaps for buttons\n"));
    AfxThrowResourceException();
  }

  static TCHAR *EmoCodesTmp[EMO_MAX_NO] = {_T(":)"), _T(":("), _T(":D"), _T(":P"), _T(":S"), _T(":O"), _T(":@"), _T(":-["), _T(":-]"), _T(":|"),    
        _T(":'("), _T(":>"), _T(":3"), _T(":*"), _T(":V"), _T(":/"), _T(";)"), _T(">:("), _T(">:O"), _T("8)"), _T("8|"), _T("O.o"),        // starting index = 10
        _T("O:)"), _T("3:)"), _T("L(\")"), _T("L3"), _T(":))"), _T(":Z"), _T(":POOP"), _T(":$"), _T(":0"), _T("::3"), _T(":4"),          // starting index = 22
        _T(":-h"), _T(":6"), _T(":8"), _T(":9"), _T(":12"), _T(":-?"), _T("(Y)"), _T(":54"), _T(":56"), _T(":60"), _T(":67"),          // starting index = 33
        _T(":72"), _T(":88"), _T("=((")};                  // starting index = 44

  static TCHAR *EmoToolTipTextTmp[EMO_MAX_NO] = {_T("Smile"), _T("Sad"), _T("Laugh"), _T("Cheeky"), _T("Worried"), _T("Surprised"), _T("Angry"), _T("Love"), _T("Vampire"), _T("Straight Face"),
        _T("Cry"), _T("Blush"), _T("Curly Lips"), _T("Kiss"), _T("Pacman "), _T("Uncertain"), _T("Wink"), _T("Grumpy"), _T("Upset"), _T("Glass"), _T("Sunglass"), _T("Confused"),
        _T("Angel"), _T("Devil"), _T("Penguin"), _T("Heart"), _T("Laugh"), _T("Sleepy"), _T("Poop"), _T("Embarassed"), _T("Leaps are sealed"), _T("Tear on on eye"), _T("Giggle"),
        _T("Wave hands"), _T("Hammer"), _T("Pig"), _T("Rose"), _T("Hush"), _T("Thinking"), _T("Thumbs up"), _T("Thumbs down"), _T("Victory"), _T("Birthday Cake"), _T("Tea"),
        _T("Fist"), _T("Bored"), _T("Broken Heart")};

  for (int i=0;i<EMO_MAX_NO; i++) {
    EmoCodes[i] = EmoCodesTmp[i];
    EmoToolTipText[i] = EmoToolTipTextTmp[i];
  }
}

CMainDlg::~CMainDlg() {
  
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_CHATCUSTOM, m_ChatEmoBox);
  DDX_Control(pDX, IDC_EDIT_CHAT_IN, m_chatBoxEditCtrl);
  DDX_Control(pDX, IDC_EMOPOP, emoPopUpBmp);
}

BEGIN_MESSAGE_MAP(CMainDlg, CDialog)
  ON_WM_SYSCOMMAND()
  ON_WM_PAINT()
  ON_WM_QUERYDRAGICON()
  ON_BN_CLICKED(IDOK, &CMainDlg::OnBnClickedOk)
  //ON_WM_SIZE()
  ON_WM_GETMINMAXINFO()
  ON_BN_CLICKED(IDC_EMOPOP, &CMainDlg::OnBnClickedEmoPop)
  ON_WM_SETFOCUS()
  ON_WM_ACTIVATE()
  //ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


// CMainDlg message handlers

BOOL CMainDlg::OnInitDialog()
{
  CDialog::OnInitDialog();

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

  // each dialog control has special bitmaps
  // emoPopUpBmp.AutoLoad(IDC_EMOPOP, this);

  //emoPopUpBmp.SizeToContent();
  /*
  tool tip experiment
  m_pTooltip = new CToolTipCtrl;
  if(!m_pTooltip->Create(this, WS_POPUP|TTS_ALWAYSTIP))
    {
        TRACE("Unable To create ToolTip\n");
        return TRUE;
    }
  // ref, MFC CToolTipCtrl
  // The lpRectTool and nIDTool parameters must both be valid, or if lpRectTool is NULL, nIDTool must be 0.
  //VERIFY(m_pTooltip->AddTool(&buttonTest, _T("smileee text over here unbelievable!!!")));

  CWnd *pBWnd = GetDlgItem(IDC_EDIT_CHAT_IN);
  VERIFY(m_pTooltip->AddTool(pBWnd, _T("smileee text over here unbelievable!!!")));
  pBWnd = GetDlgItem(IDOK);
  VERIFY(m_pTooltip->AddTool(pBWnd, _T("smileee text over here unbelievable!!!")));
  //this->EnableToolTips();
  // ref, https://learn.microsoft.com/en-us/cpp/mfc/reference/ctooltipctrl-class
  m_pTooltip->Activate(TRUE);
  */

  // Load history from database and update charbox

  // Test Insertion of information
  // primarily important operation here is to sent the text and print
  // CTime timeDate = CTime::GetCurrentTime();
  // m_ChatEmoBox.PostChatMessage(TEXT("testing 1"), timeDate);
  // m_chatBoxEditCtrl.SetWindowText(_T(""));

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
    CDialog::OnSysCommand(nID, lParam);
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
    CDialog::OnPaint();
  }
}


// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMainDlg::OnQueryDragIcon()
{
  return static_cast<HCURSOR>(m_hIcon);
}

void CMainDlg::OnBnClickedOk()
{
  CString m_chInText;    // chat input text
  // CEdit *chatBoxEditCtrl = (CEdit *) GetDlgItem(IDC_EDIT_CHAT_IN);
  //if (chatBoxEditCtrl == NULL)
    //return ;
  //chatBoxEditCtrl->GetWindowText(m_chInText);
  m_chatBoxEditCtrl.GetWindowText(m_chInText);
  //GetDlgItemText(IDC_EDIT_CHAT_IN, m_chInText);
  if (m_chInText.GetLength() > 0) {
    // primarily important operation here is to sent the text and print
    CTime timeDate = CTime::GetCurrentTime();
    // CTimeSpan tz(0, 6, 0, 0);  // for timezone
    // timeDate += tz;
    m_ChatEmoBox.PostChatMessage(m_chInText, timeDate);
    //m_emoListControl.InsertItemEmo(n, m_chInText);
    //ATLASSERT(s == _T("Friday, March 19, 1999"));   
    // m_emoListControl.SetItemText(n, 1, tmStr);
    //SetDlgItemText(IDC_EDIT_CHAT_IN, _T(""));
    m_chatBoxEditCtrl.SetWindowText(_T(""));
  }
  GotoDlgCtrl(&m_chatBoxEditCtrl);    // ref: http://blogs.msdn.com/b/oldnewthing/archive/2004/08/02/205624.aspx
  // No need to destroy now
  // CDialog::OnOK();
}

/* Bug fix 1: Minimize bug
 *  OnSize here changes the co-ordinates and dimenstions of our custom chat control
 *  changed width affect rcClip that is calculated during AddChatItemToPaintElements
 *  therefore dimensions are overlapped those paint elements and doesn't get drawn correctly
 */
void CMainDlg::OnSize(UINT nType, int cx, int cy)
{
  CDialog::OnSize(nType, cx, cy);
  // invalidate if minimized to fix bug, it didn't fix the bug; let's try more
  /*if (nType == SIZE_MINIMIZED)      // ref: http://msdn.microsoft.com/en-us/library/windows/desktop/ms632646(v=vs.85).aspx
  {  //m_ChatEmoBox.Repaint();
    isMinimized = true;
  }*/
  if (cx==0 && cy==0)
    return ;
  /*CRect rc;
  GetWindowRect(&rc);
  ClientToScreen(rc);
  CString dbgStr;
  dbgStr.Format(TEXT("cx = %d, cy = %d, width = %d, height = %d"), cx, cy, rc.Width(), rc.Height());
  AfxMessageBox(dbgStr, MB_OK);*/

  // TODO: Add your message handler code here
  // resize custom control
  // AfxMessageBox(TEXT("we are in dlg size"), MB_OK);

  // Resize edit to fill the whole view. 
   // OnSize can be called before OnInitialUpdate 
   // so make sure the edit control has been created. 
   if (::IsWindow(m_ChatEmoBox.GetSafeHwnd()))
   {
    int xEmoBox = cx/15;
    int yEmoBox = cy/15;
    int cxEmoBox = cx * 13 / 15;
    int cyEmoBox = cy * 343 / 600 - 21 / 2;
    m_ChatEmoBox.MoveWindow (xEmoBox, yEmoBox, cxEmoBox, cyEmoBox);

    /*if (nType == SIZE_RESTORED) {
      m_ChatEmoBox.Repaint();
      isMinimized = false;
    }*/
   }

  CEdit *chatBoxEditCtrl = (CEdit *) GetDlgItem(IDC_EDIT_CHAT_IN);
  if (chatBoxEditCtrl == NULL)
    return ;
    if (::IsWindow(m_chatBoxEditCtrl.GetSafeHwnd()))
  {
    int xEditBox = cx/15;
    int yEditBox = cy * 413 / 600 - 21 / 2;
    int cxEditBox = cx * 13 / 15;
    int cyEditBox = cy * 49 / 200 - 21 / 2;
    m_chatBoxEditCtrl.MoveWindow (xEditBox, yEditBox, cxEditBox, cyEditBox);
  }

   CButton *buttonCtl = (CButton *) GetDlgItem(IDOK);
  if (buttonCtl == NULL)
    return ;

   if (::IsWindow(buttonCtl->GetSafeHwnd()))
   {
    int xButton = cx*14/15 - 80;
    int yButton = cy * 29 / 30 - 21;
    int cxButton = 80;
    int cyButton = 25;
    buttonCtl->MoveWindow (xButton, yButton, cxButton, cyButton);
   }
}


void CMainDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
  // TODO: Add your message handler code here and/or call default
  lpMMI->ptMinTrackSize.x = 480;
  lpMMI->ptMinTrackSize.y = 270;
  CDialog::OnGetMinMaxInfo(lpMMI);
}


void CMainDlg::OnBnClickedEmoPop()
{
  // TODO: Add your control notification handler code here
  // modeless dialog creation ref: http://www.codeproject.com/Articles/1651/Tutorial-Modeless-Dialogs-with-MFC
  if (m_emoListPopUpDlg == NULL) {
    m_emoListPopUpDlg = new CEmoListPopUp(this);
    m_emoListPopUpDlg->Create(CEmoListPopUp::IDD);
    m_emoListPopUpDlg->ShowWindow(SW_SHOW);
  }
  /*else {
    delete m_emoListPopUpDlg;
    m_emoListPopUpDlg = NULL;
  }*/
}


void CMainDlg::OnSetFocus(CWnd* pOldWnd)
{
  CDialog::OnSetFocus(pOldWnd);

  // TODO: Add your message handler code here
  // destroy emo pop up
  DestroyEmoPopUpDlg();
}

// ref: http://msdn.microsoft.com/en-us/library/1f31c334(v=vs.90).aspx
void CMainDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
  CDialog::OnActivate(nState, pWndOther, bMinimized);

  // TODO: Add your message handler code here
  // messages ref: http://msdn.microsoft.com/en-us/library/windows/desktop/ms646274(v=vs.85).aspx
  if (nState==WA_CLICKACTIVE && m_emoListPopUpDlg /*&& pWndOther != m_emoListPopUpDlg*/) {
    // m_emoListPopUpDlg->ShowWindow(SW_HIDE);
        //AfxMessageBox(_T("we are here"));
    DestroyEmoPopUpDlg();
    GotoDlgCtrl(&m_ChatEmoBox);
  }
}

void CMainDlg::DestroyEmoPopUpDlg(bool CalledFromEmoClass) {
  if (m_emoListPopUpDlg) {
    if (CalledFromEmoClass == false)
      delete m_emoListPopUpDlg;
    m_emoListPopUpDlg = NULL;
  }
}

void CMainDlg::InsertEmoCode(int emoCodeIndex) {
  DWORD caretPos = m_chatBoxEditCtrl.GetSel();  // ref: http://msdn.microsoft.com/en-us/library/1hyt7tyx(v=vs.110).aspx
  CString m_ChatText;
  m_chatBoxEditCtrl.GetWindowText(m_ChatText);
  // AfxMessageBox(m_ChatText);
  CString emocode(EmoCodes[emoCodeIndex]);
  emocode += _T(" ");
  m_ChatText.Insert(HIWORD(caretPos), emocode);
  m_chatBoxEditCtrl.SetWindowText(m_ChatText);

  // go to control first
  GotoDlgCtrl(&m_chatBoxEditCtrl);
  // then set caret position
  m_chatBoxEditCtrl.SetSel(HIWORD(caretPos)+emocode.GetLength(), LOWORD(caretPos)+emocode.GetLength());
}

// Purpose of this function is to return tooltip text
CString CMainDlg::GetEmoToolTipText(int index) {
  return CString(EmoToolTipText[index]) + _T("   ") + CString(EmoCodes[index]);
}

// Purpose of this function is to return array of emo code
TCHAR** CMainDlg::GetEmoCodeList() {
  return EmoCodes;
}

// Purpose of this function is to return array of emo code
int CMainDlg::GetEmoCount() {
  return EMO_MAX_NO;
}


BOOL CMainDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
  // TODO: Add your message handler code here and/or call default
  //AfxMessageBox(_T("we are on mouse wheel parent"));
  // have to handle it after implementing message delivery status display implementation

  return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}

/*void CMainDlg::PostNcDestroy()
{
  CDialog::PostNcDestroy();
  if(m_pParent)
  {    
    ((CModelessDemoDlg*)m_pParent)->m_pmodeless = NULL;    
  }
  delete this;
}
*/

// Functions implemented 
// Function SetBuddy not required
void CMainDlg::SetBuddy(ContactInfo m_buddy)
{
  buddy = m_buddy;
}
