#include "clrz/text.h"

#include "string.h"

#include "func/func.h"
#include "func/tcolor.h"

static
const char* c_keywords[] = {
    "if", "else", "for", "while", "return",
    "break", "continue"
};

static
const char* c_typewords[] = {
    "enum", "union", "struct", "typedef",
    "static", "const", "void",
    "int", "unsigned", "long", "char", "float", "double"
};

static
const char* c_pragmas[] = {
    "include", "define", "pragma"
};

static
const char* c_stdfuncs[] = {
    "exit", "abort", "assert",
    "puts", "printf"
};

static
const char** c_kwrds[] = {
    c_keywords, c_typewords, c_pragmas, c_stdfuncs
};

static
const unsigned c_nr_kwrds[] = {
    SIZEOF_ARRAY(c_keywords), SIZEOF_ARRAY(c_typewords), 
    SIZEOF_ARRAY(c_pragmas), SIZEOF_ARRAY(c_stdfuncs)
};

static
const char* c_kwtype_clr[] = {
    TCLR_BOLD TCLR_FG(220), TCLR_BOLD TCLR_FG(142), TCLR_FG(1),
    TCLR_FG(50)
};

TextColorizer new_TextColorizer(enum TextType type)
{
    TextColorizer txt = {.type = type};

    switch (type)
    {
    case TXT_C:
        txt = (TextColorizer) {
            .type = TXT_C,
            .blanks = " \t",
            .sln_comment = "//",
            .kwrds = c_kwrds,
            .nr_kw_types = SIZEOF_ARRAY(c_kwrds),
            .nr_kwrds = c_nr_kwrds,
            .kwtype_clr = c_kwtype_clr,
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

