#
# Small makefile for testing with non-Microsoft compilers
#

include ../Makefile.config

all: testSnap

testSnap: testSnap.cpp Snap.o 
	$(CC) $(CXXFLAGS) -o testSnap testSnap.cpp Snap.o -I$(CGLIB) $(LDFLAGS) $(LIBS)

Snap.o: *.h *.cpp ../glib-core/*.h ../glib-core/*.cpp
	$(CC) -c $(CXXFLAGS) -static Snap.cpp -I$(CGLIB)

lib: Snap.o
	rm -f libsnap.a
	ar -cvq libsnap.a Snap.o

libinstall: lib
	cp libsnap.a /usr/local/lib/libsnap.a

clean:
	rm -f *.o *.a testSnap testSnap.exe *.plt *.tab *.png

