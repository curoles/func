#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "func/tcolor.h"
#include "func/func.h"

#include "clrz/text.h"


static const char keyword_clr[] = TCLR_BOLD TCLR_FG(220);

void colorize(const char in[], char out[], unsigned size, TextColorizer* clr)
{
    static const char delimeters[] = " \t()[],;:<>+-!?'";

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
            if (0 == strncmp(p, keyword, MAX(token_sz, strlen(keyword)))) {
                strcat(out, keyword_clr);
                strcat(out, keyword);strcat(out, TCLR_RESET);
                found_keyword = true;
                break;
            }
        }
        if (!found_keyword) {strncat(out, p, token_sz);}
        p += token_sz;
    } 
}

int main()
{
    TextColorizer clrz = new_TextColorizer();

    char istr[1024];
    char ostr[1024];

    while (fgets(istr, sizeof(istr), stdin) != NULL) {
        colorize(istr, ostr, sizeof(ostr), &clrz);
        fputs(ostr, stdout);
    }

    return EXIT_SUCCESS;
}
