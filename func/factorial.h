#pragma once

extern inline
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
