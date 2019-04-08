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

#define SIZEOF_ARRAY(a) (sizeof(a)/sizeof(a[0]))

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
