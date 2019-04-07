#pragma once

enum TextType {TXT_UNKNOWN, TXT_C};

typedef enum TextType TextType;

typedef struct TextColorizer
{
    enum TextType type;

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
