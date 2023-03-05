### Visual C++ CLR / .Net
This summary mostly contains OLEDb connection, querying examples from CLR Projects. In addition, it has similar examples, for,
- access db
- mdb

**P01 - Bangla Dictinoary**  
Feels like the Form header files are mixed up between Form2 and Form21. I think the mess up is created by brining Form2 over from an earlier project (not sure if we directly copied it over). In addition, not sure if we need following files,

- dbInsert.h
- dbInsert.cpp


Main Form Screenshot,  

![App Main Form](https://user-images.githubusercontent.com/7858031/222981610-88e07821-2911-4528-9057-01252f520ce4.png)

- images dir is not part of the project, contains static resources though.

When "Microsoft.ACE.OLEDB.12.0" is not installed in the system initial dialog box doesn't show up!  
Debugging a bit, we find following exception is hit in following line,

```cpp
OleDbDataReader^ myReader = myCommand->ExecuteReader();
```

Stack trace,  

    System.InvalidOperationException
      HResult=0x80131509

    Message=The 'Microsoft.ACE.OLEDB.12.0' provider is not registered on the local machine.
    Source=System.Data
    StackTrace:
     at System.Data.OleDb.OleDbServicesWrapper.GetDataSource(OleDbConnectionString constr, DataSourceWrapper& datasrcWrapper)
     at System.Data.OleDb.OleDbConnectionInternal..ctor(OleDbConnectionString constr, OleDbConnection connection)
     at System.Data.OleDb.OleDbConnectionFactory.CreateConnection(DbConnectionOptions options, DbConnectionPoolKey poolKey, Object poolGroupProviderInfo, DbConnectionPool pool, DbConnection owningObject)
     at System.Data.ProviderBase.DbConnectionFactory.CreateConnection(DbConnectionOptions options, DbConnectionPoolKey poolKey, Object poolGroupProviderInfo, DbConnectionPool pool, DbConnection owningConnection, DbConnectionOptions userOptions)
     at System.Data.ProviderBase.DbConnectionFactory.CreateNonPooledConnection(DbConnection owningConnection, DbConnectionPoolGroup poolGroup, DbConnectionOptions userOptions)
     at System.Data.ProviderBase.DbConnectionFactory.TryGetConnection(DbConnection owningConnection, TaskCompletionSource`1 retry, DbConnectionOptions userOptions, DbConnectionInternal oldConnection, DbConnectionInternal& connection)
     at System.Data.ProviderBase.DbConnectionInternal.TryOpenConnectionInternal(DbConnection outerConnection, DbConnectionFactory connectionFactory, TaskCompletionSource`1 retry, DbConnectionOptions userOptions)
     at System.Data.ProviderBase.DbConnectionClosed.TryOpenConnection(DbConnection outerConnection, DbConnectionFactory connectionFactory, TaskCompletionSource`1 retry, DbConnectionOptions userOptions)
     at System.Data.ProviderBase.DbConnectionInternal.OpenConnection(DbConnection outerConnection, DbConnectionFactory connectionFactory)
     at System.Data.OleDb.OleDbConnection.Open()
     at dbDictQuery.Form1.updateWordList() in D:\Code\cpp\CLR\dbDictQuery\Form1.h:line 367
     at dbDictQuery.Form1..ctor() in D:\Code\cpp\CLR\dbDictQuery\Form1.h:line 57
     at main(String[] args) in D:\Code\cpp\CLR\dbDictQuery\dbDictQuery.cpp:line 17




**Enter Data Dialog Box**  
Second Form screenshot,  

![Dictionary draft project](https://user-images.githubusercontent.com/7858031/222938941-5c4edc4a-4f32-425b-9f19-8dfede7d8831.png)


From a draft version of this project project earlier, 10-13-2009, (testing before creating a dictionary app next)  

```cpp
System::Void button_Click_Ok(System::Object^  sender, System::EventArgs^  e) {
  // If the connection string is null, use a default.
  String^ myConnectionString = gcnew String(L"Provider=Microsoft.ACE.OLEDB.12.0;Data Source=D:\\\
    CLR\\Db\\bdict.accdb;Persist Security Info=False;");

  // if(myConnectionString->Equals(S"")) 
  // {
  //    myConnectionString = S"Provider=SQLOLEDB;Data Source=localhost;Initial Catalog=Northwind;"  
  //    S"Integrated Security=SSPI;";
  // }

  OleDbConnection^ myConnection = gcnew OleDbConnection(myConnectionString);

  String^ myInsertQuery = String::Concat("INSERT INTO b2e (WordAlias, WordSerial, \
    PartsOfSpeech, Meaning, UseInSentence, EngMeaning, Antonym) Values ('",
    richTextBox1->Text, "', '", richTextBox2->Text, "', '", richTextBox3->Text,
    "', '", richTextBox4->Text, "', '", richTextBox5->Text, "', '", richTextBox6->Text,
      "', '", richTextBox8->Text,"')");

  labelSQLQuery->Text = String::Concat("Actual query: ", myInsertQuery);
  OleDbCommand^ myCommand = gcnew OleDbCommand(myInsertQuery);
  myCommand->Connection = myConnection;

  myConnection->Open();
  myCommand->ExecuteNonQuery();
  myCommand->Connection->Close();

  labelQueryStatus->Text = L"Data inserted into database successfully.";
}
```


**Examples from Earlier Drafts**  

**T02 - OLEDB Example**  
Querying mdb file, from project, 10-11-2009,  

```cpp
System::Void button_Click_Ok(System::Object^  sender, System::EventArgs^  e) {
  String^ sqlQuery = "select * from b2e;";
  String^ conString = "Provider=Microsoft.ACE.OLEDB.12.0;Data Source=D:\\CLR\\Db\\bdict.accdb;Persist Security Info=False;";
  richTextBoxGetData->Text = CreateMyOleDbDataReader(sqlQuery, conString);
}

System::String^ CreateMyOleDbDataReader(String^ mySelectQuery, String^ myConnectionString) {
  OleDbConnection^ myConnection = gcnew OleDbConnection(myConnectionString);
  OleDbCommand^ myCommand = gcnew OleDbCommand(mySelectQuery, myConnection);

  myConnection->Open();

  OleDbDataReader^ myReader = myCommand->ExecuteReader(CommandBehavior::CloseConnection);

  String^ res;

  while(myReader->Read()) {
    res = myReader->GetString(0);
    //}
    myReader->Close();
    //Implicitly closes the connection because CommandBehavior::CloseConnection was specified.
    return res;
  }
};
```

SQL OLE DB Sample is 'Northwind',

```
myConnectionString = S"Provider=SQLOLEDB;Data Source=localhost;Initial Catalog=Northwind;Integrated Security=SSPI;";
```

We also bound the oledb connection to the dataGridView.

**T01 - ODBC Example**  
Connection string from earliest ref, 10-11-2009, using odbc,  

```cpp
this->odbcSelectCommand->CommandText = L"use mydb;\r\nselect * from branch;";
this->odbcConnection->ConnectionString = L"Dsn=ar_MySQL;uid=root";
```


We encountered `System.invalidException` which we fixed.

**Refs**  
- [MSFT - Windows Forms Keys Enum](https://learn.microsoft.com/en-us/dotnet/api/system.windows.forms.keys)
