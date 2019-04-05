#pragma once

#include "func/func.h"

struct None {};

typedef struct None None;

enum ResultType {NONE, SOME, ERR};

struct Result
{
    enum ResultType type;

    union {
        int val;
        int err;
        None none;
    };
};

typedef struct Result Result;

#define TEMPLATE_RESULT(Name,T) \
struct Name                     \
{                               \
    enum ResultType type;       \
                                \
    union {                     \
        T val;                  \
        int err;                \
        None none;              \
    };                          \
};                              \
typedef struct Name Name;

#define TEMPLATE_SOME(Name,T) \
struct Name                     \
{                               \
    enum ResultType type;       \
                                \
    union {                     \
        T val;                  \
        None none;              \
    };                          \
};                              \
typedef struct Name Name;

#define GET_SOME(some, or_else) \
({                                                     \
    __auto_type some_ = (some);                        \
    __auto_type or_else_ = (or_else);                  \
    typeof(some_.val) val_ = (some_.type == SOME)      \
        ? some_.val                                    \
        : or_else_;                                    \
    val_;                                              \
})
