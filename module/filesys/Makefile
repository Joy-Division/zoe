#
# Convenience Makefile
#

all:\
	cdbios cdbios_ee \
	hdbios hdbios_ee \
	filesys

cdbios cdbios_ee:
	$(MAKE) -f$@.mk

hdbios hdbios_ee:
# Currently, the HDBIOS library cannot be decompiled,
# as no builds of the module/interface have been released.
	@echo "Skipping '$@' (PLACEHOLDER)"

filesys:
	$(MAKE) -f$@.mk
