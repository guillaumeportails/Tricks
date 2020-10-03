
CFLAGS	= -std=c99 -Wall -Wextra

all: cpreproclist smc

clean:
	rm -f cpreproclist smc

test: cpreproclist smc
	./cpreproclist aa bbb ccc
	./smc

cpreproclist: cpreproclist.c

smc: smc.c
	$(CC) -O2 -fPIC -o $@ $+

