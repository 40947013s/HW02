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

int myvector_set(sVector *pVector, uint8_t type, double a, double b)
{
    if(type != 1 && type != 2) return -1;
    else if(type == 1) 
        pVector->data.c.x = a, pVector->data.c.y = b;
    else
    {
        pVector->data.p.distance = a;
        if(a < 0 || a >= 360) return -1;        
        pVector->data.p.angle = b;   
    }    
    pVector->type = type;
    return 0;
}

int myvector_print(const sVector *pVector, uint8_t type)
{
    if(type != pVector->type) return -1;
    if(type == 1) 
        printf("(%g, %g)\n", pVector->data.c.x,pVector->data.c.y);
    else
        printf("(%g, %g-pi)\n", pVector->data.p.distance,pVector->data.p.angle/180.0);
    return 0;
}

int myvector_add(sVector *pA, const sVector *pB, const sVector *pC)
{
    pA->type = pB->type;
    if(pB->type == pC->type == 1)
    {
        pA->data.c.x = pB->data.c.x + pC->data.c.x;
        pA->data.c.y = pB->data.c.y + pC->data.c.y;        
    }
    else if(pB->type == pC->type == 2)
    {
        double x = pB->data.p.distance*cos(pB->data.p.angle*VAL) + pC->data.p.distance*cos(pC->data.p.angle*VAL);
        double y = pB->data.p.distance*sin(pB->data.p.angle*VAL) + pC->data.p.distance*sin(pC->data.p.angle*VAL);
        pA->data.p.distance = sqrt(pow(x, 2)+pow(y, 2));
        pA->data.p.angle = atan(x/y)*val;
    }
}



int main()
{
    sVector *ans = myvector_init();
    sVector *one = myvector_init();
    sVector *two = myvector_init();
    myvector_set(one, 2, 3, 90.0);
    myvector_set(two, 2, 3, 45.0);
    myvector_print(ans, 2);
}