# Microsoft Developer Studio Generated NMAKE File, Based on MoveDlg.dsp
!IF "$(CFG)" == ""
CFG=MoveDlg - Win32 Debug
!MESSAGE No configuration specified. Defaulting to MoveDlg - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "MoveDlg - Win32 Release" && "$(CFG)" != "MoveDlg - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MoveDlg.mak" CFG="MoveDlg - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MoveDlg - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MoveDlg - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "MoveDlg - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\MoveDlg.exe"


CLEAN :
  -@erase "$(INTDIR)\MoveDlg.obj"
  -@erase "$(INTDIR)\MoveDlg.pch"
  -@erase "$(INTDIR)\MoveDlg.res"
  -@erase "$(INTDIR)\StatLink.obj"
  -@erase "$(INTDIR)\StdAfx.obj"
  -@erase "$(INTDIR)\vc60.idb"
  -@erase "$(OUTDIR)\MoveDlg.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\MoveDlg.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\MoveDlg.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MoveDlg.bsc" 
BSC32_SBRS= \
  
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\MoveDlg.pdb" /machine:I386 /out:"$(OUTDIR)\MoveDlg.exe" 
LINK32_OBJS= \
  "$(INTDIR)\MoveDlg.obj" \
  "$(INTDIR)\StatLink.obj" \
  "$(INTDIR)\StdAfx.obj" \
  "$(INTDIR)\MoveDlg.res"

"$(OUTDIR)\MoveDlg.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MoveDlg - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\MoveDlg.exe"


CLEAN :
  -@erase "$(INTDIR)\MoveDlg.obj"
  -@erase "$(INTDIR)\MoveDlg.pch"
  -@erase "$(INTDIR)\MoveDlg.res"
  -@erase "$(INTDIR)\StatLink.obj"
  -@erase "$(INTDIR)\StdAfx.obj"
  -@erase "$(INTDIR)\vc60.idb"
  -@erase "$(INTDIR)\vc60.pdb"
  -@erase "$(OUTDIR)\MoveDlg.exe"
  -@erase "$(OUTDIR)\MoveDlg.ilk"
  -@erase "$(OUTDIR)\MoveDlg.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\MoveDlg.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\MoveDlg.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MoveDlg.bsc" 
BSC32_SBRS= \
  
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\MoveDlg.pdb" /debug /machine:I386 /out:"$(OUTDIR)\MoveDlg.exe" /pdbtype:sept 
LINK32_OBJS= \
  "$(INTDIR)\MoveDlg.obj" \
  "$(INTDIR)\StatLink.obj" \
  "$(INTDIR)\StdAfx.obj" \
  "$(INTDIR)\MoveDlg.res"

"$(OUTDIR)\MoveDlg.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("MoveDlg.dep")
!INCLUDE "MoveDlg.dep"
!ELSE 
!MESSAGE Warning: cannot find "MoveDlg.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "MoveDlg - Win32 Release" || "$(CFG)" == "MoveDlg - Win32 Debug"
SOURCE=.\MoveDlg.cpp

"$(INTDIR)\MoveDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\MoveDlg.pch"


SOURCE=.\MoveDlg.rc

"$(INTDIR)\MoveDlg.res" : $(SOURCE) "$(INTDIR)"
  $(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StatLink.cpp

"$(INTDIR)\StatLink.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\MoveDlg.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "MoveDlg - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\MoveDlg.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"  "$(INTDIR)\MoveDlg.pch" : $(SOURCE) "$(INTDIR)"
  $(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "MoveDlg - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\MoveDlg.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"  "$(INTDIR)\MoveDlg.pch" : $(SOURCE) "$(INTDIR)"
  $(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

