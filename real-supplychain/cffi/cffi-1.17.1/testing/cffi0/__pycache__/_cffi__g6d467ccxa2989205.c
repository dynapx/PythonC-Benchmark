
#include <stdio.h>
#include <stddef.h>
#include <stdarg.h>
#include <errno.h>
#include <sys/types.h>   /* XXX for ssize_t on some platforms */

/* this block of #ifs should be kept exactly identical between
   c/_cffi_backend.c, cffi/vengine_cpy.py, cffi/vengine_gen.py
   and cffi/_cffi_include.h */
#if defined(_MSC_VER)
# include <malloc.h>   /* for alloca() */
# if _MSC_VER < 1600   /* MSVC < 2010 */
   typedef __int8 int8_t;
   typedef __int16 int16_t;
   typedef __int32 int32_t;
   typedef __int64 int64_t;
   typedef unsigned __int8 uint8_t;
   typedef unsigned __int16 uint16_t;
   typedef unsigned __int32 uint32_t;
   typedef unsigned __int64 uint64_t;
   typedef __int8 int_least8_t;
   typedef __int16 int_least16_t;
   typedef __int32 int_least32_t;
   typedef __int64 int_least64_t;
   typedef unsigned __int8 uint_least8_t;
   typedef unsigned __int16 uint_least16_t;
   typedef unsigned __int32 uint_least32_t;
   typedef unsigned __int64 uint_least64_t;
   typedef __int8 int_fast8_t;
   typedef __int16 int_fast16_t;
   typedef __int32 int_fast32_t;
   typedef __int64 int_fast64_t;
   typedef unsigned __int8 uint_fast8_t;
   typedef unsigned __int16 uint_fast16_t;
   typedef unsigned __int32 uint_fast32_t;
   typedef unsigned __int64 uint_fast64_t;
   typedef __int64 intmax_t;
   typedef unsigned __int64 uintmax_t;
# else
#  include <stdint.h>
# endif
# if _MSC_VER < 1800   /* MSVC < 2013 */
#  ifndef __cplusplus
    typedef unsigned char _Bool;
#  endif
# endif
# define _cffi_float_complex_t   _Fcomplex    /* include <complex.h> for it */
# define _cffi_double_complex_t  _Dcomplex    /* include <complex.h> for it */
#else
# include <stdint.h>
# if (defined (__SVR4) && defined (__sun)) || defined(_AIX) || defined(__hpux)
#  include <alloca.h>
# endif
# define _cffi_float_complex_t   float _Complex
# define _cffi_double_complex_t  double _Complex
#endif

enum ee { EE1, EE2 };
int _cffi_e_enum_ee(char *out_error)
{
  if ((EE1) > 0 || (long)(EE1) != 0L) {
    char buf[64];
    if ((EE1) <= 0)
        sprintf(buf, "%ld", (long)(EE1));
    else
        sprintf(buf, "%lu", (unsigned long)(EE1));
    sprintf(out_error, "%s has the real value %s, not %s",
            "EE1", buf, "0");
    return -1;
  }
  if ((EE2) <= 0 || (unsigned long)(EE2) != 1UL) {
    char buf[64];
    if ((EE2) <= 0)
        sprintf(buf, "%ld", (long)(EE2));
    else
        sprintf(buf, "%lu", (unsigned long)(EE2));
    sprintf(out_error, "%s has the real value %s, not %s",
            "EE2", buf, "1");
    return -1;
  }
  if ((EE3) <= 0 || (unsigned long)(EE3) != 2UL) {
    char buf[64];
    if ((EE3) <= 0)
        sprintf(buf, "%ld", (long)(EE3));
    else
        sprintf(buf, "%lu", (unsigned long)(EE3));
    sprintf(out_error, "%s has the real value %s, not %s",
            "EE3", buf, "2");
    return -1;
  }
  return 0;
}

