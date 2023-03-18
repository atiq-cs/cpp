## Unicode Conversions Best Practices
Examples of incorrect unicode conversions and how to correct them,

1. Incorrect cast,  
  
from `CString` to `unsigned char*`,  

    (unsigned char*) (LPCTSTR)

Correct conversion from `CString` to `unsigned char*` should be

    (unsigned char*) (LPCSTR) CStringA(...)

2. Incorrect cast,
from `CString` to `char *`,

    (char*) (LPCTSTR)

Correct conversion from `CString` to `char *` should be,

    (LPCSTR) CStringA(...)

However, this won't work,

    unsigned char* pszStrCorrectCast = (unsigned char*) (LPCSTR) CStringA(csName);
    // buffer out of scope as deallocated
    _tprintf(_T("char pointer correct cast content but inavlid pointer: \"%S\"\n"),
      pszStrCorrectCast);

3. Incorrect cast,  
from `CString` to `char *`,

    (char*) (LPCTSTR)

Correct conversion from `CString` to `char *` should be,

    (LPCSTR) CStringA(...)

4. Incorrect cast,  
from `CString` to `char *`,  

    (char*) (LPCTSTR)

When Unicode is defined `LPCTSTR` tranlates to Unicode version: `LPWSTR` instead of `LPSTR` which was previously cast from `unsigned char *` in this project,
Correct conversion from `CString` to `char *` should be,

    (char*) (LPCSTR) CStringA(...)

5. More conversion example to convert the right way,  
  
Assigning `unsigned char *` to `CString` example,

    CString s((LPCSTR) buddy.buddyName);

CStringA, LPCSTR  to CString

    CString(...)

CString, LPCTSTR  to CStringA

    CStringA(...)

CString to LPTSTR 

    CStringA(...)

Unicode String Literal,

    TEXT("THE_STRING_LITERAL");

For, `strcpy`,

    (LPCSTR)
    (LPCTSTR) CString(...)
    (LPTSTR) (LPCTSTR) CString(...)

Assign a char* to CString,

    (LPCSTR) 

to convert CString to char *,

    (LPCSTR) CStringA(cs));
  
Conversion from `unsigned char` to LPTSTR, CString to `LPWSTR`,

    hdi.pszText = (LPTSTR) (LPCTSTR) column.m_heading;
  
**Conversion examples from MSDN**  
[MSFT - How to: Convert between various string types](https://learn.microsoft.com/en-us/cpp/text/how-to-convert-between-various-string-types)

`CString` is convenient and does the heavy lifting of converting legacy c string to Unicode.
When `CString` is not available, non-MFC use case, `mbstowcs_s` is the way to go,

```cpp
char *orig = "Hello, World!";
wchar_t * wcstring = new wchar_t[newsize];

// Convert char* string to a wchar_t* string.
size_t convertedChars = 0;
mbstowcs_s(&convertedChars, wcstring, newsize, orig, _TRUNCATE);
```

Reverse conversion function of `mbstowcs_s` is `wcstombs_s`.

Usage example,
```cpp
wchar_t *orig = _T("Hello, World!");
size_t origsize = wcslen(orig) + 1;
const size_t newsize = origsize*2;
char *nstring = new char[newsize];
wcstombs_s(&convertedChars, nstring, newsize, orig, _TRUNCATE);
```

6. In addition, be careful about using `%S` in `CStringA::Format(...)`

ref, *Conversion_from_unicode.docx*, 01-12-2014

A demo program from *01-12-2014* to catch wrong casts,

```cpp
int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
  int nRetCode = 0;
  // Previous coder have done many casts from CString to unsigned char*
  CString csName = TEXT("A CString object");
  // part 1: proves that CString to unsigned char* is wrong
  unsigned char* pszStrWrongCast = (unsigned char*) (LPCTSTR) csName;

  _tprintf(_T("cstring content: \"%s\"\n"), csName);
  _tprintf(_T("char pointer wrong cast content: \"%S\"\n"), pszStrWrongCast);

  unsigned char* pszStrCorrectCast = (unsigned char*) (LPCSTR) CStringA(csName);
  // buffer out of scope as deallocated
  _tprintf(_T("char pointer correct cast content but inavlid pointer: \"%S\"\n"), pszStrCorrectCast);
  // CStringA csaName(csName);
  // _tprintf(_T("char pointer correct cast content: \"%S\"\n"), (unsigned char*) (LPCSTR) CStringA(csName));

  CStringA csaName(csName);
  pszStrCorrectCast = (unsigned char*) (LPCSTR) csaName;
  _tprintf(_T("char pointer correct cast content: \"%S\"\n"), pszStrCorrectCast);

  return nRetCode;
}
```


**Appendix**  
Regular expression replace strings,

    Find "(= ")(.*)(")"
    Replace with = TEXT("$2")

Find patterns,

    (= ")(.*)(")

