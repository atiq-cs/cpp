// ChatControl.cpp : implementation file for our custom chat control
// We create a new window class for our control
// register it into the system, control window is created automatically by dialog using resource file
//   hence, scrollbar is automatically added to the control
// Implements drawing and chat data structure for it

#include "afxwin.h"

class CChatEdit :
  public CEdit
{
public:
  CChatEdit(void);
  ~CChatEdit(void);
//  virtual void PreSubclassWindow();
};
