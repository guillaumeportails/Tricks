
#include <stdio.h>


extern void dllbody_(float *ro);

void dllapi (void)
{
  printf("DLLAPI enter\n");

  float ro;
  dllbody_(&ro);

  printf("DLLAPI leave\n");
}

