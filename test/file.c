/**@file
 * @brief
 * @author    Igor Lesik 2019
 * @copyright Igor Lesik 2019
 *
 */
#include <assert.h>

#include "func/file.h"

static
bool test_cleanup()
{
    static const char filename[] = "Makefile";

    void fcleanup(FILE** f) { fclose(*f); }

    UNUSED FILE* file CLEANUP(fcleanup) = fopen(filename, "r");

    return true;
}

static
bool test_fopen_process_close()
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

    Result res = fopen_process_close(filename, "r", print_file);
    assert(res.type != ERR);

    res = fopen_process_close(filename, "r", lambda(int, (FILE* file) {
        return 123;}));
    assert(res.type == SOME && res.val == 123);

    return true;
}

int main()
{
    assert(test_fopen_process_close());
    assert(test_cleanup());

    return 0;
}
