/**@file
 * @brief
 * @author    Igor Lesik 2019
 * @copyright Igor Lesik 2019
 *
 */
#include <assert.h>

#include "func/func.h"

int main()
{
    int (*max)(int, int) = lambda (PURE int, (int x, int y) { return x > y ? x : y; });

    assert(max(3,7) == 7);

    int var_a = 9;
    int (*inc_var_a)(void) = lambda (int, (void) { return ++var_a; });
    inc_var_a();
    assert(var_a == 10);
    assert(inc_var_a() == 11);

    UNUSED PURE int i_am_pure(int a, int b) {return a + b;}

    return 0;
}
