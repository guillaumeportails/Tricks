
#include <stdio.h>

static void trace (int x)
{
  if (x == 1) printf ("hiddenP(%d)\n", x);
}

int internal(int x)
{
  trace (x);
  return x + 200;
}
 
