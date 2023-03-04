#include "stdafx.h"
#include "TrayNotification.h"
#include <Strsafe.h>

// Sys Tray / TaskBar / Balloon Notification API
// TODO: need to test all the functions in this header and,
//  compare against latest Tray Notif Win Sample
//


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

  NOTIFYICONDATA nid = {sizeof(nid)};
  nid.hWnd = hWnd;
  nid.uID = uID;
  // ** don't specify NIF_ICON when dwInfoFlags is set to NIIF_USER
  nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
  nid.uCallbackMessage = CallbackMessageID;

  HRESULT hr = StringCbCopyN(nid.szTip, sizeof(nid.szTip), lpszTip, sizeof(nid.szTip));
  if(FAILED(hr)) {
    MessageBox(hWnd, _T("Error setting nid.szTip"), nullptr, MB_OK | MB_ICONERROR);
    return FALSE;
  }

  nid.hIcon  = hIcon;

  return Shell_NotifyIcon(NIM_ADD, &nid);
}

// Whatever only requires for the Balloon Notif. (not Tray icon, menu)
//  Tray icon, messaging and tooltip is set by earlier NIM_Add
//  Don't worry about them here
//
// ref, NIM_MODIFY
//  https://learn.microsoft.com/en-us/windows/win32/api/shellapi/ns-shellapi-notifyicondataa
// ref, ShowPrintJobBalloon in Win Classic Sample
//
// NIF_SHOWTIP is supported with Notif. V4
BOOL ShowBalloon(HINSTANCE hInst, HWND hWnd, UINT uID, LPCTSTR pszTitle, LPCTSTR pszText, /*HICON hicon*/ DWORD dwIcon)
{
  NOTIFYICONDATA nid = {sizeof(NOTIFYICONDATA)};
  // Notif. shows an error without uID and hWnd
  nid.uID = uID;
  nid.hWnd = hWnd;

  nid.uFlags = NIF_INFO;
  nid.dwInfoFlags = NIIF_USER;

  HRESULT hr = StringCchCopy(nid.szInfoTitle, ARRAYSIZE(nid.szInfoTitle), pszTitle);
  if(FAILED(hr)) {
    MessageBox(hWnd, _T("Error setting nid.szInfoTitle"), nullptr, MB_OK | MB_ICONERROR);
    return FALSE;
  }

  hr = StringCchCopy(nid.szInfo, ARRAYSIZE(nid.szInfo), pszText);
  if(FAILED(hr)) {
    MessageBox(hWnd, _T("Error setting nid.szInfo"), nullptr, MB_OK | MB_ICONERROR);
    return FALSE;
  }

  // As per ref,
  //  https://learn.microsoft.com/en-us/windows/win32/api/shellapi/ns-shellapi-notifyicondataw
  // NIF_INFO (0x00000010)
  //  To display the balloon notification, specify NIF_INFO and provide text in szInfo.
  //
  // To set the icon utilize NIIF_USER in case we need large icon support (hBalloonIcon)
  //
  if (! IsWin7OrLater()) {
    LoadIconMetric(hInst, MAKEINTRESOURCE(dwIcon), LIM_LARGE, &nid.hBalloonIcon);

    // uTimeout is valid only in Windows 2000 and Windows XP
    nid.uTimeout = 4000;
  }
  else
    LoadIconMetric(hInst, MAKEINTRESOURCE(dwIcon), LIM_SMALL, &nid.hIcon);

  return Shell_NotifyIcon(NIM_MODIFY, &nid);
}

BOOL DeleteNotificationIcon(HWND hWnd, UINT uID)
{
  NOTIFYICONDATA nid = {sizeof(NOTIFYICONDATA)};
  return Shell_NotifyIcon(NIM_DELETE, &nid);
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
