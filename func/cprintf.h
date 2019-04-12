/** Print into a circural buffer in memory.
 *
 *
 */
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>

struct PrintCirBuf
{
    void (*printf)(struct PrintCirBuf*, const char* fmt, ...);
    void (*dump)(struct PrintCirBuf*, FILE*);

    FILE* file;
    size_t pos;
    size_t size;
    char buf[];
};

typedef struct PrintCirBuf PrintCirBuf;

extern inline
void cprintf(PrintCirBuf* buf, const char* fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    //TODO handle wrapping
    int slen = vsnprintf(&buf->buf[buf->pos], buf->size - buf->pos, fmt, args);
    va_end(args);

    if (slen > 0) {
        buf->pos = (buf->pos + slen) % buf->size;
    }
}

extern inline
void cprintf_dump(PrintCirBuf* pb,  FILE* f)
{
    f = f ? :pb->file;

    char c = '\n';
    for (size_t i = 0; i < pb->size; ++i) {
        if (c=='\n' || isprint(c)) {putc(c, f);}
        c = pb->buf[(pb->pos + i) % pb->size];
    }
    putc('\n', f);
}

extern inline
PrintCirBuf* new_PrintCirBuf(FILE* file, size_t size)
{
    PrintCirBuf* buf = (PrintCirBuf*)malloc(sizeof(PrintCirBuf) + size);
    buf->size = size;
    buf->pos = 0;
    buf->file = file;

    buf->printf = cprintf;
    buf->dump = cprintf_dump;

    return buf;
}

