#pragma once
#define MYWNDCLASS L"ChatHistory"
#define OFFSETINC 20
#define TXTLINEBUF 45

// ChatHistory

class ChatHistory : public CWnd
{
  DECLARE_DYNAMIC(ChatHistory)

private:
  CDC* m_pDC;
  WCHAR *m_message, m_crop[1000];
  INT offset_Y, m_len;
  CPoint m_ptClipStart, m_ptClipEnd;
  int m_nMaxScroll;
public:
  ChatHistory();
  virtual ~ChatHistory();

  BOOL RegisterWndClass();

protected:
  DECLARE_MESSAGE_MAP()
public:
  bool post(WCHAR *message, CTime m_time);
  
  afx_msg void OnPaint();
  afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
  afx_msg void OnSize(UINT nType, int cx, int cy);
  void DrawBitmap(CDC * pDc, const int b_ID = 0);
};


