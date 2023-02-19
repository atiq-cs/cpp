// Any more required header files to put here
#include "MFConverter.h"


// main skeleton first


//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------

MainDialog::MainDialog() : 
    m_nID(IDD_DIALOG_MAIN),
    m_hDlg(0)
{
  // allocate buffer for m_InputFileName
  // m_InputFileName = new TCHAR[MAX_PATH];
  m_InputFileName[0] = 0;
}


//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------

MainDialog::~MainDialog()
{
  // for future use
}

//-----------------------------------------------------------------------------
// OnInitDialog
//
// Handler for WM_INITDIALOG message.
//-----------------------------------------------------------------------------

HRESULT MainDialog::OnInitDialog()
{
  HRESULT hr = S_OK;
  // Register drag and drop: http://msdn.microsoft.com/en-us/library/windows/desktop/bb776406(v=vs.85).aspx

  DragAcceptFiles(m_hDlg, TRUE);
  // Set Text for media info
  SetWindowText( GetDlgItem(IDC_EDIT_MEDIA_INFO), TEXT("Plese drag and drop a file to view information."));

  return hr;
}


//-----------------------------------------------------------------------------
// ShowDialog()
// Displays the dialog
//
// Application instance
//
// Returns TRUE if successful or FALSE otherwise
//-----------------------------------------------------------------------------
BOOL MainDialog::ShowDialog(HINSTANCE hinst)
{
  // Show the dialog. Pass a pointer to ourselves as the LPARAM
  INT_PTR ret = DialogBoxParam(
    hinst, 
    MAKEINTRESOURCE(m_nID), 
    NULL, 
    DialogProc, 
    (LPARAM) this
    );

  if (ret == 0 || ret == -1)
  {
    MessageBox( NULL, TEXT("Could not create dialog"), TEXT("Error"), MB_OK | MB_ICONERROR );
    return FALSE;
  }

  return (IDOK == ret);
}


//-----------------------------------------------------------------------------
// Name: DialogProc()
// Desc: DialogProc for the dialog. This is a static class method.
//
// lParam: Pointer to the CBaseDialog object. 
//
// The CBaseDialog class specifies lParam when it calls DialogBoxParam. We store the 
// pointer as user data in the window. 
//
// (Note: The DirectShow CBasePropertyPage class uses the same technique.)
//-----------------------------------------------------------------------------
INT_PTR CALLBACK MainDialog::DialogProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
  MainDialog *pDlg = 0;  // Pointer to the dialog class that manages the dialog 

  // LRESULT lresult = 0;

  if (msg == WM_INITDIALOG)
  {
    // Get the pointer to the dialog object and store it in 
    // the window's user data

    SetWindowLongPtr(hDlg, DWLP_USER, (LONG_PTR)lParam);

    pDlg = (MainDialog*)lParam;
    if (pDlg)
    {
        pDlg->m_hDlg = hDlg;
        HRESULT hr = pDlg->OnInitDialog();
        if (FAILED(hr))
        {
            pDlg->EndDialog(0);
        }
    }
    return FALSE;
  }

  // Get the dialog object from the window's user data
  pDlg = (MainDialog*)(DWORD_PTR) GetWindowLongPtr(hDlg, DWLP_USER);

  if (pDlg != NULL)
  {
    switch (msg)
    {
    case WM_COMMAND:
      switch (LOWORD(wParam))
      {
      case IDOK:
      case IDCANCEL:
        pDlg->EndDialog(LOWORD(wParam));
        return TRUE;
      case IDC_BUTTON_START_CONV:
        pDlg->ConvertVideo();
        return TRUE;
      default:
        // we will use onCommand when necessary
        // return pDlg->OnCommand((HWND)lParam, LOWORD(wParam), HIWORD(wParam));
        return TRUE;
      }
      
      break;

    // handle drag and drop ref: http://msdn.microsoft.com/en-us/library/windows/desktop/bb774303(v=vs.85).aspx
    case WM_DROPFILES:
      // technique to call non-static member functions
      pDlg->OnDropFiles((HDROP) wParam);
      return TRUE;

  // We do not have slider
  // We do not need OnNotify yet
    case WM_NOTIFY:
      // lresult = pDlg->OnNotify((NMHDR*)lParam);

      // // The LRESULT from WM_NOTIFY can be meaningful. Store the result in DWLP_MSGRESULT.
      // SetWindowLongPtr(hDlg, DWLP_MSGRESULT, (LONG_PTR)lresult);
      // return TRUE;

    default:
      // we do not need WM_TIMER, WM_PAINT (as we are not drawing), WM_THEMECHANGED, WM_APP_NOTIFY etc yet
      // return pDlg->OnReceiveMsg(msg, wParam, lParam);
      return FALSE;
    }
  }
  else
  {
      return FALSE;
  }
}


//-----------------------------------------------------------------------------
// OnCommand
//
// Handler for WM_COMMAND messages.
//-----------------------------------------------------------------------------

// INT_PTR MainDialog::OnCommand(HWND /*hControl*/, WORD idControl, WORD /*msg*/)
/*
{
  switch (idControl)
  {
  case ID_FILE_OPENFILE:
      OnFileOpen();
      break;

  case ID_FILE_OPENURL:
      OnOpenURL();
      break;

  case ID_FILE_EXIT:
      PostQuitMessage(0);
      break;

  case IDC_MUTE:
      OnMute();
      break;

  case IDC_PLAY:
      OnPlayOrPause();
      break;

  case IDC_REWIND:
      OnRewind();
      break;

  case IDC_FASTFORWARD:
      OnFastForward();
      break;

  case ID_OPTIONS_VIDEOEFFECT: 
      ToggleMenuItemCheck(idControl, GetMenu(m_hDlg)); 
      break;

  }
  return 1;
}
*/

void MainDialog::OnDropFiles(HDROP hDrop) {
  // Get number of files; ref: http://msdn.microsoft.com/en-us/library/windows/desktop/bb776408(v=vs.85).aspx
  int numFiles = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, NULL);

  if (numFiles == 1) {
    DragQueryFile(hDrop, 0, m_InputFileName, sizeof(m_InputFileName));
    // display file name on the dialog; on media info textbox
    const size_t tempStrSize = _tcslen(TEXT("File Name: ")) + sizeof(m_InputFileName);
    LPTSTR tmpStr = new TCHAR[tempStrSize];
    _tcscpy_s(tmpStr, tempStrSize, TEXT("File Name: "));
    _tcscat_s(tmpStr, tempStrSize, m_InputFileName);
    SetWindowText( GetDlgItem(IDC_EDIT_MEDIA_INFO), tmpStr);

  }
  else if (numFiles == 0)
    MessageBox(m_hDlg, TEXT("Number of files dropped should not be zero!!"), NULL, MB_OK | MB_ICONEXCLAMATION);
  else
    MessageBox(m_hDlg, TEXT("Currently, dropping multiple files is not supported!"), NULL, MB_OK | MB_ICONINFORMATION);
  
  // finish procedure, deallocate
  DragFinish(hDrop);    //ref: http://msdn.microsoft.com/en-us/library/windows/desktop/bb776407(v=vs.85).aspx
}

#include "Transcode.h"

void MainDialog::ConvertVideo()
{
  if (m_InputFileName[0] == 0) {
    return ;
  }

  BOOL fError;
  int video_height = GetDlgItemInt(m_hDlg, IDC_EDIT_HEIGHT, &fError, TRUE);
  
  // Debug test
  // TCHAR num[53] = TEXT("Video height: ");
  // _itot_s(video_height, &num[14], 39, 10);
  // MessageBox(m_hDlg, num, NULL, MB_OK | MB_ICONINFORMATION);

  int video_width = GetDlgItemInt(m_hDlg, IDC_EDIT_WIDTH, &fError, TRUE);

  if (fError == FALSE || video_width <= 0)
    return ;
  int video_frameRate = GetDlgItemInt(m_hDlg, IDC_EDIT_FR, &fError, TRUE);
  if (fError == FALSE || video_frameRate <= 0)
    return ;
  int video_bitRate = GetDlgItemInt(m_hDlg, IDC_EDIT_BITRATE, &fError, TRUE);
  if (fError == FALSE || video_bitRate <= 0)
    return ;

  // disable button until conversion is complete
  EnableWindow(GetDlgItem(IDC_BUTTON_START_CONV), FALSE);

  (void) HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

  LPTSTR sInputFile = m_InputFileName;  // Audio source file name
  LPCTSTR sOutputFile = TEXT("H:\\Test.mp4");  // Output file name
  
  HRESULT hr = S_OK;

  hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

  if (SUCCEEDED(hr))
  {
      hr = MFStartup(MF_VERSION);
  }

  if (SUCCEEDED(hr))
  {
    CTranscoder transcoder;

    // Create a media source for the input file.
    hr = transcoder.OpenFile(sInputFile);

    if (SUCCEEDED(hr))
    {
      SetWindowText( GetDlgItem(IDC_EDIT_MEDIA_INFO), TEXT("Opened file"));

      //Configure the profile and build a topology.
      hr = transcoder.ConfigureAudioOutput();
    }

    if (SUCCEEDED(hr))
    {
      hr = transcoder.ConfigureVideoOutput(video_width, video_height, video_frameRate, video_bitRate*1024);
    }
  
    if (SUCCEEDED(hr))
    {
      hr = transcoder.ConfigureContainer();
    }

    //Transcode and generate the output file.
    if (SUCCEEDED(hr))
    {
      hr = transcoder.EncodeToFile(sOutputFile);
    }

    if (SUCCEEDED(hr))
    {
      SetWindowText( GetDlgItem(IDC_EDIT_MEDIA_INFO), TEXT("Output file created"));
    }
  }

  MFShutdown();
  CoUninitialize();

  if (FAILED(hr))
  {
    // tostringstream stros;
    // stros << hr; 
    // tstring error_str = stros.c + ::tostr;
    // wprintf_s(L"Could not create the output file (0x%X).\n", hr);
    SetWindowText( GetDlgItem(IDC_EDIT_MEDIA_INFO), TEXT("Couldn't create output file."));
  }

  // enable button
  EnableWindow(GetDlgItem(IDC_BUTTON_START_CONV), TRUE);
}
