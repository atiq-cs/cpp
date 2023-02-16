### CD/DVD Media Ejector
This software ejects CD/DVDROM Media.
After starting the software press 'Ctrl + J' to eject CD/DVDROM. Pressing 'Ctrl + J' again will close the CD/DVDROM.

**Why this software?**  
Recent statistics have emerged that use of button to eject CD/DVDROM often damages the drive. Hence, this to soft eject media drives specifically for CD/DVD!

**Features**  

- Ejects CD/DVD ROM
- Closes CD/DVD ROM

Uses commonly used shortcut key, Ctrl + J.


**Technical Details**  
Utilizes `mciSendCommand` from Winmm.lib to control the Media.


**Refs**  
- `OpenCloseMediaDrive` is based on Jagdish Bhimbha's post [MSDN Social](http://social.msdn.microsoft.com/Forums/en/Vsexpressvc/thread/8ea026f0-a81b-486f-a871-089323ceaa82)
- [codeproject - Detect cdrom](http://www.codeproject.com/Messages/2055140/Detect-CDROM-eject.aspx)
- http://stackoverflow.com/questions/1948780/the-best-way-to-always-detect-a-removable-device
- http://stackoverflow.com/questions/58670/windows-cdrom-eject
- http://www.experts-exchange.com/Programming/System/Windows__Programming/Q_10336052.html
- http://social.msdn.microsoft.com/Forums/en/Vsexpressvc/thread/8ea026f0-a81b-486f-a871-089323ceaa82


Initially, while figuring out the mechanism for ejecting media, I bumped into this,

```cpp
// LPCTSTR lpszCommand,
// LPTSTR lpszReturnString,
// UINT cchReturn,
// HANDLE hwndCallback

__declspec( dllimport ) int mciSendString(LPCTSTR lpszCommand, LPTSTR lpszReturnString, int cchReturn, HANDLE hwndCallback);

bool ProcessCDTray(bool open) {
  extern __declspec( dllexport ) HANDLE hwndCallback; 
  int ret = 0;

  // do a switch of the value passed
  switch (open)
  {
    case true:  // true = open the cd
      ret = mciSendString(_T("set cdaudio door open"), NULL, 0, hwndCallback);
      return true;
      break;
    case false: // false = close the tray
      ret = mciSendString(_T("set cdaudio door closed"), NULL, 0, hwndCallback);
      return true;
      break;
    default:
      ret = mciSendString(_T("set cdaudio door open"), NULL, 0, hwndCallback);
      return true;
      break;
  }
}
```
