#
# Convenience Makefile
#

TARGETS = usbfs nousbfs

.PHONY: all clean $(TARGETS)

all: $(TARGETS)

$(TARGETS):
	$(MAKE) -f$@.mk

clean:
	$(MAKE) -fusbfs.mk $@
	$(MAKE) -fnousbfs.mk $@
