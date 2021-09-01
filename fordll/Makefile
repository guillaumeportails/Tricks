#
# Un lib.so contenant du code gfortran doit-il etre initialise au
# chargement du lib.so ?
# Ce lib.so peut-il etre utilse depuis un mex ?
# Ce mex peut-il invoquer du code interprete ?²

CC      = gcc -std=c99 -Wall
FC      = gfortran -std=f95 -Wall -cpp


all: main dll.mex
	main
	LD_LIBRARY_PATH=. octave script.m

clean:
	rm -f main *.o *.so *.mex

main: main.o libdll.so
	$(CC) -o $@ main.o -L. -ldll -Wl,-rpath,.

main.o: main.c
	$(CC) -c $<

libdll.so: dllapi.o dllbody.o
	$(CC) -o $@ -shared $+ -lgfortran

dllapi.o: dllapi.c
	$(CC) -c $< -fPIC

dllbody.o: dllbody.F95
	$(FC) -c $< -fPIC

dll.mex: dllmex.c
	mkoctfile --mex -o $@ dllmex.c -L. -ldll
	LD_LIBRARY_PATH=. ldd dll.mex

