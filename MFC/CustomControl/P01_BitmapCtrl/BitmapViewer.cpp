// BitmapViewer.cpp : implementation file
//

#include "stdafx.h"
#include "Main.h"
#include "BitmapViewer.h"

#define BITMAPVIEWER_CLASSNAME    _T("MFCBitmapViewerCtrl")  // Window class name

// CBitmapViewer

IMPLEMENT_DYNAMIC(CBitmapViewer, CWnd)

CBitmapViewer::CBitmapViewer()
{
  RegisterWindowClass();
}

BOOL CBitmapViewer::RegisterWindowClass()
{
  WNDCLASS wndcls;
  HINSTANCE hInst = AfxGetInstanceHandle();

  if (!(::GetClassInfo(hInst, BITMAPVIEWER_CLASSNAME, &wndcls)))
  {
    // otherwise we need to register a new class
    wndcls.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
    wndcls.lpfnWndProc = ::DefWindowProc;
    wndcls.cbClsExtra = wndcls.cbWndExtra = 0;
    wndcls.hInstance = hInst;
    wndcls.hIcon = NULL;
    wndcls.hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
    wndcls.hbrBackground = (HBRUSH)(COLOR_3DFACE + 1);
    wndcls.lpszMenuName = NULL;
    wndcls.lpszClassName = BITMAPVIEWER_CLASSNAME;

    if (!AfxRegisterClass(&wndcls))
    {
      AfxThrowResourceException();
      return FALSE;
    }
  }

  return TRUE;
}

BOOL CBitmapViewer::Create(CWnd* pParentWnd, const RECT& rect, UINT nID, DWORD dwStyle /*=WS_VISIBLE*/)
{
  return CWnd::Create(BITMAPVIEWER_CLASSNAME, _T(""), dwStyle, rect, pParentWnd, nID);
}

CBitmapViewer::~CBitmapViewer()
{
}


BEGIN_MESSAGE_MAP(CBitmapViewer, CWnd)
  ON_WM_PAINT()
  ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CBitmapViewer message handlers




void CBitmapViewer::OnPaint()
{
  // Draw the bitmap - if we have one.
  if (m_Bitmap.GetSafeHandle() != NULL)
  {
    CPaintDC dc(this); // device context for painting

    // Create memory DC
    CDC MemDC;
    if (!MemDC.CreateCompatibleDC(&dc))
      return ;

    // Get Size of Display area
    CRect rect;
    GetClientRect(rect);

    // Get size of bitmap
    BITMAP bm;
    m_Bitmap.GetBitmap(&bm);

    // Draw the bitmap
    CBitmap* pOldBitmap = (CBitmap*)MemDC.SelectObject(&m_Bitmap);
    dc.StretchBlt(0, 0, rect.Width(), rect.Height(),
      &MemDC,
      0, 0, bm.bmWidth, bm.bmHeight,
      SRCCOPY);
    MemDC.SelectObject(pOldBitmap);
  }

  // Do not call CWnd::OnPaint() for painting messages
}

BOOL CBitmapViewer::OnEraseBkgnd(CDC* pDC)
{
  // If we have an image then don't perform any erasing, since the OnPaint
  // function will simply draw over the background
  if (m_Bitmap.GetSafeHandle() != NULL)
    return TRUE;

  // Obviously we don't have a bitmap - let the base class deal with it.
  return CWnd::OnEraseBkgnd(pDC);
}

BOOL CBitmapViewer::SetBitmap(UINT nIDResource)
{
  return m_Bitmap.LoadBitmap(nIDResource);
}