#ifndef HW0205_H_INCLUDE
#define HW0205_H_INCLUDE

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>

#define PI 3.14159265

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

sVector *myvector_init();
int myvector_set(sVector *pVector, uint8_t type, double a, double b);
void ctop(const sVector *c, double *distance, double *angle);
void ptoc(const sVector *p, double *x, double *y);
int myvector_print(const sVector *pVector, uint8_t type);
int myvector_add(sVector *pA, const sVector *pB, const sVector *pC);
int myvector_inner_product(double *pA, const sVector *pB, const sVector *pC);
int myvector_area(double *pA, const sVector *pB, const sVector *pC);
int myvector_cvp(double *pX, double *pY, const double *pTx, const double *pTy, const sVector *pA, const sVector *pB);

#endif