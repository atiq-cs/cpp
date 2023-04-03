### Database Demos
Demos,  
- SQLite
- SQL CE


When possible look at in-memory database Redis instead. ref, [stackshare - Redis vs SQLite](https://stackshare.io/stackups/redis-vs-sqlite#:~:text=Redis%20can%20be%20classified%20as,reasons%20why%20SQLite%20is%20favored.)

However, the database loading part is commented out in MainDlg for now.


### SQL CE
**SQL Server Compact Edition 4.0 with C++**  

SQL CE is dead for future developments by Microsoft. However, it is supported.

Although these shipped with the Pocket PC 2003 SDK, Microsoft later removed the ATL Consumer Templates and that left the impression that you should not use them on a mobile or embedded device.
Ref, [MSDN Social](https://social.msdn.microsoft.com/Forums/sqlserver/en-US/01a2d663-961f-4c9a-8d32-d5f3a859565d/how-to-access-sql-server-ce-from-unmanaged-c?forum=sqlce)

Deployment ref, [MSDN Social](https://social.msdn.microsoft.com/Forums/sqlserver/en-US/35db5fb8-443c-4b87-bda7-68fc7df6c6e6/private-deployment-of-sqlce-for-c-app?forum=sqlce)

My post:
[MSDN Social](https://social.msdn.microsoft.com/Forums/sqlserver/en-US/6deb9ec6-3604-443c-ad67-2ba244c00414/sql-server-compact-edition-35-c-sample?forum=sqlce)

This SQL CE 4.0 solution is not much used on the PC/Desktop. It has been used on the mobile widely. Yet, that has been done mostly with .Net Framework.


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


**Northwind Ole DB Samples**  
Contains following,

- Northwind.sdf
- northwindoledb.Win32.zip
- northwindoledb.zip
- SQLCE_v3.5_NorthwindOleDb_Release1.0.zip


'northwindoledb.zip' archive contains following files,

- Backup
- Backup1
- Backup2
- Backup3
- Photos
- Common.h
- dbcommon.h
- Employees.cpp
- Employees.h
- newres.h
- northwindoledb.cpp
- northwindoledb.h
- northwindoledb.ico
- NorthwindOleDb.rc
- northwindoledb.sdf
- northwindoledb.sln
- northwindoledb.v11.suo
- northwindoledb.vcxproj
- northwindoledb.vcxproj.filters
- northwindoledbppc.rc
- resource.h
- sqlce_err.h
- sqlce_oledb.h
- sqlce_sync.h
- stdafx.cpp
- stdafx.h
- transact.h


**SQL CE Refs**
- [Windows-classic-samples - OLE DB](https://github.com/microsoft/Windows-classic-samples/tree/main/Samples/Win7Samples/dataaccess/oledb)
- [MSFT - ADO.NET code examples](https://learn.microsoft.com/en-us/dotnet/framework/data/adonet/ado-net-code-examples)
- [MSFT - Creating Databases with OLE DB](https://learn.microsoft.com/en-us/previous-versions/sql/compact/sql-server-compact-4.0/ms174146\(v=sql.110\))
- [MSFT - How to: Create a Database by Using OLE DB (Programmatically)](https://learn.microsoft.com/en-us/previous-versions/sql/compact/sql-server-compact-4.0/ms172066\(v=sql.110\))

Reading Materials,  
Books,  
- Sams - [Teach Yourself Database Programming with Visual C++ 6 in 21 Days](https://dl.acm.org/doi/abs/10.5555/552636), [semanticscholar download link](https://www.semanticscholar.org/paper/Sams-Teach-Yourself-Database-Programming-with-C%2B%2B-6-Robison/aa09125021046b45a81d5f47cec8336441c29c9c)


**SQLite**  
SQLite is Preinstalled on iOS and Android.

Primary ref, for learning to use SQ Lite on Console App then main apps.  
  [David Cravey - Using SQLite in a Native Visual C++ Application](http://dcravey.wordpress.com/2011/03/21/using-sqlite-in-a-visual-c-application)

Related materials,  
- [Books List, sqlite.org](https://www.sqlite.org/books.html)
- Michael Owens - [The Definitive Guide to SQLite](https://link.springer.com/book/10.1007/978-1-4302-0172-4)
- [Chris Newman - SQLite](https://www.goodreads.com/book/show/1984913.SQLite), ref, `sqlite-developers.chm`


**General DB Refs**
- [VC ODBC Database Sample](https://github.com/microsoft/VCSamples/tree/master/VC2012Samples/ODBC%20Database%20sample)
