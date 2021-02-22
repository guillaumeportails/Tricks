
#include <stdio.h>

static void trace (int x)
{
  if (x == 1) printf ("hiddenT(%d)\n", x);
}

int internal(int x)
{
  trace (x);
  return x + 100;
}
 
