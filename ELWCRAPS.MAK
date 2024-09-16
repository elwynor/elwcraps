#################################################################################
#####                 This makefile generates ELWCRAPS.DLL                  #####
#################################################################################
!include $(WGDEV)\src\gcrules.mak

VIRDIR = .\GCVIRDAT 

!if $(OS) == WNT
DLLLIB = $(DLLLIB) wgserver.lib galgsbl.lib
PRODLL =
DEFILE =
PARSEOPTS = $(PARSEOPTS) -I. -DIS30
!endif

!if $(OS) == WG2
DLLLIB = $(DLLLIB) wgserver.lib galgsbl.lib $(BORLAND)\lib\mathh.lib $(DOSEXT)\bc4\lib\phapi.lib
PRODLL = $(DOSEXT)\bc4\lib\fpdmy
DEFILE = $(WGLIBDIR)\mathdef.def
PARSEOPTS = $(PARSEOPTS) -I. 
!endif

VIRFILES =

OBJFILES = \
     ${TEMPDIR}\elwcraps.obj 

start:              \
     $(GCBUILD)     \
     elwcraps.dll

elwcraps.dll:         \
     $(OBJFILES)    \
     $(DLLLIB)      \
     $(DEFILE)      \
     $(VIRFILES)
     $(LINK) $(LIBCMD) @&&|
$(PRODLL) $(OBJFILES)
$(RUNDIR)\$&
$(RUNDIR)\$&
$(DLLLIB) $(LINKDLL)
$(DEFILE)
|
