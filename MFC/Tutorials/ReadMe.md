### Teaching Assignments

**Assignment 01**  
Write an MFC program that will display a dialog box that will have,
- An edit control
- An OK button
- A static control  
  
When we click ok, static control will echo what is typed on the edit control. However, it will replace all texts "smile" to ":)" all texts "sad" to ":("  

A: Here's an example how to accomplish this,
```cpp
void CChatDlg::OnBnClickedSendButton()
{
  m_inputEdit.GetWindowText(cstatic);
  m_chatBox.Replace(_T("sad"), _T(":("));
  m_chatBox.Replace(_T("smile"), _T(":)"));
  UpdateData(FALSE);
}
```

**Assignment 02**  
Modify assignment 1 to support following,  
- Pressing ESC Keyboard button should not close dialog box!

**Assignment 03**  
String operations:

- Part a  
1. Concatenate texts from two edit controls and display in a static control.  
2. On another static control display length of the string.  
  
  
- Part b  
Among two edit controls in one you input a large string, on second you input a small string. On a static control display how many time small string has been found and index of the first encounter.  

**Assignment 04**  
Paint related task,

- Part a  
There will be no control on the dialog window. In the Window you will draw some text using OnPaint.  

- Part b  
In addition to part a, change the text every second.


*Revision: 07-16-2014, ref Sajid*
