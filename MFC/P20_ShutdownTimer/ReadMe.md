### Shutdown Timer
MFC draft version of the [Shutdown Timer project](../../Win32/P16_ShutdownTimer/) developed earlier using Win32 API. For reference and docs please look at the earlier project.

This MFC App version has following,
- Ballon Notification on Tray
- Sys Tray Icon

**Shutdown Timer Feature Lists**  
ref, 2013-01  

Following purpose, first TODO,  
- Shutdown computer in specified date and time

Next TODO,  
- Add the the software during Windows Start up
- User friendliness
  - Software should remember last settings (time and date)
  - Notify 1 minute before shutdown
  - Cancel option so that user can abort shutdown
  - Command Line support
- Implementation on other platforms


**App Screenshot**  
Main Dialog of the app,  

![Main Dialog](https://user-images.githubusercontent.com/7858031/222869546-8adaddae-1936-4f4e-ac40-3a7c86a687b4.png)

Balloon Notification on Tray,  

![Balloon Notification on Tray](https://user-images.githubusercontent.com/7858031/222869596-3aec72f5-3351-4eb8-9fee-c00c0d5e6fe5.png)


**Earlier thoughts**  
probably around 2013
TODO,  
- Checkbox to select shutdown everyday at this time: implement using registry

Which version to continue dev works,
- MFC version
- Previous Win32 C Version
- Or New OOP Implementation with OOP


**Refs**  
- [MSFT - MFC - Accessing File Status](https://learn.microsoft.com/en-us/cpp/mfc/accessing-file-status)
