#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

#include "func/foreach.h"

int main()
{
    int a[] = {1,2,3,4,5};
    int sum = 0;

    ARRAY_FOREACH(a, i) {
        sum += a[i];
    }

    assert(sum == (1+2+3+4+5));

    char str[] = "abcd";

    ARRAY_FOREACH(str, i) {
        str[i] = toupper(str[i]);
    }

    assert(0 == strcmp(str, "ABCD"));

    ARRAY_FOREACH(str, i) str[i] = tolower(str[i]);
    assert(0 == strcmp(str, "abcd"));

    int accum = 0;
    void accumulate(unsigned int i) {
        ++accum;
    }

    do_times(10, accumulate);
    assert(accum == 10);

    return 0;
}
