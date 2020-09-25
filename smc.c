/***********************************

Self Modifying Code

Usage :
   gcc -fPIC -g -O2 smc.c && ./a.out
   
   gdb -ex 'b main' -ex r --args ./a.out
   x/8i code


***********************************/

#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


static int __attribute__ ((noinline)) code (int x)    
{
    register void *pc;
    asm volatile ("lea  0(%%rip),%0" : "=r"(pc));
    ((int16_t *)pc)[3] = x;  // Patcher la constante 10000 ci-dessous
    return x + 10000;
}

static void bye(const char *msg)
{
    perror(msg);
    exit(1);
}

int main (int argc, char *argv[])
{
    int const v = (argc == 2) ? atoi(argv[1]) : 100;

    int const psize = getpagesize();

    void * const zone = mmap(NULL, psize, PROT_EXEC|PROT_READ|PROT_WRITE,
                            MAP_PRIVATE|MAP_ANONYMOUS,  0,0);
    if (zone == NULL) bye(zone);

    memcpy(zone, &code, 0x100);

//  int const s = code(v);
//  printf ("code(%d) = %d\n", v, s);
    
    int const d = ((int (*)(int)) zone)(v);
//  printf ("zone(%d) = %d\n", v, d);
     printf ("I feel %s\n", (d == v+v) ? "good" : "bad");
   
    return 0;
}