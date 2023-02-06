## C++ Projects

### Build
**Common build instructions**  
Create Dir for Binary Executables and Objects,

    New-Item -Type Directory x64\Release

Link CL(command line) is same for MBCS (non-Unicode) and Unicode.


For MBCS (non Unicode) projects, please replace

    /D "_UNICODE" /D "UNICODE"

with

    /D "_MBCS"

in above compile CL.


Compile / link commands are presented in each directory per project type.
- Console (Win32 Console Apps also fall under this)
- Win32 (include resource compilation)
- MFC

*Win UI: yet to figure out how to build and deploy!*

In addition, command line references are provided for 2 build types
- Debug
- Release

To note about the CLs,
- CL above are based on Visual Studio 2022 (around 2023-01).
- Linker includes some OS specific libraries which might not be necessary for cross-platform C++ projects.
- CL is simplified based on file name or paths without space. Those strings need to be surrounded by quotes when space is present in them.


**Debug Builds**
For debug builds, we need to create the debug dir,

    New-Item -Type Directory x64\Debug


**Q&A**  
1. Should we generate pch files?  
Turns out latest VS CL doesn't show generation of pch files! In case we need it back, few refs,
[MSFT Compiler Docs - /Yc (Create Precompiled Header File)](https://learn.microsoft.com/en-us/cpp/build/reference/yc-create-precompiled-header-file)

2. C ++ the application has failed to start because the application configuration is incorrect? How to fix?  
This happened a few times when the .sln file was targetting "/SUBSYSTEM:Console" However, project was a Win32 App.


**Refs**  
- [MSFT Docs - Walkthrough: Compile a C program on the command line](https://learn.microsoft.com/en-us/cpp/build/walkthrough-compile-a-c-program-on-the-command-line)
- [MSFT Docs - Release Builds and Optimizations](https://learn.microsoft.com/en-us/cpp/build/release-builds)
- [GitHub C++ `.gitignore`](https://github.com/github/gitignore/blob/main/C%2B%2B.gitignore)