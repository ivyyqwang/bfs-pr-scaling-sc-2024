### The following variables are used in this Makefile:
LINKER_DIR = ../../../linker/
LINKER = $(LINKER_DIR)EFAlinker.py

INSTALL_DIR = ../../../install
.DEFAULT_GOAL := all

pga: pga.py
	mkdir -p out
	python3 $(LINKER) -f linkable-module -L./pga_call_macros.py -L../../ScalableHashTable/linkable/sht_macros.py -L../../ScalableHashTable/linkable/sht_ext_call_macros.py -o ./out/$@ $^

all: pga

clean:
	rm -f *.exe *.out *.o sht_*_test_out.py sht_*_test_out.hpp