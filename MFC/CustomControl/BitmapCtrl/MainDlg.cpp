
// MainDlg.cpp : implementation file
// Date: 07-24-2014
// ref, CustomControlExperiment
// bird_etsy.webp converted to bird_etsy.bmp using MS Paint, size increased

#include "stdafx.h"
#include "Main.h"
#include "MainDlg.h"
#include "afxdialogex.h"
#include "Resource.h"

#ifdef _DEBUG  
#define new DEBUG_NEW
#endif


// CMainDlg dialog



CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
  : CDialogEx(CMainDlg::IDD, pParent)
{
  m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_BMP, m_Viewer);
}

BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
  ON_WM_PAINT()
  ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CMainDlg message handlers

BOOL CMainDlg::OnInitDialog()
{
  CDialogEx::OnInitDialog();

  // Set the icon for this dialog.  The framework does this automatically
  //  when the application's main window is not a dialog
  SetIcon(m_hIcon, TRUE);      // Set big icon
  SetIcon(m_hIcon, FALSE);    // Set small icon

  //m_Viewer.Create(NULL, _T(""), WS_VISIBLE, CRect(0, 0, 1000, 1000), this, 1);
  //m_Viewer.Create(_T("MFCBitmapViewerCtrl"), _T(""), WS_VISIBLE, CRect(0, 0, 100, 100), this, 1);
  //m_Viewer.Create(this, CRect(0, 0, 100, 100), 1);
  m_Viewer.SetBitmap(IDB_BITMAP_IMAGE);

  // TODO: Add extra initialization here

  return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMainDlg::OnPaint()
{
  if (IsIconic())
  {
    CPaintDC dc(this); // device context for painting

    SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

    // Center icon in client rectangle
    int cxIcon = GetSystemMetrics(SM_CXICON);
    int cyIcon = GetSystemMetrics(SM_CYICON);
    CRect rect;
    GetClientRect(&rect);
    int x = (rect.Width() - cxIcon + 1) / 2;
    int y = (rect.Height() - cyIcon + 1) / 2;

    // Draw the icon
    dc.DrawIcon(x, y, m_hIcon);
  }
  else
  {
    CDialogEx::OnPaint();
  }
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMainDlg::OnQueryDragIcon()
{
  return static_cast<HCURSOR>(m_hIcon);
}

