#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "func/func.h"
#include "func/tcolor.h"
#include "func/string.h"

#include "clrz/text.h"


static const char keyword_clr[] = TCLR_BOLD TCLR_FG(220);
static const char typeword_clr[] = TCLR_BOLD TCLR_FG(130);

void colorize(const char in[], char out[], unsigned size, TextColorizer* clr)
{
    static const char delimeters[] = " \t()[],;:<>+-!?'*";

    const char* p = in;
    out[0] = '\0';

    while (*p != '\0')
    {
        // skip white spaces, brackets, comma and etc.
        while (strchr(delimeters, *p)) {
            strncat(out, p, 1);
            ++p;
        }

        size_t token_sz = strcspn(p, delimeters);
        bool found_keyword = false;

        for (unsigned i = 0; i < clr->c_code.nr_keywords; ++i) {
            const char* keyword = clr->c_code.keywords[i];
            size_t keyword_sz = strlen(keyword); //TODO save keyword length
            if (token_sz == keyword_sz && 0 == strncmp(p, keyword, keyword_sz)) {
                strcat(out, keyword_clr);
                strcat(out, keyword);strcat(out, TCLR_RESET);
                found_keyword = true;
                break;
            }
        }

        if (!found_keyword)
        for (unsigned i = 0; i < clr->c_code.nr_typewords; ++i) {
            const char* keyword = clr->c_code.typewords[i];
            size_t keyword_sz = strlen(keyword); //TODO save keyword length
            if (token_sz == keyword_sz && 0 == strncmp(p, keyword, keyword_sz)) {
                strcat(out, typeword_clr);
                strcat(out, keyword);strcat(out, TCLR_RESET);
                found_keyword = true;
                break;
            }
        }

        if (!found_keyword) {strncat(out, p, token_sz);}
        p += token_sz;
    } 
}

TextType name2type(const char s[])
{
    static const char* clang[] = {"c", "C"};

    if (hasstr(s, clang, SIZEOF_ARRAY(clang))) {
        return TXT_C;
    }

    return TXT_UNKNOWN;
}

int main(int argc, const char* argv[])
{
    enum TextType type = TXT_UNKNOWN;
    if (argc > 1) {
        type = name2type(argv[1]);
    }

    TextColorizer clrz = new_TextColorizer(type);

    char istr[1024];
    char ostr[1024];

    while (fgets(istr, sizeof(istr), stdin) != NULL) {
        colorize(istr, ostr, sizeof(ostr), &clrz);
        fputs(ostr, stdout);
    }

    return EXIT_SUCCESS;
}
