#include "hw0204.h"

int mixed_set(sMixedNumber *pNumber, int32_t a, int32_t b, int32_t c)
{
    if(b != 0 && c == 0) return -1;
    if(b == 0 && c != 0) return -1;
    if(a != 0 && (b < 0 || c < 0)) return -1;
    if(b >= c) return -1;
    pNumber->a = a, pNumber->b = b, pNumber->c = c;
    return 0;
}

int mixed_print(const sMixedNumber number)
{
    printf( "(%d,%d,%d)\n", number.a, number.b, number.c);
    return true;
}

void mixed_add(sMixedNumber *pNumber, const sMixedNumber r1, const sMixedNumber r2)
{
    int32_t low = r1.c * r2.c;
    int32_t up_1 = 0 , up_2 = 0;
    if(r1.a >= 0) up_1 = (r1.a * r1.c + r1.b) * r2.c;
    else up_1 = (r1.a * r1.c - r1.b) * r2.c;
    if(r2.a >= 0) up_2 = (r2.a * r2.c +r2.b) * r1.c;
    else up_2 = (r2.a * r2.c - r2.b) * r1.c;
    
    int32_t up =  up_1 + up_2;
    pNumber->a = up / low;
    up -= pNumber->a * low;
    
    int32_t i = 2;
    while(i < up)
    {
        if(low % i == 0 && up % i == 0)
            low /= i, up /= i;
        else i++;
    }
    pNumber->b = up;
    pNumber->c = low;
}

void mixed_sub(sMixedNumber *pNumber, const sMixedNumber r1, const sMixedNumber r2)
{
    int32_t low = r1.c * r2.c;
    int32_t up_1 = 0 , up_2 = 0;
    if(r1.a >= 0) up_1 = (r1.a * r1.c + r1.b) * r2.c;
    else up_1 = (r1.a * r1.c - r1.b) * r2.c;
    if(r2.a >= 0) up_2 = (r2.a * r2.c + r2.b) * r1.c;
    else up_2 = (r2.a * r2.c - r2.b) * r1.c;
    int32_t up =  up_1 - up_2 ;
    
    pNumber->a = up / low;
    up -= pNumber->a * low;
    int32_t i = 2;
    while(i < up)
    {
        if(low % i == 0 && up % i == 0)
            low /= i, up /= i;
        else
            i++;
    }
    pNumber->b = up;
    pNumber->c = low;
}

void mixed_mul(sMixedNumber *pNumber, const sMixedNumber r1, const sMixedNumber r2)
{
    int32_t up_1 = 0 , up_2 = 0;
    if( r1.a >= 0) up_1 = (r1.a * r1.c + r1.b);
    else up_1 = (r1.a * r1.c - r1.b);
    if(r2.a >= 0) up_2 = (r2.a * r2.c + r2.b);
    else up_2 = (r2.a * r2.c - r2.b);
    
    int32_t up = up_1 * up_2;
    int32_t low = r1.c * r2.c;
    if(up * low < 0)
        up = -abs(up), low = abs(low);
    
    int32_t i = 2;
    while(i < (up>low ? abs(up):low))
    {
        if(low % i == 0 && up % i == 0)
            low /= i, up/= i;
        else i++;
    } 
    pNumber->a = up / low;  
    up -= pNumber->a * low;
    pNumber->b = abs(up);
    pNumber->c = low;
}

void mixed_div(sMixedNumber *pNumber, const sMixedNumber r1, const sMixedNumber r2)
{
    int32_t low = 0 , up = 0;
    if(r2.a >= 0) low = (r2.a * r2.c + r2.b) * r1.c;
    else low = (r2.a * r2.c - r2.b) * r1.c;
    if(r1.a >= 0) up = (r1.a * r1.c + r1.b) * r2.c;
    else up = (r1.a * r1.c - r1.b) * r2.c;
    if(up * low < 0)
        up = -abs(up), low = abs(low);
    
    int32_t i = 2;
    while(i < (up>low ? abs(up):low))
    {
        if(low % i == 0 && up % i == 0)
            low /= i, up/= i;
        else i++;
    } 
    pNumber->a = up / low;  
    up -= pNumber->a * low;
    pNumber->b = abs(up);
    pNumber->c = low;
}

int operator_counter(char *q)
{
    int count = 0;
    for(int i = 1; i < strlen(q)-1; i++)
        if(q[i] == '+'|| q[i] == '-'||q[i] == '*'|| q[i] == '/')
            count++, i++;
    return count;
}
void categorize(char *q, int32_t *position, bool *priority)
{
    int count = 0;
    for(int i = 1; i < strlen(q)-1; i++)
    {
        if(q[i] == '+'|| q[i] == '-')
            position[count] = i, priority[count++] = false, i++;
        if(q[i] == '*'|| q[i] == '/')
            position[count] = i, priority[count++] = true, i++;
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
        int j = start, k, a = 0, b = 0, c = 0;
        for(; q[j] != 92 && j < end; j++);
        if(q[j] != 92) return false;
        copy += (j-start+1);
        bool sign_of_a = 0;
        for(k = start; k < j; k++)
        {
            if(k == start && q[k] == '-') sign_of_a = true;            
            else if(q[k] >= '0' && q[k] <= '9') a = a*10+(q[k]-48);
            else return false;
        }if(sign_of_a) a *= -1;
        
        if(!match(copy, "frac{*}{*}")) return false;
        for(; q[j] != '{'; j++); 
        for(k = j+1; q[k] != '}'; k++)
        {
            if(q[k] >= '0' && q[k] <= '9') b = b*10+(q[k]-48);
            else return false;
        }
        if(q[k+1] != '{') return false;
        for(k+=2; k < end-1; k++)
        {
            if(q[k] >= '0' && q[k] <= '9') c = c*10+(q[k]-48);
            else return false;
        }
        mixed_set( &p[i], a, b, c);
    }
    return true;
}