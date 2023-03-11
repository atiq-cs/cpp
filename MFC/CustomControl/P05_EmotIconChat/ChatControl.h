//
//  Remarks :
//    - Derived from CWnd (alternative is CStatic)
//    created automatically by dialog using resource file
//    However, CStatic has some features like acquiring bitmap which are not required for our
//    purpose, ref 1 (below)
//  Refs    :
//    1. MSFT - https://learn.microsoft.com/en-us/cpp/mfc/reference/cstatic-class
//    2. Chris Maunder, founder of codeproject has created a custom control, article,
//      CP - http://www.codeproject.com/Articles/521/Creating-Custom-Controls
//    3. Article we are following,
//    CP - http://www.codeproject.com/Articles/5032/Creating-and-Using-custom-controls-in-VC
//


#pragma once
#include "afxwin.h"
#include <vector>
#include "resource.h"    // for IDC_CHATCUSTOM
#define CUSTOMWNDCLASS TEXT("CChatControl")


class CMainDlg;
class CChatRecordDB;
// sent status updates
enum MESSAGE_SEND_STATUS { Trying, Pending, Delivered, Failed };

// item field type, type for members of chat items
// we could reuse CHATBOX_ELEMENT_TYPE for CChatUIPainter but we may need our own in future if there is structural change to the declation of CHATBOX_ELEMENT
enum CHATBOX_FIELD_TYPE { FieldDateType, FieldNameType, FieldMessageType, FieldTimeType, FieldDeliveryStatusType };

// element type
enum CHATBOX_ELEMENT_TYPE { ElemDateType, ElemNameType, ElemMessageType, ElemEmotIconType, ElemTimeType, ElemDeliveryStatusType };

// structure for maintaining paint UI elements
typedef struct _CHATBOX_ELEMENT {
  CHATBOX_ELEMENT_TYPE type;    // type of elements
  CString sText;          // message data, date, time, emo index only in case of emo
  CPoint ptStart;
  CSize csz;
  // int recordIndex;      // index on chat records, to facilitate a mapping
} CHATBOX_ELEMENT;

// Replace vector when random access is required or we encounter a problem with CList which deduces CList as buggy
// structure for maintaining chat items
// Single record definition
typedef struct _CHATBOX_ITEM {
  MESSAGE_SEND_STATUS send_status;    // SENT, PENDING, DELIVERED
  CString sMessage;              // message data
  //CTime  msgTimeDate;            // for keeping date and time of last sent message
  // CString  time;
  // CString  date;
  CTime timedate;
  CString sUserName;
  std::vector<CHATBOX_ELEMENT> vUIElements;
  // int UIElemIndex;
  // CString user_image_path;     not used
} CHATBOX_ITEM;

class CChatControl :
  public CWnd
{
public:
  CChatControl(CMainDlg* pDlg);    // requires public access for construction from Dialog class
  ~CChatControl(void);                // requires public access for destruction from Dialog class

protected:
// Implementation
  void OnInitChatControl();
  BOOL RegisterWndClass();
public:
  void PostChatMessage(CString chat_message, CTime timedate);

// UI paint functions
protected:
  void PaintUIElements();
  int AddChatItem(CHATBOX_ITEM& chatItem);
  int CreatePaintElement(CHATBOX_ITEM& chatItem);
    // functions to pre-calculate drawing elements
  int AddPaintElement(CHATBOX_ITEM& chatItem, CHATBOX_FIELD_TYPE strType);

  // for drawing pre-calculation
  int DrawMessageEmo(CString message);
  void DrawChatText(CString str);
  bool VirtualDrawTextMultiLine(CString str);
  void VirtualDrawEmotIcon(int emoIndex);
  CString ExtractFittableLineFromStr(const CString str);
  int GetFittablePositionRecursive(const CString str, int iMin, int iMax);
  bool IsFittableInRectangle(const CString gStr, const int index);
  BOOL SaveChatHistory();


  void PaintElements();

  int FindEmoCode(int startIndex, CString str, int& foundEmoIndex);
  void UpdateNextElementsCordinates(int yOffset);

// Message Handlers
  //afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct) ;
  afx_msg void OnPaint( );
  afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
  DECLARE_MESSAGE_MAP()
  virtual void PreSubclassWindow();
  // afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
    // Dialog Data
  enum { IDD = IDC_CHATCUSTOM };

private:
// Data members
  int m_nMaxScreen;
  int m_yItem;
  int m_yClient;    // height of client rectangle
  int m_nMaxLines;
  int m_nMaxScroll;
  int m_yScrollAmount;
  int m_cyScrollUnit;
  int m_cyChatItem;

  //int startUIElemIndex;
  //int endUIElemIndex;
  
  int m_cxChatText;    // defines where message text ends and x from where time will be painted from
  int m_cxChatTextHSpace;

  CFont m_dateFont;
  CFont m_headingFont;
  CFont m_textFont;
  CFont m_timeFont;

  // font heights
  int m_yCharDate;
  int m_yCharHeading;
  int m_yCharChatText;
  int m_yCharTime;

  // CSize m_clientSize;
  int m_cxTimeWidth;
  int m_cxDeliveryStatusWidth;
  bool m_bScrollbarEnabled;
  int m_cxScrollbarWidth;
  // int lastSBACtion;
  // CHATBOX_SHARED_DATA lastPaintElement;

  // UI members and properties
  //string and variables
  CPoint m_ptStart;    // draw from this point
  CPoint m_ptClipStart;  // left top point of clip rectangle
  CPoint m_ptEnd;    // this is the limiting point

  // DC for painting
  CDC* m_pDC;
  CFont* m_pOldFont;

  //CString m_sHeadingText;
  //CString m_sDateText;
  CMainDlg* m_pMainDlg;
  TCHAR **pEmoCodesList;
  int m_iChatItemInsertionIndex;

  CChatRecordDB* g_pChatRecords;
  // CHATBOX_ITEM m_currentChatItem;

  // vector ref: cpp vector
  std::vector<CHATBOX_ITEM> m_vChatRecords;
  //std::vector<CHATBOX_ELEMENT> chatUIElements;
};

// there is a mistake inside the example code in referred URL below
//  http://www.cprogramming.com/tutorial/functors-function-objects-in-c++.html
// 
class ChatItemSorter
{
    public:
        // take the field to sort by in the constructor
    ChatItemSorter() {}
        ChatItemSorter (const CHATBOX_ITEM& item) : m_cItem( item ) {}

        bool operator() (const CHATBOX_ITEM& lhs, const CHATBOX_ITEM& rhs)
        {
            // get the field to sort by and make the comparison
            return (lhs.timedate < rhs.timedate);
        }

    private:
        CHATBOX_ITEM m_cItem;
};

// Other functions which are good without sharing data from the class
bool IsPointInsideClipRectangle(const CPoint topLeft, const CPoint bottomRight, const CPoint point);
