/* Support functions potentially required by the autoconf macros
 * AC_FUNC_MALLOC and AC_FUNC_REALLOC.
 *
 * POSIX does not clearly define what happens when one calls malloc(0)
 * or realloc(ptr, 0):
 *
 *   "If size is 0, either a null pointer or a unique pointer that can
 *    be successfully passed to free() shall be returned."
 *
 * Autoconf expects the latter behavior: If size is 0, then a valid
 * pointer should be returned.
 *
 * If Autoconf cannot determine that malloc() and realloc() behave as
 * expected (e. g. when we are cross-compiling), then it defines
 * "malloc" to "rpl_malloc" (as well as HAVE_MALLOC to 0) and "realloc"
 * to "rpl_realloc" (as well as HAVE_REALLOC to 0), relying on the
 * project to provide conforming implementations of rpl_malloc() and
 * rpl_realloc() that exhibit the expected behavior.
 *
 * Thus, we need to provide implementations of rpl_malloc() and
 * rpl_realloc() that return valid pointers even if called with a memory
 * size of zero (they can still return NULL, but only if the allocation
 * actually failed).
 */

#if HAVE_CONFIG_H
#  include <config.h>
#endif

/* These may have been already redefined by autoconf, but we need to use
 * the real malloc() and realloc() functions below.
 */
#undef malloc
#undef realloc

#include <stdlib.h>     /* for malloc(), realloc() */
#include <sys/types.h>  /* for size_t */

#ifdef HAVE_MALLOC
#  if ! HAVE_MALLOC
/* Like malloc(), but rpl_malloc(0) will (try to) return a valid pointer
 * that can be passed to free().
 *
 * That is, rpl_malloc() will only return NULL if the actual memory
 * allocation fails, not because of argument errors.
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
/* Like realloc(), but rpl_realloc(ptr, 0) will (try to) return a valid
 * pointer that can be passed to free().
 *
 * That is, rpl_realloc() will only return NULL if the actual memory
 * allocation fails, not because of argument errors.
 */
void *
rpl_realloc(void *mem, size_t n)
{
    return realloc(mem, 0 == n ? 1 : n);
}
#  endif /* ! HAVE_REALLOC */
#endif /* ifdef HAVE_REALLOC */
