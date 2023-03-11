// EmoListPopUp.cpp : implementation file
//

#include "stdafx.h"
#include "Main.h"
#include "EmoListPopUp.h"
// #include "xSkinButton.h"
// #include "afxdialogex.h"


// CEmoListPopUp dialog
IMPLEMENT_DYNAMIC(CEmoListPopUp, CDialogEx)

CEmoListPopUp::CEmoListPopUp(CMainDlg* pDlg, CWnd* pParent)
  : CDialogEx(CEmoListPopUp::IDD, pParent),
  m_pChatBoxDlg(pDlg),
  selectedEmoIndex(-1)
{
  for (int i=0; i<EMO_MAX_NO; i++)
    m_ButtonEmo[i] = new CBitmapButton();

  for (int i=0; i<EMO_MAX_NO; i++)
  if (! m_ButtonEmo[i]->LoadBitmaps(IDB_BMP_EMOTICON_01+i, IDB_BMP_EMOTICON_01+i, IDB_BMP_EMOTICON_01+i, IDB_BMP_EMOTICON_01+i)) {
    AfxMessageBox(_T("Failed to load bitmaps for buttons\n"));
    AfxThrowResourceException();
  }
}

CEmoListPopUp::~CEmoListPopUp()
{
  for (int i=0; i<EMO_MAX_NO; i++)
    delete m_ButtonEmo[i];
  // Uninstall the WH_GETMESSAGE hook function.
     //VERIFY (::UnhookWindowsHookEx (hHook));

  delete m_pToolTipCtrl;
}

void CEmoListPopUp::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
  for (int i=0; i<EMO_MAX_NO; i++)
    //DDX_Control(pDX, IDC_BUTTON_EMO01+i, m_ButtonEmo[i]);
    DDX_Control(pDX, IDC_BUTTON_EMO01+i, *m_ButtonEmo[i]);

  //DDX_Control(pDX, IDC_BUTTON_TEST, m_ButtonTest);
}

BOOL CEmoListPopUp::OnInitDialog()
{
  CDialogEx::OnInitDialog();

  m_pToolTipCtrl = new CToolTipCtrl();
  if(!m_pToolTipCtrl->Create(this, TTS_ALWAYSTIP)) {
           TRACE("Unable To create ToolTip\n");
           return TRUE;
    }

  for (int i=0; i<EMO_MAX_NO; i++) {
    // doesn't work without PreTranslateMessage
    //if (m_pToolTipCtrl->AddTool(&m_ButtonEmo[i],CString(EmoToolTipText[i]) + _T("   ") + CString(EmoCodes[i])))
    if (m_pToolTipCtrl->AddTool(m_ButtonEmo[i],m_pChatBoxDlg->GetEmoToolTipText(i)))
      TRACE("Unable to add Dialog to the tooltip\n");
  }

  m_pToolTipCtrl->Activate(TRUE);

  /*for (int i=0; i<EMO_MAX_NO; i++) {
    m_ButtonEmo[i]->SetEnableText(0);
    m_ButtonEmo[i]->SetToolTipText(CString(EmoToolTipText[i]) + _T("   ") + CString(EmoCodes[i]));
    m_ButtonEmo[i]->SetSkin(IDB_BMP_EMOTICON_01+i,IDB_BMP_EMOTICON_01+i,IDB_BMP_EMOTICON_01+i,0,IDB_BMP_EMOTICON_01+i,0,0,0,0);
  }

  /*m_ButtonEmo.SetEnableText(0);
  m_ButtonEmo.SetToolTipText(_T("3"));
  m_ButtonEmo.SetSkin(IDB_BMP_EMOTICON_01,IDB_BMP_EMOTICON_01,IDB_BMP_EMOTICON_01,0,IDB_BMP_EMOTICON_01,0,0,0,0);

  //if (m_ButtonEmo->GetBitmap() == NULL)
    //m_ButtonEmo->SetBitmap(::LoadBitmap(NULL, MAKEINTRESOURCE(IDB_BMP_EMOTICON_01)));

  SetTransparentColor(RGB(0xFF, 0xFF, 0xFF));
  EnableEasyMove(FALSE);*/

  return TRUE;  // return TRUE  unless you set the focus to a control
}


BEGIN_MESSAGE_MAP(CEmoListPopUp, CDialogEx)
  // ON_WM_KILLFOCUS()
  //ON_WM_CTLCOLOR()
  ON_WM_ERASEBKGND()
  // ref, MFC - Handlers for Message-Map Ranges
  ON_CONTROL_RANGE(BN_CLICKED, IDC_BUTTON_EMO01, IDC_BUTTON_EMO47, &OnButtonEmoClicked)
  ON_WM_ACTIVATE()
END_MESSAGE_MAP()


// CEmoListPopUp message handlers
void CEmoListPopUp::OnKillFocus(CWnd* pNewWnd)
{
  CDialogEx::OnKillFocus(pNewWnd);

  /*// TODO: Add your message handler code here
  // AfxMessageBox(_T("test"), MB_OK);
  ShowWindow(SW_HIDE);
  //OnCancel();
  delete this;*/
}

// ref, old support kb http://support.microsoft.com/kb/141758
//  restored at: https://jeffpar.github.io/kbarchive/kb/141/Q141758/
// Win32 ref, Win32 - How to Create a Tooltip for a Control
BOOL CEmoListPopUp::PreTranslateMessage(MSG* pMsg)
{
  // TODO: Add your specialized code here and/or call the base class
  if (NULL != m_pToolTipCtrl)
            m_pToolTipCtrl->RelayEvent(pMsg);

  return CDialogEx::PreTranslateMessage(pMsg);
}

BOOL CEmoListPopUp::OnEraseBkgnd(CDC* pDC)
{
    CRect rect;
    GetClientRect(&rect);
    CBrush myBrush(RGB(0xFF, 0xFF, 0xFF));    // dialog background color
    CBrush *pOld = pDC->SelectObject(&myBrush);
    BOOL bRes  = pDC->PatBlt(0, 0, rect.Width(), rect.Height(), PATCOPY);
    pDC->SelectObject(pOld);    // restore old brush
    return bRes;                       // CDialog::OnEraseBkgnd(pDC);
}

void CEmoListPopUp::OnButtonEmoClicked(UINT nID) {
  int nButton = nID - IDC_BUTTON_EMO01;
  selectedEmoIndex = nButton;
  m_pChatBoxDlg->InsertEmoCode(selectedEmoIndex);
  m_pChatBoxDlg->DestroyEmoPopUpDlg(true);
  CDialogEx::OnOK();
  /*CString dbg;
  dbg.Format(_T("got click on button %d"), nButton);
  AfxMessageBox(dbg);*/
}


/*void CEmoListPopUp::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
  CDialogEx::OnActivate(nState, pWndOther, bMinimized);

  // messages ref, WM_ACTIVATE
  if (nState==WA_CLICKACTIVE) {
    AfxMessageBox(_T("we are in emo pop up dlg"));
  }
}

// PostNcDestroy not called on destruction
void CEmoListPopUp::PostNcDestroy()
{
  // TODO: Add your specialized code here and/or call the base class
  //m_pChatBoxDlg->DestroyEmoPopUpDlg();

  // AfxMessageBox(_T("Post nc called"));
  m_pChatBoxDlg->DestroyEmoPopUpDlg(true);

  CDialogEx::PostNcDestroy();
}
*/


void CEmoListPopUp::OnCancel()
{
  m_pChatBoxDlg->DestroyEmoPopUpDlg(true);

  CDialogEx::OnCancel();
}


void CEmoListPopUp::OnOK()
{
  // ref, MFC - CDialog
  // no button is selected
  // if a button is selected, save its index and destroy the dialog
  if (selectedEmoIndex >= 0) {
    m_pChatBoxDlg->InsertEmoCode(selectedEmoIndex);
    m_pChatBoxDlg->DestroyEmoPopUpDlg(true);
    CDialogEx::OnOK();
  }
}
