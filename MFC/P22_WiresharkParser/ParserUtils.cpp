// Contains utility functions definitions
//  some functions are adapted from Sub Sync project

#include "stdafx.h"
#include "ParserUtils.h"

int GetLineType(LPCTSTR line, int length) {
  if (length > 45)
    return 2;

  if (!_tcsncmp(line, _T("+---------+"), 11))
    return 0;

  if (length == 25)
    return 1;

  return 0;
}

void GetTimeStamp(LPTSTR timestamp, LPCTSTR str) {
  int i;
  for (i=0; str[i] != ' '; i++);

  timestamp[0] = NULL;
  // 20 just to avoid the warning
  _tcsncat_s(timestamp, 20, str, i);
}

BOOL IsUDPPacket(LPCTSTR str, const int length) {
  if (length > 75 && !_tcsncmp(&str[75], _T("11"), 2))
    return TRUE;
  return FALSE;
}

int GetEquivValue(TCHAR ch, int base) {
  if (base == 16) {
    // make upper case if lowercase
    if (ch >= _T('a') && ch <= _T('z'))
      ch -= 32;

    if (ch >= _T('A') && ch <= _T('F'))
      return (ch-_T('7'));
  }

  if (ch >= _T('0') && ch <= _T('9'))
    return (ch - _T('0'));
  return 0;
}

// Modified atoi that supports convertion from base
int atoi_base(LPCTSTR str, int base) {
  int res = 0;
  int i, len, tmp;

  len = _tcslen(str);
  for (i=0; i<len; i++) {
    tmp = GetEquivValue(str[i], base);
    res = res*base + tmp;
  }
  return res;
}

CString GetIPAddress(LPCTSTR str, const int length, const int mode) {
  CString ip;
  TCHAR ipseg[3];
  unsigned long int ipsegval[4];
  int Pos = 0;

  int i;

  if (length < 120)
    return NULL;

  if (mode == 1)
    // Get source IP Address
    Pos = 84;
  else if (mode == 2)
    // Get Destination IP Address
    Pos = 96;

  for (i=0; i<4; i++) {
    _tcsncpy_s(ipseg, &str[Pos], 2);
    ipseg[2] = NULL;
    // AfxMessageBox(ipseg);
    Pos += 3;
    ipsegval[i] = atoi_base((LPTSTR)ipseg, 16);

    // CString temp;
    // temp.Format(_T("converted: %d"), ipsegval[i]);
    // AfxMessageBox(temp);

    //getchar();
  }

  ip.Format(_T("%u.%u.%u.%u"), ipsegval[0], ipsegval[1], ipsegval[2], ipsegval[3]);

  return ip;
}

// This function returns data segment from the whole packet
LPCTSTR GetDataSegment(LPCTSTR str, int length) {
  if (length > 132)
    return &str[132];
  return NULL;
}


// Time Functions
void LoadTime(LPTSTR str, TimeType* T1) {
  LPCTSTR delim=_T(":, ");
  LPTSTR token, next_token;

  // Get hour
  token = _tcstok_s(str, delim, &next_token);
  T1->hour = atoi_base(token, 10);

  // Get minute
  token = _tcstok_s(NULL, delim, &next_token);
  T1->minute = atoi_base(token, 10);

  // Get second
  token = _tcstok_s(NULL, delim, &next_token);
  T1->second = atoi_base(token, 10);

  // Get mili-second
  token = _tcstok_s(NULL, delim, &next_token);
  T1->milisec = atoi_base(token, 10);
}

void CopyTime(TimeType* T1, TimeType* T2) {
  T1->hour = T2->hour;
  T1->minute = T2->minute;
  T1->second = T2->second;
  T1->milisec = T2->milisec;
}

void SubtractTime(TimeType* TimeObj, const TimeType* diff) {
  int temp;

  // Check if time is less then offset
  if (TimeObj->hour < diff->hour)
    return ;
  if (TimeObj->hour == diff->hour) {
    if (TimeObj->minute < diff->minute)
      return ;
    else if (TimeObj->minute == diff->minute) {
      if (TimeObj->second < diff->second)
        return ;
      else if (TimeObj->second == diff->second) {
        if (TimeObj->milisec < diff->milisec)
          return ;
      }
    }
  }

  temp = TimeObj->milisec - diff->milisec;
  if (temp < 0) {
    temp += 1000;
    TimeObj->second--;
  }
  TimeObj->milisec = temp;

  temp = TimeObj->second - diff->second;
  if (temp < 0) {
    temp += 60;
    TimeObj->minute--;
  }

  TimeObj->second = temp;

  temp = TimeObj->minute - diff->minute;
  if (temp < 0) {
    temp += 60;
    TimeObj->hour--;
  }

  TimeObj->minute = temp;
  TimeObj->hour -= diff->hour;
}
// Time functions end

// Uses Win32 instead of MFC
// This function only returns true when path is a file
BOOL doesFileExist(CString FPath) {
  HANDLE hFind;
  WIN32_FIND_DATA FindFileData;
  hFind = FindFirstFile(FPath, &FindFileData);
  if (hFind == INVALID_HANDLE_VALUE)
    return false;

  // Check whether path is a directory
  if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
    return false;
   
  return true;
}

CString DecryptSignaling(LPCTSTR DS, int SignalHeaderLength, int stunKeyCount, int m_stunkey[]) {
  unsigned char decdata[1024];
  unsigned char encdata[1024];
  // unsigned char stunoldkeys[7] = {1, 4, 6, 14, 7, 9, 5};
  // unsigned char stunnewkeys[10] = {5, 6, 7, 8, 9, 1, 1, 2, 3, 4};
  unsigned char stunkeys[21];

  LPCTSTR delim=_T("|");
  LPTSTR token, next_token;
  int dataLength = 0;
  int offset = 2;
  int i, t;

  // CString temp;
  // temp.Format(_T("Received length: %d"), SignalHeaderLength);
  // AfxMessageBox(temp);

  // Set stunkeys
  // if (m_IsOldDialer) {
  //   stuntotalKey = 7;
  //   stunkeys = stunoldkeys;
  // }
  // else {
  //   stuntotalKey = 10;
  //   stunkeys = stunnewkeys;
  // }

  for (i=0; i<SignalHeaderLength; i++)
    stunkeys[i] = (unsigned char) m_stunkey[i];

  int f =1;
  // Tokenize
  token = _tcstok_s((LPTSTR) DS, delim, &next_token);
  do  {
    encdata[dataLength++] = atoi_base(token, 16);
    token = _tcstok_s(NULL, delim, &next_token);
  } while (token != NULL);

  // Decryption
  for (i = offset; i < dataLength; i++) {
    t = encdata[i] & 0x00FF;
    t -= stunkeys[(i-offset) % stunKeyCount];

    if(t >= 0)
      decdata[i-offset] = (char) t;
    else
      decdata[i-offset] = (char) (255 + t);
  }

  decdata[dataLength-offset] = NULL;

  return CString(&decdata[SignalHeaderLength]);
}
