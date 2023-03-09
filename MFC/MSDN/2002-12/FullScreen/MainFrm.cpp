////////////////////////////////////////////////////////////////
// MSDN Magazine -- December 2002
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// Compiles with VC 6.0 or VS.NET on Windows XP. Tab size=3.
//
#include "StdAfx.h"
#include "FSApp.h"
#include "MainFrm.h"
#include "FullScreenHandler.h"
#include "TraceWin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
  ON_WM_CREATE()
  ON_WM_GETMINMAXINFO()
  ON_COMMAND(ID_VIEW_FULLSCREEN, OnViewFullScreen)
  ON_UPDATE_COMMAND_UI(ID_VIEW_FULLSCREEN, OnUpdateViewFullScreen)
//  ON_WM_NCHITTEST()
END_MESSAGE_MAP()

static UINT indicators[] = {
  ID_SEPARATOR,           // status line indicator
  ID_INDICATOR_CAPS,
  ID_INDICATOR_NUM,
  ID_INDICATOR_SCRL,
};

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
  if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
    return -1;
  
  VERIFY(m_wndToolBar.Create(this) &&
    m_wndToolBar.LoadToolBar(IDR_MAINFRAME));

  VERIFY(m_wndStatusBar.Create(this) &&
    m_wndStatusBar.SetIndicators(indicators,
      sizeof(indicators)/sizeof(UINT)));

  m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
    CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

  return 0;
}

//////////////////
// Important to handle this in order to set size
// of window larger than whole screen.
//
void CMainFrame::OnGetMinMaxInfo(MINMAXINFO* lpmmi)
{
  CSize sz = FullScreenHandler.GetMaxSize();
  lpmmi->ptMaxSize = CPoint(sz);
  lpmmi->ptMaxTrackSize = CPoint(sz);
}

//////////////////
// View full screen mode. Calls CFullScreenHandler to do the work.
//
void CMainFrame::OnViewFullScreen()
{
  if (FullScreenHandler.InFullScreenMode())
    FullScreenHandler.Restore(this);
  else 
    FullScreenHandler.Maximize(this, GetActiveView());
}

//////////////////
// Put checkmark next to command if in full screen mode.
//
void CMainFrame::OnUpdateViewFullScreen(CCmdUI* pCmdUI)
{
  pCmdUI->SetCheck(FullScreenHandler.InFullScreenMode());
}

//////////////////
// Non-client hit-test handler to move window by its client area. The view
// returns HTTRANSPARENT and the frame returns HTCAPTION if the mouse
// is in the client area. Together, these handlers let user move the
// window by dragging the client area.
//
UINT CMainFrame::OnNcHitTest(CPoint pt)
{
  CRect rc;
  GetClientRect(&rc);
  ClientToScreen(&rc);
  return rc.PtInRect(pt) ? HTCAPTION : CFrameWnd::OnNcHitTest(pt);
}
