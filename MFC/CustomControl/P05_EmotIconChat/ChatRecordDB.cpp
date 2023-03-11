//
//  PURPOSE : C++ Wrapper for SQLite
//  Date    : 12-2013
//
//     ref, An Introduction To The SQLite C/C++ Interface
//      https://www.sqlite.org/cintro.html

#include "stdafx.h"
#include "ChatRecordDB.h"
#include "sqlite3.h"
#include "ChatControl.h"
// #include "dbcommon.h"
// #include <sqlce_oledb.h>
// #include <sqlce_err.h  >


////////////////////////////////////////////////////////////////////////////////
// Function    : CChatRecordDB::Employees()
//
// Description  : Constructor
//
// Notes    : This function will set reference bSuccess according to result of CChatRecordDB
//          This function call precedes opening of call of open
//
////////////////////////////////////////////////////////////////////////////////
CChatRecordDB::CChatRecordDB() : /* m_hWndEmployees(NULL), */
                                       sqlite3DbHandle(NULL),
                     szErrorMsg(NULL)
{
}

////////////////////////////////////////////////////////////////////////////////
// Function: CChatRecordDB::~CChatRecordDB()
//
// Description: Destructor
//
// Returns: none
//
// Notes:  Destory the object and stores the chat history back
//
////////////////////////////////////////////////////////////////////////////////
CChatRecordDB::~CChatRecordDB()
{
  sqlite3_close(sqlite3DbHandle);
  sqlite3DbHandle = NULL;

  // if (szErrorMsg) {
  //   delete szErrorMsg;
  //   szErrorMsg = NULL;
  // }
}

////////////////////////////////////////////////////////////////////////////////
// Function    :  Opens Database, creates if does not exist
//
// Description  :  Initialilly database system is initialized using SQL CE 4.0
//
// Returns    :  False if an error occurs, True if successful
//
// Notes    :  Wil load the data if any kind of error is not occured
//
////////////////////////////////////////////////////////////////////////////////
BOOL CChatRecordDB::LoadDatabase(std::vector<CHATBOX_ITEM> &m_rvChatRecords)
{
  HANDLE        hFind;              // File handle
  WIN32_FIND_DATA    FindFileData;          // The file structure description  

  // If database exists, open it,
  // Otherwise, create a new database, insert sample data.
  //
  hFind = FindFirstFile(IM_DEMO_APP_DATABASE, &FindFileData);
  if (INVALID_HANDLE_VALUE == hFind)
    if (CreateDatabase() == FALSE)
      return FALSE;
  FindClose(hFind);
  if (OpenDatabase() == FALSE)
    return FALSE;
  if (GetDatabaseRows(m_rvChatRecords) == FALSE)
    return FALSE;

  /*if (INVALID_HANDLE_VALUE != hFind)
  {
    FindClose(hFind);
    if (OpenDatabase() == FALSE)
      return FALSE;
  }
  else
  {
    // Create IM Demo App database file as it does not exist
    if (CreateDatabase() == FALSE)
      return FALSE;
    // Insert sample data
    if (InsertRows() == FALSE)
      return FALSE;
    // now open the newly created database
    if (OpenDatabase() == FALSE)
      return FALSE;
  }*/

  return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
// Function: CreateDatabase
//
// Description:
//    Create Database File
//    Create user table
//
// Returns: TRUE if succesfull
// ref: 
////////////////////////////////////////////////////////////////////////////////
BOOL CChatRecordDB::CreateDatabase()
{
  BOOL func_result = FALSE;
  // Create Database because it does not exist
  int rc = sqlite3_open16(IM_DEMO_APP_DATABASE, &sqlite3DbHandle);    // ref: http://www.sqlite.org/c3ref/open.html
  if (rc)
  {
    //_tcscpy(szErrorMsg, (LPCTSTR) sqlite3_errmsg16(db));
    szErrorMsg = (LPCTSTR) sqlite3_errmsg16(sqlite3DbHandle);
    sqlite3_close(sqlite3DbHandle);
    szErrorMsg = NULL;
    return func_result;
  }

  // understood the concept of executing sql statement from this, ref,
  //  https://web.archive.org/web/20220120041803/https://www.dreamincode.net/forums/topic/122300-sqlite-in-c/
  // insert statement using prepare16_v2, we want to use Unicode across the project and in sqlite
  sqlite3_stmt *statement;
  // all prepare functions ref: http://home.mengelke.de/html-php-mysql/sqlite-3_7_3-docs/c3ref/prepare.html
  // datetime TEXT to support milli-seconds: http://www.sqlite.org/datatype3.html#datetime
  if(sqlite3_prepare16_v2(sqlite3DbHandle, L"CREATE TABLE UserTable (id INTEGER PRIMARY KEY, name TEXT, message TEXT, datetime TEXT, deliverystatus TINYINT);", -1, &statement, 0) == SQLITE_OK)
  {
    int result = 0;
    result = sqlite3_step(statement);
    if (result == SQLITE_DONE)    // result codes ref: http://www.sqlite.org/capi3ref.html#SQLITE_ABORT
      func_result = TRUE;
    sqlite3_finalize(statement);    // free the statement
  }

  /*// Create Table. sqlite data types ref: http://www.sqlite.org/datatype3.html
  LPCSTR sqlCreateTable = "CREATE TABLE UserTable (id INTEGER PRIMARY KEY, name TEXT, message TEXT, datetime NUMERIC, deliverystatus TINYINT);";
  char *error;
  rc = sqlite3_exec(db, sqlCreateTable, NULL, NULL, &error);    // ref: http://www.sqlite.org/c3ref/exec.html
  if (rc)
  {
    //_tcscpy(szErrorMsg, (LPCTSTR) sqlite3_errmsg16(db));
    szErrorMsg = (LPCTSTR) sqlite3_errmsg16(db);
    sqlite3_free(error);
  }*/

  return func_result;
}

////////////////////////////////////////////////////////////////////////////////
// Function: OpenDatabase
//
// Description:  Open a connection to database, reads it for loading into vector
//
// Returns: NOERROR if succesfull
//
////////////////////////////////////////////////////////////////////////////////
BOOL CChatRecordDB::OpenDatabase()
{
  BOOL func_result = TRUE;
  // Open Database if not already opened, same code used to create database in CreateDatabase function
  if (sqlite3DbHandle == NULL) {
    int rc = sqlite3_open16(IM_DEMO_APP_DATABASE, &sqlite3DbHandle);    // ref: http://www.sqlite.org/c3ref/open.html
    if (rc)
    {
      // _tcscpy(szErrorMsg, (LPCTSTR) sqlite3_errmsg16(db));
      szErrorMsg = (LPCTSTR) sqlite3_errmsg16(sqlite3DbHandle);
      sqlite3_close(sqlite3DbHandle);
      sqlite3DbHandle = NULL;
      return func_result;
    }
  }

  return func_result;
}

////////////////////////////////////////////////////////////////////////////////
// Function: Insert Chat History
//
// Description:  Inserts sample data
//
// Returns: NOERROR if succesfull
//
////////////////////////////////////////////////////////////////////////////////
BOOL CChatRecordDB::InsertRows()
{

  // Execute SQL
  /*
  LPSTR error;
  // date insertion
  //  http://stackoverflow.com/questions/1933720/how-do-i-insert-datetime-value-into-a-sqlite-database
  LPCSTR sqlInsertQuery = "INSERT INTO UserTable VALUES(1, 'Saint', 'testing row 01', '2013-12-26 17:18:08', 1); INSERT INTO UserTable VALUES(3, 'Atique', 'testing row 02', '2013-12-26 17:10:08', 1);";
  int rc = sqlite3_exec(sqlite3DbHandle, sqlInsertQuery, NULL, NULL, &error);
  if (rc)
  {
    szErrorMsg = (LPCTSTR) sqlite3_errmsg16(sqlite3DbHandle);
    sqlite3_free(error);
    return FALSE;
  }*/

  BOOL func_result = FALSE;

  // insert using sqlite3_prepare16_v2 function though I think sqlite3_prepare_v2 or sqlite3_prepare creates same bytecode
  sqlite3_stmt *statement;
  // all prepare functions ref: http://home.mengelke.de/html-php-mysql/sqlite-3_7_3-docs/c3ref/prepare.html
  if(sqlite3_prepare16_v2(sqlite3DbHandle, L"INSERT INTO UserTable VALUES(1, 'Saint', 'testing row 01', '2013-12-26 17:18:08', 1); INSERT INTO UserTable VALUES(3, 'Atique', 'testing row 02', '2013-12-26 17:10:08', 1);", -1, &statement, 0) == SQLITE_OK)
  {
    int result = 0;
    result = sqlite3_step(statement);
    if (result == SQLITE_DONE)
      func_result = TRUE;

    sqlite3_finalize(statement);
  }

  return func_result;
}

////////////////////////////////////////////////////////////////////////////////
// Function: Run a provided insert query on  the database
//
// Description:  Inserts data provided in the query
//
// Returns: NOERROR if succesfull
//
////////////////////////////////////////////////////////////////////////////////
BOOL CChatRecordDB::RunInsertQuery(CString m_csSQLiteQuery)
{
  /*// Execute SQL
  LPSTR error;
  LPCSTR sqlInsertQuery = "INSERT INTO UserTable VALUES(1, 'Saint', 'testing row 01', '2013-12-26 17:18:08', 1); INSERT INTO UserTable VALUES(3, 'Atique', 'testing row 02', '2013-12-26 17:10:08', 1);";
  int rc = sqlite3_exec(sqlite3DbHandle, sqlInsertQuery, NULL, NULL, &error);
  if (rc)
  {
    szErrorMsg = (LPCTSTR) sqlite3_errmsg16(sqlite3DbHandle);
    sqlite3_free(error);
    return FALSE;
  }*/

  BOOL func_result = FALSE;

  // insert using sqlite3_prepare16_v2 function though I think sqlite3_prepare_v2 or sqlite3_prepare creates same bytecode
  sqlite3_stmt *statement;
  if(sqlite3_prepare16_v2(sqlite3DbHandle, m_csSQLiteQuery, -1, &statement, 0) == SQLITE_OK)
  {
    /*while (TRUE) {
      int sql_result = sqlite3_step(statement);

      if ( sql_result == SQLITE_DONE ) {
        func_result = TRUE;
        break;
      }
    }*/

    int sql_result = 0;
    sql_result = sqlite3_step(statement);
    // SQLITE_CONSTRAINT  19
    if (sql_result == SQLITE_DONE)
      func_result = TRUE;

    sqlite3_finalize(statement);
  }

  return func_result;
}

////////////////////////////////////////////////////////////////////////////////
// Function: read the rows in the vector
//
// Description:  read data into vector
//
// Returns: NOERROR if succesfull
//
////////////////////////////////////////////////////////////////////////////////
BOOL CChatRecordDB::GetDatabaseRows(std::vector<CHATBOX_ITEM> &m_rvChatRecords) {
  BOOL func_result = TRUE;

  sqlite3_stmt *statement;
  // all prepare functions ref: http://home.mengelke.de/html-php-mysql/sqlite-3_7_3-docs/c3ref/prepare.html
  if(sqlite3_prepare16_v2(sqlite3DbHandle, L"SELECT * FROM UserTable;", -1, &statement, 0) == SQLITE_OK)
  {
    int sql_result = 0;
    int ctotal = sqlite3_column_count(statement);

    if (ctotal < 5)
      func_result = FALSE;

    if (func_result)
    while (TRUE) {
      sql_result = sqlite3_step(statement);

      if ( sql_result == SQLITE_ROW ) 
      {
        CHATBOX_ITEM ciDBRow = {};
        int key = sqlite3_column_int(statement, 0);
        //LPWSTR name[100];
        ciDBRow.sUserName = CString((LPWSTR) sqlite3_column_text16(statement, 1));
        ciDBRow.sMessage = CString((LPWSTR) sqlite3_column_text16(statement, 2));
        // ciDBRow.timedate = 
        //WCHAR msg[100];
        //wcscpy_s(msg, (LPWSTR) sqlite3_column_text16(statement, 2));
      }
      else if ( sql_result == SQLITE_DONE )
        break;
      else {
        func_result = FALSE;
        break;
      }
    }
    sqlite3_finalize(statement);    // free the statement
  }

  return func_result;
}