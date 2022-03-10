#include "hw0202.h"

void printer(const IEEE ieee, double target)
{
    printf("Sign : %d\n", ieee.sign);
    
    printf("Exponent : ");
    for(int i = 0; i < 11; i++)
        printf("%d", ieee.exponent[i]);
    printf("\n");

    printf("Fraction : ");
    for(int i = 0; i < 52; i++)
        printf("%d", ieee.fration[i]);
    printf("\n");

    printf("%g = (-1)^%d * (1 ", target, ieee.sign);
    for(int i = 0;i < 52; i++)
        if(ieee.fration[i] == 1)
            printf("+ 2^-%d ", i+1);
    
    printf(") * 2^(%d-1023)", ieee.sub);
}

int32_t info_num(int32_t num) //需要多少位元存放整數
{
    int32_t temp = 0;
    for(;pow(2, temp) <= num; temp++);
    return temp;
}

void DtoB(int32_t num, int32_t *arr, int32_t size) //整數部位
{
    int32_t *buf = calloc(size, sizeof(int));
    memset(buf, 0, size);
    int32_t count = 0;
    while(num)
    {
        arr[count++] = num % 2;
        num = num >> 1;
    }
}

void dtob(double num, int32_t *arr, int32_t size) //分數部位
{
    memset(arr, 0, size);   
    for(int i = 1; i < size; i++)
    {
        if(num-pow(2, -i) > 0)
        {
            num -= pow(2, -i);
            arr[i-1] = 1;
        }
        else if(num-pow(2, -i) == 0)
        {
            num -= pow(2, -i);
            arr[i-1] = 1;
            break;
        }
    }
}

void change(IEEE *var, double target)
{
    if(target >= 0) var->sign = 0;
    else var->sign = 1, target = fabs(target);
    //取出整數位
    int32_t integer = target;
    int32_t size_int = info_num(integer);
    int32_t *front = calloc(size_int, sizeof(int));
    DtoB(integer, front, size_int);
    for(int i = 0; i < size_int-1; i++)
        var->fration[i] = front[i+1];
    //取出分數位
    double frac = target-integer;
    int32_t size_frac = 52-(size_int-1);
    int32_t *behind = calloc(size_frac, sizeof(int));
    dtob(frac, behind, size_frac);
    int32_t count_up = 0;
    for(int i = size_int-1; i < 52; i++)
        var->fration[i] = behind[count_up++];
    //計算科學記號的指數位並加上2^10
    int32_t exponent = 1023+size_int-1;
    int32_t size_exp = info_num(exponent);
    var->sub = exponent;
    int32_t *exp = calloc(size_exp, sizeof(int));
    DtoB(exponent, exp, size_exp);
    for(int i = 0; i < 11; i++)
        var->exponent[i] = 0;
    for(int i = size_exp-1, count_down = 10; i >= 0; i--)
        var->exponent[count_down--] = exp[i];
}