////////////////////////////////////////////////////////////////
// MSDN Magazine -- December 2002
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// Compiles with VC 6.0 or VS.NET on Windows XP. Tab size=3.
//
#include "StdAfx.h"
#include "FSApp.h"
#include "Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CMyDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyDoc, CDocument)
END_MESSAGE_MAP()

CMyDoc::CMyDoc()
{
}

CMyDoc::~CMyDoc()
{
}

void CMyDoc::Serialize(CArchive& ar)
{
  if (ar.IsStoring()) {
  } else {
  }
}
