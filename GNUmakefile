# GNU makefile for NeutronShielding detector.

name := NeutronShielding_jpa
G4TARGET := $(name)
G4EXLIB := true

ifndef G4INSTALL
  G4INSTALL = /var/phy/project/hep/neutrino/soft-SL6/geant4/geant4.10.00.p02/ 

endif

.PHONY: all
all: lib bin

include $(G4INSTALL)/config/binmake.gmk

visclean:
	rm -f g4*.prim g4*.eps g4*.wrl
	rm -f .DAWN_*

# Root

CPPFLAGS  += $(shell root-config --cflags) 
EXTRALIBS += $(shell root-config --libs)
LDFLAGS += -L$(shell root-config --libdir) $(EXTRALIBS)

