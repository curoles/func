/**@file
 * @brief
 * @author    Igor Lesik 2019
 * @copyright Igor Lesik 2019
 *
 */
#pragma once

#include <stdbool.h>
#include <stdint.h>

#define PURE       __attribute__ ((pure))
#define UNUSED     __attribute__ ((unused))

#define RET_NONULL __attribute__((returns_nonnull))

#define CLEANUP(func) __attribute__((cleanup(func)))

#define TRANSPARENT_UNION __attribute__((transparent_union))

#ifndef ANCHOR_EXTERN_INLINE
#define EXTERN_INLINE extern inline __attribute__((__gnu_inline__))
#else
#define EXTERN_INLINE inline
#endif

//#define likely(x)   __builtin_expect(!!(x), 1)
//#define unlikely(x) __builtin_expect(!!(x), 0)

#define SIZEOF_ARRAY(a) (sizeof(a)/sizeof((a)[0]))

//int (*max)(int, int) = lambda (int, (int x, int y) { return x > y ? x : y; });
//
#define lambda(return_type, function_body) \
({ \
    return_type anon_func_name_ function_body \
    anon_func_name_; \
})

#define MAX(a,b) \
({ typeof(a) a_ = (a); \
   typeof(b) b_ = (b); \
   a_ > b_ ? a_ : b_; })

// As used in the linux kernel.
// A macro that expands to 1 if a preprocessor value
// was defined to 1, and 0 if it was not defined or
// defined to an other value.

#define IS_DEFINED(macro) IS_DEFINED_(macro)
#define MACROTEST_1 ,
#define IS_DEFINED_(value) IS_DEFINED__(MACROTEST_##value)
#define IS_DEFINED__(comma) IS_DEFINED___(comma 1, 0)
#define IS_DEFINED___(_, v, ...) v
