// CChatRecordDB.h : header file
//

#pragma once
class CChatRecordDB
{
public:
  CChatRecordDB(BOOL& pSuccess);
  virtual ~CChatRecordDB();

  BOOL  Open(HINSTANCE hInstance);
  HRESULT LoadEmployeeInfo(DWORD dwEmployeeID);
  HRESULT SaveEmployeeInfo(DWORD dwEmployeeID);
  void  ShowEmployeePhoto();

private:
  HRESULT InitDatabase();
  HRESULT OpenDatabase();
  HRESULT CreateDatabase();
  // HRESULT GetNewDatabaseInterface();
  HRESULT ExecuteSQL(ICommandText *pICmdText, WCHAR * pwszQuery);
  HRESULT PopulateEmployeeNameList();
  HRESULT LoadEmployeePhoto(ILockBytes* pILockBytes);
  HRESULT InsertEmployeeInfo();
  void  ClearEmployeeInfo();
  HRESULT  SaveEmployeePhoto(ISequentialStream* pISequentialStream, DWORD dwPhotoID);
  BOOL  GetColumnOrdinal(DBCOLUMNINFO* pDBColumnInfo, DWORD dwNumCols, WCHAR* pwszColName, DWORD* pOrdinal);

private:
  IDBCreateSession *m_pIDBCreateSession;  // The IDBCreateSession interface
  // HWND       m_hWndEmployees;          // The employees dialog for the controls
  HINSTANCE     m_hInstance;
  HBITMAP       m_hBitmap;
};


// supplements common.h
const int COLUMN_ALIGNVAL           = 8;    // Column alignment value

inline DWORD ROUND_UP(DWORD dwSize, DWORD dwAmount) { return ((dwSize + (dwAmount-1)) & ~(dwAmount-1)); }
HRESULT DisplayCurrentThreadErrors();

#define IM_DB_PASS TEXT("sample_password")