### Unicode Clock
A clock that utilizes Unicode to show time in Bangla!  

- *rc file*: Please generate Main.rc based on [T02_VS_and_Menu/Main.rc](../Tutorials/T02_VS_and_Menu/Main.rc)
- *icon*: Main.ico (32x32) was adapted for clock.


Screenshot of the app below,   

![Bangla Clock](https://user-images.githubusercontent.com/7858031/219137657-f521f2ed-8d9f-41fb-8568-ecb2149aa82c.png)

#### Appendix

**Show System and Local Time**  

```cpp
case WM_PAINT:
  hdc = BeginPaint(hWnd, &ps);
  GetSystemTime(&st);
  GetLocalTime(&lt);

  // Time
  sprintf(greeting, "System time %02d : %02d : %02d", st.wHour, st.wMinute, st.wSecond);
  TextOut(hdc, 5, 5, greeting, strlen(greeting));
  sprintf(greeting, "Local time %02d : %02d : %02d", lt.wHour, lt.wMinute, lt.wSecond);
  TextOut(hdc, 5, 20, greeting, strlen(greeting));

  // Date
  sprintf(greeting, "System date %02d : %02d : %02d", st.wDay, st.wMonth, st.wYear);
  TextOut(hdc, 5, 40, greeting, strlen(greeting));
  sprintf(greeting, "Local date %02d : %02d : %02d", lt.wDay, lt.wMonth, lt.wYear);
  TextOut(hdc, 5, 55, greeting, strlen(greeting));

  // Day of the week
  sprintf(greeting, "Today is: %d", lt.wDayOfWeek);
  TextOut(hdc, 5, 75, greeting, strlen(greeting));

  EndPaint(hWnd, &ps);
  break;
```


**Font Enumeration Example**  

```cpp
case WM_PAINT:
  hdc = BeginPaint(hWnd, &ps);
  RECT rect;
  HBRUSH hBrush;
  HFONT hFont;

  // Set font
  //Logical units are device dependent pixels, so this will create a handle to a logical font that is 48 pixels in height.
  //The width, when set to 0, will cause the font mapper to choose the closest matching value.
  //The font face name will be Impact.
  hFont = CreateFont(48,0,0,0,FW_DONTCARE,FALSE,TRUE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
      CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Bangla"));
  SelectObject(hdc, hFont);
  /*
  //Sets the coordinates for the rectangle in which the text is to be formatted.
  SetRect(&rect, 100,100,700,200);
  SetTextColor(hdc, RGB(255,0,0));
  DrawText(hdc, TEXT("Drawing Text with Bangla"), -1,&rect, DT_NOCLIP);
  

  //Logical units are device dependent pixels, so this will create a handle to a logical font that is 36 pixels in height.
  //The width, when set to 20, will cause the font mapper to choose a font which, in this case, is stretched.
  //The font face name will be Times New Roman.  This time nEscapement is at -300 tenths of a degree (-30 degrees)
  hFont = CreateFont(36,20,-300,0,FW_DONTCARE,FALSE,TRUE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
      CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Times New Roman"));
  SelectObject(hdc,hFont);
  
  //Sets the coordinates for the rectangle in which the text is to be formatted.
  SetRect(&rect, 100, 200, 900, 800);
  SetTextColor(hdc, RGB(0,128,0));
  DrawText(hdc, TEXT("Drawing Text with Times New Roman"), -1,&rect, DT_NOCLIP);
  
      
  //Logical units are device dependent pixels, so this will create a handle to a logical font that is 36 pixels in height.
  //The width, when set to 10, will cause the font mapper to choose a font which, in this case, is compressed. 
  //The font face name will be Arial. This time nEscapement is at 250 tenths of a degree (25 degrees)
  hFont = CreateFont(36,10,250,0,FW_DONTCARE,FALSE,TRUE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
      CLIP_DEFAULT_PRECIS,ANTIALIASED_QUALITY, VARIABLE_PITCH,TEXT("Arial"));
  SelectObject(hdc,hFont);

  //Sets the coordinates for the rectangle in which the text is to be formatted.
  SetRect(&rect, 500, 200, 1400, 600);
  SetTextColor(hdc, RGB(0,0,255));
  DrawText(hdc, TEXT("Drawing Text with Arial"), -1,&rect, DT_NOCLIP);
  */

  GetSystemTime(&st);
  GetLocalTime(&lt);

  // Time
  // ch = 2438;
  //swprintf_s(greeting, L"বাংলা অক্ষর : ইউনিকোড Value");
  SetRect(&rect, 100,100,700,200);
  SetTextColor(hdc, RGB(255,0,0));
  DrawText(hdc, TEXT("বাংলা অক্ষর : ইউনিকোড Drawing Text with Bangla"), -1,&rect, DT_NOCLIP);
  //TextOut(hdc, 5, 5, greeting, _tcslen(greeting));

  for (pos = 25, ch = L'০';ch <= L'৯'; ch++, pos+=18) {
    swprintf_s(greeting, L"%c : %d", ch, ch);
    //TextOut(hdc, 5, pos, greeting, _tcslen(greeting));
  }

  // sprintf(greeting, "Local time %02d : %02d : %02d", lt.wHour, lt.wMinute, lt.wSecond);
  // TextOut(hdc, 5, 20, greeting, strlen(greeting));

  // // Date
  // sprintf(greeting, "System date %02d : %02d : %02d", st.wDay, st.wMonth, st.wYear);
  // TextOut(hdc, 5, 40, greeting, strlen(greeting));
  // sprintf(greeting, "Local date %02d : %02d : %02d", lt.wDay, lt.wMonth, lt.wYear);
  // TextOut(hdc, 5, 55, greeting, strlen(greeting));

  // // Day of the week
  // sprintf(greeting, "Today is: %d", lt.wDayOfWeek);
  // TextOut(hdc, 5, 75, greeting, strlen(greeting));

  // End application-specific layout section.
  DeleteObject(hFont);    

  EndPaint(hWnd, &ps);
  break;
```

