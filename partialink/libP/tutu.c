
#include "libP.h"

#include "internal.h"
#include <stdio.h>

extern int internal(int);
extern int toto(int);

ATTRIB_VISIBILITY
int pupu (int x)
{
  printf ("pupu %d\n", x);
  return internal(x) + popo(x);
}
 
