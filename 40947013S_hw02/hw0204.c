#include "hw0204.h"

int main() 
{
    sMixedNumber one;
    sMixedNumber two;
    sMixedNumber all;
    if(mixed_set(&one, 3, 3, 17) == 0)
        mixed_print(one);
    if(mixed_set(&two, -1, 7, 9) == 0)
        mixed_print(two);
    mixed_add(&all, one, two);
    mixed_print(all);
    mixed_sub(&all, one, two);
    mixed_print(all);
    mixed_mul(&all, one, two);
    mixed_print(all);
    mixed_div(&all, one, two);
    mixed_print(all);
    return 0;
}