////////////////////////////////////////////////////////////////
// MSDN Magazine -- December 2002
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// Compiles with VC 6.0 or VS.NET on Windows XP. Tab size=3.
//
// See FSApp.CPP for Description of program.
// 
#include "resource.h"       // main symbols

class CMyApp : public CWinApp {
public:
  CMyApp();
  virtual BOOL InitInstance();

protected:
  afx_msg void OnAppAbout();
  DECLARE_DYNAMIC(CMyApp)
  DECLARE_MESSAGE_MAP()
};
