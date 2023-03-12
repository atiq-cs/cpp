### Backup IM 2014
ref, *backup IM, 02-04-2014*,  

Drawing subtitle (date),  

Before,  

```cpp
for (int i = 0; i < charRecords.GetCount() && rcMsgClip.top <=  rcMsgClip.bottom + nSingleLineHeight; i++)
  // const int dwMessageWidth = pDC->GetTextExtent(TEXT(" 11:59:59 PM  Wednesday, September 30, 2013"));
  // const int dwMessageWidth = 565;

  // Variables
  // int i, y;
  CString str;
  TEXTMETRIC tm;
  CRect rcClip;

  // Set font
  // CFont font;
  //font.CreateStockObject(DEFAULT_GUI_FONT);
  CFont *pOldFont = NULL;
  
  // CFont *pOldFont = pDC->SelectObject(&font);
  // if (pOldFont == NULL) {
  //   ErrorExit(TEXT("SelectObject"));
  // }

  // Get line height
  pDC->GetTextMetrics(&tm);
  const int nSingleLineHeight = tm.tmHeight + tm.tmExternalLeading;

  // Get clipping rectangle
  pDC->GetClipBox(&rcClip);
  // have to call after setting font
  //   Wednesday, September 30, 2013
  // difference between CDC::GetTextExtent and CDC::GetOutputTextExtent
  //  ref, http://www.itlisting.org/5-windows/c6f8a7f114490442.aspx
  const CSize timedateDM = pDC->GetOutputTextExtent(TEXT("11:59:59 PM"));
  int dwMessageWidth = rcClip.right - timedateDM.cx;

  // set clipping rectangles for texts and time-date
  // code has to be modified if window size changes
  // rcMsgClip is the clipping rectangle for the message only
  CRect rcMsgClip = rcClip;
  // vertical spacel
  rcMsgClip.DeflateRect(0, 5);
  rcMsgClip.left += 6;

  rcMsgClip.right = dwMessageWidth;
  // rcTimeDateClip is the clipping rectangle for displaying time of the message
  CRect rcTimeDateClip(rcClip);
  // horizontal and vertical space
  rcTimeDateClip.DeflateRect(5, 5);
  //rcTimeDateClip.left += 6;
  rcTimeDateClip.left = dwMessageWidth;
  // Draw Content
  // Display list elements by drawing
  POSITION pos = charRecords.GetHeadPosition();
  int nLineHeight;

  CString preUserName = TEXT("");
```

After that,

```cpp
// Draw heading i.e., user says ".."
if (preUserName != m_currentChatItem.user_name) {
  if (i) rcMsgClip.top += nSingleLineHeight/2;
  // do display heading first time
  if (pOldFont == NULL)
    pOldFont = pDC->SelectObject(&headingFont);
  else
    pDC->SelectObject(&headingFont);

  // Single call to draw and get height of text
  nLineHeight = pDC->DrawText(m_currentChatItem.user_name+TEXT(" says"), rcMsgClip, DT_NOPREFIX);
  rcTimeDateClip.top = rcMsgClip.top = rcMsgClip.top + nLineHeight;
  preUserName = m_currentChatItem.user_name;
}
```

After draw element inside the loop,

```cpp
// Draw text with emot icon
pDC->SelectObject(&sendFont);
// To get font of parent dialog as in resource file
// pDC->SelectObject(GetParent()->GetFont());
nLineHeight = DrawMessageEmo(pDC, m_currentChatItem.message, rcMsgClip);

// CString dbgStr;
// dbgStr.Format(TEXT("Line height: %d"), nLineHeight);
// AfxMessageBox(dbgStr, MB_OK );
rcMsgClip.top += nLineHeight;    // add horizontal space

// DT_CALCRECT does not display text
// ref MFC CDC::DrawText
// int text_height = pDC->DrawText(m_currentChatItem.message, &rect, DT_NOCLIP | DT_INTERNAL);

// result with TextOut is same as DrawText
// int text_height = pDC->TextOut(rect.left, rect.top, m_currentChatItem.message);

// avoiding use of another variable
// will use when necessary of course
pDC->SelectObject(&dateTimeFont);
pDC->DrawText(m_currentChatItem.time_date, &rcTimeDateClip, DT_NOCLIP | DT_RIGHT);
rcTimeDateClip.top = rcMsgClip.top;
// rect.left -= message_width;
// rect.top += text_height;
```

After the loop,

```cpp
// restore DC
pDC->SelectObject(pOldFont);
```


### Backup TestEmoCustomControl 2013
ref, *09-01-2013*,  
Following is developed following msdn samples and documentations,

Previous `OnPaint` method was,
```cpp
void CChatControl::OnPaint() {
  PAINTSTRUCT ps;
  CDC* pDC = BeginPaint(&ps);
  RECT rect;
  const int message_width = 565;
  // GetWindowRect(&rect);
  // ref MFC CWnd::Invalidate
  GetClientRect(&rect);

  // HFONT hFont, hOldFont; 
  CFont *pOldFont;
  // Retrieve a handle to the variable stock font.  
  // hFont = (HFONT)GetStockObject(SYSTEM_FONT); 
  // DEVICE_DEFAULT_FONT is by default used, SYSTEM_FONT, DEFAULT_GUI_FONT
  // CFont *pFont = CFont::FromHandle((HFONT)GetStockObject(DEVICE_DEFAULT_FONT));

  // Select the variable stock font into the specified device context. 
  // pDC->select ...
  //
  // if (pOldFont = pDC->SelectObject(pFont)) {
    // Display the text string.  
    //TextOut(hdc, 10, 50, L"Sample ANSI_VAR_FONT text", 25); 

    // Dump the list elements to the debug window.
    POSITION pos = charRecords.GetHeadPosition();
    for (int i = 0; i < charRecords.GetCount(); i++)
    {
      CHATBOX_ITEM m_currentChatItem = (CHATBOX_ITEM) charRecords.GetNext(pos);
      // DT_CALCRECT does not display text
      // ref MFC CDC::DrawText
      int text_height = pDC->DrawText(m_currentChatItem.message, &rect, DT_NOCLIP | DT_INTERNAL);
      // result with TextOut is same as DrawText
      // int text_height = pDC->TextOut(rect.left, rect.top, m_currentChatItem.message);
    
      // avoiding use of another variable
      // will use when necessary of course
      rect.left += message_width;
      pDC->DrawText(m_currentChatItem.time_date, &rect, DT_NOCLIP | DT_INTERNAL);
      rect.left -= message_width;
      rect.top += text_height;
    }

    // pDC->Rectangle(CRect(0, 0, 100, 100));

    // Restore the original font.        
    // pDC->SelectObject(pOldFont); 
  //}

  EndPaint(&ps);
}
```

Currently following example presented by MFC Video tutorials. We are free to use MFC components and classes since we are not targeting low level SDK.  

**Current solution**: I want is to get textlength that can be drawn into clipping rectangle.. 
Seems like it is not possible to draw multi-line using textout. We cannot get text string clipped into rectangle or cannot get such a length.
DrawText is suggested by MVP.

`Textout` and `ExtTextOut` example,


```cpp
pDC->TextOut(4, y, m_currentChatItem.message, m_currentChatItem.message.GetLength());
pDC->ExtTextOut(4, y, 0, rcClip, m_currentChatItem.message, NULL);
```

rec
Let's go back to drawText,
Have to find how to ...

Multi-line is working fine. Emo has been embedded. However emo is not working when emos are put in multi-lines. Emos working for single line. Here is the backup.

```cpp
#include "stdafx.h"
#include "ChatControl.h"
#include "resource.h"    // for IDC_CHATCUSTOM


CChatControl::CChatControl(void)
{
  // Register our custom chat control class
  if (RegisterWndClass() == FALSE) {
    AfxMessageBox(_T("Window proc registration failed"), MB_OK);
  }

  // ref: http://msdn.microsoft.com/en-US/library/94hsa63e(v=vs.110).aspx
  LOGFONT lf;
  memset(&lf, 0, sizeof(LOGFONT));       // zero out structure
  lf.lfHeight = 16;                      // request a 12-pixel-height font
  lf.lfWeight = FW_DEMIBOLD;
  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, 
     _T("Times New Roman"), 7);                    // request a face name "Arial"
  VERIFY(headingFont.CreateFontIndirect(&lf));     // create the font 


  memset(&lf, 0, sizeof(LOGFONT));       // zero out structure
  lf.lfHeight = 16;                      // request a 12-pixel-height font
  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, 
     _T("Verdana"), 7);                    // request a face name "Arial"
  VERIFY(sendFont.CreateFontIndirect(&lf));  // create the font 
  

  memset(&lf, 0, sizeof(LOGFONT));       // zero out structure
  lf.lfHeight = 12;                      // request a 12-pixel-height font
  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, 
     _T("Verdana"), 7);                           // request a face name "Arial"
  VERIFY(dateTimeFont.CreateFontIndirect(&lf));   // create the font 


  // Create font objects here, code adapated from IM dialer
  /*
  headingFont = new CFont;
  sendFont= new CFont;
  dateTimeFont = new CFont;

  VERIFY(headingFont->CreateFont( 17,                // nHeight
    0,                         // nWidth
    0,                         // nEscapement
    0,                         // nOrientation
    FW_DEMIBOLD,               // nWeight
    FALSE,                     // bItalic
    FALSE,                     // bUnderline
    0,                         // cStrikeOut
    ANSI_CHARSET,              // nCharSet
    OUT_DEFAULT_PRECIS,        // nOutPrecision
    CLIP_DEFAULT_PRECIS,       // nClipPrecision
    DEFAULT_QUALITY,           // nQuality
    DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
    _T("Times New Roman"))
  ); 
 
  VERIFY(sendFont->CreateFont( 16,                // nHeight
    0,                         // nWidth
    0,                         // nEscapement
    0,                         // nOrientation
    FW_NORMAL,                 // nWeight
    FALSE,                     // bItalic
    FALSE,                     // bUnderline
    0,                         // cStrikeOut
    ANSI_CHARSET,              // nCharSet
    OUT_DEFAULT_PRECIS,        // nOutPrecision
    CLIP_DEFAULT_PRECIS,       // nClipPrecision
    DEFAULT_QUALITY,           // nQuality
    DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
    _T("Verdana"))
  ); 

  VERIFY(dateTimeFont->CreateFont( 11,                // nHeight
        0,                         // nWidth
        0,                         // nEscapement
        0,                         // nOrientation
  FW_NORMAL,                 // nWeight
        FALSE,                     // bItalic
   
  FALSE,                     // bUnderline
        0,                         // cStrikeOut
        ANSI_CHARSET,              // nCharSet
        OUT_DEFAULT_PRECIS,        // nOutPrecision
        CLIP_DEFAULT_PRECIS,       // nClipPrecision
        DEFAULT_QUALITY,           // nQuality
        DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
         
  _T("Verdana")));
  */

}

CChatControl::~CChatControl(void)
{
  // Delete fonts objects
  headingFont.DeleteObject();
  sendFont.DeleteObject();
  dateTimeFont.DeleteObject();
}

BOOL CChatControl::RegisterWndClass() {
  // Register your unique class name that you wish to use
  // ref: http://msdn.microsoft.com/en-us/library/kcb1w44w.aspx
  WNDCLASS wndcls;
  HINSTANCE hInst = AfxGetInstanceHandle();

  memset(&wndcls, 0, sizeof(WNDCLASS));   // start with NULL defaults

  // Check weather the class is registerd already
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

  /* ref: http://www.codeproject.com/Articles/5032/Creating-and-Using-custom-controls-in-VC
  WNDCLASS windowclass;

  //Check weather the class is registerd already
  if (!(::GetClassInfo(hInst, CUSTOMWNDCLASS, &windowclass)))
  {
    // If not then we have to register the new class
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
    ON_WM_PAINT()
END_MESSAGE_MAP()


int CChatControl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
  if (CWnd::OnCreate(lpCreateStruct) == -1)
    return -1;
  
  // donot create font objects here...., just doesn't work

  return 0;
}

// Paint to draw the chat box
// to do tasks
// 1. has to set transparent
void CChatControl::OnPaint() {
  // avoid paint when record is inserted
  if (charRecords.GetCount() == 0)
    return;

  PAINTSTRUCT ps;
  CDC* pDC = BeginPaint(&ps);
  //const int dwMessageWidth = pDC->GetTextExtent(TEXT(" 11:59:59 PM  Wednesday, September 30, 2013"));
  //const int dwMessageWidth = 565;
  // Variables
  // int i, y;
  CString str;
  TEXTMETRIC tm;
  CRect rcClip;

  // set font
  // CFont font;
  //font.CreateStockObject(DEFAULT_GUI_FONT);
  CFont *pOldFont = NULL;
  
  /* CFont *pOldFont = pDC->SelectObject(&font);
  if (pOldFont == NULL) {
    ErrorExit(TEXT("SelectObject"));
  }*/

  // Get line height
  pDC->GetTextMetrics(&tm);
  int nSingleLineHeight = tm.tmHeight + tm.tmExternalLeading;

  // Get clipping rectangle
  pDC->GetClipBox(&rcClip);
  // have to call after setting font
  CSize timedateDM = pDC->GetTextExtent(TEXT("11:59:59 PM  Wednesday, September 30, 2013"));
  int dwMessageWidth = rcClip.right - timedateDM.cx;

  // set clipping rectangles for texts and time-date
  // code has to be modified if window size changes
  // rcMsgClip is the clipping rectangle for the message only
  CRect rcMsgClip = rcClip;
  // vertical spacel
  rcMsgClip.DeflateRect(0, 5);
  rcMsgClip.left += 6;

  rcMsgClip.right = dwMessageWidth;
  // rcTimeDateClip is the clipping rectangle for displaying time of the message
  CRect rcTimeDateClip(rcClip);
  // horizontal and vertical space
  rcTimeDateClip.DeflateRect(5, 5);
  //rcTimeDateClip.left += 6;
  rcTimeDateClip.left = dwMessageWidth;
  // Draw Content
  // Display list elements by drawing
  POSITION pos = charRecords.GetHeadPosition();
  int nLineHeight;
  CString preUserName = TEXT("");
  for (int i = 0; i < charRecords.GetCount() && rcMsgClip.top <=  rcMsgClip.bottom + nSingleLineHeight; i++)
  {
    CHATBOX_ITEM m_currentChatItem = (CHATBOX_ITEM) charRecords.GetNext(pos);
    //pDC->TextOut(4, y, m_currentChatItem.message, m_currentChatItem.message.GetLength());

    // Draw heading i.e., user says"
    if (preUserName != m_currentChatItem.user_name) {
      // do display heading first time
      if (pOldFont == NULL)
        pOldFont = pDC->SelectObject(&headingFont);
      else
        pDC->SelectObject(&headingFont);
      nLineHeight = pDC->DrawText(m_currentChatItem.user_name+TEXT(" says: "), rcMsgClip, DT_NOPREFIX);
      rcTimeDateClip.top = rcMsgClip.top = rcMsgClip.top + nLineHeight;
      preUserName = m_currentChatItem.user_name;
    }

    // draw text with emot icon
    pDC->SelectObject(&sendFont);
    CRect msgClipRect(rcMsgClip);
    // when DT_CALCRECT is specified DrawText modified msgClipRect
    nLineHeight = pDC->DrawText(m_currentChatItem.message, msgClipRect, DT_CALCRECT | DT_NOPREFIX | DT_WORDBREAK);

    // current replacement for emo from previous project
    // ------------------------------------------------------------------------------------------------------------------------
    CString itemText = m_currentChatItem.message;
    CString emo = TEXT(":)");

    int n = itemText.Find(emo);    // ref: http://msdn.microsoft.com/en-us/library/aa300543(v=vs.60).aspx
    int startPos = 0;
    const int vSpace = 2;

    CRect emoRect(rcMsgClip);
    CString token;
    while (n != -1) {
      // get substring before emo
      if (n-startPos > 0) {
        token = itemText.Mid(startPos, n-startPos);      // ref: http://msdn.microsoft.com/en-us/library/aa300543(v=vs.60).aspx
        if (! token.IsEmpty()) {
          // draw text
          //pDC->DrawText(itemText, itemRect, DT_CALCRECT| DT_LEFT | DT_NOCLIP | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
          pDC->DrawText(token, emoRect, DT_NOPREFIX | DT_WORDBREAK);    // ref: http://msdn.microsoft.com/en-US/library/a6x7y2a4(v=vs.110).aspx
          emoRect.left += pDC->GetTextExtent(token).cx;    // ref: http://msdn.microsoft.com/en-us/library/z7e878zz(v=vs.110).aspx
        }
      }
      //CRect cpEmoRect(emoRect);
      int bitmapWidth = DrawBitmap(pDC, &emoRect);
      if (bitmapWidth==0)
        AfxMessageBox(TEXT("bitmap width zero"), MB_OK);

      // emoRect = cpEmoRect;
      emoRect.left += bitmapWidth + vSpace;
      startPos = n + emo.GetLength();
      n = itemText.Find(emo, startPos);

      /*CString dbgStr;
      //dbgStr.Format(TEXT("draw pos x = %d"), emoRect.left);
      dbgStr.Format(TEXT("emo in position = %d"), n);
      AfxMessageBox(dbgStr, MB_OK);*/
    }

    if ( itemText.GetLength()-startPos > 0) {
      token = itemText.Mid(startPos, itemText.GetLength()-startPos);      // ref: http://msdn.microsoft.com/en-us/library/aa300543(v=vs.60).aspx
      if (! token.IsEmpty()) {
        pDC->DrawText(token, emoRect, DT_NOPREFIX | DT_WORDBREAK);    // ref: http://msdn.microsoft.com/en-US/library/a6x7y2a4(v=vs.110).aspx
        // AfxMessageBox(mid, MB_OK);
      }
    }
    // ------------------------------------------------------------------------------------------------------------------------

    /*CString dbgStr;
    dbgStr.Format(TEXT("Line height: %d"), nLineHeight);
    AfxMessageBox(dbgStr, MB_OK );*/
    rcMsgClip.top = rcMsgClip.top + nLineHeight;
    // DT_CALCRECT does not display text
    // int text_height = pDC->DrawText(m_currentChatItem.message, &rect, DT_NOCLIP | DT_INTERNAL);    // ref: http://msdn.microsoft.com/en-us/library/a6x7y2a4(v=vs.110).aspx
    // result with TextOut is same as DrawText
    //int text_height = pDC->TextOut(rect.left, rect.top, m_currentChatItem.message);
    
    // avoiding use of another variable
    // will use when necessary of course
    pDC->SelectObject(&dateTimeFont);
    pDC->DrawText(m_currentChatItem.time_date, &rcTimeDateClip, DT_NOCLIP | DT_RIGHT);
    rcTimeDateClip.top = rcMsgClip.top;
    //rect.left -= message_width;
    //rect.top += text_height;
  }

  // restore DC
  pDC->SelectObject(pOldFont);
  //font.DeleteObject();

  EndPaint(&ps);
}

// post chat message to display on custom chat box
void CChatControl::PostChatMessage(CString chat_message, CTime timedate) {
  CString tmStr = timedate.Format(_T("%I:%M:%S %p    %A, %B %d, %Y"));      // ref: http://msdn.microsoft.com/en-us/library/29btb3sw.aspx & http://msdn.microsoft.com/en-us/library/fe06s4ak.aspx
  //SetChatItem(m_currentChatItem);
  CHATBOX_ITEM m_currentChatItem = {};
  m_currentChatItem.message = chat_message;
  m_currentChatItem.time_date = tmStr;

  // Set a random user name
  /* Seed the random-number generator with current time so that
  * the numbers will be different every time we run.
  * ref: http://msdn.microsoft.com/en-us/library/aa272875(v=VS.60).aspx
  */
  srand( (unsigned)time( NULL ) );
  m_currentChatItem.user_name = ((int) rand()) % 2? TEXT("Client 01") : TEXT("Client 02");

  charRecords.AddTail(m_currentChatItem);
  // invalidate entire client area
  Invalidate();

  // InvalidateRect(&rect);
  // post using two string
  // m_ChatEmoBox.PostChatMessage(m_chInText, tmStr);
}

// imported from previous project of CListCtrl modification
// msdn example: http://msdn.microsoft.com/en-us/library/kwxzck32(v=vs.110).aspx
//
// Our functions definitions
// This handler loads a bitmap from system resources, 
//  centers it in the view, and uses BitBlt() to paint the bitmap bits. 
int DrawBitmap(CDC* pDC, CRect* limitRect)
{
  // load IDB_BMP_SMILE01 from our resources
  CBitmap bmp;
  if (bmp.LoadBitmap(IDB_BMP_SMILE01))
  {
    // Get the size of the bitmap
    BITMAP bmpInfo;
    bmp.GetBitmap(&bmpInfo);

    // Create an in-memory DC compatible with the 
    // display DC we're using to paint
    CDC dcMemory;
    dcMemory.CreateCompatibleDC(pDC);

    // Select the bitmap into the in-memory DC
    CBitmap* pOldBitmap = dcMemory.SelectObject(&bmp);

    // Find a centerpoint for the bitmap in the client area
    // CRect rect;
    // GetClientRect(&rect);
    // int nX = limitRect->left + (limitRect->Width() - bmpInfo.bmWidth) / 2;
    // int nY = limitRect->top + (limitRect->Height() - bmpInfo.bmHeight) / 2;

    // Copy the bits from the in-memory DC into the on- 
    // screen DC to actually do the painting. Use the centerpoint 
    // we computed for the target offset.
    pDC->BitBlt(limitRect->left, limitRect->top, bmpInfo.bmWidth, bmpInfo.bmHeight, &dcMemory, 0, 0, SRCCOPY);

    /* if we want image scaling, ref: 
    // dcMemory.SetStretchBltMode(HALFTONE);
    CImage img;
    img.LoadFromResource(AfxGetResourceHandle(), IDB_BMP_SMILE01);
    img.StretchBlt(dcMemory.m_hDC, 0, 0, limitRect, dimy, 0, 0, img1.GetWidth(), img1.GetHeight(), SRCCOPY);    ref: http://stackoverflow.com/questions/2339702/setting-resized-bitmap-file-to-an-mfc-picture-control
    and ref: http://social.msdn.microsoft.com/Forums/vstudio/en-US/8a636954-5a3a-4a10-9e84-386ce057b2d9/colour-problems-when-scaling-a-bitmap-with-cdcstretchblt */

    dcMemory.SelectObject(pOldBitmap);
    return bmpInfo.bmWidth;
  }
  else
  {
    TRACE0("ERROR: Where's IDB_BMP_SMILE01?\n");
    return 0;
  }
}
```

ref, [msdn social - How to find bottom right position of drawn text in rectangle after CDC->DrawText cal](http://social.msdn.microsoft.com/Forums/en-US/a4a9d6f1-de46-4321-9a8e-0abc58577bba/how-to-find-bottom-right-position-of-drawn-text-in-rectangle-after-cdcdrawtext-call)


Mentions that it is not possible to get last character position using drawText

Here are the test results,  
1. Formatting has to be done manually
2. There are options like Uniscribe but it is more time consuming
3. `DrawTextExt`
