
// MainDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "ChatHistory.h"


// CMainDlg Dialog
class CMainDlg : public CDialogEx
{
// Construction
public:
  CMainDlg(CWnd* pParent = NULL);  // standard constructor

// Dialog Data
  enum { IDD = IDD_MAIN_DIALOG };

protected:
  virtual void DoDataExchange(CDataExchange* pDX);  // DDX/DDV support


// Implementation
protected:
  HICON m_hIcon;
  ChatHistory m_chathistory;

  // Generated message map functions
  virtual BOOL OnInitDialog();
  afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
  afx_msg void OnPaint();
  afx_msg HCURSOR OnQueryDragIcon();
  
  void OnOK();
  DECLARE_MESSAGE_MAP()


public:
  CEdit   m_editMsgToSend;
  afx_msg void OnBnClickedSend();
  afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
