#pragma once


// CListCtrlEmo

class CListCtrlEmo : public CListCtrl
{
  DECLARE_DYNAMIC(CListCtrlEmo)

public:
  CListCtrlEmo();
  virtual ~CListCtrlEmo();
  // public functions, allow access from other classes
  void InsertItemEmo(int itemIndex, LPCTSTR m_chatInStr);

protected:
  afx_msg void OnNMCustomdrawListEmo(NMHDR *pNMHDR, LRESULT *pResult);
  DECLARE_MESSAGE_MAP()

private:
  void DrawSubItem( CDC& dc, int nIndex, int nSubIndex );
  void DrawSubItemEmo( CDC& dc, int nIndex, int nSubIndex );
  void CalculateItemRect( int nIndex, CRect& rect );
  int DrawBitmap(CDC* pDC, CRect* limitRect);
};
