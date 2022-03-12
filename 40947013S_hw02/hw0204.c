#include "hw0204.h"

int main() 
{
    char *q = calloc(4096, sizeof(char));
    fgets(q, 4096, stdin);
    if(strlen(q) == 1) exit_program;
    q[strlen(q)-1] = 0;
    int32_t operand_size = operator_counter(q)+1;
    if(operand_size == 1) exit_program;
    sMixedNumber *p = (sMixedNumber*)calloc(operand_size, sizeof(sMixedNumber));
    int32_t *position = calloc(operand_size-1, sizeof(int32_t));
    bool *priority = calloc(operand_size-1, sizeof(bool));
    categorize(q, position, priority);
    if(set(q, position, operand_size, p)) exit_program;
    /*sMixedNumber one;
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
    mixed_print(all);*/
    return 0;
}