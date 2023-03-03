// Parsing utility functions
#pragma once

// TimeType structure
typedef struct TimeObjType {
  int hour, minute, second, milisec;
} TimeType;


// Wireshark parse functions
int GetLineType(LPCTSTR line, int length);
void GetTimeStamp(LPTSTR timestamp, LPCTSTR str);
BOOL IsUDPPacket(LPCTSTR str, const int length);
CString GetIPAddress(LPCTSTR str, const int length, const int mode);

// Number functions, convertion functions, alternative for atoi in Unicode
int GetEquivValue(TCHAR ch, int base);
int atoi_base(LPCTSTR str, int base);

// Time manipulation functions
void LoadTime(LPTSTR str, TimeType* T1);
void CopyTime(TimeType* T1, TimeType* T2);
void SubtractTime (TimeType* TimeObj, const TimeType* diff);

BOOL doesFileExist(CString FPath);
LPCTSTR GetDataSegment(LPCTSTR str, int length);
//CString DecryptSignalling(LPCTSTR DS, BOOL m_IsOldDialer, int SignalHeaderLength);
CString DecryptSignaling(LPCTSTR DS, int SignalHeaderLength, int stunNoOfKeys, int m_stunkey[]);
