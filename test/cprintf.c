#include "func/cprintf.h"

PrintCirBuf printbuf = {
    .printf = cprintf,
    .dump = cprintf_dump,
    .file = NULL,
    .pos  = 0,
    .size = 1024,
    .buf  = { [0 ... 1023] = '\0'}
};

__attribute__((destructor))
void dump_printbuf_at_exit() 
{
    cprintf_dump(&printbuf, stdout);
}

int main(void)
{
    cprintf(&printbuf, "buf #1\n");
    cprintf(&printbuf, "buf size %lu\n", printbuf.size);
    for (unsigned i = 0; i < 10/*24*/; ++i)
        printbuf.printf(&printbuf, "%lu %u %u %u\n", printbuf.pos, i, i+1, i+2);

    PrintCirBuf* b2 = new_PrintCirBuf(stdout, 20);
    b2->printf(b2, "2: %u %u %u\n", 1, 2, 3);
    b2->printf(b2, "2: %u %u %u\n", 4, 5, 6);
    b2->printf(b2, "2: %u %u %u\n", 7, 8, 9);
    b2->dump(b2, stdout);
    free(b2);

    return 0;
}
