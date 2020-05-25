#
# Makefile for KCEJ SIF MANAGER
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

INCDIRS = -I. -I$(INCDIR) -I$(SCEINCDIR)

ILIBS = 

CFLAGS  = -Wall -G0 $(INCDIRS) -O0 -O1
ASFLAGS = $(INCDIRS) -G0
LDFLAGS  = 

PROGNAME = jsifman.irx

ENTRYFILE = jsifman_entry.s
ENTRYTABLE = jsifman.tbl
ILBFILE = jsifman.ilb

OBJS = jsifman_entry.o libmain.o rvman.o

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
	@$(IFIXUP) -o jsifman-retail-jp.irx $(PROGNAME)
	@# sha1sum jsifman-retail-jp.irx
	@-sha1sum -c jsifman-retail-jp.sha1
	@rm jsifman-retail-jp.irx
