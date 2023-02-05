//------------------------------------------------------------------------------
//
// File: MainDialog.h
// Header for main dialog class
// Copyright (c) Microsoft Corporation. All rights reserved.
// 
// Author   : Atique
// Date     : November 2013
// Desc     : defines the dialog class with HWND and dialog ID
//             Declares ShowDialog, OnInitDialog, GetHwnd, GetDlgItem & EndDialog
//             Most importantly declares the dialog call back procedure DialogProc
//             Declares function to process messages
//------------------------------------------------------------------------------

#pragma once
// forward declaration
class DeviceAudioChipControl;

class MainDialog
{
public:
    MainDialog();
    ~MainDialog();

    virtual BOOL ShowDialog(HINSTANCE hinst);
    // Message handlers

    // WM_INITDIALOG
    HRESULT OnInitDialog();
    DeviceAudioChipControl *m_pDeviceControl;

    // WM_COMMAND
    // INT_PTR OnCommand(HWND hControl, WORD idControl, WORD msg);
    HWND    GetHwnd();
    BOOL ProcessMessage(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
    HWND            m_hDlg;     // this dialog window


private:
    // Dialog proc for the dialog we manage
    static INT_PTR CALLBACK DialogProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);

    // Return one of our dialog controls
    HWND GetDlgItem(int nID) { return ::GetDlgItem(m_hDlg, nID); }

    void EndDialog(INT_PTR cmd)
    {
        if (m_hDlg)
        {
            ::EndDialog(m_hDlg, cmd);
        }
    }

private:
    int             m_nID;      // Resource ID of the dialog window 
};
