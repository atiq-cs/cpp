//------------------------------------------------------------------------------
//
// File: Main.cpp (WinMain)
// Application entry-point.
// 
//------------------------------------------------------------------------------
#include "Common.h"
#include "MainDialog.h"

//
// PURPOSE: Modeless Dialog Sample OOP with Keyboard Messaging
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

    MSG msg = {};

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MODELESS_DLG_ACCL));

    /* while (TRUE)
    {
        if (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE))
        {
            if (Msg.message == WM_QUIT)
                break;
            else
            {
                if (Msg.message == WM_KEYDOWN || Msg.message == WM_LBUTTONDOWN)
                {
                    if (Msg.wParam == VK_END)
                        Msg.wParam = VK_TAB;
                    if (!IsDialogMessage(hwnd, &Msg))
                    {
                        TranslateMessage(&Msg);
                        DispatchMessage(&Msg);
                    }
                }
            }
        }
    }*/

    /*iRet = GetMessage(&msg, NULL, 0, 0);
    We need to pre translate keyboard events here, so can't use GetMessage

    Hence, use PeekMessage
      ref, http://stackoverflow.com/questions/2441457/keyboard-input-the-win32-message-loop
    */
    __pragma(warning(disable:4127))

    while (TRUE)
    { 
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                PostQuitMessage(0);
                break;
            }

            if (msg.message != WM_INITDIALOG) {
                if (msg.message == WM_KEYUP) {
                    if (pDlg != NULL)
                    {
                        pDlg->ProcessMessage(pDlg->m_hDlg, msg.message, msg.wParam, msg.lParam);
                    }
                }
            }
            
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg) || !IsDialogMessage(pDlg->GetHwnd(), &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
    }

    // Cleanup the dialog box object
    delete pDlg;

    return (int) msg.wParam;
}
