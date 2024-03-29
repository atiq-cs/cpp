### Learning Resources
**Listing**,  
- [Command Line Parsing Ref](https://github.com/atiq-cs/cpp/blob/dev/MFC/Tutorials/CommandLineParsing.md)
- [Unicode Conversion Ref](https://github.com/atiq-cs/cpp/blob/dev/MFC/Tutorials/UnicodeConversion.md)
- [VC Samples](https://github.com/atiq-cs/cpp/blob/dev/MFC/Tutorials/VCSamples.md)
- [WINVER def ref on Win32 ReadMe](../../Win32/Tutorials#target-platforms-win32)


### Teaching Assignments

**Assignment 01**  
Write an MFC program that will display a dialog box that will have,
- An edit control
- An OK button
- A static control  
  
When we click ok, static control will echo what is typed on the edit control. However, it will replace all texts "smile" to ":)" all texts "sad" to ":("  

**Assignment 02**  
Modify assignment 1 to support following,  
- Pressing ESC Keyboard button should not close dialog box!

**Assignment 03**  
String operations:

- Part a  
1. Concatenate texts from two edit controls and display in a static control.  
2. On another static control display length of the string.  
  
  
- Part b  
  - Among two edit controls in one we wanna input a large string (haystack).
  - On second one we wanna input a small string (needle).
  - Finally, for output, on a static control, display how many times small string has been found (number of occurrences) and also show index of the first encounter.  


**Assignment 04**  
Paint related task,  

- Part a  
There will be no control on the dialog window. In the Window you will draw some text using OnPaint.  

- Part b  
In addition to part a, change the text every second.  

*Revision: 07-16-2014, ref Sajid*

#### Solutions to Questions Above
**Assignment 01**  
When we click ok, static control will echo what is typed on the edit control. However, it will replace all texts "smile" to ":)" all texts "sad" to ":("  

A: *ref, test3, 07-17-2014*  
  
Here's an example how to accomplish this,

```cpp
void CChatDlg::OnBnClickedSendButton()
{
  m_inputEdit.GetWindowText(m_StaticText);
  m_chatBox.Replace(_T("sad"), _T(":("));
  m_chatBox.Replace(_T("smile"), _T(":)"));
  UpdateData(FALSE);
}
```

Data Exchange bindings look like this member variables `m_inputEdit` and `m_StaticText`,
```cpp
void CChatDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_EDIT, m_inputEdit);
  DDX_Text(pDX, IDC_STATIC, m_StaticText);
}
```

We learnt from above example that, after updating value of a DDX bound variable following method call syncs data to the UI Control,
```cpp
UpdateData(FALSE);
```

Message mapping for the button looks like this (generated by VS),

```cpp
BEGIN_MESSAGE_MAP(CChatDlg, CDialogEx)
  // ...
  ON_BN_CLICKED(IDC_BUTTON, &CChatDlg::OnBnClickedSendButton)
END_MESSAGE_MAP()
```


#### String Manipulation and Get / Set Texts on Edit/Static Controls
Here's an example of getting 2 string contents from 2 Edit controls,

    TCHAR str1[1000], str2[1000];
    
    m_inputEdit1.GetWindowTextW(str1, 1000);
    m_inputEdit2.GetWindowText(str2, 1000);

concatenate two strings.  
*Note*: In a Unicode project, `GetWindowText` resolves to `GetWindowTextW`  (project settings → Use Unicode Charset, flags: `UNICODE` and `_UNICODE`),

Using the strings from code example above, we can contenate them,

    _tcscat(str1, str2);


Another way to concatenate,

    m_inputEdit1.GetWindowText(cs1);
    m_inputEdit2.GetWindowText(cs2);
    
    // m_StaticText is bound to the STATIC Control that we are using for output
    m_StaticText = cs1 + cs2;
    // Update the content on the window control
    UpdateData(FALSE);

`m_StaticText` is bound to the control for data in following way,

    void Ctest5Dlg::DoDataExchange(CDataExchange* pDX) {
      // ...
      DDX_Text(pDX, IDC_STATIC, m_StaticText);


Initialized in Dialog's constructor,

    Ctest5Dlg::Ctest5Dlg(CWnd* pParent /*=NULL*/)
      : CDialogEx(Ctest5Dlg::IDD, pParent)
      , m_StaticText(_T(""))
    {
      // ... ...
    }


We can use `GetDlgItem` to set/retrieve text. Here's an example, how to set,

    // Example static control instance
    CStatic* staticText;     

    // retrieve control pointer
    staticText = (CStatic *) GetDlgItem(IDC_STATIC);
    // set text using the control variable retrieved
    staticText->SetWindowText(str);


**Modeless Dialogs**  
[Nish Nishant - Modeless Dialogs with MFC](https://www.codeproject.com/Articles/1651/Tutorial-Modeless-Dialogs-with-MFC)

**Access Main Window Frame in Timer Proc**  
Use of `CWnd::PostMessage` in Timer Callback Proc,
Example code,

```cpp
void MainFrame::OnPaint() {
  CFrameWnd::OnPaint();
  SetWindowText(_T("The window has been painted."));
  m_Label.SetWindowText(TextStr);
}

void CALLBACK EXPORT MainFrame::TimerProc (HWND hWnd, UINT nMsg, UINT nTimerID, DWORD dwTime) {
  MainFrame* pMainWnd = (MainFrame *) AfxGetMainWnd();

  static int i = 0;
  _stprintf(pMainWnd->TextStr, _T("Seconds passed %d"), i++);

  pMainWnd->PostMessage(WM_PAINT, (LPARAM) 0, (LPARAM) 0);
}
```

ref, *P08_TimerCallback\ping.cpp*, 04-2010

#### Appendix
**MFC Threading API**  
Example,

    AfxBeginThread(WorkerThreadDNSLookUpProc, this);

**RichEditControl, 07-21-2014**  
It creates a new window naming the pointer as Dlg. However, it does a call for Create Window,

```cpp
void CRichEditControlDlg::OnBnClickedButtonOk()
{
  HWND wndTop;
  CWnd* sdlg = new CWnd();
  CDialogEx* cdlg = new CDialogEx();
  sdlg = cdlg;
  sdlg->Create(_T("STATIC"), _T("Hi"), WS_CHILD | WS_CAPTION | WS_SYSMENU, CRect(100, 100, 400, 400), this, 1234);

  // Probably tried because that new Window wasn't getting focus
  // sdlg->SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOSIZE);

  sdlg->ShowWindow(SW_SHOWNORMAL);
  // Resize Example? Lookup ref MSFT Doc
  // sdlg->MoveWindow(CRect(10, 10, 400, 400));
}
```

A Screenshot from the 'Rich Edit Control' Sample is presented below,  
  
![RichEditControl Sample Screenshot](https://user-images.githubusercontent.com/7858031/221075250-a4c1e4f3-d485-4670-a73c-57c1d649fa26.png)


**CustomDialog 07-21-2014**  
On the contrary, *CustomDialog* creates a second dialog from resource file Dialog Definition (dlg id) (not reproduced here since it's easy to create!).

### Adding Controls By Hand
As per [MSFT - MFC UI Elements - Adding Controls By Hand](https://learn.microsoft.com/en-us/cpp/mfc/adding-controls-by-hand), we can either add controls to a dialog box with the dialog editor or add them yourself, with code. Also, look at VC Sample on Custom Control.

**Window Styles**  
For Edit Controls, `ES_MULTILINE` specifies multi-line, example,

    m_Edit.Create(ES_MULTILINE | ES_AUTOHSCROLL | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,
        CRect(10, 50, 150, 70), this, 0x1552);


ref, *P06_CEdit\P6_CEdit.cpp*, 06-26-2010

**ToolTip**  
How to add a ToolTip, following code segment extracted,

First, we add following in `MainDlg::OnInitDialog()`,

```cpp
m_pTooltip = new CToolTipCtrl;
if(!m_pTooltip->Create(this, WS_POPUP | TTS_ALWAYSTIP))
{
  TRACE("Unable To create ToolTip\n");
  return TRUE;
}

// ref: http://msdn.microsoft.com/en-us/library/s2y2wf56(v=vs.110).aspx
// The lpRectTool and nIDTool parameters must both be valid, or if lpRectTool is NULL, nIDTool must be 0.
// CWnd* pWnd = GetDlgItem(IDC_BUTTON_TEST);
VERIFY(m_pTooltip->AddTool(&m_Btn, _T("smileee text over here unbelievable!!!")));
// CToolInfo ti(TTF_SUBCLASS, buttonTest, 0, NULL, _T ("bla-bla-bla")); 
// EnableToolTips();
// ref, http://msdn.microsoft.com/en-us/library/7tabdbhs(v=vs.110).aspx 
m_pTooltip->Activate(TRUE);
```

Second, in `PreTranslateMessage`, we enable relaying of the tooltip messages,

```cpp
BOOL MainDlg::PreTranslateMessage(MSG* pMsg)
{
	if (nullptr != m_pTooltip)            
      m_pTooltip->RelayEvent(pMsg);

	return CDialogEx::PreTranslateMessage(pMsg);
}
```

**ScreenSaver App**  
ref, 'p18_ScreenSaver02\ScreenSaver.cpp', 04-13-2011
Section added following from functionx.com, tried this earlier on a dialog then tried to move this to a Window / Frame,  

```cpp
void MainFrame::OnTimer(UINT nIDEvent) {
  // TODO: Add your message handler code here and/or call default
  CClientDC dc(this);

  int x = (rand() % Width) - 10;
  int y = (rand() % Height) - 10;
  CBrush BrushRand(RGB(rand() % 255, rand() % 255, rand() % 255));
  CPen   PenRand(PS_SOLID, 1, RGB(rand() % 255, rand() % 255, rand() % 255));

  CBrush *pOldBrush = dc.SelectObject(&BrushRand);
  CPen   *pOldPen   = dc.SelectObject(&PenRand);
  
  switch(rand() % 5)
  {
  case 0:
    dc.Ellipse(x, abs(y-200), abs(y-x), y);
    break;
  case 1:
    dc.Rectangle(y, x, abs(y-x), (x+y)%255);
    break;
  case 2:
    dc.RoundRect(y, x, y, x, abs(x-y), x+y);
    break;
  case 3:
    dc.Ellipse(y, x, abs(x-y), x+y);
    break;
  case 4:
    dc.Rectangle(x, y, abs(x-y), x+y);
    break;
  }

  dc.SelectObject(pOldBrush);
  dc.SelectObject(pOldPen);

  CWnd::OnTimer(nIDEvent);
}
```