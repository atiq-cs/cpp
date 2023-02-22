
// Main.h : main header file for the Main application
//
#pragma once

#ifndef __AFXWIN_H__
  #error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMainApp:
// See Main.cpp for the implementation of this class
//

class CMainApp : public CWinApp
{
public:
  CMainApp() noexcept;


// Overrides
public:
  virtual BOOL InitInstance();

// Implementation
  afx_msg void OnAppAbout();
  DECLARE_MESSAGE_MAP()
};

extern CMainApp theApp;
