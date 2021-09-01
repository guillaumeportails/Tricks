

#include <stdio.h>


extern void dllapi (void);


int main (int argc, char *argv[])
{
  printf ("main enter\n");

  dllapi();
  printf ("main between\n");
  dllapi();

  printf ("main leave\n");
  return 0;
}

