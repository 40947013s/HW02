#include <stdio.h>

typedef struct _sVector
{
    uint8_t type; // 1: Cartesian coordinates; 2: polar coordinates
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

int main()
{
    
}