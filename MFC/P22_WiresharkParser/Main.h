
// Main.h : main header file for the Wireshark Parser application
//

#pragma once

#ifndef __AFXWIN_H__
  #error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"    // main symbols


// CMyApp:
// See WS_Parser.cpp for the implementation of this class
//

class CMyApp : public CWinApp
{
public:
  CMyApp();

// Overrides
public:
  virtual BOOL InitInstance();

// Implementation

  DECLARE_MESSAGE_MAP()
};

extern CMyApp theApp;