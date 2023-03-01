### Ping GUI
**TODO: Migrate to MAUI**

**Net Notifier cross platform**  
*a.k.a Ping GUI (penguin misspelled)*  

*broken image link,*  
> [story02](http://saos.azurewebsites.net/out_of_app_images/PingStory02.jpg)

One app to perform Ping/ICMP, DNS lookup using this one tool including command line support.

The app is able to,
- ping specified host
- Show notification when internet is available

An app to inform whether internet is available or not
- If not available then it'd estimate some reasons why it is not available (sort of basic network diagnostics)
- It can notify when specified target is alive or internet is available
- GUI should be user-friendly and easy to use: automatic retrieval of network settings has been done on dialog box. Window has been replaced with progress-bar to accomplish this.

To make the app more user friendly we check for internet at startup of the application (enable single host). If available by default enable single host ping since pinging ISP would be redundant in that case.


This project, briefly,
- A Windows GUI app
- It can ping a specified host
- Can notify when the host comes alive and can stay hidden in system tray in the mean time
- Gives annoyance-free notifications using balloon tips
- And finally with interruptible ISPs it can check whether internet service is available
- Or can notify when internet is available.

Initial dialog window to specify target host,  

![Enter hosts info](https://user-images.githubusercontent.com/7858031/221956985-f6cc5075-d2f4-4301-8b10-1e5870f34a2f.png)

Ping in progress,  

![WIP app screenshot](https://user-images.githubusercontent.com/7858031/221957276-4ec0fdac-35b2-470c-8391-2c52f86c2be5.png)

Tray Notification,

![App Tray Notification screenshot](https://user-images.githubusercontent.com/7858031/221957356-537d282e-829d-4b30-b3d3-566ef3a592be.png)


Same approach to implement Tray Notification is used in [CD Eject](../../Win32/P14_CDEject/) project!
`Shell_NotifyIcon` for `NIM_MODIFY` and `NIM_ADD` had been fixed in latest revision! We should also check and fix if required for the CD Eject project!

** Tray Notification Ref**  
Including Balloon Notifications,  
- [Win7 Sample - NotificationIcon](https://github.com/microsoft/Windows-classic-samples/blob/main/Samples/Win7Samples/winui/shell/appshellintegration/NotificationIcon), and, [MSFT Docs for the sample](https://learn.microsoft.com/en-us/windows/win32/shell/samples-notificationicon)
- [MSFT - Display the Notification](https://learn.microsoft.com/en-us/windows/win32/shell/notification-area#display-the-notification)

**Refs**  
Used to be hosted in google code (svn) in the beginning,  
- [sourceforge/pingguin](https://sourceforge.net/projects/pingguin)

**Project Goals**  
From earlier doc,  
Here's some screenshot of the project.  
  
*broken image links,*  
> [Image Ping GUI01](http://saos.azurewebsites.net/out_of_app_images/Ping GUI01.png)
  
> [Image Ping GUI02](http://saos.azurewebsites.net/out_of_app_images/Ping GUI02.png)
  
> [Image Ping GUI03](http://saos.azurewebsites.net/out_of_app_images/Ping GUI03.png)


Please open github issue if you have any suggestion/feedback.

### Command Line Options
Example CLA,

    gping /ip 192.168.16.1 /pd 174.136.48.107 /sd 4.2.2.2

N.B, `/t` switch enables notification.
Still not implemented if other strings are not provided those ip addresses will be set to "0.0.0.0".

#### Showing the Balloon Tip
`Shell_NotifyIcon` for `NIM_MODIFY` and `NIM_ADD` had been fixed in latest revision!

**Loading the Icon**  
In `ShowBalloonTip`, earlier we used to load the icon. However, this seems not to be necessary since we already added the icon during `NIM_ADD`.

`LoadImage(*)` loads the item. Other ways to load,

Method 2:  

```cpp
HICON hIcon = AfxGetApp()->LoadIcon(dwIcon);
```

Method 3:  
```cpp
LoadIconMetric(hInst, MAKEINTRESOURCE(dwIcon), LIM_LARGE, &hIcon);
```

#### DNS Lookup
When DNS Lookup is possible, a notification is displayed using dialog box. If it failed it is not displayed. Thread exits after DNS response is received.

#### Installer
*[Installer for Ping GUI](NSIS/)* is created using NSIS install script.

Has following features,
- Modern user interface
- Option to users for changing default installation directory.
- Option to users for choose whether to install start menu items.

Following updates to the installer are considered,
- Use a different uninstaller icon
- Change images of NSIS from MODERN UI
- Add a readme or help option


**Technical Info**  
- Updated NSIS installer binaries properties, ref, [sourceforge - portableapps](http://sourceforge.net/p/portableapps/launcher/ci/2.2.dev/tree/Other/Source/GeneratorWizard.nsi#l32)


#### Feature Requests
DNS Lookup is implemented in a multi-threaded approach. It checks whether internet is available or not.

We also considered that UI should be re-implemented using Win32 SDK/API. We don't need MFC since it's straight-forward!

In future, platforms to cover,
2. MAUI App for Windows to run cross platform
3. App for Linux
4. One app for MAC

In summary, **implement feature to notify on net unavailability** (from feedback below). In addition, we utilize a thread to perform requests instead of pending UI.

By Luckwin (copied from http://sa-os.blogspot.com/2011/05/Ping GUI-net-notifier-software_20.html#comment-form), 05-2012

> ... I switch on my laptop. Then, I connect to internet using passwords which then allows me to use  
> internet, internet is usually available > 24 X 7 but 2 to 5 times a day routers are automatically  
> reset.  
>  
> I have list of software which are downloading. When the routers are reset, I re-enter the  
> password and the downloading continues, but I'm not always watching if the modem has been reset,  
> so what i need is an internet unavailable Notifier. like something which sounds an alarm bell if  
> internet connection is lost!



**Tech Notes**  
How to work with OLE data types i.e Variants.  
Initially retrieve the info in variant. For example,  

    hr = pclsObj->Get(L"IPEnabled", 0, &vtProp, 0, 0);

Then check what type of data Variant contains. For example, I'm performing some actins when the variant contains a string array,  

    if (vtProp.vt == (VT_ARRAY | VT_BSTR)) {
      // do something
    }

Without this check, many types of errors occur!

Get upper and lower bound. Then calculate the difference. Let's call it `cElements`. We will use it before accessing the array. For example,

    cElements = lUBound - lLBound + 1;
    if (cElements > 0)
      m_GWIP = pbstr[0];

ref, *Help.docx 05-15-2011* (imported from git repo)

**Spec**  
Two cases that the thread performs actions,  
When internet is available
  - Enable ping single host
  - Give the message on noticebox

When not available  
- Enable ping SIP
- Give the message on notice box

In addition,  
- And toggle cases
- Enables/disables single host. But doesn't touch notice box!


#### To Do
**Automatic Network Information Retrieval**  
Automatically retrieve net settings using API.  
By default, automatically retrieve internet settings (the IP Address control initially will be set).

There are will be following options in the dialog box
- check-box: ping a single host or not
- Notify when target comes online  

If user click 'select single host' check box the text default gateway changes to "Target host IP"

Made a post on MFC newsgroup to choose a better option for automatic net info retrieval. I'm facing trouble to retrieve and parse the string array got from WMI. ref, [codeproject - IP Address WMI](http://www.codeproject.com/KB/dialog/IP_Address_WMI.aspx)

Default Gateway and primary dns server has been set and updated in the code. Secondary DNS will be fixed when I will be able to access elements from variant.

**Drafts regarding TODO tasks**  

Ping GUI New Tasks
- Ping GUI UI should be easier to understand
- Ping ISP probably should be replaced by ping default gateway
- Notification should be really implemented
- Fix Icon for initial dialog box
- Deprecated functions to be replaced

Program behavior modification included as follows,  
1. Make request to gateway
2. Then to primary dns server
3. Then to secondary dns server
4. Then make dns lookup is to be done and then,
  - Notification in system tray when internet is available
  - Add System tray icon

Revised to do tasks,  
1. check for internet at startup of the application using DNS Look up and if available enable single host
2. Implement Balloon tips, icon in system tray
3. Replace ping responses with progress bar. When internet not available first wait for default gateway<br>
then primary dns server, then secondary dns server, then DNS Lookup
4. Create a standard about Box

Drafts of the tasks as those are checked out,
- Task 1 done.

**New plan**  
First implement all options when "notify check box" is not checked. It includes.
1. Progress bar during ICMP request
2. After requests done it will mention how many of the requests have been replied with a dialog box. If no reply is received say that it's unreachable.

Subtask 1 done..  
Task 2: check if IsSingleHost is true,  
 if true then only ping to one... Otherwise, ping to all 3 (target host, gateway, and probably public IP such as google)


New task: **A report group box that updates the report..**  

Following tasks are left:
- Notification in system tray when internet is available or target host is alive
- Add System tray icon A report will be shown in the same dialog, a dns client thread will run will continuously update the dialog box whenever reply is received.
- Will notify whenever internet is available.
  - Run stage will be in cycle whenever notify is on.
  - and app will remain in system tray if minimized (and notification is set on)


Report box reports in following way,  

- Default gateway replied x% requests.
- Primary DNS Server replied y% requests.
- Secondary DNS Server replied z% requests.


When single host is selected only one static box will report the replies. Finally the static box on the bottom will request user to close the window when all requests are done.

WIP tasks,  
- Minimize in taskbar notification area
  - When minimized in taskbar notification area, icon will be added in the area.
  - When right clicked on the icon a menu will be displayed which will have following items:
    1. Restore App
    2. About Ping GUI: An about dialog box have to be implemented
    3. Exit  

  - When left clicked application will be restored
  - When notify is selected application will pop up and flash on the taskbar which can be implemented using previous code-base.
  
Example code for that,

```cpp
SetForegroundWindow();
SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
```

- A thread will be run concurrently to perform DNS lookup in case notify on internet availability is selected.
Use a proper threading mechanism and verify if previous thread implementation has to be replaced
The thread will notify the dialog box that internet is available by updating the static control on the bottom and will suggest user to close the window.

I have added the balloon tip notification on tray. Now I have to check following things:
- Adding taskbar icon in the taskbar
- Remove when window is shown

This is how we implemented it. When notify online check box is selected the next dialog box on its initialization creates the thread that continuously make DNS requests. Here is skeleton code (modifed and adapted in `NetInfoDialog::DNSThreadProc`),

```cpp
UINT WorkerThreadDNSLookUpProc( LPVOID pParam )
{
  MainDlg* pObject = (MainDlg *) pParam;

  // if pObject is not valid
  if (pObject == NULL || !pObject->IsKindOf(RUNTIME_CLASS(MainDlg)))
    return TRUE;

  // do something
  // side not making it friend enables private access
  return FALSE;
}

BOOL MainDlg::OnInitDialog()
{
  CDialogEx::OnInitDialog();
  AfxBeginThread(WorkerThreadDNSLookUpProc, this);
}
```

Following example code from earlier version (06-24-2010), inside `MainFrame::TimerProc` is for reference,

```cpp
MainFrame *pMainWnd = (MainFrame *)AfxGetMainWnd();
TCHAR *pstr = pMainWnd->TextStr;
pstr[0] = '\0';

HANDLE hIcmpFile;
unsigned long ipaddr = INADDR_NONE;
DWORD dwRetVal = 0;

TCHAR SendData[] = _T("Data Buffer");
LPVOID ReplyBuffer = NULL;
DWORD ReplySize = 0;
pMainWnd->CountRequest++;

ipaddr = inet_addr(ipaddrstrA);
if (ipaddr == INADDR_NONE)
{
  _stprintf_s(pstr, MSGSIZE, _T("\n\tUsage: pinggui /t [optional] /ip IPAddress\n"));
  PingQuit(pMainWnd, pstr);
  return;
}

hIcmpFile = IcmpCreateFile();
if (hIcmpFile == INVALID_HANDLE_VALUE)
{
  _stprintf_s(pstr, MSGSIZE, _T("\tUnable to open handle.\n"));
  _stprintf_s(&pstr[_tcslen(pstr)], MSGSIZE, _T("IcmpCreatefile returned error: %ld\n"), GetLastError());
  PingQuit(pMainWnd, pstr);
  return;
}

ReplySize = sizeof(ICMP_ECHO_REPLY) + sizeof(SendData);
ReplyBuffer = (VOID *)malloc(ReplySize);
if (ReplyBuffer == NULL)
{
  _stprintf_s(pstr, MSGSIZE, _T("\tUnable to allocate memory\n"));
  pMainWnd->MessageBox(pstr);
  PingQuit(pMainWnd, pstr);
  return;
}

_stprintf_s(&pstr[_tcslen(pstr)], MSGSIZE, _T("\n\tRequest [%d] "), pMainWnd->CountRequest);

dwRetVal = IcmpSendEcho(hIcmpFile, ipaddr, SendData, sizeof(SendData),
              NULL, ReplyBuffer, ReplySize, 1000);
if (dwRetVal != 0)
{
  PICMP_ECHO_REPLY pEchoReply = (PICMP_ECHO_REPLY)ReplyBuffer;
  struct in_addr ReplyAddr;
  ReplyAddr.S_un.S_addr = pEchoReply->Address;
  _stprintf_s(&pstr[_tcslen(pstr)], MSGSIZE, _T(" sent to %s\n"), ipaddrstr);

  if (dwRetVal > 1)
  {
      _stprintf_s(&pstr[_tcslen(pstr)], MSGSIZE, _T("\tReceived %ld icmp message responses\n\n"), dwRetVal);
      _stprintf_s(&pstr[_tcslen(pstr)], MSGSIZE, _T("\tInformation from the first response:\n"));
  }
  else
  {
      _stprintf_s(&pstr[_tcslen(pstr)], MSGSIZE, _T("\tReceived %ld icmp message response\n\n"), dwRetVal);
      _stprintf_s(&pstr[_tcslen(pstr)], MSGSIZE, _T("\tInformation from this response:\n"));
  }

  _stprintf_s(&pstr[_tcslen(pstr)], MSGSIZE, _T("\t  Received from %s\n"), CString(inet_ntoa(ReplyAddr)));

  if (pEchoReply->Status == 11003)
      _stprintf_s(&pstr[_tcslen(pstr)], MSGSIZE, _T("\t  Status = Request timed out.\n"));
  else
      _stprintf_s(&pstr[_tcslen(pstr)], MSGSIZE, _T("\t  Status = %ld\n"),
          pEchoReply->Status);

  _stprintf_s(&pstr[_tcslen(pstr)], MSGSIZE, _T("\t  Roundtrip time = %ld milliseconds\n"),
          pEchoReply->RoundTripTime);

  if (IsToggleMode == TRUE && pEchoReply->Status != 11003)
  {
      _stprintf_s(pstr, MSGSIZE, _T("\n\tServer is up.\n\n\tClick close button to quit the program."));
      PingQuit(pMainWnd, pstr);
  }

  pMainWnd->CountResponse = 0;
}
else
{
  int errorno = GetLastError();
  _stprintf_s(&pstr[_tcslen(pstr)], MSGSIZE, _T("lost in the network\n"));
  switch (errorno)
  {
  case 11010:
      _stprintf_s(&pstr[_tcslen(pstr)], MSGSIZE, _T("\tTimed out due to possible unreachability\n"), errno);
      pMainWnd->CountResponse++;
      break;
  default:
      _stprintf_s(&pstr[_tcslen(pstr)], MSGSIZE, _T("\tIcmpSendEcho returned error: %ld\n"), errorno);
  }

  if (IsToggleMode == FALSE)
  {
      if (pMainWnd->CountResponse >= 48)
      {
        _stprintf_s(pstr, MSGSIZE, _T("\tTarget client is possibly down.\n\n\tClick close button to quit the program."));
        PingQuit(pMainWnd, pstr);
        return;
      }
      else
      {
        _stprintf_s(&pstr[_tcslen(pstr)], MSGSIZE, _T("\n\n\tAnalyzing target host's unavailability.\n"));
        _stprintf_s(&pstr[_tcslen(pstr)], MSGSIZE, _T("\tAbsence of reply count %d.\n"), pMainWnd->CountResponse);

        pMainWnd->PostMessage(WM_PAINT, (LPARAM) 0, (LPARAM) 0);
        return;
      }
  }
  else
      _stprintf_s(&pstr[_tcslen(pstr)], MSGSIZE, _T("\n\tServer is still dumb."));
}

pMainWnd->PostMessage(WM_PAINT, (LPARAM) 0, (LPARAM) 0);
```

**Previous Repo**  
Old code dir in previous repo that we merged from is in [gitlab](https://gitlab.com/atiq-cs/merged_pinggui)  
- last code rev, 07-09-2011
- working solution vc project files are retained in [gitlab repo - file listing](https://gitlab.com/atiq-cs/merged_pinggui/-/tree/dev/mfc-code) above.
- old source files are left as is without renaming and touching though

Old code dir is old version of the app that
- didn't have Tray Support
- some codes are moved around


tags: C++, network-programming