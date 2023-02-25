// This is the custom control with emot icon support
//

#include "stdafx.h"
#include "Main.h"
#include "ChatHistory.h"


// ChatHistory
IMPLEMENT_DYNAMIC(ChatHistory, CWnd)

ChatHistory::ChatHistory()
{
  offset_Y = 0;
  RegisterWndClass();
  m_message = L"";
  m_len = 0;
}

ChatHistory::~ChatHistory()
{
}

BOOL ChatHistory::RegisterWndClass()
{
  WNDCLASS windowclass;
  HINSTANCE hInst = AfxGetInstanceHandle();

  // Check weather the class is registerd already
  if (!(::GetClassInfo(hInst, MYWNDCLASS, &windowclass)))
  {
    // If not then we have to register the new class
    windowclass.style = CS_DBLCLKS;// | CS_HREDRAW | CS_VREDRAW;
    windowclass.lpfnWndProc = ::DefWindowProc;
    windowclass.cbClsExtra = windowclass.cbWndExtra = 0;
    windowclass.hInstance = hInst;
    windowclass.hIcon = NULL;
    windowclass.hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
    windowclass.hbrBackground = ::GetSysColorBrush(COLOR_WINDOW);
    windowclass.lpszMenuName = NULL;
    windowclass.lpszClassName = MYWNDCLASS;

    if (!AfxRegisterClass(&windowclass))
    {
      AfxThrowResourceException();
      return FALSE;
    }
  }

  return TRUE;
}

BEGIN_MESSAGE_MAP(ChatHistory, CWnd)
  // First version missed the PAINT MSG binding
  //  hence `ChatHistory::post` wasn't working!
  ON_WM_PAINT()
  ON_WM_VSCROLL()
  ON_WM_SIZE()
END_MESSAGE_MAP()



bool ChatHistory::post(WCHAR *message, CTime m_time)
{
  m_message = message;
  Invalidate(true);
  UpdateWindow();
  return false;
}


// ChatHistory message handlers
void ChatHistory::OnPaint()
{
  TRACE0("hello!");
  PAINTSTRUCT ps;
  m_pDC = BeginPaint(&ps);
  m_len = wcslen(m_message);
  CRect cr;
  GetClientRect(cr);

  //m_pDC->TextOut(10, offset_Y, m_message);
  m_pDC->DrawText(m_message, -1, CRect(0, 0, 200, 200), DT_LEFT | DT_WORDBREAK);
  DrawBitmap(m_pDC, IDB_HAPPY);
  
  EndPaint(&ps);
}


// Second version adds Scrolling / response to Scroll messages
void ChatHistory::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
  
  int CurPos = GetScrollPos(SB_VERT);
  TRACE("\n scroll position - %d\n", CurPos);
  int yPos = CurPos;
  // lastSBACtion = nSBCode;

  switch (nSBCode) {
    // User clicked the HOME keyboard key.
  case SB_TOP:
    CurPos = 0;
    break;

    // User clicked the END keyboard key.
  case SB_BOTTOM:
    CurPos = m_nMaxScroll;
    break;

    // User clicked the top arrow.
  case SB_LINEUP:
    CurPos = max(0, CurPos - 1);

    break;

    // User clicked the bottom arrow.
  case SB_LINEDOWN:
    CurPos = min(m_nMaxScroll, CurPos + 1);
    break;

    // User clicked the scroll bar shaft above the scroll box.
  case SB_PAGEUP:
  {
    // Get the page size
    SCROLLINFO   si;
    GetScrollInfo(SB_VERT, &si);

    CurPos = max(0, CurPos - (int)si.nPage);
    // si.nPos -= si.nPage;
    break;

  }
    // User clicked the scroll bar shaft below the scroll box.+-
  case SB_PAGEDOWN:
  {
    // Get the page size. 
    SCROLLINFO   si;
    GetScrollInfo(SB_VERT, &si);
    CurPos = min(m_nMaxScroll, CurPos + (int)si.nPage);
    break;
    // si.nPos += si.nPage;
  }
    // User dragged the scroll box.
  case SB_THUMBTRACK:
    CurPos = nPos;
    // si.nPos = si.nTrackPos;
    break;

  default:
    break;
  }
  
  SetScrollPos(SB_VERT, CurPos);
  ScrollWindow(0, CurPos);
  UpdateWindow();
  Invalidate(true);
  CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}


void ChatHistory::OnSize(UINT nType, int cx, int cy)
{
  CWnd::OnSize(nType, cx, cy);

  // TODO: Add your message handler code here
}


// Third version implements the bitmap drawing (emot icon)
// CDC ref, https://learn.microsoft.com/en-us/cpp/mfc/reference/cdc-class
void ChatHistory::DrawBitmap(CDC * pDc, const int b_ID)
{
  // load IDB_BITMAP1 from our resources
  CBitmap bmp;
  if (b_ID == 0)
  {
    if (bmp.LoadBitmap(IDB_BITMAP1))
    {
      // Get the size of the bitmap
      BITMAP bmpInfo;
      bmp.GetBitmap(&bmpInfo);

      // Create an in-memory DC compatible with the 
      // display DC we're using to paint
      CDC dcMemory;
      dcMemory.CreateCompatibleDC(pDc);

      // Select the bitmap into the in-memory DC
      CBitmap* pOldBitmap = dcMemory.SelectObject(&bmp);

      // Find a centerpoint for the bitmap in the client area
      CRect rect;
      GetClientRect(&rect);
      int nX = rect.left + (rect.Width() - bmpInfo.bmWidth) / 2;
      int nY = rect.top + (rect.Height() - bmpInfo.bmHeight) / 2;

      // Copy the bits from the in-memory DC into the on- 
      // screen DC to actually do the painting. Use the centerpoint 
      // we computed for the target offset.
      pDc->BitBlt(nX, nY, bmpInfo.bmWidth, bmpInfo.bmHeight, &dcMemory,
        0, 0, SRCCOPY);

      dcMemory.SelectObject(pOldBitmap);
    }
    else
    {
      TRACE0("ERROR: Where's IDB_BITMAP1?\n");
    }
  }
  else
  {
    if (bmp.LoadBitmap(b_ID))
    {
      // Get the size of the bitmap
      BITMAP bmpInfo;
      bmp.GetBitmap(&bmpInfo);

      // Create an in-memory DC compatible with the 
      // display DC we're using to paint
      CDC dcMemory;
      dcMemory.CreateCompatibleDC(pDc);

      // Select the bitmap into the in-memory DC
      CBitmap* pOldBitmap = dcMemory.SelectObject(&bmp);

      // Find a centerpoint for the bitmap in the client area
      CRect rect;
      GetClientRect(&rect);
      int nX = rect.left + (rect.Width() - bmpInfo.bmWidth) / 2;
      int nY = rect.top + (rect.Height() - bmpInfo.bmHeight) / 2;

      // Copy the bits from the in-memory DC into the on- 
      // screen DC to actually do the painting. Use the centerpoint 
      // we computed for the target offset.
      pDc->BitBlt(nX, nY, bmpInfo.bmWidth, bmpInfo.bmHeight, &dcMemory,
        0, 0, SRCCOPY);

      dcMemory.SelectObject(pOldBitmap);
    }
    else
    {
      TRACE0("ERROR: Where's IDB_BITMAP1?\n");
    }
  }
  
}
