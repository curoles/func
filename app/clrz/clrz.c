#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "func/tcolor.h"

enum TextType {TXT_UNKNOWN, TXT_C};

static
const char* c_keywords[] = {"if", "for"};

typedef struct Text
{
    enum TextType type;

    union {

    struct {
    } unknown_txt;

    struct {
        const char** keywords;
    } c_code;

    };
} Text;

Text init()
{
    Text txt = {
        .type = TXT_C,
        .c_code = {.keywords=c_keywords}
    };

    return txt;
}

void colorize(const char in[], char out[], unsigned size)
{
    strncpy(out, in, size);
}

int main()
{
    char istr[1024];
    char ostr[1024];

    while (fgets(istr, sizeof(istr), stdin) != NULL) {
        colorize(istr, ostr, sizeof(ostr));
        fputs(ostr, stdout);
    }

    return EXIT_SUCCESS;
}
