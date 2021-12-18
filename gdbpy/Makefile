# Makefile
#
# Notes:
# - Works even with gcc -O

CC		= gcc
CFLAGS	= -g -O2


all: test

clean:; rm -f sample out.bin sread_*.m

test: sread_internal.m out.bin
	octave testreader.m

# Build Octave/MATLAB statements of the C-struct reader
sread_internal.m: sample parse.gdb
	gdb -q -x parse.gdb sample
	cat sread_internal.m

# Build a binary file of C-structs
out.bin: sample
	./$+

# The C program that produce binary files
sample: sample.c
