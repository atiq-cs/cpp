#pragma once


// CBitmapViewer

class CBitmapViewer : public CWnd
{
  DECLARE_DYNAMIC(CBitmapViewer)

public:
  CBitmapViewer();
  virtual ~CBitmapViewer();

  BOOL SetBitmap(UINT nIDResource);

protected:
  CBitmap m_Bitmap;
  DECLARE_MESSAGE_MAP()
  BOOL RegisterWindowClass();
  
  
public:
  afx_msg void OnPaint();
  afx_msg BOOL OnEraseBkgnd(CDC* pDC);
  BOOL Create(CWnd* pParentWnd, const RECT& rect, UINT nID, DWORD dwStyle = WS_VISIBLE);
};


