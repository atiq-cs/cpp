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

Icons are set during RegisterClass,

```cpp
wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAIN_APP));
wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
```

Additionally, we set the icon file using .rc file,

    // Icon with lowest ID value placed first to ensure application icon
    // remains consistent on all systems.
    IDI_MAIN_APP       ICON         "Main.ico"
    IDI_SMALL          ICON         "small.ico"

And the IDs are defined in resource.h



**Adding Menu**  
We specify the menu resource in during Window class registration,

```cpp
wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MAIN_APP);
```

We add the MENU entries in .rc file with same ID as above `IDC_MAIN_APP`,

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
We add the Version Info in .rc file to add application information to its executable file. Please have a look at the section starting with line

    1 VERSIONINFO

in [Main.rc](https://github.com/atiq-cs/cpp/blob/dev/Win32/Tutorials/T02_VS_and_Menu/Main.rc).

Please feel free to change the information strings above according to your need. More details on `versioninfo` resource on [MSFT Doc - versioninfo](https://learn.microsoft.com/en-us/windows/win32/menurc/versioninfo-resource).

*Screenshot after embedding Version Info*  
  
![Version Info](https://user-images.githubusercontent.com/7858031/218615298-26b3db65-815b-4e37-8aae-eee83d2a01c7.png)


**Icon Resources**  
[icon-icons.com](https://icon-icons.com/download/144865/ICO/48/) seems to have 3.00 ICO format icons that work properly.