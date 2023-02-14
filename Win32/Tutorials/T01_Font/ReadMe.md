### Tutorial 1 - Hello World
Once you have perused through [Quick Start Article](../) it's time to get your feet dirty. This tutorial starts with a hands on.

Main program of this application is 'Main.cpp'. The file contains verbose comments to help understand.

- The main window class name is defined in resource file (Main.rc). Please lookup def, `IDS_APP_TITLE`
- The string that appears in the application's title bar. Please lookup def, `IDC_MAIN_APP`

`<tchar.h>` is a culture agnostic helper header that allows us to write programs while using English Language.
Intro and details at: [TCHAR header intro article - codeproject by Atiq](https://www.codeproject.com/Articles/192952/String-Manipulations-using-TCHAR-Library)

ANSI example how to draw text on a Window,

```cpp
case WM_PAINT:
    PAINTSTRUCT ps;

    // assigning string without allocating memory!!
    const char *inst = "Welcome to Win32 Programming!";
    HDC hdc = BeginPaint(hWnd, &ps);

    // Here your application is laid out.
    // For this introduction, we just print out "Hello, World!"
    // in the top left corner.
    TextOutA(hdc, 25, 85, inst, strlen(inst));
    // End application-specific layout section.

    EndPaint(hWnd, &ps);
    break;
```

**Screenshot** 

![Tutorial 1 App with Custom Font](https://user-images.githubusercontent.com/7858031/218599629-d2cb84b8-010f-4c27-a261-08394a397495.png)

As we can see in above screenshot, `DrawText` only draws text within the rectangle provided. Because we intentionally provided a small rectange it could not draw the entire text!

### Misc
Set color using hex value: `0x00BBGGRR` ref, [MSFT Doc - COLORREF](https://learn.microsoft.com/en-us/windows/win32/gdi/colorref)

```cpp
SetTextColor(hdc, 0x00FF0000);
```


To make a window topmost,

```cpp
SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE);
```

**Note**  
Most of the files in this dir is copied from [P03_BaseWnd - OOP Template](../../OOP/P03_BaseWnd/)

#### Using International Languages in GUI Apps
With Unicode enabled i18n is pretty straightforward!

We just need to know how to manipulate unicode strings. Variations of string functions are to be aware of!

Here's an example that uses i18n language strings, demonstrates manipulation of those unicode strings.

```cpp
// code ... ...
case WM_PAINT:
  PAINTSTRUCT ps;
  // WCHAR is an alias of wide char: wchar_t
  WCHAR greeting[100], strA[50];
  HFONT hFont;
  RECT rect;
  HDC hdc = BeginPaint(hWnd, &ps);
  // SetBkMode(hdc, TRANSPARENT);			// Does not clear the area before drawing
  // Set font, choose a font that appropriately shows the character of your language/culture
  hFont = CreateFont(30,0,0,0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
      CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Bangla"));
  // Select font
  SelectObject(hdc, hFont);

  SetRect(&rect, 100,20,700,200);
  SetTextColor(hdc, RGB(0,141,119));
  swprintf(greeting, L"বাংলা ইউনিকোড প্রোগ্রাম");
  // wcslen is strlen equivalent
  TextOut(hdc, 40, 20, greeting, wcslen(greeting));
  swprintf(strA, L" %d", wcslen(greeting));
  swprintf(greeting, L"String - এর দৈর্ঘ্য:");
  // strcat_s equivalent
  wcscat_s(greeting, strA);
  TextOut(hdc, 40, 50, greeting, wcslen(greeting));
  DeleteObject(hFont);

  EndPaint(hWnd, &ps);
  break;
// code ... ...
```