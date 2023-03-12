### Database Demos
Demos,  
- SQLite
- SQL CE


When possible look at in-memory database Redis instead. ref, [stackshare - Redis vs SQLite](https://stackshare.io/stackups/redis-vs-sqlite#:~:text=Redis%20can%20be%20classified%20as,reasons%20why%20SQLite%20is%20favored.)

However, the database loading part is commented out in MainDlg for now.


**SQL CE**  
- `dbcommon.h` doesn't seem to be used. However, it provides demo examples.

**How to use this DB**  
[MainDlg.cpp](https://github.com/atiq-cs/cpp/blob/dev/MFC/CustomControl/P05_EmotIconChat/MainDlg.cpp) utilizes the SQLite database for now.

From previous files, here's example for SQL CE.  

Following is declared in `MainDlg.h`,

    CChatRecordDB* g_pChatRecords;

Database instantiated in a Dialog implementation file, ref, MainDlg.cpp, inside `CMainApp::InitInstance()`,

    // Create database here if does not exist. If exist open it and load records
    BOOL bSuccess;
    bSuccess = FALSE;
    g_pChatRecords = new CChatRecordDB(bSuccess);

    if (!bSuccess || NULL == g_pChatRecords || FALSE == g_pChatRecords->Open(m_hInstance))
    {
      delete g_pChatRecords;
      g_pChatRecords = NULL;
      return FALSE;
    }

Delete the instance after handling `dlg.DoModal()`'s response in same method,

    INT_PTR nResponse = dlg.DoModal();
    // handle response code ...

    if (g_pChatRecords) {
      delete g_pChatRecords;
      g_pChatRecords = NULL;
    }


**SQLite**  
SQLite is Preinstalled on iOS and Android.
Related materials,  
- [Books List, sqlite.org](https://www.sqlite.org/books.html)
- Michael Owens - [The Definitive Guide to SQLite](https://link.springer.com/book/10.1007/978-1-4302-0172-4)
- [Chris Newman - SQLite](https://www.goodreads.com/book/show/1984913.SQLite), ref, `sqlite-developers.chm`


**Refs**
- [Windows-classic-samples - OLE DB](https://github.com/microsoft/Windows-classic-samples/tree/main/Samples/Win7Samples/dataaccess/oledb)
- [MSFT - Creating Databases with OLE DB](https://learn.microsoft.com/en-us/previous-versions/sql/compact/sql-server-compact-4.0/ms174146\(v=sql.110\))
- [MSFT - How to: Create a Database by Using OLE DB (Programmatically)](https://learn.microsoft.com/en-us/previous-versions/sql/compact/sql-server-compact-4.0/ms172066\(v=sql.110\))