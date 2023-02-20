### MFC Apps
3 steps to build.

*Resource compilation*,  
Assuming resource file is named 'Main.rc',  
Compared to Win32 App Build, add,

    /D NDEBUG /D _AFXDLL

Full cmd,

    rc /D NDEBUG /D _UNICODE /D UNICODE /D _AFXDLL /l"0x0409" /nologo /fox64\Release\Main.res Main.rc

**Compile (Unicode)**  
In addition, pch and few flags added,

    cl /c /Zi /nologo /W3 /WX- /diagnostics:column /sdl /O2 /Oi /GL /D NDEBUG /D _WINDOWS /D _UNICODE /D UNICODE /D _AFXDLL /Gm- /EHsc /MD /GS /Gy /fp:precise /Zc:wchar_t /Zc:forScope /Zc:inline /Yu"pch.h" /Fpx64\Release\Main.pch /Fox64\Release\ /Fdx64\Release\vc143.pdb /external:W3 /Gd /TP /FC *.cpp

*TODO: check on pch file*

**Link**  
Compared to Win32 App Build, manifest added, libs are removed,

    link /OUT:x64\Release\Main.exe /INCREMENTAL:NO /NOLOGO /MANIFEST /MANIFESTUAC:"level='asInvoker' uiAccess='false'" /manifest:embed /manifestinput:%VCToolsInstallDir%\INCLUDE\MANIFEST\DPIAWARE.MANIFEST /DEBUG:FULL /PDB:x64\Release\Main.pdb /SUBSYSTEM:WINDOWS /OPT:REF /OPT:ICF /LTCG:incremental /LTCGOUT:x64\Release\Main.iobj /TLBID:1 /ENTRY:"wWinMainCRTStartup" /DYNAMICBASE /NXCOMPAT /IMPLIB:x64\Release\Main.lib /MACHINE:X64 x64\Release\Main.res x64\Release\*.obj

