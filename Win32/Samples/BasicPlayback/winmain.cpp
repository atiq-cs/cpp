//////////////////////////////////////////////////////////////////////////
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//
//////////////////////////////////////////////////////////////////////////

// Note: Most of the interesting code is in Player.cpp

#include "BasicPlayback.h"
#include <assert.h>


const wchar_t szTitle[] = L"BasicPlayback";
const wchar_t szWindowClass[] = L"MFBASICPLAYBACK";

HINSTANCE   g_hInstance;                        // current instance
BOOL        g_bRepaintClient = TRUE;            // Repaint the application client area?
CPlayer     *g_pPlayer = NULL;                  // Global player object.

// Note: After WM_CREATE is processed, g_pPlayer remains valid until the
// window is destroyed.

BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    OpenUrlDialogProc(HWND, UINT, WPARAM, LPARAM);
void                NotifyError(HWND hwnd, PCWSTR sErrorMessage, HRESULT hr);
void                UpdateUI(HWND hwnd, PlayerState state);
HRESULT             AllocGetWindowText(HWND hwnd, PWSTR* pszText, DWORD *pcchLen);

// Message handlers
LRESULT             OnCreateWindow(HWND hwnd);
void                OnFileOpen(HWND hwnd);
void                OnOpenURL(HWND hwnd);
void                OnPlayerEvent(HWND hwnd, WPARAM pUnkPtr);
void                OnPaint(HWND hwnd);
void                OnKeyPress(WPARAM key);


// OpenUrlDialogInfo: Contains data passed to the "Open URL" dialog proc.
struct OpenUrlDialogInfo
{
    WCHAR *pszURL;
    DWORD cch;
};

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    MSG msg;

    ZeroMemory(&msg, sizeof(msg));

    // Perform application initialization.
    if (!InitInstance(hInstance, nCmdShow))
    {
        NotifyError(NULL, L"Could not initialize the application.",
            HRESULT_FROM_WIN32(GetLastError()));
        return FALSE;
    }

    // Main message loop.
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Clean up.
    if (g_pPlayer)
    {
        g_pPlayer->Shutdown();
        g_pPlayer->Release();
    }
    return 0;
}

BOOL InitInstance(HINSTANCE hInst, int nCmdShow)
{
    HWND hwnd;
    WNDCLASSEX wcex;

    g_hInstance = hInst; // Store the instance handle.

    // Register the window class.
    ZeroMemory(&wcex, sizeof(WNDCLASSEX));
    wcex.cbSize         = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.hInstance      = hInst;
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCE(IDC_MFPLAYBACK);
    wcex.lpszClassName  = szWindowClass;

    if (RegisterClassEx(&wcex) == 0)
    {
        return FALSE;
    }

    // Create the application window.
    hwnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInst, NULL);

    if (hwnd == 0)
    {
        return FALSE;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        return OnCreateWindow(hwnd);

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDM_EXIT:
            DestroyWindow(hwnd);
            break;
        case ID_FILE_OPENFILE:
            OnFileOpen(hwnd);
            break;
        case ID_FILE_OPENURL:
            OnOpenURL(hwnd);
            break;

        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
        }
        break;

    case WM_PAINT:
        OnPaint(hwnd);
        break;

    case WM_SIZE:
        g_pPlayer->ResizeVideo(LOWORD(lParam), HIWORD(lParam));
        break;

    case WM_ERASEBKGND:
        // Suppress window erasing, to reduce flickering while the video is playing.
        return 1;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_CHAR:
        OnKeyPress(wParam);
        break;

    case WM_APP_PLAYER_EVENT:
        OnPlayerEvent(hwnd, wParam);
        break;

    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}


//  Handles the WM_CREATE message.
//
//  hwnd: Handle to the video clipping window. (For this sample, the
//        video window is just the main application window.)

LRESULT OnCreateWindow(HWND hwnd)
{
    // Initialize the player object.
    HRESULT hr = CPlayer::CreateInstance(hwnd, hwnd, &g_pPlayer);

    if (SUCCEEDED(hr))
    {
        UpdateUI(hwnd, Closed);
        return 0;   // Success.
    }
    else
    {
        NotifyError(NULL, L"Could not initialize the player object.", hr);
        return -1;  // Destroy the window
    }
}


//  Open an audio/video file.

void OnFileOpen(HWND hwnd)
{
    HRESULT hr = S_OK;

    // Show the File Open dialog.
    wchar_t path[MAX_PATH];
    path[0] = L'\0';

    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFilter = L"Windows Media\0*.wmv;*.wma;*.asf\0MP3\0*.mp3\0All files\0*.*\0";
    ofn.lpstrFile = path;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_FILEMUSTEXIST;
    ofn.hInstance = g_hInstance;

    if (GetOpenFileName(&ofn))
    {
        // Open the file with the playback object.
        hr = g_pPlayer->OpenURL(ofn.lpstrFile);

        if (SUCCEEDED(hr))
        {
            UpdateUI(hwnd, OpenPending);
        }
        else
        {
            NotifyError(hwnd, L"Could not open the file.", hr);
            UpdateUI(hwnd, Closed);
        }
    }

}

// Opens a media file from a URL.

void OnOpenURL(HWND hwnd)
{
    HRESULT hr = S_OK;

    // Pass in an OpenUrlDialogInfo structure to the dialog. The dialog fills 
    // in this structure with the URL. The dialog proc allocates the memory 
    // for the string.

    OpenUrlDialogInfo url;
    ZeroMemory(&url, sizeof(&url));

    // Show the Open URL dialog.
    if (IDOK == DialogBoxParam(g_hInstance, MAKEINTRESOURCE(IDD_OPENURL), 
        hwnd, OpenUrlDialogProc, (LPARAM)&url))
    {
        // Open the file with the playback object.
        hr = g_pPlayer->OpenURL(url.pszURL);

        if (SUCCEEDED(hr))
        {
            UpdateUI(hwnd, OpenPending);
        }
        else
        {
            NotifyError(hwnd, L"Could not open this URL.", hr);
            UpdateUI(hwnd, Closed);
        }
    }

    // The app must release the string.
    CoTaskMemFree(url.pszURL);
}


//  Description: Handles WM_PAINT messages.

void OnPaint(HWND hwnd)
{
    if (g_bRepaintClient)
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // The video is not playing, so we must paint the application window.
        RECT rc;
        GetClientRect(hwnd, &rc);
        FillRect(hdc, &rc, (HBRUSH) COLOR_WINDOW);

        EndPaint(hwnd, &ps);
    }
    else
    {
        // Video is playing. Ask the player to repaint.
        g_pPlayer->Repaint();
    }
}

void OnKeyPress(WPARAM key)
{
    switch (key)
    {
    // Space key toggles between running and paused
    case VK_SPACE:
        if (g_pPlayer->GetState() == Started)
        {
            g_pPlayer->Pause();
        }
        else if (g_pPlayer->GetState() == Paused)
        {
            g_pPlayer->Play();
        }
        break;
    }
}

void OnPlayerEvent(HWND hwnd, WPARAM pUnkPtr)
{
    HRESULT hr = S_OK;

    hr = g_pPlayer->HandleEvent(pUnkPtr);

    if (FAILED(hr))
    {
        NotifyError(hwnd, L"An error occurred.", hr);
    }
    UpdateUI(hwnd, g_pPlayer->GetState());
}

void UpdateUI(HWND hwnd, PlayerState state)
{
    BOOL bWaiting = FALSE;
    BOOL bPlayback = FALSE;

    assert(g_pPlayer != NULL);

    switch (state)
    {
    case OpenPending:
        bWaiting = TRUE;
        break;

    case Started:
        bPlayback = TRUE;
        break;

    case Paused:
        bPlayback = TRUE;
        break;
    }

    HMENU hMenu = GetMenu(hwnd);
    UINT  uEnable = MF_BYCOMMAND | (bWaiting ? MF_GRAYED : MF_ENABLED);

    EnableMenuItem(hMenu, ID_FILE_OPENFILE, uEnable);
    EnableMenuItem(hMenu, ID_FILE_OPENURL, uEnable);

    if (bPlayback && g_pPlayer->HasVideo())
    {
        g_bRepaintClient = FALSE;
    }
    else
    {
        g_bRepaintClient = TRUE;
    }
}

//  Show a message box with an error message.

void NotifyError(HWND hwnd, PCWSTR sErrorMessage, HRESULT hrErr)
{
    const size_t MESSAGE_LEN = 512;
    wchar_t message[MESSAGE_LEN];

    HRESULT hr = StringCchPrintf (message, MESSAGE_LEN, L"%s (HRESULT = 0x%X)", sErrorMessage, hrErr);
    if (SUCCEEDED(hr))
    {
        MessageBox(hwnd, message, NULL, MB_OK | MB_ICONERROR);
    }
}


//  Message handler for the "Open URL" dialog.

INT_PTR CALLBACK OpenUrlDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    static OpenUrlDialogInfo *pUrl = NULL;

    BOOL result = FALSE;

    switch (message)
    {
    case WM_INITDIALOG:
        // The app sends a pointer to an OpenUrlDialogInfo structure as the lParam.
        // We use this structure to store the URL.
        pUrl = (OpenUrlDialogInfo*)lParam;
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
            if (pUrl)
            {
                // Get the URL from the edit box in the dialog.
                // This function allocates memory. The app must call CoTaskMemAlloc.
                HRESULT hr = AllocGetWindowText(GetDlgItem(hDlg, IDC_EDIT_URL), &pUrl->pszURL, &pUrl->cch);
                if (SUCCEEDED(hr))
                {
                    result = TRUE;
                }
            }
            EndDialog(hDlg, result ? IDOK : IDABORT);
            break;

        case IDCANCEL:
            EndDialog(hDlg, LOWORD(IDCANCEL));
            break;
        }
        return (INT_PTR)FALSE;
    }
    return (INT_PTR)FALSE;
}


HRESULT AllocGetWindowText(HWND hwnd, PWSTR* pszText, DWORD *pcchLen)
{
    if (pszText == NULL)
    {
        return E_POINTER;
    }

    *pszText = NULL;  

    int cch = GetWindowTextLength(hwnd);  
    if (cch < 0) 
    {
        return E_UNEXPECTED; // This function should not return a negative value.
    }

    TCHAR *szTmp = (TCHAR*)CoTaskMemAlloc(sizeof(TCHAR) * (cch + 1)); // Include room for terminating NULL character

    if (!szTmp)
    {
        return E_OUTOFMEMORY;
    }

    if (cch == 0)
    {
        szTmp[0] = L'\0';  // No text.
    }
    else
    {
        int res = GetWindowText(hwnd, szTmp, (cch + 1));  // Size includes NULL character

        // GetWindowText returns 0 if (a) there is no text or (b) it failed.
        // We checked for (a) already, so 0 means failure here.
        if (res == 0)
        {
            CoTaskMemFree(szTmp);
            return __HRESULT_FROM_WIN32(GetLastError());
        }
    }

    // If we got here, szTmp is valid, so return it to the caller.
    *pszText = szTmp;
    if (pcchLen)
    {
        *pcchLen = static_cast<DWORD>(cch);  // Return the length NOT including the '\0' 
    }
    return S_OK;
}