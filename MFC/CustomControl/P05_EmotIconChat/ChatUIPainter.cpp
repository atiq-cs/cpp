// ChatUIPainter.cpp : implementation file for our custom chat control drawing operation class
// We create a new window class for our control
// register it into the system, control window is created automatically by dialog using resource file
//   hence, scrollbar is automatically added to the control
// Implements drawing and chat data structure for it


#include "stdafx.h"
#include "ChatUIPainter.h"
#include "resource.h"    // for IDB_BMP_SMILE01
#include "ChatControl.h"    // for CHATBOX_FIELD_TYPE, struct CHATBOX_ITEM and struct CHATBOX_ELEMENT

// our contructor
CChatUIPainter::CChatUIPainter(CDC* paintDC, CList<CHATBOX_ELEMENT, CHATBOX_ELEMENT&>& rUIElement, int yPos, int timeWidth, CHATBOX_SHARED_DATA& lpItem):    // timeWidth: time width
    pDC(paintDC),
    m_rUIElement(rUIElement),
     yScroll(yPos),
    pOldFont(NULL),
    cyChatItem(0),
    cxChatTextHSpace(2),
    lastChatItemData(lpItem)
    //processingStage(0)
{
  // initialize, get parameters
  

  // get clip rectangle and save as points
  CRect rcClip;
  pDC->GetClipBox(&rcClip);
  ptClipStart = rcClip.TopLeft();    // draw from this point

  // get shared data
  if (rUIElement.GetCount() == 0) {
    dateText = TEXT("");
    headingText = TEXT("");
  }
  else {
    dateText = lastChatItemData.date;
    headingText = lastChatItemData.name;
    ptStart = lastChatItemData.ptStart;
  }
  ptEnd = rcClip.BottomRight();    // this is the limiting point
  // ptEnd is only for chat text (not datetime or heading text)
  ptEnd.x -= timeWidth;    // for field type Time don't use ptEnd
  cxChatText = rcClip.Width() -  timeWidth;    // for field type Time use this instead
}

// delete anything we have manually created/allocated
CChatUIPainter::~CChatUIPainter(void)
{
}

// use the previously created fonts so that this class is optimized for frequent creation and destruction
void CChatUIPainter::SetFonts(CFont* pfontArray, int* pfontHeight)
{
  dateFont = &pfontArray[0];
  headingFont = &pfontArray[1];
  sendFont = &pfontArray[2];
  timeFont = &pfontArray[3];

  yCharDate = pfontHeight[0];
  yCharHeading = pfontHeight[1];
  yCharSend = pfontHeight[2];
  yCharTime = pfontHeight[3];

  // so that lines to be scrolled are hidden
  // ptStart.y -=  yScroll * pfontHeight[1];
  // ptEnd.y +=  yScroll * pfontHeight[1];
}

int CChatUIPainter::AddPaintElement(const CString gStr, CHATBOX_FIELD_TYPE strType) {
  // logic derived from drawElement
  switch(strType) {
  case FieldDateType:
  {  
    // set date font
    if (pOldFont == NULL)
      pOldFont = pDC->SelectObject(dateFont);
    else
      pDC->SelectObject(dateFont);
    int preY = ptStart.y;
    // add space from second time
    if (!dateText.IsEmpty() && dateText != gStr)
      ptStart.y += yCharDate;

    // calculate dimension only if different
    if (dateText != gStr) {
      // get extent of heading Text
      CSize size = pDC->GetOutputTextExtent(gStr);

      // add vertical space between chat items when headingText is different
      dateText = gStr;
      CHATBOX_ELEMENT tmp = { ElemDateType, dateText, ptStart, size };
      m_rUIElement.AddTail(tmp);
      ptStart.y += yCharDate;
    }
    return (ptStart.y-preY);
  }
  case FieldNameType:
  {  // set name heading font
    if (pOldFont == NULL)
      pOldFont = pDC->SelectObject(headingFont);
    else
      pDC->SelectObject(headingFont);
    int preY = ptStart.y;
    // add space from second time
    if (!headingText.IsEmpty() && headingText != gStr)
      ptStart.y += yCharHeading/2;

    // int res = 0;
    // draw only if different
    if (headingText != gStr) {
      // get extent of heading Text
      CSize size = pDC->GetOutputTextExtent(gStr);

      // add vertical space between chat items when headingText is different
      headingText = gStr;
      CHATBOX_ELEMENT tmp = { ElemNameType, headingText, ptStart, size };
      m_rUIElement.AddTail(tmp);
      ptStart.y += yCharHeading;
    }
    return (ptStart.y-preY);
  }
  case FieldMessageType:
  {
    // set chat text font
    pDC->SelectObject(sendFont);
    CPoint oldPoint = ptStart;

    // draw text with emo if exists
    // clip width is lessed by date time clip
    // use variable cyChatItem to store the height, have to add after drawing date time
    // DrawMessageEmo does/should not touch draw ending point, it should work with a copy of ptEnd
    cyChatItem = DrawMessageEmo(gStr);
    ptStart = oldPoint;
    return cyChatItem;
  }
  case FieldTimeType:
  {
    // set font for time
    if (pOldFont == NULL)
      pOldFont = pDC->SelectObject(timeFont);
    else
      pDC->SelectObject(timeFont);

    // get extent of time Text
    CSize size = pDC->GetOutputTextExtent(gStr);
    // does ChatUIPainter has knowledge on where the starting drawing point of time would be??
    // let' see we have 
    CHATBOX_ELEMENT tmp = { ElemTimeType, gStr, CPoint(cxChatText, ptStart.y), size };
    m_rUIElement.AddTail(tmp);
    // got it from previous message drawing calculation
    ptStart.y += cyChatItem;
    return 0;
  }
  default:
    return 0;
  }
}

// helper function for DrawElement
int CChatUIPainter::DrawMessageEmo(CString message)
{
  if (message.IsEmpty())
    return 0;

  // CRect msgClipRect(limitRect);
  // when DT_CALCRECT is specified DrawText modified msgClipRect
  // int height = ((CDC *)pDC)->DrawText(message, msgClipRect, DT_CALCRECT | DT_NOPREFIX | DT_WORDBREAK);

  // CString itemText = m_currentChatItem.message;
  CString emo = TEXT(":)");

  int n = message.Find(emo);    // ref: http://msdn.microsoft.com/en-us/library/aa300543(v=vs.60).aspx
  int startPos = 0;
  //CPoint ptStartDraw = ptStart;    // draw from this point
  // CPoint ptEndDraw = ptEnd;    // this is the limiting point
  // 
  // ptEndDraw.x = ptStart.x + cxChatText;

  // CRect limitRect(rcMsgClip);
  CString token;
  int YPre = ptStart.y;
  /*TEXTMETRIC tm;
  // Get line height
  pDC->GetTextMetrics(&tm);
  int nSingleLineHeight = tm.tmHeight + tm.tmExternalLeading;*/
  enum TextEmoType {NONE, BITMAP, TEXTSTR};
  TextEmoType PreviousItemType = NONE;

  while (n != -1) {
    // get substring before emo
    if (n-startPos > 0) {
      token = message.Mid(startPos, n-startPos);      // ref: http://msdn.microsoft.com/en-us/library/aa300543(v=vs.60).aspx
      // draw text
      //pDC->DrawText(itemText, itemRect, DT_CALCRECT| DT_LEFT | DT_NOCLIP | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
      // DrawTextMultiLine will modify ptStartDraw if it draws
      if (PreviousItemType == BITMAP)
        ptStart.x += cxChatTextHSpace;
      DrawChatText(token);
      PreviousItemType = TEXTSTR;
      // pDC->DrawText(token, limitRect, DT_NOPREFIX | DT_WORDBREAK);    // ref: http://msdn.microsoft.com/en-US/library/a6x7y2a4(v=vs.110).aspx
      // limitRect.left += pDC->GetTextExtent(token).cx;    // ref: http://msdn.microsoft.com/en-us/library/z7e878zz(v=vs.110).aspx
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
  }
  return (ptStart.y - YPre + yCharSend);    // add Single Line Height to move to next row
}


// DrawChatText independent function
// output: output is sent via CPoint* pointer to modify to next starting point of drawing
//    only adds required value to get correct next draw point without adding extra height
//    it should not add extra single line height
void CChatUIPainter::DrawChatText(CString str)
{
  if (str.IsEmpty())
    return ;
  // break for "\r\n", tokenize doesn't work because we lose the count
  int startPos = 0;

  CString newline = TEXT("\r\n");
  int n = str.Find(newline);
  // int height = pDC->GetOutputTextExtent(CString(TEXT("Ag"))).cy;
  CString tokStr;

  while (n != -1) {
    // get substring before emo
    if (n-startPos > 0) {
      tokStr = str.Mid(startPos, n-startPos);
      VirtualDrawTextMultiLine(tokStr);
    }
    ptStart.y += yCharSend;
    ptStart.x = cxChatTextHSpace;

    startPos = n + newline.GetLength();
    n = str.Find(newline, startPos);
  }

  if (str.GetLength()-startPos > 0) {
    tokStr = str.Mid(startPos, str.GetLength()-startPos);
    VirtualDrawTextMultiLine(tokStr);
  }


  // VirtualDrawTextMultiLine(pDC, str, ptEnd, XStart, ptStart);
  /*// check if draw is possible in single line
  CSize cch = pDC->GetOutputTextExtent(str);
  CPoint ptRes = ptEnd - (*ptStart+cch);      // ref: http://msdn.microsoft.com/en-us/library/t792xy69(v=vs.110).aspx
  // possible in single line
  if (ptRes.x >= 0 && ptRes.y >= 0) {
    ((CDC* )pDC)->TextOut(ptStart->x, ptStart->y, str);
    ptStart->x += cch.cx;
    return ;
  }

  // Multiline implementation here
  // this tokenize example ref: http://msdn.microsoft.com/en-us/library/vstudio/k4ftfkd2.aspx
  int curPos = 0;
  CString sToken = TEXT(" ");
  CString word = str.Tokenize(sToken, curPos);

  // there is no seperate word entire string is one word
  // break string and keep drawing
  if (word.IsEmpty()) {
    VirtualDrawTextMultiLine(pDC, str, ptEnd, XStart, ptStart);
    return ;
  }


  bool firstWord = true;
  do
  {
     if (firstWord) {
       firstWord = false;
     }
     else
       word = _T(" ") + word;
     VirtualDrawTextMultiLine(pDC, word, ptEnd, XStart, ptStart);
     word = str.Tokenize(sToken, curPos);
  } while (! word.IsEmpty());*/
}


// imported from previous project of CListCtrl modification
// msdn example: http://msdn.microsoft.com/en-us/library/kwxzck32(v=vs.110).aspx
// Our functions definitions
// This handler loads a bitmap from system resources, 
// centers it in the view, and uses BitBlt() to paint the bitmap 
// bits. 
void CChatUIPainter::VirtualDrawEmotIcon()
{
  // load IDB_BMP_SMILE01 from our resources
  CBitmap bmp;
  if (bmp.LoadBitmap(IDB_BMP_SMILE01))
  {
    // Get the size of the bitmap
    BITMAP bmpInfo;
    bmp.GetBitmap(&bmpInfo);
    CSize cch(bmpInfo.bmWidth, bmpInfo.bmHeight);    // ref: http://msdn.microsoft.com/en-us/library/xt679a2s(v=vs.110).aspx
    // check if drawing is not possible
    CPoint ptRes = ptEnd - (ptStart+cch);      // ref: http://msdn.microsoft.com/en-us/library/t792xy69(v=vs.110).aspx
    // not possible in single line
    if (ptRes.x < 0 || ptRes.y < 0) {
      // move to next line
      // there is still space for next line
      if (ptRes.y >= cch.cy) {
        ptStart.x =  cxChatTextHSpace;
        ptStart.y += cyChatItem;
      }
      else {
        // AfxMessageBox(TEXT("Not enough space to draw bitmap!"), MB_OK);
        return ;
      }
    }
    CHATBOX_ELEMENT tmp = { ElemEmotIconType, TEXT(":)"), ptStart, cch, 0 };
    m_rUIElement.AddTail(tmp);

    /* if we want image scaling, ref: 
    // dcMemory.SetStretchBltMode(HALFTONE);
    CImage img;
    img.LoadFromResource(AfxGetResourceHandle(), IDB_BMP_SMILE01);
    img.StretchBlt(dcMemory.m_hDC, 0, 0, limitRect, dimy, 0, 0, img1.GetWidth(), img1.GetHeight(), SRCCOPY);    ref: http://stackoverflow.com/questions/2339702/setting-resized-bitmap-file-to-an-mfc-picture-control
    and ref: http://social.msdn.microsoft.com/Forums/vstudio/en-US/8a636954-5a3a-4a10-9e84-386ce057b2d9/colour-problems-when-scaling-a-bitmap-with-cdcstretchblt */  

    ptStart.x += cch.cx;
  }
  else
  {
    TRACE0("ERROR: Where's IDB_BMP_SMILE01?\n");
    return ;
  }
}

// multiline drawing using drawText
bool CChatUIPainter::VirtualDrawTextMultiLine(CString str)
{
  // check if draw is possible in single line
  CSize cch = pDC->GetOutputTextExtent(str);
  CPoint ptRes = ptEnd - (ptStart+cch);      // ref: http://msdn.microsoft.com/en-us/library/t792xy69(v=vs.110).aspx
  // possible in single line
  // if (ptRes.x >= 0 && ptRes.y >= 0) {
  // we want to scroll, do not restrict anymore on y
  if (ptRes.x >= 0) {
    CHATBOX_ELEMENT tmp = { ElemMessageType, str, ptStart, cch };
    m_rUIElement.AddTail(tmp);

    // pDC->TextOut(ptStart.x, ptStart.y, str);
    ptStart.x += cch.cx;
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
      ptStart.x = cxChatTextHSpace;
      // next line y axis
      ptStart.y += cch.cy;
    }
    // if we are inside clip we can proceed to calculate and draw, otherwise recursion function will be unpredictable
    // as context for component function IsFittableInRectangle becomes invalid
    // no more invalid, we are only calculating not drawing in an invalid rectangle
    // if (ptStart.y + cch.cy > ptEnd.y)
    //   break;
    line = ExtractFittableLineFromStr(str);
    cch = pDC->GetOutputTextExtent(line);

    CHATBOX_ELEMENT tmp = { ElemMessageType, line, ptStart, cch };
    m_rUIElement.AddTail(tmp);

    // ((CDC* )pDC)->TextOut(ptStart.x, ptStart.y, line);
    // lastString=line;
    str = str.Mid(line.GetLength());
  }
  if (! str.IsEmpty())
    return false;

  if (! line.IsEmpty()) {
    // cch = ((CDC* )pDC)->GetOutputTextExtent(lastString);
    // for correct calculation of extent
    ptStart.x += cch.cx;
  }
  return true;
}

/*
 *  Some input string will be fittable
 */
CString CChatUIPainter::ExtractFittableLineFromStr(const CString str) {
  if (IsFittableInRectangle(str, str.GetLength()-1))
    return str;
  int pos = GetFittablePositionRecursive(str, 0, str.GetLength()-1);

  // find a space or newline before this position to break
  // if not found we break there anyway
  CString exStr = str.Mid(0, pos+1);

  int breakIndex = exStr.ReverseFind(_T(' '));      // ref: http://msdn.microsoft.com/en-us/library/aa300587(v=vs.60).aspx
  // none found: ' '
  if (breakIndex == -1)
    // get string from pos
    return exStr;
  return exStr.Mid(0, breakIndex+1);
}

/*  Author    :  Saint Atique
 *  Desc    :  Recursive function to get fittable position
 *        :  follows binary search mechanism to fast reach fittable string
 *        :  Fastest algorithm to get fittable position
 */
int CChatUIPainter::GetFittablePositionRecursive(const CString str, int iMin, int iMax) {
  int iMid = (iMin + iMax) / 2;

  if (IsFittableInRectangle(str, iMid) && ! IsFittableInRectangle(str, iMid+1))
    return iMid;

  if (IsFittableInRectangle(str, iMid))
    return GetFittablePositionRecursive(str, iMid+1, iMax);
  else
    return GetFittablePositionRecursive(str, iMin, iMid-1);
}

bool CChatUIPainter::IsFittableInRectangle(const CString gStr, const int index) {
  // index is 1 less than count/length
  CString line = gStr.Mid(0, index+1);
  CSize cch = pDC->GetOutputTextExtent(line);
  CPoint ptRes = ptEnd - (ptStart+cch);
  //if (ptRes.x >= 0 && ptRes.y >= 0) {
  if (ptRes.x >= 0) {  // y check disabled for scrolling
    return true;
  }
  return false;
}

// This function does the final act which is painting
void CChatUIPainter::PaintElements() {
  POSITION pos = m_rUIElement.GetHeadPosition();
  // ** implement drawing according to co-ordinates of update region
  for (int i = 0; i < m_rUIElement.GetCount(); i++)
  {
    CHATBOX_ELEMENT curChatELement = (CHATBOX_ELEMENT) m_rUIElement.GetNext(pos);
    curChatELement.ptStart.y -=  yScroll;
    switch(curChatELement.type) {
    case ElemDateType:
    {  
      if (IsPointInsideClipRectangle(ptClipStart, ptEnd, curChatELement.ptStart) == false || IsPointInsideClipRectangle(ptClipStart, ptEnd, curChatELement.ptStart+curChatELement.size) == false) {
        // i = m_rUIElement.GetCount();
        break;
      }

      // set date font
      if (pOldFont == NULL)
        pOldFont = pDC->SelectObject(dateFont);
      else
        pDC->SelectObject(dateFont);

      pDC->TextOut(curChatELement.ptStart.x, curChatELement.ptStart.y, curChatELement.text);
      break;
    }
    case ElemNameType:
    {  
      if (IsPointInsideClipRectangle(ptClipStart, ptEnd, curChatELement.ptStart) == false || IsPointInsideClipRectangle(ptClipStart, ptEnd, curChatELement.ptStart+curChatELement.size) == false) {
        // i = m_rUIElement.GetCount();
        break;
      }

      // set name heading font
      if (pOldFont == NULL)
        pOldFont = pDC->SelectObject(headingFont);
      else
        pDC->SelectObject(headingFont);
      pDC->TextOut(curChatELement.ptStart.x, curChatELement.ptStart.y, curChatELement.text);
      break;
    }
    case ElemMessageType:
    {
      if (IsPointInsideClipRectangle(ptClipStart, ptEnd, curChatELement.ptStart) == false || IsPointInsideClipRectangle(ptClipStart, ptEnd, curChatELement.ptStart+curChatELement.size) == false) {
        // i = m_rUIElement.GetCount();
        break;
      }

      // set chat text font
      if (pOldFont == NULL)
        pOldFont = pDC->SelectObject(sendFont);
      else
        pDC->SelectObject(sendFont);
      pDC->TextOut(curChatELement.ptStart.x, curChatELement.ptStart.y, curChatELement.text);
      break;
    }
    case ElemEmotIconType:
    {
      if (IsPointInsideClipRectangle(ptClipStart, ptEnd, curChatELement.ptStart) == false || IsPointInsideClipRectangle(ptClipStart, ptEnd, curChatELement.ptStart+curChatELement.size) == false) {
        // i = m_rUIElement.GetCount();
        break;
      }
      // have to implement selection according to index
      // requires implementation on VirtualDrawEmotIcons as well
      CBitmap bmp;
      if (bmp.LoadBitmap(IDB_BMP_SMILE01))
      {
        // Create an in-memory DC compatible with the display DC we're using to paint
        CDC dcMemory;
        dcMemory.CreateCompatibleDC((CDC *)pDC);
        // Select the bitmap into the in-memory DC
        CBitmap* pOldBitmap = dcMemory.SelectObject(&bmp);
        // Copy the bits from the in-memory DC into the on-screen DC to actually do the painting.
        pDC->BitBlt(curChatELement.ptStart.x, curChatELement.ptStart.y, curChatELement.size.cx, curChatELement.size.cy, &dcMemory, 0, 0, SRCCOPY);
        dcMemory.SelectObject(pOldBitmap);
      }
      break;
    }
    case ElemTimeType:
    {
      // not checking clip now, probably later
      // set font for time
      if (pOldFont == NULL)
        pOldFont = pDC->SelectObject(timeFont);
      else
        pDC->SelectObject(timeFont);

      pDC->TextOut(curChatELement.ptStart.x, curChatELement.ptStart.y, curChatELement.text);
      break;
    }
    default:
      break;
    }
  }
}

/*// load last chat element to fix ptStart, DateText, Heading Text
void CChatUIPainter::LoadLastChatElement() {
  if (m_rUIElement.GetCount() == 0) {
    ptStart.x = 0;
    ptStart.y = 0;
    return;
  }
  POSITION pos = m_rUIElement.GetTailPosition();
  // get time
  CHATBOX_ELEMENT lastElem = m_rUIElement.GetPrev(pos);
  if (lastElem.type != ElemTimeType)
    return;
  // get text
  lastElem = m_rUIElement.GetPrev(pos);
  ptStart = lastElem.ptStart;
  ptStart.y += lastElem.size.cy;
  POSITION bakPos = pos;
  do {
  // get name
    lastElem = m_rUIElement.GetPrev(pos);
  } while (lastElem.type != ElemNameType);
  headingText = lastElem.text;
  // get date
  lastElem = m_rUIElement.GetPrev(pos);
  dateText = lastElem.text;
}*/


void CChatUIPainter::RestorePaintUI() {
  // update shared data
  lastChatItemData.date = dateText;
  lastChatItemData.name = headingText;
  lastChatItemData.ptStart = ptStart;
  // restore font
  if (pOldFont) {
    pDC->SelectObject(&pOldFont);
    pOldFont = NULL;
  }

  if (pDC)
    pDC = NULL;

  // bakPtStart.x = ptStart.x;
  // bakPtStart.y = ptStart.y;
}

// checks if point is inside provided rectangle
bool CChatUIPainter::IsPointInsideClipRectangle(const CPoint topLeft, const CPoint bottomRight, const CPoint point) {
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
