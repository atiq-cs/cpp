//------------------------------------------------------------------------------
//
// File: OOPCommon.h
// Common header for our Windows application
// Copyright (c) Microsoft Corporation. All rights reserved.
// 
// Author    : Atique
// Date        : November 2013
// Desc        : Includes general Windows API
//        Includes TCHAR because we use it to resolve Unicode
//        And finally includes resource header file
//------------------------------------------------------------------------------

#pragma once
// defines the platform version here, we are enabling for Windows 7 or later
// N.B: ConvertUTF16ToUTF8 uses WINVER
// #define NTDDI_VERSION NTDDI_WIN7
// #define _WIN32_WINNT _WIN32_WINNT_WIN7

#include <SDKDDKVer.h>
#include <windows.h>
#include "resource.h"
#include "MainDialog.h"

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include<tchar.h>
#include<new>

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
