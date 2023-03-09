////////////////////////////////////////////////////////////////
// MSDN Magazine -- December 2002
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// Compiles with VC 6.0 or VS.NET on Windows XP. Tab size=3.
//
#include "StdAfx.h"
#include "FSApp.h"
#include "Doc.h"
#include "View.h"
#include "FullScreenHandler.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CMyView, CView)

BEGIN_MESSAGE_MAP(CMyView, CView)
  //ON_WM_NCHITTEST()
END_MESSAGE_MAP()

CMyView::CMyView()
{
  m_bMoving = FALSE;
}

CMyView::~CMyView()
{
}

void CMyView::OnDraw(CDC* pDC)
{
  CRect rc;
  GetClientRect(&rc);
  pDC->DrawText(FullScreenHandler.InFullScreenMode() ?
    _T("Type Ctrl-U to restore.") : _T(""), &rc, 0);
}

//////////////////
// Non-client hit-test handler to move window by its client area. The view
// returns HTTRANSPARENT and the frame returns HTCAPTION if the mouse
// is in the client area. Together, these handlers let user move the
// window by dragging the client area.
//
/*UINT CMyView::OnNcHitTest(CPoint pt)
{
  return HTTRANSPARENT;
}
*/