#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

#include "func/foreach.h"

int main()
{
    int a[] = {1,2,3,4,5};
    int sum = 0;

    ARRAY_FOREACH(a, lambda(void, (unsigned i, int e) {
        //printf("a[%u]=%d\n", i, e);
        sum += e;
    }))

    assert(sum == (1+2+3+4+5));

    char str[] = "abcd";

    ARRAY_FOREACH(str, lambda(void, (unsigned i, char e) {
        str[i] = toupper(e);
    }))

    //puts(str);
    assert(0 == strcmp(str, "ABCD"));

    void decapitalize(unsigned i, char e) {
        str[i] = tolower(e);
    }

    ARRAY_FOREACH(str, decapitalize);
    assert(0 == strcmp(str, "abcd"));

    return 0;
}
