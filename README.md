## C++ Projects

### Generalized Build Instructions
**Setup output directory**  
First step is to create Dir for holding Binary Executables and Objects,

    New-Item -Type Directory x64\Release

**Release Build**  
In this high level ReadMe doc, we don't provide the exact command lines, only provide customizations.

Compile / link commands are presented in each directory per project type.
- Console (Win32 Console Apps also fall under this)
- Win32 (include resource compilation)
- MFC

Compile CL changes slight based on MBCS vs Unicode.

For MBCS (non Unicode) projects, please replace

    /D "_UNICODE" /D "UNICODE"

with

    /D "_MBCS"

in above compile CL.

Link CL (command line) is same for MBCS (non-Unicode) and Unicode.


*Win UI: yet to figure out how to build and deploy!*

To note about the CLs provided in each dir,
- CL above are based on Visual Studio 2022 (around 2023-01).
- Linker includes some OS specific libraries which might not be necessary for cross-platform C++ projects.
- CL is simplified based on file name or paths without space. Those strings need to be surrounded by quotes when space is present in them.


As per experience, cl, the compiler binary reports correct line number when an error is encountered,

    $ cl /c /Zi /nologo /W4 /WX /diagnostics:column /O2 /GL /D WIN32 /D NDEBUG /D _WINDOWS /D _UNICODE /D UNICODE /Gm- /EHsc /MD /GS /fp:precise /Zc:wchar_t /Zc:forScope /Zc:inline /Fox64\Release\ /Fdx64\Release\vc143.pdb /external:W4 /Gd /TP /FC *.cpp

    Main.cpp
    
    cpp_all\Win32\OOP\P03_Wnd\Main.cpp(66,1): error C2220: the following warning is treated as an error
    cpp_all\Win32\OOP\P03_Wnd\Main.cpp(57,1): note: while compiling class template member function 'BOOL BaseWindow<MainWindow>::Create(PCWSTR,DWORD,DWORD,int,int,int,int,HWND,HMENU)'
    cpp_all\Win32\OOP\P03_Wnd\Main.cpp(183,3): note: see reference to function template instantiation 'BOOL BaseWindow<MainWindow>::Create(PCWSTR,DWORD,DWORD,int,int,int,int,HWND,HMENU)' being compiled
    cpp_all\Win32\OOP\P03_Wnd\Main.cpp(128,1): note: see reference to class template instantiation 'BaseWindow<MainWindow>' being compiled
    cpp_all\Win32\OOP\P03_Wnd\Main.cpp(66,1): warning C4302: 'type cast': truncation from 'LPWSTR' to 'WORD'


There was indeed an incorrect conversion in following in line 66,

    wcex.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));


Hence, there is no reason to distrust the compiler.

Command line references are provided for 2 build types,
- Debug
- Release


**Debug Builds**  
For debug builds, we need to create the debug dir,

    New-Item -Type Directory x64\Debug


**Refs**  
- [MSFT Docs - Walkthrough: Compile a C program on the command line](https://learn.microsoft.com/en-us/cpp/build/walkthrough-compile-a-c-program-on-the-command-line)
- [MSFT Docs - Release Builds and Optimizations](https://learn.microsoft.com/en-us/cpp/build/release-builds)


**gitignore Refs**  
- '.gitignore': [GitHub C++ `.gitignore`](https://github.com/github/gitignore/blob/main/C%2B%2B.gitignore)
- Single vs double asterisks, [henriquesd - The .gitignore File](https://henriquesd.medium.com/the-gitignore-file-dc293f6c80fb)
- old repo, [OOP-Win32-CPP/.gitignore](https://github.com/atiq-cs/cpp/blob/dev/Win32/git_ignore.md)