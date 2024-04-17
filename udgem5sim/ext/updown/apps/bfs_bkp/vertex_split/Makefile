### The following variables are used in this Makefile:
LINKER_DIR = ../../../../linker/
LINKER = $(LINKER_DIR)EFAlinker.py

INSTALL_DIR = ../../../../install
.DEFAULT_GOAL := all

sampling: GenSHTInit.py GenSampling.py
	mkdir -p out
	python3 $(LINKER) -L./ -L ../../../../libraries/UDMapShuffleReduce/linkable \
	-L ../../../../libraries/ScalableHashTable/linkable/sht_macros.py \
	-L ../../../../libraries/UDMapShuffleReduce/utils/SHTKeyValueSet.py  \
	-L ../../../../libraries/UDMapShuffleReduce -L ../../../../  -o ./out/$@ \
	../../../../libraries/ScalableHashTable/linkable/sht_ext.py \
	../../../../libraries/ScalableHashTable/linkable/sht.py \
	../../../../libraries/ScalableHashTable/linkable/memcpy.py  $^

split_vertex: GenSplitVertex.py GenSampling.py GenSHTInit.py 
	mkdir -p out
	python3 $(LINKER) -L./ -L ../../../../libraries/UDMapShuffleReduce/linkable \
	-L ../../../../libraries/ScalableHashTable/linkable/sht_macros.py \
	-L ../../../../libraries/UDMapShuffleReduce/utils/SHTKeyValueSet.py  \
	-L ../../../../libraries/UDMapShuffleReduce -L ../../../../  -o ./out/$@ \
	../../../../libraries/ScalableHashTable/linkable/sht_ext.py \
	../../../../libraries/ScalableHashTable/linkable/sht.py \
	../../../../libraries/ScalableHashTable/linkable/memcpy.py  $^

split_edge: GenSplitEdgeList.py GenSHTInit.py GenSplitVertex.py GenSHTInit.py  GenSampling.py
	mkdir -p out
	python3 $(LINKER) -L./ -L ../../../../libraries/UDMapShuffleReduce/linkable \
	-L ../../../../libraries/ScalableHashTable/linkable/sht_macros.py \
	-L ../../../../libraries/UDMapShuffleReduce/utils/SHTKeyValueSet.py  \
	-L ../../../../libraries/UDMapShuffleReduce -L ../../../../  -o ./out/$@ \
	../../../../libraries/ScalableHashTable/linkable/sht_ext.py \
	../../../../libraries/ScalableHashTable/linkable/sht.py \
	../../../../libraries/ScalableHashTable/linkable/memcpy.py  $^

alloc_neighbors: GenAllocNlist.py GenSplitEdgeList.py GenSHTInit.py GenSplitVertex.py  GenSampling.py
	mkdir -p out
	python3 $(LINKER) -L./ -L ../../../../libraries/UDMapShuffleReduce/linkable \
	-L ../../../../libraries/ScalableHashTable/linkable/sht_macros.py \
	-L ../../../../libraries/UDMapShuffleReduce/utils/SHTKeyValueSet.py  \
	-L ../../../../libraries/UDMapShuffleReduce -L ../../../../  -o ./out/$@ \
	../../../../libraries/ScalableHashTable/linkable/sht_ext.py \
	../../../../libraries/ScalableHashTable/linkable/sht.py \
	../../../../libraries/ScalableHashTable/linkable/memcpy.py  $^

split_vertex_exe: GenBuildNlist.py GenAllocNlist.py GenSplitEdgeList.py GenSHTInit.py GenSplitVertex.py GenSampling.py
	mkdir -p out
	python3 $(LINKER) -L./ -L ../../../../libraries/UDMapShuffleReduce/linkable \
	-L ../../../../libraries/ScalableHashTable/linkable/sht_macros.py \
	-L ../../../../libraries/UDMapShuffleReduce/utils/SHTKeyValueSet.py  \
	-L ../../../../libraries/UDMapShuffleReduce -L ../../../../  -o ./out/$@ \
	../../../../libraries/ScalableHashTable/linkable/sht_ext.py \
	../../../../libraries/ScalableHashTable/linkable/sht.py \
	../../../../libraries/ScalableHashTable/linkable/memcpy.py  $^

all: split_vertex_exe

clean:
	rm -f *.exe *.out *.o ./out/*.py ./out/*.hpp