#pragma once


// CAboutDlg dialog

class CAboutDlg : public CDialogEx
{
  DECLARE_DYNAMIC(CAboutDlg)

public:
  CAboutDlg(CWnd* pParent = NULL);   // standard constructor
  virtual ~CAboutDlg();

// Dialog Data
  enum { IDD = IDD_ABOUT_DLG };

protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnNMClickProjLink(NMHDR *pNMHDR, LRESULT *pResult);
};
