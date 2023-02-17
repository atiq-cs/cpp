### Shutdown Timer
Shut your computer down at specified time and date.

It's efficient and small in size since being written in Win32.


**Build instructions**  
- It was an MBCS (non Unicode) Program. Converted to Unicode through Generic TCHAR.
- We gotta remember to link against comctl32.lib (add this lib to linker cmd).

**Code**  
Retained the previous comment style for cpp which looks like this,

```cpp
/*
 * Author :
 * Date   : 
 * Status :
 * Remarks:
 * 
 */
```

**App Screenshots**  
*Runs in Windows 8/7 and earlier*  

![Shutdown Timer App Screenshot](https://user-images.githubusercontent.com/7858031/219719946-6aeaa4a2-5a6f-4466-9238-b91549efad26.png)

About Dailog Box,  
  
![Shutdown Timer App About Dialog Box](https://user-images.githubusercontent.com/7858031/219719970-91a552b1-5fcd-4af2-8124-f8dbcfc9145f.png)


**Refs**  
- Merged from [GitLab](https://gitlab.com/atiq-cs/Merged_ShutdownTimer), linked here for file history.
- Earlier version was in [sourceforge - stdt](https://sourceforge.net/projects/stdt)



**06-2011 plans**  
- Create installer using NullSoft System

Following features have to be maintained or added,
- Last date and time will be stored in registry or in a settings file so that next time it is shown.
- An option to start the software automatically.
- Schedule shutdown at certain date and time
- Run a specified task at specified time
- There should be a feedback option so that users can report errors
- Balloon tips when time expires
- System tray icon


**Installer Refs**  
For this project, after trying both Windows Installer (MSI) and InstallShield we went with InstallShield i.e., release 1.0-b3 on Github.

InstallShield (as part of VS Setup Project) creates a large dir path for the installer in output: "ShutdownTimer_setup\Express\SingleImage\DiskImages\DISK1\*.exe*  

Earlier we tried MSI Setup, related files are archived in [GitLab](https://gitlab.com/atiq-cs/Merged_ShutdownTimer/-/tree/dev/MSI_Setup)
from 11-25-2009,  
- [MSFT Docs - Windows Installer - An Installation Example](https://learn.microsoft.com/en-us/windows/win32/msi/an-installation-example)

Example cmd, 11-25-2009  

    d:\Win7\MsiVal2\msival2.exe G:\Sourcecodes\Win32\winAPI\ShutDownProgram\Setup\st_installer.Msi "c:\Program Files\Microsoft SDKs\Windows\v6.0A\bin\msitools\Schemas\MSI\120\darice.cub"

Project was in [sourceforge](http://sourceforge.net/projects/stdt) earlier.

ref, ShellControl.cpp, 11-23-2009

```cpp
case WM_TIMER:
  GetLocalTime(&lt);
  InvalidateRect(hWnd, NULL, true);

  if ((lt.wHour > 1 && lt.wHour < 7) || (lt.wHour > 16 && lt.wHour < 19))
  {
    //if (lt.wHour == 17 && lt.wMinute == 22) {
    if (count == 25) {
      ShowWindow(hWnd, SW_SHOWNORMAL);
      UpdateWindow(hWnd);
      SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE);
    }

    // Time count for shutdown in 2:00 and 17:00
    if ((lt.wHour==2 && lt.wMinute==0) || (lt.wHour==17 && lt.wMinute==0))
      count--;
    else
      count = 0;

    if (count == 0)
    {
      if (MySystemShutdown())
        sprintf_s(greeting, "Shutdown call successful.");
      else
        sprintf_s(greeting, "Shutdown call failure.");
    }
  }
  break;
```

Example action on signal to terminate the app,

```cpp
case WM_CLOSE:
  // process close event alt+f4 or clicking close button
  sprintf_s(greeting, "Cool down. Alt+F4 for goodness.");
  InvalidateRect(hWnd, NULL, false);
  isPressed = TRUE;
  break;
```

Registered class had `CS_NOCLOSE` in it,

```cpp
wcex.style          = CS_HREDRAW | CS_VREDRAW | CS_NOCLOSE;
```



dll location, ref, 03-2016

    C:\Program Files (x86)\Microsoft Visual Studio 11.0\VC\redist\x86\Microsoft.VC110.CRT