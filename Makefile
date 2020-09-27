
CFLAGS	= -std=c99 -Wall -Wextra

all: cpreproclist smc

clean:
	rm -f cpreproclist smc callgrind.out.*

test: cpreproclist
	./cpreproclist aa bbb ccc
	./smc
	valgrind --tool=callgrind --smc-check=all ./smc


cpreproclist: cpreproclist.c

smc: smc.c
	$(CC) -fPIC -g -O -Wall -Wextra -o $@ $<
	objdump -D smc | fgrep -A 6 -e '<code>:'
