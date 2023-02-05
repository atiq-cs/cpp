//------------------------------------------------------------------------------
//
// File: MainDialog.h
// Header for Main Dialog Class
// 
//------------------------------------------------------------------------------

#pragma once
// forward declaration
class DeviceAudioChipControl;

//
// PURPOSE: Defines the dialog class with HWND and Dialog ID
//
// COMMENTS:
//  Declares ShowDialog, OnInitDialog, GetHwnd, GetDlgItem & EndDialog
//  Most importantly declares the dialog call back procedure DialogProc
//  Declares function to process messages
//

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


private:
    // Dialog proc for the dialog we manage
    static INT_PTR CALLBACK DialogProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
    BOOL ProcessMessage(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

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
    HWND            m_hDlg;     // This dialog window
    int             m_nID;      // Resource ID of the dialog window 
};
