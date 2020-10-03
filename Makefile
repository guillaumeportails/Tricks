
CFLAGS	= -std=c99 -Wall -Wextra

all: cpreproclist smc cforeach.i cforeach.o

clean:
	rm -f cpreproclist smc callgrind.out.* cforeach.[io]

test: cpreproclist smc
	./cpreproclist aa bbb ccc
	./smc
	valgrind --tool=callgrind --smc-check=all ./smc


cpreproclist: cpreproclist.c

smc: smc.c
	$(CC) -fPIC -g -O -Wall -Wextra -o $@ $<
	objdump -D smc | fgrep -A 6 -e '<code>:'

# -ftrack-macro-expansion=2
cforeach.i: cforeach.c
	printf "\n------    -UNDEBUG\n" > $@
	$(CC) -E -P -UNDEBUG $< >> $@
	printf "\n------    -UNDEBUG\n" >> $@
	$(CC) -E -P -DNDEBUG $< >> $@
	cat $@

cforeach.o: cforeach.c
	$(CC)  -std=c99   -Wall -Wextra -c -UNDEBUG $<
	$(CC)  -std=c99   -Wall -Wextra -c -DNDEBUG $<
	$(CXX) -std=c++98 -Wall -Wextra -c -UNDEBUG $<
	$(CXX) -std=c++98 -Wall -Wextra -c -DNDEBUG $<
	$(CXX) -std=c++11 -Wall -Wextra -c -UNDEBUG $<
	$(CXX) -std=c++11 -Wall -Wextra -c -DNDEBUG $<
