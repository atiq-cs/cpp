
// MainDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "listctrlemo.h"


// CMainDlg dialog
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

  // Generated message map functions
  virtual BOOL OnInitDialog();
  afx_msg void OnPaint();
  afx_msg HCURSOR OnQueryDragIcon();
  DECLARE_MESSAGE_MAP()
private:
  CListCtrlEmo m_emoListControl;
  void InsertItemEmo(int itemIndex, LPCTSTR m_chatInStr);
//public:
  // afx_msg void OnNMCustomdrawListEmo(NMHDR *pNMHDR, LRESULT *pResult);
public:
  afx_msg void OnBnClickedButtonSend();
};
