## OOP Templates
This Win32 SDK Cpp Template, minimal C++ code for creating Win32 Apps.

**Window vs Dialog Based App**  
For an app with a Window instead of Dialog,  
One way to manage the UI control items under a Window is to create a class for the Main window and keep the handle for each control in the class as member.
  
For example, `hwndButton` for the button goes as a class member of the Main Window.  

  ref, [MSFT Learn - Win32 - How to Create a Button](https://learn.microsoft.com/en-us/windows/win32/controls/create-a-button)

Q: Does an app require main window as Dialog Box along with keyboard messages?  
A: Dialog Boxes are easy to create using resource editor, control items of the dialog box are easy to create and manage.
A Modeless Dialog however is pretty much like a Window. Guess that's why we created this template based on Modeless Dialog.


**P01_Modeless**  
- Base code without supporting keyboard events
- Build and run status: successful


![Screenshot of the running app](https://user-images.githubusercontent.com/7858031/216800365-e567e14d-8763-4f47-bcd6-e3332a9306f2.png)


**P02_Modeless_KB**
- Based on P01_Modeless above, fixes keyboard messaging problem
- Demonstrates how to disable pragma warning 4127

 - template which supports keyboards event, `KEY_UP`, ref, [MSFT Learn - Win32 UI - WM_KEYUP message](https://learn.microsoft.com/en-us/windows/win32/inputdev/wm-keyup)
 - `getmessage` has been replaced with `peekmessage`
 - accelerators are still enabled
 - some class members have been temporarily changed to public (roll back for better encapsulation, later)

![Screenshot of the running app](https://user-images.githubusercontent.com/7858031/216800336-80dc4ab7-9368-4eae-96e5-7d75f95e0d70.png)

**Difference between two projects above**
MainDialog.cpp
- pretty much same

MainDialog.h
- makes `m_hDlg` and `ProcessMessage(HWND, UINT, WPARAM, LPARAM)` public

Main.cpp (WinMain)
- Messaging has been changed to use `PeekMessage` so that we can access `KEY_UP` messages and respond to them.


**Refs**  
1. [SO - Keyboard Input & the Win32 message loop](http://stackoverflow.com/q/2441457)
2. [SO - C4127: Conditional Expression is Constant](http://stackoverflow.com/q/25573996)
