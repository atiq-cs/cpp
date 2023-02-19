//------------------------------------------------------------------------------
//
// File: MainDialog.h
// Implements the main dialog.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//
//------------------------------------------------------------------------------

// Modified a bit

#include <string>

/*namespace std {
  #if defined _UNICODE || defined UNICODE
    typedef wstring tstring;
    typedef wostringstream tostringstream;
  #else
    typedef string tstring;
    typedef ostringstream tostringstream;
  #endif
}*/


#pragma once

class MainDialog
{
public:
  MainDialog();
  ~MainDialog();

  virtual BOOL ShowDialog(HINSTANCE hinst);
  // Message handlers

  // WM_INITDIALOG
  HRESULT OnInitDialog(); 

  void OnDropFiles(HDROP hDrop);

  // WM_COMMAND
  // INT_PTR OnCommand(HWND hControl, WORD idControl, WORD msg);

private:
  // Dialog proc for the dialog we manage
  static INT_PTR CALLBACK DialogProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);

  // Return one of our dialog controls
  HWND GetDlgItem(int nID) { return ::GetDlgItem(m_hDlg, nID); }

  // bool ValidateDialogInputs();
  void ConvertVideo();

  void EndDialog(INT_PTR cmd)
  {
    if (m_hDlg)
    {
      ::EndDialog(m_hDlg, cmd);
    }
  }

private:
  HWND            m_hDlg;               // this dialog window
  int             m_nID;                // Resource ID of the dialog window 
  TCHAR      m_InputFileName[MAX_PATH];  // name of dropped file
};
