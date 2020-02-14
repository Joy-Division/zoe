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
PROGNAME = iop_main
IRXNAME = $(PROGNAME).irx
OBJS = iop_main.o sd_file.o sd_sub1.o sd_sub2.o sd_ioset.o sd_drv.o sd_main.o sd_cli.o sd_mstr.o sd_wk.o se_tblmd.o sd_str.o sd_str2.o sd_str3.o

all: $(IRXNAME)

clean:
	rm -f *.o $(IRXNAME)

$(IRXNAME): $(OBJS)
	$(LINK.o) -o $@ $(OBJS) $(LIBDIR) $(ILIBS)
