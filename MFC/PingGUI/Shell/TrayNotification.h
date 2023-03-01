#include "../stdafx.h"

// Shell - Tray Notification Icon related functions

BOOL AddNotificationIcon(HWND hwnd, UINT uID, UINT CallbackMessageID, HICON hIcon, LPTSTR lpszTip);
BOOL ShowBalloon(HINSTANCE hInst, HWND hWnd, UINT uID, LPCTSTR pszTitle, LPCTSTR pszText, /*HICON hicon*/ DWORD dwIcon);
BOOL DeleteNotificationIcon(HWND hwnd, UINT uID);
BOOL IsWin7OrLater();
