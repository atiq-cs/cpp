
// Main.h : main header file
//

#pragma once

#ifndef __AFXWIN_H__
  #error "include 'stdafx.h' before including this file for PCH"
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