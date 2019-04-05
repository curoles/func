/**@file
 * @brief
 * @author    Igor Lesik 2019
 * @copyright Igor Lesik 2019
 *
 */
#include <assert.h>

#include "func/file.h"

int test_fopen_process_close()
{
    static const char filename[] = "Makefile";

    assert(fopenable(filename, "r"));

    static const char* comment = "1st line:";
    static unsigned int buf_size = 128;

    int print_file(FILE* file) {
        char buf[buf_size];
        puts(comment);
        puts(fgets(buf, buf_size, file));
        return 0;
    }

    int err = fopen_process_close(filename, "r", print_file);

    return err;
}

int main()
{
    assert(0 == test_fopen_process_close());

    return 0;
}
