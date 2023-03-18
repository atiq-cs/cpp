// ref, 08-31-2013

#include "stdafx.h"
#include "ListCtrlEmo.h"
#include "resource.h"      // for IDB_BMP_SMILE01

// CListCtrlEmo

IMPLEMENT_DYNAMIC(CListCtrlEmo, CListCtrl)

CListCtrlEmo::CListCtrlEmo()
{

}

CListCtrlEmo::~CListCtrlEmo()
{
}


BEGIN_MESSAGE_MAP(CListCtrlEmo, CListCtrl)
  // ON_NOTIFY is used when handling notifications in the parent window of the control, ON_NOTIFY_REFLECT - when handling them in the control itself.
  ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnNMCustomdrawListEmo)
  // ON_PROPNOTIFY_REFLECT(NM_CUSTOMDRAW, OnNMCustomdrawListEmo)
END_MESSAGE_MAP()


// msdn example: http://msdn.microsoft.com/en-us/library/kwxzck32(v=vs.110).aspx
// Our functions definitions
// This handler loads a bitmap from system resources, 
// centers it in the view, and uses BitBlt() to paint the bitmap 
// bits. 
int CListCtrlEmo::DrawBitmap(CDC* pDC, CRect* limitRect)
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

    // Find a center point for the bitmap in the client area
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
    img.StretchBlt(dcMemory.m_hDC, 0, 0, limitRect, dimy, 0, 0, img1.GetWidth(), img1.GetHeight(), SRCCOPY);
     ref: http://stackoverflow.com/questions/2339702/setting-resized-bitmap-file-to-an-mfc-picture-control
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

// does not support Emot icons
void CListCtrlEmo::DrawSubItem( CDC& dc, int nIndex, int nSubIndex ) {
  // we are drawing single column
  // int subitemCount = GetHeaderCtrl()->GetItemCount();
  CRect itemRect;
  if (nSubIndex == 0)
  {
      CalculateItemRect(nIndex, itemRect);
  }
  else if (!GetSubItemRect(nIndex, nSubIndex, LVIR_BOUNDS, itemRect))
  {
      return ;
  }

  // Adjust text rect to not overlap with grid lne and leave some space
  // DeflateRect deflates CRect by moving its sides toward its center. ref: http://msdn.microsoft.com/en-us/library/w0k1h0f6(v=vs.110).aspx
  itemRect.DeflateRect(6, 0);
  dc.DrawText(GetItemText(nIndex, nSubIndex), itemRect, DT_LEFT | DT_NOCLIP | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
}

// This is the function implementing supports for Emot icons
void CListCtrlEmo::DrawSubItemEmo( CDC& dc, int nIndex, int nSubIndex ) {
  // we are drawing single column
  CRect itemRect;
  if (nSubIndex == 0)
  {
    CalculateItemRect(nIndex, itemRect);
  }
  else if (!GetSubItemRect(nIndex, nSubIndex, LVIR_BOUNDS, itemRect))
  {
    return ;
  }

  CString itemText = GetItemText(nIndex, nSubIndex);
  CString emo = TEXT(":)");

  // ref: http://msdn.microsoft.com/en-us/library/aa300543(v=vs.60).aspx
  int n = itemText.Find(emo);
  int startPos = 0;
  const int vSpace = 2;

  CRect emoRect(itemRect);
  CString token;
  // Adjust text rect to not overlap with grid lne and leave some space
  // DeflateRect deflates CRect by moving its sides toward its center.
  // ref, http://msdn.microsoft.com/en-us/library/w0k1h0f6(v=vs.110).aspx
  emoRect.DeflateRect(6, 0);

  while (n != -1) {
    // get substring before emo
    if (n-startPos > 0) {
      // ref: http://msdn.microsoft.com/en-us/library/aa300543(v=vs.60).aspx
      token = itemText.Mid(startPos, n-startPos);
      if (! token.IsEmpty()) {
        // draw text
        // dc.DrawText(itemText, itemRect, DT_CALCRECT| DT_LEFT | DT_NOCLIP | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
        // ref: http://msdn.microsoft.com/en-US/library/a6x7y2a4(v=vs.110).aspx
        dc.DrawText(token, emoRect, DT_LEFT | DT_NOCLIP | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
        emoRect.left += dc.GetTextExtent(token).cx;    // ref: http://msdn.microsoft.com/en-us/library/z7e878zz(v=vs.110).aspx
      }
    }

    //CRect cpEmoRect(emoRect);
    int bitmapWidth = DrawBitmap(&dc, &emoRect);
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
    // ref: http://msdn.microsoft.com/en-us/library/aa300543(v=vs.60).aspx
    token = itemText.Mid(startPos, itemText.GetLength()-startPos);
    if (! token.IsEmpty()) {
      // ref, http://msdn.microsoft.com/en-US/library/a6x7y2a4(v=vs.110).aspx
      dc.DrawText(token, emoRect, DT_LEFT | DT_NOCLIP | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
      // AfxMessageBox(mid, MB_OK);
    }
  }
}
 
void CListCtrlEmo::CalculateItemRect( int nIndex, CRect& rect )
{
  // Calculate item head subitem(index = 0) rect
  // GetSubItemRect() returns rect of entire row for subitem 0
  if (GetSubItemRect(nIndex, 0, LVIR_BOUNDS, rect))
  {
    CRect nextRect;
    if (GetSubItemRect(nIndex, 1, LVIR_BOUNDS, nextRect))
      rect.right = nextRect.left;
  }
}

//
// CListCtrlEmo message handlers
//

void CListCtrlEmo::OnNMCustomdrawListEmo(NMHDR *pNMHDR, LRESULT *pResult)
{
  // ref 2 of ReadMe
  // NMCUSTOMDRAW, LPNMCUSTOMDRAW  is for Rebar, trackbar, and header
  // NMLVCUSTOMDRAW, LPNMLVCUSTOMDRAW for list-view
  LPNMLVCUSTOMDRAW lpLVCustomDraw = reinterpret_cast<LPNMLVCUSTOMDRAW>(pNMHDR);

  // TODO: Add your control notification handler code here
  switch(lpLVCustomDraw->nmcd.dwDrawStage) {
  // ref 2 of ReadMe, section CustomDraw_Prepaint
  //
  // At the beginning of each paint cycle, the control sends the NM_CUSTOMDRAW notification code,
  // specifying the CDDS_PREPAINT value in the dwDrawStage member of the accompanying
  // `NM_CUSTOMDRAW` structure. The value that your application returns to this first
  // notification dictates how and when the control sends subsequent custom draw notifications
  // for the rest of that paint cycle.
  //
  case CDDS_PREPAINT:
    //AfxMessageBox(TEXT("we are in CDDS_PREPAINT"), MB_OK);
    // CDRF_NOTIFYSUBITEMDRAW is invalid in CDDS_PREPAINT
    *pResult |= CDRF_NOTIFYITEMDRAW;
    // *pResult |= CDRF_DOERASE;
    // *pResult |= CDRF_NOTIFYPOSTERASE;
    // The control will notify the parent of any item-specific drawing operations. It will send
    // `NM_CUSTOMDRAW` notification codes before and after it draws items. This occurs when
    // dwDrawStage equals `CDDS_PREPAINT`.
    break;
  /*case CDDS_ITEMPOSTERASE:
  {
    AfxMessageBox(TEXT("we are in CDDS_ITEMPOSTERASE"), MB_OK);
    break;
  }
  case CDDS_ITEMPREERASE:
  {
    *pResult |= CDRF_NOTIFYPOSTERASE;
    break;
  }*/
  case CDDS_ITEMPREPAINT:
  {
    // this implementation ref
    // http://sheenspace.wordpress.com/2011/01/07/custom-drawing-selected-item-rows-in-windows-list-view-control
    //
    // lpLVCustomDraw is pointer to NMLVCUSTOMDRAW structure
    //int itemIndex = lpLVCustomDraw->nmcd.dwItemSpec;

    // Can't use (lplvcd->nmcd.uItemState | CDIS_SELECTED) to tell whether item is selected
    // when List-View control has style LVS_SHOWSELALWAYS.
    // See http://msdn.microsoft.com/en-us/library/bb775483(v=vs.85).aspx
    int itemIndex = lpLVCustomDraw->nmcd.dwItemSpec;
    // int subItemIndex = lpLVCustomDraw->iSubItem;
    // if (subItemIndex == 0) {
    CDC dc;
    if (dc.Attach(lpLVCustomDraw->nmcd.hdc))
    {
      DrawSubItemEmo(dc, itemIndex, 0);
      DrawSubItem(dc, itemIndex, 1);
      dc.Detach();
    }

    *pResult |= CDRF_SKIPDEFAULT;

    //}
    /*else {  // for declaration of dc
      //*pResult |= CDRF_NOTIFYSUBITEMDRAW;
      *pResult = CDRF_DODEFAULT;
    }*/
    // *pResult |= CDRF_NOTIFYSUBITEMDRAW;

    break;
  }
  case CDDS_ITEMPREPAINT | CDDS_SUBITEM:
  {
    /*if ((lpLVCustomDraw->nmcd.dwItemSpec + lpLVCustomDraw->iSubItem) % 2) {
      lpLVCustomDraw->clrText = CLR_DEFAULT;
      lpLVCustomDraw->clrTextBk = CLR_DEFAULT;
    }
    else {
      lpLVCustomDraw->clrText = RGB(255,255,255); // white text
      lpLVCustomDraw->clrTextBk = RGB(0,0,0); // black background
    }

    {
      // this implementation ref: http://sheenspace.wordpress.com/2011/01/07/custom-drawing-selected-item-rows-in-windows-list-view-control/
      // lpLVCustomDraw is pointer to NMLVCUSTOMDRAW structure
      int itemIndex = lpLVCustomDraw->nmcd.dwItemSpec;

      // Can't use (lplvcd->nmcd.uItemState | CDIS_SELECTED) to tell whether item is selected
      // when List-View control has style LVS_SHOWSELALWAYS.
      // See http://msdn.microsoft.com/en-us/library/bb775483(v=vs.85).aspx
      UINT selectState = GetItemState(itemIndex, LVIS_SELECTED);
      if (selectState == LVIS_SELECTED)
      {
        lpLVCustomDraw->clrTextBk = RGB(0, 0, 255);
        CDC dc;

        if (dc.Attach(lpLVCustomDraw->nmcd.hdc))
        {
            DrawSelectedItem(dc, itemIndex);
            dc.Detach();
        }

        *pResult = CDRF_SKIPDEFAULT;
      }
      else
        *pResult = CDRF_NOTIFYSUBITEMDRAW;
    }

    return ;

    // *pResult = CDRF_DODEFAULT;
    // *pResult |= CDRF_NOTIFYSUBITEMDRAW;
    // handle 
    // *pResult |= CDRF_NOTIFYITEMDRAW;
    // *pResult |= CDRF_NOTIFYSUBITEMDRAW;
    // *pResult |= CDRF_NOTIFYPOSTPAINT;
    // *pResult |= CDRF_NOTIFYPOSTERASE;
    break;
  }
  default:
    // *pResult |= CDRF_NOTIFYITEMDRAW;
    break;
  }

  // *pResult |= CDRF_NOTIFYPOSTPAINT;
  // *pResult |= CDRF_NOTIFYITEMDRAW;
  // *pResult |= CDRF_NOTIFYSUBITEMDRAW;
  // *pResult = CDRF_DODEFAULT;    // CDRF_DODEFAULT = 0 */
}


// Insert text converting the emo texts with emos
// in case we need this function in future
void CListCtrlEmo::InsertItemEmo(int itemIndex, LPCTSTR m_chatInStr) {
  // split text for emo
  // draw emos
  // done

  InsertItem(LVIF_TEXT | LVIF_STATE, itemIndex, m_chatInStr, 0, LVIS_SELECTED, 0, 0);
}
