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

![image](https://user-images.githubusercontent.com/7858031/216797647-4f1b2a77-87bc-4953-a200-5f9ff93488c7.png)


**P02_Modeless_KB**
- Fixes keyboard messaging problem
- Demonstrates how to disable pragma warning 4127
