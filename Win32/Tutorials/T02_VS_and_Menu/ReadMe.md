### Tutorial 2 - Enabling Visual Style, Adding Menu and Version Info
All of these are done via adding resource file to the project. Which means compiling resource file and adding the .res file during compile.

**Enabling Visual Style**  
Need to research if we still need manifest file to enable visual style.

Also, our cl command line provided in [Win32 Main ReadMe](../../) doesn't cover how to add a manifest file in command line yet!

We add a manifest file and add that during compilation,

    <?xml version="1.0" encoding="UTF-8" standalone="yes"?>
    <assembly xmlns="urn:schemas-microsoft-com:asm.v1" manifestVersion="1.0">
    <assemblyIdentity
        version="1.0.0.0"
        processorArchitecture="X86"
        name="First Flush.Utilities.BCG"
        type="win32"
    />
    <description>This application generates html code for blogger etc posts</description>
    <dependency>
        <dependentAssembly>
            <assemblyIdentity
                type="win32"
                name="Microsoft.Windows.Common-Controls"
                version="6.0.0.0"
                processorArchitecture="X86"
                publicKeyToken="6595b64144ccf1df"
                language="*"
            />
        </dependentAssembly>
    </dependency>
    </assembly>

*Screenshot before enabling Visual Style*  
  
![Tutorial 2 App without VS Style](https://user-images.githubusercontent.com/7858031/218615364-be83dd7b-cb43-48aa-8002-1ad34586b605.png)

*Screenshot after enabling Visual Style*  
  
![Tutorial 2 App with VS Style](https://user-images.githubusercontent.com/7858031/218615483-4c3a45d6-c797-4f06-a3cf-59731cccfaaf.png)

Additionally, we set the icon file using .rc file,

    // Icon with lowest ID value placed first to ensure application icon
    // remains consistent on all systems.
    IDI_MAIN_APP       ICON         "Main.ico"
    IDI_SMALL          ICON         "small.ico"


**Adding Menu**  
We add the MENU entries in .rc file,

    IDC_MAIN_APP MENU
    BEGIN
        POPUP "&File"
        BEGIN
            MENUITEM "E&xit",                IDM_EXIT
        END
        POPUP "&Help"
        BEGIN
            MENUITEM "&About ...",           IDM_ABOUT
        END
    END


**Adding Version Info**  
We add the Version Info in .rc file to add application information on its executable file,

    // Microsoft Visual C++ generated resource script.
    //
    #include "resource.h"
    #include "afxres.h"

    /////////////////////////////////////////////////////////////////////////////
    //
    // Version
    //

    1 VERSIONINFO
    FILEVERSION 1,0,0,0
    PRODUCTVERSION 1,0,0,0
    FILEFLAGSMASK 0x0L
    #ifdef _DEBUG
    FILEFLAGS 0x1L
    #else
    FILEFLAGS 0x0L
    #endif
    FILEOS 0x0L
    FILETYPE 0x1L
    FILESUBTYPE 0x0L
    BEGIN
        BLOCK "StringFileInfo"
        BEGIN
            BLOCK "040904e4"
            BEGIN
                VALUE "Comments", "This program adds version info and enables VS Style"
                VALUE "CompanyName", "FFTSys Inc."
                VALUE "FileDescription", "Tutorial 2 Executable"
                VALUE "FileVersion", "1.0"
                VALUE "InternalName", "Tutorial 2"
                VALUE "LegalCopyright", "FFTSys (c) 2023"
                VALUE "LegalTrademarks", "FFTSys Inc."
                VALUE "OriginalFilename", "CoolApp.exe"
                VALUE "ProductName", "FFTSys Cool App"
                VALUE "ProductVersion", "1.0"
            END
        END
        BLOCK "VarFileInfo"
        BEGIN
            VALUE "Translation", 0x409, 1252
        END
    END


Please feel free to change the information strings above according to your need. More details on `versioninfo` resource on [MSFT Doc - versioninfo](https://learn.microsoft.com/en-us/windows/win32/menurc/versioninfo-resource).

*Screenshot after embedding Version Info*  
  
![Version Info](https://user-images.githubusercontent.com/7858031/218615298-26b3db65-815b-4e37-8aae-eee83d2a01c7.png)


**Icon Resources**  
[icon-icons.com](https://icon-icons.com/download/144865/ICO/48/) seems to have 3.00 ICO format icons that work properly.