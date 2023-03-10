### NSIS Installer Basics
Starter file is *BasicExample.nsi*.

**Modifications**  
- ';' replaced with '#'
- Registry section updated
- Start Menu options added
- Uninstaller files listed including deleting reg keys

The first version of installer looks like below, *ref, 04-18-2011*,

    #NSIS Modern User Interface
    #Basic Example Script
    #Written by Joost Verburg

    #--------------------------------
    #Include Modern UI

      !include "MUI2.nsh"

    #--------------------------------
    #General

      #Name and file
      Name "iQubit PingGUI"
      OutFile "PingGUI_Setup.exe"

      #Default installation folder
      InstallDir "$PROGRAMFILES\PingGUI"
      
      #Get installation folder from registry if available
      InstallDirRegKey HKCU "Software\PingGUI" ""

      #Request application privileges for Windows Vista
      RequestExecutionLevel admin
      
      #--------------------------------
      #Variables
      Var StartMenuFolder

    #--------------------------------
    #Interface Settings

      !define MUI_ABORTWARNING

    #--------------------------------
    #Pages

      !insertmacro MUI_PAGE_LICENSE "${NSISDIR}\Docs\Modern UI\License.txt"
      !insertmacro MUI_PAGE_COMPONENTS
      !insertmacro MUI_PAGE_DIRECTORY
      #Start Menu Folder Page Configuration
      !define MUI_STARTMENUPAGE_REGISTRY_ROOT "HKCU" 
      !define MUI_STARTMENUPAGE_REGISTRY_KEY "Software\PingGUI" 
      !define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "Start Menu Folder"
      
      !insertmacro MUI_PAGE_STARTMENU Application $StartMenuFolder

      !insertmacro MUI_PAGE_INSTFILES
      
      !insertmacro MUI_UNPAGE_CONFIRM
      !insertmacro MUI_UNPAGE_INSTFILES
      
    #--------------------------------
    #Languages
    
      !insertmacro MUI_LANGUAGE "English"

    #--------------------------------
    #Installer Sections

    Section "PingGUI" SAInstall

      SetOutPath "$INSTDIR"
      
      #ADD YOUR OWN FILES HERE...
      # define what to install and place it in the output path
      file mfc100u.dll
      file msvcr100.dll
      file PingGUI.exe
      
      #Store installation folder
      WriteRegStr HKCU "Software\PingGUI" "" $INSTDIR
      
      #Create uninstaller
      WriteUninstaller "$INSTDIR\Uninstall.exe"
      
        !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
        
        ;Create shortcuts
        CreateDirectory "$SMPROGRAMS\$StartMenuFolder"
      CreateShortCut "$SMPROGRAMS\$StartMenuFolder\PingGUI.lnk" "$INSTDIR\PingGUI.exe"
        CreateShortCut "$SMPROGRAMS\$StartMenuFolder\Uninstall.lnk" "$INSTDIR\Uninstall.exe"
      
      !insertmacro MUI_STARTMENU_WRITE_END


    SectionEnd

    #--------------------------------
    #Descriptions

      #Language strings
      LangString DESC_SAInstall ${LANG_ENGLISH} "A test section."

      #Assign language strings to sections
      !insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
        !insertmacro MUI_DESCRIPTION_TEXT ${SAInstall} $(DESC_SAInstall)
      !insertmacro MUI_FUNCTION_DESCRIPTION_END

    #--------------------------------
    #Uninstaller Section

    Section "Uninstall"

      #ADD YOUR OWN FILES HERE...
      Delete "$INSTDIR\PingGUI.exe"
      Delete "$INSTDIR\mfc100u.dll"
      Delete "$INSTDIR\msvcr100.dll"
      Delete "$INSTDIR\Uninstall.exe"

      RMDir "$INSTDIR"

      !insertmacro MUI_STARTMENU_GETFOLDER Application $StartMenuFolder

      Delete "$SMPROGRAMS\$StartMenuFolder\PingGUI.lnk"
      Delete "$SMPROGRAMS\$StartMenuFolder\Uninstall.lnk"
      RMDir "$SMPROGRAMS\$StartMenuFolder"


      DeleteRegKey /ifempty HKCU "Software\PingGUI"

    SectionEnd