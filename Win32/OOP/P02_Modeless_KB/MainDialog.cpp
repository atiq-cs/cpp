//------------------------------------------------------------------------------
//
// File: MainDialog.cpp
// PURPOSE: OOP Definition of the Dialog Box of the App (constructor, destructor & methods)
// Comment: Independent ShowDialog, OnInitDialog, GetHwnd, GetDlgItem & EndDialog
// 
//------------------------------------------------------------------------------
#include "Common.h"
#include "MainDialog.h"
#include "resource.h"


//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------

MainDialog::MainDialog() : 
    m_nID(IDD_DIALOG_MAIN),
    m_hDlg(0),
    m_pDeviceControl(NULL)
{
    // allocate buffer for m_InputFileName

}


//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------

MainDialog::~MainDialog()
{
    // for future use
}

//-----------------------------------------------------------------------------
// OnInitDialog
//
// Handler for WM_INITDIALOG message.
//-----------------------------------------------------------------------------

HRESULT MainDialog::OnInitDialog()
//HRESULT MainDialog::OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
    HRESULT hr = S_OK;
    return hr;
}


//-----------------------------------------------------------------------------
// ShowDialog()
// Displays the dialog
//
// Application instance
//
// Returns TRUE if successful or FALSE otherwise
//-----------------------------------------------------------------------------
BOOL MainDialog::ShowDialog(HINSTANCE hinst)
{
    // We can create modeless dialog or 
    m_hDlg = CreateDialogParam(
        hinst, 
        MAKEINTRESOURCE(m_nID), 
        NULL, 
        DialogProc, 
        (LPARAM)this
        );

    if (m_hDlg) {
        ShowWindow(m_hDlg, SW_SHOW);
        UpdateWindow(m_hDlg);
    }

    return TRUE;
}


//-----------------------------------------------------------------------------
// Name: DialogProc()
// Desc: DialogProc for the dialog. This is a static class method.
//
// lParam: Pointer to the MainDialog object. 
//
// The MainDialog class specifies lParam when it calls DialogBoxParam. We store the 
// pointer as user data in the window. 
//
// (Note: The DirectShow CBasePropertyPage class uses the same technique.)
//-----------------------------------------------------------------------------
INT_PTR CALLBACK MainDialog::DialogProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    MainDialog *pDlg = 0;  // Pointer to the dialog class that manages the dialog 

    // LRESULT lResult = 0;
    BOOL bReturn = FALSE;

    if (msg == WM_INITDIALOG)
    {
        // Get the pointer to the dialog object and store it in 
        // the window's user data, so that we can use this to process later messages
        // GWLP_USERDATA for Windows; DWLP_USER for dialog
        SetWindowLongPtr(hDlg, DWLP_USER, (LONG_PTR)lParam);

        pDlg = (MainDialog*)lParam;
        if (pDlg)
        {
            // we got this data from CreateDialogParam
            // we haven't returned from CreateDialogParam, so m_hDlg is not valid yet, but we are using it in OnInitDialog
            // so let's initialize it
            pDlg->m_hDlg = hDlg;
            HRESULT hr = pDlg->OnInitDialog();
            bReturn = hr;
            /*if (FAILED(hr))
            {
                pDlg->EndDialog(0);
            }*/
            SetDlgItemText(hDlg, IDC_STATIC_LOG_TEXT, _T("Test data on static text control updated by code"));
        }
        return bReturn;
    }

    // Get the dialog object from the window's user data
    pDlg = (MainDialog*)(DWORD_PTR) GetWindowLongPtr(hDlg, DWLP_USER);

    if (pDlg != NULL)
    {
        bReturn = pDlg->ProcessMessage(hDlg, msg, wParam, lParam);
    }
    return bReturn;
}


BOOL MainDialog::ProcessMessage(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);

    PAINTSTRUCT ps;
    HDC hdc;

    LRESULT lResult = 0;
    // Window messages other than WM_INITDIALOG

    // WCHAR string Variable for debug outputs
    TCHAR dbgStr[100] = {0};

    switch (uMsg)
    {
        case WM_PAINT:
            hdc = BeginPaint(hDlg, &ps);
            TextOut(hdc, 60, 170, TEXT("Hello, Windows!"), 15);
            _tcscat_s(dbgStr, 100, TEXT("[ Win32 App ]"));
            TextOut(hdc, 60, 210, dbgStr, (int) _tcslen(dbgStr));
            EndPaint(hDlg, &ps);
            return TRUE;

        // message for key down - not activated for now
        // case WM_KEYDOWN:
        //     _stprintf_s(dbgStr, TEXT("%hu "), LOWORD(wParam));
        //     SetDlgItemText(m_hDlg, IDC_STATIC_LOG_TEXT, dbgStr);
        //     return TRUE;

        // message for key up
        case WM_KEYUP:
            switch (LOWORD(wParam))
            {
            // Add conditions here for arrow up, down, left, right
            case VK_RETURN:
                MessageBox(m_hDlg, L"VK Return button is released.", 0, 0);
                return TRUE;
            }

            _stprintf_s(dbgStr, TEXT("%hu "), LOWORD(wParam));
            SetDlgItemText(m_hDlg, IDC_STATIC_LOG_TEXT, dbgStr);
            return TRUE;

        case WM_DESTROY:
            // lResult = OnDestroy(hDlg, wParam, lParam);
            PostQuitMessage(0);
            break;

        case WM_NCDESTROY:
            // lResult = OnNcDestroy(hDlg, wParam, lParam);
            m_hDlg = NULL;             // Since this is a modeless-only dialog 
            break;

        case WM_CLOSE:
            lResult = DestroyWindow(m_hDlg);
            break;

        case WM_COMMAND:
            _stprintf_s(dbgStr, TEXT("wm_command %hu "), LOWORD(wParam));
            SetDlgItemText(m_hDlg, IDC_STATIC_LOG_TEXT, dbgStr);
            switch (LOWORD(wParam))
            {
            case IDM_ABOUT:
                _stprintf_s(dbgStr, TEXT("IDM_ABOUT %hu "), LOWORD(wParam));
                SetDlgItemText(m_hDlg, IDC_STATIC_LOG_TEXT, dbgStr);
                return TRUE;
            /*
            case IDOK:
            case IDCANCEL:
                DestroyWindow(m_hDlg);
                //EndDialog(LOWORD(wParam));
                return TRUE;
            */
            default:
                // Add OnCommand on Demand, disabled for now
                // return pDlg->OnCommand((HWND)lParam, LOWORD(wParam), HIWORD(wParam));
                return TRUE;
            }
            break;
        default:
            break;
    }

    return (BOOL) lResult;
}

//---------------------------------------------------------------------------
HWND MainDialog::GetHwnd() {
    return m_hDlg;
}
