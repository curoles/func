/**@file
 * @brief
 * @author    Igor Lesik 2019
 * @copyright Igor Lesik 2019
 *
 */
#pragma once

#include <stdio.h>
#include <errno.h>

#include "func/func.h"
#include "func/result.h"

EXTERN_INLINE
void fcleanup(FILE** f) { fclose(*f); }

EXTERN_INLINE
__attribute__((nonnull (1, 2, 3)))
Result fopen_process_close(
    const char filename[],
    const char mode[],
    int (*process)(FILE*) ///< closure with context that processes opened file
)
{
    FILE* file = fopen(filename, mode);

    if (file == NULL) {
        return (Result){.type=ERR, .err=errno};
    }

    Result res = {.type=SOME, .val=process(file)};
    fclose(file);

    return res;
}

EXTERN_INLINE
__attribute__((nonnull (1, 2)))
bool fopenable(
    const char filename[],
    const char mode[]
)
{
    FILE* file CLEANUP(fcleanup) = fopen(filename, mode);

    return file != NULL;
}
