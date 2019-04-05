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

extern inline
__attribute__((nonnull (1, 2, 3)))
int fopen_process_close(
    ccstr filename,
    ccstr mode,
    int (*process)(FILE*) ///< closure with context that processes opened file
)
{
    int err = 0;

    FILE* file = fopen(filename, mode);

    if (file == NULL) {
        return errno;
    } else {
        err = process(file);
        fclose(file);
    }

    return err;
}

extern inline
__attribute__((nonnull (1, 2)))
bool fopenable(
    ccstr filename,
    ccstr mode
)
{
    FILE* file = fopen(filename, mode);

    if (file != NULL) {
        fclose(file);
    }

    return file != NULL;
}
