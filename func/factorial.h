#pragma once

#include "func/func.h"

EXTERN_INLINE
int factorial(int n, int acum)
{
tailcall__:
    if (n < 2)
        return acum;
    else {
        acum *= n;
        --n;
        goto tailcall__;
    }
}
