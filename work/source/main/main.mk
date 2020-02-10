#
# "ZONE OF THE ENDERS"
# Test Makefile for main.cc
#

SCE_TOP = /usr/local/sce

SCE_CM_TOP = $(SCE_TOP)/common
SCE_CM_INC = $(SCE_CM_TOP)/include

SCE_EE_TOP = $(SCE_TOP)/ee
SCE_EE_INC = $(SCE_EE_TOP)/include
SCE_EE_LIB = $(SCE_EE_TOP)/lib

SCE_IOP_TOP = $(SCE_TOP)/iop
SCE_IOP_INC = $(SCE_IOP_TOP)/gcc/mipsel-scei-elfl/include
SCE_IOP_LIB = $(SCE_IOP_TOP)/gcc/mipsel-scei-elfl/lib

PREFIX  = ee
AR      = $(PREFIX)-ar
AS      = $(PREFIX)-gcc
CC      = $(PREFIX)-gcc
CXX     = $(PREFIX)-gcc
LD      = $(PREFIX)-gcc
DVPASM  = $(PREFIX)-dvp-as
OBJCOPY = $(PREFIX)-objcopy
OBJDUMP = $(PREFIX)-objdump

TOP    = ../..
COMMON = $(TOP)/common
MODULE = $(TOP)/module
SOURCE = $(TOP)/source

INCDIRS = \
-I$(SCE_CM_INC) \
-I$(SCE_EE_INC) \
-I$(COMMON)/include \
-I$(MODULE)/include \
-I$(SOURCE)/include

VERSION ?= SLPM65019

DEFINES = -DBUILD_$(VERSION)
CFLAGS  = -Wall -O2 -c $(INCDIRS) $(DEFINES)
CXXFLAGS = $(CFLAGS)

all: ee

ee: main.cc
	$(CXX) $(CXXFLAGS) $^

clean:
	-rm *.o
