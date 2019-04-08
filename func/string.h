#pragma once

#include <alloca.h>
#include <stdio.h>

/** Use current function stack to allocate memory for snprintf.
*
* @return pointer to "printed" string, memory will be automatically
*         freed on the function return.
*
* Example:
* int main() {
*     char *tmp[5];
*     tmp[0] = SSPRINTF("This text is dynamically allocated");
*     tmp[1] = SSPRINTF("on the stack frame of main() and doesn't");
*     tmp[2] = SSPRINTF("need to be freed explicitely. It is");
*     tmp[3] = SSPRINTF("automatically freed when the function returns.");
*     tmp[4] = SSPRINTF("%s\n%s\n%s\n%s\n", tmp[0], tmp[1], tmp[2], tmp[3]);
*     printf("\nt: %p\t0: %p\t1: %p\n2: %p\t3: %p\t4: %p\n\n%s\n",
*                     tmp, tmp[0], tmp[1], tmp[2], tmp[3], tmp[4], tmp[4]);
*     return 0;
*  }
*/
#define SSPRINTF(...) \
    ({ int _ss_size = snprintf(0, 0, ##__VA_ARGS__);        \
    char *_ss_ret = __builtin_alloca(_ss_size+1);           \
    snprintf(_ss_ret, _ss_size+1, ##__VA_ARGS__);           \
    _ss_ret; })
