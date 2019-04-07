#include "clrz/text.h"

#include "func/func.h"

static
const char* c_keywords[] = {
    "if", "else", "for", "while"
};

static
const char* c_typewords[] = {
    "enum", "union", "struct", "typedef"
    "static", "const",
    "int", "unsigned", "long", "char", "float", "double"
};


TextColorizer new_TextColorizer(enum TextType type)
{
    TextColorizer txt = {.type = type};

    switch (type)
    {
    case TXT_C:
        txt = (TextColorizer) {
            .type = TXT_C,
            .c_code = {.keywords=c_keywords,
                       .nr_keywords = SIZEOF_ARRAY(c_keywords),
                       .typewords=c_typewords,
                       .nr_typewords = SIZEOF_ARRAY(c_typewords)
                      }
        };
        break;
    case TXT_UNKNOWN:
    default: {;}
        break;
    }

    return txt;
}

