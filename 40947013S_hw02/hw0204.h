#ifndef HW0204_H_INCLUDE
#define HW0204_H_INCLUDE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

typedef struct _sMixedNumber 
{
    int32_t a;
    int32_t b;
    int32_t c;
}sMixedNumber;

int mixed_set(sMixedNumber *pNumber, int32_t a, int32_t b, int32_t c);
int mixed_print(const sMixedNumber number);
void mixed_add(sMixedNumber *pNumber, const sMixedNumber r1, const sMixedNumber r2);
void mixed_sub(sMixedNumber *pNumber, const sMixedNumber r1, const sMixedNumber r2);
void mixed_mul(sMixedNumber *pNumber, const sMixedNumber r1, const sMixedNumber r2);
void mixed_div(sMixedNumber *pNumber, const sMixedNumber r1, const sMixedNumber r2);

#endif