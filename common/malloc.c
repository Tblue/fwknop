/* Support functions potentially required by the autoconf macros
 * AC_FUNC_MALLOC and AC_FUNC_REALLOC.
 *
 * Autoconf defines "malloc" to "rpl_malloc" and/or "realloc" to
 * "rpl_realloc" if it discovers that malloc() and/or realloc()
 * return NULL if the size of the memory to be allocated is zero.
 *
 * Thus, we need to provide implementations of rpl_malloc() and
 * rpl_realloc().
 */

#if HAVE_CONFIG_H
#  include <config.h>
#endif

/* These may have been defined by autoconf, but we need to use the
 * real malloc() and realloc() functions below.
 */
#undef malloc
#undef realloc

#include <stdlib.h>     /* for malloc(), realloc() */
#include <sys/types.h>  /* for size_t */

#ifdef HAVE_MALLOC
#  if ! HAVE_MALLOC
/* Like malloc(), but rpl_malloc(0) is guaranteed to return a valid
 * pointer that can be passed to free().
 */
void *
rpl_malloc(size_t n)
{
    return malloc(0 == n ? 1 : n);
}
#  endif /* ! HAVE_MALLOC */
#endif /* ifdef HAVE_MALLOC */

#ifdef HAVE_REALLOC
#  if ! HAVE_REALLOC
/* Like realloc(), but rpl_realloc(x, 0) is guaranteed to return a
 * valid pointer that can be passed to free().
 */
void *
rpl_realloc(void *mem, size_t n)
{
    return realloc(mem, 0 == n ? 1 : n);
}
#  endif /* ! HAVE_REALLOC */
#endif /* ifdef HAVE_REALLOC */
