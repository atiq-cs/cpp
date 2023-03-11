
// Main.h : main header file for the Dlg Template 1 application
//

#pragma once

#ifndef __AFXWIN_H__
  #error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"    // main symbols


// CMainApp:
// See Main.cpp for the implementation of this class
//

class CMainApp : public CWinApp
{
public:
  CMainApp();

// Overrides
public:
  virtual BOOL InitInstance();

// Implementation

  DECLARE_MESSAGE_MAP()
};

extern CMainApp theApp;
