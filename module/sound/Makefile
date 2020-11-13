#
# Makefile for KCEJ SOUND DRIVER
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

CHECKSUM = sha1sum -c

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
ASFLAGS = $(INCDIRS)
LDLIBS  =

ifeq ($(VERSION), TGS2000)
	CFLAGS += -DBORMAN_DEMO
	CHECKFILE = tgs2000.sha1
else ifeq ($(VERSION), DENGEKI)
	CFLAGS += -DDENGEKI_DEMO
	CHECKFILE = dengeki.sha1
else ifeq ($(VERSION), EU)
	CFLAGS += -DPAL_RELEASE
	CHECKFILE = eu.sha1
else ifeq ($(VERSION), US)
	CFLAGS += -DUSA_RELEASE
	CHECKFILE = us.sha1
else
	CFLAGS += -DJAPAN_RELEASE
	CHECKFILE = jp.sha1
endif

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

$(PROGNAME): $(OBJS)
	$(LINK.o) -o $@ $(OBJS) $(ILIBS)

test: $(PROGNAME)
	@$(IFIXUP) -o strip-$(PROGNAME) $(PROGNAME)
	@sha1sum strip-$(PROGNAME)
	-@$(CHECKSUM) checksums/$(CHECKFILE)
	@rm strip-$(PROGNAME)

###############################################################################

clean:
	-rm -f *.o $(PROGNAME)
