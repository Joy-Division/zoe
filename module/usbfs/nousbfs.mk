#
# KCEJ USB File System (for PlayStation 2)
# Copyright (C) Konami Computer Entertainment Japan
# Codebase Restoration by Joy Division
#
# ver."ZONE OF THE ENDERS"
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

ILIBS = 

CFLAGS  = -Wall -G0 $(INCDIRS) -O0 -O1
ASFLAGS = $(INCDIRS) -G0
LDFLAGS  = 

PROGNAME = nousbfs.irx

ENTRYFILE = nousbfs_entry.s
ENTRYTABLE = nousbfs.tbl
ILBFILE = nousbfs.ilb

OBJS = nousbfs_entry.o nousbfs.o

###############################################################################

all: $(PROGNAME)

clean:
	-rm -f $(OBJS) $(ENTRYFILE) $(PROGNAME)
	
$(ENTRYFILE): $(ENTRYTABLE)
	$(ILBGEN) -d $(LIBDIR)/$(ILBFILE) -e $(ENTRYFILE) $(ENTRYTABLE)
	
nousbfs_entry.o: $(ENTRYFILE)

$(PROGNAME): $(OBJS)
	$(LINK.o) -o $@ $(OBJS) $(ILIBS)

test: $(PROGNAME)
	@$(IFIXUP) -o nousbfs-retail-jp.irx $(PROGNAME)
	@# sha1sum nousbfs-retail-jp.irx
	@-sha1sum -c nousbfs-retail-jp.sha1
	@rm nousbfs-retail-jp.irx
