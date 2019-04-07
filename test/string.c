/**@file
 * @brief
 * @author    Igor Lesik 2019
 * @copyright Igor Lesik 2019
 *
 */
#include <assert.h>
#include <stdbool.h>

#include "func/strhash.h"

static
bool test_strhash()
{
    const unsigned int good = STRHASH("good");
    const unsigned int bad  = STRHASH("bad");
    const unsigned int ugly = STRHASH("ugly");

    assert(__builtin_constant_p(good));
    //_Static_assert(__builtin_constant_p(good), "value shall be known to be constant at compile time");

    assert(good == strhash("good"));
    assert(bad  == strhash("bad"));
    assert(ugly == strhash("ugly"));

    /*switch (strhash("good")) {
    case STRHASH("good"): break;
    case STRHASH("bad"):
    case STRHASH("ugly"):
    default:
        assert(!"must be good");
    }*/

    return true;
}


int main()
{
    assert(test_strhash());

    return 0;
}

