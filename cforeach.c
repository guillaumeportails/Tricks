// Iterate over arguments of a variadic macro
//   cc -E -std=c99 -pedantic -Wall -Wextra cppforeach.c
//
// https://stackoverflow.com/questions/1872220/is-it-possible-to-iterate-over-arguments-in-variadic-macros
//
// Cf  __VA_OPT__ of C++2a for empty __VA_ARGS__

extern int printf(const char *fmt, ...);

#ifndef METHOD
#define METHOD  2
#endif

#if METHOD==1
#define CONCATENATE(arg1, arg2)   CONCATENATE1(arg1, arg2)
#define CONCATENATE1(arg1, arg2)  CONCATENATE2(arg1, arg2)
#define CONCATENATE2(arg1, arg2)  arg1##arg2

#define FOR_EACH_1(what, x, ...)  what(x)
#define FOR_EACH_2(what, x, ...)  what(x); FOR_EACH_1(what, __VA_ARGS__)
#define FOR_EACH_3(what, x, ...)  what(x); FOR_EACH_2(what, __VA_ARGS__)
#define FOR_EACH_4(what, x, ...)  what(x); FOR_EACH_3(what, __VA_ARGS__)
#define FOR_EACH_5(what, x, ...)  what(x); FOR_EACH_4(what, __VA_ARGS__)
#define FOR_EACH_6(what, x, ...)  what(x); FOR_EACH_5(what, __VA_ARGS__)
#define FOR_EACH_7(what, x, ...)  what(x); FOR_EACH_6(what, __VA_ARGS__)
#define FOR_EACH_8(what, x, ...)  what(x); FOR_EACH_7(what, __VA_ARGS__)

#define FOR_EACH_NARG(...)    FOR_EACH_NARG_(__VA_ARGS__, FOR_EACH_RSEQ_N())
#define FOR_EACH_NARG_(...)   FOR_EACH_ARG_N(__VA_ARGS__) 
#define FOR_EACH_ARG_N(i1,i2,i3,i4,i5,i6,i7,i8, N, ...) N 
#define FOR_EACH_RSEQ_N()     8, 7, 6, 5, 4, 3, 2, 1, 0

#define FOR_EACH_(N, what, x, ...)  CONCATENATE(FOR_EACH_, N)(what, x, __VA_ARGS__)
#define FOR_EACH(what, x, ...)      FOR_EACH_(FOR_EACH_NARG(x, __VA_ARGS__), what, x, __VA_ARGS__)
#endif

#if METHOD==2
// Make a FOREACH macro
#define FE_0(WHAT, X)
#define FE_1(WHAT, X)      WHAT(X) 
#define FE_2(WHAT, X, ...) WHAT(X)FE_1(WHAT, __VA_ARGS__)
#define FE_3(WHAT, X, ...) WHAT(X)FE_2(WHAT, __VA_ARGS__)
#define FE_4(WHAT, X, ...) WHAT(X)FE_3(WHAT, __VA_ARGS__)
#define FE_5(WHAT, X, ...) WHAT(X)FE_4(WHAT, __VA_ARGS__)
//... repeat as needed

#define GET_MACRO(_0,_1,_2,_3,_4,_5,NAME,...) NAME 
#define FOR_EACH(action,...) /* ! GCC specific ##__VA_ARGS__ before C++2a */  \
  GET_MACRO(_0,##__VA_ARGS__,FE_5,FE_4,FE_3,FE_2,FE_1,FE_0)(action,__VA_ARGS__)
#endif

#define VOIDME(x)   (void)x;

#ifdef NDEBUG
#  define PRINTF(v,fmt,...)   { FOR_EACH(VOIDME, ##__VA_ARGS__) }
#else
#  define PRINTF(v,fmt,...)   { extern int verbose; if (verbose >= v) printf(fmt, ##__VA_ARGS__); }
#endif

void foo (int a, float b, char c, short d, long e)
{
#if 0
  GET_MACRO(0, 1, M5,M4,M3,M2,M1,M0)
# define TEST_STD(none,...)   GET_MACRO(0,   __VA_ARGS__, M5,M4,M3,M2,M1,M0)
# define TEST_GCC(none,...)   GET_MACRO(0, ##__VA_ARGS__, M5,M4,M3,M2,M1,M0)
  TEST_STD(none, 1)
  TEST_GCC(none, 1)
  TEST_STD(none)
  TEST_GCC(none)
#endif

  FOR_EACH(VOIDME, a, b, c, d, e)
  FOR_EACH(VOIDME, a)
  FOR_EACH(VOIDME)
  FOR_EACH(VOIDME,0, a)
//FOR_EACH(VOIDME, 1,2,3,4,5,6);          Normal fail

  PRINTF(1, "toto(%d,%f,%c,%d)\n", a,b,c,d);
  PRINTF(2, "done\n");
}

