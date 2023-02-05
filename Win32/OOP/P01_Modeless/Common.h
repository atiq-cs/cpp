//------------------------------------------------------------------------------
//
// File: Common.h
// Common header for our Windows application
// Copyright (c) Microsoft Corporation. All rights reserved.
// 
//------------------------------------------------------------------------------

#pragma once
// defines the platform version here, we are enabling for Windows 7 or later
// N.B: ConvertUTF16ToUTF8 uses WINVER
#define NTDDI_VERSION NTDDI_WIN7
#define _WIN32_WINNT _WIN32_WINNT_WIN7

#include <new>
#include <SDKDDKVer.h>
#include <windows.h>
#include <tchar.h>
#include "resource.h"
#include "MainDialog.h"

//
// PURPOSE: Provide most frequently used / common header files required for Win32 UI
//
// Author : Atiq Rahman
// Date   : 11-2013
// Comment: 
//   Includes TCHAR: to resolve between Unicode or MBCS / ANSI


inline HINSTANCE GetInstance()
{
    return (HINSTANCE)GetModuleHandle(NULL); 
}

// Include the v6 common controls in the manifest
#pragma comment(linker, \
    "\"/manifestdependency:type='Win32' "\
    "name='Microsoft.Windows.Common-Controls' "\
    "version='6.0.0.0' "\
    "processorArchitecture='*' "\
    "publicKeyToken='6595b64144ccf1df' "\
    "language='*'\"")
