////////////////////////////////////////////////////////////////
// MSDN Magazine -- December 2002
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// Compiles with VC 6.0 or VS.NET on Windows XP. Tab size=3.
//
class CMainFrame : public CFrameWnd {
public:
  virtual ~CMainFrame();

protected:
  CStatusBar  m_wndStatusBar;
  CToolBar    m_wndToolBar;
  CRect      m_rcRestore;
  CMainFrame();

  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpmmi);
  afx_msg void OnViewFullScreen();
  afx_msg void OnUpdateViewFullScreen(CCmdUI* pCmdUI);
  afx_msg UINT OnNcHitTest(CPoint point);

  DECLARE_DYNCREATE(CMainFrame)
  DECLARE_MESSAGE_MAP()
};
