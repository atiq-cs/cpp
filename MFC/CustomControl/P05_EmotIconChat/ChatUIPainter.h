enum CHATBOX_FIELD_TYPE;
struct CHATBOX_ELEMENT;
typedef struct CHATBOX_ELEMENT CHATBOX_ELEMENT;

struct CHATBOX_SHARED_DATA;
typedef struct CHATBOX_SHARED_DATA CHATBOX_SHARED_DATA;

#pragma once
class CChatUIPainter
{
private:
  // DC for painting
  CDC* pDC;
  // CRect rcClip;    // clip rectangle, for restoring points before drawing

  CFont* pOldFont;
  // Fonts for chat elements
  CFont* dateFont;
  CFont* headingFont;
  CFont* sendFont;
  CFont* timeFont;
  // font heights
  BYTE yCharDate;
  BYTE yCharHeading;
  BYTE yCharSend;
  BYTE yCharTime;

  int cxChatText;
  int cyChatItem;    // item means entire row

  // BYTE processingStage;

  //string and variables
  CPoint ptStart;    // draw from this point
  CPoint ptClipStart;  // left top point of clip rectangle
  CPoint ptEnd;    // this is the limiting point
  // CPoint& bakPtStart;    // draw from this point
  CHATBOX_SHARED_DATA& lastChatItemData;
  int  yScroll;
  CString headingText;
  CString dateText;

  // spacing and alingment
  const int cxChatTextHSpace;

  CList<CHATBOX_ELEMENT, CHATBOX_ELEMENT&>& m_rUIElement;

  // for drawing
  int DrawMessageEmo(CString message);
  void DrawChatText(CString str);
  bool VirtualDrawTextMultiLine(CString str);
  void VirtualDrawEmotIcon();
  CString ExtractFittableLineFromStr(const CString str);
  int GetFittablePositionRecursive(const CString str, int iMin, int iMax);
  bool IsFittableInRectangle(const CString gStr, const int index);
  bool IsPointInsideClipRectangle(const CPoint topLeft, const CPoint bottomRight, const CPoint point);

public:
  CChatUIPainter(CDC* paintDC, CList<CHATBOX_ELEMENT, CHATBOX_ELEMENT&>& rUIElement, int yPos, int timeWidth, CHATBOX_SHARED_DATA& lpItem);
  ~CChatUIPainter(void);
  void SetFonts(CFont* pfontArray, int* pfontHeight);
  // int DrawElement(CHATBOX_FIELD_TYPE, CString);

  // functions to pre-calculate drawing elements
  int AddPaintElement(const CString gStr, CHATBOX_FIELD_TYPE strType);
  // void SetItem(CHATBOX_ITEM& chatItem);
  // bool hasNext();
  void PaintElements();
  // void LoadLastChatElement();
  void RestorePaintUI();
};
