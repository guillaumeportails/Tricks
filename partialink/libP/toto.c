
#include "libP.h"

#include "internal.h"
#include <stdio.h>

extern int internal(int);

ATTRIB_VISIBILITY
int popo (int x)
{
  printf ("popo %d\n", x);
  return internal(x) + 10;
}
 
