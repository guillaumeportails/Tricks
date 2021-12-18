// A C program defining abd writing structs to a file,
// to be read to another language (Octave/Matlab for example)

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

// A random internal C-struct
typedef struct internal
{
  float f1;
  int i1;
#if 0  /* TODO: add recursive parsing in parse.gdb */
  struct ano
  {
    float f1,f2;
    long long ll1;
  } s1[3];
#endif
  double d1[3];         // TODO: use gdbtype.range() in parse.gdb
  unsigned long long ull1;
} Internal;

//Note: an unused struct may be not dump to the DWARFs
struct unused { int foo; };
static struct { int foo; } i_know;


// Writing a binary file of C-struct
int main (int argc, char *argv[])
{
  FILE *fp = fopen("out.bin", "w");
  if (fp == NULL) { perror("open"); exit(1); }

  for (int n = 1; n <= 7; n++)
  {
    Internal s;
    s.f1 = n * 10.010;
    s.i1 = 1000 + n;
//    s.s1[1].f1   = n * 1.001;
//    s.s1[1].f2   = n * 2.001;
//    s.s1[1].ull1 = (unsigned long long) n * 10000000000ULL;
    s.d1[0] = 100 + n;
    s.d1[1] = 200 + n;
    s.d1[2] = 300 + n;
    s.ull1 = (unsigned long long) n * 10000000000ULL;
    if (fwrite(&s, sizeof(s), 1, fp) != 1) { perror("fwrite"); exit(1); }
  }

  if (fclose(fp) != 0) { perror("fclose"); exit(1);}
  return 0;
}