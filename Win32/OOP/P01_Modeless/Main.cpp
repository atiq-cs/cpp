//------------------------------------------------------------------------------
//
// File: Main.cpp (previous name: WinMain.cpp)
// Application entry-point.
// 
//------------------------------------------------------------------------------

#include "Common.h"
#include "MainDialog.h"

//
// PURPOSE: Modeless Dialog Sample (Windows SDK C++, minimalist version)
//
// Author : Atiq Rahman
// Date   : 05-2014 (for few files, rest are from 11-2013)
//

//
// PURPOSE: Win32 Entry Point Function
//
// COMMENTS:
//  Create and show the dialog, we changed the application to support Modeless dialog
//  through MainDialog
//
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);

    MainDialog *pDlg = new (std::nothrow) MainDialog();
    if (pDlg == NULL)
    {
        MessageBox(NULL, TEXT("Out of memory."), NULL, MB_ICONSTOP);
    }
    else
    {
        // Show Dialog Window
        pDlg->ShowDialog(hInstance);
    }

    INT iRet;
    MSG msg;
    // HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MODELESS_DLG_ACCL));

    iRet = GetMessage(&msg, NULL, 0, 0);
    while (iRet != 0)
    { 
        if (iRet == -1)
        {
            HRESULT hr = HRESULT_FROM_WIN32(GetLastError());
            UNREFERENCED_PARAMETER(hr);
            MessageBox(NULL, TEXT("Error processing the application window message loop"), TEXT("Caption"), MB_ICONERROR);
        }
        else
        {
            // if (!IsWindow(pDlg->GetHwnd()) || !IsDialogMessage(pDlg->GetHwnd(), &msg)) 
            if (!TranslateAccelerator(msg.hwnd, NULL, &msg) || !IsDialogMessage(pDlg->GetHwnd(), &msg))
            { 
                TranslateMessage(&msg); 
                DispatchMessage(&msg); 
            }
        }

        iRet = GetMessage(&msg, NULL, 0, 0);
    }

    // Cleanup the dialog box object
    delete pDlg;

    return (int) msg.wParam;
}
