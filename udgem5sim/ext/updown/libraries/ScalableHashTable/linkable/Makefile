### The following variables are used in this Makefile:
LINKER_DIR = ../../../linker/
LINKER = $(LINKER_DIR)EFAlinker.py

INSTALL_DIR = ../../../install
.DEFAULT_GOAL := all

sht: sht.py
	mkdir -p out
	python3 $(LINKER) -f linkable-module -L./ -o ./out/$@ $^

sht_confsz: sht_confsz.py
	mkdir -p out
	python3 $(LINKER) -f linkable-module -L./ -o ./out/$@ $^

memcpy: memcpy.py
	mkdir -p out
	python3 $(LINKER) -f linkable-module -o ./out/$@ $^

sht_ext: sht_ext.py memcpy.py
	mkdir -p out
	python3 $(LINKER) -f linkable-module -L./sht_macros.py -L./sht_ext_call_macros.py -o ./out/$@ $^

# all: sht sht_confsz memcpy
all: sht memcpy sht_ext

clean:
	rm -f *.exe *.out *.o sht_*_test_out.py sht_*_test_out.hpp