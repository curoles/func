#pragma once

#include "func/func.h"

#define ARRAY_FOREACH(a,i) \
    for (unsigned int i = 0; i < (sizeof(a)/sizeof(a[0])); ++i)

extern inline
void do_times(unsigned int nr_times, void (*visitor)(unsigned int))
{
    for (unsigned int i = 0; i < nr_times; ++i) {
        visitor(i);
    }
}
