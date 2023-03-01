// AboutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Main.h"
#include "AboutDlg.h"
#include "afxdialogex.h"


// CAboutDlg dialog
IMPLEMENT_DYNAMIC(CAboutDlg, CDialogEx)

CAboutDlg::CAboutDlg(CWnd* pParent /*=NULL*/)
  : CDialogEx(CAboutDlg::IDD, pParent)
{
}

CAboutDlg::~CAboutDlg()
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
  ON_NOTIFY(NM_CLICK, IDC_PROJ_LINK, &CAboutDlg::OnNMClickProjLink)
END_MESSAGE_MAP()


// CAboutDlg message handlers


void CAboutDlg::OnNMClickProjLink(NMHDR *pNMHDR, LRESULT *pResult)
{
  // TODO: Add your control notification handler code here
  PNMLINK pNMLink = (PNMLINK) pNMHDR;
  ::ShellExecute(m_hWnd, _T("open"), pNMLink->item.szUrl, NULL, NULL, SW_SHOWNORMAL);

  // if (_tcscmp(pNMLink->item.szUrl, WEB_SITE) == 0)
  // {
  //   ShellExecute(NULL, L"open", pNMLink->item.szUrl, NULL, NULL, SW_SHOWNORMAL);
  // }
  // else if(_tcscmp(pNMLink->item.szUrl, BLOG_LINK) == 0)
  // {
  //   ShellExecute(NULL, L"open", pNMLink->item.szUrl, NULL, NULL, SW_SHOWNORMAL);
  // }

  *pResult = 0;
}
