#
# Sound Driver for PS2 IOP
# Makefile for IOP_MAIN.IRX
#
# ver."ZONE OF THE ENDERS"
#

ifeq ($(wildcard PathDefs),)
PathDefs:
	iop-path-setup > PathDefs || (rm -f PathDefs ; exit 1)
endif
include PathDefs

INCDIR  = -I. -I/usr/local/sce/common/include
LIBDIR = ../lib
ILIBS =\
-ilb=libsd.ilb \
-ilb=$(LIBDIR)/jsifman.ilb \
-ilb=$(LIBDIR)/usbfs.ilb \
-ilb=$(LIBDIR)/cdbios.ilb

CFLAGS   = -Wall -G0 $(INCDIR) -O0
ASFLAGS  = $(INCDIR) -G0
LDLIBS   =

# The following variables are only required when using a custom linkerscript
CLILIBS = libsd.ilb $(LIBDIR)/jsifman.ilb $(LIBDIR)/usbfs.ilb $(LIBDIR)/cdbios.ilb \
/usr/local/sce/iop/gcc/mipsel-scei-elfl/lib/iop.ilb
CLLIBS =\
-L/usr/local/sce/iop/gcc/lib/gcc-lib/mipsel-scei-elfl/2.8.1 \
-L/usr/local/sce/iop/gcc/mipsel-scei-elfl/lib
CLSTUB = zoesound_ilb_sub
CLREL = zoesound_iop_rel.o


PROGNAME = iop_main
IRXNAME  = $(PROGNAME).irx
OBJS =\
	iop_main.o \
	sd_file.o \
	sd_sub1.o \
	sd_sub2.o \
	sd_ioset.o \
	sd_drv.o \
	sd_main.o \
	sd_cli.o \
	sd_mstr.o \
	sd_wk.o \
	sd_str.o \
	sd_str2.o \
	sd_str3.o \
	se_tblmd.o

all: $(IRXNAME)

clean:
	rm -f *.o $(IRXNAME)

$(IRXNAME): $(OBJS)
	#~ $(LINK.o) -o $@ $(OBJS) $(ILIBS)
	$(ILBLD) -s $(CLSTUB).s $(CLLIBS) $(OBJS) -lgcc : $(CLILIBS)
	$(AS) $(CLSTUB).s -o $(CLSTUB).o
	$(LD) -EL -dc -r -T ldscript.txt -o $(CLREL) $(CLLIBS) $(OBJS) $(CLSTUB).o -lgcc
	$(IFIXUP) -r $(IRXNAME) $(CLREL)
	rm $(CLREL) $(CLSTUB).{s,o}
