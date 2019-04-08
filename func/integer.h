#pragma once

#include <stdint.h>

#include "func/func.h"

typedef          __int128   int128_t;
typedef unsigned __int128  uint128_t;

/*
* Function argument corresponding to a transparent union type
* can be of any type in the union; no cast is required.
* foo(int_union_t); f(-1); f(0x80);
*/
typedef union int_union {
    int s;                        // signed
    unsigned int u;               // unsigned
    unsigned char b[sizeof(int)]; // bytes

} int_union_t TRANSPARENT_UNION;

typedef union int16_union {
    int16_t s;                        // signed
    uint16_t u;                       // unsigned
    unsigned char b[sizeof(int16_t)]; // bytes

    struct {
        uint8_t lsb;
        uint8_t msb;
    } le;

    struct {
        uint8_t msb;
        uint8_t lsb;
    } be;

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    struct { uint8_t lsb; uint8_t msb;};
#else
    struct { uint8_t msb; uint8_t lsb;};
#endif
} int16_union_t TRANSPARENT_UNION;

#if 0
typedef union {
  float value;
  struct {
    unsigned int mantissa:23;
    unsigned int exponent:8;
    unsigned int negative:1;
  };
} ieee754_float_t;
  
ieee754_float_t f = (ieee754_float_t) 42.f;
printf("mantissa = %u, exponent = %u, negative = %u", f.mantissa, f.exponent, f.negative);
// mantissa = 2621440, exponent = 132, negative = 0
#endif
