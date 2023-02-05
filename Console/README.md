### Console Projects  
Should be followed for each project under this directory.

Hence the build command line follows like below,

**Compile and Build**  
Compile (MBCS / legacy / non Unicode),

    cl /c /Zi /nologo /W3 /WX- /diagnostics:column /sdl /O2 /Oi /GL /D NDEBUG /D _CONSOLE /D _MBCS /Gm- /EHsc /MD /GS /Gy /fp:precise /Zc:wchar_t /Zc:forScope /Zc:inline /permissive- /Fox64\Release\ /Fdx64\Release\vc143.pdb /external:W3 /Gd /TP /FC *.cpp

Link,

    link /OUT:x64\Release\Main.exe /NOLOGO kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /MANIFEST /MANIFESTUAC:"level='asInvoker' uiAccess='false'" /manifest:embed /DEBUG /PDB:x64\Release\Main.pdb" /SUBSYSTEM:CONSOLE /OPT:REF /OPT:ICF /LTCG:incremental /LTCGOUT:"X64\RELEASE\Main.iobj" /TLBID:1 /DYNAMICBASE /NXCOMPAT /IMPLIB:x64\Release\Main.lib" /MACHINE:X64 x64\Release\*.obj


#### Original Reference Build Configurations
From Project Configuration Properties of VS 2022,

**Release Builds**  
Compile,

    /permissive- /ifcOutput "x64\Release\" /GS /GL /W3 /Gy /Zc:wchar_t /Zi /Gm- /O2 /sdl /Fd"x64\Release\vc143.pdb" /Zc:inline /fp:precise /D "NDEBUG" /D "_CONSOLE" /D "_UNICODE" /D "UNICODE" /errorReport:prompt /WX- /Zc:forScope /Gd /Oi /MD /FC /Fa"x64\Release\" /EHsc /nologo /Fo"x64\Release\" /Fp"x64\Release\Main.pch" /diagnostics:column

Link,

    /OUT:x64\Release\Main.exe /MANIFEST /LTCG:incremental /NXCOMPAT /PDB:x64\Release\Main.pdb /DYNAMICBASE "kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "odbc32.lib" "odbccp32.lib" /DEBUG /MACHINE:X64 /OPT:REF /PGD:x64\Release\Main.pgd /SUBSYSTEM:CONSOLE /MANIFESTUAC:"level='asInvoker' uiAccess='false'" /ManifestFile:"x64\Release\Main.exe.intermediate.manifest" /LTCGOUT:"x64\Release\Main.iobj" /OPT:ICF /ERRORREPORT:PROMPT /ILK:"x64\Release\Main.ilk" /NOLOGO /TLBID:1


*Pre processor definitions*
Preprocess defs from VS Properities,

    NDEBUG;_CONSOLE; % (PreprocessorDefinitions)

Not required to define these as long as flags with cl are provided.

```cpp
#define NDEBUG
#define _CONSOLE
```

**Debug Builds Ref CL**  
Compile,

    /JMC /permissive- /ifcOutput x64\Debug\ /GS /W3 /Zc:wchar_t /ZI /Gm- /Od /sdl /Fdx64\Debug\vc143.pdb /Zc:inline /fp:precise /D "_DEBUG" /D "_CONSOLE" /D "_UNICODE" /D "UNICODE" /errorReport:prompt /WX- /Zc:forScope /RTC1 /Gd /MDd /FC /Fax64\Debug\ /EHsc /nologo /Fox64\Debug\ /Fpx64\Debug\Main.pch /diagnostics:column

Link,

    /OUT:x64\Debug\Main.exe /MANIFEST /NXCOMPAT /PDB:x64\Debug\Main.pdb /DYNAMICBASE "kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "odbc32.lib" "odbccp32.lib" /DEBUG /MACHINE:X64 /INCREMENTAL /PGD:x64\Debug\Main.pgd /SUBSYSTEM:CONSOLE /MANIFESTUAC:"level='asInvoker' uiAccess='false'" /ManifestFile:x64\Debug\Main.exe.intermediate.manifest /LTCGOUT:x64\Debug\Main.iobj /ERRORREPORT:PROMPT /ILK:x64\Debug\Main.ilk /NOLOGO /TLBID:1 


**pre compile headers**
*not required for most projects*, here, for reference,

    cl /EHsc /nologo /Yc /c *.cpp /Fp"x64\Release\Main.pch" /Fox64\Release\

**Refs**
In case we need profiling back,
- For PGD i.e., `/FASTGENPROFILE`, [MSFT Learn](https://learn.microsoft.com/en-us/cpp/build/reference/pgd-specify-database-for-profile-guided-optimizations)
