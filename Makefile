
CFLAGS	= -std=c99

all: cpreproclist

clean:
	rm cpreproclist

test: cpreproclist
	./cpreproclist aa bbb ccc

cpreproclist: cpreproclist.c

