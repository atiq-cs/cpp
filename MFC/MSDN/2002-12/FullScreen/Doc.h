////////////////////////////////////////////////////////////////
// MSDN Magazine -- December 2002
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// Compiles with VC 6.0 or VS.NET on Windows XP. Tab size=3.
//
// Typical MFC Doc
//
class CMyDoc : public CDocument {
public:
  virtual ~CMyDoc();
  virtual void Serialize(CArchive& ar);
protected:
  CMyDoc();
  DECLARE_DYNCREATE(CMyDoc)
  DECLARE_MESSAGE_MAP()
};
