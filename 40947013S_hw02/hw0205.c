#include <stdio.h>

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
    
}

int myvector_set( sVector *pVector , uint8_t type, double a, double b )
{
    
}

int main()
{
    
}