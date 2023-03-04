// Shell - Tray Notification Icon related functions

BOOL AddNotificationIcon(HWND hWnd, UINT uID, UINT CallbackMessageID, HICON hIcon, LPTSTR lpszTip);
BOOL ShowBalloon(HINSTANCE hInst, HWND hWnd, UINT uID, LPCTSTR pszTitle, LPCTSTR pszText, /*HICON hicon*/ DWORD dwIcon);
BOOL DeleteNotificationIcon(HWND hWnd, UINT uID);
BOOL IsWin7OrLater();
