/*!
 * @file
 * @copyright
 * BSD Zero Clause License
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 *
 * @brief
 * Provide wrappers around standard allocation functions
 *
 * @todo
 * - Add wrapper around `aligned_alloc()`
 * - Find a better place for the CTK_BYTE() and `CTK_*iB` macros
 */
/*==============================================================================
    GUARD
==============================================================================*/
#ifndef CTK_ALLOC_H_20180303155245
#define CTK_ALLOC_H_20180303155245
/*==============================================================================
    INCLUDE
==============================================================================*/
// C Standard Library
#include <stddef.h> // size_t
/*==============================================================================
    MACRO
==============================================================================*/
#define CTK_BYTE(n) (n)
#define CTK_KiB(n)  (CTK_BYTE(n) << 10)
#define CTK_MiB(n)  (CTK_KiB(n)  << 10)
#define CTK_GiB(n)  (CTK_MiB(n)  << 10)
/*==============================================================================
    PUBLIC FUNCTION
==============================================================================*/
/*------------------------------------------------------------------------------
    ctk_malloc()
------------------------------------------------------------------------------*/
/**
 * Wrapper around malloc() returning NULL if \p{size} is `0`.
 *
 * - A call to `malloc(0)` is implementation-defined and returns either a null
 *   pointer or a unusable non-zero value.
 * - This function returns `NULL` in that case to make it predictable.
 *
 * @param[in] size : Number of bytes to allocate
 *
 * @return
 * - @success: A pointer to the allocated memory
 * - @failure: `NULL`
 *
 * @warning
 * - \p{size} must be > `0`
 *
 * @see
 * - https://en.cppreference.com/w/c/memory/malloc
 * - @C17{Standard (ISO/IEC 9899:2017) $7.22.3p1, #subsection.7.22.3}
 */
void * ctk_malloc(size_t size);
/*------------------------------------------------------------------------------
    ctk_calloc()
------------------------------------------------------------------------------*/
/**
 * Wrapper around calloc() returning NULL if \p{num} or \p{size} is `0`.
 *
 * - A call to `calloc()` is implementation-defined if one or both of its
 *   parameters are `0` and returns either a null pointer or a unusable non-zero
 *   value.
 * - This function returns `NULL` in these cases to make it predictable.
 *
 * @param[in] num  : Number of objects to allocate
 * @param[in] size : Size of an object in bytes
 *
 * @return
 * - @success: A pointer to the allocated memory
 * - @failure: `NULL`
 *
 * @warning
 * - \p{num} must be > `0`
 * - \p{size} must be > `0`
 *
 * @see
 * - https://en.cppreference.com/w/c/memory/calloc
 * - @C17{Standard (ISO/IEC 9899:2017) $7.22.3p1, #subsection.7.22.3}
 */
void * ctk_calloc(size_t num, size_t size);
/*------------------------------------------------------------------------------
    ctk_realloc()
------------------------------------------------------------------------------*/
/**
 * Wrapper around `realloc()` returning `NULL` if \p{size} is `0`.
 *
 * - A call to `realloc()` is implementation-defined if its size is `0` and
 *   returns either a null pointer or a unusable non-zero value.
 * - This function returns `NULL` in that case to make it predictable.
 *
 * @param[in,out] ptr  : Pointer to the memory to reallocate
 * @param[in]     size : Number of bytes to allocate
 *
 * @return
 * - @success: A pointer to the reallocated memory
 * - @failure: `NULL`
 *
 * @warning
 * - \p{size} must be > `0`
 *
 * @see
 * - https://en.cppreference.com/w/c/memory/realloc
 * - @C17{Standard (ISO/IEC 9899:2017) $7.22.3p1, #subsection.7.22.3}
 */
void * ctk_realloc(void * ptr, size_t size);
/*------------------------------------------------------------------------------
    ctk_free()
------------------------------------------------------------------------------*/
/**
 * Wrapper around `free()` setting \p{*ptr} to NULL after freeing it.
 *
 * - Deallocate memory block allocated with `malloc()`, `calloc()`, `realloc()`
 *   or their wrappers and set the pointer to `NULL`.
 *
 * @param[in,out] ptr : Address of the pointer to the memory to deallocate
 *
 * @return Nothing
 */
void ctk_free_impl(void ** ptr);

#define ctk_free(ptr) \
    ctk_free_impl((void **)ptr)
/*==============================================================================
    GUARD
==============================================================================*/
#endif // CTK_ALLOC_H_20180303155245