// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__970E5960_5209_4AE7_8DD2_ACD4C1165941__INCLUDED_)
#define AFX_STDAFX_H__970E5960_5209_4AE7_8DD2_ACD4C1165941__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT
#ifndef _WIN32_WINNT
// We target Windows 7 at least
//  ref, https://learn.microsoft.com/en-us/windows/win32/winprog/using-the-windows-headers

// further ref,
//  http://code.ohloh.net/file?fid=zF6HfPYdvMh1MhOx1zgI1-1D9FQ&cid=wZKBjpj2Txs&s=&browser=Default&fp=400454&mpundefined&projSelected=true#L0
// #define _WIN32_WINNT _WIN32_WINNT_WIN8
#define _WIN32_WINNT _WIN32_WINNT_WIN7
#endif
#define _ATL_APARTMENT_THREADED

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>
#include <ocidl.h>  // Added by ClassView

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__970E5960_5209_4AE7_8DD2_ACD4C1165941__INCLUDED)
