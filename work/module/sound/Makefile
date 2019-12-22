ifeq ($(wildcard PathDefs),)
PathDefs:
	iop-path-setup > PathDefs || (rm -f PathDefs ; exit 1)
endif
include PathDefs

INCDIR  = -I. -I/usr/local/sce/common/include
LIBDIR = 
ILIBS = -ilb=libsd.ilb -ilb=jsifman.ilb -ilb=usbfs.ilb -ilb=cdbios.ilb

CFLAGS   = -Wall -G0 $(INCDIR) -O0
ASFLAGS  = $(INCDIR) -G0
LDLIBS   =
PROGNAME = iop_main
ELFNAME = $(PROGNAME).elf
IRXNAME = $(PROGNAME).irx
OBJS = iop_main.o sd_file.o sd_sub1.o sd_sub2.o sd_ioset.o sd_drv.o sd_main.o sd_cli.o sd_mstr.o sd_wk.o se_tblmd.o sd_str.o sd_str2.o sd_str3.o

all: $(IRXNAME)

clean:
	rm -f *.o $(IRXNAME) $(ELFNAME) *.map

$(IRXNAME): $(ELFNAME)

$(ELFNAME): $(OBJS)
	$(LINK.o) -o $@ $(OBJS) $(LIBDIR) $(ILIBS)
	$(IFIXUP) -r iop_main.irx $@