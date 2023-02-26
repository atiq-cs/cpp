//
//  PURPOSE : ICMP Demo with GUI App
//  Date    : 12-2009
//  Remarks :
//  * Remember to run this project from path that doesn't contain spaces
//     Otherwise, arguments gets messed up. It's due to parsing of argument
//     string after `CommandLineToArgvW`
//
//    Interesting single file GUI program with a Timer Proc!
//    - would had been better to do it with a Dialog instead and, to update the
//     text label on it with ICMP responses
//    - unsafe functions are not replaced, ANSI API calls are not replaced
//    - header files are same as in MSFT sample icmpsendecho doc
//
//   - Get command line from a GUI program i.e., CommandLineToArgvW
//   - Use of edit box, OnCreate and OnPaint
//   Timer
//   - Implementation of timer using callback procedure
//
//   Refs,
//   - look at ReadMe
//   - prev name, ping.cpp
//


// Target: Win7
// #define WINVER  0x0601
#include <afxwin.h>
#include <winsock2.h>
#include <iphlpapi.h>
#include <icmpapi.h>

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

#define ID_TIMER 101


// Example of using manifest file
// - Earlier we used to include a manifest file as resource file that would enable Visual Style / theme
// Instead using this for now for simplicity
#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


class MainFrame : public CFrameWnd
{
public:
  MainFrame ();

protected:
  static void CALLBACK EXPORT TimerProc (HWND hWnd, UINT nMsg, UINT nTimerID, DWORD dwTime);
};

// Implementations
MainFrame::MainFrame()
{
  // Create the window's frame
  Create(NULL, _T("Ping Application"), WS_OVERLAPPEDWINDOW,
      CRect(120, 100, 700, 480), NULL);

  SetTimer(ID_TIMER, 2000, &MainFrame::TimerProc);
}


class CSAApp: public CWinApp
{
public:
  BOOL InitInstance();
};

// The Timer Proc
void CALLBACK EXPORT MainFrame::TimerProc (HWND hWnd, UINT nMsg, UINT nTimerID, DWORD dwTime) {
  // Declare and initialize variables
  MainFrame* pMainWnd = (MainFrame*) AfxGetMainWnd ();
  char pstr[500];
  int i = 0;
  static int counter = 0;

  HANDLE hIcmpFile;
  unsigned long ipaddr = INADDR_NONE;
  DWORD dwRetVal = 0;
  char SendData[] = "Data Buffer";
  LPVOID ReplyBuffer = NULL;
  DWORD ReplySize = 0;
  int argc;
  char targv[200];
  char *p = targv;
  char argv[2][50];
  argv[1][0] = '\0';


  if (counter++ == 20) {
    pMainWnd->KillTimer(ID_TIMER);

    if (MessageBoxA(hWnd, "ICMP Messages Completed!", "Close", MB_OK) == IDOK)
      pMainWnd->PostMessage(WM_QUIT, (LPARAM)0, (LPARAM)0);
  }
  else if (counter++ < 20) {
    // Validate the parameters
    if(CommandLineToArgvW(GetCommandLineW(), &argc)) {
      sprintf(targv, "%s", GetCommandLineA());

      // MessageBoxA(hWnd, targv, "Cmdargs", MB_OK);
      for (i=0; *p != ' ' && *p != '\0'; i++,p++) {
        argv[0][i] = *p;
      }

      argv[0][i] = '\0';
      // MessageBoxA(hWnd, argv[0], "Argument 0", MB_OK);

      while (*p == ' ')
        p++;

      if (*p) {
        for (i=0;*p != ' ' && *p != '\0';p++,i++)
          argv[1][i] = *p;

        argv[1][i] = '\0';
        // MessageBoxA(hWnd, argv[1], "Argument 1", MB_OK);
      }

      while (*p == ' ')
        p++;

      if (*p) {
        for (i=0;*p != '\0';p++,i++)
          argv[2][i] = *p;
        argv[2][i] = '\0';
      }

      // MessageBoxA(hWnd, argv[2], "Argument 2", MB_OK);
    }
    else
      pMainWnd->MessageBox(_T("Error"), _T("NOTICE"), MB_OK);

    // sprintf(pstr, "argc: %d, argv: %s", argc, argv[1]);
    // MessageBoxA(hWnd, pstr, "NOTICE", MB_OK);
    if (argc != 2) {
      pMainWnd->KillTimer(ID_TIMER);
      sprintf(pstr, "Usage: %s IP address\n", argv[0]);

      MessageBoxA(hWnd, pstr, "Notice", MB_OK);
      pMainWnd->PostMessage(WM_QUIT, (LPARAM)0, (LPARAM)0);
    }

    // MessageBoxA(hWnd, argv[1], "Pass", MB_OK);
    char *ip = "172.16.9.1";

    ipaddr = inet_addr(argv[1]);
    if (ipaddr == INADDR_NONE) {
      sprintf(pstr, "usage: %s IP address (%s) char: %d %d\n", argv[0], argv[1], argv[1][0], ip[0]);
      MessageBoxA(hWnd, pstr, "Notice Inaddr", MB_OK);
      pMainWnd->PostMessage(WM_QUIT, (LPARAM)0, (LPARAM)0);
    }

    hIcmpFile = IcmpCreateFile();
    if (hIcmpFile == INVALID_HANDLE_VALUE) {
      sprintf(pstr, "\tUnable to open handle.\n");
      sprintf(&pstr[strlen(pstr)], "IcmpCreatefile returned error: %ld\n", GetLastError() );

      MessageBoxA(hWnd, pstr, "Notice", MB_OK);
      pMainWnd->PostMessage(WM_QUIT, (LPARAM)0, (LPARAM)0);
    }

    ReplySize = sizeof(ICMP_ECHO_REPLY) + sizeof(SendData);
    ReplyBuffer = (VOID*) malloc(ReplySize);
    if (ReplyBuffer == NULL) {
      sprintf(pstr, "\tUnable to allocate memory\n");

      MessageBoxA(hWnd, pstr, "Notice", MB_OK);
      pMainWnd->PostMessage(WM_QUIT, (LPARAM)0, (LPARAM)0);
    }

    dwRetVal = IcmpSendEcho(hIcmpFile, ipaddr, SendData, sizeof(SendData), 
      NULL, ReplyBuffer, ReplySize, 1000);

    // inside timer call back, waiting here for network, fine for experiment
    if (dwRetVal != 0) {
      PICMP_ECHO_REPLY pEchoReply = (PICMP_ECHO_REPLY)ReplyBuffer;
      struct in_addr ReplyAddr;
      ReplyAddr.S_un.S_addr = pEchoReply->Address;
      sprintf(pstr, "\tSent icmp message to %s\n", argv[1]);

      if (dwRetVal > 1) {
        sprintf(&pstr[strlen(pstr)], "\tReceived %ld icmp message responses\n", dwRetVal);
        sprintf(&pstr[strlen(pstr)], "\tInformation from the first response:\n"); 
      }
      else {
        sprintf(&pstr[strlen(pstr)], "\tReceived %ld icmp message response\n", dwRetVal);
        sprintf(&pstr[strlen(pstr)], "\tInformation from the first response:\n");
      }

      sprintf(&pstr[strlen(pstr)], "\t  Received from %s\n", inet_ntoa( ReplyAddr ) );
      sprintf(&pstr[strlen(pstr)], "\t  Status = %ld\n", 
          pEchoReply->Status);
      sprintf(&pstr[strlen(pstr)], "\t  Roundtrip time = %ld milliseconds\n", 
          pEchoReply->RoundTripTime);
    }
    else {
      sprintf(pstr, "\tCall to IcmpSendEcho failed.\n");
      sprintf(&pstr[strlen(pstr)], "\tIcmpSendEcho returned error: %ld\n", GetLastError() );
    }

    MessageBoxA(hWnd, pstr, "Notice", MB_OK);
  }
}


BOOL CSAApp::InitInstance() {
  m_pMainWnd = new MainFrame ;
  m_pMainWnd->ShowWindow(SW_SHOW);
  m_pMainWnd->UpdateWindow();

  return TRUE;
}

CSAApp theApp;
