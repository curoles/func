#include "clrz/text.h"

#include "func/func.h"

static
const char* c_keywords[] = {"if", "else", "for", "while", "typedef"};


TextColorizer new_TextColorizer()
{
    TextColorizer txt = {
        .type = TXT_C,
        .c_code = {.keywords=c_keywords,
                   .nr_keywords = SIZEOF_ARRAY(c_keywords)}
    };

    return txt;
}

