#include "TrayNotification.h"
#include <Strsafe.h>

// AddNotificationIcon - adds an icon to the notification area.
// Returns TRUE if successful, or FALSE otherwise.
// hwnd - handle to the window to receive callback messages.
// uID - identifier of the icon.
// hicon - handle to the icon to add.
// lpszTip - ToolTip text.
//
BOOL AddNotificationIcon(HWND hWnd, UINT uID, UINT CallbackMessageID, HICON hIcon, LPTSTR lpszTip) {
  if (!lpszTip)
    return FALSE;

  NOTIFYICONDATA tnid = {0};
  tnid.cbSize = sizeof(NOTIFYICONDATA);
  tnid.hWnd = hWnd;
  tnid.uID = uID;
  // ** don't specify NIF_ICON when dwInfoFlags is set to NIIF_USER
  tnid.uFlags = NIF_MESSAGE | NIF_TIP;
  tnid.uCallbackMessage = CallbackMessageID;
  tnid.dwInfoFlags = NIIF_USER;

  // We already loaded the icon in `hIcon`
  /* When we use m_hIcon which is created using LoadIcon in the constructor, just doesn't work
  HICON hIcon = (HICON) LoadImage( //load up the icon:
    hInst, //get the HINSTANCE to this program
    MAKEINTRESOURCE(dwIcon), //grab the icon out of our resource file
    IMAGE_ICON, // tells the versatile LoadImage function that we are loading an icon
    16, 16, //x and y values. we want a 16x16-pixel icon for the tray.
    LR_DEFAULTCOLOR); */

  if (IsWin7OrLater()) {
    tnid.hBalloonIcon  = hIcon;
  }
  else {
    tnid.hIcon  = hIcon;
  }

  HRESULT hr = StringCbCopyN(tnid.szTip, sizeof(tnid.szTip), lpszTip, sizeof(tnid.szTip));
  if(FAILED(hr)) {
    MessageBox(hWnd, _T("Error occurred!"), _T("Error setting tnid.szTip"), MB_OK);
    return FALSE;
  }

  return Shell_NotifyIcon(NIM_ADD, &tnid);
}

// ref, NIM_MODIFY
//  https://learn.microsoft.com/en-us/windows/win32/api/shellapi/ns-shellapi-notifyicondataa
BOOL ShowBalloon(HINSTANCE hInst, HWND hWnd, UINT uID, LPCTSTR pszTitle, LPCTSTR pszText, /*HICON hicon*/ DWORD dwIcon)
{
  HRESULT hr;
  NOTIFYICONDATA nid = {0};
  nid.cbSize = sizeof(NOTIFYICONDATA);
  nid.uFlags = NIF_INFO;
  // nid.uFlags = NIF_INFO|NIF_ICON|NIF_TIP;
  nid.uID = uID;
  nid.hWnd = hWnd;

  hr = StringCchCopy(nid.szInfoTitle, ARRAYSIZE(nid.szInfoTitle), pszTitle);
  if(FAILED(hr)) {
    MessageBox(hWnd, _T("Error occurred!"), _T("Error setting nid.szInfoTitle"), MB_OK);
    return FALSE;
  }

  // As per ref,
  //  https://learn.microsoft.com/en-us/windows/win32/api/shellapi/ns-shellapi-notifyicondataw
  // NIF_INFO (0x00000010)
  //  To display the balloon notification, specify NIF_INFO and provide text in szInfo.
  //
  // Hence, only modify texts, don't modify (hBalloonIcon or hIcon) icon here

  if (! IsWin7OrLater()) {
    // uTimeout is valid only in Windows 2000 and Windows XP
    nid.uTimeout = 4000;
  }

  hr = StringCchCopy(nid.szInfo, ARRAYSIZE(nid.szInfo), pszText);
  if(FAILED(hr)) {
    MessageBox(hWnd, _T("Error occurred!"), _T("Error setting nid.szInfo"), MB_OK);
    return FALSE;
  }

  return Shell_NotifyIcon(NIM_MODIFY, &nid);
}

BOOL DeleteNotificationIcon(HWND hWnd, UINT uID) {
  NOTIFYICONDATA tnid = {0};

  tnid.cbSize = sizeof(NOTIFYICONDATA);
  tnid.hWnd = hWnd;
  tnid.uID = uID;
  // tnid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
  // tnid.uCallbackMessage = CallbackMessageID;
  // tnid.hIcon = hicon;
  // if (lpszTip) {
  //     hr = StringCbCopyN(tnid.szTip, sizeof(tnid.szTip), lpszTip,
  //                         sizeof(tnid.szTip));
  //       if(FAILED(hr))
  //   MessageBox(NULL,
  //   _T("Error occurred!"),
  //   _T("Tray Notification"),
  //   NULL);
  // }
  // else
  //     tnid.szTip[0] = (TCHAR)'\0';

  return Shell_NotifyIcon(NIM_DELETE, &tnid);
}

BOOL IsWin7OrLater()
{
    // Initialize the OSVERSIONINFOEX structure.
    OSVERSIONINFOEX osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
    osvi.dwMajorVersion = 6;
    osvi.dwMinorVersion = 1;

    // Initialize the condition mask.
    DWORDLONG dwlConditionMask = 0;
    VER_SET_CONDITION(dwlConditionMask, VER_MAJORVERSION, VER_GREATER_EQUAL);
    VER_SET_CONDITION(dwlConditionMask, VER_MINORVERSION, VER_GREATER_EQUAL);

    // Perform the test.
    return VerifyVersionInfo(&osvi,
      VER_MAJORVERSION | VER_MINORVERSION,
      dwlConditionMask);
}
