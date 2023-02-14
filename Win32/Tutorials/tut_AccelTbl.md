### Accelerator Table
The Last tutorial is on Accelerator Table and the message loop (ref, 11-11-2010). The code hasn't been updated to utilize latest OOP Template yet!

First, we add the ACCL list in the rc file,

    /////////////////////////////////////////////////////////////////////////////
    //
    // Accelerator
    //

    MAIN_APP_Accel ACCELERATORS 
    BEGIN
        "Q",            ID_EXIT,                VIRTKEY, CONTROL, NOINVERT
        "A",            ID_SEL,                 VIRTKEY, CONTROL, NOINVERT
    END


Afterwards, we load them in winMain via `LoadAccelerators`,

```cpp
MSG msg;
BOOL bRet;
HACCEL haccel;      // handle to accelerator table 

// Load the accelerator table. 
haccel = LoadAccelerators(hInst, MAKEINTRESOURCE(MAIN_APP_Accel));
if (haccel == NULL) {
    char str[100];
    sprintf_s(str, "Accelerator Loading Error %d", GetLastError());
    MessageBox(hWnd, str, "Win32 Tutorial", MB_OK | MB_ICONEXCLAMATION);
    return 1;
}

while ( (bRet = GetMessage(&msg, (HWND) NULL, 0, 0)) != 0)
{
    if (bRet == -1) {
        // handle the error
        MessageBox(hWnd, "Getmessage Error","Error", MB_OK | MB_ICONEXCLAMATION);
    }
    else
    { 
        // Check for accelerator keystrokes. 
        
        if (!TranslateAccelerator( 
                hWnd,      // handle to receiving window 
                haccel,        // handle to active accelerator table 
                &msg))         // message data 
        {
            TranslateMessage(&msg); 
            DispatchMessage(&msg); 
        } 
    } 
}

return (int) msg.wParam;
```

And, here's how we hook up the messaging for the Edit Control in WndProc,

```cpp
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  PAINTSTRUCT ps;
  HDC hdc;
  static HWND hwndEdit;
  char str[100] = "Application with a Menu";

  switch (message) {
  case WM_CREATE:
    hwndEdit = CreateWindow("EDIT",      // predefined class 
          NULL,        // no window title 
          WS_BORDER | WS_CHILD | WS_VISIBLE | WS_VSCROLL | 
          ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL, 
          20, 35, 230, 130,  // set size in WM_SIZE message 
          hWnd,        // parent window 
          NULL,   // edit control ID 
          hInst, 
          NULL);       // pointer not needed 

    // Add text to the edit control window. 
    strcpy_s(str, 100, "Menu along with Edit Control");
          SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM) str);
    break;

  case WM_PAINT:
    hdc = BeginPaint(hWnd, &ps);
    TextOut(hdc, 40, 5, str, strlen(str));
    EndPaint(hWnd, &ps);
    break;

  case WM_COMMAND:
    switch(LOWORD (wParam)) {
      case ID_SEL:
        SendMessage(hwndEdit, EM_SETSEL, 0, -1);
        MessageBox(hWnd, "Selection Msg", "Tutorial", MB_OK | MB_ICONINFORMATION);
        break;
      case ID_EXIT:
        PostMessage(hWnd, WM_CLOSE, 0, 0);
        break;
      default:
        break;
    }
    break;

  case WM_SETFOCUS: 
      SetFocus(hwndEdit); 
      return 0; 

  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
    break;
  }

  return 0;
}
```
