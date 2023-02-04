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


**Debug Builds**
For debug builds, we need to create the debug dir,

    New-Item -Type Directory x64\Debug


**Refs**  

- [GitHub C++ `.gitignore`](https://github.com/github/gitignore/blob/main/C%2B%2B.gitignore)