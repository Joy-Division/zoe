#
#『ZONE OF THE ENDERS』File System (for PlayStation 2)
# Copyright (C) Konami Computer Entertainment Japan
# Codebase Restoration by Joy Division
#

ifeq ($(wildcard PathDefs),)
PathDefs:
	iop-path-setup > PathDefs || (rm -f PathDefs ; exit 1)
endif
include PathDefs

SCETOP ?= /usr/local/sce
SCEINCDIR = $(SCETOP)/common/include
IOPINCDIR = $(SCETOP)/iop/gcc/mipsel-scei-elfl/include
IOPLIBDIR = $(SCETOP)/iop/gcc/mipsel-scei-elfl/lib
IOPMODDIR = $(SCETOP)/iop/modules

###############################################################################

INCDIR = ../include
LIBDIR = ../lib

INCDIRS = -I$(INCDIR) -I$(SCEINCDIR)

ILIBS =\
-ilb=$(LIBDIR)/jsifman.ilb \
-ilb=$(LIBDIR)/usbfs.ilb

CFLAGS  = -Wall -G0 $(INCDIRS) -O0
ASFLAGS = $(INCDIRS) -G0
LDFLAGS  = -e FS_StartDaemonIOP

PROGNAME = filesys.irx

OBJS =\
	filesys_iop.o

###############################################################################

all: $(PROGNAME)

$(PROGNAME): $(OBJS)
	$(LINK.o) -o $@ $(OBJS) $(ILIBS)

# Stripping of the IRX is required for checksum comparisons
# as the symbol table is virtually impossible to reproduce.
test: $(PROGNAME)
	@$(IFIXUP) -o filesys-retail-jp.irx $(PROGNAME)
	@# sha1sum filesys-retail-jp.irx
	@-sha1sum -c filesys-retail-jp.sha1
	@rm filesys-retail-jp.irx

###############################################################################

clean:
	-rm -f $(OBJS) $(PROGNAME)
