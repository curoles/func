#include <assert.h>

#define ANCHOR_EXTERN_INLINE

#define T int
#define V VectInt
#define new_V new_VectInt
#define cleanup_V cleanup_VectInt
#include "func/vector.h"

#if defined(T) || defined(V) || defined(new_V) || defined(cleanup_V)
#error vector.h must undef all "template" macros
#endif

bool test1(void)
{
    VectInt v CLEANUP(cleanup_VectInt) = new_VectInt(1);

    assert(v.size == 0);

    v.push_back(&v, 1);

    assert(v.size == 1 && v.item[0] == 1);

    v.push_back(&v, 2);

    assert(v.size == 2 && v.item[0] == 1 && v.item[1] == 2);

    v.push_back(&v, 3);

    assert(v.size == 3 && v.item[0] == 1 && v.item[1] == 2 && v.item[2] == 3);

    v.foreach(&v, lambda(void, (unsigned i, int* e) {
         assert(*e == (i + 1));
    }));

    return true;
}

int main()
{
    assert(test1());

    return 0;
}
