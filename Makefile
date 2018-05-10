
CFLAGS	= -std=c99

all: define

clean:; rm define

test: define
	./define aa bbb ccc

define: define.c
