#NSIS Modern User Interface
#Installer script adapted from Basic Example
#Written by Joost Verburg

# Date: 01-18-2014

#--------------------------------
#Include Modern UI

  !include "MUI2.nsh"

#--------------------------------
#General

  #Name and file
  Name "iQubit PingGUI"
  OutFile "PingGUI_installer.exe"
  
  # added to include info on exectuable
  ;=== Program Details
  Icon "F:\git_ws\pinggui\_old_code\res\favicon.ico"
  Caption "iQubit PingGUI"
  VIProductVersion 1.0.1.41
  VIAddVersionKey ProductName "iQubit PingGUI"
  VIAddVersionKey Comments "A compiler for custom iQubit Launcher builds. For additional details, visit iQubit"
  VIAddVersionKey CompanyName iQubit
  VIAddVersionKey LegalCopyright iQubit
  VIAddVersionKey FileDescription "iQubit PingGUI"
  VIAddVersionKey FileVersion 1.0.1.41
  VIAddVersionKey ProductVersion 1.0.1.41
  VIAddVersionKey InternalName "iQubit PingGUI"
  VIAddVersionKey LegalTrademarks "Ping GUI is a Trademark of iQubit, Inc."
  VIAddVersionKey OriginalFilename PingGUI.exe

  #Default installation folder
  InstallDir "$PROGRAMFILES\PingGUI"
  
  #Get installation folder from registry if available
  InstallDirRegKey HKCU "Software\PingGUI" ""
  
  #Change Default Installer and Uninstaller Icons
  !define MUI_ICON "F:\git_ws\pinggui\_old_code\res\favicon.ico"
  !define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall-blue.ico"

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

Section "PingGUI" AppInstall

  SetOutPath "$INSTDIR"
  
  #ADD YOUR OWN FILES HERE...
  # define what to install and place it in the output path
  file mfc120u.dll
  file msvcr120.dll
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
  LangString DESC_AppInstall ${LANG_ENGLISH} "A test section."

  #Assign language strings to sections
  !insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
    !insertmacro MUI_DESCRIPTION_TEXT ${AppInstall} $(DESC_AppInstall)
  !insertmacro MUI_FUNCTION_DESCRIPTION_END

#--------------------------------
#Uninstaller Section

Section "Uninstall"

  #ADD YOUR OWN FILES HERE...
  Delete "$INSTDIR\PingGUI.exe"
  Delete "$INSTDIR\mfc120u.dll"
  Delete "$INSTDIR\msvcr120.dll"
  Delete "$INSTDIR\Uninstall.exe"

  RMDir "$INSTDIR"

  !insertmacro MUI_STARTMENU_GETFOLDER Application $StartMenuFolder

  Delete "$SMPROGRAMS\$StartMenuFolder\PingGUI.lnk"
  Delete "$SMPROGRAMS\$StartMenuFolder\Uninstall.lnk"
  RMDir "$SMPROGRAMS\$StartMenuFolder"


  DeleteRegKey /ifempty HKCU "Software\PingGUI"

SectionEnd