## Win32 Apps Classic (before Win UI)
Listing,  
- [MSFT Docs - Coding Style Conventions for C++/Win32](https://learn.microsoft.com/en-us/windows/win32/stg/coding-style-conventions)
- [Windows SDK and Visual Studio Samples](https://github.com/atiq-cs/cpp/blob/dev/Win32/Samples.md)
- RegisterClass previous versions are on [RegisterClass doc](https://github.com/atiq-cs/cpp/blob/dev/Win32/RegisterClass.md).  
- [Win32 / Network Programming Ref](../MFC/P03_ICMP/)

Projects under this directory are targeted toward Windows. Not tested on Linux Wine yet!  

*Windows Classic Apps (raw Win32 C++)!*  **Danger ☠️ !!  Proceed with Caution!!**

**Compile and Build**  
*Resource compilation*,  
Assuming resource file is named 'Main.rc',

    rc /D _UNICODE /D UNICODE /l"0x0409" /nologo /fox64\Release\Main.res Main.rc

*Compile (Unicode)*,

    cl /c /Zi /nologo /W4 /WX /diagnostics:column /O2 /GL /D WIN32 /D NDEBUG /D _WINDOWS /D _UNICODE /D UNICODE /Gm- /EHsc /MD /GS /fp:precise /Zc:wchar_t /Zc:forScope /Zc:inline /Fox64\Release\ /Fdx64\Release\vc143.pdb /external:W4 /Gd /TP /FC *.cpp

*Link*,

    link /OUT:x64\Release\Main.exe /INCREMENTAL:NO /NOLOGO mfplat.lib mf.lib mfuuid.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /MANIFEST /MANIFESTUAC:"level='asInvoker' uiAccess='false'" /manifest:embed /DEBUG /PDB:x64\Release\vc143.pdb /SUBSYSTEM:WINDOWS /OPT:REF /OPT:ICF /LTCG:incremental /LTCGOUT:x64\Release\Main.iobj /TLBID:1 /DYNAMICBASE:NO /IMPLIB:x64\Release\Main.lib /MACHINE:X64 x64\Release\Main.res x64\Release\*.obj


Additional customizations (common) are at [parent wiki](https://github.com/atiq-cs/cpp/blob/dev/README.md).

**32 bit build**  
Based on [WMP Plugin](./P21_WMPSubtitlePlugin/) dll project,  
For 32 bit builds, we add following additional args with cl,

    /Oy- /analyze-

With linker cmd, we add,

    /SAFESEH

And, change target platform if 64 bit was specified,

    /MACHINE:X86

### Win32 Samples
- CppSendWM_COPYDATA: C++ Windows app uses `WM_COPYDATA` for IPC (CppSendWM_COPYDATA) available on [GitHub - msdn-code-gallery-microsoft](https://github.com/microsoftarchive/msdn-code-gallery-microsoft/tree/master/OneCodeTeam/C%2B%2B%20Windows%20app%20uses%20WM_COPYDATA%20for%20IPC%20\(CppSendWM_COPYDATA\))


**Q&A**  
1. Should we generate pch files?  
Turns out latest VS CL doesn't show generation of pch files! In case we need it back, few refs,
[MSFT Compiler Docs - /Yc (Create Precompiled Header File)](https://learn.microsoft.com/en-us/cpp/build/reference/yc-create-precompiled-header-file)

2. C ++ the application has failed to start because the application configuration is incorrect? How to fix?  
 This happened a few times when the .sln file was targetting "/SUBSYSTEM:Console" However, project was a Win32 App.
