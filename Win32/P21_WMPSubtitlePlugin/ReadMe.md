### P21 Windows Media Player Native Subtitle Plugin
This project has been merged from prev. repo: [atiq-cs/WmpSubtitlePlugin](https://gitlab.com/atiq-cs/Merged_WmpSubtitlePlugin/-/tree/dev/WMPPluginDsp). For earlier commit log and history please have a look at that.

Recent editions of Windows Media Player uses Microsoft Media Foundation. Media Foundation has pros and performance improvements.

Using a directshow filter to render captions while Media Foundation is being used for video rendering hurts the rendering performance. It can be lagging sometimes. It is why, our target is to enable captions in WMP for some unsupported subtitle formats without altering media foundation pipeline (so that it doesn't have to add a an additional directshow filter). 

*Our target is to build a plugin for Windows Media Player that will:*
  * Create supported SAMI caption from unsupported format
  * Enable displaying this caption while playing the video
  * Provide settings to configure this plugin 

Enabling this plugin we are able to enable captions with Video when opened with Media Player. For detailed overview on this project please read the [article on codeproject](http://www.codeproject.com/Articles/766246/Windows-Media-Player-Native-Subtitle-Plugin-Cplusp)


- Based on Microsoft sample plugin: 'wmpplugin1'
- Utilizes COM and Win32 to build the plugin dll.
- We call it native since it's written in Win32 C++ directly targetting Windows.

Features,
- Launching MS Store Apps from COM
- Subtitle Converter (from on Sub format to another)
- Properly detecting encoding of input text file


#### Developer Doc
ref, CaptionDevPlan.docx, 06-11-2014  

**Windows Media Player Plugin Development**  
Perusing ref, [MSFT - Windows Media Player Plug-ins](https://learn.microsoft.com/en-us/windows/win32/wmp/windows-media-player-plug-ins) we find following options.


**Option 1: Windows Media Player User Interface Plug-ins**  
Windows Media Player user interface plug-ins add new functionality to the Now Playing pane of the full mode Player. You can create plug-ins that use the visualization area, a separate window, the settings area, the metadata area, or background plug-ins that expose no visible user interface.

**Option 2: Follow DSP or Rendering Samples**  
If other options don't work then we have following ways:
- Windows Media Player DSP Plug-ins
- Windows Media Player Rendering Plug-ins (deprecated)


**Building WMP Plug-in**  
[MSFT - The Windows Media Player SDK](https://learn.microsoft.com/en-us/windows/win32/wmp/windows-media-player-sdk) includes a plug-in wizard that you can use to build several types of plugins. The following topics describe how to install and use the wizard.


Followed the procedure: [MSFT - Getting Started with the Plug-in Wizard](https://learn.microsoft.com/en-us/windows/win32/wmp/getting-started-with-the-plug-in-wizard) and [MSFT - Using the Plug-in Wizard with Visual Studio](https://learn.microsoft.com/en-us/windows/win32/wmp/using-the-plug-in-wizard-with-visual-studio) we created a working plugin dll.

We register the dll using an elevated prompt. `/s` stands for "Silent, display no message boxes",

    $ regsvr32 /s "WMPNativeSubtitle\Debug\WMPNativeSubtitle_plugin.dll"

  
  
![regsvr32 command line Dlg Box](https://user-images.githubusercontent.com/7858031/219970548-f234778e-80ef-45bf-89bd-63926490bf8b.png)
  
Interesting: not seeing a regsvr64 binary being available!

**About User Interface Plug-ins**  
Like skins we don't need to recreate UI. We want to add functionalities to full mode of the player. We can add custom UI-plugins. It is provided by COM.  

**UI Plug-in Overview**  
Points noted below:  
- UI plug-ins can be installed, uninstalled, and configured using the Plug-ins tab of the Options dialog in Windows Media Player.
- There are five types of UI plug-ins supported by Windows Media Player. Three of these types correspond to different areas of the Now Playing pane of the full mode of the player.
- The other two types are for plug-ins that display in a separate window and for plug-ins that have no display (except perhaps a property page).
- UI plug-ins are unloaded when they are closed or disabled. UI plug-ins that appear in the Now Playing pane are also unloaded when the user chooses another plug-in of the same type or switches out of the Now Playing pane. When the user switches to skin mode, all plug-ins remain loaded, but are not displayed. If separate window or background plug-ins are running when Windows Media Player is closed, they will be automatically reloaded the next time the player is started.  
  
There are several sub-topics. We are choosing only Background Plug-ins for relevance.

**Background Plug-ins**  
Background UI plug-ins do not actually have user interfaces unless they implement property pages. When one or more background plug-in is running, a special icon appears in the Windows Media Player display next to the running track time. This icon can be clicked to display the background plug-ins options in the Options dialog box. From there, the user can choose to open the property page of any plug-in that supports one.  
  
Background plug-ins are useful for providing automatic services that do not require user input.

Getting the file open notification (WMPOpenState), ref [MSFT - WMPOpenState enumeration
](https://learn.microsoft.com/en-us/previous-versions/windows/desktop/api/wmp/ne-wmp-wmpopenstate)

Enumeration members which can be useful to us,

    wmposPlaylistChanging         = 1,
    wmposPlaylistLocating         = 2,
    wmposPlaylistConnecting       = 3,
    wmposPlaylistLoading          = 4,
    wmposPlaylistOpening          = 5,
    wmposPlaylistOpenNoMedia      = 6,
    wmposPlaylistChanged          = 7,
    wmposMediaChanging            = 8,
    wmposMediaLocating            = 9,
    wmposMediaConnecting          = 10,
    wmposMediaLoading             = 11,
    wmposMediaOpening             = 12,
    wmposMediaOpen                = 13,


**Fixing caption height**  
Default Hexadecimal value of "CaptionsHeight" is 64. I changed it to 32. We change it via Windows Registry Editor,

    Windows Registry Editor Version 5.00

    [HKEY_CURRENT_USER\Software\Microsoft\MediaPlayer\Player\Tasks\NowPlaying]
    "InitFlags"=dword:00000001
    "ShowHorizontalSeparator"=dword:00000001
    "ShowVerticalSeparator"=dword:00000001
    "PlaylistWidth"=dword:000000ba
    "PlaylistHeight"=dword:00000064
    "SettingsWidth"=dword:00000064
    "SettingsHeight"=dword:00000087
    "MetadataWidth"=dword:000000ba
    "MetadataHeight"=dword:000000a0
    "CaptionsHeight"=dword:00000032

For reference, the line with original value is,

    "CaptionsHeight"=dword:00000048

In addition, to figure that we also figured out how to set WMP 64 bit as default.

**Windows Media Player 64 bit to Set as Default**  
This registry settings allows us to set WMP 64 bit as default,

    Windows Registry Editor Version 5.00

    [HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\App Paths\wmplayer.exe]
    @=hex(2):25,00,50,00,72,00,6f,00,67,00,72,00,61,00,6d,00,46,00,69,00,6c,00,65,\
      00,73,00,25,00,5c,00,57,00,69,00,6e,00,64,00,6f,00,77,00,73,00,20,00,4d,00,\
      65,00,64,00,69,00,61,00,20,00,50,00,6c,00,61,00,79,00,65,00,72,00,5c,00,77,\
      00,6d,00,70,00,6c,00,61,00,79,00,65,00,72,00,2e,00,65,00,78,00,65,00,00,00
    "Path"=hex(2):25,00,50,00,72,00,6f,00,67,00,72,00,61,00,6d,00,46,00,69,00,6c,\
      00,65,00,73,00,25,00,5c,00,57,00,69,00,6e,00,64,00,6f,00,77,00,73,00,20,00,\
      4d,00,65,00,64,00,69,00,61,00,20,00,50,00,6c,00,61,00,79,00,65,00,72,00,00,\
      00

**Getting smi file path**  
```cpp
hr = m_spCore->get_closedCaption(&spWMPClosedCaption);
if (FAILMSG(hr))
    return true;
  BSTR smiFileName;
  hr = spWMPClosedCaption->get_SAMIFileName(&smiFileName);
  if (FAILMSG(hr))
    return TRUE;
```

**Deployment of the Plugin DLL**  
When new OS (Windows) is installed, C++ redistributable is not available by default, hence, the dll registration will fail due to missing deps!

    regsvr32 x64\Release\WMPNativeSubtitle_plugin_x64.dll

**TODO**  
If there is not an extra blank line in the file then print ending subtitle from buffer.
Match sequence numbers
Support more formats such as sub, ssa/ass; conversion from ass files
In property sheet add following option
Hide smi file


**Refs**  
- WMP official samples including Wizard can be found in our [primary Samples Doc](https://github.com/atiq-cs/cpp/blob/dev/Win32/Samples.md)
- DSP Sample is archived at [atiq-cs/WmpSubtitlePlugin](https://gitlab.com/atiq-cs/Merged_WmpSubtitlePlugin/-/tree/dev/WMPPluginDsp)
- MSFT - [Windows Media Player DSP Plug-ins](https://learn.microsoft.com/sl-si/windows/win32/wmp/windows-media-player-dsp-plug-ins)
- MSFT - [Getting Started with the Windows Media Player SDK](https://learn.microsoft.com/en-us/windows/win32/wmp/getting-started)


**Bug fixes for some subtitle files**  
Following special characters are not appearing correctly just like many other Unicode characters.  

| Character | HEX Value | Real Unicode Value                                          |
| --------- | --------- | ----------------------------------------------------------- |
| ’         | E28099    | http://www.fileformat.info/info/unicode/char/2019/index.htm |
| ”         | E2809D    | http://www.fileformat.info/info/unicode/char/201d/index.htm |


Some Refs related to the fix,
- http://stackoverflow.com/questions/3942888/unicodeencodeerror-latin-1-codec-cant-encode-character
- [cam.ac.uk - utf-8 Specs](http://www.cl.cam.ac.uk/~mgk25/unicode.html#utf-8)


More caption line related to unicdoe char bug; ref, The Fast and the Furious: Tokyo Drift (2006)  

    277
    00:37:21,609 --> 00:37:23,167
    I don't care
    if you're sick as a dog ...

    278
    00:37:23,244 --> 00:37:24,939
    or in bed with Beyoncé.


**Next Project**  
Building a new video player with Media Foundation support.  
MSFT will add captioning I guess… Just need to wait…  (well, latest update, they did!)

**Revision History**  
Earlier commit log and history is at: [atiq-cs/WmpSubtitlePlugin](https://gitlab.com/atiq-cs/Merged_WmpSubtitlePlugin/-/tree/dev/WMPPluginDsp).
Additionally, found in a revision log text file, 'WMPNativeSubtitle_gc_vc.log', 05-24-2014,

WIP Tasks,
- provide release in project directory, create installer
- Optimize code
- Bjarne stroutsup.. follow standard practices..
- add option whether to keep smi with media
- add option whether to enable unicode support or not...
- add metro app launch
- remove all unnecessary `pSamiConverter` parameters


**Nits**  
In earlier versions of this project we implemented some cool stuffs such as launching store app which is documented below for reference.

**Comment Style**  
Standard comment style is found in [atiq-cs/WmpSubtitlePlugin](https://gitlab.com/atiq-cs/Merged_WmpSubtitlePlugin/-/tree/dev/WMPPluginDsp),

```cpp
/////////////////////////////////////////////////////////////////////////////
// CWmpplugin_dsp::FinalConstruct
//
// Called when an plug-in is first loaded. Use this function to do one-time
// intializations that could fail instead of doing this in the constructor,
// which cannot return an error.
/////////////////////////////////////////////////////////////////////////////
```

**How to launch a Store App**  
Not sure if this is a good idea to launch a store app from this plugin through WMP and then to close WMP. However, it did work.

In 'WMPNativeSubtitleevents.cpp' under
```cpp
case wmposMediaOpen:
```

We put,

```cpp
if (EnableCaptionFromSubtitle() == FALSE) {
  // subtitle not available, start metro video app for supported formats
  if (FileExtSupportedInZuneVideoAppX(m_sFilePath)) {
    // if subtitle does not exist
    //HRESULT hr = FAILMSG(StartAppxZuneVideo(m_sFilePath));
    HRESULT hr = S_OK;
    if (hr == S_OK) {
      m_spCore->close();

      // success from here: http://objectmix.com/dotnet/99057-how-close-windows-media-player-window.html
      // back up ref: http://www.pcreview.co.uk/forums/close-windows-media-player-window-t3102832.html
      HWND iHwnd = ::GetForegroundWindow( );
      PostMessage(iHwnd, WM_CLOSE, 0, 0);
      hr = FAILMSG(StartAppxZuneVideo(m_sFilePath));
    }
    break;
  }
}
```

And the implementation for that was defined in 'WMPNativeSubtitle.cpp',
```cpp
HRESULT StartAppxZuneVideo(LPWSTR streamFile) {
  HRESULT hrResult = S_OK;

  if (SUCCEEDED(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED)))
  {
    DWORD dwProcessId = 0;
    // ref for app model id: http://stackoverflow.com/questions/12925748/iapplicationactivationmanageractivateapplication-in-c
    hrResult = LaunchAppForFile(TEXT("Microsoft.ZuneVideo_8wekyb3d8bbwe!Microsoft.ZuneVideo"), streamFile, &dwProcessId);
    // hrResult = LaunchApp(TEXT("Microsoft.ZuneVideo_1.4.19.0_x64__8wekyb3d8bbwe"), &dwProcessId);

    CoUninitialize();
  }

  return hrResult;
}

#include "Shobjidl.h"

HRESULT LaunchAppForFile(LPCWSTR strAppUserModelId, LPCWSTR szFilePath, PDWORD pdwProcessId)
{
  // MessageBox(NULL, metroArgs, TEXT("msgbox arg"), MB_OKCANCEL);

  CComPtr<IApplicationActivationManager> spAppActivationManager;
  HRESULT hrResult = E_INVALIDARG;

  if (strAppUserModelId)
  {
    // Instantiate IApplicationActivationManager
    hrResult = CoCreateInstance(CLSID_ApplicationActivationManager,
        NULL,
        CLSCTX_LOCAL_SERVER,
        IID_IApplicationActivationManager,
        (LPVOID*)&spAppActivationManager);

    if (SUCCEEDED(hrResult))
    {
        // This call ensures that the app is launched as the foreground window
        hrResult = CoAllowSetForegroundWindow(spAppActivationManager, NULL);
        
    }

    // Declare ShellITem
    IShellItemArray *psia;
    IShellItem* pItem = nullptr;

    if (SUCCEEDED(hrResult))
    {
      // ref, Chapter 8: Using Windows 7 Libraries and the Shell
      //  https://learn.microsoft.com/en-us/previous-versions/msdn10/ff934858
      hrResult = ::SHCreateItemFromParsingName(szFilePath, nullptr, IID_PPV_ARGS(&pItem));
    }

    if (SUCCEEDED(hrResult))
    {
      // SHCreateItemFromParsingNam
      // SHCreateShellItemArrayFromShellItem ref,
      //  https://learn.microsoft.com/en-us/windows/win32/api/shobjidl_core/nf-shobjidl_core-shcreateshellitemarrayfromshellitem
      hrResult = ::SHCreateShellItemArrayFromShellItem(pItem, IID_PPV_ARGS(&psia));    
      // Shell IID_PPV_ARGS ref
      //  https://learn.microsoft.com/en-us/windows/win32/api/combaseapi/nf-combaseapi-iid_ppv_args
      pItem->Release();
    }

    // if (SUCCEEDED(hrResult))
    // {
    //   // Create Shell item Array
    //   hrResult = SHCreateShellItemArray(NULL, psf_desktop, file_count, (PCUITEMID_CHILD_ARRAY) pidla,
    //     &This->psia_results);            
    // }
    
    // Launch the app
    if (SUCCEEDED(hrResult))
    {
      // hrResult = spAppActivationManager->ActivateApplication(strAppUserModelId,
      //     metroArgs,
      //     AO_NOSPLASHSCREEN,      // AO_NONE
      //     pdwProcessId);
      hrResult = spAppActivationManager->ActivateForFile(strAppUserModelId,
          psia,      // ISheelItemArray
          NULL,      // String verb
          pdwProcessId);
      psia->Release();
    }
  }

  return hrResult;
}
```

This was in 'SAMIConversion.cpp' earlier in,

```cpp
BOOL SubToSAMIConverter::read_data_into_buffer() {
```

version to track error,

```cpp
if( FALSE == ReadFile(hInFile, ReadBuffer, READBUFFERSIZE-1, &dwBytesRead, NULL) )
{
  // DisplayFileManagementError(TEXT("ReadFile"));
  CloseHandle(hInFile);
  hInFile = NULL;
  // returns false on eof
  writeLog(TEXT("read_data_into_buffer:: Buffer reading failed.\r\n"));
  return FALSE;
}
```

```cpp
void DisplayFileManagementError(LPTSTR lpszFunction) 
// Routine Description:
// Retrieve and output the system error message for the last-error code
{ 
    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError(); 

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, 
        NULL );

    lpDisplayBuf = 
        (LPVOID)LocalAlloc( LMEM_ZEROINIT, 
                            ( lstrlen((LPCTSTR)lpMsgBuf)
                              + lstrlen((LPCTSTR)lpszFunction)
                              + 40) // account for format string
                            * sizeof(TCHAR) );
    
    if (FAILED( StringCchPrintf((LPTSTR)lpDisplayBuf, 
                     LocalSize(lpDisplayBuf) / sizeof(TCHAR),
                     TEXT("%s failed with error code %d as follows:\n%s"), 
                     lpszFunction, 
                     dw, 
                     lpMsgBuf)))
    {
        MessageBox(NULL, TEXT("FATAL ERROR: Unable to output error code."), TEXT("Error"), MB_OK);
    }
    
  MessageBox(NULL, (LPCTSTR) lpDisplayBuf, TEXT("Error"), MB_OK);
    // _tprintf(TEXT("ERROR: %s\n"), (LPCTSTR)lpDisplayBuf);

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
}
```

Earlier when we used launch Zune Video app using StartAppxZuneVideo probably we tried this to close the parent process WMP?
Following code was commented out,

```cpp
// GetTopWindow ref
//  https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-gettopwindow

// HWND iHwnd = ::GetTopWindow(0 );
if (iHwnd == NULL)
  MessageBox(NULL,  TEXT("got handle null"), TEXT("handle"), MB_OKCANCEL);

// Taking a Snapshot and Viewing Processes ref,
//  https://learn.microsoft.com/en-us/windows/win32/toolhelp/taking-a-snapshot-and-viewing-processes
// HWND parentWnd;
PROCESSENTRY32 entry;
entry.dwSize = sizeof(PROCESSENTRY32);

HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

if (Process32First(snapshot, &entry) == TRUE)
{
  while (Process32Next(snapshot, &entry) == TRUE)
  {
    if (_tcsicmp(entry.szExeFile, _T("wmplayer.exe")) == 0)
    {  
      HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);

        if( hProcess == NULL )
          MessageBox(NULL,  TEXT("OpenProcess failed"), TEXT("OpenProcess"), MB_OKCANCEL);
        else {
          // ref: http://forums.codeguru.com/showthread.php?353149-How-to-Get-windows-Handle-using-Process-Id
          // HWND iHwnd = ::GetTopWindow(0 );
          while ( iHwnd )
          {
            DWORD pid;
            DWORD dwTheardId = ::GetWindowThreadProcessId( iHwnd,&pid);

            if ( pid == entry.th32ProcessID )
            {
              // here iHwnd is the handle to the window
              //MessageBox(NULL,  TEXT("got handle succeeded"), TEXT("handle"), MB_OKCANCEL);
              PostMessage (iHwnd, WM_CLOSE, NULL, NULL);
              SendMessage (iHwnd, WM_CLOSE, NULL, NULL);
              PostMessage (iHwnd, WM_CLOSE, NULL, NULL);
              SendMessage (iHwnd, WM_CLOSE, NULL, NULL);
              PostMessage (iHwnd, WM_CLOSE, NULL, NULL);
              SendMessage (iHwnd, WM_CLOSE, NULL, NULL);
              PostMessage (iHwnd, WM_CLOSE, NULL, NULL);
              SendMessage (iHwnd, WM_CLOSE, NULL, NULL);
              PostMessage (iHwnd, WM_CLOSE, NULL, NULL);
              SendMessage (iHwnd, WM_CLOSE, NULL, NULL);
              //PostMessage (iHwnd, WM_QUIT, NULL, NULL);
              break;
            }
            iHwnd = ::GetNextWindow( iHwnd , GW_HWNDNEXT);
          }

          // TerminateProcess ref
          //  https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-terminateprocess

          // TerminateProcess(hProcess, EXIT_SUCCESS);
          // ExitProcess (EXIT_SUCCESS);
          // MessageBox(NULL,  TEXT("OpenProcess succeeded"), TEXT("OpenProcess"), MB_OKCANCEL);
        }

      CloseHandle(hProcess);
    }
  }
}
CloseHandle(snapshot);
```
