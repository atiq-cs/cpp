# Microsoft Developer Studio Generated NMAKE File, Based on FSApp.dsp
!IF "$(CFG)" == ""
CFG=FSApp - Win32 Release
!MESSAGE No configuration specified. Defaulting to FSApp - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "FSApp - Win32 Release" && "$(CFG)" != "FSApp - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "FSApp.mak" CFG="FSApp - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "FSApp - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "FSApp - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "FSApp - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\FSApp.exe"


CLEAN :
  -@erase "$(INTDIR)\doc.obj"
  -@erase "$(INTDIR)\FSApp.obj"
  -@erase "$(INTDIR)\FSApp.pch"
  -@erase "$(INTDIR)\FSApp.res"
  -@erase "$(INTDIR)\FullScreenHandler.obj"
  -@erase "$(INTDIR)\mainfrm.obj"
  -@erase "$(INTDIR)\StatLink.obj"
  -@erase "$(INTDIR)\StdAfx.obj"
  -@erase "$(INTDIR)\vc60.idb"
  -@erase "$(INTDIR)\view.obj"
  -@erase "$(OUTDIR)\FSApp.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\FSApp.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\FSApp.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\FSApp.bsc" 
BSC32_SBRS= \
  
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\FSApp.pdb" /machine:I386 /out:"$(OUTDIR)\FSApp.exe" 
LINK32_OBJS= \
  "$(INTDIR)\doc.obj" \
  "$(INTDIR)\FSApp.obj" \
  "$(INTDIR)\mainfrm.obj" \
  "$(INTDIR)\StatLink.obj" \
  "$(INTDIR)\StdAfx.obj" \
  "$(INTDIR)\view.obj" \
  "$(INTDIR)\FSApp.res" \
  "$(INTDIR)\FullScreenHandler.obj"

"$(OUTDIR)\FSApp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "FSApp - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\FSApp.exe"


CLEAN :
  -@erase "$(INTDIR)\doc.obj"
  -@erase "$(INTDIR)\FSApp.obj"
  -@erase "$(INTDIR)\FSApp.pch"
  -@erase "$(INTDIR)\FSApp.res"
  -@erase "$(INTDIR)\FullScreenHandler.obj"
  -@erase "$(INTDIR)\mainfrm.obj"
  -@erase "$(INTDIR)\StatLink.obj"
  -@erase "$(INTDIR)\StdAfx.obj"
  -@erase "$(INTDIR)\vc60.idb"
  -@erase "$(INTDIR)\vc60.pdb"
  -@erase "$(INTDIR)\view.obj"
  -@erase "$(OUTDIR)\FSApp.exe"
  -@erase "$(OUTDIR)\FSApp.ilk"
  -@erase "$(OUTDIR)\FSApp.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\FSApp.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\FSApp.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\FSApp.bsc" 
BSC32_SBRS= \
  
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\FSApp.pdb" /debug /machine:I386 /out:"$(OUTDIR)\FSApp.exe" 
LINK32_OBJS= \
  "$(INTDIR)\doc.obj" \
  "$(INTDIR)\FSApp.obj" \
  "$(INTDIR)\mainfrm.obj" \
  "$(INTDIR)\StatLink.obj" \
  "$(INTDIR)\StdAfx.obj" \
  "$(INTDIR)\view.obj" \
  "$(INTDIR)\FSApp.res" \
  "$(INTDIR)\FullScreenHandler.obj"

"$(OUTDIR)\FSApp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("FSApp.dep")
!INCLUDE "FSApp.dep"
!ELSE 
!MESSAGE Warning: cannot find "FSApp.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "FSApp - Win32 Release" || "$(CFG)" == "FSApp - Win32 Debug"
SOURCE=.\doc.cpp

"$(INTDIR)\doc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FSApp.pch"


SOURCE=.\FSApp.cpp

"$(INTDIR)\FSApp.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FSApp.pch"


SOURCE=.\FSApp.rc

"$(INTDIR)\FSApp.res" : $(SOURCE) "$(INTDIR)"
  $(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\FullScreenHandler.cpp

"$(INTDIR)\FullScreenHandler.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FSApp.pch"


SOURCE=.\mainfrm.cpp

"$(INTDIR)\mainfrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FSApp.pch"


SOURCE=.\StatLink.cpp

"$(INTDIR)\StatLink.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FSApp.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "FSApp - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\FSApp.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"  "$(INTDIR)\FSApp.pch" : $(SOURCE) "$(INTDIR)"
  $(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "FSApp - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\FSApp.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"  "$(INTDIR)\FSApp.pch" : $(SOURCE) "$(INTDIR)"
  $(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\view.cpp

"$(INTDIR)\view.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FSApp.pch"



!ENDIF 

