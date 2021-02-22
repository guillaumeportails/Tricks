
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#include "libT/libT.h"
#include "libP/libP.h"

static void bye(const char *msg)
{
  fprintf(stderr, "bye: %s\n", msg);
  abort();
}

#if BYHAND
static void *hp = NULL;
static void *ht = NULL;
static int (*fpopo)(int);
static int (*fpupu)(int);
static int (*ftoto)(int);
static int (*ftutu)(int);
static void load (void)
{
  hp = dlopen("libP/libP.so", RTLD_NOW|RTLD_LOCAL|RTLD_DEEPBIND);
  if (hp == NULL) bye(dlerror());
  *(void **) (&fpopo) = dlsym(hp, "popo"); if (fpopo==NULL) bye(dlerror());
  *(void **) (&fpupu) = dlsym(hp, "pupu"); if (fpupu==NULL) bye(dlerror());
  ht = dlopen("libT/libT.so", RTLD_NOW|RTLD_LOCAL|RTLD_DEEPBIND);
  if (ht == NULL) bye(dlerror());
  *(void **) (&ftoto) = dlsym(ht, "toto"); if (ftoto==NULL) bye(dlerror());
  *(void **) (&ftutu) = dlsym(ht, "tutu"); if (ftutu==NULL) bye(dlerror());
  printf ("loaded\n");
}
#else
static void load (void) { }
static int (* const fpopo)(int) = popo;
static int (* const fpupu)(int) = pupu;
static int (* const ftoto)(int) = toto;
static int (* const ftutu)(int) = tutu;
#endif

int main (int argc, char *argv[])
{
  int a = (argc == 2) ? atoi(argv[1]) : 1;
  printf ("a = %d\n", a);
  load();
  printf ("toto(%d) = %d\n", a,ftoto(a));
  printf ("tutu(%d) = %d\n", a,ftutu(a));
  printf ("popo(%d) = %d\n", a,fpopo(a));
  printf ("pupu(%d) = %d\n", a,fpupu(a));
  return 0;
}
 
