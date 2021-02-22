# Tricks makefile
#
# TODO:
# -ftrack-macro-expansion=2

.PHONY = cforeach cforeach1 cforeach2

CFLAGS	= -std=c99 -Wall -Wextra

all: test

clean:
	rm -f cpreproclist smc callgrind.out.* cforeach.[io]

test: cpreproclist smc cforeach
	./cpreproclist aa bbb ccc
	./smc
	valgrind --tool=callgrind --smc-check=all ./smc


cpreproclist: cpreproclist.c


smc: smc.c
	$(CC) -fPIC -g -O -Wall -Wextra -o $@ $<
	objdump -D smc | fgrep -A 6 -e '<code>:'


cforeach: cforeach.i cforeach1 cforeach2
	@true

cforeach.i: cforeach.c
	printf "\n------    -UNDEBUG\n" > $@
	$(CC) -E -P -UNDEBUG $< >> $@
	printf "\n------    -UNDEBUG\n" >> $@
	$(CC) -E -P -DNDEBUG $< >> $@
	cat $@

cforeach1: cforeach.c
	gcc --version
	clang --version
	gcc   -std=c99 -Wall -Wextra -c -UNDEBUG $<
	gcc   -std=c99 -Wall -Wextra -c -DNDEBUG $<
	gcc   -std=c11 -Wall -Wextra -c -UNDEBUG $<
	gcc   -std=c11 -Wall -Wextra -c -DNDEBUG $<
	clang -std=c99 -Wall -Wextra -c -UNDEBUG $<
	clang -std=c99 -Wall -Wextra -c -DNDEBUG $<
	clang -std=c11 -Wall -Wextra -c -UNDEBUG $<
	clang -std=c11 -Wall -Wextra -c -DNDEBUG $<

cforeach2: cforeach.cc
	g++     -std=c++98 -Wall -Wextra -c -UNDEBUG $<
	g++     -std=c++98 -Wall -Wextra -c -DNDEBUG $<
	g++     -std=c++11 -Wall -Wextra -c -UNDEBUG $<
	g++     -std=c++11 -Wall -Wextra -c -DNDEBUG $<
	clang++ -std=c++98 -Wall -Wextra -c -UNDEBUG $<
	clang++ -std=c++98 -Wall -Wextra -c -DNDEBUG $<
	clang++ -std=c++11 -Wall -Wextra -c -UNDEBUG $<
	clang++ -std=c++11 -Wall -Wextra -c -DNDEBUG $<
