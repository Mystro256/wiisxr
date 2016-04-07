#Creates a WiiSXR Redistributable
ifndef ECHO
ECHO = echo
endif

VERSION = beta2.2

.PHONY:  all

all: dist

dist: ../WiiSXR.dol clean
	@$(ECHO) "Making Redistributable..."
	@cp ../WiiSXR.dol apps/wiiSXR/boot.dol
	@mkdir -p \
		wiisxr/bios \
		wiisxr/saves \
		wiisxr/isos
	@zip -r ../../wiiSXR-$(VERSION).zip wiisxr apps README
 
clean:
	@$(ECHO) "Cleaning..."
	@rm -f apps/wiiSXR/boot.dol ../../wiiSXR-*.zip