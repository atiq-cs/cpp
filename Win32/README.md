## Win32 Apps Classic (before Win UI)
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