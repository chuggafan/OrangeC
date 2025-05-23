#  Software License Agreement
#  
#      Copyright(C) 1994-2025 David Lindauer, (LADSoft)
#  
#      This file is part of the Orange C Compiler package.
#  
#      The Orange C Compiler package is free software: you can redistribute it and/or modify
#      it under the terms of the GNU General Public License as published by
#      the Free Software Foundation, either version 3 of the License, or
#      (at your option) any later version.
#  
#      The Orange C Compiler package is distributed in the hope that it will be useful,
#      but WITHOUT ANY WARRANTY; without even the implied warranty of
#      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#      GNU General Public License for more details.
#  
#      You should have received a copy of the GNU General Public License
#      along with Orange C.  If not, see <http://www.gnu.org/licenses/>.
#  
#      contact information:
#          email: TouchStone222@runbox.com <David Lindauer>
#  

SHELL=cmd.exe
export SHELL

ifeq "$(COMPILER)" "gcc-linux"
MKDIR := mdkdir -p
DEL := rm
COPY := cp
else
MKDIR := mkdir
DEL := del /Q
COPY := copy
endif

export MKDIR
export DEL
export COPY

all: mkapps

BASEDIRS= ALLOC cmath COMPLIB IO locale MATH PROCONT stdbit stdlib STRING strings \
	threads TIME uio wc uchar
CLIBDIRS = $(BASEDIRS) cpp
DLLDIRS = $(BASEDIRS) cpp
DIRS= $(CLIBDIRS)

define SUFFIXDIRS =
	$(foreach dir, $(1), $(dir)$(2))
endef

C_CLIBS:= $(call SUFFIXDIRS,$(DIRS),.clibs)
C_DLLS:= $(call SUFFIXDIRS,$(DLLDIRS),.dlls)
C_FORMAT= $(call SUFFIXDIRS,$(DIRS),.formats)

MAKEFILES := $(MAKEFILES) $(subst /,\,$(realpath maker.mak))
export MAKEFILES
include maker.mak

ifneq ($(shell type makefile),)
B = /b
endif

THISPATH:=$(subst /,\,$(CURDIR)\)

#DOSOBJECT:=$(THISPATH)object\dos
#export DOSOBJECT
WINOBJECT:=$(THISPATH)object\windows
export WINOBJECT

SYSOBJECT:=$(THISPATH)object\startup
export SYSOBJECT

LSCRTLOBJECT:=$(THISPATH)object\startup
export LSCRTLOBJECT

CLIBOBJECT:=$(THISPATH)object\clib
export CLIBOBJECT

CILOBJECT:=$(THISPATH)object\cil
export CILOBJECT

LIBOBJS = $(subst $(CLIBOBJECT)\,,$(shell dir $(B) $(CLIBOBJECT)\*.o))
#DOSOBJS1 = $(subst $(CLIBOBJECT)\,,$(shell dir $(B) $(DOSOBJECT)\*.o))
#DOSOBJS = $(DOSOBJS1:.OBJ=.o)
WINOBJS = $(subst $(CLIBOBJECT)\,,$(shell dir $(B) $(WINOBJECT)\*.o))
CILOBJS = $(subst $(CLIBOBJECT)\,,$(shell dir $(B) $(CILOBJECT)\*.ilo))

$(MKDIR):
	-$(MKDIR) object 2> NUL
#	-$(MKDIR) object\dos 2> NUL
	-$(MKDIR) object\windows 2> NUL
	-$(MKDIR) object\startup 2> NUL
	-$(MKDIR) object\cil 2> NUL
	-$(MKDIR) object\clib 2> NUL

copyfiles: $(MKDIR)
	-$(MKDIR) ..\..\include 2> NUL
	-$(MKDIR) ..\..\include\c 2> NUL
	-$(MKDIR) ..\..\include\c\sys 2> NUL
	-$(MKDIR) ..\..\include\c\win32 2> NUL
	-$(MKDIR) ..\..\include\c\win32\gl 2> NUL
	-$(MKDIR) ..\..\include\support 2> NUL
	-$(MKDIR) ..\..\include\support\win32 2> NUL
	-$(MKDIR) ..\..\include\support\orangec 2> NUL
	-$(COPY)  cpp\libcxx\include ..\..\include 2>NUL
	-$(COPY)  cpp\libcxx\include\support\win32 ..\..\include\support\win32 2>NUL
	-$(COPY)  cpp\libcxx\include\support\orangec ..\..\include\support\orangec 2>NUL
	-$(COPY)  cpp\stdinc_libcxx ..\..\include 2>NUL
	-$(COPY)  stdinc ..\..\include\c 2>NUL
	-$(COPY)  stdinc\sys ..\..\include\c\sys 2>NUL
	-$(COPY)  platform\win32\inc ..\..\include\c\win32 2>NUL
	-$(COPY)  platform\win32\inc\gdiplus ..\..\include\c\win32 2>NUL
	-$(COPY)  platform\win32\inc\gl ..\..\include\c\win32\gl 2>NUL

$(C_CLIBS) : %.clibs :
	$(MAKE) -C$* --eval="OBJECT=$(CLIBOBJECT)" --eval="$(BUILDING_DLL)"

$(C_FORMAT) : %.formats :
	$(MAKE) -C$* format

platform: $(C_CLIBS)
	$(MAKE) -Cplatform --eval="OBJECT=$(CLIBOBJECT)"

mklibs: platform
ifneq "$(ORANGEC_ONLY)" "YES"
#	-$(DEL) $(SYSOBJECT)\cldos.l
#	$(LIB) $(LIBFLAGS) $(SYSOBJECT)\cldos.l $(foreach dir, $(LIBOBJS), $(CLIBOBJECT)\$(dir)) $(foreach dir, $(DOSOBJS), $(DOSOBJECT)\$(dir))
endif
	-$(DEL) $(SYSOBJECT)\clwin.l
	$(LIB) $(LIBFLAGS) $(SYSOBJECT)\clwin.l $(foreach dir, $(LIBOBJS), $(CLIBOBJECT)\$(dir))
	$(LIB) $(LIBFLAGS) $(SYSOBJECT)\clwin.l $(foreach dir, $(WINOBJS), $(WINOBJECT)\$(dir))

mkapps:
	$(MAKE) copyfiles
	$(MAKE) mklibs
	$(MAKE) -Cplatform --eval="OBJECT=$(CLIBOBJECT)" final

test:
	$(MAKE) -Ccpp\libcxx\test current
BUILDING_DLL = BUILDING_DLL=-D__BUILDING_LSCRTL_DLL

FORMAT: $(C_FORMAT)
	$(MAKE) -Cstdinc format
	$(MAKE) -Cplatform format

ifdef DISTMAKE
	 	include $(DISTMAKE)

DISTRIBUTE:
	$(COPYDIR) cpp\libcxx\include\%. $(DISTINC)
	$(COPYDIR) cpp\libcxx\include\%.h $(DISTINC)
	$(COPYDIR) cpp\libcxx\include\support\win32\%. $(DISTINC)\support\win32
	$(COPYDIR) cpp\libcxx\include\support\win32\%.h $(DISTINC)\support\win32
	$(COPYDIR) cpp\stdinc_libcxx\%. $(DISTINC)
	$(COPYDIR) cpp\stdinc_libcxx\%.h $(DISTINC)
	$(COPYDIR) stdinc\%.h $(DISTINC)\c
	$(COPYDIR) stdinc\sys\%.h $(DISTINC)\c\sys
	$(COPYDIR) platform\win32\inc\%.h $(DISTINC)\c\win32
ifndef BUILDENV
	$(COPYDIR) object\startup\%.l $(DISTLIB)
	$(COPYDIR) object\startup\%.o $(DISTLIB)
ifneq "$(ORANGEC_ONLY)" "YES"
#	$(COPYDIR) object\startup\%.exe $(DISTLIB)
endif
	$(COPYDIR) object\startup\%.dll $(DISTBIN)
	$(MAKE) -Cplatform DISTRIBUTE
endif
endif

clean:
#	-$(DEL) $(DOSOBJECT) 2> NUL
	-$(DEL) $(WINOBJECT) 2> NUL
	-$(DEL) $(SYSOBJECT) 2> NUL
	-$(DEL) $(CILOBJECT) 2> NUL
	-$(DEL) $(CLIBOBJECT) 2> NUL
	-$(DEL) platform\win32\crtdmain\*.o 2>NUL
	-$(DEL) platform\win32\lscrtl\*.o 2>NUL
	-$(DEL) platform\win32\lscrtl\*.dll 2>NUL
	-$(DEL) platform\win32\lsdbghelper\*.o 2>NUL
	-$(DEL) platform\win32\msvcrdm\*.o 2>NUL
	-$(DEL) platform\win32\occil\*.o 2>NUL
	-$(DEL) platform\win32\occil\occmsil.dll 2>NUL
	-$(DEL) platform\win32\pe\*.o 2>NUL
	-$(DEL) platform\win32\pels\*.o 2>NUL
	-$(DEL) platform\win32\rtl\*.o 2>NUL
#	-$(DEL) platform\dos32\debug\*.o 2>NUL
#	-$(DEL) platform\dos32\le\*.o 2>NUL
#	-$(DEL) platform\dos32\pm\*.o 2>NUL
#	-$(DEL) platform\dos32\rtl\*.o 2>NUL
#	-rmdir $(DOSOBJECT) 2> NUL
	-rmdir $(WINOBJECT) 2> NUL
	-rmdir $(SYSOBJECT) 2> NUL
	-rmdir $(CILOBJECT) 2> NUL
	-rmdir $(CLIBOBJECT) 2> NUL
	-rmdir object 2> NUL
