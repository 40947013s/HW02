#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>

#define PI 3.14159265
#define VAL 180.0/PI 

typedef struct _sVector
{
    uint8_t type;
    union Component
    {
        struct _sCartesian
        {
            double x;
            double y;
        } c;
        struct _sPolar
        {
            double distance;
            double angle;
        } p;
    } data;
}sVector;

sVector *myvector_init()
{
    sVector *res = (sVector *)calloc(1, sizeof(sVector *));
    res->type = 0;
    res->data.c.x = 0;
    res->data.c.y = 0;
    res->data.p.distance = 0;
    res->data.p.angle = 0;
}

int myvector_set( sVector *pVector , uint8_t type, double a, double b )
{
    if(type != 1 && type != 2) return -1;
    else if(type == 1) 
    {
        /*double sum_square = pow(a, 2)+pow(b, 2);
        pVector->data.p.distance = sqrt(sum_square);
        pVector->data.p.angle = VAL * atan(a/b);*/
        pVector->data.c.x = a, pVector->data.c.y = b;
    }
    else
    {
        pVector->data.p.distance = a, pVector->data.p.angle = b/360.0;
        /*pVector->data.c.x = a * cos((b/360.0)*VAL);
        pVector->data.c.y = b * sin((b/360.0)*VAL);*/
    }
    return 0;
}

int main()
{
    sVector *ans = myvector_init();
    myvector_set(ans, 1, 3, 4);
}