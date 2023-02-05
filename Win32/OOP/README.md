## OOP-Templates
This Win32-SDK-Cpp-Template, minimal C++ code for creating Win32 Apps.

**Window vs Dialog Based App**  
For an app with a Window instead of Dialog,  
One way to manage the UI control items under a Window is to create a class for the Main window and keep the handle for each control in the class as member.
  
For example, `hwndButton` for the button goes as a class member of the Main Window.  
 ref, [MSFT Learn - Win32 - How to Create a Button](https://learn.microsoft.com/en-us/windows/win32/controls/create-a-button)

**P01_Modeless**  
- Base code without supporting keyboard events
- Build and run status: successful


![Screenshot of the running app](https://user-images.githubusercontent.com/7858031/216797833-ad281a5c-b468-41f7-a214-02d71c95b178.png)


**P02_Modeless_KB**
- Fixes keyboard messaging problem
- Demonstrates how to disable pragma warning 4127
