## Standard C++ Docs and Projects
Standard C++ (anything that is not specific to Win32/MFC etc.) Documentations are here.

### Language Resources
- *[Books and E-Books Resources](https://github.com/atiq-cs/cpp/blob/dev/Console/Books.md)*
- `std::cout` formatting examples, [MSFT - String and I/O Formatting \(Modern C++\)](https://learn.microsoft.com/en-us/cpp/text/string-and-i-o-formatting-modern-cpp)
- `std::string` ref, [MSFT - string typedef](https://learn.microsoft.com/en-us/cpp/standard-library/string-typedefs)

#### Coding Guidelines
- [reddit - Developing a C++ Coding Standard for a program](https://www.reddit.com/r/cpp/comments/62l68j)
- [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
- [Google Docs - Jialiang Ge - Microsoft All-In-One Code Framework](https://docs.google.com/document/d/1sg2G9EEp50mC5Ouu94kTkKEQxJ8K70p8/edit?usp=sharing&ouid=106507132518514033249&rtpof=true&sd=true), because all [old links to this doc](https://marketplace.visualstudio.com/items?itemName=JialiangGeMSFT.MicrosoftAll-In-OneCodeFramework) expired!
- [Geotechnical Software Services - C++ Programming Style Guidelines](https://geosoft.no/development/cppstyle.html), 01-2011
- [Tom Goodale - C/C++ Coding Guidlines](http://www.sourceformat.com/pdf/cpp-coding-standard-gridlab.pdf)

## Console Projects
Console projects are supposed to run in all platforms (Windows, Unix, Linux).

### Build Instructions
Should be followed for each project under this directory. *[Projects under "WinConsole"](https://github.com/atiq-cs/cpp/tree/dev/WinConsole) should also follow this. However, projects under WinConsole might link to additional libraries, more details on WinConsole's ReadMe.*

Build command line follows,

**Compile and Build**  
*Remember to set unicode flags if you are using unicode strings in your project.*  

Compile (MBCS / legacy / non Unicode),

    cl /c /Zi /nologo /W3 /WX- /diagnostics:column /sdl /O2 /Oi /GL /D NDEBUG /D _CONSOLE /D _MBCS /Gm- /EHsc /MD /GS /Gy /fp:precise /Zc:wchar_t /Zc:forScope /Zc:inline /permissive- /Fox64\Release\ /Fdx64\Release\vc143.pdb /external:W3 /Gd /TP /FC *.cpp

Link,

    link /OUT:x64\Release\Main.exe /NOLOGO kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /MANIFEST /MANIFESTUAC:"level='asInvoker' uiAccess='false'" /manifest:embed /DEBUG /PDB:x64\Release\Main.pdb /SUBSYSTEM:CONSOLE /OPT:REF /OPT:ICF /LTCG:incremental /LTCGOUT:x64\Release\Main.iobj /TLBID:1 /DYNAMICBASE /NXCOMPAT /IMPLIB:x64\Release\Main.lib /MACHINE:X64 x64\Release\*.obj


With typo on double quotes on the link cmd, we get errors similar to following,

    LINK : fatal error LNK1201: error writing to program database 'x64\Release\Main.pdb \SUBSYSTEM:CONSOLE \OPT:REF \OPT:ICF \LTCG:incremental \LTCGOUT:X64\RELEASE\Main.iobj \TLBID:1 \DYNAMICBASE \NXCOMPAT \IMPLIB:x64\Release\Main.lib'; check for insufficient disk space, invalid path, or insufficient privilege


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


### Standard C++
Converting numbers to strings,

```cpp
std::string itoa(int i)
{
  std::stringstream out;
  out << i;
  return out.str();
}
```

**File I/O**  
Read: Open a file, read and close,

```cpp
ifstream loadfile;
loadfile.open("comptime.cnt");

if (!loadfile.fail()) {
  loadfile >> elapsedtime;
  loadfile >> starttime;
}

loadfile.close();
```

Write: Open a file, write and close,

```cpp
ofstream of;
of.open("comptime.cnt");
of << elapsedtime;
of << "\n";
of << starttime;
of.close();
```
