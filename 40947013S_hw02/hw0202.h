#ifndef HW0202_H_INCLUDE
#define HW0202_H_INCLUDE

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define exit_program printf("Invaild input.\n"),\
exit(0);

typedef struct _IEEE
{
    bool sign;
    int32_t exponent[11];
    int32_t fraction[52];
    int32_t sub;
}IEEE;

void printer(const IEEE ieee, double target);
int32_t info_num(int32_t num);
void DtoB(int32_t num, int32_t *arr, int32_t size);
void dtob(double num, int32_t *arr, int32_t size);
void change(IEEE *var, double target);

#endif