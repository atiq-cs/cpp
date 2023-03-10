
#if !defined(AFX_MYDIALOG_H__20B59A5E_FBE6_4A1C_A6B7_FDC199FE74EC__INCLUDED_)
#define AFX_MYDIALOG_H__20B59A5E_FBE6_4A1C_A6B7_FDC199FE74EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NetInfoDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// NetInfoDialog dialog

class NetInfoDialog : public CDialog
{
// Construction
public:
  // NetInfoDialog(CWnd* pParent = NULL);   // standard constructor
  // NetInfoDialog::NetInfoDialog(UINT nIDTemplate);
  NetInfoDialog();
  void GetNetInfo(CString* strArray);
  // BOOL isNotifyOn() { return (m_isNotifyOn != 0); }
  CString GetWMINETINFO();
  static UINT DNSThreadProc( LPVOID pParam );
  void AdjustNetControls(BOOL IsSingleHost, CString Msg);
  typedef struct THREADSTRUCT        // structure for passing to the controlling function
  {
    NetInfoDialog*  _this;
  } THREADSTRUCT;


// Dialog Data
  //{{AFX_DATA(NetInfoDialog)
  enum { IDD = NETINFO_DIALOG };
    // NOTE: the ClassWizard will add data members here
  //}}AFX_DATA

protected:
  virtual BOOL OnInitDialog();
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //{{AFX_MSG(NetInfoDialog)
  afx_msg void OnBnClickedSingleHostCheck();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()

public:
  CString m_GWIP;
  CString m_PRIDNS;
  CString m_SecDNS;

  BOOL m_isNotifyOn;
  BOOL m_IsSingleHost;
  // Stores the number of requests to send set by user
  int m_MaxPingReqs;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYDIALOG_H__20B59A5E_FBE6_4A1C_A6B7_FDC199FE74EC__INCLUDED_)
