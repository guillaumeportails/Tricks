
# -fPIC pas necessaire en x86
# ld.so: -L/path/to/lib pour eviter LD_LIBRARY_PATH=$LD_LIBRARY_PATH:. ? Non

CC     = gcc
CFLAGS = -g2 -O0 -fvisibility=hidden -fpie

STRIP  = true
STRIP  = strip

SHELL := bash

all: T P main maino mains maind mainh #mainx
	-./main 1
	-./maino 1
	-./mains 1
	-./mainh 1
	-./mainx 1
	-LD_LIBRARY_PATH=$LD_LIBRARY_PATH:. ./maind 1
	file *.o lib*
	nm -D lib[PT]/lib[PT].so
	nm lib[PT]/lib[PT].{o,so}
	nm xlib.o
	-strings -a libd.so | grep internal

clean:; rm -f main main[sdohx] *.[oa] *.so lib[PT]/*.{o,a,so}

T P: NOW
	(cd lib$@; make LIB=$@ -f ../Makefile.sub)


gdb: maind
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:. gdb --args ./maind 2


main: main.o $(wildcard lib[TP]/[tp][ou][tp][ou].o lib[TP]/internal.o)
	-$(CC) -o $@ $+

maino: main.o $(wildcard lib[TP]/lib[TP].o)
	-$(CC) -o $@ $+

# link statique
mains: main.o $(wildcard lib[TP]/lib[TP].a)
	-$(CC) -o $@ $+

# le chemin des lib.so est impose dans l'exec
# man ld.so :
#   When  resolving  shared object dependencies, the dynamic linker first inspects each depen‐
#   dency string to see if it contains a slash (this can occur if  a  shared  object  pathname
#   containing  slashes was specified at link time).  If a slash is found, then the dependency
#   string is interpreted as a (relative or absolute)  pathname,  and  the  shared  object  is
#   loaded using that pathname.
maind: main.o  $(wildcard lib[TP]/lib[TP].so)
	-$(CC) -o $@ $+
	strings -a $@ | grep lib[PT].so
	readelf -d $@ | grep Shared

# link est dynamique par defaut, le rpath permet de trouver les lib.so sans LD_LIBRARY_PATH
# cf man ld.so :                             cf LD_DEBUG
#    cas "no slash in lib.so names"
#    Rpath token expansion
mainw: main.o  $(wildcard lib[TP]/lib[TP].so)
	-$(CC) -o $@ -Wl,-rpath,'$$ORIGIN/libP',-rpath,'$$ORIGIN/libT' -LlibP -LlibT main.o -lP -lT
	strings -a $@ | grep lib[PT].so
	readelf -d $@ | grep Shared

mainh: hand.o  $(wildcard lib[TP]/lib[TP].so)
	-$(CC) -o $@ $+ -ldl

mainx: main.o xlib.o
	-$(CC) -o $@ $+

main.o: main.c

hand.o: main.c
	$(CC) -o $@ -DBYHAND -c $+


xtoto.o: toto.o
	objcopy --redefine-syms=redefsym $< $@

xtutu.o: tutu.o
	objcopy --redefine-syms=redefsym $< $@

xinternal.o: internal.o
	objcopy --redefine-syms=redefsym $< $@


lib.o: toto.o tutu.o internal.o
	$(CC) -o $@ -r $+
	$(STRIP) --strip-unneeded $@

xlib.o: xtoto.o xtutu.o xinternal.o
	$(CC) -o $@ -r $+
	$(STRIP) --strip-unneeded $@

libs.a: toto.o tutu.o internal.o
	ar r $@ $+
	$(STRIP) --strip-unneeded $@

libd.so: toto.o tutu.o internal.o
	$(CC) -o $@ -shared $+
	$(STRIP) --strip-unneeded $@

toto.o: toto.c
tutu.o: tutu.c
internal.o: internal.c


NOW:

