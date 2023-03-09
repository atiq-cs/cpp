////////////////////////////////////////////////////////////////
// MSDN Magazine -- December 2002
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// Compiles with VC 6.0 or VS.NET on Windows XP. Tab size=3.
//
class CMyView : public CView {
public:
  virtual ~CMyView();
  CMyDoc* GetDocument() { return (CMyDoc*)m_pDocument; }
  virtual void OnDraw(CDC* pDC);  // overridden to draw this view

protected:
  BOOL    m_bMoving; // moving the window?
  CPoint  m_ptPrev;  // previous point while moving
  CMyView();

  afx_msg UINT OnNcHitTest(CPoint point);

  DECLARE_DYNCREATE(CMyView)
  DECLARE_MESSAGE_MAP()
};
