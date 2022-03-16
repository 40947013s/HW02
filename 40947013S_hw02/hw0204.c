#include "hw0204.h"

int main() 
{
    char *q = calloc(4096, sizeof(char));
    printf("Q:  ");    
    fgets(q, 4096, stdin);
    
    if(strlen(q) == 1) exit_program;
    q[strlen(q)-1] = 0;
    int32_t operand_size = operator_counter(q)+1;
    if(operand_size == 1) exit_program;
    sMixedNumber *p = (sMixedNumber*)calloc(operand_size, sizeof(sMixedNumber));
    sMixedNumber ans;
    int32_t *position = calloc(operand_size-1, sizeof(int32_t));
    bool *priority = calloc(operand_size-1, sizeof(bool));
    categorize(q, position, priority);

    if(!set(q, position, operand_size, p)) exit_program;


    for(int i = 0; i < operand_size-1; i++)
        if(priority[i])
            calculator(&p[i], &p[i+1], kind_of_calculate(q[position[i]]));
    
    for(int i = 0; i < operand_size-1; i++)
        if(priority[i] == 0)
            calculator(&p[i], &p[i+1], kind_of_calculate(q[position[i]]));
        else mixed_cpy(&p[i], &p[i+1]);
    
    printf("A:  ");    
    mixed_print(p[operand_size-1]);
    return 0;
}