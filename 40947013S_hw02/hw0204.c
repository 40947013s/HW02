#include "hw0204.h"
#include "mymatch.h"
int operator_counter(char *q)
{
    int count = 0;
    for(int i = 1; i < strlen(q)-1; i++)
        if(q[i] == '+'|| q[i] == '-'||q[i] == '*'|| q[i] == '/')
            count++;
    return count;
}
void categorize(char *q, int32_t *position, bool *priority)
{
    int count = 0;
    for(int i = 1; i < strlen(q)-1; i++)
    {
        if(q[i] == '+'|| q[i] == '-')
            position[count] = i, priority[count++] = false;
        if(q[i] == '*'|| q[i] == '/')
            position[count] = i, priority[count++] = true;
    }        
}

bool set(char *q, int32_t *position, int n, sMixedNumber *p)
{
    for(int i = 0; i < n; i++)
    {
        int start = i == 0 ? 0 : position[i-1]+1;
        int end = i == n-1 ? strlen(q) : position[i];
        if(end - start == 0) return false;        
        char *copy = calloc(end-start, sizeof(char));
        int count = 0;
        for(int j = start; j < end; j++)
            copy[count++] = q[j];
        
        if(copy[0] == '0' && count == 1) 
        {
            mixed_set( &p[i], 0, 0, 0);
            continue;
        }
        int j = start, k, a = 0, b, c;
        for(; q[j] != 92 && j < end; j++);
        if(q[j] != 92) return false;
        copy += (j-start+1);
        printf("%s\n", copy);
        for(k = start; k < j; k++)
        {
            if(q[k] >= '0' && q[k] <= '9') a = a*10+q[k];
            else return false;
        }
        
        if(!match(copy, "frac{*}{*}")) return false;
        for(; q[j] != '{'; j++); 
        for(k = j+1; q[k] != '}'; k++)
        {
            if(q[k] >= '0' && q[k] <= '9') b = b*10+q[k];
            else return false;
        }
        if(q[k+1] != '{') return false;
        for(k++; k < end; k++)
        {
            printf("%c", q[k]);
            if(q[k] >= '0' && q[k] <= '9') c = c*10+q[k];
            else return false;
        }printf("\n"); 
        mixed_set( &p[i], a, b, c);
    }
    return true;
}

int main() 
{
    char *q = calloc(4096, sizeof(char));
    fgets(q, 4096, stdin);
    if(strlen(q) == 0) 
    {
        printf("Wrong input. Exit program.\n"); return 0;
    }
    else q[strlen(q)-1] = 0;
    int32_t operand_size = operator_counter(q)+1;
    if(operand_size == 1) return 0;
    sMixedNumber *p = (sMixedNumber*)calloc(operand_size, sizeof(sMixedNumber));
    int32_t *position = calloc(operand_size-1, sizeof(int32_t));
    bool *priority = calloc(operand_size-1, sizeof(bool));
    categorize(q, position, priority);
    /*for(int i = 0; i < operand_size-1; i++)
        printf("%d %d\n", position[i], position[i]);*/
    set(q, position, operand_size, p);
    mixed_print(p[0]);
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