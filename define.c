// C preprocessor abuse trick

#include <stdio.h>


#define LISTE(tuple) \
  /*    var siz  type    dft   unit   */   \
  tuple(D,    1, float,  1.2,  "m")	\
  tuple(V,    1, float,  2.3,  "m/s")	\
  tuple(P,    3, float,  3.4,  "m")	\
  tuple(Nb,   1, int,      5,  "none")


#define GEN_STRUCT(var,size,type,dft,unit)		type var[size];

struct s
{
  LISTE(GEN_STRUCT)
};


#define GEN_PARAM(var,size,type,dft,unit)		type var,

void toto (struct s *s, LISTE(GEN_PARAM) int end)
{
# define GEN_AFFECT(var,size,type,dft,unit)		{ for(int i=0; i<size; i++) s->var[i] = var; }
  LISTE(GEN_AFFECT);
   
# define GEN_PRINT(var,size,type,dft,unit)		printf(" " #var " = %f ... " unit "\n", (float) s->var[0]);
  LISTE(GEN_PRINT);
}


int main (int argc, char *argv[])
{
  struct s s;
# define GEN_CALL(var,size,type,dft,unit)		dft,
  toto (&s, LISTE(GEN_CALL) 1234);
  
  return 0;
}
