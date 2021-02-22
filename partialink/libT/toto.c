
#include "libT.h"

#include "internal.h"
#include <stdio.h>

extern int internal(int);

ATTRIB_VISIBILITY
int toto (int x)
{
  printf ("toto %d\n", x);
  return internal(x) + 10;
}
 
