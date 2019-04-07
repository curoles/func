#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "func/func.h"
#include "func/tcolor.h"
#include "func/string.h"

#include "clrz/text.h"


static const char comment_clr[]  = TCLR_FG(32);

void colorize(const char in[], char out[], unsigned size, TextColorizer* txt)
{
    static const char delimeters[] = " \t()[],;:<>+-!?'*";

    const char* p = in;
    out[0] = '\0';

    while (*p != '\0')
    {
        // skip white spaces
        while (strchr(txt->blanks, *p)) {
            strncat(out, p, 1);
            ++p;
        }

        if (isalpha(*p))
        {
            size_t token_sz = strcspn(p, delimeters);
            bool found_keyword = false;

            for (unsigned i = 0; i < txt->nr_kw_types && !found_keyword; ++i) {
                const char** kwrds = txt->kwrds[i];
                for (unsigned k = 0; k < txt->nr_kwrds[i]; ++k) {
                    const char* keyword = kwrds[k];
                    size_t keyword_sz = strlen(keyword);
                    if (token_sz == keyword_sz && 0 == strncmp(p, keyword, keyword_sz)) {
                        strcat(out, txt->kwtype_clr[i]);
                        strcat(out, keyword);
                        strcat(out, TCLR_RESET);
                        found_keyword = true;
                        break;
                    }
                }
            }
            if (!found_keyword) {strncat(out, p, token_sz);}
            p += token_sz;

        } else { // not alphabetic symbol
            if (0 == strncmp(p, txt->sln_comment, strlen(txt->sln_comment))) {
                strcat(out, comment_clr);
                strcat(out, p);
                strcat(out, TCLR_RESET);
                break;
            } else {
                strncat(out, p, 1);
                ++p;
            }
        }

    } 
}

TextType name2type(const char s[])
{
    static const char* clang[] = {"c", "C", NULL};
    static const char* cpplang[] = {"c++", "C++", NULL};
    static const char** all_types[] = {clang, cpplang};

    if (hasstr(s, clang, SIZEOF_ARRAY(clang))) {
        return TXT_C;
    } else {
        printf("Usage:\nclrz <file type>\nTypes:\n");
        for (unsigned i = 0; i < SIZEOF_ARRAY(all_types); ++i) {
            for (const char** t = all_types[i]; *t != NULL; ++t)
                printf("%s ", *t);
            puts("");
        }
        exit(1);
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
