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


//int (*max)(int, int) = lambda (int, (int x, int y) { return x > y ? x : y; });
//
#define lambda(return_type, function_body) \
({ \
    return_type anon_func_name_ function_body \
    anon_func_name_; \
})
