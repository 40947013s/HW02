#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

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

sVector * myvector_init()
{
    sVector *res = (sVector *)calloc(1, sizeof(sVector *));
    res->type = 0;
    res->data.c.x = 0;
    res->data.c.y = 0;
    res->data.p.distance = 0;
    res->data.c.angle = 0;
}

int myvector_set( sVector *pVector , uint8_t type, double a, double b )
{
    double x, y, distance, angle; 
    if(type != 1 || type != 2) return -1;
    else if(type == 1) 
    {
        x = a, y = b;
        distance = sqrt(pow(a, 2)+pow(b, 2));
        
    }
}

int main()
{
    
}