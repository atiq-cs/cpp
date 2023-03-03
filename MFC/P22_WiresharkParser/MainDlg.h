// MainDlg.h : dlg header file
//
#pragma once
#ifdef STUN_KEYS_ENABLED
#include "StunKeySettings.h"
#endif

// WSPDlg dialog
class WSPDlg : public CDialogEx
{
// Construction
public:
  WSPDlg(CWnd* pParent = NULL);  // standard constructor

// Dialog Data
  enum { IDD = IDD_WS_PARSER_DIALOG };

  protected:
  virtual void DoDataExchange(CDataExchange* pDX);  // DDX/DDV support


// Implementation
protected:
  HICON m_hIcon;

private:
  // Generated message map functions
  virtual BOOL OnInitDialog();
  afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
  afx_msg void OnPaint();
  afx_msg HCURSOR OnQueryDragIcon();
  DECLARE_MESSAGE_MAP()
  afx_msg void OnEnUpdateMfceditbrowse1();
  afx_msg void OnBnClickedParsebtn();
  afx_msg void OnDropFiles(HDROP hDropInfo);
  afx_msg void OnNMClickSettings(NMHDR *pNMHDR, LRESULT *pResult);

public:
  #ifdef STUN_KEYS_ENABLED
  void GetKeyInfo(StunKeySettings *keydlgobj);
  #endif

private:
  CString m_InputText;
  CString m_OutputText;
  BOOL IsFileLoadOnProgress;
  BOOL IsParsingOnProgress;
  int m_SignalingHeaderLength;
  int   m_stunKeysCount;
  int m_StunKeys[21];
  void ParseWiresharkUDP();
  void UpdateEditControlFromFile(CString FBText);
};
