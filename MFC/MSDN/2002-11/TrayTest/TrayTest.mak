# Microsoft Developer Studio Generated NMAKE File, Based on TrayTest.dsp
!IF "$(CFG)" == ""
CFG=TrayTest - Win32 Release
!MESSAGE No configuration specified. Defaulting to TrayTest - Win32 Release.
!ENDIF

!IF "$(CFG)" != "TrayTest - Win32 Release" && "$(CFG)" != "TrayTest - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE
!MESSAGE NMAKE /f "TrayTest.mak" CFG="TrayTest - Win32 Release"
!MESSAGE
!MESSAGE Possible choices for configuration are:
!MESSAGE
!MESSAGE "TrayTest - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "TrayTest - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE
!ERROR An invalid configuration is specified.
!ENDIF

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF

!IF  "$(CFG)" == "TrayTest - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\TrayTest.exe" "$(OUTDIR)\TrayTest.bsc"


CLEAN :
  -@erase "$(INTDIR)\Mainfrm.obj"
  -@erase "$(INTDIR)\Mainfrm.sbr"
  -@erase "$(INTDIR)\StatLink.obj"
  -@erase "$(INTDIR)\StatLink.sbr"
  -@erase "$(INTDIR)\Stdafx.obj"
  -@erase "$(INTDIR)\Stdafx.sbr"
  -@erase "$(INTDIR)\Subclass.obj"
  -@erase "$(INTDIR)\Subclass.sbr"
  -@erase "$(INTDIR)\TrayIcon.obj"
  -@erase "$(INTDIR)\TrayIcon.sbr"
  -@erase "$(INTDIR)\TrayTest.obj"
  -@erase "$(INTDIR)\TrayTest.pch"
  -@erase "$(INTDIR)\TrayTest.res"
  -@erase "$(INTDIR)\TrayTest.sbr"
  -@erase "$(INTDIR)\vc60.idb"
  -@erase "$(OUTDIR)\TrayTest.bsc"
  -@erase "$(OUTDIR)\TrayTest.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\TrayTest.pch" /Yu"STDAFX.H" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $<
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $<
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $<
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $<
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $<
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $<
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\TrayTest.res" /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TrayTest.bsc"
BSC32_SBRS= \
  "$(INTDIR)\Mainfrm.sbr" \
  "$(INTDIR)\StatLink.sbr" \
  "$(INTDIR)\Stdafx.sbr" \
  "$(INTDIR)\Subclass.sbr" \
  "$(INTDIR)\TrayIcon.sbr" \
  "$(INTDIR)\TrayTest.sbr"

"$(OUTDIR)\TrayTest.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=oldnames.lib /nologo /stack:0x2800 /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\TrayTest.pdb" /machine:IX86 /out:"$(OUTDIR)\TrayTest.exe"
LINK32_OBJS= \
  "$(INTDIR)\Mainfrm.obj" \
  "$(INTDIR)\StatLink.obj" \
  "$(INTDIR)\Stdafx.obj" \
  "$(INTDIR)\Subclass.obj" \
  "$(INTDIR)\TrayIcon.obj" \
  "$(INTDIR)\TrayTest.obj" \
  "$(INTDIR)\TrayTest.res"

"$(OUTDIR)\TrayTest.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "TrayTest - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\TrayTest.exe"


CLEAN :
  -@erase "$(INTDIR)\Mainfrm.obj"
  -@erase "$(INTDIR)\StatLink.obj"
  -@erase "$(INTDIR)\Stdafx.obj"
  -@erase "$(INTDIR)\Subclass.obj"
  -@erase "$(INTDIR)\TrayIcon.obj"
  -@erase "$(INTDIR)\TrayTest.obj"
  -@erase "$(INTDIR)\TrayTest.pch"
  -@erase "$(INTDIR)\TrayTest.res"
  -@erase "$(INTDIR)\vc60.idb"
  -@erase "$(INTDIR)\vc60.pdb"
  -@erase "$(OUTDIR)\TrayTest.exe"
  -@erase "$(OUTDIR)\TrayTest.ilk"
  -@erase "$(OUTDIR)\TrayTest.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\TrayTest.pch" /Yu"STDAFX.H" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $<
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $<
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $<
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $<
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $<
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $<
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\TrayTest.res" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TrayTest.bsc"
BSC32_SBRS= \
 
LINK32=link.exe
LINK32_FLAGS=oldnames.lib /nologo /stack:0x2800 /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\TrayTest.pdb" /debug /machine:IX86 /out:"$(OUTDIR)\TrayTest.exe"
LINK32_OBJS= \
  "$(INTDIR)\Mainfrm.obj" \
  "$(INTDIR)\StatLink.obj" \
  "$(INTDIR)\Stdafx.obj" \
  "$(INTDIR)\Subclass.obj" \
  "$(INTDIR)\TrayIcon.obj" \
  "$(INTDIR)\TrayTest.obj" \
  "$(INTDIR)\TrayTest.res"

"$(OUTDIR)\TrayTest.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("TrayTest.dep")
!INCLUDE "TrayTest.dep"
!ELSE
!MESSAGE Warning: cannot find "TrayTest.dep"
!ENDIF
!ENDIF


!IF "$(CFG)" == "TrayTest - Win32 Release" || "$(CFG)" == "TrayTest - Win32 Debug"
SOURCE=.\Mainfrm.cpp

!IF  "$(CFG)" == "TrayTest - Win32 Release"


"$(INTDIR)\Mainfrm.obj"  "$(INTDIR)\Mainfrm.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TrayTest.pch"


!ELSEIF  "$(CFG)" == "TrayTest - Win32 Debug"


"$(INTDIR)\Mainfrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TrayTest.pch"


!ENDIF

SOURCE=.\StatLink.cpp

!IF  "$(CFG)" == "TrayTest - Win32 Release"


"$(INTDIR)\StatLink.obj"  "$(INTDIR)\StatLink.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TrayTest.pch"


!ELSEIF  "$(CFG)" == "TrayTest - Win32 Debug"


"$(INTDIR)\StatLink.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TrayTest.pch"


!ENDIF

SOURCE=.\Stdafx.cpp

!IF  "$(CFG)" == "TrayTest - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\TrayTest.pch" /Yc"STDAFX.H" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c

"$(INTDIR)\Stdafx.obj"  "$(INTDIR)\Stdafx.sbr"  "$(INTDIR)\TrayTest.pch" : $(SOURCE) "$(INTDIR)"
  $(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "TrayTest - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\TrayTest.pch" /Yc"STDAFX.H" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c

"$(INTDIR)\Stdafx.obj"  "$(INTDIR)\TrayTest.pch" : $(SOURCE) "$(INTDIR)"
  $(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF

SOURCE=.\Subclass.cpp

!IF  "$(CFG)" == "TrayTest - Win32 Release"


"$(INTDIR)\Subclass.obj"  "$(INTDIR)\Subclass.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TrayTest.pch"


!ELSEIF  "$(CFG)" == "TrayTest - Win32 Debug"


"$(INTDIR)\Subclass.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TrayTest.pch"


!ENDIF

SOURCE=.\TrayIcon.CPP

!IF  "$(CFG)" == "TrayTest - Win32 Release"


"$(INTDIR)\TrayIcon.obj"  "$(INTDIR)\TrayIcon.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TrayTest.pch"


!ELSEIF  "$(CFG)" == "TrayTest - Win32 Debug"


"$(INTDIR)\TrayIcon.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TrayTest.pch"


!ENDIF

SOURCE=.\TrayTest.cpp

!IF  "$(CFG)" == "TrayTest - Win32 Release"


"$(INTDIR)\TrayTest.obj"  "$(INTDIR)\TrayTest.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TrayTest.pch"


!ELSEIF  "$(CFG)" == "TrayTest - Win32 Debug"


"$(INTDIR)\TrayTest.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TrayTest.pch"


!ENDIF

SOURCE=.\TrayTest.rc

"$(INTDIR)\TrayTest.res" : $(SOURCE) "$(INTDIR)"
  $(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF

