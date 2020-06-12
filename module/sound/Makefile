#
# Makefile for IOP SOUND
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
-ilb=libsd.ilb \
-ilb=$(LIBDIR)/jsifman.ilb \
-ilb=$(LIBDIR)/usbfs.ilb \
-ilb=$(LIBDIR)/cdbios.ilb

CFLAGS  = -Wall -G0 $(INCDIRS) -O0
ASFLAGS = $(INCDIRS) -G0
LDLIBS  =

ifeq ($(TGS2000), 1)
	CFLAGS += -DBORMAN_DEMO
endif

# "CL" variables for custom linker script use:

CLILIBS =\
libsd.ilb \
$(LIBDIR)/jsifman.ilb \
$(LIBDIR)/usbfs.ilb \
$(LIBDIR)/cdbios.ilb \
$(IOPLIBDIR)/iop.ilb

CLLIBS =\
-L$(SCETOP)/iop/gcc/lib/gcc-lib/mipsel-scei-elfl/2.8.1 \
-L$(SCETOP)/iop/gcc/mipsel-scei-elfl/lib

CLSTUB = zoesound_ilb_stub
CLREL = zoesound_iop_rel.o

PROGNAME = iop_main.irx

OBJS =\
	iop_main.o \
	sd_wk.o \
	sd_file.o \
	sd_sub1.o \
	sd_sub2.o \
	sd_ioset.o \
	sd_drv.o \
	sd_main.o \
	sd_cli.o \
	sd_mstr.o \
	sd_str.o \
	sd_str2.o \
	sd_str3.o \
	se_tblmd.o

###############################################################################

all: $(PROGNAME)

# The commented out line will suffice for regular building
# but using a custom linkerscript requires the performed steps to be done
# manually because iop-elf-gcc passes the options in such a way that ioplibld
# makes things break
$(PROGNAME): $(OBJS)
	@#~ $(LINK.o) -o $@ $(OBJS) $(ILIBS)
	$(ILBLD) -s $(CLSTUB).s $(CLLIBS) $(OBJS) -lgcc : $(CLILIBS)
	$(AS) $(CLSTUB).s -o $(CLSTUB).o
	$(LD) -EL -dc -r -T ldscript.txt -o $(CLREL) $(CLLIBS) $(OBJS) $(CLSTUB).o -lgcc
	$(IFIXUP) -r $(PROGNAME) $(CLREL)
	rm $(CLREL) $(CLSTUB).{s,o}

test: $(PROGNAME)
	@$(IFIXUP) -o retail-jp.irx $(PROGNAME)
	@sha1sum retail-jp.irx
	-@sha1sum -c retail-jp.sha1
	@rm retail-jp.irx

###############################################################################

clean:
	-rm -f *.o $(PROGNAME)
