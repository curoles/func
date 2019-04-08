#include <assert.h>

#include "func/integer.h"

bool test_int64_union(void)
{
    int16_union_t i = (int16_union_t) (uint16_t) 0xb1dd;

    assert(i.u == 0xB1DD);

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    assert(i.le.msb == 0xB1 && i.le.lsb == 0xDD);
    assert(i.be.lsb == 0xB1 && i.be.msb == 0xDD);
#endif

    assert(i.msb == 0xB1 && i.lsb == 0xDD);

    return true;
}

int main(void)
{
    assert(test_int64_union());

    return 0;
}
