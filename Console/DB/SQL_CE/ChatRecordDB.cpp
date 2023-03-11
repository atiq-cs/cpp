//
//  PURPOSE : C++ Example for SQL CE Database
//  Date    : 12-2013
//
//     Adapted from Windows Sample
//

#include "stdafx.h"
#include "ChatRecordDB.h"
#include "dbcommon.h"
#include <sqlce_oledb.h>
#include <sqlce_err.h  >


////////////////////////////////////////////////////////////////////////////////
// Function    : CChatRecordDB::Employees()
//
// Description  : Constructor
//
// Notes    : This function will set reference bSuccess according to result of CChatRecordDB
//          This function call precedes opening of call of open
//
////////////////////////////////////////////////////////////////////////////////
CChatRecordDB::CChatRecordDB(BOOL& bSuccess) : /*m_hWndEmployees(NULL), */
                        m_hInstance(NULL),
                        m_pIDBCreateSession(NULL),
                        m_hBitmap(NULL)
{
  HRESULT hr = NOERROR;

  // Initialize environment
  //
  hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
  if(FAILED(hr))
  {
    bSuccess = FALSE;

    MessageBox(NULL, L"COM Initialization Failure.", L"Employees", MB_OK);
    return;
  }

  bSuccess = TRUE;
}

////////////////////////////////////////////////////////////////////////////////
// Function: CChatRecordDB::~Employees()
//
// Description: Destructor
//
// Returns: none
//
// Notes:
//
////////////////////////////////////////////////////////////////////////////////
CChatRecordDB::~CChatRecordDB()
{
  // Release interfaces
  //
  if(m_pIDBCreateSession)
  {
    HRESULT        hr = NOERROR;
    IDBInitialize *pIDBInitialize = NULL;

    hr = m_pIDBCreateSession->QueryInterface(IID_IDBInitialize, (void **) &pIDBInitialize);
    if(SUCCEEDED(hr))
    {
      pIDBInitialize->Uninitialize();
      pIDBInitialize->Release();
    }
        
    m_pIDBCreateSession->Release();
  }

  // if (m_hWndEmployees)
  // {
  //   DestroyWindow(m_hWndEmployees);
  // }

  // Uninitialize the environment
  CoUninitialize();
}

////////////////////////////////////////////////////////////////////////////////
// Function    :  Opens Database, creates if does not exist
//
// Description  :  Initialilly database system is initialized using SQL CE 4.0
//
// Returns    :  False if an error occurs
//
// Notes:
//
////////////////////////////////////////////////////////////////////////////////
BOOL CChatRecordDB::Open(HINSTANCE hInstance)
{
  HRESULT hr = NOERROR;
  /*RECT  rect;
  DWORD  dwCurSel;*/
  //DWORD  dwEmployeeID;
  
  m_hInstance = hInstance;

  // Create the dialog window
  //
  /*GetClientRect(hWndParent, &rect);
  m_hWndEmployees = CreateDialog(  hInstance, 
                  MAKEINTRESOURCE(IDD_DIALOG_EMPLOYEES), 
                  hWndParent, 
                  (DLGPROC)EmployeesDlgProc); */

  /*if (NULL == m_hWndEmployees)
  {
  MessageBox(NULL, L"Error - Create dialog", L"Northwind Oledb sample", MB_OK);
  return NULL;
  }*/

  // Open a connection to database and create a session object.
  //
  hr = InitDatabase();
  if (FAILED(hr))
  {
    MessageBox(NULL, L"Error - Initialize database", L"IM Demo App DB", MB_OK);
    return FALSE;
  }

  // Populate combobox with employee name list.
  //
  /*hr = PopulateEmployeeNameList();
  if (FAILED(hr))
  {  
    MessageBox(NULL, L"Error - Retrive employee name list", L"IM Demo App DB", MB_OK);
    return FALSE;
  }*/

  // Display the dialog window and center it under the commandbar
  /*
  if (m_hWndEmployees)
  {
    MoveWindow(m_hWndEmployees, rect.left, rect.top, rect.right-rect.left,rect.bottom-rect.top, TRUE);
    ShowWindow(m_hWndEmployees, SW_SHOW);
    UpdateWindow(m_hWndEmployees);
  }

  // Set current selection of employee name combobox to index 0,
  //
  dwCurSel = SendDlgItemMessage(m_hWndEmployees, IDC_COMBO_NAME, CB_SETCURSEL, 0, 0);
  if (CB_ERR != dwCurSel)
  {
    // Retrieve current selected employee id from employee name combobox,
    // and load other employee info.
    //
    dwEmployeeID = SendDlgItemMessage(m_hWndEmployees, IDC_COMBO_NAME, CB_GETITEMDATA, dwCurSel, 0);*/
    //dwEmployeeID = 0;
    //hr = LoadEmployeeInfo(dwEmployeeID);
    /*if (FAILED(hr))
    {
      MessageBox(NULL, L"Error - Update employee info", L"Northwind Oledb sample", MB_OK);
      return NULL;
    }
    ShowEmployeePhoto();
  }*/

  //return m_hWndEmployees;
  return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
// Function: InitDatabase()
//
// Description: Open a connection to database, 
//        then create a session object.
//
// Returns: NOERROR if succesfull
//
// Notes:
//
////////////////////////////////////////////////////////////////////////////////
HRESULT CChatRecordDB::InitDatabase()
{
    HRESULT           hr        = NOERROR;  // Error code reporting
  HANDLE        hFind;              // File handle
  WIN32_FIND_DATA    FindFileData;          // The file structure description  

  // If database exists, open it,
  // Otherwise, create a new database, insert sample data.
  //
  hFind = FindFirstFile(IM_DEMO_APP_DATABASE, &FindFileData);
  if (INVALID_HANDLE_VALUE != hFind)
  {
    FindClose(hFind);
    hr = OpenDatabase();
  }
  else
  {
    // Create IM Demo App database
    // Fails to set db with encryption
    hr = CreateDatabase();
    if(SUCCEEDED(hr))
    {
      hr = OpenDatabase();
    }
    if(SUCCEEDED(hr))
    {
      // Insert sample data
      // usually failing
      hr = InsertEmployeeInfo();
    }
  }

  return hr;
}

////////////////////////////////////////////////////////////////////////////////
// Function: CreateDatabase
//
// Description:
//    Create Northwind Database through OLE DB
//    Create Employees table
//
// Returns: NOERROR if succesfull
// ref 'Create a Database by Using OLE DB' in ReadMe
////////////////////////////////////////////////////////////////////////////////
HRESULT CChatRecordDB::CreateDatabase()
{
  HRESULT        hr           = NOERROR;  // Error code reporting
  DBPROPSET      dbpropset[2];          // Property Set used to initialize provider
  DBPROP        dbprop[1];            // property array used in property set to initialize provider
  DBPROP        sscedbprop[2];          // Property array for security and case-sensitivity properties

  // IDBInitialize      *pIDBInitialize      = NULL;    // Provider Interface Pointer
  // ref, Accessing Password-protected Databases with OLE DB
  //  https://learn.microsoft.com/en-us/previous-versions/sql/compact/sql-server-compact-4.0/ms173465(v=sql.110)
  // IDBProperties    *pIDBProperties     = NULL;
  IDBDataSourceAdmin  *pIDBDataSourceAdmin = NULL;  // Provider Interface Pointer
  IUnknown      *pIUnknownSession   = NULL;  // Provider Interface Pointer
  IDBCreateCommand  *pIDBCrtCmd       = NULL;  // Provider Interface Pointer
  ICommandText    *pICmdText       = NULL;  // Provider Interface Pointer

  // Delete the DB file if it already exists
  DeleteFile(IM_DEMO_APP_DATABASE);

  // Create an instance of the OLE DB Provider
  // changed from CLSID_SQLSERVERCE_3_5
  /*hr = CoCreateInstance(  CLSID_SQLSERVERCE, 
          0, 
          CLSCTX_INPROC_SERVER, 
          IID_IDBInitialize, 
          (void**) &pIDBInitialize);*/
  hr = CoCreateInstance(  CLSID_SQLSERVERCE, 
          0, 
          CLSCTX_INPROC_SERVER, 
          IID_IDBDataSourceAdmin, 
          (void**) &pIDBDataSourceAdmin);

  if(FAILED(hr))
  {
    goto Exit;
  }

  VariantInit(&dbprop[0].vValue);
  for (int i = 0; i < sizeof(sscedbprop) / sizeof(sscedbprop[0]); i++)
    VariantInit(&sscedbprop[i].vValue);


  // Initialize a property with name of database
  dbprop[0].dwPropertyID    = DBPROP_INIT_DATASOURCE;
  dbprop[0].dwOptions      = DBPROPOPTIONS_REQUIRED;
  dbprop[0].vValue.vt      = VT_BSTR;
  dbprop[0].vValue.bstrVal  = SysAllocString(IM_DEMO_APP_DATABASE);

  if(NULL == dbprop[0].vValue.bstrVal)
  {
    hr = E_OUTOFMEMORY;
    goto Exit;
  }

  // Specify the encryption mode. 
   sscedbprop[0].dwPropertyID = DBPROP_SSCE_ENCRYPTIONMODE;
   sscedbprop[0].dwOptions = DBPROPOPTIONS_REQUIRED;
   sscedbprop[0].vValue.vt = VT_I4;
   sscedbprop[0].vValue.intVal = DBPROPVAL_SSCE_EM_PLATFORM_DEFAULT;

   // Specify the strong password.
   sscedbprop[1].dwPropertyID = DBPROP_SSCE_DBPASSWORD;
   sscedbprop[1].dwOptions = DBPROPOPTIONS_REQUIRED;
   sscedbprop[1].vValue.vt = VT_BSTR;
   sscedbprop[1].vValue.bstrVal = SysAllocString(L"REVE@ppDB321");

   if(NULL == sscedbprop[1].vValue.bstrVal)
   {
     hr = E_OUTOFMEMORY;
     goto Exit;
   }

   // Set the case sensitivity to true.
   /* sscedbprop[2].dwPropertyID  = DBPROP_SSCE_DBCASESENSITIVE;
   sscedbprop[2].dwOptions   = DBPROPOPTIONS_REQUIRED;
   sscedbprop[2].vValue.vt   = VT_BOOL;
   sscedbprop[2].vValue.boolVal = VARIANT_TRUE;*/

  // Initialize the property set
  dbpropset[0].guidPropertySet = DBPROPSET_DBINIT;
  dbpropset[0].rgProperties   = dbprop;
  dbpropset[0].cProperties   = sizeof(dbprop)/sizeof(dbprop[0]);

  // for encryption and security
  dbpropset[1].guidPropertySet = DBPROPSET_SSCE_DBINIT ;
  dbpropset[1].rgProperties  = sscedbprop;
  dbpropset[1].cProperties  = sizeof(sscedbprop)/sizeof(sscedbprop[0]);

  // Get IDBDataSourceAdmin interface
  // hr = pIDBInitialize->QueryInterface(IID_IDBDataSourceAdmin, (void **) &pIDBDataSourceAdmin);
  // if(FAILED(hr))
  // {
  //   goto Exit;
  // }

  // Create and initialize data store
  //
  hr = pIDBDataSourceAdmin->CreateDataSource(sizeof(dbpropset)/sizeof(dbpropset[0]), dbpropset, NULL, IID_IUnknown, &pIUnknownSession);
  if(FAILED(hr))  
    {
    goto Exit;
    }

  /*
  // Set the properties into the provider's data source object.
  hr = pIDBInitialize->QueryInterface(IID_IDBProperties,(void**)&pIDBProperties);
  if(FAILED(hr))  
    {
    goto Exit;
    }

  DBPROP           sscedbprop_open[1];      // for opening database security properties are different
  VariantInit(&sscedbprop_open[0].vValue);

  // Second property set has one property containing the 
  // provider-specific database password in the pwdPassword variable 
  // that was obtained from a dialog box (not shown).
  sscedbprop_open[0].dwPropertyID = DBPROP_SSCE_DBPASSWORD;
  sscedbprop_open[0].dwOptions = DBPROPOPTIONS_REQUIRED;
  sscedbprop_open[0].vValue.vt = VT_BSTR;
  sscedbprop_open[0].vValue.bstrVal = SysAllocString(L"REVE@ppDB321");
  if(NULL == sscedbprop_open[0].vValue.bstrVal)
  {
    hr = E_OUTOFMEMORY;
    goto Exit;
  }

  // Initialize the provider-specific property set.
  dbpropset[1].guidPropertySet = DBPROPSET_SSCE_DBINIT;
  dbpropset[1].rgProperties = sscedbprop_open;
  dbpropset[1].cProperties = sizeof(sscedbprop_open)/sizeof(sscedbprop_open[0]);


  hr = pIDBProperties->SetProperties(sizeof(dbpropset)/sizeof(dbpropset[0]), dbpropset);
  if(FAILED(hr))
  {
    goto Exit;
  }
  // Initialize the data source.
  hr = pIDBInitialize->Initialize();
  if(FAILED(hr))
  {
     goto Exit;
  }

  // DisplayCurrentThreadErrors();
    // Get IDBCreateSession interface
    //
    hr = pIDBInitialize->QueryInterface(IID_IDBCreateSession, (void**)&m_pIDBCreateSession);
  if(FAILED(hr))
  {
    goto Exit;
  }*/

  // Get IDBCreateCommand interface
  //
  hr = pIUnknownSession->QueryInterface(IID_IDBCreateCommand, (void**)&pIDBCrtCmd);
  if(FAILED(hr))
  {
    goto Exit;
  }

  // Create a command object
  //
  hr = pIDBCrtCmd->CreateCommand(NULL, IID_ICommandText, (IUnknown**)&pICmdText);
  if(FAILED(hr))
  {
    goto Exit;
  }

  // Drop "Employees" table if it exists ignoring errors
  // we are creating new database, how come it will have a table created previously
  // ExecuteSQL(pICmdText, (LPWSTR)SQL_DROP_EMPLOYEES);

  // Create Employees table
  //
  hr = ExecuteSQL(pICmdText, (LPWSTR)SQL_CREATE_EMPLOYEES_TABLE);
  if(FAILED(hr))
  {
    goto Exit;
  }

  // Create Index
  // Note: The sample table has small amount of demo data, the index is created here.
  // In your application, to improve performance, index shoule be created after 
  // inserting initial data. 
  //
  hr = ExecuteSQL(pICmdText, (LPWSTR)SQL_CREATE_EMPLOYEES_INDEX);
  if(FAILED(hr))
  {
    goto Exit;
  }


Exit:
  // Clear Variant
  VariantClear(&dbprop[0].vValue);
  for (int i = 0; i < sizeof(sscedbprop) / sizeof(sscedbprop[0]); i++)
    VariantClear(&sscedbprop[i].vValue);

  // Release interfaces
  //
  if(pICmdText)
  {
    pICmdText->Release();
  }

  if(pIDBCrtCmd)
  {
    pIDBCrtCmd->Release();
  }

  if(pIUnknownSession)
  {
    pIUnknownSession->Release();
  }

  if(pIDBDataSourceAdmin)
  {
    pIDBDataSourceAdmin->Release();
  }

  // if(pIDBInitialize)
  // {
  //   pIDBInitialize->Release();
  // }

  return hr;
}

////////////////////////////////////////////////////////////////////////////////
// Function: OpenDatabase
//
// Description:  Open a connection to database
//
// Returns: NOERROR if succesfull
//
////////////////////////////////////////////////////////////////////////////////
HRESULT CChatRecordDB::OpenDatabase()
{
    HRESULT           hr        = NOERROR;  // Error code reporting
  DBPROP        dbprop[1];          // property used in property set to initialize provider
  DBPROPSET      dbpropset[2];        // Property Set used to initialize provider
  DBPROP        sscedbprop[1];      // for opening database security properties are different


    IDBInitialize       *pIDBInitialize = NULL;    // Provider Interface Pointer
  IDBProperties       *pIDBProperties  = NULL;    // Provider Interface Pointer

  VariantInit(&dbprop[0].vValue);    
  VariantInit(&sscedbprop[0].vValue);

    // Create an instance of the OLE DB Provider
  // Saint Atique: changed from CLSID_SQLSERVERCE_3_5
  hr = CoCreateInstance(  CLSID_SQLSERVERCE, 
        0, 
        CLSCTX_INPROC_SERVER, 
        IID_IDBInitialize, 
        (void**)&pIDBInitialize);
  if(FAILED(hr))
  {
    goto Exit;
  }

  // Initialize a property with name of database
  dbprop[0].dwPropertyID  = DBPROP_INIT_DATASOURCE;
  dbprop[0].dwOptions    = DBPROPOPTIONS_REQUIRED;
  dbprop[0].vValue.vt    = VT_BSTR;
  dbprop[0].vValue.bstrVal= SysAllocString(IM_DEMO_APP_DATABASE);

  if(NULL == dbprop[0].vValue.bstrVal)
  {
    hr = E_OUTOFMEMORY;
    goto Exit;
  }

  // Initialize the property set
  //
  dbpropset[0].guidPropertySet = DBPROPSET_DBINIT;
  dbpropset[0].rgProperties   = dbprop;
  dbpropset[0].cProperties   = sizeof(dbprop)/sizeof(dbprop[0]);

  // Second property set has one property containing the 
  // provider-specific database password in the pwdPassword variable 
  // that was obtained from a dialog box (not shown).
  sscedbprop[0].dwPropertyID = DBPROP_SSCE_DBPASSWORD;
  sscedbprop[0].dwOptions = DBPROPOPTIONS_REQUIRED;
  sscedbprop[0].vValue.vt = VT_BSTR;
  sscedbprop[0].vValue.bstrVal = SysAllocString(L"REVE@ppDB321");
  if(NULL == sscedbprop[0].vValue.bstrVal)
  {
    hr = E_OUTOFMEMORY;
    goto Exit;
  }

  // Initialize the provider-specific property set.
  dbpropset[1].guidPropertySet = DBPROPSET_SSCE_DBINIT;
  dbpropset[1].rgProperties = sscedbprop;
  dbpropset[1].cProperties = sizeof(sscedbprop)/sizeof(sscedbprop[0]);

  //Set initialization properties.
  //
  hr = pIDBInitialize->QueryInterface(IID_IDBProperties, (void **)&pIDBProperties);

  if(FAILED(hr))
  {
    goto Exit;
  }

  // Sets properties in the Data Source and initialization property groups
  //
  hr = pIDBProperties->SetProperties(2, dbpropset); 
  if(FAILED(hr))
  {
    goto Exit;
  }

  // Initializes a data source object 
  //
  hr = pIDBInitialize->Initialize();
  if(FAILED(hr))
  {
    goto Exit;
  }

  // Get IDBCreateSession interface
  hr = pIDBInitialize->QueryInterface(IID_IDBCreateSession, (void**)&m_pIDBCreateSession);

Exit:
  // Clear Variant
  VariantClear(&dbprop[0].vValue);
  VariantClear(&sscedbprop[0].vValue);
  
  // Release interfaces
  //
  if(pIDBProperties)
  {
    pIDBProperties->Release();
  }

  if (pIDBInitialize)
  {
      pIDBInitialize->Release();
  }

  return hr;
}

////////////////////////////////////////////////////////////////////////////////
// Function: ExecuteSQL
//
// Description:
//    Executes a non row returning SQL statement
//
// Parameters
//    pICmdText  - a pointer to the ICommandText interface on the Command Object
//    pwszQuery  - the SQL statement to execute
//
// Returns: NOERROR if succesfull
//
////////////////////////////////////////////////////////////////////////////////
HRESULT CChatRecordDB::ExecuteSQL(ICommandText *pICmdText, WCHAR * pwszQuery)
{
  HRESULT hr = NOERROR;

  hr = pICmdText->SetCommandText(DBGUID_SQL, pwszQuery); 
  if(FAILED(hr))
  {
    goto Exit;
  }

  hr = pICmdText->Execute(NULL, IID_NULL, NULL, NULL, NULL);

Exit:
  return hr;
}


////////////////////////////////////////////////////////////////////////////////
// Function: InsertEmployeeInfo
//
// Description:  Inserts sample data
//
// Returns: NOERROR if succesfull
//
////////////////////////////////////////////////////////////////////////////////
HRESULT CChatRecordDB::InsertEmployeeInfo()
{
  HRESULT        hr          = NOERROR;      // Error code reporting
  DBBINDING      *prgBinding      = NULL;        // Binding used to create accessor
  HROW        rghRows[1]          = {DB_NULL_HROW};   // Array of row handles obtained from the rowset object
  HROW        *prghRows      = rghRows;      // Row handle(s) pointer
  DBID        TableID;                // Used to open/create table
  DBID        IndexID;                // Used to create index
  DBPROPSET      rowsetpropset[1];            // Used when opening integrated index
  DBPROP        rowsetprop[1];              // Used when opening integrated index
  ULONG        cRowsObtained    = 0;        // Number of rows obtained from the rowset object
  DBOBJECT      dbObject;                // DBOBJECT data.
  DBCOLUMNINFO    *pDBColumnInfo    = NULL;        // Record column metadata
  BYTE        *pData        = NULL;        // record data
  WCHAR        *pStringsBuffer    = NULL;
  DWORD        dwBindingSize    = 0;
  DWORD        dwIndex        = 0;
  DWORD        dwRow        = 0;
  DWORD        dwCol        = 0;
  DWORD        dwOffset      = 0;
  ULONG        ulNumCols;

  IOpenRowset      *pIOpenRowset    = NULL;        // Provider Interface Pointer
  IRowset        *pIRowset      = NULL;        // Provider Interface Pointer
  ITransactionLocal  *pITxnLocal      = NULL;        // Provider Interface Pointer
  IRowsetChange    *pIRowsetChange    = NULL;        // Provider Interface Pointer
  IAccessor      *pIAccessor      = NULL;        // Provider Interface Pointer
  ISequentialStream  *pISequentialStream = NULL;        // Provider Interface Pointer
  IColumnsInfo    *pIColumnsInfo    = NULL;        // Provider Interface Pointer
  HACCESSOR      hAccessor      = DB_NULL_HACCESSOR;// Accessor handle

  VariantInit(&rowsetprop[0].vValue);

  // Validate IDBCreateSession interface
  if (NULL == m_pIDBCreateSession)
  {
    hr = E_POINTER;
    goto Exit;
  }

  // Create a session object 
  hr = m_pIDBCreateSession->CreateSession(NULL, IID_IOpenRowset, (IUnknown**)&pIOpenRowset);
  if(FAILED(hr))
  {
      goto Exit;
  }

  hr = pIOpenRowset->QueryInterface(IID_ITransactionLocal, (void**)&pITxnLocal);
  if(FAILED(hr))
  {
    goto Exit;
  }

  // Set up information necessary to open a table 
  // using an index and have the ability to seek.
  //
  TableID.eKind      = DBKIND_NAME;
  TableID.uName.pwszName  = (WCHAR*)TABLE_EMPLOYEE;

  IndexID.eKind      = DBKIND_NAME;
  IndexID.uName.pwszName  = L"PK_UserTable";

  // Request ability to use IRowsetChange interface
  // 
  rowsetpropset[0].cProperties  = 1;
  rowsetpropset[0].guidPropertySet= DBPROPSET_ROWSET;
  rowsetpropset[0].rgProperties  = rowsetprop;

  rowsetprop[0].dwPropertyID    = DBPROP_IRowsetChange;
  rowsetprop[0].dwOptions      = DBPROPOPTIONS_REQUIRED;
  rowsetprop[0].colid        = DB_NULLID;
  rowsetprop[0].vValue.vt      = VT_BOOL;
  rowsetprop[0].vValue.boolVal  = VARIANT_TRUE;

  // Open the table using the index
  //
  hr = pIOpenRowset->OpenRowset(  NULL,
          &TableID,
          &IndexID,
          IID_IRowset,
          sizeof(rowsetpropset)/sizeof(rowsetpropset[0]),
          rowsetpropset,
          (IUnknown**) &pIRowset);
  if(FAILED(hr))
  {
    goto Exit;
  }

    // Get IRowsetChange interface
  //
  hr = pIRowset->QueryInterface(IID_IRowsetChange, (void**)&pIRowsetChange);
  if(FAILED(hr))
  {
    goto Exit;
  }

    // Get IColumnsInfo interface
  //
    hr = pIRowset->QueryInterface(IID_IColumnsInfo, (void **)&pIColumnsInfo);
  if(FAILED(hr))
  {
    goto Exit;
  }

  // Get the column metadata 
  //
    hr = pIColumnsInfo->GetColumnInfo(&ulNumCols, &pDBColumnInfo, &pStringsBuffer);
  if(FAILED(hr) || 0 == ulNumCols)
  {
    goto Exit;
  }

    // Create a DBBINDING array.
    // The binding doesn't include the bookmark column (first column).
  //
  dwBindingSize = ulNumCols - 1;
  prgBinding = (DBBINDING*)CoTaskMemAlloc(sizeof(DBBINDING)*dwBindingSize);
  if (NULL == prgBinding)
  {
    hr = E_OUTOFMEMORY;
    goto Exit;
  }

  // Set initial offset for binding position
  //
  dwOffset = 0;

  // Prepare structures to create the accessor
  for (dwIndex = 0; dwIndex < dwBindingSize; ++dwIndex)
  {
    prgBinding[dwIndex].iOrdinal  = pDBColumnInfo[dwIndex + 1].iOrdinal;
    prgBinding[dwIndex].pTypeInfo  = NULL;
    prgBinding[dwIndex].pBindExt  = NULL;
    prgBinding[dwIndex].dwMemOwner  = DBMEMOWNER_CLIENTOWNED;
    prgBinding[dwIndex].dwFlags    = 0;
    prgBinding[dwIndex].bPrecision  = pDBColumnInfo[dwIndex + 1].bPrecision;
    prgBinding[dwIndex].bScale    = pDBColumnInfo[dwIndex + 1].bScale;
    prgBinding[dwIndex].dwPart    = DBPART_VALUE | DBPART_STATUS | DBPART_LENGTH;
    prgBinding[dwIndex].obLength  = dwOffset;                                     
    prgBinding[dwIndex].obStatus  = prgBinding[dwIndex].obLength + sizeof(ULONG);  
    prgBinding[dwIndex].obValue    = prgBinding[dwIndex].obStatus + sizeof(DBSTATUS);

    switch(pDBColumnInfo[dwIndex + 1].wType)
    {
    case DBTYPE_BYTES:
      // Set up the DBOBJECT structure.
      //
      dbObject.dwFlags = STGM_WRITE;
      dbObject.iid = IID_ISequentialStream;

      prgBinding[dwIndex].pObject    = &dbObject;
      prgBinding[dwIndex].cbMaxLen  = sizeof(IUnknown*);
      prgBinding[dwIndex].wType    = DBTYPE_IUNKNOWN;
      break;

    case DBTYPE_WSTR:
      prgBinding[dwIndex].pObject    = NULL;
      prgBinding[dwIndex].wType    = pDBColumnInfo[dwIndex + 1].wType;
      prgBinding[dwIndex].cbMaxLen  = sizeof(WCHAR)*(pDBColumnInfo[dwIndex + 1].ulColumnSize + 1);  // Extra buffer for null terminator 
      break;

    default:
      prgBinding[dwIndex].pObject    = NULL;
      prgBinding[dwIndex].wType    = pDBColumnInfo[dwIndex + 1].wType;
      prgBinding[dwIndex].cbMaxLen  = pDBColumnInfo[dwIndex + 1].ulColumnSize; 
      break;
    }

    // Calculate new offset
    // 
    dwOffset = prgBinding[dwIndex].obValue + prgBinding[dwIndex].cbMaxLen;

    // Properly align the offset
    //
    dwOffset = ROUND_UP(dwOffset, COLUMN_ALIGNVAL);
  }

  // Get IAccessor interface
  //
  hr = pIRowset->QueryInterface(IID_IAccessor, (void**)&pIAccessor);
  if(FAILED(hr))
  {
    goto Exit;
  }

  // Create accessor.
  hr = pIAccessor->CreateAccessor(DBACCESSOR_ROWDATA, 
          dwBindingSize, 
          prgBinding,
          0,
          &hAccessor,
          NULL);
  if(FAILED(hr))
  {
      goto Exit;
  }

  // Allocate data buffer for seek and retrieve operation.
  //
  pData = (BYTE*)CoTaskMemAlloc(dwOffset);
  if (NULL == pData)
  {
    hr = E_OUTOFMEMORY;
    goto Exit;
  }

  // Begins a new local transaction
  //
  hr = pITxnLocal->StartTransaction(ISOLATIONLEVEL_READCOMMITTED | ISOLATIONLEVEL_CURSORSTABILITY, 0, NULL, NULL);
  if(FAILED(hr))
  {
    goto Exit;
  }

  // Insert sample data
  //
  for (dwRow = 0; dwRow < sizeof(g_SampleEmployeeData)/sizeof(g_SampleEmployeeData[0]); ++dwRow)
  {
    DWORD  dwPhotoCol;
    DWORD   dwInfoSize;
    LPWSTR  lpwszInfo;

    // Set data buffer to zero
    memset(pData, 0, dwOffset);

    for (dwCol = 0; dwCol < dwBindingSize; ++dwCol)
    {
      // Get column value in string
      //
      lpwszInfo = g_SampleEmployeeData[dwRow].wszEmployeeInfo[dwCol];

      switch(prgBinding[dwCol].wType)
      {
        case DBTYPE_WSTR:
          // Copy value to binding buffer, truncate the string if it is too long
          //
          dwInfoSize = prgBinding[dwCol].cbMaxLen/sizeof(WCHAR) - 1;
          if (_tcslen(lpwszInfo) >= dwInfoSize)
          {
            _tcsncpy_s((WCHAR*)(pData+prgBinding[dwCol].obValue), dwOffset, lpwszInfo, dwInfoSize);
            *(WCHAR*)(pData+prgBinding[dwCol].obValue+dwInfoSize*sizeof(WCHAR)) = WCHAR('\0');
          }
          else
          {
            _tcscpy_s((WCHAR*)(pData+prgBinding[dwCol].obValue), dwOffset, lpwszInfo);
          }

          *(ULONG*)(pData+prgBinding[dwCol].obLength)    = _tcslen((WCHAR*)(pData+prgBinding[dwCol].obValue))*sizeof(WCHAR);
          *(DBSTATUS*)(pData+prgBinding[dwCol].obStatus)  = DBSTATUS_S_OK;
          break;

        case DBTYPE_IUNKNOWN:
          dwPhotoCol = dwCol;
          break;

        case DBTYPE_I4:
          *(int*) (pData+prgBinding[dwCol].obValue)    = _wtoi(g_SampleEmployeeData[dwRow].wszEmployeeInfo[dwCol]);
          *(ULONG*) (pData+prgBinding[dwCol].obLength)    = 4;
          *(DBSTATUS*) (pData+prgBinding[dwCol].obStatus)  = DBSTATUS_S_OK;
          break;

        default:
          break;
      }
    }

    // Insert data to database
    // set of errors occur here, have to fix this
    // because we used 
    hr = pIRowsetChange->InsertRow(DB_NULL_HCHAPTER, hAccessor, pData, prghRows);
    if (hr == DB_S_ERRORSOCCURRED) {
      // Display errors that occured on the current (main) thread.
          hr = DisplayCurrentThreadErrors();

      goto Abort;
    }
    else if (hr != S_OK) {
      MessageBox(NULL, L"Error - other error occured", L"IM Demo App DB: InsertEmployeeInfo", MB_OK);
      goto Abort;
    }

    /*if (FAILED(hr))
    {
      goto Abort;
    }*/

    // Get the row data
    //
    hr = pIRowset->GetData(rghRows[0], hAccessor, pData);
    if(FAILED(hr))
    {
      goto Abort;
    }

    // Check the status
    //
    if (DBSTATUS_S_OK != *(DBSTATUS*)(pData+prgBinding[dwPhotoCol].obStatus))
    {
      hr = E_FAIL;
      goto Abort;
    }                                                                                                                                                                                                                                                                                                                                                                                                       

    // Insert photo into database through ISequentialStream
    pISequentialStream = (*(ISequentialStream**) (pData + prgBinding[dwPhotoCol].obValue));
    if (pISequentialStream)
    {
      // Insert photo
      //
      hr = SaveEmployeePhoto(pISequentialStream, g_SampleEmployeeData[dwRow].dwEmployeePhoto);
      if(FAILED(hr))
      {
        goto Abort;
      }

      // Release ISequentialStream interface
      //
      hr = pISequentialStream->Release();
      if(FAILED(hr))
      {
        pISequentialStream = NULL;
        goto Abort;
      }

      pISequentialStream = NULL;
    }

        // Release the rowset
    //
    hr = pIRowset->ReleaseRows(1, prghRows, NULL, NULL, NULL);
    if(FAILED(hr))
    {
      goto Abort;
    }

    prghRows[0] = DB_NULL_HROW;
  }

  // Commit the transaction
  //
  if (pITxnLocal)
  {
    pITxnLocal->Commit(FALSE, XACTTC_SYNC, 0);
  }

  goto Exit;

Abort:
  if (DB_NULL_HROW != prghRows[0])
  {
      pIRowset->ReleaseRows(1, prghRows, NULL, NULL, NULL);
  }

  // Abort the transaction
  //
  if (pITxnLocal)
  {
    pITxnLocal->Abort(NULL, FALSE, FALSE);
  }

Exit:
  // Clear Variants
  VariantClear(&rowsetprop[0].vValue);

  // Free allocated DBBinding memory
  //
  if (prgBinding)
  {
    CoTaskMemFree(prgBinding);
    prgBinding = NULL;
  }

  // Free allocated column info memory
  //
  if (pDBColumnInfo)
  {
    CoTaskMemFree(pDBColumnInfo);
    pDBColumnInfo = NULL;
  }

  // Free allocated column string values buffer
  //
  if (pStringsBuffer)
  {
      CoTaskMemFree(pStringsBuffer);
      pStringsBuffer = NULL;
  }

  // Free data record buffer
  //
  if (pData)
  {
    CoTaskMemFree(pData);
    pData = NULL;
  }

  // Release interfaces
  //
  if(pISequentialStream)
  {
    pISequentialStream->Release();
  }

  if(pIAccessor)
  {
    pIAccessor->ReleaseAccessor(hAccessor, NULL); 
    pIAccessor->Release();
  }

  if (pIColumnsInfo)
  {
    pIColumnsInfo->Release();
  }

  if (pIRowsetChange)
  {
    pIRowsetChange->Release();
  }

  if (pITxnLocal)
  {
    pITxnLocal->Release();
  }

  if(pIRowset)
  {
    pIRowset->Release();
  }

  if(pIOpenRowset)
  {
    pIOpenRowset->Release();
  }

  return hr;
}  

////////////////////////////////////////////////////////////////////////////////
// Function: SaveEmployeePhoto()
//
// Description: Save employee photo to database.
//
// Returns: NOERROR if succesfull
//
// Notes:
//
////////////////////////////////////////////////////////////////////////////////
HRESULT CChatRecordDB::SaveEmployeePhoto(ISequentialStream* pISequentialStream, DWORD dwPhotoID)
{
  HRESULT hr = E_FAIL;
  HRSRC  hrSrc;
  HGLOBAL hPhoto = NULL;
  BYTE  *pPhotoData = NULL;
  DWORD  dwSize;
  DWORD  dwWritten;

  // Determine the location of the employee photo resource 
  //
  hrSrc = FindResource(m_hInstance, MAKEINTRESOURCE(dwPhotoID), TEXT("PHOTO")); 
  if (NULL == hrSrc)
  {
        goto Exit;
  }

  // Load the employee photo resource into memory
  //
  hPhoto = LoadResource(m_hInstance, hrSrc);
  if (NULL == hPhoto)
  {
        goto Exit;
  }

  // Lock the resource in memory
  // Get a pointer to the first byte of the resource
  //
  pPhotoData = (BYTE*)LockResource(hPhoto);
  if (NULL == pPhotoData)
  {
        goto Exit;
  }

  // Get the size, in bytes, of the resource
  //
  dwSize = SizeofResource(m_hInstance, hrSrc);
  if (0 == dwSize)
  {
    goto Exit;
  }

  // Write the photo data into the stream object 
  //
  hr = pISequentialStream->Write(pPhotoData, dwSize, &dwWritten);
  if(FAILED(hr) || (dwWritten != dwSize)) 
  {
    goto Exit;
  }

  hr = NOERROR;

Exit:
  // Release memory
  if (hPhoto)
  {
    DeleteObject(hPhoto);
  }

  return hr;
}

////////////////////////////////////////////////////////////////////////////////
// Function: PopulateEmployeeNameList()
//
// Description: Populate combobox with employee name list.
//
// Returns: NOERROR if succesfull
//
// Notes:
//
////////////////////////////////////////////////////////////////////////////////
HRESULT CChatRecordDB::PopulateEmployeeNameList()
{
  HRESULT          hr          = NOERROR;      // Error code reporting
  DBID            TableID;                // Used to open/create table
  DBID            IndexID;                // Used to open/create index
  DBPROPSET          rowsetpropset[1];            // Used when opening integrated index
  DBPROP            rowsetprop[1];              // Used when opening integrated index
  DBBINDING        *prgBinding      = NULL;        // Binding used to create accessor
  HROW            rghRows[1];                // Array of row handles obtained from the rowset object
  HROW*            prghRows      = rghRows;      // Row handle(s) pointer
     ULONG            cRowsObtained;              // Number of rows obtained from the rowset object
  BYTE          *pData        = NULL;        // Record data
  DBCOLUMNINFO      *pDBColumnInfo    = NULL;        // Record column metadata
  WCHAR          *pwszName      = NULL;        // Record employee name
  DWORD          dwIndex        = 0;
  DWORD          dwOffset      = 0;
  DWORD          dwBindingSize    = 0;
  DWORD          dwOrdinal      = 0;
  ULONG          ulNumCols      = 0;
  WCHAR          *pStringsBuffer    = NULL;

  IOpenRowset        *pIOpenRowset    = NULL;        // Provider Interface Pointer
  IRowset          *pIRowset      = NULL;        // Provider Interface Pointer
  IColumnsInfo      *pIColumnsInfo    = NULL;        // Provider Interface Pointer
  IAccessor*          pIAccessor      = NULL;        // Provider Interface Pointer
  HACCESSOR          hAccessor      = DB_NULL_HACCESSOR;// Accessor handle

  WCHAR*          pwszEmployees[]    =  {        // Info to retrieve employee names
                    L"EmployeeID",
                    L"LastName", 
                    L"FirstName"
                  };

  VariantInit(&rowsetprop[0].vValue);

  // Validate IDBCreateSession interface
  //
  if (NULL == m_pIDBCreateSession)
  {
    hr = E_POINTER;
    goto Exit;
  }

  // Create a session object 
  //
  hr = m_pIDBCreateSession->CreateSession(NULL, IID_IOpenRowset, (IUnknown**) &pIOpenRowset);
  if(FAILED(hr))
  {
      goto Exit;
  }

  // Set up information necessary to open a table 
  // using an index and have the ability to seek.
  //
  TableID.eKind      = DBKIND_NAME;
  TableID.uName.pwszName  = (WCHAR*)TABLE_EMPLOYEE;

  IndexID.eKind      = DBKIND_NAME;
  IndexID.uName.pwszName  = L"PK_UserTable";

  // Request ability to use IRowsetIndex interface
  rowsetpropset[0].cProperties  = 1;
  rowsetpropset[0].guidPropertySet= DBPROPSET_ROWSET;
  rowsetpropset[0].rgProperties  = rowsetprop;

  rowsetprop[0].dwPropertyID    = DBPROP_IRowsetIndex;
  rowsetprop[0].dwOptions      = DBPROPOPTIONS_REQUIRED;
  rowsetprop[0].colid        = DB_NULLID;
  rowsetprop[0].vValue.vt      = VT_BOOL;
  rowsetprop[0].vValue.boolVal  = VARIANT_TRUE;

  // Open the table using the index
  //
  hr = pIOpenRowset->OpenRowset(NULL, 
        &TableID, 
        &IndexID, 
        IID_IRowset, 
        sizeof(rowsetpropset)/sizeof(rowsetpropset[0]),
        rowsetpropset, 
        (IUnknown**)&pIRowset);
  if(FAILED(hr))
  {
    goto Exit;
  }

  // Get IColumnsInfo interface
  //
  hr = pIRowset->QueryInterface(IID_IColumnsInfo, (void **)&pIColumnsInfo);
  if(FAILED(hr))
  {
    goto Exit;
  }

  // Get the column metadata 
  //
  hr = pIColumnsInfo->GetColumnInfo(&ulNumCols, &pDBColumnInfo, &pStringsBuffer);
  if(FAILED(hr) || 0 == ulNumCols)
  {
    goto Exit;
  }

  // Create a DBBINDING array.
  //
  dwBindingSize = sizeof(pwszEmployees)/sizeof(pwszEmployees[0]);
  prgBinding = (DBBINDING*)CoTaskMemAlloc(sizeof(DBBINDING)*dwBindingSize);
  if (NULL == prgBinding)
  {
    hr = E_OUTOFMEMORY;
    goto Exit;
  }

  // Set initial offset for binding position
  //
  dwOffset = 0;

  // Prepare structures to create the accessor
  //
  for (dwIndex = 0; dwIndex < dwBindingSize; ++dwIndex)
  {
    if (!GetColumnOrdinal(pDBColumnInfo, ulNumCols, pwszEmployees[dwIndex], &dwOrdinal))
    {
      hr = E_FAIL;
      goto Exit;
    }

    prgBinding[dwIndex].iOrdinal  = dwOrdinal;
    prgBinding[dwIndex].dwPart    = DBPART_VALUE | DBPART_STATUS | DBPART_LENGTH;
    prgBinding[dwIndex].obLength  = dwOffset;                                     
    prgBinding[dwIndex].obStatus  = prgBinding[dwIndex].obLength + sizeof(ULONG);  
    prgBinding[dwIndex].obValue    = prgBinding[dwIndex].obStatus + sizeof(DBSTATUS);
    prgBinding[dwIndex].wType    = pDBColumnInfo[dwOrdinal].wType;
    prgBinding[dwIndex].pTypeInfo  = NULL;
    prgBinding[dwIndex].pObject    = NULL;
    prgBinding[dwIndex].pBindExt  = NULL;
    prgBinding[dwIndex].dwMemOwner  = DBMEMOWNER_CLIENTOWNED;
    prgBinding[dwIndex].dwFlags    = 0;
    prgBinding[dwIndex].bPrecision  = pDBColumnInfo[dwOrdinal].bPrecision;
    prgBinding[dwIndex].bScale    = pDBColumnInfo[dwOrdinal].bScale;

    switch(prgBinding[dwIndex].wType)
    {
    case DBTYPE_WSTR:    
      prgBinding[dwIndex].cbMaxLen = sizeof(WCHAR)*(pDBColumnInfo[dwOrdinal].ulColumnSize + 1);  // Extra buffer for null terminator 
      break;
    default:
      prgBinding[dwIndex].cbMaxLen = pDBColumnInfo[dwOrdinal].ulColumnSize; 
      break;
    }

    // Calculate the offset, and properly align it
    // 
    dwOffset = prgBinding[dwIndex].obValue + prgBinding[dwIndex].cbMaxLen;
    dwOffset = ROUND_UP(dwOffset, COLUMN_ALIGNVAL);
  }

  // Get IAccessor 
  //
  hr = pIRowset->QueryInterface(IID_IAccessor, (void**)&pIAccessor);
  if(FAILED(hr))
  {
    goto Exit;
  }

  // Create the accessor
  //
  hr = pIAccessor->CreateAccessor(DBACCESSOR_ROWDATA, 
          dwBindingSize, 
          prgBinding, 
          0, 
          &hAccessor, 
          NULL);
          if(FAILED(hr))
  {
    goto Exit;
  }

  // Allocate data buffer.
  //
  pData = (BYTE*)CoTaskMemAlloc(dwOffset);
  if (NULL == pData)
  {
    hr = E_OUTOFMEMORY;
    goto Exit;
  }

  // Allocate a memory big enough to held employee name
  // LastName + ', ' + FirstName
  //
  pwszName = (WCHAR*)CoTaskMemAlloc(prgBinding[1].cbMaxLen + prgBinding[2].cbMaxLen + 2);
  if (NULL == pwszName)
  {
    hr = E_OUTOFMEMORY;
    goto Exit;
  }

  // Retrive a row
  //
  hr = pIRowset->GetNextRows(DB_NULL_HCHAPTER, 0, 1, &cRowsObtained, &prghRows);
  while (SUCCEEDED(hr) && DB_S_ENDOFROWSET != hr)
  {
    // Set data buffer to zero
    //
    memset(pData, 0, dwOffset);

    // Fetch actual data
    hr = pIRowset->GetData(prghRows[0], hAccessor, pData);
    if (FAILED(hr))
    {
      // Release the rowset.
      //
      pIRowset->ReleaseRows(1, prghRows, NULL, NULL, NULL);
      goto Exit;
    }

    // If return a null value, ignore the contents of the value and length parts of the buffer.
    //
    if (DBSTATUS_S_ISNULL != *(DBSTATUS *)(pData+prgBinding[0].obStatus))
    {
      // If return a null value, ignore the contents of the value and length parts of the buffer.
      //
      if (DBSTATUS_S_ISNULL != *(DBSTATUS *)(pData+prgBinding[1].obStatus) && 
        DBSTATUS_S_ISNULL != *(DBSTATUS *)(pData+prgBinding[2].obStatus))
      {
        // Combine employee last name and first name
        //
        _tcscpy_s(pwszName, prgBinding[1].cbMaxLen + prgBinding[2].cbMaxLen + 2, (WCHAR*)(pData+prgBinding[1].obValue));
        _tcscpy_s(pwszName, prgBinding[1].cbMaxLen + prgBinding[2].cbMaxLen + 2, L", ");
        _tcscpy_s(pwszName, prgBinding[1].cbMaxLen + prgBinding[2].cbMaxLen + 2, (WCHAR*)(pData+prgBinding[2].obValue));

        // Add new item into combobox
        //
        /*dwIndex = SendDlgItemMessage(m_hWndEmployees, IDC_COMBO_NAME, CB_ADDSTRING, 0, (LPARAM)pwszName);
        if (CB_ERR != dwIndex)
        {
          // Set item assocaited data to employee id.
          SendDlgItemMessage(  m_hWndEmployees, 
                    IDC_COMBO_NAME, 
                    CB_SETITEMDATA, 
                    dwIndex, 
                    *(LONG*)(pData+prgBinding[0].obValue));
        }*/
      }
    }

    // Release the rowset.
    //
    hr = pIRowset->ReleaseRows(1, prghRows, NULL, NULL, NULL);
    if(FAILED(hr))
    {
      goto Exit;
    }

    // Fetches next row.
    hr = pIRowset->GetNextRows(DB_NULL_HCHAPTER, 0, 1, &cRowsObtained, &prghRows);
  }

Exit:
  // Clear Variants
  //
  VariantClear(&rowsetprop[0].vValue);

  // Free allocated DBBinding memory
  //
  if (prgBinding)
  {
      CoTaskMemFree(prgBinding);
      prgBinding = NULL;
  }

  // Free allocated column info memory
  //
  if (pDBColumnInfo)
  {
      CoTaskMemFree(pDBColumnInfo);
      pDBColumnInfo = NULL;
  }

// Free allocated column string values buffer
  //
  if (pStringsBuffer)
  {
      CoTaskMemFree(pStringsBuffer);
      pStringsBuffer = NULL;
  }

  // Free data record buffer
  //
  if (pData)
  {
    CoTaskMemFree(pData);
    pData = NULL;
  }

  // Free employee name buffer
  //
  if (pwszName)
  {
    CoTaskMemFree(pwszName);
    pwszName = NULL;
  }

  // Release interfaces
  //
  if(pIAccessor)
  {
    pIAccessor->ReleaseAccessor(hAccessor, NULL); 
    pIAccessor->Release();
  }

  if (pIColumnsInfo)
  {
    pIColumnsInfo->Release();
  }

  if(pIRowset)
  {
    pIRowset->Release();
  }

  if(pIOpenRowset)
  {
    pIOpenRowset->Release();
  }

  return hr;
}

////////////////////////////////////////////////////////////////////////////////
// Function: LoadEmployeeInfo()
//
// Description: Update employee info based on employee id.
//
// Returns: NOERROR if succesfull
//
// Notes:
//
////////////////////////////////////////////////////////////////////////////////
HRESULT CChatRecordDB::LoadEmployeeInfo(DWORD dwEmployeeID)
{
  HRESULT        hr          = NOERROR;      // Error code reporting
  DBBINDING      *prgBinding      = NULL;        // Binding used to create accessor
  HROW        rghRows[1];                // Array of row handles obtained from the rowset object
  HROW        *prghRows      = rghRows;      // Row handle(s) pointer
  DBID        TableID;                // Used to open/create table
  DBID        IndexID;                // Used to create index
  DBPROPSET      rowsetpropset[1];            // Used when opening integrated index
  DBPROP        rowsetprop[1];              // Used when opening integrated index
     ULONG        cRowsObtained    = 0;        // Number of rows obtained from the rowset object
    DBOBJECT      dbObject;                // DBOBJECT data.
  DBCOLUMNINFO    *pDBColumnInfo    = NULL;        // Record column metadata
  BYTE        *pData        = NULL;        // record data
  WCHAR        *pStringsBuffer    = NULL;
  DWORD        dwBindingSize    = 0;
  DWORD        dwIndex        = 0;
  DWORD        dwOffset      = 0;
  DWORD        dwOrdinal      = 0;
  ULONG        ulNumCols;

  IOpenRowset      *pIOpenRowset    = NULL;        // Provider Interface Pointer
  IRowset        *pIRowset      = NULL;        // Provider Interface Pointer
  IRowsetIndex    *pIRowsetIndex    = NULL;        // Provider Interface Pointer
  IAccessor      *pIAccessor      = NULL;        // Provider Interface Pointer
  //ILockBytes      *pILockBytes    = NULL;        // Provider Interface Pointer
  IColumnsInfo    *pIColumnsInfo    = NULL;        // Provider Interface Pointer
  HACCESSOR      hAccessor      = DB_NULL_HACCESSOR;// Accessor handle

  WCHAR*        pwszEmployees[]    =  {            // Employee info Column names
                  L"EmployeeID",
                  L"Address",
                  L"City",   
                  L"Region", 
                  L"PostalCode",
                  L"Country", 
                  L"HomePhone",
                  L"Photo"  
                };
  
  VariantInit(&rowsetprop[0].vValue);

  // Validate IDBCreateSession interface
  //
  if (NULL == m_pIDBCreateSession)
  {
    hr = E_POINTER;
    goto Exit;
  }

    // Create a session object 
    //
    hr = m_pIDBCreateSession->CreateSession(NULL, IID_IOpenRowset, (IUnknown**) &pIOpenRowset);
    if(FAILED(hr))
    {
        goto Exit;
    }

  // Set up information necessary to open a table 
  // using an index and have the ability to seek.
  //
  TableID.eKind      = DBKIND_NAME;
  TableID.uName.pwszName  = (WCHAR*)TABLE_EMPLOYEE;

  IndexID.eKind      = DBKIND_NAME;
  IndexID.uName.pwszName  = L"PK_UserTable";

  // Request ability to use IRowsetChange interface
  // 
  rowsetpropset[0].cProperties  = 1;
  rowsetpropset[0].guidPropertySet= DBPROPSET_ROWSET;
  rowsetpropset[0].rgProperties  = rowsetprop;

  rowsetprop[0].dwPropertyID    = DBPROP_IRowsetIndex;
  rowsetprop[0].dwOptions      = DBPROPOPTIONS_REQUIRED;
  rowsetprop[0].colid        = DB_NULLID;
  rowsetprop[0].vValue.vt      = VT_BOOL;
  rowsetprop[0].vValue.boolVal  = VARIANT_TRUE;

  // Open the table using the index
  //
  hr = pIOpenRowset->OpenRowset(  NULL,
                  &TableID,
                  &IndexID,
                  IID_IRowsetIndex,
                  sizeof(rowsetpropset)/sizeof(rowsetpropset[0]),
                  rowsetpropset,
                  (IUnknown**) &pIRowsetIndex);
  if(FAILED(hr))
  {
    goto Exit;
  }

    // Get IRowset interface
  //
  hr = pIRowsetIndex->QueryInterface(IID_IRowset, (void**) &pIRowset);
  if(FAILED(hr))
  {
    goto Exit;
  }

    // Get IColumnsInfo interface
  //
    hr = pIRowset->QueryInterface(IID_IColumnsInfo, (void **)&pIColumnsInfo);
  if(FAILED(hr))
  {
    goto Exit;
  }

  // Get the column metadata 
  //
    hr = pIColumnsInfo->GetColumnInfo(&ulNumCols, &pDBColumnInfo, &pStringsBuffer);
  if(FAILED(hr) || 0 == ulNumCols)
  {
    goto Exit;
  }

    // Create a DBBINDING array.
  //
  dwBindingSize = sizeof(pwszEmployees)/sizeof(pwszEmployees[0]);
  prgBinding = (DBBINDING*)CoTaskMemAlloc(sizeof(DBBINDING)*dwBindingSize);
  if (NULL == prgBinding)
  {
    hr = E_OUTOFMEMORY;
    goto Exit;
  }

  // Set initial offset for binding position
  //
  dwOffset = 0;

  // Prepare structures to create the accessor
  //
  for (dwIndex = 0; dwIndex < dwBindingSize; ++dwIndex)
  {
    if (!GetColumnOrdinal(pDBColumnInfo, ulNumCols, pwszEmployees[dwIndex], &dwOrdinal))
    {
      hr = E_FAIL;
      goto Exit;
    }

    // Prepare structures to create the accessor
    //
    prgBinding[dwIndex].iOrdinal  = dwOrdinal;
    prgBinding[dwIndex].dwPart    = DBPART_VALUE | DBPART_STATUS | DBPART_LENGTH;
    prgBinding[dwIndex].obLength  = dwOffset;                                     
    prgBinding[dwIndex].obStatus  = prgBinding[dwIndex].obLength + sizeof(ULONG);  
    prgBinding[dwIndex].obValue    = prgBinding[dwIndex].obStatus + sizeof(DBSTATUS);
    prgBinding[dwIndex].pTypeInfo  = NULL;
    prgBinding[dwIndex].pBindExt  = NULL;
    prgBinding[dwIndex].dwMemOwner  = DBMEMOWNER_CLIENTOWNED;
    prgBinding[dwIndex].dwFlags    = 0;
    prgBinding[dwIndex].bPrecision  = pDBColumnInfo[dwOrdinal].bPrecision;
    prgBinding[dwIndex].bScale    = pDBColumnInfo[dwOrdinal].bScale;

    switch(pDBColumnInfo[dwOrdinal].wType)
    {
    case DBTYPE_BYTES:    // Column "Photo" binding (BLOB) 
      // Set up the DBOBJECT structure.
      //
      dbObject.dwFlags = STGM_READ;
      dbObject.iid   = IID_ILockBytes;

      prgBinding[dwIndex].pObject    = &dbObject;
      prgBinding[dwIndex].cbMaxLen  = sizeof(IUnknown*);
      prgBinding[dwIndex].wType    = DBTYPE_IUNKNOWN;
      break;

    case DBTYPE_WSTR:
      prgBinding[dwIndex].pObject    = NULL;
      prgBinding[dwIndex].wType    = pDBColumnInfo[dwOrdinal].wType;
      prgBinding[dwIndex].cbMaxLen  = sizeof(WCHAR)*(pDBColumnInfo[dwOrdinal].ulColumnSize + 1);  // Extra buffer for null terminator 
      break;

    default:
      prgBinding[dwIndex].pObject    = NULL;
      prgBinding[dwIndex].wType    = pDBColumnInfo[dwOrdinal].wType;
      prgBinding[dwIndex].cbMaxLen  = pDBColumnInfo[dwOrdinal].ulColumnSize; 
      break;
    }

    // Calculate new offset
    // 
    dwOffset = prgBinding[dwIndex].obValue + prgBinding[dwIndex].cbMaxLen;

    // Properly align the offset
    //
    dwOffset = ROUND_UP(dwOffset, COLUMN_ALIGNVAL);
  }

  // Get IAccessor interface
  //
  hr = pIRowset->QueryInterface(IID_IAccessor, (void**)&pIAccessor);
  if(FAILED(hr))
  {
    goto Exit;
  }

  // Create accessor.
  //
    hr = pIAccessor->CreateAccessor(DBACCESSOR_ROWDATA, 
            dwBindingSize, 
            prgBinding,
            0,
            &hAccessor,
            NULL);

    if(FAILED(hr))
    {
        goto Exit;
    }

  // Allocate data buffer for seek and retrieve operation.
  //
  pData = (BYTE*)CoTaskMemAlloc(dwOffset);
  if (NULL == pData)
  {
    hr = E_OUTOFMEMORY;
    goto Exit;
  }

  // Set data buffer to zero
  //
  memset(pData, 0, dwOffset);

  // Set data buffer for seek operation
  //
  *(ULONG*) (pData+prgBinding[0].obLength)    = 4;
  *(DBSTATUS*) (pData+prgBinding[0].obStatus)  = DBSTATUS_S_OK;
  *(int*) (pData+prgBinding[0].obValue)    = dwEmployeeID;

   // Position at a key value within the current range 
  //
  hr = pIRowsetIndex->Seek(hAccessor, 1, pData, DBSEEK_FIRSTEQ);
  if(FAILED(hr))
  {
    goto Exit;  
  }

  // Retrieve a row handle for the row resulting from the seek
  //
  hr = pIRowset->GetNextRows(DB_NULL_HCHAPTER, 0, 1, &cRowsObtained, &prghRows);
  if(FAILED(hr))
  {
    goto Exit;  
  }

  if (DB_S_ENDOFROWSET != hr)
  {
    // Fetch actual data
    //
    hr = pIRowset->GetData(prghRows[0], hAccessor, pData);
    if (FAILED(hr))
    {
      goto Exit;
    }

    // Clear employee info on the dialog
    //
    ClearEmployeeInfo();

    /*// Update dialog
    // If return a null value or status is not OK, ignore the contents of the value and length parts of the buffer.
    //
    if (DBSTATUS_S_ISNULL != *(DBSTATUS *)(pData+prgBinding[0].obStatus) && 
          DBSTATUS_S_OK == *(DBSTATUS *)(pData+prgBinding[0].obStatus))
    {
      SetDlgItemInt(m_hWndEmployees,  IDC_EDIT_EMPLOYEE_ID, *(LONG*)(pData+prgBinding[0].obValue), 0);
    }

    if (DBSTATUS_S_ISNULL != *(DBSTATUS *)(pData+prgBinding[1].obStatus) &&
            DBSTATUS_S_OK == *(DBSTATUS *)(pData+prgBinding[1].obStatus))
    {
      SetDlgItemText(m_hWndEmployees, IDC_EDIT_ADDRESS, (WCHAR*)(pData+prgBinding[1].obValue));
    }

    if (DBSTATUS_S_ISNULL != *(DBSTATUS *)(pData+prgBinding[2].obStatus) &&
            DBSTATUS_S_OK == *(DBSTATUS *)(pData+prgBinding[2].obStatus))
    {
      SetDlgItemText(m_hWndEmployees, IDC_EDIT_CITY, (WCHAR*)(pData+prgBinding[2].obValue));
    }

    if (DBSTATUS_S_ISNULL != *(DBSTATUS *)(pData+prgBinding[3].obStatus) &&
            DBSTATUS_S_OK == *(DBSTATUS *)(pData+prgBinding[3].obStatus))
    {
      SetDlgItemText(m_hWndEmployees, IDC_EDIT_REGION, (WCHAR*)(pData+prgBinding[3].obValue));
    }

    if (DBSTATUS_S_ISNULL != *(DBSTATUS *)(pData+prgBinding[4].obStatus) &&
            DBSTATUS_S_OK == *(DBSTATUS *)(pData+prgBinding[4].obStatus))
    {
      SetDlgItemText(m_hWndEmployees, IDC_EDIT_POSTAL_CODE, (WCHAR*)(pData+prgBinding[4].obValue));
    }

    if (DBSTATUS_S_ISNULL != *(DBSTATUS *)(pData+prgBinding[5].obStatus) &&
            DBSTATUS_S_OK == *(DBSTATUS *)(pData+prgBinding[5].obStatus))
    {
      SetDlgItemText(m_hWndEmployees, IDC_EDIT_COUNTRY, (WCHAR*)(pData+prgBinding[5].obValue));
    }

    if (DBSTATUS_S_ISNULL != *(DBSTATUS *)(pData+prgBinding[6].obStatus) &&
            DBSTATUS_S_OK == *(DBSTATUS *)(pData+prgBinding[6].obStatus))
    {
      SetDlgItemText(m_hWndEmployees, IDC_EDIT_HOME_PHONE, (WCHAR*)(pData+prgBinding[6].obValue));
    }

    // Update employee photo
    // 
    if (DBSTATUS_S_ISNULL != *(DBSTATUS *)(pData+prgBinding[7].obStatus) &&
            DBSTATUS_S_OK == *(DBSTATUS *)(pData+prgBinding[7].obStatus))
    {
      pILockBytes = (*(ILockBytes**) (pData + prgBinding[7].obValue));
      LoadEmployeePhoto(pILockBytes);
    }*/
  }

  // Release the rowset.
  //
  pIRowset->ReleaseRows(1, prghRows, NULL, NULL, NULL);

Exit:
  // Clear Variants
  //
  VariantClear(&rowsetprop[0].vValue);

  // Free allocated DBBinding memory
  //
  if (prgBinding)
  {
      CoTaskMemFree(prgBinding);
      prgBinding = NULL;
  }

  // Free allocated column info memory
  //
  if (pDBColumnInfo)
  {
      CoTaskMemFree(pDBColumnInfo);
      pDBColumnInfo = NULL;
  }
  
  // Free allocated column string values buffer
  //
  if (pStringsBuffer)
  {
    CoTaskMemFree(pStringsBuffer);
    pStringsBuffer = NULL;
  }

  // Free data record buffer
  //
  if (pData)
  {
    CoTaskMemFree(pData);
    pData = NULL;
  }

  // Release interfaces
  //
  /*if(pILockBytes)
  {
    pILockBytes->Release();
  }*/

  if(pIAccessor)
  {
    pIAccessor->ReleaseAccessor(hAccessor, NULL); 
    pIAccessor->Release();
  }

  if (pIColumnsInfo)
  {
    pIColumnsInfo->Release();
  }

  if(pIRowset)
  {
    pIRowset->Release();
  }

  if (pIRowsetIndex)
  {
    pIRowsetIndex->Release();
  }

  if(pIOpenRowset)
  {
    pIOpenRowset->Release();
  }

  return hr;
}

////////////////////////////////////////////////////////////////////////////////
// Function: LoadEmployeePhoto()
//
// Description: Load employee photo from database.
//
// Returns: NOERROR if succesfull
//
// Notes: This sample only display 24 bit bitmap
//
////////////////////////////////////////////////////////////////////////////////
HRESULT CChatRecordDB::LoadEmployeePhoto(ILockBytes* pILockBytes)
{
  HRESULT        hr = NOERROR;
  ULONG        ulRead;
  ULARGE_INTEGER    ulStart;
  BITMAPFILEHEADER  bmpFileHeader;
  BITMAPINFO      bmpInfo;
  //BYTE        *pPhotoBits;
  // HDC          hDC;

  if (m_hBitmap)
  {
    // Delete bitmap object, release the device contexts, 
    //
    DeleteObject(m_hBitmap);
    m_hBitmap = NULL;
  }

  // Validate ILockBytes interface 
  //
  if (NULL == pILockBytes)
  {
    return hr;
  }

  // Read Bitmap file header
  //
  ulRead = 0;
  ulStart.QuadPart = 0;
  hr = pILockBytes->ReadAt(ulStart, &bmpFileHeader, sizeof(BITMAPFILEHEADER), &ulRead);
  if(FAILED(hr) || sizeof(BITMAPFILEHEADER) != ulRead) 
  {
    return hr;
  }

  // Read Bitmap info header
  //
  ulStart.QuadPart += ulRead;
  ulRead = 0;
  hr = pILockBytes->ReadAt(ulStart, &bmpInfo, sizeof(BITMAPINFOHEADER), &ulRead);
  if(FAILED(hr) || sizeof(BITMAPINFOHEADER) != ulRead) 
  {
    return hr;
  }

  /*// THIS SAMPLE ONLY SUPPORT 24 BIT BITMAP
  //
  if (24 != bmpInfo.bmiHeader.biBitCount)
  {
    return hr;
  }

  // Retrieve the device context handle
  //
  hDC = GetDC(m_hWndEmployees);

  // Creates a device-independent bitmap (DIB) with bitmap info
  //
  m_hBitmap = CreateDIBSection(  hDC,
                &bmpInfo, 
                DIB_RGB_COLORS, 
                (void **)&pPhotoBits, 
                NULL, 
                0);

  // Read bitmap bits
  //
  ulStart.QuadPart += ulRead;
  ulRead = 0;
  hr = pILockBytes->ReadAt(ulStart, pPhotoBits, bmpInfo.bmiHeader.biSizeImage, &ulRead);
  if(FAILED(hr) || bmpInfo.bmiHeader.biSizeImage != ulRead) 
  {
    // Delete bitmap object, release the device contexts, 
    //
    DeleteObject(m_hBitmap);
    m_hBitmap = NULL;
  }

  ReleaseDC(m_hWndEmployees, hDC);*/

  return hr;
}

////////////////////////////////////////////////////////////////////////////////
// Function: ShowEmployeePhoto()
//
// Description: Show employee photo.
//
// Notes: This sample only display 24 bit bitmap
//
////////////////////////////////////////////////////////////////////////////////
/*void CChatRecordDB::ShowEmployeePhoto()
{
  HDC          hdcMem;
  HDC          hDC;

  // If m_hBitmap is NULL, 
  // clear the photo area with a gray rectangle
  //
  if (NULL == m_hBitmap)
  {
    HBRUSH        hBrush;
    RECT        rect;

    SetRect(&rect, PHOTO_X, PHOTO_Y, PHOTO_X + PHOTO_WIDTH, PHOTO_Y + PHOTO_HEIGHT);

    hDC = GetDC(m_hWndEmployees);
    hBrush = CreateSolidBrush(RGB(192, 192, 192));
    FillRect(hDC, &rect, hBrush);

    DeleteObject(hBrush);
    ReleaseDC(m_hWndEmployees, hDC);

    return;
  }

  // Retrieve the device context handle
  //
  hDC = GetDC(m_hWndEmployees);

  // Creates a memory device context, select bitmap handle
  //
  hdcMem = CreateCompatibleDC(hDC);
  SelectObject(hdcMem, m_hBitmap);

  // Display bitmap,
  //
  BitBlt(  hDC, 
        PHOTO_X, 
        PHOTO_Y, 
        PHOTO_WIDTH,
        PHOTO_HEIGHT, 
        hdcMem, 
        0, 
        0,  
        SRCCOPY); 

  // Delete bitmap object, release the device contexts, 
  //
  DeleteDC(hdcMem);
  ReleaseDC(m_hWndEmployees, hDC);
}*/


////////////////////////////////////////////////////////////////////////////////
// Function: ClearEmployeeInfo()
//
// Description: clear employee info displayed on the window.
//
// Returns:
//
// Notes:
//
////////////////////////////////////////////////////////////////////////////////
void CChatRecordDB::ClearEmployeeInfo()
{
  /*SetDlgItemText(m_hWndEmployees, IDC_EDIT_EMPLOYEE_ID, L"");
  SetDlgItemText(m_hWndEmployees, IDC_EDIT_ADDRESS,     L"");
  SetDlgItemText(m_hWndEmployees, IDC_EDIT_CITY,        L"");
  SetDlgItemText(m_hWndEmployees, IDC_EDIT_REGION,      L"");
  SetDlgItemText(m_hWndEmployees, IDC_EDIT_POSTAL_CODE, L"");
  SetDlgItemText(m_hWndEmployees, IDC_EDIT_COUNTRY,     L"");
  SetDlgItemText(m_hWndEmployees, IDC_EDIT_HOME_PHONE,  L"");*/

  LoadEmployeePhoto(NULL);
}

////////////////////////////////////////////////////////////////////////////////
// Function: SaveEmployeeInfo()
//
// Description: Save employee info to database.
//
// Returns: NOERROR if succesfull
//
// Notes:
//
////////////////////////////////////////////////////////////////////////////////
HRESULT CChatRecordDB::SaveEmployeeInfo(DWORD dwEmployeeID)
{
  HRESULT        hr          = NOERROR;      // Error code reporting
  DBBINDING      *prgBinding      = NULL;        // Binding used to create accessor
  HROW        rghRows[1];                // Array of row handles obtained from the rowset object
  HROW        *prghRows      = rghRows;      // Row handle(s) pointer
  DBID        TableID;                // Used to open/create table
  DBID        IndexID;                // Used to create index
  DBPROPSET      rowsetpropset[1];            // Used when opening integrated index
  DBPROP        rowsetprop[2];              // Used when opening integrated index
  ULONG        cRowsObtained    = 0;        // Number of rows obtained from the rowset object
  DBCOLUMNINFO    *pDBColumnInfo    = NULL;        // Record column metadata
  BYTE        *pData        = NULL;        // record data
  WCHAR        *pStringsBuffer    = NULL;
  DWORD        dwBindingSize    = 0;
  DWORD        dwIndex        = 0;
  DWORD        dwOffset      = 0;
  DWORD        dwOrdinal      = 0;
  ULONG        ulNumCols;

  IOpenRowset      *pIOpenRowset    = NULL;        // Provider Interface Pointer
  IRowset        *pIRowset      = NULL;        // Provider Interface Pointer
  IRowsetChange    *pIRowsetChange    = NULL;
  IRowsetIndex    *pIRowsetIndex    = NULL;        // Provider Interface Pointer
  IAccessor      *pIAccessor      = NULL;        // Provider Interface Pointer
  IColumnsInfo    *pIColumnsInfo    = NULL;        // Provider Interface Pointer
  HACCESSOR      hAccessor      = DB_NULL_HACCESSOR;// Accessor handle

  WCHAR*        pwszEmployees[]    =  {        // Employee info column names
                          L"EmployeeID",
                          L"Address",
                          L"City",
                          L"Region",
                          L"PostalCode",
                          L"Country",
                          L"HomePhone"
                        };
  
  VariantInit(&rowsetprop[0].vValue);
  VariantInit(&rowsetprop[1].vValue);

  // Validate IDBCreateSession interface
  //
  if (NULL == m_pIDBCreateSession)
  {
    hr = E_POINTER;
    goto Exit;
  }

  // Create a session object 
  //
  hr = m_pIDBCreateSession->CreateSession(NULL, IID_IOpenRowset, (IUnknown**) &pIOpenRowset);
  if(FAILED(hr))
  {
      goto Exit;
  }

  // Set up information necessary to open a table 
  // using an index and have the ability to seek.
  //
  TableID.eKind      = DBKIND_NAME;
  TableID.uName.pwszName  = (WCHAR*)TABLE_EMPLOYEE;

  IndexID.eKind      = DBKIND_NAME;
  IndexID.uName.pwszName  = L"PK_UserTable";

  // Request ability to use IRowsetChange interface
  // 
  rowsetpropset[0].cProperties  = 2;
  rowsetpropset[0].guidPropertySet= DBPROPSET_ROWSET;
  rowsetpropset[0].rgProperties  = rowsetprop;

  rowsetprop[0].dwPropertyID    = DBPROP_IRowsetChange;
  rowsetprop[0].dwOptions      = DBPROPOPTIONS_REQUIRED;
  rowsetprop[0].colid        = DB_NULLID;
  rowsetprop[0].vValue.vt      = VT_BOOL;
  rowsetprop[0].vValue.boolVal  = VARIANT_TRUE;

  rowsetprop[1].dwPropertyID    = DBPROP_IRowsetIndex;
  rowsetprop[1].dwOptions      = DBPROPOPTIONS_REQUIRED;
  rowsetprop[1].colid        = DB_NULLID;
  rowsetprop[1].vValue.vt      = VT_BOOL;
  rowsetprop[1].vValue.boolVal  = VARIANT_TRUE;

  // Open the table using the index
  //
  hr = pIOpenRowset->OpenRowset(  NULL,
          &TableID,
          &IndexID,
          IID_IRowsetIndex,
          sizeof(rowsetpropset)/sizeof(rowsetpropset[0]),
          rowsetpropset,
          (IUnknown**) &pIRowsetIndex);
  if(FAILED(hr))
  {
    goto Exit;
  }

  // Get IRowset interface
  //
  hr = pIRowsetIndex->QueryInterface(IID_IRowset, (void**) &pIRowset);
  if(FAILED(hr))
  {
    goto Exit;
  }

  hr = pIRowset->QueryInterface(IID_IRowsetChange, (void**)&pIRowsetChange);
  if(FAILED(hr))
  {
    goto Exit;
  }

  // Get IColumnsInfo interface
  //
    hr = pIRowset->QueryInterface(IID_IColumnsInfo, (void **)&pIColumnsInfo);
  if(FAILED(hr))
  {
    goto Exit;
  }

  // Get the column metadata 
  //
    hr = pIColumnsInfo->GetColumnInfo(&ulNumCols, &pDBColumnInfo, &pStringsBuffer);
  if(FAILED(hr) || 0 == ulNumCols)
  {
    goto Exit;
  }

  // Create a DBBINDING array.
  //
  dwBindingSize = sizeof(pwszEmployees)/sizeof(pwszEmployees[0]);
  prgBinding = (DBBINDING*)CoTaskMemAlloc(sizeof(DBBINDING)*dwBindingSize);
  if (NULL == prgBinding)
  {
    hr = E_OUTOFMEMORY;
    goto Exit;
  }

  // Set initial offset for binding position
  //
  dwOffset = 0;

  // Prepare structures to create the accessor
  //
  for (dwIndex = 0; dwIndex < dwBindingSize; ++dwIndex)
  {
    if (!GetColumnOrdinal(pDBColumnInfo, ulNumCols, pwszEmployees[dwIndex], &dwOrdinal))
    {
      hr = E_FAIL;
      goto Exit;
    }

    prgBinding[dwIndex].iOrdinal  = dwOrdinal;
    prgBinding[dwIndex].dwPart    = DBPART_VALUE | DBPART_STATUS | DBPART_LENGTH;
    prgBinding[dwIndex].obLength  = dwOffset;                                     
    prgBinding[dwIndex].obStatus  = prgBinding[dwIndex].obLength + sizeof(ULONG);  
    prgBinding[dwIndex].obValue    = prgBinding[dwIndex].obStatus + sizeof(DBSTATUS);
    prgBinding[dwIndex].pTypeInfo  = NULL;
    prgBinding[dwIndex].pObject    = NULL;
    prgBinding[dwIndex].pBindExt  = NULL;
    prgBinding[dwIndex].dwMemOwner  = DBMEMOWNER_CLIENTOWNED;
    prgBinding[dwIndex].dwFlags    = 0;
    prgBinding[dwIndex].wType    = pDBColumnInfo[dwOrdinal].wType;
    prgBinding[dwIndex].bPrecision  = pDBColumnInfo[dwOrdinal].bPrecision;
    prgBinding[dwIndex].bScale    = pDBColumnInfo[dwOrdinal].bScale;

    switch(prgBinding[dwIndex].wType)
    {
    case DBTYPE_WSTR:    
      prgBinding[dwIndex].cbMaxLen = sizeof(WCHAR)*(pDBColumnInfo[dwOrdinal].ulColumnSize + 1);  // Extra buffer for null terminator 
      break;
    default:
      prgBinding[dwIndex].cbMaxLen = pDBColumnInfo[dwOrdinal].ulColumnSize; 
      break;
    }
    
    // Calculate new offset
    // 
    dwOffset = prgBinding[dwIndex].obValue + prgBinding[dwIndex].cbMaxLen;

    // Properly align the offset
    //
    dwOffset = ROUND_UP(dwOffset, COLUMN_ALIGNVAL);
  }

  // Get IAccessor interface
  //
  hr = pIRowset->QueryInterface(IID_IAccessor, (void**)&pIAccessor);
  if(FAILED(hr))
  {
    goto Exit;
  }

  // Create accessor.
  //
  hr = pIAccessor->CreateAccessor(DBACCESSOR_ROWDATA, 
                dwBindingSize, 
                prgBinding,
                0,
                &hAccessor,
                NULL);
  if(FAILED(hr))
  {
      goto Exit;
  }

  // Allocate data buffer for seek and retrieve operation.
  //
  pData = (BYTE*)CoTaskMemAlloc(dwOffset);
  if (NULL == pData)
  {
    hr = E_OUTOFMEMORY;
    goto Exit;
  }

  // Set data buffer to zero
  //
  memset(pData, 0, dwOffset);

  // Set data buffer for seek operation
  //
  *(ULONG*) (pData+prgBinding[0].obLength)    = 4;
  *(DBSTATUS*) (pData+prgBinding[0].obStatus)  = DBSTATUS_S_OK;
  *(int*) (pData+prgBinding[0].obValue)    = dwEmployeeID;

  // Position at a key value within the current range 
  //
  hr = pIRowsetIndex->Seek(hAccessor, 1, pData, DBSEEK_FIRSTEQ);
  if(FAILED(hr))
  {
    goto Exit;  
  }

  // Retrieve a row handle for the row resulting from the seek
  //
  hr = pIRowset->GetNextRows(DB_NULL_HCHAPTER, 0, 1, &cRowsObtained, &prghRows);
  if(FAILED(hr))
  {
    goto Exit;  
  }

  if (DB_S_ENDOFROWSET != hr)
  {
/*    GetDlgItemText(m_hWndEmployees, IDC_EDIT_ADDRESS,    (WCHAR*)(pData+prgBinding[1].obValue), prgBinding[1].cbMaxLen);
    GetDlgItemText(m_hWndEmployees, IDC_EDIT_CITY,      (WCHAR*)(pData+prgBinding[2].obValue), prgBinding[2].cbMaxLen);
    GetDlgItemText(m_hWndEmployees, IDC_EDIT_REGION,    (WCHAR*)(pData+prgBinding[3].obValue), prgBinding[3].cbMaxLen);
    GetDlgItemText(m_hWndEmployees, IDC_EDIT_POSTAL_CODE, (WCHAR*)(pData+prgBinding[4].obValue), prgBinding[4].cbMaxLen);
    GetDlgItemText(m_hWndEmployees, IDC_EDIT_COUNTRY,    (WCHAR*)(pData+prgBinding[5].obValue), prgBinding[5].cbMaxLen);
    GetDlgItemText(m_hWndEmployees, IDC_EDIT_HOME_PHONE,  (WCHAR*)(pData+prgBinding[6].obValue), prgBinding[6].cbMaxLen);*/

    for (dwIndex = 1; dwIndex <= 6; ++dwIndex)
    {
      *(ULONG*)(pData+prgBinding[dwIndex].obLength)   = wcslen((WCHAR*)(pData+prgBinding[dwIndex].obValue))*sizeof(WCHAR);
      *(DBSTATUS*)(pData+prgBinding[dwIndex].obStatus) = DBSTATUS_S_OK;
    }

    // Set data to database
    //
    hr = pIRowsetChange->SetData(prghRows[0], hAccessor, pData);
  }

  // Release the rowset.
  //
  pIRowset->ReleaseRows(1, prghRows, NULL, NULL, NULL);

Exit:
  // Clear Variants
  //
  VariantClear(&rowsetprop[0].vValue);
  VariantClear(&rowsetprop[1].vValue);

  // Free allocated DBBinding memory
  //
  if (prgBinding)
  {
      CoTaskMemFree(prgBinding);
      prgBinding = NULL;
  }

  // Free allocated column info memory
  //
  if (pDBColumnInfo)
  {
      CoTaskMemFree(pDBColumnInfo);
      pDBColumnInfo = NULL;
  }

// Free allocated column string values buffer
  //
  if (pStringsBuffer)
  {
    CoTaskMemFree(pStringsBuffer);
    pStringsBuffer = NULL;
  }

  // Free data record buffer
  //
  if (pData)
  {
    CoTaskMemFree(pData);
    pData = NULL;
  }

  // Release interfaces
  //
  if(pIAccessor)
  {
    pIAccessor->ReleaseAccessor(hAccessor, NULL); 
    pIAccessor->Release();
  }

  if (pIColumnsInfo)
  {
    pIColumnsInfo->Release();
  }

  if (pIRowsetChange)
  {
    pIRowsetChange->Release();
  }

  if(pIRowset)
  {
    pIRowset->Release();
  }

  if (pIRowsetIndex)
  {
    pIRowsetIndex->Release();
  }

  if(pIOpenRowset)
  {
    pIOpenRowset->Release();
  }

  return hr;
}

////////////////////////////////////////////////////////////////////////////////
// Function: GetColumnOrdinal()
//
// Description: Returns column ordinal for column name.
//
// Parameters
//    pDBColumnInfo  - a pointer to Database column info
//    dwNumCols    - number of columns
//    pwszColName    - column name
//    pOrdinal    - column ordinal
//
// Returns: TRUE if succesfull
//
////////////////////////////////////////////////////////////////////////////////
BOOL CChatRecordDB::GetColumnOrdinal(DBCOLUMNINFO* pDBColumnInfo, DWORD dwNumCols, WCHAR* pwszColName, DWORD* pOrdinal)
{
  for(DWORD dwCol = 0; dwCol< dwNumCols; ++dwCol)
  {
    if(NULL != pDBColumnInfo[dwCol].pwszName)
    {
      if(0 == _wcsicmp(pDBColumnInfo[dwCol].pwszName, pwszColName))
      {
        *pOrdinal = pDBColumnInfo[dwCol].iOrdinal;
        return TRUE;
      }
    }
  }

  return FALSE;
}


/// <summary>
/// This function demonstrates a routine that can handle and display 
/// errors from the OLE DB provider for SQL Server Compact 3.5. The
/// errors that occured on the current thread are displayed.
/// </summary>
HRESULT DisplayCurrentThreadErrors()
{
    static TCHAR *sErrIErrorInfo     = L"IErrorInfo interface";
    static TCHAR *sErrIErrorRecords  = L"IErrorRecords interface";
    static TCHAR *sErrRecordCount    = L"error record count";
    static TCHAR *sErrInfo           = L"ERRORINFO structure";
    static TCHAR *sErrStandardInfo   = L"standard error info";
    static TCHAR *sErrDescription    = L"standard error description";
    static TCHAR *sErrNoSource       = L"error source";

    HRESULT hr                          = S_OK;
    IErrorInfo       *pIErrorInfo       = NULL;
    IErrorRecords    *pIErrorRecords    = NULL;
    ERRORINFO        errorInfo          = { 0 };
    IErrorInfo       *pIErrorInfoRecord = NULL;

    try
    {
      // This interface supports returning error information.
      // Get the error object from the system for the current
      // thread.
      hr = GetErrorInfo(0, &pIErrorInfo);
      if ( hr == S_FALSE )
      {
          TRACE(L"No error occured.\n");
          return S_OK;
      }

      if(FAILED(hr) || NULL == pIErrorInfo)
          throw sErrIErrorInfo;

      // The error records are retrieved from the IIErrorRecords
      // interface, which can be obtained from the IErrorInfo
      // interface.
      hr = pIErrorInfo->QueryInterface(IID_IErrorRecords,
          (void **) &pIErrorRecords);
      if ( FAILED(hr) || NULL == pIErrorRecords )
          throw sErrIErrorRecords;

      // The IErrorInfo interface is no longer required because
      // we have the IErrorRecords interface, relase it.
      pIErrorInfo->Release();
      pIErrorInfo = NULL;

      ULONG ulNumErrorRecs = 0;

      // Determine the number of records in this error object
      hr = pIErrorRecords->GetRecordCount(&ulNumErrorRecs);
      if ( FAILED(hr) )
          throw sErrRecordCount;


      // Loop over each error record in the error object to display 
      // information about each error. Errors are returned. 
      for (DWORD dwErrorIndex = 0;
            dwErrorIndex < ulNumErrorRecs;
            dwErrorIndex++)
      {
        // Retrieve basic error information for this error.
        hr = pIErrorRecords->GetBasicErrorInfo(dwErrorIndex,
          &errorInfo);
        if ( FAILED(hr) )
            throw sErrInfo;

        TCHAR szCLSID[64]  = { 0 };
        TCHAR szIID[64]    = { 0 };
        TCHAR szDISPID[64] = { 0 };

        StringFromGUID2(errorInfo.clsid, (LPOLESTR)szCLSID,
            sizeof(szCLSID));
        StringFromGUID2(errorInfo.iid, (LPOLESTR)szIID,
            sizeof(szIID));

        TRACE(L"HRESULT           = %lx\n", errorInfo.hrError);
        TRACE(L"clsid             = %s\n", szCLSID);
        TRACE(L"iid               = %s\n", szIID);
        TRACE(L"dispid            = %ld\n", errorInfo.dispid);
        TRACE(L"Native Error Code = %lx\n", errorInfo.dwMinor);

        // Retrieve standard error information for this error.
        hr = pIErrorRecords->GetErrorInfo(dwErrorIndex, NULL,
            &pIErrorInfoRecord);

        if ( FAILED(hr) )
            throw sErrStandardInfo;

        BSTR bstrDescriptionOfError;
        BSTR bstrSourceOfError;

        // Get the description of the error.
        hr = pIErrorInfoRecord->GetDescription(
              &bstrDescriptionOfError);
        if ( FAILED(hr) )
          throw sErrDescription;

        TRACE(L"Description = %s\n", bstrDescriptionOfError);

        // Get the source of the error.
        hr = pIErrorInfoRecord->GetSource(&bstrSourceOfError);
        if ( FAILED(hr) )
            throw sErrNoSource;

        TRACE(L"Description = %s\n", bstrSourceOfError);

        // This interface variable will be used the next time 
        // though this loop. In the last error case this interface 
        // is no longer needed so we must release it.
        if(NULL != pIErrorInfoRecord)
            pIErrorInfoRecord->Release();
        pIErrorInfoRecord = NULL;
      }
    }
    catch( TCHAR *szMsg )
    {
      TRACE(L"Failed to retrieve ");
      TRACE(szMsg);
    }

    if( pIErrorInfoRecord )
        pIErrorInfoRecord->Release();

    if ( pIErrorInfo )
        pIErrorInfo->Release();

    if ( pIErrorRecords )
        pIErrorRecords->Release();

    return hr;
}
