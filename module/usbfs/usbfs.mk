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

#
# PLACEHOLDER
#

###############################################################################

all:
	@echo "USBFS PLACEHOLDER"

#
# PLACEHOLDER
#
