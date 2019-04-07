#pragma once

enum TextType {TXT_UNKNOWN, TXT_C};

typedef enum TextType TextType;

typedef struct TextColorizer
{
    enum TextType type;

    const char* blanks;
    const char* sln_comment;

    const char*** kwrds;
    unsigned nr_kw_types;
    const unsigned* nr_kwrds;
    const char** kwtype_clr; 

    union {

    struct {
    } unknown_txt;

    struct {
        const char** keywords;
        unsigned nr_keywords;
        const char** typewords;
        unsigned nr_typewords;
    } c_code;

    };
} TextColorizer;

TextColorizer new_TextColorizer(enum TextType type);
