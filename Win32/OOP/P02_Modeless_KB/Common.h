//------------------------------------------------------------------------------
//
// File: Common.h
// Common header for our Windows application
// Copyright (c) Microsoft Corporation. All rights reserved.
// 
//------------------------------------------------------------------------------

#pragma once

// N.B: ConvertUTF16ToUTF8 uses WINVER
#define NTDDI_VERSION NTDDI_WIN7
#define _WIN32_WINNT _WIN32_WINNT_WIN7

#include <SDKDDKVer.h>
#include <windows.h>
#include "resource.h"
#include "MainDialog.h"

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <new>

//
// PURPOSE: Provide most frequently used / common header files required for Win32 UI
//
// Comment: Includes,
//  - TCHAR: to resolve between Unicode or MBCS / ANSI
//  - Resource header file



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
