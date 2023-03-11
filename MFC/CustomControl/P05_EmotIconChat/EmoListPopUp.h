
#pragma once
#include "afxcmn.h"
#include "afxwin.h"
//#include "xSkinButton.h"
//#include "CDialogSK.h"  // for custom dialog sk
#include "MainDlg.h"  // for referene to this dialog

//class CxSkinButton;

//class CMainDlg;

// CEmoListPopUp dialog
class CEmoListPopUp : public CDialogEx
{
  DECLARE_DYNAMIC(CEmoListPopUp)

public:
  CEmoListPopUp(CMainDlg* pDlg, CWnd* pParent = NULL);   // standard constructor
  virtual ~CEmoListPopUp();
  //CMainDlg& m_rChatBoxDlg;

  // Dialog Data
  enum { IDD = IDD_DIALOG_EMOPOP };

private:
  // our private variables
  CBitmapButton* m_ButtonEmo[EMO_MAX_NO];
  CToolTipCtrl* m_pToolTipCtrl;
  CMainDlg* m_pChatBoxDlg;
  int selectedEmoIndex;

protected:
  //LRESULT CALLBACK GetMessageProc(int nCode, WPARAM wParam, LPARAM lParam);
  virtual BOOL OnInitDialog();
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnKillFocus(CWnd* pNewWnd);
  virtual BOOL PreTranslateMessage(MSG* pMsg);
  afx_msg BOOL OnEraseBkgnd(CDC* pDC);
  afx_msg void OnButtonEmoClicked(UINT nID);
  virtual void OnCancel();
  virtual void OnOK();


  //CBrush m_brush;
//public:
  //afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
  //virtual void PostNcDestroy();
};

//LRESULT CALLBACK GetMessageProc(int nCode, WPARAM wParam, LPARAM lParam);
