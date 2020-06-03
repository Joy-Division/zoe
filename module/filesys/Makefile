#
# Convenience Makefile
#

TARGETS =\
	cdbios cdbios_ee \
	hdbios hdbios_ee \
	filesys

.PHONY: all clean $(TARGETS)

all: $(TARGETS)

cdbios cdbios_ee filesys:
	$(MAKE) -f$@.mk

hdbios hdbios_ee:
# Currently, the HDBIOS library cannot be decompiled,
# as no builds of the module/interface have been released.
	@echo "*** SKIPPING '$@' (UNAVAILABLE)"

clean:
	$(MAKE) -fcdbios.mk $@
	$(MAKE) -fcdbios_ee.mk $@
#	$(MAKE) -fhdbios.mk $@
#	$(MAKE) -fhdbios_ee.mk $@
	$(MAKE) -ffilesys.mk $@
