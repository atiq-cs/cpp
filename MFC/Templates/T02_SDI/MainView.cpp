
// MainView.cpp : implementation of the CMainView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Main.h"
#endif

#include "MainDoc.h"
#include "MainView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainView

IMPLEMENT_DYNCREATE(CMainView, CView)

BEGIN_MESSAGE_MAP(CMainView, CView)
END_MESSAGE_MAP()

// CMainView construction/destruction

CMainView::CMainView() noexcept
{
  // TODO: add construction code here

}

CMainView::~CMainView()
{
}

BOOL CMainView::PreCreateWindow(CREATESTRUCT& cs)
{
  // TODO: Modify the Window class or styles here by modifying
  //  the CREATESTRUCT cs

  return CView::PreCreateWindow(cs);
}

// CMainView drawing

void CMainView::OnDraw(CDC* /*pDC*/)
{
  CMainDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  if (!pDoc)
    return ;

  // TODO: add draw code for native data here
}


// CMainView diagnostics

#ifdef _DEBUG
void CMainView::AssertValid() const
{
  CView::AssertValid();
}

void CMainView::Dump(CDumpContext& dc) const
{
  CView::Dump(dc);
}

CMainDoc* CMainView::GetDocument() const // non-debug version is inline
{
  ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMainDoc)));
  return (CMainDoc*)m_pDocument;
}
#endif //_DEBUG


// CMainView message handlers
