/**@file
 * @brief
 * @author    Igor Lesik 2019
 * @copyright Igor Lesik 2019
 *
 */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "func/strhash.h"

static
bool test_strhash()
{
    const unsigned int good = STRHASH("good");
    const unsigned int bad  = STRHASH("bad");
    const unsigned int ugly = STRHASH("ugly");

    assert(good != bad && good != ugly && bad != ugly);

    assert(__builtin_constant_p(good));

    const unsigned int good2 = strhash("good");
    assert(!__builtin_constant_p(good2));

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

    unsigned int str_hash = strhash("good");
    if (str_hash == STRHASH("ok")) {
        assert(0);
    } else if (str_hash == STRHASH("all right")) {
        assert(0);
    } else if (str_hash == STRHASH("good")) {
        //hit
    } else {
        assert(0);
    }


    return true;
}


int main()
{
    assert(test_strhash());

    return 0;
}

