### T04: Mouse KeyBoard WM Messaging
USB HandSet Messaging: For Keyboard related events, virtual key mappings, USB HandSet Messaging (private repository and proprietary) project is the best reference.

A `WndProc` handling Windows Size change, Mouse and keyboard messages looks like below,

```cpp
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  // Only draw / erase on specific rectangle area    
  RECT curRect={5, 5, 50, 400};
  //RECT curRect;

  switch (message) {
  case WM_PAINT:
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);
    //GetClientRect(hWnd, &curRect);
    if (!count)
        sprintf(greeting, "Current in main: %d", count);

    TextOut(hdc, 5, 5, greeting, strlen(greeting));
  
    EndPaint(hWnd, &ps);
    break;

  case WM_LBUTTONDOWN: // left button clicked
    // fDraw = TRUE;
    // ptPrevious.x = LOWORD(lParam); 
    // ptPrevious.y = HIWORD(lParam);
    sprintf(greeting, "Left button clicked");
    InvalidateRect(hWnd, NULL, false);
    break;
 
  case WM_LBUTTONUP: // left button released
    // if (fDraw)
    // { 
    //   hdc = GetDC(hWnd); 
    //   MoveToEx(hdc, ptPrevious.x, ptPrevious.y, NULL); 
    //   LineTo(hdc, LOWORD(lParam), HIWORD(lParam)); 
    //   ReleaseDC(hWnd, hdc);
    // } 
    // fDraw = FALSE;
    sprintf(greeting, "Left button clicked");
    InvalidateRect(hWnd, NULL, false);

    break;
   
  case WM_MOUSEMOVE: 
    // if (fDraw) 
    // { 
    //   hdc = GetDC(hWnd); 
    //   MoveToEx(hdc, ptPrevious.x, ptPrevious.y, NULL); 
    //   LineTo(hdc, ptPrevious.x = LOWORD(lParam), 
    //     ptPrevious.y = HIWORD(lParam)); 
    //   ReleaseDC(hWnd, hdc);
    // }
    ptPrevious.x = LOWORD(lParam); 
    ptPrevious.y = HIWORD(lParam); 
    sprintf(greeting, "Current Mouse position: (%d, %d)", ptPrevious.x, ptPrevious.y);
    InvalidateRect(hWnd, NULL, false);

    break;


  case WM_KEYDOWN: 
    switch (wParam)  {
    case VK_LEFT:
      // Process the LEFT ARROW key. 
      sprintf(greeting, "Left key has been pressed");
      InvalidateRect(hWnd, NULL, false);
      break; 

    case VK_RIGHT:
      // Process the RIGHT ARROW key. 
      sprintf(greeting, "Right key has been pressed");
      InvalidateRect(hWnd, NULL, false);
      break; 

    case VK_UP:
      // Process the UP ARROW key. 
      sprintf(greeting, "Up key has been pressed");
      InvalidateRect(hWnd, NULL, false);
      break; 

    case VK_DOWN:
      // Process the DOWN ARROW key. 
      sprintf(greeting, "Down key has been pressed");
      InvalidateRect(hWnd, NULL, false);
      break; 

    case VK_HOME:
      // Process the HOME key. 
      sprintf(greeting, "Home key has been pressed");
      InvalidateRect(hWnd, NULL, false);
      break; 

    case VK_END:
      // Process the END key. 
      sprintf(greeting, "End key has been pressed");
      InvalidateRect(hWnd, NULL, false);
      break; 

    case VK_INSERT:
      // Process the INS key. 
      sprintf(greeting, "Insert key has been pressed");
      InvalidateRect(hWnd, NULL, false);
      break; 

    case VK_DELETE:
      // Process the DEL key. 
      sprintf(greeting, "Delete key has been pressed");
      InvalidateRect(hWnd, NULL, false);
      break; 

    case VK_F2:
      // Process the F2 key. 
      sprintf(greeting, "F2 has been pressed");
      InvalidateRect(hWnd, NULL, false);
      break; 

    // Process other non-character keystrokes. 
          
    default:
        break; 
    }
    break;

  case WM_SIZE: 
    switch (wParam) { 
    case SIZE_MINIMIZED: 
      sprintf(greeting, "Window mimimized.");
      InvalidateRect(hWnd, NULL, false);
      break; 

    case SIZE_RESTORED: 
      // Wondering what we were trying to do here on using rcCurrent
      // Move the star back into the client area if necessary.  
      //
      // if (rcCurrent.right > (int) LOWORD(lParam)) 
      // {
      //     rcCurrent.left = 
      //         (rcCurrent.right = 
      //             (int) LOWORD(lParam)) - 20; 
      // }
      // if (rcCurrent.bottom > (int) HIWORD(lParam)) 
      // {
      //     rcCurrent.top = 
      //         (rcCurrent.bottom = 
      //             (int) HIWORD(lParam)) - 20; 
      // }
            
      sprintf(greeting, "Window restored.");
      InvalidateRect(hWnd, NULL, false);
      break; 

    case SIZE_MAXIMIZED: 
      sprintf(greeting, "Window Maximized.");
      InvalidateRect(hWnd, NULL, false);
      break; 

    default
      break; 
    }

    break;

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

*ref, MouseKeyBoardWindowStroke 10-12-2009*
