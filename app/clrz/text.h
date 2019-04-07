#pragma once

enum TextType {TXT_UNKNOWN, TXT_C};

typedef struct TextColorizer
{
    enum TextType type;

    union {

    struct {
    } unknown_txt;

    struct {
        const char** keywords;
        unsigned nr_keywords;
    } c_code;

    };
} TextColorizer;

TextColorizer new_TextColorizer();
