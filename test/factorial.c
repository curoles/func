/**@file
 * @brief
 * @author    Igor Lesik 2019
 * @copyright Igor Lesik 2019
 *
 */
#include <assert.h>

#include "func/factorial.h"

int my_factorial(int x) {
    if (x == 0)
        return 1;
    else
        return x * my_factorial(x - 1);
}

int main()
{
    assert(factorial(4,1) == 4*3*2*1);

    for (unsigned i = 0; i < 10; ++i) {
        assert(factorial(i, 1) == my_factorial(i));
    }

    return 0;
}
