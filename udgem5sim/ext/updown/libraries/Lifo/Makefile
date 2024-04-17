### The following variables are used in this Makefile:
LINKER_DIR = ../../../linker/
LINKER = $(LINKER_DIR)EFAlinker.py

UDWEAVE_DIR = ../../../udweave
UDWEAVE = $(UDWEAVE_DIR)/UDweave.py
UDW_HEADER_FILES = $(wildcard *.udwh)

INSTALL_DIR = ../../../install
.DEFAULT_GOAL := all


%.py: %.udw $(UDW_HEADER_FILES) 
	$(UDWEAVE) -i $< -I ../../libraries/LMStaticMaps/ \
					 -o $@

#all: ../../build/te/wf2/wf2k4_partialMatch/wf2k4_ingestion_efa.bin
all: lifo.py

clean:
	@rm -f lifo.py

