// C preprocessor abuse trick (as old as the C pre-processor is)

#include <stdio.h>


#define MYLIST(tuple) \
  /*    var siz  type    dft   unit   */   \
  tuple(D,    1, float,  1.2,  "m")	\
  tuple(V,    1, float,  2.3,  "m/s")	\
  tuple(P,    3, float,  3.4,  "m")	\
  tuple(Nb,   1, int,      5,  "none")



struct s
{
# define GEN_STRUCT(var,size,type,dft,unit)		type var[size];
  MYLIST(GEN_STRUCT)
};


#define GEN_PARAM(var,size,type,dft,unit)		type var,
void foo (struct s *s, MYLIST(GEN_PARAM) int end)
{
  (void) end;   // Arg not used

# define GEN_AFFECT(var,size,type,dft,unit)		{ for(int i=0; i<size; i++) s->var[i] = var; }
  MYLIST(GEN_AFFECT);
   
# define GEN_PRINT(var,size,type,dft,unit)		printf(" " #var " = %f ... " unit "\n", (float) s->var[0]);
  MYLIST(GEN_PRINT);
}


int main (int argc, char *argv[])
{
  (void) argc;  // Arg not used
  (void) argv;  // Arg not used

  struct s s;
  
# define GEN_CALL(var,size,type,dft,unit)		dft,
  foo (&s, MYLIST(GEN_CALL) 1234);

  return 0;
}
