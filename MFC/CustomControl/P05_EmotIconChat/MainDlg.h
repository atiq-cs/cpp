
// MainDlg.h : header file
//

#pragma once
#include "chatcontrol.h"
#include "chatedit.h"
#include "afxext.h"
#include "afxwin.h"

class CEmoListPopUp;    // partial declaration
const int EMO_MAX_NO = 47;


struct ContactInfo
{
  int serial;
  bool isSubscribed;   
  unsigned char buddyName[100], nickName[100], jobTitle[100], email[100], businessNumber[50];
  unsigned char homeNumber[50],mobileNumber[50], m_subscribedUserBasicStatus[10], m_subscribedUserNote[200];
  unsigned char m_subscribeedUserIMStatus[15];
};


// CMainDlg dialog
class CMainDlg : public CDialog
{
// Construction
public:
  CMainDlg(CWnd* pParent = NULL);  // standard constructor
  ~CMainDlg();

// Implementation
  void DestroyEmoPopUpDlg(bool CalledFromEmoClass = false);
  // insert emot icons
  void InsertEmoCode(int emoCodeIndex);
  CString GetEmoToolTipText(int index);
  TCHAR** GetEmoCodeList();
  int GetEmoCount();

protected:
  virtual void DoDataExchange(CDataExchange* pDX);  // DDX/DDV support
  void inline OnCancel() { DestroyWindow(); }
  
  //virtual BOOL PreTranslateMessage(MSG* pMsg);
  // Generated message map functions
  virtual BOOL OnInitDialog();
  afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
  afx_msg void OnPaint();
  afx_msg HCURSOR OnQueryDragIcon();
  virtual void inline PostNcDestroy() { CDialog::PostNcDestroy();  delete this;} 
  DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnBnClickedOk();
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
  afx_msg void OnBnClickedEmoPop();
  afx_msg void OnSetFocus(CWnd* pOldWnd);
  afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
  afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

  enum { IDD = IDD_Main_DIALOG };

  // extra functions IM Demo App inclusion
  void SetBuddy(ContactInfo m_buddy);

// data members
private:
  CChatControl m_ChatEmoBox;
  CChatEdit m_chatBoxEditCtrl;
  CEmoListPopUp *m_emoListPopUpDlg;
  CBitmapButton emoPopUpBmp;

  BOOL m_bDialogDestroyed;    // indicates whether emo pop up dialog is destroyed by On Ok or On Cancel
    // Emo code
  TCHAR *EmoCodes[EMO_MAX_NO];
  TCHAR *EmoToolTipText[EMO_MAX_NO];
  // Tool-tip
  // minimize
  // bool isMinimized;

  // Functions to implement IM Demo App's MessageDialog class
  ContactInfo buddy;

protected:
  HICON m_hIcon;
};
