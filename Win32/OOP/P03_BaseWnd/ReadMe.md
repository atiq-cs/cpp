## P03 Window Based Template
*Note: this template is updated based on P04_VS2022.*  

This is an OOP Skeleton with an actual Window as Base. It features,
- Standard App Menu
- Window which can be drawn or an app can be developed

### Troubleshooting
**Not Passing Application State Pointer Properly**  
Window was being created. However, application state was being lost. As a result,
- Our custom WndProc wasn't recieving any messages!
- Nothing was being drawn as WM_PAINT wasn't being received!
- Menu commands were not recieved as it was missing WM_COMMAND as well. Logically, message hook was broken!

What was I thinking? Turns out I wasn't passing the pointer of the class anywhere. How could we expect to retrieve it magically via lParam if we haven't stored it there in first place. Anyways, TLDR; had to RTFM for this missing bit!

It was working because `CreateWindow` call was valid and it was just using `DefWndProc` for Message hooks.

And, this is what fixes it. We gotta pass the class object pointer via `lpParam`, otherwise above happens.
[MSFT Doc - CreateWindowExW](https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-createwindowexw)'s last param is where we must pass the class pointer.

**Copy Paste Bug**: This bug was created by Copy Pasting the `CreateWindow` call from SDK Template.

*Notes*  
We are retrieving the pointer value when `WndProc` receives a `WM_NCCREATE` message. However, this can be recovered through `WM_CREATE` as well. In below example, we are showing how to cast the pointers slightly differently,

```cpp
if (uMsg == WM_CREATE)
{
  CREATESTRUCT* pCreate = (CREATESTRUCT *) lParam;
  pThis = (DERIVED_TYPE *) pCreate->lpCreateParams;
  SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR) pThis);
}
else
  pThis = (DERIVED_TYPE *) GetWindowLongPtr(hWnd, GWLP_USERDATA);
```

Window creation fails on the line below when we did not pass the class pointer in `lpParam` in the first place!

```cpp
if (uMsg == WM_NCCREATE)
{
    // ... ...
    pThis->m_hWnd = hWnd;
}
```

**Refs**  
- Primary [MSFT Doc - Managing Application State](https://learn.microsoft.com/en-us/windows/win32/learnwin32/managing-application-state-)
- How can I make a WNDPROC or DLGPROC a member of my C++ class, [Raymond Chen - MSFT Blog](https://devblogs.microsoft.com/oldnewthing/20140203-00/?p=1893)
- [MSFT - Windows-classic-samples - OOP Sample BaseWindow](https://github.com/microsoft/Windows-classic-samples/tree/main/Samples/Win7Samples/begin/LearnWin32/BaseWindow), Source File of Interest: `Main.cpp`, related, MSFT Doc on Sample Info, [BaseWindow Sample](https://learn.microsoft.com/en-us/windows/win32/learnwin32/basewindow-sample)
 

Previous two projects:
- [P01_Modeless](https://github.com/atiq-cs/cpp/tree/dev/Win32/OOP/P01_Modeless)
- [P02_Modeless_KB](https://github.com/atiq-cs/cpp/tree/dev/Win32/OOP/P02_Modeless_KB)

founded the OOP code based on a Modeless Dialog. However, this one is founded on **Wnd**.

Refs on `WM_COMMAND`,  
- Restating the obvious about the WM_COMMAND message, [MSFT Blog - Raymond Chen](https://devblogs.microsoft.com/oldnewthing/20060302-10/?p=32093)


*Screenshot*  

![P03 Window Based OOP Template](https://user-images.githubusercontent.com/7858031/218355852-689d1d3c-3c4e-474e-864c-be2e117c0dbb.png)
