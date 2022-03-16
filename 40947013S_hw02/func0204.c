#include "hw0204.h"

int mixed_set(sMixedNumber *pNumber, int32_t a, int32_t b, int32_t c)
{
    if(b >= c || c <= 0 || (a > 0 && b < 0)) return -1;
    if(b == 0 && c != 1) return -1;
    pNumber->a = a, pNumber->b = b, pNumber->c = c;
    return 0;
}

int mixed_print(const sMixedNumber number)
{
    if(number.b == 0)
        if(number.a >= 0) printf("%d\n", number.a);
        else printf("(%d)\n", number.a);
    else 
    {
        if(number.a == 0) 
            printf("%cfrac{%d}{%d}\n", 92, number.b, number.c);
        else if(number.a > 0)
            printf("%d%cfrac{%d}{%d}\n", number.a, 92, number.b, number.c);
        else
            printf("(%d%cfrac{%d}{%d})\n", number.a, 92, number.b, number.c);
    }
    
    return true;
}

void mixed_add(sMixedNumber *pNumber, const sMixedNumber r1, const sMixedNumber r2)
{
    bool sign = false;
    int32_t low = r1.c * r2.c;
    int32_t up_1 = 0 , up_2 = 0;
    up_1 = r1.a >= 0 ? (r1.a*r1.c+r1.b)*r2.c : (r1.a*r1.c-r1.b)*r2.c;
    up_2 = r2.a >= 0 ? (r2.a*r2.c+r2.b)*r1.c : (r2.a*r2.c-r2.b)*r1.c;   
    
    int32_t up =  up_1 + up_2;
    sign = up < 0 ? true : false;
    up = abs(up);
    int32_t i = 2;
    while(i < (up <= low ? up : low))
    {
        if(low % i == 0 && up % i == 0)
            low /= i, up /= i;
        else i++;
    }
    int32_t side = up/low;
    up -= side * low;
    pNumber->a = sign ? -side : side;
    pNumber->b = (sign && side == 0) ? -up : up;
    pNumber->c = pNumber->b == 0 ? 1 : low;
}

void mixed_sub(sMixedNumber *pNumber, const sMixedNumber r1, const sMixedNumber r2)
{
    bool sign = false;
    int32_t low = r1.c * r2.c;
    int32_t up_1 = 0 , up_2 = 0;
    up_1 = r1.a >= 0 ? (r1.a*r1.c+r1.b)*r2.c : (r1.a*r1.c-r1.b)*r2.c;
    up_2 = r2.a >= 0 ? (r2.a*r2.c+r2.b)*r1.c : (r2.a*r2.c-r2.b)*r1.c;   
    
    int32_t up =  up_1 - up_2;
    sign = up < 0 ? true : false;
    up = abs(up);
    int32_t i = 2;
    while(i < (up <= low ? up : low))
    {
        if(low % i == 0 && up % i == 0)
            low /= i, up /= i;
        else i++;
    }
    int32_t side = up/low;
    up -= side * low;
    pNumber->a = sign ? -side : side;
    pNumber->b = (sign && side == 0) ? -up : up;
    pNumber->c = pNumber->b == 0 ? 1 : low;
}

void mixed_mul(sMixedNumber *pNumber, const sMixedNumber r1, const sMixedNumber r2)
{
    bool sign = false;
    int32_t up_1 = r1.a >= 0 ? r1.a*r1.c+r1.b : r1.a*r1.c- r1.b;
    int32_t up_2 = r2.a >= 0 ? r2.a*r2.c+r2.b : r2.a*r2.c- r2.b;    
    
    int32_t up = up_1 * up_2, low = r1.c * r2.c;
    sign = up*low >= 0 ? false : true;
    up = abs(up), low = abs(low);
    int32_t i = 2;
    while(i < (up <= low ? up : low))
    {
        if(low % i == 0 && up % i == 0)
            low /= i, up/= i;
        else i++;
    } 
    int32_t side = up/low;
    up -= side * low;
    pNumber->a = sign ? -side : side;
    pNumber->b = (sign && side == 0) ? -up : up;
    pNumber->c = pNumber->b == 0 ? 1 : low;
}

void mixed_div(sMixedNumber *pNumber, const sMixedNumber r1, const sMixedNumber r2)
{
    bool sign = false;
    int32_t up = r1.a >= 0 ? (r1.a*r1.c+r1.b)*r2.c : (r1.a*r1.c-r1.b)*r2.c;
    int32_t low = r2.a >= 0 ? (r2.a*r2.c+r2.b)*r1.c : (r2.a*r2.c-r2.b)*r1.c; 
   
    sign = up*low >= 0 ? false : true;
    up = abs(up), low = abs(low);
    
    int32_t i = 2;
    while(i < (abs(up) <= abs(low) ? abs(up) : abs(low)))
    {
        if(low % i == 0 && up % i == 0)
            low /= i, up/= i;
        else i++;
    } 
    int32_t side = up/low;
    up -= side * low;
    pNumber->a = sign ? -side : side;
    pNumber->b = (sign && side == 0) ? -up : up;
    pNumber->c = pNumber->b == 0 ? 1 : low;
}

int operator_counter(char *q)
{
    int count = 0;
    for(int i = 1; i < strlen(q)-1; i++)
        if((q[i] == '+'|| q[i] == '-'||q[i] == '*'|| q[i] == '/') && q[i-1] != '(')
            count++, i++;
    return count;
}
void categorize(char *q, int32_t *position, bool *priority)
{
    int count = 0;
    for(int i = 1; i < strlen(q)-1; i++)
    {
        if((q[i] == '+'|| q[i] == '-') && q[i-1] != '(')
        {
            position[count] = i, priority[count++] = false; i++;
        }
        if(q[i] == '*'|| q[i] == '/')
        {
            position[count] = i, priority[count++] = true; i++;
        }
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
        bool sign = false;
        
        //判斷是否為整數為負數    
        if(q[start] == '(' && q[end-1] == ')' && q[start+1] == '-')
        {
            start+=2; end--; sign = true;
        }
        for(int j = start; j < end; j++)
        {
            copy[count++] = q[j];
        }
        int j = start, k, a = 0, b = 0, c = 0;
        for(; q[j] != 92 && j < end; j++);
        if(q[j] != 92)
        {
            for(int k = start; k < end; k++)
            {   
                if(q[k] >= '0' && q[k] <= '9') a = a*10+(q[k]-48);
                else return false;
            }if(sign && a != 0) a *= -1;
            if(sign && a == 0) return false;
            
            if(mixed_set(&p[i], a, 0, 1) == -1) return false;
            continue;
        }
        copy += (j-start+1);
        for(k = start; k < j; k++)
        { 
            if(k == start && q[k] == '-') sign = true;
            if(q[k] >= '0' && q[k] <= '9') a = a*10+(q[k]-48);
            else return false;
        }if(sign && a != 0) a *= -1;
        if(sign && a == 0) return false;
        
        if(!match(copy, "frac{*}{*}")) return false;
        for(; q[j] != '{'; j++); 
        for(k = j+1; q[k] != '}'; k++)
        {
            if(k == start && q[k] == '-') 
            {
                if(sign) return false;
                sign = true;
            }
            else if(q[k] >= '0' && q[k] <= '9') b = b*10+(q[k]-48);
            else return false;
        }if(sign && b != 0 && a == 0) b *= -1;
        if(sign && b == 0) return false;
        
        if(q[k+1] != '{') return false;
        for(k+=2; k < end-1; k++)
        {
            if(q[k] >= '0' && q[k] <= '9') c = c*10+(q[k]-48);
            else return false;
        }
        if(mixed_set( &p[i], a, b, c) == -1) return false;
    }
    return true;
}

void calculator(sMixedNumber *r1,sMixedNumber *r2, int i)
{    
    switch(i)
    {
        case 1:
        { mixed_add(r1, *r1, *r2); *r2 = *r1; break; }
        case 2:
        { mixed_sub(r1, *r1, *r2); *r2 = *r1; break; }
        case 3:
        { mixed_mul(r1, *r1, *r2); *r2 = *r1; break; }
        case 4:
        { mixed_div(r1, *r1, *r2); *r2 = *r1; break; }
    }
}

void mixed_cpy(sMixedNumber *r1,sMixedNumber *r2)
{
    *r2 = *r1;
}

int kind_of_calculate(char c)
{
    switch(c)
    {
        case '+': return 1;
        case '-': return 2;
        case '*': return 3;
        case '/': return 4;        
    }
    return -1;
}