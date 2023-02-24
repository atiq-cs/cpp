
// MainDlg.h : header file
//

#pragma once
#include "BitmapViewer.h"

// CMainDlg dialog
class CMainDlg : public CDialogEx
{
private:
  
// Construction
public:
  CMainDlg(CWnd* pParent = NULL);  // standard constructor

// Dialog Data
  enum { IDD = IDD_Main_DIALOG };

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
public:
  // CBitmapViewer tag_heuer;
  CBitmapViewer m_Viewer;
};
