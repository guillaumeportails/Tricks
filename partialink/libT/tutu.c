
#include "libT.h"

#include "internal.h"
#include <stdio.h>

extern int internal(int);
extern int toto(int);

ATTRIB_VISIBILITY
int tutu (int x)
{
  printf ("tutu %d\n", x);
  return internal(x) + toto(x);
}
 
