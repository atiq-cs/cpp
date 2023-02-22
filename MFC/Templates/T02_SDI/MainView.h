
// MainView.h : interface of the CMainView class
//

#pragma once


class CMainView : public CView
{
protected: // create from serialization only
  CMainView() noexcept;
  DECLARE_DYNCREATE(CMainView)

// Attributes
public:
  CMainDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
  virtual void OnDraw(CDC* pDC);  // overridden to draw this view
  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
  virtual ~CMainView();
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
  DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MainView.cpp
inline CMainDoc* CMainView::GetDocument() const
   { return reinterpret_cast<CMainDoc*>(m_pDocument); }
#endif

