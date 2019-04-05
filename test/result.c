#include <assert.h>
#include <stdio.h>

#include "func/result.h"

void print_result(Result r)
{
    switch (r.type) {
    case NONE: puts("None"); break;
    case SOME: printf("Some %d\n", r.val); break;
    case ERR:  printf("Error %d\n", r.err); break;
    }
}

TEMPLATE_RESULT(ResultUInt64, uint64_t)
TEMPLATE_SOME(SomeInt, int)

int main()
{
    UNUSED None none = ((None) {});

    UNUSED int some_kind = SOME;
    assert(some_kind == 1);

    SomeInt some1 = {.type = SOME, .val = 123};
    assert(GET_SOME(some1, 0) == 123);

    some1.type = NONE;
    assert(GET_SOME(some1, 321) == 321);

    UNUSED Result r1 = {.type = NONE};
    UNUSED Result r2 = {.type = SOME, .val = 7};
    UNUSED Result r3 = {.type = ERR, .err = -7};
    UNUSED ResultUInt64 r4 = {.type = SOME, .val = 8UL};

    print_result(r1);
    print_result(r2);
    print_result(r3);

    return 0;
}
