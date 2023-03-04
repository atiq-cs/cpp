
// MainDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "atlcomtime.h"


// MainDlg dialog
class MainDlg : public CDialogEx
{
// Construction
public:
  MainDlg(CWnd* pParent = NULL);  // standard constructor
  ~MainDlg();  // standard constructor

// Dialog Data
  enum { IDD = IDD_MAIN_DIALOG };

  protected:
  virtual void DoDataExchange(CDataExchange* pDX);  // DDX/DDV support


// Implementation
protected:
  HICON m_hIcon;

  // Generated message map functions
  virtual BOOL OnInitDialog();
  afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
  afx_msg void OnPaint();
  afx_msg HCURSOR OnQueryDragIcon();
  afx_msg void OnAppAbout();
  afx_msg void OnAppExit();
  afx_msg void OnAppOpen();
  afx_msg LRESULT OnTrayNotify(WPARAM wp, LPARAM lp);
  DECLARE_MESSAGE_MAP()

  void OnTrayContextMenu ();
private:
  // Control variable asssociated with action combo box
  CComboBox cbAction;
public:
  afx_msg void OnBnClickedOk();
protected:
  // Maintains tray icon status
  BOOL isTrayIconAdded;
  // Stores the time received from user
  COleDateTime m_Time;
};
