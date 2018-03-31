/**
 * \file common/malloc.c
 *
 * \brief Support functions potentially required by the autoconf macros
 *        \c AC_FUNC_MALLOC and \c AC_FUNC_REALLOC.
 *
 * POSIX does not clearly define what happens when one calls
 * \c malloc(0) or \c realloc(ptr, 0):
 *
 *   <em>
 *   If \c size is 0, either a null pointer or a unique pointer
 *   that can be successfully passed to \c free() shall be returned.
 *   </em>
 *
 * Autoconf expects the latter behavior: If \c size is 0, then a
 * valid pointer should be returned.
 *
 * If Autoconf cannot determine that \c malloc() and \c realloc()
 * behave as expected (e. g. when we are cross-compiling), then it
 * defines \c malloc to \c rpl_malloc (as well as \c HAVE_MALLOC to
 * 0) and \c realloc to \c rpl_realloc (as well as \c HAVE_REALLOC to
 * 0), relying on the project to provide conforming implementations
 * of \c rpl_malloc() and \c rpl_realloc() that exhibit the expected
 * behavior.
 *
 * Thus, we need to provide implementations of \c rpl_malloc() and
 * \c rpl_realloc() that return valid pointers even if called with a
 * memory size of 0 (they can still return \c NULL, but only if the
 * allocation actually failed).
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
/**
 * \brief \c malloc() replacement that accepts a \c size of 0.
 *
 * This is like \c malloc(), but \c rpl_malloc(0) will (try to) return a
 * valid pointer that can be passed to \c free().
 *
 * \returns A pointer to the allocated memory, or \c NULL if (and only
 *          if) the actual memory allocation fails (i. e. \b not because
 *          of argument errors).
 */
void *
rpl_malloc(size_t size)
{
    return malloc(0 == size ? 1 : size);
}
#  endif /* ! HAVE_MALLOC */
#endif /* ifdef HAVE_MALLOC */

#ifdef HAVE_REALLOC
#  if ! HAVE_REALLOC
/**
 * \brief \c realloc() replacement that accepts a \c size of 0.
 *
 * This is like \c realloc(), but \c rpl_realloc(ptr, 0) will (try to)
 * return a valid pointer that can be passed to \c free().
 *
 * \returns A pointer to the allocated memory, or \c NULL if (and only
 *          if) the actual memory allocation fails (i. e. \b not because
 *          of argument errors).
 */
void *
rpl_realloc(void *ptr, size_t size)
{
    return realloc(ptr, 0 == size ? 1 : size);
}
#  endif /* ! HAVE_REALLOC */
#endif /* ifdef HAVE_REALLOC */
