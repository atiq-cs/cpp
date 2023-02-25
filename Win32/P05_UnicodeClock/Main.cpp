#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <stdio.h>
//
//  PURPOSE : Unicode Clock in Bangla
//  Date    : 10-12-2009
//  Remarks :
//   - GetSystemTime is for something else; utilize `GetLocalTime` instead.
//   - Removed common code function `WinMain` body
//
//  TODO: add feature minimize in sys tray
//

// Global variables

// The main window class name.
static TCHAR szWindowClass[] = _T("UniClock");

// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("বাংলা ঘড়ি");

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void ShowTime(WCHAR *str, HDC tDC);

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow);


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  PAINTSTRUCT ps;
  HDC hdc;
  WCHAR greeting[100];

  UINT_PTR IDT_TIMER1=10;

  switch (message) {
  case WM_CREATE:
    // Let's create a Timer
    SetTimer(hWnd, IDT_TIMER1, 1000, (TIMERPROC) NULL);
    break;

    case WM_PAINT:
        HFONT hFont;
    RECT rect;
    hdc = BeginPaint(hWnd, &ps);
    // SetBkMode(hdc, TRANSPARENT);      // Does not clear the area before drawing

    // set font
    hFont = CreateFont(48,0,0,0,FW_DONTCARE,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
            CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Bangla"));
    // Select font
    SelectObject(hdc, hFont);


    // Time
    //swprintf_s(greeting, L"আতিক %ld", '২');
    // ch = 2438;
    //swprintf_s(greeting, L"বাংলা অক্ষর : ইউনিকোড Value");

    // GetClientRect(hWnd, &rect);
    SetRect(&rect, 100, 20, 700, 200);
    SetTextColor(hdc, RGB(0,141,119));
    DrawText(hdc, TEXT("বাংলা ঘড়ি\n"), -1,&rect, DT_NOCLIP);

    ShowTime(greeting, hdc);

    // sprintf(greeting, "Local time %02d : %02d : %02d", lt.wHour, lt.wMinute, lt.wSecond);
    // TextOut(hdc, 5, 20, greeting, strlen(greeting));

    // Date
    // sprintf(greeting, "System date %02d : %02d : %02d", st.wDay, st.wMonth, st.wYear);
    // TextOut(hdc, 5, 40, greeting, strlen(greeting));
    // sprintf(greeting, "Local date %02d : %02d : %02d", lt.wDay, lt.wMonth, lt.wYear);
    // TextOut(hdc, 5, 55, greeting, strlen(greeting));

    // Day of the week
    // sprintf(greeting, "Today is: %d", lt.wDayOfWeek);
    // TextOut(hdc, 5, 75, greeting, strlen(greeting));

    DeleteObject(hFont);
    EndPaint(hWnd, &ps);
    break;
  case WM_TIMER:
    InvalidateRect(hWnd, NULL, false);
    break;

  case WM_DESTROY:
    PostQuitMessage(0);

    if (IDT_TIMER1)
      KillTimer(hWnd, IDT_TIMER1);
    break;

  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
    break;
  }

  return 0;
}

// TODO: rewrite to not write into HDC on this function
// - the text for morning, after-noon and evening could be retrieved via GetAMPMEquiv()
// - time in Unicode could be another function
// In the end, we wanna TextOut those inside WM_PAINT
void ShowTime(WCHAR *str, HDC tDC) {
  int curPos, val, formattedHour;
  SYSTEMTIME lt;
  bool shouldShowSpace = false;

  GetLocalTime(&lt);
  curPos = 0;

  // Get hour
  SetTextColor(tDC, RGB(0x41,0x41,0x41));

  if (lt.wHour > 3 && lt.wHour < 7) {
    TextOut(tDC, 220, 80, L"ভোর", _tcslen(L"ভোর"));
  }
  else if (lt.wHour >6 && lt.wHour < 12) {
    TextOut(tDC, 220, 80, L"সকাল", _tcslen(L"সকাল"));
  }
  else if (lt.wHour >11 && lt.wHour < 16) {
    TextOut(tDC, 220, 80, L"মধ্যাহ্ন", _tcslen(L"মধ্যাহ্ন"));
  }
  else if (lt.wHour >15 && lt.wHour < 19) {
    TextOut(tDC, 220, 80, L"অপরাহ্ন", _tcslen(L"অপরাহ্ন"));
  }
  else if (lt.wHour > 18 && lt.wHour < 21) {
    TextOut(tDC, 220, 80, L"সন্ধ্যা", _tcslen(L"সন্ধ্যা"));
  }
  else if (lt.wHour > 20 && lt.wHour < 24) {
    TextOut(tDC, 220, 80, L"রাত", _tcslen(L"রাত"));
  }
  else
    TextOut(tDC, 220, 80, L"গভীর রাত", _tcslen(L"গভীর রাত"));

  formattedHour = (lt.wHour>12)?(lt.wHour-12):lt.wHour;
  val = formattedHour/10;
  if (val) {
    val += L'০';
    str[curPos++] = val;
  }

  val = L'০' + formattedHour%10;
  if (val)
    str[curPos++] = val;
  
  if (shouldShowSpace)
    str[curPos++] = ' ';

  str[curPos++] = ':';

  if (shouldShowSpace)
    str[curPos++] = ' ';

  // Get Minute
  val = L'০' + lt.wMinute/10;
  if (val)
    str[curPos++] = val;

  val = L'০' + lt.wMinute%10;
  if (val)
    str[curPos++] = val;

  if (shouldShowSpace)
    str[curPos++] = ' ';
  str[curPos++] = ':';
  if (shouldShowSpace)
    str[curPos++] = ' ';

  // Get Second
  val = L'০' + lt.wSecond / 10;
  if (val)
    str[curPos++] = val;

  val = L'০' + lt.wSecond % 10;
  if (val)
    str[curPos++] = val;

  SetTextColor(tDC, RGB(0,141,119));
  TextOut(tDC, 70, 80, str, curPos);
}
