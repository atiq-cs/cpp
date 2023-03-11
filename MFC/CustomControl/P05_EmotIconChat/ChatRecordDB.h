
// CChatRecordDB.h  : header file for SQLite database implementation 

#pragma once

#include <vector>

// forward declaration
typedef struct sqlite3 sqlite3;
typedef struct _CHATBOX_ITEM CHATBOX_ITEM;

class CChatRecordDB
{
public:
  CChatRecordDB();
  virtual ~CChatRecordDB();
  BOOL LoadDatabase(std::vector<CHATBOX_ITEM> &m_rvChatRecords);
  BOOL RunInsertQuery(CString m_csSQLiteQuery);

private:
  BOOL InitDatabase();
  BOOL OpenDatabase();
  BOOL CreateDatabase();
  BOOL InsertRows();
  BOOL GetDatabaseRows(std::vector<CHATBOX_ITEM> &m_rvChatRecords);

private:
  LPCTSTR szErrorMsg;
  sqlite3 *sqlite3DbHandle;
};

// hardcoded db file name
const WCHAR IM_DEMO_APP_DATABASE[]      = L"IMDemoChat.db";
