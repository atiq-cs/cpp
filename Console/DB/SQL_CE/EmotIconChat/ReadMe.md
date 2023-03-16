### SQL CE Demos
During earlier deveopment of SQL CE DB Ops we had this console driver program which utilizes the same source files,
- ChatRecordDB.cpp
- ChatRecordDB.h

ref, DbOperations.cpp, 12-19-2013
```cpp
#include "stdafx.h"
#include <sqlce_oledb.h>
#include <sqlce_err.h>
#include "ChatRecordDB.h"

int _tmain(int argc, _TCHAR* argv[])
{
  CoInitializeEx(NULL, COINIT_MULTITHREADED);
  CChatRecordDB charrecordobj;

  HRESULT hr = charrecordobj.CreateDatabase();
  if (SUCCEEDED(hr)) {
    hr = charrecordobj.OpenDatabase();
  }
  if (SUCCEEDED(hr)) {
    hr = charrecordobj.InsertData();
  }
  return 0;
}
```
