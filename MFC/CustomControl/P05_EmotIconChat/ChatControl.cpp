//
//  PURPOSE : Custom control for Chat with Emot Icon Support
//  Date    : 12-2013
//  Remarks :
//    - We create a new window class for our control; register it into the system, control window is
//    created automatically by dialog using resource file.
//    - Custom Drawing operations implemented
//    - Hence, scrollbar is automatically added to the control.
//    - Implements drawing and chat data structure for it
//    - Two senders are randomly selected to simulate sender and recipients of instant messaging
//
//   Instantiation flow (moved from ChatUIPainter.h)
//    - An object of the class is instantiated right after the call of BeginPaint of OnPaint
//     function
//    - It is destroyed when that function exits
//    - Input to this class is the CDC, using which we perform all drawing operations
//    - We also handle relaled drawing for scrollbar operations, and for future OnSize operation
//
//    Demos,
//    - SQLite DB
//    - Custom Control
//
//   Refs,
//   - look at ReadMe
//


#include "stdafx.h"
#include "ChatControl.h"
#include "MainDlg.h"  // for referene to this dialog
#include "ChatRecordDB.h"
// #include "ChatUIPainter.h"  // for custom drawing operation class
// #include <math.h>    // for ceil


// Contructor
CChatControl::CChatControl(CMainDlg* pDlg):
  m_nMaxScreen(0),
  m_yItem(0),
  m_nMaxScroll(0),
  m_cxTimeWidth(0),
  m_cxDeliveryStatusWidth(17),
  m_nMaxLines(0),
  m_yScrollAmount(0),
  m_yClient(0),
  m_cyChatItem(0),
  m_cxScrollbarWidth(18),
  m_bScrollbarEnabled(false),
  m_cyScrollUnit(0),
  // startUIElemIndex(0),
  // endUIElemIndex(-1),
  m_pDC(NULL),
  m_pOldFont(NULL),
  // m_sDateText(TEXT("")),
  // m_sHeadingText(TEXT("")),
  m_cxChatText(0),
  m_cxChatTextHSpace(2),
  m_pMainDlg(pDlg),
  pEmoCodesList(NULL),
  m_iChatItemInsertionIndex(0)
  // isAlternateNameColor(false)
  // lastSBACtion(0)
{
  // Register our custom chat control class
  if (RegisterWndClass() == FALSE) {
    AfxMessageBox(_T("Window proc registration failed"), MB_OK);
  }

  m_yCharDate = m_yCharHeading = m_yCharChatText = m_yCharTime = 0;

  // Create database here if it does not exist
  // If it exists, open it and load records
  g_pChatRecords = new CChatRecordDB();

  if (NULL == g_pChatRecords || FALSE == g_pChatRecords->LoadDatabase(m_vChatRecords))
  {
    // MessageBox(NULL, L"Create Database Failure.", L"Database", MB_OK);
    MessageBox(_T("Create Database Failure"), _T("Database"), MB_ICONERROR | MB_OK);

    delete g_pChatRecords;
    g_pChatRecords = NULL;
  }
}

// Clane up: delete anything we have manually created/allocated
CChatControl::~CChatControl(void)
{
  // store info back to database
  SaveChatHistory();

  // delete fonts objects
  m_dateFont.DeleteObject();
  m_headingFont.DeleteObject();
  m_textFont.DeleteObject();
  m_timeFont.DeleteObject();

  if (g_pChatRecords) {
    delete g_pChatRecords;
    g_pChatRecords = NULL;
  }
}

// registers the window class for custom control
// without registering control window creation will not succeed
BOOL CChatControl::RegisterWndClass() {
  // Register your unique class name that you wish to use
  //   https://learn.microsoft.com/en-us/cpp/mfc/reference/application-information-and-management?#afxregisterclass
  WNDCLASS wndcls;
  HINSTANCE hInst = AfxGetInstanceHandle();

  memset(&wndcls, 0, sizeof(WNDCLASS));   // start with NULL defaults

  //Check weather the class is registerd already
  if (!(::GetClassInfo(hInst, CUSTOMWNDCLASS, &wndcls)))
  {
    wndcls.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
    //you can specify your own window procedure
    wndcls.lpfnWndProc = ::DefWindowProc; 
    wndcls.hInstance = hInst;
    // set it later, when we have an icon
    //wndcls.hIcon = LoadIcon(wndcls.hInstance, MAKEINTRESOURCE(IDI_MYICON));
    wndcls.hIcon = NULL;
    wndcls.hCursor = LoadCursor(wndcls.hInstance, MAKEINTRESOURCE(IDC_ARROW));
    wndcls.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wndcls.lpszMenuName = NULL;
    // Specify your own class name for using FindWindow later
    wndcls.lpszClassName = CUSTOMWNDCLASS;

    // Register the new class and trace if it fails 
    if(!AfxRegisterClass(&wndcls))
    {
        TRACE("Class Registration Failed\n");
        return FALSE;
    }
  }

  /* ref: https://www.codeproject.com/Articles/5032/Creating-and-Using-custom-controls-in-VC  
  WNDCLASS windowclass;

  //Check weather the class is registerd already
  if (!(::GetClassInfo(hInst, CUSTOMWNDCLASS, &windowclass)))
  {
    //If not then we have to register the new class
    windowclass.style = CS_DBLCLKS;// | CS_HREDRAW | CS_VREDRAW;
    windowclass.lpfnWndProc = ::DefWindowProc;
    windowclass.cbClsExtra = windowclass.cbWndExtra = 0;
    windowclass.hInstance = hInst;
    windowclass.hIcon = NULL;
    windowclass.hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
    windowclass.hbrBackground = ::GetSysColorBrush(COLOR_WINDOW);
    windowclass.lpszMenuName = NULL;
    windowclass.lpszClassName = CUSTOMWNDCLASS;

    if (!AfxRegisterClass(&windowclass))
    {
        AfxThrowResourceException();
        return FALSE;
    }
  }*/

  return TRUE;
}

BEGIN_MESSAGE_MAP(CChatControl, CWnd)
  // ON_WM_CREATE() doesn't work dialog box creates controls from resource earlier, use PreSubClassWindow instead
  ON_WM_PAINT()
  ON_WM_VSCROLL()
  ON_WM_SIZE()
  ON_WM_MOUSEHWHEEL()
END_MESSAGE_MAP()

/*
OnCreate is not reached as WM_CREATE message is suppressed
int CChatControl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
  if (CWnd::OnCreate(lpCreateStruct) == -1)
    return -1;
  
  return 0;
}*/

// CWnd Class - https://learn.microsoft.com/en-us/cpp/mfc/reference/cwnd-class
void CChatControl::PreSubclassWindow()
{
  // TODO: Add your specialized code here and/or call the base class
  OnInitChatControl();

  CWnd::PreSubclassWindow();
}

// Perform initialization before window creation here
void CChatControl::OnInitChatControl() {
  // Create required fonts
  // CFont Class - https://learn.microsoft.com/en-us/cpp/mfc/reference/cfont-class
  LOGFONT lf;

  // Date font
  memset(&lf, 0, sizeof(LOGFONT));       // zero out structure
  lf.lfHeight = 20;                      // request a 16-pixel-height font
  // lf.lfWeight = FW_DEMIBOLD;
  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("Arial"), 7);                    // request a face name "Arial"
  VERIFY(m_dateFont.CreateFontIndirect(&lf));  // create the font 

  // heading font
  memset(&lf, 0, sizeof(LOGFONT));       // zero out structure
  lf.lfHeight = 16;                      // request a 16-pixel-height font
  lf.lfWeight = FW_DEMIBOLD;
  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, 
     _T("Times New Roman"), 7);                    // request a face name "Times New Roman"
  VERIFY(m_headingFont.CreateFontIndirect(&lf));  // create the font 

  // text font
  memset(&lf, 0, sizeof(LOGFONT));       // zero out structure
  lf.lfHeight = 14;                      // request a 14-pixel-height font
  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, 
     _T("Verdana"), 7);                    // request a face name "Verdana"
  VERIFY(m_textFont.CreateFontIndirect(&lf));  // create the font 
  
  // time font
  memset(&lf, 0, sizeof(LOGFONT));       // zero out structure
  lf.lfHeight = 12;                      // request a 12-pixel-height font
  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, 
     _T("Verdana"), 7);                    // request a face name "Verdana"
  VERIFY(m_timeFont.CreateFontIndirect(&lf));  // create the font

  // Pre-calculate font heights

  // Get the handle to the client area's device context, use GETDC to retrieve outside of WM_Paint
  CDC* pdc = GetDC(); 

  // ref: https://learn.microsoft.com/en-us/cpp/atl-mfc-shared/reference/csize-class?#csize
  m_cxTimeWidth = pdc->GetOutputTextExtent(TEXT("11:59:59 PM")).cx;
  // quick fix, need to improve the logic
  // deliveryStatusWidth += scrollbarWidth;

  // Extract font dimensions from the text metrics. 
  TEXTMETRIC tm;
  // get height for font 0
  CFont* pOldFont = pdc->SelectObject(&m_dateFont);
  pdc->GetTextMetrics(&tm);

  // xChar = tm.tmAveCharWidth; 
  // xUpper = (tm.tmPitchAndFamily & 1 ? 3 : 2) * xChar/2; 
  m_yCharDate = tm.tmHeight + tm.tmExternalLeading + 4;
  m_cyScrollUnit = m_yCharDate;

  // get height for font 1
  pdc->SelectObject(&m_headingFont);
    pdc->GetTextMetrics(&tm);
  m_yCharHeading = tm.tmHeight + tm.tmExternalLeading + 4;
 
  // get height for font 2
  pdc->SelectObject(&m_textFont);
    pdc->GetTextMetrics(&tm);
  m_yCharChatText = tm.tmHeight + tm.tmExternalLeading+10;

  // get height for font 3
  pdc->SelectObject(&m_timeFont);
    pdc->GetTextMetrics(&tm); 
  m_yCharTime = tm.tmHeight + tm.tmExternalLeading; 

  // get clip rectangle fails here, probably control is not created yet

  // restore old font
  pdc->SelectObject(pOldFont);
  // Free the device context. 
  ReleaseDC(pdc);

  // perfect place for setting scroll bar, or use EnableScrollBarCtrl
  // ShowScrollBar(SB_VERT, FALSE);    // if we want the vertical scrollbar to hide explicitly
  /* MSFT - About Scroll Bars
    https://learn.microsoft.com/en-us/windows/win32/controls/about-scroll-bars

  Scroll Bar Visibility:
   The system hides and disables a standard scroll bar when equal minimum and maximum values are specified. The system also hides and disables a standard scroll bar if you specify a page size that
   includes the entire scroll range of the scroll bar. This is the way to temporarily hide a scroll bar when it is not needed for the content of the client area. There is no need to make scrolling
   requests through the scroll bar when it is hidden. The system enables the scroll bar and shows it again when you set the minimum and maximum values to unequal values or when the page size that 
   does not include the entire scroll range. The ShowScrollBar function can also be used to hide or show a scroll bar. It does not affect the scroll bar's range, page size, or scroll box position. 

   The EnableScrollBar function can be used to disable one or both arrows of a scroll bar. An application displays disabled arrows in gray and does not respond to user input. */
  // no lines in drawn in control initially, nothing to scroll
  SetScrollRange(SB_VERT, 0, 0, FALSE);
  
  // CTime timeDate = CTime::GetCurrentTime();
  // PostChatMessage(_T("lots of text"), timeDate);
  // m_chatBoxCtrl.SetWindowText(_T(""));

  // ref, MSFT - How to set focus in a dialog box
  // https://devblogs.microsoft.com/oldnewthing/20040802-00/?p=38283
  // GotoDlgCtrl(&m_chatBoxCtrl);
}

// Paint to draw the chat box
// to do tasks
// 1. has to set transparent
void CChatControl::OnPaint() {
  // avoid paint when record is inserted
  if (m_vChatRecords.empty()) {
    // Read from database
    // Dummy code to unblock tool-tip for all controls in the dialog
    // CTime timeDate = CTime::GetCurrentTime();
    // PostChatMessage(TEXT("test emo 1 :P emo2 :POOP"), timeDate);

    // PAINTSTRUCT ps;
    // m_pDC = BeginPaint(&ps);
    // m_pDC->TextOut(0, 0, _T(" "));
    // EndPaint(&ps);
    // m_pDC = NULL;

    return ;
  }

  if (m_pDC)
    return ;

  if (m_ptEnd == CPoint(0,0))
    return ;

  PAINTSTRUCT ps;
  m_pDC = BeginPaint(&ps);

  // Initialization which were previously done in ChatUIPainter
  // get clip rectangle and save as points
  /* CRect rcClip;
  pDC->GetClipBox(&rcClip);
  ptClipStart = rcClip.TopLeft();    // draw from this point

  ptEnd = rcClip.BottomRight();    // this is the limiting point
  // ptEnd is only for chat text (not datetime or heading text)
  ptEnd.x -= timeWidth;    // for field type Time don't use ptEnd
  */

  // updated in PostchatMessage, no need to update on each paint
  // cxChatText = rcClip.Width() -  timeWidth;    // for field type Time use this instead

  // CChatUIPainter m_clsUIPainter(pDC, chatUIElements,  yScrollAmount, timeWidth, lastPaintElement);
  // m_clsUIPainter.SetFonts(m_fontArray, m_fontHeight);
  // m_clsUIPainter.PaintElements();
  PaintUIElements();

  // restore font
  if (m_pOldFont) {
    m_pDC->SelectObject(&m_pOldFont);
    m_pOldFont = NULL;
  }

  if (m_pDC)
    m_pDC = NULL;

  EndPaint(&ps);
}

// in case user resizes the window, fix page size
void CChatControl::OnSize(UINT nType, int cx, int cy)
{
  CWnd::OnSize(nType, cx, cy);
}

// MFC scrolling implementation example
//  ref CWnd class
void CChatControl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
  int CurPos = GetScrollPos(SB_VERT);
  int yPos = CurPos;
  // lastSBACtion = nSBCode;

  switch (nSBCode) {
    // User clicked the HOME keyboard key.
    case SB_TOP:
      CurPos = 0;
      break;

    // User clicked the END keyboard key.
    case SB_BOTTOM:
      CurPos = m_nMaxScroll;
      break;

    // User clicked the top arrow.
    case SB_LINEUP:
      CurPos = max(0, CurPos-1);
      break;

    // User clicked the bottom arrow.
    case SB_LINEDOWN:
      CurPos = min(m_nMaxScroll, CurPos+1);
      break;

    // User clicked the scroll bar shaft above the scroll box.
    case SB_PAGEUP:
    {
      // Get the page size
      SCROLLINFO   si;
      GetScrollInfo(SB_VERT, &si);
   
      CurPos = max(0, CurPos - (int) si.nPage);
      // si.nPos -= si.nPage;
      break;
              
    }
    // User clicked the scroll bar shaft below the scroll box.+-
    case SB_PAGEDOWN:
    {
      // Get the page size. 
      SCROLLINFO   si;
      GetScrollInfo(SB_VERT, &si);
      CurPos = min(m_nMaxScroll, CurPos + (int) si.nPage);
      break;
      // si.nPos += si.nPage;
    }
    // User dragged the scroll box.
    case SB_THUMBTRACK:
      CurPos = nPos;
     // si.nPos = si.nTrackPos;
      break;

    default:
      break; 
  }

  if (CurPos != yPos) {
    SetScrollPos(SB_VERT, CurPos);
    // ref CWnd Class
    // yAmount: Specifies the amount, in device units, of vertical scrolling. This parameter must be a negative value to scroll up.
    // differs 284 - 241

    // scrolling to other position from Max Scroll position
    // we need to 
    //  && CurPos == nMaxScroll-1
    int scrollY = 0;
    if (yPos==m_nMaxScroll) {
      scrollY =  (m_yItem-m_yClient) % m_cyScrollUnit-m_cyScrollUnit;
    }
    else if (CurPos == m_nMaxScroll) {
      scrollY =  m_cyScrollUnit-(m_yItem-m_yClient) % m_cyScrollUnit;
    }
    scrollY += m_cyScrollUnit * (yPos-CurPos);
    m_yScrollAmount -= scrollY;
    ScrollWindow(0, scrollY);

    /*{
      //yScrollAmount = 0;
      // adjust extra scrolling
      int scrollY = yScrollAmount % cyScrollUnit;
      yScrollAmount -= scrollY;
          ScrollWindow(0, scrollY);
      // Invalidate();
    }
    else if (yPos==nMaxScroll-1 && CurPos == nMaxScroll) {
    }*/
    // else {
      // scrollY += cyScrollUnit * (yPos-CurPos);
      // yScrollAmount -= ;
      // yScrollAmount -= scrollY;

      // ScrollWindow(0, cyScrollUnit * (yPos-CurPos));
      // ScrollWindow(0, scrollY);
    // Invalidate();

    /*if (invalideRectList.IsEmpty() == false) {
      POSITION pos = invalideRectList.GetHeadPosition();
      int i = 0;
      // ** implement drawing according to co-ordinates of update region
      //  && endUIElemIndex == -1
      for (; i < invalideRectList.GetCount(); i++)
      {
        CRect invalidRect = (CRect) invalideRectList.GetNext(pos);
        invalidRect.top += cyScrollUnit * (yPos-CurPos);
        invalidRect.bottom += cyScrollUnit * (yPos-CurPos);
        InvalidateRect(invalidRect);
      }
      invalideRectList.RemoveAll();
    }*/
    UpdateWindow ();
  }

  CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

// post chat message to display on custom chat box
// this function has the responsibility to set everything up
// so that next OnPaint can easily draw elements and scrollbar with appropriate positions
void CChatControl::PostChatMessage(CString chat_message, CTime time_date) {
  // construct new chat item
  CHATBOX_ITEM m_currentChatItem = {};
  m_currentChatItem.sMessage = chat_message;
  // m_currentChatItem.date = TEXT("TODAY");
  // m_currentChatItem.timedate = TEXT("TODAY");

  // Set a random user name
  /* Seed the random-number generator with current time so that
   * the numbers will be different every time we run.
   * cpp Rand - https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/rand
   */
    srand( (unsigned) time( NULL ) );
  bool isRecievedFromNetwork = (bool) ((rand()) % 2);
  if (isRecievedFromNetwork) {
    m_currentChatItem.sUserName = TEXT("Client 01");
  }
  else {
    m_currentChatItem.sUserName = TEXT("Client 02");

    // Convert the time to GMT/UTC
    CTimeSpan tz(0, 6, 0, 0);  // for timezone
    time_date -= tz;

    // convert time to local now
    // MSFT - How to convert UTC time to local time
    //  https://support.microsoft.com/en-us/topic/how-to-convert-utc-time-to-local-time-0569c45d-5fb8-a516-814c-75374b44830a
    FILETIME FileTime, LocalFileTime;
    SYSTEMTIME UTCTime, LocalTime;

    // CTime Class
    // https://learn.microsoft.com/en-us/cpp/atl-mfc-shared/reference/ctime-class
    time_date.GetAsSystemTime(UTCTime);
    SystemTimeToFileTime(&UTCTime,&FileTime);
    FileTimeToLocalFileTime(&FileTime, &LocalFileTime);
    FileTimeToSystemTime(&LocalFileTime, &LocalTime);
    time_date = CTime(LocalTime);

    // to simulate out of order timestamp
    // randomize time, expect time as gmt as well
    int randOffset = ((int) rand()) % 3600;
    int minOffest = randOffset / 60;
    int secOffset = randOffset % 60;
    CTimeSpan tzRev(0, 0, minOffest, secOffset);  // for timezone
    time_date -= tzRev;
  }

  m_currentChatItem.timedate = time_date;

  m_currentChatItem.send_status = Trying;

  // insert the chat item into appropriate position
  int yItemDiff = AddChatItem(m_currentChatItem);

  // pre-calculation
  // get max number of lines fittable in client rect
  // we need this to calculate max scroll position
  if (m_nMaxScreen == 0) {
    // Get the device context
    CDC* pdc = GetDC();
    CRect rc;
    // gives wrong dimension
    // CSize sz = pDC->GetWindowExt();
    //nMaxScreen = sz.cy / m_fontHeight[2];
    pdc->GetClipBox(&rc);
    m_yClient = rc.Height();
    m_nMaxScreen = m_yClient / m_cyScrollUnit;
    /*CString dbgStr;
    dbgStr.Format(TEXT("exact mak screen lines = %f"), (double) (rc.Height()) / m_fontHeight[2]);
    AfxMessageBox(dbgStr, MB_OK);*/

    // Free the device context. 
    ReleaseDC(pdc);
  }

  /*int yExtra = (yItem - yClient) % cyScrollUnit;
  nMaxLines = yItem /  cyScrollUnit;
  if (yExtra)
    nMaxLines++;*/

  // Enable scrollbar if total height exceeds current client rectangle height for the first time
  // if scrollbar is already enabled
  //  check if we are in maxScrollPos, old one
  //   if yes then we have to scroll automatically 
  //   if no then we have to adjust scrollbar range and page size

  // total height exceeds current client rectangle height
  if (m_yClient < m_yItem) {
    // get current scroll position, no need to know this to verify condition for automatic scrolling
    int yScrollPos = 0;
    if (m_bScrollbarEnabled) {
      yScrollPos = GetScrollPos(SB_VERT);
    }

    // set scrollbar
    SCROLLINFO si;
    // Set the vertical scrolling range and page size
    si.cbSize = sizeof(si);
    // automaticlly scroll only if current scroll position is max
    // we use old nMaxScroll to check this
    if (yScrollPos==m_nMaxScroll) {
      m_yScrollAmount += yItemDiff;
      ScrollWindow(0, -yItemDiff);
      m_nMaxScroll = (m_yItem - m_yClient) % m_cyScrollUnit?(m_yItem - m_yClient) / m_cyScrollUnit+1:(m_yItem - m_yClient) / m_cyScrollUnit;
      si.nPos = m_nMaxScroll;
      si.fMask  = SIF_PAGE | SIF_RANGE | SIF_POS;
      // invalid the client rectangle if last element not been inserted on the end
      if (m_iChatItemInsertionIndex < (int) m_vChatRecords.size() -1)
        Invalidate();
    }
    else {
      si.fMask  = SIF_PAGE | SIF_RANGE;
      m_nMaxScroll = (m_yItem - m_yClient) % m_cyScrollUnit?(m_yItem - m_yClient) / m_cyScrollUnit+1:(m_yItem - m_yClient) / m_cyScrollUnit;
    }

    si.nMin = 0;
    m_nMaxLines = m_nMaxScreen + m_nMaxScroll;
    si.nMax = m_nMaxLines - 1;
    si.nPage  = m_nMaxScreen;
    SetScrollInfo(SB_VERT, &si);

    if (m_bScrollbarEnabled==false) {
      m_yScrollAmount = m_yItem - m_yClient;
      // Update paint elements here
      // Invalidate();  // need to redraw entire client as scrollbar is being drawn first time, to get time in correct position
      m_bScrollbarEnabled = true;
      //timeWidth -= 18;
      //deliveryStatusWidth -= scrollbarWidth;
      //ScrollWindow(0, );
      UpdateWindow();
    }
  }
  else {
    // Invalidate entire client area; client rectangle is redrawn when UpdateWindow is called.
    // improve this
    Invalidate();
    // Update Window to cause View to redraw.
    // how to update only a region
    UpdateWindow();
  }
}

#include <algorithm> // for lower_bound

int CChatControl::AddChatItem(CHATBOX_ITEM& chatItem) {
  // find lower bound to insert
  ChatItemSorter chatItemComparator;
  // <algorithm> functions
  // https://learn.microsoft.com/en-us/cpp/standard-library/algorithm-functions
  // And, SO - find lower bound
  // http://stackoverflow.com/questions/4940809/how-to-find-a-lower-bound-in-a-sorted-vector
  //
  // find proper position in descending order
  std::vector<CHATBOX_ITEM>::iterator it = std::lower_bound( m_vChatRecords.begin(), m_vChatRecords.end(), chatItem, chatItemComparator);
  // ref: http://stackoverflow.com/questions/2152986/best-way-to-get-the-index-of-an-iterator
  m_iChatItemInsertionIndex = it - m_vChatRecords.begin();

  // UI elements can appear out of order, so we need to update drawing starting point
  // get ptstart from current UI element that is mapped by chatRecord
  
  // update ptStart
  if (m_iChatItemInsertionIndex == 0) {
    m_ptStart = CPoint(0, 0);
  }
  else {
    std::vector<CHATBOX_ELEMENT> vCurUIElem = (it - 1)->vUIElements;
    int i=vCurUIElem.size()-1;
    for (; i < (int) vCurUIElem.size() && vCurUIElem[i].type != ElemMessageType; i--);
    m_ptStart.x = 0;
    m_ptStart.y = vCurUIElem[i].ptStart.y + vCurUIElem[i].csz.cy + 10;    // 10 to match with m_yCharChatText
  }

  m_vChatRecords.insert(it, chatItem);
  // Do preparsing here, for example, detecting all emot icons here so that it saves time for onPaint
  // add the chat item as UI Elements
  int yItemDiff = CreatePaintElement(m_vChatRecords[m_iChatItemInsertionIndex]);

  // update starting drawing point for all drawing elements
  if (m_vChatRecords.size() > 1 && m_iChatItemInsertionIndex < (int) m_vChatRecords.size()-1)
    UpdateNextElementsCordinates(yItemDiff);

  /* if (it == m_vChatRecords.begin()) {
    // m_uiIndex = 0;
    // m_currentChatItem.UIElemIndex = m_uiIndex;
    m_ptStart.x = 0;
    m_ptStart.y = 0;
    // m_uiIndex is index of insertion for 
    // we will try to eliminate use of return value for this function
    yItemDiff = CreatePaintElement(chatItem);
  }
  else if (it == m_vChatRecords.end()) {
    m_uiIndex = chatUIElements.size();
    m_currentChatItem.UIElemIndex = m_uiIndex;
    ptStart.y = chatUIElements.at(m_uiIndex-3).ptStart.y + chatUIElements.at(m_uiIndex-3).size.cy+m_yCharChatText;
    yItemDiff = CreatePaintElement(m_currentChatItem, m_uiIndex, recordIndex);
  }
  else {
    m_uiIndex = m_currentChatItem.UIElemIndex = it->UIElemIndex;
    ptStart = chatUIElements[m_uiIndex].ptStart;
    yItemDiff = CreatePaintElement(m_currentChatItem, m_uiIndex, recordIndex);
  }


  int v_index = it - chatRecords.begin() + 1;
  chatRecords.insert( it, m_currentChatItem ); // insert before iterator it
  // std::vector<CHATBOX_ITEM>::iterator v_it = 
  for (; v_index < (int)chatRecords.size(); v_index++) {
    chatRecords[v_index].UIElemIndex += m_uiIndex - m_currentChatItem.UIElemIndex;
  }*/

  return yItemDiff;
}

// Update elements for UI
// Each raw element can be output to the display using single textout or drawbitmap call
int CChatControl::CreatePaintElement(CHATBOX_ITEM& chatItem) {
  // pDC must be null for continueing
  if (m_pDC)
    return 0;
  // Get the device context
  m_pDC = GetDC();

  // get clip rectangle and save it
    //  concern: this causes trouble for minimize if controls are moved
  CRect rcClip;
  m_pDC->GetClipBox(&rcClip);
  m_ptClipStart = rcClip.TopLeft();    // draw from this point
  m_ptEnd = rcClip.BottomRight();    // this is the limiting point
  // ptEnd is only for chat text (not datetime or heading text or other elements)
  int resWidth = m_cxTimeWidth + m_cxDeliveryStatusWidth;
  if (m_bScrollbarEnabled == false)
    resWidth += m_cxScrollbarWidth;
  m_ptEnd.x -= resWidth;    // for field type Time don't use ptEnd
  m_cxChatText = m_ptEnd.x - m_ptClipStart.x;    // for field type Time use this instead

  int preYItem = m_yItem;
  // _tcsftime   ref
  // https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/strftime-wcsftime-strftime-l-wcsftime-l
  m_yItem += AddPaintElement(chatItem, FieldDateType);
  m_yItem += AddPaintElement(chatItem, FieldNameType);
  
  // will add 0 anyway, but this y Offset will be added by AddPaintElement for FieldTimeType
  m_yItem += AddPaintElement(chatItem, FieldMessageType);
  m_yItem += AddPaintElement(chatItem, FieldTimeType);
  m_yItem += AddPaintElement(chatItem, FieldDeliveryStatusType);

    // Free the device context. 
    ReleaseDC(m_pDC);
  m_pDC = NULL;
  return (m_yItem  - preYItem);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// UI Paint functions start
int CChatControl::AddPaintElement(CHATBOX_ITEM& chatItem, CHATBOX_FIELD_TYPE strType) {
  std::vector<CHATBOX_ELEMENT> &vUIElements = chatItem.vUIElements;

  // logic derived from drawElement
  switch(strType) {
  case FieldDateType:
  {
    CString sCurrentDate = chatItem.timedate.Format(_T("%B %d, %Y"));
    CString csPreviousDate;    // previous date
    if (m_iChatItemInsertionIndex > 0)
      csPreviousDate = m_vChatRecords[m_iChatItemInsertionIndex-1].timedate.Format(_T("%B %d, %Y"));
    // set date font
    if (m_pOldFont == NULL)
      m_pOldFont = m_pDC->SelectObject(&m_dateFont);
    else
      m_pDC->SelectObject(&m_dateFont);
    int preY = m_ptStart.y;
    // add vertical space from second time
    if (!csPreviousDate.IsEmpty() && sCurrentDate != csPreviousDate)
      m_ptStart.y += m_yCharDate;

    // calculate dimension only if different
    if (sCurrentDate != csPreviousDate) {
      // get extent of heading Text
      CSize size = m_pDC->GetOutputTextExtent(sCurrentDate);

      // add vertical space between chat items when headingText is different
      CHATBOX_ELEMENT tmp = { ElemDateType, sCurrentDate, m_ptStart, size };
      //chatUIElements.push_back(tmp);

      // ref: http://stackoverflow.com/questions/671423/c-stl-vectors-get-iterator-from-index
      vUIElements.push_back(tmp);
      m_ptStart.y += m_yCharDate;
    }

    return (m_ptStart.y-preY);
  }
  case FieldNameType:
  {
    CString csPreviousName;    // previous date
    if (m_iChatItemInsertionIndex > 0)
      csPreviousName = m_vChatRecords[m_iChatItemInsertionIndex-1].sUserName;

    // set name heading font
    if (m_pOldFont == NULL)
      m_pOldFont = m_pDC->SelectObject(&m_headingFont);
    else
      m_pDC->SelectObject(&m_headingFont);
    int preY = m_ptStart.y;
    // add space from second time
    if (!csPreviousName.IsEmpty() && csPreviousName != chatItem.sUserName)
      m_ptStart.y += m_yCharHeading/2;

    // int res = 0;
    // draw only if different
    if (csPreviousName != chatItem.sUserName) {
      // get extent of heading Text
      CSize size = m_pDC->GetOutputTextExtent(chatItem.sUserName);

      // add vertical space between chat items when headingText is different
      CHATBOX_ELEMENT tmp = { ElemNameType, chatItem.sUserName, m_ptStart, size };
      // chatUIElements.push_back(tmp);

     // ref: http://stackoverflow.com/questions/671423/c-stl-vectors-get-iterator-from-index
      vUIElements.push_back(tmp);
      m_ptStart.y += m_yCharHeading;
    }

    return (m_ptStart.y-preY);
  }
  case FieldMessageType:
  {
    // set chat text font
    m_pDC->SelectObject(m_textFont);
    CPoint oldPoint = m_ptStart;

    // draw text with emo if exists
    // clip width is lessed by date time clip
    // use variable cyChatItem to store the height, have to add after drawing date time
    // DrawMessageEmo does/should not touch draw ending point, it should work with a copy of ptEnd
    m_cyChatItem = DrawMessageEmo(chatItem.sMessage);
    m_ptStart = oldPoint;
    return m_cyChatItem;
  }
  case FieldTimeType:
  {
    CString sCurrentTime = chatItem.timedate.Format(_T("%I:%M:%S %p"));    // current item's time element
    // set font for time
    if (m_pOldFont == NULL)
      m_pOldFont = m_pDC->SelectObject(&m_timeFont);
    else
      m_pDC->SelectObject(&m_timeFont);

    // get extent of time Text
    CSize size = m_pDC->GetOutputTextExtent(sCurrentTime);
    // does ChatUIPainter has knowledge on where the starting drawing point of time would be??
    // let' see we have 
    CPoint ptTime = CPoint(m_cxChatText, m_ptStart.y);
    CHATBOX_ELEMENT tmp = { ElemTimeType, sCurrentTime, ptTime, size };
    vUIElements.push_back(tmp);
    return 0;
  }
  case FieldDeliveryStatusType:
  {
    // set font for time
    if (m_pOldFont == NULL)
      m_pOldFont = m_pDC->SelectObject(&m_timeFont);
    else
      m_pDC->SelectObject(&m_timeFont);

    CPoint delivPtStart(m_cxChatText+m_cxTimeWidth+1, m_ptStart.y);
    CHATBOX_ELEMENT tmp = { ElemDeliveryStatusType, TEXT(""), delivPtStart, CPoint(m_cxDeliveryStatusWidth, m_cxDeliveryStatusWidth) };
    vUIElements.push_back(tmp);
    // got it from previous message drawing calculation
    m_ptStart.y += m_cyChatItem;
    return 0;
  }
  default:
    return 0;
  }
}

/* int CChatControl::AddPaintElement(MESSAGE_SEND_STATUS status, int indexOfInsertion, int recordIndex) {
  // logic derived from drawElement
  // set font not required
  CPoint delivPtStart(cxChatText+timeWidth+1, ptStart.y);
  CHATBOX_ELEMENT tmp = { ElemDeliveryStatusType, TEXT(""), delivPtStart, CPoint(deliveryStatusWidth, deliveryStatusWidth) };
  chatUIElements.insert(chatUIElements.begin()+indexOfInsertion, tmp);

  // not changing ptStart for delivery status print
  //ptStart.x += cch.cx;
  return 0;
} */

// helper function for DrawElement
// efficient implementation of emot icon code matching
int CChatControl::DrawMessageEmo(CString message)
{
  if (message.IsEmpty())
    return 0;

  if (pEmoCodesList == NULL) {
    pEmoCodesList = m_pMainDlg->GetEmoCodeList();
  }

  // minimum length of emot icons = 2
  // maximum length of emot icons = 3, one emo of length 5  :POOP
  // starting charset of emot icons ":;>8O3L(="

  CString token;
  int YPre = m_ptStart.y;
  enum TextEmoType {NONE, BITMAP, TEXTSTR};
  TextEmoType PreviousItemType = NONE;
  int startPos = 0;
  int emoPos = 0;
  int emoIndex = 0;
  while ((emoPos = FindEmoCode(startPos, message, emoIndex)) >= 0) {
    // emo found, draw now
    // whether there is any text before emot icon
    if (emoPos>startPos) {
      token = message.Mid(startPos, emoPos-startPos);
      if (PreviousItemType == BITMAP)
        m_ptStart.x += m_cxChatTextHSpace;
      DrawChatText(token);
      PreviousItemType = TEXTSTR;
    }

    // add vspace before and after emo, to solve spacing problem of text after emo
    if (PreviousItemType == TEXTSTR)
      m_ptStart.x += m_cxChatTextHSpace;
    VirtualDrawEmotIcon(emoIndex);
    CString tmpDbg(pEmoCodesList[emoIndex]);
    startPos = emoPos + _tcslen(pEmoCodesList[emoIndex]);
  }
  if ( message.GetLength()-startPos > 0) {
    // ref, CStringT::Mid
    // https://learn.microsoft.com/en-us/cpp/atl-mfc-shared/reference/cstringt-class?view=msvc-170#mid
    token = message.Mid(startPos, message.GetLength()-startPos);
    if (PreviousItemType == BITMAP)
      m_ptStart.x += m_cxChatTextHSpace;
    DrawChatText(token);
  }
  // draw left over text
  

  /*CString emo = TEXT(":)");
  
  int n = message.Find(emo);
  int startPos = 0;
  //CPoint ptStartDraw = ptStart;    // draw from this point
  // CPoint ptEndDraw = ptEnd;    // this is the limiting point
  // 
  // ptEndDraw.x = ptStart.x + cxChatText;

  // CRect limitRect(rcMsgClip);

  while (n != -1) {
    // get substring before emo
    if (n-startPos > 0) {
      token = message.Mid(startPos, n-startPos);
      // draw text
      //pDC->DrawText(itemText, itemRect, DT_CALCRECT| DT_LEFT | DT_NOCLIP | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
      // DrawTextMultiLine will modify ptStartDraw if it draws
      if (PreviousItemType == BITMAP)
        ptStart.x += cxChatTextHSpace;
      DrawChatText(token);
      PreviousItemType = TEXTSTR;

      // CDC::DrawText
      // https://learn.microsoft.com/en-us/cpp/mfc/reference/cdc-class?#drawtext
      // pDC->DrawText(token, limitRect, DT_NOPREFIX | DT_WORDBREAK);
      // ref, CDC Class
      // limitRect.left += pDC->GetTextExtent(token).cx;
    }
    // add vspace before and after emo, to solve spacing problem of text after emo
    if (PreviousItemType == TEXTSTR)
      ptStart.x += cxChatTextHSpace;
    VirtualDrawEmotIcon();

    //ptStartDraw.x += cxChatTextHSpace;
    PreviousItemType = BITMAP;
    startPos = n + emo.GetLength();
    n = message.Find(emo, startPos);
  }

  if ( message.GetLength()-startPos > 0) {
    token = message.Mid(startPos, message.GetLength()-startPos);      // ref: http://msdn.microsoft.com/en-us/library/aa300543(v=vs.60).aspx
    if (PreviousItemType == BITMAP)
      ptStart.x += cxChatTextHSpace;
    DrawChatText(token);
  }*/
  return (m_ptStart.y - YPre + m_yCharChatText);    // add Single Line Height to move to next row
}

// Returns -1 if emot icon not found
int CChatControl::FindEmoCode(int startIndex, CString str, int& foundEmoIndex) {
  TCHAR* startEmoChar = _T(":;>8O3L(=");
  int nStartEmoChar = 9;
  int nEmoCount = m_pMainDlg->GetEmoCount();

  // effect of :))
  // 0 => 26
  // 1 <-> 26 => --

  // effect of :88
  // 35 => 45
  // 36 <-> 45 => 35 <-> 44

  // effect of :60 and :67
  // 34, 35 => 42, 43
  // 36 <-> 43 => 34, 41

  // effect of :POOP
  // 4 => 28
  // 5 <-> 27 => -= 2
  // 28 => --
  // 29 <-> 33 => same position
  // 34, 35 => 42, 43
  // 36 => -= 2
  // 37 => 45
  // 38 <-> 44 => -=3
  // 45 => 44
  // 46 => same position
  static TCHAR *EmoCodeMap[EMO_MAX_NO] = {_T(":))"), _T(":)"), _T(":("), _T(":D"), _T(":POOP"), _T(":P"), _T(":S"), _T(":O"), _T(":@"), _T(":-["), _T(":-]"), _T(":|"),
        _T(":'("), _T(":>"), _T(":3"), _T(":*"), _T(":V"), _T(":/"), _T(";)"), _T(">:("), _T(">:O"), _T("8)"), _T("8|"), _T("O.o"),    // starting index = 12
        _T("O:)"), _T("3:)"), _T("L(\")"), _T("L3"), _T(":Z"), _T(":$"), _T(":0"), _T("::3"), _T(":4"),          // starting index = 24
        _T(":-h"), _T(":60"), _T(":67"), _T(":6"), _T(":88"), _T(":8"), _T(":9"), _T(":12"), _T(":-?"), _T("(Y)"), _T(":54"),      // starting index = 33
        _T(":56"), _T(":72"), _T("=((")};          // starting index = 44

  static int emoCodeMapToIndex[EMO_MAX_NO] = {26, 0, 1, 2, 28, 3, 4, 5, 6, 7, 8 ,9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 27, 29, 30, 31, 32, 33,
        42, 43, 34, 45, 35, 36, 37, 38, 39, 40, 41, 44, 46};

  for (int i=startIndex; i<str.GetLength()-1; i++) {
    int j = 0;
    // match each char with beginning charset
    for (;j<nStartEmoChar; j++)
      if (str[i] == startEmoChar[j])
        break;

    // emo first char match
    if (j < nStartEmoChar) {
      // check for each emo match from current char position
      // get length of emo
      int k=0;
      int emoLength = 0;
      for (; k<nEmoCount; k++) {
        emoLength = _tcslen(EmoCodeMap[k]);
        // should have more or equal number of characters left
        if (emoLength <= str.GetLength()-i) {
          if (CString(EmoCodeMap[k]) == str.Mid(i, emoLength))
            break;
        }
      }
      // emo matched
      if (k<nEmoCount) {
        foundEmoIndex = emoCodeMapToIndex[k];
        return i;
      }

    }
  }
  foundEmoIndex = -1;
  return -1;
}

// DrawChatText independent function
// output: output is sent via CPoint* pointer to modify to next starting point of drawing
//    only adds required value to get correct next draw point without adding extra height
//    it should not add extra single line height
void CChatControl::DrawChatText(CString str)
{
  if (str.IsEmpty())
    return ;
  // break for "\r\n", tokenize doesn't work because we lose the count
  int startPos = 0;

  CString newline = TEXT("\r\n");
  int n = str.Find(newline);
  CString tokStr;

  while (n != -1) {
    // get substring before newline
    if (n-startPos > 0) {
      tokStr = str.Mid(startPos, n-startPos);
      VirtualDrawTextMultiLine(tokStr);
    }
    m_ptStart.y += m_yCharChatText;
    m_ptStart.x = m_cxChatTextHSpace;

    startPos = n + newline.GetLength();
    n = str.Find(newline, startPos);
  }

  if (str.GetLength()-startPos > 0) {
    tokStr = str.Mid(startPos, str.GetLength()-startPos);
    VirtualDrawTextMultiLine(tokStr);
  }
}

// imported from previous project of CListCtrl modification
// msdn example, ref, CDC Class
// Our functions definitions
// This handler loads a bitmap from system resources, 
// centers it in the view, and uses BitBlt() to paint the bitmap 
// bits. 
void CChatControl::VirtualDrawEmotIcon(int emoIndex)
{
  /*// load IDB_BMP_SMILE01 from our resources
  CBitmap bmp;
  // if (bmp.LoadBitmap(IDB_BMP_SMILE01))
  CPngImage pngImage;
  //image.Load(AfxGetInstanceHandle(), IDB_PNG_SMILE01);
  pngImage.Load(IDB_PNG_SMILE01);

  // if (bmp.LoadBitmap(IDB_PNG_SMILE01))
  // ref, MFC CGdiObject Class
  if (bmp.Attach(pngImage.Detach()))
  {
    // Get the size of the bitmap
    BITMAP bmpInfo;
    bmp.GetBitmap(&bmpInfo);*/

    // ref MFC CSize Class
    //CSize cch(bmpInfo.bmWidth, bmpInfo.bmHeight);
    CSize cch(24, 24);
    // check if drawing is not possible
    // ref CPoint Class
    CPoint ptRes = m_ptEnd - (m_ptStart+cch);
    // not possible in single line
    if (ptRes.x < 0) {
      // move to next line
      // there is still space for next line
      //if (ptRes.y >= cch.cy) {
        m_ptStart.x =  m_cxChatTextHSpace;
        m_ptStart.y += m_yCharChatText;
      /*}
      else {
        // AfxMessageBox(TEXT("Not enough space to draw bitmap!"), MB_OK);
        return ;
      }*/
    }

    CString emoIndexStr;
    emoIndexStr.Format(TEXT("%d"), emoIndex);
    CHATBOX_ELEMENT tmp = { ElemEmotIconType, emoIndexStr, m_ptStart, cch };
    m_vChatRecords[m_iChatItemInsertionIndex].vUIElements.push_back(tmp);

    /* if we want image scaling, ref: 
    // dcMemory.SetStretchBltMode(HALFTONE);
    CImage img;
    img.LoadFromResource(AfxGetResourceHandle(), IDB_BMP_SMILE01);
    img.StretchBlt(dcMemory.m_hDC, 0, 0, limitRect, dimy, 0, 0, img1.GetWidth(), img1.GetHeight(), SRCCOPY);

    Refs
    - http://stackoverflow.com/questions/2339702/setting-resized-bitmap-file-to-an-mfc-picture-control
    - https://social.msdn.microsoft.com/Forums/vstudio/en-US/8a636954-5a3a-4a10-9e84-386ce057b2d9/colour-problems-when-scaling-a-bitmap-with-cdcstretchblt
    */  

    m_ptStart.x += cch.cx;
  /*}
  else
  {
    TRACE0("ERROR: Where's IDB_BMP_SMILE01?\n");
    return ;
  }*/
}

// multiline drawing using drawText
bool CChatControl::VirtualDrawTextMultiLine(CString str)
{
  // check if draw is possible in single line
  CSize cch = m_pDC->GetOutputTextExtent(str);
  // ref CPoint
  CPoint ptRes = m_ptEnd - (m_ptStart+cch);
  // possible in single line
  // if (ptRes.x >= 0 && ptRes.y >= 0) {
  // we want to scroll, do not restrict anymore on y
  if (ptRes.x >= 0) {
    CHATBOX_ELEMENT tmp = { ElemMessageType, str, m_ptStart, cch };
    m_vChatRecords[m_iChatItemInsertionIndex].vUIElements.push_back(tmp);

    // pDC->TextOut(ptStart.x, ptStart.y, str);
    m_ptStart.x += cch.cx;
    return true;
  }

  // multiline implementation here, input text must exceed current line during draw as it comes here
  // Implementation without using DrawText MODIFYSTRING
  // take the string, if string length is zero break
  // get extent, get the fittable string using binary divisive mechanism

  bool firstLine = true;
  // int height = 0;
  CString line;

  while (! str.IsEmpty()) 
  {
    if (firstLine)
      firstLine = false;
    else {
      // beginning x of next line
      m_ptStart.x = m_cxChatTextHSpace;
      // next line y axis
      // ptStart.y += cch.cy;
      m_ptStart.y += m_yCharChatText;
    }
    // if we are inside clip we can proceed to calculate and draw, otherwise recursion function will be unpredictable
    // as context for component function IsFittableInRectangle becomes invalid
    // no more invalid, we are only calculating not drawing in an invalid rectangle
    line = ExtractFittableLineFromStr(str);
    cch = m_pDC->GetOutputTextExtent(line);

    CHATBOX_ELEMENT tmp = { ElemMessageType, line, m_ptStart, cch };
    m_vChatRecords[m_iChatItemInsertionIndex].vUIElements.push_back(tmp);

    str = str.Mid(line.GetLength());
  }
  if (! str.IsEmpty())
    return false;

  if (! line.IsEmpty()) {
    // for correct calculation of extent
    m_ptStart.x += cch.cx;
  }
  return true;
}


// Some input string will be fittable
CString CChatControl::ExtractFittableLineFromStr(const CString str) {
  if (IsFittableInRectangle(str, str.GetLength()-1))
    return str;
  int pos = GetFittablePositionRecursive(str, 0, str.GetLength()-1);

  // find a space or newline before this position to break
  // if not found we break there anyway
  CString exStr = str.Mid(0, pos+1);

  // ref, CString::ReverseFind
  int breakIndex = exStr.ReverseFind(_T(' '));
  // none found: ' '
  if (breakIndex == -1)
    // get string from pos
    return exStr;
  return exStr.Mid(0, breakIndex+1);
}


// Recursive function to get fittable position
//  Fastest algorithm to get fittable position
//
// follows binary search mechanism to fast reach fittable string
int CChatControl::GetFittablePositionRecursive(const CString str, int iMin, int iMax) {
  int iMid = (iMin + iMax) / 2;

  if (IsFittableInRectangle(str, iMid) && ! IsFittableInRectangle(str, iMid+1))
    return iMid;

  if (IsFittableInRectangle(str, iMid))
    return GetFittablePositionRecursive(str, iMid+1, iMax);
  else
    return GetFittablePositionRecursive(str, iMin, iMid-1);
}

bool CChatControl::IsFittableInRectangle(const CString gStr, const int index) {
  // index is 1 less than count/length
  CString line = gStr.Mid(0, index+1);
  CSize cch = m_pDC->GetOutputTextExtent(line);
  CPoint ptRes = m_ptEnd - (m_ptStart+cch);
  // if (ptRes.x >= 0 && ptRes.y >= 0) {
  if (ptRes.x >= 0) {  // y check disabled for scrolling
    return true;
  }
  return false;
}

// This function does the final act which is painting
// Paints UI Elements
//  if scrollbar is not enabled startUIElemIndex is initialized with endUIElemIndex
//  if scrollbar is enabled startUIElemIndex 
void CChatControl::PaintUIElements() {
  // should not modify drawing indexes here, we should only draw here
  // startUIElemIndex = -1;
  // endUIElemIndex = -1;
  // save previous color
  COLORREF oldColor = m_pDC->GetTextColor();

  // To detect new line
  //int preY=ptStart.y;    // dummy initialization ptStart.y might not be necessary

  // POSITION pos = chatUIElements.GetHeadPosition();
  bool drawStarted = false;
  bool isInsideRect = true;
  bool isAlternateNameColor = false;
  bool rowDrawComplete = false;

  // ** implement drawing according to co-ordinates of update region
  //  && endUIElemIndex == -1; ) && (i<endUIElemIndex+1)
  for (int i=0; i < (int) m_vChatRecords.size() && rowDrawComplete==false; i++) {
    for (int j=0; j < (int) m_vChatRecords[i].vUIElements.size() && rowDrawComplete==false; j++) {
      CHATBOX_ELEMENT curChatElement = m_vChatRecords[i].vUIElements[j];
      curChatElement.ptStart.y -=  m_yScrollAmount;

      switch(curChatElement.type) {
      case ElemDateType:
      {  
        if (IsPointInsideClipRectangle(m_ptClipStart, m_ptEnd, curChatElement.ptStart) == false && IsPointInsideClipRectangle(m_ptClipStart, m_ptEnd, curChatElement.ptStart+curChatElement.csz) == false) {
          if (drawStarted)
            isInsideRect = false;
          break;
        }
        // set date color
        m_pDC->SetTextColor(RGB(4,95,192));
        // set background color
        COLORREF oldBkColor = m_pDC->SetBkColor(RGB(170,194,154));
        // set date font
        if (m_pOldFont == NULL)
          m_pOldFont = m_pDC->SelectObject(&m_dateFont);
        else
          m_pDC->SelectObject(&m_dateFont);
        // set text align
        // UINT oldTextAlignment = pDC->SetTextAlign(TA_CENTER | TA_TOP | TA_NOUPDATECP);
        int offsetX = ((m_ptEnd.x + m_cxTimeWidth - m_ptClipStart.x) - curChatElement.csz.cx)/2;
        // pDC->TextOut(curChatElement.ptStart.x+offsetX, curChatElement.ptStart.y, curChatElement.text);
        // pDC->DrawText(curChatElement.text, CRect(ptClipStart,ptEnd), DT_CENTER);
        m_pDC->ExtTextOut(curChatElement.ptStart.x+offsetX, curChatElement.ptStart.y, ETO_OPAQUE, CRect(m_ptClipStart.x, curChatElement.ptStart.y, m_ptEnd.x+m_cxTimeWidth+m_cxDeliveryStatusWidth+m_cxScrollbarWidth, curChatElement.ptStart.y+m_yCharDate), curChatElement.sText, NULL);
        // pDC->SetTextAlign(oldTextAlignment);
        m_pDC->SetBkColor(oldBkColor);
        drawStarted = true;
        break;
      }
      case ElemNameType:
      {  
        if (isAlternateNameColor) {
          isAlternateNameColor = false;
        }
        else {
          isAlternateNameColor = true;
        }
        if (IsPointInsideClipRectangle(m_ptClipStart, m_ptEnd, curChatElement.ptStart) == false && IsPointInsideClipRectangle(m_ptClipStart, m_ptEnd, curChatElement.ptStart+curChatElement.csz) == false) {
          if (drawStarted)
            isInsideRect = false;
          break;
        }

        if (isAlternateNameColor)
          m_pDC->SetTextColor(RGB(136,97,11));
        else
          //ref CDC Class
          m_pDC->SetTextColor(RGB(11,136,99));

        // we are remoing backgroud color for name
        // set name heading font
        if (m_pOldFont == NULL)
          m_pOldFont = m_pDC->SelectObject(&m_headingFont);
        else
          m_pDC->SelectObject(&m_headingFont);

        m_pDC->TextOut(curChatElement.ptStart.x, curChatElement.ptStart.y, curChatElement.sText);

        m_pDC->SetTextColor(oldColor);
        drawStarted = true;
        break;
      }
      case ElemMessageType:
      {
        if (IsPointInsideClipRectangle(m_ptClipStart, m_ptEnd, curChatElement.ptStart) == false && IsPointInsideClipRectangle(m_ptClipStart, m_ptEnd, curChatElement.ptStart+curChatElement.csz) == false) {
          if (drawStarted)
            isInsideRect = false;
          break;
        }
        // set chat text font
        if (m_pOldFont == NULL)
          m_pOldFont = m_pDC->SelectObject(&m_textFont);
        else
          m_pDC->SelectObject(&m_textFont);

        m_pDC->TextOut(curChatElement.ptStart.x, curChatElement.ptStart.y, curChatElement.sText);
        drawStarted = true;
        break;
      }
      case ElemEmotIconType:
      {
        if (IsPointInsideClipRectangle(m_ptClipStart, m_ptEnd, curChatElement.ptStart) == false && IsPointInsideClipRectangle(m_ptClipStart, m_ptEnd, curChatElement.ptStart+curChatElement.csz) == false) {
          if (drawStarted)
            isInsideRect = false;
          break;
        }

        // have to implement selection according to index
        // requires implementation on VirtualDrawEmotIcons as well
        CBitmap bmp;
        // if (bmp.LoadBitmap(IDB_BMP_SMILE01))
        /*// for PNG images
        CImage image;
        image.LoadFromResource(AfxGetInstanceHandle(), IDB_PNG_SMILE01);
        //image.AlphaBlend(pDC, curChatElement.ptStart.x, curChatElement.ptStart.y, curChatElement.size.cx, curChatElement.size.cy, 0, 0, curChatElement.size.cx, curChatElement.size.cy);
        //image.AlphaBlend(pDC->GetSafeHdc(), curChatElement.ptStart.x, curChatElement.ptStart.y, curChatElement.size.cx, curChatElement.size.cy);
        image.AlphaBlend(pDC->GetSafeHdc(), curChatElement.ptStart.x, curChatElement.ptStart.y, 255, AC_SRC_OVER);
        /*CPngImage pngImage;
        if (pngImage.Load(IDB_PNG_SMILE01)) {
          pngImage.transp
        }
        */

        // ref CGdiObject Class
        // if (bmp.Attach(pngImage.Detach()))
        // ref C runtime library _ttoi
        if (bmp.LoadBitmap(IDB_BMP_EMOTICON_01+_ttoi(curChatElement.sText)))
        {
          // COLORREF oldBkColor = pDC->SetBkColor(TRANSPARENT);
          // Create an in-memory DC compatible with the display DC we're using to paint
          // COLORREF oldBkColor;
          // if (isAlternate) {
          //   oldBkColor = pDC->SetBkColor(RGB(170,194,154));
          // }

          CDC dcMemory;
          dcMemory.CreateCompatibleDC(m_pDC);
          // Select the bitmap into the in-memory DC
          CBitmap* pOldBitmap = dcMemory.SelectObject(&bmp);
          // Copy the bits from the in-memory DC into the on-screen DC to actually do the painting.
          m_pDC->BitBlt(curChatElement.ptStart.x, curChatElement.ptStart.y, curChatElement.csz.cx, curChatElement.csz.cy, &dcMemory, 0, 0, SRCCOPY);
          // transparency not working yet
          // pDC->TransparentBlt(curChatElement.ptStart.x, curChatElement.ptStart.y, curChatElement.size.cx, curChatElement.size.cy, &dcMemory, 0, 0, curChatElement.size.cx, curChatElement.size.cy, RGB(255,255,255));
          dcMemory.SelectObject(pOldBitmap);
          // pDC->SetBkColor(oldBkColor);
        }
        drawStarted = true;
        break;
      }
      case ElemTimeType:
      {
        if (IsPointInsideClipRectangle(m_ptClipStart+CSize(m_cxChatText, 0), m_ptEnd+CSize(m_cxTimeWidth, 0), curChatElement.ptStart) == false && IsPointInsideClipRectangle(m_ptClipStart+CSize(m_cxChatText, 0), m_ptEnd+CSize(m_cxTimeWidth, 0), curChatElement.ptStart+curChatElement.csz) == false) {
          // but don't break loop setting 'isInsideRect' because time can be out of rectangle for multiline chat text still next item can be inside rect
          break;
        }

        // not checking clip now, probably later
        // set font for time
        if (m_pOldFont == NULL)
          m_pOldFont = m_pDC->SelectObject(&m_timeFont);
        else
          m_pDC->SelectObject(&m_timeFont);

        // set text align
        UINT oldTextAlignment = m_pDC->SetTextAlign(TA_RIGHT);
        m_pDC->TextOut(m_ptEnd.x+m_cxTimeWidth, curChatElement.ptStart.y, curChatElement.sText);
        m_pDC->SetTextAlign(oldTextAlignment);
        drawStarted = true;
        break;
      }
      case ElemDeliveryStatusType:
      {
        /*if (IsPointInsideClipRectangle(ptClipStart, ptEnd, curChatElement.ptStart) == false && IsPointInsideClipRectangle(ptClipStart, ptEnd, curChatElement.ptStart+curChatElement.size) == false) {
          if (drawStarted)
            isInsideRect = false;
          break;
        }*/
        CBitmap bmp;
        if (bmp.LoadBitmap(IDB_BMP_DELIV_STATUS_01))
        {
          CDC dcMemory; 
          dcMemory.CreateCompatibleDC(m_pDC);
          // Select the bitmap into the in-memory DC
          CBitmap* pOldBitmap = dcMemory.SelectObject(&bmp);
          // Copy the bits from the in-memory DC into the on-screen DC to actually do the painting.
          m_pDC->BitBlt(curChatElement.ptStart.x, curChatElement.ptStart.y, curChatElement.csz.cx, curChatElement.csz.cy, &dcMemory, 0, 0, SRCCOPY);
          // transparency not working yet
          // pDC->TransparentBlt(curChatElement.ptStart.x, curChatElement.ptStart.y, curChatElement.size.cx, curChatElement.size.cy, &dcMemory, 0, 0, curChatElement.size.cx, curChatElement.size.cy, RGB(255,255,255));
          dcMemory.SelectObject(pOldBitmap);
          // pDC->SetBkColor(oldBkColor);
        }
        if (isInsideRect == false)
          rowDrawComplete = true;
        break;
      }
      default:
        break;
      }
    }
  }
}

// checks if point is inside provided rectangle
bool IsPointInsideClipRectangle(const CPoint topLeft, const CPoint bottomRight, const CPoint point) {
  // check x
  if (topLeft.x > point.x)
    return false;
  if (point.x > bottomRight.x)
    return false;
  // check y
  if (topLeft.y > point.y)
    return false;
  if (point.y > bottomRight.y)
    return false;
  return true;
}

void CChatControl::UpdateNextElementsCordinates(int yOffset) {
  std::vector<CHATBOX_ITEM>::iterator crIter;
  std::vector<CHATBOX_ELEMENT>::iterator cUIIter;
  for (crIter = m_vChatRecords.begin()+m_iChatItemInsertionIndex+1; crIter < m_vChatRecords.end(); crIter++) {
    for (cUIIter = crIter->vUIElements.begin(); cUIIter != crIter->vUIElements.end(); cUIIter++) {
      cUIIter->ptStart.y += yOffset;
    }
  }
}

void CChatControl::OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt)
{
  // This feature requires Windows Vista or greater.
  // The symbol _WIN32_WINNT must be >= 0x0600.
  // TODO: Add your message handler code here and/or call default
  AfxMessageBox(_T("we are on mouse wheel child"));
  CWnd::OnMouseHWheel(nFlags, zDelta, pt);
}


////////////////////////////////////////////////////////////////////////////////
// Function    : CChatControl::SaveChatHistory()
//
// Description : Save chat history into database
//
// Returns     : none
//
// Notes        : Save the chat history back to database
//     be careful about constraint errors
////////////////////////////////////////////////////////////////////////////////
BOOL CChatControl::SaveChatHistory()
{
  CString csInsertQuery = L"";
  // query string example
  //"1, 'Saint', 'testing row 01', '2013-12-26 17:18:08', 1); INSERT INTO UserTable VALUES(3, 'Atique', 'testing row 02', '2013-12-26 17:10:08', 1);", -1, &statement, 0) == SQLITE_OK)

  // form a big query
  for (int i=0; i < (int) m_vChatRecords.size(); i++) {
    CHATBOX_ITEM ciCurItem = m_vChatRecords.at(i);
    WCHAR szNumBuf[12];
    // ref C runtime library _itow_s, _itot_s
    _itot_s(i+3, szNumBuf, 12, 10);
    csInsertQuery += L"INSERT INTO UserTable VALUES(" + CString(szNumBuf) + L", '" + ciCurItem.sUserName + L"', '" + ciCurItem.sMessage + L"', '" + ciCurItem.timedate.Format(_T("%Y-%m-%d %H:%M:%S.")) + L"', " + L"1); ";
  }
  if (g_pChatRecords && csInsertQuery.IsEmpty() == FALSE)
    g_pChatRecords->RunInsertQuery(csInsertQuery);
  return TRUE;
}

/*
// in case user resizes the window, fix page size
void CChatControl::Repaint()
{
  Invalidate();
}

int Compare (const CHATBOX_ITEM& cItem) {

   if (year<d.year) {
      return -1;
   }
   else if (year>d.year) {
      return 1;
   }
   else if (month<d.month) {
      return -1;
   }
   else if (month>d.month) {
      return 1;
   }
   // same for day

   return 0;
}
*/
